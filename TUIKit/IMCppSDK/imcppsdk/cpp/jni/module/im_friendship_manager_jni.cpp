//
// Created by EDY on 2022/8/22.
//

#include <jni.h>
#include "jni_util.h"
#include "java_basic_jni.h"
#include "v2_im_engine.h"
#include "jni_helper.h"
#include "friend_listener_jni.h"
#include "callback_impl.h"
#include "value_callback_impl.h"
#include "V2TIMErrorCode.h"
#include "im_callbak_jni.h"
#include "friend_info_jni.h"
#include "friend_info_result_jni.h"
#include "friend_application_jni.h"
#include "friend_application_result_jni.h"
#include "friend_operation_result_jni.h"
#include "friend_search_param_jni.h"
#include "friend_add_application_jni.h"
#include "friend_check_result_jni.h"
#include "friend_group_jni.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env ,jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<v2im::jni::FriendListenerJni> friend_listener_jni;

DEFINE_NATIVE_FUNC(void, NativeInitCplusplusFriendListener) {
    if (!friend_listener_jni) {
        friend_listener_jni = std::make_shared<v2im::jni::FriendListenerJni>();
    }
    friend_listener_jni->InitListener();
}

DEFINE_NATIVE_FUNC(void, NativeAddFriendListener, jobject listener, jstring listenerPath) {
    if (!friend_listener_jni) {
        friend_listener_jni = std::make_shared<v2im::jni::FriendListenerJni>();
    }

    friend_listener_jni->AddListener(env, listener, listenerPath);
}

DEFINE_NATIVE_FUNC(void, NativeRemoveFriendListener, jstring listenerPath) {
    if (friend_listener_jni) {
        friend_listener_jni->RemoveListener(env,listenerPath);
    }
}

