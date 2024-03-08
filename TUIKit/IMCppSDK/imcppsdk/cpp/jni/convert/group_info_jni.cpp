//
// Created by EDY on 2022/9/30.
//

#include "group_info_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupInfoJni::j_cls_;
        jfieldID GroupInfoJni::j_field_array_[FieldIDMax];
        jmethodID GroupInfoJni::j_method_id_array_[MethodIDMax];


        bool GroupInfoJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupInfo");
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

            jfield = env->GetFieldID(j_cls_, "groupType", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupType] = jfield;

            jfield = env->GetFieldID(j_cls_, "supportTopic", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSupportTopic] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupName] = jfield;

            jfield = env->GetFieldID(j_cls_, "notification", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDNotification] = jfield;

            jfield = env->GetFieldID(j_cls_, "introduction", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIntroduction] = jfield;

            jfield = env->GetFieldID(j_cls_, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "isAllMuted", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsAllMuted] = jfield;

            jfield = env->GetFieldID(j_cls_, "owner", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDOwner] = jfield;

            jfield = env->GetFieldID(j_cls_, "createTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCreateTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupAddOpt", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupAddOpt] = jfield;

            jfield = env->GetFieldID(j_cls_, "customInfo", "Ljava/util/Map;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCustomInfo] = jfield;

            jfield = env->GetFieldID(j_cls_, "lastInfoTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDLastInfoTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "lastMessageTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDLastMessageTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "memberCount", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMemberCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "onlineCount", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDOnlineCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "memberMaxCount", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMemberMaxCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "role", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRole] = jfield;

            jfield = env->GetFieldID(j_cls_, "recvOpt", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRecvOpt] = jfield;

            jfield = env->GetFieldID(j_cls_, "joinTime", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDJoinTime] = jfield;

            jfield = env->GetFieldID(j_cls_, "modifyFlag", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDModifyFlag] = jfield;

            return true;
        }

        jobject GroupInfoJni::Convert2JObject(const V2TIMGroupInfo &groupInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jObj) {
                return nullptr;
            }

            env->SetObjectField(jObj, j_field_array_[FieldIDGroupID], StringJni::Cstring2Jstring(env, groupInfo.groupID.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDGroupType], StringJni::Cstring2Jstring(env, groupInfo.groupType.CString()));
            env->SetBooleanField(jObj, j_field_array_[FieldIDSupportTopic], groupInfo.isSupportTopic);
            env->SetObjectField(jObj, j_field_array_[FieldIDGroupName], StringJni::Cstring2Jstring(env, groupInfo.groupName.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDNotification], StringJni::Cstring2Jstring(env, groupInfo.notification.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDIntroduction], StringJni::Cstring2Jstring(env, groupInfo.introduction.CString()));
            env->SetObjectField(jObj, j_field_array_[FieldIDFaceUrl], StringJni::Cstring2Jstring(env, groupInfo.faceURL.CString()));
            env->SetBooleanField(jObj, j_field_array_[FieldIDIsAllMuted], groupInfo.allMuted);
            env->SetObjectField(jObj, j_field_array_[FieldIDOwner], StringJni::Cstring2Jstring(env, groupInfo.owner.CString()));
            env->SetLongField(jObj, j_field_array_[FieldIDCreateTime], (jlong) groupInfo.createTime);
            env->SetIntField(jObj, j_field_array_[FieldIDGroupAddOpt], (jint) groupInfo.groupAddOpt);

            jobject mapObj = HashMapJni::NewHashMap();
            V2TIMStringVector keys = groupInfo.customInfo.AllKeys();
            for (int i = 0; i < groupInfo.customInfo.Size(); ++i) {
                jstring keyStr = StringJni::Cstring2Jstring(env,keys[i].CString());
                if (keyStr){
                    V2TIMBuffer buffer = groupInfo.customInfo.Get(keys[i]);
                    jobject valueByte = ByteJni::Cuint8_t2JByteArray(env,buffer.Data(),buffer.Size());
                    if (valueByte){
                        HashMapJni::Put(mapObj,keyStr,valueByte);
                        env->DeleteLocalRef(valueByte);
                    }
                    env->DeleteLocalRef(keyStr);
                }
            }
            env->SetObjectField(jObj,j_field_array_[FieldIDCustomInfo],mapObj);
            env->DeleteLocalRef(mapObj);

            env->SetLongField(jObj, j_field_array_[FieldIDLastInfoTime], (jlong) groupInfo.lastInfoTime);
            env->SetLongField(jObj, j_field_array_[FieldIDLastMessageTime], (jlong) groupInfo.lastMessageTime);
            env->SetIntField(jObj, j_field_array_[FieldIDMemberCount], (jint) groupInfo.memberCount);
            env->SetIntField(jObj, j_field_array_[FieldIDOnlineCount], (jint) groupInfo.onlineCount);
            env->SetLongField(jObj, j_field_array_[FieldIDMemberMaxCount], (jlong) groupInfo.memberMaxCount);
            env->SetIntField(jObj, j_field_array_[FieldIDRole], (jint) groupInfo.role);
            env->SetIntField(jObj, j_field_array_[FieldIDRecvOpt], (jint) groupInfo.recvOpt);
            env->SetLongField(jObj, j_field_array_[FieldIDJoinTime], (jlong) groupInfo.joinTime);
            return jObj;
        }

        bool GroupInfoJni::Convert2CoreObject(jobject const &j_obj_groupInfo, V2TIMGroupInfo &groupInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }
            
            jstring jStr = nullptr;

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDGroupID]);
            if (jStr) {
                groupInfo.groupID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDGroupType]);
            if (jStr) {
                groupInfo.groupType = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }
            
            groupInfo.isSupportTopic = env->GetBooleanField(j_obj_groupInfo, j_field_array_[FieldIDSupportTopic]);

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDGroupName]);
            if (jStr) {
                groupInfo.groupName = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDNotification]);
            if (jStr) {
                groupInfo.notification = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDIntroduction]);
            if (jStr) {
                groupInfo.introduction = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDFaceUrl]);
            if (jStr) {
                groupInfo.faceURL = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            groupInfo.allMuted = env->GetBooleanField(j_obj_groupInfo, j_field_array_[FieldIDIsAllMuted]);

            jStr = (jstring) env->GetObjectField(j_obj_groupInfo, j_field_array_[FieldIDOwner]);
            if (jStr) {
                groupInfo.allMuted = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            groupInfo.createTime = env->GetLongField(j_obj_groupInfo, j_field_array_[FieldIDCreateTime]);
            groupInfo.groupAddOpt = V2TIMGroupAddOpt(env->GetIntField(j_obj_groupInfo, j_field_array_[FieldIDGroupAddOpt]));

            jobject j_obj_customHashMap = env->GetObjectField(j_obj_groupInfo,j_field_array_[FieldIDCustomInfo]);
            jobject entry_set = HashMapJni::entrySet(j_obj_customHashMap);
            jobject iterator = HashMapJni::iterator(entry_set);
            while (HashMapJni::hasNext(iterator)) {
                jobject object = HashMapJni::next(iterator);
                if (nullptr == object) {
                    continue;
                }
                auto jStr_key = (jstring) HashMapJni::getKey(object);
                if (nullptr != jStr_key) {

                    auto jByte_value = (jbyteArray) HashMapJni::getValue(object);

                    V2TIMString c_key_str = StringJni::Jstring2Cstring(env, jStr_key).c_str();
                    V2TIMBuffer c_value_buffer = ByteJni::JByteArray2V2TIMBuffer(env, jByte_value);
                    groupInfo.customInfo.Insert(c_key_str, c_value_buffer);

                    env->DeleteLocalRef(jByte_value);
                    env->DeleteLocalRef(jStr_key);
                }
            }

            groupInfo.lastInfoTime = env->GetLongField(j_obj_groupInfo, j_field_array_[FieldIDLastInfoTime]);
            groupInfo.lastMessageTime = env->GetLongField(j_obj_groupInfo, j_field_array_[FieldIDLastMessageTime]);
            groupInfo.memberCount = env->GetIntField(j_obj_groupInfo, j_field_array_[FieldIDMemberCount]);
            groupInfo.onlineCount = env->GetIntField(j_obj_groupInfo, j_field_array_[FieldIDOnlineCount]);
            groupInfo.memberMaxCount = env->GetLongField(j_obj_groupInfo, j_field_array_[FieldIDMemberMaxCount]);
            groupInfo.role = env->GetIntField(j_obj_groupInfo, j_field_array_[FieldIDRole]);
            groupInfo.recvOpt = V2TIMReceiveMessageOpt(env->GetIntField(j_obj_groupInfo, j_field_array_[FieldIDRecvOpt]));
            groupInfo.joinTime = env->GetLongField(j_obj_groupInfo, j_field_array_[FieldIDJoinTime]);

            //群资料修改标记位
            groupInfo.modifyFlag = env->GetIntField(j_obj_groupInfo, j_field_array_[FieldIDModifyFlag]);

            return true;
        }
    }//namespace jni
}//namespace v2im