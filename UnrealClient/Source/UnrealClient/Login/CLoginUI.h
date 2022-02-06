// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// 헤더파일은 .generated 파일 위에 선언해야함
#include "CLoginUI.generated.h"


// UUserWidget 블루프린트 클래스를 상속받음
// 이 클래스로 블루프린트를 만든다
// -> UI에 필요한 변수나 함수 세팅이 가능해짐
// 
// UCLASS 언리얼 컨텐츠 브라우저에 세팅하기 위한 키워드
UCLASS()
class UNREALCLIENT_API UCLoginUI : public UUserWidget
{
	// 언리얼 세팅 매크로
	GENERATED_BODY()
	
public:
	// UPROPERTY: 블루프린트에서 사용하기 위한 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString IP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString Port;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString Password;

};
