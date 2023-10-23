#pragma once
#include "../3d/FBXobj3d.h"
#include"../Collider/BoxCollider.h"

class Buns : public FBXobj3d
{
public:
	Buns();
	~Buns();

	//������
	void BunsInitialize();
	//�X�V
	void BunsUpdate();
	//�`��
	void Draw();
	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

private:
	//�|�C���^
	Input* input = nullptr;

	//��Ɖ��ւ̑��x
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

};
