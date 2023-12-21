//
// Created by EDY on 2023/11/2.
//

#include "message_reaction_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "message_reaction_jni.h"

namespace v2im {
    namespace jni {

        jclass MessageReactionResultJni::j_cls_;
        jfieldID MessageReactionResultJni::j_field_array_[FieldIDMax];
        jmethodID MessageReactionResultJni::j_method_id_array[MethodIDMax];

        bool MessageReactionResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageReactionResult");
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
            j_method_id_array[MethodIDConstructor] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_,"resultCode", "I");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDResultCode] = jfield;

            jfield = env->GetFieldID(j_cls_,"resultInfo", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDResultInfo] = jfield;

            jfield = env->GetFieldID(j_cls_,"messageID", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDMessageID] = jfield;

            jfield = env->GetFieldID(j_cls_,"reactionList", "Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDReactionList] = jfield;

            return true;
        }

        jobject MessageReactionResultJni::Convert2JObject(const V2TIMMessageReactionResult &reactionResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject reactionResultObj = env->NewObject(j_cls_, j_method_id_array[MethodIDConstructor]);
            if (nullptr == reactionResultObj) {
                return nullptr;
            }

            env->SetIntField(reactionResultObj, j_field_array_[FieldIDResultCode], reactionResult.resultCode);

            jstring jStr;
            jStr = StringJni::Cstring2Jstring(env, reactionResult.resultInfo.CString());
            if (jStr) {
                env->SetObjectField(reactionResultObj, j_field_array_[FieldIDResultInfo], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, reactionResult.msgID.CString());
            if (jStr) {
                env->SetObjectField(reactionResultObj, j_field_array_[FieldIDMessageID], jStr);
                env->DeleteLocalRef(jStr);
            }

            if (!reactionResult.reactionList.Empty()){
                jobject reactionListObj = ArrayListJni::NewArrayList();
                for (int i = 0; i < reactionResult.reactionList.Size(); ++i) {
                    jobject reactionObj = MessageReactionJni::Convert2JObject(reactionResult.reactionList[i]);
                    if (reactionObj){
                        ArrayListJni::Add(reactionListObj,reactionObj);
                        env->DeleteLocalRef(reactionObj);
                    }
                }
                env->SetObjectField(reactionResultObj, j_field_array_[FieldIDReactionList], reactionListObj);
                env->DeleteLocalRef(reactionListObj);
            }

            return reactionResultObj;
        }
    }
}