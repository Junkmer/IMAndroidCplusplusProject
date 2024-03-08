//
// Created by Junker on 2022/9/15.
//

#ifndef IMCPLUSPLUSDEMO_SIMPLE_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_SIMPLE_LISTENER_JNI_H

#include <jni.h>
#include <memory>

#include "../include/V2TIMListener.h"
#include <map>

namespace v2im {
    namespace jni {
        class SimpleListenerJni final : public std::enable_shared_from_this<SimpleListenerJni>,
                                        public V2TIMSimpleMsgListener {

        public:
            SimpleListenerJni() = default;

            ~SimpleListenerJni() override = default;

            void InitListener();

            void AddListener(JNIEnv *env, jobject listener_simple);

            void RemoveListener(jobject listener_simple);

            static bool InitIDs(JNIEnv *env);

        protected:
            // V2TIMSimpleMsgListener

            void OnRecvC2CTextMessage(const V2TIMString &msgID, const V2TIMUserFullInfo &sender, const V2TIMString &text) override;

            void OnRecvC2CCustomMessage(const V2TIMString &msgID, const V2TIMUserFullInfo &sender, const V2TIMBuffer &customData) override;

            void OnRecvGroupTextMessage(const V2TIMString &msgID, const V2TIMString &groupID, const V2TIMGroupMemberFullInfo &sender, const V2TIMString &text) override;

            void OnRecvGroupCustomMessage(const V2TIMString &msgID, const V2TIMString &groupID, const V2TIMGroupMemberFullInfo &sender, const V2TIMBuffer &customData) override;

        private:

            enum MethodID {
                MethodIDOnRecvC2CTextMessage = 0,
                MethodIDOnRecvC2CCustomMessage,
                MethodIDOnRecvGroupTextMessage,
                MethodIDOnRecvGroupCustomMessage,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jmethodID j_method_id_array_[MethodIDMax];
            std::map<jobject,jobject> listener_simple_map;
        };
    }
}

#endif //IMCPLUSPLUSDEMO_SIMPLE_LISTENER_JNI_H
