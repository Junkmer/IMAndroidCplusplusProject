//
// Created by EDY on 2022/9/27.
//

#include <LogUtil.h>
#include <v2_im_engine.h>
#include "advanced_msg_listener_jni.h"

#include "jni_helper.h"
#include "message_jni.h"
#include "java_basic_jni.h"
#include "message_receipt_jni.h"
#include "user_full_info_jni.h"
#include "message_extension_jni.h"
#include "message_reaction_change_info_jni.h"

namespace v2im {
    namespace jni {

        jclass AdvancedMsgListenerJni::j_cls_;
        jmethodID AdvancedMsgListenerJni::j_method_id_array_[MethodIDMax];

        void AdvancedMsgListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddAdvancedMsgListener(this);
        }

        void AdvancedMsgListenerJni::AddListener(JNIEnv *env, jobject listener_advanced_msg, jstring listenerPath) {
            if (nullptr == listener_advanced_msg) {
                LOGE("AdvancedMsgListenerJni | AddListener listener_simple is null");
                return;
            }

            std::string path;
            for (auto &item: listener_advanced_msg_map) {
                path = StringJni::Jstring2Cstring(env, listenerPath);
                if (path.empty() || path == item.first) {
                    return;
                }
            }

            jobject j_obj = env->NewGlobalRef(listener_advanced_msg);
            listener_advanced_msg_map.insert(std::make_pair(path, j_obj));
        }

        void AdvancedMsgListenerJni::RemoveListener(JNIEnv *env, jstring listenerPath) {
            if (nullptr == listenerPath) {
                LOGE("AdvancedMsgListenerJni | RemoveListener listener_simple is null");
                return;
            }
            listener_advanced_msg_map.erase(StringJni::Jstring2Cstring(env, listenerPath));
        }

