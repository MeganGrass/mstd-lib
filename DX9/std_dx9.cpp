/*
*
*	Megan Grass
*	April 12, 2024
*
*/


#pragma once

#include "std_dx9.h"

#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif
#pragma comment(lib, "dxguid.lib")

extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

D3DVERTEXELEMENT9 ElementVecPoint[] =
{
	{ 0, offsetof(vecp, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vecp, size), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVecPointc[] =
{
	{ 0, offsetof(vecpc, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vecpc, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vecpc, size), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVecPointct[] =
{
	{ 0, offsetof(vecpct, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vecpct, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vecpct, size), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
	{ 0, offsetof(vecpct, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3t[] =
{
	{ 0, offsetof(vec3t, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3t, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec4t[] =
{
	{ 0, offsetof(vec4t, vec), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec4t, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec4ct[] =
{
	{ 0, offsetof(vec4ct, vec), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec4ct, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vec4ct, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3n[] =
{
	{ 0, offsetof(vec3n, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3n, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3nt[] =
{
	{ 0, offsetof(vec3nt, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3nt, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, offsetof(vec3nt, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3c[] =
{
	{ 0, offsetof(vec3c, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3c, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3cn[] =
{
	{ 0, offsetof(vec3cn, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3cn, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, offsetof(vec3cn, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3ct[] =
{
	{ 0, offsetof(vec3ct, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3ct, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vec3ct, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 ElementVec3cnt[] =
{
	{ 0, offsetof(vec3cnt, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3cnt, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, offsetof(vec3cnt, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vec3cnt, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};


static LRESULT CALLBACK DirectX9WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	Standard_DirectX_9* DX9 = (Standard_DirectX_9*)dwRefData;

	if (!DX9 || !DX9->Ready() || !DX9->NormalState()) { return DefSubclassProc(hWnd, uMsg, wParam, lParam); }

	{
		WINDOWPLACEMENT WindowPlacement{ sizeof(WINDOWPLACEMENT) };
		GetWindowPlacement(DX9->Window()->GetParent(), &WindowPlacement);
		if ((WindowPlacement.showCmd == SW_SHOWMINIMIZED) || IsIconic(DX9->Window()->GetParent()))
		{
			DX9->SetDeviceState(D3DDEVICE_STATE::UNKNOWN);
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);
		}
	}

	switch (uMsg)
	{
	case WM_WINDOWPOSCHANGING:
		break;
	case WM_WINDOWPOSCHANGED:
		DX9->Window()->MsgPositionChanged(wParam, lParam);
		if (!DX9->NativeResolution())
		{
			RECT Rect{};
			GetWindowRect(DX9->Window()->Get(), &Rect);
			DX9->GetPresentParameters()->BackBufferWidth = (Rect.right - Rect.left);
			DX9->GetPresentParameters()->BackBufferHeight = (Rect.bottom - Rect.top);
		}
		DX9->Reset();
		break;
	case WM_DISPLAYCHANGE:
		DX9->Window()->MsgDisplayChange(wParam, lParam);
		DX9->Reset();
		break;
	case WM_DROPFILES:
		SendMessage(DX9->Window()->GetParent(), WM_DROPFILES, wParam, lParam);
		break;
	case WM_DPICHANGED:
		DX9->Window()->MsgDpiChanged(wParam, lParam);
		DX9->Reset();
		break;
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

void Standard_DirectX_9::Shutdown(void)
{
	{
		static std::mutex Mutex;
		std::scoped_lock<std::mutex> Lock(Mutex);
	}

	if (b_Complete) { return; }

	b_Abort = true;
	b_Active = false;

	auto StartTime = std::chrono::steady_clock::now();

	while (!b_Complete && !Stop())
	{
		if (std::chrono::steady_clock::now() - StartTime > std::chrono::seconds(5)) { break; }
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	e_DeviceState = D3DDEVICE_STATE::UNKNOWN;

	DestroyWindow(Window()->Get());
}

void Standard_DirectX_9::Update(void)
{
	b_Complete = false;

	while (!b_Ready)
	{
		if (b_Abort)
		{
			b_Complete = !(b_Active = false);
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	Wnd->SetTimer(60);

	while (b_Active)
	{
		Wnd->SleepTimer();

		if (!NormalState())
		{
			e_DeviceState = D3DDEVICE_STATE::UNKNOWN;

			while (b_Active && !NormalState())
			{
				Test();

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	}

	b_Complete = true;
}

void Standard_DirectX_9::InitShaders(void)
{
	std::filesystem::path ShaderPath = Standard_Windows_Common().GetCurrentWorkingDir() / L"shader";
	std::filesystem::path PassThrough = ShaderPath / L"pixel_passthrough.hlsl";
	std::filesystem::path PlayStationDither = ShaderPath / L"pixel_playstation_dither.hlsl";
	std::filesystem::path Vertex = ShaderPath / L"vertex.hlsl";

	PassthroughPixelShader.reset(CreatePixelShaderFromFile(PassThrough, "main", "ps_3_0"));

	PS1DitherPixelShader.reset(CreatePixelShaderFromFile(PlayStationDither, "main", "ps_3_0"));

	ShaderVecPointc = CreateVertexShader(Vertex, ElementVecPointc, "vecpc", "vs_3_0");

	ShaderVecPointct = CreateVertexShader(Vertex, ElementVecPointc, "vecpct", "vs_3_0");

	ShaderVec3t = CreateVertexShader(Vertex, ElementVec3t, "vec3t", "vs_3_0");

	ShaderVec3n = CreateVertexShader(Vertex, ElementVec3n, "vec3n", "vs_3_0");

	ShaderVec3nt = CreateVertexShader(Vertex, ElementVec3nt, "vec3nt", "vs_3_0");

	ShaderVec3c = CreateVertexShader(Vertex, ElementVec3c, "vec3c", "vs_3_0");

	ShaderVec3cn = CreateVertexShader(Vertex, ElementVec3cn, "vec3cn", "vs_3_0");

	ShaderVec3ct = CreateVertexShader(Vertex, ElementVec3ct, "vec3ct", "vs_3_0");

	ShaderVec3cnt = CreateVertexShader(Vertex, ElementVec3cnt, "vec3cnt", "vs_3_0");

	ShaderVec4t = CreateVertexShader(Vertex, ElementVec4t, "vec4t", "vs_3_0");

	ShaderVec4ct = CreateVertexShader(Vertex, ElementVec4ct, "vec4ct", "vs_3_0");
}

const bool Standard_DirectX_9::Initialize(std::shared_ptr<Standard_Window> StdWnd, UINT Width, UINT Height, bool NativeResolution)
{
	if (b_Ready) { return true; }

	Wnd = StdWnd;

	b_NativeResolution = NativeResolution;

	DragAcceptFiles(Wnd->Get(), TRUE);

	SetWindowSubclass(Wnd->Get(), DirectX9WndProc, 0, (DWORD_PTR)this);

	IDirect3D9Ex* Direct3D9Ex = nullptr;
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &Direct3D9Ex))) { Wnd->GetErrorMessage(); }
	pD3D.reset(Direct3D9Ex);

	D3DCAPS9* DeviceCaps = new D3DCAPS9{};
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DeviceCaps))) { Wnd->GetErrorMessage(); }
	m_DeviceCaps.reset(DeviceCaps);

	D3DADAPTER_IDENTIFIER9* AdapterIdentifier = new D3DADAPTER_IDENTIFIER9{};
	if (FAILED(pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, NULL, AdapterIdentifier))) { Wnd->GetErrorMessage(); }
	m_AdapterIdentifier.reset(AdapterIdentifier);

	D3DDISPLAYMODE* DisplayMode = new D3DDISPLAYMODE{};
	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, DisplayMode))) { Wnd->GetErrorMessage(); }
	m_DisplayMode.reset(DisplayMode);

	if (FAILED(pD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_DisplayMode->Format, m_DisplayMode->Format, TRUE))) { Wnd->GetErrorMessage(); }

	if (FAILED(pD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_DisplayMode->Format, m_DisplayMode->Format, FALSE))) { Wnd->GetErrorMessage(); }

	D3DPRESENT_PARAMETERS* PresentParameters = new D3DPRESENT_PARAMETERS{};
	m_PresentParameters.reset(PresentParameters);

	if (b_AntiAliasing)
	{
		DWORD pQualityLevels = NULL;
		if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_DisplayMode->Format, FALSE, D3DMULTISAMPLE_NONMASKABLE, &pQualityLevels)))
		{
			b_AntiAliasing = true;
			m_PresentParameters->MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			m_PresentParameters->MultiSampleQuality = pQualityLevels - 1;
		}
	}
	else
	{
		m_PresentParameters->MultiSampleType = D3DMULTISAMPLE_NONE;
		m_PresentParameters->MultiSampleQuality = NULL;
	}

	if (b_NativeResolution)
	{
		m_PresentParameters->BackBufferWidth = Width;
		m_PresentParameters->BackBufferHeight = Height;
	}
	else
	{
		m_PresentParameters->BackBufferWidth = NULL;
		m_PresentParameters->BackBufferHeight = NULL;
	}

	m_NativeWidth = static_cast<float>(m_PresentParameters->BackBufferWidth);
	m_NativeHeight = static_cast<float>(m_PresentParameters->BackBufferHeight);

	m_PresentParameters->BackBufferFormat = D3DFMT_UNKNOWN;
	m_PresentParameters->BackBufferCount = 1;
	m_PresentParameters->SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_PresentParameters->hDeviceWindow = Wnd->Get();
	m_PresentParameters->Windowed = TRUE;
	m_PresentParameters->EnableAutoDepthStencil = TRUE;
	m_PresentParameters->AutoDepthStencilFormat = D3DFMT_D24S8;
	m_PresentParameters->Flags = NULL;
	m_PresentParameters->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_PresentParameters->PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	/*if (b_Fullscreen)
	{
		m_PresentParameters->BackBufferWidth = m_DisplayMode->Width;
		m_PresentParameters->BackBufferHeight = m_DisplayMode->Height;
		D3DDISPLAYMODEEX FullScreenDisplayMode{};
		D3DDISPLAYROTATION DisplayRotation = D3DDISPLAYROTATION_IDENTITY;
		if (FAILED(pD3D->GetAdapterDisplayModeEx(D3DADAPTER_DEFAULT, &FullScreenDisplayMode, &DisplayRotation))) { Wnd->GetErrorMessage(); }
	}*/

	IDirect3DDevice9Ex* Direct3DDevice9Ex = nullptr;

	if (FAILED(pD3D->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_PresentParameters->hDeviceWindow,
		D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED | D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_ENABLE_PRESENTSTATS | D3DCREATE_NOWINDOWCHANGES,
		m_PresentParameters.get(), NULL, &Direct3DDevice9Ex)))
	{
		Wnd->GetErrorMessage();
	}

	pDevice.reset(Direct3DDevice9Ex);

	Reset();

	InitShaders();

	return b_Ready = b_Active = true;
}

void Standard_DirectX_9::Test(void)
{
	static std::mutex Mutex;
	std::scoped_lock<std::mutex> Lock(Mutex);

	HRESULT hRes = pDevice->CheckDeviceState(m_PresentParameters.get()->hDeviceWindow);

	if (hRes == D3D_OK)
	{
		e_DeviceState = D3DDEVICE_STATE::NORMAL;
		//std::cout << "Direct-X: The device is in a normal state" << std::endl;
	}
	else if (hRes == D3DERR_DEVICELOST)
	{
		e_DeviceState = D3DDEVICE_STATE::LOST;
		std::cout << "Direct-X: The device has been lost but cannot be reset at this time" << std::endl;
	}
	else if (hRes == D3DERR_DEVICEHUNG || hRes == D3DERR_DEVICENOTRESET)
	{
		e_DeviceState = D3DDEVICE_STATE::NOTRESET;
		std::cout << "Direct-X: The device has been hung and needs to be reset" << std::endl;
		Reset();
	}
	else if (hRes == D3DERR_DEVICEREMOVED)
	{
		e_DeviceState = D3DDEVICE_STATE::REMOVED;
		std::cout << "Direct-X: The hardware adapter has been removed" << std::endl;
	}
	else if (hRes == D3DERR_OUTOFVIDEOMEMORY)
	{
		e_DeviceState = D3DDEVICE_STATE::OUT_OF_MEMORY;
		std::cout << "Direct-X: Direct3D does not have enough display memory to perform the operation" << std::endl;
	}
	else if (hRes == S_PRESENT_MODE_CHANGED)
	{
		e_DeviceState = D3DDEVICE_STATE::MODE_CHANGED;
		std::cout << "Direct-X: The desktop display mode has been changed" << std::endl;
		Reset();
	}
	else if (hRes == S_PRESENT_OCCLUDED)
	{
		e_DeviceState = D3DDEVICE_STATE::OCCLUDED;
		std::cout << "Direct-X: The presentation area is occluded" << std::endl;
		//Test();
	}
}

void Standard_DirectX_9::Reset(void)
{
	static std::mutex Mutex;
	std::scoped_lock<std::mutex> Lock(Mutex);

	HRESULT hRes = pDevice->ResetEx(m_PresentParameters.get(), NULL);

	if (hRes == D3D_OK)
	{
		if (pSwapChain) { pSwapChain.reset(); }

		if (FAILED(pDevice->CreateAdditionalSwapChain(m_PresentParameters.get(), (IDirect3DSwapChain9**)&pSwapChain))) { Wnd->GetErrorMessage(); }

		if (m_DeviceCaps->PixelShaderVersion >= D3DPS_VERSION(3, 0))
		{
			pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, reinterpret_cast<DWORD&>(m_DeviceCaps->MaxPointSize));
		}
		else
		{
			pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, 0x3F800000);
		}

		pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, b_AntiAliasing);

		pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

		pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		pDevice->SetRenderState(D3DRS_LASTPIXEL, FALSE);

		Lighting(FALSE);

		TextureFiltering(m_TextureFilter = D3DTEXF_NONE);

		e_DeviceState = D3DDEVICE_STATE::NORMAL;

		b_DeviceWasReset = true;

		//std::cout << "Direct-X: The device has been reset successfully" << std::endl;
	}
	else if (hRes == D3DERR_DEVICELOST)
	{
		e_DeviceState = D3DDEVICE_STATE::LOST;
		std::cout << "Direct-X: The device has been lost but cannot be reset at this time" << std::endl;
	}
	else if (hRes == D3DERR_DEVICEHUNG || hRes == D3DERR_DEVICENOTRESET)
	{
		e_DeviceState = D3DDEVICE_STATE::NOTRESET;
		std::cout << "Direct-X: The device has been hung and needs to be reset" << std::endl;
		Reset();
	}
	else
	{
		e_DeviceState = D3DDEVICE_STATE::UNKNOWN;
		std::cout << "Direct-X: An unknown error occurred while resetting the device: " << std::hex << hRes << std::endl;
	}
}

D3DCAPS9* Standard_DirectX_9::GetUpdatedDeviceCaps(void)
{
	D3DCAPS9* DeviceCaps = new D3DCAPS9{};
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DeviceCaps))) { Wnd->GetErrorMessage(); }
	m_DeviceCaps.reset(DeviceCaps);
	return m_DeviceCaps.get();
}

D3DADAPTER_IDENTIFIER9* Standard_DirectX_9::GetAdapterId(void)
{
	D3DADAPTER_IDENTIFIER9* AdapterIdentifier = new D3DADAPTER_IDENTIFIER9{};
	if (FAILED(pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, NULL, AdapterIdentifier))) { Wnd->GetErrorMessage(); }
	m_AdapterIdentifier.reset(AdapterIdentifier);
	return m_AdapterIdentifier.get();
}

D3DDISPLAYMODE* Standard_DirectX_9::GetDisplayMode(void)
{
	D3DDISPLAYMODE* DisplayMode = new D3DDISPLAYMODE{};
	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, DisplayMode))) { Wnd->GetErrorMessage(); }
	m_DisplayMode.reset(DisplayMode);
	return m_DisplayMode.get();
}

IDirect3DSurface9* Standard_DirectX_9::CreateRenderSurface(std::uint16_t Width, std::uint16_t Height, D3DFORMAT Format)
{
	IDirect3DSurface9* pSurface = nullptr;

	if (FAILED(pDevice->CreateRenderTarget(Width, Height, Format, m_PresentParameters->MultiSampleType, m_PresentParameters->MultiSampleQuality, FALSE, &pSurface, NULL))) { Wnd->GetErrorMessage(); }

	return pSurface;
}

IDirect3DTexture9* Standard_DirectX_9::CreateTexture(std::uint16_t Width, std::uint16_t Height, DWORD Usage)
{
	IDirect3DTexture9* pTexture = nullptr;

	D3DLOCKED_RECT LockedRect{};

	RECT Area = { 0, 0, Width, Height };

	if (FAILED(D3DXCreateTexture(pDevice.get(), Width, Height, D3DX_DEFAULT, Usage, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture))) { Wnd->GetErrorMessage(); }

	if (Usage != D3DUSAGE_RENDERTARGET)
	{
		if (FAILED(pTexture->LockRect(0, &LockedRect, &Area, NULL)))
		{
			Wnd->GetErrorMessage(false);
			pTexture->Release();
			return nullptr;
		}

		BYTE* Bits = static_cast<BYTE*>(LockedRect.pBits);

		if (Bits) { std::memset(Bits, 0xFF, (size_t)(Width * Height * 4)); }

		if (FAILED(pTexture->UnlockRect(0)))
		{
			Wnd->GetErrorMessage(false);
			pTexture->Release();
			return nullptr;
		}
	}

	return pTexture;
}

IDirect3DTexture9* Standard_DirectX_9::CreateTexture(std::unique_ptr<Standard_Image>& Image, bool b_Alpha, DWORD AlphaColor, std::uint8_t AlphaChannel, bool b_VerticalFlip)
{
	if (!Image->IsOpen()) { return nullptr; }

	auto NextPowerOfTwo = [](int32_t x) {
		if (x <= 0) { return 1; }
		x--;
		for (int Shift = 1; Shift < 32; Shift <<= 1) { x |= x >> Shift; }
		return x + 1;
		};

	uint32_t PowWidth = NextPowerOfTwo(Image->GetWidth());
	uint32_t PowHeight = NextPowerOfTwo(Image->GetHeight());

	IDirect3DTexture9* pImage = nullptr;
	IDirect3DTexture9* pImagePow = nullptr;

	D3DLOCKED_RECT LockedRect{};
	D3DLOCKED_RECT LockedRectPow{};

	if (FAILED(D3DXCreateTexture(pDevice.get(), Image->GetWidth(), Image->GetHeight(), D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pImage))) { Wnd->GetErrorMessage(); }
	if (FAILED(D3DXCreateTexture(pDevice.get(), PowWidth, PowHeight, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pImagePow))) { Wnd->GetErrorMessage(); }

	if (FAILED(pImage->LockRect(0, &LockedRect, NULL, 0))) { Wnd->GetErrorMessage(); }
	if (FAILED(pImagePow->LockRect(0, &LockedRectPow, NULL, 0))) { Wnd->GetErrorMessage(); }

	BYTE* pBits = static_cast<BYTE*>(LockedRect.pBits);
	BYTE* pBitsPow = static_cast<BYTE*>(LockedRectPow.pBits);

	if (pBits)
	{
		if (Image->GetDepth() == 4)
		{
			std::uint32_t i = 0;
			for (LONG Y = 0; Y < Image->GetHeight(); Y++)
			{
				for (LONG X = 0; X < Image->GetWidth(); X += 2)
				{
					uint32_t iPixel = Y * Image->GetWidth() + X;
					uint8_t iPalette = Image->GetData().data()[iPixel / 2];
					Pixel_32bpp Color0 = Image->GetPalette().data()[iPalette >> 4];
					Pixel_32bpp Color1 = Image->GetPalette().data()[iPalette & 0x0F];
					uint8_t Alpha = 0xFF;

					if (b_Alpha)
					{
						if ((Color0.R == GetRValue(AlphaColor)) && (Color0.G == GetGValue(AlphaColor)) && (Color0.B == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Color0.R << 16) | (Color0.G << 8) | Color0.B;

					Alpha = 0xFF;

					if (b_Alpha)
					{
						if ((Color1.R == GetRValue(AlphaColor)) && (Color1.G == GetGValue(AlphaColor)) && (Color1.B == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Color1.R << 16) | (Color1.G << 8) | Color1.B;
				}
			}
		}
		else if (Image->GetDepth() == 8)
		{
			std::uint32_t i = 0;
			for (LONG Y = 0; Y < Image->GetHeight(); Y++)
			{
				for (LONG X = 0; X < Image->GetWidth(); X++)
				{
					uint32_t iPixel = Y * Image->GetWidth() + X;
					uint8_t iPalette = Image->GetData().data()[iPixel];
					Pixel_32bpp Color = Image->GetPalette().data()[iPalette];
					uint8_t Alpha = 0xFF;
					if (b_Alpha)
					{
						if ((Color.R == GetRValue(AlphaColor)) && (Color.G == GetGValue(AlphaColor)) && (Color.B == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Color.R << 16) | (Color.G << 8) | Color.B;
				}
			}
		}
		else if (Image->GetDepth() == 16)
		{
			std::uint32_t i = 0;
			for (LONG Y = 0; Y < Image->GetHeight(); Y++)
			{
				for (LONG X = 0; X < Image->GetWidth(); X++)
				{
					uint32_t iPixel = Y * Image->GetWidth() + X;
					uint16_t iPixelData = ((uint16_t*)Image->GetData().data())[iPixel];
					uint8_t Red = (iPixelData & 0x7C00) >> 10;
					uint8_t Green = (iPixelData & 0x03E0) >> 5;
					uint8_t Blue = (iPixelData & 0x001F);
					uint8_t Alpha = 0xFF;
					Red = (Red << 3) | (Red >> 2);
					Green = (Green << 3) | (Green >> 2);
					Blue = (Blue << 3) | (Blue >> 2);
					if (b_Alpha)
					{
						if ((Red == GetRValue(AlphaColor)) && (Green == GetGValue(AlphaColor)) && (Blue == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Red << 16) | (Green << 8) | Blue;
				}
			}
		}
		else if (Image->GetDepth() == 24)
		{
			std::uint32_t i = 0;
			for (LONG Y = 0; Y < Image->GetHeight(); Y++)
			{
				for (LONG X = 0; X < Image->GetWidth(); X++)
				{
					uint32_t iPixel = Y * Image->GetWidth() + X;
					uint8_t Blue = Image->GetData().data()[iPixel * 3];
					uint8_t Green = Image->GetData().data()[iPixel * 3 + 1];
					uint8_t Red = Image->GetData().data()[iPixel * 3 + 2];
					uint8_t Alpha = 0xFF;
					if (b_Alpha)
					{
						if ((Red == GetRValue(AlphaColor)) && (Green == GetGValue(AlphaColor)) && (Blue == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Red << 16) | (Green << 8) | Blue;
				}
			}
		}
		else if (Image->GetDepth() == 32)
		{
			std::uint32_t i = 0;
			for (LONG Y = 0; Y < Image->GetHeight(); Y++)
			{
				for (LONG X = 0; X < Image->GetWidth(); X++)
				{
					uint32_t iPixel = Y * Image->GetWidth() + X;
					uint8_t Blue = Image->GetData().data()[iPixel * 4];
					uint8_t Green = Image->GetData().data()[iPixel * 4 + 1];
					uint8_t Red = Image->GetData().data()[iPixel * 4 + 2];
					uint8_t Alpha = Image->GetData().data()[iPixel * 4 + 3];
					if (b_Alpha)
					{
						if ((Red == GetRValue(AlphaColor)) && (Green == GetGValue(AlphaColor)) && (Blue == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Red << 16) | (Green << 8) | Blue;
				}
			}
		}
	}

	for (LONG Y = 0; Y < Image->GetHeight(); Y++)
	{
		for (LONG X = 0; X < Image->GetWidth(); X++)
		{
			if (pBits != nullptr && pBitsPow != nullptr)
			{
				((uint32_t*)pBitsPow)[Y * PowWidth + X] = ((uint32_t*)pBits)[Y * Image->GetWidth() + X];
			}
		}
	}

	if (b_VerticalFlip && pBits)
	{
		std::vector<uint32_t> Temp(PowWidth * Image->GetHeight());
		std::memcpy(Temp.data(), pBitsPow, (std::size_t)PowWidth * Image->GetHeight() * sizeof(uint32_t));

		for (LONG Y = 0; Y < Image->GetHeight(); Y++)
		{
			for (LONG X = 0; X < Image->GetWidth(); X++)
			{
				std::size_t iSrc = (std::size_t)(Image->GetHeight() - Y - 1) * PowWidth + X;
				std::size_t iDst = (std::size_t)Y * PowWidth + X;
				((uint32_t*)pBitsPow)[iDst] = Temp[iSrc];
			}
		}
	}

	if (FAILED(pImagePow->UnlockRect(0))) { Wnd->GetErrorMessage(); }
	if (FAILED(pImage->UnlockRect(0))) { Wnd->GetErrorMessage(); }
	pImage->Release();

	return pImagePow;
}

IDirect3DTexture9* Standard_DirectX_9::CreateTexture(std::unique_ptr<Sony_PlayStation_Texture>& TIM, uint16_t iPalette, Sony_Texture_Transparency Transparency, DWORD TransparencyColor,
	bool b_VerticalFlip)
{
	Standard_String Str;

	if (!TIM->IsOpen())
	{
		Str.Message(L"Direct-X: Error, Sony PlayStation Texture Image is not open");
		return nullptr;
	}

	bool b_Superblack = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::Superblack));
	bool b_Superimposed = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::Superimposed));
	bool b_External = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::External));
	bool b_Half = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::Half));
	bool b_Full = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::Full));
	bool b_Inverse = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::Inverse));
	bool b_Quarter = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::Quarter));
	bool b_STP = (std::to_underlying(Transparency) & std::to_underlying(Sony_Texture_Transparency::STP));

	iPalette = std::clamp(iPalette, (uint16_t)0, (uint16_t)(TIM->GetPalette().size() - 1));

	auto GetTransparency = [b_Half, b_Full, b_Inverse, b_Quarter]()
		{
			if (b_Half || b_Full || b_Inverse || b_Quarter)
			{
				if (b_Half) { return 0x80; }
				else if (b_Full) { return 0x00; }
				else if (b_Inverse) { return 0xFF; }
				else if (b_Quarter) { return 0x40; }
			}
			return 0x00;
		};

	auto GetAlpha = [b_Superblack, b_Superimposed, b_External, b_STP, GetTransparency, &TIM, iPalette, TransparencyColor](Sony_Pixel_16bpp Color)
		{
			if (b_Superblack && !Color.Red() && !Color.Green() && !Color.Blue() && !Color.Alpha())
			{
				return 0x00;
			}

			if (b_Superimposed && !TIM->GetPalette().empty() &&
				(Color.R == TIM->GetPalette()[TIM->GetPalettePtr(iPalette)].R) &&
				(Color.G == TIM->GetPalette()[TIM->GetPalettePtr(iPalette)].G) &&
				(Color.B == TIM->GetPalette()[TIM->GetPalettePtr(iPalette)].B))
			{
				return GetTransparency();
			}

			if (b_External &&
				(Color.Red() == GetRValue(TransparencyColor)) &&
				(Color.Green() == GetGValue(TransparencyColor)) &&
				(Color.Blue() == GetBValue(TransparencyColor)))
			{
				return GetTransparency();
			}

			if (b_STP && Color.Alpha())
			{
				return GetTransparency();
			}

			return 0xFF;
		};

	auto GetAlpha24 = [b_Superblack, b_Superimposed, b_External, b_STP, GetTransparency, &TIM, iPalette, TransparencyColor](Sony_Pixel_24bpp Color)
		{
			if (b_Superblack && !Color.R && !Color.G && !Color.B)
			{
				return 0x00;
			}

			if (b_Superimposed && !TIM->GetPalette().empty() &&
				(Color.R == TIM->GetPalette()[TIM->GetPalettePtr(iPalette)].Red()) &&
				(Color.G == TIM->GetPalette()[TIM->GetPalettePtr(iPalette)].Green()) &&
				(Color.B == TIM->GetPalette()[TIM->GetPalettePtr(iPalette)].Blue()))
			{
				return GetTransparency();
			}

			if (b_External &&
				(Color.R == GetRValue(TransparencyColor)) &&
				(Color.G == GetGValue(TransparencyColor)) &&
				(Color.B == GetBValue(TransparencyColor)))
			{
				return GetTransparency();
			}

			return 0xFF;
		};

	auto NextPowerOfTwo = [](int32_t x) {
		if (x <= 0) { return 1; }
		x--;
		for (int Shift = 1; Shift < 32; Shift <<= 1) { x |= x >> Shift; }
		return x + 1;
		};

	std::uint32_t Depth = TIM->GetDepth();

	LONG Width = TIM->GetWidth();
	LONG Height = TIM->GetHeight();

	std::size_t pPalette = TIM->GetPalettePtr(iPalette);

	IDirect3DTexture9* pTexture = nullptr;

	D3DLOCKED_RECT LockedRect{};

	RECT Area = { 0, 0, Width, Height };

	UINT WidthPow = NextPowerOfTwo(Width);
	UINT HeightPow = NextPowerOfTwo(Height);

	if (FAILED(D3DXCreateTexture(pDevice.get(), WidthPow, HeightPow, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture)))
	{
		Wnd->GetErrorMessage(false);
		return nullptr;
	}

	if (TIM->GetPixels().empty())
	{
		std::cout << "Direct-X: Error, Sony PlayStation Texture Image pixel data is empty" << std::endl;
		return pTexture;
	}

	if (FAILED(pTexture->LockRect(0, &LockedRect, &Area, NULL)))
	{
		Wnd->GetErrorMessage(false);
		pTexture->Release();
		return nullptr;
	}

	BYTE* Bits = static_cast<BYTE*>(LockedRect.pBits);

	if (Bits)
	{
		for (LONG Y = 0; Y < Height; Y++)
		{
			for (LONG X = 0; X < Width; X++)
			{
				if (Depth == 4)
				{
					Sony_Pixel_4bpp Pixels = TIM->Get4bpp(X, Y);

					if (!TIM->GetPalette().empty())
					{
						Sony_Pixel_16bpp Color = TIM->GetPalette()[pPalette + Pixels.Pix0];

						((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + X] = (GetAlpha(Color) << 24) | Color.Red() << 16 | Color.Green() << 8 | Color.Blue();

						Color = TIM->GetPalette()[pPalette + Pixels.Pix1];

						((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + ++X] = (GetAlpha(Color) << 24) | Color.Red() << 16 | Color.Green() << 8 | Color.Blue();
					}
					else
					{
						((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + X] = 0xFF000000;
						((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + ++X] = 0xFF000000;
					}
				}

				else if (Depth == 8)
				{
					Sony_Pixel_8bpp Pixels = TIM->Get8bpp(X, Y);

					if (!TIM->GetPalette().empty())
					{
						Sony_Pixel_16bpp Color = TIM->GetPalette()[pPalette + Pixels.Pixel];

						((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + X] = (GetAlpha(Color) << 24) | Color.Red() << 16 | Color.Green() << 8 | Color.Blue();
					}
					else
					{
						((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + X] = 0xFF000000;
					}
				}

				else if (Depth == 16)
				{
					Sony_Pixel_16bpp Color = TIM->Get16bpp(X, Y);

					((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + X] = (GetAlpha(Color) << 24) | Color.Red() << 16 | Color.Green() << 8 | Color.Blue();
				}

				else if (Depth == 24)
				{
					Sony_Pixel_24bpp Color = TIM->Get24bpp(X, Y);

					((uint32_t*)Bits)[(Height - Y - 1) * WidthPow + X] = (GetAlpha24(Color) << 24) | Color.R << 16 | Color.G << 8 | Color.B;
				}
			}
		}
	}

	if (b_VerticalFlip && Bits)
	{
		std::vector<uint32_t> Temp(WidthPow * Height);
		std::memcpy(Temp.data(), Bits, (std::size_t)WidthPow * Height * sizeof(uint32_t));

		for (LONG Y = 0; Y < Height; Y++)
		{
			for (LONG X = 0; X < Width; X++)
			{
				std::size_t iSrc = (std::size_t)(Height - Y - 1) * WidthPow + X;
				std::size_t iDst = (std::size_t)Y * WidthPow + X;
				((uint32_t*)Bits)[iDst] = Temp[iSrc];
			}
		}
	}

	if (FAILED(pTexture->UnlockRect(0)))
	{
		Wnd->GetErrorMessage(false);
		pTexture->Release();
		return nullptr;
	}

	return pTexture;
}

IDirect3DTexture9* Standard_DirectX_9::BlitTexture(IDirect3DTexture9* Source, IDirect3DTexture9* Dest, size_t Width, size_t Height, UINT X, UINT Y, bool b_VertFlip)
{
	if (!Source || !Dest) { return nullptr; }

	if (!Width || !Height) { return Dest; }

	D3DSURFACE_DESC SourceDesc{};
	D3DSURFACE_DESC DestDesc{};
	D3DLOCKED_RECT SrcRect{};
	D3DLOCKED_RECT DstRect{};

	if (FAILED(Source->GetLevelDesc(0, &SourceDesc)) || FAILED(Dest->GetLevelDesc(0, &DestDesc))) { return Dest; }

	if (X + Width > DestDesc.Width) { Width = (size_t)DestDesc.Width - X; }
	if (Y + Height > DestDesc.Height) { Height = (size_t)DestDesc.Height - Y; }

	if (SourceDesc.Format != D3DFMT_A8R8G8B8 || DestDesc.Format != D3DFMT_A8R8G8B8)
	{
		std::cout << "Direct-X: Error, Source and Destination textures must be in A8R8G8B8 format" << std::endl;
		return Dest;
	}

	RECT SrcArea = { 0, 0, (LONG)Width, (LONG)Height };
	RECT DstArea = { (LONG)X, (LONG)Y, (LONG)(X + Width), (LONG)(Y + Height) };

	if (FAILED(Source->LockRect(0, &SrcRect, &SrcArea, D3DLOCK_READONLY))) { return Dest; }

	if (FAILED(Dest->LockRect(0, &DstRect, &DstArea, 0)))
	{
		Source->UnlockRect(0);
		return Dest;
	}

	BYTE* SrcBits = static_cast<BYTE*>(SrcRect.pBits);
	BYTE* DstBits = static_cast<BYTE*>(DstRect.pBits);

	for (UINT row = 0; row < Height; ++row)
	{
		BYTE* SrcRow;
		BYTE* DstRow = DstBits + row * DstRect.Pitch;

		if (b_VertFlip) { SrcRow = SrcBits + (Height - 1 - row) * SrcRect.Pitch; }
		else { SrcRow = SrcBits + row * SrcRect.Pitch; }

		if (DstRow && SrcRow) { std::memcpy(DstRow, SrcRow, Width * 4); }
	}

	Dest->UnlockRect(0);
	Source->UnlockRect(0);

	return Dest;
}

bool Standard_DirectX_9::SaveTexture(IDirect3DTexture9* Texture, D3DXIMAGE_FILEFORMAT Format, bool b_VertFlip, const std::filesystem::path& Filename)
{
	if (!Texture) { return false; }

	IDirect3DTexture9* DestTexture = nullptr;

	if (b_VertFlip)
	{
		IDirect3DSurface9* DestSurface = nullptr;
		IDirect3DSurface9* TextureSurface = nullptr;
		D3DSURFACE_DESC TextureDesc{};
		D3DLOCKED_RECT LockedRect{};

		if (FAILED(Texture->GetLevelDesc(0, &TextureDesc)) ||
			FAILED(pDevice->CreateTexture(TextureDesc.Width, TextureDesc.Height, 1, 0, TextureDesc.Format, D3DPOOL_SYSTEMMEM, &DestTexture, nullptr)) ||
			FAILED(Texture->GetSurfaceLevel(0, &TextureSurface)) ||
			FAILED(DestTexture->GetSurfaceLevel(0, &DestSurface)) ||
			FAILED(pDevice->GetRenderTargetData(TextureSurface, DestSurface)))
		{
			Wnd->GetErrorMessage(false);
			return false;
		}

		TextureSurface->Release();

		if (SUCCEEDED(DestSurface->LockRect(&LockedRect, nullptr, D3DLOCK_READONLY | D3DLOCK_NO_DIRTY_UPDATE)))
		{
			UINT rowBytes = TextureDesc.Width * 4;
			std::vector<BYTE> FlippedBytes(TextureDesc.Height * rowBytes);

			BYTE* src = static_cast<BYTE*>(LockedRect.pBits);
			for (size_t y = 0; y < (size_t)TextureDesc.Height; ++y)
			{
				std::memcpy(&FlippedBytes[y * rowBytes], src + ((size_t)TextureDesc.Height - 1 - y) * LockedRect.Pitch, rowBytes);
			}
			DestSurface->UnlockRect();

			if (SUCCEEDED(DestSurface->LockRect(&LockedRect, nullptr, 0)))
			{
				for (size_t y = 0; y < (size_t)TextureDesc.Height; ++y)
				{
					std::memcpy(static_cast<BYTE*>(LockedRect.pBits) + y * LockedRect.Pitch, &FlippedBytes[y * rowBytes], rowBytes);
				}
				DestSurface->UnlockRect();
			}
		}

		DestSurface->Release();
	}
	else
	{
		DestTexture = Texture;
	}

	if (FAILED(D3DXSaveTextureToFileW(Filename.wstring().c_str(), Format, DestTexture, nullptr)))
	{
		Wnd->GetErrorMessage(false);
		return false;
	}

	if (b_VertFlip) { DestTexture->Release(); }

	return true;
}

IDirect3DIndexBuffer9* Standard_DirectX_9::CreateIndexBuffer(D3DFORMAT Format, std::size_t Length)
{
	if ((Format != D3DFMT_INDEX16) && (Format != D3DFMT_INDEX32)) { return nullptr; }

	IDirect3DIndexBuffer9* pIndexBuffer = nullptr;

	if (FAILED(pDevice->CreateIndexBuffer(static_cast<UINT>(Length), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, Format, D3DPOOL_DEFAULT, &pIndexBuffer, NULL))) { Wnd->GetErrorMessage(); }

	return pIndexBuffer;
}

IDirect3DIndexBuffer9* Standard_DirectX_9::CreateIndexBuffer(D3DFORMAT Format, void* pData, std::size_t Length)
{
	if ((Format != D3DFMT_INDEX16) && (Format != D3DFMT_INDEX32)) { return nullptr; }

	IDirect3DIndexBuffer9* pIndexBuffer = CreateIndexBuffer(Format, Length);

	UpdateIndexBuffer(pIndexBuffer, pData);

	return pIndexBuffer;
}

void Standard_DirectX_9::UpdateIndexBuffer(IDirect3DIndexBuffer9* Buffer, void* pData)
{
	if (!Buffer) { return; }

	HRESULT hRes = Buffer->GetDesc(&IndexBufferDesc);
	if (FAILED(hRes)) { return; }

	void* pIndices = nullptr;

	if (FAILED(Buffer->Lock(0, IndexBufferDesc.Size, reinterpret_cast<void**>(&pIndices), 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pIndices, pData, IndexBufferDesc.Size);
	}
	catch (...) { std::cout << "UpdateIndexBuffer: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVertexBuffer(DWORD FVF, std::size_t Length)
{
	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;

	if (FAILED(pDevice->CreateVertexBuffer(static_cast<UINT>(Length), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT, &pVertexBuffer, NULL))) { Wnd->GetErrorMessage(); }

	return pVertexBuffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVertexBuffer(DWORD FVF, void* pData, std::size_t Length)
{
	IDirect3DVertexBuffer9* pVertexBuffer = CreateVertexBuffer(FVF, Length);

	UpdateVertexBuffer(pVertexBuffer, pData);

	return pVertexBuffer;
}

void Standard_DirectX_9::UpdateVertexBuffer(IDirect3DVertexBuffer9* Buffer, void* pData)
{
	if (!Buffer) { return; }

	HRESULT hRes = Buffer->GetDesc(&VertexBufferDesc);
	if (FAILED(hRes)) { return; }

	void* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, VertexBufferDesc.Size, reinterpret_cast<void**>(&pVertices), 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, pData, VertexBufferDesc.Size);
	}
	catch (...) { std::cout << "UpdateVertexBuffer: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vecpc> Data)
{
	if (Data.empty())
	{
		std::cout << "CreatePoint: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTC, Data.size() * sizeof(vecpc));

	vecpc* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vecpc));
	}
	catch (...) { std::cout << "CreatePoint: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vecpct> Data)
{
	if (Data.empty())
	{
		std::cout << "CreatePoint: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTCT, Data.size() * sizeof(vecpct));

	vecpct* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vecpct));
	}
	catch (...) { std::cout << "CreatePoint: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3t(std::vector<vec3t> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3t: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERT3T, Data.size() * sizeof(vec3t));

	vec3t* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3t));
	}
	catch (...) { std::cout << "CreateVec3t: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3t(std::vector<vec3> Vector, std::vector<vec2> UV)
{
	if (Vector.size() != UV.size())
	{
		std::cout << "CreateVec3t: Vector and UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || UV.empty())
	{
		std::cout << "CreateVec3t: Vector and/or UV are empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERT3T, Vector.size() * sizeof(vec3t));

	vec3t* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].uv = UV[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec4t(std::vector<vec4t> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec4t: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERT4T, Data.size() * sizeof(vec4t));

	vec4t* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec4t));
	}
	catch (...) { std::cout << "CreateVec4t: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec4t(std::vector<vec4> Vector, std::vector<vec2> UV)
{
	if (Vector.size() != UV.size())
	{
		std::cout << "CreateVec4t: Vector and UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || UV.empty())
	{
		std::cout << "CreateVec4t: Vector and/or UV are empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERT4T, Vector.size() * sizeof(vec4t));

	vec4t* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].uv = UV[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec4ct(std::vector<vec4ct> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec4ct: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERT4CT, Data.size() * sizeof(vec4ct));

	vec4ct* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec4ct));
	}
	catch (...) { std::cout << "CreateVec4ct: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec4ct(std::vector<vec4> Vector, std::vector<vec2> UV, DWORD Color)
{
	if (Vector.size() != UV.size())
	{
		std::cout << "CreateVec4ct: Vector and UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || UV.empty())
	{
		std::cout << "CreateVec4ct: Vector and/or UV are empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERT4CT, Vector.size() * sizeof(vec4ct));

	vec4ct* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].color = Color;
		pVertices[i].uv = UV[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3n(std::vector<vec3n> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3n: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTN, Data.size() * sizeof(vec3n));

	vec3n* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3n));
	}
	catch (...) { std::cout << "CreateVec3n: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3n(std::vector<vec3> Vector, std::vector<vec3> Normal)
{
	if (Vector.size() != Normal.size())
	{
		std::cout << "CreateVec3n: Vector and Normal sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || Normal.empty())
	{
		std::cout << "CreateVec3n: Vector and/or Normal are empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTN, Vector.size() * sizeof(vec3n));

	vec3n* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].normal = Normal[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3nt(std::vector<vec3nt> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3nt: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTNT, Data.size() * sizeof(vec3nt));

	vec3nt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3nt));
	}
	catch (...) { std::cout << "CreateVec3nt: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3nt(std::vector<vec3> Vector, std::vector<vec3> Normal, std::vector<vec2> UV)
{
	if ((Vector.size() != Normal.size()) || (Vector.size() != UV.size()) || (Normal.size() != UV.size()))
	{
		std::cout << "CreateVec3nt: Vector, Normal, and/or UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || Normal.empty() || UV.empty())
	{
		std::cout << "CreateVec3nt: Vector, Normal, and/or UV are empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTNT, Vector.size() * sizeof(vec3nt));

	vec3nt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].normal = Normal[i];
		pVertices[i].uv = UV[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3c(std::vector<vec3c> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3c: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTC, Data.size() * sizeof(vec3c));

	vec3c* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3c));
	}
	catch (...) { std::cout << "CreateVec3c: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3c(std::vector<vec3> Vector, DWORD Color, DWORD Transparency)
{
	if (Vector.empty())
	{
		std::cout << "CreateVec3c: Vector is empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, Transparency);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTC, Vector.size() * sizeof(vec3c));

	vec3c* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].color = Color;
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3cn(std::vector<vec3cn> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3cn: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTCN, Data.size() * sizeof(vec3cn));

	vec3cn* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3cn));
	}
	catch (...) { std::cout << "CreateVec3cn: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3cn(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, DWORD Transparency)
{
	if (Vector.size() != Normal.size())
	{
		std::cout << "CreateVec3cn: Vector and Normal sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || Normal.empty())
	{
		std::cout << "CreateVec3cn: Vector and/or Normal are empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, Transparency);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTCN, Vector.size() * sizeof(vec3cn));

	vec3cn* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].normal = Normal[i];
		pVertices[i].color = Color;
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3ct(std::vector<vec3ct> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3ct: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTCT, Data.size() * sizeof(vec3ct));

	vec3ct* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3ct));
	}
	catch (...) { std::cout << "CreateVec3ct: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3ct(std::vector<vec3> Vector, DWORD Color, std::vector<vec2> UV, DWORD Transparency)
{
	if (Vector.size() != UV.size())
	{
		std::cout << "CreateVec3ct: Vector and UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || UV.empty())
	{
		std::cout << "CreateVec3ct: Vector and/or UV are empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, Transparency);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTCT, Vector.size() * sizeof(vec3ct));

	vec3ct* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].color = Color;
		pVertices[i].uv = UV[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3cnt(std::vector<vec3cnt> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3cnt: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTCNT, Data.size() * sizeof(vec3cnt));

	vec3cnt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3cnt));
	}
	catch (...) { std::cout << "CreateVec3cnt: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3cnt(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, std::vector<vec2> UV, DWORD Transparency)
{
	if ((Vector.size() != Normal.size()) || (Vector.size() != UV.size()) || (Normal.size() != UV.size()))
	{
		std::cout << "CreateVec3cnt: Vector, Normal, and/or UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || Normal.empty() || UV.empty())
	{
		std::cout << "CreateVec3cnt: Vector, Normal, and/or UV are empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, Transparency);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTCNT, Vector.size() * sizeof(vec3cnt));

	vec3cnt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].normal = Normal[i];
		pVertices[i].color = Color;
		pVertices[i].uv = UV[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}

IDirect3DPixelShader9* Standard_DirectX_9::CreatePixelShader(const char* Code, const char* FunctionName, const char* Profile)
{
	ID3DXBuffer* pShaderBuffer = nullptr;
	IDirect3DPixelShader9* pShader = nullptr;

	if (FAILED(D3DXCompileShader(Code, static_cast<UINT>(strlen(Code)), NULL, NULL, FunctionName, Profile, 0, &pShaderBuffer, NULL, NULL))) { Wnd->GetErrorMessage(); }

	if (FAILED(pDevice->CreatePixelShader((DWORD*)pShaderBuffer->GetBufferPointer(), &pShader))) { Wnd->GetErrorMessage(); }

	pShaderBuffer->Release();

	return pShader;
}

IDirect3DPixelShader9* Standard_DirectX_9::CreatePixelShaderFromFile(const std::filesystem::path& Filename, const char* FunctionName, const char* Profile)
{
	StdFile m_File { Filename, FileAccessMode::Read, true, false };
	if (!m_File.IsOpen()) { Wnd->GetErrorMessage(); }

	std::string ShaderCode((std::istreambuf_iterator<char>(m_File.Get())), std::istreambuf_iterator<char>());

	ShaderCode.push_back('\0');

	return CreatePixelShader(ShaderCode.c_str(), FunctionName, Profile);
}

D3DSHADERPACKET Standard_DirectX_9::CreateVertexShader(void* Element, const char* Code, const char* FunctionName, const char* Profile)
{
	ID3DXBuffer* pShaderBuffer = nullptr;
	IDirect3DVertexShader9* pShader = nullptr;
	ID3DXConstantTable* Const = nullptr;
	IDirect3DVertexDeclaration9* Decl = nullptr;
	D3DSHADERPACKET Packet{};

	if (FAILED(D3DXCompileShader(Code, static_cast<UINT>(strlen(Code)), NULL, NULL, FunctionName, Profile, 0, &pShaderBuffer, NULL, &Const))) { Wnd->GetErrorMessage(); }

	if (FAILED(pDevice->CreateVertexDeclaration((D3DVERTEXELEMENT9*)Element, &Decl))) { Wnd->GetErrorMessage(); }

	if (FAILED(pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &pShader))) { Wnd->GetErrorMessage(); }

	pShaderBuffer->Release();

	Packet.Const.reset(Const);
	Packet.Decl.reset(Decl);
	Packet.Shader.reset(pShader);

	return Packet;
}

D3DSHADERPACKET Standard_DirectX_9::CreateVertexShader(const std::filesystem::path& Filename, void* Element, const char* FunctionName, const char* Profile)
{
	StdFile m_File { Filename, FileAccessMode::Read, true, false };
	if (!m_File.IsOpen()) { Wnd->GetErrorMessage(); }

	std::string ShaderCode((std::istreambuf_iterator<char>(m_File.Get())), std::istreambuf_iterator<char>());

	ShaderCode.push_back('\0');

	return CreateVertexShader(Element, ShaderCode.c_str(), FunctionName, Profile);
}

void Standard_DirectX_9::SetHomogeneousShader(DWORD FVF, D3DXMATRIX* Projection)
{
	ID3DXConstantTable* Const = nullptr;
	IDirect3DVertexDeclaration9* Decl = nullptr;
	IDirect3DVertexShader9* Shader = nullptr;

	D3DXMATRIX ProjectionMatrix;

	switch (FVF)
	{
	case D3DFVF_VERT4T:
		Const = ShaderVec4t.Const.get();
		Decl = ShaderVec4t.Decl.get();
		Shader = ShaderVec4t.Shader.get();
		break;
	case D3DFVF_VERT4CT:
		Const = ShaderVec4ct.Const.get();
		Decl = ShaderVec4ct.Decl.get();
		Shader = ShaderVec4ct.Shader.get();
		break;
	default:
		pDevice->SetVertexShader(nullptr);
		std::cout << "SetHomogeneousShader: Unsupported FVF (0x" << std::hex << FVF << ")" << std::dec << std::endl;
		return;
	}

	pDevice->SetVertexDeclaration(Decl);

	if (!Projection) { pDevice->GetTransform(D3DTS_PROJECTION, &ProjectionMatrix); } else { ProjectionMatrix = *Projection; }

	D3DXVECTOR4 Clip(0.0f, 0.0f, m_DepthScaleZ, m_DepthMaxZ);

	D3DXHANDLE pProjection = Const->GetConstantByName(NULL, "Projection");
	D3DXHANDLE pClip = Const->GetConstantByName(NULL, "Clip");

	Const->SetMatrix(pDevice.get(), pProjection, &ProjectionMatrix);
	Const->SetVector(pDevice.get(), pClip, &Clip);

	pDevice->SetVertexShader(Shader);
}

void Standard_DirectX_9::SetVertexShader(DWORD FVF, D3DXMATRIX* World, D3DXMATRIX* View, D3DXMATRIX* Projection)
{
	ID3DXConstantTable* Const = nullptr;
	IDirect3DVertexDeclaration9* Decl = nullptr;
	IDirect3DVertexShader9* Shader = nullptr;

	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjectionMatrix;

	switch (FVF)
	{
	case D3DFVF_POINTC:
		Const = ShaderVecPointc.Const.get();
		Decl = ShaderVecPointc.Decl.get();
		Shader = ShaderVecPointc.Shader.get();
		break;
	case D3DFVF_POINTCT:
		Const = ShaderVecPointct.Const.get();
		Decl = ShaderVecPointct.Decl.get();
		Shader = ShaderVecPointct.Shader.get();
		break;
	case D3DFVF_VERT3T:
		Const = ShaderVec3t.Const.get();
		Decl = ShaderVec3t.Decl.get();
		Shader = ShaderVec3t.Shader.get();
		break;
	case D3DFVF_VERT4T:
		SetHomogeneousShader(FVF, Projection);
		return;
	case D3DFVF_VERT4CT:
		SetHomogeneousShader(FVF, Projection);
		return;
	case D3DFVF_VERTN:
		Const = ShaderVec3n.Const.get();
		Decl = ShaderVec3n.Decl.get();
		Shader = ShaderVec3n.Shader.get();
		break;
	case D3DFVF_VERTNT:
		Const = ShaderVec3nt.Const.get();
		Decl = ShaderVec3nt.Decl.get();
		Shader = ShaderVec3nt.Shader.get();
		break;
	case D3DFVF_VERTC:
		Const = ShaderVec3c.Const.get();
		Decl = ShaderVec3c.Decl.get();
		Shader = ShaderVec3c.Shader.get();
		break;
	case D3DFVF_VERTCN:
		Const = ShaderVec3cn.Const.get();
		Decl = ShaderVec3cn.Decl.get();
		Shader = ShaderVec3cn.Shader.get();
		break;
	case D3DFVF_VERTCT:
		Const = ShaderVec3ct.Const.get();
		Decl = ShaderVec3ct.Decl.get();
		Shader = ShaderVec3ct.Shader.get();
		break;
	case D3DFVF_VERTCNT:
		Const = ShaderVec3cnt.Const.get();
		Decl = ShaderVec3cnt.Decl.get();
		Shader = ShaderVec3cnt.Shader.get();
		break;
	default:
		pDevice->SetVertexShader(nullptr);
		std::cout << "SetVertexShader: Unsupported FVF (0x" << std::hex << FVF << ")" << std::dec << std::endl;
		return;
	}

	pDevice->SetVertexDeclaration(Decl);

	if (!World) { pDevice->GetTransform(D3DTS_WORLD, &WorldMatrix); } else { WorldMatrix = *World; }
	if (!View) { pDevice->GetTransform(D3DTS_VIEW, &ViewMatrix); } else { ViewMatrix = *View; }
	if (!Projection) { pDevice->GetTransform(D3DTS_PROJECTION, &ProjectionMatrix); } else { ProjectionMatrix = *Projection; }

	D3DXHANDLE pWorld = Const->GetConstantByName(NULL, "World");
	D3DXHANDLE pView = Const->GetConstantByName(NULL, "View");
	D3DXHANDLE pProjection = Const->GetConstantByName(NULL, "Projection");

	Const->SetMatrix(pDevice.get(), pWorld, &WorldMatrix);
	Const->SetMatrix(pDevice.get(), pView, &ViewMatrix);
	Const->SetMatrix(pDevice.get(), pProjection, &ProjectionMatrix);

	pDevice->SetVertexShader(Shader);
}

void Standard_DirectX_9::Draw(D3DDRAWPACKET Packet)
{
	float Width = 0.0f;
	float Height = 0.0f;
	float ScaleX = 0.0f;
	float ScaleY = 0.0f;
	static constexpr float Nullify = 0.0f;

	if (FAILED(Packet.Vertices->GetDesc(&VertexBufferDesc))) { return; }

	if (!Packet.PixelShader) { Packet.PixelShader = PassthroughPixelShader.get(); }

	if (Packet.Primitive.Fill == D3DFILL_WIREFRAME) { Packet.Texture = nullptr; }

	if (Packet.Texture)
	{
		if (!FAILED(Packet.Texture->GetLevelDesc(0, &TextureDesc)))
		{
			Width = (float)TextureDesc.Width;
			Height = (float)TextureDesc.Height;
			if (Packet.TextureAttr.Width && Width > Packet.TextureAttr.Width) { ScaleX = Packet.TextureAttr.Width / Width; }
			if (Packet.TextureAttr.Height && Height > Packet.TextureAttr.Height) { ScaleY = Packet.TextureAttr.Height / Height; }
		}
	}

	ZBuffer(Packet.ZBuffer.Active, Packet.ZBuffer.Type, Packet.ZBuffer.Func);

	SetVertexShader(VertexBufferDesc.FVF, Packet.Matrix.World, Packet.Matrix.View, Packet.Matrix.Projection);

	pDevice->SetPixelShaderConstantF(0, &Width, 1);
	pDevice->SetPixelShaderConstantF(1, &Height, 1);
	pDevice->SetPixelShaderConstantF(2, &ScaleX, 1);
	pDevice->SetPixelShaderConstantF(3, &ScaleY, 1);

	pDevice->SetPixelShader(Packet.PixelShader);

	pDevice->SetRenderState(D3DRS_FILLMODE, Packet.Primitive.Fill);

	pDevice->SetStreamSource(0, Packet.Vertices, 0, Packet.Primitive.Stride);

	pDevice->SetTexture(0, Packet.Texture);

	if (Packet.Indices)
	{
		pDevice->SetIndices(Packet.Indices);
		if (FAILED(Packet.Indices->GetDesc(&IndexBufferDesc))) { return; }

		UINT IndexSize = (IndexBufferDesc.Format == D3DFMT_INDEX16) ? sizeof(WORD) : sizeof(DWORD);
		UINT NumIndices = IndexBufferDesc.Size / IndexSize;

		switch (Packet.Primitive.Type)
		{
		case D3DPT_POINTLIST:
			pDevice->DrawIndexedPrimitive(Packet.Primitive.Type, 0, 0, VertexBufferDesc.Size / Packet.Primitive.Stride, 0, NumIndices);
			break;
		case D3DPT_LINELIST:
			pDevice->DrawIndexedPrimitive(Packet.Primitive.Type, 0, 0, VertexBufferDesc.Size / Packet.Primitive.Stride / 2, 0, NumIndices / 2);
			break;
		case D3DPT_LINESTRIP:
			pDevice->DrawIndexedPrimitive(Packet.Primitive.Type, 0, 0, VertexBufferDesc.Size / Packet.Primitive.Stride - 1, 0, NumIndices - 1);
			break;
		case D3DPT_TRIANGLELIST:
			pDevice->DrawIndexedPrimitive(Packet.Primitive.Type, 0, 0, VertexBufferDesc.Size / Packet.Primitive.Stride / 3, 0, NumIndices / 3);
			break;
		case D3DPT_TRIANGLESTRIP:
		case D3DPT_TRIANGLEFAN:
			pDevice->DrawIndexedPrimitive(Packet.Primitive.Type, 0, 0, VertexBufferDesc.Size / Packet.Primitive.Stride - 2, 0, NumIndices - 2);
			break;
		}
	}
	else
	{
		pDevice->SetFVF(VertexBufferDesc.FVF);

		switch (Packet.Primitive.Type)
		{
		case D3DPT_POINTLIST:
			pDevice->DrawPrimitive(Packet.Primitive.Type, 0, VertexBufferDesc.Size / Packet.Primitive.Stride);
			break;
		case D3DPT_LINELIST:
			pDevice->DrawPrimitive(Packet.Primitive.Type, 0, VertexBufferDesc.Size / Packet.Primitive.Stride / 2);
			break;
		case D3DPT_LINESTRIP:
			pDevice->DrawPrimitive(Packet.Primitive.Type, 0, VertexBufferDesc.Size / Packet.Primitive.Stride - 1);
			break;
		case D3DPT_TRIANGLELIST:
			pDevice->DrawPrimitive(Packet.Primitive.Type, 0, VertexBufferDesc.Size / Packet.Primitive.Stride / 3);
			break;
		case D3DPT_TRIANGLESTRIP:
		case D3DPT_TRIANGLEFAN:
			pDevice->DrawPrimitive(Packet.Primitive.Type, 0, VertexBufferDesc.Size / Packet.Primitive.Stride - 2);
			break;
		}
	}

	pDevice->SetPixelShaderConstantF(0, &Nullify, 1);
	pDevice->SetPixelShaderConstantF(1, &Nullify, 1);
	pDevice->SetPixelShaderConstantF(2, &Nullify, 1);
	pDevice->SetPixelShaderConstantF(3, &Nullify, 1);
}

D3DXMATRIX Standard_DirectX_9::SetWorld(float X, float Y, float Z, float RX, float RY, float RZ, float SX, float SY, float SZ)
{
	D3DXMATRIX World, Translation, RotX, RotY, RotZ, Scale;

	D3DXMatrixTranslation(&Translation, X, Y, Z);

	D3DXMatrixRotationX(&RotX, D3DXToRadian(RX));
	D3DXMatrixRotationY(&RotY, D3DXToRadian(RY));
	D3DXMatrixRotationZ(&RotZ, D3DXToRadian(RZ));

	D3DXMatrixScaling(&Scale, SX, SY, SZ);

	World = Scale * RotX * RotY * RotZ * Translation;

	pDevice->SetTransform(D3DTS_WORLD, &World);

	return World;
}

void Standard_DirectX_9::AntiAliasing(bool OnOff)
{
	b_AntiAliasing = OnOff;

	if (b_AntiAliasing)
	{
		DWORD pQualityLevels = NULL;
		if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_DisplayMode->Format, FALSE, D3DMULTISAMPLE_NONMASKABLE, &pQualityLevels)))
		{
			b_AntiAliasing = true;
			m_PresentParameters->MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			m_PresentParameters->MultiSampleQuality = pQualityLevels - 1;
		}
	}
	else
	{
		m_PresentParameters->MultiSampleType = D3DMULTISAMPLE_NONE;
		m_PresentParameters->MultiSampleQuality = NULL;
	}

	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, b_AntiAliasing);
}

void Standard_DirectX_9::Lighting(bool OnOff)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, OnOff);

	if (OnOff)
	{
		pDevice->SetRenderState(D3DRS_AMBIENT, AmbientColor);
		pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		AlphaBlending(TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA, D3DBLENDOP_ADD);

		pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

		/*pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);*/

		D3DMATERIAL9 material{};
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 1.0f;
		material.Diffuse.b = 1.0f;
		material.Diffuse.a = 1.0f;
		material.Ambient.r = static_cast<float>(GetRValue(AmbientColor)) / 255.0f;
		material.Ambient.g = static_cast<float>(GetGValue(AmbientColor)) / 255.0f;
		material.Ambient.b = static_cast<float>(GetBValue(AmbientColor)) / 255.0f;
		material.Ambient.a = static_cast<float>(GetAValue(AmbientColor)) / 255.0f;
		pDevice->SetMaterial(&material);
	}
	else
	{
		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLEND_ZERO);

		//pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		//pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	}
}

void Standard_DirectX_9::CreateAxisGrid(void)
{
	if (Grid && Axis) { return; }

	Grid.reset(CreateVertexBuffer(D3DFVF_VERTC, 68 * sizeof(vec3c)));

	if (!Grid) { return; }

	vec3c* pVertices = nullptr;

	if (FAILED(Grid->Lock(0, 68 * sizeof(vec3c), reinterpret_cast<void**>(&pVertices), 0))) { Wnd->GetErrorMessage(); }

	size_t n = 0;
	for (FLOAT i = -8.0f; i < 8.000001f; i += 1.0f, n += 2)
	{
		pVertices[n + 0].vec.Set(-8.0f, 0.0f, i);
		pVertices[n + 1].vec.Set(8.0f, 0.0f, i);
		pVertices[n + 0].color = pVertices[n + 1].color = D3DCOLOR_XRGB(192, 192, 192);
	}
	for (FLOAT i = -8.0f; i < 8.000001f; i += 1.0f, n += 2)
	{
		pVertices[n + 0].vec.Set(i, 0.0f, -8.0f);
		pVertices[n + 1].vec.Set(i, 0.0f, 8.0f);
		pVertices[n + 0].color = pVertices[n + 1].color = D3DCOLOR_XRGB(192, 192, 192);
	}

	if (FAILED(Grid->Unlock())) { Wnd->GetErrorMessage(); }

	if (Axis) { return; }

	Axis.reset(CreateVertexBuffer(D3DFVF_VERTC, 6 * sizeof(vec3c)));

	if (!Axis) { return; }

	if (FAILED(Axis->Lock(0, 6 * sizeof(vec3c), reinterpret_cast<void**>(&pVertices), 0))) { Wnd->GetErrorMessage(); }

	pVertices[0].vec.Set(0.0f, 0.0f, 0.0f);
	pVertices[1].vec.Set(8.0f, 0.0f, 0.0f);
	pVertices[2].vec.Set(0.0f, 0.0f, 0.0f);
	pVertices[3].vec.Set(0.0f, -8.0f, 0.0f);
	pVertices[4].vec.Set(0.0f, 0.0f, 0.0f);
	pVertices[5].vec.Set(0.0f, 0.0f, 8.0f);

	pVertices[0].color = D3DCOLOR_XRGB(255, 0, 0);
	pVertices[1].color = D3DCOLOR_XRGB(255, 0, 0);
	pVertices[2].color = D3DCOLOR_XRGB(0, 255, 0);
	pVertices[3].color = D3DCOLOR_XRGB(0, 255, 0);
	pVertices[4].color = D3DCOLOR_XRGB(0, 0, 255);
	pVertices[5].color = D3DCOLOR_XRGB(0, 0, 255);

	if (FAILED(Axis->Unlock())) { Wnd->GetErrorMessage(); }
}

bool Standard_DirectX_9::SaveScreenshot(D3DXIMAGE_FILEFORMAT Format, std::filesystem::path Output)
{
	RECT WindowRect{};

	GetClientRect(Wnd->Get(), &WindowRect);

	IDirect3DSurface9* pSurface = nullptr;

	if (FAILED(pDevice->CreateOffscreenPlainSurfaceEx(WindowRect.right, WindowRect.bottom, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pSurface, NULL, NULL)))
	{
		if (pSurface) { pSurface->Release(); }
		return false;
	}

	if (FAILED(pDevice->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pSurface)))
	{
		if (pSurface) { pSurface->Release(); }
		return false;
	}

	if (FAILED(D3DXSaveSurfaceToFile(Output.wstring().c_str(), Format, pSurface, NULL, NULL)))
	{
		if (pSurface) { pSurface->Release(); }
		return false;
	}

	if (pSurface) { pSurface->Release(); }

	return true;
}

void Standard_DirectX_9::SetPSXLightToggle(bool b_PerPixel, bool b_Off)
{
	b_LightingDisabled = b_Off;
	b_PerVertexLighting = !b_PerPixel;
	b_PerPixelLighting = b_PerPixel;
	const float Mode = b_LightingDisabled ? 0.0f : (b_PerPixel ? 2.0f : 1.0f);
	pDevice->SetPixelShaderConstantF(15, &Mode, 1);
	pDevice->SetVertexShaderConstantF(23, &Mode, 1);
}

void Standard_DirectX_9::SetPSXLightMag(std::uint8_t Mag)
{
	PlayStationLight().Mag = Mag;
}

void Standard_DirectX_9::SetPSXLightAmbient(colorvec Color)
{
	PlayStationLight().Ambient = { Color.r / 255, Color.g / 255, Color.b / 255, 1.0f };

	const float Ambient[4] = { m_Light.Ambient.r, m_Light.Ambient.g, m_Light.Ambient.b, 1.0f };
	pDevice->SetPixelShaderConstantF(5, Ambient, 1);
}

void Standard_DirectX_9::SetPSXLight(std::size_t Index, std::uint8_t Mode, colorvec Color, vec3 Position, std::uint16_t Intensity)
{
	Index = min(Index, 2);

	PlayStationLight().Data[Index].Mode = Mode;

	PlayStationLight().Data[Index].Color = { Color.r / 255.0f, Color.g / 255.0f, Color.b / 255.0f, 1.0f };

	PlayStationLight().Data[Index].Position = { Position.x / 4096.0f, Position.y / 4096.0f, Position.z / 4096.0f };

	PlayStationLight().Data[Index].Intensity = !Intensity ? 0.0f : ((1.0f / Intensity) * 4096);
}

void Standard_DirectX_9::UpdateLightConstants(void)
{
	SetPSXLightToggle(b_PerPixelLighting, b_LightingDisabled);

	const float Ambient[4] = { m_Light.Ambient.r, m_Light.Ambient.g, m_Light.Ambient.b, 0.0f };

	float Position[3][4] = {};
	for (int i = 0; i < 3; ++i)
	{
		Position[i][0] = m_Light.Data[i].Position.x;
		Position[i][1] = m_Light.Data[i].Position.y;
		Position[i][2] = m_Light.Data[i].Position.z;
		Position[i][3] = 0.0f;
	}

	float Color[3][4] = {};
	for (int i = 0; i < 3; ++i)
	{
		Color[i][0] = m_Light.Data[i].Color.r;
		Color[i][1] = m_Light.Data[i].Color.g;
		Color[i][2] = m_Light.Data[i].Color.b;
		Color[i][3] = 0.0f;
	}

	const float Intensity[4] = { m_Light.Data[0].Intensity, m_Light.Data[1].Intensity, m_Light.Data[2].Intensity, 0.0f };

	pDevice->SetPixelShaderConstantF(5, Ambient, 1);
	pDevice->SetPixelShaderConstantF(6, &Position[0][0], 3);
	pDevice->SetPixelShaderConstantF(9, &Color[0][0], 3);
	pDevice->SetPixelShaderConstantF(12, Intensity, 1);

	pDevice->SetVertexShaderConstantF(13, Ambient, 1);
	pDevice->SetVertexShaderConstantF(14, &Position[0][0], 3);
	pDevice->SetVertexShaderConstantF(17, &Color[0][0], 3);
	pDevice->SetVertexShaderConstantF(20, Intensity, 1);
}