//
// Created by EDY on 2022/10/8.
//

#include "message_search_param_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass MessageSearchParamJni::j_cls_;
        jfieldID MessageSearchParamJni::j_field_array_[FieldIDMax];
        jmethodID MessageSearchParamJni::j_method_id_array_[MethodIDMax];

        bool MessageSearchParamJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageSearchParam");
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
            jfield = env->GetFieldID(j_cls_, "conversationID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDConversationID] = jfield;

            jfield = env->GetFieldID(j_cls_, "keywordList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDKeywordList] = jfield;

            jfield = env->GetFieldID(j_cls_, "type", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDType] = jfield;

            jfield = env->GetFieldID(j_cls_, "userIDList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDUserIDList] = jfield;

            jfield = env->GetFieldID(j_cls_, "messageTypeList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMessageTypeList] = jfield;

            jfield = env->GetFieldID(j_cls_, "searchTimePosition", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSearchTimePosition] = jfield;

            jfield = env->GetFieldID(j_cls_, "searchTimePeriod", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDSearchTimePeriod] = jfield;

            jfield = env->GetFieldID(j_cls_, "pageSize", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDPageSize] = jfield;

            jfield = env->GetFieldID(j_cls_, "pageIndex", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDPageIndex] = jfield;

            return true;
        }

        bool MessageSearchParamJni::Convert2CoreObject(jobject const &j_obj_searchParam, V2TIMMessageSearchParam &searchParam) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            jstring jStr = nullptr;
            jStr = (jstring) env->GetObjectField(j_obj_searchParam, j_field_array_[FieldIDConversationID]);
            if (jStr) {
                searchParam.conversationID = StringJni::Jstring2Cstring(env, jStr).c_str();
                env->DeleteLocalRef(jStr);
            }

            jobject j_obj_keywordList = env->GetObjectField(j_obj_searchParam, j_field_array_[FieldIDKeywordList]);
            int size;
            size = ArrayListJni::Size(j_obj_keywordList);
            for (int i = 0; i < size; ++i) {
                auto j_str_keyword = (jstring) ArrayListJni::Get(j_obj_keywordList, i);
                V2TIMString keywordStr = StringJni::Jstring2Cstring(env, j_str_keyword).c_str();
                searchParam.keywordList.PushBack(keywordStr);
                env->DeleteLocalRef(j_str_keyword);
            }
            env->DeleteLocalRef(j_obj_keywordList);

            searchParam.keywordListMatchType = V2TIMKeywordListMatchType(env->GetIntField(j_obj_searchParam, j_field_array_[FieldIDType]));

            jobject j_obj_userIDList = env->GetObjectField(j_obj_searchParam, j_field_array_[FieldIDUserIDList]);
            size = ArrayListJni::Size(j_obj_userIDList);
            for (int i = 0; i < size; ++i) {
                auto j_str_userID = (jstring) ArrayListJni::Get(j_obj_keywordList, i);
                V2TIMString keywordStr = StringJni::Jstring2Cstring(env, j_str_userID).c_str();
                searchParam.keywordList.PushBack(keywordStr);
                env->DeleteLocalRef(j_str_userID);
            }
            env->DeleteLocalRef(j_obj_userIDList);

            jobject j_obj_messageTypeList = env->GetObjectField(j_obj_searchParam, j_field_array_[FieldIDMessageTypeList]);
            size = ArrayListJni::Size(j_obj_messageTypeList);
            for (int i = 0; i < size; ++i) {
                int messageType = IntegerJni::IntValue(ArrayListJni::Get(j_obj_messageTypeList, i));
                searchParam.messageTypeList.PushBack(V2TIMElemType(messageType));
            }
            env->DeleteLocalRef(j_obj_messageTypeList);

            searchParam.searchTimePosition = (uint32_t) env->GetLongField(j_obj_searchParam, j_field_array_[FieldIDSearchTimePosition]);
            searchParam.searchTimePeriod = (uint32_t) env->GetLongField(j_obj_searchParam, j_field_array_[FieldIDSearchTimePeriod]);
            searchParam.pageSize = (uint32_t) env->GetIntField(j_obj_searchParam, j_field_array_[FieldIDPageSize]);
            searchParam.pageIndex = (uint32_t) env->GetIntField(j_obj_searchParam, j_field_array_[FieldIDPageIndex]);

            return true;
        }

    }// namespace jni
}// namespace v2im