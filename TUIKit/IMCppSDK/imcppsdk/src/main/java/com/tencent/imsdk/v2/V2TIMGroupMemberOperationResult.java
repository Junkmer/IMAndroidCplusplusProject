package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupMemberOperationResult.html
 */
public class V2TIMGroupMemberOperationResult implements Serializable {
    public static final int OPERATION_RESULT_FAIL = 0;
    public static final int OPERATION_RESULT_SUCC = 1;
    public static final int OPERATION_RESULT_INVALID = 2;
    public static final int OPERATION_RESULT_PENDING = 3;
    public static final int OPERATION_RESULT_OVERLIMIT = 4;

    private String memberID;
    private int result;

    public String getMemberID() {
        return memberID;
    }

    public int getResult() {
        return result;
    }
}
