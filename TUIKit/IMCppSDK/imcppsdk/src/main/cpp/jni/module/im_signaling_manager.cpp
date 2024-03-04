//
// Created by EDY on 2022/8/22.
//

#include <jni.h>
#include "jni_util.h"
#include "java_basic_jni.h"
#include "v2_im_engine.h"
#include "jni_helper.h"
#include "signaling_listener_jni.h"
#include "callback_impl.h"
#include "value_callback_impl.h"
#include "V2TIMErrorCode.h"
#include "im_callbak_jni.h"
#include "offline_push_info_jni.h"
#include "V2TIMMessage.h"
#include "message_jni.h"
#include "signaling_info_jni.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<v2im::jni::SignalingListenerJni> signaling_listener_jni;

DEFINE_NATIVE_FUNC(void, NativeInitCplusplusSignalingListener) {
    if (!signaling_listener_jni) {
        signaling_listener_jni = std::make_shared<v2im::jni::SignalingListenerJni>();
    }
    signaling_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeAddSignalingListener, jobject signal_listener, jstring listenerPath) {
    if (!signaling_listener_jni) {
        signaling_listener_jni = std::make_shared<v2im::jni::SignalingListenerJni>();
    }

    signaling_listener_jni->AddListener(env, signal_listener, listenerPath);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveSignalingListener, jstring listenerPath) {
    if (signaling_listener_jni) {
        signaling_listener_jni->RemoveListener(env, listenerPath);
    }
}

DEFINE_NATIVE_FUNC(jstring, NativeInvite, jstring invitee, jstring data, jboolean online_user_only, jobject offline_push_info, jint timeout,
                   jobject callback) {

    V2TIMString invitee_str = v2im::jni::StringJni::Jstring2Cstring(env, invitee).c_str();
    V2TIMString data_str = v2im::jni::StringJni::Jstring2Cstring(env, data).c_str();
    V2TIMOfflinePushInfo pushInfo;
    if (offline_push_info) {
        v2im::jni::OfflinePushInfoJni::Convert2CoreObject(offline_push_info, pushInfo);
    }
    V2TIMString inviteIDStr = v2im::V2IMEngine::GetInstance()->Invite(invitee_str, data_str, online_user_only, pushInfo, timeout,
                                                                      new v2im::CallbackIMpl(callback));
    return v2im::jni::StringJni::Cstring2Jstring(env, inviteIDStr.CString());
}

DEFINE_NATIVE_FUNC(jstring, NativeInviteInGroup, jstring group_id, jobject invitee_list, jstring data, jboolean online_user_only, jint timeout,
                   jobject callback) {

    V2TIMString groupID_str = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector inviteeList;
    int size = v2im::jni::ArrayListJni::Size(invitee_list);
    for (int i = 0; i < size; ++i) {
        auto inviteeJStr = (jstring) v2im::jni::ArrayListJni::Get(invitee_list, i);
        inviteeList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, inviteeJStr).c_str());
        env->DeleteLocalRef(inviteeJStr);
    }

    V2TIMString data_str = v2im::jni::StringJni::Jstring2Cstring(env, data).c_str();

    V2TIMString inviteIDStr = v2im::V2IMEngine::GetInstance()->InviteInGroup(groupID_str, inviteeList, data_str, online_user_only, timeout,
                                                                             new v2im::CallbackIMpl(callback));
    return v2im::jni::StringJni::Cstring2Jstring(env, inviteIDStr.CString());
}

DEFINE_NATIVE_FUNC(void, NativeCancel, jstring invite_id, jstring data, jobject callback) {

    V2TIMString inviteID_str = v2im::jni::StringJni::Jstring2Cstring(env, invite_id).c_str();
    V2TIMString data_str = v2im::jni::StringJni::Jstring2Cstring(env, data).c_str();

    v2im::V2IMEngine::GetInstance()->Cancel(inviteID_str, data_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeAccept, jstring invite_id, jstring data, jobject callback) {

    V2TIMString inviteID_str = v2im::jni::StringJni::Jstring2Cstring(env, invite_id).c_str();
    V2TIMString data_str = v2im::jni::StringJni::Jstring2Cstring(env, data).c_str();

    v2im::V2IMEngine::GetInstance()->Accept(inviteID_str, data_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeReject, jstring invite_id, jstring data, jobject callback) {

    V2TIMString inviteID_str = v2im::jni::StringJni::Jstring2Cstring(env, invite_id).c_str();
    V2TIMString data_str = v2im::jni::StringJni::Jstring2Cstring(env, data).c_str();

    v2im::V2IMEngine::GetInstance()->Reject(inviteID_str, data_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(jobject, NativeGetSignalingInfo, jobject msg) {
    V2TIMMessage timMessage;
    v2im::jni::MessageJni::Convert2CoreObject(msg,timMessage);

    V2TIMSignalingInfo signalingInfo = v2im::V2IMEngine::GetInstance()->GetSignalingInfo(timMessage);
    if (signalingInfo.inviteID.Empty()&&signalingInfo.inviteeList.Empty()){
        return nullptr;
    } else{
        return v2im::jni::SignalingInfoJni::Convert2JObject(signalingInfo);
    }
}

DEFINE_NATIVE_FUNC(void, NativeAddInvitedSignaling, jobject info, jobject callback) {

    V2TIMSignalingInfo signalingInfo;
    bool flag = v2im::jni::SignalingInfoJni::Convert2CoreObject(info, signalingInfo);
    if (flag) {
        v2im::V2IMEngine::GetInstance()->AddInvitedSignaling(signalingInfo, new v2im::CallbackIMpl(callback));
    }

}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeInitCplusplusSignalingListener", "()V",                                                                                                             (void *) NativeInitCplusplusSignalingListener},
        {"nativeAddSignalingListener",           "(Lcom/tencent/imsdk/v2/V2TIMSignalingListener;Ljava/lang/String;)V",                                              (void *) NativeAddSignalingListener},
        {"nativeRemoveSignalingListener",        "(Ljava/lang/String;)V",                                                                                           (void *) NativeRemoveSignalingListener},
        {"nativeInvite",                         "(Ljava/lang/String;Ljava/lang/String;ZLcom/tencent/imsdk/v2/V2TIMOfflinePushInfo;"
                                                 "ILcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",                                                       (jstring *) NativeInvite},
        {"nativeInviteInGroup",                  "(Ljava/lang/String;Ljava/util/List;Ljava/lang/String;ZILcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;", (jstring *) NativeInviteInGroup},
        {"nativeCancel",                         "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                    (void *) NativeCancel},
        {"nativeAccept",                         "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                    (void *) NativeAccept},
        {"nativeReject",                         "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                    (void *) NativeReject},
        {"nativeGetSignalingInfo",               "(Lcom/tencent/imsdk/v2/V2TIMMessage;)Lcom/tencent/imsdk/v2/V2TIMSignalingInfo;",                                  (jobject *) NativeGetSignalingInfo},
        {"nativeAddInvitedSignaling",            "(Lcom/tencent/imsdk/v2/V2TIMSignalingInfo;Lcom/tencent/imsdk/common/IMCallback;)V",                               (void *) NativeAddInvitedSignaling},
};

//注册 native 方法
int RegisterNativeMethodsForV2TIMSignalingManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMSignalingManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}

#ifdef __cplusplus
}
#endif