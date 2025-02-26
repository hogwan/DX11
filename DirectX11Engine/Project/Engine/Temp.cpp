#include "pch.h"
#include "Temp.h"
#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

// Graphics Pipeline

// ========================
// IA (Input Assembler)
// ========================
// Vertex Buffer
// Index Buffer
// Topology
// Layout

// =========================
// Vertex Shader Stage
// =========================
// ������ 3���� �� ��ǥ�迡�� NDC 2���� ��ǥ�� ����

// Tessellation
// Hull Shader
// Domain Shader

// Geometry Shader

// =========================
// Rasterizer
// =========================

// =========================
// Pixel Shader
// =========================
// �ȼ� �� ȣ��Ǵ� �Լ�
// �� �ȼ��� ������ �����ؼ� ����Ÿ�ٿ� ���

// =========================
// Output Merge State
// =========================
// DepthStencil State
// BlendState State

// RenderTargetTexture
// DepthStencilTexture

// ���� ������ �����ϴ� ����
ComPtr<ID3D11Buffer> g_VB;

// ���� ���۳����� ����� ������ ����Ű�� �ε��� ������ �����ϴ� ����
ComPtr<ID3D11Buffer> g_IB;

// �������(Constant Buffer) ��ü�� ��ġ, ũ��, ȸ�� ������ �����ϴ� �뵵
ComPtr<ID3D11Buffer> g_CB;

// ���� �ϳ��� �����ϴ� Layout ����
ComPtr<ID3D11InputLayout> g_Layout;

// System Mem ���� ����
Vtx g_arrVtx[4] = {};
UINT g_arrIdx[6] = {0,2,3,0,1,2};

// HLSL
// Vertex Shader
ComPtr<ID3DBlob>			g_VSBlob;	// ������ �� ���̴� �ڵ带 ����
ComPtr<ID3D11VertexShader>	g_VS;		// Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>			g_PSBlob;
ComPtr<ID3D11PixelShader>	g_PS;

//Error Blob
ComPtr<ID3DBlob>		g_ErrBlob;


int TempInit()
{
	// 0 - 1 
	// |   |
	// 3 - 2
	g_arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	// ���� ���� ����
	D3D11_BUFFER_DESC VBDesc = {};

	VBDesc.ByteWidth = sizeof(Vtx) * 4;
	VBDesc.MiscFlags = 0;

	//������ �뵵 ����
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// ���۰� ������ ���Ŀ� CPU���� �����ؼ� GPU �� �ִ� �����͸�
	// ����Ⱑ �����ϰ� ����
	VBDesc.CPUAccessFlags =D3D11_CPU_ACCESS_WRITE;
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{
		return E_FAIL;
	}

	//IndexBuffer
	D3D11_BUFFER_DESC IBDesc = {};

	IBDesc.ByteWidth = sizeof(UINT) * 6;
	IBDesc.MiscFlags = 0;

	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	IBDesc.CPUAccessFlags = 0;
	IBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ISubDesc = {};
	ISubDesc.pSysMem = g_arrIdx;

	if (FAILED(DEVICE->CreateBuffer(&IBDesc, &ISubDesc, g_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ���ؽ� ���̴�
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Std2D", "vs_5_0", D3DCOMPILE_DEBUG, 0
		, g_VSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer()
				, "���ؽ� ���̴� ������ ����", MB_OK);
		}
		else
		{
			MessageBox(nullptr, L"������ ã�� �� �����ϴ�."
				, L"���ؽ� ���̴� ������ ����", MB_OK);
		}
		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
		, g_VSBlob->GetBufferSize()
		, nullptr, g_VS.GetAddressOf())))
	{
		return E_FAIL;
	}

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

	// ���� ���̾ƿ� ����
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].SemanticName = "POSITION";

	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].SemanticName = "COLOR";

	if (FAILED(DEVICE->CreateInputLayout(LayoutDesc, 2
		, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), g_Layout.GetAddressOf())))
	{
		return E_FAIL;
	}

	//Pixel Shader
	if (FAILED(DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
		, g_PSBlob->GetBufferSize()
		, nullptr, g_PS.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void TempRelease()
{
}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.y += DT * 0.5f;
		}
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::S))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.y -=DT * 0.5f;
		}
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::A))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.x -= DT * 0.5f;
		}
	}

	if (KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(KEY::D))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_arrVtx[i].vPos.x += DT * 0.5f;
		}
	}

	//Sysmem -> GPU
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, g_arrVtx, sizeof(Vtx) * 4);

	CONTEXT->Unmap(g_VB.Get(), 0);
}

void TempRender()
{
	UINT Stride = sizeof(Vtx);
	UINT Offset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	CONTEXT->DrawIndexed(6,0,0);
}
