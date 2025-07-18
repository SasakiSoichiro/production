//=============================================================================
//
//	メイン処理 [main.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _MAIN_H_	//このマクロ定義がされていなかったら
#define _MAIN_H_	//二重インクルード防止のマクロ定義
#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x800)	//ビルド時の警告対処用マクロ
#include "dinput.h"					//入力処理に必要
#include "xaudio2.h"				//サウンド処理に必要
#include "Xinput.h"					//ジョイパッド処理に必要
//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXのコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")	//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド処理に必要
//マクロ定義
#define CLASS_NAME "WindowClass"									//nanikore
#define WINDOW_NAME  "ポゴダイッ！"									//ウィンドウの名前
#define SCREEN_WIDTH (1280)											//ウィンドウの幅
#define SCREEN_HEIGHT (720)											//ウィンドウの高さ
#define FVF_VERTEX_2D  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//なにこれ
#define OBJ_WIDTH (30)												//プレイヤーの幅
#define OBJ_HEIGHT (60)												//プレイヤーの高さ

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;    //頂点座標
	float rhw;          //座標変換用係数(1.0fで固定)
	D3DCOLOR col;       //頂点カラー
	D3DXVECTOR2 tex;    //テクスチャ座標
}VERTEX_2D;

//画面の種類
typedef enum
{
	MODE_TITLE=0,		//タイトル画面
	MODE_TUTORIAL,		//チュートリアル画面
	MODE_GAME,			//ゲーム画面
	MODE_RESULT,		//リザルト画面
	MODE_RANKING,		//ランキング画面
	MODE_EDIT,			//編集画面
	MODE_STAGESELECT,	//ステージ選択
	MODE_BLOCKINFO,		//ブロックの説明
	MODE_MAX
}MODE;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawPos(void);
void DrawAnimPatten(void);
void DrawPosPGCircle(void);
void DrawPosPYCircle(void);
void DrawMove(void);
void DrawStage(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif