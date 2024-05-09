// Copyright 2023 devran. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FDebugObjectData
{
public:
	FWeakObjectPtr DebugObject;

	TMap<FName, FString> Properties;

public:
	bool operator==(const FWeakObjectPtr* Other) const
	{
		return DebugObject.Get()->GetFName() == Other->Get()->GetFName();
	}
};


/**
 * The logical representation of an SEGDTable
 */
class ENHANCEDGAMEPLAYDEBUGGER_API EGDDebugContainer
{
public:
	FName DebugContainerName;

	// Data of each debug object in this container
	TArray<FDebugObjectData> DebugObjectsData;

public:
	EGDDebugContainer(FName InDebugContainerName);

	/**
	 * Creates new debug object data and adds it to the container.
	 *
	 * @param DebugObject Debug object to add
	 * @return Created debug object data
	 */
	FDebugObjectData* AddDebugObject(UObject* DebugObject);

	/**
	* Updates all properties of the debug objects in this container
	*/
	void UpdateProperties();

	/**
	 * Get the property's value based on its name and add the key-value pair to the properties map.
	 *
	 * @param DebugObject Debug object to add property to
	 * @param PropertyName Name of the property to add
	 */
	void AddProperty(UObject* DebugObject, FName PropertyName);

	/**
	 * Adds the property to the debug object data.
	 *
	 * @param DebugObjectData Debug object data to add property to
	 * @param PropertyName Name of the property to add
	 */
	void AddProperty(FDebugObjectData& DebugObjectData, FName PropertyName);

private:
	/**
	 * Finds the debug data of the debug object.
	 *
	 * @param DebugObject Debug object to find debug data of
	 * @return Found debug object data
	 */
	FDebugObjectData* FindDebugObjectData(const UObject* DebugObject);

	/**
	* Gets the value of a property as a string.
	*/
	FString GetPropertyValueAsString(UObject* DebugObject, FProperty* Property) const;

};
