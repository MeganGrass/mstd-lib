/*
*
*	Megan Grass
*	April 12, 2024
*
*
*	TODO:
*		Draw is now broken because texture dimensions are pow2
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

D3DVERTEXELEMENT9 VecpElements[] =
{
	{ 0, offsetof(vecp, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vecp, size), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 VecpgElements[] =
{
	{ 0, offsetof(vecpg, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vecpg, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vecpg, size), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 VecpgtElements[] =
{
	{ 0, offsetof(vecpgt, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vecpgt, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vecpgt, size), D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE, 0 },
	{ 0, offsetof(vecpgt, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3tElements[] =
{
	{ 0, offsetof(vec3t, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3t, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec4tElements[] =
{
	{ 0, offsetof(vec4t, vec), D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec4t, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3nElements[] =
{
	{ 0, offsetof(vec3n, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3n, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3ntElements[] =
{
	{ 0, offsetof(vec3nt, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3nt, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, offsetof(vec3nt, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3gElements[] =
{
	{ 0, offsetof(vec3g, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3g, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3gnElements[] =
{
	{ 0, offsetof(vec3gn, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3gn, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, offsetof(vec3gn, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3gtElements[] =
{
	{ 0, offsetof(vec3gt, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3gt, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vec3gt, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

D3DVERTEXELEMENT9 Vec3gntElements[] =
{
	{ 0, offsetof(vec3gnt, vec), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, offsetof(vec3gnt, normal), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
	{ 0, offsetof(vec3gnt, color), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
	{ 0, offsetof(vec3gnt, uv), D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};


/*
	Standard Direct-X 9 Window Message Handler
*/
static LRESULT CALLBACK DirectX9WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	Standard_DirectX_9* DX9 = (Standard_DirectX_9*)dwRefData;

	if (!DX9 || !DX9->Ready()) { return DefSubclassProc(hWnd, uMsg, wParam, lParam); }

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


/*
	Soft shutdown
*/
void Standard_DirectX_9::Shutdown(void)
{
	b_Abort = true;
	b_Active = false;
	e_DeviceState = D3DDEVICE_STATE::UNKNOWN;

	if (AxisGrid) { AxisGrid->Release(); AxisGrid = nullptr; }

	if (ShaderVecpg.Decl) { ShaderVecpg.Decl->Release(); ShaderVecpg.Decl = nullptr; }
	if (ShaderVecpg.Shader) { ShaderVecpg.Shader->Release(); ShaderVecpg.Shader = nullptr; }
	if (ShaderVecpg.Const) { ShaderVecpg.Const->Release(); ShaderVecpg.Const = nullptr; }

	if (ShaderVecpgt.Decl) { ShaderVecpgt.Decl->Release(); ShaderVecpgt.Decl = nullptr; }
	if (ShaderVecpgt.Shader) { ShaderVecpgt.Shader->Release(); ShaderVecpgt.Shader = nullptr; }
	if (ShaderVecpgt.Const) { ShaderVecpgt.Const->Release(); ShaderVecpgt.Const = nullptr; }

	if (ShaderVec3t.Decl) { ShaderVec3t.Decl->Release(); ShaderVec3t.Decl = nullptr; }
	if (ShaderVec3t.Shader) { ShaderVec3t.Shader->Release(); ShaderVec3t.Shader = nullptr; }
	if (ShaderVec3t.Const) { ShaderVec3t.Const->Release(); ShaderVec3t.Const = nullptr; }

	if (ShaderVec4t.Decl) { ShaderVec4t.Decl->Release(); ShaderVec4t.Decl = nullptr; }
	if (ShaderVec4t.Shader) { ShaderVec4t.Shader->Release(); ShaderVec4t.Shader = nullptr; }
	if (ShaderVec4t.Const) { ShaderVec4t.Const->Release(); ShaderVec4t.Const = nullptr; }

	if (ShaderVec3n.Decl) { ShaderVec3n.Decl->Release(); ShaderVec3n.Decl = nullptr; }
	if (ShaderVec3n.Shader) { ShaderVec3n.Shader->Release(); ShaderVec3n.Shader = nullptr; }
	if (ShaderVec3n.Const) { ShaderVec3n.Const->Release(); ShaderVec3n.Const = nullptr; }

	if (ShaderVec3nt.Decl) { ShaderVec3nt.Decl->Release(); ShaderVec3nt.Decl = nullptr; }
	if (ShaderVec3nt.Shader) { ShaderVec3nt.Shader->Release(); ShaderVec3nt.Shader = nullptr; }
	if (ShaderVec3nt.Const) { ShaderVec3nt.Const->Release(); ShaderVec3nt.Const = nullptr; }

	if (ShaderVec3g.Decl) { ShaderVec3g.Decl->Release(); ShaderVec3g.Decl = nullptr; }
	if (ShaderVec3g.Shader) { ShaderVec3g.Shader->Release(); ShaderVec3g.Shader = nullptr; }
	if (ShaderVec3g.Const) { ShaderVec3g.Const->Release(); ShaderVec3g.Const = nullptr; }

	if (ShaderVec3gn.Decl) { ShaderVec3gn.Decl->Release(); ShaderVec3gn.Decl = nullptr; }
	if (ShaderVec3gn.Shader) { ShaderVec3gn.Shader->Release(); ShaderVec3gn.Shader = nullptr; }
	if (ShaderVec3gn.Const) { ShaderVec3gn.Const->Release(); ShaderVec3gn.Const = nullptr; }

	if (ShaderVec3gt.Decl) { ShaderVec3gt.Decl->Release(); ShaderVec3gt.Decl = nullptr; }
	if (ShaderVec3gt.Shader) { ShaderVec3gt.Shader->Release(); ShaderVec3gt.Shader = nullptr; }
	if (ShaderVec3gt.Const) { ShaderVec3gt.Const->Release(); ShaderVec3gt.Const = nullptr; }

	if (ShaderVec3gnt.Decl) { ShaderVec3gnt.Decl->Release(); ShaderVec3gnt.Decl = nullptr; }
	if (ShaderVec3gnt.Shader) { ShaderVec3gnt.Shader->Release(); ShaderVec3gnt.Shader = nullptr; }
	if (ShaderVec3gnt.Const) { ShaderVec3gnt.Const->Release(); ShaderVec3gnt.Const = nullptr; }

	if (pSwapChain) { pSwapChain->Release(); pSwapChain = nullptr; }
	if (pDevice) { pDevice->Release(); pDevice = nullptr; }
	if (pD3D) { pD3D->Release(); pD3D = nullptr; }
}


