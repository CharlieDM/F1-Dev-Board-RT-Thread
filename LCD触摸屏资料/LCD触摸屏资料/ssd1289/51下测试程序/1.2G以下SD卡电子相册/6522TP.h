/*-----------------------------------------------
  ���ƣ�д����
  ��˾��
  ��վ��
  ��д��
  ���ڣ�
  ���ݣ�320x240���ء�16λBMPͼƬ��HEX���ݣ�����д�����ϣ���ԭͼƬ
  ע�����
------------------------------------------------*/
/*˶ҫ���ӿƼ� http://hyao.taobao.com/ 
��Ƭ��������ѹ3.3V
����Ĭ��IO���ӷ�ʽ��

�����ߣ�RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^1;

������: DB0-DB7��������P0^0-P0^7;  DB8-DB15��������P2^0-P2^7;

�����������ӷ�ʽ��(��ʹ�ô����ɲ�����)
D_CLK-P1^2;  D_CS-P1^3;  D_DIN-P1^4;  D_OUT-P1^6;  D_PENIRQ-P1^7;

SD�����ߣ�(��ʹ�ô����ɲ�����)
SD_MISO-P31;  SD_SCK-P32;  SD_MOSI-P33;  SD_CS-P34;
*/
#include"reg52.h"
//============================================================
//����оƬ���϶���
#define WINDOW_XADDR_START	0x0050 // ˮƽ�Ŀ�ʼ��ַ��
#define WINDOW_XADDR_END	0x0051 // ˮƽ�Ľ�����ַ��
#define WINDOW_YADDR_START	0x0052 // ��ֱ�Ŀ�ʼ��ַ��
#define WINDOW_YADDR_END	0x0053 // ��ֱ�Ľ�����ַ��
#define GRAM_XADDR		    0x0020 // GRAM ˮƽ�ĵ�ַ��
#define GRAM_YADDR		    0x0021 // GRAM ��ֱ�ĵ�ַ��
#define GRAMWR 			    0x0022 // ����д

//=============================================================
//����Һ�����ӿ�
sbit CS=P1^0;		//Ƭѡ
sbit RES=P1^1;		//��λ
sbit RS=P3^5;		//����/����ѡ��
sbit RW=P3^6;
                    //���ݿ�ʹ��P2 P0
//====================================================//
//��������
void LGDP6522_init(void);							   //LCD��ʼ��
void Init_data(unsigned char x, unsigned int y);   //д��������
void Write_Cmd(unsigned char DH,unsigned char DL);	   //д����
void Write_Data(unsigned char DH,unsigned char DL);	   //д����
void delayms(unsigned int tt); //��ʱ����
void  Write_Data_U16(unsigned int y); //д16λ����
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1); //��������
void ClearScreen(unsigned int bColor);	//����

//===============================================================
//����
void ClearScreen(unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<320;i++)
	{
	
	   for (j=0;j<240;j++)
	       Write_Data_U16(bColor);
	}
}


//===============================================================
//д��������

void Init_data(unsigned char x, unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Cmd(0x00,x);
	Write_Data(m,n);

}



//==============================================================
//д16λ����
void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}
//=============================================================
//д����

void Write_Cmd(unsigned char DH,unsigned char DL)
{
  
	CS=0;
	RS=0;

	P2=DH;
	P0=DL;
	
	RW=0;
	RW=1;
	CS=1;
}

//===================================================================
//д����

void Write_Data(unsigned char DH,unsigned char DL)
{
 
  
	
	CS=0;
	
	RS=1;
	P2=DH;

	P0=DL;	
	RW=0;
	RW=1;
	CS=1;
}





//============================================================
//��ʱ����
void delayms(unsigned int count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<260;j++);
       }                                                                                     
}



//=============================================================
//Һ����ʼ��

