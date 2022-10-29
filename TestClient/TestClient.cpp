#include "pch.h"
#include <iostream>
#include "User.h"

using namespace std;

void Pause()
{
    cout << "Pause ";
    std::string input;
    cin >> input;
}

bool isNumber(const string& str)
{
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}


// 동시접속 테스트
int userCount = 0;
std::vector<User*> socketArray;

void Test()
{
    cout << "Create Client Socket" << endl;

    for (size_t i = 0; i < userCount; i++)
    {
        socketArray.push_back(new User("127.0.0.1", 30001));
    }

    Pause();

    cout << "Connect Server" << endl;
    for (size_t i = 0; i < userCount; i++)
    {
        socketArray[i]->ConnectServer();
    }

    Pause();

    cout << "Disconnect" << endl;
    for (size_t i = 0; i < userCount; i++)
    {
        socketArray[i]->Disconnect();
    }

    for (size_t i = 0; i < userCount; i++)
    {
        delete socketArray[i];
    }
    socketArray.clear();
}

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    while (true)
    {
        cout << "Test Client Count: ";
        std::string input;
        cin >> input;

        if (input == "quit")
        {
            break;
        }

        if (isNumber(input.c_str()) == true)
        {
            userCount = std::stoi(input.c_str());
            Test();
        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }

    WSACleanup(); 

    return 0;
}

