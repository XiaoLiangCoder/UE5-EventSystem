// Copyright TanXiaoliang. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"


enum class EXXPublishEventMode : uint8
{
	Direct,			/// 点对点
	Broadcast,		/// 点对多

};

/**
 * 事件系统
 *		1. EventType：事件类型。类型可以是class、struct、enum、GameplayTag、FName、FString、int、...
 *		2. Event不应该有逻辑，只期望有数据。
 *		3. 每一类EventType类型的事件（类型相当于一个Id），都有一个全新的TXXEventSystem类去传递事件消息
 */
template<typename EventType, EXXPublishEventMode Mode = EXXPublishEventMode::Direct>
class XUANXUE_API TXXEventSystem
{
public:
	using FDelegate = TDelegate<void( const EventType& )>; /// Direct delegate

private:
	using FBroadcastDelegate = TMulticastDelegate<void( const EventType& )>;
	static constexpr bool s_bIsDirectMode = ( Mode == EXXPublishEventMode::Direct );
	using FObserverDelegate = std::conditional_t<s_bIsDirectMode, FDelegate, FBroadcastDelegate>;

	/// <summary>
	/// 事件观察者注册的delegate。组合模式的delegate观察者比继承模式观察者更灵活。
	/// </summary>
	FObserverDelegate m_ObserverDelegate;

private:
	/// Private构造函数可以防止外部意外创建
	TXXEventSystem( )
	{
		/// 绑定回调===>在切换World时清空所有事件观察者
		FWorldDelegates::OnPostWorldCleanup.AddLambda( 
			[]( UWorld* _pWorld, bool, bool )
			{
				if constexpr ( s_bIsDirectMode )
				{
					GetInstance( ).m_ObserverDelegate.Unbind( );
				}
				else
				{
					GetInstance( ).m_ObserverDelegate.Clear( );
				}
			} );
	};

	/// 删除不需要的构造函数
	TXXEventSystem( const TXXEventSystem<EventType>& ) = delete;
	TXXEventSystem( const TXXEventSystem<EventType>&& ) = delete;

	/// 删除不需要的赋值运算符
	TXXEventSystem<EventType>& operator=( const TXXEventSystem<EventType>& ) = delete;
	TXXEventSystem<EventType>& operator=( const TXXEventSystem<EventType>&& ) = delete;
	
public:
	/// 单例模式：每一个类EventType都有一个s_Instance单例
	static TXXEventSystem<EventType, Mode>& GetInstance( )
	{
		static TXXEventSystem<EventType, Mode> s_Instance;
		return s_Instance;
	};

	/// <summary>
	/// 注册事件接收者
	/// </summary>
	auto RegisterObserver( FDelegate&& _InDelegate )
	{
		if constexpr ( s_bIsDirectMode )
		{
			m_ObserverDelegate = std::move( _InDelegate );
		}
		else
		{
			return m_ObserverDelegate.Add( std::move( _InDelegate ) );
		}
	};

	/// <summary>
	/// 取消注册事件接收者
	/// </summary>
	template<typename = typename std::enable_if_t<s_bIsDirectMode>>
	void UnregisterObserver( )
	{
		m_ObserverDelegate.Unbind( );
	};

	template<typename = typename std::enable_if_t<Mode == EXXPublishEventMode::Broadcast>>
	void UnregisterObserver( const FDelegateHandle& _InHandle )
	{
		m_ObserverDelegate.Remove( _InHandle );
	};

	/// <summary>
	/// 发布事件
	/// </summary>
	void PublishEvent( const EventType& _pEvent )
	{
		if constexpr ( Mode == EXXPublishEventMode::Direct )
		{
			m_ObserverDelegate.ExecuteIfBound( _pEvent );
		}
		else
		{
			m_ObserverDelegate.Broadcast( _pEvent );
		}
	};
};


