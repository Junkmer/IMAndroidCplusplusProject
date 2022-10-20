
cmake_minimum_required(VERSION 3.10.2)

#添加项目
project("ImC++Demo")

## 设置.cpp 原文件统一管理变量 src-files
file(GLOB src-files
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/jni/*.cpp
        ${CMAKE_SOURCE_DIR}/jni/basic/*.cpp
        ${CMAKE_SOURCE_DIR}/jni/convert/*.cpp
        ${CMAKE_SOURCE_DIR}/jni/listener/*.cpp
        ${CMAKE_SOURCE_DIR}/jni/module/*.cpp
        ${CMAKE_SOURCE_DIR}/engine/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
)

#添加目标库
add_library(
        ImC++Demo

        SHARED

        ${src-files}
)

#添加头文件
include_directories(
        include
        util
        jni/convert
        jni/basic
        jni/listener
        engine
)

#导入第三方动态库
add_library(imsdk SHARED IMPORTED)

#绑定第三方库所在位置
set_target_properties(
        imsdk
        PROPERTIES IMPORTED_LOCATION
        # {CMAKE_SOURCE_DIR} 这个地址对应的是 CMakeList.txt 地址,也就是：.../工程名/app/src/main/cpp/，我们需要定位到jniLibs文件夹下，所以得改成：${CMAKE_SOURCE_DIR}/../jniLibs
        #/${ANDROID_ABI}表示处理器架构 第三方库必须存放在这类路径下
        # 路径一定要设置正确，不然会报依赖错误（注：一定要仔细、一定要仔细、一定要仔细）
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libImSDK.so
)

find_library(
        log-lib

        log)

target_link_libraries(
        ImC++Demo

        ${log-lib}

        # 将第三方库与目标库进行关联
        imsdk
)