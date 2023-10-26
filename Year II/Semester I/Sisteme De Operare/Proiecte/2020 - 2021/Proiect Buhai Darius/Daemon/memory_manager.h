#ifndef DISKANALYZER_MEMORY_MANAGER_H
#define DISKANALYZER_MEMORY_MANAGER_H

int initialize_processes();

void initialize_mutex();

int *get_process_counter();

int *get_task_details(int);

pthread_mutex_t* get_mutex();

void close_shm_ptr(void *, int);

#endif //DISKANALYZER_MEMORY_MANAGER_H
