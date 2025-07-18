//**********************************
//
// ポーズ処理 [pause.h]
// Author:Sasaki Soichiro
//
//**********************************
#ifndef _PAUSE_H_ // このマクロ定義がされていなかったら
#define _PAUSE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "object2D.h"

//********************
// ポーズクラス
//********************
class CPause :public CObject2D
{
public:
	CPause(int nPriority = 7);	// コンストラクタ
	~CPause();					// デストラクタ
	static CPause* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);// 位置
	void SetRot(D3DXVECTOR3 rot);// 向き
	D3DXVECTOR3 GetPos(void);// 位置情報の取得
	D3DXVECTOR2 GetSize(void);// 大きさ情報の取得
	static bool GetPause(void) { return m_bPause; }			// ポーズ情報の取得
	static void SwitchPause(void) { m_bPause = !m_bPause; }	// ポーズ切り替え
private:
	int  m_nIdxTexture;		// テクスチャのインデックス
	static bool m_bPause;	// ポーズ切替用
};
#endif