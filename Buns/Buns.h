#pragma once
#include "../3d/fbxobj3d.h"
#include"../Collider/BoxCollider.h"

class Buns : public FBXobj3d
{
public:
	Buns(Input* Input);

	//������
	void BunsInitialize(bool Flag);
	//�X�V
	void BunsUpdate();
	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	//�Q�b�^�[�A�Z�b�^�[
	XMVECTOR GetUpVector() { return upVel; }

	XMVECTOR GetDownVector() { return downVel; }


private:
	//�|�C���^
	Input* input = nullptr;

	//��ɍs����
	bool Upflag = false;

	bool Reverse = false;

	bool Push = false;

	XMFLOAT3 OldPosition= { 0.0f,0.0f,0.0f };

	//��Ɖ��ւ̑��x
	XMVECTOR Velocity = { 0.0f,0.0f,0.0f };
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

};
