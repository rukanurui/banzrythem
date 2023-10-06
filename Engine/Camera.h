#pragma once

#include <DirectXMath.h>
#include"Input.h"
#include"WindowsApp.h"
#include"pad.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��


using namespace DirectX;

class Camera
{
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;


public: // �����o�֐�

	//�R���X�g���N�^
	Camera(Input* input,WindowsApp* windows);
	//������
	virtual void Initialize(int window_width, int window_height,Input* input);
	//�X�V
	void Update(int window_width, int window_height);
	void UpdateViewMatrix();
	void UpdateProjectionMatrix(int window_width, int window_height);

	//�J�������W�ƒ����_�����ړ�
	void MoveVector(const XMVECTOR& move);
	//�����_�݈̂ړ�
	void MoveTarget(const XMVECTOR& move);

	//update�O����
	void CurrentUpdate(XMFLOAT3 vel);

	//Getter
	//�r���[�s��֘A
	const XMMATRIX& GetViewMatrix() {return matView;}

	/// ���_���W�̎擾
	const XMFLOAT3& GetEye() { return eye; }

	/// �����_���W�̎擾
	const XMFLOAT3& GetTarget() { return target; }
	const float& GetTargetX() { return target.x; }
	const float& GetTargetY() { return target.y; }
	const float& GetTargetZ() { return target.z; }


	const XMFLOAT3& GetUp() {return up;}

	const XMFLOAT3& GetRoatation() { return rotation; }

	const XMMATRIX& GetmatRot() { return matRot; }



	//�v���W�F�N�V�����s��֘A

	const XMMATRIX& GetProjectionMatrix() {return matProjection;}

	const XMMATRIX& GetViewProjectionMatrix() {return matViewProjection;}

	inline const XMMATRIX& GetBillboardMatrix() {
		return matBillboard;
	}

	//Setter
	//�r���[�s��֘A

	/// ���_���W�̐ݒ�
	void SetEye(XMFLOAT3 eye);

	/// �����_���W�̐ݒ�
	void SetTarget(XMFLOAT3 target);

	void SetUp(XMFLOAT3 up);

	void SetViewMatrix(XMMATRIX viewmatrix);

	void SetRoatation(XMFLOAT3 roatation);

	void SetmouseX(float mouseX);

	void SetmouseY(float mouseY);


protected://�����o�ϐ�
	Input* input=nullptr;
	WindowsApp* windows = nullptr;
	//pad* Pad = nullptr;
	// �r���[�s��
	static XMMATRIX matView;
	// �r���{�[�h�s��
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	// Y�����r���{�[�h�s��
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	// �ˉe�s��
	static XMMATRIX matProjection;
	// �r���[�v���W�F�N�V�����s��
	static XMMATRIX matViewProjection;
	//���[���h�s��
	static XMMATRIX matWorld;
	// X,Y,Z�����̃��[�J����]�p
	static XMFLOAT3 rotation;
	// �J�����̍��W
	static XMFLOAT3 eye;
	// �����_���W(���Ă�ꏊ)
	static XMFLOAT3 target;
	// �J�����̍��W(�ǂɓ�����O)
	XMFLOAT3 walleye;
	// �����_���W(�ǂɓ�����O)
	XMFLOAT3 walltarget;
	// ������x�N�g��
	static XMFLOAT3 up;
	// �A�X�y�N�g��
	float aspectRatio = 1.0f;
	//�t���O
	bool viewDirtyFlag = false;
	// ��]�s��
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
	// �X�P�[�����O
	float scaleX = 0.5f;
	float scaleY = 0.5f;

	//1�t���[���O�̃A���O��
	float angleculentX = 0.0f;
	float angleculentY = 0.0f;

	//���Z����Ă����A���O��
	float anglelimitX = 0.0f;
	float anglelimitY = 0.0f;

	float CurretmouseX = 0;
	float CurretmouseY = 0;

	XMFLOAT3 Velocity{ 0,0,0 };//���x

	// �J���������_�܂ł̋���
	float distance = 3;

	float angleX = 0.0f;
	float angleY = 0.0f;

};

