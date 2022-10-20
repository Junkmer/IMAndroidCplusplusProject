package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMSignalingInfo.html
 */
public class V2TIMSignalingInfo implements Serializable {
    public static final int SIGNALING_ACTION_TYPE_INVITE = 1;
    public static final int SIGNALING_ACTION_TYPE_CANCEL_INVITE = 2;
    public static final int SIGNALING_ACTION_TYPE_ACCEPT_INVITE = 3;
    public static final int SIGNALING_ACTION_TYPE_REJECT_INVITE = 4;
    public static final int SIGNALING_ACTION_TYPE_INVITE_TIMEOUT = 5;

    private String inviteID;
    private String groupID;
    private String inviter;
    private List<String> inviteeList = new ArrayList<>();
    private String data;
    private int timeout;
    private int actionType;
//    private int businessID;
//    private boolean onlineUserOnly;
//    private V2TIMOfflinePushInfo offlinePushInfo;

    public String getInviteID() {
        return inviteID;
    }

    public void setInviteID(String inviteID) {
        this.inviteID = inviteID;
    }

    public String getGroupID() {
        return groupID;
    }

    public void setGroupID(String groupID) {
        this.groupID = groupID;
    }

    public String getInviter() {
        return inviter;
    }

    public void setInviter(String inviter) {
        this.inviter = inviter;
    }

    public List<String> getInviteeList() {
        return inviteeList;
    }

    public void setInviteeList(List<String> inviteeList) {
        this.inviteeList = inviteeList;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public int getTimeout() {
        return timeout;
    }

    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }

    public int getActionType() {
        return actionType;
    }

    public void setActionType(int actionType) {
        this.actionType = actionType;
    }

//    public int getBusinessID() {
//        return businessID;
//    }
//
//    public void setBusinessID(int businessID) {
//        this.businessID = businessID;
//    }
//
//    public boolean isOnlineUserOnly() {
//        return onlineUserOnly;
//    }
//
//    public V2TIMOfflinePushInfo getOfflinePushInfo() {
//        return offlinePushInfo;
//    }

    private void addInvitee(String invitee){
        inviteeList.add(invitee);
    }
}
