//
// Created by EDY on 2023/10/19.
//

#ifndef IMCSDKDEMO_CALL_EXPERIMENTAL_API_JNI_H
#define IMCSDKDEMO_CALL_EXPERIMENTAL_API_JNI_H

#include <jni.h>
#include <string>
//#include "json.h"
#include "V2TIMManager.h"

namespace v2im {
    namespace jni {

        class CallExperimentalAPIJni {
        public:
            static const void *ConvertToCoreObject(JNIEnv *env, const V2TIMString &api, const jobject &param);

        private:
            static V2TIMString setCustomServerInfo(const jobject &param);

            static V2TIMString setQuicChannelInfo(const jobject &param);

            static V2TIMString setProxyInfo(const jobject &param);

            static V2TIMString initLocalStorage(const jobject &param);

            static bool setTestEnvironment(const jobject &param);

            static bool setIPv6Prior(const jobject &param);

            static V2TIMString setCosSaveRegion(const jobject &param);

            static int setUIPlatform(const jobject &param);

            static V2TIMString setDatabaseEncryptInfo(const jobject &param);

            static long isCommercialAbilityEnabled(const jobject &param);

            static V2TIMString setPacketRetryInfo(const jobject &param);

            static int setOfflinePushState(const jobject &param);

            static const void * getOfflinePushState();

            static V2TIMStringVector getMessageRevoker(const jobject &param);

            static V2TIMString writeLog(const jobject &param);

            static V2TIMBuffer sendTRTCCustomData(const jobject &param);

            static V2TIMString clearLocalHistoryMessage(const jobject &param);

            static V2TIMString reportTUIComponentUsage(const jobject &param);

            static int setApplicationID(const jobject &param);

        public:
            static V2TIMString value_str;
            static bool value_bool;
            static int value_int;
            static long value_long;
            static V2TIMStringVector value_vector;
            static V2TIMBuffer value_butter;
        };

    } // namespace tim
} // namespace jni


#endif //IMCSDKDEMO_CALL_EXPERIMENTAL_API_JNI_H
