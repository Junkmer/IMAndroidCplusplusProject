//
// Created by EDY on 2022/9/23.
//

#include <jni_helper.h>
#include "offline_push_info_jni.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass OfflinePushInfoJni::j_cls_;
        jfieldID OfflinePushInfoJni::j_field_array_[FieldIDMax];
        jmethodID OfflinePushInfoJni::j_method_id_array_[MethodIDMax];

        bool OfflinePushInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMOfflinePushInfo");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "title", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDTitle] = jfield;

            jfield = env->GetFieldID(j_cls_, "desc", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDDesc] = jfield;

            jfield = env->GetFieldID(j_cls_, "ext", "[B");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDExt] = jfield;

            jfield = env->GetFieldID(j_cls_, "disable", "Z");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDDisable] = jfield;

            jfield = env->GetFieldID(j_cls_, "IOSSound", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDIOSSound] = jfield;

            jfield = env->GetFieldID(j_cls_, "androidSound", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDAndroidSound] = jfield;

            jfield =
                    env->GetFieldID(j_cls_, "ignoreIOSBadge",
                                    "Z");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDIgnoreIOSBadge] = jfield;

            jfield = env->GetFieldID(j_cls_, "oppoChannelID", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDOppoChannelID] = jfield;


            jfield = env->GetFieldID(j_cls_, "fcmChannelID", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDFcmChannelID] = jfield;

            jfield = env->GetFieldID(j_cls_, "xiaomiChannelID", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDXiaomiChannelID] = jfield;

            jfield = env->GetFieldID(j_cls_, "vivoClassification", "I");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDVivoClassification] = jfield;

            jfield = env->GetFieldID(j_cls_, "vivoCategory", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDVivoCategory] = jfield;

            jfield = env->GetFieldID(j_cls_, "iOSPushType", "I");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDIOSPushType] = jfield;

            jfield = env->GetFieldID(j_cls_, "huaweiCategory", "Ljava/lang/String;");
            if (jfield == nullptr) {
                return false;
            }
            j_field_array_[FieldIDHuaweiCategory] = jfield;

            return true;
        }

        jobject OfflinePushInfoJni::Convert2JObject(const V2TIMOfflinePushInfo &offlinePushInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject j_pushInfoObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);

            jstring jStr = nullptr;

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.title.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDTitle], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.desc.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDDesc], jStr);
                env->DeleteLocalRef(jStr);
            }

            jbyteArray byteArr = StringJni::Cstring2JbyteArray(env, offlinePushInfo.ext.CString());
            env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDExt], byteArr);
            env->DeleteLocalRef(byteArr);

            env->SetBooleanField(j_pushInfoObj, j_field_array_[FieldIDDisable], offlinePushInfo.disablePush);

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.iOSSound.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDIOSSound], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetBooleanField(j_pushInfoObj, j_field_array_[FieldIDIgnoreIOSBadge], offlinePushInfo.ignoreIOSBadge);

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.AndroidOPPOChannelID.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDOppoChannelID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.AndroidFCMChannelID.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDFcmChannelID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.AndroidXiaoMiChannelID.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDXiaomiChannelID], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(j_pushInfoObj, j_field_array_[FieldIDVivoClassification], offlinePushInfo.AndroidVIVOClassification);

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.AndroidVIVOCategory.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDVivoCategory], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(j_pushInfoObj, j_field_array_[FieldIDIOSPushType], offlinePushInfo.iOSPushType);

            jStr = StringJni::Cstring2Jstring(env, offlinePushInfo.AndroidHuaWeiCategory.CString());
            if (jStr){
                env->SetObjectField(j_pushInfoObj, j_field_array_[FieldIDHuaweiCategory], jStr);
                env->DeleteLocalRef(jStr);
            }

            return j_pushInfoObj;
        }

        bool OfflinePushInfoJni::Convert2CoreObject(const jobject &object, V2TIMOfflinePushInfo &offlinePushInfo) {

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jstring jStr = nullptr;
            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDTitle]);
            if (jStr) {
                offlinePushInfo.title = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDDesc]);
            if (jStr) {
                offlinePushInfo.desc = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            auto byteArr = (jbyteArray)env->GetObjectField(object, j_field_array_[FieldIDExt]);
            if (byteArr){
                offlinePushInfo.ext = StringJni::JbyteArray2Cstring(env,byteArr).c_str();
                env->DeleteLocalRef(byteArr);
            }

            offlinePushInfo.disablePush = env->GetBooleanField(object, j_field_array_[FieldIDDisable]);

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDIOSSound]);
            if (jStr) {
                offlinePushInfo.iOSSound = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDAndroidSound]);
            if (jStr) {
                offlinePushInfo.AndroidSound = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            offlinePushInfo.ignoreIOSBadge = env->GetBooleanField(object, j_field_array_[FieldIDIgnoreIOSBadge]);

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDOppoChannelID]);
            if (jStr) {
                offlinePushInfo.AndroidOPPOChannelID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDFcmChannelID]);
            if (jStr) {
                offlinePushInfo.AndroidFCMChannelID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDXiaomiChannelID]);
            if (jStr) {
                offlinePushInfo.AndroidXiaoMiChannelID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            offlinePushInfo.AndroidVIVOClassification = env->GetIntField(object, j_field_array_[FieldIDVivoClassification]);

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDVivoCategory]);
            if (jStr) {
                offlinePushInfo.AndroidVIVOCategory = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            offlinePushInfo.iOSPushType = V2TIMIOSOfflinePushType(env->GetIntField(object, j_field_array_[FieldIDIOSPushType]));

            jStr = (jstring) env->GetObjectField(object, j_field_array_[FieldIDHuaweiCategory]);
            if (jStr) {
                offlinePushInfo.AndroidHuaWeiCategory = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            return true;
        }
    }// namespace jni
}// namespace v2im
 
 