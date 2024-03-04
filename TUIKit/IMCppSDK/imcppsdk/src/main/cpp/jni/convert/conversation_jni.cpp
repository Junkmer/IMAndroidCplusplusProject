//
// Created by Junker on 2022/9/27.
//

#include "conversation_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "conversation_jni.h"
#include "message_jni.h"
#include "group_at_info_jni.h"

namespace v2im {
    namespace jni {

        jclass ConversationJni::j_cls_;
        jfieldID ConversationJni::j_field_id_array_[FieldIDMax];
        jmethodID ConversationJni::j_method_id_array_[MethodIDMax];

        bool ConversationJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMConversation");
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
            j_method_id_array_[MethodIDConstruct] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addGroupAtInfo", "(Lcom/tencent/imsdk/v2/V2TIMGroupAtInfo;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddGroupAtInfo] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addMark", "(J)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddMark] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addConversationGroup", "(Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddConversationGroup] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "conversationID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDConversationID] = jfield;

            jfield = env->GetFieldID(j_cls_, "type", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDType] = jfield;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDGroupID] = jfield;

            jfield = env->GetFieldID(j_cls_, "showName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDShowName] = jfield;

            jfield = env->GetFieldID(j_cls_, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "recvOpt", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDRecvOpt] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupType", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDGroupType] = jfield;

            jfield = env->GetFieldID(j_cls_, "unreadCount", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDUnreadCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "lastMessage", "Lcom/tencent/imsdk/v2/V2TIMMessage;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDLastMessage] = jfield;

            jfield = env->GetFieldID(j_cls_, "draftText", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDDraftText] = jfield;

            jfield = env->GetFieldID(j_cls_, "draftTimestamp", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDDraftTimestamp] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupAtInfoList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDGroupAtInfoList] = jfield;

            jfield = env->GetFieldID(j_cls_, "pinned", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDPinned] = jfield;

            jfield = env->GetFieldID(j_cls_, "orderKey", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDOrderKey] = jfield;

            jfield = env->GetFieldID(j_cls_, "markList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDMarkList] = jfield;

            jfield = env->GetFieldID(j_cls_, "customData", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDCustomData] = jfield;

            jfield = env->GetFieldID(j_cls_, "conversationGroupList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDConversationGroupList] = jfield;

            jfield = env->GetFieldID(j_cls_, "c2CReadTimestamp", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDC2CReadTimestamp] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupReadSequence", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_field_id_array_[FieldIDGroupReadSequence] = jfield;

            return true;
        }

        jobject ConversationJni::Convert2JObject(const V2TIMConversation &conversation) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject conversationObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstruct]);
            if (nullptr == conversationObj) {
                return nullptr;
            }

            jstring jStr = nullptr;

            jStr = StringJni::Cstring2Jstring(env, conversation.conversationID.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDConversationID], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(conversationObj, j_field_id_array_[FieldIDType], (jint) conversation.type);

            jStr = StringJni::Cstring2Jstring(env, conversation.userID.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDUserID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, conversation.groupID.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDGroupID], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, conversation.showName.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDShowName], jStr);
                env->DeleteLocalRef(jStr);
            }

            jStr = StringJni::Cstring2Jstring(env, conversation.faceUrl.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDFaceUrl], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(conversationObj, j_field_id_array_[FieldIDRecvOpt], (jint) conversation.recvOpt);

            jStr = StringJni::Cstring2Jstring(env, conversation.groupType.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDGroupType], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetIntField(conversationObj, j_field_id_array_[FieldIDUnreadCount], (jint) conversation.unreadCount);

            if (conversation.lastMessage){
                jobject lastMessageObj = MessageJni::Convert2JObject(*conversation.lastMessage);
                if (lastMessageObj){
                    env->SetObjectField(conversationObj,j_field_id_array_[FieldIDLastMessage],lastMessageObj);
                    env->DeleteLocalRef(lastMessageObj);
                }
            }

            jStr = StringJni::Cstring2Jstring(env, conversation.draftText.CString());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDDraftText], jStr);
                env->DeleteLocalRef(jStr);
            }

            env->SetLongField(conversationObj, j_field_id_array_[FieldIDDraftTimestamp], (jlong) conversation.draftTimestamp);

            for (int i = 0; i < conversation.groupAtInfolist.Size(); ++i) {
                jobject atInfoObj = GroupAtInfoJni::Convert2JObject(conversation.groupAtInfolist[i]);
                if (atInfoObj){
                    env->CallVoidMethod(conversationObj,j_method_id_array_[MethodIDAddGroupAtInfo],atInfoObj);
                    env->DeleteLocalRef(atInfoObj);
                }
            }

            env->SetBooleanField(conversationObj, j_field_id_array_[FieldIDPinned], (jint) conversation.isPinned);
            env->SetLongField(conversationObj, j_field_id_array_[FieldIDOrderKey], (jlong) conversation.orderKey);

            for (int i = 0; i < conversation.markList.Size(); ++i) {
                env->CallVoidMethod(conversationObj, j_method_id_array_[MethodIDAddMark], (jlong) conversation.markList[i]);
            }

            jStr = StringJni::Cuint8_t2Jstring(env, conversation.customData.Data(), conversation.customData.Size());
            if (jStr) {
                env->SetObjectField(conversationObj, j_field_id_array_[FieldIDCustomData], jStr);
                env->DeleteLocalRef(jStr);
            }

            for (int i = 0; i < conversation.conversationGroupList.Size(); ++i) {
                jstring conversationGroupStr = StringJni::Cstring2Jstring(env,conversation.conversationGroupList[i].CString());
                env->CallVoidMethod(conversationObj, j_method_id_array_[MethodIDAddMark], conversationGroupStr);
                env->DeleteLocalRef(conversationGroupStr);
            }

            env->SetLongField(conversationObj, j_field_id_array_[FieldIDC2CReadTimestamp], (jlong) conversation.c2cReadTimestamp);
            env->SetLongField(conversationObj, j_field_id_array_[FieldIDGroupReadSequence], (jlong) conversation.groupReadSequence);
            return conversationObj;
        }
    }// namespace v2im
}// namespace jni