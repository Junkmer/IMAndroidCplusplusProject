//
// Created by EDY on 2022/8/22.
//

#include <jni.h>
#include "jni_util.h"
#include "java_basic_jni.h"
#include "v2_im_engine.h"
#include "jni_helper.h"
#include "advanced_msg_listener_jni.h"
#include "callback_impl.h"
#include "value_callback_impl.h"
#include "V2TIMErrorCode.h"
#include "im_callbak_jni.h"
#include "message_jni.h"
#include "offline_push_info_jni.h"
#include "send_callback_impl.h"
#include "receive_message_opt_info_jni.h"
#include "group_message_read_member_list_jni.h"
#include "message_list_get_option_jni.h"
#include "message_search_result_item_jni.h"
#include "message_search_result_jni.h"
#include "message_search_param_jni.h"
#include "message_receipt_jni.h"
#include "complete_callback_impl.h"
#include "message_extension_jni.h"
#include "message_extension_result_jni.h"
#include "message_reaction_jni.h"
#include "message_reaction_result_jni.h"
#include "message_reaction_user_result_jni.h"
#include "LogUtil.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<v2im::jni::AdvancedMsgListenerJni> advance_listener_jni;

DEFINE_NATIVE_FUNC(void, nativeInitCplusplusAdvancedMsgListener) {
    if (!advance_listener_jni) {
        advance_listener_jni = std::make_shared<v2im::jni::AdvancedMsgListenerJni>();
    }
    advance_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeAddAdvancedMsgListener, jobject listener, jstring listenerPath) {
    if (!advance_listener_jni) {
        advance_listener_jni = std::make_shared<v2im::jni::AdvancedMsgListenerJni>();
    }

    advance_listener_jni->AddListener(env, listener, listenerPath);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveAdvancedMsgListener, jstring listenerPath) {
    if (advance_listener_jni) {
        advance_listener_jni->RemoveListener(env, listenerPath);
    }
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateTextMessage, jstring text) {
    V2TIMString textStr = v2im::jni::StringJni::Jstring2Cstring(env, text).c_str();
    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateTextMessage(textStr);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateTextAtMessage, jstring text, jobject at_user_list) {
    V2TIMString textStr = v2im::jni::StringJni::Jstring2Cstring(env, text).c_str();

    V2TIMStringVector atUserIDList;
    int size = v2im::jni::ArrayListJni::Size(at_user_list);
    for (int i = 0; i < size; ++i) {
        V2TIMString groupID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(at_user_list, i)).c_str();
        atUserIDList.PushBack(groupID);
    }

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateTextAtMessage(textStr, atUserIDList);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateCustomMessage, jbyteArray data) {
    V2TIMBuffer dataBuffer = v2im::jni::ByteJni::JByteArray2V2TIMBuffer(env, data);

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateCustomMessage(dataBuffer);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateCustomMessageForParame, jbyteArray data, jstring description, jbyteArray extension) {
    V2TIMBuffer dataBuffer = v2im::jni::ByteJni::JByteArray2V2TIMBuffer(env, data);
    V2TIMString descStr = v2im::jni::StringJni::Jstring2Cstring(env, description).c_str();
    V2TIMString extStr = v2im::jni::StringJni::JbyteArray2Cstring(env, extension).c_str();

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateCustomMessage(dataBuffer, descStr, extStr);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateImageMessage, jstring image_path) {
    V2TIMString imagePathStr = v2im::jni::StringJni::Jstring2Cstring(env, image_path).c_str();
    LOGE("create before Image path = %s", imagePathStr.CString());

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateImageMessage(imagePathStr);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateSoundMessage, jstring sound_path, jint duration) {
    V2TIMString soundPathStr = v2im::jni::StringJni::Jstring2Cstring(env, sound_path).c_str();

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateSoundMessage(soundPathStr, (uint32_t) duration);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateVideoMessage, jstring video_file_path, jstring type, jint duration, jstring snapshot_path) {
    V2TIMString videoFilePathStr = v2im::jni::StringJni::Jstring2Cstring(env, video_file_path).c_str();
    V2TIMString typeStr = v2im::jni::StringJni::Jstring2Cstring(env, video_file_path).c_str();
    V2TIMString snapshotPathStr = v2im::jni::StringJni::Jstring2Cstring(env, snapshot_path).c_str();

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateVideoMessage(videoFilePathStr, typeStr, (uint32_t) duration, snapshotPathStr);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateFileMessage, jstring file_path, jstring file_name) {
    V2TIMString filePathStr = v2im::jni::StringJni::Jstring2Cstring(env, file_path).c_str();
    V2TIMString fileNameStr = v2im::jni::StringJni::Jstring2Cstring(env, file_name).c_str();

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateFileMessage(filePathStr, fileNameStr);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateLocationMessage, jstring desc, jdouble longitude, jdouble latitude) {
    V2TIMString descStr = v2im::jni::StringJni::Jstring2Cstring(env, desc).c_str();

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateLocationMessage(descStr, longitude, latitude);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateFaceMessage, jint index, jbyteArray data) {
    V2TIMBuffer dataBuffer = v2im::jni::ByteJni::JByteArray2V2TIMBuffer(env, data);

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateFaceMessage((uint32_t) index, dataBuffer);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateMergerMessage, jobject message_list, jstring title, jobject abstract_list, jstring compatible_text) {
    V2TIMMessageVector messageVector;
    int size;
    size = v2im::jni::ArrayListJni::Size(message_list);
    for (int i = 0; i < size; ++i) {
        jobject messageObj = v2im::jni::ArrayListJni::Get(message_list, i);
        V2TIMMessage timMessage;
        if (v2im::jni::MessageJni::Convert2CoreObject(messageObj,timMessage)){
            messageVector.PushBack(timMessage);
        }
        env->DeleteLocalRef(messageObj);
    }

    V2TIMString titleStr = v2im::jni::StringJni::Jstring2Cstring(env, title).c_str();

    V2TIMStringVector stringVector;
    size = v2im::jni::ArrayListJni::Size(abstract_list);
    for (int i = 0; i < size; ++i) {
        auto abstractJStr = (jstring) v2im::jni::ArrayListJni::Get(abstract_list, i);
        V2TIMString abstract = v2im::jni::StringJni::Jstring2Cstring(env, abstractJStr).c_str();
        stringVector.PushBack(abstract);
        env->DeleteLocalRef(abstractJStr);
    }

    V2TIMString compatibleTextStr = v2im::jni::StringJni::Jstring2Cstring(env, compatible_text).c_str();

    V2TIMMessage message = v2im::V2IMEngine::GetInstance()->CreateMergerMessage(messageVector, titleStr, stringVector, compatibleTextStr);
    return v2im::jni::MessageJni::Convert2JObject(message);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateForwardMessage, jobject message) {
    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(message,message_c);
    V2TIMMessage messageObj = v2im::V2IMEngine::GetInstance()->CreateForwardMessage(message_c);
    return v2im::jni::MessageJni::Convert2JObject(messageObj);
}

