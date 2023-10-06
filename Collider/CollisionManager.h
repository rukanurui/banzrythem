#pragma once
#include"CollisionPrimitive.h"
#include"RayCastHit.h"
#include"QueryCallback.h"

#include<d3d12.h>
#include<forward_list>

class BaseCollider;

class CollisionManager
{
public://�ÓI�����o�ϐ�
	static CollisionManager* GetInstance();

public://�����o�֐�
	//�R���C�_�[�̒ǉ�
	inline void ADDCollider(BaseCollider* collider) {
		colliders.push_front(collider);
	}

	//�R���C�_�[�̍폜
	inline void RemoveCollider(BaseCollider* collider) {
		colliders.remove(collider);
	}

	//�S�Ă̏Փ˃`�F�b�N
	void CheckAllCollisions();

	//�R�[���o�b�N�p�̏Փ˃`�F�b�N(��)
	void CheckQuerySphere(const Sphere& sphere,QueryCallback* callback,unsigned short color = (unsigned short)0xffffffff);

	//�R�[���o�b�N�p�̏Փ˃`�F�b�N(AABB)
	void CheckQueryBox(const Sphere& sphere, QueryCallback* callback, unsigned short color = (unsigned short)0xffffffff);

	//���C�Ƃ��ׂẴR���C�_�[�Ƃ̏Փ˔���
	bool RayCast(const Ray& ray, RayCastHit* hitinfo = nullptr, float MaxDistance = D3D12_FLOAT32_MAX);

	void CheckBoxShere();

	//���ʂƋ��̃R���C�_�[�Ƃ̏Փ˔���


private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = delete;
	//�R���C�_�[�̃��X�g
	std::forward_list<BaseCollider*> colliders;
};

