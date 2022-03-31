#pragma once

// 용도 : 비동기 통신 overlapped 데이터 처리 클래스
// 분류 :
// 첨언 :
class Overlapped
{
protected: // member var
	WSAOVERLAPPED m_overlapped;

public: // default
	Overlapped();
	virtual ~Overlapped() = 0 {};

	Overlapped(const Overlapped& _other) = delete;
	Overlapped(Overlapped&& _other) = delete;
	Overlapped& operator=(const Overlapped& _other) = delete;
	Overlapped& operator=(const Overlapped&& _other) = delete;

private:

public: // member Func
	virtual void Excute(BOOL _result, DWORD _byteSize) {};
	
	LPWSAOVERLAPPED GetLPOverlapped();
	void ResetOverlapped();
};