DEFINE_NATIVE_FUNC(void, NativeGetFriendList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto *_env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {
            jobject friendInfoList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendInfoObj = v2im::jni::FriendInfoJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendInfoList, friendInfoObj);
                _env->DeleteLocalRef(friendInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendInfoList);
            _env->DeleteLocalRef(friendInfoList);
        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetFriendList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetFriendsInfo, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendInfoResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendInfoResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendInfoResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendInfoResultObj = v2im::jni::FriendInfoResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendInfoResultList, friendInfoResultObj);
                _env->DeleteLocalRef(friendInfoResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendInfoResultList);
            _env->DeleteLocalRef(friendInfoResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetFriendsInfo(userIDList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetFriendInfo, jobject info, jobject callback) {

    V2TIMFriendInfo info_c;
    v2im::jni::FriendInfoJni::Convert2CoreObject(info, info_c);

    v2im::V2IMEngine::GetInstance()->SetFriendInfo(info_c, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSearchFriends, jobject search_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMFriendSearchParam searchParam;
    v2im::jni::FriendSearchParamJni::Convert2CoreObject(search_param, searchParam);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendInfoResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendInfoResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendInfoResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendInfoResultObj = v2im::jni::FriendInfoResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendInfoResultList, friendInfoResultObj);
                _env->DeleteLocalRef(friendInfoResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendInfoResultList);
            _env->DeleteLocalRef(friendInfoResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SearchFriends(searchParam, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeAddFriend, jobject application, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMFriendAddApplication friendAddApplication;
    v2im::jni::FriendAddApplicationJni::Convert2CoreObject(application, friendAddApplication);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject operationResult_jObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResult_jObj);
            _env->DeleteLocalRef(operationResult_jObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->AddFriend(friendAddApplication, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteFromFriendList, jobject user_idlist, jint delete_type, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto deleteType = V2TIMFriendType(delete_type);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendOperationResultObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendOperationResultList, friendOperationResultObj);
                _env->DeleteLocalRef(friendOperationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendOperationResultList);
            _env->DeleteLocalRef(friendOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->DeleteFromFriendList(userIDList, deleteType, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeCheckFriend, jobject user_idlist, jint check_type, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto checkType = V2TIMFriendType(check_type);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendCheckResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendCheckResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendCheckResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendCheckResultObj = v2im::jni::FriendCheckResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendCheckResultList, friendCheckResultObj);
                _env->DeleteLocalRef(friendCheckResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendCheckResultList);
            _env->DeleteLocalRef(friendCheckResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->CheckFriend(userIDList, checkType, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetFriendApplicationList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendApplicationResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendApplicationResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject applicationResult = v2im::jni::FriendApplicationResultJni::Convert2JObject(value);
            if (applicationResult) {
                v2im::jni::IMCallbackJNI::Success(jni_callback, applicationResult);
                _env->DeleteLocalRef(applicationResult);
            }

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetFriendApplicationList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeAcceptFriendApplication, jobject application, jint response_type, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMFriendApplication friendApplication;
    v2im::jni::FriendApplicationJni::Convert2CoreObject(application, friendApplication);
    auto acceptType = V2TIMFriendAcceptType(response_type);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject operationResult_jObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResult_jObj);
            _env->DeleteLocalRef(operationResult_jObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->AcceptFriendApplication(friendApplication, acceptType, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeRefuseFriendApplication, jobject application, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMFriendApplication friendApplication;
    v2im::jni::FriendApplicationJni::Convert2CoreObject(application, friendApplication);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject operationResult_jObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResult_jObj);
            _env->DeleteLocalRef(operationResult_jObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->RefuseFriendApplication(friendApplication, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteFriendApplication, jobject application, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMFriendApplication friendApplication;
    v2im::jni::FriendApplicationJni::Convert2CoreObject(application, friendApplication);

    v2im::V2IMEngine::GetInstance()->DeleteFriendApplication(friendApplication, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativesSetFriendApplicationRead, jobject callback) {

    v2im::V2IMEngine::GetInstance()->SetFriendApplicationRead(new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeAddToBlackList, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendOperationResultObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendOperationResultList, friendOperationResultObj);
                _env->DeleteLocalRef(friendOperationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendOperationResultList);
            _env->DeleteLocalRef(friendOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->AddToBlackList(userIDList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteFromBlackList, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendOperationResultObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendOperationResultList, friendOperationResultObj);
                _env->DeleteLocalRef(friendOperationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendOperationResultList);
            _env->DeleteLocalRef(friendOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->DeleteFromBlackList(userIDList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetBlackList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendInfoList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendInfoObj = v2im::jni::FriendInfoJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendInfoList, friendInfoObj);
                _env->DeleteLocalRef(friendInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendInfoList);
            _env->DeleteLocalRef(friendInfoList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetBlackList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeCreateFriendGroup, jstring group_name, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupName = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendOperationResultObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendOperationResultList, friendOperationResultObj);
                _env->DeleteLocalRef(friendOperationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendOperationResultList);
            _env->DeleteLocalRef(friendOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->CreateFriendGroup(groupName, userIDList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetFriendGroups, jobject group_name_list, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector groupNameList;
    int size = v2im::jni::ArrayListJni::Size(group_name_list);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(group_name_list, i);
        groupNameList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendGroupVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendGroupVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendGroupList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendGroupObj = v2im::jni::FriendGroupJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendGroupList, friendGroupObj);
                _env->DeleteLocalRef(friendGroupObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendGroupList);
            _env->DeleteLocalRef(friendGroupList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetFriendGroups(groupNameList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteFriendGroup, jobject group_name_list, jobject callback) {

    V2TIMStringVector groupNameList;
    int size = v2im::jni::ArrayListJni::Size(group_name_list);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(group_name_list, i);
        groupNameList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    v2im::V2IMEngine::GetInstance()->DeleteFriendGroup(groupNameList, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeRenameFriendGroup, jstring old_name, jstring new_name, jobject callback) {

    V2TIMString oldName_str = v2im::jni::StringJni::Jstring2Cstring(env, old_name).c_str();
    V2TIMString newName_str = v2im::jni::StringJni::Jstring2Cstring(env, new_name).c_str();

    v2im::V2IMEngine::GetInstance()->RenameFriendGroup(oldName_str, newName_str, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeAddFriendsToFriendGroup, jstring group_name, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupName = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendOperationResultObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendOperationResultList, friendOperationResultObj);
                _env->DeleteLocalRef(friendOperationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendOperationResultList);
            _env->DeleteLocalRef(friendOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->AddFriendsToFriendGroup(groupName, userIDList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteFriendsFromFriendGroup, jstring group_name, jobject user_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupName = v2im::jni::StringJni::Jstring2Cstring(env, group_name).c_str();

    V2TIMStringVector userIDList;
    int size = v2im::jni::ArrayListJni::Size(user_idlist);
    for (int i = 0; i < size; ++i) {
        auto userID_jStr = (jstring) v2im::jni::ArrayListJni::Get(user_idlist, i);
        userIDList.PushBack(v2im::jni::StringJni::Jstring2Cstring(env, userID_jStr).c_str());
        env->DeleteLocalRef(userID_jStr);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMFriendOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMFriendOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject friendOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject friendOperationResultObj = v2im::jni::FriendOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(friendOperationResultList, friendOperationResultObj);
                _env->DeleteLocalRef(friendOperationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, friendOperationResultList);
            _env->DeleteLocalRef(friendOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->DeleteFriendsFromFriendGroup(groupName, userIDList, value_callback);
}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeInitCplusplusFriendListener", "()V",                                 (void *) NativeInitCplusplusFriendListener},
        {"nativeAddFriendListener",            "(Lcom/tencent/imsdk/v2/V2TIMFriendshipListener;Ljava/lang/String;)V",                                 (void *) NativeAddFriendListener},
        {"nativeRemoveFriendListener",         "(Ljava/lang/String;)V",                                                                                                   (void *) NativeRemoveFriendListener},
        {"nativeGetFriendList",                "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                     (void *) NativeGetFriendList},
        {"nativeGetFriendsInfo",               "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                     (void *) NativeGetFriendsInfo},
        {"nativeSetFriendInfo",                "(Lcom/tencent/imsdk/v2/V2TIMFriendInfo;Lcom/tencent/imsdk/common/IMCallback;)V",           (void *) NativeSetFriendInfo},
        {"nativeSearchFriends",                "(Lcom/tencent/imsdk/v2/V2TIMFriendSearchParam;Lcom/tencent/imsdk/common/IMCallback;)V",    (void *) NativeSearchFriends},
        {"nativeAddFriend",                    "(Lcom/tencent/imsdk/v2/V2TIMFriendAddApplication;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeAddFriend},
        {"nativeDeleteFromFriendList",         "(Ljava/util/List;ILcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeDeleteFromFriendList},
        {"nativeCheckFriend",                  "(Ljava/util/List;ILcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeCheckFriend},
        {"nativeGetFriendApplicationList",     "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                     (void *) NativeGetFriendApplicationList},
        {"nativeAcceptFriendApplication",      "(Lcom/tencent/imsdk/v2/V2TIMFriendApplication;ILcom/tencent/imsdk/common/IMCallback;)V",   (void *) NativeAcceptFriendApplication},
        {"nativeRefuseFriendApplication",      "(Lcom/tencent/imsdk/v2/V2TIMFriendApplication;Lcom/tencent/imsdk/common/IMCallback;)V",    (void *) NativeRefuseFriendApplication},
        {"nativeDeleteFriendApplication",      "(Lcom/tencent/imsdk/v2/V2TIMFriendApplication;Lcom/tencent/imsdk/common/IMCallback;)V",    (void *) NativeDeleteFriendApplication},
        {"nativesSetFriendApplicationRead",    "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                     (void *) NativesSetFriendApplicationRead},
        {"nativeAddToBlackList",               "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                     (void *) NativeAddToBlackList},
        {"nativeDeleteFromBlackList",          "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                     (void *) NativeDeleteFromBlackList},
        {"nativeGetBlackList",                 "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                     (void *) NativeGetBlackList},
        {"nativeCreateFriendGroup",            "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                   (void *) NativeCreateFriendGroup},
        {"nativeGetFriendGroups",              "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                     (void *) NativeGetFriendGroups},
        {"nativeDeleteFriendGroup",            "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                     (void *) NativeDeleteFriendGroup},
        {"nativeRenameFriendGroup",            "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                 (void *) NativeRenameFriendGroup},
        {"nativeAddFriendsToFriendGroup",      "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                   (void *) NativeAddFriendsToFriendGroup},
        {"nativeDeleteFriendsFromFriendGroup", "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                   (void *) NativeDeleteFriendsFromFriendGroup},
};

//注册 native 方法
int RegisterNativeMethodsForV2TIMFriendshipManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMFriendshipManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}

#ifdef __cplusplus
}
#endif
