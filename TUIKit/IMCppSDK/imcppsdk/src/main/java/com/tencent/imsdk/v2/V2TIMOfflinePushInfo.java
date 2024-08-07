package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMOfflinePushInfo.html
 */
public class V2TIMOfflinePushInfo implements Serializable {
    public static final String IOS_OFFLINE_PUSH_NO_SOUND = "push.no_sound";
    public static final String IOS_OFFLINE_PUSH_DEFAULT_SOUND = "default";
    public static final int IOS_OFFLINE_PUSH_TYPE_APNS = 0;
    public static final int IOS_OFFLINE_PUSH_TYPE_VOIP = 1;

    public static final int OFFLINE_PUSH_FLAG_DEFAULT = 0;
    public static final int OFFLINE_PUSH_FLAG_NO_PUSH = 1;

    public static final int OFFLINE_APNS_BADGE_MODE_DEFAULT = 0;
    public static final int OFFLINE_APNS_BADGE_MODE_IGNORE  = 1;

    private String title;
    private String desc;
    private byte[] ext;
    private boolean disable;
    private String IOSSound;
    private String androidSound;
    private boolean ignoreIOSBadge;
    private String oppoChannelID;
    private String fcmChannelID;
    private String xiaomiChannelID;
    private int vivoClassification = 1;
    private String vivoCategory;
    private int iOSPushType = 0;
    private String huaweiCategory;

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public byte[] getExt() {
        return ext;
    }

    public void setExt(byte[] ext) {
        this.ext = ext;
    }

    public boolean isDisable() {
        return disable;
    }

    public void disablePush(boolean disable) {
        this.disable = disable;
    }

    public void setIOSSound(String IOSSound) {
        this.IOSSound = IOSSound;
    }

    public void setAndroidSound(String androidSound) {
        this.androidSound = androidSound;
    }

    public void setIgnoreIOSBadge(boolean ignoreIOSBadge) {
        this.ignoreIOSBadge = ignoreIOSBadge;
    }

    public void setAndroidOPPOChannelID(String channelID) {
        this.oppoChannelID = channelID;
    }

    public void setAndroidFCMChannelID(String channelID) {
        this.fcmChannelID = channelID;
    }

    public void setAndroidXiaoMiChannelID(String channelID) {
        this.xiaomiChannelID = channelID;
    }

    /** @deprecated */
    @Deprecated
    public void setAndroidVIVOClassification(int classification) {
        this.vivoClassification = classification;
    }

    public void setAndroidVIVOCategory(String category) {
        this.vivoCategory = category;
    }

    public void setIOSPushType(int iosPushType) {
        this.iOSPushType = iosPushType;
    }

    public void setAndroidHuaWeiCategory(String category) {
        this.huaweiCategory = category;
    }
}