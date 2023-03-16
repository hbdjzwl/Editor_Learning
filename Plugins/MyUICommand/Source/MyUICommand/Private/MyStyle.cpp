#include "MyStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FMyStyle::StyleInstance = NULL;

void FMyStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FMyStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FMyStyle::GetStyleSetName()
{
	return TEXT("TestYaksueStyle");
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FMyStyle::Create()
{
	//创建一个新的Style实例：
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));

	//设置资源目录，为本插件的Resources目录
	FString ResourcesPath = IPluginManager::Get().FindPlugin("MyUICommand")->GetBaseDir() / TEXT("Resources");
	Style->SetContentRoot(ResourcesPath);

	//注册图标：类.命令
	Style->Set("MyCustomCommands.LevelEditor_TooolBar_Command", new IMAGE_BRUSH(TEXT("PicA"), Icon40x40));
	Style->Set("MyCustomCommands.AssetEditor_Menu_Command", new IMAGE_BRUSH(TEXT("PicB"), Icon40x40));

	return Style;
}

#undef IMAGE_BRUSH


void FMyStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}
