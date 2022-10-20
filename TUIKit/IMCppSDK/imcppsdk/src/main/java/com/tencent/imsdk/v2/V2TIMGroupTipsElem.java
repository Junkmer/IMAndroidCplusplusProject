package com.tencent.imsdk.v2;

import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupTipsElem.html
 */
public class V2TIMGroupTipsElem extends V2TIMElem {
    public static final int GROUP_TIPS_TYPE_INVALID = 0;
    public static final int V2TIM_GROUP_TIPS_TYPE_JOIN = 1;
    public static final int V2TIM_GROUP_TIPS_TYPE_INVITE = 2;
    public static final int V2TIM_GROUP_TIPS_TYPE_QUIT = 3;
    public static final int V2TIM_GROUP_TIPS_TYPE_KICKED = 4;
    public static final int V2TIM_GROUP_TIPS_TYPE_SET_ADMIN = 5;
    public static final int V2TIM_GROUP_TIPS_TYPE_CANCEL_ADMIN = 6;
    public static final int V2TIM_GROUP_TIPS_TYPE_GROUP_INFO_CHANGE = 7;
    public static final int V2TIM_GROUP_TIPS_TYPE_MEMBER_INFO_CHANGE = 8;

    private String groupID;
    private int type;
    private V2TIMGroupMemberInfo opMember;
    private List<V2TIMGroupMemberInfo> memberList  = new ArrayList<>();
    private List<V2TIMGroupChangeInfo> groupChangeInfoList = new ArrayList<>();
    private List<V2TIMGroupMemberChangeInfo> memberChangeInfoList = new ArrayList<>();
    private int memberCount;

    public String getGroupID() {
        return groupID;
    }

    public int getType() {
        return type;
    }

    public V2TIMGroupMemberInfo getOpMember() {
        return opMember;
    }

    public List<V2TIMGroupMemberInfo> getMemberList() {
        return memberList;
    }

    public List<V2TIMGroupChangeInfo> getGroupChangeInfoList() {
        return groupChangeInfoList;
    }

    public List<V2TIMGroupMemberChangeInfo> getMemberChangeInfoList() {
        return memberChangeInfoList;
    }

    public int getMemberCount() {
        return memberCount;
    }

    private void addMember(V2TIMGroupMemberInfo changeInfo){
        memberList.add(changeInfo);
    }

    private void addGroupChangeInfo(V2TIMGroupChangeInfo changeInfo){
        groupChangeInfoList.add(changeInfo);
    }

    private void addMemberChangeInfo(V2TIMGroupMemberChangeInfo changeInfo){
        memberChangeInfoList.add(changeInfo);
    }

    @Override
    public String toString() {
        return "V2TIMGroupTipsElem{" +
                "groupID='" + groupID + '\'' +
                ", type=" + type +
                ", opMember=" + opMember +
                ", memberList=" + memberList +
                ", groupChangeInfoList=" + groupChangeInfoList +
                ", memberChangeInfoList=" + memberChangeInfoList +
                ", memberCount=" + memberCount +
                '}';
    }
}
