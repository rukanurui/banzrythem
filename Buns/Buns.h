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

	void BunsCollisionColorSet();

	//ゲッター、セッター
	XMVECTOR GetUpVector() { return upVel; }

	XMVECTOR GetDownVector() { return downVel; }

	int GetSand() { return Sandwich; }

	int GetSandAttribute() { return SandAttribute; }

	bool GetPerfect() { return perfect; }

	XMFLOAT3 GetIngredientsRotation() { return IngredientsRotation; }

	void SetEndSand(bool flag) { EndSand = flag; }

	void SetSandAttribute(int flag) { SandAttribute = flag; }

private:
	//ポインタ
	Input* input = nullptr;

	//上に行くか
	bool Upflag = false;

	bool Reverse = false;

	bool Push = false;

	bool Sandwich = 0;

	bool EndSand = false;

	bool perfect = false;

	int SandAttribute = 0;

	int SandTime = 0;

	XMFLOAT3 IngredientsRotation;

	float circle_time = 0.0f;

	XMFLOAT3 OldPosition= { 0.0f,0.0f,0.0f };

	//上と下への速度
	XMVECTOR Velocity = { 0.0f,0.0f,0.0f };
	XMVECTOR upVel = { 0.0f,0.0f,0.0f };
	XMVECTOR downVel = { 0.0f,0.0f,0.0f };

	XMVECTOR Accumulation = { 0.0f,0.0f,0.0f };
};
