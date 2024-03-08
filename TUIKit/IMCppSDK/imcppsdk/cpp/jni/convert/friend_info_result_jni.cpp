//
// Created by EDY on 2022/9/30.
//

#include "friend_info_result_jni.h"
#include <jni_helper.h>
#include "java_basic_jni.h"
#include "friend_info_jni.h"

namespace v2im {
    namespace jni {
        jclass FriendInfoResultJni::j_cls_;
        jfieldID FriendInfoResultJni::j_field_array_[FieldIDMax];
        jmethodID FriendInfoResultJni::j_method_id_array_[MethodIDMax];

        bool FriendInfoResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendInfoResult");
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

            jfield = env->GetFieldID(j_cls_, "relation", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRelation] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendInfo", "Lcom/tencent/imsdk/v2/V2TIMFriendInfo;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFriendInfo] = jfield;

            return true;
        }

        jobject FriendInfoResultJni::Convert2JObject(const V2TIMFriendInfoResult &friendInfoResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject friendInfoResultObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (nullptr == friendInfoResultObj) {
                return nullptr;
            }

            env->SetIntField(friendInfoResultObj, j_field_array_[FieldIDResultCode], (jint) friendInfoResult.resultCode);

            jstring resultInfo_jStr = StringJni::Cstring2Jstring(env, friendInfoResult.resultInfo.CString());
            if (resultInfo_jStr) {
                env->SetObjectField(friendInfoResultObj, j_field_array_[FieldIDResultInfo], resultInfo_jStr);
                env->DeleteLocalRef(resultInfo_jStr);
            }

            env->SetIntField(friendInfoResultObj, j_field_array_[FieldIDRelation], (jint) friendInfoResult.relation);

            jobject friendInfoObj = FriendInfoJni::Convert2JObject(friendInfoResult.friendInfo);
            if (friendInfoObj){
                env->SetObjectField(friendInfoResultObj,j_field_array_[FieldIDFriendInfo],friendInfoObj);
                env->DeleteLocalRef(friendInfoObj);
            }
            return friendInfoResultObj;
        }

    }
}