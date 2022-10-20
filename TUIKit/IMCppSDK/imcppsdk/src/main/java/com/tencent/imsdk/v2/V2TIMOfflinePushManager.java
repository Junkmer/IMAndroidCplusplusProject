package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

public abstract class V2TIMOfflinePushManager {

/////////////////////////////////////////////////////////////////////////////////
//                               java层-抽象函数
/////////////////////////////////////////////////////////////////////////////////

    public abstract void setOfflinePushConfig(V2TIMOfflinePushConfig config, V2TIMCallback callback);

    public abstract void doBackground(int unreadCount, V2TIMCallback callback);

    public abstract void doForeground(V2TIMCallback callback);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------  native层-本地接口
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    native void  nativeSetOfflinePushConfig(V2TIMOfflinePushConfig config, IMCallback callback);

    native void  nativeDoBackground(int unreadCount, IMCallback callback);

    native void  nativeDoForeground(IMCallback callback);

}

