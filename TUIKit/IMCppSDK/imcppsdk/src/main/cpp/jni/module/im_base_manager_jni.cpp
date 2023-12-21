//
// Created by EDY on 2022/8/22.
//

#include <android/log.h>
#include <jni.h>
#include <bits/sysconf.h>
#include <string>
#include <iostream>

#include "LogUtil.h"
#include "value_callback_impl.h"

#include "../include/V2TIMManager.h"
#include "../convert/sdk_config_jni.h"
#include "../basic/jni_helper.h"
#include "../listener/base_listener_jni.h"
#include "../basic/jni_util.h"
#include "im_callbak_jni.h"
#include "v2_im_engine.h"
#include "V2TIMErrorCode.h"
#include "../../engine/callback_impl.h"
#include "simple_listener_jni.h"
#include "send_callback_impl.h"
#include "java_basic_jni.h"
#include "group_listener_jni.h"
#include "user_full_info_jni.h"
#include "user_status_jni.h"
#include "V2TIMErrorCode.h"
//监听
#include "conversation_listener_jni.h"


#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...)  \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<v2im::jni::BaseListenerJni> base_listener_jni;
static std::shared_ptr<v2im::jni::SimpleListenerJni> simple_listener_jni;
static std::shared_ptr<v2im::jni::GroupListenerJni> group_listener_jni;

DEFINE_NATIVE_FUNC(void, NativeInitCplusplusSDKListener) {
    if (!base_listener_jni) {
        base_listener_jni = std::make_shared<v2im::jni::BaseListenerJni>();
    }
    base_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeInitCplusplusSimpleMsgListener) {
    if (!simple_listener_jni) {
        simple_listener_jni = std::make_shared<v2im::jni::SimpleListenerJni>();
    }
    simple_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeInitCplusplusGroupListener) {
    if (!group_listener_jni) {
        group_listener_jni = std::make_shared<v2im::jni::GroupListenerJni>();
    }
    group_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeAddSDKListener, jobject sdkListener, jstring listenerPath) {
    if (!base_listener_jni) {
        base_listener_jni = std::make_shared<v2im::jni::BaseListenerJni>();
    }
    base_listener_jni->AddSDKListener(env, sdkListener, listenerPath);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveSDKListener, jstring listenerPath) {
    if (base_listener_jni) {
        base_listener_jni->RemoveSDKListener(env, listenerPath);
    }
}

DEFINE_NATIVE_FUNC(bool, NativeInitSDK, const jint sdkAppID, jobject sdkConfig) {
    V2TIMSDKConfig config = v2im::jni::SDKConfigJni::ConvertToCoreObject(env, sdkConfig);
    bool flag = V2TIMManager::GetInstance()->InitSDK(sdkAppID, config);
    return flag;
}

DEFINE_NATIVE_FUNC(void, NativeUninitSDK) {
    V2TIMManager::GetInstance()->UnInitSDK();
}

DEFINE_NATIVE_FUNC(void, NativeLogin, const jstring userID, const jstring userSig, jobject callback) {
    V2TIMString user_id = v2im::jni::StringJni::Jstring2Cstring(env, userID).c_str();
    V2TIMString user_sig = v2im::jni::StringJni::Jstring2Cstring(env, userSig).c_str();

    v2im::V2IMEngine::GetInstance()->Login(user_id, user_sig, new v2im::CallbackIMpl(callback));

}

