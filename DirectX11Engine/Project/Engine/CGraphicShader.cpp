#include "pch.h"
#include "CGraphicShader.h"
#include "CDevice.h"

CGraphicShader::CGraphicShader()
	: CShader(ASSET_TYPE::GRAPHICS_SHADER)
{
}

CGraphicShader::~CGraphicShader()
{
}

int CGraphicShader::CreateVertexShader(const wstring& _strFilePath, const string& _VSFuncName)
{
	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _VSFuncName, "vs_5_0", D3DCOMPILE_DEBUG, 0
		, m_VSBlob.GetAddressOf(), m_ErrBlob.GetAddressOf())))
	{
		if (nullptr != m_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)m_ErrBlob->GetBufferPointer()
				, "���ؽ� ���̴� ������ ����", MB_OK);
		}
		else
		{
			MessageBox(nullptr, L"������ ã�� �� �����ϴ�."
				, L"���ؽ� ���̴� ������ ����", MB_OK);
		}
		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer()
		, m_VSBlob->GetBufferSize()
		, nullptr, m_VS.GetAddressOf())))
	{
		return E_FAIL;
	}
}

int CGraphicShader::CreatePixelShader(const wstring& _strFilePath, const string& _PSFuncName)
{
	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Std2D", "ps_5_0", D3DCOMPILE_DEBUG, 0
		, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer()
				, "�ȼ� ���̴� ������ ����", MB_OK);
		}
		else
		{
			MessageBox(nullptr, L"������ ã�� �� �����ϴ�."
				, L"�ȼ� ���̴� ������ ����", MB_OK);
		}
		return E_FAIL;
	}
}

void CGraphicShader::Binding()
{
	CONTEXT->VSSetShader(m_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(m_PS.Get(), nullptr, 0);
}