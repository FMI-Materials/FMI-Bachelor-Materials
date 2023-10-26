GCC=gcc
FLAGS=

DAEMON_CFILES:=$(wildcard Daemon/*.c)
WORKER_CFILES:=$(wildcard Worker/*.c)
SHARED_CFILES:=$(wildcard Shared/*.c)

DA_CFILES:=da.c

DAEMON_OUTPUT:=daemon_runner

LIB_HFILES:=-IShared -IDaemon -IWorker -pthread


all: daemon_release da
debug: daemon_debug da

release_lrt: daemon_release_lrt da
debug_lrt: daemon_debug_lrt da

daemon_release: 
	$(GCC) -g $(DAEMON_CFILES) $(WORKER_CFILES) $(SHARED_CFILES) -o $(DAEMON_OUTPUT) $(LIB_HFILES) $(FLAGS)

daemon_debug:
	$(GCC) -g $(DAEMON_CFILES) $(WORKER_CFILES) $(SHARED_CFILES) -o $(DAEMON_OUTPUT) $(LIB_HFILES) $(FLAGS) -DDEBUG


daemon_release_lrt:
	$(GCC) -g $(DAEMON_CFILES) $(WORKER_CFILES) $(SHARED_CFILES) -lrt -o $(DAEMON_OUTPUT) $(LIB_HFILES) $(FLAGS)

daemon_debug_lrt:
	$(GCC) -g $(DAEMON_CFILES) $(WORKER_CFILES) $(SHARED_CFILES) -lrt -o $(DAEMON_OUTPUT) $(LIB_HFILES) $(FLAGS) -DDEBUG


da: da.c
	$(GCC) -o da $(DA_CFILES)

clean:
	rm da
	rm daemon_runner
	rm -r daemon_runner.*
	rm -r TempData/*

update:
	git add .
	git commit -m "Automated update" .
	git pull
	git push
