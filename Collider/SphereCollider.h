#pragma once
#include"BaseCollider.h"
#include"CollisionPrimitive.h"
#include<DirectXMath.h>

//���Փ˔���
class SphereCollider:public BaseCollider,public Sphere
{
private://�G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	SphereCollider(XMVECTOR offset ={ 0,0,0,0 }, float radius = 1.0f) :
		offset(offset),
		radius(radius)
	{
		//���`��
		shapeType = COLLISIONSHAPE_SPHERE;
	}

		//�X�V
	void Update()override;

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	//�I�u�W�F�N�g���S����̃I�t�Z�b�g
	XMVECTOR offset;
	//���a
	float radius;
};

