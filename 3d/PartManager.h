#pragma once
#include"fbxobj3d.h"
#include"../Collider/SphereCollider.h"


class PartManager : public FBXobj3d
{

public://�����o�֐�

	PartManager();
	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	//���ʂ̃p�[�e�B�N���̏�����
	void PartInitialize(XMFLOAT3 pos);

	//�e���̏�����
	void BullisticInitialize(XMFLOAT3& pos,XMVECTOR& Velocity,XMFLOAT3& angle);

	//�e���̏�����(�G)
	void BullisticInitializeEnemy(XMFLOAT3& pos, XMVECTOR& Velocity, XMFLOAT3& angle, int& num);

	//���ʂ̃p�[�e�B�N���̍X�V
	void PartUpdate();

	//�e���̍X�V
	void BullisticUpdate();
	void BullisticUpdateEnemy();

	const bool& Getdead() { return dead; }

	const int& Getbullisticnum() { return numbullistic; }

	//�����t���O��setter
	void Setdead(bool flag) { this->dead = flag; }


private:

	XMVECTOR Vel{0.0f,0.0f,0.0f};

	float G = -0.1f;//�d�͉����x

	//���ڂ̒e����
	int numbullistic = 0;

	//�����t���O
	bool dead = false;

	//�o�ߎ���
	float alivecount = 0;

	//���l�J�E���g�p�ϐ�
	int count = 0;

	//�ő厝������
	const float alivelimit = 60;



};

