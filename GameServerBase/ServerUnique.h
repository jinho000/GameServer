#pragma once

// 용도 :
// 분류 :
// 첨언 :
class ServerUnique
{
private: // member var
	static std::atomic<__int64> UniqueID;

public:
	static __int64 GetNextUniqueId();

private: // default
	ServerUnique();
	~ServerUnique();

	ServerUnique(const ServerUnique& _other) = delete;
	ServerUnique(ServerUnique&& _other) noexcept;

protected:
	ServerUnique& operator=(const ServerUnique& _other) = delete;
	ServerUnique& operator=(const ServerUnique&& _other) = delete;

private:

public: // member Func
};

