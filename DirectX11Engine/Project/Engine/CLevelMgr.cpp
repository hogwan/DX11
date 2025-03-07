#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"

#include "components.h"

#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

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

void CLevelMgr::init()
{
	m_CurLevel = new CLevel;

	// Camera Object 积己
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Camera()->SetCameraPriority(0);
	m_CurLevel->AddObject(0, pCamObj);


	// Player 坷宏璃飘 积己
	CGameObject* pObject = new CGameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CPlayerScript);

	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pObject->Transform()->SetRelativeScale(100.f, 100.f, 0.2f);

	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"texture\\Character.png"));

	m_CurLevel->AddObject(0,pObject);
	
	DrawDebugRect(Vec3(0.f, 0.f, 500.f), Vec3(100.f, 100.f, 1.f), Vec3(0.f, 0.f, 0.f), Vec4(0.f, 1.f, 0.f, 1.f), 100.f);
	DrawDebugCircle(Vec3(0.f, 0.f, 500.f), 100.f, Vec4(0.f, 1.f, 0.f, 1.f), 100.f);
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
