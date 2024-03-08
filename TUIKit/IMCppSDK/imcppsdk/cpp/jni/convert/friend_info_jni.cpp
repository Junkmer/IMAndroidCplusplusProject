//
// Created by EDY on 2022/9/28.
//

#include "friend_info_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "user_full_info_jni.h"

namespace v2im {
    namespace jni {
        jclass FriendInfoJni::j_cls_;
        jfieldID FriendInfoJni::j_field_id_array_[FieldIDMax];
        jmethodID FriendInfoJni::j_method_id_array_[MethodIDMax];

        bool FriendInfoJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendInfo");
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

            jmethod = env->GetMethodID(j_cls_, "addFriendGroup", "(Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddFriendGroup] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "putFriendCustomInfo", "(Ljava/lang/String;[B)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDPutFriendCustomInfo] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendRemark", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDFriendRemark] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendAddTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDFriendAddTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendGroups", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDFriendGroups] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendCustomInfo", "Ljava/util/HashMap;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDFriendCustomInfo] = jfield;

            jfield = env->GetFieldID(j_cls_, "userFullInfo", "Lcom/tencent/imsdk/v2/V2TIMUserFullInfo;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDUserFullInfo] = jfield;

            return true;
        }

        jobject FriendInfoJni::Convert2JObject(const V2TIMFriendInfo &friendInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject friendInfoObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);
            if (nullptr == friendInfoObj) {
                return nullptr;
            }

            jstring jStr = nullptr;

            jStr = StringJni::Cstring2Jstring(env, friendInfo.userID.CString());
            if (jStr) {
                env->SetObjectField(friendInfoObj, j_field_id_array_[FieldIDUserID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, friendInfo.friendRemark.CString());
            if (jStr) {
                env->SetObjectField(friendInfoObj, j_field_id_array_[FieldIDFriendRemark], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetLongField(friendInfoObj, j_field_id_array_[FieldIDFriendAddTime], (jlong) friendInfo.friendAddTime);

            for (int i = 0; i < friendInfo.friendGroups.Size(); ++i) {
                jstring groupItem = StringJni::Cstring2Jstring(env, friendInfo.friendGroups[i].CString());
                if (groupItem) {
                    env->CallVoidMethod(friendInfoObj, j_method_id_array_[MethodIDAddFriendGroup], groupItem);
                    env->DeleteLocalRef(groupItem);
                }
            }

            V2TIMStringVector key_vector = friendInfo.friendCustomInfo.AllKeys();
            for (int i = 0; i < friendInfo.friendCustomInfo.Size(); ++i) {
                jstring keyStr = StringJni::Cstring2Jstring(env, key_vector[i].CString());
                if (keyStr) {
                    V2TIMBuffer valueBuffer = friendInfo.friendCustomInfo.Get(key_vector[i]);
                    jbyteArray valueByte = ByteJni::Cuint8_t2JByteArray(env, valueBuffer.Data(), valueBuffer.Size());
                    if (valueByte) {
                        env->CallVoidMethod(friendInfoObj, j_method_id_array_[MethodIDAddFriendGroup], keyStr, valueByte);
                        env->DeleteLocalRef(valueByte);
                    }
                    env->DeleteLocalRef(keyStr);
                }
            }

            jobject userProfileObj = UserFullInfoJni::Convert2JObject(friendInfo.userFullInfo);
            if (userProfileObj) {
                env->SetObjectField(friendInfoObj, j_field_id_array_[FieldIDUserFullInfo], userProfileObj);
                env->DeleteLocalRef(userProfileObj);
            }
            return friendInfoObj;
        }

        bool FriendInfoJni::Convert2CoreObject(const jobject &j_obj_friendInfo, V2TIMFriendInfo &friendInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto userID_jStr = (jstring) env->GetObjectField(j_obj_friendInfo, j_field_id_array_[FieldIDUserID]);
            if (userID_jStr) {
                friendInfo.userID = StringJni::Jstring2Cstring(env, userID_jStr).c_str();
                env->DeleteLocalRef(userID_jStr);
            }

            bool modify_remark_flag = false;

            auto friendRemark_jStr = (jstring) env->GetObjectField(j_obj_friendInfo, j_field_id_array_[FieldIDFriendRemark]);
            if (friendRemark_jStr) {
                modify_remark_flag = true;
                friendInfo.friendRemark = StringJni::Jstring2Cstring(env, friendRemark_jStr).c_str();
                env->DeleteLocalRef(friendRemark_jStr);
            }

            friendInfo.friendAddTime = (uint64_t) env->GetLongField(j_obj_friendInfo, j_field_id_array_[FieldIDFriendAddTime]);

            jobject friendGroupList = env->GetObjectField(j_obj_friendInfo, j_field_id_array_[FieldIDFriendGroups]);
            if (friendGroupList) {
                int size = ArrayListJni::Size(friendGroupList);
                for (int i = 0; i < size; ++i) {
                    auto friendGroupObj = (jstring) ArrayListJni::Get(friendGroupList, i);
                    friendInfo.friendGroups.PushBack(StringJni::Jstring2Cstring(env, friendGroupObj).c_str());
                    env->DeleteLocalRef(friendGroupObj);
                }
                env->DeleteLocalRef(friendGroupList);
            }

            bool modify_custom_flag = false;

            jobject j_obj_customHashMap = env->GetObjectField(j_obj_friendInfo, j_field_id_array_[FieldIDFriendCustomInfo]);
            jobject entry_set = HashMapJni::entrySet(j_obj_customHashMap);
            jobject iterator = HashMapJni::iterator(entry_set);
            while (HashMapJni::hasNext(iterator)) {
                jobject object = HashMapJni::next(iterator);
                if (nullptr == object) {
                    continue;
                }
                auto jStr_key = (jstring) HashMapJni::getKey(object);
                if (nullptr != jStr_key) {
                    modify_custom_flag = true;

                    auto jByte_value = (jbyteArray) HashMapJni::getValue(object);

                    V2TIMString c_key_str = StringJni::Jstring2Cstring(env, jStr_key).c_str();
                    V2TIMBuffer c_value_buffer = ByteJni::JByteArray2V2TIMBuffer(env, jByte_value);
                    friendInfo.friendCustomInfo.Insert(c_key_str, c_value_buffer);

                    env->DeleteLocalRef(jByte_value);
                    env->DeleteLocalRef(jStr_key);
                }
            }

            auto userFullInfo_jObj = env->GetObjectField(j_obj_friendInfo, j_field_id_array_[FieldIDUserFullInfo]);
            if (userFullInfo_jObj) {
                UserFullInfoJni::Convert2CoreObject(userFullInfo_jObj, friendInfo.userFullInfo);
                env->DeleteLocalRef(userFullInfo_jObj);
            }

            if (modify_remark_flag && modify_custom_flag) {// 判断是更新 备注 还是 自定义资料
                friendInfo.modifyFlag = V2TIM_FRIEND_INFO_MODIFY_FLAG_REMARK | V2TIM_FRIEND_INFO_MODIFY_FLAG_CUSTOM;
            } else if (modify_remark_flag) {
                friendInfo.modifyFlag = V2TIM_FRIEND_INFO_MODIFY_FLAG_REMARK;
            } else if (modify_custom_flag) {
                friendInfo.modifyFlag = V2TIM_FRIEND_INFO_MODIFY_FLAG_CUSTOM;
            }
            return true;
        }
    }// namespace jni
}// namespace v2im