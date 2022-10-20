package com.tencent.imsdk.v2;

import java.util.List;
import java.util.Map;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupListener.html
 */
public abstract class V2TIMGroupListener {

    public void onMemberEnter(String groupID, List<V2TIMGroupMemberInfo> memberList){}

    public void onMemberLeave(String groupID, V2TIMGroupMemberInfo member){}

    public void onMemberInvited(String groupID, V2TIMGroupMemberInfo opUser, List<V2TIMGroupMemberInfo> memberList){}

    public void onMemberKicked(String groupID, V2TIMGroupMemberInfo opUser, List<V2TIMGroupMemberInfo> memberList){}

    public void onMemberInfoChanged(String groupID, List<V2TIMGroupMemberChangeInfo> v2TIMGroupMemberChangeInfoList){}

    public void onGroupCreated(String groupID){}

    public void onGroupDismissed(String groupID, V2TIMGroupMemberInfo opUser){}

    public void onGroupRecycled(String groupID, V2TIMGroupMemberInfo opUser){}

    public void onGroupInfoChanged(String groupID, List<V2TIMGroupChangeInfo> changeInfos){}

    public void onReceiveJoinApplication(String groupID, V2TIMGroupMemberInfo member, String opReason){}

    public void onApplicationProcessed(String groupID, V2TIMGroupMemberInfo opUser, boolean isAgreeJoin, String opReason){}

    public void onGrantAdministrator(String groupID, V2TIMGroupMemberInfo opUser, List<V2TIMGroupMemberInfo> memberList){}

    public void onRevokeAdministrator(String groupID, V2TIMGroupMemberInfo opUser, List<V2TIMGroupMemberInfo> memberList){}

    public void onQuitFromGroup(String groupID){}

    public void onReceiveRESTCustomData(String groupID, byte[] customData){}

    public void onGroupAttributeChanged(String groupID, Map<String, String> groupAttributeMap){}

    public void onTopicCreated(String groupID, String topicID){}

    public void onTopicDeleted(String groupID, List<String> topicIDList){}

    public void onTopicInfoChanged(String groupID, V2TIMTopicInfo topicInfo){}
}
