#include "pch.h"
#include <iostream>
#include "User.h"

using namespace std;

void Pause()
{
    std::string input;
    cin >> input;
}

// 동시접속 테스트
int userCount = 10;
std::vector<User*> socketArray;

void Test()
{
    for (size_t i = 0; i < userCount; i++)
    {
        socketArray.push_back(new User("127.0.0.1", 30001));
        socketArray[i]->ConnectServer();
    }

    // login
    {
        for (size_t i = 0; i < userCount; i++)
        {
            socketArray[i]->Login(std::string("ID") + std::to_string(i), std::to_string(i));
        }
    }

    Pause();

    for (size_t i = 0; i < userCount; i++)
    {
        delete socketArray[i];
    }
}

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    User user("127.0.0.1", 30001);
    user.ConnectServer();
    
    Pause();

    user.Login("ID1", "1");

    WSACleanup();

    return 0;
}

