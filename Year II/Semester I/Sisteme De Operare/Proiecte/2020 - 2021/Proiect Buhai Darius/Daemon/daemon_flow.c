#include <stdio.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#include "process_manager.h"
#include "memory_manager.h"
#include "signal_manager.h"

_Noreturn int run_daemon() {

    initialize_signals();
    initialize_mutex();

    int initialization_error = initialize_processes();

    if (initialization_error != 0) {
        printf("Processed with error %d\n", initialization_error);
        abort();
    }

    while (1) {
        update_ids();
        if (get_current_signal() != NULL) {
            int error = process_signal(*get_current_signal());
            if (error)
                printf("Processed with error %d\n", error);
            fflush(stdout);
            reset_current_signal();
        }

        take_new_task();
        sleep(1);
    }
}
