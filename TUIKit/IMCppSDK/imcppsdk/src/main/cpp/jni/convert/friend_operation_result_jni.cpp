//
// Created by EDY on 2022/9/30.
//

#include "friend_operation_result_jni.h"
#include <jni_helper.h>
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass FriendOperationResultJni::j_cls_;
        jfieldID FriendOperationResultJni::j_field_array_[FieldIDMax];
        jmethodID FriendOperationResultJni::j_method_id_array_[MethodIDMax];

        bool FriendOperationResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendOperationResult");
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

            jfield = env->GetFieldID(j_cls_, "resultCode", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDResultCode] = jfield;

            jfield = env->GetFieldID(j_cls_, "resultInfo", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDResultInfo] = jfield;
            return true;
        }

        jobject FriendOperationResultJni::Convert2JObject(const V2TIMFriendOperationResult &operationResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject operationResultObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (nullptr == operationResultObj) {
                return nullptr;
            }

            jstring userID_jStr = StringJni::Cstring2Jstring(env, operationResult.userID.CString());
            if (userID_jStr) {
                env->SetObjectField(operationResultObj, j_field_array_[FieldIDResultInfo], userID_jStr);
                env->DeleteLocalRef(userID_jStr);
            }

            env->SetIntField(operationResultObj, j_field_array_[FieldIDResultCode], (jint) operationResult.resultCode);

            jstring resultInfo_jStr = StringJni::Cstring2Jstring(env, operationResult.resultInfo.CString());
            if (resultInfo_jStr) {
                env->SetObjectField(operationResultObj, j_field_array_[FieldIDResultInfo], resultInfo_jStr);
                env->DeleteLocalRef(resultInfo_jStr);
            }

            return operationResultObj;
        }
    }// namespace jni
}// namespace v2im