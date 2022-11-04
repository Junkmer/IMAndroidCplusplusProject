//
// Created by EDY on 2022/8/22.
//

#include <jni.h>
#include <LogUtil.h>
#include "jni_util.h"
#include "value_callback_impl.h"
#include "conversation_listener_jni.h"
#include "v2_im_engine.h"
#include "V2TIMErrorCode.h"
#include "jni_helper.h"
#include "conversation_result_jni.h"
#include "im_callbak_jni.h"
#include "java_basic_jni.h"
#include "conversation_jni.h"
#include "conversation_list_filter_jni.h"
#include "callback_impl.h"
#include "conversation_operation_result_jni.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<v2im::jni::ConversationListenerJni> conversation_listener_jni;

DEFINE_NATIVE_FUNC(void, NativeInitCplusplusConversationListener) {
    if (!conversation_listener_jni) {
        conversation_listener_jni = std::make_shared<v2im::jni::ConversationListenerJni>();
    }
    conversation_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeAddConversationListener, jobject listener, jstring listenerPath) {
    if (!conversation_listener_jni) {
        conversation_listener_jni = std::make_shared<v2im::jni::ConversationListenerJni>();
    }
    conversation_listener_jni->AddListener(env, listener, listenerPath);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveConversationListener, jstring listenerPath) {
    if (conversation_listener_jni) {
        conversation_listener_jni->RemoveListener(env, listenerPath);
    }
}

