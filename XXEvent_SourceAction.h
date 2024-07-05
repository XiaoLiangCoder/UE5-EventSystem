// Copyright TanXiaoliang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


/**
 * 具体事件: Source和Action事件
 *		1. SourceType/ActionType可以是class、struct、enum、GameplayTag、FName、FString、int...
 */
template<typename SourceType, typename ActionType>
struct XUANXUE_API FXXEvent_SourceAction
{
public:
	FXXEvent_SourceAction( SourceType&& _InSource, ActionType&& _InAction )
		:m_Source( _InSource ), m_Action( _InAction ) {};

public:
	/// Source : 事件发起者的标识
	SourceType m_Source;

	/// Action：事件动作的标识
	ActionType m_Action;
};


template<typename SourceType, typename ActionType, typename ResultType>
struct XUANXUE_API FXXEvent_SourceActionWithResult : public FXXEvent_SourceAction<SourceType, ActionType>
{
public:
	/// 万能引用(&&) + 完美转发(std::forward)
	FXXEvent_SourceActionWithResult( SourceType&& _InSource, ActionType&& _InAction, ResultType&& _InResult )
		:FXXEvent_SourceAction<SourceType, ActionType>( 
			std::forward<SourceType>( _InSource ), std::forward<ActionType>( _InAction ) ), m_Result{ _InResult }{};
	
public:
	/// Result: Source执行Action产生的结果
	ResultType m_Result;
};
