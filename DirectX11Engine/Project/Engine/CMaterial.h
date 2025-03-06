#pragma once
#include "CAsset.h"
#include "assets.h"

class CMaterial
	:public CAsset
{
private:
	tMtrlConst			m_Const;
	Ptr<CGraphicShader> m_Shader;
	Ptr<CTexture>		m_arrTex[TEX_PARAM::END];

public:
	void SetShader(Ptr<CGraphicShader> _Shader) { m_Shader = _Shader; }
	Ptr<CGraphicShader> GetShader() { return m_Shader; }

	template<typename T>
	void SetScalarparam(SCALAR_PARAM _Param, const T& _Value);

	void SetTexParam(TEX_PARAM _Param, Ptr<CTexture> _Tex);

public:
	void Binding();

	virtual int Load(const wstring& _FilePath) { return S_OK; };
	virtual int Save(const wstring& _FilePath) { return S_OK; };

public:
	CMaterial();
	~CMaterial();
};

template<typename T>
inline void CMaterial::SetScalarparam(SCALAR_PARAM _Param, const T& _Value)
{
	void* pValue = (void*)&_Value;

	switch (_Param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
		m_Const.iArr[_Param - INT_0] = *((int*)pValue);
		break;

	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
		m_Const.fArr[_Param - FLOAT_0] = *((float*)pValue);
		break;

	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
		m_Const.v2Arr[_Param - VEC2_0] = *((Vec2*)pValue);
		break;

	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
		m_Const.v4Arr[_Param - VEC4_0] = *((Vec4*)pValue);
		break;

	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
		m_Const.matArr[_Param - MAT_0] = *((Matrix*)pValue);
		break;

	default:
		break;
	}
}
