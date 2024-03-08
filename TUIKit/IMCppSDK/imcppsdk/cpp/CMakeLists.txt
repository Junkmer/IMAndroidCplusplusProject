cmake_minimum_required(VERSION 3.18.1)
project("ImCxxSDKDemo")

set(IM_CXX_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/thirdparty)

include(${IM_CXX_SDK_PATH}/im_cxx_sdk_jni.cmake)
include(${THIRD_PARTY_PATH}/thirdparty.cmake)


set(IM_CXX_SDK_JNI_FILES
        ${IM_CXX_SDK_JNI_SRC}
        ${THIRD_PARTY_SRC}
        )

add_library(
        ImCxxSDKDemo

        SHARED

        ${IM_CXX_SDK_JNI_FILES}
)

find_library(
        log-lib

        log)

target_link_libraries(
        ImCxxSDKDemo

        ${log-lib}

        # 将第三方库与目标库进行关联
        imcxxsdk
)