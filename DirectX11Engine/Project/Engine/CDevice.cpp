#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
{

}

CDevice::~CDevice()
{

}

int CDevice::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_RenderResolution = _Resolution;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(
		nullptr
		, D3D_DRIVER_TYPE_HARDWARE
		, nullptr
		, iFlag
		, nullptr
		, 0
		, D3D11_SDK_VERSION
		, m_Device.GetAddressOf()
		, &level
		, m_Context.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SwapChain ����
	if (FAILED(CreateSwapChain()))
	{
		return E_FAIL;
	}

	// View
	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}

	// ViewPort ����
	// ������ ȭ�鿡 ������ ������ ����
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_RenderResolution.x;
	viewport.Height = m_RenderResolution.y;

	// ���� �ؽ��Ŀ� ����Ǵ� ���� Min, Max ����
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	// ViewPort ���� ����
	m_Context->RSSetViewports(1, &viewport);

	return S_OK;
}

void CDevice::ClearTarget(float(_ArrColor)[4])
{
	m_Context->ClearRenderTargetView(m_RTV.Get(), _ArrColor);
	m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.f, 0);
}

int CDevice::CreateSwapChain()
{
	// 1. ��Ʈ ��� ����
	// DXGI_SWAP_EFFECT_DISCARD
	// DXGI_SWAP_EFFECT_SEQUENTIAL
	
	// 2. ��Ī �̵� ���������̼� ��
	// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
	// DXGI_SWAP_EFFECT_FLIP_DISCARD

	DXGI_SWAP_CHAIN_DESC Desc = {};

	// SwapChain �� ȭ���� �Խ�(Present) �� �� ��� ������ ������
	Desc.OutputWindow = m_hMainWnd;
	Desc.Windowed = true;

	// SwapChain�� ����� �� �� ���� �ɼ�
	Desc.BufferCount = 1;
	Desc.BufferDesc.Width = (UINT)m_RenderResolution.x;
	Desc.BufferDesc.Height = (UINT)m_RenderResolution.y;
	Desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;


	IDXGIDevice* pDXGIDevice = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIFactory* pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &Desc, m_SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}

	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}

	pDXGIDevice->Release();
	pAdapter->Release();
	pFactory->Release();

	return S_OK;
}

int CDevice::CreateView()
{
	// RenderTarget Texture �� ����ü�����κ��� ��������
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RenderTargetTex.GetAddressOf());

	// RenderTargetView �� �����Ѵ�.
	m_Device->CreateRenderTargetView(m_RenderTargetTex.Get(), nullptr, m_RTV.GetAddressOf());

	// DepthStencil�� Texture ����
	D3D11_TEXTURE2D_DESC Desc = {};

	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.Width = (UINT)m_RenderResolution.x;
	Desc.Height = (UINT)m_RenderResolution.y;
	Desc.ArraySize = 1;

	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_Device->CreateTexture2D(&Desc, nullptr, m_DepthStencilTex.GetAddressOf());

	// DepthStencilView
	m_Device->CreateDepthStencilView(m_DepthStencilTex.Get(), nullptr, m_DSV.GetAddressOf());

	// RenderTarget �� DepthStencilTarget �� ������� �����Ѵ�.
	m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

	return S_OK;
}
