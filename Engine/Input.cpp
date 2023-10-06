#include "Input.h"



#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;


void Input::Initialize(WindowsApp* winApp)
{

    HRESULT result;

    this->winApp = winApp;

    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

    //ComPtr<IDirectInputDevice8> devkeyboard = nullptr;
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
    result = dinput->CreateDevice(GUID_SysMouse, &devmouse, NULL);
    //���̓f�[�^�`���̃Z�b�g
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); //�W���`��
    result = devmouse->SetDataFormat(&c_dfDIMouse); //�W���`��
    //�r�����䃌�x���̃Z�b�g
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

    result = devmouse->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{

    HRESULT result;

    //�O��̃L�[���͂�ۑ�
    memcpy(oldkey, key, sizeof(key));
    
    //�L�[�{�[�h���̎擾�J�n
    result = devkeyboard->Acquire();
    
    result = devkeyboard->GetDeviceState(sizeof(key), key);

    //�}�E�X���̎擾�J�n
    result = devmouse->Acquire();
    //�O��̃}�E�X���͂�ۑ�
    oldmouse = mouse;

    SetCursorPos(990, 540);

    ShowCursor(FALSE);

    result = devmouse->GetDeviceState(sizeof(mouse), &mouse);
}

Input* Input::GetInstance()
{
    static Input instance;

    return &instance;
}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) {
        return true;
    }
    //�����łȂ����false
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    //�O�񉟂��ĂȂ��A���񉟂��Ă���
    if (!oldkey[keyNumber] && key[keyNumber]) {
        return true;
    }
    //�����łȂ����false
    return false;
}

bool Input::PushclickLeft()
{
    if (mouse.rgbButtons[0])
    {
        return true;
    }
    return false;
}

bool Input::PushclickRight()
{
    if (mouse.rgbButtons[1])
    {
        return true;
    }
    return false;
}

bool Input::TriggerclickLeft(BYTE mouseNumber)
{
    if (!oldmouse.rgbButtons[0] && mouse.rgbButtons[0])
    {
        return true;
    }
    return false;
}

void Input::Mousemove()
{
    if (mouse.lX > 0) velx = 0.1f;

    if (mouse.lX < 0)velx = -0.1f;

}

Input::MouseMove Input::GetMouseMove()
{
    MouseMove tmp;
    tmp.lX = mouse.lX;
    tmp.lY = mouse.lY;
    tmp.lZ = mouse.lZ;
    return tmp;
}



