#pragma once
#include "SpriteCommon.h"
#include <string>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
using namespace Microsoft::WRL;


class Sprite
{
private: // エイリアス
// Microsoft::WRL::を省略
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::を省略
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMMATRIX = DirectX::XMMATRIX;

public:

    // 頂点データ
    struct VertexPosUv
    {
        XMFLOAT3 pos; // xyz座標
        XMFLOAT2 uv;  // uv座標
    };

    // 定数バッファ用データ構造体
    struct ConstBufferData {
        XMFLOAT4 color; // 色 (RGBA)
        XMMATRIX mat;   // ３Ｄ変換行列
        float time;
        float alpha;//アルファ
        float Move = 50.0f;//ブロックノイズの大きさ
    };

    static Sprite* Create(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

    void Initialize(SpriteCommon* spriteCommon, UINT texNumber,XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);

    //頂点バッファの転送
    void TransferVertexBuffer();

    void Draw();

    void Update();

    //コンストラクタ
    //Sprite(SpriteCommon* spriteCommon);

    void SetPosition(const DirectX::XMFLOAT3& position) { positiona = position; }
    void SetRotation(float rotation) { rotationa = rotation; }
    void SetSize(const DirectX::XMFLOAT2& size) { sizea = size; }
    void SetTexLeftTop(const XMFLOAT2& texLeftTop) { texLeftTopa = texLeftTop ;}
    void SetTexSize(const XMFLOAT2& texSize) { texSizea = texSize; }
    void SetColor(const XMFLOAT4& color) { colora = color; }

    //DebugText
    void DebugInitialize(SpriteCommon* spriteCommon, UINT texnumber);
    void DebugPrint(const std::string& text, float x, float y, float scale = 1.0f);
    void DebugDrawAll();
    void DebugFinalize();

protected:
    SpriteCommon* spriteCommona = nullptr;
    //頂点バッファ;
    ComPtr<ID3D12Resource> vertBuffa;
    //頂点バッファビュー;
    D3D12_VERTEX_BUFFER_VIEW vbViewa{};
    //定数バッファ;
    ComPtr<ID3D12Resource> constBuffa;
    // 頂点数
    static const int vertNum = 4;
    // Z軸回りの回転角
    float rotationa = 0.0f;
    // 座標
    XMFLOAT3 positiona = { 0,0,0 };
    // ワールド行列
    XMMATRIX matWorlda;
    // 色(RGBA)
    XMFLOAT4 colora = { 1, 1, 1, 1 };
    // テクスチャ番号
    UINT texNumbera = 0;
    // 大きさ
    XMFLOAT2 sizea= { 100, 100 };
    // アンカーポイント
    XMFLOAT2 anchorpointa = { 0.5f, 0.5f };
    // 左右反転
    bool isFlipXa = false;
    // 上下反転
    bool isFlipYa = false;
    // テクスチャ左上座標
    XMFLOAT2 texLeftTopa = { 0, 0 };
    // テクスチャ切り出しサイズ
    XMFLOAT2 texSizea = { 100, 100 };
    // 非表示
    bool isInvisiblea = false;

    //DebugText用
    static const int maxCharCount = 256;    // 最大文字数
    static const int fontWidth = 80;         // フォント画像内1文字分の横幅
    static const int fontHeight = 80;       // フォント画像内1文字分の縦幅
    static const int fontLineCount = 16;    // フォント画像内1行分の文字数
    // スプライトデータの配列
    Sprite* spritesa[maxCharCount];
    // スプライトデータ配列の添え字番号
    int spriteIndexa = 0;

};

