#include "Sprite.h"

#include <d3dx12.h>

using namespace DirectX;

Sprite*Sprite::Create(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
    //�������m��
    Sprite* instance = new Sprite();
    //�C���X�^���X������
    instance->Initialize(spriteCommon, texNumber, anchorpoint, isFlipX, isFlipY);

    return instance;
}

void Sprite::Initialize(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
    HRESULT result = S_FALSE;

    //�����o�ϐ��ɏ�������
    spriteCommona = spriteCommon;
    texNumbera = texNumber;
    anchorpointa = anchorpoint;
    isFlipXa = isFlipX;
    isFlipYa = isFlipY;

    // ���_�f�[�^
    VertexPosUv vertices[4];

    // �w��ԍ��̉摜���ǂݍ��ݍς݂Ȃ�
    if (spriteCommona->GetTexBuff(texNumbera)) {
        // �e�N�X�`�����擾
        D3D12_RESOURCE_DESC resDesc = spriteCommona->GetTexBuff(texNumbera)->GetDesc();

        // �X�v���C�g�̑傫�����摜�̉𑜓x�ɍ��킹��
        sizea = { (float)resDesc.Width, (float)resDesc.Height };
        texSizea = { (float)resDesc.Width, (float)resDesc.Height };
    }

    // ���_�o�b�t�@����
    result = spriteCommona->GetDevice()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices)),
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuffa));

    // ���_�o�b�t�@�f�[�^�]��
    TransferVertexBuffer();

    // ���_�o�b�t�@�r���[�̍쐬
    vbViewa.BufferLocation = vertBuffa->GetGPUVirtualAddress();
    vbViewa.SizeInBytes = sizeof(vertices);
    vbViewa.StrideInBytes = sizeof(vertices[0]);

    // �萔�o�b�t�@�̐���
    result = spriteCommona->GetDevice()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
        IID_PPV_ARGS(&constBuffa));

    // �萔�o�b�t�@�Ƀf�[�^�]��
    ConstBufferData* constMap = nullptr;
    result = constBuffa->Map(0, nullptr, (void**)&constMap);
    constMap->color = XMFLOAT4(1, 1, 1, 1); // �F�w��iRGBA�j
    constMap->mat = spriteCommona->GetMatProjection();  
    constBuffa->Unmap(0, nullptr);

    


}

void Sprite::TransferVertexBuffer()
{
    HRESULT result = S_FALSE;

    // ���_�f�[�^
    VertexPosUv vertices[] = {
        //     u     v
        {{}, {0.0f, 1.0f}}, // ����
        {{}, {0.0f, 0.0f}}, // ����
        {{}, {1.0f, 1.0f}}, // �E��
        {{}, {1.0f, 0.0f}}, // �E��
    };

    // �����A����A�E���A�E��
    enum { LB, LT, RB, RT };

    float left = (0.0f - anchorpointa.x) * sizea.x;
    float right = (1.0f - anchorpointa.x) * sizea.x;
    float top = (0.0f - anchorpointa.y) * sizea.y;
    float bottom = (1.0f - anchorpointa.y) * sizea.y;

    if (isFlipXa)
    {// ���E����ւ�
        left = -left;
        right = -right;
    }

    if (isFlipYa)
    {// ���E����ւ�
        top = -top;
        bottom = -bottom;
    }

    vertices[LB].pos = { left, bottom,  0.0f }; // ����
    vertices[LT].pos = { left, top,     0.0f }; // ����
    vertices[RB].pos = { right, bottom, 0.0f }; // �E��
    vertices[RT].pos = { right, top,    0.0f }; // �E��

    // �w��ԍ��̉摜���ǂݍ��ݍς݂Ȃ�
    if (spriteCommona->GetTexBuff(texNumbera)) {
        // �e�N�X�`�����擾
        D3D12_RESOURCE_DESC resDesc = spriteCommona->GetTexBuff(texNumbera)->GetDesc();

        float tex_left = texLeftTopa.x / resDesc.Width;
        float tex_right = (texLeftTopa.x + texSizea.x) / resDesc.Width;
        float tex_top = texLeftTopa.y / resDesc.Height;
        float tex_bottom = (texLeftTopa.y + texSizea.y) / resDesc.Height;

        vertices[LB].uv = { tex_left,   tex_bottom }; // ����
        vertices[LT].uv = { tex_left,   tex_top }; // ����
        vertices[RB].uv = { tex_right,  tex_bottom }; // �E��
        vertices[RT].uv = { tex_right,  tex_top }; // �E��
    }

    // ���_�o�b�t�@�ւ̃f�[�^�]��
    VertexPosUv* vertMap = nullptr;
    result = vertBuffa->Map(0, nullptr, (void**)&vertMap);
    memcpy(vertMap, vertices, sizeof(vertices));
    vertBuffa->Unmap(0, nullptr);
}

