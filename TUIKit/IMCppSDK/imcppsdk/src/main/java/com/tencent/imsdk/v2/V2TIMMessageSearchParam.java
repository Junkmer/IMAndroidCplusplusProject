package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMMessageSearchParam.html
 */
public class V2TIMMessageSearchParam implements Serializable {
    public static final int V2TIM_KEYWORD_LIST_MATCH_TYPE_OR = 0;
    public static final int V2TIM_KEYWORD_LIST_MATCH_TYPE_AND = 1;

    private String conversationID;
    private List<String> keywordList;
    private int keywordListMatchType;
    private List<String> senderUserIDList;
    private List<Integer> messageTypeList;
    private long searchTimePosition;
    private long searchTimePeriod;
    private int pageSize;
    private int pageIndex;
    private int searchCount;
    private String searchCursor;

    public void setConversationID(String conversationID) {
        this.conversationID = conversationID;
    }

    public void setKeywordList(List<String> keywordList) {
        this.keywordList = keywordList;
    }

    public void setKeywordListMatchType(int keywordListMatchType) {
        this.keywordListMatchType = keywordListMatchType;
    }

    public void setSenderUserIDList(List<String> senderUserIDList) {
        this.senderUserIDList = senderUserIDList;
    }

    public void setMessageTypeList(List<Integer> messageTypeList) {
        this.messageTypeList = messageTypeList;
    }

    public void setSearchTimePosition(long searchTimePosition) {
        this.searchTimePosition = searchTimePosition;
    }

    public void setSearchTimePeriod(long searchTimePeriod) {
        this.searchTimePeriod = searchTimePeriod;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }

    public void setPageIndex(int pageIndex) {
        this.pageIndex = pageIndex;
    }

    public void setSearchCount(int searchCount) {
        this.searchCount = searchCount;
    }

    public void setSearchCursor(String searchCursor) {
        this.searchCursor = searchCursor;
    }

    public List<String> getKeywordList() {
        return keywordList;
    }

    public List<Integer> getMessageTypeList() {
        return messageTypeList;
    }

    public long getSearchTimePosition() {
        return searchTimePosition;
    }

    public long getSearchTimePeriod() {
        return searchTimePeriod;
    }

    public int getPageSize() {
        return pageSize;
    }

    public int getPageIndex() {
        return pageIndex;
    }
}
