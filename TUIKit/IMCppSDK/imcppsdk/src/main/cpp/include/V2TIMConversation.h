// Copyright (c) 2021 Tencent. All rights reserved.

#ifndef __V2TIM_CONVERSATION_H__
#define __V2TIM_CONVERSATION_H__

#include "V2TIMCommon.h"
#include "V2TIMMessage.h"
#include "V2TIMString.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                    （一）枚举值定义
//
/////////////////////////////////////////////////////////////////////////////////

/// 会话类型
enum V2TIMConversationType {
    ///< 未知
    V2TIM_UNKNOWN = 0,
    ///< 单聊
    V2TIM_C2C = 1,
    ///< 群聊
    V2TIM_GROUP = 2,
};

/// 会话标记类型
enum V2TIMConversationMarkType {
    ///< 会话标星
    V2TIM_CONVERSATION_MARK_TYPE_STAR     = 0x1,
    ///< 会话标记未读（重要会话）
    V2TIM_CONVERSATION_MARK_TYPE_UNREAD   = 0x1 << 1,
    ///< 会话折叠
    V2TIM_CONVERSATION_MARK_TYPE_FOLD     = 0x1 << 2,
    ///< 会话隐藏
    V2TIM_CONVERSATION_MARK_TYPE_HIDE     = 0x1 << 3,
};

/////////////////////////////////////////////////////////////////////////////////
//
//                     （二）结构体定义
//
/////////////////////////////////////////////////////////////////////////////////

DEFINE_VECTOR(uint64_t)
typedef TXuint64_tVector UInt64Vector;

/// 会话对象
struct TIM_API V2TIMConversation {
    /// 会话类型
    V2TIMConversationType type;
    /// 会话唯一 ID，如果是 C2C 单聊，组成方式为 c2c_userID，如果是群聊，组成方式为 group_groupID
    V2TIMString conversationID;
    /// 如果会话类型为 C2C 单聊，userID 会存储对方的用户ID，否则为空字符串
    V2TIMString userID;
    /// 如果会话类型为群聊，groupID 会存储当前群的群 ID，否则为空字符串
    V2TIMString groupID;
    /// 如果会话类型为群聊，groupType 为当前群类型，否则为空字符串
    V2TIMString groupType;
    /// 会话展示名称（群组：群名称 >> 群 ID；C2C：对方好友备注 >> 对方昵称 >> 对方的 userID）
    V2TIMString showName;
    /// 会话展示头像（群组：群头像；C2C：对方头像）
    V2TIMString faceUrl;
    /// 会话未读消息数量,直播群（AVChatRoom）不支持未读计数，默认为 0
    int unreadCount;
    /// 消息接收选项（接收 | 接收但不提醒 | 不接收）
    V2TIMReceiveMessageOpt recvOpt;
    /// 会话最后一条消息，如果会话没有消息，lastMessage 字段为 NULL
    /// 5.5.892 以前版本，请您使用 lastMessage -> timestamp 对会话做排序，timestamp 越大，会话越靠前
    V2TIMMessage *lastMessage;
    /// 群会话 @ 信息列表，用于展示 “有人@我” 或 “@所有人” 这两种提醒状态
    V2TIMGroupAtInfoVector groupAtInfolist;
    /// 草稿信息，设置草稿信息请调用 SetConversationDraft() 接口
    V2TIMString draftText;
    /// 上次设置草稿时的 UTC 时间戳
    uint64_t draftTimestamp;
    /// 是否置顶
    bool isPinned;
    // 排序字段（5.5.892 及以后版本支持）
    // @note
    // - 排序字段 orderKey
    // 是按照会话的激活时间线性递增的一个数字（注意：不是时间戳，因为同一时刻可能会有多个会话被同时激活）
    // - 5.5.892 及其以后版本，推荐您使用该字段对所有会话进行排序，orderKey
    // 值越大，代表该会话排序越靠前
    // - 当您 “清空会话所有消息” 或者 “逐个删除会话的所有消息” 之后，会话的 lastMessage
    // 变为空，但会话的 orderKey
    // 不会改变；如果想保持会话的排序位置不变，可以使用该字段对所有会话进行排序
    uint64_t orderKey;
    /// 会话标记列表，取值详见 @V2TIMConversationMarkType（从 6.5 版本开始支持）
    TXV2TIMUInt64Vector markList;
    /// 会话自定义数据（从 6.5 版本开始支持）
    V2TIMBuffer customData;
    /// 会话所属分组列表（从 6.5 版本开始支持）
    V2TIMStringVector conversationGroupList;
    /// 最新已读消息的 UTC 时间戳，仅对单聊会话生效（从 7.1 版本开始支持）
    uint64_t c2cReadTimestamp;
    /// 已读消息的 sequence，仅对群聊会话生效（从 7.1 版本开始支持）
    uint64_t groupReadSequence;

    V2TIMConversation();
    V2TIMConversation(const V2TIMConversation& conversation);
    V2TIMConversation& operator =(const V2TIMConversation& conversation);
    ~V2TIMConversation();
};

DEFINE_VECTOR(V2TIMConversation)
typedef TXV2TIMConversationVector V2TIMConversationVector;

/// 会话 filter
struct TIM_API V2TIMConversationListFilter {
    /// C2C 或群会话(填 0 代表不过滤此项)
    V2TIMConversationType type;
    /// 会话分组名称(填空代表不过滤此项)
    V2TIMString conversationGroup;
    /// 标记类型，取值详见 @V2TIMConversationMarkType(填 0 代表不过滤此项)
    uint64_t markType;
    /// 设置为 true 时返回包含未读数的会话；设置为 false 时返回所有会话（默认值是 false）
    bool hasUnreadCount;
    /// 设置为 true 时返回包含群 @ 消息的会话；设置为 false 时返回所有会话（默认值是 false）
    bool hasGroupAtInfo;
    
    V2TIMConversationListFilter();
    V2TIMConversationListFilter(const V2TIMConversationListFilter& filter);
    V2TIMConversationListFilter& operator =(const V2TIMConversationListFilter& filter);
    ~V2TIMConversationListFilter();
};

/// 获取会话列表结果
struct TIM_API V2TIMConversationResult  {
    /// 获取下一次分页拉取的游标
    uint64_t nextSeq;
    /// 会话列表是否已经拉取完毕
    bool isFinished;
    /// 获取会话列表
    V2TIMConversationVector conversationList;

    V2TIMConversationResult();
    V2TIMConversationResult(const V2TIMConversationResult& conversationResult);
    V2TIMConversationResult& operator=(const V2TIMConversationResult& conversationResult);
    ~V2TIMConversationResult();
};

/// 会话操作结果
struct TIM_API V2TIMConversationOperationResult {
    /// 会话 ID
    V2TIMString conversationID;
    /// 返回码
    int resultCode;
    /// 返回信息
    V2TIMString resultInfo;

    V2TIMConversationOperationResult();
    V2TIMConversationOperationResult(const V2TIMConversationOperationResult &result);
    ~V2TIMConversationOperationResult();
    V2TIMConversationOperationResult& operator=(const V2TIMConversationOperationResult &result);
};

DEFINE_VECTOR(V2TIMConversationOperationResult)
typedef TXV2TIMConversationOperationResultVector V2TIMConversationOperationResultVector;

#endif /* __V2TIM_CONVERSATION_H__ */
