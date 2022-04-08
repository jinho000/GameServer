// Fill out your copyright notice in the Description page of Project Settings.


#include "CChatMessage.h"

void UCChatMessage::Init(const FString& _nickName, const FString& _message)
{
	m_chatMessage = _nickName + TEXT(": ") + _message;
}

const FString& UCChatMessage::GetChatMessage() const
{
	return m_chatMessage;
}

