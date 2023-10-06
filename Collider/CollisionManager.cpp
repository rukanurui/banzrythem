#include "CollisionManager.h"
#include"BaseCollider.h"
#include"Collision.h"

using namespace DirectX;

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	//�S�Ă̑g�ݍ��킹�ɂ��đ�������`�F�b�N
	itA = colliders.begin();
	for (;itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			//�Ƃ��ɋ�
			 if (colA->GetShapeType()==COLLISIONSHAPE_SPHERE&&
				colB->GetShapeType()==COLLISIONSHAPE_SPHERE)
			{
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}

			 //���ƒ�����
			 if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				 colB->GetShapeType() == COLLISIONSHAPE_BOX)
			 {

				 Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				 Box* BoxB = dynamic_cast<Box*>(colB);
				 DirectX::XMVECTOR inter;

				 if (Collision::CheckSphere2Box(*SphereA, *BoxB, &inter))
				 {
					 colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					 colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				 }
			 }

			//���ƒ����̔���
			else if (colA->GetShapeType() == COLLISIONSHAPE_BOX &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE)
			{
				Box* BoxA = dynamic_cast<Box*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Box(*SphereB, *BoxA, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}

		}
	}
}

void CollisionManager::CheckQuerySphere(const Sphere& sphere, QueryCallback* callback,unsigned short color)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	//���ׂẴR���C�_�[�Ƒ�������`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		//����������Ȃ���΃X�L�b�v
		if (!(col->color&color))
		{
			continue;
		}

		//���̏ꍇ
		if (col->GetShapeType() == COLLISIONSHAPE_SPHERE)
		{

			Sphere* sphereB = dynamic_cast<Sphere*>(col);
			XMVECTOR tempInter;
			XMVECTOR tempReject;

			//������Ȃ���Ώ��O
			if (!Collision::CheckSphere2Sphere(sphere, *sphereB, &tempInter, &tempReject))continue;

			//���������Z�b�g
			QueryHit info;
			info.collider = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			//�N�G���\�R�[���o�b�N�Ăяo��
			if (!callback->OnQueryHit(info))
			{
				//�߂�l��false�̏ꍇ�I��
				return;
			}
		}
		//���̓����蔻��
	}

}

void CollisionManager::CheckQueryBox(const Sphere& sphere, QueryCallback* callback, unsigned short color)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	//���ׂẴR���C�_�[�Ƒ�������`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		//����������Ȃ���΃X�L�b�v
		if (!(col->color & color))
		{
			continue;
		}

		//��`�̏ꍇ
		if (col->GetShapeType() == COLLISIONSHAPE_BOX)
		{

			Box* box = dynamic_cast<Box*>(col);
			XMVECTOR tempInter;
			XMVECTOR tempReject;

			//������Ȃ���Ώ��O
			if (!Collision::CheckSphere2Box(sphere, *box, &tempInter, &tempReject))continue;

			//���������Z�b�g
			QueryHit info;
			info.collider = col;
			info.object = col->GetObject3d();
			info.inter = tempInter;
			info.reject = tempReject;

			//�N�G���\�R�[���o�b�N�Ăяo��
			if (!callback->OnQueryHit(info))
			{
				//�߂�l��false�̏ꍇ�I��
				return;
			}
		}
		//���̓����蔻��
	}

}

void CollisionManager::CheckBoxShere() 
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	//�S�Ă̑g�ݍ��킹�ɂ��đ�������`�F�b�N
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;
			//���ƒ�����
			if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_BOX)
			{
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Box* BoxB = dynamic_cast<Box*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Box(*SphereA, *BoxB, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
			}
			/*else if(colA->GetShapeType() == COLLISIONSHAPE_BOX &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE)
			{
				Box* BoxA = dynamic_cast<Box*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				DirectX::XMVECTOR inter;
				if (Collision::CheckSphere2Box(*SphereA, *BoxB, &inter)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}

			}*/

		}
	}

}

bool CollisionManager::RayCast(const Ray& ray, RayCastHit* hitinfo, float MaxDistance)
{
	bool result = false;
	//�����p�̃C�e���[�^�[
	std::forward_list<BaseCollider*>::iterator it;
	//���܂łōł��߂��R���C�_�[���L�^���邽�߂̃C�e���[�^�[
	std::forward_list<BaseCollider*>::iterator it_hit;
	//���܂łōł��߂��R���C�_�[�Ƃ̋������L�^���邽�߂̃C�e���[�^�[
	float distance = MaxDistance;
	//���܂łōł��߂��R���C�_�[�Ƃ̌�_���L�^���邽�߂̃C�e���[�^�[
	XMVECTOR inter;
	//���ׂẴR���C�_�[�Ƒ�������`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;
		//���̏ꍇ
		if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);
			float tempDistance;
			XMVECTOR tempInter;
			//������Ȃ���Ώ��O
			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter))continue;
			//�������ŏ��łȂ���Ώ��O
			if (tempDistance >= distance)continue;
			//���܂łōł��������߂��̂Ŕ�����Ƃ�
			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
		//���̓����蔻��
	}
	//�ŏI�I�ɉ����ɓ������Ă��猋�ʂ���������
	if (result&&hitinfo)
	{
		hitinfo->distance = distance;
		hitinfo->inter = inter;
		hitinfo->collider = *it_hit;
		hitinfo->object = hitinfo->collider->GetObject3d();
	}
	return result;
}
