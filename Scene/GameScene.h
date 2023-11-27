#pragma once
#include <vector>
#include <string>

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��

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
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�����o�֐�

	//������
	void Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)override;
	
	//�X�V
	void Update()override;
	
	//�`��
	void Draw()override;
	//���
	void Finalize()override;

private://�����o�ϐ�
	WindowsApp * Windows = nullptr;
	//pad* Pad = nullptr;
	Input* input = nullptr;
	DXCommon* dxCommon = nullptr;
	DebugText* debugText;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	Buns* buns = nullptr;
	//�Փ˃}�l�[�W���[
	CollisionManager* collisionManager = nullptr;

	//�X�v���C�g
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

	//3d�֘A
	//���f��
	FbxModel* bunsmodel1 = nullptr;//�o���Y���f��1
	FbxModel* bunsmodel2 = nullptr;//�o���Y���f��2
	FbxModel* bunsmodel3 = nullptr;//�o���Y���f��3
	FbxModel* meatmodel = nullptr;//�����f��
	FbxModel* cheasemodel = nullptr;//�`�[�Y���f��
	FbxModel* soxmodel = nullptr;//�C�����f��
	FbxModel* tomatomodel1 = nullptr;//�g�}�g���f��1
	FbxModel* tomatomodel2 = nullptr;//�g�}�g���f��2
	FbxModel* tomatomodel3 = nullptr;//�g�}�g���f��3
	FbxModel* tomatomodel4 = nullptr;//�g�}�g���f��4
	FbxModel* retasumodel1 = nullptr;//���^�X���f��1
	FbxModel* retasumodel2 = nullptr;//���^�X���f��2

	//�o���Y�p
	Buns* bunsup = nullptr;//��̃o���Y
	FBXobj3d* bunsup2 = nullptr;//��̃o���Y2
	FBXobj3d* bunsup3 = nullptr;//��̃o���Y3
	Buns* bunsdown = nullptr;//���̃o���Y
	FBXobj3d* bunsdown2 = nullptr;//���̃o���Y2
	FBXobj3d* bunsdown3 = nullptr;//���̃o���Y3

	RandomObj* random_ = nullptr;
	ScoreManager* score_ = nullptr;

	char moji[64];


	//�Q�[���Ŏg���ϐ�
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

	

	///�J�����֘A
	//�ЂƂO�̃}�E�X�̍��W
	float CurretmouseX = 0;
	float CurretmouseY = 0;
	//�J���������ʒu
	XMFLOAT3 EyeInitialize = { 0,4,0 };
	//�f�o�b�O�p���Z�b�g�t���O
	int resetflag = 0;
	//�J�����̍X�V�����p
	int firstfrag = 0;

	//�V�[���֘A
	float timecount = 0;//���ԊǗ������ϐ�
	//���񂾂Ƃ��̃V�[��
	int diescene = 0;
	//�N���A�����V�[��
	int clearscene = 0;
	int tutoscene = 0;
	int goflag = 0;
	

};

