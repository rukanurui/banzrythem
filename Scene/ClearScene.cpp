#include"ClearScene.h"
#include"SceneManager.h"
#include<fstream>

class GameScene;
class TitleScene;

template<>
BaseScene* BaseScene::makeScene<ClearScene>() {
    return new ClearScene();
}

void ClearScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //ポインタ置き場
    this->dxCommon = dxcommon;
    this->input = input;
    this->spriteCommon = spritecommon;
    this->Windows = windows;

    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

}


void ClearScene::Update()
{  

    
    //次のシーンを生成
    BaseScene* scene = makeScene<TitleScene>();
    //シーン切り替え
    sceneManager->NextScene(scene);
    
    return;
    ////次のシーンを生成
    //BaseScene* scene = makeScene<GameScene>();
    ////シーン切り替え
    //sceneManager->NextScene(scene);
    ////現在のプレイ中シーンをシーンマネージャーに渡す
    //sceneManager->SetplayScene(playscene);
    //return;

}

void ClearScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

    //スプライト描画前処理
    spriteCommon->PreDraw();    
}

void ClearScene::Finalize()
{
    /*delete clear;
    delete Windows;
    delete input;
    delete dxCommon;
    delete spriteCommon;
    delete modelfloor;
    delete modelwall;
    delete floor;*/
    

}


