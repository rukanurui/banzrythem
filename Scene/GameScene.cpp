#pragma once
#include "GameScene.h"
#include <cassert>
#include <iomanip>
#include"../Collider/CollisionManager.h"
#include"../Collider/Collision.h"
#include"../Collider/CollisionColor.h"
#include"SceneManager.h"


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

    //�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
    spriteCommon->LoadTexture(101, L"Resources/White1x1.png");

    //�X�v���C�g����

   
    trans = Sprite::Create(spriteCommon, 101);
    trans->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    trans->SetSize({ Effectsize });
    trans->TransferVertexBuffer();

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

    bunsmodel = FbxLoader::GetInstance()->LoadModelFromFile("testfbx");
    modelfloor = FbxLoader::GetInstance()->LoadModelFromFile("floor");

    bunsup = new FBXobj3d();
    bunsup->Initialize();
    bunsup->SetPosition({ 0.0f,5.0f,5.0f });
    bunsup->SetScale({ 0.01f,0.001f,0.01f });
    bunsup->SetModel(bunsmodel);
    bunsup->SetCollider(new BoxCollider);

    bunsdown = new FBXobj3d();
    bunsdown->Initialize();
    bunsdown->SetPosition({ 0.0f,2.0f,5.0f });
    bunsdown->SetScale({ 0.01f,0.001f,0.01f });
    bunsdown->SetModel(bunsmodel);
    bunsdown->SetCollider(new BoxCollider);

    //��
    floor = new FBXobj3d();
    floor->Initialize();
    floor->SetPosition({ 0.0f,-1.0f,0.0f });
    floor->SetScale({ 1.0f,0.1f,1.0f });
    floor->SetModel(modelfloor);
    //floor->SetCollider(new BoxCollider(XMVECTOR{ 100.0f,0.7f,100.0f,0 }, 1.0f));
  
    //�w�i

    //�v���C���[�֘A����
   

    //�n�`3d�I�u�W�F�N�g
   

    ////�ǂ̃X�P�[��0.1=���[���h��10

    //�X�e�[�W�f�[�^�ǂݎ��



    //�G�̐���
 

    int counter = 0; // �A�j���[�V�����̌o�ߎ��ԃJ�E���^�[(�A�j���[�V��������fbx�̎��̂ݎg�p)

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

        // �}�E�X�̓��͂��擾
        Input::MouseMove mouseMove = input->GetMouseMove();

        CurretmouseX = mouseMove.lX;
        CurretmouseY = mouseMove.lY;

        camera->SetmouseX(CurretmouseX);
        camera->SetmouseY(CurretmouseY);

        //�X�V����
        bunsup->Update();
        bunsdown->Update();
        floor->Update();
        camera->CurrentUpdate();

        if (input->TriggerKey(DIK_SPACE))
        {
            upVel.m128_f32[1] = -0.1f;
            downVel.m128_f32[1] = 0.1f;
          
        }
     
        bunsup->MoveVector(upVel);
        bunsdown->MoveVector(downVel);
        
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

        //SPACE�L�[��������N���A�V�[����
        if (input->TriggerKey(DIK_P))
        {
            //���̃V�[���𐶐�
            BaseScene* scene = makeScene<ClearScene>();
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

    
     //�X�v���C�g�`��O����
     spriteCommon->PreDraw();

     //�V�[���؂�ւ�����
     if (transscene == false)
     {
         transEffect->Draw(cmdList);
     }

     if (playscene == 1)
     {
         bunsup->Draw(cmdList);
         bunsdown->Draw(cmdList);
     }

     floor->Draw(cmdList);

    // �f�o�b�O�e�L�X�g�`��
    //debugText->DrawAll();
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
