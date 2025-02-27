#include "pch.h"
#include "Temp.h"
#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CConstBuffer.h"
#include "CMesh.h"
#include "CGraphicShader.h"

// Mesh
Ptr<CMesh> g_RectMesh = nullptr;
Ptr<CMesh> g_CircleMesh = nullptr;

// System Mem ���� ����
Vtx g_arrVtx[4] = {};
UINT g_arrIdx[6] = {0,2,3,0,1,2};

// ��ü�� ��ġ��
tTransform g_Trans = {};

// HLSL
Ptr<CGraphicShader> g_Shader = nullptr;


int TempInit()
{
	// RectMesh
	// 0 - 1 
	// |   |
	// 3 - 2
	g_arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_RectMesh = new CMesh();
	g_RectMesh->Create(g_arrVtx, 4, g_arrIdx, 6);

	// CircleMesh
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v0;
	
	// ������ ���Ϳ� �ִ´�
	v0.vPos = Vec3(0.f, 0.f, 0.f);
	v0.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v0);

	float Radius = 0.5f;
	UINT Slice = 10;
	float AngleStep = 2 * XM_PI / Slice;

	float Angle = 0.f;
	for (UINT i = 0; i <= Slice; i++)
	{
		Vtx v;
		v.vPos = Vec3(cosf(Angle) * Radius, sinf(Angle) * Radius, 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);

		vecVtx.push_back(v);
		Angle += AngleStep;
	}

	for (UINT i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	g_CircleMesh = new CMesh;
	g_CircleMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());

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
	g_CircleMesh->Render();
}
