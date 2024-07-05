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
	/// Source : 事件发起者的标识
	SourceType m_Source;

	/// Action：事件动作的标识
	ActionType m_Action;
};


template<typename SourceType, typename ActionType, typename ResultType>
struct XUANXUE_API FXXEvent_SourceActionWithResult : public FXXEvent_SourceAction<SourceType, ActionType>
{	
public:
	/// Result: Source执行Action产生的结果
	ResultType m_Result;
};
