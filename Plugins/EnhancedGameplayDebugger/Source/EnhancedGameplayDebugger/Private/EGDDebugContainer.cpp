// Copyright 2023 devran. All Rights Reserved.


#include "EGDDebugContainer.h"

EGDDebugContainer::EGDDebugContainer(FName InDebugContainerName)
	: DebugContainerName("")
{
	DebugContainerName = InDebugContainerName;
}

FDebugObjectData* EGDDebugContainer::AddDebugObject(UObject* DebugObject)
{
	FDebugObjectData DebugObjectData;
	DebugObjectData.DebugObject = DebugObject;
	DebugObjectData.Properties.Add("Name", DebugObject->GetFName().ToString());

	int32 i = DebugObjectsData.Add(DebugObjectData);

	return &DebugObjectsData[i];
}

void EGDDebugContainer::UpdateProperties()
{
	if (DebugObjectsData.Num() < 1) return;

	for (FDebugObjectData& DebugObjectData : DebugObjectsData)
	{
		if (DebugObjectData.DebugObject.IsValid())
		{
			TArray<FName> Keys;
			DebugObjectData.Properties.GetKeys(Keys);
			int32 KeysLen = Keys.Num();

			for (const FName& PropertyName : Keys)
			{
				if (PropertyName != "Name")
				{
					// Get the property's value as string
					FProperty* Prop = DebugObjectData.DebugObject.Get()->GetClass()->FindPropertyByName(PropertyName);
					FString Value = GetPropertyValueAsString(DebugObjectData.DebugObject.Get(), Prop);

					DebugObjectData.Properties.Add(PropertyName, Value);
				}
			}
		}
	}
}

void EGDDebugContainer::AddProperty(UObject* DebugObject, FName PropertyName)
{
	{
		FDebugObjectData* DebugObjectData = FindDebugObjectData(DebugObject);
		if (DebugObjectData)
		{
			FProperty* Prop = DebugObjectData->DebugObject.Get()->GetClass()->FindPropertyByName(PropertyName);
			FString Value = GetPropertyValueAsString(DebugObjectData->DebugObject.Get(), Prop);

			DebugObjectData->Properties.Add(PropertyName, Value);
			return;
		}
	}

	FDebugObjectData* DebugObjectData = AddDebugObject(DebugObject);

	FProperty* Prop = DebugObjectData->DebugObject.Get()->GetClass()->FindPropertyByName(PropertyName);
	FString Value = GetPropertyValueAsString(DebugObjectData->DebugObject.Get(), Prop);
	DebugObjectData->Properties.Add(PropertyName, Value);
}

void EGDDebugContainer::AddProperty(FDebugObjectData& DebugObjectData, FName PropertyName)
{
	if (DebugObjectData.DebugObject.IsValid())
	{
		FProperty* Prop = DebugObjectData.DebugObject.Get()->GetClass()->FindPropertyByName(PropertyName);
		FString Value = GetPropertyValueAsString(DebugObjectData.DebugObject.Get(), Prop);

		DebugObjectData.Properties.Add(PropertyName, Value);
	}
}

FDebugObjectData* EGDDebugContainer::FindDebugObjectData(const UObject* DebugObject)
{
	for (FDebugObjectData& DebugObjectData : DebugObjectsData)
	{
		if (DebugObjectData.DebugObject.IsValid())
		{
			if (DebugObjectData.DebugObject.Get()->GetFName() == DebugObject->GetFName())
			{
				return &DebugObjectData;
			}
		}
	}

	return nullptr;
}

FString EGDDebugContainer::GetPropertyValueAsString(UObject* DebugObject, FProperty* Property) const
{
	if (!IsValid(DebugObject) || !Property) return "";

	if (FObjectProperty* ObjectProp = CastField<FObjectProperty>(Property))
	{
		UObject* Value = ObjectProp->GetPropertyValue_InContainer(DebugObject);
		return *Value->GetName();
	}
	if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Property))
	{
		bool Value = BoolProp->GetPropertyValue_InContainer(DebugObject);
		return Value ? "true" : "false";
	}
	if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
	{
		float Value = FloatProp->GetPropertyValue_InContainer(DebugObject);
		return FString::SanitizeFloat(Value);
	}
	if (FIntProperty* IntProp = CastField<FIntProperty>(Property))
	{
		int32 Value = IntProp->GetPropertyValue_InContainer(DebugObject);
		return FString::FromInt(Value);
	}
	if (FNameProperty* NameProp = CastField<FNameProperty>(Property))
	{
		FName Value = NameProp->GetPropertyValue_InContainer(DebugObject);
		return *Value.ToString();
	}
	if (FTextProperty* TextProp = CastField<FTextProperty>(Property))
	{
		FText Value = TextProp->GetPropertyValue_InContainer(DebugObject);
		return *Value.ToString();
	}

	return "";
}
