package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupAtInfo.html
 */
public class V2TIMGroupAtInfo implements Serializable {
    public static final String AT_ALL_TAG = "__kImSDK_MesssageAtALL__";
    public static final int TIM_AT_UNKNOWN = 0;
    public static final int TIM_AT_ME = 1;
    public static final int TIM_AT_ALL = 2;
    public static final int TIM_AT_ALL_AT_ME = 3;

    private long seq;
    private int atType;

    public long getSeq() {
        return seq;
    }

    public int getAtType() {
        return atType;
    }
}