/*
	Update device state
*/
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

	Wnd->SetTimer(30);

	while (b_Active)
	{
		Wnd->SleepTimer();

		if (e_DeviceState != D3DDEVICE_STATE::NORMAL)
		{
			e_DeviceState = D3DDEVICE_STATE::UNKNOWN;

			while ((b_Active) && (e_DeviceState != D3DDEVICE_STATE::NORMAL))
			{
				Test();

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	}

	b_Complete = true;
}


/*
	Initialize basic shaders
*/
void Standard_DirectX_9::InitShaders(void)
{
	PassthroughPixelShader = CreatePixelShader(PixelShaderCode, "main", "ps_3_0");

	PS1DitherPixelShader = CreatePixelShader(PlayStationDitherShaderCode, "main", "ps_3_0");

	if (FAILED(pDevice->CreateVertexDeclaration(VecpgElements, &ShaderVecpg.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(VecpgtElements, &ShaderVecpgt.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3tElements, &ShaderVec3t.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec4tElements, &ShaderVec4t.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3nElements, &ShaderVec3n.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3ntElements, &ShaderVec3nt.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3gElements, &ShaderVec3g.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3gnElements, &ShaderVec3gn.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3gtElements, &ShaderVec3gt.Decl))) { Wnd->GetErrorMessage(); }
	if (FAILED(pDevice->CreateVertexDeclaration(Vec3gntElements, &ShaderVec3gnt.Decl))) { Wnd->GetErrorMessage(); }

	ID3DXBuffer* pShaderBuffer = nullptr;

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vecpg", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVecpg.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVecpg.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vecpgt", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVecpgt.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVecpgt.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3t", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3t.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3t.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec4t", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec4t.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec4t.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3n", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3n.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3n.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3nt", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3nt.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3nt.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3g", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3g.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3g.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3gn", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3gn.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3gn.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3gt", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3gt.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3gt.Shader);
	pShaderBuffer->Release();

	if (FAILED(D3DXCompileShader(VertexShaderCode, static_cast<UINT>(strlen(VertexShaderCode)), NULL, NULL, "vec3gnt", "vs_3_0", 0, &pShaderBuffer, NULL, &ShaderVec3gnt.Const))) { Wnd->GetErrorMessage(); }
	pDevice->CreateVertexShader((DWORD*)pShaderBuffer->GetBufferPointer(), &ShaderVec3gnt.Shader);
	pShaderBuffer->Release();
}


/*
	Initialize
*/
bool Standard_DirectX_9::Initialize(std::shared_ptr<Standard_Window> StdWnd, UINT Width, UINT Height, bool NativeResolution)
{
	if (b_Ready) { return true; }

	Wnd = StdWnd;

	b_NativeResolution = NativeResolution;

	DragAcceptFiles(Wnd->Get(), TRUE);

	SetWindowSubclass(Wnd->Get(), DirectX9WndProc, 0, (DWORD_PTR)this);

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &pD3D))) { Wnd->GetErrorMessage(); }

	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps))) { Wnd->GetErrorMessage(); }

	if (FAILED(pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, NULL, &AdapterIdentifier))) { Wnd->GetErrorMessage(); }

	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode))) { Wnd->GetErrorMessage(); }

	if (FAILED(pD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, DisplayMode.Format, TRUE))) { Wnd->GetErrorMessage(); }

	if (FAILED(pD3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, DisplayMode.Format, FALSE))) { Wnd->GetErrorMessage(); }

	if (b_AntiAliasing)
	{
		DWORD pQualityLevels = NULL;
		if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, FALSE, D3DMULTISAMPLE_NONMASKABLE, &pQualityLevels)))
		{
			b_AntiAliasing = true;
			PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			PresentParameters.MultiSampleQuality = pQualityLevels - 1;
		}
	}
	else
	{
		PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
		PresentParameters.MultiSampleQuality = NULL;
	}

	if (b_NativeResolution)
	{
		PresentParameters.BackBufferWidth = Width;
		PresentParameters.BackBufferHeight = Height;
	}
	else
	{
		PresentParameters.BackBufferWidth = NULL;
		PresentParameters.BackBufferHeight = NULL;
	}

	m_NativeWidth = static_cast<float>(PresentParameters.BackBufferWidth);
	m_NativeHeight = static_cast<float>(PresentParameters.BackBufferHeight);

	PresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	PresentParameters.BackBufferCount = 1;
	PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParameters.hDeviceWindow = Wnd->Get();
	PresentParameters.Windowed = TRUE;
	PresentParameters.EnableAutoDepthStencil = TRUE;
	PresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	PresentParameters.Flags = NULL;
	PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	/*if (b_Fullscreen)
	{
		PresentParameters.BackBufferWidth = DisplayMode.Width;
		PresentParameters.BackBufferHeight = DisplayMode.Height;
		D3DDISPLAYMODEEX FullScreenDisplayMode{};
		D3DDISPLAYROTATION DisplayRotation = D3DDISPLAYROTATION_IDENTITY;
		if (FAILED(pD3D->GetAdapterDisplayModeEx(D3DADAPTER_DEFAULT, &FullScreenDisplayMode, &DisplayRotation))) { Wnd->GetErrorMessage(); }
	}*/

	if (FAILED(pD3D->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, PresentParameters.hDeviceWindow,
		D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED | D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_ENABLE_PRESENTSTATS,
		&PresentParameters, NULL, &pDevice))) { Wnd->GetErrorMessage(); }

	if (FAILED(pDevice->CreateAdditionalSwapChain(&PresentParameters, (IDirect3DSwapChain9**)&pSwapChain))) { Wnd->GetErrorMessage(); }

	if (DeviceCaps.PixelShaderVersion >= D3DPS_VERSION(3, 0))
	{
		pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, reinterpret_cast<DWORD&>(DeviceCaps.MaxPointSize));
	}
	else
	{
		pDevice->SetRenderState(D3DRS_POINTSIZE_MAX, 0x3F800000);
	}

	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, b_AntiAliasing);

	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_LASTPIXEL, FALSE);

	TextureFiltering(m_TextureFilter);

	InitShaders();

	return b_Ready = b_Active = true;
}


