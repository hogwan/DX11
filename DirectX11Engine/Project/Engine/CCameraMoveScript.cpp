#include "pch.h"
#include "CCameraMoveScript.h"
#include "CTransform.h"
#include "CCamera.h"

CCameraMoveScript::CCameraMoveScript()
	:m_Speed(200.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::tick()
{
	//ī�޶� ���� ��� ����
	if (KEY_TAP(KEY::P))
	{
		Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC ? Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE) : Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		{
			Vec3 vPos = Transform()->GetRelativePos();
			Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, 0.f));
			Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}
	}

	if (Camera()->GetProjType() == PROJ_TYPE::PERSPECTIVE)
	{
		MoveByPerspective();
	}
	else
	{
		MoveByOrthographic();
	}
	
}

void CCameraMoveScript::MoveByPerspective()
{
	// Shift �ӵ� ����
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
		vCurPos += vFront * Speed * DT;
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

void CCameraMoveScript::MoveByOrthographic()
{
	// Shift �ӵ� ����
	float Speed = m_Speed;
	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 4.f;
	}

	Vec3 vCurPos = Transform()->GetRelativePos();


	if (KEY_PRESSED(KEY::W))
	{
		vCurPos.y += Speed * DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vCurPos.y -= Speed * DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vCurPos.x -= Speed * DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vCurPos.x += Speed * DT;
	}

	if (KEY_PRESSED(KEY::Q))
	{
		float Scale = Camera()->GetScale();
		Scale += DT;
		Camera()->SetScale(Scale);
	}

	if (KEY_PRESSED(KEY::E))
	{
		float Scale = Camera()->GetScale();
		Scale -= DT;

		if (Scale < 0.01f)
		{
			Scale = 0.01f;
		}

		Camera()->SetScale(Scale);
	}

	GetOwner()->Transform()->SetRelativePos(vCurPos);
}