DEFINE_NATIVE_FUNC(jobject, NativeCreateTargetedGroupMessage, jobject message, jobject receiver_list) {
    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(message,message_c);

    V2TIMStringVector stringVector;
    int size = v2im::jni::ArrayListJni::Size(receiver_list);
    for (int i = 0; i < size; ++i) {
        auto receiverJStr = (jstring) v2im::jni::ArrayListJni::Get(receiver_list, i);
        V2TIMString receiver = v2im::jni::StringJni::Jstring2Cstring(env, receiverJStr).c_str();
        stringVector.PushBack(receiver);
        env->DeleteLocalRef(receiverJStr);
    }

    V2TIMMessage messageObj = v2im::V2IMEngine::GetInstance()->CreateTargetedGroupMessage(message_c, stringVector);
    return v2im::jni::MessageJni::Convert2JObject(messageObj);
}

DEFINE_NATIVE_FUNC(jstring, NativeSendMessage, jobject message, jstring receiver, jstring group_id, jint priority, jboolean online_user_only,
                   jobject offline_push_info, jobject callback) {

    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(message,message_c);
    V2TIMString receiverStr = v2im::jni::StringJni::Jstring2Cstring(env, receiver).c_str();
    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    auto messagePriority = V2TIMMessagePriority(priority);
    V2TIMOfflinePushInfo offlinePushInfo;
    if (offline_push_info) {
        v2im::jni::OfflinePushInfoJni::Convert2CoreObject(offline_push_info, offlinePushInfo);
    }

    bool isRetry = message_c.status == V2TIMMessageStatus::V2TIM_MSG_STATUS_SEND_FAIL;

    V2TIMString msgIDStr = v2im::V2IMEngine::GetInstance()->SendMessage(message_c, receiverStr, groupIDStr, messagePriority, online_user_only,
                                                                        offlinePushInfo, new v2im::SendCallbackImpl(message,callback));

    v2im::jni::MessageJni::UpdateJMessageStatus(message,message_c,isRetry);

    return v2im::jni::StringJni::Cstring2Jstring(env, msgIDStr.CString());
}

