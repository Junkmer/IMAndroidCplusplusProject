//
// Created by EDY on 2022/10/8.
//

#include "message_search_result_item_jni.h"

#include "jni_helper.h"
#include "java_basic_jni.h"
#include "message_jni.h"

namespace v2im {
    namespace jni {
        jclass MessageSearchResultItemJni::j_cls_;
        jfieldID MessageSearchResultItemJni::j_field_array_[FieldIDMax];
        jmethodID MessageSearchResultItemJni::j_method_id_array_[MethodIDMax];

        bool MessageSearchResultItemJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageSearchResultItem");
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

            jmethod = env->GetMethodID(j_cls_, "addMessage", "(Lcom/tencent/imsdk/v2/V2TIMMessage;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddMessage] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_, "conversationID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDConversationID] = jfield;

            jfield = env->GetFieldID(j_cls_, "messageCount", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMessageCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "messageList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMessageList] = jfield;

            return true;
        }

        jobject MessageSearchResultItemJni::Convert2JObject(const V2TIMMessageSearchResultItem &searchResultItem) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject j_obj_searchResultItem = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!j_obj_searchResultItem) {
                return nullptr;
            }

            jstring j_str_conversationID = StringJni::Cstring2Jstring(env, searchResultItem.conversationID.CString());
            if (j_str_conversationID){
                env->SetObjectField(j_obj_searchResultItem, j_field_array_[FieldIDConversationID], j_str_conversationID);
                env->DeleteLocalRef(j_str_conversationID);
            }

            env->SetIntField(j_obj_searchResultItem, j_field_array_[FieldIDMessageCount], (jint) searchResultItem.messageCount);

            for (int i = 0; i < searchResultItem.messageList.Size(); ++i) {
                jobject j_obj_message = MessageJni::Convert2JObject(searchResultItem.messageList[i]);
                env->CallVoidMethod(j_obj_searchResultItem,j_method_id_array_[MethodIDAddMessage],j_obj_message);
                env->DeleteLocalRef(j_obj_message);
            }

            return j_obj_searchResultItem;
        }
    }// namespace jni
}// namespace v2im