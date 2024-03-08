//
// Created by EDY on 2022/9/30.
//

#include "create_group_member_info_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
         jclass CreateGroupMemberInfoJni::j_cls_;
         jfieldID CreateGroupMemberInfoJni::j_field_array_[FieldIDMax];
         jmethodID CreateGroupMemberInfoJni::j_method_id_array_[MethodIDMax];

        bool CreateGroupMemberInfoJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMCreateGroupMemberInfo");
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

            jfield = env->GetFieldID(j_cls_, "role", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDRole] = jfield;

            return true;
        }

        bool CreateGroupMemberInfoJni::Convert2CoreObject(jobject const &j_obj_createMemberInfo, V2TIMCreateGroupMemberInfo &createMemberInfo) {

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto userIDStr = (jstring) env->GetObjectField(j_obj_createMemberInfo, j_field_array_[FieldIDUserID]);
            if (userIDStr) {
                createMemberInfo.userID = StringJni::Jstring2Cstring(env, userIDStr).c_str();
                env->DeleteLocalRef(userIDStr);
            }

            createMemberInfo.role =(uint32_t) env->GetIntField(j_obj_createMemberInfo, j_field_array_[FieldIDRole]);
            return true;
        }
    }//namespace jni
}//namespace v2im