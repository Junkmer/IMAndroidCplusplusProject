//
// Created by EDY on 2022/8/23.
//

#include <iostream>
#include "base_listener_jni.h"

#include "../basic/jni_util.h"
#include "../basic/jni_helper.h"
#include "../util/LogUtil.h"
#include "V2TIMManager.h"
#include "../engine/v2_im_engine.h"
#include "java_basic_jni.h"
#include "user_full_info_jni.h"
#include "user_status_jni.h"
#include "receive_message_opt_info_jni.h"

namespace v2im {
    namespace jni {

        void BaseListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddSDKListener(this);
        }

        void BaseListenerJni::AddSDKListener(JNIEnv *env, jobject listener_imsdk, jstring listenerPath) {
            if (nullptr == listener_imsdk) {
                LOGE("addSDKListener | listener_imsdk is null");
                return;
            }

            std::string path;
            for (auto &item: listener_imsdk_map) {
                path = StringJni::Jstring2Cstring(env, listenerPath);
                if (path.empty() || path == item.first) {
                    return;
                }
            }

            jobject jni_object = env->NewGlobalRef(listener_imsdk);
            listener_imsdk_map.insert(std::make_pair(path, jni_object));
        }

        void BaseListenerJni::RemoveSDKListener(JNIEnv *env, jstring listenerPath) {
            listener_imsdk_map.erase(StringJni::Jstring2Cstring(env, listenerPath));
        }

        void BaseListenerJni::OnConnecting() {
            CallJavaMethod("onConnecting");
        }

        void BaseListenerJni::OnConnectSuccess() {
            CallJavaMethod("onConnectSuccess");
        }

        void BaseListenerJni::OnConnectFailed(int error_code, const V2TIMString &error_message) {
            CallJavaMethod("onConnectFailed", error_code, error_message.CString());
        }

        void BaseListenerJni::OnKickedOffline() {
            CallJavaMethod("onKickedOffline");
        }

        void BaseListenerJni::OnUserSigExpired() {
            CallJavaMethod("onUserSigExpired");
        }

        void BaseListenerJni::OnSelfInfoUpdated(const V2TIMUserFullInfo &info) {
            jobject j_obj_info = UserFullInfoJni::Convert2JObject(info);

            CallJavaMethod("onSelfInfoUpdated", "(Lcom/tencent/imsdk/v2/V2TIMUserFullInfo;)V", j_obj_info);
        }

