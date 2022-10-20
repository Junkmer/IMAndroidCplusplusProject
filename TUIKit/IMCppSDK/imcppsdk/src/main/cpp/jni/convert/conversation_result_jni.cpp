//
// Created by EDY on 2022/9/29.
//

#include "conversation_result_jni.h"
#include "jni_helper.h"
#include "conversation_jni.h"

namespace v2im {
    namespace jni {
        jclass ConversationResultJni::j_cls_;
        jfieldID ConversationResultJni::j_field_array_[FieldIDMax];
        jmethodID ConversationResultJni::j_method_id_array_[MethodIDMax];

        bool ConversationResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_){
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMConversationResult");
            if (nullptr == cls){
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_,"<init>", "()V");
            if (nullptr == jmethod){
                return false;
            }
            j_method_id_array_[MethodIDConstructor] = jmethod;

            jmethod = env->GetMethodID(j_cls_,"addConversation", "(Lcom/tencent/imsdk/v2/V2TIMConversation;)V");
            if (nullptr == jmethod){
                return false;
            }
            j_method_id_array_[MethodIDAddConversation] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_,"nextSeq","J");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDNextSeq] = jfield;

            jfield = env->GetFieldID(j_cls_,"isFinished","Z");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDIsFinished] = jfield;

            jfield = env->GetFieldID(j_cls_,"conversationList","Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDConversationList] = jfield;

            return true;
        }

        jobject ConversationResultJni::Convert2JObject(const V2TIMConversationResult &conversationResult) {
            ScopedJEnv scopedJEnv;
            auto * env = scopedJEnv.GetEnv();

            if (!InitIDs(env)){
                return nullptr;
            }

            jobject conversationResultObj = env->NewObject(j_cls_,j_method_id_array_[MethodIDConstructor]);
            if (nullptr == conversationResultObj){
                return nullptr;
            }

            env->SetLongField(conversationResultObj,j_field_array_[FieldIDNextSeq],(jlong)conversationResult.nextSeq);
            env->SetBooleanField(conversationResultObj,j_field_array_[FieldIDIsFinished],conversationResult.isFinished);

            for (int i = 0; i < conversationResult.conversationList.Size(); ++i) {
                jobject conversationObj = ConversationJni::Convert2JObject(conversationResult.conversationList[i]);
                env->CallVoidMethod(conversationResultObj,j_method_id_array_[MethodIDAddConversation],conversationObj);
                env->DeleteLocalRef(conversationObj);
            }
            return conversationResultObj;
        }
    }
}