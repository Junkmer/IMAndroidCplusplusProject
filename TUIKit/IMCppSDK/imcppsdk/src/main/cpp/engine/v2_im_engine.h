//
// Created by EDY on 2022/9/7.
//

#ifndef IMCPLUSPLUSDEMO_V2_IM_ENGINE_H
#define IMCPLUSPLUSDEMO_V2_IM_ENGINE_H

#include <jni.h>
#include "V2TIMCallback.h"
#include <functional>
#include "V2TIMManager.h"
#include "V2TIMConversationManager.h"
#include "V2TIMFriendshipManager.h"
#include "V2TIMGroupManager.h"
#include "V2TIMMessageManager.h"
#include "V2TIMOfflinePushManager.h"
#include "V2TIMSignalingManager.h"
#include "v2_im_common.h"
#include "download_param_jni.h"

namespace v2im {
//    class V2IMEngine final : public V2TIMManager,
//                             V2TIMConversationManager,
//                             V2TIMFriendshipManager,
//                             V2TIMGroupManager,
//                             V2TIMMessageManager,
//                             V2TIMOfflinePushManager,
//                             V2TIMSignalingManager {
    class V2IMEngine {

    protected:
        V2IMEngine() = default;

        ~V2IMEngine() = default;

    private:
        V2TIMMessageManager *GetMessageManager();

        V2TIMGroupManager *GetGroupManager();

        V2TIMConversationManager *GetConversationManager();

        V2TIMFriendshipManager *GetFriendshipManager();

        V2TIMOfflinePushManager *GetOfflinePushManager();

        V2TIMSignalingManager *GetSignalingManager();

    public:
        static V2IMEngine *GetInstance();

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMManager  ----------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------
        void AddSDKListener(V2TIMSDKListener *listener);

        void RemoveSDKListener(V2TIMSDKListener *listener);

        bool InitSDK(uint32_t sdkAppID, const V2TIMSDKConfig &config);

        void UnInitSDK();

        V2TIMString GetVersion();

        int64_t GetServerTime();

        void Login(const V2TIMString &userID, const V2TIMString &userSig, V2TIMCallback *callback);

        void Logout(V2TIMCallback *callback);

        V2TIMString GetLoginUser();

        V2TIMLoginStatus GetLoginStatus();

        void AddSimpleMsgListener(V2TIMSimpleMsgListener *listener);

        void RemoveSimpleMsgListener(V2TIMSimpleMsgListener *listener);

        V2TIMString SendC2CTextMessage(const V2TIMString &text, const V2TIMString &userID, V2TIMSendCallback *callback);

        V2TIMString SendC2CCustomMessage(const V2TIMBuffer &customData, const V2TIMString &userID, V2TIMSendCallback *callback);

        V2TIMString SendGroupTextMessage(const V2TIMString &text, const V2TIMString &groupID, V2TIMMessagePriority priority,
                                         V2TIMSendCallback *callback);

        V2TIMString SendGroupCustomMessage(const V2TIMBuffer &customData, const V2TIMString &groupID, V2TIMMessagePriority priority,
                                           V2TIMSendCallback *callback);

        void AddGroupListener(V2TIMGroupListener *listener);

        void RemoveGroupListener(V2TIMGroupListener *listener);

        void CreateGroup(const V2TIMString &groupType, const V2TIMString &groupID, const V2TIMString &groupName,
                         V2TIMValueCallback<V2TIMString> *callback);

        void JoinGroup(const V2TIMString &groupID, const V2TIMString &message, V2TIMCallback *callback);

        void QuitGroup(const V2TIMString &groupID, V2TIMCallback *callback);

        void DismissGroup(const V2TIMString &groupID, V2TIMCallback *callback);

        void GetUsersInfo(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMUserFullInfoVector> *callback);

        void SetSelfInfo(const V2TIMUserFullInfo &info, V2TIMCallback *callback);

        void GetUserStatus(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMUserStatusVector> *callback);

        void SetSelfStatus(const V2TIMUserStatus &status, V2TIMCallback *callback);

        void SubscribeUserStatus(const V2TIMStringVector &userIDList, V2TIMCallback *callback);

