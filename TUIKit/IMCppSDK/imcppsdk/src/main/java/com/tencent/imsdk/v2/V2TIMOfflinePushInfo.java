package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMOfflinePushInfo.html
 */
public class V2TIMOfflinePushInfo implements Serializable {
    public static final String IOS_OFFLINE_PUSH_NO_SOUND = "push.no_sound";
    public static final String IOS_OFFLINE_PUSH_DEFAULT_SOUND = "default";

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
    private String androidOPPOChannelID;
    private int androidVIVOClassification;

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

    public void setDisable(boolean disable) {
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

    public void setAndroidOPPOChannelID(String androidOPPOChannelID) {
        this.androidOPPOChannelID = androidOPPOChannelID;
    }

    public void setAndroidVIVOClassification(int androidVIVOClassification) {
        this.androidVIVOClassification = androidVIVOClassification;
    }
}
