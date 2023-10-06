#pragma once
#include <xaudio2.h>

#include <cstdint>
#include <wrl.h>
#include <map>
#include <string>

class Audio
{
public:
    // �`�����N�w�b�_
    struct ChunkHeader
    {
        char id[4]; // �`�����N����ID
        int32_t size;  // �`�����N�T�C�Y
    };

    // RIFF�w�b�_�`�����N
    struct RiffHeader
    {
        ChunkHeader chunk;   // "RIFF"
        char type[4]; // "WAVE"
    };

    // FMT�`�����N
    struct FormatChunk
    {
        ChunkHeader chunk; // "fmt "
        WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
    };

    class XAudio2VoiceCallback : public IXAudio2VoiceCallback
    {
    public:
        // �{�C�X�����p�X�̊J�n��
        STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
        // �{�C�X�����p�X�̏I����
        STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
        // �o�b�t�@�X�g���[���̍Đ����I��������
        STDMETHOD_(void, OnStreamEnd) (THIS) {};
        // �o�b�t�@�̎g�p�J�n��
        STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
        // �o�b�t�@�̖����ɒB������
        STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {};
        // �Đ������[�v�ʒu�ɒB������
        STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
        // �{�C�X�̎��s�G���[��
        STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
    };

    // �����f�[�^
    struct SoundData
    {
        // �g�`�t�H�[�}�b�g
        WAVEFORMATEX wfex;
        // �o�b�t�@�̐擪�A�h���X
        BYTE* pBuffer;
        // �o�b�t�@�̃T�C�Y
        unsigned int bufferSize;
    };

    void Initialize(const std::string directoryPath="Resources/");

    void Finalize();

    void LoadWave(const std::string filename);

    void Unload(SoundData* sounddata);

    void PlayWave(const std::string filename);

private:
    //Xaudio2�̃C���X�^���X
    Microsoft::WRL::ComPtr<IXAudio2> xAudio2a;

    std::map<std::string, SoundData> soundDatasa;
    //�T�E���h�i�[�f�B���N�g��
    std::string directoryPatha;
};

