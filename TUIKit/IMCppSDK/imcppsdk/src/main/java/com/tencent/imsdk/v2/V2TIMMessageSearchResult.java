package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMMessageSearchResult.html
 */
public class V2TIMMessageSearchResult implements Serializable {
    private int totalCount;
    private List<V2TIMMessageSearchResultItem> messageSearchResultItems = new ArrayList<>();

    public int getTotalCount() {
        return totalCount;
    }

    public List<V2TIMMessageSearchResultItem> getMessageSearchResultItems() {
        return messageSearchResultItems;
    }

    private void addMessageSearchResultItem(V2TIMMessageSearchResultItem resultItem){
        this.messageSearchResultItems.add(resultItem);
    }
}
