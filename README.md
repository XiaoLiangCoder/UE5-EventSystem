# UE5-EventSystem
UE5事件系统

使用例子:
1. 声明
   ```
    /// 声明Menu事件
    using FXXEventForMenu = FXXEvent_SourceAction<const FGameplayTag&, const FGameplayTag&>;
    using FXXEventSystemForMenu = TXXEventSystem<FXXEventForMenu>;
   ```
2. 注册事件接收者
   ```
   /// 创建和注册事件接收者
   FXXEventSystemForMenu::GetInstance( ).RegisterObserver(
   FXXEventSystemForMenu::FDelegate::CreateUObject( this, &UXXGFS_MenuBase::ProcessMenuEvent ) );
   ```
3. 发送事件
   ```
   /// m_OptionTag和ActionTag均为FGameplayTag类型
   FXXEventForMenu Event( m_OptionTag, ActionTag );
   /// 通知Menu事件接收者GFS，该Option被点击
   FXXEventSystemForMenu::GetInstance( ).PublishEvent( Event );
   ```
