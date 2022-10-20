//
// Created by EDY on 2022/9/23.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_LISTENER_JNI_H

#include <jni.h>
#include <memory>
#include <map>
#include "V2TIMGroupManager.h"

namespace v2im {
    namespace jni {
        class GroupListenerJni final : public std::enable_shared_from_this<GroupListenerJni>, public V2TIMGroupListener {
        public:
            GroupListenerJni() = default;

            ~GroupListenerJni() override = default;

            void InitListener();

            void AddListener(JNIEnv *env, jobject listener_simple, jstring listenerPath);

            void RemoveListener(JNIEnv *env, jstring listenerPath);

            static bool InitIDs(JNIEnv *env);

        protected:
            //V2TIMGroupListener
            void OnMemberEnter(const V2TIMString &groupID, const V2TIMGroupMemberInfoVector &memberList) override;

            void OnMemberLeave(const V2TIMString &groupID, const V2TIMGroupMemberInfo &member) override;

            void OnMemberInvited(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser, const V2TIMGroupMemberInfoVector &memberList) override;

            void OnMemberKicked(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser, const V2TIMGroupMemberInfoVector &memberList) override;

            void OnMemberInfoChanged(const V2TIMString &groupID, const V2TIMGroupMemberChangeInfoVector &v2TIMGroupMemberChangeInfoList) override;

            void OnGroupCreated(const V2TIMString &groupID) override;

            void OnGroupDismissed(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser) override;

            void OnGroupRecycled(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser) override;

            void OnGroupInfoChanged(const V2TIMString &groupID, const V2TIMGroupChangeInfoVector &changeInfos) override;

            void OnGroupAttributeChanged(const V2TIMString &groupID, const V2TIMGroupAttributeMap &groupAttributeMap) override;

            void OnReceiveJoinApplication(const V2TIMString &groupID, const V2TIMGroupMemberInfo &member, const V2TIMString &opReason) override;

            void OnApplicationProcessed(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser, bool isAgreeJoin,
                                        const V2TIMString &opReason) override;

            void OnGrantAdministrator(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser,
                                      const V2TIMGroupMemberInfoVector &memberList) override;

            void OnRevokeAdministrator(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser,
                                       const V2TIMGroupMemberInfoVector &memberList) override;

            void OnQuitFromGroup(const V2TIMString &groupID) override;

            void OnReceiveRESTCustomData(const V2TIMString &groupID, const V2TIMBuffer &customData) override;

            void OnTopicCreated(const V2TIMString &groupID, const V2TIMString &topicID) override;

            void OnTopicDeleted(const V2TIMString &groupID, const V2TIMStringVector &topicIDList) override;

            void OnTopicChanged(const V2TIMString &groupID, const V2TIMTopicInfo &topicInfo) override;

        private:
            enum MethodID {
                MethodIDOnMemberEnter = 0,
                MethodIDOnMemberLeave,
                MethodIDOnMemberInvited,
                MethodIDOnMemberKicked,
                MethodIDOnMemberInfoChanged,
                MethodIDOnGroupCreated,
                MethodIDOnGroupDismissed,
                MethodIDOnGroupRecycled,
                MethodIDOnGroupInfoChanged,
                MethodIDOnReceiveJoinRequest,
                MethodIDOnReceiveJoinResponse,
                MethodIDOnGrantAdministrator,
                MethodIDOnRevokeAdministrator,
                MethodIDOnQuitFromGroup,
                MethodIDOnReceiveCustomData,
                MethodIDOnGroupAttributeChanged,
                MethodIDOnTopicCreated,
                MethodIDOnTopicDeleted,
                MethodIDOnTopicChanged,

                MethodIDMax,
            };

            std::map<std::string,jobject> listener_group_map;
            static jclass j_cls_;
            static jmethodID j_method_id_array_[MethodIDMax];
        };

    }// namespace jni
}// namespace v2im


#endif //IMCPLUSPLUSDEMO_GROUP_LISTENER_JNI_H
