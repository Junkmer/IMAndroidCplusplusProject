package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.List;

public abstract class V2TIMConversationManager {

/////////////////////////////////////////////////////////////////////////////////
//                               java层-抽象函数
/////////////////////////////////////////////////////////////////////////////////

    public abstract void addConversationListener(V2TIMConversationListener listener);

    public abstract void removeConversationListener(V2TIMConversationListener listener);

    public abstract void getConversationList(long nextSeq, int count, V2TIMValueCallback<V2TIMConversationResult> callback);

    public abstract void getConversation(String conversationID, V2TIMValueCallback<V2TIMConversation> callback);

    public abstract void getConversationList(List<String> conversationIDList, V2TIMValueCallback<List<V2TIMConversation>> callback);

    public abstract void getConversationListByFilter(V2TIMConversationListFilter filter, V2TIMValueCallback<V2TIMConversationResult> callback);

    public abstract void deleteConversation(String conversationID, V2TIMCallback callback);

    public abstract void setConversationDraft(String conversationID, String draftText, V2TIMCallback callback);

    public abstract void setConversationCustomData(List<String> conversationIDList, String customData, V2TIMValueCallback<List<V2TIMConversationOperationResult>> callback);

    public abstract void pinConversation(String conversationID, boolean isPinned, V2TIMCallback callback);

    public abstract void markConversation(List<String> conversationIDList, long markType, boolean enableMark, V2TIMValueCallback<List<V2TIMConversationOperationResult>> callback);

    public abstract void getTotalUnreadMessageCount(V2TIMValueCallback<Long> callback);

    public abstract void createConversationGroup(String groupName, List<String> conversationIDList, V2TIMValueCallback<List<V2TIMConversationOperationResult>> callback);

    public abstract void getConversationGroupList(V2TIMValueCallback<List<String>> callback);

    public abstract void deleteConversationGroup(String groupName, V2TIMCallback callback);

    public abstract void renameConversationGroup(String oldName, String newName, V2TIMCallback callback);

    public abstract void addConversationsToGroup(String groupName, List<String> conversationIDList, V2TIMValueCallback<List<V2TIMConversationOperationResult>> callback);

    public abstract void deleteConversationsFromGroup(String groupName, List<String> conversationIDList, V2TIMValueCallback<List<V2TIMConversationOperationResult>> callback);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------  native层-本地接口
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    native void nativeAddConversationListener(V2TIMConversationListener listener,String listenerPath);

    native void nativeRemoveConversationListener(String listenerPath);

    native void nativeGetConversationList(long nextSeq, int count, IMCallback<V2TIMConversationResult> callback);

    native void nativeGetConversation(String conversationID, IMCallback<V2TIMConversation> callback);

    native void nativeGetConversationList(List<String> conversationIDList, IMCallback<List<V2TIMConversation>> callback);

    native void nativeGetConversationListByFilter(V2TIMConversationListFilter filter, IMCallback<V2TIMConversationResult> callback);

    native void nativeDeleteConversation(String conversationID, IMCallback callback);

    native void nativeSetConversationDraft(String conversationID, String draftText, IMCallback callback);

    native void nativeSetConversationCustomData(List<String> conversationIDList, String customData, IMCallback<List<V2TIMConversationOperationResult>> callback);

    native void nativePinConversation(String conversationID, boolean isPinned, IMCallback callback);

    native void nativeMarkConversation(List<String> conversationIDList, long markType, boolean enableMark, IMCallback<List<V2TIMConversationOperationResult>> callback);

    native void nativeGetTotalUnreadMessageCount(IMCallback<Long> callback);

    native void nativeCreateConversationGroup(String groupName, List<String> conversationIDList, IMCallback<List<V2TIMConversationOperationResult>> callback);

    native void nativeGetConversationGroupList(IMCallback<List<String>> callback);

    native void nativeDeleteConversationGroup(String groupName, IMCallback callback);

    native void nativeRenameConversationGroup(String oldName, String newName, IMCallback callback);

    native void nativeAddConversationsToGroup(String groupName, List<String> conversationIDList, IMCallback<List<V2TIMConversationOperationResult>> callback);

    native void nativeDeleteConversationsFromGroup(String groupName, List<String> conversationIDList, IMCallback<List<V2TIMConversationOperationResult>> callback);

    //--------------------------------------------------  set c++ 层监听
    native void nativeInitCplusplusConversationListener();

}
