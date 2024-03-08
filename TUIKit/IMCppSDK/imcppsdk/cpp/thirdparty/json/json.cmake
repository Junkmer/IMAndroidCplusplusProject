get_filename_component(JSON_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(JSON_CMAKE_DIR ${JSON_CMAKE_DIR})

#添加json头文件路径
include_directories(
        ${JSON_CMAKE_DIR}/
)

file(GLOB_RECURSE SRC_CPP "${JSON_CMAKE_DIR}/*.cpp")

set(JSON_SRC ${SRC_CPP})
