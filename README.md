# UE5-EventSystem
UE5事件系统

使用例子：
1. 声明
   '''C++
    /// 声明Menu事件
    using FXXEventForMenu = FXXEvent_SourceAction<const FGameplayTag&, const FGameplayTag&>;
    using FXXEventSystemForMenu = TXXEventSystem<FXXEventForMenu>;
   '''
3. 注册事件接收者
   '''C++
   /// 创建和注册事件接收者
   FXXEventSystemForMenu::GetInstance( ).RegisterObserver(
   FXXEventSystemForMenu::FDelegate::CreateUObject( this, &UXXGFS_MenuBase::ProcessMenuEvent ) );
   '''
5. 发送事件
   '''C++
   /// m_OptionTag和ActionTag均为
   FXXEventForMenu Event( m_OptionTag, ActionTag );
   /// 通知Menu事件接收者GFS，该Option被点击FGameplayTag类型
   FXXEventSystemForMenu::GetInstance( ).PublishEvent( Event );
   '''
