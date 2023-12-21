//
// Created by EDY on 2022/10/8.
//

#include "receive_message_opt_info_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass ReceiveMessageOptInfoJni::j_cls_;
        jfieldID ReceiveMessageOptInfoJni::j_field_array_[FieldIDMax];
        jmethodID ReceiveMessageOptInfoJni::j_method_id_array_[MethodIDMax];

        bool ReceiveMessageOptInfoJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMReceiveMessageOptInfo");
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
            jfield = env->GetFieldID(j_cls_, "c2CReceiveMessageOpt", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDC2CReceiveMessageOpt] = jfield;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUserID] = jfield;

            return true;
        }

        jobject ReceiveMessageOptInfoJni::Convert2JObject(const V2TIMReceiveMessageOptInfo &messageOptInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject userStatusObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!userStatusObj) {
                return nullptr;
            }

            env->SetIntField(userStatusObj, j_field_array_[FieldIDC2CReceiveMessageOpt], (jint) messageOptInfo.receiveOpt);
            env->SetObjectField(userStatusObj, j_field_array_[FieldIDUserID], StringJni::Cstring2Jstring(env, messageOptInfo.userID.CString()));

            return userStatusObj;
        }

        jobject ReceiveMessageOptInfoJni::Convert2JObject_AllRecvMsg(const V2TIMReceiveMessageOptInfo &messageOptInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject userStatusObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!userStatusObj) {
                return nullptr;
            }

            env->SetIntField(userStatusObj, j_field_array_[FieldIDStartHour], messageOptInfo.startHour);
            env->SetIntField(userStatusObj, j_field_array_[FieldIDStartMinute], messageOptInfo.startMinute);
            env->SetIntField(userStatusObj, j_field_array_[FieldIDStartSecond], messageOptInfo.startSecond);
            env->SetLongField(userStatusObj, j_field_array_[FieldIDStartTimeStamp], messageOptInfo.startTimeStamp);
            env->SetLongField(userStatusObj, j_field_array_[FieldIDDuration], messageOptInfo.duration);
            env->SetIntField(userStatusObj, j_field_array_[FieldIDAllReceiveMessageOpt], messageOptInfo.receiveOpt);
            return userStatusObj;
        }

    }// namespace jni
}// namespace v2im