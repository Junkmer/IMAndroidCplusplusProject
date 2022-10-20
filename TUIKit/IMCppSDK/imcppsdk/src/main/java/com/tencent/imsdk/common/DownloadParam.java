package com.tencent.imsdk.common;

import java.io.Serializable;

/**
 * 该类仅用于下载媒体消息文件
 */
public class DownloadParam implements Serializable {
    protected String roleTypeID;//群消息就是 groupID，C2C消息就是对方的 userID
    protected String messageID;
    protected long sequence;
    protected int elemType;
}