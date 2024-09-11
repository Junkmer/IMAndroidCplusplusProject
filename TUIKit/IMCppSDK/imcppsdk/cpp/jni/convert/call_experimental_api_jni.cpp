//
// Created by EDY on 2023/10/19.
//

#include <jni_helper.h>
#include "call_experimental_api_jni.h"
#include "java_basic_jni.h"
#include "jni_util.h"
#include "jni_json_objarr_util.h"
#include "jni_json_objarr_util.h"
#include "json.h"
#include "LogUtil.h"

namespace v2im {
    namespace jni {

        std::string CallExperimentalAPIJni::value_str;
        bool CallExperimentalAPIJni::value_bool;
        int CallExperimentalAPIJni::value_int;
        long CallExperimentalAPIJni::value_long;
        V2TIMStringVector CallExperimentalAPIJni::value_vector;
        V2TIMBuffer CallExperimentalAPIJni::value_butter;

        const void *CallExperimentalAPIJni::ConvertToCoreObject(JNIEnv *env, const V2TIMString &apiStr, const jobject &param) {

            if (apiStr == "setCustomServerInfo") {
                value_str = setCustomServerInfo(param);
                return &value_str;
            } else if (apiStr == "setQuicChannelInfo") {
                value_str = setQuicChannelInfo(param);
                return &value_str;
            } else if (apiStr == "setProxyInfo") {
                value_str = setProxyInfo(param);
                return &value_str;
            } else if (apiStr == "initLocalStorage") {
                value_str = initLocalStorage(param);
                return &value_str;
            } else if (apiStr == "setTestEnvironment") {
                value_bool = setTestEnvironment(param);
                return &value_bool;
            } else if (apiStr == "setIPv6Prior") {
                value_bool = setIPv6Prior(param);
                return &value_bool;
            } else if (apiStr == "setCosSaveRegion") {
                value_str = setCosSaveRegion(param);
                return &value_str;
            } else if (apiStr == "setUIPlatform") {
                value_int = setUIPlatform(param);
                return &value_int;
            } else if (apiStr == "setDatabaseEncryptInfo") {
                value_str = setDatabaseEncryptInfo(param);
                return &value_str;
            } else if (apiStr == "isCommercialAbilityEnabled") {
                value_long = isCommercialAbilityEnabled(param);
                return &value_long;
            } else if (apiStr == "setPacketRetryInfo") {
                value_str = setPacketRetryInfo(param);
                return &value_str;
            } else if (apiStr == "setOfflinePushState") {
                value_int = setOfflinePushState(param);
                return &value_int;
            } else if (apiStr == "getOfflinePushState") {
                return getOfflinePushState();
            } else if (apiStr == "getMessageRevoker") {
                value_vector = getMessageRevoker(param);
                return &value_vector;
            } else if (apiStr == "writeLog") {
                value_str = writeLog(param);
                return &value_str;
            } else if (apiStr == "sendTRTCCustomData") {
                value_butter = sendTRTCCustomData(param);
                return &value_butter;
            } else if (apiStr == "clearLocalHistoryMessage") {
                value_str = clearLocalHistoryMessage(param);
                return &value_str;
            } else if (apiStr == "reportTUIComponentUsage") {
                value_str = reportTUIComponentUsage(param);
                return &value_str;
            } else if (apiStr == "setApplicationID") {
                value_int = setApplicationID(param);
                return &value_int;
            }
            return nullptr;
        }