void LGDP6522_init(void)
{ 
  	CS=0;
delayms(50);//�����ʵ�������ʱ�������ȶ���ʾ
Init_data(0x0000,0x0001);    delayms(1);  //�򿪾���
    Init_data(0x0003,0xA8A4);    delayms(1);   //0xA8A4
    Init_data(0x000C,0x0000);    delayms(1);   
    Init_data(0x000D,0x080C);    delayms(1);   
    Init_data(0x000E,0x2B00);    delayms(1);   
    Init_data(0x001E,0x00B0);    delayms(1);   
    Init_data(0x0001,0x2B3F);    delayms(1);   //�����������320*240  0x6B3F
    Init_data(0x0002,0x0600);    delayms(1);
    Init_data(0x0010,0x0000);    delayms(1);
    Init_data(0x0011,0x6070);    delayms(1);        //0x4030           //�������ݸ�ʽ  16λɫ 
    Init_data(0x0005,0x0000);    delayms(1);
    Init_data(0x0006,0x0000);    delayms(1);
    Init_data(0x0016,0xEF1C);    delayms(1);
    Init_data(0x0017,0x0003);    delayms(1);
    Init_data(0x0007,0x0233);    delayms(1);        //0x0233       
    Init_data(0x000B,0x0000);    delayms(1);
    Init_data(0x000F,0x0000);    delayms(1);        //ɨ�迪ʼ��ַ
    Init_data(0x0041,0x0000);    delayms(1);
    Init_data(0x0042,0x0000);    delayms(1);
    Init_data(0x0048,0x0000);    delayms(1);
    Init_data(0x0049,0x013F);    delayms(1);
    Init_data(0x004A,0x0000);    delayms(1);
    Init_data(0x004B,0x0000);    delayms(1);
    Init_data(0x0044,0xEF00);    delayms(1);
    Init_data(0x0045,0x0000);    delayms(1);
    Init_data(0x0046,0x013F);    delayms(1);
    Init_data(0x0030,0x0707);    delayms(1);
    Init_data(0x0031,0x0204);    delayms(1);
    Init_data(0x0032,0x0204);    delayms(1);
    Init_data(0x0033,0x0502);    delayms(1);
    Init_data(0x0034,0x0507);    delayms(1);
    Init_data(0x0035,0x0204);    delayms(1);
    Init_data(0x0036,0x0204);    delayms(1);
    Init_data(0x0037,0x0502);    delayms(1);
    Init_data(0x003A,0x0302);    delayms(1);
    Init_data(0x003B,0x0302);    delayms(1);
    Init_data(0x0023,0x0000);    delayms(1);
    Init_data(0x0024,0x0000);    delayms(1);
    Init_data(0x0025,0x8000);    delayms(1);
    Init_data(0x004f,0);        //����ַ0
    Init_data(0x004e,0);        //����ַ0
	Write_Cmd(0x0022);


/*	Init_data(0x0001,0x0100); //Դɨ������SS=0, ������ƶ������Ǵ�S1��S720
	//��Դɨ������SS=1, ������ƶ������Ǵ�S720��S1��
	//SM=0������ɨ�裨SM=1������ɨ�裩

	Init_data(0x0002,0x0700); //B/C=1��EOR=1���е��ã�B/C=0��֡/�����ã�
	Init_data(0x0003,0x1030); //AM=0����ַ��ˮƽ�����Զ���1
	//I/D[1:0] = 11��ˮƽ��ֱ���������
	//BGR=1:����BGR��ʽ
	//TRI=0��DFM=*��8λ�����������ݴ���
	Init_data(0x0004,0x0000); //�����������ã�������
	
	//��ʾ����
	Init_data(0x0008,0x0207); //���ú���غ�ǰ�� 
	Init_data(0x0009,0x0000);//���÷���ʾ��ʱ����ISC[3:0]
	Init_data(0x000A,0x0000); //֡��ǹ���

	Init_data(0x000C,0x0000);//RGB��ʾ�ӿڿ���1
	Init_data(0x000D,0x0000);//֡���λ��
	Init_data(0x000F,0x0000);//RGB��ʾ�ӿڿ���2
	
	//��Դ����
	Init_data(0x0010,0x0000);   
	Init_data(0x0011,0x0007);  
	Init_data(0x0012,0x0000);  
	Init_data(0x0013,0x0000); 
	//vgh 
	Init_data(0x0010,0x1290);   
	Init_data(0x0011,0x0227);
	//delayms(100);
	//vregiout 
	Init_data(0x0012,0x001d); //0x001b
	//delayms(100); 
	//vom amplitude
	Init_data(0x0013,0x1500);
	//delayms(100); 
	//vom H
	Init_data(0x0029,0x0018); 
	Init_data(0x002B,0x000D); 
	
	//٤��У��
	Init_data(0x0030,0x0004);
	Init_data(0x0031,0x0307);
	Init_data(0x0032,0x0002);//0006
	Init_data(0x0035,0x0206);
	Init_data(0x0036,0x0408);
	Init_data(0x0037,0x0507); 
	Init_data(0x0038,0x0204);//0200
	Init_data(0x0039,0x0707); 
	Init_data(0x003C,0x0405);//0504
	Init_data(0x003D,0x0F02); 
	
	//��������
	Init_data(0x0050,0x0000);//ˮƽ��ʼλ��
	Init_data(0x0051,0x00EF);//ˮƽ��ֹλ��
	Init_data(0x0052,0x0000);//��ֱ��ʼλ��
	Init_data(0x0053,0x013F);//��ֱ��ֹλ��

	Init_data(0x0060,0xA700);//��ɨ�����ã�GS=1����G320ɨ�赽G1��320��
	Init_data(0x0061,0x0001); 
	Init_data(0x006A,0x0000);
	//
	Init_data(0x0080,0x0000); 
	Init_data(0x0081,0x0000); 
	Init_data(0x0082,0x0000); 
	Init_data(0x0083,0x0000); 
	Init_data(0x0084,0x0000); 
	Init_data(0x0085,0x0000); 
	//
	Init_data(0x0090,0x0010); 
	Init_data(0x0092,0x0600); 
	Init_data(0x0093,0x0003); 
	Init_data(0x0095,0x0110); 
	Init_data(0x0097,0x0000); 
	Init_data(0x0098,0x0000);
	Init_data(0x0007,0x0133);
	//write_cmd_data(0x0022);*/			
  	CS=1;
//	Write_Cmd_Data(0x0022);//		
}



//===============================================================

//===============================================================
//��������
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{ 
  Init_data(WINDOW_XADDR_START,x0);
  Init_data(WINDOW_XADDR_END,x1);
  Init_data(WINDOW_YADDR_START,y0);
  Init_data(WINDOW_YADDR_END,y1);
  Init_data(GRAM_XADDR,x0);
  Init_data(GRAM_YADDR,y0);
  Write_Cmd (0x00,0x22);//LCD_WriteCMD(GRAMWR);
}