/*
	Update device state
*/
void Standard_DirectX_9::Test(void)
{
	if (!pDevice) { return; }

	HRESULT hRes = pDevice->TestCooperativeLevel();

	if (hRes == D3D_OK)
	{
		e_DeviceState = D3DDEVICE_STATE::NORMAL;
	}
	else if (hRes == D3DERR_DEVICELOST)
	{
		e_DeviceState = D3DDEVICE_STATE::LOST;
		std::cout << "Direct-X: The device has been lost but cannot be reset at this time" << std::endl;
	}
	else if (hRes == D3DERR_DEVICENOTRESET)
	{
		Reset(&PresentParameters);
	}
	else if (hRes == D3DERR_DRIVERINTERNALERROR)
	{
		e_DeviceState = D3DDEVICE_STATE::DRIVER_ERROR;
		std::cout << "Direct-X: Internal driver error" << std::endl;
	}
}


/*
	Reset device state
*/
void Standard_DirectX_9::Reset(D3DPRESENT_PARAMETERS* Present)
{
	if (Present)
	{
		PresentParameters = *Present;
	}

	if (!pDevice) { return; }

	HRESULT hRes = pDevice->Reset(&PresentParameters);

	if (hRes == D3D_OK)
	{
		e_DeviceState = D3DDEVICE_STATE::NORMAL;
	}
	else if (hRes == D3DERR_DEVICELOST)
	{
		e_DeviceState = D3DDEVICE_STATE::LOST;
		std::cout << "Direct-X: The device has been lost but cannot be reset at this time" << std::endl;
	}
	else if (hRes == D3DERR_DEVICEREMOVED)
	{
		e_DeviceState = D3DDEVICE_STATE::REMOVED;
		std::cout << "Direct-X: The hardware adapter has been removed" << std::endl;
	}
	else if (hRes == D3DERR_DRIVERINTERNALERROR)
	{
		e_DeviceState = D3DDEVICE_STATE::DRIVER_ERROR;
		std::cout << "Direct-X: Internal driver error" << std::endl;
	}
	else if (hRes == D3DERR_OUTOFVIDEOMEMORY)
	{
		e_DeviceState = D3DDEVICE_STATE::OUT_OF_MEMORY;
		std::cout << "Direct-X: Direct3D does not have enough display memory to perform the operation" << std::endl;
	}
}


/*
	Get Device Caps
*/
D3DCAPS9* Standard_DirectX_9::GetDeviceCaps(void)
{
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps))) { Wnd->GetErrorMessage(); }
	return &DeviceCaps;
}


/*
	Get Adapter Identifier
*/
D3DADAPTER_IDENTIFIER9* Standard_DirectX_9::GetAdapterId(void)
{
	if (FAILED(pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, NULL, &AdapterIdentifier))) { Wnd->GetErrorMessage(); }
	return &AdapterIdentifier;
}


