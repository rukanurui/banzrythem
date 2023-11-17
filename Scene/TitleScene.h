#pragma once

#include"BaseScene.h"
#include "../Engine/Input.h"
#include "../Engine/DXCommon.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include "../Engine/WindowsApp.h"
#include "../Engine/Audio.h"
#include "../Engine/Camera.h"
#include "fbxsdk.h"
#include "../3d/FbxLoader.h"
#include "../3d/FBXobj3d.h"
#include "../3d/Modelfbx.h"
#include <vector>


class TitleScene: public BaseScene
{
protected:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;

	void Update()override;

	void Draw()override;

	void Finalize()override;

	void Settitleflag(bool now) { this->titleflag = now; }

private:
	//ポインタ
	WindowsApp* Windows = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Camera* camera = nullptr;

	//sprite
	Sprite* title = nullptr;
	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ WindowsApp::window_width,WindowsApp::window_height };
	XMFLOAT2 movesize = { 800,300 };

	//3d
	FbxModel* bamodel = nullptr;
	FbxModel* nnmodel = nullptr;
	FbxModel* zumodel = nullptr;
	FbxModel* rimodel = nullptr;
	FbxModel* zu2model = nullptr;
	FbxModel* mumodel = nullptr;

	FBXobj3d* ba = nullptr;
	FBXobj3d* nn = nullptr;
	FBXobj3d* zu = nullptr;
	FBXobj3d* ri = nullptr;
	FBXobj3d* zu2 = nullptr;
	FBXobj3d* mu = nullptr;


	bool transfrag = true;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;

	///カメラ関連
	//ひとつ前のマウスの座標
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//カメラ初期位置
	XMFLOAT3 EyeInitialize = { 0,4,0 };

	//今のシーンがタイトルかどうか
	bool titleflag = true;

};