        void UnsubscribeUserStatus(const V2TIMStringVector &userIDList, V2TIMCallback *callback);

        void CallExperimentalAPI(const V2TIMString &api, const void *param, V2TIMValueCallback<V2TIMBaseObject> *callback);

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMConversationManager  ----------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

        void AddConversationListener(V2TIMConversationListener *listener);

        void RemoveConversationListener(V2TIMConversationListener *listener);

        void GetConversationList(uint64_t nextSeq, uint32_t count, V2TIMValueCallback<V2TIMConversationResult> *callback);

        void GetConversation(const V2TIMString &conversationID, V2TIMValueCallback<V2TIMConversation> *callback);

        void GetConversationList(const V2TIMStringVector &conversationIDList, V2TIMValueCallback<V2TIMConversationVector> *callback);

        void GetConversationListByFilter(const V2TIMConversationListFilter &filter, uint64_t nextSeq, uint32_t count,
                                         V2TIMValueCallback<V2TIMConversationResult> *callback);

        void DeleteConversation(const V2TIMString &conversationID, V2TIMCallback *callback);

        void SetConversationDraft(const V2TIMString &conversationID, const V2TIMString &draftText, V2TIMCallback *callback);

        void SetConversationCustomData(const V2TIMStringVector &conversationIDList, const V2TIMBuffer &customData,
                                       V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback);

        void PinConversation(const V2TIMString &conversationID, bool isPinned, V2TIMCallback *callback);

        void MarkConversation(const V2TIMStringVector &conversationIDList, uint64_t markType, bool enableMark,
                              V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback);

        void GetTotalUnreadMessageCount(V2TIMValueCallback<uint64_t> *callback);

        void CreateConversationGroup(const V2TIMString &groupName, const V2TIMStringVector &conversationIDList,
                                     V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback);

        void GetConversationGroupList(V2TIMValueCallback<V2TIMStringVector> *callback);

        void DeleteConversationGroup(const V2TIMString &groupName, V2TIMCallback *callback);

        void RenameConversationGroup(const V2TIMString &oldName, const V2TIMString &newName, V2TIMCallback *callback);

        void AddConversationsToGroup(const V2TIMString &groupName, const V2TIMStringVector &conversationIDList,
                                     V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback);

        void DeleteConversationsFromGroup(const V2TIMString &groupName, const V2TIMStringVector &conversationIDList,
                                          V2TIMValueCallback<V2TIMConversationOperationResultVector> *callback);

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMFriendshipManager  ------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

        void AddFriendListener(V2TIMFriendshipListener *listener);

        void RemoveFriendListener(V2TIMFriendshipListener *listener);

        void GetFriendList(V2TIMValueCallback<V2TIMFriendInfoVector> *callback);

        void GetFriendsInfo(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMFriendInfoResultVector> *callback);

        void SetFriendInfo(const V2TIMFriendInfo &info, V2TIMCallback *callback);

        void SearchFriends(const V2TIMFriendSearchParam &searchParam, V2TIMValueCallback<V2TIMFriendInfoResultVector> *callback);

        void AddFriend(const V2TIMFriendAddApplication &application, V2TIMValueCallback<V2TIMFriendOperationResult> *callback);

        void DeleteFromFriendList(const V2TIMStringVector &userIDList, V2TIMFriendType deleteType,
                                  V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback);

        void CheckFriend(const V2TIMStringVector &userIDList, V2TIMFriendType checkType,
                         V2TIMValueCallback<V2TIMFriendCheckResultVector> *callback);

        void GetFriendApplicationList(V2TIMValueCallback<V2TIMFriendApplicationResult> *callback);

        void AcceptFriendApplication(const V2TIMFriendApplication &application, V2TIMFriendAcceptType acceptType,
                                     V2TIMValueCallback<V2TIMFriendOperationResult> *callback);

        void RefuseFriendApplication(const V2TIMFriendApplication &application, V2TIMValueCallback<V2TIMFriendOperationResult> *callback);

        void DeleteFriendApplication(const V2TIMFriendApplication &application, V2TIMCallback *callback);

