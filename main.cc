#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#include "xorshift.h" //semilla y función para puntos aleatorios
#include "matematica.h" //definiciones basicas
#include "genetico.h"
#include "simulated_annealing.h"

void crearHorario(vector<int>& H, int n_cursos=7, int clases=2){//clases de 3 horas
	H.resize(144,0);//6dias*24horas
	for (int i=0;i<n_cursos;i++){
		for (int j=0;j<clases;j++){
			int pos=XorShift(144);
			int cant=0;
			while(cant<3){
				while(H[pos]!=0 || (pos%24)<7 || (pos%24)>21){
					pos=(pos+1)%144;
				}
				H[pos]=i;
				cant++;
			}
		}
	}
	int l=0;
	for (int i=0;i<144;i++){
		if(H[i]==0){
			l++;
		}
	}
	cout << l << endl;
}

//PROBLEMA DE HORARIO DE ESTUDIO
void imprimirHorario(vector<int>& H){
	if(H.size()!=144){
		return;
	}
	for (int i=0;i<6;i++){
		for (int j=0;j<24;j++){
			cout << H[i*24+j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char **argv){
	SeedXorShift();
	vector<int> H;
	crearHorario(H,7,2);
	imprimirHorario(H);
	/*Parcial<Individuo> HorarioDeEstudio1(1,300,108,H);
	Simulated_Annealing<Parcial<Individuo> > SA(&HorarioDeEstudio1);
	Individuo mejor=SA.iniciar(false);
	double ma = HorarioDeEstudio1.aptitud(mejor, true);*/
	
	Parcial<Individuo> HorarioDeEstudio(30,300,108,H);
	Genetico<Parcial<Individuo> > G(&HorarioDeEstudio,0.4,0.3,true);
	Individuo mejorg=G.iniciar(false);
	double ma = HorarioDeEstudio.aptitud(mejorg, true);

	cout << ma << endl;

	return 0;
}
