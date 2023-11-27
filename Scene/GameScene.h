#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定

#include "../Engine/Input.h"

#include "../Engine/WindowsApp.h"
#include "../Engine/DXCommon.h"

#include "../3d/Object3d.h"
#include "../3d/model.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include"../2d/PostEffect.h"
#include "../2d/DebugText.h"
#include "../Engine/Audio.h"

#include "fbxsdk.h"
#include "../3d/FbxLoader.h"
#include "../3d/FBXobj3d.h"
#include "../3d/Modelfbx.h"

#include "../Engine/Camera.h"

#include <memory>
#include <list>

#include"BaseScene.h"
#include"TransEffect.h"
#include"../Buns/Buns.h"
#include"../RandomObj.h"
#include"../ScoreManager.h"




class CollisionManager;


class GameScene : public BaseScene
{
protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://メンバ関数

	//初期化
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;
	
	//更新
	void Update()override;
	
	//描画
	void Draw()override;
	//解放
	void Finalize()override;

private://メンバ変数
	WindowsApp * Windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	Buns* buns = nullptr;
	//衝突マネージャー
	CollisionManager* collisionManager = nullptr;

	//スプライト
	SpriteCommon* spriteCommon = nullptr;
	Sprite* trans = nullptr;
	Sprite* sousa = nullptr;
	Sprite* owari = nullptr;
	TransEffect* transEffect = nullptr;

	XMFLOAT3 spritepos{ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize = { 1280,720 };

	XMFLOAT2 Effectsize{ 0,0 };
	float transcount = 0;
	bool transscene = false;
	
	bool transfrag = true;
	bool playflag = false;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;
	int count = 0;

	//3d関連
	//モデル
	FbxModel* bunsmodel1 = nullptr;//バンズモデル1
	FbxModel* bunsmodel2 = nullptr;//バンズモデル2
	FbxModel* bunsmodel3 = nullptr;//バンズモデル3
	FbxModel* meatmodel = nullptr;//肉モデル
	FbxModel* cheasemodel = nullptr;//チーズモデル
	FbxModel* soxmodel = nullptr;//靴下モデル
	FbxModel* tomatomodel1 = nullptr;//トマトモデル1
	FbxModel* tomatomodel2 = nullptr;//トマトモデル2
	FbxModel* tomatomodel3 = nullptr;//トマトモデル3
	FbxModel* tomatomodel4 = nullptr;//トマトモデル4
	FbxModel* retasumodel1 = nullptr;//レタスモデル1
	FbxModel* retasumodel2 = nullptr;//レタスモデル2

	//バンズ用
	Buns* bunsup = nullptr;//上のバンズ
	FBXobj3d* bunsup2 = nullptr;//上のバンズ2
	FBXobj3d* bunsup3 = nullptr;//上のバンズ3
	Buns* bunsdown = nullptr;//下のバンズ
	FBXobj3d* bunsdown2 = nullptr;//下のバンズ2
	FBXobj3d* bunsdown3 = nullptr;//下のバンズ3

	RandomObj* random_ = nullptr;
	ScoreManager* score_ = nullptr;

	char moji[64];


	//ゲームで使う変数
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

	

	///カメラ関連
	//ひとつ前のマウスの座標
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//カメラ初期位置
	XMFLOAT3 EyeInitialize = { 0,4,0 };
	//デバッグ用リセットフラグ
	int resetflag = 0;
	//カメラの更新処理用
	int firstfrag = 0;

	//シーン関連
	float timecount = 0;//時間管理酔う変数
	//死んだときのシーン
	int diescene = 0;
	//クリアしたシーン
	int clearscene = 0;
	int tutoscene = 0;
	int goflag = 0;
	

};

