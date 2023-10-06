#pragma once
#include"BaseScene.h"
#include "../Engine/Input.h"
#include "../Engine/DXCommon.h"
#include "../2d/SpriteCommon.h"
#include "../2d/Sprite.h"
#include "../Engine/WindowsApp.h"
#include "../Engine/Audio.h"

class SceneManager
{
public:
	//������
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows);
	//�V�[���؂�ւ�
	void NextScene(BaseScene* nextScene) { nextscene = nextScene;}
	//�V�[���ݒ�
	void SetplayScene(int scene) { playscene = scene; }
	//�X�V
	void Update();
	//�`��
	void Draw();

	~SceneManager();

private:

	WindowsApp* Windows = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	BaseScene* scene = nullptr;
	BaseScene* nextscene = nullptr;

	bool transfrag = true;

	//�ǂ̃X�e�[�W���v���C���Ă��邩
	int playscene = 0;

	
};

