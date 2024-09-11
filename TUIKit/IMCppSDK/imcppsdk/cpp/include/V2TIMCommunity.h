// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef __V2TIM_COMMUNITY_H__
#define __V2TIM_COMMUNITY_H__

#include "V2TIMCallback.h"
#include "V2TIMCommon.h"
#include "V2TIMDefine.h"
#include "V2TIMGroup.h"

/// 话题资料修改标记位
enum V2TIMTopicInfoModifyFlag {
    /// 未定义
    V2TIM_COMMUNITY_MODIFY_FLAG_UNKNOWN = 0x00,
    /// 名称
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_NAME = 0x01,
    /// 公告
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_NOTIFICATION = 0x01 << 1,
    /// 简介
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_INTRODUCTION = 0x01 << 2,
    /// 头像
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_FACE_URL = 0x01 << 3,
    /// 禁言
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_MUTE_ALL = 0x01 << 8,
    /// 话题自定义字段
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_CUSTOM_STRING = 0x1 << 11,
    /// 话题草稿
    V2TIM_COMMUNITY_MODIFY_FLAG_TOPIC_DRAFT = 0x1 << 14,
    /// 话题默认权限，7.8 版本开始支持
    V2TIM_COMMUNITY_MODIFY_FLAG_DEFAULT_PERMISSIONS = 0x1 << 15,
};

/// 权限组修改标记位
enum V2TIMPermissionGroupInfoModifyFlag {
    /// 未定义
    V2TIM_PERMISSION_MODIFY_FLAG_NONE = 0,
    /// 名称
    V2TIM_PERMISSION_MODIFY_FLAG_NAME = 0x1,
    /// 群权限
    V2TIM_PERMISSION_MODIFY_FLAG_GROUP_PERMISSION = 0x1 << 1,
    /// 自定义字段
    V2TIM_PERMISSION_MODIFY_FLAG_CUSTOM_DATA = 0x1 << 2,
};

/// 社群权限能力位
enum V2TIMCommunityPermissionValue {
    /// 修改群资料权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_GROUP_INFO = 0x1,
    /// 群成员管理权限，包含踢人，进群审核、修改成员资料等。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_GROUP_MEMBER = 0x1 << 1,
    /// 管理权限组资料权限，包含创建、修改、删除权限组；在权限组中添加、修改、删除话题权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_MANAGE_PERMISSION_GROUP_INFO = 0x1 << 2,
    /// 权限组成员管理权限，包含邀请成员进权限组和把成员从权限组踢出等。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_PERMISSION_GROUP_MEMBER = 0x1 << 3,
    /// 话题管理权限，包含创建、修改、删除话题等。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_TOPIC_IN_COMMUNITY = 0x1 << 4,
    /// 对某群成员在社群下所有话题的禁言权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_MUTE_MEMBER = 0x1 << 5,
    /// 群成员在社群下所有话题的发消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_SEND_MESSAGE = 0x1 << 6,
    /// 在社群下所有话题发 at all 消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_AT_ALL = 0x1 << 7,
    /// 在社群下所有话题拉取入群前的历史消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_GET_HISTORY_MESSAGE = 0x1 << 8,
    /// 在社群下所有话题撤回他人消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_REVOKE_OTHER_MEMBER_MESSAGE = 0x1 << 9,
    /// 封禁社群成员权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_BAN_MEMBER = 0x1 << 10,
};

/// 话题权限能力位
enum V2TIMTopicPermissionValue {
    /// 管理指定话题权限，包含修改、删除话题。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC = 0x1,
    /// 在话题中管理话题权限，包含添加、修改、移除话题权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC_PERMISSION = 0x1 << 1,
    /// 在话题中禁言成员权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_MUTE_MEMBER = 0x1 << 2,
    /// 在话题中发消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_SEND_MESSAGE = 0x1 << 3,
    /// 在话题中拉取入群前的历史消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_GET_HISTORY_MESSAGE = 0x1 << 4,
    /// 在话题中撤回他人消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_REVOKE_OTHER_MEMBER_MESSAGE = 0x1 << 5,
    /// 在话题中发消息时有 at all 权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_AT_ALL = 0x1 << 6,
};

/////////////////////////////////////////////////////////////////////////////////
//
// 话题基本资料
//
/////////////////////////////////////////////////////////////////////////////////

struct V2TIMMessage;

