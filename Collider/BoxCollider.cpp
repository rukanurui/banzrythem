#include"BoxCollider.h"

using namespace DirectX;

void BoxCollider::Update()
{
	//���[���h�s�񂩂���W�𒊏o
	const XMMATRIX& matWorld = fbxobject->GetMatWorld();

	//�����̂̃����o�ϐ����X�V
	Box::center = matWorld.r[3];
	
	Box::radius = radius;

	Box::minpos.m128_f32[0] = center.m128_f32[0] - offset.m128_f32[0];
	Box::minpos.m128_f32[1] = center.m128_f32[1] - offset.m128_f32[1];
	Box::minpos.m128_f32[2] = center.m128_f32[2] - offset.m128_f32[2];

	Box::maxpos.m128_f32[0] = center.m128_f32[0] + offset.m128_f32[0];
	Box::maxpos.m128_f32[1] = center.m128_f32[1] + offset.m128_f32[1];
	Box::maxpos.m128_f32[2] = center.m128_f32[2] + offset.m128_f32[2];

}
