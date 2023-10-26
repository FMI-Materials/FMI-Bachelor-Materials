#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <inttypes.h>

#define ADD 1
#define SUSPEND 2
#define RESUME 3
#define KILL 4
#define INFO 5
#define LIST 6
#define PRINT 7
#define PID_PATH "TempData/daemon.pid"
#define OUTPUT_PATH "TempData/daemon_output.txt"
#define INSTRUCTION_PATH "TempData/daemon_instruction.txt"

int daemon_pid;
int process_pid;

int fsize(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}

void write_to_file(const char *file_path, const char *data) {
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open output file\n");
        return;
    }

    fprintf(fp, "%s", data);
    fclose(fp);
}

char *read_from_file(const char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open input file\n");
        return NULL;
    }

    int file_size = fsize(fp);
    char *data = malloc(sizeof(char) * file_size);
    fread(data, file_size, 1, fp);
    fclose(fp);

    return data;
}


pid_t get_daemon_pid() {

    FILE *fp = fopen(PID_PATH, "r");
    if (fp == NULL) {
        printf("No pid available!\n");
        exit(-1);
    }

    int size = fsize(fp);
    char data[size];
    fscanf(fp, "%s", data);
    return atoi(data);
}

int is_option(const char *option, const char *str1, const char *str2) {
    return strcmp(option, str1) == 0 || strcmp(option, str2) == 0;
}

void print_daemon_output(int signo) {
    char *data = read_from_file(OUTPUT_PATH);
    printf("%s\n", data);
}

void send_daemon_instruction(char *instructions) {
    write_to_file(INSTRUCTION_PATH, instructions);
    kill(daemon_pid, SIGUSR1);
    sleep(3);
}

void init() {
    daemon_pid = get_daemon_pid();
    process_pid = getpid();
    signal(SIGUSR2, print_daemon_output);
}


int main(int argc, char **argv) {

    init();
    if (argc == 1) {
        printf("No arguments provided. Exiting...");
        return 0;
    }

    char instructions[1024];

    /// Add a new analysis task
    if (is_option(argv[1], "-a", "--add")) {
        if (argc < 3) {
            printf("Not enough arguments provided. Exiting...");
            return -1;
        }

        int priority = 1;
        char *path = argv[2];

        if (argc == 5 && is_option(argv[3], "-p", "--priority")) {
            priority = atoi(argv[4]);
            if (priority < 1 || priority > 3) {
                printf("Priority should have one of the values: 1-low, 2-normal, 3-high\n");
                return -1;
            }
        }

        sprintf(instructions, "TYPE %d\nPRIORITY %d\nPATH %s\nPPID %d", ADD, priority, path, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// Suspend
    if (is_option(argv[1], "-S", "--suspend")) {
        if (argc < 3) return -1;
        int pid = atoi(argv[2]);
        sprintf(instructions, "TYPE %d\nPID %d\nPPID %d", SUSPEND, pid, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// Resume
    if (is_option(argv[1], "-R", "--resume")) {
        if (argc < 3) return -1;
        int pid = atoi(argv[2]);
        sprintf(instructions, "TYPE %d\nPID %d\nPPID %d", RESUME, pid, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// Kill
    if (is_option(argv[1], "-r", "--remove")) {
        if (argc < 3) return -1;
        int pid = atoi(argv[2]);
        // Send signal instruction
        sprintf(instructions, "TYPE %d\nPID %d\nPPID %d", KILL, pid, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// Info
    if (is_option(argv[1], "-i", "--info")) {
        if (argc < 3) return -1;
        int pid = atoi(argv[2]);
        // Send signal instruction
        sprintf(instructions, "TYPE %d\nPID %d\nPPID %d", INFO, pid, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// List
    if (is_option(argv[1], "-l", "--list")) {
        if (argc < 2) return -1;
        sprintf(instructions, "TYPE %d\nPID %d\nPPID %d", LIST, 0, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// Analysis report for tasks that are "done"
    if (is_option(argv[1], "-p", "--print")) {
        if (argc < 3) return -1;
        int pid = atoi(argv[2]);
        sprintf(instructions, "TYPE %d\nPID %d\nPPID %d", PRINT, pid, process_pid);
        send_daemon_instruction(instructions);
        return 0;
    }

    /// Terminate
    if (is_option(argv[1], "-t", "--terminate")) {
        pid_t d_pid = get_daemon_pid();
        if(d_pid!=-1)
            kill(d_pid, SIGTERM);
        printf("Daemon with PID `%d` terminated\n", d_pid);
        return 0;
    }

    /// Helper
    if (is_option(argv[1], "-h", "--help")) {
        printf("Usage: da [OPTION]... [DIR]...\n"
               "Analyze the space occupied by the directory at [DIR]\n\n"
               "-a, --add           analyze a new directory path for disk usage\n"
               "-p, --priority      set priority for the new analysis (works only with -a argument)\n"
               "-S, --suspend <id>  suspend task with <id>\n"
               "-R, --resume <id>   resume task with <id>\n"
               "-r, --remove <id>   remove the analysis with the given <id>\n"
               "-i, --info <id>     print status about the analysis with <id> (pending, progress, d\n"
               "-l, --list          list all analysis tasks, with their ID and the corresponding root p\n"
               "-p, --print <id>    print analysis report for those tasks that are \"done\"\n"
               "-t, --terminate     terminates daemon\n\n"
        );
        return 0;
    }

    printf("Unknown command. Exiting...\n");
    return 0;
}