        std::string CallExperimentalAPIJni::setCustomServerInfo(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            param_json["serverPublicKey"] = JSONObjectJNI::optJsonString(env, param, "serverPublicKey");// string, 只写(必填), 服务器公钥

            jobject j_arr_long = JSONObjectJNI::optJson2JArr(env, param, "longconnectionAddressList");
            if (j_arr_long) {
                json::Array long_server_address_array;
                int lengthLong = JSONArrayJNI::jArr2Length(env, param);
                for (int i = 0; i < lengthLong; ++i) {
                    jobject j_obj_long = JSONArrayJNI::optJArr2JsonObj(env, j_arr_long, i);
                    if (j_obj_long) {
                        json::Object long_server_address;
                        jstring j_ip = JSONObjectJNI::optJsonString(env, j_obj_long, "ip");
                        int j_port = JSONObjectJNI::optJsonInt(env, j_obj_long, "port");
                        bool j_isIpv6 = JSONObjectJNI::optJsonBoolean(env, j_obj_long, "isIPv6");

                        long_server_address["ip"] = StringJni::Jstring2Cstring(env, j_ip);
                        long_server_address["port"] = j_port;
                        long_server_address["isIPv6"] = j_isIpv6;

                        env->DeleteLocalRef(j_ip);
                        env->DeleteLocalRef(j_obj_long);
                    }
                }
                env->DeleteLocalRef(j_arr_long);
                param_json["longconnectionAddressList"] = long_server_address_array;
            }

            jobject j_arr_short = JSONObjectJNI::optJson2JArr(env, param, "shortconnectionAddressList");
            if (j_arr_short) {
                json::Array short_server_address_array;
                int lengthShort = JSONArrayJNI::jArr2Length(env, param);
                for (int i = 0; i < lengthShort; ++i) {
                    jobject j_obj_short = JSONArrayJNI::optJArr2JsonObj(env, j_arr_short, i);
                    if (j_obj_short) {
                        json::Object short_server_address;
                        jstring j_ip = JSONObjectJNI::optJsonString(env, j_obj_short, "ip");
                        int j_port = JSONObjectJNI::optJsonInt(env, j_obj_short, "port");
                        bool j_isIpv6 = JSONObjectJNI::optJsonBoolean(env, j_obj_short, "isIPv6");

                        short_server_address["ip"] = StringJni::Jstring2Cstring(env, j_ip);
                        short_server_address["port"] = j_port;
                        short_server_address["isIPv6"] = j_isIpv6;
                        short_server_address_array.push_back(short_server_address);

                        env->DeleteLocalRef(j_ip);
                        env->DeleteLocalRef(j_obj_short);
                    }
                }
                env->DeleteLocalRef(j_arr_short);
                param_json["shortconnectionAddressList"] = short_server_address_array;
            }

            return json::Serialize(param_json);
        }

        std::string CallExperimentalAPIJni::setQuicChannelInfo(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            bool j_isUseQuicChannel = JSONObjectJNI::optJsonBoolean(env, param, "forceUseQuicChannel");
            // bool, 只写(选填), true 表示设置 Quic 通道信息, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetQuicChannelInfo 时需要设置
            param_json["forceUseQuicChannel"] = j_isUseQuicChannel;
            return json::Serialize(param_json);
        }

        std::string CallExperimentalAPIJni::setProxyInfo(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            int j_type = JSONObjectJNI::optJsonInt(env, param, "proxyType");// 代理类型 proxyType: 0 无代理，1 Http 代理，2 Socks5 代理
            jstring j_host = JSONObjectJNI::optJsonString(env, param, "proxyHost");
            int j_port = JSONObjectJNI::optJsonInt(env, param, "proxyPort");
            jstring j_username = JSONObjectJNI::optJsonString(env, param, "proxyUsername");
            jstring j_password = JSONObjectJNI::optJsonString(env, param, "proxyPassword");

            param_json["proxyType"] = j_type;
            param_json["proxyHost"] = StringJni::Jstring2Cstring(env, j_host);
            param_json["proxyPort"] = j_port;
            param_json["proxyUsername"] = StringJni::Jstring2Cstring(env, j_username);
            param_json["proxyPassword"] = StringJni::Jstring2Cstring(env, j_password);

            env->DeleteLocalRef(j_host);
            env->DeleteLocalRef(j_username);
            env->DeleteLocalRef(j_password);

            return json::Serialize(param_json);
        }

        std::string CallExperimentalAPIJni::initLocalStorage(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            return StringJni::Jstring2Cstring(env, (jstring) param);
        }

        bool CallExperimentalAPIJni::setTestEnvironment(jobject const &param) {
            return (bool) param;
        }

        bool CallExperimentalAPIJni::setIPv6Prior(jobject const &param) {
            return (bool) param;
        }

        std::string CallExperimentalAPIJni::setCosSaveRegion(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            jstring j_convId = JSONObjectJNI::optJsonString(env, param, "conversationID");
            jstring j_cosRegion = JSONObjectJNI::optJsonString(env, param, "cosSaveRegion");

            param_json["conversationID"] = StringJni::Jstring2Cstring(env, j_convId);
            param_json["cosSaveRegion"] = StringJni::Jstring2Cstring(env, j_cosRegion);

            env->DeleteLocalRef(j_convId);
            env->DeleteLocalRef(j_cosRegion);

            return json::Serialize(param_json);
        }

        std::string CallExperimentalAPIJni::setDatabaseEncryptInfo(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            int j_type = JSONObjectJNI::optJsonInt(env, param, "encryptType");
            jstring j_key = JSONObjectJNI::optJsonString(env, param, "encryptKey");

            json::Object encrypt_info;
            encrypt_info["encryptType"] = j_type;
            encrypt_info["encryptKey"] = StringJni::Jstring2Cstring(env, j_key);

            env->DeleteLocalRef(j_key);

            return json::Serialize(encrypt_info);
        }