/*
	Get Display Mode
*/
D3DDISPLAYMODE* Standard_DirectX_9::GetDisplayMode(void)
{
	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode))) { Wnd->GetErrorMessage(); }
	return &DisplayMode;
}


/*
	Create Texture
*/
IDirect3DTexture9* Standard_DirectX_9::CreateTexture(std::unique_ptr<Standard_Image>& Image, bool b_Alpha, DWORD AlphaColor, std::uint8_t AlphaChannel)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return nullptr; }

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

	if (FAILED(D3DXCreateTexture(pDevice, Image->GetWidth(), Image->GetHeight(), D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pImage))) { Wnd->GetErrorMessage(); }
	if (FAILED(D3DXCreateTexture(pDevice, PowWidth, PowHeight, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pImagePow))) { Wnd->GetErrorMessage(); }

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
					RGBQUAD Color0 = Image->GetPalette().data()[iPalette >> 4];
					RGBQUAD Color1 = Image->GetPalette().data()[iPalette & 0x0F];
					uint8_t Alpha = 0xFF;

					if (b_Alpha)
					{
						if ((Color0.rgbRed == GetRValue(AlphaColor)) && (Color0.rgbGreen == GetGValue(AlphaColor)) && (Color0.rgbBlue == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Color0.rgbRed << 16) | (Color0.rgbGreen << 8) | Color0.rgbBlue;

					Alpha = 0xFF;

					if (b_Alpha)
					{
						if ((Color1.rgbRed == GetRValue(AlphaColor)) && (Color1.rgbGreen == GetGValue(AlphaColor)) && (Color1.rgbBlue == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Color1.rgbRed << 16) | (Color1.rgbGreen << 8) | Color1.rgbBlue;
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
					RGBQUAD Color = Image->GetPalette().data()[iPalette];
					uint8_t Alpha = 0xFF;
					if (b_Alpha)
					{
						if ((Color.rgbRed == GetRValue(AlphaColor)) && (Color.rgbGreen == GetGValue(AlphaColor)) && (Color.rgbBlue == GetBValue(AlphaColor))) { Alpha = AlphaChannel; }
					}
					((uint32_t*)pBits)[i++] = (Alpha << 24) | (Color.rgbRed << 16) | (Color.rgbGreen << 8) | Color.rgbBlue;
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

	if (FAILED(pImagePow->UnlockRect(0))) { Wnd->GetErrorMessage(); }
	if (FAILED(pImage->UnlockRect(0))) { Wnd->GetErrorMessage(); }
	pImage->Release();

	return pImagePow;
}


/*
	Create Texture from Sony PlayStation Texture (*.TIM)
*/
IDirect3DTexture9* Standard_DirectX_9::CreateTexture(std::unique_ptr<Sony_PlayStation_Texture>& TIM, uint16_t iPalette, Sony_Texture_Transparency Transparency, DWORD TransparencyColor)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return nullptr; }

	if (!TIM->IsOpen())
	{
		Str->Message(L"Direct-X: Error, Sony PlayStation Texture Image is not open");
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

	if (FAILED(D3DXCreateTexture(pDevice, WidthPow, HeightPow, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture)))
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

	if (FAILED(pTexture->UnlockRect(0)))
	{
		Wnd->GetErrorMessage(false);
		pTexture->Release();
		return nullptr;
	}

	return pTexture;
}


/*
	Save Texture (32bpp)
*/
bool Standard_DirectX_9::SaveTexture(IDirect3DTexture9* Texture, D3DXIMAGE_FILEFORMAT Format, const std::filesystem::path& Filename)
{
	if (!Texture) { return false; }

	HRESULT hr = D3DXSaveTextureToFile(Filename.wstring().c_str(), Format, Texture, nullptr);
	if (FAILED(hr))
	{
		Wnd->GetErrorMessage(false);
		return false;
	}

	return true;
}


/*
	Create index buffer
*/
IDirect3DIndexBuffer9* Standard_DirectX_9::CreateIndexBuffer(D3DFORMAT Format, std::size_t Length)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return nullptr; }

	if ((Format != D3DFMT_INDEX16) && (Format != D3DFMT_INDEX32)) { return nullptr; }

	IDirect3DIndexBuffer9* pIndexBuffer = nullptr;

	if (FAILED(pDevice->CreateIndexBuffer(static_cast<UINT>(Length), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, Format, D3DPOOL_DEFAULT, &pIndexBuffer, NULL))) { Wnd->GetErrorMessage(); }

	return pIndexBuffer;
}


/*
	Create index buffer
*/
IDirect3DIndexBuffer9* Standard_DirectX_9::CreateIndexBuffer(D3DFORMAT Format, void* pData, std::size_t Length)
{
	if ((Format != D3DFMT_INDEX16) && (Format != D3DFMT_INDEX32)) { return nullptr; }

	IDirect3DIndexBuffer9* pIndexBuffer = CreateIndexBuffer(Format, Length);

	UpdateIndexBuffer(pIndexBuffer, pData);

	return pIndexBuffer;
}


/*
	Update index buffer
*/
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


