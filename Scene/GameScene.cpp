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
    spriteCommon->LoadTexture(0, L"Resources/sousa.png");
    spriteCommon->LoadTexture(1, L"Resources/owari.png");
    spriteCommon->LoadTexture(3, L"Resources/UI/PERFETC3.png");
    spriteCommon->LoadTexture(4, L"Resources/UI/GOOD1.png");
    spriteCommon->LoadTexture(5, L"Resources/UI/BAD1.png");
    spriteCommon->LoadTexture(6, L"Resources/back.png");




    //ポストエフェクト用テクスチャの読み込み
    spriteCommon->LoadTexture(101, L"Resources/White1x1.png");

    //スプライト生成
    trans = Sprite::Create(spriteCommon, 101);
    trans->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    trans->SetSize({ Effectsize });
    trans->TransferVertexBuffer();

    sousa = Sprite::Create(spriteCommon,0);
    sousa->SetPosition({ spritepos });
    sousa->SetSize({ spritesize });
    sousa->TransferVertexBuffer();

    owari = Sprite::Create(spriteCommon, 1);
    owari->SetPosition({ spritepos });
    owari->SetSize({ spritesize });
    owari->TransferVertexBuffer();

    perfect = Sprite::Create(spriteCommon, 3);
    perfect->SetPosition({ 400,480,0});
    perfect->SetRotation(-10);
    perfect->SetSize({ 200,50 });
    perfect->TransferVertexBuffer();

    good = Sprite::Create(spriteCommon, 4);
    good->SetPosition({ 400,480,0 });
    good->SetRotation(-10);
    good->SetSize({ 1024,389 });
    good->TransferVertexBuffer();

    bad = Sprite::Create(spriteCommon, 5);
    bad->SetPosition({ 400,480,0 });
    bad->SetRotation(-10);
    bad->SetSize({ 1024,469 });
    bad->TransferVertexBuffer();

    back = Sprite::Create(spriteCommon, 6);
    back->SetPosition({ 640,360,0 });
    //back->SetRotation(0);
    back->SetSize({ 1280,720 });
    back->TransferVertexBuffer();

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

    random_ = new RandomObj();
    random_->SetmeatModel(meatmodel);
    random_->SettomatoModel(tomatomodel1);
    random_->SettomatoModel2(tomatomodel2);
    random_->SettomatoModel3(tomatomodel3);
    random_->SettomatoModel4(tomatomodel4);
    random_->SetretasuModel(retasumodel1);
    random_->SetretasuModel2(retasumodel2);
    random_->SettirzuModel(cheasemodel);
    random_->SetkutusitaModel(soxmodel);

    minibunsup = new FBXobj3d();
    minibunsup->Initialize();
    minibunsup->SetPosition({ 4.0f,bunslap,5.0f });
    minibunsup->SetScale({ 0.004f,0.004f,0.004f });
    minibunsup->SetModel(bunsmodel1);

    minibunsup2 = new FBXobj3d();
    minibunsup2->Initialize();
    minibunsup2->SetPosition({ 4.0f,bunslap,5.0f });
    minibunsup2->SetScale({ 0.004f,0.004f,0.004f });
    minibunsup2->SetModel(bunsmodel2);

    minibunsup3 = new FBXobj3d();
    minibunsup3->Initialize();
    minibunsup3->SetPosition({ 4.0f,bunslap,5.0f });
    minibunsup3->SetScale({ 0.004f,0.004f,0.004f });
    minibunsup3->SetModel(bunsmodel3);

    minibunsdown = new FBXobj3d();
    minibunsdown->Initialize();
    minibunsdown->SetPosition({ 4.0f,2.0f,5.0f });
    minibunsdown->SetScale({ 0.004f,0.004f,0.004f });
    minibunsdown->SetRotation({ 0.0f,0.0f,-180.0f });
    minibunsdown->SetModel(bunsmodel1);

    minibunsdown2 = new FBXobj3d();
    minibunsdown2->Initialize();
    minibunsdown2->SetPosition({ 4.0f,2.0f,5.0f });
    minibunsdown2->SetScale({ 0.004f,0.004f,0.004f });
    minibunsdown2->SetRotation({ 0.0f,0.0f,-180.0f });
    minibunsdown2->SetModel(bunsmodel2);

    minibunsdown3 = new FBXobj3d();
    minibunsdown3->Initialize();
    minibunsdown3->SetPosition({ 4.0f,2.0f,5.0f });
    minibunsdown3->SetScale({ 0.004f,0.004f,0.004f });
    minibunsdown3->SetRotation({ 0.0f,0.0f,-180.0f });
    minibunsdown3->SetModel(bunsmodel3);

   

    score_ = new ScoreManager(); 

    int counter = 0; // アニメーションの経過時間カウンター(アニメーションするfbxの時のみ使用)


    //デバックテキスト
    //debugText = new DebugText();
    debugText = new Sprite();
    debugText2 = new Sprite();
    debugText3 = new Sprite();



    const int debugTextTexNumber = 2;
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/ASC_white1280.png");
    debugText->DebugInitialize(spriteCommon, debugTextTexNumber);
    debugText2->DebugInitialize(spriteCommon, debugTextTexNumber);
    debugText3->DebugInitialize(spriteCommon, debugTextTexNumber);

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

      
        count++;

        time2count++;

        if (time2count >= 60)
        {
            time2count = 0;
            timecount += 1;
        }

        if (count < 3600)
        {
            // マウスの入力を取得
            Input::MouseMove mouseMove = input->GetMouseMove();

            CurretmouseX = mouseMove.lX;
            CurretmouseY = mouseMove.lY;

            camera->SetmouseX(CurretmouseX);
            camera->SetmouseY(CurretmouseY);

            camera->SetTarget({ 0.0f,3.8f,2.5f });

            //更新処理
            random_->SetBunsPosition({ 0,0,0 });
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
            minibunsup->Update();
            minibunsup2->Update();
            minibunsup3->Update();
            minibunsdown->Update();
            minibunsdown2->Update();
            minibunsdown3->Update();
            camera->CurrentUpdate();
            sousa->Update();
            back->Update();
          
            //debugText->Print("105", 100, 100, 50);

         
            collisionManager->CheckAllCollisions();

            if (bunsup->GetSand() == 1 && bunsdown->GetSand() == 1)
            {
                Scalecomboflag = false;
            }


            if (Scalecomboflag == false)
            {
                if (Scalecomboflag2 == true)
                {
                    if (Scalecombo.y > 70.0f)Scalecombo.y -= 15.0f;
                    if (Scalecombo.x > 280.0f)Scalecombo.x -= 60.0f;

                    if (Scalecombo.y <= 70.0f && Scalecombo.y <= 280.0f)
                    {
                        Scalecomboflag2 = false;
                        Scalecomboflag = true;
                    }
                }
                else
                {
                    if (Scalecombo.y < 80.0f)Scalecombo.y += 15.0f;
                    if (Scalecombo.x < 320.0f)Scalecombo.x += 60.0f;

                    if (Scalecombo.y >= 80.0f && Scalecombo.x >= 320.0f)Scalecomboflag2 = true;

                }
            }
            else
            {
                ScalecomboTime++;

                if (ScalecomboTime >= 180)
                {
                    Scalecombo.x = 0;
                    Scalecombo.y = 0;
                    ScalecomboTime = 0;
                }
            }

            perfect->SetSize({ Scalecombo });
            perfect->Update();
            perfect->TransferVertexBuffer();

            good->SetSize({ Scalecombo });
            good->Update();
            good->TransferVertexBuffer();

            bad->SetSize({ Scalecombo });
            bad->Update();
            bad->TransferVertexBuffer();

            //セット処理
            score_->SetUpSandPoint(bunsup->GetSand());
            score_->SetUnderSandPoint(bunsdown->GetSand());
            score_->SetSandType(bunsup->GetSandAttribute());

            score_->SetPerfect(bunsup->GetPerfect());

            score_->Update();

            foodnum = bunsup->GetSandAttribute();

            if (foodnum == meat)
            {
                std::unique_ptr<FBXobj3d>& listmeat = std::make_unique<FBXobj3d>();
                listmeat->Initialize();
                listmeat->SetModel(meatmodel);
                listmeat->SetPosition({ 4.0f, lap,5.0f });
                listmeat->SetScale({ 0.004f,0.004f,0.004f });
                meats.push_back(std::move(listmeat));

                lap = lap + 0.7f;
                bunslap = bunslap + 0.7f;
            }
            else if (foodnum == bunsnum)
            {
            }
            else if (foodnum == tomato)
            {
                std::unique_ptr<FBXobj3d>& listtomato = std::make_unique<FBXobj3d>();
                listtomato->Initialize();
                listtomato->SetModel(tomatomodel1);
                listtomato->SetPosition({ 4.0f, lap,5.0f });
                listtomato->SetScale({ 0.004f,0.004f,0.004f });
                tomatos.push_back(std::move(listtomato));
                std::unique_ptr<FBXobj3d>& listtomato2 = std::make_unique<FBXobj3d>();
                listtomato2->Initialize();
                listtomato2->SetModel(tomatomodel2);
                listtomato2->SetPosition({ 4.0f, lap,5.0f });
                listtomato2->SetScale({ 0.004f,0.004f,0.004f });
                tomato2s.push_back(std::move(listtomato2));
                std::unique_ptr<FBXobj3d>& listtomato3 = std::make_unique<FBXobj3d>();
                listtomato3->Initialize();
                listtomato3->SetModel(tomatomodel3);
                listtomato3->SetPosition({ 4.0f, lap,5.0f });
                listtomato3->SetScale({ 0.004f,0.004f,0.004f });
                tomato3s.push_back(std::move(listtomato3));
                std::unique_ptr<FBXobj3d>& listtomato4 = std::make_unique<FBXobj3d>();
                listtomato4->Initialize();
                listtomato4->SetModel(tomatomodel4);
                listtomato4->SetPosition({ 4.0f, lap,5.0f });
                listtomato4->SetScale({ 0.004f,0.004f,0.004f });
                tomato4s.push_back(std::move(listtomato4));

                lap = lap + 0.7f;
                bunslap = bunslap + 0.7f;
            }
            else if (foodnum == retasu)
            {
                std::unique_ptr<FBXobj3d>& listretasu = std::make_unique<FBXobj3d>();
                listretasu->Initialize();
                listretasu->SetModel(retasumodel1);
                listretasu->SetPosition({ 4.0f, lap,5.0f });
                listretasu->SetScale({ 0.004f,0.004f,0.004f });
                retasus.push_back(std::move(listretasu));
                std::unique_ptr<FBXobj3d>& listretasu2 = std::make_unique<FBXobj3d>();
                listretasu2->Initialize();
                listretasu2->SetModel(retasumodel2);
                listretasu2->SetPosition({ 4.0f, lap,5.0f });
                listretasu2->SetScale({ 0.004f,0.004f,0.004f });
                retasu2s.push_back(std::move(listretasu2));

                lap = lap + 0.7f;
                bunslap = bunslap + 0.7f;
            }
            else if (foodnum == chease)
            {
                std::unique_ptr<FBXobj3d>& listchases = std::make_unique<FBXobj3d>();
                listchases->Initialize();
                listchases->SetModel(cheasemodel);
                listchases->SetPosition({ 4.0f, lap,5.0f });
                listchases->SetScale({ 0.004f,0.004f,0.004f });
                chases.push_back(std::move(listchases));

                lap = lap + 0.7f;
                bunslap = bunslap + 0.7f;
            }
            else if (foodnum == sox)
            {
                std::unique_ptr<FBXobj3d>& listsoxs = std::make_unique<FBXobj3d>();
                listsoxs->Initialize();
                listsoxs->SetModel(soxmodel);
                listsoxs->SetPosition({ 4.0f, lap,5.0f });
                listsoxs->SetScale({ 0.004f,0.004f,0.004f });
                soxs.push_back(std::move(listsoxs));

                lap = lap + 0.7f;
                bunslap = bunslap + 0.7f;
            }

            for (std::unique_ptr<FBXobj3d>& listmeat : meats)
            {
                listmeat->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listtomato : tomatos)
            {
                listtomato->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listtomato2 : tomato2s)
            {
                listtomato2->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listtomato3 : tomato3s)
            {
                listtomato3->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listtomato4 : tomato4s)
            {
                listtomato4->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listretasu : retasus)
            {
                listretasu->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listretasu2 : retasu2s)
            {
                listretasu2->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listchase : chases)
            {
                listchase->Update();
            }
            for (std::unique_ptr<FBXobj3d>& listsox : soxs)
            {
                listsox->Update();
            }

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
        }
        else if(count >= 3600)
        {
            bunsup->Update();
            bunsup2->Update();
            bunsup3->Update();
            bunsdown->Update();
            bunsdown2->Update();
            bunsdown3->Update();
            owari->Update();
            camera->CurrentUpdate();

            //パッドのポインタ
            pad* pad_ = nullptr;
            pad_ = new pad();

            //パッドの更新
            pad_->Update();

            //SPACEキー押したらクリアシーンへ
            if (pad_->iPad_X == 1)
            {
                //次のシーンを生成
                BaseScene* scene = makeScene<ClearScene>();
                //シーン切り替え
                sceneManager->NextScene(scene);
                //現在のプレイ中シーンをシーンマネージャーに渡す
                sceneManager->SetplayScene(playscene);

            }

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
    }

}




void GameScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

     //シーン切り替え処理
     if (transscene == false)
     {
         transEffect->Draw(cmdList);
     }

     if (playscene == 1)
     {
         spriteCommon->PreDraw();
         if (transscene != false)back->Draw();


         
         bunsup->Draw(cmdList);
         bunsup2->Draw(cmdList);
         bunsup3->Draw(cmdList);
         bunsdown->Draw(cmdList);
         bunsdown2->Draw(cmdList);
         bunsdown3->Draw(cmdList);

         minibunsup->Draw(cmdList);
         minibunsup2->Draw(cmdList);
         minibunsup3->Draw(cmdList);
         minibunsdown->Draw(cmdList);
         minibunsdown2->Draw(cmdList);
         minibunsdown3->Draw(cmdList);
         
         random_->RandomDraw(cmdList);

         for (std::unique_ptr<FBXobj3d>& listmeat : meats)
         {
             listmeat->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listtomato : tomatos)
         {
             listtomato->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listtomato2 : tomato2s)
         {
             listtomato2->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listtomato3 : tomato3s)
         {
             listtomato3->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listtomato4 : tomato4s)
         {
             listtomato4->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listretasu : retasus)
         {
             listretasu->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listretasu2 : retasu2s)
         {
             listretasu2->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listchase : chases)
         {
             listchase->Draw(cmdList);
         }
         for (std::unique_ptr<FBXobj3d>& listsox : soxs)
         {
             listsox->Draw(cmdList);
         }
         //  スプライト描画前処理
         spriteCommon->PreDraw();
         //back->Draw();


         sousa->Draw();
         if (score_->GetType() == 1)
         {
             perfect->Draw();
         }
         else  if (score_->GetType() == 2)
         {
             good->Draw();
         }
         else if (score_->GetType() == 3)
         {
             bad->Draw();
         }

         if (count > 3600)
         {
             owari->Draw();
         }

         // デバッグテキスト描画
         sprintf_s(moji, "%d", score_->GetCombo());
         sprintf_s(moji2, "%d", score_->GetScore());
         sprintf_s(moji3, "%d", timecount);

   
         debugText->SetColor({ 1,1,1,0 });
         debugText->DebugPrint(moji, 100, 100,3.0f);
         debugText->DebugDrawAll();
         
         debugText2->DebugPrint(moji2, 640, 360);
         debugText2->DebugDrawAll();

         debugText3->DebugPrint(moji3, 640, 100);
         debugText3->DebugDrawAll();


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

