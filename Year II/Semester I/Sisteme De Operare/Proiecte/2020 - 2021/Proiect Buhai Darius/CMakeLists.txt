cmake_minimum_required(VERSION 3.17)
project(DiskAnalyzer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

SET(GCC_COVERAGE_COMPILE_FLAGS "-DCLION -DDEBUG")
SET(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(daemon Daemon/daemon.c Daemon/daemon_flow.c Daemon/daemon_flow.h Daemon/process_manager.c Daemon/process_manager.h Shared/shared.h Shared/shared.c Daemon/memory_manager.c Daemon/memory_manager.h Daemon/signal_manager.c Daemon/signal_manager.h Worker/analyzer.c Worker/analyzer.h)
add_executable(da da.c)