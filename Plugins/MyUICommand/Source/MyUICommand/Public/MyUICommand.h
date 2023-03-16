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

	//��������:��ȡ����ѡ����ʲ�
	void GetSelectAllAssets(FOnContentBrowserGetSelection GetSelectionDelegate);

	//ע����������
	void RegisterAllCommand();

	//�ؿ��༭��
	void CreateLevelEditorWidget();

	//���������
	void CreateContentBrowserWidget();

	//�ʲ��༭��:�����ʲ�UI����ע��ӳ������
	void CreateAssetWidgetAndRegisterAssetCommand();


	TSharedPtr<class FUICommandList> PluginCommandList;


};
