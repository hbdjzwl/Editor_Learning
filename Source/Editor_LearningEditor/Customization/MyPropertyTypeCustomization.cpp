#include "MyPropertyTypeCustomization.h"
#include "Editor_Learning/TypeData/CommonType.h"

FMyPropertyTypeCustomization::FMyPropertyTypeCustomization()
{

}




void FMyPropertyTypeCustomization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	NamePropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyToDay, Name));
	DayPropertyHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMyToDay, Day));



	HeaderRow.NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("ÊôÐÔ¹æÔò")))
		];

// 	HeaderRow.NameContent()
// 		[
// 			StructPropertyHandle->CreatePropertyNameWidget()
// 		]
// 	.ValueContent()
// 		.MinDesiredWidth(250.f)
// 		.VAlign(VAlign_Center)
// 		[
// 			NamePropertyHandle->CreatePropertyValueWidget()
// 		];
}

void FMyPropertyTypeCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{


}