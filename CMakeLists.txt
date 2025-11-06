cmake_minimum_required(VERSION 3.31)
project(Kaleidoscope)

set(CMAKE_CXX_STANDARD 20)

# Get LLVM flags from llvm-config
execute_process(
        COMMAND llvm-config --cxxflags
        OUTPUT_VARIABLE LLVM_CXXFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND llvm-config --ldflags --system-libs --libs core
        OUTPUT_VARIABLE LLVM_LDFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Convert LLVM flags into list format
separate_arguments(LLVM_CXXFLAGS_LIST UNIX_COMMAND "${LLVM_CXXFLAGS}")
separate_arguments(LLVM_LDFLAGS_LIST UNIX_COMMAND "${LLVM_LDFLAGS}")

add_executable(Kaleidoscope main.cpp)

# Apply compile options from LLVM
target_compile_options(Kaleidoscope PRIVATE ${LLVM_CXXFLAGS_LIST})

# Apply link flags and libraries from LLVM
target_link_libraries(Kaleidoscope PRIVATE ${LLVM_LDFLAGS_LIST})
