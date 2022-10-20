//
// Created by EDY on 2022/9/30.
//

#include "group_member_info_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "group_member_full_info_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupMemberInfoResultJni::j_cls_;
        jfieldID GroupMemberInfoResultJni::j_field_array_[FieldIDMax];
        jmethodID GroupMemberInfoResultJni::j_method_id_array_[MethodIDMax];

        bool GroupMemberInfoResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupMemberInfoResult");
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

            jmethod = env->GetMethodID(j_cls_, "addMemberInfo", "(Lcom/tencent/imsdk/v2/V2TIMGroupMemberFullInfo;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddMemberInfo] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_, "nextSeq", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDNextSeq] = jfield;

            jfield = env->GetFieldID(j_cls_, "memberInfoList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMemberInfoList] = jfield;

            return true;
        }

        jobject GroupMemberInfoResultJni::Convert2JObject(const V2TIMGroupMemberInfoResult &memberInfoResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject jObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jObj) {
                return nullptr;
            }

            env->SetLongField(jObj, j_field_array_[FieldIDNextSeq], (jlong) memberInfoResult.nextSequence);
            for (int i = 0; i < memberInfoResult.memberInfoList.Size(); ++i) {
                jobject j_obj_memberInfo = GroupMemberFullInfoJNI::Convert2JObject(memberInfoResult.memberInfoList[i]);
                env->CallVoidMethod(jObj, j_method_id_array_[MethodIDAddMemberInfo], j_obj_memberInfo);
                env->DeleteLocalRef(j_obj_memberInfo);
            }

            return jObj;
        }

    }//namespace jni
}//namespace v2im