        void SetFriendApplicationRead(V2TIMCallback *callback);

        void AddToBlackList(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback);

        void DeleteFromBlackList(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback);

        void GetBlackList(V2TIMValueCallback<V2TIMFriendInfoVector> *callback);

        void CreateFriendGroup(const V2TIMString &groupName, const V2TIMStringVector &userIDList,
                               V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback);

        void GetFriendGroups(const V2TIMStringVector &groupNameList, V2TIMValueCallback<V2TIMFriendGroupVector> *callback);

        void DeleteFriendGroup(const V2TIMStringVector &groupNameList, V2TIMCallback *callback);

        void RenameFriendGroup(const V2TIMString &oldName, const V2TIMString &newName, V2TIMCallback *callback);

        void AddFriendsToFriendGroup(const V2TIMString &groupName, const V2TIMStringVector &userIDList,
                                     V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback);

        void DeleteFriendsFromFriendGroup(const V2TIMString &groupName, const V2TIMStringVector &userIDList,
                                          V2TIMValueCallback<V2TIMFriendOperationResultVector> *callback);

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMGroupManager  -----------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

        void CreateGroup(const V2TIMGroupInfo &info, const V2TIMCreateGroupMemberInfoVector &memberList,
                         V2TIMValueCallback<V2TIMString> *callback);

        void GetJoinedGroupList(V2TIMValueCallback<V2TIMGroupInfoVector> *callback);

        void GetGroupsInfo(const V2TIMStringVector &groupIDList, V2TIMValueCallback<V2TIMGroupInfoResultVector> *callback);

        void SearchGroups(const V2TIMGroupSearchParam &searchParam, V2TIMValueCallback<V2TIMGroupInfoVector> *callback);

        void SetGroupInfo(const V2TIMGroupInfo &info, V2TIMCallback *callback);

        void InitGroupAttributes(const V2TIMString &groupID, const V2TIMGroupAttributeMap &attributes, V2TIMCallback *callback);

        void SetGroupAttributes(const V2TIMString &groupID, const V2TIMGroupAttributeMap &attributes, V2TIMCallback *callback);

        void DeleteGroupAttributes(const V2TIMString &groupID, const V2TIMStringVector &keys, V2TIMCallback *callback);

        void GetGroupAttributes(const V2TIMString &groupID, const V2TIMStringVector &keys,
                                V2TIMValueCallback<V2TIMGroupAttributeMap> *callback);

        void GetGroupOnlineMemberCount(const V2TIMString &groupID, V2TIMValueCallback<uint32_t> *callback);

        void GetGroupMemberList(const V2TIMString &groupID, uint32_t filter, uint64_t nextSeq,
                                V2TIMValueCallback<V2TIMGroupMemberInfoResult> *callback);

        void GetGroupMembersInfo(const V2TIMString &groupID, V2TIMStringVector memberList,
                                 V2TIMValueCallback<V2TIMGroupMemberFullInfoVector> *callback);

        void SearchGroupMembers(const V2TIMGroupMemberSearchParam &param, V2TIMValueCallback<V2TIMGroupSearchGroupMembersMap> *callback);

        void SetGroupMemberInfo(const V2TIMString &groupID, const V2TIMGroupMemberFullInfo &info, V2TIMCallback *callback);

        void MuteGroupMember(const V2TIMString &groupID, const V2TIMString &userID, uint32_t seconds, V2TIMCallback *callback);

        void InviteUserToGroup(const V2TIMString &groupID, const V2TIMStringVector &userList,
                               V2TIMValueCallback<V2TIMGroupMemberOperationResultVector> *callback);

        void KickGroupMember(const V2TIMString &groupID, const V2TIMStringVector &memberList, const V2TIMString &reason,
                             V2TIMValueCallback<V2TIMGroupMemberOperationResultVector> *callback);

        void SetGroupMemberRole(const V2TIMString &groupID, const V2TIMString &userID, uint32_t role, V2TIMCallback *callback);

        void MarkGroupMemberList(const V2TIMString &groupID, const V2TIMStringVector &memberList, uint32_t markType, bool enableMark,
                                 V2TIMCallback *callback);

