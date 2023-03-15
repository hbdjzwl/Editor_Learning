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
};


//命令A
TSharedPtr< FUICommandInfo > CommandA;

//命令快捷键B
TSharedPtr< FUICommandInfo > CommandB;