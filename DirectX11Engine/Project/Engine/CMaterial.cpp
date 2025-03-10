#include "pch.h"
#include "CMaterial.h"
#include "CGraphicShader.h"
#include "CDevice.h"
#include "CConstBuffer.h"

CMaterial::CMaterial()
	:CAsset(ASSET_TYPE::MATERIAL)
{

}

CMaterial::~CMaterial()
{
}

void CMaterial::SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _Tex)
{
	m_arrTex[_Param] = _Tex;
}

void CMaterial::Binding()
{
	// 텍스쳐 바인딩
	for (UINT i = 0; i < TEX_PARAM::END; i++)
	{
		if (nullptr == m_arrTex[i])
		{
			CTexture::Clear(i);
			continue;
		}

		m_arrTex[i]->Binding(i);
	}

	if (nullptr != m_Shader.Get())
	{
		m_Shader->Binding();
	}

	//상수 데이터 바인딩
	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();


}
