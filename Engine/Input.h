#include <Windows.h>
#include <wrl.h>
#include "WindowsApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>


#pragma once
class Input
{
public:
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

public: //�����o�֐�
	//������
	void Initialize(WindowsApp* winApp);
	//�X�V
	void Update();

	static Input* GetInstance();

	float GetVelx() { return velx;}
	float GetVely() { return vely; }

/// <summary>
/// �L�[�̉������`�F�b�N
/// </summary>
/// <param name = "keyNumber">�L�[�ԍ�(DIK_0�Ȃ�)</param>
/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);

/// <summary>
/// �L�[�̃g���K�[���`�F�b�N
/// </summary>
/// <param name = "keyNumber">�L�[�ԍ�(DIK_0�Ȃ�)</param>
/// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
/// �}�E�X�̉������`�F�b�N
/// </summary>
/// <param name = "keyNumber">�}�E�X�ԍ�(DIK_0�Ȃ�)</param>
/// <returns>������Ă��邩</returns>
	bool PushclickLeft();

	//�E�N���b�N
	bool PushclickRight();

	/// <summary>
	/// �}�E�X�̃g���K�[���`�F�b�N
	/// </summary>
	/// <param name = "keyNumber">�}�E�X�ԍ�(DIK_0�Ȃ�)</param>
	/// <returns>�g���K�[��</returns>
	bool TriggerclickLeft(BYTE mouseNumber);

	void Mousemove();

	MouseMove GetMouseMove();

private: //�����o�ϐ�
	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devkeyboard;
	//�}�E�X�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devmouse;
	//�S�L�[�̓��͏����擾����
	BYTE key[256] = {};
	//�O�t���[���̑S�L�[�̓��͏����擾����
	BYTE oldkey[256] = {};
	//�}�E�X�̓��͏����擾����
	DIMOUSESTATE mouse;
	//�O�t���[���̃}�E�X�̓��͏����擾����
	DIMOUSESTATE oldmouse;
	//�C���X�^���X����
	ComPtr<IDirectInput8> dinput = nullptr;
	//WindowsAPI
	WindowsApp* winApp = nullptr;

	//�}�E�Xx���W
	float mouseX = 0;
	//�}�E�Xy���W
	float mouseY = 0;
	//1�t���[���O�̃}�E�Xx���W
	float oldMouseX = 0;
	//1�t���[���O�̃}�E�Xy���W
	float oldMouseY = 0;
	//x���̈ړ����x
	float velx = 0;
	//x���̈ړ����x
	float vely = 0;

};

