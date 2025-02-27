#include "pch.h"
#include "CPlayerScript.h"


CPlayerScript::CPlayerScript()
	: m_Speed(1.f)
{
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::tick()
{
	Vec3 vCurPos = GetOwner()->Transform()->GetRelativePos();


	if (KEY_PRESSED(KEY::W))
	{
		vCurPos.y += m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vCurPos.y -= m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vCurPos.x -= m_Speed * DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vCurPos.x += m_Speed * DT;
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}
