#include "pch.h"
#include "Temp.h"
#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CConstBuffer.h"
#include "CMesh.h"
#include "CGraphicShader.h"
#include "CAssetMgr.h"

// 물체의 위치값
tTransform g_Trans = {};

int TempInit()
{
	

	return S_OK;
}

void TempRelease()
{

}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		g_Trans.Position.y += DT;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::S))
	{
		g_Trans.Position.y -= DT;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::A))
	{
		g_Trans.Position.x -= DT;
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::D))
	{
		g_Trans.Position.x += DT;
	}

	//Sysmem -> GPU
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Trans);
	pCB->Binding();
}

void TempRender()
{
	Ptr<CGraphicShader> Shader = CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader");
	Shader->Binding();
	Ptr<CMesh> g_RectMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	g_RectMesh->Render();
}
