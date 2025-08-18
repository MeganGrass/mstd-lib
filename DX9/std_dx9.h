/*
*
*	Megan Grass
*	April 12, 2024
*
*/


#pragma once

#include "../Windows/std_window.h"

#include "../Geometry/std_matrix.h"

#include "../std_image.h"

#include "../std_thread_pool.h"

#include <sony_texture.h>

#include <d3d9.h>

#include <d3dx9tex.h>


/*
	Point (w/ Color)
	 - vecpc
*/
#define D3DFVF_POINTC (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE)

/*
	Point (w/ Color and Texture)
	 - vecpt
*/
#define D3DFVF_POINTCT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE | D3DFVF_TEX1)

/*
	Texture
	 - vec3t
*/
#define D3DFVF_VERT3T (D3DFVF_XYZ | D3DFVF_TEX1)

/*
	Texture W
	 - vec4t
*/
#define D3DFVF_VERT4T (D3DFVF_XYZW | D3DFVF_TEX1)

/*
	Texture W (w/ Color)
	 - vec4ct
*/
#define D3DFVF_VERT4CT (D3DFVF_XYZW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*
	Vertex (w/ Normal)
	 - vec3n
*/
#define D3DFVF_VERTN (D3DFVF_XYZ | D3DFVF_NORMAL)

/*
	Vertex (w/ Normal and UV)
	 - vec3nt
*/
#define D3DFVF_VERTNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

/*
	Vertex (w/ Color)
	 - vec3c
*/
#define D3DFVF_VERTC (D3DFVF_XYZ | D3DFVF_DIFFUSE)

/*
	Vertex (w/ Normal and Color)
	 - vec3cn
*/
#define D3DFVF_VERTCN (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)

/*
	Vertex (w/ Color and UV)
	 - vec3ct
*/
#define D3DFVF_VERTCT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*
	Vertex (w/ Normal, Color and UV)
	 - vec3cnt
*/
#define D3DFVF_VERTCNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*
	16-bit depth buffer
*/
const D3DFORMAT D3DFMT_DF16 = ((D3DFORMAT)(MAKEFOURCC('D', 'F', '1', '6')));

/*
	24-bit depth buffer
*/
const D3DFORMAT D3DFMT_DF24 = ((D3DFORMAT)(MAKEFOURCC('D', 'F', '2', '4')));

/*
	24-bit depth buffer/8-bit stencil buffer
*/
const D3DFORMAT D3DFMT_INTZ = ((D3DFORMAT)(MAKEFOURCC('I', 'N', 'T', 'Z')));

/*
	Dummy Render Target
*/
const D3DFORMAT D3DFMT_NULL = ((D3DFORMAT)(MAKEFOURCC('N', 'U', 'L', 'L')));

/*
	Direct-X 9 smart pointer deleter
*/
template <typename T>
struct IDirect3DDelete9
{
	void operator()(T* ptr) const
	{
		if (ptr)
		{
			ptr->Release();
			ptr = nullptr;
		}
	}
};

/*
	Direct-X 9 Device State
*/
enum class D3DDEVICE_STATE : int32_t
{
	UNKNOWN = (0 << 0),			// The device state is unknown
	NORMAL = (1 << 0),			// The device is normally operational
	LOST = (1 << 1),			// The device has been lost but cannot be reset at this time
	NOTRESET = (1 << 2),		// The device has been lost and can be reset
	REMOVED = (1 << 3),			// The hardware adapter has been removed
	DRIVER_ERROR = (1 << 4),	// Internal driver error
	OUT_OF_MEMORY = (1 << 5),	// Direct3D does not have enough display memory to perform the operation
	MODE_CHANGED = (1 << 6),	// The desktop display mode has been changed
	OCCLUDED = (1 << 7),		// The presentation area is occluded
};