        void TransferGroupOwner(const V2TIMString &groupID, const V2TIMString &userID, V2TIMCallback *callback);

        void GetGroupApplicationList(V2TIMValueCallback<V2TIMGroupApplicationResult> *callback);

        void AcceptGroupApplication(const V2TIMGroupApplication &application, const V2TIMString &reason, V2TIMCallback *callback);

        void RefuseGroupApplication(const V2TIMGroupApplication &application, const V2TIMString &reason, V2TIMCallback *callback);

        void SetGroupApplicationRead(V2TIMCallback *callback);

        void GetJoinedCommunityList(V2TIMValueCallback<V2TIMGroupInfoVector> *callback);

        void CreateTopicInCommunity(const V2TIMString &groupID, const V2TIMTopicInfo &topicInfo,
                                    V2TIMValueCallback<V2TIMString> *callback);

        void DeleteTopicFromCommunity(const V2TIMString &groupID, const V2TIMStringVector &topicIDList,
                                      V2TIMValueCallback<V2TIMTopicOperationResultVector> *callback);

        void SetTopicInfo(const V2TIMTopicInfo &topicInfo, V2TIMCallback *callback);

        void GetTopicInfoList(const V2TIMString &groupID, const V2TIMStringVector &topicIDList,
                              V2TIMValueCallback<V2TIMTopicInfoResultVector> *callback);

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMMessageManager  ---------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

        void AddAdvancedMsgListener(V2TIMAdvancedMsgListener *listener);

        void RemoveAdvancedMsgListener(V2TIMAdvancedMsgListener *listener);

        V2TIMMessage CreateTextMessage(const V2TIMString &text);

        V2TIMMessage CreateTextAtMessage(const V2TIMString &text, const V2TIMStringVector &atUserList);

        V2TIMMessage CreateCustomMessage(const V2TIMBuffer &data);

        V2TIMMessage CreateCustomMessage(const V2TIMBuffer &data, const V2TIMString &description, const V2TIMString &extension);

        V2TIMMessage CreateImageMessage(const V2TIMString &imagePath);

        V2TIMMessage CreateSoundMessage(const V2TIMString &soundPath, uint32_t duration);

        V2TIMMessage CreateVideoMessage(const V2TIMString &videoFilePath, const V2TIMString &type,
                                        uint32_t duration, const V2TIMString &snapshotPath);

        V2TIMMessage CreateFileMessage(const V2TIMString &filePath, const V2TIMString &fileName);

        V2TIMMessage CreateLocationMessage(const V2TIMString &desc, double longitude, double latitude);

        V2TIMMessage CreateFaceMessage(uint32_t index, const V2TIMBuffer &data);

        V2TIMMessage CreateMergerMessage(const V2TIMMessageVector &messageList, const V2TIMString &title,
                                         const V2TIMStringVector &abstractList, const V2TIMString &compatibleText);

        V2TIMMessage CreateForwardMessage(const V2TIMMessage &message);

        V2TIMMessage CreateTargetedGroupMessage(const V2TIMMessage &message, const V2TIMStringVector &receiverList);

        V2TIMString SendMessage(V2TIMMessage &message, const V2TIMString &receiver, const V2TIMString &groupID, V2TIMMessagePriority priority,
                                bool onlineUserOnly, const V2TIMOfflinePushInfo &offlinePushInfo, V2TIMSendCallback *callback);

        void SetC2CReceiveMessageOpt(const V2TIMStringVector &userIDList, V2TIMReceiveMessageOpt opt, V2TIMCallback *callback);

        void GetC2CReceiveMessageOpt(const V2TIMStringVector &userIDList, V2TIMValueCallback<V2TIMReceiveMessageOptInfoVector> *callback);

        void SetGroupReceiveMessageOpt(const V2TIMString &groupID, V2TIMReceiveMessageOpt opt, V2TIMCallback *callback);

        void GetHistoryMessageList(const V2TIMMessageListGetOption &getOption, V2TIMValueCallback<V2TIMMessageVector> *callback);

        void RevokeMessage(const V2TIMMessage &message, V2TIMCallback *callback);