DEFINE_NATIVE_FUNC(void, NativeLogout, jobject callback) {
    v2im::V2IMEngine::GetInstance()->Logout(new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(jstring, NativeGetVersion) {
    const char *sdk_version = v2im::V2IMEngine::GetInstance()->GetVersion().CString();
    return v2im::jni::StringJni::Cstring2Jstring(env, sdk_version);
}

DEFINE_NATIVE_FUNC(jlong, NativeGetServerTime) {
    return v2im::V2IMEngine::GetInstance()->GetServerTime();
}

DEFINE_NATIVE_FUNC(jstring, NativeGetLoginUser) {
    const char *user_id = v2im::V2IMEngine::GetInstance()->GetLoginUser().CString();
    return v2im::jni::StringJni::Cstring2Jstring(env, user_id);
}

DEFINE_NATIVE_FUNC(jint, NativeGetLoginStatus) {
    return v2im::V2IMEngine::GetInstance()->GetLoginStatus();
}

DEFINE_NATIVE_FUNC(void, NativeAddSimpleMsgListener, jobject simple_listener) {
    if (!simple_listener_jni) {
        simple_listener_jni = std::make_shared<v2im::jni::SimpleListenerJni>();
    }
    simple_listener_jni->AddListener(env, simple_listener);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveSimpleMsgListener, jobject simple_listener) {
    if (simple_listener_jni) {
        simple_listener_jni->RemoveListener(simple_listener);
    }
}

DEFINE_NATIVE_FUNC(jstring, NativeSendC2CTextMessage, jstring text, jstring user_id, jobject callback) {
    V2TIMString textCStr = v2im::jni::StringJni::Jstring2Cstring(env, text).c_str();
    V2TIMString userIdCStr = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();

    V2TIMString msgID = v2im::V2IMEngine::GetInstance()->SendC2CTextMessage(textCStr, userIdCStr,
                                                                            new v2im::SendCallbackImpl(callback));
    return v2im::jni::StringJni::Cstring2Jstring(env, msgID.CString());
}

DEFINE_NATIVE_FUNC(jstring, NativeSendC2CCustomMessage, jbyteArray custom_data, jstring user_id, jobject callback) {
    V2TIMBuffer custom_data_c = v2im::jni::ByteJni::JByteArray2V2TIMBuffer(env, custom_data);
    V2TIMString user_id_c = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();

    V2TIMString msgID = v2im::V2IMEngine::GetInstance()->SendC2CCustomMessage(custom_data_c, user_id_c, new v2im::SendCallbackImpl(callback));
    return v2im::jni::StringJni::Cstring2Jstring(env, msgID.CString());
}

DEFINE_NATIVE_FUNC(jstring, NativeSendGroupTextMessage, jstring text, jstring group_id, jint priority, jobject callback) {
    V2TIMString textCStr = v2im::jni::StringJni::Jstring2Cstring(env, text).c_str();
    V2TIMString groupIdCStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMString msgID = v2im::V2IMEngine::GetInstance()->SendGroupTextMessage(textCStr, groupIdCStr, static_cast<V2TIMMessagePriority>(priority),
                                                                              new v2im::SendCallbackImpl(callback));
    return v2im::jni::StringJni::Cstring2Jstring(env, msgID.CString());
}

DEFINE_NATIVE_FUNC(jstring, NativeSendGroupCustomMessage, jbyteArray custom_data, jstring group_id, jint priority, jobject callback) {
    V2TIMBuffer custom_data_c = v2im::jni::ByteJni::JByteArray2V2TIMBuffer(env, custom_data);
    V2TIMString groupIdCStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMString msgID = v2im::V2IMEngine::GetInstance()->SendGroupCustomMessage(custom_data_c, groupIdCStr,
                                                                                static_cast<V2TIMMessagePriority>(priority),
                                                                                new v2im::SendCallbackImpl(callback));
    return v2im::jni::StringJni::Cstring2Jstring(env, msgID.CString());
}

DEFINE_NATIVE_FUNC(void, NativeAddGroupListener, jobject listener, jstring listenerPath) {
    if (!group_listener_jni) {
        group_listener_jni = std::make_shared<v2im::jni::GroupListenerJni>();
    }
    group_listener_jni->AddListener(env, listener, listenerPath);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveGroupListener, jstring listenerPath) {
    if (group_listener_jni) {
        group_listener_jni->RemoveListener(env, listenerPath);
    }
}

DEFINE_NATIVE_FUNC(void, NativeCreateGroup, jstring group_type, jstring group_id, jstring group_name, jobject callback) {
    if (nullptr == group_id || nullptr == group_type) {
        return;
    }
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupTypeStr = v2im::jni::StringJni::Jstring2Cstring(env, group_type).c_str();
    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMString groupNameStr = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback(
            [=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
                v2im::jni::ScopedJEnv scopedJEnv;

                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::StringJni::Cstring2Jstring(env, value.CString()));
                } else {
                    v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
                }

                scopedJEnv.GetEnv()->DeleteGlobalRef(jni_callback);
                delete value_callback;
            });

    v2im::V2IMEngine::GetInstance()->CreateGroup(groupTypeStr, groupIDStr, groupNameStr, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeJoinGroup, jstring group_id, jstring message, jobject callback) {
    if (nullptr == group_id) {
        return;
    }

    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMString messageStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    v2im::V2IMEngine::GetInstance()->JoinGroup(groupIDStr, messageStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeQuitGroup, jstring group_id, jobject callback) {
    if (nullptr == group_id) {
        return;
    }

    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    v2im::V2IMEngine::GetInstance()->QuitGroup(groupIDStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeDismissGroup, jstring group_id, jobject callback) {
    if (nullptr == group_id) {
        return;
    }

    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    v2im::V2IMEngine::GetInstance()->DismissGroup(groupIDStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetUsersInfo, jobject user_id_list, jobject callback) {
    if (nullptr == user_id_list) {
        return;
    }

    jobject jni_callback = env->NewGlobalRef(callback);

    int size = v2im::jni::ArrayListJni::Size(user_id_list);
    V2TIMStringVector stringVector;
    for (int i = 0; i < size; ++i) {
        auto userID = (jstring) v2im::jni::ArrayListJni::Get(user_id_list, i);
        if (nullptr != userID) {
            stringVector.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID).c_str());
        }
        env->DeleteLocalRef(userID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMUserFullInfoVector>{};
    value_callback->setCallback(
            [=](const int &error_code, const V2TIMString &error_message, const V2TIMUserFullInfoVector &userFullInfoVector) {
                v2im::jni::ScopedJEnv scopedJEnv;
                auto _env = scopedJEnv.GetEnv();

                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    if (!userFullInfoVector.Empty()) {
                        jobject userFullInfoList = v2im::jni::ArrayListJni::NewArrayList();
                        for (int i = 0; i < userFullInfoVector.Size(); ++i) {
                            jobject userFullInfo = v2im::jni::UserFullInfoJni::Convert2JObject(userFullInfoVector[i]);
                            v2im::jni::ArrayListJni::Add(userFullInfoList, userFullInfo);
                            _env->DeleteLocalRef(userFullInfo);
                        }
                        v2im::jni::IMCallbackJNI::Success(jni_callback, userFullInfoList);
                        _env->DeleteLocalRef(userFullInfoList);
                    }
                } else {
                    v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
                }

                scopedJEnv.GetEnv()->DeleteGlobalRef(jni_callback);
                delete value_callback;
            });

    v2im::V2IMEngine::GetInstance()->GetUsersInfo(stringVector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetSelfInfo, jobject info, jobject callback) {
    if (nullptr == info) {
        return;
    }

    V2TIMUserFullInfo userFullInfo;
    bool flag = v2im::jni::UserFullInfoJni::Convert2CoreObject(info, userFullInfo);
    if (flag) {
        v2im::V2IMEngine::GetInstance()->SetSelfInfo(userFullInfo, new v2im::CallbackIMpl(callback));
    }
}

DEFINE_NATIVE_FUNC(void, NativeSubscribeUserInfo, jobject user_id_list, jobject callback) {
    if (nullptr == user_id_list) {
        return;
    }

    json::Array user_id_array;
    int size = tim::jni::ArrayListJni::Size(user_id_list);
    for (int i = 0; i < size; ++i){
        auto userId = (jstring)tim::jni::ArrayListJni::Get(user_id_list,i);
        user_id_array.push_back(tim::jni::StringJni::Jstring2Cstring(env,userId));
    }
    std::string paramStr = json::Serialize(user_id_array);

    tim::TIMEngine::GetInstance()->SubscribeUserInfo(paramStr.c_str(), new tim::TIMCallbackIMpl(callback));
}


DEFINE_NATIVE_FUNC(void, NativeUnsubscribeUserInfo, jobject user_id_list, jobject callback) {
    if (nullptr == user_id_list) {
        return;
    }

    json::Array user_id_array;
    int size = tim::jni::ArrayListJni::Size(user_id_list);
    for (int i = 0; i < size; ++i){
        auto userId = (jstring)tim::jni::ArrayListJni::Get(user_id_list,i);
        user_id_array.push_back(tim::jni::StringJni::Jstring2Cstring(env,userId));
    }
    std::string paramStr = json::Serialize(user_id_array);

    tim::TIMEngine::GetInstance()->UnsubscribeUserInfo(paramStr.c_str(), new tim::TIMCallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetUserStatus, jobject user_id_list, jobject callback) {
    if (nullptr == user_id_list) {
        return;
    }

    int size = v2im::jni::ArrayListJni::Size(user_id_list);
    V2TIMStringVector stringVector;
    for (int i = 0; i < size; ++i) {
        auto userID = (jstring) v2im::jni::ArrayListJni::Get(user_id_list, i);
        stringVector.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID).c_str());
    }

    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMUserStatusVector>{};
    value_callback->setCallback(
            [=](const int &error_code, const V2TIMString &error_message, const V2TIMUserStatusVector &userStatusVector) {
                v2im::jni::ScopedJEnv scopedJEnv;
                auto _env = scopedJEnv.GetEnv();

                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    if (!userStatusVector.Empty()) {
                        jobject userStatusList = v2im::jni::ArrayListJni::NewArrayList();
                        for (int i = 0; i < userStatusVector.Size(); ++i) {
                            jobject userStatus = v2im::jni::UserStatusJni::Convert2JObject(userStatusVector[i]);
                            v2im::jni::ArrayListJni::Add(userStatusList, userStatus);
                            _env->DeleteLocalRef(userStatus);
                        }
                        v2im::jni::IMCallbackJNI::Success(jni_callback, userStatusList);
                        _env->DeleteLocalRef(userStatusList);
                    }
                } else {
                    v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
                }

                _env->DeleteGlobalRef(jni_callback);
                delete value_callback;
            });


    v2im::V2IMEngine::GetInstance()->GetUserStatus(stringVector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetSelfStatus, jobject status, jobject callback) {
    if (nullptr == status) {
        return;
    }

    V2TIMUserStatus userStatus;
    bool flag = v2im::jni::UserStatusJni::Convert2CoreObject(status, userStatus);
    if (flag) {
        v2im::V2IMEngine::GetInstance()->SetSelfStatus(userStatus, new v2im::CallbackIMpl(callback));
    }

}

DEFINE_NATIVE_FUNC(void, NativeSubscribeUserStatus, jobject user_id_list, jobject callback) {
    if (nullptr == user_id_list) {
        return;
    }

    int size = v2im::jni::ArrayListJni::Size(user_id_list);
    V2TIMStringVector stringVector;
    for (int i = 0; i < size; ++i) {
        auto userID = (jstring) v2im::jni::ArrayListJni::Get(user_id_list, i);
        stringVector.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID).c_str());
    }

    v2im::V2IMEngine::GetInstance()->SubscribeUserStatus(stringVector, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeUnsubscribeUserStatus, jobject user_id_list, jobject callback) {
    if (nullptr == user_id_list) {
        return;
    }

    int size = v2im::jni::ArrayListJni::Size(user_id_list);
    V2TIMStringVector stringVector;
    for (int i = 0; i < size; ++i) {
        auto userID = (jstring) v2im::jni::ArrayListJni::Get(user_id_list, i);
        stringVector.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID).c_str());
    }

    v2im::V2IMEngine::GetInstance()->UnsubscribeUserStatus(stringVector, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeCallExperimentalAPI, jstring api, jobject param, jobject callback) {
    if (nullptr == api || nullptr == param) {
        return;
    }

    V2TIMString apiStr = v2im::jni::StringJni::Jstring2Cstring(env, api).c_str();


    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMBaseObject>{};
    value_callback->setCallback(
            [=](const int &error_code, const V2TIMString &error_message, const V2TIMBaseObject &baseObject) {
                v2im::jni::ScopedJEnv scopedJEnv;

                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    if (baseObject.obj_ptr) {
                        v2im::jni::IMCallbackJNI::Success(jni_callback, (jobject const &) baseObject);
                    }
                } else {
                    v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
                }

                scopedJEnv.GetEnv()->DeleteGlobalRef(jni_callback);
                delete value_callback;
            });

    v2im::V2IMEngine::GetInstance()->CallExperimentalAPI(apiStr, param, value_callback);
}

