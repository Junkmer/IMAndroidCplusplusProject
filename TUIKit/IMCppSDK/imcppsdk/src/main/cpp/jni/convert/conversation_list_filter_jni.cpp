//
// Created by Junker on 2022/9/29.
//

#include <jni_helper.h>
#include "conversation_list_filter_jni.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass ConversationListFilterJni::j_cls_;
        jfieldID ConversationListFilterJni::j_field_array_[FieldIDMax];
        jmethodID ConversationListFilterJni::j_method_id_array_[MethodIDMax];

        bool ConversationListFilterJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMConversationListFilter");
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

            jfield = env->GetFieldID(j_cls_, "conversationType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDConversationType] = jfield;

            jfield = env->GetFieldID(j_cls_, "nextSeq", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDNextSeq] = jfield;

            jfield = env->GetFieldID(j_cls_, "count", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "markType", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMarkType] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDGroupName] = jfield;

            return true;
        }

        jobject ConversationListFilterJni::Convert2JObject(const V2TIMConversationListFilter &listFilter) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject listFilterObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (nullptr == listFilterObj) {
                return nullptr;
            }

            env->SetIntField(listFilterObj, j_field_array_[FieldIDConversationType], (jint) listFilter.type);
            env->SetLongField(listFilterObj, j_field_array_[FieldIDNextSeq], (jlong) listFilter.nextSeq);
            env->SetIntField(listFilterObj, j_field_array_[FieldIDCount], (jint) listFilter.count);
            env->SetLongField(listFilterObj, j_field_array_[FieldIDMarkType], (jlong) listFilter.markType);

            jstring groupName = StringJni::Cstring2Jstring(env, listFilter.groupName.CString());
            if (groupName) {
                env->SetObjectField(listFilterObj, j_field_array_[FieldIDGroupName], groupName);
                env->DeleteLocalRef(groupName);
            }

            return listFilterObj;
        }

        bool ConversationListFilterJni::Convert2CoreObject(const jobject &filterObj, V2TIMConversationListFilter &listFilter) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            listFilter.type = V2TIMConversationType(env->GetIntField(filterObj, j_field_array_[FieldIDConversationType]));
            listFilter.nextSeq = (uint64_t) env->GetLongField(filterObj, j_field_array_[FieldIDNextSeq]);
            listFilter.count = (uint32_t) env->GetIntField(filterObj, j_field_array_[FieldIDCount]);
            listFilter.markType = (uint64_t) env->GetLongField(filterObj, j_field_array_[FieldIDMarkType]);

            auto jStr = (jstring) env->GetObjectField(filterObj,j_field_array_[FieldIDGroupName]);
            if (jStr){
                listFilter.groupName = StringJni::Jstring2Cstring(env,jStr).c_str();
                env->DeleteLocalRef(jStr);
            }
            return true;
        }
    }
}