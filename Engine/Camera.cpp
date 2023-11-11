#include "Camera.h"
#include "../Physics.h"


using namespace DirectX;
XMMATRIX Camera::matView = {};
XMMATRIX Camera::matProjection = {};
XMMATRIX Camera::matViewProjection = {};
XMMATRIX Camera::matWorld = {};
XMFLOAT3 Camera::eye = { 0, 4.0f, 0.0f };
XMFLOAT3 Camera::target = { 0, 5.0f, 0 };
XMFLOAT3 Camera::up = { 0, 1, 0 };
XMFLOAT3 Camera::rotation = { 0, 0, 0 };



Camera::Camera(Input* input,WindowsApp*windows)
{
	assert(input);
	assert(windows);
	this->input = input;
	this->windows = windows;
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = 1.0f / (float)windows->window_width;
	scaleY = 1.0f / (float)windows->window_height;
}

void Camera::Initialize(int window_width, int window_height,Input* input)
{

	// �r���[�s��̐���
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
}

void Camera::Update(int window_width, int window_height)
{
	// �Čv�Z�K�v�Ȃ�
	if (viewDirtyFlag) {
		// �r���[�s��X�V
		UpdateViewMatrix();
		viewDirtyFlag = false;
	}
	
	UpdateProjectionMatrix(window_width, window_height);
	matViewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix()
{

	// ���_���W
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	// �����_���W
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	// �i���́j�����
	XMVECTOR upVector = XMLoadFloat3(&up);

	// �J����Z���i���������j
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	// 0�x�N�g�����ƌ�������܂�Ȃ��̂ŏ��O
	//assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	// �x�N�g���𐳋K��
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	// �J������X���i�E�����j
	XMVECTOR cameraAxisX;
	// X���͏������Z���̊O�ςŋ��܂�
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	// �x�N�g���𐳋K��
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	// �J������Y���i������j
	XMVECTOR cameraAxisY;
	// Y����Z����X���̊O�ςŋ��܂�
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);

	// �����܂łŒ�������3�����̃x�N�g��������
	//�i���[���h���W�n�ł̃J�����̉E�����A������A�O�����j	

	// �J������]�s��
	XMMATRIX matCameraRot;
	// �J�������W�n�����[���h���W�n�̕ϊ��s��
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
	// �]�u�ɂ��t�s��i�t��]�j���v�Z
	matView = XMMatrixTranspose(matCameraRot);

	// ���_���W��-1���|�������W
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	// �J�����̈ʒu���烏�[���h���_�ւ̃x�N�g���i�J�������W�n�j
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);	// X����
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);	// Y����
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);	// Z����
	// ��̃x�N�g���ɂ܂Ƃ߂�
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	// �r���[�s��ɕ��s�ړ�������ݒ�
	matView.r[3] = translation;

}

void Camera::UpdateProjectionMatrix(int window_width, int window_height)
{
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
}

void Camera::SetEye(XMFLOAT3 eye)
{
	Camera::eye = eye;

	UpdateViewMatrix();
}

void Camera::SetTarget(XMFLOAT3 target)
{
	Camera::target = target;

	UpdateViewMatrix();
}

void Camera::SetUp(XMFLOAT3 up)
{
	Camera::up = up;

	UpdateViewMatrix();
}

void Camera::SetRoatation(XMFLOAT3 roatation)
{
	Camera::rotation = roatation;
}

void Camera::SetmouseX(float mouseX)
{
	Camera::CurretmouseX = mouseX;
}

void Camera::SetmouseY(float mouseY)
{
	Camera::CurretmouseY = mouseY;
}

