#pragma once
#include "../3d/FBXobj3d.h"
#include"../Collider/BoxCollider.h"

class Buns : public FBXobj3d
{
public:
	Buns();
	~Buns();

	//初期化
	void BunsInitialize();
	//更新
	void BunsUpdate();
	//描画
	void Draw();
	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

private:
	//ポインタ
	Input* input = nullptr;

	//上と下への速度
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

};
