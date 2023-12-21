package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;
import com.tencent.imsdk.common.IMLog;

import java.util.HashMap;
import java.util.List;

public class V2TIMMessageManagerImpl extends V2TIMMessageManager {
    private static final String TAG = "V2TIMMessageManagerImpl";

    private static class V2TIMMessageManagerImplHolder {
        private static final V2TIMMessageManagerImpl v2TIMMessageManagerImpl = new V2TIMMessageManagerImpl();
    }

    static V2TIMMessageManagerImpl getInstance() {
        return V2TIMMessageManagerImplHolder.v2TIMMessageManagerImpl;
    }

    @Override
    public void addAdvancedMsgListener(V2TIMAdvancedMsgListener listener) {
        nativeAddAdvancedMsgListener(listener,listener.toString());
    }

    @Override
    public void removeAdvancedMsgListener(V2TIMAdvancedMsgListener listener) {
        nativeRemoveAdvancedMsgListener(listener.toString());
    }

    @Override
    public V2TIMMessage createTextMessage(String text) {
        return nativeCreateTextMessage(text);
    }

    @Override
    public V2TIMMessage createTextAtMessage(String text, List<String> atUserList) {
        return nativeCreateTextAtMessage(text, atUserList);
    }

    @Override
    public V2TIMMessage createCustomMessage(byte[] data) {
        return nativeCreateCustomMessage(data);
    }

    @Override
    public V2TIMMessage createCustomMessage(byte[] data, String description, byte[] extension) {
        return nativeCreateCustomMessage(data, description, extension);
    }

    @Override
    public V2TIMMessage createImageMessage(String imagePath) {
        return nativeCreateImageMessage(imagePath);
    }

    @Override
    public V2TIMMessage createSoundMessage(String soundPath, int duration) {
        return nativeCreateSoundMessage(soundPath, duration);
    }

    @Override
    public V2TIMMessage createVideoMessage(String videoFilePath, String type, int duration, String snapshotPath) {
        return nativeCreateVideoMessage(videoFilePath, type, duration, snapshotPath);
    }

    @Override
    public V2TIMMessage createFileMessage(String filePath, String fileName) {
        return nativeCreateFileMessage(filePath, fileName);
    }

    @Override
    public V2TIMMessage createLocationMessage(String desc, double longitude, double latitude) {
        return nativeCreateLocationMessage(desc, longitude, latitude);
    }

    @Override
    public V2TIMMessage createFaceMessage(int index, byte[] data) {
        return nativeCreateFaceMessage(index, data);
    }

    @Override
    public V2TIMMessage createMergerMessage(List<V2TIMMessage> messageList, String title, List<String> abstractList, String compatibleText) {
        return nativeCreateMergerMessage(messageList, title, abstractList, compatibleText);
    }

    @Override
    public V2TIMMessage createForwardMessage(V2TIMMessage message) {
        return nativeCreateForwardMessage(message);
    }

    @Override
    public V2TIMMessage createTargetedGroupMessage(V2TIMMessage message, List<String> receiverList) {
        return nativeCreateTargetedGroupMessage(message, receiverList);
    }

    @Override
    public V2TIMMessage createAtSignedGroupMessage(V2TIMMessage message, List<String> atUserList) {
        if (atUserList == null || atUserList.size() == 0) {
            IMLog.e(TAG, "atUserList invalid, atUserList must is not null and size > 0");
            return null;
        }
        if (message.getElemList().size() == 0) {
            IMLog.e(TAG, "elemList invalid, elemList must have data");
            return null;
        }
        V2TIMMessage newMessage = new V2TIMMessage();
        for (V2TIMElem v2TIMElem : message.getElemList()) {
            newMessage.addElem(v2TIMElem);
        }
        newMessage.setGroupAtUserList(atUserList);
        return message;
    }

