package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupMemberChangeInfo.html
 */
public class V2TIMGroupMemberChangeInfo implements Serializable {
    private String userID;
    private long muteTime;

    public String getUserID() {
        return userID;
    }

    public long getMuteTime() {
        return muteTime;
    }
}
