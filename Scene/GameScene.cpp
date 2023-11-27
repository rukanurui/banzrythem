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

    //モデル読み込み
    bunsmodel1 = FbxLoader::GetInstance()->LoadModelFromFile("banzu1");
    bunsmodel2 = FbxLoader::GetInstance()->LoadModelFromFile("banzu2");
    bunsmodel3 = FbxLoader::GetInstance()->LoadModelFromFile("banzu3");
    meatmodel = FbxLoader::GetInstance()->LoadModelFromFile("humbergu");
    cheasemodel = FbxLoader::GetInstance()->LoadModelFromFile("ti-zu");
    tomatomodel1 = FbxLoader::GetInstance()->LoadModelFromFile("tomato1");
    tomatomodel2 = FbxLoader::GetInstance()->LoadModelFromFile("tomato2");
    tomatomodel3 = FbxLoader::GetInstance()->LoadModelFromFile("tomato3");
    tomatomodel4 = FbxLoader::GetInstance()->LoadModelFromFile("tomato4");
    retasumodel1 = FbxLoader::GetInstance()->LoadModelFromFile("retasu1");
    retasumodel2 = FbxLoader::GetInstance()->LoadModelFromFile("retasu2");
    soxmodel = FbxLoader::GetInstance()->LoadModelFromFile("kutusita");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");



    bunsup = new Buns(input);
    bunsup->Initialize();
    bunsup->SetPosition({ 0.0f,4.0f,5.0f });
    bunsup->BunsInitialize(false);
    bunsup->SetScale({ 0.01f,0.01f,0.01f });
    bunsup->SetModel(bunsmodel1);
    bunsup->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,0.5f,2.0f,0.0f },1.0f));
    bunsup->BunsCollisionColorSet();

    bunsup2 = new FBXobj3d();
    bunsup2->Initialize();
    bunsup2->SetPosition({ 0.0f,5.0f,5.0f });
    bunsup2->SetScale({ 0.01f,0.01f,0.01f });
    bunsup2->SetModel(bunsmodel2);

    bunsup3 = new FBXobj3d();
    bunsup3->Initialize();
    bunsup3->SetPosition({ 0.0f,5.0f,5.0f });
    bunsup3->SetScale({ 0.01f,0.01f,0.01f });
    bunsup3->SetModel(bunsmodel3);

    bunsdown = new Buns(input);
    bunsdown->Initialize();
    bunsdown->SetPosition({ 0.0f,2.0f,5.0f });
    bunsdown->BunsInitialize(true);
    bunsdown->SetScale({ 0.01f,0.01f,0.01f });
    bunsdown->SetModel(bunsmodel1);
    bunsdown->SetCollider(new BoxCollider(XMVECTOR{ 1.0f,0.5f,2.0f,0.0f }, 1.0f));
    bunsdown->BunsCollisionColorSet();

    bunsdown2 = new FBXobj3d();
    bunsdown2->Initialize();
    bunsdown2->SetPosition({ 0.0f,2.0f,5.0f });
    bunsdown2->SetScale({ 0.01f,0.01f,0.01f });
    bunsdown2->SetModel(bunsmodel2);

    bunsdown3 = new FBXobj3d();
    bunsdown3->Initialize();
    bunsdown3->SetPosition({ 0.0f,2.0f,5.0f });
    bunsdown3->SetScale({ 0.01f,0.01f,0.01f });
    bunsdown3->SetModel(bunsmodel3);


    //床
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));

    random_ = new RandomObj();
    random_->SetmeatModel(meatmodel);
    random_->SettomatoModel(tomatomodel1);
    random_->SetretasuModel(retasumodel1);
    random_->SettirzuModel(cheasemodel);
    random_->SetkutusitaModel(soxmodel);

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

        //RandomNumberを代入
        RandomNumber = random_->GetRandomNumber();

        if (RandomNumber !=1 && RandomNumber !=2)
        {
            RandomCreate = false;
        }

        //更新処理
        random_->SetBunsPosition({0,0,0});
        random_->RandomInitialize();
        random_->RandomUpdate();
        bunsup->Update();
        bunsup2->Update();
        bunsup3->Update();
        bunsdown->Update();
        bunsdown2->Update();
        bunsdown3->Update();
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

        bunsup2->SetPosition(bunsup->GetPos());
        bunsup3->SetPosition(bunsup->GetPos());
        bunsup2->SetRotation(bunsup->GetRotation());
        bunsup3->SetRotation(bunsup->GetRotation());

        bunsdown2->SetPosition(bunsdown->GetPos());
        bunsdown3->SetPosition(bunsdown->GetPos());
        bunsdown2->SetRotation(bunsdown->GetRotation());
        bunsdown3->SetRotation(bunsdown->GetRotation());
        
        //ランダムでトマトとレタスが指定されてたら生成する
        if (RandomNumber == 2 && RandomCreate == false)
        {
            tomato2 = new FBXobj3d();
            tomato2->Initialize();
            tomato2->SetPosition({ random_->GetPos()});
            tomato2->SetScale({ 0.01f,0.01f,0.01f });
            tomato2->SetModel(tomatomodel2);

            tomato3 = new FBXobj3d();
            tomato3->Initialize();
            tomato3->SetPosition({ random_->GetPos() });
            tomato3->SetScale({ 0.01f,0.01f,0.01f });
            tomato3->SetModel(tomatomodel3);

            tomato4 = new FBXobj3d();
            tomato4->Initialize();
            tomato4->SetPosition({ random_->GetPos() });
            tomato4->SetScale({ 0.01f,0.01f,0.01f });
            tomato4->SetModel(tomatomodel4);

            RandomCreate = true;
        }
        if (RandomNumber == 2 && RandomCreate == true)
        {
            tomato2->SetPosition({ random_->GetPos()});
            tomato3->SetPosition({ random_->GetPos()});
            tomato4->SetPosition({ random_->GetPos()});
            tomato2->SetRotation(random_->GetRotation());
            tomato3->SetRotation(random_->GetRotation());
            tomato4->SetRotation(random_->GetRotation());
        }

        if (RandomNumber == 1 && RandomCreate == false)
        {
            retasu2 = new FBXobj3d();
            retasu2->Initialize();
            retasu2->SetPosition({ random_->GetPos() });
            retasu2->SetScale({ 0.01f,0.01f,0.01f });
            retasu2->SetModel(retasumodel2);
            RandomCreate = true;
        }

       if (RandomNumber == 1 && RandomCreate == true)
        {
            retasu2->SetPosition(random_->GetPos());
            retasu2->SetRotation(random_->GetRotation());
        }

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
         bunsup2->Draw(cmdList);
         bunsup3->Draw(cmdList);
         bunsdown->Draw(cmdList);
         bunsdown2->Draw(cmdList);
         bunsdown3->Draw(cmdList);
         if (RandomNumber == 2)
         {
             tomato2->Draw(cmdList);
             tomato3->Draw(cmdList);
             tomato4->Draw(cmdList);
         }
         if (RandomNumber == 1)
         {
             retasu2->Draw(cmdList);
         }
         
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

