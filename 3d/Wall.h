#pragma once
#include"fbxobj3d.h"
#include"../Collider/BoxCollider.h"
#include"../Collider/CollisionColor.h"

class Wall : public FBXobj3d
{

public:

	Wall();

	void WallInitialize();

	void objgunInitialize();

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info)override;

	//�e�̃t���O
	const int& Gethave() { return infohave; }
	void Sethave(bool Have);

	const int die = 1;

private:

	bool infohave = false;

};