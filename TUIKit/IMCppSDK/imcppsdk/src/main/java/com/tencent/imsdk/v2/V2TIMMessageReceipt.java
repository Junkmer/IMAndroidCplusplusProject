package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMMessageReceipt.html
 */
public class V2TIMMessageReceipt implements Serializable {
    private String msgID;
    private String userID;
    private boolean peerRead;
    private long timestamp;
    private String groupID;
    private long readCount;
    private long unreadCount;

    public String getMsgID() {
        return msgID;
    }

    public String getUserID() {
        return userID;
    }

    public boolean isPeerRead() {
        return peerRead;
    }

    public long getTimestamp() {
        return timestamp;
    }

    public String getGroupID() {
        return groupID;
    }

    public long getReadCount() {
        return readCount;
    }

    public long getUnreadCount() {
        return unreadCount;
    }
}
