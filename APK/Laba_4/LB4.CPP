#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

void get_Random_Number(unsigned);

void tm_sound(int freq, int time)
	{
	  int cnt;

	  outp(0x43, 0xb6);

	  cnt = (int)(1193180L / freq);

	  outp(0x42, cnt % 256);
	  outp(0x42, cnt);

	  outp(0x61, inp(0x61) | 3);
	  delay(time);
	  outp(0x61, inp(0x61) & 0xfc);
}

void value_Timer(int freq, int freq2) { //Setting counter
	short value;
	value = 1193180 / freq;        //calculating value for counter of timer
    outp(0x42, value%256);
    value/=256;
    outp(0x42, value);
    delay(freq2);
}

void koefficent_Channel() {
	long max=0,h,l,element;
	long i;
	for ( i = 0; i<65535; i++)
	{
		outp(0x43, 0x00);// 0000 0000
		l = inp(0x40);
		h = inp(0x40);
		element = h*256 + l;
		if (element > max)
			max = element;
	}
	printf ("%hx\n",max);
	max = 0;
	for ( i = 0; i<65535; i++)
	{
		outp(0x43, 0x40); // 0100 0000
		l = inp(0x41);
		h = inp(0x41);
		element = h*256 + l;
		if (element > max)
			max = element;
	}
	printf ("%hx\n",max);
	max = 0;
	for ( i = 0; i<65535; i++)
	{
		outp(0x43, 0x80); //1000 0000
		l = inp(0x42);
		h = inp(0x42);
		element = h*256 + l;
		if (element > max)
			max = element;
	}
	printf ("%hx\n",max);
	max = 0;

}

void words_of_Channel ()//Reading the words of channel
{
	unsigned char t;
	char *str;
	str = (char*)calloc(9, sizeof(char));

  //Reading the first Channel
	outp(0x43, 0xe2);           	//11100010b
	t = inp(0x40);
	itoa(t, str, 2);
	printf("Condition word 0: %s\n", str);
	//Reading the second channel
	outp(0x43, 0xe4);             //11100100b
	t = inp(0x41);
	itoa(t, str, 2);
	printf("Condition word 1: %s\n", str);
	//Reading the third channel
	outp(0x43, 0xe8);             //11101000b
	t = inp(0x42);
	itoa(t, str, 2);
	printf("Condition word 2: %s\n", str);

	free(str);
}

int main() {
	int music[] = { 659, 622, 659, 622, 659, 493, 622, 523, 440 };

		int duraion[] =
		{
		  200,200,200,200,200,200,200,200,200
		};


	words_of_Channel();
	printf("////////////////////////////////////\n");
	for(i = 0; i < 9; i++) {
		tm_sound(mary[i], del[i]);
	}
	koefficent_Channel();

	printf("\nGetting random number(0-out):\n");
	unsigned k = 1;
	while (k!=0) {
		printf("Enter the number:\n");
		scanf("%u",&k);
		if (k==0)
			break;
		get_Random_Number(k);
	}
	system("pause");
	return 0;
}

void get_Random_Number (unsigned num) {
	unsigned random_Number;
	outp (0x43, 0xB4);
	outp (0x42, num%256);
	num /= 256;

	outp(0x42, num);
	outp(0x61, inp(0x61) | 0x01);
	getch();
	outp (0x70, 0x00);
	//int sekond = inp(0x71);
	//delay(sekond);
	outp (0x43, 0x86);
	random_Number = inp(0x42);
	random_Number = inp(0x42)*256 + random_Number;
	printf("%u\n", random_Number);

	outp (0x61, inp(0x61) & 0xFC);
}
