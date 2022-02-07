#pragma once

// 용도 :
// 분류 :
// 첨언 :
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

	// 윈도우는 ANSI 인코딩을 사용
	// 클라이언트로부터 전달받은 UTF8데이터를 ANSI 문자열로 변환
	static bool UTF8ToANSI(const std::string& _UTF8Str, std::string& _ANSIStrBuffer);
	static bool UTF8ToUNICODE(const std::string& _UTF8Str, std::wstring& _UNICODEStrBuffer);
	static bool UNICODEToANSI(const std::wstring& _UNICODEStr, std::string& _ANSIStrBuffer);

	// 데이터 전송시 ANSI문자열을 UTF8인코딩으로 변환
	static bool ANSIToUTF8(const std::string& _ANSIStr, std::string& _UTF8StrBuffer);
	static bool ANSIToUNICODE(const std::string& _ANSIStr, std::wstring& _UNICODEStrBuffer);
	static bool UNICODEToUTF8(const std::wstring& _UNICODEStr, std::string& _UTF8StrBuffer);
};