/*
	Create vertex buffer
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVertexBuffer(DWORD FVF, std::size_t Length)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return nullptr; }

	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;

	if (FAILED(pDevice->CreateVertexBuffer(static_cast<UINT>(Length), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT, &pVertexBuffer, NULL))) { Wnd->GetErrorMessage(); }

	return pVertexBuffer;
}


/*
	Create vertex buffer
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVertexBuffer(DWORD FVF, void* pData, std::size_t Length)
{
	IDirect3DVertexBuffer9* pVertexBuffer = CreateVertexBuffer(FVF, Length);

	UpdateVertexBuffer(pVertexBuffer, pData);

	return pVertexBuffer;
}


/*
	Update vertex buffer
*/
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


/*
	Create Point Vertex Buffer (Gouraud-shaded)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vecpg> Data)
{
	if (Data.empty())
	{
		std::cout << "CreatePoint: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTG, Data.size() * sizeof(vecpg));

	vecpg* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vecpg));
	}
	catch (...) { std::cout << "CreatePoint: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Point Vertex Buffer (Gouraud-shaded)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vec3> Vector, DWORD Color, float Size, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if (Vector.empty())
	{
		std::cout << "CreatePoint: Vector is empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, TransparencyRate);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTG, Vector.size() * sizeof(vecpg));

	vecpg* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].color = Color;
		pVertices[i].size = Size;
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Point Vertex Buffer (Gouraud-shaded)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vec3> Vector, std::vector<DWORD> Color, float Size, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if (Vector.empty() || Color.empty())
	{
		std::cout << "CreatePoint: Vector and/or Color is empty" << std::endl;
		return nullptr;
	}

	if (Vector.size() != Color.size())
	{
		std::cout << "CreatePoint: Vector and Color sizes do not match" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTG, Vector.size() * sizeof(vecpg));

	vecpg* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];

		pVertices[i].color = GetTransparency(Color[i], TransparencyRate);

		pVertices[i].size = Size;
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Point Vertex Buffer (Gouraud-shaded)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vec3> Vector, std::vector<DWORD> Color, std::vector<float> Size, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if (Vector.empty() || Color.empty() || Size.empty())
	{
		std::cout << "CreatePoint: Vector, Color, and/or Size is empty" << std::endl;
		return nullptr;
	}

	if ((Vector.size() != Color.size()) || (Vector.size() != Size.size()))
	{
		std::cout << "CreatePoint: Vector, Color, and Size sizes do not match" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTG, Vector.size() * sizeof(vecpg));

	vecpg* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].color = GetTransparency(Color[i], TransparencyRate);
		pVertices[i].size = Size[i];
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Point Vertex Buffer (Gouraud-shaded w/ Texture)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreatePoint(std::vector<vecpgt> Data)
{
	if (Data.empty())
	{
		std::cout << "CreatePoint: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_POINTGT, Data.size() * sizeof(vecpgt));

	vecpgt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vecpgt));
	}
	catch (...) { std::cout << "CreatePoint: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Texture Vertex Buffer
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3t(std::vector<vec3t> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3t: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_TEX3D, Data.size() * sizeof(vec3t));

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


/*
	Create Texture Vertex Buffer
*/
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

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_TEX3D, Vector.size() * sizeof(vec3t));

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


/*
	Create Texture Vertex Buffer (W)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec4t(std::vector<vec4t> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec4t: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_TEX4D, Data.size() * sizeof(vec4t));

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


/*
	Create Texture Vertex Buffer (W)
*/
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

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_TEX4D, Vector.size() * sizeof(vec4t));

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


/*
	Create Vertex Buffer (w/ Normal)
*/
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


/*
	Create Vertex Buffer (w/ Normal)
*/
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


/*
	Create Vertex Buffer (w/ UV)
*/
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


/*
	Create Vertex Buffer (w/ UV)
*/
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


