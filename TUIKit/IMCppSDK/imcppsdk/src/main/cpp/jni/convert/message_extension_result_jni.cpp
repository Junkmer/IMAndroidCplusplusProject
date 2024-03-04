//
// Created by EDY on 2023/11/2.
//

#include "message_extension_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "message_extension_jni.h"

namespace v2im {
    namespace jni {

        jclass MessageExtensionResultJni::j_cls_;
        jfieldID MessageExtensionResultJni::j_field_array_[FieldIDMax];
        jmethodID MessageExtensionResultJni::j_method_id_array[MethodIDMax];

        bool MessageExtensionResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageExtensionResult");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array[MethodIDConstructor] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_,"resultCode", "I");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDResultCode] = jfield;

            jfield = env->GetFieldID(j_cls_,"resultInfo", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDResultInfo] = jfield;

            jfield = env->GetFieldID(j_cls_,"extension", "Lcom/tencent/imsdk/v2/V2TIMMessageExtension;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDExtension] = jfield;

            return true;
        }

        jobject MessageExtensionResultJni::Convert2JObject(const V2TIMMessageExtensionResult &extensionResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject extensionResultObj = env->NewObject(j_cls_, j_method_id_array[MethodIDConstructor]);
            if (nullptr == extensionResultObj) {
                return nullptr;
            }

            env->SetIntField(extensionResultObj, j_field_array_[FieldIDResultCode], extensionResult.resultCode);

            jstring jStr;
            jStr = StringJni::Cstring2Jstring(env, extensionResult.resultInfo.CString());
            if (jStr) {
                env->SetObjectField(extensionResultObj, j_field_array_[FieldIDResultInfo], jStr);
                env->DeleteLocalRef(jStr);
            }

            jobject extensionObj = MessageExtensionJni::Convert2JObject(extensionResult.extension);
            if (extensionObj){
                env->SetObjectField(extensionResultObj, j_field_array_[FieldIDExtension], extensionObj);
                env->DeleteLocalRef(extensionObj);
            }
            return extensionResultObj;
        }
    }
}