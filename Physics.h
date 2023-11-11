#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include "Math.h"
#include <vector>
#include <DirectXMath.h>

#define PI 3.1415926535897932384626433832795
#define LENGTH      200                 // �R�̒���
#define CLENGTH     (LENGTH * 2 * PI)   // �R��L�΂��Ĉ���������ꍇ�ɏo����~�̉~���̒���
#define MASS        0.1346              //���̎���
#define G           9.81                // �d�͉����x


class Physics
{
protected:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	Physics();
	//�X�v���C���Ȑ�
	static XMFLOAT3 splinePosition(const std::vector<XMFLOAT3>& points, size_t startIndex, float t);

	static float easingOut(const float& start, const float& end, const float t);

private:

	float acceleration_g = G / 60;//�����x
	float N = MASS * 0.08;//���C��
	float vel = -10;//�������̃x�N�g��
	float JumpVel = 2;

	double x1;     // �R��L�΂��Ĉ���������ꍇ�ɏo����~����̍��W�A�O�͕R�����̐^���ɂ���ʒu
	double angle;
	double speed; // x�̑��x

	float g1;
	float Time = 0;

};