/*
	Create Vertex Buffer (Gouraud-shaded)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3g(std::vector<vec3g> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3g: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTG, Data.size() * sizeof(vec3g));

	vec3g* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3g));
	}
	catch (...) { std::cout << "CreateVec3g: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Vertex Buffer (Gouraud-shaded)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3g(std::vector<vec3> Vector, DWORD Color, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if (Vector.empty())
	{
		std::cout << "CreateVec3g: Vector is empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, TransparencyRate);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTG, Vector.size() * sizeof(vec3g));

	vec3g* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	for (std::size_t i = 0; i < Vector.size(); i++)
	{
		pVertices[i].vec = Vector[i];
		pVertices[i].color = Color;
	}

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Vertex Buffer (Gouraud-shaded w/ Normal)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3gn(std::vector<vec3gn> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3gn: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTGN, Data.size() * sizeof(vec3gn));

	vec3gn* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3gn));
	}
	catch (...) { std::cout << "CreateVec3gn: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Vertex Buffer (Gouraud-shaded w/ Normal)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3gn(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if (Vector.size() != Normal.size())
	{
		std::cout << "CreateVec3gn: Vector and Normal sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || Normal.empty())
	{
		std::cout << "CreateVec3gn: Vector and/or Normal are empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, TransparencyRate);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTGN, Vector.size() * sizeof(vec3gn));

	vec3gn* pVertices = nullptr;

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


/*
	Create Vertex Buffer (Gouraud-shaded w/ UV)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3gt(std::vector<vec3gt> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3gt: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTGT, Data.size() * sizeof(vec3gt));

	vec3gt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3gt));
	}
	catch (...) { std::cout << "CreateVec3gt: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Vertex Buffer (Gouraud-shaded w/ UV)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3gt(std::vector<vec3> Vector, DWORD Color, std::vector<vec2> UV, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if (Vector.size() != UV.size())
	{
		std::cout << "CreateVec3gt: Vector and UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || UV.empty())
	{
		std::cout << "CreateVec3gt: Vector and/or UV are empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, TransparencyRate);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTGT, Vector.size() * sizeof(vec3gt));

	vec3gt* pVertices = nullptr;

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


/*
	Create Vertex Buffer (Gouraud-shaded w/ Normal and UV)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3gnt(std::vector<vec3gnt> Data)
{
	if (Data.empty())
	{
		std::cout << "CreateVec3gnt: Data is empty" << std::endl;
		return nullptr;
	}

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTGNT, Data.size() * sizeof(vec3gnt));

	vec3gnt* pVertices = nullptr;

	if (FAILED(Buffer->Lock(0, 0, (void**)&pVertices, 0))) { Wnd->GetErrorMessage(); }

	try
	{
		std::memcpy(pVertices, Data.data(), Data.size() * sizeof(vec3gnt));
	}
	catch (...) { std::cout << "CreateVec3gnt: Memory copy failed" << std::endl; }

	if (FAILED(Buffer->Unlock())) { Wnd->GetErrorMessage(); }

	return Buffer;
}


/*
	Create Vertex Buffer (Gouraud-shaded w/ Normal and UV)
*/
IDirect3DVertexBuffer9* Standard_DirectX_9::CreateVec3gnt(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, std::vector<vec2> UV, D3DTRANSPARENCY_RATE TransparencyRate)
{
	if ((Vector.size() != Normal.size()) || (Vector.size() != UV.size()) || (Normal.size() != UV.size()))
	{
		std::cout << "CreateVec3gnt: Vector, Normal, and/or UV sizes do not match" << std::endl;
		return nullptr;
	}

	if (Vector.empty() || Normal.empty() || UV.empty())
	{
		std::cout << "CreateVec3gnt: Vector, Normal, and/or UV are empty" << std::endl;
		return nullptr;
	}

	Color = GetTransparency(Color, TransparencyRate);

	IDirect3DVertexBuffer9* Buffer = CreateVertexBuffer(D3DFVF_VERTGNT, Vector.size() * sizeof(vec3gnt));

	vec3gnt* pVertices = nullptr;

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


/*
	Create pixel shader
*/
IDirect3DPixelShader9* Standard_DirectX_9::CreatePixelShader(const char* Code, const char* FunctionName, const char* Profile)
{
	//if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return nullptr; }

	ID3DXBuffer* pBuffer = nullptr;

	IDirect3DPixelShader9* pShader = nullptr;

	if (FAILED(D3DXCompileShader(Code, static_cast<UINT>(strlen(Code)), NULL, NULL, FunctionName, Profile, 0, &pBuffer, NULL, NULL))) { Wnd->GetErrorMessage(); }

	if (FAILED(pDevice->CreatePixelShader((DWORD*)pBuffer->GetBufferPointer(), &pShader))) { Wnd->GetErrorMessage(); }

	pBuffer->Release();

	return pShader;
}


/*
	Set vertex shader + matrix
*/
void Standard_DirectX_9::SetVertexShader(DWORD FVF)
{
	D3DXMATRIX World, View, Projection, Matrix;

	ID3DXConstantTable* Const = nullptr;
	IDirect3DVertexDeclaration9* Decl = nullptr;
	IDirect3DVertexShader9* Shader = nullptr;

	switch (FVF)
	{
	case D3DFVF_POINTG:
		Const = ShaderVecpg.Const;
		Decl = ShaderVecpg.Decl;
		Shader = ShaderVecpg.Shader;
		break;
	case D3DFVF_POINTGT:
		Const = ShaderVecpgt.Const;
		Decl = ShaderVecpgt.Decl;
		Shader = ShaderVecpgt.Shader;
		break;
	case D3DFVF_TEX3D:
		Const = ShaderVec3t.Const;
		Decl = ShaderVec3t.Decl;
		Shader = ShaderVec3t.Shader;
		break;
	case D3DFVF_TEX4D:
		Const = ShaderVec4t.Const;
		Decl = ShaderVec4t.Decl;
		Shader = ShaderVec4t.Shader;
		break;
	case D3DFVF_VERTN:
		Const = ShaderVec3n.Const;
		Decl = ShaderVec3n.Decl;
		Shader = ShaderVec3n.Shader;
		break;
	case D3DFVF_VERTNT:
		Const = ShaderVec3nt.Const;
		Decl = ShaderVec3nt.Decl;
		Shader = ShaderVec3nt.Shader;
		break;
	case D3DFVF_VERTG:
		Const = ShaderVec3g.Const;
		Decl = ShaderVec3g.Decl;
		Shader = ShaderVec3g.Shader;
		break;
	case D3DFVF_VERTGN:
		Const = ShaderVec3gn.Const;
		Decl = ShaderVec3gn.Decl;
		Shader = ShaderVec3gn.Shader;
		break;
	case D3DFVF_VERTGT:
		Const = ShaderVec3gt.Const;
		Decl = ShaderVec3gt.Decl;
		Shader = ShaderVec3gt.Shader;
		break;
	case D3DFVF_VERTGNT:
		Const = ShaderVec3gnt.Const;
		Decl = ShaderVec3gnt.Decl;
		Shader = ShaderVec3gnt.Shader;
		break;
	default:
		pDevice->SetVertexShader(NULL);
		std::cout << "SetVertexShader: Unsupported FVF (0x" << std::hex << FVF << ")" << std::dec << std::endl;
		return;
	}

	pDevice->SetVertexDeclaration(Decl);

	pDevice->GetTransform(D3DTS_WORLD, &World);
	pDevice->GetTransform(D3DTS_VIEW, &View);
	pDevice->GetTransform(D3DTS_PROJECTION, &Projection);

	Matrix = World * View * Projection;

	D3DXHANDLE pWorldViewProjectionMatrix = Const->GetConstantByName(NULL, "WorldViewProjectionMatrix");
	D3DXHANDLE pWorldMatrix = Const->GetConstantByName(NULL, "WorldMatrix");

	HRESULT hRes0 = Const->SetMatrix(pDevice, pWorldViewProjectionMatrix, &Matrix);
	HRESULT hRes1 = Const->SetMatrix(pDevice, pWorldMatrix, &World);

	if (FAILED(hRes0)) std::cout << "WorldViewProjectionMatrix failed" << std::endl;
	if (FAILED(hRes1)) std::cout << "WorldMatrix failed" << std::endl;

	pDevice->SetVertexShader(Shader);
}


/*
	Draw
*/
void Standard_DirectX_9::Draw(D3DDRAWPACKET Packet)
{
	float Width = 0.0f;
	float Height = 0.0f;

	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return; }

	if (!Packet.Vertices) { return; }

	if (FAILED(Packet.Vertices->GetDesc(&VertexBufferDesc))) { return; }

	if (Packet.Indices)
	{
		if (FAILED(Packet.Indices->GetDesc(&IndexBufferDesc))) { return; }
	}

	if (Packet.FillMode == D3DFILL_WIREFRAME)
	{
		Lighting(FALSE);
		Packet.Texture = nullptr;
	}
	else
	{
		Lighting(VertexBufferDesc.FVF & D3DFVF_NORMAL ? TRUE : FALSE);
	}

	if (Packet.Texture)
	{
		if (!FAILED(Packet.Texture->GetLevelDesc(0, &TextureDesc)))
		{
			Width = static_cast<float>(TextureDesc.Width);
			Height = static_cast<float>(TextureDesc.Height);
		}
	}

	ZBuffer(Packet.bZBuffer, Packet.ZType, Packet.ZFunc);

	SetVertexShader(VertexBufferDesc.FVF);

	pDevice->SetPixelShaderConstantF(0, &Width, 1);
	pDevice->SetPixelShaderConstantF(1, &Height, 1);

	pDevice->SetPixelShader(Packet.PixelShader);

	pDevice->SetRenderState(D3DRS_FILLMODE, Packet.FillMode);
	pDevice->SetRenderState(D3DRS_SHADEMODE, (VertexBufferDesc.FVF & D3DFVF_DIFFUSE) ? D3DSHADE_GOURAUD : D3DSHADE_FLAT);
	pDevice->SetRenderState(D3DRS_COLORVERTEX, (VertexBufferDesc.FVF & D3DFVF_DIFFUSE) ? TRUE : FALSE);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, (VertexBufferDesc.FVF & D3DFVF_NORMAL) ? TRUE : FALSE);

	pDevice->SetStreamSource(0, Packet.Vertices, 0, Packet.Stride);
	pDevice->SetIndices(Packet.Indices);
	pDevice->SetTexture(0, Packet.Texture);
	pDevice->SetFVF(VertexBufferDesc.FVF);

	if (Packet.Indices)
	{
		pDevice->DrawIndexedPrimitive(Packet.PrimitiveType, 0, 0, VertexBufferDesc.Size, 0, IndexBufferDesc.Size);
	}
	else
	{
		switch (Packet.FillMode)
		{
		case D3DFILL_POINT:
			pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, VertexBufferDesc.Size / Packet.Stride);
			break;
		case D3DFILL_WIREFRAME:
			switch (Packet.PrimitiveType)
			{
			case D3DPT_LINELIST:
				pDevice->DrawPrimitive(Packet.PrimitiveType, 0, VertexBufferDesc.Size / Packet.Stride / 2);
				break;
			case D3DPT_LINESTRIP:
				pDevice->DrawPrimitive(Packet.PrimitiveType, 0, VertexBufferDesc.Size / Packet.Stride - 1);
				break;
			}
			break;
		case D3DFILL_SOLID:
			switch (Packet.PrimitiveType)
			{
			case D3DPT_TRIANGLELIST:
				pDevice->DrawPrimitive(Packet.PrimitiveType, 0, VertexBufferDesc.Size / Packet.Stride / 3);
				break;
			case D3DPT_TRIANGLESTRIP:
			case D3DPT_TRIANGLEFAN:
				pDevice->DrawPrimitive(Packet.PrimitiveType, 0, VertexBufferDesc.Size / Packet.Stride - 2);
				break;
			}
			break;
		}
	}
}


