//
// Created by EDY on 2024/1/15.
//

#include <jni_helper.h>
#include <java_basic_jni.h>
#include "message_reaction_change_info_jni.h"
#include "message_reaction_jni.h"

namespace v2im {
    namespace jni{

        jclass MessageReactionChangeInfoJni::j_cls;
        jfieldID MessageReactionChangeInfoJni::j_field_array_[FieldIDMax];
        jmethodID MessageReactionChangeInfoJni::j_method_id_array_[MethodIDMax];

        bool MessageReactionChangeInfoJni::InitIDs(JNIEnv *env) {
            if (j_cls != nullptr) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessageReactionChangeInfo");
            if (nullptr == cls) {
                return false;
            }

            j_cls = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls, "messageID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDMessageID] = jfield;

            jfield = env->GetFieldID(j_cls, "reactionList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FieldIDReactionList] = jfield;

            return true;
        }

        jobject MessageReactionChangeInfoJni::Convert2JObject(const V2TIMMessageReactionChangeInfo &reactionChangeInfo) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject reactionChangeInfoObj = env->NewObject(j_cls, j_method_id_array_[MethodIDConstruct]);
            if (!reactionChangeInfoObj) {
                return nullptr;
            }

            env->SetObjectField(reactionChangeInfoObj, j_field_array_[FieldIDMessageID], StringJni::Cstring2Jstring(env, reactionChangeInfo.msgID.CString()));

            jobject j_obj_reactionList = ArrayListJni::NewArrayList();
            for (int i = 0; i < reactionChangeInfo.reactionList.Size(); ++i) {
                jobject j_obj_reaction = MessageReactionJni::Convert2JObject(reactionChangeInfo.reactionList[i]);
                if (j_obj_reaction) {
                    ArrayListJni::Add(j_obj_reactionList,j_obj_reaction);
                    env->DeleteLocalRef(j_obj_reaction);
                }
            }
            env->SetObjectField(reactionChangeInfoObj, j_field_array_[FieldIDReactionList], j_obj_reactionList);
            return nullptr;
        }
    }
} // v2im