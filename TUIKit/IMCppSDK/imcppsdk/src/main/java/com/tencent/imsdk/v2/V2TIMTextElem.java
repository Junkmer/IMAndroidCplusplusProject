package com.tencent.imsdk.v2;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMTextElem.html
 */
public class V2TIMTextElem extends V2TIMElem {
    private String 	text;

    public V2TIMTextElem(){
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_TEXT);
    }


    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return "V2TIMTextElem{" +
                "text='" + text + '\'' +
                '}';
    }
}
