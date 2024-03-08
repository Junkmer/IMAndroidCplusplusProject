//
// Created by EDY on 2022/9/30.
//

#include "friend_check_result_jni.h"
#include <jni_helper.h>
#include "java_basic_jni.h"
#include "friend_info_jni.h"

namespace v2im {
    namespace jni {
        jclass FriendCheckResultJni::j_cls_;
        jfieldID FriendCheckResultJni::j_field_array_[FieldIDMax];
        jmethodID FriendCheckResultJni::j_method_id_array_[MethodIDMax];

        bool FriendCheckResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendCheckResult");
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

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "resultCode", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDResultCode] = jfield;

            jfield = env->GetFieldID(j_cls_, "resultInfo", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDResultInfo] = jfield;

            jfield = env->GetFieldID(j_cls_, "resultType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDResultType] = jfield;

            return true;
        }

        jobject FriendCheckResultJni::Convert2JObject(const V2TIMFriendCheckResult &friendCheckResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject friendInfoResultObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (nullptr == friendInfoResultObj) {
                return nullptr;
            }

            jstring userID_jStr = StringJni::Cstring2Jstring(env, friendCheckResult.userID.CString());
            if (userID_jStr) {
                env->SetObjectField(friendInfoResultObj, j_field_array_[FieldIDUserID], userID_jStr);
                env->DeleteLocalRef(userID_jStr);
            }

            env->SetIntField(friendInfoResultObj, j_field_array_[FieldIDResultCode], (jint) friendCheckResult.resultCode);

            jstring resultInfo_jStr = StringJni::Cstring2Jstring(env, friendCheckResult.resultInfo.CString());
            if (resultInfo_jStr) {
                env->SetObjectField(friendInfoResultObj, j_field_array_[FieldIDResultInfo], resultInfo_jStr);
                env->DeleteLocalRef(resultInfo_jStr);
            }

            env->SetIntField(friendInfoResultObj, j_field_array_[FieldIDResultType], (jint) friendCheckResult.relationType);
            return friendInfoResultObj;
        }
    }
}