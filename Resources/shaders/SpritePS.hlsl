#include "Sprite.hlsli"

Texture2D<float4> tex : register(t0);//0�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//0�Ԗڂɐݒ肳�ꂽ�T���v���[


float4 main(VSOutput input) : SV_TARGET
{
	//float2 samplePoint = input.uv;
	//samplePoint.x += 0.05;

	////�c��
	//samplePoint -= float2(0.5, 0.5);
	//float distPower = pow(length(samplePoint), 1);
	//samplePoint *= float2(distPower, distPower);
	//samplePoint += float2(0.5, 0.5);
	//float4 Tex = tex.Sample(smp, samplePoint);


	//return Tex;
	return tex.Sample(smp, input.uv) * color;
}

