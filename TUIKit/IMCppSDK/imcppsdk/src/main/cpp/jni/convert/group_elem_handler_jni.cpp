//
// Created by Junker on 2022/9/22.
//

#include <jni_helper.h>
#include "group_elem_handler_jni.h"
#include "java_basic_jni.h"
#include "group_member_info_jni.h"
#include "group_change_info_jni.h"
#include "group_member_change_info_jni.h"

namespace v2im {
    namespace jni {

        std::string GroupElemHandlerJni::GetHandlerType() {
            return "GroupElemHandlerJni";
        }

        bool GroupElemHandlerJni::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupTipsElem");
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

            jmethod = env->GetMethodID(j_cls_, "addMember", "(Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddMember] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addGroupChangeInfo", "(Lcom/tencent/imsdk/v2/V2TIMGroupChangeInfo;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddGroupChangeInfo] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addMemberChangeInfo", "(Lcom/tencent/imsdk/v2/V2TIMGroupMemberChangeInfo;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDAddMemberChangeInfo] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetFieldID(j_cls_,"groupID", "Ljava/lang/String;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDGroupID] = jfield;

            jfield = env->GetFieldID(j_cls_,"type", "I");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDType] = jfield;

            jfield = env->GetFieldID(j_cls_,"opMember", "Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDOpMember] = jfield;

            jfield = env->GetFieldID(j_cls_,"memberList", "Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDMemberList] = jfield;

            jfield = env->GetFieldID(j_cls_,"groupChangeInfoList", "Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDGroupChangeInfoList] = jfield;

            jfield = env->GetFieldID(j_cls_,"memberChangeInfoList", "Ljava/util/List;");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDMemberChangeInfoList] = jfield;

            jfield = env->GetFieldID(j_cls_,"memberCount", "I");
            if (nullptr == jfield){
                return false;
            }
            j_field_array_[FieldIDMemberCount] = jfield;

            return true;
        }

        jobject GroupElemHandlerJni::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_GROUP_TIPS) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *groupTipsElem = (V2TIMGroupTipsElem *) elem;

            auto *jElemObj = env->NewObject(j_cls_, j_method_id_array_[MethodIDConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetObjectField(jElemObj, j_field_array_[FieldIDGroupID], StringJni::Cstring2Jstring(env, groupTipsElem->groupID.CString()));
            env->SetIntField(jElemObj, j_field_array_[FieldIDType], (jint) groupTipsElem->type);

            jobject opMemberObj = GroupMemberInfoJni::Convert2JObject(groupTipsElem->opMember);
            env->SetObjectField(jElemObj, j_field_array_[FieldIDOpMember], opMemberObj);
            env->DeleteLocalRef(opMemberObj);

            for (int i = 0; i < groupTipsElem->memberList.Size(); ++i) {
                jobject memberObj = GroupMemberInfoJni::Convert2JObject(groupTipsElem->memberList[i]);
                env->CallVoidMethod(jElemObj, j_method_id_array_[MethodIDAddMember], memberObj);
                env->DeleteLocalRef(memberObj);
            }

            for (int i = 0; i < groupTipsElem->groupChangeInfoList.Size(); ++i) {
                jobject infoChangeObj = GroupChangeInfoJni::Convert2JObject(groupTipsElem->groupChangeInfoList[i]);
                env->CallVoidMethod(jElemObj, j_method_id_array_[MethodIDAddGroupChangeInfo], infoChangeObj);
                env->DeleteLocalRef(infoChangeObj);
            }

            for (int i = 0; i < groupTipsElem->memberChangeInfoList.Size(); ++i) {
                jobject memberInfoChangeObj = GroupMemberChangeInfoJni::Convert2JObject(groupTipsElem->memberChangeInfoList[i]);
                env->CallVoidMethod(jElemObj, j_method_id_array_[MethodIDAddMemberChangeInfo], memberInfoChangeObj);
                env->DeleteLocalRef(memberInfoChangeObj);
            }

            env->SetIntField(jElemObj, j_field_array_[FieldIDMemberCount], (jint) groupTipsElem->memberCount);

            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> GroupElemHandlerJni::Convert2CoreObject(int elemType, jobject jElemObj) {
            return nullptr;
        }
    }// namespace jni
}// namespace v2im