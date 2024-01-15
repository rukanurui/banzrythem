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

	void SetUpSandPoint(bool point) { UpSandPoint = point; }

	void SetUnderSandPoint(bool point) { UnderSandPoint = point; }


	void SetSandType(int type) { SandType = type; }

	void SetPerfect(bool i) { perfect = i; }

	void SetIngredientsRotation(XMFLOAT3 rotation) { IngredientsRotation = rotation; }
	void SetBunsUpRotation(XMFLOAT3 rotation) { BunsUpRotation = rotation; }
	void SetBunsDownRotation(XMFLOAT3 rotation) { BunsDownRotation = rotation; }


	//getter
	int GetScore() { return Score; }

	bool GetSandWitch() { return SandWitch; }

	int GetCombo() { return combo; }

	int GetComboTime() { return combotime; }

	int GetComboFlag() { return comoboflag; }

	int GetType() { return type; }
private:

	int Score = 0;

	bool UpSandPoint = false;

	bool UnderSandPoint = false;

	bool SandWitch = false;

	int SandType = 0;

	int Time=0;

	int combo = 0;

	int combotime = 0;

	int comoboflag = 0;

	int type = 0;

	bool perfect = false;

	XMFLOAT3 IngredientsRotation = {0,0,0};

	XMFLOAT3 BunsUpRotation = { 0,0,0 };

	XMFLOAT3 BunsDownRotation = { 0,0,0 };
};

