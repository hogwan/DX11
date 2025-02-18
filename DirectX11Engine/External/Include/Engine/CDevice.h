#pragma once
class CDevice
{
private:
	HWND					m_hMainWnd = nullptr;
	POINT					m_RenderResolution = {};

	ID3D11Device*			m_Device = nullptr;				// GPU 메모리 할당, DX11 관련 객체 생성
	ID3D11DeviceContext*	m_Context = nullptr;				// GPU 랜더링 관련 명령

	IDXGISwapChain*			m_SwapChain = nullptr;			// 랜더타겟 버퍼 소유, 화면에 최종 화면을 게시

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



