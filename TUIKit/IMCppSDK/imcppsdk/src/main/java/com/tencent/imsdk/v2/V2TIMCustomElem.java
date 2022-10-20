package com.tencent.imsdk.v2;

import java.util.Arrays;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMCustomElem.html
 */
public class V2TIMCustomElem extends V2TIMElem {
    private byte[] data;
    private String description;
    private byte[] extension;

    public V2TIMCustomElem(){
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_CUSTOM);
    }


    public byte[] getData() {
        return data;
    }

    public void setData(byte[] data) {
        this.data = data;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public byte[] getExtension() {
        return extension;
    }

    public void setExtension(byte[] extension) {
        this.extension = extension;
    }


    @Override
    public String toString() {
        return "V2TIMCustomElem{" +
                "data=" + Arrays.toString(data) +
                ", description='" + description + '\'' +
                ", extension=" + Arrays.toString(extension) +
                '}';
    }
}
