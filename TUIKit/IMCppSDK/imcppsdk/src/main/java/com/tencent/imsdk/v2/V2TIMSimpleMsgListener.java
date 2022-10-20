package com.tencent.imsdk.v2;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMSimpleMsgListener.html
 */
public abstract class V2TIMSimpleMsgListener {
    public void onRecvC2CTextMessage(String msgID, V2TIMUserInfo sender, String text) {}

    public void onRecvC2CCustomMessage(String msgID, V2TIMUserInfo sender, byte[] customData) {}

    public void onRecvGroupTextMessage(String msgID, String groupID, V2TIMGroupMemberInfo sender, String text) {}

    public void onRecvGroupCustomMessage(String msgID, String groupID, V2TIMGroupMemberInfo sender, byte[] customData) {}
}
