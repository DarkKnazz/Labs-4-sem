	#include <stdio.h>
	#include <conio.h>
	#include <dos.h>
	#include <windows.h>
	#include <stdlib.h>
	
	void sound(int, int);
	int rnd_set(int bound);
	void tm_sound(int freq, int time);
	void coefficient();

	// Array of frequences
	int mary[] =
	{
	  659, 622, 659, 622, 659, 493, 622, 523, 440
	};

	// Array of durations
	int del[] =
	{
	  200,200,200,200,200,200,200,200,200
	};

	int main(void)
	{
	  int i;
	
	  outp(0x43, 0xe2);
	
	  printf("\nCondition word of channel 1: %d\n",inp(0x40));

	  outp(0x43, 0xe4);
	
	  printf("\nCondition word of channel 2: %d\n",inp(0x41));

	  outp(0x43, 0xe8);
	  printf("\nCondition word of channel 3: %d\n",inp(0x42));
	  for(i=0 ;i < 9;i++)
	    tm_sound(mary[i], del[i]);
	  coefficient();
	  return 0;
	}

	void tm_sound(int freq, int time)
	{
	  int cnt;

	  // Задаем режим канала 2 таймера
	  outp(0x43, 0xb6);

	  // Вычисляем задержку для загрузки в
	  // регистр счетчика таймера
	  cnt = (int)(1193180L / freq);

	  // Загружаем регистр счетчика таймера - сначала
	  // младший, затем старший байты
	  outp(0x42, cnt % 256);
	  outp(0x42, cnt);

	  // Включаем громкоговоритель. Сигнал от
	  // канала 2 таймера теперь будет проходить
	  // на вход громкоговорителя
	  outp(0x61, inp(0x61) | 3);
	  // Выполняем задержку.
	  delay(time);
	  // Выключаем громкоговоритель.
	  outp(0x61, inp(0x61) & 0xfc);
	}

void coefficient() 
{ 
	unsigned short ans = 0, temp = 0; 
	long j;
	int i; 
	char *str; 
	str=(char*)malloc(5);
	for (i = 0; i < 3; i++) 
	{ 

		for (j = 0; j < 65535; j++) 
		{ 

			if (i == 0) 
				outp(0x43, 0x00); 
			if (i == 1) 
				outp(0x43, 0x40); 
			if (i == 2) 
				outp(0x43, 0x80); 
			temp = inp(0x40 + i); 

			temp << 8; 
			temp += inp(0x40 + i); 

			if (temp > ans) 
				ans = temp; 
		}
			itoa(ans, str, 16); 
			printf("\nFrequency for %d port: %s\n", i, str);
			ans = 0;
	} 
}