#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "SpriteCommon.h"
#include "Sprite.h"
#include "../Engine/WindowsApp.h"
#include <d3dcompiler.h>
#include "../Engine/Input.h"

using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3dcompiler.lib")

class PostEffect :
    public Sprite
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::���ȗ�
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMMATRIX = DirectX::XMMATRIX;

public:

    //�R���X�g���N�^
   /* PostEffect();*/

    static PostEffect* Create(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
    void Initialize(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
    //���_�o�b�t�@�̓]��
    //void TransferVertexBuffer();
    //�`��
    void Draw(ID3D12GraphicsCommandList* cmdList);

    //�V�[���`��O����
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
    //�V�[���`��㏈��
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
    //�p�C�v���C������
    void CreateGraphicsPipelineState();


private:
    //�e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff[2];
    //SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //�[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    //RTV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //�O���t�B�b�N�X�p�C�v���C��
    ComPtr<ID3D12PipelineState> pipelineState;
    //���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootSignature;



private:
    //��ʃN���A�J���[
    static const float clearColor[4];

};

