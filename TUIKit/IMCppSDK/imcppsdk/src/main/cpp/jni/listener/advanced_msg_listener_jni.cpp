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
                path = StringJni::Jstring2Cstring(env,listenerPath);
                if (path.empty() || path == item.first){
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
            listener_advanced_msg_map.erase(StringJni::Jstring2Cstring(env,listenerPath));
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

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageRevoked", "(Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageRevoked] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRecvMessageModified", "(Lcom/tencent/imsdk/v2/V2TIMMessage;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvMessageModified] = jmethod;

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
                if (j_obj_receipt){
                    ArrayListJni::Add(j_obj_receiptList,j_obj_receipt);
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
                if (j_obj_receipt){
                    ArrayListJni::Add(j_obj_receiptList,j_obj_receipt);
                    env->DeleteLocalRef(j_obj_receipt);
                }
            }

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageReadReceipts], j_obj_receiptList);
            }

            env->DeleteLocalRef(j_obj_receiptList);
        }

        void AdvancedMsgListenerJni::OnRecvMessageRevoked(const V2TIMString &messageID) {
            if (listener_advanced_msg_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDStr = StringJni::Cstring2Jstring(env,messageID.CString());

            for (auto &item: listener_advanced_msg_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnRecvMessageRevoked], msgIDStr);
            }

            env->DeleteLocalRef(msgIDStr);
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
    }// namespace jni
}// namespace v2im