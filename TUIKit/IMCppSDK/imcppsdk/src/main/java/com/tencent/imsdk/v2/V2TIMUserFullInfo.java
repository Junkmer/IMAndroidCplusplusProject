package com.tencent.imsdk.v2;

import java.util.HashMap;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMUserFullInfo.html
 */
public class V2TIMUserFullInfo extends V2TIMUserInfo {
     public static final String PROFILE_TYPE_KEY_NICK = "Tag_Profile_IM_Nick";
     public static final String PROFILE_TYPE_KEY_FACEURL = "Tag_Profile_IM_Image";
     public static final String PROFILE_TYPE_KEY_ALLOWTYPE = "Tag_Profile_IM_AllowType";
     public static final String PROFILE_TYPE_KEY_GENDER = "Tag_Profile_IM_Gender";
     public static final String PROFILE_TYPE_KEY_SELF_SIGNATURE = "Tag_Profile_IM_SelfSignature";
     public static final String PROFILE_TYPE_KEY_CUSTOM_PREFIX = "Tag_Profile_Custom_";
    
    public static final int V2TIM_FRIEND_ALLOW_ANY = 0;
    public static final int V2TIM_FRIEND_NEED_CONFIRM = 1;
    public static final int V2TIM_FRIEND_DENY_ANY = 2;
    public static final int V2TIM_GENDER_UNKNOWN = 0;
    public static final int V2TIM_GENDER_MALE = 1;
    public static final int V2TIM_GENDER_FEMALE = 2;

    private String selfSignature;
    private int gender = Integer.MIN_VALUE;
    private int role = Integer.MIN_VALUE;
    private int level = Integer.MIN_VALUE;
    private int allowType = Integer.MIN_VALUE;
    private HashMap<String, byte[]> customHashMap;

    public void setUserID(String userID){
        super.setUserID(userID);
    }

    public void setNickname(String nickname) {
        super.setNickname(nickname);
    }

    public void setFaceUrl(String faceUrl) {
        super.setFaceUrl(faceUrl);
    }

    public String getSelfSignature() {
        return selfSignature;
    }

    public void setSelfSignature(String selfSignature) {
        this.selfSignature = selfSignature;
    }

    public int getGender() {
        return gender;
    }

    public void setGender(int gender) {
        this.gender = gender;
    }

    public int getRole() {
        return role;
    }

    public void setRole(int role) {
        this.role = role;
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public int getAllowType() {
        return allowType;
    }

    public void setAllowType(int allowType) {
        this.allowType = allowType;
    }

    public HashMap<String, byte[]> getCustomHashMap() {
        return customHashMap;
    }

    public void setCustomHashMap(HashMap<String, byte[]> customHashMap) {
        this.customHashMap = customHashMap;
    }

    @Override
    public String toString() {
        return "V2TIMUserFullInfo{" +
                "nickname='" + getNickName() + '\'' +
                ", faceUrl='" + getFaceUrl() + '\'' +
                ", selfSignature='" + selfSignature + '\'' +
                ", gender=" + gender +
                ", role=" + role +
                ", level=" + level +
                ", allowType=" + allowType +
                ", customHashMap=" + customHashMap +
                ", birthday=" + getBirthday() +
                '}';
    }

}