//void test(JNIEnv *env) {
//    jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMManager");
//    jmethodID jmethod = nullptr;
//    jmethod = env->GetMethodID(cls, "nativeInitCplusplusSDKListener", "()V");
//    jmethod = env->GetMethodID(cls, "nativeInitCplusplusSimpleMsgListener", "()V");
//    jmethod = env->GetMethodID(cls, "nativeInitCplusplusGroupListener", "()V");
//}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeInitCplusplusSDKListener",       "()V",                                                                                            (void *) NativeInitCplusplusSDKListener},
        {"nativeInitCplusplusSimpleMsgListener", "()V",                                                                                            (void *) NativeInitCplusplusSimpleMsgListener},
        {"nativeInitCplusplusGroupListener",     "()V",                                                                                            (void *) NativeInitCplusplusGroupListener},
        {"nativeAddSDKListener",                "(Lcom/tencent/imsdk/v2/V2TIMSDKListener;Ljava/lang/String;)V",                                   (void *) NativeAddSDKListener},
        {"nativeRemoveSDKListener",             "(Ljava/lang/String;)V",                                                                          (void *) NativeRemoveSDKListener},
        {"nativeInitSDK",                       "(ILcom/tencent/imsdk/v2/V2TIMSDKConfig;)Z",                                                      (bool *) NativeInitSDK},
        {"nativeUninitSDK",                     "()V",                                                                                            (void *) NativeUninitSDK},
        {"nativeLogin",                         "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeLogin},
        {"nativeLogout",                        "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                       (void *) NativeLogout},
        {"nativeGetVersion",                    "()Ljava/lang/String;",                                                                           (jstring *) NativeGetVersion},
        {"nativeGetServerTime",                 "()J",                                                                                            (jlong *) NativeGetServerTime},
        {"nativeGetLoginUser",                  "()Ljava/lang/String;",                                                                           (jstring *) NativeGetLoginUser},
        {"nativeGetLoginStatus",                "()I",                                                                                            (jint *) NativeGetLoginStatus},
        {"nativeAddSimpleMsgListener",          "(Lcom/tencent/imsdk/v2/V2TIMSimpleMsgListener;Ljava/lang/String;)V",                             (void *) NativeAddSimpleMsgListener},
        {"nativeRemoveSimpleMsgListener",       "(Ljava/lang/String;)V",                                                                          (void *) NativeRemoveSimpleMsgListener},
        {"nativeSendC2CTextMessage",            "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",  (jstring *) NativeSendC2CTextMessage},
        {"nativeSendC2CCustomMessage",          "([BLjava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",                  (jstring *) NativeSendC2CCustomMessage},
        {"nativeSendGroupTextMessage",          "(Ljava/lang/String;Ljava/lang/String;ILcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;", (jstring *) NativeSendGroupTextMessage},
        {"nativeSendGroupCustomMessage",        "([BLjava/lang/String;ILcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",                 (jstring *) NativeSendGroupCustomMessage},
        {"nativeAddGroupListener",              "(Lcom/tencent/imsdk/v2/V2TIMGroupListener;Ljava/lang/String;)V",                                 (void *) NativeAddGroupListener},
        {"nativeRemoveGroupListener",           "(Ljava/lang/String;)V",                                                                          (void *) NativeRemoveGroupListener},
        {"nativeCreateGroup",                   "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeCreateGroup},
        {"nativeJoinGroup",                     "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeJoinGroup},
        {"nativeQuitGroup",                     "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                     (void *) NativeQuitGroup},
        {"nativeDismissGroup",                  "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                     (void *) NativeDismissGroup},
        {"nativeGetUsersInfo",                  "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                       (void *) NativeGetUsersInfo},
        {"nativeSetSelfInfo",                   "(Lcom/tencent/imsdk/v2/V2TIMUserFullInfo;Lcom/tencent/imsdk/common/IMCallback;)V",               (void *) NativeSetSelfInfo},
        {"nativeSubscribeUserInfo",       "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                       (void *) NativeSubscribeUserInfo},
        {"nativeUnsubscribeUserInfo",     "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                       (void *) NativeUnsubscribeUserInfo},
        {"nativeGetUserStatus",                 "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                       (void *) NativeGetUserStatus},
        {"nativeSetSelfStatus",                 "(Lcom/tencent/imsdk/v2/V2TIMUserStatus;Lcom/tencent/imsdk/common/IMCallback;)V",                 (void *) NativeSetSelfStatus},
        {"nativeSubscribeUserStatus",           "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                       (void *) NativeSubscribeUserStatus},
        {"nativeUnsubscribeUserStatus",         "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                       (void *) NativeUnsubscribeUserStatus},
        {"nativeCallExperimentalAPI",           "(Ljava/lang/String;Ljava/lang/Object;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeCallExperimentalAPI},
};

// 注册 native 方法
int RegisterNativeMethodsForV2TIMManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}


#ifdef __cplusplus
}
#endif
