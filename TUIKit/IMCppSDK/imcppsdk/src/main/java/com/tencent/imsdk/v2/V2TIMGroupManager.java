package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public abstract class V2TIMGroupManager {

/////////////////////////////////////////////////////////////////////////////////
//                               java层-抽象函数
/////////////////////////////////////////////////////////////////////////////////

    public abstract void createGroup(V2TIMGroupInfo info, List<V2TIMCreateGroupMemberInfo> memberList, V2TIMValueCallback<String> callback);

    public abstract void getJoinedGroupList(V2TIMValueCallback<List<V2TIMGroupInfo>> callback);

    public abstract void getGroupsInfo(List<String> groupIDList, V2TIMValueCallback<List<V2TIMGroupInfoResult>> callback);

    public abstract void searchGroups(V2TIMGroupSearchParam searchParam, V2TIMValueCallback<List<V2TIMGroupInfo>> callback);

    public abstract void setGroupInfo(V2TIMGroupInfo info, V2TIMCallback callback);

    public abstract void initGroupAttributes(String groupID, HashMap<String, String> attributes, V2TIMCallback callback);

    public abstract void setGroupAttributes(String groupID, HashMap<String, String> attributes, V2TIMCallback callback);

    public abstract void deleteGroupAttributes(String groupID, List<String> keys, V2TIMCallback callback);

    public abstract void getGroupAttributes(String groupID, List<String> keys, V2TIMValueCallback<Map<String, String>> callback);

    public abstract void getGroupOnlineMemberCount(String groupID, V2TIMValueCallback<Integer> callback);

    public abstract void getGroupMemberList(String groupID, int filter, long nextSeq, V2TIMValueCallback<V2TIMGroupMemberInfoResult> callback);

    public abstract void getGroupMembersInfo(String groupID, List<String> memberList, V2TIMValueCallback<List<V2TIMGroupMemberFullInfo>> callback);

    public abstract void searchGroupMembers(V2TIMGroupMemberSearchParam param, V2TIMValueCallback<HashMap<String, List<V2TIMGroupMemberFullInfo>>> callback);

    public abstract void setGroupMemberInfo(String groupID, V2TIMGroupMemberFullInfo info, V2TIMCallback callback);

    public abstract void muteGroupMember(String groupID, String userID, int seconds, V2TIMCallback callback);

    public abstract void inviteUserToGroup(String groupID, List<String> userList, V2TIMValueCallback<List<V2TIMGroupMemberOperationResult>> callback);

    public abstract void kickGroupMember(String groupID, List<String> memberList, String reason, V2TIMValueCallback<List<V2TIMGroupMemberOperationResult>> callback);

    public abstract void setGroupMemberRole(String groupID, String userID, int role, V2TIMCallback callback);

    public abstract void markGroupMemberList(String groupID, List<String> memberIDList, int markType, boolean enableMark, V2TIMCallback callback);

    public abstract void transferGroupOwner(String groupID, String userID, V2TIMCallback callback);

    public abstract void getGroupApplicationList(V2TIMValueCallback<V2TIMGroupApplicationResult> callback);

    public abstract void acceptGroupApplication(V2TIMGroupApplication application, String reason, V2TIMCallback callback);

    public abstract void refuseGroupApplication(V2TIMGroupApplication application, String reason, V2TIMCallback callback);

    public abstract void setGroupApplicationRead(V2TIMCallback callback);

    public abstract void getJoinedCommunityList(V2TIMValueCallback<List<V2TIMGroupInfo>> callback);

    public abstract void createTopicInCommunity(String groupID, V2TIMTopicInfo topicInfo, V2TIMValueCallback<String> callback);

    public abstract void deleteTopicFromCommunity(String groupID, List<String> topicIDList, V2TIMValueCallback<List<V2TIMTopicOperationResult>> callback);

    public abstract void setTopicInfo(V2TIMTopicInfo topicInfo, V2TIMCallback callback);

    public abstract void getTopicInfoList(String groupID, List<String> topicIDList, V2TIMValueCallback<List<V2TIMTopicInfoResult>> callback);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------  native层-本地接口
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    native void nativeCreateGroup(V2TIMGroupInfo info, List<V2TIMCreateGroupMemberInfo> memberList, IMCallback<String> callback);

    native void nativeGetJoinedGroupList(IMCallback<List<V2TIMGroupInfo>> callback);

    native void nativeGetGroupsInfo(List<String> groupIDList, IMCallback<List<V2TIMGroupInfoResult>> callback);

    native void nativeSearchGroups(V2TIMGroupSearchParam searchParam, IMCallback<List<V2TIMGroupInfo>> callback);

    native void nativeSetGroupInfo(V2TIMGroupInfo info, IMCallback callback);

    native void nativeInitGroupAttributes(String groupID, HashMap<String, String> attributes, IMCallback callback);

    native void nativeSetGroupAttributes(String groupID, HashMap<String, String> attributes, IMCallback callback);

    native void nativeDeleteGroupAttributes(String groupID, List<String> keys, IMCallback callback);

    native void nativeGetGroupAttributes(String groupID, List<String> keys, IMCallback<Map<String, String>> callback);

    native void nativeGetGroupOnlineMemberCount(String groupID, IMCallback<Integer> callback);

    native void nativeGetGroupMemberList(String groupID, int filter, long nextSeq, IMCallback<V2TIMGroupMemberInfoResult> callback);

    native void nativeGetGroupMembersInfo(String groupID, List<String> memberList, IMCallback<List<V2TIMGroupMemberFullInfo>> callback);

    native void nativeSearchGroupMembers(V2TIMGroupMemberSearchParam param, IMCallback<HashMap<String, List<V2TIMGroupMemberFullInfo>>> callback);

    native void nativeSetGroupMemberInfo(String groupID, V2TIMGroupMemberFullInfo info, IMCallback callback);

    native void nativeMuteGroupMember(String groupID, String userID, int seconds, IMCallback callback);

    native void nativeInviteUserToGroup(String groupID, List<String> userList, IMCallback<List<V2TIMGroupMemberOperationResult>> callback);

    native void nativeKickGroupMember(String groupID, List<String> memberList, String reason, IMCallback<List<V2TIMGroupMemberOperationResult>> callback);

    native void nativeSetGroupMemberRole(String groupID, String userID, int role, IMCallback callback);

    native void nativeMarkGroupMemberList(String groupID, List<String> memberIDList, int markType, boolean enableMark, IMCallback callback);

    native void nativeTransferGroupOwner(String groupID, String userID, IMCallback callback);

    native void nativeGetGroupApplicationList(IMCallback<V2TIMGroupApplicationResult> callback);

    native void nativeAcceptGroupApplication(V2TIMGroupApplication application, String reason, IMCallback callback);

    native void nativeRefuseGroupApplication(V2TIMGroupApplication application, String reason, IMCallback callback);

    native void nativeSetGroupApplicationRead(IMCallback callback);

    native void nativeGetJoinedCommunityList(IMCallback<List<V2TIMGroupInfo>> callback);

    native void nativeCreateTopicInCommunity(String groupID, V2TIMTopicInfo topicInfo, IMCallback<String> callback);

    native void nativeDeleteTopicFromCommunity(String groupID, List<String> topicIDList, IMCallback<List<V2TIMTopicOperationResult>> callback);

    native void nativeSetTopicInfo(V2TIMTopicInfo topicInfo, IMCallback callback);

    native void nativeGetTopicInfoList(String groupID, List<String> topicIDList, IMCallback<List<V2TIMTopicInfoResult>> callback);

}
