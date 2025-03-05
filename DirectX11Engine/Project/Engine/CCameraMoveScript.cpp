#include "pch.h"
#include "CCameraMoveScript.h"
#include "CTransform.h"


CCameraMoveScript::CCameraMoveScript()
	:m_Speed(200.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::tick()
{
	// Shift 속도 배율
	float Speed = m_Speed;
	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 4.f;
	}

	Vec3 vCurPos = Transform()->GetRelativePos();
	Vec3 vCurRot = Transform()->GetRelativeRotation();
	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);


	if (KEY_PRESSED(KEY::W))
	{
		vCurPos += vFront* Speed * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vCurPos -= vFront * Speed * DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vCurPos -= vRight * Speed * DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vCurPos += vRight * Speed * DT;
	}

	if (KEY_PRESSED(KEY::Q))
	{
		vCurPos -= vUp * Speed * DT;
	}

	if (KEY_PRESSED(KEY::E))
	{
		vCurPos += vUp * Speed * DT;
	}

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vDrag = CKeyMgr::GetInst()->GetMouseDrag();

		vCurRot.y += vDrag.x * DT * XM_PI * 8.f;
		vCurRot.x -= vDrag.y * DT * XM_PI * 8.f;

		Transform()->SetRelativeRotation(vCurRot);
	}


	GetOwner()->Transform()->SetRelativePos(vCurPos);
}
