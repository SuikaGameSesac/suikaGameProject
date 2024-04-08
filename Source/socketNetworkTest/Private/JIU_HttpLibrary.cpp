// Fill out your copyright notice in the Description page of Project Settings.


#include "JIU_HttpLibrary.h"
#include "Json.h"

FString UJIU_HttpLibrary::JsonParse(const FString& data)
{
	FString json;

	// JsonReader를 만든다.
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(data);
	// JsonObject를 만든다.
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

	/*for (int i=0 ; i<2 ; i++)
	{
		FString title = TEXT( "CON_TITLE" );
		FString addr = TEXT( "CON_ADDRESS" );
		json.Append( FString::Printf( TEXT( "title : %s / address : %s\n" ) , *title , *addr ) );
	}*/
	// 해독(deserialize)을한다.
	if (FJsonSerializer::Deserialize(reader, jsonObj))
	{
		auto response = jsonObj->GetObjectField(TEXT("response"));
		auto body = response->GetObjectField(TEXT("body"));
		auto items = body->GetObjectField(TEXT("items"));
		TArray<TSharedPtr<FJsonValue>> item = items->GetArrayField(TEXT("item"));

		for (TSharedPtr<FJsonValue> pair : item)
		{
			FString title = pair->AsObject()->GetStringField("CON_TITLE");
			FString addr = pair->AsObject()->GetStringField("CON_ADDRESS");
			json.Append(FString::Printf(TEXT("title : %s / address : %s\n"), *title, *addr));
		}
	}


	return json;
}

FString UJIU_HttpLibrary::MapToJson(const TMap<FString, FString>& map)
{
	// JsonObject를 생성
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject);
	// map의 내용을 JsonObject에 모두 담는다.
	for (auto& pair : map)
	{
		jsonObj->SetStringField(pair.Key, pair.Value);
	}

	// JsonObject를 Serialize 하고싶다.
	FString jsonData;

	auto writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);
	FJsonSerializer::Serialize(jsonObj.ToSharedRef(), writer);

	// 그것을 반환 하고싶다.
	return jsonData;
}

bool UJIU_HttpLibrary::SaveJson(const FString& filename, const FString& json)
{
	// 만약 지정된 폴더가 없으면 해당 폴더를 만든다.
	// 파일매니저를 가져오고싶다.
	FPlatformFileManager& fileManager = FPlatformFileManager::Get();
	IPlatformFile& platformFile = fileManager.GetPlatformFile();

	FString directoryPath = FPaths::ProjectContentDir() + "/jsonData";
	if (false == platformFile.DirectoryExists(*directoryPath))
	{
		platformFile.CreateDirectory(*directoryPath);
	}

	// json문자열을 파일로 저장한다.
	FString filePath = directoryPath + "/" + filename;
	bool bResult = FFileHelper::SaveStringToFile(json, *filePath);
	if (false == bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyJsonLibrary::SaveJson Failed...T,.T "));
	}
	return bResult;
}