/*
	Draw Texture Vertex Buffer (W)
*/
void Standard_DirectX_9::DrawVec4t(IDirect3DVertexBuffer9* Buffer, IDirect3DTexture9* Texture, IDirect3DPixelShader9* PixelShader)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return; }

	DWORD CullMode = 0;
	DWORD Clipping = 0;
	DWORD ShadeMode = 0;

	pDevice->GetRenderState(D3DRS_CULLMODE, &CullMode);
	pDevice->GetRenderState(D3DRS_CLIPPING, &Clipping);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_CLIPPING, FALSE);

	Draw({ Buffer, nullptr, Texture, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec4t), true, D3DZB_USEW, D3DCMP_EQUAL, D3DFILL_SOLID, D3DPT_TRIANGLESTRIP });

	pDevice->SetRenderState(D3DRS_CULLMODE, CullMode);
	pDevice->SetRenderState(D3DRS_CLIPPING, Clipping);
}


/*
	Set world matrix
*/
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


/*
	Enable/Disable Anti-Aliasing
*/
void Standard_DirectX_9::AntiAliasing(bool OnOff)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return; }

	b_AntiAliasing = OnOff;

	if (b_AntiAliasing)
	{
		DWORD pQualityLevels = NULL;
		if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisplayMode.Format, FALSE, D3DMULTISAMPLE_NONMASKABLE, &pQualityLevels)))
		{
			b_AntiAliasing = true;
			PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
			PresentParameters.MultiSampleQuality = pQualityLevels - 1;
		}
	}
	else
	{
		PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
		PresentParameters.MultiSampleQuality = NULL;
	}

	pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, b_AntiAliasing);
}


