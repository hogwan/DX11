#pragma once

class CConstBuffer;

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND					m_hMainWnd = nullptr;
	Vec2					m_RenderResolution;

	ComPtr<ID3D11Device>			m_Device;			// GPU �޸� �Ҵ�, DX11 ���� ��ü ����
	ComPtr<ID3D11DeviceContext>		m_Context;			// GPU ������ ���� ���
	ComPtr<IDXGISwapChain>			m_SwapChain;		// ����Ÿ�� ���� ����, ȭ�鿡 ���� ȭ���� �Խ�

	ComPtr<ID3D11Texture2D>			m_RenderTargetTex;
	ComPtr<ID3D11RenderTargetView>	m_RTV;

	ComPtr<ID3D11Texture2D>			m_DepthStencilTex;
	ComPtr<ID3D11DepthStencilView>	m_DSV;

	ComPtr<ID3D11SamplerState>		m_Sampler[2];
	ComPtr<ID3D11RasterizerState>	m_RS[(UINT)RS_TYPE::END];
	//ComPtr<ID3D11BlendState>		m_BS[];
	//ComPtr<ID3D11DepthStencilState> m_DS[];
	CConstBuffer*					m_CB[(UINT)CB_TYPE::END] = {};

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();
	int CreateSamplerState();
	int CreateRasterizerState();

public:
	int init(HWND _hWnd, Vec2 _Resolution);
	void ClearTarget(float(_ArrColor)[4]);
	void Present() { m_SwapChain->Present(0, 0); }

	Vec2 GetRenderResolution() { return m_RenderResolution; }

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	CConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_CB[(UINT)_Type]; }
	ComPtr<ID3D11RasterizerState> GetRS(RS_TYPE _Type) { return m_RS[(UINT)_Type]; }



};