    @Override
    public String sendMessage(V2TIMMessage message, String receiver, String groupID, int priority, boolean onlineUserOnly, V2TIMOfflinePushInfo offlinePushInfo, V2TIMSendCallback<V2TIMMessage> _callback_) {
        if (message != null){
            message.setRead(true);
            message.setSelf(true);
            message.setStatus(V2TIMMessage.V2TIM_MSG_STATUS_SENDING);
        }

        return nativeSendMessage(message, receiver, groupID, priority, onlineUserOnly, offlinePushInfo, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void progress(int progress) {
                super.progress(progress);
            }

            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setC2CReceiveMessageOpt(List<String> userIDList, int opt, V2TIMCallback _callback_) {
        nativeSetC2CReceiveMessageOpt(userIDList, opt, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getC2CReceiveMessageOpt(List<String> userIDList, V2TIMValueCallback<List<V2TIMReceiveMessageOptInfo>> _callback_) {
        nativeGetC2CReceiveMessageOpt(userIDList, new IMCallback<List<V2TIMReceiveMessageOptInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMReceiveMessageOptInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setGroupReceiveMessageOpt(String groupID, int opt, V2TIMCallback _callback_) {
        nativeSetGroupReceiveMessageOpt(groupID, opt, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setAllReceiveMessageOpt(int opt, int startHour, int startMinute, int startSecond, long duration, V2TIMCallback _callback_) {
        nativeSetAllReceiveMessageOpt(opt, startHour, startMinute, startSecond, duration, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setAllReceiveMessageOpt(int opt, long startTimeStamp, long duration, V2TIMCallback _callback_) {
        nativeSetAllReceiveMessageOpt(opt, startTimeStamp, duration, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getAllReceiveMessageOpt(V2TIMValueCallback<V2TIMReceiveMessageOptInfo> _callback_) {
        nativeGetAllReceiveMessageOpt(new IMCallback<V2TIMReceiveMessageOptInfo>(_callback_) {
            @Override
            public void success(V2TIMReceiveMessageOptInfo data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getC2CHistoryMessageList(String userID, int count, V2TIMMessage lastMsg, V2TIMValueCallback<List<V2TIMMessage>> _callback_) {
        nativeGetC2CHistoryMessageList(userID, count, lastMsg, new IMCallback<List<V2TIMMessage>>(_callback_) {
            @Override
            public void success(List<V2TIMMessage> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupHistoryMessageList(String groupID, int count, V2TIMMessage lastMsg, V2TIMValueCallback<List<V2TIMMessage>> _callback_) {
        nativeGetGroupHistoryMessageList(groupID, count, lastMsg, new IMCallback<List<V2TIMMessage>>(_callback_) {
            @Override
            public void success(List<V2TIMMessage> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getHistoryMessageList(V2TIMMessageListGetOption option, V2TIMValueCallback<List<V2TIMMessage>> _callback_) {
        nativeGetHistoryMessageList(option, new IMCallback<List<V2TIMMessage>>(_callback_) {
            @Override
            public void success(List<V2TIMMessage> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void revokeMessage(V2TIMMessage msg, V2TIMCallback _callback_) {
        nativeRevokeMessage(msg, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void modifyMessage(V2TIMMessage msg, V2TIMCompleteCallback<V2TIMMessage> _callback_) {
        nativeModifyMessage(msg, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void failOrComplete(int code, String errorMessage, V2TIMMessage data) {
                super.failOrComplete(code, errorMessage, data);
            }
        });
    }

    @Override
    public void markC2CMessageAsRead(String userID, V2TIMCallback _callback_) {
        nativeMarkC2CMessageAsRead(userID, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void markGroupMessageAsRead(String groupID, V2TIMCallback _callback_) {
        nativeMarkGroupMessageAsRead(groupID, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void markAllMessageAsRead(V2TIMCallback _callback_) {
        nativeMarkAllMessageAsRead(new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteMessageFromLocalStorage(V2TIMMessage msg, V2TIMCallback _callback_) {
        nativeDeleteMessageFromLocalStorage(msg, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteMessages(List<V2TIMMessage> messages, V2TIMCallback _callback_) {
        nativeDeleteMessages(messages, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void clearC2CHistoryMessage(String userID, V2TIMCallback _callback_) {
        nativeClearC2CHistoryMessage(userID, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void clearGroupHistoryMessage(String groupID, V2TIMCallback _callback_) {
        nativeClearGroupHistoryMessage(groupID, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public String insertGroupMessageToLocalStorage(V2TIMMessage msg, String groupID, String sender, V2TIMValueCallback<V2TIMMessage> _callback_) {
        return nativeInsertGroupMessageToLocalStorage(msg, groupID, sender, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public String insertC2CMessageToLocalStorage(V2TIMMessage msg, String userID, String sender, V2TIMValueCallback<V2TIMMessage> _callback_) {
        return nativeInsertC2CMessageToLocalStorage(msg, userID, sender, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void findMessages(List<String> messageIDList, V2TIMValueCallback<List<V2TIMMessage>> _callback_) {
        nativeFindMessages(messageIDList, new IMCallback<List<V2TIMMessage>>(_callback_) {
            @Override
            public void success(List<V2TIMMessage> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void searchLocalMessages(V2TIMMessageSearchParam searchParam, V2TIMValueCallback<V2TIMMessageSearchResult> _callback_) {
        nativeSearchLocalMessages(searchParam, new IMCallback<V2TIMMessageSearchResult>(_callback_) {
            @Override
            public void success(V2TIMMessageSearchResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void searchCloudMessages(V2TIMMessageSearchParam searchParam, V2TIMValueCallback<V2TIMMessageSearchResult> _callback_) {
        nativeSearchCloudMessages(searchParam, new IMCallback<V2TIMMessageSearchResult>(_callback_) {
            @Override
            public void success(V2TIMMessageSearchResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void sendMessageReadReceipts(List<V2TIMMessage> messageList, V2TIMCallback _callback_) {
        nativeSendMessageReadReceipts(messageList, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getMessageReadReceipts(List<V2TIMMessage> messageList, V2TIMValueCallback<List<V2TIMMessageReceipt>> _callback_) {
        nativeGetMessageReadReceipts(messageList, new IMCallback<List<V2TIMMessageReceipt>>(_callback_) {
            @Override
            public void success(List<V2TIMMessageReceipt> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupMessageReadMemberList(V2TIMMessage message, int filter, long nextSeq, int count, V2TIMValueCallback<V2TIMGroupMessageReadMemberList> _callback_) {
        nativeGetGroupMessageReadMemberList(message, filter, nextSeq, count, new IMCallback<V2TIMGroupMessageReadMemberList>(_callback_) {
            @Override
            public void success(V2TIMGroupMessageReadMemberList data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setMessageExtensions(V2TIMMessage message, List<V2TIMMessageExtension> extensions, V2TIMValueCallback<List<V2TIMMessageExtensionResult>> _callback_) {
        nativeSetMessageExtensions(message, extensions, new IMCallback<List<V2TIMMessageExtensionResult>>(_callback_) {
            @Override
            public void success(List<V2TIMMessageExtensionResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getMessageExtensions(V2TIMMessage message, V2TIMValueCallback<List<V2TIMMessageExtension>> _callback_) {
        nativeGetMessageExtensions(message, new IMCallback<List<V2TIMMessageExtension>>(_callback_) {
            @Override
            public void success(List<V2TIMMessageExtension> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteMessageExtensions(V2TIMMessage message, List<String> keys, V2TIMValueCallback<List<V2TIMMessageExtensionResult>> _callback_) {
        nativeDeleteMessageExtensions(message, keys, new IMCallback<List<V2TIMMessageExtensionResult>>(_callback_) {
            @Override
            public void success(List<V2TIMMessageExtensionResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void addMessageReaction(V2TIMMessage message, String reactionID, V2TIMCallback _callback_) {
        nativeAddMessageReaction(message, reactionID, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void removeMessageReaction(V2TIMMessage message, String reactionID, V2TIMCallback _callback_) {
        nativeRemoveMessageReaction(message, reactionID, new IMCallback(_callback_) {
            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getMessageReactions(List<V2TIMMessage> messageList, int maxUserCountPerReaction, V2TIMValueCallback<List<V2TIMMessageReactionResult>> _callback_) {
        nativeGetMessageReactions(messageList, maxUserCountPerReaction, new IMCallback<List<V2TIMMessageReactionResult>>(_callback_) {
            @Override
            public void success(List<V2TIMMessageReactionResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getAllUserListOfMessageReaction(V2TIMMessage message, String reactionID, int nextSeq, int count, V2TIMValueCallback<V2TIMMessageReactionUserResult> _callback_) {
        nativeGetAllUserListOfMessageReaction(message, reactionID, nextSeq, count, new IMCallback<V2TIMMessageReactionUserResult>(_callback_) {
            @Override
            public void success(V2TIMMessageReactionUserResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void translateText(List<String> sourceTextList, String sourceLanguage, String targetLanguage, V2TIMValueCallback<HashMap<String, String>> _callback_) {
        nativeTranslateText(sourceTextList, sourceLanguage, targetLanguage, new IMCallback<HashMap<String, String>>(_callback_) {
            @Override
            public void success(HashMap<String, String> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }
}
