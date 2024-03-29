package com.tencent.imsdk.v2;

import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMAdvancedMsgListener.html
 */
public abstract class V2TIMAdvancedMsgListener {

    public void onRecvNewMessage(V2TIMMessage msg) {
    }

    public void onRecvMessageReadReceipts(List<V2TIMMessageReceipt> receiptList) {
    }

    public void onRecvC2CReadReceipt(List<V2TIMMessageReceipt> receiptList) {
    }

    public void onRecvMessageRevoked(String msgID, V2TIMUserFullInfo operateUser, String reason) {
    }

    public void onRecvMessageModified(V2TIMMessage msg) {
    }


    public void onRecvMessageExtensionsChanged(String msgID, List<V2TIMMessageExtension> extensions) {
    }

    public void onRecvMessageExtensionsDeleted(String msgID, List<String> extensionKeys) {
    }

    public void onRecvMessageReactionsChanged(List<V2TIMMessageReactionChangeInfo> changeInfos) {
    }

    public void onRecvMessageRevoked(String msgID) {
    }
}
