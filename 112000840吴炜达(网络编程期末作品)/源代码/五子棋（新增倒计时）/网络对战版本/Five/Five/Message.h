#pragma once
typedef struct  tagStep { //����һ��������ݽṹ
    int x;
    int y;
    int color;
} STEP;

typedef struct tagMsgStruct {
    // ��ϢID
    UINT uMsg;
    // ������Ϣ
    int x;
    int y;
    int color;
    // ��Ϣ����
    TCHAR szMsg[128];
} MSGSTRUCT;

//���������Ϣ
#define MSG_DROPDOWN    0x01 //����
#define MSG_ROLLBACK    0x02 //����
#define MSG_AGREEBACK   0x03 //ͬ�����
#define MSG_REFUSEDBACK 0x04 //�ܾ�����
#define MSG_DRAW		  0x05 //����
#define MSG_AGREEDRAW  0x06 //ͬ�����
#define MSG_REFUSEDRAW 0x07 //�ܾ�����
#define MSG_GIVEUP     0x08 //����
#define MSG_CHAT       0x09 //����
#define MSG_OPPOSITE   0x0a //������Ϣ
#define MSG_PLAYAGAIN   0x0b //�ٴο���
#define MSG_AGREEAGAIN  0x0c //ͬ���ٴο���