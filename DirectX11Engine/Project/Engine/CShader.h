#pragma once
#include "CAsset.h"
class CShader :
    public CAsset
{
protected:
    ComPtr<ID3DBlob>		m_ErrBlob;

public:
    virtual void Binding() = 0;

private:
    virtual int Load(const wstring& _FilePath) override { return S_OK; }
    virtual int Save(const wstring& _FilePath) override { return S_OK; }

public:
    CShader(ASSET_TYPE _Type);
    ~CShader();
};

