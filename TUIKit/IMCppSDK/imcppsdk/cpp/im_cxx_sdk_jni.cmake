#CMAKE_CURRENT_LIST_FILE 表示当前的 .cmake 文件路径
get_filename_component(IM_CXX_SDK_JNI_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(IM_CXX_SDK_JNI_DIR ${IM_CXX_SDK_JNI_CMAKE_DIR})

#导入第三方动态库
add_library(imcxxsdk SHARED IMPORTED)
#绑定第三方库所在位置
set_target_properties(
        imcxxsdk
        PROPERTIES IMPORTED_LOCATION
        PROPERTIES IMPORTED_LOCATION
        # {CMAKE_SOURCE_DIR} 这个地址对应的是 CMakeList.txt 地址,也就是：.../工程名/imcsdk/cpp/，我们需要定位到libs文件夹下，所以得改成：${CMAKE_SOURCE_DIR}/../libs
        #/${ANDROID_ABI}表示处理器架构 第三方库必须存放在这类路径下
        # 路径一定要设置正确，不然会报依赖错误（注：一定要仔细、一定要仔细、一定要仔细）
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libImSDK.so
)

#添加头文件
include_directories(
        ${IM_CXX_SDK_JNI_DIR}/engine/
        ${IM_CXX_SDK_JNI_DIR}/include/
        ${IM_CXX_SDK_JNI_DIR}/jni/
        ${IM_CXX_SDK_JNI_DIR}/jni/basic/
        ${IM_CXX_SDK_JNI_DIR}/jni/convert/
        ${IM_CXX_SDK_JNI_DIR}/jni/listener/
        ${IM_CXX_SDK_JNI_DIR}/jni/module/
        ${IM_CXX_SDK_JNI_DIR}/util/
)

#需要引入的.cpp源文件
file(GLOB_RECURSE IM_CXX_SDK_JNI_CPP
        ${IM_CXX_SDK_JNI_DIR}/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/engine/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/jni/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/jni/basic/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/jni/convert/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/jni/listener/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/jni/module/*.cpp
        ${IM_CXX_SDK_JNI_DIR}/util/*.cpp
        )

set(IM_CXX_SDK_JNI_SRC
        ${IM_CXX_SDK_JNI_CPP}
        )