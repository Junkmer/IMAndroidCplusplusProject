//
// Created by EDY on 2022/9/21.
//

#include "image_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass ImageJni::j_cls_;
        jfieldID ImageJni::j_field_array_[FieldIDMax];
        jmethodID ImageJni::j_method_id_array_[MethodIDMax];

        bool ImageJni::InitIDs(JNIEnv *env) {
            if (j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMImageElem$V2TIMImage");
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

            jfield = env->GetFieldID(j_cls_, "uuid", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUuid] = jfield;

            jfield = env->GetFieldID(j_cls_, "type", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDType] = jfield;

            jfield = env->GetFieldID(j_cls_, "size", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSize] = jfield;

            jfield = env->GetFieldID(j_cls_, "width", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDWidth] = jfield;

            jfield = env->GetFieldID(j_cls_, "height", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDHeight] = jfield;

            jfield = env->GetFieldID(j_cls_, "url", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "param", "Lcom/tencent/imsdk/common/DownloadParam;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldDownloadParam] = jfield;

            return true;
        }

        jobject ImageJni::Convert2JObject(JNIEnv *env, V2TIMImage &elem,const DownloadParam &param) {

            jobject jImage = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jImage) {
                return nullptr;
            }
            env->SetObjectField(jImage, j_field_array_[FieldIDUuid], StringJni::Cstring2Jstring(env, elem.uuid.CString()));
            env->SetIntField(jImage, j_field_array_[FieldIDType], (jint) elem.type);
            env->SetIntField(jImage, j_field_array_[FieldIDSize], (jint) elem.size);
            env->SetIntField(jImage, j_field_array_[FieldIDWidth], (jint) elem.width);
            env->SetIntField(jImage, j_field_array_[FieldIDHeight], (jint) elem.height);
            env->SetObjectField(jImage, j_field_array_[FieldIDUrl], StringJni::Cstring2Jstring(env, elem.url.CString()));

            jobject j_obj_param = DownloadParamJni::Convert2JObject(param);
            if (j_obj_param){
                env->SetObjectField(jImage,j_field_array_[FieldDownloadParam], j_obj_param);
                env->DeleteLocalRef(j_obj_param);
            }

            return jImage;
        }

        bool ImageJni::Convert2CoreObject(const jobject &jElemObj, V2TIMImage &image) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto uuidStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[FieldIDUuid]);
            if (uuidStr){
                image.uuid = StringJni::Jstring2Cstring(env, uuidStr).c_str();
                env->DeleteLocalRef(uuidStr);
            }

            image.type = V2TIMImageType(env->GetIntField(jElemObj, j_field_array_[FieldIDType]));
            image.size = (uint64_t) env->GetIntField(jElemObj, j_field_array_[FieldIDSize]);
            image.width = (uint64_t) env->GetIntField(jElemObj, j_field_array_[FieldIDWidth]);
            image.height = (uint64_t) env->GetIntField(jElemObj, j_field_array_[FieldIDHeight]);

            auto urlStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[FieldIDUrl]);
            if (urlStr){
                image.uuid = StringJni::Jstring2Cstring(env, urlStr).c_str();
                env->DeleteLocalRef(urlStr);
            }
            return true;
        }

    }
}