#include"PlaneCollider.h"

using namespace DirectX;

void PlaneCollider::Update()
{
	//���[���h�s�񂩂���W�𒊏o
	const XMMATRIX& matWorld = fbxobject->GetMatWorld();

	//���̃����o�ϐ����X�V
	Plane::normal = matWorld.r[3] + offset;
	Plane::distance = distance;
}