#pragma once

class UIWindowBase;
class UIManager
{
private:
	std::vector<UIWindowBase*> m_vecUIObj;

private:
	UIManager() {}
	~UIManager() {}

public:
	static UIManager* GetInst();

	void Init();
	void Update();
	void Destroy();
};

