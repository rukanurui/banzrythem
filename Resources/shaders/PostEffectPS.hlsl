#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0);//0�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1);//1�Ԗڂɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);//0�Ԗڂɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	float2 samplePoint = input.uv;
	//samplePoint.x += 0.05;

	
	//�p��
	samplePoint -= float2(0.5, 0.5);
	float distPower = pow(length(samplePoint), 0.10);
	samplePoint *= float2(distPower, distPower);
	samplePoint += float2(0.5, 0.5);
	float4 Tex = tex0.Sample(smp, samplePoint);

	//���U�C�N
	float dest = 500;
	Tex = tex0.Sample(smp, floor(samplePoint * dest) / dest);

	////�������m�C�Y
	//float sinv = sin(input.uv.y * 2 + time * -0.1);
	//float steped = step(0.99, sinv * sinv);
	//Tex.rgb -= (1 - steped) * abs(sin(input.uv.y * 50.0 + time * 1.0)) * 0.05;
	//Tex.rgb -= (1 - steped) * abs(sin(input.uv.y * 100.0 - time * 2.0)) * 0.08;
	//Tex.rgb += steped * 0.1;

	//rgb���炵
	samplePoint.x += 0.005;
	Tex.b = tex0.Sample(smp, samplePoint).b;

	//�r�l�b�g
	float vignette = length(float2(0.5, 0.5) - input.uv);
	vignette = clamp(vignette - 0.35, 0, 1);
	Tex.rgb -= vignette;
	
	float4 color = Tex;

	return float4(color.rgb,1.0f);
}



