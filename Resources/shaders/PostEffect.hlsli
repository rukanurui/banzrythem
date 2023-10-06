//#include "math.h"
//#include <DirectXMath.h>


cbuffer cbuff0 : register(b0)
{
	float4 color; // êF (RGBA)
	matrix mat;   // ÇRÇcïœä∑çsóÒ
	float time;
	float alpha;
};

struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};