void Sprite::Draw()
{
    if (isInvisiblea) {
        return;
    }

    ID3D12GraphicsCommandList* cmdList = spriteCommona->GetCommandList();

    // ���_�o�b�t�@���Z�b�g
    cmdList->IASetVertexBuffers(0, 1, &vbViewa);

    // ���[�g�p�����[�^0�ӂɒ萔�o�b�t�@���Z�b�g
    cmdList->SetGraphicsRootConstantBufferView(0, constBuffa->GetGPUVirtualAddress());

    ///////////////////////////////////////////////////////////////////////////////koko
    // ���[�g�p�����[�^1�ӂɃV�F�[�_���\�[�X�r���[���Z�b�g
    spriteCommona->SetGraphicsRootDescriptorTabl(1, texNumbera);

    // �|���S���̕`��i4���_�Ŏl�p�`�j
    cmdList->DrawInstanced(4, 1, 0, 0);
}

void Sprite::Update()
{
    // ���[���h�s��̍X�V
    matWorlda = XMMatrixIdentity();
    // Z����]
    matWorlda *= XMMatrixRotationZ(XMConvertToRadians(rotationa));
    // ���s�ړ�
    matWorlda *= XMMatrixTranslation(positiona.x, positiona.y, positiona.z);

    // �萔�o�b�t�@�̓]��
    ConstBufferData* constMap = nullptr;
    HRESULT result = constBuffa->Map(0, nullptr, (void**)&constMap);
    constMap->mat = matWorlda * spriteCommona->GetMatProjection();
    constMap->color = colora;
    constBuffa->Unmap(0, nullptr);
}

void Sprite::DebugInitialize(SpriteCommon* spriteCommon, UINT texnumber)
{
    assert(spriteCommon);
    spriteCommona = spriteCommon;

    // �S�ẴX�v���C�g�f�[�^�ɂ���
    for (int i = 0; i < _countof(spritesa); i++)
    {
        // �X�v���C�g�𐶐�����
        spritesa[i] = Sprite::Create(spriteCommona, texnumber, { 0,0 });
    }
}

void Sprite::DebugPrint(const std::string& text, float x, float y, float scale)
{
    // �S�Ă̕����ɂ���
    for (int i = 0; i < text.size(); i++)
    {
        // �ő啶��������
        if (spriteIndexa >= maxCharCount) {
            break;
        }

        // 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
        const unsigned char& character = text[i];

        // ASCII�R�[�h��2�i����΂����ԍ����v�Z
        int fontIndex = character - 32;
        if (character >= 0x7f) {
            fontIndex = 0;
        }

        int fontIndexY = fontIndex / fontLineCount;
        int fontIndexX = fontIndex % fontLineCount;

        // ���W�v�Z
        spritesa[spriteIndexa]->SetPosition({ x + fontWidth * scale * i, y, 0 });
        spritesa[spriteIndexa]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
        spritesa[spriteIndexa]->SetTexSize({ fontWidth, fontHeight });
        spritesa[spriteIndexa]->SetSize({ fontWidth * scale, fontHeight * scale });
        // ���_�o�b�t�@�]��
        spritesa[spriteIndexa]->TransferVertexBuffer();
        // �X�V
        spritesa[spriteIndexa]->Update();

        // �������P�i�߂�
        spriteIndexa++;
    }
}

// �܂Ƃ߂ĕ`��
void Sprite::DebugDrawAll()
{
    // �S�Ă̕����̃X�v���C�g�ɂ���
    for (int i = 0; i < spriteIndexa; i++)
    {
        // �X�v���C�g�`��
        spritesa[i]->Draw();
    }

    spriteIndexa = 0;
}

void Sprite::DebugFinalize()
{
    for (auto& sprite : spritesa) {
        delete sprite;
    }
}

