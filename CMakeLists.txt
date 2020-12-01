cmake_minimum_required(VERSION 3.1)

project(RISCV-Simulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 -Wall")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(
        Simulator
        src/MainCPU.cpp
        src/MemoryManager.cpp
        src/Simulator.cpp
        src/Cache.cpp
        src/bpus/GAp.cpp src/bpus/GAp.h src/bpus/AgreeSAp.cpp src/bpus/AgreeSAp.h src/bpus/AgreeGAp.cpp src/bpus/AgreeGAp.h src/bpus/PAs.cpp src/bpus/PAs.h src/bpus/PAp.cpp src/bpus/PAp.h src/bpus/MAs.cpp src/bpus/MAs.h src/bpus/TAGE.cpp src/bpus/TAGE.h)

add_executable(
        CacheSim
        src/MainCache.cpp
        src/MemoryManager.cpp
        src/Cache.cpp
)

add_executable(
        CacheOptimized
        src/MainCacheOptimization.cpp
        src/MemoryManager.cpp
        src/Cache.cpp
)

add_executable(
        BPUTests
        bpu_tests/ifs_test.c
        bpu_tests/empty_test.c
        bpu_tests/func_test.c bpu_tests/cycles_test.c bpu_tests/math_tests.c bpu_tests/random_test.c_s bpu_tests/matrix_mul_test.c bpu_tests/quick_sort_test.c bpu_tests/index_of_test.c bpu_tests/str_test.c bpu_tests/aliasing_test.c)

add_executable(ToDirenoTrace src/ToDirenoTrace.cpp)