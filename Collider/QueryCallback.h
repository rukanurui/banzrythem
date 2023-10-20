#pragma once
#include<DirectXMath.h>

class FBXobj3d;
class BaseCollider;

//�N�G���[�ɂ����𓾂邽�߂̍\����
struct QueryHit
{
	//�Փˑ���̃I�u�W�F�N�g
	FBXobj3d* object = nullptr;
	//�Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	//�Փ˓_
	DirectX::XMVECTOR inter;
	//�r�˃x�N�g��
	DirectX::XMVECTOR reject;
};

class QueryCallback
{
public:
	QueryCallback() = default;
	virtual~QueryCallback() = default;

	//�������R�[���o�b�N
	virtual bool OnQueryHit(const QueryHit& info) = 0;
};