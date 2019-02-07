/*
  geraldo.rabelo@gmail.com fev-2019
  gcc campainha.c -o campainha.exe
  
  Windows:
	COM1:9600,N,8,1,P
	echo "1" > COM1
	echo "2" > COM1

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
	char *soar;
	char *silenciar;
	char *configurar;

	soar = malloc(15*sizeof(char));
	silenciar = malloc(15*sizeof(char));
	configurar = malloc(22*sizeof(char));

	sprintf(configurar,"MODE COM3:9600,N,8,1,P");
	sprintf(soar,"echo \"1\" > COM3");
	sprintf(silenciar,"echo \"2\" > COM3");

	//printf("\n%s\n%s\n",soar,silenciar);

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
	alarme[11].minutos = 00;
	alarme[11].status = 0;

	while(1) {

		if (i == 12) { i = 0; }
		if (alarme[i].status == 1) {
			while(alarme[i].status == 1) {
				
				time(&now);
				hora_atual = localtime(&now);
				if ((alarme[i].hora == hora_atual->tm_hour) && (alarme[i].minutos == hora_atual->tm_min)) {
					alarme[i].status = 0;
					printf("\n[%2d:%2d] Soando...\n",hora_atual->tm_hour,hora_atual->tm_min);
					printf("\n%s : %d",system(configurar));
					sleep(3);
					printf("\n%s : %d",soar,system(soar));
					sleep(4);
					printf("\n%s : %d\n",silenciar,system(silenciar));
					sleep(65);
					i++;
				}

				if (system(configurar) == -1) {
					printf("\a\n");
					printf("\nCAMPAINHA DESCONECTADA! POR FAVOR VERIFIQUE A CONEXAO -> CABO USB");
				}
				//sleep(1);
				system("cls");
				//sleep(1);
				printf("\n[%02d:%02d] proximo alarme: %02d:%02d",hora_atual->tm_hour,hora_atual->tm_min,alarme[i].hora,alarme[i].minutos);
				sleep(5);
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