/*
	Enable/Disable Texture Filtering
*/
void Standard_DirectX_9::TextureFiltering(D3DTEXTUREFILTERTYPE Type)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return; }

	m_TextureFilter = Type;

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, m_TextureFilter);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, m_TextureFilter);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, m_TextureFilter);
}


/*
	Enable/Disable Lighting
*/
void Standard_DirectX_9::Lighting(bool OnOff)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return; }

	pDevice->SetRenderState(D3DRS_LIGHTING, OnOff);

	if (OnOff)
	{
		pDevice->SetRenderState(D3DRS_AMBIENT, AmbientColor);
		pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

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
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLEND_ZERO);

		//pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		//pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	}
}


/*
	Enable/Disable Z-Buffer
*/
void Standard_DirectX_9::ZBuffer(bool OnOff, D3DZBUFFERTYPE Type, D3DCMPFUNC Func)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return; }

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, OnOff);

	if (OnOff)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, Type);
	}
	else
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}

	pDevice->SetRenderState(D3DRS_ZFUNC, Func);
}


/*
	Create Axis grid
*/
void Standard_DirectX_9::CreateAxisGrid(void)
{
	if (AxisGrid) { return; }

	AxisGrid = CreateVertexBuffer(D3DFVF_VERTG, 68 * sizeof(vec3g));

	if (!AxisGrid) { return; }

	vec3g* pVertices = nullptr;

	if (FAILED(AxisGrid->Lock(0, 68 * sizeof(vec3g), reinterpret_cast<void**>(&pVertices), 0))) { Wnd->GetErrorMessage(); }

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

	if (FAILED(AxisGrid->Unlock())) { Wnd->GetErrorMessage(); }

	XyzAxis = CreateVertexBuffer(D3DFVF_VERTG, 6 * sizeof(vec3g));

	if (!XyzAxis) { return; }

	if (FAILED(XyzAxis->Lock(0, 6 * sizeof(vec3g), reinterpret_cast<void**>(&pVertices), 0))) { Wnd->GetErrorMessage(); }

	pVertices[0].vec.Set(0.0f, 0.01f, 0.0f);
	pVertices[1].vec.Set(-8.0f, 0.0f, 0.0f);
	pVertices[2].vec.Set(0.0f, 0.01f, 0.0f);
	pVertices[3].vec.Set(0.0f, 8.0f, 0.0f);
	pVertices[4].vec.Set(0.0f, 0.01f, 0.0f);
	pVertices[5].vec.Set(0.0f, 0.0f, -8.0f);

	pVertices[0].color = D3DCOLOR_XRGB(255, 0, 0);
	pVertices[1].color = D3DCOLOR_XRGB(255, 0, 0);
	pVertices[2].color = D3DCOLOR_XRGB(0, 255, 0);
	pVertices[3].color = D3DCOLOR_XRGB(0, 255, 0);
	pVertices[4].color = D3DCOLOR_XRGB(0, 0, 255);
	pVertices[5].color = D3DCOLOR_XRGB(0, 0, 255);

	if (FAILED(XyzAxis->Unlock())) { Wnd->GetErrorMessage(); }
}


/*
	Save screenshot
*/
bool Standard_DirectX_9::SaveScreenshot(D3DXIMAGE_FILEFORMAT Format, std::filesystem::path Output)
{
	if (e_DeviceState != D3DDEVICE_STATE::NORMAL) { return false; }

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