        int CallExperimentalAPIJni::setUIPlatform(jobject const &param) {
            /**
             *  UI 组件库类型:
             *  1：flutter 2:flutter_uikit 3:uni-app 4:uni-app_uikit 5:unity 6:unity_uikit
             *  7:electron 8:electron_uikit 9:ue 10:ue_uikit 11:mp 12:mp_uikit 13:web 14:web_uikit 15:tuikit
             */
            return IntegerJni::IntValue(param);
        }

        long CallExperimentalAPIJni::isCommercialAbilityEnabled(jobject const &param) {
            return LongJni::LongValue(param);
        }

        std::string CallExperimentalAPIJni::setPacketRetryInfo(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            int j_maxCount = JSONObjectJNI::optJsonInt(env, param, "maxRetryCount");
            int j_timeout = JSONObjectJNI::optJsonInt(env, param, "packetRequestTimeout");

            json::Object param_json;

            param_json["maxRetryCount"] = j_maxCount;
            param_json["packetRequestTimeout"] = j_timeout;
            return json::Serialize(param_json);
        }

        int CallExperimentalAPIJni::setOfflinePushState(jobject const &param) {
            // uint32, 只写(选填), 设置推送状态：0 - 不设置 1 - 开启推送 2 - 关闭推送, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetOfflinePushState 时需要设置
            return IntegerJni::IntValue(param);
        }

        const void *CallExperimentalAPIJni::getOfflinePushState() {
            return nullptr;
        }

        V2TIMStringVector CallExperimentalAPIJni::getMessageRevoker(jobject const &param) {

            V2TIMStringVector messageIDList;

            std::vector<std::string> messageIDVector = ArrayListJni::JStringListToCoreVector(param);
            for (const auto &item: messageIDVector) {
                messageIDList.PushBack(item.c_str());
            }
            return messageIDList;
        }

        std::string CallExperimentalAPIJni::writeLog(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            int j_level = JSONObjectJNI::optJsonInt(env, param, "logLevel");
            jstring j_fileName = JSONObjectJNI::optJsonString(env, param, "fileName");
            jstring j_funcName = JSONObjectJNI::optJsonString(env, param, "funcName");
            int j_lineNumber = JSONObjectJNI::optJsonInt(env, param, "lineNumber");
            jstring j_logContent = JSONObjectJNI::optJsonString(env, param, "logContent");

            // 当 kTIMRequestInternalOperation 为 kTIMInternalOperationWriteLog 时需要设置
            param_json["logLevel"] = j_level;
            param_json["fileName"] = StringJni::Jstring2Cstring(env, j_fileName);
            param_json["funcName"] = StringJni::Jstring2Cstring(env, j_funcName);
            param_json["lineNumber"] = j_lineNumber;
            param_json["logContent"] = StringJni::Jstring2Cstring(env, j_logContent);

            env->DeleteLocalRef(j_fileName);
            env->DeleteLocalRef(j_funcName);
            env->DeleteLocalRef(j_logContent);

            return json::Serialize(param_json);
        }

        V2TIMBuffer CallExperimentalAPIJni::sendTRTCCustomData(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            auto data = StringJni::JbyteArray2Cstring(env, (jbyteArray) param);
            return V2TIMBuffer{reinterpret_cast<const uint8_t*>(data.c_str()), data.size()};
        }

        std::string CallExperimentalAPIJni::clearLocalHistoryMessage(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            jstring j_convId = JSONObjectJNI::optJsonString(env, param, "conversationID");
            long j_beginTime = JSONObjectJNI::optJsonLong(env, param, "beginTimestamp");
            long j_endTime = JSONObjectJNI::optJsonLong(env, param, "endTimestamp");

            // 当 kTIMRequestInternalOperation 为 kTIMInternalOperationClearLocalHistoryMessage 时需要设置
            param_json["conversationID"] = StringJni::Jstring2Cstring(env, j_convId);
            param_json["beginTimestamp"] = (long long) j_beginTime;
            param_json["endTimestamp"] = (long long) j_endTime;

            env->DeleteLocalRef(j_convId);

            return json::Serialize(param_json);
        }

        std::string CallExperimentalAPIJni::reportTUIComponentUsage(jobject const &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            json::Object param_json;

            int j_componentType = JSONObjectJNI::optJsonInt(env, param, "UIComponentType");
            int j_styleType = JSONObjectJNI::optJsonInt(env, param, "UIStyleType");

            param_json["UIComponentType"] = j_componentType;// uint32, 只写(选填), Tuikit 上报类型
            param_json["UIStyleType"] = j_styleType;// uint32, 只写(选填), Tuikit 风格，经典版、简约版

            return json::Serialize(param_json);
        }

        int CallExperimentalAPIJni::setApplicationID(jobject const &param) {
            return IntegerJni::IntValue(param);
        }


    } // namespace jni
} // namespace tim