/*
	Direct-X 9 Vertex Shader Packet
*/
struct D3DSHADERPACKET final
{
	std::unique_ptr<ID3DXConstantTable, IDirect3DDelete9<ID3DXConstantTable>> Const;
	std::unique_ptr<IDirect3DVertexDeclaration9, IDirect3DDelete9<IDirect3DVertexDeclaration9>> Decl;
	std::unique_ptr<IDirect3DVertexShader9, IDirect3DDelete9<IDirect3DVertexShader9>> Shader;
};

/*
	Direct-X 9 Draw Packet
*/
struct D3DDRAWPACKET final
{
	IDirect3DVertexBuffer9* Vertices;
	IDirect3DIndexBuffer9* Indices;
	IDirect3DTexture9* Texture;
	IDirect3DPixelShader9* PixelShader;
	struct Z_BUFFER
	{
		BOOL Active;
		D3DZBUFFERTYPE Type;
		D3DCMPFUNC Func;
	} ZBuffer{ FALSE, D3DZB_FORCE_DWORD, D3DCMP_FORCE_DWORD };
	struct PRIMITIVE
	{
		UINT Stride;
		D3DFILLMODE Fill;
		D3DPRIMITIVETYPE Type;
	} Primitive{ NULL, D3DFILL_FORCE_DWORD, D3DPT_FORCE_DWORD };
	struct TEXTURE
	{
		float Width;
		float Height;
	} TextureAttr{ 0.0f, 0.0f };
	struct MATRIX
	{
		D3DXMATRIX* World;
		D3DXMATRIX* View;
		D3DXMATRIX* Projection;
	} Matrix{ nullptr, nullptr, nullptr };
};

