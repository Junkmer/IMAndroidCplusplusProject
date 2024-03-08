//
// Created by EDY on 2022/9/30.
//

#include "friend_search_param_jni.h"

namespace v2im {
    namespace jni {
        jclass FriendSearchParamJni::j_cls_;
        jfieldID FriendSearchParamJni::j_field_array_[FieldIDMax];
        jmethodID FriendSearchParamJni::j_method_id_array_[MethodIDMax];

        bool FriendSearchParamJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendSearchParam");
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

            jfield = env->GetFieldID(j_cls_, "keywordList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDKeywordList] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchUserID", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchNickName", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchNickName] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSearchRemark", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDIsSearchRemark] = jfield;
            return true;
        }

        bool FriendSearchParamJni::Convert2CoreObject(jobject const &j_obj_searchParam, V2TIMFriendSearchParam &searchParam) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jobject keywordListObj = env->GetObjectField(j_obj_searchParam,j_field_array_[FieldIDKeywordList]);
            int size = ArrayListJni::Size(keywordListObj);
            for (int i = 0; i < size; ++i) {
                auto keywordJStr = (jstring) ArrayListJni::Get(keywordListObj,i);
                if (keywordJStr){
                    searchParam.keywordList.PushBack(StringJni::Jstring2Cstring(env,keywordJStr).c_str());
                    env->DeleteLocalRef(keywordJStr);
                }
            }
            env->DeleteLocalRef(keywordListObj);

            searchParam.isSearchUserID = env->GetBooleanField(j_obj_searchParam,j_field_array_[FieldIDIsSearchUserID]);
            searchParam.isSearchNickName = env->GetBooleanField(j_obj_searchParam,j_field_array_[FieldIDIsSearchNickName]);
            searchParam.isSearchRemark = env->GetBooleanField(j_obj_searchParam,j_field_array_[FieldIDIsSearchRemark]);

            return true;
        }
    }
}