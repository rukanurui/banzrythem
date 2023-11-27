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
    //�|�C���^�u����

    this->dxCommon = dxcommon;
    this->input = input;
    this->audio = audio;
    this->spriteCommon = spritecommon;
    this->Windows = windows;
   

    //�J��������
    camera = new Camera(this->input, this->Windows);
    camera->Initialize(WindowsApp::window_width, WindowsApp::window_height, this->input);

#pragma region �`�揉��������


    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    // �X�v���C�g���ʃe�N�X�`���ǂݍ���
    spriteCommon->LoadTexture(0, L"Resources/sousa.png");
    spriteCommon->LoadTexture(1, L"Resources/owari.png");

    //�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
    spriteCommon->LoadTexture(101, L"Resources/White1x1.png");

    //�X�v���C�g����
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

    int PFnum = 101;
    //�|�X�g�G�t�F�N�g�̏�����
    transEffect = TransEffect::Create(spriteCommon, PFnum, { 0,0 }, false, false);

    collisionManager = CollisionManager::GetInstance();


    //FBX�֘A
    //�f�o�C�X���Z�b�g
    FBXobj3d::SetDevice(dxCommon->GetDevice());
    //�J�������Z�b�g
    FBXobj3d::SetCamera(camera);
    //FBX�p�C�v���C������
    FBXobj3d::CreateGraphicsPipeline();

    //���f���ǂݍ���
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

    score_ = new ScoreManager();

    //�w�i

    //�v���C���[�֘A����
   

    //�n�`3d�I�u�W�F�N�g
   

    ////�ǂ̃X�P�[��0.1=���[���h��10

    //�X�e�[�W�f�[�^�ǂݎ��



    //�G�̐���
 

    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[(�A�j���[�V��������fbx�̎��̂ݎg�p)


    //�f�o�b�N�e�L�X�g
    debugText = new DebugText();
    const int debugTextTexNumber = 2;
    spriteCommon->LoadTexture(debugTextTexNumber, L"Resources/ASC_white1280.png");
    debugText->Initialize(spriteCommon, debugTextTexNumber);

}


void GameScene::Update()
{

    // �}�E�X�̓��͂��擾
    Input::MouseMove mouseMove = input->GetMouseMove();

    //��ʑJ�ڏ���
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


    //�Q�[���{��
    if (transscene == true)
    {
        
        count++;

        if (count < 3600)
        {
            // �}�E�X�̓��͂��擾
            Input::MouseMove mouseMove = input->GetMouseMove();

            CurretmouseX = mouseMove.lX;
            CurretmouseY = mouseMove.lY;

            camera->SetmouseX(CurretmouseX);
            camera->SetmouseY(CurretmouseY);

            camera->SetTarget({ 0.0f,3.8f,2.5f });

            //�X�V����
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
            camera->CurrentUpdate();
            sousa->Update();

            //debugText->Print("105", 100, 100, 50);

            collisionManager->CheckAllCollisions();

            //�Z�b�g����
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

            //�p�b�h�̃|�C���^
            pad* pad_ = nullptr;
            pad_ = new pad();

            //�p�b�h�̍X�V
            pad_->Update();

            //SPACE�L�[��������N���A�V�[����
            if (pad_->iPad_X == 1)
            {
                //���̃V�[���𐶐�
                BaseScene* scene = makeScene<ClearScene>();
                //�V�[���؂�ւ�
                sceneManager->NextScene(scene);
                //���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
                sceneManager->SetplayScene(playscene);

            }

        }
        
        

        //R�L�[���������烊�g���C
        if (input->TriggerKey(DIK_R))
        {
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<GameoverScene>();
            //�V�[���؂�ւ�
            sceneManager->NextScene(scene);
            //���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
            sceneManager->SetplayScene(playscene);
        }
    }

}




void GameScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

     //�V�[���؂�ւ�����
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
         
         random_->RandomDraw(cmdList);

         //�X�v���C�g�`��O����
         spriteCommon->PreDraw();

         sousa->Draw();

         if (count > 3600)
         {
             owari->Draw();
         }

         // �f�o�b�O�e�L�X�g�`��
         sprintf_s(moji, "%d", score_->GetScore());
         debugText->Print(moji, 100, 100);
        // debugText->DrawAll();
     }

   //  floor->Draw(cmdList);
}


void GameScene::Finalize()
{
    //3d�I�u�W�F�N�g���
    //delete object3d;
    //3d���f�����
    //delete Model;

    //�f�o�b�O�e�L�X�g���
    //debugText->Finalize();
    delete debugText;

    //�X�v���C�g���
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

