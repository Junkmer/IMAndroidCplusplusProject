//
// Created by EDY on 2022/9/27.
//

#ifndef IMCPLUSPLUSDEMO_SIGNALING_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_SIGNALING_LISTENER_JNI_H

#include <jni.h>
#include <memory>
#include <map>
#include "V2TIMListener.h"

namespace v2im {
    namespace jni {
        class SignalingListenerJni final : public std::enable_shared_from_this<SignalingListenerJni>, V2TIMSignalingListener {
        public:
            SignalingListenerJni() = default;

            ~SignalingListenerJni() override = default;

            void InitListener();

            void AddListener(JNIEnv *env, jobject listener_signaling, jstring listenerPath);

            void RemoveListener(JNIEnv *env, jstring listenerPath);

            static bool InitIDs(JNIEnv *env);

        protected:
            // V2TIMSignalingListener
            void OnReceiveNewInvitation(const V2TIMString &inviteID, const V2TIMString &inviter, const V2TIMString &groupID,
                                        const V2TIMStringVector &inviteeList, const V2TIMString &data) override;

            void OnInviteeAccepted(const V2TIMString &inviteID, const V2TIMString &invitee, const V2TIMString &data) override;

            void OnInviteeRejected(const V2TIMString &inviteID, const V2TIMString &invitee, const V2TIMString &data) override;

            void OnInvitationCancelled(const V2TIMString &inviteID, const V2TIMString &inviter, const V2TIMString &data) override;

            void OnInvitationTimeout(const V2TIMString &inviteID, const V2TIMStringVector &inviteeList) override;

        private:
            enum MethodID{
                MethodIDOnReceiveNewInvitation = 0,
                MethodIDOnInviteeAccepted,
                MethodIDOnInviteeRejected,
                MethodIDOnInvitationCancelled,
                MethodIDOnInvitationTimeout,
                
                MethodIDMax,
            };

            std::map<std::string,jobject> listener_signaling_map;
            static jclass j_cls_;
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_SIGNALING_LISTENER_JNI_H
