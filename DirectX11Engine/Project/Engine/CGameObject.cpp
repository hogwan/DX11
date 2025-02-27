#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CRenderComponent.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr != m_arrCom[i])
			m_arrCom[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->tick();
	}
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}
}

void CGameObject::render()
{
	if (m_RenderCom)
	{
		m_RenderCom->render();
	}
}

void CGameObject::AddComponent(CComponent* _Component)
{
	// �Է����� ������ ������Ʈ�� Ÿ���� Ȯ���Ѵ�.
	COMPONENT_TYPE type = _Component->GetComponentType();

	// �Է����� ���� ������Ʈ�� �̹� ������ �ִ� ���
	assert(m_arrCom[(UINT)type] == nullptr);

	// �Էµ� ������Ʈ�� ������ ���� ������Ʈ���� Ȯ��
	CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);
	if (nullptr != pRenderCom)
	{
		// �̹� ������ ���� ������Ʈ�� ������ ���
		assert(!m_RenderCom);

		m_RenderCom = pRenderCom;
	}

	// �Էµ� ������Ʈ�� �迭�� �˸��� �ε��� �ڸ��� �ּҰ��� ����Ѵ�.
	m_arrCom[(UINT)type] = _Component;

	// ������Ʈ�� ���� ������Ʈ�� �������� �˸�
	_Component->m_Owner = this;
}
