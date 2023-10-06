#include "SpriteNoise.hlsli"

Texture2D<float4> tex0 : register(t0);//0�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1);//1�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//0�Ԗڂɐݒ肳�ꂽ�T���v���[

float Noise(float2 coord) {
	return frac(sin(dot(coord, float2(12.9898, 78.233))) * 43758.5453);
}

float Block(float2 st) {
	float m = Move;
	float2 p = floor(st * m) / m;
	return Noise(p);
}


float4 main(VSOutput input) : SV_TARGET
{
	float2 samplePoint = input.uv;
	//samplePoint.x += 0.05;

	//�m�C�Y
	
	float t = time.x;
	float4 Tex = tex0.Sample(smp, samplePoint);
	float noise1 = Block(samplePoint + float2(t, t)) - 0.1f;
	Tex.rgb += float3(noise1, noise1, noise1);

	float4 color = Tex;

	return float4(color.rgb,alpha);
}

