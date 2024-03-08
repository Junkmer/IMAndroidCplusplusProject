//
// Created by EDY on 2022/9/30.
//

#include "group_member_operation_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupMemberOperationResultJni::j_cls_;
        jfieldID GroupMemberOperationResultJni::j_field_array_[FieldIDMax];
        jmethodID GroupMemberOperationResultJni::j_method_id_array_[MethodIDMax];

        bool GroupMemberOperationResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupMemberOperationResult");
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
            jfield = env->GetFieldID(j_cls_, "memberID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMemberID] = jfield;

            jfield = env->GetFieldID(j_cls_, "result", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDResult] = jfield;

            return true;
        }

        jobject GroupMemberOperationResultJni::Convert2JObject(const V2TIMGroupMemberOperationResult &operationResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jObj) {
                return nullptr;
            }

            env->SetObjectField(jObj, j_field_array_[FieldIDMemberID], StringJni::Cstring2Jstring(env, operationResult.userID.CString()));
            env->SetIntField(jObj, j_field_array_[FieldIDResult], (jint) operationResult.result);

            return jObj;
        }

    }//namespace jni
}//namespace v2im