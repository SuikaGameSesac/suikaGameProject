// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JIU_HttpLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETNETWORKTEST_API UJIU_HttpLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	FString JsonParse(const FString& data);

	FString MapToJson(const TMap<FString, FString>& map);

	bool SaveJson(const FString& filename, const FString& json);
};