        void ModifyMessage(const V2TIMMessage &message, V2TIMCompleteCallback<V2TIMMessage> *callback);

        void MarkC2CMessageAsRead(const V2TIMString &userID, V2TIMCallback *callback);

        void MarkGroupMessageAsRead(const V2TIMString &groupID, V2TIMCallback *callback);

        void MarkAllMessageAsRead(V2TIMCallback *callback);

        void DeleteMessages(const V2TIMMessageVector &messages, V2TIMCallback *callback);

        void ClearC2CHistoryMessage(const V2TIMString &userID, V2TIMCallback *callback);

        void ClearGroupHistoryMessage(const V2TIMString &groupID, V2TIMCallback *callback);

        V2TIMString InsertGroupMessageToLocalStorage(V2TIMMessage &message, const V2TIMString &groupID, const V2TIMString &sender,
                                                     V2TIMValueCallback<V2TIMMessage> *callback);

        V2TIMString InsertC2CMessageToLocalStorage(V2TIMMessage &message, const V2TIMString &userID, const V2TIMString &sender,
                                                   V2TIMValueCallback<V2TIMMessage> *callback);

        void FindMessages(const V2TIMStringVector &messageIDList, V2TIMValueCallback<V2TIMMessageVector> *callback);

        void SearchLocalMessages(const V2TIMMessageSearchParam &searchParam, V2TIMValueCallback<V2TIMMessageSearchResult> *callback);

        void SendMessageReadReceipts(const V2TIMMessageVector &messageList, V2TIMCallback *callback);

        void GetMessageReadReceipts(const V2TIMMessageVector &messageList, V2TIMValueCallback<V2TIMMessageReceiptVector> *callback);

        void GetGroupMessageReadMemberList(const V2TIMMessage &message, V2TIMGroupMessageReadMembersFilter filter, uint64_t nextSeq, uint32_t count,
                                           V2TIMValueCallback<V2TIMGroupMessageReadMemberList> *callback);

        /** 下载富媒体消息 **/
        //图片
        void DownloadImage(const DownloadParam &param, const V2TIMImageType imageType, const V2TIMString &path, V2TIMDownloadCallback *callback);

        //语音
        void GetSoundUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback);
        void DownloadSound(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback);

        //视频
        void GetVideoUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback);
        void GetSnapshotUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback);
        void DownloadVideo(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback);
        void DownloadSnapshot(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback);

        //文件
        void GetFileUrl(const DownloadParam &param, V2TIMValueCallback<V2TIMString> *callback);
        void DownloadFile(const DownloadParam &param, const V2TIMString &path, V2TIMDownloadCallback *callback);

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMOfflinePushManager  -----------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

        void SetOfflinePushConfig(const V2TIMOfflinePushConfig &config, V2TIMCallback *callback);

        void DoBackground(uint32_t unreadCount, V2TIMCallback *callback);

        void DoForeground(V2TIMCallback *callback);

// ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------  V2TIMSignalingManager  -------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------

        void AddSignalingListener(V2TIMSignalingListener *listener);

        void RemoveSignalingListener(V2TIMSignalingListener *listener);

        V2TIMString Invite(const V2TIMString &invitee, const V2TIMString &data, bool onlineUserOnly,
                           const V2TIMOfflinePushInfo &offlinePushInfo, int timeout, V2TIMCallback *callback);

        V2TIMString InviteInGroup(const V2TIMString &groupID, const V2TIMStringVector &inviteeList,
                                  const V2TIMString &data, bool onlineUserOnly, int timeout, V2TIMCallback *callback);

        void Cancel(const V2TIMString &inviteID, const V2TIMString &data, V2TIMCallback *callback);

        void Accept(const V2TIMString &inviteID, const V2TIMString &data, V2TIMCallback *callback);

        void Reject(const V2TIMString &inviteID, const V2TIMString &data, V2TIMCallback *callback);

        V2TIMSignalingInfo GetSignalingInfo(const V2TIMMessage &msg);

        void AddInvitedSignaling(const V2TIMSignalingInfo &info, V2TIMCallback *callback);

    };
}

#endif //IMCPLUSPLUSDEMO_V2_IM_ENGINE_H
