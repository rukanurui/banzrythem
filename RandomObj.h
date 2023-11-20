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
	//�o���Y���f��
	void SetBunsModel(FbxModel* model) { meatmodel = model; }


private:
	//�����_���ϐ�
	float RandomHalfway_X = 0;
	float RandomHalfway_Y = 0;

	int RandomNumber = 0;

	float TimeRate = 0.0f;

	float CreateObjTime = 0.0f;

	
	size_t startIndex = 1;

	XMFLOAT3 BunsPosition;

	//�o�͎��̃I�u�W�F�N�g�z��
	std::list<std::unique_ptr<RandomObj>> Objs;
	//HWND
	HWND hwnd = nullptr;

	//�I�u�W�F�N�g�̃��f���|�C���^
	FbxModel* meatmodel = nullptr;//���f��
};

