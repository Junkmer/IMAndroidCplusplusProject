//
// Created by EDY on 2022/10/8.
//

#include "message_list_get_option_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "message_jni.h"
#include "LogUtil.h"

namespace v2im {
    namespace jni {
        jclass MessageListGetOptionJni::j_cls_;
        jfieldID MessageListGetOptionJni::j_field_array_[FieldIDMax];
        jmethodID MessageListGetOptionJni::j_method_id_array_[MethodIDMax];

        bool MessageListGetOptionJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageListGetOption");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDConstructor] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_, "getType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGetType] = jfield;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupID] = jfield;

            jfield = env->GetFieldID(j_cls_, "count", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "lastMsg", "Lcom/tencent/imsdk/v2/V2TIMMessage;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDLastMsg] = jfield;

            jfield = env->GetFieldID(j_cls_, "lastMsgSeq", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDLastMsgSeq] = jfield;

            jfield = env->GetFieldID(j_cls_, "getTimeBegin", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGetTimeBegin] = jfield;

            jfield = env->GetFieldID(j_cls_, "getTimePeriod", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGetTimePeriod] = jfield;

            jfield = env->GetFieldID(j_cls_, "messageTypeList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMessageTypeList] = jfield;

            return true;
        }

        bool MessageListGetOptionJni::Convert2CoreObject(jobject const &j_obj_getOption, V2TIMMessageListGetOption &getOption) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            getOption.getType = V2TIMMessageGetType(env->GetIntField(j_obj_getOption, j_field_array_[FieldIDGetType]));

            jstring jStr = nullptr;
            jStr = (jstring) env->GetObjectField(j_obj_getOption, j_field_array_[FieldIDUserID]);
            if (jStr) {
                getOption.userID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_getOption, j_field_array_[FieldIDGroupID]);
            if (jStr) {
                getOption.groupID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            getOption.count = env->GetIntField(j_obj_getOption, j_field_array_[FieldIDCount]);

            jobject j_obj_message = env->GetObjectField(j_obj_getOption,j_field_array_[FieldIDLastMsg]);
            if (j_obj_message){
                std::unique_ptr<V2TIMMessage> timMessage = v2im::jni::MessageJni::Convert2CoreObject(j_obj_message);
                getOption.lastMsg = timMessage.get();
                timMessage.release();// 释放局部变量指针 elem，让传入 message->elemList 数据的elem重新分配内存。
                env->DeleteLocalRef(j_obj_message);
            }

            getOption.lastMsgSeq = env->GetLongField(j_obj_getOption, j_field_array_[FieldIDLastMsgSeq]);
            getOption.getTimeBegin = env->GetLongField(j_obj_getOption, j_field_array_[FieldIDGetTimeBegin]);
            getOption.getTimePeriod = env->GetLongField(j_obj_getOption, j_field_array_[FieldIDGetTimePeriod]);

            jobject j_obj_messageTypeList = env->GetObjectField(j_obj_getOption,j_field_array_[FieldIDMessageTypeList]);
            if (j_obj_messageTypeList){
                int size = ArrayListJni::Size(j_obj_messageTypeList);
                for (int i = 0; i < size; ++i) {
                    jobject messageTypeObj = ArrayListJni::Get(j_obj_messageTypeList,i);
                    int messageType = IntegerJni::IntValue(ArrayListJni::Get(j_obj_messageTypeList,i));
                    getOption.messageTypeList.PushBack(V2TIMElemType(messageType));
                }
                env->DeleteLocalRef(j_obj_messageTypeList);
            }
            return true;
        }

    }// namespace jni
}// namespace v2im