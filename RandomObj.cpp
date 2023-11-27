#include "RandomObj.h"
#include "stdio.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include <fstream>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include"../Collider/BoxCollider.h"
#include "Physics.h"

RandomObj::RandomObj()
{
}

void RandomObj::RandomInitialize()
{
	//���ɂ̓t���O�������Ă���
	CreateObjTime += 1.0f;
	if (CreateObjTime == 300)
	{
		//�������ԏ�����
		CreateObjTime = 0.0f;
		//��������OBJ�����߂�
		RandomNumber = rand()%5;

		//����
		std::unique_ptr<RandomObj>randomObj = std::make_unique<RandomObj>();
		//������
		randomObj->Initialize();

		//�����_�����ɂ���Đ���
		if (RandomNumber == 0)
		{
			//�����Ń��f���̌`����Z�b�g
			randomObj->SetModel(meatmodel);
			//�R���W�����̃T�C�Y�o�^
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//�X�P�[���̃T�C�Y
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJ�̑���
			randomObj->collider->SetColor(COLLISION_COLOR_MEAT);

		}
		else if (RandomNumber == 1)
		{
			//�����Ń��f���̌`����Z�b�g
			randomObj->SetModel(tomatomodel);
			//�R���W�����̃T�C�Y�o�^
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//�X�P�[���̃T�C�Y
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJ�̑���
			randomObj->collider->SetColor(COLLISION_COLOR_TOMATO);

			for (int i = 0; i < 3; i++)
			{
				//����
				std::unique_ptr<RandomObj>childObj = std::make_unique<RandomObj>();
				//������
				childObj->Initialize();

				if (i == 0)
				{
					//�q����
					childObj->SetModel(tomatomodel2);
					childObj->SetPosition({ 0,0,100 });
					childObj->SetScale({ 0.01f,0.01f,0.01f });
					ChildObjs.push_back(std::move(childObj));
				}
				else if(i == 1)
				{
					childObj->SetModel(tomatomodel3);
					childObj->SetPosition({ 0,0,100 });
					childObj->SetScale({ 0.01f,0.01f,0.01f });
					ChildObjs.push_back(std::move(childObj));
				}
				else if(i == 2)
				{
					childObj->SetModel(tomatomodel4);
					childObj->SetPosition({ 0,0,100 });
					childObj->SetScale({ 0.01f,0.01f,0.01f });
					ChildObjs.push_back(std::move(childObj));
				}
			}
			

		}
		else if (RandomNumber == 2)
		{
			//�����Ń��f���̌`����Z�b�g
			randomObj->SetModel(retasumodel);
			//�R���W�����̃T�C�Y�o�^
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//�X�P�[���̃T�C�Y
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJ�̑���
			randomObj->collider->SetColor(COLLISION_COLOR_RETASU);

			//����
			std::unique_ptr<RandomObj>childObj = std::make_unique<RandomObj>();
			//������
			childObj->Initialize();

			childObj->SetModel(retasumodel2);
			childObj->SetPosition({ 0,0,100 });
			childObj->SetScale({ 0.01f,0.01f,0.01f });
			ChildObjs.push_back(std::move(childObj));

		}
		else if (RandomNumber == 3)
		{
			//�����Ń��f���̌`����Z�b�g
			randomObj->SetModel(tirzumodel);
			//�R���W�����̃T�C�Y�o�^
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//�X�P�[���̃T�C�Y
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJ�̑���
			randomObj->collider->SetColor(COLLISION_COLOR_TIRZU);

		}
		else if (RandomNumber == 4)
		{
			//�����Ń��f���̌`����Z�b�g
			randomObj->SetModel(kutusitamodel);
			//�R���W�����̃T�C�Y�o�^
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//�X�P�[���̃T�C�Y
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJ�̑���
			randomObj->collider->SetColor(COLLISION_COLOR_KUTUSITA);

		}
	
		//�|�W�V�����̏����ʒu�ݒ�
		randomObj->SetPosition({ 0,0,100 });

		//OBJ�̉�]�ݒ�
		float RandomRotationZ= rand()%90+(-45);

	//	float RandomRotationZ = rand() % 45 + (-45);


		randomObj->SetRotation({ 0,0,RandomRotationZ });

		randomObj->SetCanGetFlag(true);
		//�R���W�����̑����w��
		//fence->SetFbxVer(block_ver);
		
		randomObj->RandomHalfway_X = rand() % 100 + (-50);
		randomObj->RandomHalfway_Y = rand() % 100 + (-50);
		//�o�^
		Objs.push_back(std::move(randomObj));
	}
}

void RandomObj::RandomDraw(ID3D12GraphicsCommandList* cmdList)
{
	//�`�悷��
	for (std::unique_ptr<RandomObj>& Obj_ : Objs) {
		if(Obj_->GetCanGetFlag()==true)Obj_->Draw(cmdList);
	}

	for (std::unique_ptr<RandomObj>& childObj_ : ChildObjs) {
		childObj_->Draw(cmdList);
	}

}

void RandomObj::RandomUpdate()
{
	//�X�V
	for (std::unique_ptr<RandomObj>& Obj_ : Objs) {

		//�ړ��̓_
	    std::vector<XMFLOAT3>points;

		//�Ō�ƏI����2����
		//eye�����distance��ǉ����ĕω�����
		points = {
			{0                            ,3.5                             ,100                            },
            {0                            ,3.5                             ,100                            },
           // {0        ,0         ,50                             },
			//{0                            ,0                             ,-2                             },
			{BunsPosition.x               ,3.5                ,4.0f               },
            {BunsPosition.x               ,3.5                ,4.0f               },
		};

		//����i�߂�
		Obj_->TimeRate += 0.01f;

		bool LostFlag = false;

		//1�ȏア�����玟�ɐi�߂�
		if (Obj_->TimeRate >= 1.0f)
		{
			if (Obj_->startIndex < points.size() - 3)
			{
				if (Obj_->startIndex != points.size() - 4)
				{
					Obj_->startIndex += 1;
				}
				else
				{
					//�S�ẴX�v���C���Ȑ����ړ������玟�̃C�x���g
					Obj_->SetCanGetFlag(false);

					//�폜�t���O�������Ă���̂Ȃ�OBJ���폜
					//Obj_.release();
				}
				Obj_->TimeRate -= 1.0f;
			}
			else
			{
				Obj_->TimeRate = 1.0f;

				Obj_->SetCanGetFlag(false);

				LostFlag = true;
				
			}
		}

		//�v�Z�����_�̍��W��target�̍��W�ɑ��
		XMFLOAT3 Eye_ = Physics::splinePosition(points, Obj_->startIndex, Obj_->TimeRate);

		Obj_->SetPosition(Eye_);

		for (std::unique_ptr<RandomObj>& childObj_ : ChildObjs) {
			childObj_->SetPosition(Eye_);
			childObj_->SetRotation(Obj_->GetRotation());
			childObj_->Update();
		}

		if (LostFlag == true)
		{
			ChildObjs.clear();
		}

		Obj_->Update();

	}

}
