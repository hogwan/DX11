#include "pch.h"
#include "CCamera.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CRenderMgr.h"
#include "CTransform.h"

#include "CDevice.h"

CCamera::CCamera()
	:CComponent(COMPONENT_TYPE::CAMERA)
	, m_CamPriority(-1)
	, m_Far(1000.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::finaltick()
{
	// View ��� ���
	Vec3 vCamWorldPos = GetOwner()->Transform()->GetRelativePos();
	Matrix matViewTrans = XMMatrixTranslation(-vCamWorldPos.x, -vCamWorldPos.y, -vCamWorldPos.z);

	// ī�޶� �ٶ󺸴� ������ z ������ �Ĵٺ����� �ϴ� ȸ������ ȸ����ķ� ���ؾ� �Ѵ�.
	// ī�޶��� ��, ��, �� ����
	Vec3 vR = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec3 vU = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vF = Transform()->GetRelativeDir(DIR_TYPE::FRONT);

	Matrix matViewRot = XMMatrixIdentity();
	matViewRot._11 = vR.x; matViewRot._12 = vU.x; matViewRot._13 = vF.x;
	matViewRot._21 = vR.y; matViewRot._22 = vU.y; matViewRot._23 = vF.y;
	matViewRot._31 = vR.z; matViewRot._32 = vU.z; matViewRot._33 = vF.z;

	m_matView = matViewTrans * matViewRot;

	// Proj ��� ���
	Vec2 vRenderResolution = CDevice::GetInst()->GetRenderResolution();
	float AspectRatio = vRenderResolution.x / vRenderResolution.y;
	m_matProj = XMMatrixPerspectiveFovLH((XM_PI / 3.f), AspectRatio, 1.f, m_Far);
}

void CCamera::render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;
	
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		pLayer->render();
	}
}

void CCamera::SetCameraPriority(int _Priority)
{
	m_CamPriority = _Priority;

	if (0 <= m_CamPriority)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, m_CamPriority);
	}
}
