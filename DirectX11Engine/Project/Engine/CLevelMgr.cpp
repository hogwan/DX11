#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"

#include "CTransform.h"
#include "CPlayerScript.h"
#include "CMeshRender.h"

CLevelMgr::CLevelMgr()
	:m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
	{
		delete m_CurLevel;
		m_CurLevel = nullptr;
	}
}

void CLevelMgr::begin()
{
	m_CurLevel = new CLevel;

	CGameObject* pObject1 = new CGameObject;
	pObject1->AddComponent(new CTransform);
	pObject1->AddComponent(new CMeshRender);
	pObject1->AddComponent(new CPlayerScript);
	pObject1->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);
	pObject1->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
	pObject1->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	m_CurLevel->AddObject(0,pObject1);
}

void CLevelMgr::tick()
{
	if (nullptr != m_CurLevel)
	{
		m_CurLevel->tick();
		m_CurLevel->finaltick();
	}
}

void CLevelMgr::render()
{
	if (nullptr != m_CurLevel)
		m_CurLevel->render();
}
