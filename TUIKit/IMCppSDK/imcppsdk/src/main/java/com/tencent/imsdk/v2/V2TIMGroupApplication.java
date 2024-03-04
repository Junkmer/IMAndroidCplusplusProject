package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupApplication.html
 */
public class V2TIMGroupApplication implements Serializable {
    public static final int V2TIM_GROUP_JOIN_APPLICATION_NEED_APPROVED_BY_ADMIN = 0;
    public static final int V2TIM_GROUP_INVITE_APPLICATION_NEED_APPROVED_BY_INVITEE = 1;
    public static final int V2TIM_GROUP_INVITE_APPLICATION_NEED_APPROVED_BY_ADMIN = 2;
    public static final int V2TIM_GROUP_APPLICATION_HANDLE_STATUS_UNHANDLED = 0;
    public static final int V2TIM_GROUP_APPLICATION_HANDLE_STATUS_HANDLED_BY_OTHER = 1;
    public static final int V2TIM_GROUP_APPLICATION_HANDLE_STATUS_HANDLED_BY_SELF = 2;
    public static final int V2TIM_GROUP_APPLICATION_HANDLE_RESULT_REFUSE = 0;
    public static final int V2TIM_GROUP_APPLICATION_HANDLE_RESULT_AGREE = 1;

    private String groupID;
    private String fromUser;
    private String fromUserNickName;
    private String fromUserFaceUrl;
    private String toUser;
    private long addTime;
    private String requestMsg;
    private String handledMsg;
    private int applicationType;
    private int handleStatus;
    private int handleResult;

    public String getGroupID() {
        return groupID;
    }

    public String getFromUser() {
        return fromUser;
    }

    public String getFromUserNickName() {
        return fromUserNickName;
    }

    public String getFromUserFaceUrl() {
        return fromUserFaceUrl;
    }

    public String getToUser() {
        return toUser;
    }

    public long getAddTime() {
        return addTime;
    }

    public String getRequestMsg() {
        return requestMsg;
    }

    public String getHandledMsg() {
        return handledMsg;
    }

    public int getApplicationType() {
        return applicationType;
    }

    public int getHandleStatus() {
        return handleStatus;
    }

    public int getHandleResult() {
        return handleResult;
    }
}
