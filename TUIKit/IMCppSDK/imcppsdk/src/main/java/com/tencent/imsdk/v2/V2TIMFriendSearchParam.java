package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendSearchParam.html
 */
public class V2TIMFriendSearchParam implements Serializable {
    private List<String> keywordList;
    private boolean isSearchUserID;
    private boolean isSearchNickName;
    private boolean isSearchRemark;

    public void setKeywordList(List<String> keywordList) {
        this.keywordList = keywordList;
    }

    public void setSearchUserID(boolean searchUserID) {
        isSearchUserID = searchUserID;
    }

    public void setSearchNickName(boolean searchNickName) {
        isSearchNickName = searchNickName;
    }

    public void setSearchRemark(boolean searchRemark) {
        isSearchRemark = searchRemark;
    }
}
