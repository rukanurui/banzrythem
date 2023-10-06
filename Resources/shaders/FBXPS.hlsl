#include"FBX.hlsli"

//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex : register(t0);
//0�ԃX���b�g�ɒǉ����ꂽ�T���v���[
SamplerState smp : register(s0);

struct PSOutput
{
	float4 target0 : SV_TARGET0;
	float4 target1 : SV_TARGET1;
};


//�G���g���[�|�C���g
PSOutput main(VSOutput input)
{
	PSOutput output;
	//�e�N�X�`���}�b�s���O
	float4 texcolor = tex.Sample(smp, input.uv);

	//Lambert����
	float3 Light = normalize(float3(1, -1, 1));//�E���������̃��C�g
	//phong����
	float4 ambient = texcolor * 0.2;//�A���r�G���g
	float3 eyeDir = normalize(camerapos.xyz - input.normal);//�����x�N�g��
	float3 halfvec = normalize(Light + eyeDir);//�n�[�t�x�N�g��
	float intensity =
		saturate(dot(normalize(input.normal), halfvec));
	float millar = pow(intensity, 30);
	float4 specularColor = float4(1, 1, 1, 1);
	float specular = specularColor * millar;
	float diffuse = saturate(dot(-Light, input.normal));
	float brightness = diffuse + 0.3f;
	//float brightness = ambient + diffuse + specular;
	//float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
	float4 phong = float4(brightness, brightness, brightness, 1.0f);
	//float4 shadecolor = float4(1,0,0,1.0f);//�P�F�œh��Ԃ�
	//�A�e�ƃe�N�X�`���̐F������
	//output.target0 = shadecolor * texcolor;
	//output.target1 = shadecolor * texcolor;
	output.target0 = phong * texcolor;
	output.target1 = float4((phong * texcolor).rgb, 1);
	return output;
}