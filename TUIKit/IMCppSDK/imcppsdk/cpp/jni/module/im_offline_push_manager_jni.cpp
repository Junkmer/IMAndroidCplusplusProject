//
// Created by EDY on 2022/8/22.
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
#include "offline_push_config_jni.h"
#include "V2TIMMessage.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

DEFINE_NATIVE_FUNC(void, NativeSetOfflinePushConfig, jobject config, jobject callback) {

    V2TIMOfflinePushConfig pushConfig;
    v2im::jni::OfflinePushConfigJni::Convert2CoreObject(config, pushConfig);

    v2im::V2IMEngine::GetInstance()->SetOfflinePushConfig(pushConfig, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeDoBackground, jint unread_count, jobject callback) {
    v2im::V2IMEngine::GetInstance()->DoBackground(unread_count, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeDoForeground, jobject callback) {
    v2im::V2IMEngine::GetInstance()->DoForeground(new v2im::CallbackIMpl(callback));
}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeSetOfflinePushConfig", "(Lcom/tencent/imsdk/v2/V2TIMOfflinePushConfig;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeSetOfflinePushConfig},
        {"nativeDoBackground",         "(ILcom/tencent/imsdk/common/IMCallback;)V",                                                                 (void *) NativeDoBackground},
        {"nativeDoForeground",         "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                  (void *) NativeDoForeground},
};

//注册 native 方法
int RegisterNativeMethodsForV2TIMOfflinePushManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMOfflinePushManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}

#ifdef __cplusplus
}
#endif