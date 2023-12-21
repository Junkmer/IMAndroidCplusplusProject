package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * @Author Junker
 * @ClassName V2TIMMessageExtensionResult
 * @date 2023/10/31 16:13
 * @Version 1.0
 * @Description
 */
public class V2TIMMessageExtensionResult implements Serializable {
    private int resultCode;
    private String resultInfo;
    private V2TIMMessageExtension extension;

    public int getResultCode() {
        return resultCode;
    }

    public String getResultInfo() {
        return resultInfo;
    }

    public V2TIMMessageExtension getExtension() {
        return extension;
    }

    @Override
    public String toString() {
        return "V2TIMMessageExtensionResult{" +
                "resultCode=" + resultCode +
                ", resultInfo='" + resultInfo + '\'' +
                ", extension=" + extension +
                '}';
    }
}
