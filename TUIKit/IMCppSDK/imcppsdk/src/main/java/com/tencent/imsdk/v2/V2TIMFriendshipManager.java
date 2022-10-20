package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.List;

public abstract class V2TIMFriendshipManager {

/////////////////////////////////////////////////////////////////////////////////
//                               java层-抽象函数
/////////////////////////////////////////////////////////////////////////////////

    public abstract void addFriendListener(V2TIMFriendshipListener listener);

    public abstract void removeFriendListener(V2TIMFriendshipListener listener);

    public abstract void getFriendList(V2TIMValueCallback<List<V2TIMFriendInfo>> callback);

    public abstract void getFriendsInfo(List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendInfoResult>> callback);

    public abstract void setFriendInfo(V2TIMFriendInfo info, V2TIMCallback callback);

    public abstract void searchFriends(V2TIMFriendSearchParam searchParam, V2TIMValueCallback<List<V2TIMFriendInfoResult>> callback);

    public abstract void addFriend(V2TIMFriendAddApplication application, V2TIMValueCallback<V2TIMFriendOperationResult> callback);

    public abstract void deleteFromFriendList(List<String> userIDList, int deleteType, V2TIMValueCallback<List<V2TIMFriendOperationResult>> callback);

    public abstract void checkFriend(List<String> userIDList, int checkType, V2TIMValueCallback<List<V2TIMFriendCheckResult>> callback);

    public abstract void getFriendApplicationList(V2TIMValueCallback<V2TIMFriendApplicationResult> callback);

    public abstract void acceptFriendApplication(V2TIMFriendApplication application, int responseType, V2TIMValueCallback<V2TIMFriendOperationResult> callback);

    public abstract void refuseFriendApplication(V2TIMFriendApplication application, V2TIMValueCallback<V2TIMFriendOperationResult> callback);

    public abstract void deleteFriendApplication(V2TIMFriendApplication application, V2TIMCallback callback);

    public abstract void setFriendApplicationRead(V2TIMCallback callback);

    public abstract void addToBlackList(List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> callback);

    public abstract void deleteFromBlackList(List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> callback);

    public abstract void getBlackList(V2TIMValueCallback<List<V2TIMFriendInfo>> callback);

    public abstract void createFriendGroup(String groupName, List<String> userIDList, final V2TIMValueCallback<List<V2TIMFriendOperationResult>> callback);

    public abstract void getFriendGroups(List<String> groupNameList, final V2TIMValueCallback<List<V2TIMFriendGroup>> callback);

    public abstract void deleteFriendGroup(List<String> groupNameList, final V2TIMCallback callback);

    public abstract void renameFriendGroup(String oldName, String newName, V2TIMCallback callback);

    public abstract void addFriendsToFriendGroup(String groupName, List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> callback);

    public abstract void deleteFriendsFromFriendGroup(String groupName, List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> callback);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------  native层-本地接口
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    native void nativeAddFriendListener(V2TIMFriendshipListener listener,String listenerPath);

    native void nativeRemoveFriendListener(String listenerPath);

    native void nativeGetFriendList(IMCallback<List<V2TIMFriendInfo>> callback);

    native void nativeGetFriendsInfo(List<String> userIDList, IMCallback<List<V2TIMFriendInfoResult>> callback);

    native void nativeSetFriendInfo(V2TIMFriendInfo info, IMCallback callback);

    native void nativeSearchFriends(V2TIMFriendSearchParam searchParam, IMCallback<List<V2TIMFriendInfoResult>> callback);

    native void nativeAddFriend(V2TIMFriendAddApplication application, IMCallback<V2TIMFriendOperationResult> callback);

    native void nativeDeleteFromFriendList(List<String> userIDList, int deleteType, IMCallback<List<V2TIMFriendOperationResult>> callback);

    native void nativeCheckFriend(List<String> userIDList, int checkType, IMCallback<List<V2TIMFriendCheckResult>> callback);

    native void nativeGetFriendApplicationList(IMCallback<V2TIMFriendApplicationResult> callback);

    native void nativeAcceptFriendApplication(V2TIMFriendApplication application, int responseType, IMCallback<V2TIMFriendOperationResult> callback);

    native void nativeRefuseFriendApplication(V2TIMFriendApplication application, IMCallback<V2TIMFriendOperationResult> callback);

    native void nativeDeleteFriendApplication(V2TIMFriendApplication application, IMCallback callback);

    native void nativesSetFriendApplicationRead(IMCallback callback);

    native void nativeAddToBlackList(List<String> userIDList, IMCallback<List<V2TIMFriendOperationResult>> callback);

    native void nativeDeleteFromBlackList(List<String> userIDList, IMCallback<List<V2TIMFriendOperationResult>> callback);

    native void nativeGetBlackList(IMCallback<List<V2TIMFriendInfo>> callback);

    native void nativeCreateFriendGroup(String groupName, List<String> userIDList, IMCallback<List<V2TIMFriendOperationResult>> callback);

    native void nativeGetFriendGroups(List<String> groupNameList, IMCallback<List<V2TIMFriendGroup>> callback);

    native void nativeDeleteFriendGroup(List<String> groupNameList, IMCallback callback);

    native void nativeRenameFriendGroup(String oldName, String newName, IMCallback callback);

    native void nativeAddFriendsToFriendGroup(String groupName, List<String> userIDList, IMCallback<List<V2TIMFriendOperationResult>> callback);

    native void nativeDeleteFriendsFromFriendGroup(String groupName, List<String> userIDList, IMCallback<List<V2TIMFriendOperationResult>> callback);

    //--------------------------------------------------  set c++ 层监听
    native void nativeInitCplusplusFriendListener();
}
