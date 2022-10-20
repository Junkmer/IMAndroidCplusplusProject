package com.tencent.imsdk.v2;

import java.util.Arrays;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFaceElem.html
 */
public class V2TIMFaceElem extends V2TIMElem {
    private int index;
    private byte[] data;

    public V2TIMFaceElem(){
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_FACE);
    }


    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public byte[] getData() {
        return data;
    }

    public void setData(byte[] data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "V2TIMFaceElem{" +
                "index=" + index +
                ", data=" + Arrays.toString(data) +
                '}';
    }
}
