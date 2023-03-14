#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class FMyCustomCommands : public TCommands<FMyCustomCommands>
{
public:
	FMyCustomCommands();

	// TCommands<>的接口：注册命令
	virtual void RegisterCommands() override;

public:

	//命令A
	TSharedPtr< FUICommandInfo > LevelEditor_MenuBar_Command;

	TSharedPtr< FUICommandInfo > LevelEditor_Menu_Command;

	TSharedPtr< FUICommandInfo > LevelEditor_Toolbar_Command;

	//命令A
	TSharedPtr< FUICommandInfo > CommandA;

	//命令快捷键B
	TSharedPtr< FUICommandInfo > CommandB;

};
