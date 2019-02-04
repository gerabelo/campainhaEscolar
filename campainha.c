/*
  geraldo.rabelo@gmail.com fev-2019
  gcc campainha.c -o campainha.exe
  
  Windows:
	system("COM1:9600,N,8,1,P");
	system("echo \"1\" > COM1");
	system("echo \"2\" > COM1");

  Linux:
	stty -F /dev/ttyACM0 -hupcl
	echo 1 > /dev/ttyACM0
	echo 2 > /dev/ttyACM0
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct horarios {
	int hora;
	int minutos ;
	int status;
} Horarios;

void soar(void);

int main(void) {

	time_t now;
	time(&now);
	Horarios alarme[12];
	struct tm *hora_atual = localtime(&now);
	int i = 0;

	alarme[0].hora = 7;
	alarme[0].minutos = 0;
	alarme[0].status = 0;

	alarme[1].hora = 8;
	alarme[1].minutos = 45;
	alarme[1].status = 0;

	alarme[2].hora = 9;
	alarme[2].minutos = 5;
	alarme[2].status = 0;

	alarme[3].hora = 9;
	alarme[3].minutos = 15;
	alarme[3].status = 0;

	alarme[4].hora = 9;
	alarme[4].minutos = 30;
	alarme[4].status = 0;

	alarme[5].hora = 11;
	alarme[5].minutos = 0;
	alarme[5].status = 0;

	alarme[6].hora = 13;
	alarme[6].minutos = 0;
	alarme[6].status = 0;

	alarme[7].hora = 14;
	alarme[7].minutos = 45;
	alarme[7].status = 0;

	alarme[8].hora = 15;
	alarme[8].minutos = 5;
	alarme[8].status = 0;

	alarme[9].hora = 15;
	alarme[9].minutos = 15;
	alarme[9].status = 0;

	alarme[10].hora = 15;
	alarme[10].minutos = 30;
	alarme[10].status = 0;

	alarme[11].hora = 17;
	alarme[11].minutos = 0;
	alarme[11].status = 0;

	while(1) {
		if (i == 12) { i = 0; }
		if (alarme[i].status == 1) {
			printf("\n[%02d:%02d] proximo alarme: %02d:%02d",hora_atual->tm_hour,hora_atual->tm_min,alarme[i].hora,alarme[i].minutos);
			while(1) {
				if ((alarme[i].hora == hora_atual->tm_hour) && (alarme[i].minutos == hora_atual->tm_min)) {
					alarme[i].status = 0;
					soar();
				}
				sleep(30);
			}
		}

		if (alarme[i].hora < hora_atual->tm_hour) { alarme[i].status = 1; i++; }
		else if ((alarme[i].hora == hora_atual->tm_hour) && (alarme[i].minutos < hora_atual->tm_min)) { alarme[i].status = 1; i++; }
		else {
			alarme[i].status = 1;
		}

		time(&now);
		hora_atual = localtime(&now);
		sleep(1);
	}
}

void soar(void) {
	time_t now;
	time(&now);
	struct tm *hora_atual = localtime(&now);

	printf("\n[%2d:%2d] Soando...\n",hora_atual->tm_hour,hora_atual->tm_min);
	system("MODE COM1:9600,N,8,1");
	system("ECHO 1 > COM1");
	sleep(3);
	system("ECHO 2 > COM1");
}
