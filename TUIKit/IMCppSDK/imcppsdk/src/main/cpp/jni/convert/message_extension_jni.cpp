//
// Created by EDY on 2023/11/2.
//

#include "message_extension_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass MessageExtensionJni::j_cls_;
        jfieldID MessageExtensionJni::j_field_array_[FieldIDMax];
        jmethodID MessageExtensionJni::j_method_id_array[MethodIDMax];

        bool MessageExtensionJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageExtension");
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
            
            jfield = env->GetFieldID(j_cls_,"extensionKey", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDExtensionKey] = jfield;

            jfield = env->GetFieldID(j_cls_,"extensionValue", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDExtensionValue] = jfield;

            return true;
        }

        jobject MessageExtensionJni::Convert2JObject(const V2TIMMessageExtension &messageExtension) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject messageExtensionObj = env->NewObject(j_cls_, j_method_id_array[MethodIDConstructor]);
            if (nullptr == messageExtensionObj) {
                return nullptr;
            }

            jstring jStr;
            jStr = StringJni::Cstring2Jstring(env, messageExtension.extensionKey.CString());
            if (jStr) {
                env->SetObjectField(messageExtensionObj, j_field_array_[FieldIDExtensionKey], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, messageExtension.extensionValue.CString());
            if (jStr) {
                env->SetObjectField(messageExtensionObj, j_field_array_[FieldIDExtensionValue], jStr);
                env->DeleteLocalRef(jStr);
            }
            
            return messageExtensionObj;
        }

        bool MessageExtensionJni::Convert2CoreObject(const jobject &j_obj_messageExtension, V2TIMMessageExtension &messageExtension) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jstring jStr;
            jStr = (jstring) env->GetObjectField(j_obj_messageExtension,j_field_array_[FieldIDExtensionKey]);
            if (jStr){
                messageExtension.extensionKey = StringJni::Jstring2Cstring(env,jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_messageExtension,j_field_array_[FieldIDExtensionValue]);
            if (jStr){
                messageExtension.extensionValue = StringJni::Jstring2Cstring(env,jStr).c_str();
                env->DeleteLocalRef(jStr);
            }
            return true;
        }
    }
}