struct TIM_API V2TIMTopicInfo : V2TIMBaseObject {
    /// 话题 ID，只能在创建话题或者修改话题信息的时候设置。组成方式为：社群 ID + @TOPIC#_xxx，例如社群 ID 为 @TGS#_123，则话题 ID 为 @TGS#_123@TOPIC#_xxx
    V2TIMString topicID;
    /// 话题名称，最长 150 字节，使用 UTF-8 编码
    V2TIMString topicName;
    /// 话题头像，最长 500 字节，使用 UTF-8 编码
    V2TIMString topicFaceURL;
    /// 话题介绍，最长 400 字节，使用 UTF-8 编码
    V2TIMString introduction;
    /// 话题公告，最长 400 字节，使用 UTF-8 编码
    V2TIMString notification;
    /// 话题全员禁言
    bool isAllMuted;
    /// 当前用户在话题中的禁言时间
    uint32_t selfMuteTime;
    /// 话题自定义字段
    V2TIMString customString;
    /// 话题消息接收选项，修改话题消息接收选项请调用 setGroupReceiveMessageOpt 接口
    V2TIMReceiveMessageOpt recvOpt;
    /// 话题草稿
    V2TIMString draftText;
    /// 话题消息未读数量
    uint64_t unreadCount;
    /// 话题 lastMessage
    V2TIMMessage *lastMessage;
    /// 话题已读消息的 sequence，从 7.8 版本开始支持
    uint64_t readSequence;
    /// 话题 at 信息列表
    V2TIMGroupAtInfoVector groupAtInfoList;
    /// 话题创建时间，单位：秒
    uint32_t createTime;
    /// 话题默认权限，7.8 版本开始支持
    /// 群成员在没有加入任何权限组时的默认权限，仅在社群资料 V2TIMGroupInfo 中 enablePermissionGroup = true 打开权限组之后生效
    uint64_t defaultPermissions;
    /**
     * 获取登录用户在话题中的消息接收选项是否继承社群。该功能仅增强版 SDK 8.1 及以上版本支持
     */
    bool IsInheritMessageReceiveOptionFromCommunity();
    /**
     * 设置登录用户在话题中的消息接收选项是否继承社群。该功能仅增强版 SDK 8.1 及以上版本支持
     */
    void SetInheritMessageReceiveOptionFromCommunity(bool isInherit, V2TIMCallback* callback);

    /// 话题资料修改标记位
    /// 枚举 V2TIMGroupInfoModifyFlag 列出哪些字段支持修改，如果您修改群资料，请设置这个字段值
    /// 如果您同时修改多个字段，多个枚举值按位或 | 组合，例如，同时修改群名称和头像
    /// info.topicName = "new group name";
    /// info.topicFaceURL = "new face url";
    /// info.modifyFlag = V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_NAME |
    /// V2TIM_GROUP_INFO_MODIFY_FLAG_FACE_URL;
    uint32_t modifyFlag;

    V2TIMTopicInfo();
    V2TIMTopicInfo(const V2TIMTopicInfo& topicInfo);
    V2TIMTopicInfo& operator=(const V2TIMTopicInfo& topicInfo);
    ~V2TIMTopicInfo() override;
};

/////////////////////////////////////////////////////////////////////////////////
//
// 话题处理结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMTopicOperationResult {
    /// 结果 0：成功；非0：失败
    int32_t errorCode;
    /// 如果删除失败，会返回错误信息
    V2TIMString errorMsg;
    /// 如果删除成功，会返回对应的 topicID
    V2TIMString topicID;

    V2TIMTopicOperationResult();
    V2TIMTopicOperationResult(const V2TIMTopicOperationResult& result);
    ~V2TIMTopicOperationResult();
};

DEFINE_VECTOR(V2TIMTopicOperationResult)
typedef TXV2TIMTopicOperationResultVector V2TIMTopicOperationResultVector;

/////////////////////////////////////////////////////////////////////////////////
//
// 话题资料获取结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMTopicInfoResult {
    /// 结果 0：成功；非0：失败
    int32_t errorCode;
    /// 如果获取失败，会返回错误信息
    V2TIMString errorMsg;
    /// 如果获取成功，会返回对应的 info
    V2TIMTopicInfo topicInfo;

    V2TIMTopicInfoResult();
    V2TIMTopicInfoResult(const V2TIMTopicInfoResult& result);
    ~V2TIMTopicInfoResult();
};

DEFINE_VECTOR(V2TIMTopicInfoResult)
typedef TXV2TIMTopicInfoResultVector V2TIMTopicInfoResultVector;

