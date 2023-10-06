#pragma once
#include<DirectXMath.h>


class FBXobj3d;
class BaseCollider;

//�Փˏ��
struct CollisionInfo

{
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	CollisionInfo(FBXobj3d* object, BaseCollider* collider, const XMVECTOR& inter)
	{
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	//�Փˑ���̃I�u�W�F�N�g
	FBXobj3d* object = nullptr;
	//�Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	//�Փ˓_
	XMVECTOR inter;

};

