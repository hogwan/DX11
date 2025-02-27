#include "pch.h"
#include "CLayer.h"
#include "CGameObject.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	Safe_Del_Vec<CGameObject>(m_vecObject);
}

void CLayer::begin()
{
	for (size_t i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->begin();
	}
}

void CLayer::tick()
{
	for (size_t i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->tick();
	}
}

void CLayer::finaltick()
{
	for (size_t i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->finaltick();
	}
}

void CLayer::render()
{
	for (size_t i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i]->render();
	}
}

void CLayer::AddObject(CGameObject* _Object)
{
	m_vecObject.push_back(_Object);
}
