//
// Created by Junker on 2022/9/15.
//

#include <LogUtil.h>
#include <java_basic_jni.h>
#include "simple_listener_jni.h"

#include "v2_im_engine.h"
#include "jni_util.h"
#include "jni_helper.h"
#include "user_full_info_jni.h"
#include "group_member_full_info_jni.h"

namespace v2im {
    namespace jni {

        jclass SimpleListenerJni::j_cls_;
        jmethodID SimpleListenerJni::j_method_id_array_[MethodIDMax];

        void SimpleListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddSimpleMsgListener(this);
        }

        void SimpleListenerJni::AddListener(JNIEnv *env, jobject listener_simple) {
            if (nullptr == listener_simple) {
                LOGE("SimpleListenerJni | AddListener listener_simple is null");
                return;
            }

            jobject j_obj = env->NewGlobalRef(listener_simple);
            listener_simple_map.insert(std::make_pair(listener_simple, j_obj));

        }

        void SimpleListenerJni::RemoveListener(jobject listener_simple) {
            if (nullptr == listener_simple) {
                LOGE("SimpleListenerJni | RemoveListener listener_simple is null");
                return;
            }
            listener_simple_map.erase(listener_simple);
        }

        bool SimpleListenerJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMSimpleMsgListener");
            if (nullptr == cls) {
                return false;
            }

            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID j_method = nullptr;
            j_method = env->GetMethodID(j_cls_, "onRecvC2CTextMessage",
                                        "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMUserInfo;Ljava/lang/String;)V");
            if (nullptr == j_method) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvC2CTextMessage] = j_method;

            j_method = env->GetMethodID(j_cls_, "onRecvC2CCustomMessage",
                                        "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMUserInfo;[B)V");
            if (nullptr == j_method) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvC2CCustomMessage] = j_method;

            j_method = env->GetMethodID(j_cls_, "onRecvGroupTextMessage",
                                        "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;Ljava/lang/String;)V");
            if (nullptr == j_method) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvGroupTextMessage] = j_method;

            j_method = env->GetMethodID(j_cls_, "onRecvGroupCustomMessage",
                                        "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;[B)V");
            if (nullptr == j_method) {
                return false;
            }
            j_method_id_array_[MethodIDOnRecvGroupCustomMessage] = j_method;

            return true;
        }

        void SimpleListenerJni::OnRecvC2CTextMessage(const V2TIMString &msgID, const V2TIMUserFullInfo &sender, const V2TIMString &text) {
            if (listener_simple_map.empty()) {
                return;
            }
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDJni = StringJni::Cstring2Jstring(env, msgID.CString());
            jobject senderJni = UserFullInfoJni::Convert2JObject(sender);
            jstring textJni = StringJni::Cstring2Jstring(env, msgID.CString());

            for (auto item_listener = listener_simple_map.begin(); item_listener != listener_simple_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnRecvC2CTextMessage], msgIDJni, senderJni, textJni);
            }
            env->DeleteLocalRef(msgIDJni);
            env->DeleteLocalRef(senderJni);
            env->DeleteLocalRef(textJni);
        }

        void SimpleListenerJni::OnRecvC2CCustomMessage(const V2TIMString &msgID, const V2TIMUserFullInfo &sender, const V2TIMBuffer &customData) {
            if (listener_simple_map.empty()) {
                return;
            }
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDJni = StringJni::Cstring2Jstring(env, msgID.CString());
            jobject senderJni = UserFullInfoJni::Convert2JObject(sender);
            jbyteArray customDataJni = ByteJni::Cuint8_t2JByteArray(env, customData.Data(), customData.Size());

            for (auto item_listener = listener_simple_map.begin(); item_listener != listener_simple_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnRecvC2CCustomMessage], msgIDJni, senderJni, customDataJni);
            }

            env->DeleteLocalRef(msgIDJni);
            env->DeleteLocalRef(senderJni);
            env->DeleteLocalRef(customDataJni);
        }

        void SimpleListenerJni::OnRecvGroupTextMessage(const V2TIMString &msgID, const V2TIMString &groupID, const V2TIMGroupMemberFullInfo &sender,
                                                       const V2TIMString &text) {
            if (listener_simple_map.empty()) {
                return;
            }
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDJni = StringJni::Cstring2Jstring(env, msgID.CString());
            jstring groupIDJni = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject senderJni = GroupMemberFullInfoJNI::Convert2JObject(sender);
            jstring textJni = StringJni::Cstring2Jstring(env, text.CString());

            for (auto item_listener = listener_simple_map.begin(); item_listener != listener_simple_map.end(); ++item_listener) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnRecvGroupTextMessage], msgIDJni, groupIDJni, senderJni,
                                    textJni);
            }

        }

        void SimpleListenerJni::OnRecvGroupCustomMessage(const V2TIMString &msgID, const V2TIMString &groupID, const V2TIMGroupMemberFullInfo &sender,
                                                         const V2TIMBuffer &customData) {
            if (listener_simple_map.empty()) {
                return;
            }
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring msgIDJni = StringJni::Cstring2Jstring(env, msgID.CString());
            jstring groupIDJni = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject senderJni = GroupMemberFullInfoJNI::Convert2JObject(sender);
            jbyteArray customDataJni = ByteJni::Cuint8_t2JByteArray(env, customData.Data(), customData.Size());

            for (auto item_listener = listener_simple_map.begin(); item_listener != listener_simple_map.end(); ++item_listener) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnRecvGroupTextMessage], msgIDJni, groupIDJni, senderJni,
                                    customDataJni);
            }
        }

    }
}