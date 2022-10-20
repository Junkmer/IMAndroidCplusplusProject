//
// Created by Junker on 2022/9/22.
//

#include <jni_helper.h>
#include "java_basic_jni.h"
#include "group_member_change_info_jni.h"

namespace v2im {
    namespace jni {

        jclass GroupMemberChangeInfoJni::j_cls_;
        jfieldID GroupMemberChangeInfoJni::j_field_id_array_[FieldIDMax];
        jmethodID GroupMemberChangeInfoJni::j_method_id_array_[MethodIDMax];

        bool GroupMemberChangeInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupMemberChangeInfo");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "muteTime", "J");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDMuteTime] = jfield;

            return true;
        }

        jobject GroupMemberChangeInfoJni::Convert2JObject(const V2TIMGroupMemberChangeInfo &groupMemberChangeInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject changeItemObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);
            if (!changeItemObj) {
                return nullptr;
            }

            env->SetObjectField(changeItemObj, j_field_id_array_[FieldIDUserID],StringJni::Cstring2Jstring(env,groupMemberChangeInfo.userID.CString()));
            env->SetLongField(changeItemObj, j_field_id_array_[FieldIDMuteTime], (jlong)groupMemberChangeInfo.muteTime);

            return changeItemObj;
        }
    }
}