//
// Created by EDY on 2022/9/27.
//

#include <LogUtil.h>
#include <v2_im_engine.h>
#include <jni_helper.h>
#include "signaling_listener_jni.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass SignalingListenerJni::j_cls_;
        jmethodID SignalingListenerJni::j_method_id_array_[MethodIDMax];

        void SignalingListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddSignalingListener(this);
        }

        void SignalingListenerJni::AddListener(JNIEnv *env, jobject listener_signaling, jstring listenerPath) {
            if (nullptr == listener_signaling) {
                LOGE("GroupListenerJni | AddListener listener_simple is null");
                return;
            }

            std::string path;
            for (auto &item: listener_signaling_map) {
                path = StringJni::Jstring2Cstring(env, listenerPath);
                if (path.empty() || path == item.first) {
                    return;
                }
            }

            jobject j_obj = env->NewGlobalRef(listener_signaling);
            listener_signaling_map.insert(std::make_pair(path, j_obj));
        }

        void SignalingListenerJni::RemoveListener(JNIEnv *env, jstring listenerPath) {
            if (nullptr == listenerPath) {
                LOGE("SimpleListenerJni | RemoveListener listener_simple is null");
                return;
            }
            listener_signaling_map.erase(StringJni::Jstring2Cstring(env, listenerPath));
            if (listener_signaling_map.empty()) {
                v2im::V2IMEngine::GetInstance()->RemoveSignalingListener(this);
            }
        }

        bool SignalingListenerJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMSignalingListener");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "onReceiveNewInvitation",
                                       "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/List;Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnReceiveNewInvitation] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onInviteeAccepted", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnInviteeAccepted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onInviteeRejected", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnInviteeRejected] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onInvitationCancelled", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnInvitationCancelled] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onInvitationTimeout", "(Ljava/lang/String;Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnInvitationTimeout] = jmethod;

            return true;
        }

        void SignalingListenerJni::OnReceiveNewInvitation(const V2TIMString &inviteID, const V2TIMString &inviter, const V2TIMString &groupID,
                                                          const V2TIMStringVector &inviteeList, const V2TIMString &data) {
            if (listener_signaling_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring jStr_inviteID = StringJni::Cstring2Jstring(env, inviteID.CString());
            jstring jStr_inviter = StringJni::Cstring2Jstring(env, inviter.CString());
            jstring jStr_groupID = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject inviteeListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < inviteeList.Size(); ++i) {
                jstring inviteeObj = StringJni::Cstring2Jstring(env, inviteeList[i].CString());
                if (inviteeObj) {
                    ArrayListJni::Add(inviteeListObj, inviteeObj);
                    env->DeleteLocalRef(inviteeObj);
                }
            }

            jstring jStr_data = StringJni::Cstring2Jstring(env, data.CString());

            for (auto &item: listener_signaling_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnReceiveNewInvitation], jStr_inviteID, jStr_inviter,
                                    jStr_groupID, inviteeListObj, jStr_data);
            }

            env->DeleteLocalRef(jStr_inviteID);
            env->DeleteLocalRef(jStr_inviter);
            env->DeleteLocalRef(jStr_groupID);
            env->DeleteLocalRef(inviteeListObj);
            env->DeleteLocalRef(jStr_data);
        }

        void SignalingListenerJni::OnInviteeAccepted(const V2TIMString &inviteID, const V2TIMString &invitee, const V2TIMString &data) {
            if (listener_signaling_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring jStr_inviteID = StringJni::Cstring2Jstring(env, inviteID.CString());
            jstring jStr_invitee = StringJni::Cstring2Jstring(env, invitee.CString());
            jstring jStr_data = StringJni::Cstring2Jstring(env, data.CString());

            for (auto &item: listener_signaling_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnInviteeAccepted], jStr_inviteID, jStr_invitee, jStr_data);
            }

            env->DeleteLocalRef(jStr_inviteID);
            env->DeleteLocalRef(jStr_invitee);
            env->DeleteLocalRef(jStr_data);
        }

        void SignalingListenerJni::OnInviteeRejected(const V2TIMString &inviteID, const V2TIMString &invitee, const V2TIMString &data) {
            if (listener_signaling_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring jStr_inviteID = StringJni::Cstring2Jstring(env, inviteID.CString());
            jstring jStr_invitee = StringJni::Cstring2Jstring(env, invitee.CString());
            jstring jStr_data = StringJni::Cstring2Jstring(env, data.CString());

            for (auto &item: listener_signaling_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnInviteeRejected], jStr_inviteID, jStr_invitee, jStr_data);
            }

            env->DeleteLocalRef(jStr_inviteID);
            env->DeleteLocalRef(jStr_invitee);
            env->DeleteLocalRef(jStr_data);
        }

        void SignalingListenerJni::OnInvitationCancelled(const V2TIMString &inviteID, const V2TIMString &inviter, const V2TIMString &data) {
            if (listener_signaling_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring jStr_inviteID = StringJni::Cstring2Jstring(env, inviteID.CString());
            jstring jStr_inviter = StringJni::Cstring2Jstring(env, inviter.CString());
            jstring jStr_data = StringJni::Cstring2Jstring(env, data.CString());

            for (auto &item: listener_signaling_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnInvitationCancelled], jStr_inviteID, jStr_inviter, jStr_data);
            }

            env->DeleteLocalRef(jStr_inviteID);
            env->DeleteLocalRef(jStr_inviter);
            env->DeleteLocalRef(jStr_data);
        }

        void SignalingListenerJni::OnInvitationTimeout(const V2TIMString &inviteID, const V2TIMStringVector &inviteeList) {
            if (listener_signaling_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring jStr_inviteID = StringJni::Cstring2Jstring(env, inviteID.CString());

            jobject inviteeListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < inviteeList.Size(); ++i) {
                jstring inviteeObj = StringJni::Cstring2Jstring(env, inviteeList[i].CString());
                if (inviteeObj) {
                    ArrayListJni::Add(inviteeListObj, inviteeObj);
                    env->DeleteLocalRef(inviteeObj);
                }
            }

            for (auto &item: listener_signaling_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnInvitationTimeout], jStr_inviteID, inviteeListObj);
            }

            env->DeleteLocalRef(jStr_inviteID);
            env->DeleteLocalRef(inviteeListObj);
        }
    }// namespace jni
}// namespace v2im