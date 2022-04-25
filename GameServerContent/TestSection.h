#pragma once
#include <GameServerCore/ServerSection.h>
// 용도 :
// 분류 :
// 첨언 :
class TestSection : public ServerSection
{
private: // member var
	

public: // default
	TestSection();
	~TestSection();

	TestSection(const TestSection& _other) = delete;
	TestSection(TestSection&& _other) = delete;

protected:
	TestSection& operator=(const TestSection& _other) = delete;
	TestSection& operator=(const TestSection&& _other) = delete;

private:

public: // member Func
	void Init() override;
};

