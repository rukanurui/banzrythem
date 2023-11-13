#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class ScoreManager
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	void Update();

	void AddSandPoint(int point) { SandPoint += point; }

	void SetIngredientsRotation(XMFLOAT3 rotation) { IngredientsRotation = rotation; }
	void SetBunsUpRotation(XMFLOAT3 rotation) { BunsUpRotation = rotation; }
	void SetBunsDownRotation(XMFLOAT3 rotation) { BunsDownRotation = rotation; }


private:

	int Score = 0;

	int SandPoint = 0;

	XMFLOAT3 IngredientsRotation = {0,0,0};

	XMFLOAT3 BunsUpRotation = { 0,0,0 };

	XMFLOAT3 BunsDownRotation = { 0,0,0 };



};

