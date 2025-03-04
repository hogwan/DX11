#include "pch.h"
#include "CTexture.h"
#include "CDevice.h"

CTexture::CTexture()
	:CAsset(ASSET_TYPE::TEXTURE)
{
}

CTexture::~CTexture()
{
}

void CTexture::Binding(int _RegisterNum)
{
	CONTEXT->PSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
}

int CTexture::Load(const wstring& _FilePath)
{
	wchar_t Ext[50] = {};

	_wsplitpath_s(_FilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, Ext, 50);

	wstring strExt = Ext;

	HRESULT hr;
	if (strExt == L".dds" || strExt == L".DDS")
	{
		// .dds .DDS
		hr = LoadFromDDSFile(_FilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
	}
	else if (strExt == L".tag" || strExt == L".TGA")
	{
		// .tag .TGA
		hr = LoadFromTGAFile(_FilePath.c_str(), nullptr, m_Image);
	}
	else
	{
		// .png .jpg .jpeg .bmp
		hr = LoadFromWICFile(_FilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
	}

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"�ؽ��� �ε� ����", L"�ؽ��� �ε� ����", MB_OK);
		return E_FAIL;
	}
	
	//Texture2D Description �ۼ��ؼ� Texture2D ��ü ����
	// Texture2D ��ü�� �̿��ؼ� ShaderResourceView ����
	hr = CreateShaderResourceView(DEVICE
							, m_Image.GetImages()
							, m_Image.GetImageCount()
							, m_Image.GetMetadata()
							, m_SRV.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ShaderResourceView ���� ����", L"�ؽ��� �ε� ����", MB_OK);
		return E_FAIL;
	}

	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

	return hr;
}

int CTexture::Save(const wstring& _FilePath)
{
	return 0;
}
