//
// Created by EDY on 2022/9/20.
//

#include <LogUtil.h>
#include "message_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "elem_processor_jni.h"
#include "offline_push_info_jni.h"

namespace v2im {
    namespace jni {

        jclass MessageJni::j_cls_;
        jfieldID MessageJni::j_filed_id_array[FieldIDMax];
        jmethodID MessageJni::j_method_id_array[MethodIDMax];

        bool MessageJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMessage");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array[MethodIDConstructor] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addElem", "(Lcom/tencent/imsdk/v2/V2TIMElem;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array[MethodIDAddMessageElem] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_, "msgID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDMsgID] = jfield;

            jfield = env->GetFieldID(j_cls_, "timestamp", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDTimestamp] = jfield;

            jfield = env->GetFieldID(j_cls_, "sender", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDSender] = jfield;

            jfield = env->GetFieldID(j_cls_, "nickName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDNickName] = jfield;

            jfield = env->GetFieldID(j_cls_, "friendRemark", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDFriendRemark] = jfield;

            jfield = env->GetFieldID(j_cls_, "faceUrl", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDFaceUrl] = jfield;

            jfield = env->GetFieldID(j_cls_, "nameCard", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDNameCard] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDGroupID] = jfield;

            jfield = env->GetFieldID(j_cls_, "userID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDUserID] = jfield;

            jfield = env->GetFieldID(j_cls_, "status", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDStatus] = jfield;

            jfield = env->GetFieldID(j_cls_, "elemType", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDElemType] = jfield;

            jfield = env->GetFieldID(j_cls_, "elemList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDElemList] = jfield;

            jfield = env->GetFieldID(j_cls_, "localCustomInt", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDLocalCustomInt] = jfield;

            jfield = env->GetFieldID(j_cls_, "localCustomData", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDLocalCustomData] = jfield;

            jfield = env->GetFieldID(j_cls_, "cloudCustomData", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDCloudCustomData] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSelf", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsSelf] = jfield;

            jfield = env->GetFieldID(j_cls_, "isRead", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsRead] = jfield;

            jfield = env->GetFieldID(j_cls_, "isPeerRead", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsPeerRead] = jfield;

            jfield = env->GetFieldID(j_cls_, "needReadReceipt", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDNeedReadReceipt] = jfield;

            jfield = env->GetFieldID(j_cls_, "isBroadcastMessage", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsBroadcastMessage] = jfield;

            jfield = env->GetFieldID(j_cls_, "priority", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDPriority] = jfield;

            jfield = env->GetFieldID(j_cls_, "offlinePushInfo", "Lcom/tencent/imsdk/v2/V2TIMOfflinePushInfo;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDOfflinePushInfo] = jfield;

            jfield = env->GetFieldID(j_cls_, "groupAtUserList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDGroupAtUserList] = jfield;

            jfield = env->GetFieldID(j_cls_, "seq", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDSeq] = jfield;

            jfield = env->GetFieldID(j_cls_, "random", "J");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDRandom] = jfield;

            jfield = env->GetFieldID(j_cls_, "isExcludedFromUnreadCount", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsExcludedFromUnreadCount] = jfield;

            jfield = env->GetFieldID(j_cls_, "isExcludedFromLastMessage", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsExcludedFromLastMessage] = jfield;

            jfield = env->GetFieldID(j_cls_, "isSupportMessageExtension", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsSupportMessageExtension] = jfield;

            jfield = env->GetFieldID(j_cls_, "isExcludedFromContentModeration", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_filed_id_array[FieldIDIsExcludedFromContentModeration] = jfield;

            return true;
        }

        jobject MessageJni::Convert2JObject(const V2TIMMessage &v2TimMessage) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            jobject j_obj_message = env->NewObject(j_cls_, j_method_id_array[MethodIDConstructor]);
            if (nullptr == j_obj_message) {
                return nullptr;
            }

            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDMsgID], StringJni::Cstring2Jstring(env, v2TimMessage.msgID.CString()));
            env->SetLongField(j_obj_message, j_filed_id_array[FieldIDTimestamp], (jlong) v2TimMessage.timestamp);
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDSender], StringJni::Cstring2Jstring(env, v2TimMessage.sender.CString()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDNickName], StringJni::Cstring2Jstring(env, v2TimMessage.nickName.CString()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDFriendRemark],
                                StringJni::Cstring2Jstring(env, v2TimMessage.friendRemark.CString()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDFaceUrl], StringJni::Cstring2Jstring(env, v2TimMessage.faceURL.CString()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDNameCard], StringJni::Cstring2Jstring(env, v2TimMessage.nameCard.CString()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDGroupID], StringJni::Cstring2Jstring(env, v2TimMessage.groupID.CString()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDUserID], StringJni::Cstring2Jstring(env, v2TimMessage.userID.CString()));
            env->SetIntField(j_obj_message, j_filed_id_array[FieldIDStatus], (jint) v2TimMessage.status);
            env->SetIntField(j_obj_message, j_filed_id_array[FieldIDElemType], (jint) v2TimMessage.elemList[0]->elemType);
            env->SetIntField(j_obj_message, j_filed_id_array[FieldIDLocalCustomInt], (jint) v2TimMessage.localCustomInt);
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDLocalCustomData],
                                StringJni::Cuint8_t2Jstring(env, v2TimMessage.localCustomData.Data(), v2TimMessage.localCustomData.Size()));
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDCloudCustomData],
                                StringJni::Cuint8_t2Jstring(env, v2TimMessage.cloudCustomData.Data(), v2TimMessage.cloudCustomData.Size()));
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsSelf], v2TimMessage.isSelf);
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsRead], v2TimMessage.IsRead());
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsPeerRead], v2TimMessage.IsPeerRead());
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDNeedReadReceipt], v2TimMessage.needReadReceipt);
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsBroadcastMessage], v2TimMessage.isBroadcastMessage);
            env->SetIntField(j_obj_message, j_filed_id_array[FieldIDPriority], (jint) v2TimMessage.priority);

            jobject offlinePushObj = OfflinePushInfoJni::Convert2JObject(v2TimMessage.offlinePushInfo);
            if (offlinePushObj) {
                env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDOfflinePushInfo], offlinePushObj);
                env->DeleteLocalRef(offlinePushObj);
            }

            for (int i = 0; i < v2TimMessage.elemList.Size(); ++i) {
                auto *jElemObj = ElemProcessor::GetInstance().ParseElem(v2TimMessage,i);
                if (jElemObj) {
                    env->CallVoidMethod(j_obj_message, j_method_id_array[MethodIDAddMessageElem], jElemObj);
                    env->DeleteLocalRef(jElemObj);
                }
            }

            jobject arrayList = ArrayListJni::NewArrayList();
            for (int i = 0; i < v2TimMessage.groupAtUserList.Size(); ++i) {
                jstring userIDObj = StringJni::Cstring2Jstring(env, v2TimMessage.groupAtUserList[i].CString());
                ArrayListJni::Add(arrayList, userIDObj);

                env->DeleteLocalRef(userIDObj);
            }
            env->SetObjectField(j_obj_message, j_filed_id_array[FieldIDGroupAtUserList], arrayList);
            env->DeleteLocalRef(arrayList);

            env->SetLongField(j_obj_message, j_filed_id_array[FieldIDSeq], (jlong) v2TimMessage.seq);
            env->SetLongField(j_obj_message, j_filed_id_array[FieldIDRandom], (jlong) v2TimMessage.random);
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsExcludedFromUnreadCount], v2TimMessage.isExcludedFromUnreadCount);
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsExcludedFromLastMessage], v2TimMessage.isExcludedFromLastMessage);
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsExcludedFromContentModeration], v2TimMessage.isExcludedFromLastMessage);
            env->SetBooleanField(j_obj_message, j_filed_id_array[FieldIDIsSupportMessageExtension], v2TimMessage.supportMessageExtension);
            return j_obj_message;
        }

        bool MessageJni::Convert2CoreObject(const jobject &messageObj,V2TIMMessage &message) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return false;
            }

            auto msgIDStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDMsgID]);
            if (nullptr != msgIDStr) {
                message.msgID = StringJni::Jstring2Cstring(env, msgIDStr).c_str();
                env->DeleteLocalRef(msgIDStr);
            }

            message.timestamp = (int64_t) env->GetLongField(messageObj, j_filed_id_array[FieldIDTimestamp]);

            auto senderStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDSender]);
            if (nullptr != senderStr) {
                message.sender = StringJni::Jstring2Cstring(env, senderStr).c_str();
                env->DeleteLocalRef(senderStr);
            }

            auto nickNameStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDNickName]);
            if (nullptr != nickNameStr) {
                message.nickName = StringJni::Jstring2Cstring(env, nickNameStr).c_str();
                env->DeleteLocalRef(nickNameStr);
            }

            auto friendRemarkStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDFriendRemark]);
            if (nullptr != friendRemarkStr) {
                message.friendRemark = StringJni::Jstring2Cstring(env, friendRemarkStr).c_str();
                env->DeleteLocalRef(friendRemarkStr);
            }

            auto faceURLStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDFaceUrl]);
            if (nullptr != faceURLStr) {
                message.faceURL = StringJni::Jstring2Cstring(env, faceURLStr).c_str();
                env->DeleteLocalRef(faceURLStr);
            }

            auto nameCardStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDNameCard]);
            if (nullptr != nameCardStr) {
                message.nameCard = StringJni::Jstring2Cstring(env, nameCardStr).c_str();
                env->DeleteLocalRef(nameCardStr);
            }

            auto groupIDStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDGroupID]);
            if (nullptr != groupIDStr) {
                message.groupID = StringJni::Jstring2Cstring(env, groupIDStr).c_str();
                env->DeleteLocalRef(groupIDStr);
            }

            auto userIDStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDUserID]);
            if (nullptr != userIDStr) {
                message.userID = StringJni::Jstring2Cstring(env, userIDStr).c_str();
                env->DeleteLocalRef(userIDStr);
            }

            message.status = V2TIMMessageStatus(env->GetIntField(messageObj, j_filed_id_array[FieldIDStatus]));

            message.localCustomInt = env->GetIntField(messageObj, j_filed_id_array[FieldIDLocalCustomInt]);
            auto localCustomDataStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDLocalCustomData]);
            if (nullptr != localCustomDataStr) {
                message.localCustomData = StringJni::Jstring2V2TIMBuffer(env, localCustomDataStr);
                env->DeleteLocalRef(localCustomDataStr);
            }

            auto cloudCustomDataStr = (jstring) env->GetObjectField(messageObj, j_filed_id_array[FieldIDCloudCustomData]);
            if (nullptr != cloudCustomDataStr) {
                message.cloudCustomData = StringJni::Jstring2V2TIMBuffer(env, cloudCustomDataStr);
                env->DeleteLocalRef(cloudCustomDataStr);
            }

            message.isSelf = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsSelf]);
            message.isRead = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsRead]);
            message.isPeerRead = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsPeerRead]);
            message.needReadReceipt = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDNeedReadReceipt]);
            message.isBroadcastMessage = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsBroadcastMessage]);
            message.priority = V2TIMMessagePriority(env->GetIntField(messageObj, j_filed_id_array[FieldIDPriority]));

            jobject offlinePushObj = env->GetObjectField(messageObj, j_filed_id_array[FieldIDOfflinePushInfo]);
            if (offlinePushObj) {
                OfflinePushInfoJni::Convert2CoreObject(offlinePushObj, message.offlinePushInfo);
                env->DeleteLocalRef(offlinePushObj);
            }

            auto *elemListObj = env->GetObjectField(messageObj, j_filed_id_array[FieldIDElemList]);
            int size;
            size = ArrayListJni::Size(elemListObj);
            if (size > 0) {
                for (int i = 0; i < size; ++i) {
                    auto *jElemObj = ArrayListJni::Get(elemListObj, i);
                    if (nullptr == jElemObj) {
                        continue;
                    }
                    jclass cls = env->GetObjectClass(jElemObj);
                    jmethodID get_type = env->GetMethodID(cls, "getElementType", "()I");
                    if (!get_type) continue;

                    auto type = env->CallIntMethod(jElemObj, get_type);
                    std::unique_ptr<V2TIMElem> elem = ElemProcessor::GetInstance().BuildElem(type, jElemObj);
                    if (elem) {
                        message.elemList.PushBack(elem.get());
                        elem.release();// 释放局部变量指针 elem，让传入 message->elemList 数据的elem重新分配内存。
                    }
                }
            }

            jobject j_obj_atUserList = env->GetObjectField(messageObj, j_filed_id_array[FieldIDGroupAtUserList]);
            size = ArrayListJni::Size(j_obj_atUserList);
            if (size > 0) {
                for (int i = 0; i < size; ++i) {
                    auto atUserObj = (jstring) ArrayListJni::Get(j_obj_atUserList, i);
                    message.groupAtUserList.PushBack(StringJni::Jstring2Cstring(env, atUserObj).c_str());
                }
            }

            message.seq = (uint64_t) env->GetLongField(messageObj, j_filed_id_array[FieldIDSeq]);
            message.random = (uint64_t) env->GetLongField(messageObj, j_filed_id_array[FieldIDRandom]);
            message.isExcludedFromUnreadCount = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsExcludedFromUnreadCount]);
            message.isExcludedFromLastMessage = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsExcludedFromLastMessage]);
            message.isExcludedFromContentModeration = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsExcludedFromContentModeration]);
            message.supportMessageExtension = (bool) env->GetBooleanField(messageObj, j_filed_id_array[FieldIDIsSupportMessageExtension]);
            return true;
        }

        void MessageJni::UpdateJMessageObject(jobject &messageObj, V2TIMMessage &v2TimMessage) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return;
            }

            env->SetObjectField(messageObj, j_filed_id_array[FieldIDMsgID], StringJni::Cstring2Jstring(env, v2TimMessage.msgID.CString()));
            env->SetLongField(messageObj, j_filed_id_array[FieldIDTimestamp], (jlong) v2TimMessage.timestamp);
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDSender], StringJni::Cstring2Jstring(env, v2TimMessage.sender.CString()));
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDNickName], StringJni::Cstring2Jstring(env, v2TimMessage.nickName.CString()));
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDFriendRemark],
                                StringJni::Cstring2Jstring(env, v2TimMessage.friendRemark.CString()));
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDFaceUrl], StringJni::Cstring2Jstring(env, v2TimMessage.faceURL.CString()));
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDNameCard], StringJni::Cstring2Jstring(env, v2TimMessage.nameCard.CString()));
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDGroupID], StringJni::Cstring2Jstring(env, v2TimMessage.groupID.CString()));
            env->SetObjectField(messageObj, j_filed_id_array[FieldIDUserID], StringJni::Cstring2Jstring(env, v2TimMessage.userID.CString()));
            env->SetIntField(messageObj, j_filed_id_array[FieldIDStatus], (jint) v2TimMessage.status);
            env->SetIntField(messageObj, j_filed_id_array[FieldIDPriority], (jint) v2TimMessage.priority);
            env->SetLongField(messageObj, j_filed_id_array[FieldIDSeq], (jlong) v2TimMessage.seq);
            env->SetLongField(messageObj, j_filed_id_array[FieldIDRandom], (jlong) v2TimMessage.random);
        }

    }
}

#include "message_jni.h"
