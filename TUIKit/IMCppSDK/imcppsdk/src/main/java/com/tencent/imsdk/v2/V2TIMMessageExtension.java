package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * @Author Junker
 * @ClassName V2TIMMessageExtension
 * @date 2023/10/31 16:11
 * @Version 1.0
 * @Description TODO
 */
public class V2TIMMessageExtension implements Serializable {
    private String extensionKey;
    private String extensionValue;

    public String getExtensionKey() {
        return extensionKey;
    }

    public void setExtensionKey(String extensionKey) {
        this.extensionKey = extensionKey;
    }

    public String getExtensionValue() {
        return extensionValue;
    }

    public void setExtensionValue(String extensionValue) {
        this.extensionValue = extensionValue;
    }

    @Override
    public String toString() {
        return "V2TIMMessageExtension{" +
                "extensionKey='" + extensionKey + '\'' +
                ", extensionValue='" + extensionValue + '\'' +
                '}';
    }
}
