//
// Created by EDY on 2022/9/30.
//

#include "topic_operation_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass TopicOperationResultJni::j_cls_;
        jfieldID TopicOperationResultJni::j_field_array_[FieldIDMax];
        jmethodID TopicOperationResultJni::j_method_id_array_[MethodIDMax];

        bool TopicOperationResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMTopicOperationResult");
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
            jfield = env->GetFieldID(j_cls_, "errorCode", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDErrorCode] = jfield;

            jfield = env->GetFieldID(j_cls_, "errorMessage", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDErrorMessage] = jfield;

            jfield = env->GetFieldID(j_cls_, "topicID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDTopicID] = jfield;

            return true;
        }

        jobject TopicOperationResultJni::Convert2JObject(const V2TIMTopicOperationResult &operationResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jObj) {
                return nullptr;
            }

            env->SetIntField(jObj, j_field_array_[FieldIDErrorCode], (jint) operationResult.errorCode);
            env->SetObjectField(jObj, j_field_array_[FieldIDErrorMessage], StringJni::Cstring2Jstring(env, operationResult.errorMsg.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDTopicID], StringJni::Cstring2Jstring(env, operationResult.topicID.CString()));

            return jObj;
        }

    }//namespace jni
}//namespace v2im