#include "PartManager.h"
#include"../Collider/QueryCallback.h"
#include "../Collider/CollisionManager.h"

PartManager::PartManager()
{
}

void PartManager::PartInitialize(XMFLOAT3 pos)
{

	position = pos;

	srand(rand());
	int pcount = rand() % 10 + 1;

	Vel.m128_f32[0] = (float)rand() / RAND_MAX;
	Vel.m128_f32[1] = (float)rand() / RAND_MAX;
	Vel.m128_f32[2] = (float)rand() / RAND_MAX;

	//������ݒ�
	if (pcount >= 4)
	{
		Vel.m128_f32[0] *= -1;
	}
	if (pcount % 2 == 0)
	{
		Vel.m128_f32[1] *= -1;
	}
	if (pcount % 2 == 1)
	{
		Vel.m128_f32[2] *= -1;
	}

	//�R���C�_�[�̑����ݒ�
	collider->SetColor(COLLISION_COLOR_PART);
}

void PartManager::BullisticInitialize(XMFLOAT3& pos,XMVECTOR& Velocity,XMFLOAT3& angle)
{

	position = pos;

	//angle�ɂ�����萔�l
	const int reverveangle = 55;

	//�e�̃x�N�g������
	Vel = Velocity;

	rotation.y = angle.y * reverveangle;
	rotation.x = angle.x * -reverveangle;
	
	//�R���C�_�[�̑����ݒ�
	collider->SetColor(COLLISION_COLOR_PART);
}

void PartManager::BullisticInitializeEnemy(XMFLOAT3& pos, XMVECTOR& Velocity, XMFLOAT3& angle, int& num)
{

	numbullistic = num;

	position = pos;

	//angle�ɂ�����萔�l
	const int reverveangle = 58;

	//�e�̃x�N�g������
	Vel = Velocity;

	rotation.y = angle.y * reverveangle;
	//rotation.x = angle.x * -55;

	//�R���C�_�[�̑����ݒ�
	collider->SetColor(COLLISION_COLOR_PART);
}

void PartManager::OnCollision(const CollisionInfo& info)
{

}

void PartManager::PartUpdate()
{
	
	//�d�͉��Z
	G -= 0.01f;
	if (G <= -0.1f)
	{
		G = -0.1f;
	}
	
	Vel.m128_f32[1] += G;
	
	//���W�ύX
	position.x += Vel.m128_f32[0];
	position.y += Vel.m128_f32[1];
	position.z += Vel.m128_f32[2];
	
	
	//�n�ʊђʂ��Ȃ��悤��
	if (position.y <= 0)
	{
		position.y = 0;
	}

	//�o�����ԃJ�E���g
	alivecount++;

	//1�b�o�߂�����
	if (alivecount >= alivelimit)
	{
		dead = true;
	}
	
	
	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;
	
	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);
	
	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f
	
	//��������J����
	//�r���[�v���W�F�N�V�����s��
	const XMMATRIX& matViewProjection =
		camera->GetViewProjectionMatrix();
	//���f���̃��b�V���g�����X�t�H�[��
	const XMMATRIX& modelTransform = fbxmodel->GetModelTransform();
	//�J�������W
	const XMFLOAT3& camerapos = camera->GetEye();
	
	//�A�j���[�V����
	if (isPlay) {
		//1�t���[���i�߂�
		currentTime += frameTime;
		//�Ō�܂ōĐ�������擪�ɖ߂�
		if (currentTime > endTime) {
			currentTime = startTime;
		}
	}
	
	//�{�[���z��
	std::vector<FbxModel::Bone>& bones = fbxmodel->GetBones();
	
	// �X�L���̒萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataSkin* constMapSkin = nullptr;
	result = constBuffSkin->Map(0, nullptr, (void**)&constMapSkin);
	for (int i = 0; i < bones.size(); i++)
	{
		//���̎p���s��
		XMMATRIX matCurrentPose;
		//���̎p���s����擾
		FbxAMatrix fbxCurrentPose =
			bones[i].fbxCluster->GetLink()->EvaluateGlobalTransform(currentTime);
		//XMMATRIX�ɕϊ�
		FbxLoader::ConvertMatrixFromFbx(&matCurrentPose, fbxCurrentPose);
		//�������ăX�L�j���O�s���
		constMapSkin->bones[i] = bones[i].invInitialPose * matCurrentPose;
	}
	constBuffSkin->Unmap(0, nullptr);
	
	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataTransform* constMap = nullptr;
	result = constBufferTransform->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->viewproj = matViewProjection;
		constMap->world = modelTransform * matWorld;
		constMap->camerapos = camerapos;
		constBufferTransform->Unmap(0, nullptr);
	}

}

void PartManager::BullisticUpdate()
{

	const int wait = 15;
	count++;

	if (count>=wait)
	{
		//position��ς���
		position.x += Vel.m128_f32[0];
		position.y += Vel.m128_f32[1];
		position.z += Vel.m128_f32[2];
		//���W�X�V
		UpdateWorld();
	}
	else
	{
		//�X�P�[����L�΂�
		MoveScaleZ(Vel.m128_f32[2] * 0.01);
		//���W�X�V
		UpdateWorld();
	}
}

void PartManager::BullisticUpdateEnemy()
{
	const int wait = 45;
	count++;

	if (count >= wait)
	{
		//position��ς���
		position.x += Vel.m128_f32[0];
		position.y += Vel.m128_f32[1];
		position.z += Vel.m128_f32[2];
		//���W�X�V
		UpdateWorld();
	}
	else
	{
		//�X�P�[����L�΂�
		MoveScaleZ(Vel.m128_f32[2] * 0.01);
		//���W�X�V
		UpdateWorld();
	}
}



