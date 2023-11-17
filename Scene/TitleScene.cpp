#include "TitleScene.h"
#include"SceneManager.h"

class GameScene;

template<>
BaseScene* BaseScene::makeScene<TitleScene>() {
    return new TitleScene();
}

void TitleScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //ポインタ置き場
    this->dxCommon = dxcommon;
    this->input = input;
    this->spriteCommon = spritecommon;
    this->Windows = windows;

    //カメラ生成
    camera = new Camera(this->input, this->Windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);

    //FBX関連
    //デバイスをセット
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //カメラをセット
    FBXobj3d::SetCamera(camera);
    //FBXパイプライン生成
    FBXobj3d::CreateGraphicsPipeline();

    bamodel = FbxLoader::GetInstance()->LoadModelFromFile("ba");
    nnmodel = FbxLoader::GetInstance()->LoadModelFromFile("nn");
    zumodel = FbxLoader::GetInstance()->LoadModelFromFile("zu");
    rimodel = FbxLoader::GetInstance()->LoadModelFromFile("ri");
    zu2model = FbxLoader::GetInstance()->LoadModelFromFile("zu2");
    mumodel = FbxLoader::GetInstance()->LoadModelFromFile("mu");

    ba = new FBXobj3d();
    ba->Initialize();
    ba->SetPosition({ -5.0f,5.0f,5.0f });
    ba->SetScale({ 0.005f,0.005f,0.005f });
    ba->SetModel(bamodel);

    nn = new FBXobj3d();
    nn->Initialize();
    nn->SetPosition({ -3.0f,5.0f,5.0f });
    nn->SetScale({ 0.005f,0.005f,0.005f });
    nn->SetModel(nnmodel);

    zu = new FBXobj3d();
    zu->Initialize();
    zu->SetPosition({ -1.0f,5.0f,5.0f });
    zu->SetScale({ 0.005f,0.005f,0.005f });
    zu->SetModel(zumodel);

    ri = new FBXobj3d();
    ri->Initialize();
    ri->SetPosition({ 1.0f,5.0f,5.0f });
    ri->SetScale({ 0.005f,0.005f,0.005f });
    ri->SetModel(rimodel);

    zu2 = new FBXobj3d();
    zu2->Initialize();
    zu2->SetPosition({ 3.0f,5.0f,5.0f });
    zu2->SetScale({ 0.005f,0.005f,0.005f });
    zu2->SetModel(zu2model);

    mu = new FBXobj3d();
    mu->Initialize();
    mu->SetPosition({ 5.0f,5.0f,5.0f });
    mu->SetScale({ 0.005f,0.005f,0.005f });
    mu->SetModel(mumodel);


    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    spriteCommon->LoadTexture(2, L"Resources/start.png");

    title = Sprite::Create(spriteCommon, 2);
    title->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    title->TransferVertexBuffer();

}

void TitleScene::Update()
{

    //// マウスの入力を取得
    //Input::MouseMove mouseMove = input->GetMouseMove();

    //CurretmouseX = mouseMove.lX;
    //CurretmouseY = mouseMove.lY;

    //camera->SetmouseX(CurretmouseX);
    //camera->SetmouseY(CurretmouseY);

    camera->CurrentUpdate();

    if (titleflag == true)
    {
        if (spritesize.x >= 1280)
        {
            transfrag = true;
        }
        if (spritesize.x <= 1000)
        {
            transfrag = false;
        }

        if (transfrag == true)
        {
            spritesize.x -= 1.0f;
            spritesize.y -= 1.0f;
        }
        else
        {
            spritesize.x +=1.0f;
            spritesize.y +=1.0f;
        }

        ba->Update();
        nn->Update();
        zu->Update();
        ri->Update();
        zu2->Update();
        mu->Update();

        //title->SetRotation(spriteangle);
        title->SetSize(spritesize);
        title->TransferVertexBuffer();
        title->Update();
        if (input->TriggerKey(DIK_SPACE))
        {
            playscene = 1;
            spritesize = { 1280,720 };
            transfrag = true;
            titleflag = false;
            //次のシーンを生成
            
            BaseScene* scene = makeScene<GameScene>();
            //シーン切り替え
            sceneManager->NextScene(scene);
            //現在のプレイ中シーンをシーンマネージャーに渡す
            sceneManager->SetplayScene(playscene);

        }
    }
   
}

void TitleScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    //スプライト描画前処理
    spriteCommon->PreDraw();
    if (titleflag == true)
    {
        title->Draw();
        ba->Draw(cmdList);
        nn->Draw(cmdList);
        zu->Draw(cmdList);
        ri->Draw(cmdList);
        zu2->Draw(cmdList);
        mu->Draw(cmdList);
    }

}

void TitleScene::Finalize()
{

}
