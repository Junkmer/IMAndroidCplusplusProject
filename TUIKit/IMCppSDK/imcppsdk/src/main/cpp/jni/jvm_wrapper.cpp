//
// Created by EDY on 2022/8/22.
//

#include <android/log.h>
#include <jni.h>

//日志打印
#include "../util/LogUtil.h"

// Java 基础数据类型
#include "java_basic_jni.h"

// C++ 回调 Java 通用 Callback
#include "basic/jni_helper.h"

// 初始化 SDKConfig
#include "convert/sdk_config_jni.h"

//监听相关
#include "advanced_msg_listener_jni.h"
//#include "base_listener_jni.h"
#include "conversation_listener_jni.h"
#include "friend_listener_jni.h"
#include "group_listener_jni.h"
#include "im_callbak_jni.h"
#include "signaling_listener_jni.h"
#include "simple_listener_jni.h"

//会话相关
#include "conversation_jni.h"
#include "conversation_list_filter_jni.h"
#include "conversation_operation_result_jni.h"
#include "conversation_result_jni.h"

//资料关系链相关
#include "friend_add_application_jni.h"
#include "friend_application_jni.h"
#include "friend_application_result_jni.h"
#include "friend_check_result_jni.h"
#include "friend_group_jni.h"
#include "friend_info_jni.h"
#include "friend_info_result_jni.h"
#include "friend_operation_result_jni.h"
#include "friend_search_param_jni.h"
#include "user_full_info_jni.h"
#include "user_status_jni.h"
#include "user_info_jni.h"
#include "official_account_info_jni.h"

//群组相关
#include "create_group_member_info_jni.h"
#include "group_application_jni.h"
#include "group_application_result_jni.h"
#include "group_at_info_jni.h"
#include "group_change_info_jni.h"
#include "group_info_jni.h"
#include "group_info_result_jni.h"
#include "group_member_change_info_jni.h"
#include "group_member_full_info_jni.h"
#include "group_member_info_jni.h"
#include "group_member_info_result_jni.h"
#include "group_member_operation_result_jni.h"
#include "group_member_search_param_jni.h"
#include "group_message_read_member_list_jni.h"
#include "group_search_param.h"
#include "group_topic_info_jni.h"
#include "topic_info_result_jni.h"
#include "topic_operation_result_jni.h"

//推送相关
#include "offline_push_config_jni.h"
#include "offline_push_info_jni.h"

//消息相关
#include "elem_processor_jni.h"
#include "image_jni.h"
#include "message_jni.h"
#include "message_list_get_option_jni.h"
#include "message_receipt_jni.h"
#include "message_search_param_jni.h"
#include "message_search_result_item_jni.h"
#include "message_search_result_jni.h"
#include "receive_message_opt_info_jni.h"
#include "download_param_jni.h"
#include "message_extension_jni.h"
#include "message_extension_result_jni.h"
#include "message_reaction_jni.h"
#include "message_reaction_result_jni.h"
#include "message_reaction_user_result_jni.h"
#include "message_reaction_change_info_jni.h"

//信令相关
#include "signaling_info_jni.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHECK_INITIDS_RESULT(success, class_name) \
    if(false == (success)) {                      \
        LOGE("%s InitIDs failed",class_name);     \
    }

