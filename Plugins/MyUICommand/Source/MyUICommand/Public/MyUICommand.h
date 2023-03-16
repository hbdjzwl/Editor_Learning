// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "ContentBrowserDelegates.h"

class FMyUICommandModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//辅助函数:获取所有选择的资产
	void GetSelectAllAssets(FOnContentBrowserGetSelection GetSelectionDelegate);

	//注册所有命令
	void RegisterAllCommand();

	//关卡编辑器
	void CreateLevelEditorWidget();

	//内容浏览器
	void CreateContentBrowserWidget();

	//资产编辑器:创建资产UI、及注册映射命令
	void CreateAssetWidgetAndRegisterAssetCommand();


	TSharedPtr<class FUICommandList> PluginCommandList;


};
