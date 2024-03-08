//
// Created by EDY on 2022/9/26.
//

#include "user_status_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass UserStatusJni::j_cls_;
        jfieldID UserStatusJni::j_field_array_[FieldIDMax];
        jmethodID UserStatusJni::j_method_id_array_[MethodIDMax];

        bool UserStatusJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMUserStatus");
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
            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "statusType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDStatusType] = jfield;

            jfield = env->GetFieldID(j_cls_, "customStatus", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCustomStatus] = jfield;

            return true;
        }

        jobject UserStatusJni::Convert2JObject(const V2TIMUserStatus &userStatus) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject userStatusObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!userStatusObj) {
                return nullptr;
            }

            env->SetObjectField(userStatusObj, j_field_array_[FieldIDUserID], StringJni::Cstring2Jstring(env, userStatus.userID.CString()));
            env->SetIntField(userStatusObj, j_field_array_[FieldIDStatusType], (jint) userStatus.statusType);
            if (!userStatus.customStatus.Empty()) {
                env->SetObjectField(userStatusObj, j_field_array_[FieldIDCustomStatus],
                                    StringJni::Cstring2Jstring(env, userStatus.customStatus.CString()));
            }

            return userStatusObj;
        }

        bool UserStatusJni::Convert2CoreObject(const jobject &userStatusObj, V2TIMUserStatus &userStatus) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto userIDStr = (jstring) env->GetObjectField(userStatusObj, j_field_array_[FieldIDUserID]);
            if (userIDStr) {
                userStatus.userID = StringJni::Jstring2Cstring(env, userIDStr).c_str();
                env->DeleteLocalRef(userIDStr);
            }

            userStatus.statusType = V2TIMUserStatusType(env->GetIntField(userStatusObj, j_field_array_[FieldIDStatusType]));

            auto customStatusStr = (jstring) env->GetObjectField(userStatusObj, j_field_array_[FieldIDCustomStatus]);
            if (customStatusStr){
                userStatus.customStatus = StringJni::Jstring2Cstring(env,customStatusStr).c_str();
                env->DeleteLocalRef(customStatusStr);
            }
            return true;
        }
    }
}