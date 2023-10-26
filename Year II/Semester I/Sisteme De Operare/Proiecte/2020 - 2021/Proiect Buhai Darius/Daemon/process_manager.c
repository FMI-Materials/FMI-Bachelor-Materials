#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "process_manager.h"
#include "memory_manager.h"
#include "signal_manager.h"
#include "../Worker/analyzer.h"

int task_cnt = 0;
struct task_details tasks[MAX_PROCESSES];

void update_ids() {
    /// Update task statuses according to the changes made by workers
    for (int i = 1; i <= task_cnt; ++i) {
        int *task_details = get_task_details(i);
        if (task_details != NULL)
            tasks[i].status = *task_details;
    }
}

void take_new_task() {
    int *process_counter = get_process_counter();
    if (*process_counter == ALLOWED_PROCESSES)
        return;

    close_shm_ptr(process_counter, sizeof(*process_counter));

    int next_task_id = -1;
    // Look for a pending task and start a process for it
    for (int i = 1; i <= task_cnt; ++i) {
        if (tasks[i].status != PENDING) continue;
        if (next_task_id == -1 || tasks[i].priority > tasks[next_task_id].priority) {
            next_task_id = i;
        }
    }

    // no new task
    if (next_task_id == -1) {
        return;
    }

    puts("found new task");
    // found new task
    pid_t pid = fork();

    if (pid < 0) {
        perror("couldn't fork child");
        return;
    }

    if (pid == 0) {
        process_counter = get_process_counter();
        int *task_details = get_task_details(next_task_id);
        *task_details = PROCESSING;

        *process_counter += 1;
        printf("%s, %d\n", tasks[next_task_id].path, next_task_id);

        analyze(tasks[next_task_id].path, next_task_id);
        *process_counter -= 1;

        *task_details = DONE;
        close_shm_ptr(task_details, sizeof(*task_details) * getpagesize());
        close_shm_ptr(process_counter, sizeof(*process_counter));
        exit(0);
    } else {
        tasks[next_task_id].status = PROCESSING;
        tasks[next_task_id].worker_pid = pid;
    }
}

