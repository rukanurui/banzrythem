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
protected: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	RandomObj();
	//HWND���Z�b�g
	void SetHwnd(HWND hwnd_) { hwnd = hwnd_; }
	//�����_���ɐ���
	void RandomInitialize();
	//�`��
	void RandomDraw(ID3D12GraphicsCommandList* cmdList);
	//OBJ�̍X�V����
	void RandomUpdate();

	//���W�Z�b�g
	void SetBunsPosition(XMFLOAT3 pos) { BunsPosition = pos; }

	//���邩�̃t���O�Z�b�g


	//���f���Z�b�g
	//�����f��
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

	//�i���o�[��Getter
	const int& GetRandomNumber() { return RandomNumber; }

	bool GetGetFlag() { return GetFlag; }

private:
	//�����_���ϐ�
	float RandomHalfway_X = 0;
	float RandomHalfway_Y = 0;

	int RandomNumber = 0;	

	bool GetFlag = true;

	float TimeRate = 0.0f;

	float CreateObjTime = 0.0f;

	
	size_t startIndex = 1;

	XMFLOAT3 BunsPosition;

	//�o�͎��̃I�u�W�F�N�g�z��
	std::list<std::unique_ptr<RandomObj>> Objs;
	//�q�̃I�u�W�F�N�g�z��
	std::list<std::unique_ptr<RandomObj>> ChildObjs;
	//HWND
	HWND hwnd = nullptr;

	//�I�u�W�F�N�g�̃��f���|�C���^
	FbxModel* meatmodel = nullptr;//���f��
	FbxModel* tomatomodel = nullptr;//���f��
	FbxModel* tomatomodel2 = nullptr;//�g�}�g���f��2
	FbxModel* tomatomodel3 = nullptr;//�g�}�g���f��3
	FbxModel* tomatomodel4 = nullptr;//�g�}�g���f��4
	FbxModel* retasumodel = nullptr;//���f��
	FbxModel* retasumodel2 = nullptr;//���f��
	FbxModel* tirzumodel = nullptr;//���f��
	FbxModel* kutusitamodel = nullptr;//���f��


};

