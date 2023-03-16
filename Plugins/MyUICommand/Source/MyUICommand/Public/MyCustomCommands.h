#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class FMyCustomCommands : public TCommands<FMyCustomCommands>
{
public:
	FMyCustomCommands();

	// TCommands注册命令的接口
	virtual void RegisterCommands() override;

public:
	//菜单栏命令
	TSharedPtr< FUICommandInfo > LevelEditor_MenuBar_Command;

	//菜单命令
	TSharedPtr< FUICommandInfo > LevelEditor_Menu_Command;

	//工具栏命令
	TSharedPtr< FUICommandInfo > LevelEditor_TooolBar_Command;



	//内容浏览器右键菜单
	TSharedPtr< FUICommandInfo > ContentBrowser_SelectRightMouseMenu;

	//内容浏览器快捷键
	TSharedPtr< FUICommandInfo > ContentBrowser_ShortcutKey;




	//资源编辑器菜单命令
	TSharedPtr< FUICommandInfo > AssetEditor_Menu_Command;

	//资源编辑器工具栏命令
	TSharedPtr< FUICommandInfo > AssetEditor_TooolBar_Command;
};


