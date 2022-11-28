cmake_minimum_required(VERSION 3.14)

project(otf2_converter VERSION 0.1.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

include_directories("${PROJECT_SOURCE_DIR}/include")

# OTF2
find_package(OTF2 REQUIRED)
include_directories(${OTF2_INCLUDE_DIR})
# Pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES 
    src/attribute_callbacks.c
    src/barectf-platform-linux-fs.c
    src/barectf.c
    src/event_callbacks.c
    src/global_def_callbacks.c
    src/main.c
    src/utilities_functions.c
)

file(COPY ${PROJECT_SOURCE_DIR}/metadata DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
    ${OTF2_LIBRARY}
    Threads::Threads
)
