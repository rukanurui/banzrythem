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
	//作るにはフラグが立ってから
	CreateObjTime += 1.0f;
	if (CreateObjTime == 300)
	{
		//生成時間初期化
		CreateObjTime = 0.0f;
		//生成するOBJを決める
		RandomNumber = rand()%5;

		//生成
		std::unique_ptr<RandomObj>randomObj = std::make_unique<RandomObj>();
		//初期化
		randomObj->Initialize();

		//ランダム数によって生成
		if (RandomNumber == 0)
		{
			//ここでモデルの形状をセット
			randomObj->SetModel(meatmodel);
			//コリジョンのサイズ登録
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//スケールのサイズ
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJの属性
			randomObj->collider->SetColor(COLLISION_COLOR_MEAT);

		}
		else if (RandomNumber == 1)
		{
			//ここでモデルの形状をセット
			randomObj->SetModel(tomatomodel);
			//コリジョンのサイズ登録
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//スケールのサイズ
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJの属性
			randomObj->collider->SetColor(COLLISION_COLOR_TOMATO);

			for (int i = 0; i < 3; i++)
			{
				//生成
				std::unique_ptr<RandomObj>childObj = std::make_unique<RandomObj>();
				//初期化
				childObj->Initialize();

				if (i == 0)
				{
					//子生成
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
			//ここでモデルの形状をセット
			randomObj->SetModel(retasumodel);
			//コリジョンのサイズ登録
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//スケールのサイズ
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJの属性
			randomObj->collider->SetColor(COLLISION_COLOR_RETASU);

			//生成
			std::unique_ptr<RandomObj>childObj = std::make_unique<RandomObj>();
			//初期化
			childObj->Initialize();

			childObj->SetModel(retasumodel2);
			childObj->SetPosition({ 0,0,100 });
			childObj->SetScale({ 0.01f,0.01f,0.01f });
			ChildObjs.push_back(std::move(childObj));

		}
		else if (RandomNumber == 3)
		{
			//ここでモデルの形状をセット
			randomObj->SetModel(tirzumodel);
			//コリジョンのサイズ登録
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//スケールのサイズ
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJの属性
			randomObj->collider->SetColor(COLLISION_COLOR_TIRZU);

		}
		else if (RandomNumber == 4)
		{
			//ここでモデルの形状をセット
			randomObj->SetModel(kutusitamodel);
			//コリジョンのサイズ登録
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,1.0f,2.5f,0 }, 1.0f));
			//スケールのサイズ
			randomObj->SetScale({ 0.01f,0.01f,0.01f });
			//OBJの属性
			randomObj->collider->SetColor(COLLISION_COLOR_KUTUSITA);

		}
	
		//ポジションの初期位置設定
		randomObj->SetPosition({ 0,0,100 });

		//OBJの回転設定
		float RandomRotationZ= rand()%90+(-45);

	//	float RandomRotationZ = rand() % 45 + (-45);


		randomObj->SetRotation({ 0,0,RandomRotationZ });

		randomObj->SetCanGetFlag(true);
		//コリジョンの属性指定
		//fence->SetFbxVer(block_ver);
		
		randomObj->RandomHalfway_X = rand() % 100 + (-50);
		randomObj->RandomHalfway_Y = rand() % 100 + (-50);
		//登録
		Objs.push_back(std::move(randomObj));
	}
}

void RandomObj::RandomDraw(ID3D12GraphicsCommandList* cmdList)
{
	//描画する
	for (std::unique_ptr<RandomObj>& Obj_ : Objs) {
		if(Obj_->GetCanGetFlag()==true)Obj_->Draw(cmdList);
	}

	for (std::unique_ptr<RandomObj>& childObj_ : ChildObjs) {
		childObj_->Draw(cmdList);
	}

}

void RandomObj::RandomUpdate()
{
	//更新
	for (std::unique_ptr<RandomObj>& Obj_ : Objs) {

		//移動の点
	    std::vector<XMFLOAT3>points;

		//最後と終わりは2つずつ
		//eyeを基準にdistanceを追加して変化する
		points = {
			{0                            ,3.5                             ,100                            },
            {0                            ,3.5                             ,100                            },
           // {0        ,0         ,50                             },
			//{0                            ,0                             ,-2                             },
			{BunsPosition.x               ,3.5                ,4.0f               },
            {BunsPosition.x               ,3.5                ,4.0f               },
		};

		//時を進める
		Obj_->TimeRate += 0.01f;

		bool LostFlag = false;

		//1以上いったら次に進める
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
					//全てのスプライン曲線を移動したら次のイベント
					Obj_->SetCanGetFlag(false);

					//削除フラグが立っているのならOBJを削除
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

		//計算した点の座標をtargetの座標に代入
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
