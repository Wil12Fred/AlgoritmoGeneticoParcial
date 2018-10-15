template<class Indiv>
struct Problema{
	typedef Indiv indiv;
	int tamano_de_poblacion;
	int numero_de_generaciones;
	int numero_de_cromosomas;
	Problema(){}
	Problema(int n_poblacion, int n_generaciones,int n_cromosomas){
		tamano_de_poblacion=n_poblacion;
		numero_de_generaciones=n_generaciones;
		numero_de_cromosomas=n_cromosomas;
	}
	void generar_nuevo_individuo(Indiv& B){}
	int valor_aleatorio(int max){
		return XorShift(max);
	}
	double valor_aleatorio(double max){
		long long aleatorio = XorShift(100000000);
		return (max*aleatorio)/double(100000000);
	}
	double aptitud(Indiv& individuo){
		return -1;
	}
};

template<class Indiv>
struct Parcial: Problema<Indiv>{
	vector<int>* Horario;
	int n_cursos;
	double grado_de_sinapsis;
	double grado_de_motivacion;
	double grado_de_desgaste;
	Parcial(int n_poblacion, int n_generaciones,int n_cromosomas,vector<int>& H)://R
		Problema<Indiv>(n_poblacion, n_generaciones, n_cromosomas){
		n_cursos=0;
		Horario=&H;
		//Horario=new vector<int>(H.size());
		for (int i=0;i<H.size();i++){
			//(*Horario)[i]=H[i];
			n_cursos=max(n_cursos,H[i]);
		}
		grado_de_sinapsis=0.05;
		grado_de_motivacion=0.05;
		grado_de_desgaste=0.07;
	}
	int NumeroDeCromosomas(){
		return this->numero_de_cromosomas;
	}
	void generar_nuevo_individuo(Indiv& B){
		Represent nuevo(NumeroDeCromosomas());
		for (int i=0;i<NumeroDeCromosomas();i++){
			nuevo.cromosomas[i]=XorShift(n_cursos+1);
		}
		B.representacion=nuevo;
		B.maxInt=n_cursos;
	}
	double aptitud(Indiv& individuo, bool print=false){
		int j=0;
		vector<double> Apr(n_cursos+1, 0.5);//aprendizaje (entendimiento)
		vector<double> Int(n_cursos+1, 1);//interez
		vector<double> Con(n_cursos+1, 0);//conocimiento de los cursos
		double ene=1;//energia
		for (int i=0;i<Horario->size();i++){
			if(print && i%24==0) cout << endl;
			int c=0;
			if((*Horario)[i]==0){
				c=individuo.representacion.cromosomas[j];
				if(print)
					cout << "\e[36m" << c << "\e[0m ";
				j++;
			} else {
				c=(*Horario)[i];
				if(print)
					cout << c << " ";
			}
			
			//actualización
			if(c==0){//descanso
				ene=min(double(1),ene+grado_de_desgaste*0.7);//aumento de energia
			} else {//estudio
				Con[c]+=Apr[c]*Int[c]*ene;
				ene=max(0.05,ene-grado_de_desgaste);//disminución de energía
			}
			for (int k=1;k<Apr.size();k++){
				if(k==c){
					Apr[c]=min(double(1),Apr[c]+0.1);//aumento de entendimiento
					if((*Horario)[i]==0){//si estudias
						Int[c]=max(0.5,Int[c]-grado_de_motivacion);//disminucion de interes
					} else {// si te enseñan
						Int[c]=min(double(1),Int[c]+grado_de_motivacion);//aumenta interes
					}
				} else {
					Apr[k]=max(0.5,Apr[k]-0.05);
					Int[c]=min(double(1),Int[c]+grado_de_sinapsis);
				}
			}
		}
		if(print)
			cout << endl;
		double apt=1;
		for (int i=1;i<Con.size();i++){
			if(print){
				cout << "curso " << i << ": " << Con[i] << endl;
			}
			apt*=Con[i];
		}
		return apt;
	}
};
