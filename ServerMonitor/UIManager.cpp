#include "pch.h"
#include "UIManager.h"
#include "UIWindowBase.h"
#include "ResourceMonitor.h"

UIManager* UIManager::GetInst()
{
    static UIManager inst;
    return &inst;
}

void UIManager::Init()
{
	m_vecUIObj.push_back(new ResourceMonitor);
}

void UIManager::Update()
{
	for (size_t i = 0; i < m_vecUIObj.size(); i++)
	{
		m_vecUIObj[i]->Update();
	}
}

void UIManager::Destroy()
{
	for (size_t i = 0; i < m_vecUIObj.size(); i++)
	{
		delete m_vecUIObj[i];
	}
}
