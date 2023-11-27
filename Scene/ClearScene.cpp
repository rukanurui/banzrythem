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

}


void ClearScene::Update()
{  

    
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

void ClearScene::Draw()
{
    // �R�}���h���X�g�̎擾
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

    //�X�v���C�g�`��O����
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


