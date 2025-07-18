//=============================================================================
//
//	リザルト処理 [result.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
#include "rankingscore.h"
#include "score.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//頂点バッファへのポインタ
//タイトル画面の初期化処理
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	Player* pPlayer=GetPlayer();
	if (pPlayer->nLife >= 1)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\STAGECLEAR000.png",
			&g_pTextureResult);
	}
	if (pPlayer->nLife <= 0)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameover000.png",
			&g_pTextureResult);
	}
	//頂点バッファの生成。頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//←右回りで設定する
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定　　　　
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();
	InitRankingscore();
	ResetRanking();
	SetRanking(GetScore());
	SetRankingTexure();
	InitScore();
	SetScore(GetScore());

}
//タイトル画面の終了処理
void UninitResult(void)
{
	StopSound();
	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	UninitRankingscore();
	UninitScore();
}
//タイトル画面の更新処理
void UpdateResult(void)
{
	UpdateRankingscore();
	UpdateScore();
	if (KeyboardTrigger(DIK_RETURN) == true)
	{//エンターキーが押された
		//モード設定
		SetFade(MODE_STAGESELECT);
	}
	if (JoyPadTrigger(JOYKEY_A) == true)
	{//エンターキーが押された
		//モード設定
		SetFade(MODE_STAGESELECT);
	}
	
}
//タイトル画面の描画処理
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ランキングの描画処理
	DrawRankingscore();

	DrawScore();
}