#ifndef DISKANALYZER_SIGNAL_MANAGER_H
#define DISKANALYZER_SIGNAL_MANAGER_H

#include "../Shared/shared.h"

void initialize_signals();

struct signal_details *get_current_signal();

void reset_current_signal();

int send_signal(pid_t);

void write_daemon_output(char *);

#endif //DISKANALYZER_SIGNAL_MANAGER_H
