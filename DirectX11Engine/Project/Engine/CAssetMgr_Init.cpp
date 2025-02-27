#include "pch.h"
#include "CAssetMgr.h"
#include "CPathMgr.h"

void CAssetMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultTexture();
	CreateDefaultMaterial();
	CreateDefaultGraphicShader();
	CreateDefaultComputeShader();
}

void CAssetMgr::CreateDefaultMesh()
{
	CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");

	{
		Ptr<CMesh> RectMesh = nullptr;

		vector<Vtx> vecVtx;
		vector<UINT> vecIdx;
		Vtx v;

		// RectMesh
		// 0 - 1 
		// |   |
		// 3 - 2
		v.vPos = Vec3(-0.5f, 0.5f, 0.f);
		v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
		vecVtx.push_back(v);

		v.vPos = Vec3(0.5f, 0.5f, 0.f);
		v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
		vecVtx.push_back(v);

		v.vPos = Vec3(0.5f, -0.5f, 0.f);
		v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
		vecVtx.push_back(v);

		v.vPos = Vec3(-0.5f, -0.5f, 0.f);
		v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
		vecVtx.push_back(v);

		vecIdx.push_back(0);
		vecIdx.push_back(2);
		vecIdx.push_back(3);

		vecIdx.push_back(0);
		vecIdx.push_back(1);
		vecIdx.push_back(2);

		RectMesh = new CMesh();
		RectMesh->Create(vecVtx.data(), (UINT)vecIdx.size(), vecIdx.data(), (UINT)vecIdx.size());
		AddAsset<CMesh>(L"RectMesh", RectMesh);
	}
	
	{
		// CircleMesh
		Ptr<CMesh> CircleMesh = nullptr;

		vector<Vtx> vecVtx;
		vector<UINT> vecIdx;
		Vtx v0;

		// 원점을 벡터에 넣는다
		v0.vPos = Vec3(0.f, 0.f, 0.f);
		v0.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v0);

		float Radius = 0.5f;
		UINT Slice = 50;
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

		CircleMesh = new CMesh;
		CircleMesh->Create(vecVtx.data(), (UINT)vecIdx.size(), vecIdx.data(), (UINT)vecIdx.size());
		AddAsset<CMesh>(L"CircleMesh", CircleMesh);
	}
	
}

void CAssetMgr::CreateDefaultTexture()
{
}

void CAssetMgr::CreateDefaultMaterial()
{
}

void CAssetMgr::CreateDefaultGraphicShader()
{
	//CreateShader
	{
		wstring strPath = CPathMgr::GetInst()->GetContentPath();

		Ptr<CGraphicShader> Shader = new CGraphicShader;
		Shader->CreateVertexShader(strPath + L"shader\\std2d.fx", "VS_Std2D");
		Shader->CreatePixelShader(strPath + L"shader\\std2d.fx", "PS_Std2D");

		AddAsset<CGraphicShader>(L"Std2DShader", Shader);
	}
}

void CAssetMgr::CreateDefaultComputeShader()
{
}