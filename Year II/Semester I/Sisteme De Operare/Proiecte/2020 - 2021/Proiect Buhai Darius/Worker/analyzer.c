#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#include "analyzer.h"
#include "../Shared/shared.h"

int total_rec_count = 0;

int is_dir(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

LL get_file_size(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == 0)
        return path_stat.st_size;
    return 0;
}

void set_next_path(const char *base_path, const char *name, char *next_path) {
    strcpy(next_path, base_path);
    if (next_path[strlen(next_path) - 1] != '/') {
        strcat(next_path, "/");
    }
    strcat(next_path, name);
}

void count_dirs(const char *base_path, LL *total_size) {

    DIR *dir = opendir(base_path);
    if (dir == NULL) return;

    struct dirent *dp;
    char next_path[MAX_PATH_LENGTH];

    while (1) {
        dp = readdir(dir);
        if (dp == NULL) break;

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            set_next_path(base_path, dp->d_name, next_path);
            *total_size += get_file_size(next_path);
            total_rec_count += 1;
            if (is_dir(next_path)) {
                count_dirs(next_path, total_size);
            }
        }
    }
    closedir(dir);
}

LL output_data(const char *base_path, char unit[], char hashtags[],
                      FILE *analysis_fd, const char *status_path, LL *total, int first,
                      int *file_count, int *dir_count, int job_id) {

    DIR *dir = opendir(base_path);
    if (dir == NULL) return 0;

    struct dirent *dp;
    char next_path[MAX_PATH_LENGTH];
    LL cur_dir_size = 0;

    while (1) {
        dp = readdir(dir);
        if (dp == NULL) break;

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            set_next_path(base_path, dp->d_name, next_path);
            cur_dir_size += get_file_size(next_path);
            if (is_dir(next_path)) {
                cur_dir_size += output_data(next_path, unit, hashtags, analysis_fd,
                                            status_path, total, 0, file_count, dir_count, job_id);
                *dir_count += 1;
            } else {
                *file_count += 1;
            }
        }
    }
    closedir(dir);

    double percentage = (double) cur_dir_size / (double) *total;
    int hashtag_cnt = percentage * 40.0 + 1;
    if (hashtag_cnt > 40) hashtag_cnt = 40;

    LL copy = cur_dir_size;
    unit = "B";
    if (copy > 1024) {
        unit = "KB";
        copy /= 1024;
    }
    if (copy > 1024) {
        unit = "MB";
        copy /= 1024;
    }
    if (copy > 1024) {
        unit = "GB";
        copy /= 1024;
    }

    for (int i = 0; i < hashtag_cnt; ++i)
        hashtags[i] = '#';
    hashtags[hashtag_cnt] = '\0';

    if (!first)
        fprintf(analysis_fd, "|-%s/  %0.2lf%%  %lld%s  %s\n", base_path, percentage * 100, copy, unit, hashtags);

    FILE *status_fd = safe_fopen(status_path, "w");
    if (status_fd) {
        percentage = (double) (*file_count + *dir_count) / (double) total_rec_count;
        fprintf(status_fd, "%d%%\n%d files\n%d dirs", (int) (percentage * 100), *file_count, *dir_count);
        safe_fclose(status_fd);
    }

    return cur_dir_size;
}

void analyze(const char *path, int job_id) {

    char *output_path = get_current_path();
    char *status_path = get_current_path();

    strncat(output_path, ANALYSIS_PATH, strlen(ANALYSIS_PATH));
    strncat(status_path, STATUS_PATH, strlen(STATUS_PATH));

    sprintf(output_path, output_path, job_id);
    sprintf(status_path, status_path, job_id);

    FILE *fd = safe_fopen(output_path, "w");
    FILE *status_fd = safe_fopen(status_path, "w");
    fprintf(status_fd, "%d%%\n%d files\n%d dirs", 0, 0, 0);
    safe_fclose(status_fd);
    if (fd == NULL) {
        fprintf(stderr, "Path doesn't exist!\n");
        return;
    }

    LL total_size = 0;
    count_dirs(path, &total_size);

    char unit[3], hashtags[42];
    LL copy = total_size;
    unit[0] = 'B';
    unit[1] = '\0';
    if (copy > 1024) {
        unit[0] = 'K';
        unit[1] = 'B';
        unit[2] = '\0';
        copy /= 1024;
    }
    if (copy > 1024) {
        unit[0] = 'M';
        copy /= 1024;
    }
    if (copy > 1024) {
        unit[0] = 'G';
        copy /= 1024;
    }

    for (int i = 0; i < 41; ++i) {
        hashtags[i] = '#';
    }
    hashtags[41] = '\0';

    fprintf(fd, "Path  Usage  Size  Amount\n%s  100%%  %lld%s  %s\n|\n", path, copy, unit, hashtags);

    int file_count = 0, dir_count = 0;
    output_data(path, unit, hashtags, fd, status_path, &total_size, 1, &file_count, &dir_count, job_id);

    safe_fclose(fd);
}
