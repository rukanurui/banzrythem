#pragma once
#include "../3d/fbxobj3d.h"
#include"../Collider/BoxCollider.h"

class Buns : public FBXobj3d
{
public:
	Buns(Input* Input);

	//初期化
	void BunsInitialize(bool Flag);
	//更新
	void BunsUpdate();
	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info)override;

	//ゲッター、セッター
	XMVECTOR GetUpVector() { return upVel; }

	XMVECTOR GetDownVector() { return downVel; }


private:
	//ポインタ
	Input* input = nullptr;

	pad* pad_ = nullptr;

	//上に行くか
	bool Upflag = false;

	bool Reverse = false;

	bool Push = false;

	XMFLOAT3 OldPosition= { 0.0f,0.0f,0.0f };

	//上と下への速度
	XMVECTOR Velocity = { 0.0f,0.0f,0.0f };
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

};
