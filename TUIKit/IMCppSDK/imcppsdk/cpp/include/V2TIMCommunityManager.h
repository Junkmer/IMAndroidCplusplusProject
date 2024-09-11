// Copyright (c) 2023 Tencent. All rights reserved.

/////////////////////////////////////////////////////////////////////
//
//                     腾讯云通信服务 IMSDK
//
//   社群接口，里面包含了社群相关的功能，比如创建话题，修改话题等操作接口。
//
/////////////////////////////////////////////////////////////////////

#ifndef __V2TIM_COMMUNITY_MANAGER_H__
#define __V2TIM_COMMUNITY_MANAGER_H__

#include "V2TIMCallback.h"
#include "V2TIMCommunity.h"
#include "V2TIMDefine.h"
#include "V2TIMListener.h"

class TIM_API V2TIMCommunityManager {
public:
    virtual ~V2TIMCommunityManager() {}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                         社群监听
    //
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * 1.1 添加社群监听器
     */
    virtual void AddCommunityListener(V2TIMCommunityListener *listener) = 0;

    /**
     * 1.2 移除社群监听器
     */
    virtual void RemoveCommunityListener(V2TIMCommunityListener *listener) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                         社群接口
    //
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * 2.1 创建支持话题的社群
     */
    virtual void CreateCommunity(const V2TIMGroupInfo &info, const V2TIMCreateGroupMemberInfoVector &memberList,
                                 V2TIMValueCallback<V2TIMString> *callback) = 0;
    /**
     * 2.2 获取当前用户已经加入的支持话题的社群列表
     */
    virtual void GetJoinedCommunityList(V2TIMValueCallback<V2TIMGroupInfoVector> *callback) = 0;

    /**
     * 2.3 创建话题
     *
     * @param groupID 社群 ID，必须以 @TGS#_ 开头。
     */
    virtual void CreateTopicInCommunity(const V2TIMString &groupID, const V2TIMTopicInfo &topicInfo,
                                        V2TIMValueCallback<V2TIMString> *callback) = 0;

    /**
     * 2.4 删除话题
     */
    virtual void DeleteTopicFromCommunity(const V2TIMString &groupID, const V2TIMStringVector &topicIDList,
                                          V2TIMValueCallback<V2TIMTopicOperationResultVector> *callback) = 0;

    /**
     * 2.5 修改话题信息
     */
    virtual void SetTopicInfo(const V2TIMTopicInfo &topicInfo, V2TIMCallback *callback) = 0;

    /**
     * 2.6 获取话题列表。
     * @note: topicIDList 传空时，获取此社群下的所有话题列表
     */
    virtual void GetTopicInfoList(const V2TIMString &groupID, const V2TIMStringVector &topicIDList,
                                  V2TIMValueCallback<V2TIMTopicInfoResultVector> *callback) = 0;

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                         权限组相关的接口
    //
    /////////////////////////////////////////////////////////////////////////////////

    /**
     * 3.1 创建社群权限组（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void CreatePermissionGroupInCommunity(const V2TIMPermissionGroupInfo &info,
                                                  V2TIMValueCallback<V2TIMString> *callback) = 0;

    /**
     * 3.2 删除社群权限组（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void DeletePermissionGroupFromCommunity(
        const V2TIMString &groupID, const V2TIMStringVector &permissionGroupIDList,
        V2TIMValueCallback<V2TIMPermissionGroupOperationResultVector> *callback) = 0;

    /**
     * 3.3 修改社群权限组（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void ModifyPermissionGroupInfoInCommunity(const V2TIMPermissionGroupInfo &info,
                                                      V2TIMCallback *callback) = 0;

    /**
     * 3.4 获取已加入的社群权限组列表（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void GetJoinedPermissionGroupListInCommunity(
        const V2TIMString &groupID, V2TIMValueCallback<V2TIMPermissionGroupInfoResultVector> *callback) = 0;

    /**
     * 3.5 获取社群权限组列表（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     * - permissionGroupIDList 为空时，获取所有的权限组列表；不为空时，获取指定的权限组列表。
     */
    virtual void GetPermissionGroupListInCommunity(
        const V2TIMString &groupID, const V2TIMStringVector &permissionGroupIDList,
        V2TIMValueCallback<V2TIMPermissionGroupInfoResultVector> *callback) = 0;

    /**
     * 3.6 向社群权限组添加成员（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void AddCommunityMembersToPermissionGroup(
        const V2TIMString &groupID, const V2TIMString &permissionGroupID, const V2TIMStringVector &memberList,
        V2TIMValueCallback<V2TIMPermissionGroupMemberOperationResultVector> *callback) = 0;

    /**
     * 3.7 从社群权限组删除成员（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void RemoveCommunityMembersFromPermissionGroup(
        const V2TIMString &groupID, const V2TIMString &permissionGroupID, const V2TIMStringVector &memberList,
        V2TIMValueCallback<V2TIMPermissionGroupMemberOperationResultVector> *callback) = 0;

    /**
     * 3.8 获取社群权限组成员列表（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void GetCommunityMemberListInPermissionGroup(
        const V2TIMString &groupID, const V2TIMString &permissionGroupID, const V2TIMString &nextCursor,
        V2TIMValueCallback<V2TIMPermissionGroupMemberInfoResult> *callback) = 0;

    /**
     * 3.9 向权限组添加话题权限（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void AddTopicPermissionToPermissionGroup(const V2TIMString &groupID, const V2TIMString &permissionGroupID,
                                                     const V2TIMStringToUint64Map &topicPermissionMap,
                                                     V2TIMValueCallback<V2TIMTopicOperationResultVector> *callback) = 0;

    /**
     * 3.10 从权限组中删除话题权限（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void DeleteTopicPermissionFromPermissionGroup(
        const V2TIMString &groupID, const V2TIMString &permissionGroupID, const V2TIMStringVector &topicIDList,
        V2TIMValueCallback<V2TIMTopicOperationResultVector> *callback) = 0;

    /**
     * 3.11 修改权限组中的话题权限（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void ModifyTopicPermissionInPermissionGroup(
            const V2TIMString &groupID, const V2TIMString &permissionGroupID,
            const V2TIMStringToUint64Map &topicPermissionMap,
            V2TIMValueCallback<V2TIMTopicOperationResultVector> *callback) = 0;

    /**
     * 3.12 获取权限组中的话题权限（7.8 及其以上版本支持）
     * @note
     * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
     */
    virtual void GetTopicPermissionInPermissionGroup(
            const V2TIMString &groupID, const V2TIMString &permissionGroupID,
            const V2TIMStringVector &topicIDList, V2TIMValueCallback<V2TIMTopicPermissionResultVector> *callback) = 0;
};

#endif  // __V2TIM_COMMUNITY_MANAGER_H__
