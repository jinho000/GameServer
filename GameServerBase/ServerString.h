#pragma once

// �뵵 :
// �з� :
// ÷�� :
class ServerString
{
private: // member var

private:
	ServerString();
	~ServerString();

public: // default

	ServerString(const ServerString& _other) = delete;
	ServerString(ServerString&& _other) = delete;

protected:
	ServerString& operator=(const ServerString& _other) = delete;
	ServerString& operator=(const ServerString&& _other) = delete;

private:

public: // member Func

	// ������� ANSI ���ڵ��� ���
	// Ŭ���̾�Ʈ�κ��� ���޹��� UTF8�����͸� ANSI ���ڿ��� ��ȯ
	static bool UTF8ToANSI(const std::string& _UTF8Str, std::string& _ANSIStrBuffer);
	static bool UTF8ToUNICODE(const std::string& _UTF8Str, std::wstring& _UNICODEStrBuffer);
	static bool UNICODEToANSI(const std::wstring& _UNICODEStr, std::string& _ANSIStrBuffer);

	// ������ ���۽� ANSI���ڿ��� UTF8���ڵ����� ��ȯ
	static bool ANSIToUTF8(const std::string& _ANSIStr, std::string& _UTF8StrBuffer);
	static bool ANSIToUNICODE(const std::string& _ANSIStr, std::wstring& _UNICODEStrBuffer);
	static bool UNICODEToUTF8(const std::wstring& _UNICODEStr, std::string& _UTF8StrBuffer);
};

