cmake_minimum_required(VERSION 3.16)
project(gameboy_emulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # lets your editor/clangd find headers

add_executable(gameboy
    main.cpp
    src/hardware/bus.cpp
    src/hardware/cartridge.cpp
    src/hardware/cpu.cpp
    src/hardware/instructions.cpp
    src/hardware/Platform.cpp
)

target_include_directories(gameboy PRIVATE src/headers)

target_compile_options(gameboy PRIVATE -Wall -Wextra)