int process_signal(struct signal_details signal) {
    // adding a new task in the task list

    if (signal.type == ADD) {
        char output[1024];
        for (int i = 1; i <= task_cnt; ++i) {
            if (tasks[i].status == REMOVED) continue;
            if (is_prefix(tasks[i].path, signal.path)) {
                sprintf(output, "Directory `%s` is already included in analysis with ID `%d`",
                        signal.path, i);
                write_daemon_output(output);
                send_signal(signal.ppid);
                return 0;
            }
        }

        ++task_cnt;

        // add task to list
        tasks[task_cnt].task_id = task_cnt;
        strcpy(tasks[task_cnt].path, signal.path);
        tasks[task_cnt].status = PENDING;
        tasks[task_cnt].priority = signal.priority;
        tasks[task_cnt].worker_pid = -1;

        // update task_status in shm
        int *task_details = get_task_details(task_cnt);
        *task_details = PENDING;
        close_shm_ptr(task_details, (int)sizeof(*task_details) * getpagesize());

        sprintf(output, "Created analysis task with ID `%d` for `%s` and priority `%s`",
                task_cnt, tasks[task_cnt].path, get_literal_priority(tasks[task_cnt].priority));

        char *status_path = get_current_path();
        strcat(status_path, STATUS_PATH);
        sprintf(status_path, status_path, task_cnt);
        remove(status_path);

        FILE *status_fd = safe_fopen(status_path, "w");
        fprintf(status_fd, "%d%%\n%d files\n%d dirs", 0, 0, 0);
        safe_fclose(status_fd);

        write_daemon_output(output);
        send_signal(signal.ppid);
        return 0;
    }

    if (signal.pid <= 0 && signal.type != LIST) {
        write_daemon_output("Please input a valid task id.");
        send_signal(signal.ppid);
        return 0;
    }

    // suspending / resuming / killing a worker
    if (signal.type == SUSPEND || signal.type == RESUME || signal.type == KILL) {
        // Determine the process running with that pid
        int worker_pid = tasks[signal.pid].worker_pid;

        char output[1024];
        if (worker_pid != -1 && signal.pid <= task_cnt) {
            int *task_details = get_task_details(signal.pid);
            if (signal.type == SUSPEND) {
                kill(worker_pid, SIGSTOP);
                *task_details = PAUSED;
                sprintf(output, "Task with ID `%d` suspended", signal.pid);
            } else if (signal.type == RESUME) {
                kill(worker_pid, SIGCONT);
                *task_details = PROCESSING;
                sprintf(output, "Task with ID `%d` resumed", signal.pid);
            } else {
                kill(worker_pid, SIGTERM);
                *task_details = REMOVED;
                sprintf(output, "Removed analysis task with ID `%d` for `%s`",
                        signal.pid, tasks[signal.pid].path);
            }
            close_shm_ptr(task_details, sizeof(*task_details) * getpagesize());
        } else {
            sprintf(output, "Task with ID `%d` is not running, or was never created.", signal.pid);
        }

        if (signal.type == KILL) {

            char *analysis_path = get_current_path();
            strcat(analysis_path, ANALYSIS_PATH);
            sprintf(analysis_path, analysis_path, signal.pid);

            char *status_path = get_current_path();
            strcat(status_path, STATUS_PATH);
            sprintf(status_path, status_path, signal.pid);

            remove(analysis_path);
            remove(status_path);

            free(analysis_path);
            free(status_path);
        }

        write_daemon_output(output);
        send_signal(signal.ppid);
        return 0;
    }

    if (signal.type == INFO) {
        // Determine the process running with that pid
        char output[1024];
        if (signal.pid <= task_cnt && tasks[signal.pid].status != REMOVED) {

            char *status_path = get_current_path();
            strcat(status_path, STATUS_PATH);
            sprintf(status_path, status_path, signal.pid);

            if (access(status_path, F_OK) != 0) {
                sprintf(output, "Task with ID `%d` has not yet been loaded!", signal.pid);
                write_daemon_output(output);
                send_signal(signal.ppid);
                return 0;
            }

            FILE *fd = safe_fopen(status_path, "r");

            int files, dirs, percentage;
            fscanf(fd, "%d%%\n%d files\n%d dirs", &percentage, &files, &dirs);
            safe_fclose(fd);

            char pri[] = "***";
            pri[tasks[signal.pid].priority] = '\0';

            sprintf(output, "ID  PRI PATH  DONE  STATUS  DETAILS\n%d  "
                            "%s  %s  %d%%  %s  %d files, %d dirs",
                    signal.pid, pri, tasks[signal.pid].path, percentage,
                    get_literal_status(tasks[signal.pid].status), files, dirs);
            free(status_path);
        } else {
            sprintf(output, "Task with ID `%d` does not exist.", signal.pid);
        }
        write_daemon_output(output);
        send_signal(signal.ppid);
        return 0;
    }

    if (signal.type == LIST) {
        char output[4096] = "";
        sprintf(output, "ID  PRI  PATH  Done  Status  Details\n");
        int max_len = 4096;

        for (int i = 1; i <= task_cnt; ++i) {
            if (tasks[i].status == REMOVED) continue;

            char *status_path = get_current_path();
            strcat(status_path, STATUS_PATH);
            sprintf(status_path, status_path, i);

            if (access(status_path, F_OK) != 0)
                continue;
            FILE *fd = safe_fopen(status_path, "r");

            int files, dirs, percentage;
            fscanf(fd, "%d%%\n%d files\n%d dirs", &percentage, &files, &dirs);
            safe_fclose(fd);

            char pri[] = "***";
            pri[tasks[i].priority] = '\0';

            snprintf(output + strlen(output), max_len - strlen(output),
                     "%d  %s  %s  %d%%  %s  %d files, %d dirs\n",
                     i, pri, tasks[i].path, percentage,
                     get_literal_status(tasks[i].status), files, dirs);
            free(status_path);
        }
        write_daemon_output(output);
        send_signal(signal.ppid);
        return 0;
    }

    if (signal.type == PRINT) {
        size_t len = 256;
        char output[4096] = "";
        char *aux = calloc(256, sizeof(*aux));
        if (tasks[signal.pid].status == DONE) {

            char *analysis_path = get_current_path();
            strcat(analysis_path, ANALYSIS_PATH);
            sprintf(analysis_path, analysis_path, signal.pid);


            FILE *fd = safe_fopen(analysis_path, "r");
            if (fd) {
                while (1) {
                    if (getline(&aux, &len, fd) == -1) break;
                    if (strlen(aux) > 4096 - strlen(output)) break;
                    snprintf(output + strlen(output), 4096 - strlen(output), "%s", aux);
                }
            } else {
                sprintf(output, "No existing analysis for task with ID `%d`", signal.pid);
            }
            safe_fclose(fd);
            free(analysis_path);
        } else {
            sprintf(output, "No existing analysis for task with ID `%d`", signal.pid);
        }
        free(aux);

        write_daemon_output(output);
        send_signal(signal.ppid);
    }
    return 0;
}

void end_all_tasks() {
    for (int i = 1; i <= task_cnt; ++i) {
        tasks[i].status = REMOVED;
        if(tasks[i].worker_pid!=-1)
            kill(tasks[i].worker_pid, SIGTERM);
    }
}
