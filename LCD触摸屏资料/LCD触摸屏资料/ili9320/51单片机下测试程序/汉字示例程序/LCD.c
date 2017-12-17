#include <reg51.h>


/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


#define  LCD_DataPortH P2     //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P0     //��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����,��ȷ��P0���Ѿ�����10K����,����̫С����С4.7K,�Ƽ�10K.
sbit LCD_RS = P3^5;  		 //����/�����л�
sbit LCD_WR = P3^6;		  //д����
sbit LCD_RD =P3^7;		     //������
sbit LCD_CS=P1^0;		//Ƭѡ	
sbit LCD_REST = P1^2;	      //��λ   


void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}


void main_Write_COM( int  DH)	 //����
{	
    LCD_RS=0;
	LCD_CS =0;	 
	P2=DH>>8;	
	P0=DH;		
	LCD_WR=0;
	LCD_WR=1;
	LCD_CS =1;	
}
void cld_write_color(char hh,char ll)	//������ɫ����Ϊ����ٶȸ�8λ��8λ�ֱ𴫵�	
{
    LCD_RS=1;
	LCD_CS =0;	  				
	P2=hh;	
	P0=ll;					
	LCD_WR=0;
	LCD_WR=1;
	LCD_CS =1;	
}
void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	cld_write_color(m,n);

}
void main_Write_DATA(int DH)	//����	
{
    LCD_RS=1;
	LCD_CS =0;	  				
	P2=DH>>8;	
	P0=DH;					
	LCD_WR=0;
	LCD_WR=1;
	LCD_CS =1;	
}


void main_W_com_data( int com1,dat1)	//��������һ�� 
{
   main_Write_COM(com1);
   main_Write_DATA(dat1);
}

void LCD_SetPos(unsigned int x1,unsigned int x2,unsigned int y1,unsigned int y2)
{
	main_Write_COM(0x0020);main_Write_DATA(x1);	  //����X����λ��
    main_Write_COM(0x0021);main_Write_DATA(y1);   //����Y����λ��
    main_Write_COM(0x0050);main_Write_DATA(x1);   //��ʼX
	main_Write_COM(0x0052);main_Write_DATA(y1);	  //��ʼY
    main_Write_COM(0x0051);main_Write_DATA(x2);   //����X
	main_Write_COM(0x0053);main_Write_DATA(y2);   //����Y
    main_Write_COM(0x0022);							 
}

void Lcd_Init(void)
{

    LCD_REST=1;
    delayms(5);	
	LCD_REST=0;
	delayms(5);
	LCD_REST=1;
	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delayms(5);
	

	LCD_CS =0;  //��Ƭѡʹ��
	//************* Start Initial Sequence **********//
 main_W_com_data(0x00e5, 0x8000);	
		main_W_com_data(0x0000, 0x0001);	
		main_W_com_data(0x0001, 0x0100);
		main_W_com_data(0x0002, 0x0700);
		main_W_com_data(0x0003, 0x1030);
		main_W_com_data(0x0004, 0x0000);
		main_W_com_data(0x0008, 0x0202);	
		main_W_com_data(0x0009, 0x0000);	
		main_W_com_data(0x000A, 0x0000);
		main_W_com_data(0x000C, 0x0000);	
		main_W_com_data(0x000D, 0x0000);	
		main_W_com_data(0x000F, 0x0000);	
	//-----Power On sequence-----------------------	
		main_W_com_data(0x0010, 0x0000);	
		main_W_com_data(0x0011, 0x0007);	
		main_W_com_data(0x0012, 0x0000);	
		main_W_com_data(0x0013, 0x0000);	
		delayms(150);
		main_W_com_data(0x0010, 0x17B0);	
		main_W_com_data(0x0011, 0x0007);	
		delayms(50);
		main_W_com_data(0x0012, 0x013A);	
		delayms(50);
		main_W_com_data(0x0013, 0x1A00);	
		main_W_com_data(0x0029, 0x000c);		
		delayms(50);
	//-----Gamma control-----------------------	
		main_W_com_data(0x0030, 0x0000);	
		main_W_com_data(0x0031, 0x0505);	
		main_W_com_data(0x0032, 0x0004);	
		main_W_com_data(0x0035, 0x0006);	
		main_W_com_data(0x0036, 0x0707);	
		main_W_com_data(0x0037, 0x0105);	
		main_W_com_data(0x0038, 0x0002);	
		main_W_com_data(0x0039, 0x0707);	
		main_W_com_data(0x003C, 0x0704);	
		main_W_com_data(0x003D, 0x0807);	
	//-----Set RAM area-----------------------	
		main_W_com_data(0x0050, 0x0000);
		main_W_com_data(0x0051, 0x00EF);
		main_W_com_data(0x0052, 0x0000);
		main_W_com_data(0x0053, 0x013F);
		main_W_com_data(0x0060, 0x2700);
		main_W_com_data(0x0061, 0x0001);
		main_W_com_data(0x006A, 0x0000);
		main_W_com_data(0x0021, 0x0000);	
		main_W_com_data(0x0020, 0x0000);	
	//-----Partial Display Control------------	
		main_W_com_data(0x0080, 0x0000);	
		main_W_com_data(0x0081, 0x0000);
		main_W_com_data(0x0082, 0x0000);
		main_W_com_data(0x0083, 0x0000);
		main_W_com_data(0x0084, 0x0000);	
		main_W_com_data(0x0085, 0x0000);
	//-----Panel Control----------------------
		main_W_com_data(0x0090, 0x0010);	
		main_W_com_data(0x0092, 0x0000);
		main_W_com_data(0x0093, 0x0003);
		main_W_com_data(0x0095, 0x0110);
		main_W_com_data(0x0097, 0x0000);	
		main_W_com_data(0x0098, 0x0000);
	//-----Display on-----------------------	
		main_W_com_data(0x0007, 0x0173);	
		delayms(50);
		 main_Write_COM(0x0022);	

	LCD_CS =1;  //�ر�Ƭѡʹ��

}