void Camera::MoveVector(const XMVECTOR& move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.m128_f32[0];
	eye_moved.y += move.m128_f32[1];
	eye_moved.z += move.m128_f32[2];

	target_moved.x += move.m128_f32[0];
	target_moved.y += move.m128_f32[1];
	target_moved.z += move.m128_f32[2];

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::MoveTarget(const XMVECTOR& move)
{
	XMFLOAT3 target_moved = GetTarget();

	target_moved.x += move.m128_f32[0];
	target_moved.y += move.m128_f32[1];
	target_moved.z += move.m128_f32[2];

	SetTarget(target_moved);
}

void Camera::CurrentUpdate()
{
	viewDirtyFlag = false;
	

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	if (mouseMove.lX == CurretmouseX || mouseMove.lY == CurretmouseY)
	{
		
		float dy = (mouseMove.lX * scaleX) * 0.25;
		float dx = (mouseMove.lY * scaleY) * 0.25;

		angleX = -dx * XM_PI;
		angleY = -dy * XM_PI;

		viewDirtyFlag = true;
	}

	
	anglelimitX += angleX;
	anglelimitY += angleY;
	/*
	if (anglelimitX <= 1.4f && anglelimitX >= -1.4f)
	{
		angleculentX = anglelimitX;
	}
	else
	{
		anglelimitX = angleculentX;
	}*/

	//���W����
	if (!input->PushKey(DIK_A) && !input->PushKey(DIK_D)) Velocity.x = 0;
	if ((input->PushKey(DIK_A) || input->PushKey(DIK_D)))
	{

		if (input->PushKey(DIK_A)) Velocity.x = -0.3f;
		else
		{
			if (input->PushKey(DIK_D)) Velocity.x = 0.3f;
		}

		XMVECTOR move = { Velocity.x,Velocity.y,0,0 };

		move = XMVector3Transform(move, matRot);
		MoveTarget(move);
	}


	if (!input->PushKey(DIK_W) && !input->PushKey(DIK_S)) Velocity.z = 0;
	if ((input->PushKey(DIK_W) || input->PushKey(DIK_S)))
	{
		if (input->PushKey(DIK_S)) Velocity.z = -0.3f;
		else
		{
			if (input->PushKey(DIK_W)) Velocity.z = 0.3f;
		}


		XMVECTOR move = { 0,0,Velocity.z,0 };

		move = XMVector3Transform(move, matRot);
		MoveTarget(move);

	}

	
	if (viewDirtyFlag == true)
	{
		XMMATRIX matRotNew = XMMatrixIdentity();
		
		matRotNew*= XMMatrixRotationX(-anglelimitX);
		matRotNew*=XMMatrixRotationY(-anglelimitY);

		matRot = matRotNew;

		// �����_���王�_�ւ̃x�N�g���ƁA������x�N�g��
		XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };
		XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };
		// �x�N�g������]
		vTargetEye = XMVector3Transform(vTargetEye, matRot);
		vUp = XMVector3Transform(vUp, matRot);
		// �����_���炸�炵���ʒu�Ɏ��_���W������
		const XMFLOAT3& Target = GetTarget();
		
		SetEye({ Target.x + vTargetEye.m128_f32[0], Target.y + vTargetEye.m128_f32[1], Target.z + vTargetEye.m128_f32[2] });
		//SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });//����͎g�p����

	}



	//�C�x���g�̎��_�ړ��̓_
	std::vector<XMFLOAT3>points;

	//�Ō�ƏI����2����
	//eye�����distance��ǉ����ĕω�����
	points = {
		{eye.x             ,eye.y              ,eye.z             },
		{eye.x             ,eye.y              ,eye.z             },
		{eye.x             ,eye.y              ,eye.z + 0.1f      },
		{eye.x             ,eye.y              ,eye.z             },
		{eye.x             ,eye.y              ,eye.z             },
	};

	//����i�߂�
	TimeRate += 0.07f;

	//1�ȏア�����玟�ɐi�߂�
	if (TimeRate >= 1.0f)
	{
		if (startIndex < points.size() - 3)
		{
			if (startIndex != points.size() - 4)
			{
				startIndex += 1;
			}
			else
			{
				//�S�ẴX�v���C���Ȑ����ړ������玟�̃C�x���g
				startIndex = 1;
			}
			TimeRate -= 1.0f;
		}
		else
		{
			TimeRate = 1.0f;
		}
	}

	//�v�Z�����_�̍��W��target�̍��W�ɑ��
	XMFLOAT3 Eye_ = Physics::splinePosition(points, startIndex, TimeRate);

	SetEye(Eye_);

	Camera::Update(windows->window_width, windows->window_height);

}
