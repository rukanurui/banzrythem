#include "Physics.h"
#define Pl 3.14159

template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMMATRIX = DirectX::XMMATRIX;
using XMVECTOR = DirectX::XMVECTOR;


Physics::Physics()
{
}

XMFLOAT3 Physics::splinePosition(const std::vector<XMFLOAT3>& points, size_t startIndex, float t)
{
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];
	if (startIndex < 1)return points[1];

	XMFLOAT3 p0 = points[startIndex - 1];
	XMFLOAT3 p1 = points[startIndex];
	XMFLOAT3 p2 = points[startIndex + 1];
	XMFLOAT3 p3 = points[startIndex + 2];

	XMFLOAT3 position;

	//X座標
	position.x = 0.5 * ((2.0f * p1.x) + ((-1 * p0.x) + p2.x) * t +
		((2 * p0.x) - (5 * p1.x) + (4 * p2.x) - p3.x) * t * t +
		((-1 * p0.x) + (3 * p1.x) - (3 * p2.x) + p3.x) * t * t * t);

	//Y座標
	position.y = 0.5 * ((2.0f * p1.y) + ((-1 * p0.y) + p2.y) * t +
		((2 * p0.y) - (5 * p1.y) + (4 * p2.y) - p3.y) * t * t +
		((-1 * p0.y) + (3 * p1.y) - (3 * p2.y) + p3.y) * t * t * t);

	//Z座標
	position.z = 0.5 * ((2.0f * p1.z) + ((-1 * p0.z) + p2.z) * t +
		((2 * p0.z) - (5 * p1.z) + (4 * p2.z) - p3.z) * t * t +
		((-1 * p0.z) + (3 * p1.z) - (3 * p2.z) + p3.z) * t * t * t);

	return position;
}

float Physics::easingOut(const float& start, const float& end, const float t)
{
	return start * (1.0f - t * (2 - t)) + end * (t * (2 - t));
}

float Physics::Angle(float x, float y, float x1, float y1, float z)
{
	double ax, ay, bx, by;

	// bx,by 自分の進んでいる方向 ax,ay 本来進むべき方向  
	bx = cos(z);
	by = sin(z);
	ax = (x + x1) - x;
	ay = (y + y1) - y;

	// 外積を利用し向きを照準側に向ける
	z += (ax * by - ay * bx < 0.0) ? +Pl / 180 * 8 : -Pl / 180 * 8;

	return z;

}