/*
	Standard Direct-X 9
*/
class Standard_DirectX_9 final :
	private Standard_Thread_Pool {
private:

	std::shared_ptr<Standard_Window> Wnd;

	std::unique_ptr<IDirect3D9Ex, IDirect3DDelete9<IDirect3D9Ex>> pD3D;

	std::unique_ptr<IDirect3DDevice9Ex, IDirect3DDelete9<IDirect3DDevice9Ex>> pDevice;

	std::unique_ptr<IDirect3DSwapChain9Ex, IDirect3DDelete9<IDirect3DSwapChain9Ex>> pSwapChain;

	std::unique_ptr<D3DCAPS9> m_DeviceCaps;

	std::unique_ptr<D3DADAPTER_IDENTIFIER9> m_AdapterIdentifier;

	std::unique_ptr<D3DDISPLAYMODE> m_DisplayMode;

	std::unique_ptr<D3DPRESENT_PARAMETERS> m_PresentParameters;

	D3DDEVICE_STATE e_DeviceState;

	D3DINDEXBUFFER_DESC IndexBufferDesc;

	D3DVERTEXBUFFER_DESC VertexBufferDesc;

	D3DSURFACE_DESC TextureDesc;

	std::unique_ptr<IDirect3DVertexBuffer9, IDirect3DDelete9<IDirect3DVertexBuffer9>> Grid;

	std::unique_ptr<IDirect3DVertexBuffer9, IDirect3DDelete9<IDirect3DVertexBuffer9>> Axis;

	bool b_Ready;

	bool b_Abort;

	bool b_Active;

	bool b_Complete;

	bool b_NativeResolution;

	float m_NativeWidth;

	float m_NativeHeight;

	bool b_AntiAliasing;

	float m_DepthScaleZ, m_DepthMaxZ;

	D3DTEXTUREFILTERTYPE m_TextureFilter;

	DWORD AmbientColor;

	void Update(void);

	void InitShaders(void);

	D3DSHADERPACKET ShaderVecPoint;

	D3DSHADERPACKET ShaderVecPointc;

	D3DSHADERPACKET ShaderVecPointct;

	D3DSHADERPACKET ShaderVec3t;

	D3DSHADERPACKET ShaderVec4t;

	D3DSHADERPACKET ShaderVec4ct;

	D3DSHADERPACKET ShaderVec3n;

	D3DSHADERPACKET ShaderVec3nt;

	D3DSHADERPACKET ShaderVec3c;

	D3DSHADERPACKET ShaderVec3cn;

	D3DSHADERPACKET ShaderVec3ct;

	D3DSHADERPACKET ShaderVec3cnt;

public:

	// View Grid
	bool b_ViewGrid;

	// View Axis
	bool b_ViewAxis;

	/*
		Was the device reset?
		 - always true when the device is reset
	*/
	bool b_DeviceWasReset = false;

	/*
		Generic Pixel Shader
		 - uv coordinates used when texture is bound
		 - diffuse color used when texture is not bound and diffuse exists
		 - solid white used when texture is not bound and diffuse does not exist
		 - this shader is used for generic draw functions when no other shader is specified
	*/
	std::unique_ptr<IDirect3DPixelShader9, IDirect3DDelete9<IDirect3DPixelShader9>> PassthroughPixelShader;

	// Sony PlayStation (1994) Dithering Pixel Shader
	std::unique_ptr<IDirect3DPixelShader9, IDirect3DDelete9<IDirect3DPixelShader9>> PS1DitherPixelShader;

	explicit Standard_DirectX_9(void) :
		Wnd(nullptr),
		pD3D(nullptr),
		pDevice(nullptr),
		pSwapChain(nullptr),
		m_DeviceCaps(nullptr),
		m_AdapterIdentifier(nullptr),
		m_DisplayMode(nullptr),
		m_PresentParameters(nullptr),
		e_DeviceState(D3DDEVICE_STATE::UNKNOWN),
		IndexBufferDesc(),
		VertexBufferDesc(),
		TextureDesc(),
		Grid(nullptr),
		Axis(nullptr),
		m_DepthScaleZ(0.0f),
		m_DepthMaxZ(0.0f),
		b_Ready(false),
		b_Abort(false),
		b_Active(false),
		b_Complete(false),
		b_NativeResolution(false),
		m_NativeWidth(0.0f),
		m_NativeHeight(0.0f),
		b_AntiAliasing(true),
		b_ViewGrid(true),
		b_ViewAxis(true),
		m_TextureFilter(D3DTEXF_POINT),
		AmbientColor(0xFF808080),
		PassthroughPixelShader(nullptr),
		PS1DitherPixelShader(nullptr),
		ShaderVecPoint{},
		ShaderVecPointc{},
		ShaderVecPointct{},
		ShaderVec3t{},
		ShaderVec4t{},
		ShaderVec4ct{},
		ShaderVec3n{},
		ShaderVec3nt{},
		ShaderVec3c{},
		ShaderVec3cn{},
		ShaderVec3ct{},
		ShaderVec3cnt{}
	{
		InitPool(1);
		Enqueue([this]() { Update(); });
	}
	virtual ~Standard_DirectX_9(void) = default;

	// Shutdown
	void Shutdown(void);

	// Is renderer in normal state?
	[[nodiscard]] const bool NormalState(void) const { return (std::to_underlying(e_DeviceState) & std::to_underlying(D3DDEVICE_STATE::NORMAL)) != 0; }

	/*
		Initialize
		 - if NativeResolution is true, Width and Height are used as the internal rendering resolution
		 - if NativeResolution is false, the window's client area size is used as the internal rendering resolution
		 - the drawing area will always be sized to the window's client area
	*/
	const bool Initialize(std::shared_ptr<Standard_Window> StdWnd, UINT Width, UINT Height, bool NativeResolution = false);

	// Check device state
	void Test(void);

	/*
		Reset device state
		 - device state may change
	*/
	void Reset(void);

	// Get Window
	[[nodiscard]] const std::shared_ptr<Standard_Window>& Window(void) const { return Wnd; }

	// Get D3D
	[[nodiscard]] IDirect3D9Ex* D3D(void) const { return pD3D.get(); }

	// Get Device
	[[nodiscard]] IDirect3DDevice9Ex* Device(void) const { return pDevice.get(); }

	// Get device state
	[[nodiscard]] const D3DDEVICE_STATE& DeviceState(void) const { return e_DeviceState; }

	// Set device state
	[[nodiscard]] void SetDeviceState(D3DDEVICE_STATE State) { e_DeviceState = State; }

	// Get Swap Chain (additional)
	[[nodiscard]] IDirect3DSwapChain9Ex* SwapChain(void) const { return pSwapChain.get(); }

	// Get Device Caps
	[[nodiscard]] D3DCAPS9* GetUpdatedDeviceCaps(void);

	// Get Device Caps
	[[nodiscard]] D3DCAPS9* GetDeviceCaps(void) const { return m_DeviceCaps.get(); }

	// Get Adapter Identifier
	[[nodiscard]] D3DADAPTER_IDENTIFIER9* GetAdapterId(void);

	// Get Display Mode
	[[nodiscard]] D3DDISPLAYMODE* GetDisplayMode(void);

	// Get Present Parameters
	[[nodiscard]] D3DPRESENT_PARAMETERS* GetPresentParameters(void) { return m_PresentParameters.get(); }

	// Is render target format supported?
	[[nodiscard]] const bool RenderTargetSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, Format));
	}

	// Is surface format supported?
	[[nodiscard]] const bool SurfaceFormatSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, NULL, D3DRTYPE_SURFACE, Format));
	}

	// Is depth format supported?
	[[nodiscard]] const bool DepthFormatSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, Format));
	}

	// Is texture format supported?
	[[nodiscard]] const bool TextureFormatSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, NULL, D3DRTYPE_TEXTURE, Format));
	}

	// Is alpha blending supported?
	[[nodiscard]] const bool AlphaBlendingSupport(D3DRESOURCETYPE Type, D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, Type, Format));
	}

	// Is mipmap autogeneration supported?
	[[nodiscard]] const bool MipmapAutogenerationSupport(D3DRESOURCETYPE Type, D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_AUTOGENMIPMAP, Type, Format));
	}

	// Create Canvas Render Surface (32bpp)
	[[nodiscard]] IDirect3DSurface9* CreateRenderSurface(std::uint16_t Width, std::uint16_t Height, D3DFORMAT Format = D3DFMT_A8R8G8B8);

	// Create Canvas Texture (32bpp)
	[[nodiscard]] IDirect3DTexture9* CreateTexture(std::uint16_t Width, std::uint16_t Height, DWORD Usage = D3DUSAGE_DYNAMIC);

	/*
		Create Texture (32bpp)
		 - 4bpp/8bpp/16bpp/24bpp/32bpp supported
		 - Width and Height are automatically adjusted to power of two
		 - if "b_Alpha" is true and pixel color equals "AlphaColor", alpha channel will be set to "AlphaChannel"
	*/
	[[nodiscard]] IDirect3DTexture9* CreateTexture(std::unique_ptr<Standard_Image>& Image, bool b_Alpha = false, DWORD AlphaColor = 0xFF00FF, std::uint8_t AlphaChannel = 0x00, bool b_VerticalFlip = false);

	/*
		Create Texture (32bpp) from Sony PlayStation Texture (*.TIM)
		 - 4bpp/8bpp/16bpp/24bpp supported
		 - Width and Height are automatically adjusted to power of two
		 - if TransparencyFlags & Superblack, Full Transparency for solid black pixels (5:5:5:1 and 8:8:8)
		 - if TransparencyFlags & Superimposed, Semi/Full Transparency for palette index 0 (if available)
		 - if TransparencyFlags & External, Semi/Full Transparency for external color (TransparencyColor)
		 - if TransparencyFlags & STP, STP flag determines if Semi/Full Transparency is used
	*/
	[[nodiscard]] IDirect3DTexture9* CreateTexture(
		std::unique_ptr<Sony_PlayStation_Texture>& TIM,
		uint16_t iPalette = 0,
		Sony_Texture_Transparency TransparencyFlags = Sony_Texture_Transparency::None,
		DWORD TransparencyColor = 0xFF00FF,
		bool b_VerticalFlip = false);

	// Blit Texture (32bpp)
	[[nodiscard]] IDirect3DTexture9* BlitTexture(IDirect3DTexture9* Source, IDirect3DTexture9* Dest, size_t Width, size_t Height, UINT X, UINT Y, bool b_VertFlip = false);

	// Save Texture (32bpp)
	bool SaveTexture(IDirect3DTexture9* Texture, D3DXIMAGE_FILEFORMAT Format, bool b_VertFlip, const std::filesystem::path& Filename);

	// Create index buffer
	[[nodiscard]] IDirect3DIndexBuffer9* CreateIndexBuffer(D3DFORMAT Format, std::size_t Length);

	// Create index buffer
	[[nodiscard]] IDirect3DIndexBuffer9* CreateIndexBuffer(D3DFORMAT Format, void* pData, std::size_t Length);

	// Update index buffer
	void UpdateIndexBuffer(IDirect3DIndexBuffer9* Buffer, void* pData);

	// Create vertex buffer
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVertexBuffer(DWORD FVF, std::size_t Length);

	// Create vertex buffer
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVertexBuffer(DWORD FVF, void* pData, std::size_t Length);

	// Update vertex buffer
	void UpdateVertexBuffer(IDirect3DVertexBuffer9* Buffer, void* pData);

	// Create Point Vertex Buffer (w/ Color and Texture)
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vecpc> Data);

	// Create Point Vertex Buffer (w/ Color and Texture)
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vecpct> Data);

	// Create Texture Vertex Buffer
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3t(std::vector<vec3t> Data);

	// Create Texture Vertex Buffer
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3t(std::vector<vec3> Vector, std::vector<vec2> UV);

	// Create Texture Vertex Buffer (W)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec4t(std::vector<vec4t> Data);

	// Create Texture Vertex Buffer (W)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec4t(std::vector<vec4> Vector, std::vector<vec2> UV);

	// Create Texture Vertex Buffer (W) (w/ Color)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec4ct(std::vector<vec4ct> Data);

	// Create Texture Vertex Buffer (W) (w/ Color)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec4ct(std::vector<vec4> Vector, std::vector<vec2> UV, DWORD Color);

	// Create Vertex Buffer (w/ Normal)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3n(std::vector<vec3n> Data);

	// Create Vertex Buffer (w/ Normal)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3n(std::vector<vec3> Vector, std::vector<vec3> Normal);

	// Create Vertex Buffer (w/ UV)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3nt(std::vector<vec3nt> Data);

	// Create Vertex Buffer (w/ UV)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3nt(std::vector<vec3> Vector, std::vector<vec3> Normal, std::vector<vec2> UV);

	// Create Vertex Buffer (w/ Color)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3c(std::vector<vec3c> Data);

	// Create Vertex Buffer (w/ Color)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3c(std::vector<vec3> Vector, DWORD Color, DWORD Transparency = 0xFF);

	// Create Vertex Buffer (w/ Normal and Color)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3cn(std::vector<vec3cn> Data);

	// Create Vertex Buffer (w/ Normal and Color)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3cn(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, DWORD Transparency = 0xFF);

	// Create Vertex Buffer (w/ Color and UV)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3ct(std::vector<vec3ct> Data);

	// Create Vertex Buffer (w/ Color and UV)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3ct(std::vector<vec3> Vector, DWORD Color, std::vector<vec2> UV, DWORD Transparency = 0xFF);

	// Create Vertex Buffer (w/ Normal, Color and UV)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3cnt(std::vector<vec3cnt> Data);

	// Create Vertex Buffer (w/ Normal, Color and UV)
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3cnt(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, std::vector<vec2> UV, DWORD Transparency = 0xFF);

	// Create pixel shader
	[[nodiscard]] IDirect3DPixelShader9* CreatePixelShader(const char* Code, const char* FunctionName = "main", const char* Profile = "ps_3_0");

	// Create pixel shader from file
	[[nodiscard]] IDirect3DPixelShader9* CreatePixelShaderFromFile(const std::filesystem::path& Filename, const char* FunctionName = "main", const char* Profile = "ps_3_0");

	// Create vertex shader
	[[nodiscard]] D3DSHADERPACKET CreateVertexShader(void* Element, const char* Code, const char* FunctionName = "main", const char* Profile = "ps_3_0");

	// Create vertex shader from file
	[[nodiscard]] D3DSHADERPACKET CreateVertexShader(const std::filesystem::path& Filename, void* Element, const char* FunctionName = "main", const char* Profile = "ps_3_0");

	// Set homogeneous vertex shader + matrix
	void SetHomogeneousShader(DWORD FVF, D3DXMATRIX* Projection = nullptr);

	// Set vertex shader + matrix
	void SetVertexShader(DWORD FVF, D3DXMATRIX* World = nullptr, D3DXMATRIX* View = nullptr, D3DXMATRIX* Projection = nullptr);

	/*
		Draw
		 - if D3DFILL_WIREFRAME is used, lighting and texture is disabled
		 - pixel shader info:
			Pixel Shader Constant (F) [c0] is set to texture width
			Pixel Shader Constant (F) [c1] is set to texture height
	*/
	void Draw(D3DDRAWPACKET Packet);

	// Draw Point Vertex Buffer (w/ Color)
	void DrawPointC(IDirect3DVertexBuffer9* Buffer, IDirect3DPixelShader9* Shader = nullptr)
	{
		Draw({ Buffer, nullptr, nullptr, Shader,
			{ TRUE, D3DZB_TRUE, D3DCMP_LESSEQUAL },
			{ sizeof(vecpc), D3DFILL_POINT, D3DPT_POINTLIST },
			{ 0.0f, 0.0f },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Point Vertex Buffer (w/ Color and UV)
	void DrawPointCT(IDirect3DVertexBuffer9* Buffer, IDirect3DTexture9* Texture, IDirect3DPixelShader9* Shader = nullptr, float Width = 0.0f, float Height = 0.0f)
	{
		Draw({ Buffer, nullptr, Texture, Shader,
			{ TRUE, D3DZB_TRUE, D3DCMP_LESSEQUAL },
			{ sizeof(vecpct), D3DFILL_POINT, D3DPT_POINTLIST },
			{ Width, Height },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Texture Vertex Buffer
	void DrawVec3t(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* Shader = nullptr,
		float Width = 0.0f, float Height = 0.0f,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3t), FillMode, PrimitiveType },
			{ Width, Height },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Texture Vertex Buffer (W)
	void DrawVec4t(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* PixelShader = nullptr,
		float TexWidth = 0.0f, float TexHeight = 0.0f,
		D3DXMATRIX* Projection = nullptr)
	{
		Draw({ Buffer, nullptr, Texture, PixelShader,
			{ TRUE, D3DZB_TRUE, D3DCMP_LESSEQUAL },
			{ sizeof(vec4t), D3DFILL_SOLID, D3DPT_TRIANGLESTRIP },
			{ TexWidth, TexHeight },
			{ nullptr, nullptr, Projection } });
	}

	// Draw Texture Vertex Buffer (W) (w/ Color)
	void DrawVec4ct(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* PixelShader = nullptr,
		float TexWidth = 0.0f,
		float TexHeight = 0.0f,
		D3DXMATRIX* Projection = nullptr)
	{
		Draw({ Buffer, nullptr, Texture, PixelShader,
			{ TRUE, D3DZB_TRUE, D3DCMP_LESSEQUAL },
			{ sizeof(vec4ct), D3DFILL_SOLID, D3DPT_TRIANGLESTRIP },
			{ TexWidth, TexHeight },
			{ nullptr, nullptr, Projection } });
	}

	// Draw Vertex Buffer (w/ Normal)
	void DrawVec3n(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DPixelShader9* Shader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, nullptr, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3n), FillMode, PrimitiveType },
			{ 0.0f, 0.0f },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Vertex Buffer (w/ UV)
	void DrawVec3nt(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* Shader = nullptr,
		float Width = 0.0f, float Height = 0.0f,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3nt), FillMode, PrimitiveType },
			{ Width, Height },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Vertex Buffer (w/ Color)
	void DrawVec3c(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DPixelShader9* Shader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, nullptr, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3c), FillMode, PrimitiveType },
			{ 0.0f, 0.0f },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Vertex Buffer (w/ Normal and Color)
	void DrawVec3cn(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DPixelShader9* Shader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, nullptr, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3cn), FillMode, PrimitiveType },
			{ 0.0f, 0.0f },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Vertex Buffer (w/ Color and UV)
	void DrawVec3ct(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* Shader = nullptr,
		float Width = 0.0f, float Height = 0.0f,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3ct), FillMode, PrimitiveType },
			{ Width, Height },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Vertex Buffer (w/ Normal, Color and UV)
	void DrawVec3cnt(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* Shader = nullptr,
		float Width = 0.0f, float Height = 0.0f,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		BOOL b_ZBuffer = TRUE,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, Shader,
			{ b_ZBuffer, b_ZBuffer ? D3DZB_TRUE : D3DZB_FALSE, ZFunc },
			{ sizeof(vec3cnt), FillMode, PrimitiveType },
			{ Width, Height },
			{ nullptr, nullptr, nullptr } });
	}

	// Get D3DXMATRIX from Standard_Matrix
	[[nodiscard]] D3DXMATRIX* GetMatrix(Standard_Matrix Matrix) { return (D3DXMATRIX*)&Matrix; }

	// Reset world matrix
	void ResetWorld(void) { SetWorld(Standard_Matrix(vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 1.0f, 1.0f, 1.0f })); }

	// Reset world matrix
	void ResetWorld(Standard_Matrix& Matrix) { SetWorld(Matrix = Standard_Matrix(vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 1.0f, 1.0f, 1.0f })); }

	// Set world matrix
	D3DXMATRIX SetWorld(float X, float Y, float Z, float RX, float RY, float RZ, float SX = 1.0f, float SY = 1.0f, float SZ = 1.0f);

	// Set world matrix
	void SetWorld(const vec3& Translation, const vec3& Rotation, const vec3& Scale = vec3{ 1.0f, 1.0f, 1.0f })
	{
		SetWorld(Standard_Matrix(vec3{ Translation.x, Translation.y, Translation.z }, vec3{ Rotation.x, Rotation.y, Rotation.z }, vec3{ Scale.x, Scale.y, Scale.z }));
	}

	// Set world matrix
	void SetWorld(Standard_Matrix World) { pDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&World); }

	// Set world matrix
	void SetWorld(std::shared_ptr<Standard_Matrix> World) { pDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)World.get()); }

	// Set view matrix
	void SetView(Standard_Matrix View) { pDevice->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&View); }

	// Set view matrix
	void SetView(std::shared_ptr<Standard_Matrix> View) { pDevice->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)View.get()); }

	// Set projection matrix
	void SetProjection(Standard_Matrix Projection) { pDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&Projection); }

	// Set projection matrix
	void SetProjection(std::shared_ptr<Standard_Matrix> Projection) { pDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)Projection.get()); }

	// Is the renderer in a normal state?
	[[nodiscard]] const bool& Ready(void) const { return b_Ready; }

	// Was the device created with native resolution?
	[[nodiscard]] const bool& NativeResolution(void) const { return b_NativeResolution; }

	/*
		Get native width
		 - if return is 0.0f, the window's client area is used for the internal rendering resolution
	*/
	[[nodiscard]] const float& NativeWidth(void) const { return m_NativeWidth; }

	/*
		Get native height
		 - if return is 0.0f, the window's client area is used for the internal rendering resolution
	*/
	[[nodiscard]] const float& NativeHeight(void) const { return m_NativeHeight; }

	// Set Homogeneous Depth Scale
	void SetDepthScale(float ScaleZ, float MaxZ)
	{
		m_DepthScaleZ = ScaleZ;
		m_DepthMaxZ = MaxZ;

		float DepthBias = m_DepthScaleZ / 65536.0f;
		float SlopeScaleBias = m_DepthMaxZ / 65536.0f;

		pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&DepthBias);
		pDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, *(DWORD*)&SlopeScaleBias);
	}

	// Ambient Light Color
	[[nodiscard]] DWORD& Ambient(void) { return AmbientColor; }

	// Set color transparency
	[[nodiscard]] const DWORD GetTransparency(DWORD Color, DWORD Transparency) { return ((Color & 0xFFFFFF) | Transparency << 24); }

	/*
		Enable/Disable Anti-Aliasing
		 - highest (n)x MSAA available (4x max) is the default
	*/
	void AntiAliasing(bool OnOff);

	// Enable/Disable Texture Filtering
	void TextureFiltering(D3DTEXTUREFILTERTYPE Type)
	{
		m_TextureFilter = Type;

		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, m_TextureFilter);
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, m_TextureFilter);

		pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, m_TextureFilter == D3DTEXF_ANISOTROPIC ? m_DeviceCaps->MaxAnisotropy : 0);
	}

	// Alpha Blending
	void AlphaBlending(BOOL OnOff, D3DBLEND SrcBlend = D3DBLEND_SRCALPHA, D3DBLEND DestBlend = D3DBLEND_INVSRCALPHA, D3DBLENDOP BlendOp = D3DBLENDOP_ADD)
	{
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, OnOff);
		pDevice->SetRenderState(D3DRS_SRCBLEND, SrcBlend);
		pDevice->SetRenderState(D3DRS_DESTBLEND, DestBlend);
		pDevice->SetRenderState(D3DRS_BLENDOP, BlendOp);
	}

	// Alpha Testing
	void AlphaTesting(BOOL OnOff, std::uint8_t Ref = 0xFF, D3DCMPFUNC Func = D3DCMP_GREATEREQUAL)
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, OnOff);
		pDevice->SetRenderState(D3DRS_ALPHAREF, Ref);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, Func);
	}

	// Enable/Disable Lighting
	void Lighting(bool OnOff);

	// Enable/Disable Z-Buffer
	void ZBuffer(BOOL OnOff, D3DZBUFFERTYPE Type, D3DCMPFUNC Func)
	{
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, OnOff);
		pDevice->SetRenderState(D3DRS_ZENABLE, Type);
		pDevice->SetRenderState(D3DRS_ZFUNC, Func);
	}

	// Create Axis and Grid
	void CreateAxisGrid(void);

	// Draw Grid
	void DrawGrid(void)
	{
		Draw({ Grid.get(), nullptr, nullptr, nullptr,
			{ TRUE, D3DZB_TRUE, D3DCMP_LESSEQUAL },
			{ sizeof(vec3c), D3DFILL_WIREFRAME, D3DPT_LINELIST },
			{ 0.0f, 0.0f },
			{ nullptr, nullptr, nullptr } });
	}

	// Draw Axis
	void DrawAxis(void)
	{
		Draw({ Axis.get(), nullptr, nullptr, nullptr,
			{ TRUE, D3DZB_TRUE, D3DCMP_LESSEQUAL },
			{ sizeof(vec3c), D3DFILL_WIREFRAME, D3DPT_LINELIST },
			{ 0.0f, 0.0f },
			{ nullptr, nullptr, nullptr } });
	}

	// Save screenshot
	bool SaveScreenshot(D3DXIMAGE_FILEFORMAT Format, std::filesystem::path Output);

};