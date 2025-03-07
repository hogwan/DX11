#include "pch.h"
#include "CDbgRenderMgr.h"
#include "CTimeMgr.h"

#include "CGameObject.h"
#include "CMeshRender.h"
#include "CTransform.h"
#include "CAssetMgr.h"
#include "CMesh.h"

CDbgRenderMgr::CDbgRenderMgr()
	:m_DebugRenderObj(nullptr)
{
	m_DebugRenderObj = new CGameObject;
	m_DebugRenderObj->AddComponent(new CTransform);
	m_DebugRenderObj->AddComponent(new CMeshRender);

	m_DebugRenderObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl"));
}

CDbgRenderMgr::~CDbgRenderMgr()
{
	delete m_DebugRenderObj;
	m_DebugRenderObj = nullptr;
}

void CDbgRenderMgr::render()
{
	list<tDebugShapeInfo>::iterator iter = m_ShapeInfo.begin();

	for (; iter != m_ShapeInfo.end();)
	{
		// ������� ������ �ȵǾ� ������
		if (iter->matWorld == XMMatrixIdentity())
		{
			m_DebugRenderObj->Transform()->SetRelativePos(iter->Position);
			m_DebugRenderObj->Transform()->SetRelativeScale(iter->Scale);
			m_DebugRenderObj->Transform()->SetRelativeRotation(iter->Rotation);
			m_DebugRenderObj->Transform()->finaltick();
		}
		else
		{
			m_DebugRenderObj->Transform()->SetWorldMat(iter->matWorld);
		}

		// �޽�
		switch (iter->Shape)
		{
		case DEBUG_SHAPE::RECT:
			m_DebugRenderObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_DebugRenderObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::LINE:
			m_DebugRenderObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"LineMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_DebugRenderObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_DebugRenderObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		default:
			break;
		}
		m_DebugRenderObj->MeshRender()->GetMaterial()->SetScalarparam(VEC4_0, iter->Color);
		m_DebugRenderObj->render();

		iter->Age += DT;

		if (iter->Duration < iter->Age)
		{
			iter = m_ShapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}