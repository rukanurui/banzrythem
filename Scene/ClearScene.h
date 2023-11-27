#pragma once
#include"BaseScene.h"
#include "../Engine/Input.h"
#include "../Engine/DXCommon.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include "../Engine/WindowsApp.h"
#include "../Engine/Audio.h"
#include"../3d/Wall.h"
#include <vector>
#include <memory>
#include <list>
#include<sstream>
#include <string>

class GameScene;
class TitleScene;

class ClearScene : public BaseScene
{
protected:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;

	void Update()override;

	void Draw()override;

	void Finalize()override;

	
private:
	//�|�C���^
	WindowsApp* Windows = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;

	//�X�v���C�g
	XMFLOAT3 spritepos{ WindowsApp::window_width / 2 ,WindowsApp::window_height / 2,0 };
	XMFLOAT2 spritesize{ WindowsApp::window_width,WindowsApp::window_height };
	XMFLOAT2 movesize = { 800,300 };


	bool transfrag = true;
	float spriteangle = 0;
	bool overfrag = true;
	int wait = 0;

};

