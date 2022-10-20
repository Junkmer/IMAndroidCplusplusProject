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

namespace v2im {
    namespace jni {

        void BaseListenerJni::InitListener(){
            v2im::V2IMEngine::GetInstance()->AddSDKListener(this);
        }

        void BaseListenerJni::AddSDKListener(JNIEnv *env, jobject listener_imsdk, jstring listenerPath) {
            if (nullptr == listener_imsdk) {
                LOGE("addSDKListener | listener_imsdk is null");
                return;
            }

            std::string path;
            for (auto &item: listener_imsdk_map) {
                path = StringJni::Jstring2Cstring(env,listenerPath);
                if (path.empty() || path == item.first){
                    return;
                }
            }

            jobject jni_object = env->NewGlobalRef(listener_imsdk);
            listener_imsdk_map.insert(std::make_pair(path, jni_object));
        }

        void BaseListenerJni::RemoveSDKListener(JNIEnv *env, jstring listenerPath) {
            listener_imsdk_map.erase(StringJni::Jstring2Cstring(env,listenerPath));
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
            CallJavaMethod("onSelfInfoUpdated", info);
        }

        void BaseListenerJni::OnUserStatusChanged(const V2TIMUserStatusVector &userStatusList) {
            CallJavaMethod("onUserStatusChanged", userStatusList);
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

        void BaseListenerJni::CallJavaMethod(const char *method_name, const V2TIMUserFullInfo &info) {
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

                jmethodID method = env->GetMethodID(j_cls, method_name, "(Lcom/tencent/imsdk/v2/V2TIMUserFullInfo;)V");
                if (nullptr != method) {
                    jobject j_obj_info = UserFullInfoJni::Convert2JObject(info);
                    env->CallVoidMethod(item.second, method, j_obj_info);
                    env->DeleteLocalRef(j_obj_info);
                } else {
                    LOGE("get %s method failed", method_name);
                    return;
                }
                env->DeleteLocalRef(j_cls);
            }
        }

        void BaseListenerJni::CallJavaMethod(const char *method_name, const V2TIMUserStatusVector &userStatusVector) {
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

                jmethodID method = env->GetMethodID(j_cls, method_name, "(Ljava/util/List;)V");
                if (nullptr != method) {

                    jobject userStatusList = v2im::jni::ArrayListJni::NewArrayList();
                    for (int i = 0; i < userStatusVector.Size(); ++i) {
                        jobject userStatus = v2im::jni::UserStatusJni::Convert2JObject(userStatusVector[i]);
                        v2im::jni::ArrayListJni::Add(userStatusList, userStatus);
                        env->DeleteLocalRef(userStatus);
                    }

                    env->CallVoidMethod(item.second, method, userStatusList);
                    env->DeleteLocalRef(userStatusList);
                } else {
                    LOGE("get %s method failed", method_name);
                    return;
                }
                env->DeleteLocalRef(j_cls);
            }
        }

    }
}
