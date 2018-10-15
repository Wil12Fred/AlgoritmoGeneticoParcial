struct Individuo{
	Represent representacion;
	double aptitud;
	int maxInt;
	Individuo(){maxInt=1;}//R
	Individuo(Represent rep){//R
		representacion=rep;
		maxInt=1;
	}
	Individuo(Represent rep,int mI){//R
		representacion=rep;
		maxInt=mI;
	}
	Individuo(Represent representacion,double aptitud){//R
		representacion=representacion;
		aptitud=aptitud;
		maxInt=1;
	}
	Individuo operator=(const Individuo& B){//R
		representacion=B.representacion;
		aptitud=B.aptitud;
		maxInt=B.maxInt;
		return *(this);
	}
	bool operator ==(const Individuo B)const{//R
		return (representacion==B.representacion);
	}
	Individuo cruzamiento(const Individuo* B){//R
		//printf("cruzando\n");
		Represent nuevo(representacion.tamano());
		bool cromosoma_padre=XorShift(2);
		int tamano_minimo=3;
		int division=XorShift(representacion.tamano()/2-tamano_minimo)+tamano_minimo;
		for (int i=0;i<representacion.tamano()/2;i++){
			if(i==division)
				cromosoma_padre=!cromosoma_padre;
			if(cromosoma_padre)
				nuevo.cromosomas[i]=representacion.cromosomas[i];
			else
				nuevo.cromosomas[i]=B->representacion.cromosomas[i];
		}
		cromosoma_padre=XorShift(2);
		division=representacion.tamano()/2+XorShift(representacion.tamano()/2-tamano_minimo)+tamano_minimo;
		for (int i=representacion.tamano()/2;i<representacion.tamano();i++){
			if(i==division)
				cromosoma_padre=!cromosoma_padre;
			if(cromosoma_padre)
				nuevo.cromosomas[i]=representacion.cromosomas[i];
			else
				nuevo.cromosomas[i]=B->representacion.cromosomas[i];
		}
		return Individuo(nuevo, maxInt);
	}
	void mutacion_swap(Represent& nuevo){//R
		int findice_mutacion=XorShift(representacion.tamano());
		int sindice_mutacion=XorShift(representacion.tamano());
		if(findice_mutacion==sindice_mutacion){
			sindice_mutacion=(sindice_mutacion+1)%representacion.tamano();
		}
		int cromosoma_aleatorio=nuevo.cromosomas[sindice_mutacion];
		nuevo.cromosomas[sindice_mutacion]=nuevo.cromosomas[findice_mutacion];
		nuevo.cromosomas[findice_mutacion]=cromosoma_aleatorio;
	}
	void mutacion_alter(Represent& nuevo, int n/*,int maxInt=1*/){//R
		set<int> S;
		for (int i=0;i<n;i++){
			//nuevo.cromosomas[XorShift(representacion.tamano())]=XorShift(2);
			int pos=XorShift(representacion.tamano());
			while (S.find(pos)!=S.end()){
				pos=XorShift(representacion.tamano()); 
			}
			int new_value=XorShift(maxInt+1);
			if(new_value==nuevo.cromosomas[pos]){
				new_value=(new_value+1)%(maxInt+1);
			}
			nuevo.cromosomas[pos]=new_value;//!(nuevo.cromosomas[pos]);
			S.insert(pos);
		}
	}
	Individuo mutacion(){//R
		Represent nuevo(representacion.tamano());
		nuevo=representacion;
		//mutacion_swap(nuevo); //swap
		mutacion_alter(nuevo, XorShift(2)+1); //alter
		return Individuo(nuevo, maxInt);
	}
	bool operator <(const Individuo& B)const{//R
		return (aptitud==B.aptitud)?representacion<B.representacion:aptitud<B.aptitud;
	}
};
