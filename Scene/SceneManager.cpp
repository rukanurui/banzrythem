#include "SceneManager.h"


void SceneManager::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
	this->dxCommon = dxcommon;
	this->input = input;
	this->audio = audio;
	this->spriteCommon = spritecommon;
	this->Windows = windows;

}

void SceneManager::Update()
{
	//�V�[���؂�ւ�
	//���V�[���̗\�񂪂���Ȃ�
	if (nextscene)
	{
		//�Â��V�[���̏I��
		if (scene)
		{
			scene->Finalize();
			delete scene;
		}

		//�V�[���؂�ւ�
		scene = nextscene;
		nextscene = nullptr;

		//�V�[���}�l�[�W���[���Z�b�g
		scene->SetSceneManager(this);

		//���݂ǂ̃X�e�[�W�Ȃ̂������̃V�[���ɓn��
		scene->SetSlayScene(playscene);
		//���̃V�[��������������
		scene->Initialize(dxCommon,input,audio,spriteCommon,Windows);
		
	}

	//�V�[���X�V
	scene->Update();

}

void SceneManager::Draw()
{
	scene->Draw();
}


SceneManager::~SceneManager()
{
	//�V�[���̏I���Ɖ��
	scene->Finalize();
	delete scene;
}