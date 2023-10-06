#include "GameoverScene.h"
#include"SceneManager.h"

class GameScene;
class TitleScene;

template<>
BaseScene* BaseScene::makeScene<GameoverScene>() {
    return new GameoverScene();
}

void GameoverScene::Initialize(DXCommon* dxcommon, Input* input, Audio* audio, SpriteCommon* spritecommon, WindowsApp* windows)
{
    //�|�C���^�u����
    this->dxCommon = dxcommon;
    this->input = input;
    this->spriteCommon = spritecommon;
    this->Windows = windows;

    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon->GetDevice(), dxCommon->GetCommandList(), Windows->window_width, Windows->window_height);

    spriteCommon->LoadTexture(3, L"Resources/gameover.png");
    gameover = Sprite::Create(spriteCommon, 3);
    gameover->SetPosition({ WindowsApp::window_width / 2,WindowsApp::window_height / 2,0 });
    gameover->TransferVertexBuffer();

}

void GameoverScene::Update()
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

    gameover->SetSize(spritesize);

    gameover->TransferVertexBuffer();

    gameover->Update();

    wait++;
   

    if (playscene == 1)
    {

        if (wait>=60)
        {
            wait = 60;
            if (input->TriggerKey(DIK_R))
            {
                ////���̃V�[���𐶐�
                //BaseScene* scene = makeScene<GameScene>();
                ////�V�[���؂�ւ�
                //sceneManager->NextScene(scene);
                ////���݂̃v���C���V�[�����V�[���}�l�[�W���[�ɓn��
                //sceneManager->SetplayScene(playscene);
                //return;

                //���̃V�[���𐶐�
                BaseScene* scene = makeScene<TitleScene>();
                //�V�[���؂�ւ�
                sceneManager->NextScene(scene);

            }
        }
        
        
    }

    
}

void GameoverScene::Draw()
{
    //�X�v���C�g�`��O����
    spriteCommon->PreDraw();
    gameover->Draw();
}

void GameoverScene::Finalize()
{
}
