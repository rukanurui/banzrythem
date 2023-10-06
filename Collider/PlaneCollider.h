#pragma once
#include"BaseCollider.h"
#include"CollisionPrimitive.h"
#include<DirectXMath.h>

class PlaneCollider :public BaseCollider, public Plane
{
private://�G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlaneCollider(XMVECTOR offset = { 0,0,0,0 }) :
		offset(offset)
	{
		//����
		shapeType = COLLISIONSHAPE_PLANE;
	}

	//�X�V
	void Update()override;



private:
	//�I�u�W�F�N�g���S����̃I�t�Z�b�g
	XMVECTOR offset;

};