//
// Created by EDY on 2022/9/30.
//

#include "group_application_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupApplicationJni::j_cls_;
        jfieldID GroupApplicationJni::j_field_array_[FieldIDMax];
        jmethodID GroupApplicationJni::j_method_id_array_[MethodIDMax];


        bool GroupApplicationJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupApplication");
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
            jfield = env->GetFieldID(j_cls_, "groupID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupID] = jfield;

            jfield = env->GetFieldID(j_cls_, "fromUser", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFromUser] = jfield;

            jfield = env->GetFieldID(j_cls_, "fromUserNickName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFromUserNickName] = jfield;

            jfield = env->GetFieldID(j_cls_, "fromUserFaceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFromUserFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "toUser", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDToUser] = jfield;

            jfield = env->GetFieldID(j_cls_, "addTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDAddTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "requestMsg", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRequestMsg] = jfield;

            jfield = env->GetFieldID(j_cls_, "handledMsg", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDHandledMsg] = jfield;

            jfield = env->GetFieldID(j_cls_, "type", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDType] = jfield;

            jfield = env->GetFieldID(j_cls_, "handleStatus", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDHandleStatus] = jfield;

            jfield = env->GetFieldID(j_cls_, "handleResult", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDHandleResult] = jfield;

            return true;
        }
        
        jobject GroupApplicationJni::Convert2JObject(const V2TIMGroupApplication &groupApplication) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jObj) {
                return nullptr;
            }

            env->SetObjectField(jObj, j_field_array_[FieldIDGroupID], StringJni::Cstring2Jstring(env, groupApplication.groupID.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDFromUser], StringJni::Cstring2Jstring(env, groupApplication.fromUserFaceUrl.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDFromUserNickName], StringJni::Cstring2Jstring(env, groupApplication.fromUserNickName.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDFromUserFaceUrl], StringJni::Cstring2Jstring(env, groupApplication.fromUserFaceUrl.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDToUser], StringJni::Cstring2Jstring(env, groupApplication.toUser.CString()));
            env->SetLongField(jObj, j_field_array_[FieldIDAddTime], (jlong) groupApplication.addTime);
            env->SetObjectField(jObj, j_field_array_[FieldIDRequestMsg], StringJni::Cstring2Jstring(env, groupApplication.requestMsg.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDHandledMsg], StringJni::Cstring2Jstring(env, groupApplication.handledMsg.CString()));
            env->SetIntField(jObj, j_field_array_[FieldIDType], (jint) groupApplication.getType);
            env->SetIntField(jObj, j_field_array_[FieldIDType], (jint) groupApplication.handleStatus);
            env->SetIntField(jObj, j_field_array_[FieldIDType], (jint) groupApplication.handleResult);

            return jObj;
        }

        bool GroupApplicationJni::Convert2CoreObject(jobject const &j_obj_groupApplication, V2TIMGroupApplication &groupApplication) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jstring jStr = nullptr;
            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDGroupID]);
            if (jStr) {
                groupApplication.groupID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDFromUser]);
            if (jStr) {
                groupApplication.fromUser = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDFromUserNickName]);
            if (jStr) {
                groupApplication.fromUserNickName = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDFromUserFaceUrl]);
            if (jStr) {
                groupApplication.fromUserFaceUrl = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDToUser]);
            if (jStr) {
                groupApplication.toUser = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            groupApplication.addTime = env->GetLongField(j_obj_groupApplication, j_field_array_[FieldIDAddTime]);

            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDRequestMsg]);
            if (jStr) {
                groupApplication.requestMsg = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupApplication, j_field_array_[FieldIDHandledMsg]);
            if (jStr) {
                groupApplication.handledMsg = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            groupApplication.getType = V2TIMGroupApplicationGetType(env->GetIntField(j_obj_groupApplication, j_field_array_[FieldIDType]));
            groupApplication.handleStatus = V2TIMGroupApplicationHandleStatus(env->GetIntField(j_obj_groupApplication, j_field_array_[FieldIDHandleStatus]));
            groupApplication.handleResult = V2TIMGroupApplicationHandleResult(env->GetIntField(j_obj_groupApplication, j_field_array_[FieldIDHandleResult]));
            
            return true;
        }
    }//namespace jni
}//namespace v2im