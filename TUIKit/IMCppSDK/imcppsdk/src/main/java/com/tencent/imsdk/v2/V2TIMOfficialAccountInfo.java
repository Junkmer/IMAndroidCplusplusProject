package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * @Author Junker
 * @ClassName V2TIMOfficialAccountInfo
 * @date 2024/1/12 16:44
 * @Version 1.0
 * @Description
 */
public class V2TIMOfficialAccountInfo implements Serializable {
    private String officialAccountID;
    private String officialAccountName;
    private String faceUrl;
    private String ownerUserID;
    private String organization;
    private String introduction;
    private String customData;
    private long createTime;
    private long subscriberCount;
    private long subscribeTime;

    public String getOfficialAccountID() {
        return officialAccountID;
    }

    public String getOfficialAccountName() {
        return officialAccountName;
    }

    public String getFaceUrl() {
        return faceUrl;
    }

    public String getOwnerUserID() {
        return ownerUserID;
    }

    public String getOrganization() {
        return organization;
    }

    public String getIntroduction() {
        return introduction;
    }

    public String getCustomData() {
        return customData;
    }

    public long getCreateTime() {
        return createTime;
    }

    public long getSubscriberCount() {
        return subscriberCount;
    }

    public long getSubscribeTime() {
        return subscribeTime;
    }

    @Override
    public String toString() {
        return "V2TIMOfficialAccountInfo{" +
                "officialAccountID='" + officialAccountID + '\'' +
                ", officialAccountName='" + officialAccountName + '\'' +
                ", faceUrl='" + faceUrl + '\'' +
                ", ownerUserID='" + ownerUserID + '\'' +
                ", organization='" + organization + '\'' +
                ", introduction='" + introduction + '\'' +
                ", customData='" + customData + '\'' +
                ", createTime=" + createTime +
                ", subscriberCount=" + subscriberCount +
                ", subscribeTime=" + subscribeTime +
                '}';
    }
}
