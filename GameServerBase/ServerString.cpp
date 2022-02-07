#include "pch.h"
#include "ServerString.h"
#include "ServerDebug.h"

ServerString::ServerString()
{
}

ServerString::~ServerString()
{
}

bool ServerString::UTF8ToANSI(const std::string& _UTF8bytes, std::string& _outBuffer)
{
    std::wstring tempUNICODE;
    if (false == UTF8ToUNICODE(_UTF8bytes, tempUNICODE))
    {
        return false;
    }

    if (false == UNICODEToANSI(tempUNICODE, _outBuffer))
    {
        return false;
    }

    return true;
}

bool ServerString::UTF8ToUNICODE(const std::string& _UTF8bytes, std::wstring& _outBuffer)
{
	// ���� ����
	_outBuffer.clear();

    // ��ȯ�� ���ڵ��� ���� ���� ���� ���ϱ�
    int len = MultiByteToWideChar(
        CP_UTF8, 
        0, 
        _UTF8bytes.c_str(),
        static_cast<int>(_UTF8bytes.size()),
        NULL, 
        0
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    // �����ڵ� out buffer�� ä���
    _outBuffer.resize(len + 10);
    len = MultiByteToWideChar(
        CP_UTF8,
        0,
        _UTF8bytes.c_str(),
        static_cast<int>(_UTF8bytes.size()),
        _outBuffer.data(),
        static_cast<int>(_outBuffer.size())
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }
    
	return true;
}

bool ServerString::UNICODEToANSI(const std::wstring& _unicode, std::string& _outBuffer)
{
    // ���� ����
    _outBuffer.clear();

    // ��ȯ�� ���ڵ��� ���� ���� ���� ���ϱ�
    int len = WideCharToMultiByte(
        CP_ACP,
        0,
        _unicode.c_str(),
        static_cast<int>(_unicode.size()),
        NULL,
        0,
        NULL,
        NULL
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    // outBuffer�� ���� ä���
    _outBuffer.resize(len + 10);
    len = WideCharToMultiByte(
        CP_ACP,
        0,
        _unicode.c_str(),
        static_cast<int>(_unicode.size()),
        _outBuffer.data(),
        static_cast<int>(_outBuffer.size()),
        NULL,
        NULL
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    return true;
}

bool ServerString::ANSIToUTF8(const std::string& _ANSIStr, std::string& _UTF8StrBuffer)
{
    std::wstring tempUNICODE;
    if (false == ANSIToUNICODE(_ANSIStr, tempUNICODE))
    {
        return false;
    }

    if (false == UNICODEToUTF8(tempUNICODE, _UTF8StrBuffer))
    {
        return false;
    }

    return true;
}

bool ServerString::ANSIToUNICODE(const std::string& _ANSIStr, std::wstring& _UNICODEStrBuffer)
{
    _UNICODEStrBuffer.clear();

    int len = MultiByteToWideChar(
        CP_ACP,
        0,
        _ANSIStr.c_str(),
        static_cast<int>(_ANSIStr.size()),
        nullptr,
        0
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    _UNICODEStrBuffer.resize(len + 10);
    len = MultiByteToWideChar(
        CP_ACP,
        0,
        _ANSIStr.c_str(),
        static_cast<int>(_ANSIStr.size()),
        _UNICODEStrBuffer.data(),
        static_cast<int>(_UNICODEStrBuffer.size())
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    return true;
}

bool ServerString::UNICODEToUTF8(const std::wstring& _UNICODEStr, std::string& _UTF8StrBuffer)
{
    _UTF8StrBuffer.clear();

    int len = WideCharToMultiByte(
        CP_UTF8,
        0,
        _UNICODEStr.c_str(),
        static_cast<int>(_UNICODEStr.size()),
        nullptr,
        0,
        nullptr,
        nullptr
    );
    
    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    _UTF8StrBuffer.resize(len + 10);
    len = WideCharToMultiByte(
        CP_UTF8,
        0,
        _UNICODEStr.c_str(),
        static_cast<int>(_UNICODEStr.size()),
        _UTF8StrBuffer.data(),
        static_cast<int>(_UTF8StrBuffer.size()),
        nullptr,
        nullptr
    );

    if (len <= 0)
    {
        // ��ȯ���� 0���� ���ų� ������ ����
        ServerDebug::GetLastErrorPrint();
        return false;
    }

    return true;
}
