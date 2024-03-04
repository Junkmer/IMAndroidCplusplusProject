//
// Created by EDY on 2023/11/2.
//

#include "message_reaction_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "user_info_jni.h"

namespace v2im {
    namespace jni {

        jclass MessageReactionJni::j_cls_;
        jfieldID MessageReactionJni::j_field_array_[FieldIDMax];
        jmethodID MessageReactionJni::j_method_id_array[MethodIDMax];

        bool MessageReactionJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageReaction");
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
            jfield = env->GetFieldID(j_cls_,"reactionID", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDReactionID] = jfield;

            jfield = env->GetFieldID(j_cls_,"totalUserCount", "I");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDTotalUserCount] = jfield;

            jfield = env->GetFieldID(j_cls_,"partialUserList", "Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDPartialUserList] = jfield;

            jfield = env->GetFieldID(j_cls_,"reactedByMyself", "Z");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDReactedByMyself] = jfield;

            return true;
        }

        jobject MessageReactionJni::Convert2JObject(const V2TIMMessageReaction &messageReaction) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject messageReactionObj = env->NewObject(j_cls_, j_method_id_array[MethodIDConstructor]);
            if (nullptr == messageReactionObj) {
                return nullptr;
            }

            jstring jStr;
            jStr = StringJni::Cstring2Jstring(env, messageReaction.reactionID.CString());
            if (jStr) {
                env->SetObjectField(messageReactionObj, j_field_array_[FieldIDReactionID], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(messageReactionObj, j_field_array_[FieldIDTotalUserCount], (jint)messageReaction.totalUserCount);

            if (!messageReaction.partialUserList.Empty()){
                jobject userListObj =  ArrayListJni::NewArrayList();
                for (int i = 0; i < messageReaction.partialUserList.Size(); ++i) {
                    jobject user_obj = UserInfoJni::Convert2JObject(messageReaction.partialUserList[i]);
                    if (user_obj){
                        ArrayListJni::Add(userListObj,user_obj);
                        env->DeleteLocalRef(user_obj);
                    }
                }
                env->SetObjectField(messageReactionObj,j_field_array_[FieldIDPartialUserList],userListObj);
                env->DeleteLocalRef(userListObj);
            }
            env->SetBooleanField(messageReactionObj,j_field_array_[FieldIDReactedByMyself], messageReaction.reactedByMyself);
            return messageReactionObj;
        }
    }
}