#pragma once
#include "CShader.h"
class CGraphicShader :
    public CShader
{
private:
    ComPtr<ID3DBlob>    m_VSBlob;
    ComPtr<ID3DBlob>    m_PSBlob;

    ComPtr<ID3D11VertexShader> m_VS;
    ComPtr<ID3D11PixelShader> m_PS;

public:
    int CreateVertexShader(const wstring& _strFilePath, const string& _VSFuncName);;
    int CreatePixelShader(const wstring& _strFilePath, const string& _PSFuncName);

    virtual void Binding() override;

public:
    CGraphicShader();
    ~CGraphicShader();
};