DEFINE_NATIVE_FUNC(void, NativeSetC2CReceiveMessageOpt, jobject user_idlist, jint opt, jobject callback) {
    V2TIMStringVector stringVector;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto abstractJStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        V2TIMString abstract = v2im::jni::StringJni::Jstring2Cstring(env, abstractJStr).c_str();
        stringVector.PushBack(abstract);
        env->DeleteLocalRef(abstractJStr);
    }

    auto messageOpt = V2TIMReceiveMessageOpt(opt);

    v2im::V2IMEngine::GetInstance()->SetC2CReceiveMessageOpt(stringVector, messageOpt, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetC2CReceiveMessageOpt, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector stringVector;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto abstractJStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        V2TIMString abstract = v2im::jni::StringJni::Jstring2Cstring(env, abstractJStr).c_str();
        stringVector.PushBack(abstract);
        env->DeleteLocalRef(abstractJStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMReceiveMessageOptInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMReceiveMessageOptInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject optInfoObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject optInfoObj = v2im::jni::ReceiveMessageOptInfoJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(optInfoObjList, optInfoObj);
                _env->DeleteLocalRef(optInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, optInfoObjList);
            _env->DeleteLocalRef(optInfoObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetC2CReceiveMessageOpt(stringVector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetGroupReceiveMessageOpt, jstring group_id, jint opt, jobject callback) {
    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    auto messageOpt = V2TIMReceiveMessageOpt(opt);

    v2im::V2IMEngine::GetInstance()->SetGroupReceiveMessageOpt(groupIDStr, messageOpt, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSetAllReceiveMessageOpt, jint opt, jint start_hour, jint start_minute, jint start_second, jlong duration, jobject callback) {
    auto messageOpt = V2TIMReceiveMessageOpt(opt);
    v2im::V2IMEngine::GetInstance()->SetAllReceiveMessageOpt(messageOpt,start_hour,start_minute,start_second,duration, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSetAllReceiveMessageOpt2Time, jint opt, jlong start_time_stamp, jlong duration, jobject callback) {
    auto messageOpt = V2TIMReceiveMessageOpt(opt);
    v2im::V2IMEngine::GetInstance()->SetAllReceiveMessageOpt2(messageOpt, start_time_stamp, duration, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetAllReceiveMessageOpt, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMReceiveMessageOptInfo>;
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMReceiveMessageOptInfo &value){
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject msgOpt = v2im::jni::ReceiveMessageOptInfoJni::Convert2JObject_AllRecvMsg(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, msgOpt);
            _env->DeleteLocalRef(msgOpt);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetAllReceiveMessageOpt(value_callback);
}

void WriteLogExample(const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
//    V2TIMStringToV2TIMStringMap map;
//    map.Insert("logLevel", "V2TIM_LOG_DEBUG");                  // 必填字段
//    std::string content;
//    content.append(error_message.CString()).append(std::to_string(error_code)).append(std::to_string(value.Size()));
//    map.Insert("logContent", content.c_str());                     // 必填字段
//
//    V2TIMManager::GetInstance()->CallExperimentalAPI("writeLog", &map, nullptr);
}

DEFINE_NATIVE_FUNC(void, NativeGetC2CHistoryMessageList, jstring user_id, jint count, jobject last_msg, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);
    V2TIMMessageListGetOption option;
    option.userID = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();
    option.count = (uint32_t) count;
    option.getType = V2TIMMessageGetType::V2TIM_GET_CLOUD_OLDER_MSG;
    if (last_msg) {
        static V2TIMMessage message_c;
        bool msgFlg = v2im::jni::MessageJni::Convert2CoreObject(last_msg,message_c);
        if (msgFlg){
            option.lastMsg = &message_c;
//            option.lastMsg = new V2TIMMessage(message_c);
        }

    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
        WriteLogExample(error_code,error_message,value);

        v2im::jni::ScopedJEnv scopedJEnv;
        auto *_env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject messageObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject messageObj = v2im::jni::MessageJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(messageObjList, messageObj);
                _env->DeleteLocalRef(messageObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageObjList);
            _env->DeleteLocalRef(messageObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetHistoryMessageList(option, value_callback);
}


DEFINE_NATIVE_FUNC(void, NativeGetGroupHistoryMessageList, jstring group_id, jint count, jobject last_msg, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);
    V2TIMMessageListGetOption option;
    option.groupID = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    option.count = (uint32_t) count;
    option.getType = V2TIMMessageGetType::V2TIM_GET_CLOUD_OLDER_MSG;
    if (last_msg) {
        V2TIMMessage timMessage;
        bool msgFlag = v2im::jni::MessageJni::Convert2CoreObject(last_msg,timMessage);
        if (msgFlag){
            option.lastMsg = new V2TIMMessage(timMessage);
        }
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject messageObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject messageObj = v2im::jni::MessageJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(messageObjList, messageObj);
                _env->DeleteLocalRef(messageObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageObjList);
            _env->DeleteLocalRef(messageObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetHistoryMessageList(option, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetHistoryMessageList, jobject option, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessageListGetOption listGetOption;
    v2im::jni::MessageListGetOptionJni::Convert2CoreObject(option, listGetOption);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject messageObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject messageObj = v2im::jni::MessageJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(messageObjList, messageObj);
                _env->DeleteLocalRef(messageObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageObjList);
            _env->DeleteLocalRef(messageObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetHistoryMessageList(listGetOption, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeRevokeMessage, jobject msg, jobject callback) {
    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(msg,message_c);

    v2im::V2IMEngine::GetInstance()->RevokeMessage(message_c, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeModifyMessage, jobject msg, jobject callback) {
    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(msg,message_c);

    v2im::V2IMEngine::GetInstance()->ModifyMessage(message_c, new v2im::CompleteCallbackImpl<V2TIMMessage>(callback));
}

DEFINE_NATIVE_FUNC(void, NativeMarkC2CMessageAsRead, jstring user_id, jobject callback) {
    V2TIMString userIDStr = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();

    v2im::V2IMEngine::GetInstance()->MarkC2CMessageAsRead(userIDStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeMarkGroupMessageAsRead, jstring group_id, jobject callback) {
    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    v2im::V2IMEngine::GetInstance()->MarkGroupMessageAsRead(groupIDStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeMarkAllMessageAsRead, jobject callback) {
    v2im::V2IMEngine::GetInstance()->MarkAllMessageAsRead(new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeDeleteMessageFromLocalStorage, jobject msg, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

//    v2im::V2IMEngine::GetInstance()->DeleteMessages();
}

DEFINE_NATIVE_FUNC(void, NativeDeleteMessages, jobject messages, jobject callback) {
    V2TIMMessageVector messageVector;
    int size;
    size = v2im::jni::ArrayListJni::Size(messages);
    for (int i = 0; i < size; ++i) {
        jobject messageObj = v2im::jni::ArrayListJni::Get(messages, i);
        V2TIMMessage message_c;
        v2im::jni::MessageJni::Convert2CoreObject(messageObj,message_c);
        messageVector.PushBack(message_c);
        env->DeleteLocalRef(messageObj);
    }

    v2im::V2IMEngine::GetInstance()->DeleteMessages(messageVector, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeClearC2CHistoryMessage, jstring user_id, jobject callback) {
    V2TIMString userIDStr = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();

    v2im::V2IMEngine::GetInstance()->ClearC2CHistoryMessage(userIDStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeClearGroupHistoryMessage, jstring group_id, jobject callback) {
    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    v2im::V2IMEngine::GetInstance()->ClearGroupHistoryMessage(groupIDStr, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(jstring, NativeInsertGroupMessageToLocalStorage, jobject msg, jstring group_id, jstring sender, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(msg,message_c);
    V2TIMString groupIDStr = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMString senderStr = v2im::jni::StringJni::Jstring2Cstring(env, sender).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessage>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject messageObj = v2im::jni::MessageJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageObj);
            _env->DeleteLocalRef(messageObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    V2TIMString msgIDStr = v2im::V2IMEngine::GetInstance()->InsertGroupMessageToLocalStorage(message_c, groupIDStr, senderStr, value_callback);
    return v2im::jni::StringJni::Cstring2Jstring(env, msgIDStr.CString());
}

DEFINE_NATIVE_FUNC(jstring, NativeInsertC2CMessageToLocalStorage, jobject msg, jstring user_id, jstring sender, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(msg,message_c);
    V2TIMString userIDStr = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();
    V2TIMString senderStr = v2im::jni::StringJni::Jstring2Cstring(env, sender).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessage>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessage &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject messageObj = v2im::jni::MessageJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageObj);
            _env->DeleteLocalRef(messageObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    V2TIMString msgIDStr = v2im::V2IMEngine::GetInstance()->InsertC2CMessageToLocalStorage(message_c, userIDStr, senderStr, value_callback);
    return v2im::jni::StringJni::Cstring2Jstring(env, msgIDStr.CString());
}

DEFINE_NATIVE_FUNC(void, NativeFindMessages, jobject message_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector stringVector;
    int size = v2im::jni::ArrayListJni::Size(message_idlist);
    for (int i = 0; i < size; ++i) {
        auto abstractJStr = (jstring) v2im::jni::ArrayListJni::Get(message_idlist, i);
        V2TIMString abstract = v2im::jni::StringJni::Jstring2Cstring(env, abstractJStr).c_str();
        stringVector.PushBack(abstract);
        env->DeleteLocalRef(abstractJStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject messageObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject messageObj = v2im::jni::MessageJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(messageObjList, messageObj);
                _env->DeleteLocalRef(messageObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageObjList);
            _env->DeleteLocalRef(messageObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->FindMessages(stringVector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSearchLocalMessages, jobject search_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessageSearchParam searchParam;
    v2im::jni::MessageSearchParamJni::Convert2CoreObject(search_param, searchParam);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageSearchResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageSearchResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject searchResultObj = v2im::jni::MessageSearchResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, searchResultObj);
            _env->DeleteLocalRef(searchResultObj);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SearchLocalMessages(searchParam, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSearchCloudMessages, jobject search_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessageSearchParam searchParam;
    v2im::jni::MessageSearchParamJni::Convert2CoreObject(search_param, searchParam);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageSearchResult>;
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageSearchResult &value){
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code){
            jobject searchResultObj = v2im::jni::MessageSearchResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, searchResultObj);
            _env->DeleteLocalRef(searchResultObj);
        } else{
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }

        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SearchCloudMessages(searchParam,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSendMessageReadReceipts, jobject message_list, jobject callback) {
    V2TIMMessageVector messageVector;
    int size;
    size = v2im::jni::ArrayListJni::Size(message_list);
    for (int i = 0; i < size; ++i) {
        jobject messageObj = v2im::jni::ArrayListJni::Get(message_list, i);
        V2TIMMessage message_c;
        v2im::jni::MessageJni::Convert2CoreObject(messageObj,message_c);
        messageVector.PushBack(message_c);
        env->DeleteLocalRef(messageObj);
    }

    v2im::V2IMEngine::GetInstance()->SendMessageReadReceipts(messageVector, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetMessageReadReceipts, jobject message_list, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessageVector messageVector;
    int size;
    size = v2im::jni::ArrayListJni::Size(message_list);
    for (int i = 0; i < size; ++i) {
        jobject messageObj = v2im::jni::ArrayListJni::Get(message_list, i);
        if (messageObj) {
            V2TIMMessage message_c;
            if (v2im::jni::MessageJni::Convert2CoreObject(messageObj,message_c)) {
                messageVector.PushBack(message_c);
            }
            env->DeleteLocalRef(messageObj);
        }
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageReceiptVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageReceiptVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject messageReceiptObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject messageReceiptObj = v2im::jni::MessageReceiptJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(messageReceiptObjList, messageReceiptObj);
                _env->DeleteLocalRef(messageReceiptObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, messageReceiptObjList);
            _env->DeleteLocalRef(messageReceiptObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetMessageReadReceipts(messageVector, value_callback);
}
DEFINE_NATIVE_FUNC(void, NativeGetGroupMessageReadMemberList, jobject message, jint filter, jlong next_seq, jint count, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage message_c;
    v2im::jni::MessageJni::Convert2CoreObject(message,message_c);
    auto readMembersFilter = V2TIMGroupMessageReadMembersFilter(filter);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupMessageReadMemberList>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupMessageReadMemberList &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject readMemberListObj = v2im::jni::GroupMessageReadMemberListJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, readMemberListObj);
            _env->DeleteLocalRef(readMemberListObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupMessageReadMemberList(message_c, readMembersFilter, (uint64_t) next_seq, (uint32_t) count,
                                                                   value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetMessageExtensions, jobject message, jobject extensions, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage timMessage;
    v2im::jni::MessageJni::Convert2CoreObject(message,timMessage);

    V2TIMMessageExtensionVector extensionVector;
    int size = v2im::jni::ArrayListJni::Size(extensions);
    for (int i = 0; i < size; ++i){
        V2TIMMessageExtension extension;
        jobject extension_obj = v2im::jni::ArrayListJni::Get(extensions,i);
        bool flag = v2im::jni::MessageExtensionJni::Convert2CoreObject(extension_obj,extension);
        if (flag){
            extensionVector.PushBack(extension);
        }
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageExtensionResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageExtensionResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject extensionResultObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject extensionResultObj = v2im::jni::MessageExtensionResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(extensionResultObjList, extensionResultObj);
                _env->DeleteLocalRef(extensionResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, extensionResultObjList);
            _env->DeleteLocalRef(extensionResultObjList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SetMessageExtensions(timMessage, extensionVector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetMessageExtensions, jobject message, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage v2TimMessage;
    v2im::jni::MessageJni::Convert2CoreObject(message,v2TimMessage);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageExtensionVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageExtensionVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject extensionResultObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject extensionResultObj = v2im::jni::MessageExtensionJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(extensionResultObjList, extensionResultObj);
                _env->DeleteLocalRef(extensionResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, extensionResultObjList);
            _env->DeleteLocalRef(extensionResultObjList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetMessageExtensions(v2TimMessage,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteMessageExtensions, jobject message, jobject keys, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage v2TimMessage;
    v2im::jni::MessageJni::Convert2CoreObject(message,v2TimMessage);

    V2TIMStringVector key_array;
    int size = v2im::jni::ArrayListJni::Size(keys);
    for (int i = 0; i < size; ++i){
        auto keyStr = (jstring)v2im::jni::ArrayListJni::Get(keys,i);
        key_array.PushBack(v2im::jni::StringJni::Jstring2Cstring(env,keyStr).c_str());
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageExtensionResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageExtensionResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject extensionResultObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject extensionResultObj = v2im::jni::MessageExtensionResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(extensionResultObjList, extensionResultObj);
                _env->DeleteLocalRef(extensionResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, extensionResultObjList);
            _env->DeleteLocalRef(extensionResultObjList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->DeleteMessageExtensions(v2TimMessage,key_array,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeAddMessageReaction, jobject message, jstring reaction_id, jobject callback) {
    V2TIMMessage timMessage;
    v2im::jni::MessageJni::Convert2CoreObject(message,timMessage);
    std::string reactionIdStr = v2im::jni::StringJni::Jstring2Cstring(env,reaction_id);
    v2im::V2IMEngine::GetInstance()->AddMessageReaction(timMessage,reactionIdStr.c_str(),new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeRemoveMessageReaction, jobject message, jstring reaction_id, jobject callback) {
    V2TIMMessage timMessage;
    v2im::jni::MessageJni::Convert2CoreObject(message,timMessage);
    std::string reactionIdStr = v2im::jni::StringJni::Jstring2Cstring(env,reaction_id);
    v2im::V2IMEngine::GetInstance()->RemoveMessageReaction(timMessage,reactionIdStr.c_str(),new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetMessageReactions, jobject message_list, jint max_user_count_per_reaction, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessageVector message_array;
    int size;
    size = v2im::jni::ArrayListJni::Size(message_list);
    for (int i = 0; i < size; ++i) {
        jobject messageObj = v2im::jni::ArrayListJni::Get(message_list, i);
        if (messageObj) {
            V2TIMMessage timMessage;
            v2im::jni::MessageJni::Convert2CoreObject(messageObj,timMessage);
            message_array.PushBack(timMessage);
            env->DeleteLocalRef(messageObj);
        }
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageReactionResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageReactionResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject reactionsResultObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject reactionsResultObj = v2im::jni::MessageReactionResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(reactionsResultObjList, reactionsResultObj);
                _env->DeleteLocalRef(reactionsResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, reactionsResultObjList);
            _env->DeleteLocalRef(reactionsResultObjList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetMessageReactions(message_array,max_user_count_per_reaction,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetAllUserListOfMessageReaction, jobject message, jstring reaction_id, jint next_seq, jint count, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMMessage timMessage;
    v2im::jni::MessageJni::Convert2CoreObject(message,timMessage);
    std::string reactionIdStr = v2im::jni::StringJni::Jstring2Cstring(env,reaction_id);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMMessageReactionUserResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMMessageReactionUserResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject reactionUserResultObj = v2im::jni::MessageReactionUserResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, reactionUserResultObj);
            _env->DeleteLocalRef(reactionUserResultObj);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetAllUserListOfMessageReaction(timMessage,reactionIdStr.c_str(),next_seq,count,value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeTranslateText, jobject source_text_list, jstring source_language, jstring target_language, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector source_text_array;
    int size = v2im::jni::ArrayListJni::Size(source_text_list);
    for (int i = 0; i < size; ++i){
        auto keyStr = (jstring)v2im::jni::ArrayListJni::Get(source_text_list,i);
        source_text_array.PushBack(v2im::jni::StringJni::Jstring2Cstring(env,keyStr).c_str());
    }

    std::string souLan = v2im::jni::StringJni::Jstring2Cstring(env,source_language);
    std::string tarLan = v2im::jni::StringJni::Jstring2Cstring(env,target_language);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMStringToV2TIMStringMap>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMStringToV2TIMStringMap &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject j_obj_translateHashMap = v2im::jni::HashMapJni::NewHashMap();
            V2TIMStringVector keys  = value.AllKeys();
            for (int i = 0; i < keys.Size(); ++i) {
                jstring sourceTextKey = v2im::jni::StringJni::Cstring2Jstring(_env, keys[i].CString());
                if (sourceTextKey) {
                    jstring targetTextValue = v2im::jni::StringJni::Cstring2Jstring(_env, value.Get(keys[i]).CString());
                    if (targetTextValue) {
                        v2im::jni::HashMapJni::Put(j_obj_translateHashMap, sourceTextKey, targetTextValue);
                        _env->DeleteLocalRef(targetTextValue);
                    }
                    _env->DeleteLocalRef(sourceTextKey);
                }
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, j_obj_translateHashMap);
            _env->DeleteLocalRef(j_obj_translateHashMap);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->TranslateText(source_text_array,souLan.c_str(),tarLan.c_str(),value_callback);
}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeInitCplusplusAdvancedMsgListener", "()V",                                                                                                       (void *) nativeInitCplusplusAdvancedMsgListener},
        {"nativeAddAdvancedMsgListener",           "(Lcom/tencent/imsdk/v2/V2TIMAdvancedMsgListener;Ljava/lang/String;)V",                                      (void *) NativeAddAdvancedMsgListener},
        {"nativeRemoveAdvancedMsgListener",        "(Ljava/lang/String;)V",                                                                                     (void *) NativeRemoveAdvancedMsgListener},
        {"nativeCreateTextMessage",                "(Ljava/lang/String;)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                                   (jobject *) NativeCreateTextMessage},
        {"nativeCreateTextAtMessage",              "(Ljava/lang/String;Ljava/util/List;)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                   (jobject *) NativeCreateTextAtMessage},
        {"nativeCreateCustomMessage",              "([B)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                                                   (jobject *) NativeCreateCustomMessage},
        {"nativeCreateCustomMessage",              "([BLjava/lang/String;[B)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                               (jobject *) NativeCreateCustomMessageForParame},
        {"nativeCreateImageMessage",               "(Ljava/lang/String;)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                                   (jobject *) NativeCreateImageMessage},
        {"nativeCreateSoundMessage",               "(Ljava/lang/String;I)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                                  (jobject *) NativeCreateSoundMessage},
        {"nativeCreateVideoMessage",               "(Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)Lcom/tencent/imsdk/v2/V2TIMMessage;",              (jobject *) NativeCreateVideoMessage},
        {"nativeCreateFileMessage",                "(Ljava/lang/String;Ljava/lang/String;)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                 (jobject *) NativeCreateFileMessage},
        {"nativeCreateLocationMessage",            "(Ljava/lang/String;DD)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                                 (jobject *) NativeCreateLocationMessage},
        {"nativeCreateFaceMessage",                "(I[B)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                                                  (jobject *) NativeCreateFaceMessage},
        {"nativeCreateMergerMessage",              "(Ljava/util/List;Ljava/lang/String;Ljava/util/List;Ljava/lang/String;)Lcom/tencent/imsdk/v2/V2TIMMessage;", (jobject *) NativeCreateMergerMessage},
        {"nativeCreateForwardMessage",             "(Lcom/tencent/imsdk/v2/V2TIMMessage;)Lcom/tencent/imsdk/v2/V2TIMMessage;",                                  (jobject *) NativeCreateForwardMessage},
        {"nativeCreateTargetedGroupMessage",       "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/util/List;)Lcom/tencent/imsdk/v2/V2TIMMessage;",                  (jobject *) NativeCreateTargetedGroupMessage},
        {"nativeSendMessage",
                                                   "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/lang/String;Ljava/lang/String;"
                                                   "IZLcom/tencent/imsdk/v2/V2TIMOfflinePushInfo;Lcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",     (jstring *) NativeSendMessage},
        {"nativeSetC2CReceiveMessageOpt",          "(Ljava/util/List;ILcom/tencent/imsdk/common/IMCallback;)V",                                                 (void *) NativeSetC2CReceiveMessageOpt},
        {"nativeGetC2CReceiveMessageOpt",          "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeGetC2CReceiveMessageOpt},
        {"nativeSetGroupReceiveMessageOpt",        "(Ljava/lang/String;ILcom/tencent/imsdk/common/IMCallback;)V",                                               (void *) NativeSetGroupReceiveMessageOpt},
        {"nativeSetAllReceiveMessageOpt",         "(IIIIJLcom/tencent/imsdk/common/IMCallback;)V",                                                         (void *) NativeSetAllReceiveMessageOpt},
        {"nativeSetAllReceiveMessageOpt",         "(IJJLcom/tencent/imsdk/common/IMCallback;)V",                                                           (void *) NativeSetAllReceiveMessageOpt2Time},
        {"nativeGetAllReceiveMessageOpt",         "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                              (void *) NativeGetAllReceiveMessageOpt},
        {"nativeGetC2CHistoryMessageList",         "(Ljava/lang/String;ILcom/tencent/imsdk/v2/V2TIMMessage;Lcom/tencent/imsdk/common/IMCallback;)V",            (void *) NativeGetC2CHistoryMessageList},
        {"nativeGetGroupHistoryMessageList",       "(Ljava/lang/String;ILcom/tencent/imsdk/v2/V2TIMMessage;Lcom/tencent/imsdk/common/IMCallback;)V",            (void *) NativeGetGroupHistoryMessageList},
        {"nativeGetHistoryMessageList",            "(Lcom/tencent/imsdk/v2/V2TIMMessageListGetOption;Lcom/tencent/imsdk/common/IMCallback;)V",                  (void *) NativeGetHistoryMessageList},
        {"nativeRevokeMessage",                    "(Lcom/tencent/imsdk/v2/V2TIMMessage;Lcom/tencent/imsdk/common/IMCallback;)V",                               (void *) NativeRevokeMessage},
        {"nativeModifyMessage",                    "(Lcom/tencent/imsdk/v2/V2TIMMessage;Lcom/tencent/imsdk/common/IMCallback;)V",                               (void *) NativeModifyMessage},
        {"nativeMarkC2CMessageAsRead",             "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                                (void *) NativeMarkC2CMessageAsRead},
        {"nativeMarkGroupMessageAsRead",           "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                                (void *) NativeMarkGroupMessageAsRead},
        {"nativeMarkAllMessageAsRead",             "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                  (void *) NativeMarkAllMessageAsRead},
        {"nativeDeleteMessageFromLocalStorage",    "(Lcom/tencent/imsdk/v2/V2TIMMessage;Lcom/tencent/imsdk/common/IMCallback;)V",                               (void *) NativeDeleteMessageFromLocalStorage},
        {"nativeDeleteMessages",                   "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeDeleteMessages},
        {"nativeClearC2CHistoryMessage",           "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                                (void *) NativeClearC2CHistoryMessage},
        {"nativeClearGroupHistoryMessage",         "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                                (void *) NativeClearGroupHistoryMessage},
        {"nativeInsertGroupMessageToLocalStorage",
                                                   "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/lang/String;"
                                                   "Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",                                (jstring *) NativeInsertGroupMessageToLocalStorage},
        {"nativeInsertC2CMessageToLocalStorage",
                                                   "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/lang/String;"
                                                   "Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)Ljava/lang/String;",                                (jstring *) NativeInsertC2CMessageToLocalStorage},
        {"nativeFindMessages",                     "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeFindMessages},
        {"nativeSearchLocalMessages",              "(Lcom/tencent/imsdk/v2/V2TIMMessageSearchParam;Lcom/tencent/imsdk/common/IMCallback;)V",                    (void *) NativeSearchLocalMessages},
        {"nativeSearchCloudMessages",             "(Lcom/tencent/imsdk/v2/V2TIMMessageSearchParam;Lcom/tencent/imsdk/common/IMCallback;)V",                (void *) NativeSearchCloudMessages},
        {"nativeSendMessageReadReceipts",          "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeSendMessageReadReceipts},
        {"nativeGetMessageReadReceipts",           "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeGetMessageReadReceipts},
        {"nativeGetGroupMessageReadMemberList",    "(Lcom/tencent/imsdk/v2/V2TIMMessage;IJILcom/tencent/imsdk/common/IMCallback;)V",                            (void *) NativeGetGroupMessageReadMemberList},
        {"nativeSetMessageExtensions",            "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",           (void *) NativeSetMessageExtensions},
        {"nativeGetMessageExtensions",            "(Lcom/tencent/imsdk/v2/V2TIMMessage;Lcom/tencent/imsdk/common/IMCallback;)V",                           (void *) NativeGetMessageExtensions},
        {"nativeDeleteMessageExtensions",         "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",           (void *) NativeDeleteMessageExtensions},
        {"nativeAddMessageReaction",              "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",         (void *) NativeAddMessageReaction},
        {"nativeRemoveMessageReaction",           "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",         (void *) NativeRemoveMessageReaction},
        {"nativeGetMessageReactions",             "(Ljava/util/List;ILcom/tencent/imsdk/common/IMCallback;)V",                                             (void *) NativeGetMessageReactions},
        {"nativeGetAllUserListOfMessageReaction", "(Lcom/tencent/imsdk/v2/V2TIMMessage;Ljava/lang/String;IILcom/tencent/imsdk/common/IMCallback;)V",       (void *) NativeGetAllUserListOfMessageReaction},
        {"nativeTranslateText",                   "(Ljava/util/List;Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",          (void *) NativeTranslateText},
};

//注册 native 方法
int RegisterNativeMethodsForV2TIMMessageManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMMessageManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}

#ifdef __cplusplus
}
#endif