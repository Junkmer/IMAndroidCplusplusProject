//
// Created by Junker on 2022/9/22.
//

#include <jni_helper.h>
#include "group_change_info_jni.h"

#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass GroupChangeInfoJni::j_cls_;
        jfieldID GroupChangeInfoJni::j_field_id_array_[FieldIDMax];
        jmethodID GroupChangeInfoJni::j_method_id_array_[MethodIDMax];
        
        bool GroupChangeInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupChangeInfo");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass)env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "type", "I");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDType] = jfield;

            jfield = env->GetFieldID(j_cls_, "value", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDValue] = jfield;

            jfield = env->GetFieldID(j_cls_, "boolValue", "Z");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDBoolValue] = jfield;

            jfield = env->GetFieldID(j_cls_, "intValue", "I");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDIntValue] = jfield;

            jfield = env->GetFieldID(j_cls_, "key", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_id_array_[FieldIDKey] = jfield;

            return true;
        }

        jobject GroupChangeInfoJni::Convert2JObject(const V2TIMGroupChangeInfo &groupChangeInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject changeItemObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);
            if (!changeItemObj) {
                return nullptr;
            }

            env->SetIntField(changeItemObj, j_field_id_array_[FieldIDType],(jint)(groupChangeInfo.type));
            env->SetObjectField(changeItemObj, j_field_id_array_[FieldIDValue],StringJni::Cstring2Jstring(env,groupChangeInfo.value.CString()));
            env->SetBooleanField(changeItemObj, j_field_id_array_[FieldIDBoolValue], groupChangeInfo.boolValue);
            env->SetIntField(changeItemObj, j_field_id_array_[FieldIDIntValue],(jint)(groupChangeInfo.intValue));
            env->SetObjectField(changeItemObj, j_field_id_array_[FieldIDKey],StringJni::Cstring2Jstring(env,groupChangeInfo.key.CString()));
            
            return changeItemObj;
        }
    }
}