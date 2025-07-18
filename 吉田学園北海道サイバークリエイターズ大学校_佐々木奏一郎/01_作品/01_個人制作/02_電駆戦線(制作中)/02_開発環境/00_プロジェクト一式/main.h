//****************************************
//
// メイン処理 [main.h]
// Author:Sasaki Soichiro
//
//****************************************
#ifndef _MAIN_H_ // このマクロ定義がされていなかったら
#define _MAIN_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x800)	// ビルド時の警告対処用マクロ
#include "dinput.h"					// 入力処理に必要
#include "xaudio2.h"				// サウンド処理に必要
#include "Xinput.h"					// ジョイパッド処理に必要

//********************
// ライブラリのリンク
//********************
#pragma comment(lib,"d3d9.lib")		// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	// DirectXのコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")	// システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")	// 入力処理に必要
#pragma comment(lib,"xinput.lib")	// ジョイパッド処理に必要

//********************
// マクロ定義
//********************
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME  "電駆戦線"	// ウィンドウの名前
#define SCREEN_WIDTH (1280)		// 画面の横幅
#define SCREEN_HEIGHT (720)		// 画面の縦幅
#define FVF_VERTEX_2D  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)			// 座標・カラー・テクスチャ
#define FVF_VERTEX_2D_MULTI  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX2)		// 座標・カラー・テクスチャ
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 座標・法線・カラー・テクスチャ

//****************************
// 頂点情報[2D]の構造体を定義
//****************************
typedef struct
{
	D3DXVECTOR3 pos;    // 頂点座標
	float rhw;          // 座標変換用係数(1.0fで固定)
	D3DCOLOR col;       // 頂点カラー
	D3DXVECTOR2 tex;    // テクスチャ座標
}VERTEX_2D;

//***********************************************
// 頂点情報[2D](マルチテクスチャ)の構造体を定義
//***********************************************
typedef struct
{
	D3DXVECTOR3 pos;    // 頂点座標
	float rhw;          // 座標変換用係数(1.0fで固定)
	D3DCOLOR col;       // 頂点カラー
	D3DXVECTOR2 tex;    // テクスチャ座標
	D3DXVECTOR2 texM;   // テクスチャ座標
}VERTEX_2D_MULTI;

//****************************
//頂点情報[3D]の構造体を定義
//****************************
typedef struct
{
	D3DXVECTOR3 pos;    // 頂点座標
	D3DXVECTOR3 nor;    // 法線ベクトル
	D3DCOLOR col;       // 頂点カラー
	D3DXVECTOR2 tex;    // テクスチャ座標
}VERTEX_3D;

//********************
// 前方宣言
//********************
class CRenderer;// レンダリングクラス
class CObject;	// オブジェクトクラス

//********************
// プロトタイプ宣言
//********************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif