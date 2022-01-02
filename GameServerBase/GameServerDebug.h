#pragma once

// 용도 :
// 분류 :
// 첨언 :
class GameServerDebug
{
private: // member var
	

private: // default
	GameServerDebug();
	~GameServerDebug();

	GameServerDebug(const GameServerDebug& _other) = delete;
	GameServerDebug(GameServerDebug&& _other) noexcept;

protected:
	GameServerDebug& operator=(const GameServerDebug& _other) = delete;
	GameServerDebug& operator=(const GameServerDebug&& _other) = delete;

private:

public: // member Func
	static void AssertDebugMsg(const std::string& msg);

};

