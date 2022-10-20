//
// Created by EDY on 2022/9/30.
//

#include "group_application_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "group_application_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupApplicationResultJni::j_cls_;
        jfieldID GroupApplicationResultJni::j_field_array_[FieldIDMax];
        jmethodID GroupApplicationResultJni::j_method_id_array_[MethodIDMax];

        bool GroupApplicationResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupApplicationResult");
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

            jmethod = env->GetMethodID(j_cls_, "addGroupApplication", "(Lcom/tencent/imsdk/v2/V2TIMGroupApplication;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddGroupApplication] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_, "unreadCount", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUnreadCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupApplicationList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupApplicationList] = jfield;

            return true;
        }

        jobject GroupApplicationResultJni::Convert2JObject(const V2TIMGroupApplicationResult &applicationResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jObj) {
                return nullptr;
            }


            env->SetIntField(jObj, j_field_array_[FieldIDUnreadCount], (jint) applicationResult.unreadCount);

            for (int i = 0; i < applicationResult.applicationList.Size(); ++i) {
                jobject j_obj_application = GroupApplicationJni::Convert2JObject(applicationResult.applicationList[i]);
                env->CallVoidMethod(jObj,j_method_id_array_[MethodIDAddGroupApplication],j_obj_application);
                env->DeleteLocalRef(j_obj_application);
            }
            return jObj;
        }

    }//namespace jni
}//namespace v2im