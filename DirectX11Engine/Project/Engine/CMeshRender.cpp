#include "pch.h"
#include "CMeshRender.h"
#include "CMesh.h"
#include "CGraphicShader.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	:CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{
	// ������Ʈ�� ��ġ���� ������۸� ���ؼ� ���ε�
	GetOwner()->Transform()->Binding();
	
	//����� ��Ƽ���� ���ε�
	GetMaterial()->Binding();

	// �޽� ���ε� �� ������
	GetMesh()->Render();

}