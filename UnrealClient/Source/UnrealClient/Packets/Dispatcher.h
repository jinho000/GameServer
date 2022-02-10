// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include <memory>
#include "ClientPackets/ClientPacketBase.h"

using  MessageHandler = std::function<void(std::shared_ptr<ClientPacketBase>)>;


// Ã·¾ð : 
class Diapatchar final
{
private: // Member Var
	TMap<unsigned int, MessageHandler> m_handler;

public: // Default
	Diapatchar() {}
	~Diapatchar() {}

	bool AddHandler(MessageId Id, const MessageHandler& _Handler)
	{
		AddHandler(static_cast<unsigned int>(Id), _Handler);
	}

	bool AddHandler(unsigned int Id, const MessageHandler& _Handler)
	{
		Handlers_.Add(Id, _Handler);

		return true;
	}

	// int* TMap.find

	bool GetHandler(MessageId Id, MessageHandler& _Handler)
	{
		return GetHandler(static_cast<unsigned int>(Id), _Handler);
	}

	bool GetHandler(uint32_t Id, MessageHandler& _Handler)
	{
		auto FindData = Handlers_.Find(Id);

		if (nullptr == FindData)
		{
			return false;
		}

		_Handler = *FindData;

		return true;
	}


	Diapatchar(const Diapatchar& _Other) = delete;
	Diapatchar(Diapatchar&& _Other) noexcept = delete;

protected:
	Diapatchar& operator=(const Diapatchar& _Other) = delete;
	Diapatchar& operator=(Diapatchar&& _Other) = delete;

private:

public: // Member Function
};

