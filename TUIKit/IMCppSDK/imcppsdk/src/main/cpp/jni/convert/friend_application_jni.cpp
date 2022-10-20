//
// Created by EDY on 2022/9/28.
//

#include "friend_application_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass FriendApplicationJni::j_cls_;
        jfieldID FriendApplicationJni::j_field_id_array_[FieldIDMax];
        jmethodID FriendApplicationJni::j_method_id_array_[MethodIDMax];

        bool FriendApplicationJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendApplication");
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
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "nickname", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDNickname] = jfield;

            jfield = env->GetFieldID(j_cls_, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "addTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDAddTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "addSource", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDAddSource] = jfield;

            jfield = env->GetFieldID(j_cls_, "addWording", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDAddWording] = jfield;

            jfield = env->GetFieldID(j_cls_, "type", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDType] = jfield;

            return true;
        }

        jobject FriendApplicationJni::Convert2JObject(const V2TIMFriendApplication &application) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject applicationObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);
            if (nullptr == applicationObj) {
                return nullptr;
            }

            jstring jStr = nullptr;

            jStr = StringJni::Cstring2Jstring(env, application.userID.CString());
            if (jStr) {
                env->SetObjectField(applicationObj, j_field_id_array_[FieldIDUserID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, application.nickName.CString());
            if (jStr) {
                env->SetObjectField(applicationObj, j_field_id_array_[FieldIDNickname], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, application.faceUrl.CString());
            if (jStr) {
                env->SetObjectField(applicationObj, j_field_id_array_[FieldIDFaceUrl], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetLongField(applicationObj, j_field_id_array_[FieldIDAddTime], (jlong) application.addTime);

            jStr = StringJni::Cstring2Jstring(env, application.addSource.CString());
            if (jStr) {
                env->SetObjectField(applicationObj, j_field_id_array_[FieldIDAddSource], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, application.addWording.CString());
            if (jStr) {
                env->SetObjectField(applicationObj, j_field_id_array_[FieldIDAddWording], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(applicationObj, j_field_id_array_[FieldIDType], (jint) application.type);

            return applicationObj;
        }

        bool FriendApplicationJni::Convert2CoreObject(const jobject &j_obj_application, V2TIMFriendApplication &application) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }
            jstring jStr = nullptr;

            jStr = (jstring) env->GetObjectField(j_obj_application, j_field_id_array_[FieldIDUserID]);
            if (jStr) {
                application.userID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_application, j_field_id_array_[FieldIDNickname]);
            if (jStr) {
                application.nickName = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_application, j_field_id_array_[FieldIDFaceUrl]);
            if (jStr) {
                application.faceUrl = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            application.addTime = (uint64_t) env->GetLongField(j_obj_application, j_field_id_array_[FieldIDAddTime]);

            jStr = (jstring) env->GetObjectField(j_obj_application, j_field_id_array_[FieldIDAddSource]);
            if (jStr) {
                application.addSource = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_application, j_field_id_array_[FieldIDAddWording]);
            if (jStr) {
                application.addWording = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            application.type = V2TIMFriendApplicationType(env->GetIntField(j_obj_application, j_field_id_array_[FieldIDType]));
            return true;
        }
    }// namespace jni
}// namespace v2im