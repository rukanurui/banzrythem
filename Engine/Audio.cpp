#include "Audio.h"
#include <Windows.h>
#pragma comment(lib,"xaudio2.lib")
#include <cassert>
#include <fstream>

void Audio::Initialize(const std::string directoryPath)
{
    directoryPatha = directoryPath;
    HRESULT result;
    IXAudio2MasteringVoice* masterVoice;

    // XAudio�G���W���̃C���X�^���X�𐶐�
    result = XAudio2Create(&xAudio2a, 0, XAUDIO2_DEFAULT_PROCESSOR);
    assert(SUCCEEDED(result));

    // �}�X�^�[�{�C�X�𐶐�
    result = xAudio2a->CreateMasteringVoice(&masterVoice);
    assert(SUCCEEDED(result));
}

void Audio::Finalize()
{
       //XAudio2���
       xAudio2a.Reset();
       // �����f�[�^���
       std::map< std::string, SoundData>::iterator it = soundDatasa.begin();
       for (;it !=soundDatasa.end();++it)
       {

           Unload(&it->second);
       }
       soundDatasa.clear();

}

void Audio::LoadWave(const std::string filename)
{
    if (soundDatasa.find(filename) != soundDatasa.end())
    {
        //�d���ǂݍ��݂Ȃ̂ŁA��������������
        return;
    }

    std::string fullpath = directoryPatha + filename;

    // �t�@�C�����̓X�g���[���̃C���X�^���X
    std::ifstream file;
    // .wav�t�@�C�����o�C�i�����[�h�ŊJ��
    file.open(filename, std::ios_base::binary);
    // �t�@�C���I�[�v�����s�����o����
    assert(file.is_open());

    // RIFF�w�b�_�[�̓ǂݍ���
    RiffHeader riff;
    file.read((char*)&riff, sizeof(riff));
    // �t�@�C����RIFF���`�F�b�N
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    // �^�C�v��WAVE���`�F�b�N
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }

    // Format�`�����N�̓ǂݍ���
    FormatChunk format = {};
    // �`�����N�w�b�_�[�̊m�F
    file.read((char*)&format, sizeof(ChunkHeader));
    if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
        assert(0);
    }
    // �`�����N�{�̂̓ǂݍ���
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char*)&format.fmt, format.chunk.size);

    // Data�`�����N�̓ǂݍ���
    ChunkHeader data;
    file.read((char*)&data, sizeof(data));
    // JUNK�`�����N�����o�����ꍇ
    if (strncmp(data.id, "JUNK ", 4) == 0) {
        // �ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
        file.seekg(data.size, std::ios_base::cur);
        // �ēǂݍ���
        file.read((char*)&data, sizeof(data));
    }

    if (strncmp(data.id, "data ", 4) != 0) {
        assert(0);
    }

    // Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
    char* pBuffer = new char[data.size];
    file.read(pBuffer, data.size);

    // Wave�t�@�C�������
    file.close();

    // return����ׂ̉����f�[�^
    SoundData soundData = {};

    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
    soundData.bufferSize = data.size;

    //�T�E���h�f�[�^��A�z�z��Ɋi�[
    soundDatasa.insert(std::make_pair(filename, soundData));
}

void Audio::Unload(SoundData* sounddata)
{
    // �o�b�t�@�̃����������
    delete[] sounddata->pBuffer;

    sounddata->pBuffer = 0;
    sounddata->bufferSize = 0;
    sounddata->wfex = {};
}

void Audio::PlayWave(const std::string filename)
{
    HRESULT result;

    std::map< std::string, SoundData>::iterator it = soundDatasa.find(filename);
    assert(it != soundDatasa.end());

    SoundData& soundData = it->second;

    // �g�`�t�H�[�}�b�g������SourceVoice�̐���
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2a->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));

    // �Đ�����g�`�f�[�^�̐ݒ�
    XAUDIO2_BUFFER buf{};
    buf.pAudioData = soundData.pBuffer;
    buf.AudioBytes = soundData.bufferSize;
    buf.Flags = XAUDIO2_END_OF_STREAM;

    // �g�`�f�[�^�̍Đ�
    result = pSourceVoice->SubmitSourceBuffer(&buf);
    result = pSourceVoice->Start();
}
