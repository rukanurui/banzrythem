#include "FBX.hlsli"
//�G���g���[�|�C���g

//�X�L�j������̗v�_�E�@��������
struct SkinOutPut
{
	float4 pos;
	float3 normal;
};

//�D���l���h����
SkinOutPut ComputeSkin(VSInput input)
{
	//�[���N���A
	SkinOutPut output = (SkinOutPut)0;

	uint iBone;//�v�Z����{�[���ԍ�
	float weight;//�{�[���E�F�C�g(�d��)
	matrix m;//�X�L�j�����s��

	//�{�[��0
	iBone = input.boneIndices.x;
	weight = input.boneWeights.x;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);
	//�{�[��1
	iBone = input.boneIndices.y;
	weight = input.boneWeights.y;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);
	//�{�[��2
	iBone = input.boneIndices.z;
	weight = input.boneWeights.z;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);
	//�{�[��3
	iBone = input.boneIndices.w;
	weight = input.boneWeights.w;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	return output;
}

VSOutput main(VSInput input)
{
	//�X�L�j�����v�Z
	SkinOutPut skinned = ComputeSkin(input);
	//�@���Ƀ��[���h�s��ɂ��X�P�[�����O�E��]��K�p
	float4 wnormal = normalize(mul(world, float4(skinned.normal, 0)));
	//�s�N�Z���V�F�[�_�[�ɖ߂��l
	VSOutput output;
	//�s��ɂ����W�Ԋ�
	output.svpos = mul(mul(viewproj, world), skinned.pos);
	//���[���h�@�������̃X�e�[�W�ɓn��
	output.normal = wnormal.xyz;
	//���͒l�����̂܂܎��̃X�e�[�W�ɓn��
	output.uv = input.uv;

	return output;
}