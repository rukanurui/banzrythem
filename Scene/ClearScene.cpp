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
    //�|�C���^�u����
    this->dxCommon = dxcommon;
    this->input = input;
    this->spriteCommon = spritecommon;
    this->Windows = windows;

    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    spriteCommon->LoadTexture(4, L"Resources/clear.png");


    clear = Sprite::Create(spriteCommon, 4);
    clear->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    clear->TransferVertexBuffer();

}


void ClearScene::Update()
{  

    if (spritesize.x >= 1280)
    {
        transfrag = true;
    }
    if (spritesize.x <= 800)
    {
        transfrag = false;
    }

    if (transfrag == true)
    {
        spritesize.x -= 4.0f;
        spritesize.y -= 3.0f;
    }
    else
    {
        spritesize.x += 4.0f;
        spritesize.y += 3.0f;
    }

    clear->SetSize(spritesize);

    clear->TransferVertexBuffer();

    clear->Update();

    wait++;

    if (playscene == 1)
    {

        if (wait>=60)
        {

            wait = 60;

            if (input->PushKey(DIK_SPACE))
            {
                playscene = 2;
                //���̃V�[���𐶐�
                BaseScene* scene = makeScene<TitleScene>();
                //�V�[���؂�ւ�
                sceneManager->NextScene(scene);

                return;
                ////���̃V�[���𐶐�
                //BaseScene* scene = makeScene<GameScene>();
                ////�V�[���؂�ւ�
                //sceneManager->NextScene(scene);
                ////���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
                //sceneManager->SetplayScene(playscene);
                //return;
            }
        }

    }

}

void ClearScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

    if (playscene == 2)
    {
       
    }

    //�X�v���C�g�`��O����
    spriteCommon->PreDraw();
    clear->Draw();
    
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


