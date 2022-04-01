#include "pch.h"
#include "ServerCore.h"
#include <tinyxml2.h>
#include <conio.h>

#include <GameServerBase/GameServerDirectory.h>
#include <GameServerNet/ServerHelper.h>

#include "NetQueue.h"
#include "DBQueue1.h"

DBInfo	ServerCore::DBConfig = {};
int		ServerCore::ServerPort = 0;

TCPListener ServerCore::ServerListener;
std::function<void(PtrSTCPSession)> ServerCore::AcceptCallBack;

ServerCore::ServerCore()
{
}

ServerCore::~ServerCore()
{
}

void ServerCore::SetAcceptCallBack(const std::function<void(std::shared_ptr<TCPSession>)>& _acceptCallBack)
{
	AcceptCallBack = _acceptCallBack;
}

bool ServerCore::CoreInit()
{
	ServerDebug::Initialize();
	ServerDebug::LogInfo("Server Init");

	std::stringstream xmlStream;
	tinyxml2::XMLDocument Doc;

	// xml 파일 읽어오기
	{
		GameServerDirectory Dir;
		Dir.MoveParent("Project");
		xmlStream << Dir.PathToPlusFileName("ServerConfig.xml");
		Doc.LoadFile(xmlStream.str().c_str());

		if (true == Doc.Error())
		{
			ServerDebug::LogErrorAssert("Server Config Xml Open Error\n");
			return false;
		}
	}

	// 시작 루트 경로
	tinyxml2::XMLElement* Root = Doc.FirstChildElement("ServerApp");
	if (nullptr == Root)
	{
		return false;
	}

	// Server Config에서 서버 IP, Port 정보 가져오기
	ServerDebug::LogInfo("Server Config Info");
	{
		tinyxml2::XMLElement* ServerStart = Root->FirstChildElement("ServerStart");
		ServerPort = nullptr != ServerStart->FindAttribute("Port") ? std::stoi(ServerStart->FindAttribute("Port")->Value()) : -1;
		
		ServerDebug::LogInfo(std::string("ServerPort : " + std::to_string(ServerPort)));
	}

	// Server Config에서 DB정보 가져오기
	{
		// <DataBase Host = "127.0.0.1" Port = "3306" Name = "userver2" User = "root" PW = "1234" / >
		tinyxml2::XMLElement* ServerStart = Root->FirstChildElement("DataBase");
		DBConfig.DBHost = nullptr != ServerStart->FindAttribute("Host") ? ServerStart->FindAttribute("Host")->Value() : "";
		DBConfig.DBUser = nullptr != ServerStart->FindAttribute("User")->Value() ? ServerStart->FindAttribute("User")->Value() : "";
		DBConfig.DBPW = nullptr != ServerStart->FindAttribute("PW")->Value() ? ServerStart->FindAttribute("PW")->Value() : "";
		DBConfig.DBName = nullptr != ServerStart->FindAttribute("Name")->Value() ? ServerStart->FindAttribute("Name")->Value() : "";
		DBConfig.DBPort = nullptr != ServerStart->FindAttribute("Port")->Value() ? std::stoi(ServerStart->FindAttribute("Port")->Value()) : -1;

		ServerDebug::LogInfo("DB Config Info");
		ServerDebug::LogInfo(std::string("DBHost : " + DBConfig.DBHost));
		ServerDebug::LogInfo(std::string("DBUser : " + DBConfig.DBUser));
		ServerDebug::LogInfo(std::string("DBPW : " + DBConfig.DBPW));
		ServerDebug::LogInfo(std::string("DBName : " + DBConfig.DBName));
		ServerDebug::LogInfo(std::string("DBPort : " + std::to_string(DBConfig.DBPort)));
	}

	ServerDebug::LogInfo("Server Config OK");

	DBQueue1::Init();
	ServerDebug::LogInfo("DB Thread Init OK");

	NetQueue::Init();
	ServerDebug::LogInfo("Net Thread Init OK");

	ServerHelper::InitSocketLib();
	ServerDebug::LogInfo("ServerHelper And ServerDebug Init OK");

	return true;
}

bool ServerCore::CoreRun()
{
	// 액셉트 콜백은 Content에서 해준다
	if (nullptr == AcceptCallBack)
	{
		ServerDebug::LogErrorAssert("AcceptCallBack is null");
		return false;
	}

	ServerListener.Initialize("127.0.0.1", ServerPort, AcceptCallBack);
	ServerListener.BindNetQueue(NetQueue::GetQueue());
	ServerListener.StartAccept(10);


	while (true)
	{
		if ('`' == _getch())
		{
			return true;
		}
	}
}

bool ServerCore::CoreEnd()
{
	ServerDebug::Destroy();
	NetQueue::Destroy();
	DBQueue1::Destroy();

    return true;
}
