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
		RandomNumber = 0;

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
			randomObj->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,0.7f,1.0f,0 }, 1.0f));
			//スケールのサイズ
			randomObj->SetScale({ 0.01,0.01,0.01 });
		}

	
		//ポジションの初期位置設定
		randomObj->SetPosition({ 0,0,100 });

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
		Obj_->Draw(cmdList);
	}
}

void RandomObj::RandomUpdate()
{
	//更新
	for (std::unique_ptr<RandomObj>& Obj_ : Objs) {

		//移動の点
	    std::vector<XMFLOAT3>points;

		float RandomHalfway_X = rand() % 100 + (-50);
		float RandomHalfway_Y = rand() % 100 + (-50);
		//最後と終わりは2つずつ
		//eyeを基準にdistanceを追加して変化する
		points = {
			{0                            ,0                             ,100                            },
            {0                            ,0                             ,100                            },
            {Obj_->RandomHalfway_X        ,Obj_->RandomHalfway_Y         ,50                             },
			{0                            ,0                             ,-2                             },
			{BunsPosition.x               ,BunsPosition.y                ,BunsPosition.z-2               },
            {BunsPosition.x               ,BunsPosition.y                ,BunsPosition.z-2               },
		};

		//時を進める
		Obj_->TimeRate += 0.01f;

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
			}
		}

		//計算した点の座標をtargetの座標に代入
		XMFLOAT3 Eye_ = Physics::splinePosition(points, Obj_->startIndex, Obj_->TimeRate);

		Obj_->SetPosition(Eye_);

		Obj_->Update();



	}

}
