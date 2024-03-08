package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.List;

public abstract class V2TIMSignalingManager {

/////////////////////////////////////////////////////////////////////////////////
//                               java层-抽象函数
/////////////////////////////////////////////////////////////////////////////////

    public abstract void addSignalingListener(V2TIMSignalingListener listener);

    public abstract void removeSignalingListener(V2TIMSignalingListener listener);

    public abstract String invite(String invitee, String data, boolean onlineUserOnly, V2TIMOfflinePushInfo offlinePushInfo, int timeout, V2TIMCallback callback);

    public abstract String inviteInGroup(String groupID, List<String> inviteeList, String data, boolean onlineUserOnly, int timeout, V2TIMCallback callback);

    public abstract void cancel(String inviteID, String data, V2TIMCallback callback);

    public abstract void accept(String inviteID, String data, V2TIMCallback callback);

    public abstract void reject(String inviteID, String data, V2TIMCallback callback);

    public abstract V2TIMSignalingInfo getSignalingInfo(V2TIMMessage msg);

    public abstract void addInvitedSignaling(final V2TIMSignalingInfo info, final V2TIMCallback callback);

    public abstract void modifyInvitation(String inviteID, String data, V2TIMCallback callback);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------  native层-本地接口
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    native void nativeAddSignalingListener(V2TIMSignalingListener listener,String listenerPath);

    native void nativeRemoveSignalingListener(String listenerPath);

    native String nativeInvite(String invitee, String data, boolean onlineUserOnly, V2TIMOfflinePushInfo offlinePushInfo, int timeout, IMCallback callback);

    native String nativeInviteInGroup(String groupID, List<String> inviteeList, String data, boolean onlineUserOnly, int timeout, IMCallback callback);

    native void nativeCancel(String inviteID, String data, IMCallback callback);

    native void nativeAccept(String inviteID, String data, IMCallback callback);

    native void nativeReject(String inviteID, String data, IMCallback callback);

    native V2TIMSignalingInfo nativeGetSignalingInfo(V2TIMMessage msg);

    native void nativeAddInvitedSignaling(final V2TIMSignalingInfo info, final IMCallback callback);

    native void nativeModifyInvitation(String inviteID, String data, IMCallback callback);

    //--------------------------------------------------  set c++ 层监听
    native void nativeInitCplusplusSignalingListener();

}
