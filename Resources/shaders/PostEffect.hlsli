//#include "math.h"
//#include <DirectXMath.h>


cbuffer cbuff0 : register(b0)
{
	float4 color; // �F (RGBA)
	matrix mat;   // �R�c�ϊ��s��
	float time;
	float alpha;
};

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};