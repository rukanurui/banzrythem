#pragma once
#define __STDC_WANT_LIB_EXT1__ 1
#include "../3d/fbxobj3d.h"
#include"../Collider/BoxCollider.h"
#include "memory.h"
#include  <list>
#include "stdio.h"
#include <string.h>
#include <DirectXMath.h>
#include <share.h>
#include <sstream>

class RandomObj : public FBXobj3d
{
protected: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	RandomObj();
	//HWNDをセット
	void SetHwnd(HWND hwnd_) { hwnd = hwnd_; }
	//ランダムに生成
	void RandomInitialize();
	//描画
	void RandomDraw(ID3D12GraphicsCommandList* cmdList);
	//OBJの更新処理
	void RandomUpdate();

	//座標セット
	void SetBunsPosition(XMFLOAT3 pos) { BunsPosition = pos; }

	//取れるかのフラグセット


	//モデルセット
	//肉モデル
	void SetmeatModel(FbxModel* model) { meatmodel = model; }
	void SettomatoModel(FbxModel* model) { tomatomodel = model; }
	void SettomatoModel2(FbxModel* model) { tomatomodel2 = model; }
	void SettomatoModel3(FbxModel* model) { tomatomodel3 = model; }
	void SettomatoModel4(FbxModel* model) { tomatomodel4 = model; }
	void SetretasuModel(FbxModel* model) { retasumodel = model; }
	void SetretasuModel2(FbxModel* model) { retasumodel2 = model; }
	void SettirzuModel(FbxModel* model) { tirzumodel = model; }
	void SetkutusitaModel(FbxModel* model) { kutusitamodel = model; }

	//void SetcheseModel(FbxModel* model) { chesemodel = model; }

	//ナンバーのGetter
	const int& GetRandomNumber() { return RandomNumber; }

	bool GetGetFlag() { return GetFlag; }

private:
	//ランダム変数
	float RandomHalfway_X = 0;
	float RandomHalfway_Y = 0;

	int RandomNumber = 0;	

	bool GetFlag = true;

	float TimeRate = 0.0f;

	float CreateObjTime = 0.0f;

	
	size_t startIndex = 1;

	XMFLOAT3 BunsPosition;

	//出力時のオブジェクト配列
	std::list<std::unique_ptr<RandomObj>> Objs;
	//子のオブジェクト配列
	std::list<std::unique_ptr<RandomObj>> ChildObjs;
	//HWND
	HWND hwnd = nullptr;

	//オブジェクトのモデルポインタ
	FbxModel* meatmodel = nullptr;//モデル
	FbxModel* tomatomodel = nullptr;//モデル
	FbxModel* tomatomodel2 = nullptr;//トマトモデル2
	FbxModel* tomatomodel3 = nullptr;//トマトモデル3
	FbxModel* tomatomodel4 = nullptr;//トマトモデル4
	FbxModel* retasumodel = nullptr;//モデル
	FbxModel* retasumodel2 = nullptr;//モデル
	FbxModel* tirzumodel = nullptr;//モデル
	FbxModel* kutusitamodel = nullptr;//モデル


};

