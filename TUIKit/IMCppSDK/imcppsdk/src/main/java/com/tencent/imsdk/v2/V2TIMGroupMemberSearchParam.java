package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupMemberSearchParam.html
 */
public class V2TIMGroupMemberSearchParam implements Serializable {
    private List<String> groupIDList = new ArrayList<>();
    private List<String> keywordList = new ArrayList<>();
    private boolean isSearchMemberUserID;
    private boolean isSearchMemberNickName;
    private boolean isSearchMemberRemark;
    private boolean isSearchMemberNameCard;

    public void setGroupIDList(List<String> groupIDList) {
        this.groupIDList = groupIDList;
    }

    public void setKeywordList(List<String> keywordList) {
        this.keywordList = keywordList;
    }

    public void setSearchMemberUserID(boolean searchMemberUserID) {
        isSearchMemberUserID = searchMemberUserID;
    }

    public void setSearchMemberNickName(boolean searchMemberNickName) {
        isSearchMemberNickName = searchMemberNickName;
    }

    public void setSearchMemberRemark(boolean searchMemberRemark) {
        isSearchMemberRemark = searchMemberRemark;
    }

    public void setSearchMemberNameCard(boolean searchMemberNameCard) {
        isSearchMemberNameCard = searchMemberNameCard;
    }
}