        bool AdvancedMsgListenerJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMAdvancedMsgListener");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "onRecvNewMessage", "(Lcom/tencent/imsdk/v2/V2TIMMessage;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvNewMessage] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageReadReceipts", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageReadReceipts] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvC2CReadReceipt", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvC2CReadReceipt] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageRevoked", "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMUserFullInfo;Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageRevoked2Data] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageModified", "(Lcom/tencent/imsdk/v2/V2TIMMessage;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageModified] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageExtensionsChanged", "(Ljava/lang/String;Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageExtensionsChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageExtensionsDeleted", "(Ljava/lang/String;Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageExtensionsDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageReactionsChanged", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageReactionsChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageRevoked", "(Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageRevoked] = jmethod;

            return true;
        }

        void AdvancedMsgListenerJni::OnRecvNewMessage(const V2TIMMessage &message) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_message = MessageJni::Convert2JObject(message);

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvNewMessage], j_obj_message);
            }

            env->DeleteLocalRef(j_obj_message);
        }

        void AdvancedMsgListenerJni::OnRecvC2CReadReceipt(const V2TIMMessageReceiptVector &receiptList) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_receiptList = ArrayListJni::NewArrayList();
            for (int i = 0; i < receiptList.Size(); ++i) {
                jobject j_obj_receipt = MessageReceiptJni::Convert2JObject(receiptList[i]);
                if (j_obj_receipt) {
                    ArrayListJni::Add(j_obj_receiptList, j_obj_receipt);
                    env->DeleteLocalRef(j_obj_receipt);
                }
            }

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvC2CReadReceipt], j_obj_receiptList);
            }

            env->DeleteLocalRef(j_obj_receiptList);
        }

        void AdvancedMsgListenerJni::OnRecvMessageReadReceipts(const V2TIMMessageReceiptVector &receiptList) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_receiptList = ArrayListJni::NewArrayList();
            for (int i = 0; i < receiptList.Size(); ++i) {
                jobject j_obj_receipt = MessageReceiptJni::Convert2JObject(receiptList[i]);
                if (j_obj_receipt) {
                    ArrayListJni::Add(j_obj_receiptList, j_obj_receipt);
                    env->DeleteLocalRef(j_obj_receipt);
                }
            }

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageReadReceipts], j_obj_receiptList);
            }

            env->DeleteLocalRef(j_obj_receiptList);
        }

        void AdvancedMsgListenerJni::OnRecvMessageRevoked(const V2TIMString &msgID, const V2TIMUserFullInfo &operateUser, const V2TIMString &reason) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDStr = StringJni::Cstring2Jstring(env, msgID.CString());
            jobject j_obj_operateUser = UserFullInfoJni::Convert2JObject(operateUser);
            jstring reasonStr = StringJni::Cstring2Jstring(env, reason.CString());

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageRevoked], msgIDStr, j_obj_operateUser, reasonStr);
            }

            env->DeleteLocalRef(msgIDStr);
            env->DeleteLocalRef(j_obj_operateUser);
            env->DeleteLocalRef(reasonStr);
        }

        void AdvancedMsgListenerJni::OnRecvMessageModified(const V2TIMMessage &message) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_message = MessageJni::Convert2JObject(message);

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageModified], j_obj_message);
            }

            env->DeleteLocalRef(j_obj_message);
        }

        void AdvancedMsgListenerJni::OnRecvMessageExtensionsChanged(const V2TIMString &msgID, const V2TIMMessageExtensionVector &extensions) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDStr = StringJni::Cstring2Jstring(env, msgID.CString());

            jobject j_obj_extensionList = ArrayListJni::NewArrayList();
            for (int i = 0; i < extensions.Size(); ++i) {
                jobject j_obj_extensions = MessageExtensionJni::Convert2JObject(extensions[i]);
                if (j_obj_extensions) {
                    ArrayListJni::Add(j_obj_extensionList, j_obj_extensions);
                    env->DeleteLocalRef(j_obj_extensions);
                }
            }

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageExtensionsChanged], msgIDStr, j_obj_extensionList);
            }

            env->DeleteLocalRef(msgIDStr);
            env->DeleteLocalRef(j_obj_extensionList);
        }

        void AdvancedMsgListenerJni::OnRecvMessageExtensionsDeleted(const V2TIMString &msgID, const V2TIMStringVector &extensionKeys) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDStr = StringJni::Cstring2Jstring(env, msgID.CString());

            jobject j_obj_extensionKeyList = ArrayListJni::NewArrayList();
            for (int i = 0; i < extensionKeys.Size(); ++i) {
                jobject j_obj_extensionKey = StringJni::Cstring2Jstring(env,extensionKeys[i].CString());
                if (j_obj_extensionKey) {
                    ArrayListJni::Add(j_obj_extensionKeyList, j_obj_extensionKey);
                    env->DeleteLocalRef(j_obj_extensionKey);
                }
            }

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageExtensionsDeleted], msgIDStr, j_obj_extensionKeyList);
            }

            env->DeleteLocalRef(msgIDStr);
            env->DeleteLocalRef(j_obj_extensionKeyList);
        }

        void AdvancedMsgListenerJni::OnRecvMessageReactionsChanged(const V2TIMMessageReactionChangeInfoVector &changeInfos) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_changeInfoList = ArrayListJni::NewArrayList();
            for (int i = 0; i < changeInfos.Size(); ++i) {
                jobject j_obj_changeInfo = MessageReactionChangeInfoJni::Convert2JObject(changeInfos[i]);
                if (j_obj_changeInfo) {
                    ArrayListJni::Add(j_obj_changeInfoList, j_obj_changeInfo);
                    env->DeleteLocalRef(j_obj_changeInfo);
                }
            }

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageReactionsChanged], j_obj_changeInfoList);
            }

            env->DeleteLocalRef(j_obj_changeInfoList);
        }

        void AdvancedMsgListenerJni::OnRecvMessageRevoked(const V2TIMString &messageID) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDStr = StringJni::Cstring2Jstring(env, messageID.CString());

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageRevoked], msgIDStr);
            }

            env->DeleteLocalRef(msgIDStr);
        }
    }// namespace jni
}// namespace v2im