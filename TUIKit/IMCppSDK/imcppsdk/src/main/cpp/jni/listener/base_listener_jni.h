//
// Created by EDY on 2022/8/23.
//

#ifndef IMCPLUSPLUSDEMO_BASE_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_BASE_LISTENER_JNI_H

#include <jni.h>
#include <string>
#include <set>
#include <map>

#include "../../include/V2TIMListener.h"

namespace v2im {
    namespace jni {
        class BaseListenerJni final : public V2TIMSDKListener {
        public:
            BaseListenerJni() = default;

            ~BaseListenerJni() override = default;

            void InitListener();

            void AddSDKListener(JNIEnv *env, jobject listener_imsdk, jstring listenerPath);

            void RemoveSDKListener(JNIEnv *env, jstring listenerPath);

        protected:
            // V2TIMSDKListener
            void OnConnecting() override;

            void OnConnectSuccess() override;

            void OnConnectFailed(int error_code, const V2TIMString &error_message) override;

            void OnKickedOffline() override;

            void OnUserSigExpired() override;

            void OnSelfInfoUpdated(const V2TIMUserFullInfo &info) override;

            void OnUserStatusChanged(const V2TIMUserStatusVector &userStatusList) override;

        private:
            void CallJavaMethod(const char *method_name);

            void CallJavaMethod(const char *method_name, int code, const std::string &message);

            void CallJavaMethod(const char *method_name, const V2TIMUserFullInfo &info);

            void CallJavaMethod(const char *method_name, const V2TIMUserStatusVector &userStatusList);

        private:
            std::map<std::string, jobject> listener_imsdk_map;//map 容器不允许有重复的key值
        };
    }// namespace v2im
}// namespace jni
#endif //IMCPLUSPLUSDEMO_BASE_LISTENER_JNI_H
