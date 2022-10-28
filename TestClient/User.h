#pragma once
#include "TCPClientSocket.h"

class User
{
private: // member var
	TCPClientSocket m_clientSocket;

	// 캐릭터 리스트

public: // default
	User(const std::string& _serverIP, int _serverPort);
	~User();
	
public: // member Func
	void ConnectServer();
	void Disconnect();

	void Login(const std::string& _ID, const std::string& _PW);
	//void Join();
	//void CreateCharacter();
	//void SelectCharacter();
	//void RequestMatch();
	//void Chatting();
};

