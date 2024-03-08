//
// Created by EDY on 2023/11/2.
//

#include "user_info_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass UserInfoJni::j_cls;
        jfieldID UserInfoJni::j_field_array_[FieldIDMax];
        jmethodID UserInfoJni::j_method_id_array_[MethodIDMax];

        bool UserInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls != nullptr) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMUserInfo");
            if (nullptr == cls) {
                return false;
            }

            j_cls = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls, "nickName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDNickname] = jfield;

            jfield = env->GetFieldID(j_cls, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFaceUrl] = jfield;


            jfield = env->GetFieldID(j_cls, "birthday", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDBirthday] = jfield;

            return true;
        }

        jobject UserInfoJni::Convert2JObject(const V2TIMUserInfo &userInfo_obj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject juserFullInfoObj = env->NewObject(j_cls, j_method_id_array_[MethodIDConstruct]);
            if (!juserFullInfoObj) {
                return nullptr;
            }

            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDUserID], StringJni::Cstring2Jstring(env, userInfo_obj.userID.CString()));
            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDNickname], StringJni::Cstring2Jstring(env, userInfo_obj.nickName.CString()));
            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDFaceUrl], StringJni::Cstring2Jstring(env, userInfo_obj.faceURL.CString()));

            //TODO:im c++ sdk 获取消息回应回调中，用户资料中缺少 birthDay 字段
//            env->SetLongField(juserFullInfoObj, j_field_array_[FieldIDBirthday], userFullInfo_json_obj[kTIMUserProfileBirthDay].ToInt64());
            return juserFullInfoObj;
        }

    }
}
