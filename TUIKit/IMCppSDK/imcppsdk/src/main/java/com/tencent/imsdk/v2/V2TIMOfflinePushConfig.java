package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMOfflinePushConfig.html
 */
public class V2TIMOfflinePushConfig implements Serializable {
    private long businessID;
    private String token;
    private boolean isTPNSToken;

   public V2TIMOfflinePushConfig(long businessID, String token) {
        this.businessID = businessID;
        this.token = token;
    }

    public V2TIMOfflinePushConfig(long businessID, String token, boolean isTPNSToken) {
        this.businessID = businessID;
        this.token = token;
        this.isTPNSToken = isTPNSToken;
    }
}
