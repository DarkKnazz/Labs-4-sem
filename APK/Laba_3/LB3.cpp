#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

char color = 0x01;  

struct VIDEO
{
  unsigned char symb; 
  unsigned char attr;
};

void get_reg();
void print(int, int, int);

void interrupt(*int70) (...);
void interrupt(*int71) (...);
void interrupt(*int72) (...);
void interrupt(*int73) (...);
void interrupt(*int74) (...);
void interrupt(*int75) (...);
void interrupt(*int76) (...);
void interrupt(*int77) (...);

void interrupt(*int8) (...);
void interrupt(*int9) (...);
void interrupt(*intA) (...);
void interrupt(*intB) (...);
void interrupt(*intC) (...);
void interrupt(*intD) (...);
void interrupt(*intE) (...);
void interrupt(*intF) (...);

void interrupt  new8(...) { get_reg(); int8(); }
void interrupt  new9(...) { color++; get_reg(); int9(); }
void interrupt  newA(...) { get_reg(); intA(); }
void interrupt  newB(...) { get_reg(); intB(); }
void interrupt  newC(...) { get_reg(); intC(); }
void interrupt  newD(...) { get_reg(); intD(); }
void interrupt  newE(...) { get_reg(); intE(); }
void interrupt  newF(...) { get_reg(); intF(); }

void interrupt  new70(...) { get_reg(); int70(); }
void interrupt  new71(...) { get_reg(); int71(); }
void interrupt  new72(...) { get_reg(); int72(); }
void interrupt  new73(...) { get_reg(); int73(); }
void interrupt  new74(...) { get_reg(); int74(); }
void interrupt  new75(...) { get_reg(); int75(); }
void interrupt  new76(...) { get_reg(); int76(); }
void interrupt  new77(...) { get_reg(); int77(); }

void print(int val, int y, int x)
{
      char temp;
      VIDEO far* screen = (VIDEO far *)MK_FP(0xB800, 0);
      screen += ( y * 80 + x );

	  int i;
	  for(i = 7; i >= 0; i--) {
		temp = val%2;
		val /=2;
		screen->symb = temp + '0';
		if(color == 0x07)
			color = 0x01;
		screen->attr = color;
		screen++;
      }
}

void get_reg()
{
	//получаем данные для регистра запросов ВЕДУЩЕГО и печатаем
	outp(0x20, 0x0A);
	print(inp(0x20), 3, 12);

	//получаем данные для регистра обслуживания ВЕДУЩЕГО
	outp(0x20, 0x0B);
	print(inp(0x20), 5, 12);

	//р-р масок ВЕДУЩЕГО
	print(inp(0x21), 7, 12);

	//все тоже для ведомого
	outp(0xA0, 0x0A);
	print(inp(0xA0), 9, 12);

	outp(0xA0, 0x0B);
	print(inp(0xA0), 11, 12);

	print(inp(0xA1), 13, 12);
}

void init()
{

	int70 = getvect(0x70);
	int71 = getvect(0x71);
	int72 = getvect(0x72);
	int73 = getvect(0x73);
	int74 = getvect(0x74);
	int75 = getvect(0x75);
	int76 = getvect(0x76);
	int77 = getvect(0x77);

	int8 = getvect(0x08);
	int9 = getvect(0x09);
	intA = getvect(0x0A);
	intB = getvect(0x0B);
	intC = getvect(0x0C);
	intD = getvect(0x0D);
	intE = getvect(0x0E);
	intF = getvect(0x0F);

	setvect(0xB0, new8);
	setvect(0xB1, new9);
	setvect(0xB2, newA);
	setvect(0xB3, newB);
	setvect(0xB4, newC);
	setvect(0xB5, newD);
	setvect(0xB6, newE);
	setvect(0xB7, newF);

	setvect(0X08, new70);
	setvect(0X09, new71);
	setvect(0X0A, new72);
	setvect(0X0B, new73);
	setvect(0X0C, new74);
	setvect(0X0D, new75);
	setvect(0X0E, new76);
	setvect(0X0F, new77);


	_disable();

	//Ведущий
	outp(0X20, 0x11);
	outp(0X21, 0xB0);
	outp(0x21, 0x04);
	outp(0X21, 0x01);

	//Ведомый
	outp(0xA0, 0x11);
	outp(0xA1, 0x08);
	outp(0xA1, 0x02);
	outp(0xA1, 0x01);

	_enable();

}

int main()
{
      unsigned far *fp;
      init();

      FP_SEG (fp) = _psp;
      FP_OFF (fp) = 0x2c;

      _dos_freemem(*fp);

      _dos_keep(0, (_DS -_CS) + (_SP/16) + 1);
	return 0;
}