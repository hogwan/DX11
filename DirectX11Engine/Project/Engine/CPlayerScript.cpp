#include "pch.h"
#include "CPlayerScript.h"


CPlayerScript::CPlayerScript()
	: m_Speed(100.f)
{
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::tick()
{
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();


	if (KEY_PRESSED(KEY::UP))
	{
		vCurPos.y += m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vCurPos.y -= m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		vCurPos.x -= m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vCurPos.x += m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		/*Vec3 ZRot = GetOwner()->Transform()->GetRelativeRotation();
		ZRot.z += DT * XM_PI;

		GetOwner()->Transform()->SetRelativeRotation(ZRot);*/

		vCurPos.z += DT * m_Speed;
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}
