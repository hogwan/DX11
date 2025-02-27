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

// Mesh
Ptr<CMesh> g_RectMesh = nullptr;
Ptr<CMesh> g_CircleMesh = nullptr;

// 물체의 위치값
tTransform g_Trans = {};

// HLSL
Ptr<CGraphicShader> g_Shader = nullptr;


int TempInit()
{
	//CreateShader
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	g_Shader = new CGraphicShader;
	g_Shader->CreateVertexShader(strPath, "VS_Std2D");
	g_Shader->CreatePixelShader(strPath, "PS_Std2D");

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
	g_Shader->Binding();
	g_RectMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	g_RectMesh->Render();
}
