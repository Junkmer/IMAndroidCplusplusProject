package com.tencent.imsdk.v2;

import android.content.Context;
import android.util.Log;

import com.tencent.imsdk.common.IMCallback;
import com.tencent.imsdk.common.SystemUtil;

import java.util.List;

public abstract class V2TIMManager {
    private static final String TAG = V2TIMManager.class.getSimpleName();

    public static boolean mLoadLibrarySuccess = false;
    public boolean isInit = false;

    public static final int V2TIM_STATUS_LOGINED = 1;
    public static final int V2TIM_STATUS_LOGINING = 2;
    public static final int V2TIM_STATUS_LOGOUT = 3;
    public static final String GROUP_TYPE_WORK = "Work";
    public static final String GROUP_TYPE_PUBLIC = "Public";
    public static final String GROUP_TYPE_MEETING = "Meeting";
    public static final String GROUP_TYPE_AVCHATROOM = "AVChatRoom";
    public static final String GROUP_TYPE_COMMUNITY = "Community";

    //加载so库
    static {
        try {
            mLoadLibrarySuccess = SystemUtil.loadIMLibrary();
        } catch (Exception e) {
            Log.e(TAG, e.toString());
        }
    }

/////////////////////////////////////////////////////////////////////////////////
//                               java层-抽象函数
/////////////////////////////////////////////////////////////////////////////////

    /**
     * 获取 V2TIMManager 管理器实例
     */
    public static V2TIMManager getInstance() {
        return V2TIMManagerImpl.getInstance();
    }

    public abstract boolean initSDK(Context context, int sdkAppID, V2TIMSDKConfig config);

    public abstract void unInitSDK();

    public abstract void addIMSDKListener(V2TIMSDKListener listener);

    public abstract void removeIMSDKListener(V2TIMSDKListener listener);

    public abstract String getVersion();

    public abstract long getServerTime();

    public abstract void login(String userID, String userSig, V2TIMCallback callback);

    public abstract void logout(V2TIMCallback callback);

    public abstract String getLoginUser();

    public abstract int getLoginStatus();

    public abstract void addSimpleMsgListener(V2TIMSimpleMsgListener v2TIMSimpleMsgListener);

    public abstract void removeSimpleMsgListener(V2TIMSimpleMsgListener v2TIMSimpleMsgListener);

    public abstract String sendC2CTextMessage(String text, String userID, V2TIMValueCallback<V2TIMMessage> callback);

    public abstract String sendC2CCustomMessage(byte[] customData, String userID, V2TIMValueCallback<V2TIMMessage> callback);

    public abstract String sendGroupTextMessage(String text, String groupID, int priority, V2TIMValueCallback<V2TIMMessage> callback);

    public abstract String sendGroupCustomMessage(byte[] customData, String groupID, int priority, V2TIMValueCallback<V2TIMMessage> callback);

    public abstract void addGroupListener(V2TIMGroupListener listener);

    public abstract void removeGroupListener(V2TIMGroupListener listener);

    public abstract void createGroup(String groupType, String groupID, String groupName, V2TIMValueCallback<String> callback);

    public abstract void joinGroup(String groupID, String message, V2TIMCallback callback);

    public abstract void quitGroup(String groupID, final V2TIMCallback callback);

    public abstract void dismissGroup(String groupID, final V2TIMCallback callback);

    public abstract void getUsersInfo(List<String> userIDList, V2TIMValueCallback<List<V2TIMUserFullInfo>> callback);

    public abstract void setSelfInfo(V2TIMUserFullInfo info, V2TIMCallback callback);

    public abstract void getUserStatus(List<String> userIDList, V2TIMValueCallback<List<V2TIMUserStatus>> callback);

    public abstract void setSelfStatus(V2TIMUserStatus status, V2TIMCallback callback);

    public abstract void subscribeUserStatus(List<String> userIDList, V2TIMCallback callback);

    public abstract void unsubscribeUserStatus(List<String> userIDList, V2TIMCallback callback);

    public abstract void callExperimentalAPI(String api, Object param, V2TIMValueCallback<Object> callback);

/////////////////////////////////////////////////////////////////////////////////
//                        高级接口功能入口
/////////////////////////////////////////////////////////////////////////////////

    public static V2TIMMessageManager getMessageManager() {
        return V2TIMMessageManagerImpl.getInstance();
    }

    public static V2TIMGroupManager getGroupManager() {
        return V2TIMGroupManagerImpl.getInstance();
    }

    public static V2TIMConversationManager getConversationManager() {
        return V2TIMConversationManagerImpl.getInstance();
    }

    public static V2TIMFriendshipManager getFriendshipManager() {
        return V2TIMFriendshipManagerImpl.getInstance();
    }

    public static V2TIMOfflinePushManager getOfflinePushManager() {
        return V2TIMOfflinePushManagerImpl.getInstance();
    }

    public static V2TIMSignalingManager getSignalingManager() {
        return V2TIMSignalingManagerImpl.getInstance();
    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------  native层-本地接口
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    native void nativeAddSDKListener(V2TIMSDKListener listener,String listenerPath);

    native void nativeRemoveSDKListener(String listenerPath);

    public native boolean nativeInitSDK(int sdkAppID, V2TIMSDKConfig sdkConfig);

    native void nativeUninitSDK();

    native void nativeLogin(String userID, String userSig, IMCallback callback);

    public native String nativeGetVersion();

    public native long nativeGetServerTime();

    native void nativeLogout(IMCallback callback);

    public native String nativeGetLoginUser();

    public native int nativeGetLoginStatus();

    native void nativeAddSimpleMsgListener(V2TIMSimpleMsgListener v2TIMSimpleMsgListener,String listenerPath);

    native void nativeRemoveSimpleMsgListener(String listenerPath);

    public native String nativeSendC2CTextMessage(String text, String userID, IMCallback<V2TIMMessage> callback);

    public native String nativeSendC2CCustomMessage(byte[] customData, String userID, IMCallback<V2TIMMessage> callback);

    public native String nativeSendGroupTextMessage(String text, String groupID, int priority, IMCallback<V2TIMMessage> callback);

    public native String nativeSendGroupCustomMessage(byte[] customData, String groupID, int priority, IMCallback<V2TIMMessage> callback);

    native void nativeAddGroupListener(V2TIMGroupListener listener,String listenerPath);

    native void nativeRemoveGroupListener(String listenerPath);

    native void nativeCreateGroup(String groupType, String groupID, String groupName, IMCallback<String> callback);

    native void nativeJoinGroup(String groupID, String message, IMCallback callback);

    native void nativeQuitGroup(String groupID, final IMCallback callback);

    native void nativeDismissGroup(String groupID, final IMCallback callback);

    native void nativeGetUsersInfo(List<String> userIDList, IMCallback<List<V2TIMUserFullInfo>> callback);

    native void nativeSetSelfInfo(V2TIMUserFullInfo info, IMCallback callback);

    native void nativeGetUserStatus(List<String> userIDList, IMCallback<List<V2TIMUserStatus>> callback);

    native void nativeSetSelfStatus(V2TIMUserStatus status, IMCallback callback);

    native void nativeSubscribeUserStatus(List<String> userIDList, IMCallback callback);

    native void nativeUnsubscribeUserStatus(List<String> userIDList, IMCallback callback);

    native void nativeCallExperimentalAPI(String api, Object param, IMCallback<Object> callback);

//--------------------------------------------------  set c++ 层监听
    protected native void nativeInitCplusplusSDKListener();
    protected native void nativeInitCplusplusSimpleMsgListener();
    protected native void nativeInitCplusplusGroupListener();
}
