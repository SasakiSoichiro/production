//******************************************
//
// オブジェクト2D処理 [object2D.h]
// Author:Sasaki Soichiro
//
//******************************************
#ifndef _OBJECT2D_H_ // このマクロ定義がされていなかったら
#define _OBJECT2D_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//********************
// オブジェクトクラス
//********************
class CObject2D:public CObject
{
public:
	CObject2D(int nPriority);	// コンストラクタ
	~CObject2D();				// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	void SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);// UV座標の設定
	void SetCol(D3DXCOLOR col);// 色の設定
	void SetSize(D3DXVECTOR2 size);// 大きさの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置情報の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// 向き情報の取得
	D3DXCOLOR GetCol(void) { return m_col; }	// 色情報の取得
	D3DXVECTOR2 GetSize(void){ return m_size; }	// 大きさ情報の取得
	//void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
private:
	//LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXCOLOR m_col;	// 色
	D3DXVECTOR2 m_size;	// 大きさ
};
#endif