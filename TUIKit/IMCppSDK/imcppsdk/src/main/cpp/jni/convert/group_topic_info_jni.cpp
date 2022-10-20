//
// Created by Junker on 2022/9/23.
//

#include <jni_helper.h>
#include "group_topic_info_jni.h"
#include "java_basic_jni.h"
#include "message_jni.h"
#include "group_at_info_jni.h"
#include "V2TIMCommon.h"

namespace v2im {
    namespace jni {
        jclass GroupTopicInfoJni::j_cls_;
        jfieldID GroupTopicInfoJni::j_field_id_array_[FieldIDMax];
        jmethodID GroupTopicInfoJni::j_method_id_array_[MethodIDMax];

        bool GroupTopicInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMTopicInfo");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addGroupAtInfo", "(Lcom/tencent/imsdk/v2/V2TIMGroupAtInfo;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDAddGroupAtInfo] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "topicID", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDTopicID] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "topicName", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDTopicName] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "topicFaceUrl", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDTopicFaceUrl] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "introduction", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDIntroduction] = jfield;

            jfield = env->GetFieldID(j_cls_, "notification", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDNotification] = jfield;

            jfield = env->GetFieldID(j_cls_, "allMute", "Z");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDAllMute] = jfield;

            jfield = env->GetFieldID(j_cls_, "selfMuteTime", "J");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDSelfMuteTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "customString", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDCustomString] = jfield;

            jfield = env->GetFieldID(j_cls_, "recvOpt", "I");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDRecvOpt] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "draftText", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDDraftText] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "unreadCount", "J");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDUnreadCount] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "lastMessage", "Lcom/tencent/imsdk/v2/V2TIMMessage;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDLastMessage] = jfield;
            
            jfield = env->GetFieldID(j_cls_, "groupAtInfoList", "Ljava/util/List;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDGroupAtInfoList] = jfield;
            
            return true;
        }

        jobject GroupTopicInfoJni::Convert2JObject(const V2TIMTopicInfo &topicInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject j_obj_topicInfo = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);

            jstring jStr = nullptr;

            jStr = StringJni::Cstring2Jstring(env,topicInfo.topicID.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDTopicID],jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env,topicInfo.topicName.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDTopicName],jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env,topicInfo.topicFaceURL.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDTopicFaceUrl],jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env,topicInfo.introduction.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDIntroduction],jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env,topicInfo.notification.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDNotification],jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetBooleanField(j_obj_topicInfo,j_field_id_array_[FieldIDAllMute],topicInfo.isAllMuted);
            env->SetLongField(j_obj_topicInfo,j_field_id_array_[FieldIDSelfMuteTime],(jlong)topicInfo.selfMuteTime);

            jStr = StringJni::Cstring2Jstring(env,topicInfo.customString.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDCustomString],jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(j_obj_topicInfo,j_field_id_array_[FieldIDRecvOpt],(jint)topicInfo.recvOpt);

            jStr = StringJni::Cstring2Jstring(env,topicInfo.draftText.CString());
            if (jStr){
                env->SetObjectField(j_obj_topicInfo,j_field_id_array_[FieldIDDraftText],jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetLongField(j_obj_topicInfo,j_field_id_array_[FieldIDUnreadCount],(jlong)topicInfo.unreadCount);

            if (topicInfo.lastMessage){
                jobject j_obj_lastMessage = MessageJni::Convert2JObject(*topicInfo.lastMessage);
                if (j_obj_lastMessage) {
                    env->SetObjectField(j_obj_topicInfo, j_field_id_array_[FieldIDLastMessage], j_obj_lastMessage);
                    env->DeleteLocalRef(j_obj_lastMessage);
                }
            }

            for (int i = 0; i < topicInfo.groupAtInfoList.Size(); ++i) {
                jobject j_obj_atInfo = GroupAtInfoJni::Convert2JObject(topicInfo.groupAtInfoList[i]);
                if (nullptr != j_obj_atInfo) {
                    env->CallVoidMethod(j_obj_topicInfo,j_method_id_array_[i],j_obj_topicInfo);
                    env->DeleteLocalRef(j_obj_atInfo);
                }
            }

            return j_obj_topicInfo;
            
        }

        bool GroupTopicInfoJni::Convert2CoreObject(const jobject &object, V2TIMTopicInfo &topicInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jstring jStr = nullptr;
            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDTopicID]);
            if (jStr) {
                topicInfo.topicID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDTopicName]);
            if (jStr) {
                topicInfo.topicName = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDTopicFaceUrl]);
            if (jStr) {
                topicInfo.topicFaceURL = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDIntroduction]);
            if (jStr) {
                topicInfo.introduction = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDNotification]);
            if (jStr) {
                topicInfo.notification = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            topicInfo.isAllMuted = env->GetBooleanField(object,j_field_id_array_[FieldIDAllMute]);
            topicInfo.selfMuteTime = env->GetLongField(object,j_field_id_array_[FieldIDSelfMuteTime]);


            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDCustomString]);
            if (jStr) {
                topicInfo.customString = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            topicInfo.recvOpt = V2TIMReceiveMessageOpt(env->GetIntField(object,j_field_id_array_[FieldIDRecvOpt]));

            jStr = (jstring) env->GetObjectField(object, j_field_id_array_[FieldIDDraftText]);
            if (jStr) {
                topicInfo.draftText = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            topicInfo.unreadCount = env->GetLongField(object,j_field_id_array_[FieldIDUnreadCount]);

            jobject j_obj = nullptr;

//            j_obj = env->GetObjectField(object, j_field_id_array_[FieldIDLastMessage]);
//            if (j_obj) {
//                topicInfo.lastMessage = MessageJni::Convert2JObject();
//                env->DeleteLocalRef(jStr);
//            }

//            jobject j_obj = nullptr;
//            j_obj = env->GetObjectField(object, j_field_id_array_[FieldIDGroupAtInfoList]);
//            if (j_obj) {
//                topicInfo. = StringJni::Jstring2Cstring(env, jStr).c_str();
//                env->DeleteLocalRef(jStr);
//            }

            return true;
        }

    }// namespace jni
}// namespace v2im