// Fill out your copyright notice in the Description page of Project Settings.


#include "JIU_HttpLibrary.h"
#include "Json.h"

FString UJIU_HttpLibrary::JsonParse(const FString& data)
{
	FString json;

	// JsonReader�� �����.
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(data);
	// JsonObject�� �����.
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

	/*for (int i=0 ; i<2 ; i++)
	{
		FString title = TEXT( "CON_TITLE" );
		FString addr = TEXT( "CON_ADDRESS" );
		json.Append( FString::Printf( TEXT( "title : %s / address : %s\n" ) , *title , *addr ) );
	}*/
	// �ص�(deserialize)���Ѵ�.
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
	// JsonObject�� ����
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject);
	// map�� ������ JsonObject�� ��� ��´�.
	for (auto& pair : map)
	{
		jsonObj->SetStringField(pair.Key, pair.Value);
	}

	// JsonObject�� Serialize �ϰ�ʹ�.
	FString jsonData;

	auto writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);
	FJsonSerializer::Serialize(jsonObj.ToSharedRef(), writer);

	// �װ��� ��ȯ �ϰ�ʹ�.
	return jsonData;
}

bool UJIU_HttpLibrary::SaveJson(const FString& filename, const FString& json)
{
	// ���� ������ ������ ������ �ش� ������ �����.
	// ���ϸŴ����� ��������ʹ�.
	FPlatformFileManager& fileManager = FPlatformFileManager::Get();
	IPlatformFile& platformFile = fileManager.GetPlatformFile();

	FString directoryPath = FPaths::ProjectContentDir() + "/jsonData";
	if (false == platformFile.DirectoryExists(*directoryPath))
	{
		platformFile.CreateDirectory(*directoryPath);
	}

	// json���ڿ��� ���Ϸ� �����Ѵ�.
	FString filePath = directoryPath + "/" + filename;
	bool bResult = FFileHelper::SaveStringToFile(json, *filePath);
	if (false == bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyJsonLibrary::SaveJson Failed...T,.T "));
	}
	return bResult;
}
