
#include "v2_im_engine.h"

#include <utility>

#include "LogUtil.h"
#include "jni_helper.h"
#include "V2TIMManager.h"
#include "jni.h"
#include "v2_im_common.h"
#include "value_callback_impl.h"
#include "message_jni.h"

namespace v2im {

    V2IMEngine *V2IMEngine::GetInstance() {
        static auto *instance = new V2IMEngine();
        return instance;
    }

    void GetCppIMMessage(const V2TIMMessageVector &messageList, const Callback<V2TIMMessageVector> &callback) {
        if (messageList.Size() > 0) {
            V2TIMStringVector stringVector;
            for (int i = 0; i < messageList.Size(); ++i) {
                stringVector.PushBack(messageList[i].msgID);
            }

            auto findMessage_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
            findMessage_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    V2TIMMessageVector messageVector;
                    for (int i = 0; i < value.Size(); ++i) {
                        if (value[i].status == V2TIMMessageStatus::V2TIM_MSG_STATUS_SEND_SUCC) {
                            messageVector.PushBack(value[i]);
                        }
                    }
                    if (messageVector.Size() > 0) {
                        callback(V2TIMErrorCode::ERR_SUCC, "", messageVector);
                    } else {
                        callback(V2TIMErrorCode::ERR_NOT_MESSAGE, "not find message", {});
                    }
                } else {
                    callback(error_code, error_message, {});
                }
                delete findMessage_callback;
            });

            v2im::V2IMEngine::GetInstance()->FindMessages(stringVector, findMessage_callback);
        } else {
            callback(V2TIMErrorCode::ERR_NOT_MESSAGE, "not find message!", {});
        }
    }

    void GetAccurateMessage(const V2TIMMessage *message, const Callback<V2TIMMessage> &callback) {
        if (message) {
            V2TIMStringVector stringVector;
            stringVector.PushBack(message->msgID);

            auto findMessage_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
            findMessage_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    bool titleFlag = false;
                    for (int i = 0; i < value.Size(); ++i) {
                        if (!message->userID.Empty()) {
                            titleFlag = message->userID == value[i].userID;
                        } else {
                            titleFlag = message->groupID == value[i].groupID;
                        }
                        if (message->msgID == value[i].msgID && message->seq == value[i].seq && message->status == value[i].status && titleFlag) {
                            callback(V2TIMErrorCode::ERR_SUCC, "", value[i]);
                            break;
                        }
                    }
                } else {
                    callback(V2TIMErrorCode::ERR_SUCC, error_message, {});
                }
                delete findMessage_callback;
            });
            v2im::V2IMEngine::GetInstance()->FindMessages(stringVector, findMessage_callback);
        } else {
            callback(V2TIMErrorCode::ERR_NOT_MESSAGE, "not find message!", {});
        }
    }

    void GetSpecifyMessage(const DownloadParam *param, const Callback<V2TIMMessage> &callback) {
        if (param) {
            V2TIMStringVector stringVector;
            stringVector.PushBack(param->messageID);

            auto findMessage_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
            findMessage_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    bool titleFlag = false;
                    for (int i = 0; i < value.Size(); ++i) {
                        titleFlag = param->roleTypeID == value[i].userID || param->roleTypeID == value[i].groupID;

                        if (param->messageID == value[i].msgID && param->sequence == value[i].seq &&
                            V2TIMMessageStatus::V2TIM_MSG_STATUS_SEND_SUCC == value[i].status && titleFlag &&
                            param->elemType == value[i].elemList[0]->elemType) {
                            callback(V2TIMErrorCode::ERR_SUCC, "", value[i]);
                            break;
                        }
                    }
                } else {
                    callback(error_code, error_message, {});
                }
                delete findMessage_callback;
            });
            v2im::V2IMEngine::GetInstance()->FindMessages(stringVector, findMessage_callback);
        } else {
            callback(V2TIMErrorCode::ERR_NOT_MESSAGE, "not find message!", {});
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              BaseManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void V2IMEngine::AddSDKListener(V2TIMSDKListener *listener) {
        V2TIMManager::GetInstance()->AddSDKListener(listener);
    }

    void V2IMEngine::RemoveSDKListener(V2TIMSDKListener *listener) {
        V2TIMManager::GetInstance()->RemoveSDKListener(listener);
    }

    bool V2IMEngine::InitSDK(uint32_t sdkAppID, const V2TIMSDKConfig &config) {
        return V2TIMManager::GetInstance()->InitSDK(sdkAppID, config);
    }

    void V2IMEngine::UnInitSDK() {
        V2TIMManager::GetInstance()->UnInitSDK();
    }

    V2TIMString V2IMEngine::GetVersion() {
        return V2TIMManager::GetInstance()->GetVersion();
    }

    int64_t V2IMEngine::GetServerTime() {
        return V2TIMManager::GetInstance()->GetServerTime();
    }

    void V2IMEngine::Login(const V2TIMString &userID, const V2TIMString &userSig, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->Login(userID, userSig, callback);
    }

    void V2IMEngine::Logout(V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->Logout(callback);
    }

    V2TIMString V2IMEngine::GetLoginUser() {
        return V2TIMManager::GetInstance()->GetLoginUser();
    }

    V2TIMLoginStatus V2IMEngine::GetLoginStatus() {
        return V2TIMManager::GetInstance()->GetLoginStatus();
    }

    void V2IMEngine::AddSimpleMsgListener(V2TIMSimpleMsgListener *listener) {
        V2TIMManager::GetInstance()->AddSimpleMsgListener(listener);
    }

    void V2IMEngine::RemoveSimpleMsgListener(V2TIMSimpleMsgListener *listener) {
        V2TIMManager::GetInstance()->RemoveSimpleMsgListener(listener);
    }

    V2TIMString V2IMEngine::SendC2CTextMessage(const V2TIMString &text, const V2TIMString &userID, V2TIMSendCallback *callback) {
        return V2TIMManager::GetInstance()->SendC2CTextMessage(text, userID, callback);
    }

    V2TIMString V2IMEngine::SendC2CCustomMessage(const V2TIMBuffer &customData, const V2TIMString &userID, V2TIMSendCallback *callback) {
        return V2TIMManager::GetInstance()->SendC2CCustomMessage(customData, userID, callback);
    }

    V2TIMString V2IMEngine::SendGroupTextMessage(const V2TIMString &text, const V2TIMString &groupID, V2TIMMessagePriority priority,
                                                 V2TIMSendCallback *callback) {
        return V2TIMManager::GetInstance()->SendGroupTextMessage(text, groupID, priority, callback);
    }

    V2TIMString V2IMEngine::SendGroupCustomMessage(const V2TIMBuffer &customData, const V2TIMString &groupID, V2TIMMessagePriority priority,
                                                   V2TIMSendCallback *callback) {
        return V2TIMManager::GetInstance()->SendGroupCustomMessage(customData, groupID, priority, callback);
    }

    void V2IMEngine::AddGroupListener(V2TIMGroupListener *listener) {
        return V2TIMManager::GetInstance()->AddGroupListener(listener);
    }

    void V2IMEngine::RemoveGroupListener(V2TIMGroupListener *listener) {
        return V2TIMManager::GetInstance()->RemoveGroupListener(listener);
    }

    void V2IMEngine::CreateGroup(const V2TIMString &groupType, const V2TIMString &groupID, const V2TIMString &groupName,
                                 V2TIMValueCallback<V2TIMString> *callback) {
        return V2TIMManager::GetInstance()->CreateGroup(groupType, groupID, groupName, callback);
    }

    void V2IMEngine::JoinGroup(const V2TIMString &groupID, const V2TIMString &message, V2TIMCallback *callback) {
        return V2TIMManager::GetInstance()->JoinGroup(groupID, message, callback);
    }

    void V2IMEngine::QuitGroup(const V2TIMString &groupID, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->QuitGroup(groupID, callback);
    }

    void V2IMEngine::DismissGroup(const V2TIMString &groupID, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->DismissGroup(groupID, callback);
    }

    void V2IMEngine::GetUsersInfo(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMUserFullInfoVector> *callback) {
        V2TIMManager::GetInstance()->GetUsersInfo(userIDList, callback);
    }

    void V2IMEngine::SetSelfInfo(const V2TIMUserFullInfo &info, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->SetSelfInfo(info, callback);
    }

    void V2IMEngine::GetUserStatus(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMUserStatusVector> *callback) {
        V2TIMManager::GetInstance()->GetUserStatus(userIDList, callback);
    }

    void V2IMEngine::SetSelfStatus(const V2TIMUserStatus &status, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->SetSelfStatus(status, callback);
    }

    void V2IMEngine::SubscribeUserStatus(const V2TIMStringVector &userIDList, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->SubscribeUserStatus(userIDList, callback);
    }

    void V2IMEngine::UnsubscribeUserStatus(const V2TIMStringVector &userIDList, V2TIMCallback *callback) {
        V2TIMManager::GetInstance()->UnsubscribeUserStatus(userIDList, callback);
    }

    V2TIMMessageManager *V2IMEngine::GetMessageManager() {
        return V2TIMManager::GetInstance()->GetMessageManager();
    }

    V2TIMGroupManager *V2IMEngine::GetGroupManager() {
        return V2TIMManager::GetInstance()->GetGroupManager();
    }

    V2TIMConversationManager *V2IMEngine::GetConversationManager() {
        return V2TIMManager::GetInstance()->GetConversationManager();
    }

    V2TIMFriendshipManager *V2IMEngine::GetFriendshipManager() {
        return V2TIMManager::GetInstance()->GetFriendshipManager();
    }

    V2TIMOfflinePushManager *V2IMEngine::GetOfflinePushManager() {
        return V2TIMManager::GetInstance()->GetOfflinePushManager();
    }

    V2TIMSignalingManager *V2IMEngine::GetSignalingManager() {
        return V2TIMManager::GetInstance()->GetSignalingManager();
    }

    void V2IMEngine::CallExperimentalAPI(const V2TIMString &api, const void *param, V2TIMValueCallback<V2TIMBaseObject> *callback) {
        V2TIMManager::GetInstance()->CallExperimentalAPI(api, param, callback);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              ConversationManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


    void V2IMEngine::AddConversationListener(V2TIMConversationListener *listener) {
        GetConversationManager()->AddConversationListener(listener);
    }

    void V2IMEngine::RemoveConversationListener(V2TIMConversationListener *listener) {
        GetConversationManager()->RemoveConversationListener(listener);
    }

    void V2IMEngine::GetConversationList(uint64_t nextSeq, uint32_t count, V2TIMValueCallback<V2TIMConversationResult> *callback) {
        GetConversationManager()->GetConversationList(nextSeq, count, callback);
    }

    void V2IMEngine::GetConversation(const V2TIMString &conversationID, V2TIMValueCallback<V2TIMConversation> *callback) {
        GetConversationManager()->GetConversation(conversationID, callback);
    }

    void V2IMEngine::GetConversationList(const V2TIMStringVector &conversationIDList, V2TIMValueCallback<V2TIMConversationVector> *callback) {
        GetConversationManager()->GetConversationList(conversationIDList, callback);
    }

    void V2IMEngine::GetConversationListByFilter(const V2TIMConversationListFilter &filter, V2TIMValueCallback<V2TIMConversationResult> *callback) {
        GetConversationManager()->GetConversationListByFilter(filter, callback);
    }

    void V2IMEngine::DeleteConversation(const V2TIMString &conversationID, V2TIMCallback *callback) {
        GetConversationManager()->DeleteConversation(conversationID, callback);
    }

    void V2IMEngine::SetConversationDraft(const V2TIMString &conversationID, const V2TIMString &draftText, V2TIMCallback *callback) {
        GetConversationManager()->SetConversationDraft(conversationID, draftText, callback);
    }

    void V2IMEngine::SetConversationCustomData(const V2TIMStringVector &conversationIDList, const V2TIMBuffer &customData,
                                               V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback) {
        GetConversationManager()->SetConversationCustomData(conversationIDList, customData, callback);
    }

    void V2IMEngine::PinConversation(const V2TIMString &conversationID, bool isPinned, V2TIMCallback *callback) {
        GetConversationManager()->PinConversation(conversationID, isPinned, callback);
    }

    void V2IMEngine::MarkConversation(const V2TIMStringVector &conversationIDList, uint64_t markType, bool enableMark,
                                      V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback) {
        GetConversationManager()->MarkConversation(conversationIDList, markType, enableMark, callback);
    }

    void V2IMEngine::GetTotalUnreadMessageCount(V2TIMValueCallback<uint64_t> *callback) {
        GetConversationManager()->GetTotalUnreadMessageCount(callback);
    }

    void V2IMEngine::CreateConversationGroup(const V2TIMString &groupName, const V2TIMStringVector &conversationIDList,
                                             V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback) {
        GetConversationManager()->CreateConversationGroup(groupName, conversationIDList, callback);
    }

    void V2IMEngine::GetConversationGroupList(V2TIMValueCallback<V2TIMStringVector> *callback) {
        GetConversationManager()->GetConversationGroupList(callback);
    }

    void V2IMEngine::DeleteConversationGroup(const V2TIMString &groupName, V2TIMCallback *callback) {
        GetConversationManager()->DeleteConversationGroup(groupName, callback);
    }

    void V2IMEngine::RenameConversationGroup(const V2TIMString &oldName, const V2TIMString &newName, V2TIMCallback *callback) {
        GetConversationManager()->RenameConversationGroup(oldName, newName, callback);
    }

    void V2IMEngine::AddConversationsToGroup(const V2TIMString &groupName, const V2TIMStringVector &conversationIDList,
                                             V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback) {
        GetConversationManager()->AddConversationsToGroup(groupName, conversationIDList, callback);
    }

    void V2IMEngine::DeleteConversationsFromGroup(const V2TIMString &groupName, const V2TIMStringVector &conversationIDList,
                                                  V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback) {
        GetConversationManager()->DeleteConversationsFromGroup(groupName, conversationIDList, callback);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              FriendshipManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void V2IMEngine::AddFriendListener(V2TIMFriendshipListener *listener) {
        GetFriendshipManager()->AddFriendListener(listener);
    }

    void V2IMEngine::RemoveFriendListener(V2TIMFriendshipListener *listener) {
        GetFriendshipManager()->RemoveFriendListener(listener);
    }

    void V2IMEngine::GetFriendList(V2TIMValueCallback<V2TIMFriendInfoVector> *callback) {
        GetFriendshipManager()->GetFriendList(callback);
    }

    void V2IMEngine::GetFriendsInfo(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMFriendInfoResultVector> *callback) {
        GetFriendshipManager()->GetFriendsInfo(userIDList, callback);
    }

    void V2IMEngine::SetFriendInfo(const V2TIMFriendInfo &info, V2TIMCallback *callback) {
        GetFriendshipManager()->SetFriendInfo(info, callback);
    }

    void V2IMEngine::SearchFriends(const V2TIMFriendSearchParam &searchParam, V2TIMValueCallback<V2TIMFriendInfoResultVector> *callback) {
        GetFriendshipManager()->SearchFriends(searchParam, callback);
    }

    void V2IMEngine::AddFriend(const V2TIMFriendAddApplication &application, V2TIMValueCallback<V2TIMFriendOperationResult> *callback) {
        GetFriendshipManager()->AddFriend(application, callback);
    }

    void V2IMEngine::DeleteFromFriendList(const V2TIMStringVector &userIDList, V2TIMFriendType deleteType,
                                          V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback) {
        GetFriendshipManager()->DeleteFromFriendList(userIDList, deleteType, callback);
    }

    void V2IMEngine::CheckFriend(const V2TIMStringVector &userIDList, V2TIMFriendType checkType,
                                 V2TIMValueCallback<V2TIMFriendCheckResultVector> *callback) {
        GetFriendshipManager()->CheckFriend(userIDList, checkType, callback);
    }

    void V2IMEngine::GetFriendApplicationList(V2TIMValueCallback<V2TIMFriendApplicationResult> *callback) {
        GetFriendshipManager()->GetFriendApplicationList(callback);
    }

    void V2IMEngine::AcceptFriendApplication(const V2TIMFriendApplication &application, V2TIMFriendAcceptType acceptType,
                                             V2TIMValueCallback<V2TIMFriendOperationResult> *callback) {
        GetFriendshipManager()->AcceptFriendApplication(application, acceptType, callback);
    }

    void V2IMEngine::RefuseFriendApplication(const V2TIMFriendApplication &application, V2TIMValueCallback<V2TIMFriendOperationResult> *callback) {
        GetFriendshipManager()->RefuseFriendApplication(application, callback);
    }

    void V2IMEngine::DeleteFriendApplication(const V2TIMFriendApplication &application, V2TIMCallback *callback) {
        GetFriendshipManager()->DeleteFriendApplication(application, callback);
    }

    void V2IMEngine::SetFriendApplicationRead(V2TIMCallback *callback) {
        GetFriendshipManager()->SetFriendApplicationRead(callback);
    }

    void V2IMEngine::AddToBlackList(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback) {
        GetFriendshipManager()->AddToBlackList(userIDList, callback);
    }

    void V2IMEngine::DeleteFromBlackList(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback) {
        GetFriendshipManager()->DeleteFromBlackList(userIDList, callback);
    }

    void V2IMEngine::GetBlackList(V2TIMValueCallback<V2TIMFriendInfoVector> *callback) {
        GetFriendshipManager()->GetBlackList(callback);
    }

    void V2IMEngine::CreateFriendGroup(const V2TIMString &groupName, const V2TIMStringVector &userIDList,
                                       V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback) {
        GetFriendshipManager()->CreateFriendGroup(groupName, userIDList, callback);
    }

    void V2IMEngine::GetFriendGroups(const V2TIMStringVector &groupNameList, V2TIMValueCallback<V2TIMFriendGroupVector> *callback) {
        GetFriendshipManager()->GetFriendGroups(groupNameList, callback);
    }

    void V2IMEngine::DeleteFriendGroup(const V2TIMStringVector &groupNameList, V2TIMCallback *callback) {
        GetFriendshipManager()->DeleteFriendGroup(groupNameList, callback);
    }

    void V2IMEngine::RenameFriendGroup(const V2TIMString &oldName, const V2TIMString &newName, V2TIMCallback *callback) {
        GetFriendshipManager()->RenameFriendGroup(oldName, newName, callback);
    }

    void V2IMEngine::AddFriendsToFriendGroup(const V2TIMString &groupName, const V2TIMStringVector &userIDList,
                                             V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback) {
        GetFriendshipManager()->AddFriendsToFriendGroup(groupName, userIDList, callback);
    }

    void V2IMEngine::DeleteFriendsFromFriendGroup(const V2TIMString &groupName, const V2TIMStringVector &userIDList,
                                                  V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback) {
        GetFriendshipManager()->DeleteFriendsFromFriendGroup(groupName, userIDList, callback);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              GroupManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void V2IMEngine::CreateGroup(const V2TIMGroupInfo &info, const V2TIMCreateGroupMemberInfoVector &memberList,
                                 V2TIMValueCallback<V2TIMString> *callback) {
        GetGroupManager()->CreateGroup(info, memberList, callback);
    }

    void V2IMEngine::GetJoinedGroupList(V2TIMValueCallback<V2TIMGroupInfoVector> *callback) {
        GetGroupManager()->GetJoinedGroupList(callback);
    }

    void V2IMEngine::GetGroupsInfo(const V2TIMStringVector &groupIDList, V2TIMValueCallback<V2TIMGroupInfoResultVector> *callback) {
        GetGroupManager()->GetGroupsInfo(groupIDList, callback);
    }

    void V2IMEngine::SearchGroups(const V2TIMGroupSearchParam &searchParam, V2TIMValueCallback<V2TIMGroupInfoVector> *callback) {
        GetGroupManager()->SearchGroups(searchParam, callback);
    }

    void V2IMEngine::SetGroupInfo(const V2TIMGroupInfo &info, V2TIMCallback *callback) {
        GetGroupManager()->SetGroupInfo(info, callback);
    }

    void V2IMEngine::InitGroupAttributes(const V2TIMString &groupID, const V2TIMGroupAttributeMap &attributes, V2TIMCallback *callback) {
        GetGroupManager()->InitGroupAttributes(groupID, attributes, callback);
    }

    void V2IMEngine::SetGroupAttributes(const V2TIMString &groupID, const V2TIMGroupAttributeMap &attributes, V2TIMCallback *callback) {
        GetGroupManager()->SetGroupAttributes(groupID, attributes, callback);
    }

    void V2IMEngine::DeleteGroupAttributes(const V2TIMString &groupID, const V2TIMStringVector &keys, V2TIMCallback *callback) {
        GetGroupManager()->DeleteGroupAttributes(groupID, keys, callback);
    }

    void V2IMEngine::GetGroupAttributes(const V2TIMString &groupID, const V2TIMStringVector &keys,
                                        V2TIMValueCallback<V2TIMGroupAttributeMap> *callback) {
        GetGroupManager()->GetGroupAttributes(groupID, keys, callback);
    }

    void V2IMEngine::GetGroupOnlineMemberCount(const V2TIMString &groupID, V2TIMValueCallback<uint32_t> *callback) {
        GetGroupManager()->GetGroupOnlineMemberCount(groupID, callback);
    }

    void V2IMEngine::GetGroupMemberList(const V2TIMString &groupID, uint32_t filter, uint64_t nextSeq,
                                        V2TIMValueCallback<V2TIMGroupMemberInfoResult> *callback) {
        GetGroupManager()->GetGroupMemberList(groupID, filter, nextSeq, callback);
    }

    void V2IMEngine::GetGroupMembersInfo(const V2TIMString &groupID, V2TIMStringVector memberList,
                                         V2TIMValueCallback<V2TIMGroupMemberFullInfoVector> *callback) {
        GetGroupManager()->GetGroupMembersInfo(groupID, memberList, callback);
    }

    void V2IMEngine::SearchGroupMembers(const V2TIMGroupMemberSearchParam &param, V2TIMValueCallback<V2TIMGroupSearchGroupMembersMap> *callback) {
        GetGroupManager()->SearchGroupMembers(param, callback);
    }

    void V2IMEngine::SetGroupMemberInfo(const V2TIMString &groupID, const V2TIMGroupMemberFullInfo &info, V2TIMCallback *callback) {
        GetGroupManager()->SetGroupMemberInfo(groupID, info, callback);
    }

    void V2IMEngine::MuteGroupMember(const V2TIMString &groupID, const V2TIMString &userID, uint32_t seconds, V2TIMCallback *callback) {
        GetGroupManager()->MuteGroupMember(groupID, userID, seconds, callback);
    }

    void V2IMEngine::InviteUserToGroup(const V2TIMString &groupID, const V2TIMStringVector &userList,
                                       V2TIMValueCallback<V2TIMGroupMemberOperationResultVector> *callback) {
        GetGroupManager()->InviteUserToGroup(groupID, userList, callback);
    }

    void V2IMEngine::KickGroupMember(const V2TIMString &groupID, const V2TIMStringVector &memberList, const V2TIMString &reason,
                                     V2TIMValueCallback<V2TIMGroupMemberOperationResultVector> *callback) {
        GetGroupManager()->KickGroupMember(groupID, memberList, reason, callback);
    }

    void V2IMEngine::SetGroupMemberRole(const V2TIMString &groupID, const V2TIMString &userID, uint32_t role, V2TIMCallback *callback) {
        GetGroupManager()->SetGroupMemberRole(groupID, userID, role, callback);
    }

    void V2IMEngine::MarkGroupMemberList(const V2TIMString &groupID, const V2TIMStringVector &memberList, uint32_t markType, bool enableMark,
                                         V2TIMCallback *callback) {
        GetGroupManager()->MarkGroupMemberList(groupID, memberList, markType, enableMark, callback);
    }

    void V2IMEngine::TransferGroupOwner(const V2TIMString &groupID, const V2TIMString &userID, V2TIMCallback *callback) {
        GetGroupManager()->TransferGroupOwner(groupID, userID, callback);
    }

    void V2IMEngine::GetGroupApplicationList(V2TIMValueCallback<V2TIMGroupApplicationResult> *callback) {
        GetGroupManager()->GetGroupApplicationList(callback);
    }

    void V2IMEngine::AcceptGroupApplication(const V2TIMGroupApplication &application, const V2TIMString &reason, V2TIMCallback *callback) {
        GetGroupManager()->AcceptGroupApplication(application, reason, callback);
    }

    void V2IMEngine::RefuseGroupApplication(const V2TIMGroupApplication &application, const V2TIMString &reason, V2TIMCallback *callback) {
        GetGroupManager()->RefuseGroupApplication(application, reason, callback);
    }

    void V2IMEngine::SetGroupApplicationRead(V2TIMCallback *callback) {
        GetGroupManager()->SetGroupApplicationRead(callback);
    }

    void V2IMEngine::GetJoinedCommunityList(V2TIMValueCallback<V2TIMGroupInfoVector> *callback) {
        GetGroupManager()->GetJoinedCommunityList(callback);
    }

    void V2IMEngine::CreateTopicInCommunity(const V2TIMString &groupID, const V2TIMTopicInfo &topicInfo,
                                            V2TIMValueCallback<V2TIMString> *callback) {
        GetGroupManager()->CreateTopicInCommunity(groupID, topicInfo, callback);
    }

    void V2IMEngine::DeleteTopicFromCommunity(const V2TIMString &groupID, const V2TIMStringVector &topicIDList,
                                              V2TIMValueCallback<V2TIMTopicOperationResultVector> *callback) {
        GetGroupManager()->DeleteTopicFromCommunity(groupID, topicIDList, callback);
    }

    void V2IMEngine::SetTopicInfo(const V2TIMTopicInfo &topicInfo, V2TIMCallback *callback) {
        GetGroupManager()->SetTopicInfo(topicInfo, callback);
    }

    void V2IMEngine::GetTopicInfoList(const V2TIMString &groupID, const V2TIMStringVector &topicIDList,
                                      V2TIMValueCallback<V2TIMTopicInfoResultVector> *callback) {
        GetGroupManager()->GetTopicInfoList(groupID, topicIDList, callback);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              MessageBaseManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void V2IMEngine::AddAdvancedMsgListener(V2TIMAdvancedMsgListener *listener) {
        GetMessageManager()->AddAdvancedMsgListener(listener);
    }

    void V2IMEngine::RemoveAdvancedMsgListener(V2TIMAdvancedMsgListener *listener) {
        GetMessageManager()->RemoveAdvancedMsgListener(listener);
    }

    V2TIMMessage V2IMEngine::CreateTextMessage(const V2TIMString &text) {
        return GetMessageManager()->CreateTextMessage(text);
    }

    V2TIMMessage V2IMEngine::CreateTextAtMessage(const V2TIMString &text, const V2TIMStringVector &atUserList) {
        return GetMessageManager()->CreateTextAtMessage(text, atUserList);
    }

    V2TIMMessage V2IMEngine::CreateCustomMessage(const V2TIMBuffer &data) {
        return GetMessageManager()->CreateCustomMessage(data);
    }

    V2TIMMessage V2IMEngine::CreateCustomMessage(const V2TIMBuffer &data, const V2TIMString &description, const V2TIMString &extension) {
        return GetMessageManager()->CreateCustomMessage(data, description, extension);
    }

    V2TIMMessage V2IMEngine::CreateImageMessage(const V2TIMString &imagePath) {
        return GetMessageManager()->CreateImageMessage(imagePath);
    }

    V2TIMMessage V2IMEngine::CreateSoundMessage(const V2TIMString &soundPath, uint32_t duration) {
        return GetMessageManager()->CreateSoundMessage(soundPath, duration);
    }

    V2TIMMessage V2IMEngine::CreateVideoMessage(const V2TIMString &videoFilePath, const V2TIMString &type,
                                                uint32_t duration, const V2TIMString &snapshotPath) {
        return GetMessageManager()->CreateVideoMessage(videoFilePath, type, duration, snapshotPath);
    }

    V2TIMMessage V2IMEngine::CreateFileMessage(const V2TIMString &filePath, const V2TIMString &fileName) {
        return GetMessageManager()->CreateFileMessage(filePath, fileName);
    }

    V2TIMMessage V2IMEngine::CreateLocationMessage(const V2TIMString &desc, double longitude, double latitude) {
        return GetMessageManager()->CreateLocationMessage(desc, longitude, latitude);
    }

    V2TIMMessage V2IMEngine::CreateFaceMessage(uint32_t index, const V2TIMBuffer &data) {
        return GetMessageManager()->CreateFaceMessage(index, data);
    }

    V2TIMMessage V2IMEngine::CreateMergerMessage(const V2TIMMessageVector &messageList, const V2TIMString &title,
                                                 const V2TIMStringVector &abstractList, const V2TIMString &compatibleText) {
        return GetMessageManager()->CreateMergerMessage(messageList, title, abstractList, compatibleText);
    }

    V2TIMMessage V2IMEngine::CreateForwardMessage(const V2TIMMessage &message) {
        return GetMessageManager()->CreateForwardMessage(message);
    }

    V2TIMMessage V2IMEngine::CreateTargetedGroupMessage(const V2TIMMessage &message, const V2TIMStringVector &receiverList) {
        return GetMessageManager()->CreateTargetedGroupMessage(message, receiverList);
    }

    V2TIMString V2IMEngine::SendMessage(V2TIMMessage &message, const V2TIMString &receiver, const V2TIMString &groupID, V2TIMMessagePriority priority,
                                        bool onlineUserOnly, const V2TIMOfflinePushInfo &offlinePushInfo, V2TIMSendCallback *callback) {
        return GetMessageManager()->SendMessage(message, receiver, groupID, priority, onlineUserOnly, offlinePushInfo, callback);
    }

    void V2IMEngine::SetC2CReceiveMessageOpt(const V2TIMStringVector &userIDList, V2TIMReceiveMessageOpt opt, V2TIMCallback *callback) {
        GetMessageManager()->SetC2CReceiveMessageOpt(userIDList, opt, callback);
    }

    void V2IMEngine::GetC2CReceiveMessageOpt(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMReceiveMessageOptInfoVector> *callback) {
        GetMessageManager()->GetC2CReceiveMessageOpt(userIDList, callback);
    }

    void V2IMEngine::SetGroupReceiveMessageOpt(const V2TIMString &groupID, V2TIMReceiveMessageOpt opt, V2TIMCallback *callback) {
        GetMessageManager()->SetGroupReceiveMessageOpt(groupID, opt, callback);
    }

    void V2IMEngine::GetHistoryMessageList(const V2TIMMessageListGetOption &getOption, V2TIMValueCallback<V2TIMMessageVector> *callback) {
        GetAccurateMessage(getOption.lastMsg, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            V2TIMMessageListGetOption option = getOption;
            if (V2TIMErrorCode::ERR_SUCC == error_code) {
                auto *message = new V2TIMMessage(value);
                option.lastMsg = message;
            }
            GetMessageManager()->GetHistoryMessageList(option, callback);
        });
    }

    void V2IMEngine::RevokeMessage(const V2TIMMessage &message, V2TIMCallback *callback) {
        GetMessageManager()->RevokeMessage(message, callback);
    }

    void V2IMEngine::ModifyMessage(const V2TIMMessage &message, V2TIMCompleteCallback<V2TIMMessage> *callback) {
        GetMessageManager()->ModifyMessage(message, callback);
    }

    void V2IMEngine::MarkC2CMessageAsRead(const V2TIMString &userID, V2TIMCallback *callback) {
        GetMessageManager()->MarkC2CMessageAsRead(userID, callback);
    }

    void V2IMEngine::MarkGroupMessageAsRead(const V2TIMString &groupID, V2TIMCallback *callback) {
        GetMessageManager()->MarkGroupMessageAsRead(groupID, callback);
    }

    void V2IMEngine::MarkAllMessageAsRead(V2TIMCallback *callback) {
        GetMessageManager()->MarkAllMessageAsRead(callback);
    }

    void V2IMEngine::DeleteMessages(const V2TIMMessageVector &messages, V2TIMCallback *callback) {
        GetMessageManager()->DeleteMessages(messages, callback);
    }

    void V2IMEngine::ClearC2CHistoryMessage(const V2TIMString &userID, V2TIMCallback *callback) {
        GetMessageManager()->ClearC2CHistoryMessage(userID, callback);
    }

    void V2IMEngine::ClearGroupHistoryMessage(const V2TIMString &groupID, V2TIMCallback *callback) {
        GetMessageManager()->ClearGroupHistoryMessage(groupID, callback);
    }

    V2TIMString V2IMEngine::InsertGroupMessageToLocalStorage(V2TIMMessage &message, const V2TIMString &groupID, const V2TIMString &sender,
                                                             V2TIMValueCallback<V2TIMMessage> *callback) {
        return GetMessageManager()->InsertGroupMessageToLocalStorage(message, groupID, sender, callback);
    }

    V2TIMString V2IMEngine::InsertC2CMessageToLocalStorage(V2TIMMessage &message, const V2TIMString &userID, const V2TIMString &sender,
                                                           V2TIMValueCallback<V2TIMMessage> *callback) {
        return GetMessageManager()->InsertC2CMessageToLocalStorage(message, userID, sender, callback);
    }

    void V2IMEngine::FindMessages(const V2TIMStringVector &messageIDList, V2TIMValueCallback<V2TIMMessageVector> *callback) {
        GetMessageManager()->FindMessages(messageIDList, callback);
    }

    void V2IMEngine::SearchLocalMessages(const V2TIMMessageSearchParam &searchParam, V2TIMValueCallback<V2TIMMessageSearchResult> *callback) {
        GetMessageManager()->SearchLocalMessages(searchParam, callback);
    }

    void V2IMEngine::SendMessageReadReceipts(const V2TIMMessageVector &messageList, V2TIMCallback *callback) {
        GetMessageManager()->SendMessageReadReceipts(messageList, callback);
    }


    void V2IMEngine::GetMessageReadReceipts(const V2TIMMessageVector &messageList, V2TIMValueCallback<V2TIMMessageReceiptVector> *callback) {
        GetCppIMMessage(messageList, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
            GetMessageManager()->GetMessageReadReceipts(value, callback);
        });
    }

    void V2IMEngine::GetGroupMessageReadMemberList(const V2TIMMessage &message, V2TIMGroupMessageReadMembersFilter filter,
                                                   uint64_t nextSeq, uint32_t count, V2TIMValueCallback<V2TIMGroupMessageReadMemberList> *callback) {
        auto *timMessage = new V2TIMMessage(message);
        GetAccurateMessage(timMessage, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (V2TIMErrorCode::ERR_SUCC == error_code) {
                GetMessageManager()->GetGroupMessageReadMemberList(value, filter, nextSeq, count, callback);
            } else {
                GetMessageManager()->GetGroupMessageReadMemberList(value, filter, nextSeq, count, callback);
            }
        });
    }

    /** 下载富媒体消息 **/
    //图片
    void V2IMEngine::DownloadImage(const DownloadParam &param, const V2TIMImageType imageType, const V2TIMString &path,
                                   V2TIMDownloadCallback *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_IMAGE) {
                    auto *imageElem = dynamic_cast<V2TIMImageElem *>(elem);
                    V2TIMImageVector imageVector = imageElem->imageList;
                    for (int i = 0; i < imageVector.Size(); ++i) {
                        if (imageVector[i].type == imageType) {
                            imageVector[i].DownloadImage(path, callback);
                            break;
                        }
                    }
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    //语音
    void V2IMEngine::GetSoundUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_SOUND) {
                    auto *soundElem = dynamic_cast<V2TIMSoundElem *>(elem);
                    soundElem->GetUrl(callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    void V2IMEngine::DownloadSound(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_SOUND) {
                    auto *soundElem = dynamic_cast<V2TIMSoundElem *>(elem);
                    soundElem->DownloadSound(path, callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    //视频
    void V2IMEngine::GetVideoUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_VIDEO) {
                    auto *videoElem = dynamic_cast<V2TIMVideoElem *>(elem);
                    videoElem->GetVideoUrl(callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    void V2IMEngine::GetSnapshotUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_VIDEO) {
                    auto *videoElem = dynamic_cast<V2TIMVideoElem *>(elem);
                    videoElem->GetSnapshotUrl(callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    void V2IMEngine::DownloadVideo(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_VIDEO) {
                    auto *videoElem = dynamic_cast<V2TIMVideoElem *>(elem);
                    videoElem->DownloadVideo(path, callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    void V2IMEngine::DownloadSnapshot(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_VIDEO) {
                    auto *videoElem = dynamic_cast<V2TIMVideoElem *>(elem);
                    videoElem->DownloadSnapshot(path, callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    //文件
    void V2IMEngine::GetFileUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_FILE) {
                    auto *fileElem = dynamic_cast<V2TIMFileElem *>(elem);
                    fileElem->GetUrl(callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

    void V2IMEngine::DownloadFile(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback) {
        auto *pItem = new DownloadParam(param);
        GetSpecifyMessage(pItem, [=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
            if (error_code == V2TIMErrorCode::ERR_SUCC) {
                V2TIMElem *elem = value.elemList[0];
                if (elem->elemType == V2TIM_ELEM_TYPE_FILE) {
                    auto *fileElem = dynamic_cast<V2TIMFileElem *>(elem);
                    fileElem->DownloadFile(path, callback);
                }
            } else {
                callback->OnError(error_code, error_message);
            }
        });
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              OfflinePushManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void V2IMEngine::SetOfflinePushConfig(const V2TIMOfflinePushConfig &config, V2TIMCallback *callback) {
        GetOfflinePushManager()->SetOfflinePushConfig(config, callback);
    }

    void V2IMEngine::DoBackground(uint32_t unreadCount, V2TIMCallback *callback) {
        GetOfflinePushManager()->DoBackground(unreadCount, callback);
    }

    void V2IMEngine::DoForeground(V2TIMCallback *callback) {
        GetOfflinePushManager()->DoForeground(callback);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              SignalingManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void V2IMEngine::AddSignalingListener(V2TIMSignalingListener *listener) {
        GetSignalingManager()->AddSignalingListener(listener);
    }

    void V2IMEngine::RemoveSignalingListener(V2TIMSignalingListener *listener) {
        GetSignalingManager()->RemoveSignalingListener(listener);
    }

    V2TIMString V2IMEngine::Invite(const V2TIMString &invitee, const V2TIMString &data, bool onlineUserOnly,
                                   const V2TIMOfflinePushInfo &offlinePushInfo, int timeout, V2TIMCallback *callback) {
        return GetSignalingManager()->Invite(invitee, data, onlineUserOnly, offlinePushInfo, timeout, callback);
    }

    V2TIMString V2IMEngine::InviteInGroup(const V2TIMString &groupID, const V2TIMStringVector &inviteeList,
                                          const V2TIMString &data, bool onlineUserOnly, int timeout, V2TIMCallback *callback) {
        return GetSignalingManager()->InviteInGroup(groupID, inviteeList, data, onlineUserOnly, timeout, callback);
    }

    void V2IMEngine::Cancel(const V2TIMString &inviteID, const V2TIMString &data, V2TIMCallback *callback) {
        GetSignalingManager()->Cancel(inviteID, data, callback);
    }

    void V2IMEngine::Accept(const V2TIMString &inviteID, const V2TIMString &data, V2TIMCallback *callback) {
        GetSignalingManager()->Accept(inviteID, data, callback);
    }

    void V2IMEngine::Reject(const V2TIMString &inviteID, const V2TIMString &data, V2TIMCallback *callback) {
        GetSignalingManager()->Reject(inviteID, data, callback);
    }

    V2TIMSignalingInfo V2IMEngine::GetSignalingInfo(const V2TIMMessage &msg) {
        return GetSignalingManager()->GetSignalingInfo(msg);
    }

    void V2IMEngine::AddInvitedSignaling(const V2TIMSignalingInfo &info, V2TIMCallback *callback) {
        GetSignalingManager()->AddInvitedSignaling(info, callback);
    }

}

