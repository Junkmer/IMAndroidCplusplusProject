//
// Created by EDY on 2022/9/19.
//

#include "group_member_full_info_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {

        jclass GroupMemberFullInfoJNI::j_cls_;
        jfieldID GroupMemberFullInfoJNI::j_field_array_[FieldIDMax];
        jmethodID GroupMemberFullInfoJNI::j_method_id_array_[MethodIDMax];

        bool GroupMemberFullInfoJNI::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupMemberFullInfo");
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
            j_field_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "nickName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDNickName] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendRemark", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFriendRemark] = jfield;

            jfield = env->GetFieldID(j_cls_, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "role", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRole] = jfield;

            jfield = env->GetFieldID(j_cls_, "muteUntil", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMuteUntil] = jfield;

            jfield = env->GetFieldID(j_cls_, "joinTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDJoinTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "customInfo", "Ljava/util/Map;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCustomInfo] = jfield;

            jfield = env->GetFieldID(j_cls_, "modifyFlag", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDModifyFlag] = jfield;
            return true;
        }

        jobject GroupMemberFullInfoJNI::Convert2JObject(const V2TIMGroupMemberFullInfo &memberFullInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jmemberFullInfoObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);
            if (nullptr == jmemberFullInfoObj) {
                return nullptr;
            }

            env->SetObjectField(jmemberFullInfoObj, j_field_array_[FieldIDUserID], StringJni::Cstring2Jstring(env, memberFullInfo.userID.CString()));
            env->SetObjectField(jmemberFullInfoObj, j_field_array_[FieldIDNickName],
                                StringJni::Cstring2Jstring(env, memberFullInfo.nickName.CString()));
            env->SetObjectField(jmemberFullInfoObj, j_field_array_[FieldIDFriendRemark],
                                StringJni::Cstring2Jstring(env, memberFullInfo.friendRemark.CString()));
            env->SetObjectField(jmemberFullInfoObj, j_field_array_[FieldIDFaceUrl],
                                StringJni::Cstring2Jstring(env, memberFullInfo.faceURL.CString()));
            env->SetIntField(jmemberFullInfoObj, j_field_array_[FieldIDRole], (jint) memberFullInfo.role);
            env->SetLongField(jmemberFullInfoObj, j_field_array_[FieldIDMuteUntil], (jlong) memberFullInfo.muteUntil);
            env->SetLongField(jmemberFullInfoObj, j_field_array_[FieldIDJoinTime], (jlong) memberFullInfo.joinTime);

            V2TIMStringVector vectorKeys = memberFullInfo.customInfo.AllKeys();
            jobject mapObj = HashMapJni::NewHashMap();
            for (int i = 0; i < memberFullInfo.customInfo.Size(); ++i) {
                V2TIMBuffer buffer = memberFullInfo.customInfo.Get(vectorKeys[i]);
                jstring key = StringJni::Cstring2Jstring(env, vectorKeys[i].CString());
                jstring value = StringJni::Cuint8_t2Jstring(env, buffer.Data(), buffer.Size());
                HashMapJni::Put(mapObj, key, value);

                env->DeleteLocalRef(key);
                env->DeleteLocalRef(value);
            }
            env->SetObjectField(jmemberFullInfoObj, j_field_array_[FieldIDCustomInfo], mapObj);

            env->DeleteLocalRef(mapObj);

            return jmemberFullInfoObj;
        }

        bool GroupMemberFullInfoJNI::Convert2CoreObject(jobject const &j_obj_groupSearchParam, V2TIMGroupMemberFullInfo &memberFullInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto userIDJStr = (jstring) env->GetObjectField(j_obj_groupSearchParam, j_field_array_[FieldIDUserID]);
            if (userIDJStr) {
                memberFullInfo.userID = StringJni::Jstring2Cstring(env, userIDJStr).c_str();
                env->DeleteLocalRef(userIDJStr);
            }

            auto nameCardJStr = (jstring) env->GetObjectField(j_obj_groupSearchParam, j_field_array_[FieldIDUserID]);
            if (nameCardJStr) {
                memberFullInfo.modifyFlag = V2TIM_GROUP_MEMBER_INFO_MODIFY_FLAG_NAME_CARD;
                memberFullInfo.nameCard = StringJni::Jstring2Cstring(env, nameCardJStr).c_str();
                env->DeleteLocalRef(nameCardJStr);
            }

            jobject j_obj_customHashMap = env->GetObjectField(j_obj_groupSearchParam, j_field_array_[FieldIDCustomInfo]);
            if (j_obj_customHashMap){
                jobject entry_set = HashMapJni::entrySet(j_obj_customHashMap);
                jobject iterator = HashMapJni::iterator(entry_set);
                while (HashMapJni::hasNext(iterator)) {
                    jobject object = HashMapJni::next(iterator);
                    if (nullptr == object) {
                        continue;
                    }
                    auto jStr_key = (jstring) HashMapJni::getKey(object);
                    if (nullptr != jStr_key) {
                        memberFullInfo.modifyFlag = memberFullInfo.modifyFlag | V2TIM_GROUP_MEMBER_INFO_MODIFY_FLAG_CUSTOM_INFO;

                        auto jByte_value = (jbyteArray) HashMapJni::getValue(object);

                        V2TIMString c_key_str = StringJni::Jstring2Cstring(env, jStr_key).c_str();
                        V2TIMBuffer c_value_buffer = ByteJni::JByteArray2V2TIMBuffer(env, jByte_value);
                        memberFullInfo.customInfo.Insert(c_key_str, c_value_buffer);

                        env->DeleteLocalRef(jByte_value);
                        env->DeleteLocalRef(jStr_key);
                    }
                }
            }

//            memberFullInfo.role = (uint32_t) env->GetIntField(j_obj_groupSearchParam, j_field_array_[FieldIDRole]);
//            memberFullInfo.muteUntil = (uint32_t) env->GetLongField(j_obj_groupSearchParam, j_field_array_[FieldIDMuteUntil]);
//            memberFullInfo.joinTime = (uint64_t) env->GetLongField(j_obj_groupSearchParam, j_field_array_[FieldIDJoinTime]);

            //修改群成员资料标记位
//            memberFullInfo.modifyFlag = env->GetIntField(j_obj_groupSearchParam, j_field_array_[FieldIDModifyFlag]);
            return true;
        }
    }// namespace jni
}// namespace v2im
