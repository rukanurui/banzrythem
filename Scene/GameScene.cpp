#pragma once
#include "GameScene.h"
#include <cassert>
#include <iomanip>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include"SceneManager.h"

#include"../Collider/SphereCollider.h"


using namespace DirectX;

class ClearScene;
class GameoverScene;


template<>
BaseScene* BaseScene::makeScene<GameScene>() {
    return new GameScene();
}


void GameScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //ポインタ置き場

    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->Windows = windows;
   

    //カメラ生成
    camera = new Camera(this->input, this->Windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);

#pragma region 描画初期化処理


    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    // スプライト共通テクスチャ読み込み

    //ポストエフェクト用テクスチャの読み込み
    spriteCommon->LoadTexture(101, L"Resources/White1x1.png");

    //スプライト生成

   
    trans = Sprite::Create(spriteCommon, 101);
    trans->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    trans->SetSize({ Effectsize });
    trans->TransferVertexBuffer();

    int PFnum = 101;
    //ポストエフェクトの初期化
    transEffect = TransEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);

    collisionManager = CollisionManager::GetInstance();


    //FBX関連
    //デバイスをセット
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //カメラをセット
    FBXobj3d::SetCamera(camera);
    //FBXパイプライン生成
    FBXobj3d::CreateGraphicsPipeline();

    bunsmodel = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");

    bunsup = new Buns(input);
    bunsup->Initialize();
    bunsup->SetPosition({ 0.0f,5.0f,5.0f });
    bunsdown->BunsInitialize(false);
    bunsup->SetScale({ 0.01f,0.001f,0.01f });
    bunsup->SetModel(bunsmodel);
    bunsup->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,0.5f,2.0f,0.0f },1.0f));
    bunsup->BunsCollisionColorSet();

    bunsdown = new Buns(input);
    bunsdown->Initialize();
    bunsdown->SetPosition({ 0.0f,2.0f,5.0f });
    bunsdown->BunsInitialize(true);
    bunsdown->SetScale({ 0.01f,0.001f,0.01f });
    bunsdown->SetModel(bunsmodel);
    bunsdown->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,0.5f,2.0f,0.0f }, 1.0f));
    bunsdown->BunsCollisionColorSet();

    //床
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

    random_ = new RandomObj();
    random_->SetBunsModel(bunsmodel);

    score_ = new ScoreManager();

    //背景

    //プレイヤー関連処理
   

    //地形3dオブジェクト
   

    ////壁のスケール0.1=ワールドで10

    //ステージデータ読み取り



    //敵の生成
 

    int counter = 0; // アニメーションの経過時間カウンター(アニメーションするfbxの時のみ使用)


    //デバックテキスト
    debugText = new DebugText();

    const int debugTextTexNumber = 2;

    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/ASC_white1280.png");
    debugText->Initialize(spriteCommon, debugTextTexNumber);
}


void GameScene::Update()
{

    // マウスの入力を取得
    Input::MouseMove mouseMove = input->GetMouseMove();

    //画面遷移処理
    if (transscene == false)
    {
        transcount += 1.0f;

        if (transcount >= 120.0f)
        {
            transcount = 0.0f;
            transscene = true;

            const XMFLOAT3 respos = { 0.0f,5.0f,5.0f };

            camera->SetTarget(respos);
            //camera->SetEye(respos);

            camera->Update(WindowsApp::window_width, WindowsApp::window_height);
        }
    }


    //ゲーム本編
    if (transscene == true)
    {
        

        // マウスの入力を取得
        Input::MouseMove mouseMove = input->GetMouseMove();

        CurretmouseX = mouseMove.lX;
        CurretmouseY = mouseMove.lY;

        camera->SetmouseX(CurretmouseX);
        camera->SetmouseY(CurretmouseY);

        camera->SetTarget({ 0.0f,3.8f,2.5f });

       

        //更新処理
        random_->SetBunsPosition({0,0,0});
        random_->RandomInitialize();
        random_->RandomUpdate();
        bunsup->Update();
        bunsdown->Update();
        bunsup->BunsUpdate();
        bunsdown->BunsUpdate();
        floor->Update();
        camera->CurrentUpdate();

        collisionManager->CheckAllCollisions();

        //セット処理
        score_->SetUpSandPoint(bunsup->GetSand());
        score_->SetUnderSandPoint(bunsdown->GetSand());
        score_->SetSandType(bunsup->GetSandAttribute());

        score_->Update();

        bunsup->SetEndSand(score_->GetSandWitch());
        bunsdown->SetEndSand(score_->GetSandWitch());

        //Rキーを押したらリトライ
        if (input->TriggerKey(DIK_R))
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<GameoverScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);
        }

        //SPACEキーをしたらクリアシーンへ
        if (input->TriggerKey(DIK_P))
        {
            //次のシーンを生成
            BaseScene* scene = makeScene<ClearScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);

        }
    }

}




void GameScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

    
     //スプライト描画前処理
     spriteCommon->PreDraw();

     //シーン切り替え処理
     if (transscene == false)
     {
         transEffect->Draw(cmdList);
     }

     if (playscene == 1)
     {

         bunsup->Draw(cmdList);
         bunsdown->Draw(cmdList);
         random_->RandomDraw(cmdList);


         // デバッグテキスト描画
         sprintf_s(moji, "%d", score_->GetScore());
         debugText->Print(moji, 100, 100);
         debugText->DrawAll();
     }

   //  floor->Draw(cmdList);

 
}


void GameScene::Finalize()
{
    //3dオブジェクト解放
    //delete object3d;
    //3dモデル解放
    //delete Model;

    //デバッグテキスト解放
    //debugText->Finalize();
    delete debugText;

    //スプライト解放
    //for (auto& sprite : sprites) {
    //    delete sprite;
    //}
    //sprites.clear();

    delete camera;
    //delete Windows;
    //delete input;
    /*delete dxCommon;
    delete audio;*/


}