        void BaseListenerJni::OnUserStatusChanged(const V2TIMUserStatusVector &userStatusList) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_userStatusList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < userStatusList.Size(); ++i) {
                jobject userStatus = v2im::jni::UserStatusJni::Convert2JObject(userStatusList[i]);
                v2im::jni::ArrayListJni::Add(j_obj_userStatusList, userStatus);
                env->DeleteLocalRef(userStatus);
            }

            CallJavaMethod("onUserStatusChanged", "(Ljava/util/List;)V", j_obj_userStatusList);
        }

        void BaseListenerJni::OnUserInfoChanged(const V2TIMUserFullInfoVector &infoList) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_userInfoList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < infoList.Size(); ++i) {
                jobject userInfo = v2im::jni::UserFullInfoJni::Convert2JObject(infoList[i]);
                v2im::jni::ArrayListJni::Add(j_obj_userInfoList, userInfo);
                env->DeleteLocalRef(userInfo);
            }

            CallJavaMethod("onUserInfoChanged", "(Ljava/util/List;)V", j_obj_userInfoList);
        }

        void BaseListenerJni::OnAllReceiveMessageOptChanged(const V2TIMReceiveMessageOptInfo &receiveMessageOptInfo) {
            jobject j_obj_info = ReceiveMessageOptInfoJni::Convert2JObject_AllRecvMsg(receiveMessageOptInfo);

            CallJavaMethod("onAllReceiveMessageOptChanged", "(Lcom/tencent/imsdk/v2/V2TIMReceiveMessageOptInfo;)V", j_obj_info);
        }

        void BaseListenerJni::onExperimentalNotify(const V2TIMString &key, const V2TIMString &param) {
            CallJavaMethod("onExperimentalNotify", key.CString(), param.CString());
        }

        void BaseListenerJni::CallJavaMethod(const char *method_name) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();
            if (nullptr == env || scopedJEnv.CheckAndClearException()) {
                return;
            }

            if (nullptr == method_name) {
                LOGE("invalid method_name");
                return;
            }

            if (listener_imsdk_map.empty()) {
                LOGE("listener_imsdk_list is empty");
                return;
            }

            for (auto &item: listener_imsdk_map) {
                jclass j_cls = env->GetObjectClass(item.second);
                if (nullptr == j_cls) {
                    LOGE("get object class faild");
                }

                jmethodID method = env->GetMethodID(j_cls, method_name, "()V");
                if (nullptr != method) {
                    env->CallVoidMethod(item.second, method);
                } else {
                    LOGE("get %s method failed", method_name);
                    return;
                }
                env->DeleteLocalRef(j_cls);
            }
        }

        void BaseListenerJni::CallJavaMethod(const char *method_name, int code, const std::string &message) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (nullptr == env || scopedJEnv.CheckAndClearException()) {
                return;
            }

            if (nullptr == method_name) {
                LOGE("invalid method_name");
                return;
            }

            if (listener_imsdk_map.empty()) {
                LOGE("listener_imsdk_list is empty");
                return;
            }

            for (auto &item: listener_imsdk_map) {
                jclass j_cls = env->GetObjectClass(item.second);
                if (nullptr == j_cls) {
                    LOGE("get object class failed");
                    return;
                }

                jmethodID method = env->GetMethodID(j_cls, method_name, "(ILjava/lang/String;)V");
                if (nullptr != method) {
                    env->CallVoidMethod(item.second, method, code, StringJni::Cstring2Jstring(env, message));
                } else {
                    LOGE("get %s method failed", method_name);
                    return;
                }
                env->DeleteLocalRef(j_cls);
            }
        }

        void BaseListenerJni::CallJavaMethod(const char *method_name, const char *sig, jobject const &jobj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (nullptr == env || scopedJEnv.CheckAndClearException()) {
                return;
            }

            if (nullptr == method_name) {
                LOGE("invalid method_name");
                return;
            }

            if (listener_imsdk_map.empty()) {
                LOGE("listener_imsdk_list is empty");
                return;
            }

            for (auto &item: listener_imsdk_map) {
                jclass j_cls = env->GetObjectClass(item.second);
                if (nullptr == j_cls) {
                    LOGE("get object class failed");
                    return;
                }

                jmethodID method = env->GetMethodID(j_cls, method_name, sig);
                if (nullptr != method) {
                    env->CallVoidMethod(item.second, method, jobj);
                } else {
                    LOGE("get %s method failed", method_name);
                    return;
                }
                env->DeleteLocalRef(j_cls);
            }
            env->DeleteLocalRef(jobj);
        }

        void BaseListenerJni::CallJavaMethod(const char *method_name, const std::string &key, const std::string &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (nullptr == env || scopedJEnv.CheckAndClearException()) {
                return;
            }

            if (nullptr == method_name) {
                LOGE("invalid method_name");
                return;
            }

            if (listener_imsdk_map.empty()) {
                LOGE("listener_imsdk_list is empty");
                return;
            }

            for (auto &item: listener_imsdk_map) {
                jclass j_cls = env->GetObjectClass(item.second);
                if (nullptr == j_cls) {
                    LOGE("get object class failed");
                    return;
                }

                jmethodID method = env->GetMethodID(j_cls, method_name, "(Ljava/lang/String;Ljava/lang/Object;)V");
                if (nullptr != method) {
                    env->CallVoidMethod(item.second, method, StringJni::Cstring2Jstring(env, key), StringJni::Cstring2Jstring(env, param));
                } else {
                    LOGE("get %s method failed", method_name);
                    return;
                }
                env->DeleteLocalRef(j_cls);
            }
        }

    }
}