/////////////////////////////////////////////////////////////
#include "8X16.h"
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);
 for(i=0; i<16;i++) {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			}
		}
}


void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor) {

		LCD_PutChar8x16( x, y, c, fColor, bColor );
	}


#include "GB1616.h"	//16*16������ģ

void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+16-1,y, y+16-1);

	for (k=0;k<64;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1])){ 
    	for(i=0;i<32;i++) {
		  unsigned short m=codeGB_16[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			} 
		  }
		}  
	  }	
	}

	#include "GB3232.h"	//32*32������ģ

void PutGB3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+32-1,y, y+32-1);

	for (k=0;k<15;k++) { //15��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if ((codeGB_32[k].Index[0]==c[0])&&(codeGB_32[k].Index[1]==c[1])){ 
    	for(i=0;i<128;i++) {
		  unsigned short m=codeGB_32[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			} 
		  }
		}  
	  }	
	}

void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) {
	 unsigned char l=0;
	while(*s) {
		if( *s < 0x80) 
		    {
			LCD_PutChar(x+l*8,y,*s,fColor,bColor);
			s++;l++;
			}
		else
		    {
			PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
			s+=2;l+=2;
			}
		}
	}


void Pant(unsigned int color)
{
	int i,j;


    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
         main_Write_DATA(color);
	    }

	  }		
}

main()
{

	Lcd_Init();          //TFT��ʼ��
		while(1)
	{ 
 	Pant(0xffff);	 //TFT����

LCD_PutString(40,60,"I LOVE MY JOB ",Blue2,Yellow);

LCD_PutString(40,100,"רҵ����֧����̳",0x07e0,0xf800);
LCD_PutString(40,120,"רҵ�����幤�ذ�",0xF800,Yellow);
LCD_PutString(40,140,"1234567890",0xF800,Yellow);
LCD_PutString(20,160,"abcdefghijklmnopqistuvwxyz",0xF800,Yellow);
LCD_PutString(20,180,"`,./<>';:[]{}\|?)(-=+*&^%$",0xF800,Yellow);
PutGB3232(20,200,"��",Blue,Yellow);	//д��32x32����
PutGB3232(60,200,"��",Blue,Red);
PutGB3232(100,200,"��",Blue,Magenta);
PutGB3232(140,200,"Ƭ",Blue,Green);
PutGB3232(180,200,"��",Blue,Cyan);	
PutGB3232(20,240,"��",Blue,0X00);	
PutGB3232(60,240,"ҫ",Blue,0X00);	
PutGB3232(100,240,"��",Blue,0X00);	
PutGB3232(140,240,"��",Blue,0X00);	
PutGB3232(180,240,"��",Blue,0X00);
PutGB3232(20,280,"��",Blue,0X00);		
PutGB3232(60,280,"��",Blue,0X00);	
PutGB3232(100,280,"ӭ",Blue,0X00);	
PutGB3232(140,280,"��",Blue,0X00);	
PutGB3232(180,280,"��",Blue,0X00);	
	delayms(500);
}

}













