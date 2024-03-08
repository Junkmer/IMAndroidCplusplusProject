//
// Created by EDY on 2023/11/2.
//

#include "message_reaction_user_result_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "user_info_jni.h"

namespace v2im {
    namespace jni {

        jclass MessageReactionUserResultJni::j_cls_;
        jfieldID MessageReactionUserResultJni::j_field_array_[FieldIDMax];
        jmethodID MessageReactionUserResultJni::j_method_id_array[MethodIDMax];

        bool MessageReactionUserResultJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageReactionUserResult");
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
            jfield = env->GetFieldID(j_cls_,"userInfoList", "Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDUserInfoList] = jfield;

            jfield = env->GetFieldID(j_cls_,"nextSeq", "I");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDNextSeq] = jfield;

            jfield = env->GetFieldID(j_cls_,"isFinished", "Z");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDIsFinished] = jfield;

            return true;
        }

        jobject MessageReactionUserResultJni::Convert2JObject(const V2TIMMessageReactionUserResult &reactionUserResult) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject reactionUserResultObj = env->NewObject(j_cls_, j_method_id_array[MethodIDConstructor]);
            if (nullptr == reactionUserResultObj) {
                return nullptr;
            }

            if (!reactionUserResult.userInfoList.Empty()){
                jobject userListObj =  ArrayListJni::NewArrayList();
                for (int i = 0; i < reactionUserResult.userInfoList.Size(); ++i) {
                    jobject user_obj = UserInfoJni::Convert2JObject(reactionUserResult.userInfoList[i]);
                    if (user_obj){
                        ArrayListJni::Add(userListObj,user_obj);
                        env->DeleteLocalRef(user_obj);
                    }
                }
                env->SetObjectField(reactionUserResultObj,j_field_array_[FieldIDUserInfoList],userListObj);
                env->DeleteLocalRef(userListObj);
            }

            env->SetIntField(reactionUserResultObj, j_field_array_[FieldIDNextSeq], (jint) reactionUserResult.nextSeq);
            env->SetBooleanField(reactionUserResultObj,j_field_array_[FieldIDIsFinished], reactionUserResult.isFinished);
            return reactionUserResultObj;
        }
    }
}