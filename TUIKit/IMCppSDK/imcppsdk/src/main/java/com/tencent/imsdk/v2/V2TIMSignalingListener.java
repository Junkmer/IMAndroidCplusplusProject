package com.tencent.imsdk.v2;

import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMSignalingListener.html
 */
public abstract class V2TIMSignalingListener {
    public void onReceiveNewInvitation(String inviteID, String inviter, String groupID, List<String> inviteeList, String data) {
    }

    public void onInviteeAccepted(String inviteID, String invitee, String data) {
    }

    public void onInviteeRejected(String inviteID, String invitee, String data) {
    }

    public void onInvitationCancelled(String inviteID, String inviter, String data) {
    }

    public void onInvitationTimeout(String inviteID, List<String> inviteeList) {
    }
}
