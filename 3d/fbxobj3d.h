#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Modelfbx.h"
#include "../Engine/Camera.h"
#include "FbxLoader.h"
#include "fbxsdk.h"
#include <string>
#include"../Collider/ColisionInfo.h"
#include"../Collider/CollisionColor.h"

class BaseCollider;

class FBXobj3d
{
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;	

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����(���W�ϊ�)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;//�r���[�v���W�F�N�V����
		XMMATRIX world;//���[���h�s��
		XMFLOAT3 camerapos;//�J�������W(���[���h���W)
	};

	//�{�[���̍ő吔
	static const int MAX_BONES = 32;

	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public://�����o�֐�
	//�R���X�g���N�^
	FBXobj3d() = default;
	//�f�X�g���N�^
	virtual ~FBXobj3d();
	//������
	virtual void Initialize();
	//�O���t�B�b�N�X�p�C�v���C���̐���
	static void CreateGraphicsPipeline();
	//���t���[������
	virtual void Update();
	//���f���̃Z�b�g
	void SetModel(FbxModel* model) { this->fbxmodel = model; }
	//�`��
	virtual void Draw(ID3D12GraphicsCommandList* cmdList);
	//Fbx�A�j���[�V�����Đ�
	void PlayAnimation();

	//�Փˎ��R�[���o�b�N�֐�
	virtual void OnCollision(const CollisionInfo& info) {};

	//getter
	//���[���h�s��̃Q�b�^�[
	const XMMATRIX& GetMatWorld() { return matWorld; }
	void SetMatWorld(XMMATRIX World) { this->matWorld = World; }

	const XMFLOAT3& GetPos() { return position; }
	const float& GetPosX() { return position.x; }
	const float& GetPosY() { return position.y; }
	const float& GetPosZ() { return position.z; }

	const XMFLOAT3& GetScale() { return scale; }

	const XMFLOAT3& GetRotation() { return rotation; }

	const float& GetScaleX() { return scale.x; }
	const float& GetScaleY() { return scale.y; }
	const float& GetScaleZ() { return scale.z; }

	const XMMATRIX& GetmatTrans() { return matTrans; }
	
	//setter
	static void SetDevice(ID3D12Device* device) { FBXobj3d::device = device; }
	static void SetCamera(Camera* camera) { FBXobj3d::camera = camera; }
	//�|�W�V�����̕ύX
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetPosX(float x) { this->position.x = x; }
	//�X�P�[���̕ύX
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	//�p�x�̕ύX
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	//���s�ړ��s��̃Z�b�^�[
	void SetmatTrans(XMMATRIX Mattrans) { this->matTrans = Mattrans; }
	//�R���C�_�[�̃Z�b�g
	void SetCollider(BaseCollider* collider);
	//���[���h���W�X�V
	void UpdateWorld();
	//�X�P�[���ω�
	void MoveScaleZ(float Velocity);
	//�x�N�g���ɂ����W�ړ�
	void MoveVector(const XMVECTOR& move);

	void SetCanGetFlag(bool flag) { CanGet = flag; }
	bool GetCanGetFlag() { return CanGet; }

protected://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBufferTransform;
	//�X�L���̒萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffSkin;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	XMMATRIX matScale, matRot, matTrans;
	//���f��
	FbxModel* fbxmodel = nullptr;

	bool CanGet = false;
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	
	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;

	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F
	static ComPtr<ID3D12PipelineState> pipelinestate;

	//�N���X��(�f�o�b�O�p)
	const char* name = nullptr;
	//�R���C�_�[
	BaseCollider* collider = nullptr;

};