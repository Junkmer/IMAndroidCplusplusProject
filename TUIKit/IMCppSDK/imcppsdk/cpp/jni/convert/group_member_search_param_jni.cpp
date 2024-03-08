//
// Created by EDY on 2022/9/30.
//

#include "group_member_search_param_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupMemberSearchParamJni::j_cls_;
        jfieldID GroupMemberSearchParamJni::j_field_array_[FieldIDMax];
        jmethodID GroupMemberSearchParamJni::j_method_id_array_[MethodIDMax];

        bool GroupMemberSearchParamJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupMemberSearchParam");
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
            jfield = env->GetFieldID(j_cls_, "groupIDList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupIDList] = jfield;

            jfield = env->GetFieldID(j_cls_, "keywordList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDKeywordList] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchMemberUserID", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchMemberUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchMemberNickName", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchMemberNickName] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchMemberRemark", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchMemberRemark] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchMemberNameCard", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchMemberNameCard] = jfield;

            return true;
        }

        bool GroupMemberSearchParamJni::Convert2CoreObject(jobject const &j_obj_memberSearchParam, V2TIMGroupMemberSearchParam &memberSearchParam) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jobject groupIDListObj = env->GetObjectField(j_obj_memberSearchParam,j_field_array_[FieldIDGroupIDList]);
            if (groupIDListObj){
                int size = ArrayListJni::Size(groupIDListObj);
                for (int i = 0; i < size; ++i) {
                    auto groupIDStr = (jstring) ArrayListJni::Get(groupIDListObj,i);
                    memberSearchParam.groupIDList.PushBack(StringJni::Jstring2Cstring(env,groupIDStr).c_str());
                    env->DeleteLocalRef(groupIDStr);
                }
                env->DeleteLocalRef(groupIDListObj);
            }

            jobject keywordListObj = env->GetObjectField(j_obj_memberSearchParam,j_field_array_[FieldIDKeywordList]);
            if (keywordListObj){
                int size = ArrayListJni::Size(keywordListObj);
                for (int i = 0; i < size; ++i) {
                    auto keywordStr = (jstring) ArrayListJni::Get(keywordListObj,i);
                    memberSearchParam.keywordList.PushBack(StringJni::Jstring2Cstring(env,keywordStr).c_str());
                    env->DeleteLocalRef(keywordStr);
                }
                env->DeleteLocalRef(keywordListObj);
            }

            memberSearchParam.isSearchMemberUserID = env->GetBooleanField(j_obj_memberSearchParam, j_field_array_[FieldIDIsSearchMemberUserID]);
            memberSearchParam.isSearchMemberNickName = env->GetBooleanField(j_obj_memberSearchParam, j_field_array_[FieldIDIsSearchMemberNickName]);
            memberSearchParam.isSearchMemberRemark = env->GetBooleanField(j_obj_memberSearchParam, j_field_array_[FieldIDIsSearchMemberRemark]);
            memberSearchParam.isSearchMemberNameCard = env->GetBooleanField(j_obj_memberSearchParam, j_field_array_[FieldIDIsSearchMemberNameCard]);

            return true;
        }
    }//namespace jni
}//namespace v2im