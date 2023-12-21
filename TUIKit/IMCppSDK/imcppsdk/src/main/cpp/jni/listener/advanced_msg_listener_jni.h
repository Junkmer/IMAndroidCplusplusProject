//
// Created by EDY on 2022/9/27.
//

#ifndef IMCPLUSPLUSDEMO_ADVANCED_MSG_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_ADVANCED_MSG_LISTENER_JNI_H

#include <jni.h>
#include <memory>
#include <map>
#include "V2TIMListener.h"

namespace v2im {
    namespace jni {
        class AdvancedMsgListenerJni final : public std::enable_shared_from_this<AdvancedMsgListenerJni>, V2TIMAdvancedMsgListener {
        public:
            AdvancedMsgListenerJni() = default;

            ~AdvancedMsgListenerJni() override = default;

            void InitListener();

            void AddListener(JNIEnv *env, jobject listener_advanced_msg, jstring listenerPath);

            void RemoveListener(JNIEnv *env, jstring listenerPath);

            static bool InitIDs(JNIEnv *env);

        protected:
            // V2TIMAdvancedMsgListener
            void OnRecvNewMessage(const V2TIMMessage &message) override;

            void OnRecvC2CReadReceipt(const V2TIMMessageReceiptVector &receiptList) override;

            void OnRecvMessageReadReceipts(const V2TIMMessageReceiptVector &receiptList) override;

            void OnRecvMessageRevoked(const V2TIMString &msgID, const V2TIMUserFullInfo &operateUser, const V2TIMString &reason) override;

            void OnRecvMessageModified(const V2TIMMessage &message) override;

            void OnRecvMessageExtensionsChanged(const V2TIMString &msgID,const V2TIMMessageExtensionVector &extensions) override;

            void OnRecvMessageExtensionsDeleted(const V2TIMString &msgID,const V2TIMStringVector &extensionKeys) override;

            void OnRecvMessageReactionsChanged(const V2TIMMessageReactionChangeInfoVector &changeInfos) override;

            void OnRecvMessageRevoked(const V2TIMString &msgID) override;

        private:
            enum MethodID {
                MethodIDOnRecvNewMessage = 0,
                MethodIDOnRecvMessageReadReceipts,
                MethodIDOnRecvC2CReadReceipt,
                MethodIDOnRecvMessageRevoked2Data,
                MethodIDOnRecvMessageModified,
                MethodIDOnRecvMessageExtensionsChanged,
                MethodIDOnRecvMessageExtensionsDeleted,
                MethodIDOnRecvMessageReactionsChanged,
                MethodIDOnRecvMessageRevoked,

                MethodIDMax,
            };

            std::map<std::string,jobject> listener_advanced_msg_map;
            static jclass j_cls_;
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_ADVANCED_MSG_LISTENER_JNI_H
