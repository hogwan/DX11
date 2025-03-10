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
	// 오브젝트의 위치값을 상수버퍼를 통해서 바인딩
	GetOwner()->Transform()->Binding();
	
	//사용할 머티리얼 바인딩
	GetMaterial()->Binding();

	// 메시 바인딩 및 랜더링
	GetMesh()->Render();

}