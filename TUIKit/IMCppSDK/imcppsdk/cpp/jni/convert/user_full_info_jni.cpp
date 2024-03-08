//
// Created by EDY on 2022/9/16.
//

#include "user_full_info_jni.h"

#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass UserFullInfoJni::j_cls;
        jfieldID UserFullInfoJni::j_field_array_[FieldIDMax];
        jmethodID UserFullInfoJni::j_method_id_array_[MethodIDMax];

        bool UserFullInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls != nullptr) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMUserFullInfo");
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

            jfield = env->GetFieldID(j_cls, "selfSignature", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSelfSignature] = jfield;

            jfield = env->GetFieldID(j_cls, "gender", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGender] = jfield;

            jfield = env->GetFieldID(j_cls, "role", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRole] = jfield;

            jfield = env->GetFieldID(j_cls, "level", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDLevel] = jfield;

            jfield = env->GetFieldID(j_cls, "birthday", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDBirthday] = jfield;

            jfield = env->GetFieldID(j_cls, "allowType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDAllowType] = jfield;

            jfield = env->GetFieldID(j_cls, "customHashMap", "Ljava/util/HashMap;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCustomHashMap] = jfield;

            return true;
        }

        jobject UserFullInfoJni::Convert2JObject(const V2TIMUserFullInfo &userFullInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject juserFullInfoObj = env->NewObject(j_cls, j_method_id_array_[MethodIDConstruct]);
            if (!juserFullInfoObj) {
                return nullptr;
            }

            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDUserID], StringJni::Cstring2Jstring(env, userFullInfo.userID.CString()));
            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDNickname], StringJni::Cstring2Jstring(env, userFullInfo.nickName.CString()));
            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDFaceUrl], StringJni::Cstring2Jstring(env, userFullInfo.faceURL.CString()));
            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDSelfSignature],StringJni::Cstring2Jstring(env, userFullInfo.selfSignature.CString()));
            env->SetIntField(juserFullInfoObj, j_field_array_[FieldIDGender], userFullInfo.gender);
            env->SetIntField(juserFullInfoObj, j_field_array_[FieldIDRole], (jint) userFullInfo.role);
            env->SetIntField(juserFullInfoObj, j_field_array_[FieldIDLevel], (jint) userFullInfo.level);
            env->SetIntField(juserFullInfoObj, j_field_array_[FieldIDAllowType], userFullInfo.allowType);
            env->SetLongField(juserFullInfoObj, j_field_array_[FieldIDBirthday], userFullInfo.birthday);

            V2TIMStringVector vectorKeys = userFullInfo.customInfo.AllKeys();
            jobject mapObj = HashMapJni::NewHashMap();
            for (int i = 0; i < userFullInfo.customInfo.Size(); ++i) {
                V2TIMBuffer buffer = userFullInfo.customInfo.Get(vectorKeys[i]);
                jstring key = StringJni::Cstring2Jstring(env, vectorKeys[i].CString());
                jstring value = StringJni::V2TIMBuffer2Jstring(env, buffer.Data(), buffer.Size());
                HashMapJni::Put(mapObj, key, value);

                env->DeleteLocalRef(key);
                env->DeleteLocalRef(value);
            }
            env->SetObjectField(juserFullInfoObj, j_field_array_[FieldIDCustomHashMap], mapObj);

            env->DeleteLocalRef(mapObj);
            return juserFullInfoObj;
        }

        bool UserFullInfoJni::Convert2CoreObject(const jobject &j_obj_userFullInfo, V2TIMUserFullInfo &userFullInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto userID_jStr = (jstring) env->GetObjectField(j_obj_userFullInfo, j_field_array_[FieldIDUserID]);
            if (userID_jStr) {
                userFullInfo.userID = StringJni::Jstring2Cstring(env, userID_jStr).c_str();
                env->DeleteLocalRef(userID_jStr);
            }

            auto nickName_jStr = (jstring) env->GetObjectField(j_obj_userFullInfo, j_field_array_[FieldIDNickname]);
            if (nickName_jStr) {
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_NICK;
                userFullInfo.nickName = StringJni::Jstring2Cstring(env, nickName_jStr).c_str();
                env->DeleteLocalRef(nickName_jStr);
            }

            auto faceUrl_jStr = (jstring) env->GetObjectField(j_obj_userFullInfo, j_field_array_[FieldIDFaceUrl]);
            if (faceUrl_jStr) {
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_FACE_URL;
                userFullInfo.faceURL = StringJni::Jstring2Cstring(env, faceUrl_jStr).c_str();
                env->DeleteLocalRef(faceUrl_jStr);
            }

            auto selfSignature_jStr = (jstring) env->GetObjectField(j_obj_userFullInfo, j_field_array_[FieldIDSelfSignature]);
            if (selfSignature_jStr) {
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_SELF_SIGNATURE;
                userFullInfo.selfSignature = StringJni::Jstring2Cstring(env, selfSignature_jStr).c_str();
                env->DeleteLocalRef(selfSignature_jStr);
            }

            int genderInt = env->GetIntField(j_obj_userFullInfo, j_field_array_[FieldIDGender]);
            if (genderInt != IntegerJni::MIN_VALUE()){
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_GENDER;
                userFullInfo.gender = V2TIMGender(genderInt);
            }

            int roleInt = env->GetIntField(j_obj_userFullInfo, j_field_array_[FieldIDRole]);
            if (roleInt != IntegerJni::MIN_VALUE()){
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_ROLE;
                userFullInfo.role = (uint32_t)roleInt;
            }

            int levelInt = env->GetIntField(j_obj_userFullInfo, j_field_array_[FieldIDLevel]);
            if (levelInt != IntegerJni::MIN_VALUE()){
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_LEVEL;
                userFullInfo.level = (uint32_t)levelInt;
            }

            int allowTypeInt = env->GetIntField(j_obj_userFullInfo, j_field_array_[FieldIDAllowType]);
            if (allowTypeInt != IntegerJni::MIN_VALUE()){
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_ALLOW_TYPE;
                userFullInfo.allowType = V2TIMFriendAllowType(allowTypeInt);
            }

            long birthdayLong = env->GetLongField(j_obj_userFullInfo, j_field_array_[FieldIDBirthday]);
            if (birthdayLong != LongJni::MIN_VALUE()){
                userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_BIRTHDAY;
                userFullInfo.birthday = (uint32_t)birthdayLong;
            }

            jobject j_obj_customHashMap = env->GetObjectField(j_obj_userFullInfo, j_field_array_[FieldIDCustomHashMap]);
            jobject entry_set = HashMapJni::entrySet(j_obj_customHashMap);
            jobject iterator = HashMapJni::iterator(entry_set);
            while (HashMapJni::hasNext(iterator)) {
                jobject object = HashMapJni::next(iterator);
                if (nullptr == object) {
                    continue;
                }
                auto jStr_key = (jstring) HashMapJni::getKey(object);
                if (nullptr != jStr_key) {
                    userFullInfo.modifyFlag = userFullInfo.modifyFlag | V2TIM_USER_INFO_MODIFY_FLAG_CUSTOM;
                    auto jByte_value = (jbyteArray) HashMapJni::getValue(object);
                    if (nullptr != jByte_value) {
                        V2TIMString c_key_str = StringJni::Jstring2Cstring(env, jStr_key).c_str();
                        V2TIMBuffer c_value_buffer = ByteJni::JByteArray2V2TIMBuffer(env, jByte_value);
                        userFullInfo.customInfo.Insert(c_key_str, c_value_buffer);

                        env->DeleteLocalRef(jByte_value);
                    }
                    env->DeleteLocalRef(jStr_key);
                }
            }

            return true;
        }
    }
}
