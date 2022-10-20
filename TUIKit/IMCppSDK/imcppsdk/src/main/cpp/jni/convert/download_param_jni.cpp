//
// Created by EDY on 2022/10/18.
//

#include "download_param_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass DownloadParamJni::j_cls_;
        jfieldID DownloadParamJni::j_field_array_[FieldIDMax];
        jmethodID DownloadParamJni::j_method_id_array_[MethodIDMax];

        bool DownloadParamJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/common/DownloadParam");
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
            jfield = env->GetFieldID(j_cls_, "roleTypeID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRoleTypeID] = jfield;

            jfield = env->GetFieldID(j_cls_, "messageID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMessageID] = jfield;

            jfield = env->GetFieldID(j_cls_, "sequence", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSequence] = jfield;

            jfield = env->GetFieldID(j_cls_, "elemType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDElemType] = jfield;

            return true;
        }

        jobject DownloadParamJni::Convert2JObject(const DownloadParam &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject j_obj_param = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!j_obj_param) {
                return nullptr;
            }

            jstring jStr = nullptr;

            jStr = StringJni::Cstring2Jstring(env, param.roleTypeID.CString());
            if (jStr) {
                env->SetObjectField(j_obj_param, j_field_array_[FieldIDRoleTypeID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, param.messageID.CString());
            if (jStr) {
                env->SetObjectField(j_obj_param, j_field_array_[FieldIDMessageID], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetLongField(j_obj_param, j_field_array_[FieldIDSequence], (jlong) param.sequence);
            env->SetIntField(j_obj_param, j_field_array_[FieldIDElemType], (jint) param.elemType);
            return j_obj_param;
        }

        bool DownloadParamJni::Convert2CoreObject(const jobject &j_obj_param, DownloadParam &param) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jstring jStr = nullptr;

            jStr = (jstring) env->GetObjectField(j_obj_param, j_field_array_[FieldIDRoleTypeID]);
            if (jStr) {
                param.roleTypeID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_param, j_field_array_[FieldIDMessageID]);
            if (jStr) {
                param.messageID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            param.sequence = (uint64_t) env->GetLongField(j_obj_param, j_field_array_[FieldIDSequence]);
            param.elemType = (uint32_t) env->GetIntField(j_obj_param, j_field_array_[FieldIDElemType]);
            return true;
        }
    }
}