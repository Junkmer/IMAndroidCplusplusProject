//
// Created by EDY on 2024/1/15.
//

#include <jni_helper.h>
#include <java_basic_jni.h>
#include "official_account_info_jni.h"

namespace v2im {
    namespace jni{

        jclass OfficialAccountInfoJni::j_cls;
        jfieldID OfficialAccountInfoJni::j_field_array_[FieldIDMax];
        jmethodID OfficialAccountInfoJni::j_method_id_array_[MethodIDMax];

        bool OfficialAccountInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls != nullptr) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMOfficialAccountInfo");
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

            jfield = env->GetFieldID(j_cls, "officialAccountID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDOfficialAccountID] = jfield;

            jfield = env->GetFieldID(j_cls, "officialAccountName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDOfficialAccountName] = jfield;

            jfield = env->GetFieldID(j_cls, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls, "ownerUserID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDOwnerUserID] = jfield;

            jfield = env->GetFieldID(j_cls, "organization", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDOrganization] = jfield;

            jfield = env->GetFieldID(j_cls, "introduction", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIntroduction] = jfield;

            jfield = env->GetFieldID(j_cls, "customData", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCustomData] = jfield;

            jfield = env->GetFieldID(j_cls, "createTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCreateTime] = jfield;

            jfield = env->GetFieldID(j_cls, "subscriberCount", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSubscriberCount] = jfield;

            jfield = env->GetFieldID(j_cls, "subscribeTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSubscribeTime] = jfield;
            return true;
        }

        jobject OfficialAccountInfoJni::Convert2JObject(const V2TIMOfficialAccountInfo &accountInfo_obj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject accountInfoObj = env->NewObject(j_cls, j_method_id_array_[MethodIDConstruct]);
            if (!accountInfoObj) {
                return nullptr;
            }
            
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDOfficialAccountID], StringJni::Cstring2Jstring(env, accountInfo_obj.officialAccountID.CString()));
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDOfficialAccountName], StringJni::Cstring2Jstring(env, accountInfo_obj.officialAccountName.CString()));
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDFaceUrl], StringJni::Cstring2Jstring(env, accountInfo_obj.faceUrl.CString()));
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDOwnerUserID], StringJni::Cstring2Jstring(env, accountInfo_obj.ownerUserID.CString()));
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDOrganization], StringJni::Cstring2Jstring(env, accountInfo_obj.organization.CString()));
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDIntroduction], StringJni::Cstring2Jstring(env, accountInfo_obj.introduction.CString()));
            env->SetObjectField(accountInfoObj, j_field_array_[FieldIDCustomData], StringJni::Cstring2Jstring(env, accountInfo_obj.customData.CString()));
            env->SetLongField(accountInfoObj,j_field_array_[FieldIDCreateTime],(jlong) accountInfo_obj.createTime);
            env->SetLongField(accountInfoObj,j_field_array_[FieldIDSubscriberCount],(jlong) accountInfo_obj.subscriberCount);
            env->SetLongField(accountInfoObj,j_field_array_[FieldIDSubscribeTime],(jlong) accountInfo_obj.subscribeTime);

            return accountInfoObj;
        }
    }// jni
} // v2im