extern int RegisterNativeMethodsForV2TIMManager(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMConversationManager(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMFriendshipManager(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMGroupManager(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMMessageManager(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMOfflinePushManager(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMSignalingManager(JNIEnv *env);
//注册下载媒体消息文件
extern int RegisterNativeMethodsForV2TIMImageElem(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMSoundElem(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMVideoElem(JNIEnv *env);
extern int RegisterNativeMethodsForV2TIMFileElem(JNIEnv *env);


static void InitJNI(JNIEnv *env) {
    // Java 基础数据类型
    bool success = v2im::jni::IntegerJni::Init(env);
    CHECK_INITIDS_RESULT(success, "IntegerJni")

    success = v2im::jni::LongJni::Init(env);
    CHECK_INITIDS_RESULT(success, "LongJni")

    success = v2im::jni::StringJni::Init(env);
    CHECK_INITIDS_RESULT(success, "StringJni")

    success = v2im::jni::ArrayListJni::Init(env);
    CHECK_INITIDS_RESULT(success, "ArrayListJni")

    success = v2im::jni::HashMapJni::Init(env);
    CHECK_INITIDS_RESULT(success, "HashMapJni")

    // C++ 回调 Java 通用 Callback
    success = v2im::jni::IMCallbackJNI::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "IMCallbackJNI")

    // 初始化 SDKConfig
    success = v2im::jni::SDKConfigJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "SDKConfigJni")

    //监听相关
    success = v2im::jni::AdvancedMsgListenerJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "AdvancedMsgListenerJni")

    success = v2im::jni::ConversationListenerJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "ConversationListenerJni")

    success = v2im::jni::FriendListenerJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendListenerJni")

    success = v2im::jni::GroupListenerJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupListenerJni")

    success = v2im::jni::IMCallbackJNI::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "IMCallbackJNI")

    success = v2im::jni::SignalingListenerJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "SignalingListenerJni")

    success = v2im::jni::SimpleListenerJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "SimpleListenerJni")


    //会话相关
    success = v2im::jni::ConversationJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "ConversationJni")

    success = v2im::jni::ConversationListFilterJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "ConversationListFilterJni")

    success = v2im::jni::ConversationOperationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "ConversationOperationResultJni")

    success = v2im::jni::ConversationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "ConversationResultJni")


    //资料关系链相关
    success = v2im::jni::FriendAddApplicationJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendAddApplicationJni")

    success = v2im::jni::FriendApplicationJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendApplicationJni")

    success = v2im::jni::FriendApplicationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendApplicationResultJni")

    success = v2im::jni::FriendCheckResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendCheckResultJni")

    success = v2im::jni::FriendGroupJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendGroupJni")

    success = v2im::jni::FriendInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendInfoJni")

    success = v2im::jni::FriendInfoResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendInfoResultJni")

    success = v2im::jni::FriendOperationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendOperationResultJni")

    success = v2im::jni::FriendSearchParamJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "FriendSearchParamJni")

    success = v2im::jni::UserFullInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "UserFullInfoJni")

    success = v2im::jni::UserStatusJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "UserStatusJni")

    success = v2im::jni::UserInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "UserInfoJni")

    success = v2im::jni::OfficialAccountInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "OfficialAccountInfoJni")

    //群组相关
    success = v2im::jni::CreateGroupMemberInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "CreateGroupMemberInfoJni")

    success = v2im::jni::GroupApplicationJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupApplicationJni")

    success = v2im::jni::GroupApplicationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupApplicationResultJni")

    success = v2im::jni::GroupAtInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupAtInfoJni")

    success = v2im::jni::GroupChangeInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupChangeInfoJni")

    success = v2im::jni::GroupInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupInfoJni")

    success = v2im::jni::GroupInfoResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupInfoResultJni")

    success = v2im::jni::GroupMemberChangeInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMemberChangeInfoJni")

    success = v2im::jni::GroupMemberFullInfoJNI::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMemberFullInfoJNI")

    success = v2im::jni::GroupMemberInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMemberInfoJni")

    success = v2im::jni::GroupMemberInfoResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMemberInfoResultJni")

    success = v2im::jni::GroupMemberOperationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMemberOperationResultJni")

    success = v2im::jni::GroupMemberSearchParamJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMemberSearchParamJni")

    success = v2im::jni::GroupMessageReadMemberListJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupMessageReadMemberListJni")

    success = v2im::jni::GroupSearchParam::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupSearchParam")

    success = v2im::jni::GroupTopicInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "GroupTopicInfoJni")

    success = v2im::jni::TopicInfoResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "TopicInfoResultJni")

    success = v2im::jni::TopicOperationResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "TopicOperationResultJni")

    //推送相关
    success = v2im::jni::OfflinePushConfigJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "OfflinePushConfigJni")

    success = v2im::jni::OfflinePushInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "OfflinePushInfoJni")

    //消息相关
    success = v2im::jni::ImageJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageJni")

    success = v2im::jni::MessageJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageJni")

    success = v2im::jni::MessageListGetOptionJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageListGetOptionJni")

    success = v2im::jni::MessageReceiptJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageReceiptJni")

    success = v2im::jni::MessageSearchParamJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageSearchParamJni")

    success = v2im::jni::MessageSearchResultItemJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageSearchResultItemJni")

    success = v2im::jni::MessageSearchResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageSearchResultJni")

    success = v2im::jni::ReceiveMessageOptInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "ReceiveMessageOptInfoJni")

    success = v2im::jni::DownloadParamJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "DownloadParamJni")

    success = v2im::jni::MessageExtensionJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageExtensionJni")

    success = v2im::jni::MessageExtensionResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageExtensionResultJni")

    success = v2im::jni::MessageReactionJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageReactionJni")

    success = v2im::jni::MessageReactionResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageReactionResultJni")

    success = v2im::jni::MessageReactionUserResultJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageReactionUserResultJni")

    success = v2im::jni::MessageReactionChangeInfoJni::InitIDs(env);
    CHECK_INITIDS_RESULT(success, "MessageReactionChangeInfoJni")

    v2im::jni::ElemProcessor::GetInstance().RegisterElemHandler();
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    v2im::jni::JniHelper::Init(vm);

    jint result = JNI_ERR;
    v2im::jni::ScopedJEnv scopedJEnv;
    JNIEnv *env = scopedJEnv.GetEnv();
    if (NULL == env) {
        __android_log_print(ANDROID_LOG_ERROR, "Native-IMSDK",
                            " ############### invalid JNIEnv ############### ");
        return result;
    }
    LOGE("jvm_wrapper.cpp JNI_OnLoad | env = %p", env);
    InitJNI(env);

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMManager(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMConversationManager(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMFriendshipManager(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMGroupManager(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMMessageManager(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMOfflinePushManager(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMSignalingManager(env)) {
        return result;
    }

    //下载消息

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMImageElem(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMSoundElem(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMVideoElem(env)) {
        return result;
    }

    if (JNI_TRUE != RegisterNativeMethodsForV2TIMFileElem(env)) {
        return result;
    }

#ifdef __arm__
    __android_log_print(ANDROID_LOG_INFO, "Native-IMSDK",
                        " ############### imsdk version arm32 ############### ");
#endif

#ifdef __aarch64__
    __android_log_print(ANDROID_LOG_INFO, "Native-IMSDK",
                        " ################ imsdk version arm64 ############### ");
#endif

    return JNI_VERSION_1_6;
}

//JNIEXPORT void JNI_OnUnload(JavaVM *aJvm, void *aReserved){}

#ifdef __cplusplus
}
#endif