#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "shared.h"
#include "../Daemon/memory_manager.h"

static char *current_path;

int fsize(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    int size = (int)ftell(fp);
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

char *get_literal_priority(int priority) {
    if (priority == 1)
        return "low";
    if (priority == 2)
        return "normal";
    if (priority == 3)
        return "high";
    return "unknown";
}

char *get_literal_status(int status) {
    if (status == PENDING) return "pending";
    if (status == PROCESSING) return "in progress";
    if (status == PAUSED) return "paused";
    if (status == REMOVED) return "killed";
    if (status == DONE) return "done";
    return "unknown";
}

void save_current_path() {
    current_path = calloc(FILENAME_MAX, sizeof(char));
#ifdef CLION
    current_path = "/Users/dariusbuhai/Desktop/Programs/C/DiskAnalyzer";
#else
    CURRENT_DIR(current_path, FILENAME_MAX);
#endif
}

char *get_current_path() {
    char *path = calloc(FILENAME_MAX, sizeof(char));
    strcat(path, current_path);
    return path;
}

FILE *safe_fopen(const char *file_name, const char *file_perm) {
    pthread_mutex_lock(get_mutex());

    FILE *out = fopen(file_name, file_perm);

    pthread_mutex_unlock(get_mutex());
    return out;
}

void safe_fclose(FILE *file_name) {
    pthread_mutex_lock(get_mutex());

    fclose(file_name);

    pthread_mutex_unlock(get_mutex());
}

int is_prefix(const char *pre, const char *str) {
    size_t lenpre = strlen(pre), lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}
