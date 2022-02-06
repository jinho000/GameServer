// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// ��������� .generated ���� ���� �����ؾ���
#include "CLoginUI.generated.h"


// UUserWidget �������Ʈ Ŭ������ ��ӹ���
// �� Ŭ������ �������Ʈ�� �����
// -> UI�� �ʿ��� ������ �Լ� ������ ��������
// 
// UCLASS �𸮾� ������ �������� �����ϱ� ���� Ű����
UCLASS()
class UNREALCLIENT_API UCLoginUI : public UUserWidget
{
	// �𸮾� ���� ��ũ��
	GENERATED_BODY()
	
public:
	// UPROPERTY: �������Ʈ���� ����ϱ� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString IP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString Port;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConnectInfo")
	FString Password;

public:
	// UFUNCTION: �������Ʈ���� �Լ��� ����ϱ� ���� ����
	UFUNCTION(BlueprintCallable, Category = "Login|Connect")
	void ResetConnectInfo();
	
	UFUNCTION(BlueprintCallable, Category = "Login|Connect")
	void ConnectServer();

	UFUNCTION(BlueprintCallable, Category = "Login|Connect")
	void Login();
};
