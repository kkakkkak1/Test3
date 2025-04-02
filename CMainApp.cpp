#include "pch.h"
#include "CMainApp.h"
#include "CTimerMgr.h"
#include "CFrameMgr.h"

IDirect3DVertexBuffer9* Triangle = 0;

CMainApp::CMainApp() : m_pGraphicDev(nullptr)
{ 
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(Engine::CGraphicDev::GetInstance()->Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDevClass)))
		return E_FAIL;
	
	m_pGraphicDev = m_pDevClass->Get_GraphicDev();
	m_pGraphicDev->AddRef();

	IDirect3DVertexBuffer9* g_pVB; 	//선언

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(
		3 * sizeof(CUSTOMVERTEX), // 3개의 버텍스 (삼각형)
		0,
		D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT,
		&g_pVB,
		NULL
	))) return E_FAIL;

	VTXCOL* vertices;
	Triangle->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = { {-1.f, 0.f, 2.f}, D3DCOLOR_XRGB(255,0,0) };
	vertices[1] = { {0.f, 1.f, 2.f}, D3DCOLOR_XRGB(0,255,0) };
	vertices[1] = { {1.f, 0.f, 2.f}, D3DCOLOR_XRGB(0,0,255) };

	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0))
		return E_FAIL;
		memcpy(pVertices, vertices, sizeof(vertices));
		g_pVB->Unlock();


#pragma region 테스트1
	//D3DXMATRIX World;


	//m_pGraphicDev->CreateVertexBuffer(
	//	3 * sizeof(VTXCOL),
	//	D3DUSAGE_WRITEONLY,
	//	FVF_COL,
	//	D3DPOOL_MANAGED,
	//	&Triangle,
	//	0
	//);

	//VTXCOL* v;
	//Triangle->Lock(0, 0, (void**)&v, 0);

	//v[0] = { {-1.f, 0.f, 2.f}, D3DCOLOR_XRGB(255,0,0) };
	//v[1] = { {0.f, 1.f, 2.f}, D3DCOLOR_XRGB(0,255,0) };
	//v[1] = { {1.f, 0.f, 2.f}, D3DCOLOR_XRGB(0,0,255) };
	//Triangle->Unlock();

	//D3DXMATRIX proj;
	//D3DXMatrixPerspectiveFovLH(
	//	&proj,
	//	D3DX_PI * 0.5f,
	//	(float)WINCX / (float)WINCY,
	//	1.0f,
	//	1000.0f
	//);
	//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);

	//if (m_pGraphicDev)
	//{
	//	m_pGraphicDev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//		0, 1.0f, 0);
	//	m_pGraphicDev->BeginScene();

	//	m_pGraphicDev->SetFVF(D3DFVF_XYZ);
	//	m_pGraphicDev->SetStreamSource(0, Triangle, 0, sizeof(VTXCOL));

	//	D3DXMatrixTranslation(&World, -1.25f, 0.0f, 0.0f);
	//	m_pGraphicDev->SetTransform(D3DTS_WORLD, &World);

	//	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	//	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//	D3DXMatrixTranslation(&World, 1.25f, 0.0f, 0.0f);
	//	m_pGraphicDev->SetTransform(D3DTS_WORLD, &World);

	//	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//	m_pGraphicDev->EndScene();
	//	m_pGraphicDev->Present(0, 0, 0, 0);
	//}
#pragma endregion

	
#pragma region 테스트2
	/*IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9* IB = 0;

	m_pGraphicDev->CreateVertexBuffer(
		8 * sizeof(VTXCOL),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ,
		D3DPOOL_MANAGED,
		&VB,
		0);

	m_pGraphicDev->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);

	VTXCOL* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[1] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[2] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[3] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[4] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[5] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[6] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };
	vertices[7] = { {0.f, 1.f, 0.f}, D3DCOLOR_XRGB(0,0,0) };

	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	IB->Unlock();

	D3DXVECTOR3 position(0.f, 0.f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)WINCX / (float)WINCY,
		1.0f,
		1000.0f
	);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);*/




	//IDirect3DVertexBuffer9* m_pVertexBuffer; 	//선언
	//VTXCOL* TestVertices;

	//m_pGraphicDev->CreateVertexBuffer(3 * sizeof(VTXCOL), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0,
	//	D3DPOOL_DEFAULT,
	//	TestVertices, HANDLE * pSharedHandle);
	/*TestVertices[0].vPosition = { -1.f, 1.f, 0.f };*/
#pragma endregion

	return S_OK;
}

_int CMainApp::Update_MainApp(_float _fTimeDelta)
{
	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
}

void CMainApp::Render_MainApp()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	m_pDevClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	m_pDevClass->Render_End();

	m_pGraphicDev->SetStreamSource(0, Triangle, 0, sizeof(VTXCOL));
	m_pGraphicDev->SetFVF(FVF_COL);
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if (FAILED(pMainApp->Ready_MainApp()))
	{
		Engine::Safe_Release(pMainApp);
		return nullptr;
	}

	return pMainApp;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphicDev);

	CTimerMgr::GetInstance()->DestroyInstance();
	CFrameMgr::GetInstance()->DestroyInstance();
	m_pDevClass->DestroyInstance();
}
