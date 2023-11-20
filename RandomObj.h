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
	//バンズモデル
	void SetBunsModel(FbxModel* model) { meatmodel = model; }


private:
	//ランダム変数
	float RandomHalfway_X = 0;
	float RandomHalfway_Y = 0;

	int RandomNumber = 0;

	float TimeRate = 0.0f;

	float CreateObjTime = 0.0f;

	
	size_t startIndex = 1;

	XMFLOAT3 BunsPosition;

	//出力時のオブジェクト配列
	std::list<std::unique_ptr<RandomObj>> Objs;
	//HWND
	HWND hwnd = nullptr;

	//オブジェクトのモデルポインタ
	FbxModel* meatmodel = nullptr;//モデル
};

