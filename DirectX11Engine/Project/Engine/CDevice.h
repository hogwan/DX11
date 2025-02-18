#pragma once
class CDevice
{
private:
	HWND					m_hMainWnd = nullptr;
	POINT					m_RenderResolution = {};

	ID3D11Device*			m_Device = nullptr;				// GPU �޸� �Ҵ�, DX11 ���� ��ü ����
	ID3D11DeviceContext*	m_Context = nullptr;				// GPU ������ ���� ���

	IDXGISwapChain*			m_SwapChain = nullptr;			// ����Ÿ�� ���� ����, ȭ�鿡 ���� ȭ���� �Խ�

	ID3D11Texture2D*		m_RenderTarget = nullptr;
	ID3D11RenderTargetView*	m_RTV = nullptr;

	ID3D11Texture2D*		m_DepthStencilTex = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
public:
	static CDevice* GetInst()
	{
		static CDevice mgr;
		return &mgr;
	}
public:
	int init(HWND _hWnd, POINT _Resolution);

private:
	CDevice();
	~CDevice();
	CDevice(const CDevice& _other) = delete;
};



