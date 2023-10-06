#include "PlayerCol.h"
#include"QueryCallback.h"
#include"CollisionManager.h";

PlayerCol::PlayerCol()
{

}

void PlayerCol::OnCollision(const CollisionInfo& info)
{
	if (info.collider->color == 8 || info.collider->color == 16)
	{
		hit = 1;
	}

	if (info.collider->color == 1)
	{
		//���R���C�_�[�擾
		SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
		assert(sphereCollider);

		class PlayerQueryCallback :public QueryCallback
		{
		public:
			PlayerQueryCallback(Sphere* sphere) :sphere(sphere) {};

			//�Փˎ��R�[���o�b�N�֐�
			bool OnQueryHit(const QueryHit& info)
			{
				//���[���h�̏����
				const XMVECTOR up = { 0,1,0,0 };
				//�r�˕���
				XMVECTOR rejectDir = XMVector3Normalize(info.reject);
				//������ƍ��E�����̊p�x���̃R�T�C���l
				float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

				//�����o������
				sphere->center += info.reject;
				move += info.reject;

				return true;
			}
			//�N�G���\�Ɏg�p���鋅
			Sphere* sphere = nullptr;
			//�r�˂ɂ��ړ���(�ݐ�)
			XMVECTOR move = {};
		};

		//�N�G���\�R�[���o�b�N�̊֐��I�u�W�F�N�g
		PlayerQueryCallback callback(sphereCollider);

		//�G�ƓG�̌���������
		CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
		//�����ɂ��r�˕�������
		position.x += callback.move.m128_f32[0];
		position.y += callback.move.m128_f32[1];
		position.z += callback.move.m128_f32[2];
	}

	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	
}

void PlayerCol::colUpdate()
{

	if (hit==0)
	{
		//���R���C�_�[�擾
		SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
		assert(sphereCollider);

		class PlayerQueryCallback :public QueryCallback
		{
		public:
			PlayerQueryCallback(Sphere* sphere) :sphere(sphere) {};

			//�Փˎ��R�[���o�b�N�֐�
			bool OnQueryHit(const QueryHit& info)
			{
				//���[���h�̏����
				const XMVECTOR up = { 0,1,0,0 };
				//�r�˕���
				XMVECTOR rejectDir = XMVector3Normalize(info.reject);
				//������ƍ��E�����̊p�x���̃R�T�C���l
				float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

				//�����o������
				sphere->center += info.reject;
				move += info.reject;

				return true;
			}
			//�N�G���\�Ɏg�p���鋅
			Sphere* sphere = nullptr;
			//�r�˂ɂ��ړ���(�ݐ�)
			XMVECTOR move = {};
		};

		//�N�G���\�R�[���o�b�N�̊֐��I�u�W�F�N�g
		PlayerQueryCallback callback(sphereCollider);

		//�G�ƓG�̌���������
		CollisionManager::GetInstance()->CheckQuerySphere(*sphereCollider, &callback, COLLISION_COLOR_LANDSHAPE);
		//�����ɂ��r�˕�������
		position.x += callback.move.m128_f32[0];
		position.y += callback.move.m128_f32[1];
		position.z += callback.move.m128_f32[2];
	}
	
	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}

}



void PlayerCol::ColInitialize()
{
	//�����̒ǉ�
	collider->SetColor(COLLISION_COLOR_PLAYER);
}
