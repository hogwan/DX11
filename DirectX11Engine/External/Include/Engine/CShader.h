#pragma once
#include "CAsset.h"
class CShader :
    public CAsset
{
private:
    ComPtr<ID3DBlob>		m_ErrBlob;

public:
    virtual void Binding() = 0;

public:
    CShader(ASSET_TYPE _Type);
    ~CShader();
};

