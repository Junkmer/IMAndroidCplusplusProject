//
// Created by EDY on 2022/9/27.
//

#ifndef IMCPLUSPLUSDEMO_CONVERSATION_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_CONVERSATION_LISTENER_JNI_H

#include <jni.h>
#include <memory>
#include <map>
#include "V2TIMListener.h"

namespace v2im {
    namespace jni {
        class ConversationListenerJni final : public std::enable_shared_from_this<ConversationListenerJni>, V2TIMConversationListener {
        public:
            ConversationListenerJni() = default;

            ~ConversationListenerJni() override = default;

            void InitListener();

            void AddListener(JNIEnv *env, jobject listener_conversation, jstring listenerPath);

            void RemoveListener(JNIEnv *env, jstring listenerPath);

            static bool InitIDs(JNIEnv *env);

        protected:
            // V2TIMConversationListener
            void OnSyncServerStart() override;

            void OnSyncServerFinish() override;

            void OnSyncServerFailed() override;

            void OnNewConversation(const V2TIMConversationVector &conversationList) override;

            void OnConversationChanged(const V2TIMConversationVector &conversationList) override;

            void OnConversationDeleted(const V2TIMStringVector &conversationIDList) override;

            void OnTotalUnreadMessageCountChanged(uint64_t totalUnreadCount) override;

            void OnUnreadMessageCountChangedByFilter(const V2TIMConversationListFilter &filter, uint64_t totalUnreadCount) override;

            void OnConversationGroupCreated(const V2TIMString &groupName, const V2TIMConversationVector &conversationList) override;

            void OnConversationGroupDeleted(const V2TIMString &groupName) override;

            void OnConversationGroupNameChanged(const V2TIMString &oldName, const V2TIMString &newName) override;

            void OnConversationsAddedToGroup(const V2TIMString &groupName, const V2TIMConversationVector &conversationList) override;

            void OnConversationsDeletedFromGroup(const V2TIMString &groupName, const V2TIMConversationVector &conversationList) override;

        private:
            enum MethodID {
                MethodIDOnSyncServerStart = 0,
                MethodIDOnSyncServerFinish,
                MethodIDOnSyncServerFailed,
                MethodIDOnNewConversation,
                MethodIDOnConversationChanged,
                MethodIDOnConversationDeleted,
                MethodIDOnTotalUnreadMessageCountChanged,
                MethodIDOnUnreadMessageCountChangedByFilter,
                MethodIDOnConversationGroupCreated,
                MethodIDOnConversationGroupDeleted,
                MethodIDOnConversationGroupNameChanged,
                MethodIDOnConversationsAddedToGroup,
                MethodIDOnConversationsDeletedFromGroup,

                MethodIDMax,
            };

            std::map<std::string, jobject> listener_conversation_map;
            static jclass j_cls_;
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_CONVERSATION_LISTENER_JNI_H
