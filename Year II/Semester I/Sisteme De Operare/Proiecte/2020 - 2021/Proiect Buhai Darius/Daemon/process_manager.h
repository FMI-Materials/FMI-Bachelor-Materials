#ifndef DISKANALYZER_PROCESS_MANAGER_H
#define DISKANALYZER_PROCESS_MANAGER_H

#include "../Shared/shared.h"

void update_ids();

void take_new_task();

int process_signal(struct signal_details);

void end_all_tasks();

#endif //DISKANALYZER_PROCESS_MANAGER_H
