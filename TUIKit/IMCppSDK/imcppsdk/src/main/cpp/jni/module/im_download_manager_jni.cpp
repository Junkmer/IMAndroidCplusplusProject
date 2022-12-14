//
// Created by Junker on 2022/10/17.
//

#include <jni.h>
#include "jni_util.h"
#include "java_basic_jni.h"
#include "v2_im_engine.h"
#include "jni_helper.h"
#include "callback_impl.h"
#include "value_callback_impl.h"
#include "V2TIMErrorCode.h"
#include "im_callbak_jni.h"
#include "download_param_jni.h"
#include "download_callback_impl.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

DEFINE_NATIVE_FUNC(void, NativeDownloadImage, jobject j_obj_param, int type,jstring path, jobject callback) {

    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);
    auto imageType = V2TIMImageType(type);
    V2TIMString pathStr = v2im::jni::StringJni::Jstring2Cstring(env,path).c_str();

    v2im::V2IMEngine::GetInstance()->DownloadImage(param,imageType,pathStr,new v2im::DownloadCallbackImpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetSoundUrl, jobject j_obj_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::StringJni::Cstring2Jstring(env,value.CString()));
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetSoundUrl(param,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDownloadSound, jobject j_obj_param, jstring path, jobject callback) {
    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);
    V2TIMString pathStr = v2im::jni::StringJni::Jstring2Cstring(env,path).c_str();

    v2im::V2IMEngine::GetInstance()->DownloadSound(param,pathStr,new v2im::DownloadCallbackImpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetVideoUrl, jobject j_obj_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::StringJni::Cstring2Jstring(env,value.CString()));
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetVideoUrl(param,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetSnapshotUrl, jobject j_obj_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::StringJni::Cstring2Jstring(env,value.CString()));
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetSnapshotUrl(param,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDownloadVideo, jobject j_obj_param, jstring path, jobject callback) {
    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);
    V2TIMString pathStr = v2im::jni::StringJni::Jstring2Cstring(env,path).c_str();

    v2im::V2IMEngine::GetInstance()->DownloadVideo(param,pathStr,new v2im::DownloadCallbackImpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeDownloadSnapshot, jobject j_obj_param, jstring path, jobject callback) {
    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);
    V2TIMString pathStr = v2im::jni::StringJni::Jstring2Cstring(env,path).c_str();

    v2im::V2IMEngine::GetInstance()->DownloadSnapshot(param,pathStr,new v2im::DownloadCallbackImpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetFileUrl, jobject j_obj_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::StringJni::Cstring2Jstring(env,value.CString()));
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetFileUrl(param,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDownloadFile, jobject j_obj_param, jstring path, jobject callback) {
    DownloadParam param;
    v2im::jni::DownloadParamJni::Convert2CoreObject(j_obj_param,param);
    V2TIMString pathStr = v2im::jni::StringJni::Jstring2Cstring(env,path).c_str();

    v2im::V2IMEngine::GetInstance()->DownloadFile(param,pathStr,new v2im::DownloadCallbackImpl(callback));
}

// ??????
static JNINativeMethod gImageMethods[] = {
        {"nativeDownloadImage", "(Lcom/tencent/imsdk/common/DownloadParam;ILjava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeDownloadImage},
};

// ??????
static JNINativeMethod gSoundMethods[] = {
        {"nativeGetSoundUrl",   "(Lcom/tencent/imsdk/common/DownloadParam;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeGetSoundUrl},
        {"nativeDownloadSound", "(Lcom/tencent/imsdk/common/DownloadParam;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeDownloadSound},
};

// ??????
static JNINativeMethod gVideoMethods[] = {
        {"nativeGetVideoUrl",      "(Lcom/tencent/imsdk/common/DownloadParam;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeGetVideoUrl},
        {"nativeGetSnapshotUrl",   "(Lcom/tencent/imsdk/common/DownloadParam;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeGetSnapshotUrl},
        {"nativeDownloadVideo",    "(Lcom/tencent/imsdk/common/DownloadParam;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeDownloadVideo},
        {"nativeDownloadSnapshot", "(Lcom/tencent/imsdk/common/DownloadParam;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeDownloadSnapshot},
};

// ??????
static JNINativeMethod gFileMethods[] = {
        {"nativeGetFileUrl",   "(Lcom/tencent/imsdk/common/DownloadParam;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeGetFileUrl},
        {"nativeDownloadFile", "(Lcom/tencent/imsdk/common/DownloadParam;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeDownloadFile},
};


//?????? V2TIMImageElem native ??????
int RegisterNativeMethodsForV2TIMImageElem(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMImageElem$V2TIMImage", gImageMethods,
                                                  sizeof(gImageMethods) / sizeof(gImageMethods[0]));
}

//?????? V2TIMSoundElem native ??????
int RegisterNativeMethodsForV2TIMSoundElem(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMSoundElem", gSoundMethods,
                                                  sizeof(gSoundMethods) / sizeof(gSoundMethods[0]));
}

//?????? V2TIMVideoElem native ??????
int RegisterNativeMethodsForV2TIMVideoElem(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMVideoElem", gVideoMethods,
                                                  sizeof(gVideoMethods) / sizeof(gVideoMethods[0]));
}

//?????? V2TIMFileElem native ??????
int RegisterNativeMethodsForV2TIMFileElem(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMFileElem", gFileMethods,
                                                  sizeof(gFileMethods) / sizeof(gFileMethods[0]));
}

#ifdef __cplusplus
}
#endif