package com.tencent.imsdk.v2;

import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMMergerElem.html
 */
public class V2TIMMergerElem extends V2TIMElem {
    private boolean layersOverLimit;
    private String title;
    private List<String> abstractList = new ArrayList<>();

    public V2TIMMergerElem(){
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_MERGER);
    }


    private void addAbstract(String item) {
        abstractList.add(item);
    }

    public boolean isLayersOverLimit() {
        return layersOverLimit;
    }

    public String getTitle() {
        return title;
    }

    public List<String> getAbstractList() {
        return abstractList;
    }

    public  void downloadMergerMessage(final V2TIMValueCallback<List<V2TIMMessage>> callback) {
    }

    @Override
    public String toString() {
        return "V2TIMMergerElem{" +
                "layersOverLimit=" + layersOverLimit +
                ", title='" + title + '\'' +
                ", abstractList=" + abstractList +
                '}';
    }
}
