//****************************************
//
// オブジェクト2D処理 [object2D.cpp]
// Author:Sasaki Soichiro
//
//****************************************

//*******************
// インクルード
//*******************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//*******************
// マクロ定義
//*******************
#define OBJ_HEIGHT (150.0f) // オブジェクトの高さ
#define OBJ_WIDTH (250.0f)	// オブジェクトの幅

//*******************
// コンストラクタ
//*******************
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	//m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//*******************
// デストラクタ
//*******************
CObject2D::~CObject2D()
{
}

//**************
// 初期化処理
//**************
HRESULT CObject2D::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	m_pos = pos;
	float fAngle = atan2f(m_size.x, m_size.y);
	VERTEX_2D* pVertex;//頂点情報へのポインタ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);

	//頂点座標の設定
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * m_size.x, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * m_size.y, 0.0f);//←右回りで設定する
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * m_size.x, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * m_size.y, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * m_size.x, m_pos.y + cosf(m_rot.z - fAngle) * m_size.y, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * m_size.x, m_pos.y + cosf(m_rot.z + fAngle) * m_size.y, 0.0f);

	//rhwの設定
	pVertex[0].rhw = 1.0f;
	pVertex[1].rhw = 1.0f;
	pVertex[2].rhw = 1.0f;
	pVertex[3].rhw = 1.0f;
	//頂点カラーの設定　　　　
	pVertex[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVertex[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVertex[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVertex[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;

}

//**************
// 終了処理
//**************
void CObject2D::Uninit(void)
{
	//// テクスチャの破棄
	//if (m_pTexture != NULL)
	//{
	//	//m_pTexture->Release();
	//	m_pTexture = NULL;
	//}
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}

//**************
// 更新処理
//**************
void CObject2D::Update(void)
{
}

//**************
// 描画処理
//**************
void CObject2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//**************
// 位置設定
//**************
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVertex;//頂点情報へのポインタ
	m_pos = pos;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y)/2.0f;
	float fAngle= atan2f(m_size.x, m_size.y);
//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI+fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//←右回りで設定する
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle)* fRength, 0.0f);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//**************
// 向きの設定
//**************
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	VERTEX_2D* pVertex;//頂点情報へのポインタ
	m_rot=rot;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//←右回りで設定する
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle) * fRength, 0.0f);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//**************
// UV座標の設定
//**************
void CObject2D::SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4)
{
	VERTEX_2D* pVertex;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].tex = uv1;
	pVertex[1].tex = uv2;
	pVertex[2].tex = uv3;
	pVertex[3].tex = uv4;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//**************
// 色の設定
//**************
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D* pVertex;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].col = col;
	pVertex[1].col = col;
	pVertex[2].col = col;
	pVertex[3].col = col;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//**************
// 大きさの設定
//**************
void CObject2D::SetSize(D3DXVECTOR2 size)
{
	VERTEX_2D* pVertex;//頂点情報へのポインタ
	m_size = size;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//←右回りで設定する
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle) * fRength, 0.0f);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}


//void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
//{
//	m_pTexture = pTexture;
//}
//CObject2D*CObject2D::Create(void)
//{
//	CObject2D* pObject2D;
//	pObject2D = new CObject2D;
//	pObject2D->Init();
//	return pObject2D;
//}