/////////////////////////////////////////////////////////////////////////////////
//
// 权限组信息
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMPermissionGroupInfo {
    /// 群 ID
    V2TIMString groupID;
    /// 权限组 ID
    V2TIMString permissionGroupID;
    /// 权限组名称
    V2TIMString permissionGroupName;
    /// 权限组自定义字段
    V2TIMString customData;
    /// 群权限
    uint64_t groupPermission;
    /// 权限组当前人数
    uint64_t memberCount;
    /// 权限组资料修改标记位
    /// 枚举 V2TIMPermissionGroupInfoModifyFlag 列出哪些字段支持修改，如果您修改权限组资料，请设置这个字段值
    /// 如果您同时修改多个字段，多个枚举值按位或 | 组合，例如，同时修改群名称和头像
    /// info.permissionGroupName = "new permission group name";
    /// info.customData = "new custom data";
    /// info.modifyFlag = V2TIM_PERMISSION_MODIFY_FLAG_NAME | V2TIM_PERMISSION_MODIFY_FLAG_CUSTOM_STRING;
    uint32_t modifyFlag;

    V2TIMPermissionGroupInfo();
    V2TIMPermissionGroupInfo(const V2TIMPermissionGroupInfo& info);
    ~V2TIMPermissionGroupInfo();
};

/////////////////////////////////////////////////////////////////////////////////
//
// 权限组信息获取结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMPermissionGroupInfoResult {
    /// 结果 0：成功；非0：失败
    int resultCode;
    /// 如果获取失败，会返回错误信息
    V2TIMString resultMsg;
    /// 如果获取成功，会返回对应的 info
    V2TIMPermissionGroupInfo info;

    V2TIMPermissionGroupInfoResult();
    V2TIMPermissionGroupInfoResult(const V2TIMPermissionGroupInfoResult& permissionGroupInfoResult);
    ~V2TIMPermissionGroupInfoResult();
};

DEFINE_VECTOR(V2TIMPermissionGroupInfoResult)
typedef TXV2TIMPermissionGroupInfoResultVector V2TIMPermissionGroupInfoResultVector;

/////////////////////////////////////////////////////////////////////////////////
//
// 权限组处理结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMPermissionGroupOperationResult {
    /// 结果 0：成功；非0：失败
    int resultCode;
    /// 如果处理失败，会返回错误信息
    V2TIMString resultMsg;
    /// 权限组 ID
    V2TIMString permissionGroupID;

    V2TIMPermissionGroupOperationResult();
    V2TIMPermissionGroupOperationResult(const V2TIMPermissionGroupOperationResult& operationResult);
    ~V2TIMPermissionGroupOperationResult();
};

DEFINE_VECTOR(V2TIMPermissionGroupOperationResult)
typedef TXV2TIMPermissionGroupOperationResultVector V2TIMPermissionGroupOperationResultVector;

/////////////////////////////////////////////////////////////////////////////////
//
// 权限组成员获取结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMPermissionGroupMemberInfoResult {
    /// 分页拉取的游标
    V2TIMString nextCursor;
    /// 群成员列表
    V2TIMGroupMemberInfoVector memberInfoList;

    V2TIMPermissionGroupMemberInfoResult();
    V2TIMPermissionGroupMemberInfoResult(const V2TIMPermissionGroupMemberInfoResult& result);
    ~V2TIMPermissionGroupMemberInfoResult();
};

/////////////////////////////////////////////////////////////////////////////////
//
// 权限组成员处理结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMPermissionGroupMemberOperationResult {
    /// 被操作成员
    V2TIMString memberID;
    /// 结果 0：成功；非0：失败
    int resultCode;

    V2TIMPermissionGroupMemberOperationResult();
    V2TIMPermissionGroupMemberOperationResult(
            const V2TIMPermissionGroupMemberOperationResult& memberOperationResult);
    ~V2TIMPermissionGroupMemberOperationResult();
};

DEFINE_VECTOR(V2TIMPermissionGroupMemberOperationResult)
typedef TXV2TIMPermissionGroupMemberOperationResultVector V2TIMPermissionGroupMemberOperationResultVector;

/////////////////////////////////////////////////////////////////////////////////
//
// 话题权限获取结果
//
/////////////////////////////////////////////////////////////////////////////////

struct TIM_API V2TIMTopicPermissionResult {
    /// 话题 ID
    V2TIMString topicID;
    /// 结果 0：成功；非0：失败
    int resultCode;
    /// 如果处理失败，会返回错误信息
    V2TIMString resultMsg;
    /// 话题权限
    uint64_t topicPermission;
    /// 社群 ID
    V2TIMString groupID;
    /// 权限组 ID
    V2TIMString permissionGroupID;

    V2TIMTopicPermissionResult();
    V2TIMTopicPermissionResult(const V2TIMTopicPermissionResult& topicPermissionResult);
    ~V2TIMTopicPermissionResult();
};

DEFINE_VECTOR(V2TIMTopicPermissionResult)
typedef TXV2TIMTopicPermissionResultVector V2TIMTopicPermissionResultVector;

#endif  // __V2TIM_COMMUNITY_H__