DEFINE_NATIVE_FUNC(void, NativeGetConversationList, jlong next_seq, jint count, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto nextSeq_c = (uint64_t) next_seq;
    auto count_c = (uint32_t) count;

    LOGE("GetConversationList-Request, next_seq = %ld | count = %d",next_seq,count);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationResult>{};
    value_callback->setCallback(
            [=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationResult &conversationResult) {
                LOGE("GetConversationList-CallBack, nextSeq = %lu | isFinished = %d",conversationResult.nextSeq,conversationResult.isFinished);

                v2im::jni::ScopedJEnv scopedJEnv;
                auto _env = scopedJEnv.GetEnv();

                if (V2TIMErrorCode::ERR_SUCC == error_code) {
                    jobject conversationResultObj = v2im::jni::ConversationResultJni::Convert2JObject(conversationResult);
                    if (conversationResultObj) {
                        v2im::jni::IMCallbackJNI::Success(jni_callback, conversationResultObj);
                        _env->DeleteLocalRef(conversationResultObj);
                    }
                } else {
                    v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
                }
                _env->DeleteGlobalRef(jni_callback);
                delete value_callback;
            });

    v2im::V2IMEngine::GetInstance()->GetConversationList(nextSeq_c, count_c, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetConversation, jstring conversation_id, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString conversationIDStr = v2im::jni::StringJni::Jstring2Cstring(env, conversation_id).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversation>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversation &conversation) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject conversationObj = v2im::jni::ConversationJni::Convert2JObject(conversation);
            if (conversationObj) {
                v2im::jni::IMCallbackJNI::Success(jni_callback, conversationObj);
                _env->DeleteLocalRef(conversationObj);
            }
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetConversation(conversationIDStr, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetConversationListForID, jobject conversation_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector conversation_vector;

    int size = v2im::jni::ArrayListJni::Size(conversation_idlist);
    for (int i = 0; i < size; ++i) {
        auto item = (jstring) v2im::jni::ArrayListJni::Get(conversation_idlist, i);
        V2TIMString conversation = v2im::jni::StringJni::Jstring2Cstring(env, item).c_str();
        conversation_vector.PushBack(conversation);
        env->DeleteLocalRef(item);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject conversationObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject conversationObj = v2im::jni::ConversationJni::Convert2JObject(value[i]);
                if (conversationObj) {
                    v2im::jni::ArrayListJni::Add(conversationObjList, conversationObj);
                    _env->DeleteLocalRef(conversationObj);
                }
            }

            v2im::jni::IMCallbackJNI::Success(jni_callback, conversationObjList);
            _env->DeleteLocalRef(conversationObjList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetConversationList(conversation_vector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetConversationListByFilter, jobject filter, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMConversationListFilter listFilter;

    bool flag = v2im::jni::ConversationListFilterJni::Convert2CoreObject(filter, listFilter);
    if (flag) {
        return;
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject resultObj = v2im::jni::ConversationResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, resultObj);
            _env->DeleteLocalRef(resultObj);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetConversationListByFilter(listFilter, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteConversation, jstring conversation_id, jobject callback) {

    V2TIMString conversationID_str = v2im::jni::StringJni::Jstring2Cstring(env, conversation_id).c_str();

    v2im::V2IMEngine::GetInstance()->DeleteConversation(conversationID_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSetConversationDraft, jstring conversation_id, jstring draft_text, jobject callback) {

    V2TIMString conversationID = v2im::jni::StringJni::Jstring2Cstring(env, conversation_id).c_str();
    V2TIMString draftText = v2im::jni::StringJni::Jstring2Cstring(env, draft_text).c_str();

    v2im::V2IMEngine::GetInstance()->SetConversationDraft(conversationID, draftText, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSetConversationCustomData, jobject conversation_idlist, jstring custom_data, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector conversation_vector;
    int size = v2im::jni::ArrayListJni::Size(conversation_idlist);
    for (int i = 0; i < size; ++i) {
        auto item = (jstring) v2im::jni::ArrayListJni::Get(conversation_idlist, i);
        V2TIMString conversation = v2im::jni::StringJni::Jstring2Cstring(env, item).c_str();
        conversation_vector.PushBack(conversation);
        env->DeleteLocalRef(item);
    }

    V2TIMBuffer customData_buffer = v2im::jni::StringJni::Jstring2V2TIMBuffer(env, custom_data);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject operationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject operationResultObj = v2im::jni::ConversationOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(operationResultList, operationResultObj);
                _env->DeleteLocalRef(operationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResultList);
            _env->DeleteLocalRef(operationResultList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SetConversationCustomData(conversation_vector, customData_buffer, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativePinConversation, jstring conversation_id, jboolean is_pinned, jobject callback) {

    V2TIMString conversationID_str = v2im::jni::StringJni::Jstring2Cstring(env, conversation_id).c_str();

    v2im::V2IMEngine::GetInstance()->PinConversation(conversationID_str, (bool) is_pinned, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeMarkConversation, jobject conversation_idlist, jlong mark_type, jboolean enable_mark, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector conversation_vector;
    int size = v2im::jni::ArrayListJni::Size(conversation_idlist);
    for (int i = 0; i < size; ++i) {
        auto item = (jstring) v2im::jni::ArrayListJni::Get(conversation_idlist, i);
        V2TIMString conversation = v2im::jni::StringJni::Jstring2Cstring(env, item).c_str();
        conversation_vector.PushBack(conversation);
        env->DeleteLocalRef(item);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject operationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject operationResultObj = v2im::jni::ConversationOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(operationResultList, operationResultObj);
                _env->DeleteLocalRef(operationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResultList);
            _env->DeleteLocalRef(operationResultList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->MarkConversation(conversation_vector, (uint64_t) mark_type, (bool) enable_mark, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetTotalUnreadMessageCount, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<uint64_t>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const uint64_t &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::LongJni::NewUInt64(value));
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetTotalUnreadMessageCount(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeCreateConversationGroup, jstring group_name, jobject conversation_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupName_str = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    V2TIMStringVector conversation_vector;
    int size = v2im::jni::ArrayListJni::Size(conversation_idlist);
    for (int i = 0; i < size; ++i) {
        auto item = (jstring) v2im::jni::ArrayListJni::Get(conversation_idlist, i);
        V2TIMString conversation = v2im::jni::StringJni::Jstring2Cstring(env, item).c_str();
        conversation_vector.PushBack(conversation);
        env->DeleteLocalRef(item);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject operationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject operationResultObj = v2im::jni::ConversationOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(operationResultList, operationResultObj);
                _env->DeleteLocalRef(operationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResultList);
            env->DeleteLocalRef(operationResultList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->CreateConversationGroup(groupName_str, conversation_vector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetConversationGroupList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMStringVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMStringVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject groupObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jstring groupObj = v2im::jni::StringJni::Cstring2Jstring(env, value[i].CString());
                v2im::jni::ArrayListJni::Add(groupObjList, groupObj);
                _env->DeleteLocalRef(groupObj);
            }

            v2im::jni::IMCallbackJNI::Success(jni_callback, groupObjList);
            _env->DeleteLocalRef(groupObjList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetConversationGroupList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteConversationGroup, jstring group_name, jobject callback) {

    V2TIMString groupName_str = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    v2im::V2IMEngine::GetInstance()->DeleteConversationGroup(groupName_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeRenameConversationGroup, jstring old_name, jstring new_name, jobject callback) {

    V2TIMString oldName_str = v2im::jni::StringJni::Jstring2Cstring(env, old_name).c_str();
    V2TIMString newName_str = v2im::jni::StringJni::Jstring2Cstring(env, new_name).c_str();

    v2im::V2IMEngine::GetInstance()->RenameConversationGroup(oldName_str, newName_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeAddConversationsToGroup, jstring group_name, jobject conversation_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupName_str = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    V2TIMStringVector conversation_vector;
    int size = v2im::jni::ArrayListJni::Size(conversation_idlist);
    for (int i = 0; i < size; ++i) {
        auto item = (jstring) v2im::jni::ArrayListJni::Get(conversation_idlist, i);
        V2TIMString conversation = v2im::jni::StringJni::Jstring2Cstring(env, item).c_str();
        conversation_vector.PushBack(conversation);
        env->DeleteLocalRef(item);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject operationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject operationResultObj = v2im::jni::ConversationOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(operationResultList, operationResultObj);
                _env->DeleteLocalRef(operationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResultList);
            _env->DeleteLocalRef(operationResultList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->AddConversationsToGroup(groupName_str, conversation_vector, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteConversationsFromGroup, jstring group_name, jobject conversation_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupName_str = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    V2TIMStringVector conversation_vector;
    int size = v2im::jni::ArrayListJni::Size(conversation_idlist);
    for (int i = 0; i < size; ++i) {
        auto item = (jstring) v2im::jni::ArrayListJni::Get(conversation_idlist, i);
        V2TIMString conversation = v2im::jni::StringJni::Jstring2Cstring(env, item).c_str();
        conversation_vector.PushBack(conversation);
        env->DeleteLocalRef(item);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMConversationOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMConversationOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject operationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject operationResultObj = v2im::jni::ConversationOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(operationResultList, operationResultObj);
                _env->DeleteLocalRef(operationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResultList);
            _env->DeleteLocalRef(operationResultList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->DeleteConversationsFromGroup(groupName_str, conversation_vector, value_callback);
}

//void test(JNIEnv *env) {
//    jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMConversationManager");
//    jmethodID jmethod = nullptr;
//    jmethod = env->GetMethodID(cls, "nativeInitCplusplusConversationListener", "()V");
//}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeInitCplusplusConversationListener", "()V",                                                                          (void *) NativeInitCplusplusConversationListener},
        {"nativeAddConversationListener",           "(Lcom/tencent/imsdk/v2/V2TIMConversationListener;Ljava/lang/String;)V",        (void *) NativeAddConversationListener},
        {"nativeRemoveConversationListener",        "(Ljava/lang/String;)V",                                                        (void *) NativeRemoveConversationListener},
        {"nativeGetConversationList",               "(JILcom/tencent/imsdk/common/IMCallback;)V",                                   (void *) NativeGetConversationList},
        {"nativeGetConversation",                   "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeGetConversation},
        {"nativeGetConversationList",               "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                     (void *) NativeGetConversationListForID},
        {"nativeGetConversationListByFilter",       "(Lcom/tencent/imsdk/v2/V2TIMConversationListFilter;"
                                                    "Lcom/tencent/imsdk/common/IMCallback;)V",                                                      (void *) NativeGetConversationListByFilter},
        {"nativeDeleteConversation",                "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeDeleteConversation},
        {"nativeSetConversationDraft",              "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeSetConversationDraft},
        {"nativeSetConversationCustomData",         "(Ljava/util/List;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",   (void *) NativeSetConversationCustomData},
        {"nativePinConversation",                   "(Ljava/lang/String;ZLcom/tencent/imsdk/common/IMCallback;)V",                  (void *) NativePinConversation},
        {"nativeMarkConversation",                  "(Ljava/util/List;JZLcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeMarkConversation},
        {"nativeGetTotalUnreadMessageCount",        "(Lcom/tencent/imsdk/common/IMCallback;)V",                                     (void *) NativeGetTotalUnreadMessageCount},
        {"nativeCreateConversationGroup",           "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",   (void *) NativeCreateConversationGroup},
        {"nativeGetConversationGroupList",          "(Lcom/tencent/imsdk/common/IMCallback;)V",                                     (void *) NativeGetConversationGroupList},
        {"nativeDeleteConversationGroup",           "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                   (void *) NativeDeleteConversationGroup},
        {"nativeRenameConversationGroup",           "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeRenameConversationGroup},
        {"nativeAddConversationsToGroup",           "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",   (void *) NativeAddConversationsToGroup},
        {"nativeDeleteConversationsFromGroup",      "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",   (void *) NativeDeleteConversationsFromGroup},

};

//注册 native 方法
int RegisterNativeMethodsForV2TIMConversationManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMConversationManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}

#ifdef __cplusplus
}
#endif
