template<class P,class Indiv=typename P::indiv>
struct Simulated_Annealing: Genetico<P>{
	double T;
	int iteration;
	Indiv mejora;
	Simulated_Annealing(P* p):
		Genetico<P>(p,0,1,true){
		T=1;
		iteration=0;
		this->problema->tamano_de_poblacion=1;
	}
	set<Indiv>* m_poblacion(){
		return this->poblacion;
	}
	double t_aptitud(Indiv i, double apt_total){
		return exp((i.aptitud/apt_total)/T);
	}
	Indiv seleccion_de_eliminacion(){
		double backup_aptitud_total=this->aptitud_total;
		this->aptitud_total=0;
		Indiv other;
		for (auto it=m_poblacion()->begin();it!=m_poblacion()->end();it++){
			if(!(*it==mejora)){
				other=*it;
			}
			this->aptitud_total+=t_aptitud(*it,backup_aptitud_total);
		}
		if (this->seleccion_rueda_de_ruleta(t_aptitud(other,backup_aptitud_total))){
			this->aptitud_total=backup_aptitud_total;
			return other;
		}
		this->aptitud_total=backup_aptitud_total;
		return mejora;
	}
	void ajustar_poblacion(){
		while(this->poblacion->size()>this->problema->tamano_de_poblacion){
			Indiv condenado=this->seleccion_de_eliminacion();
			this->aptitud_total-=condenado.aptitud;
			this->poblacion->erase(condenado);
		}
	}
	void generar_nueva_poblacion(){
		mejora=this->obtenerMejor();
		double pasMejorAptitud=mejora.aptitud;
		this->mutar_individuos();
		ajustar_poblacion();
		mejora=this->obtenerMejor();
		//pair<double,double> X=mejora.representacion.getX();
		//cout << ++iteration;
		//cout << "; " << X.first << "; " << X.second;
		//cout << "; " << this->problema->func(X.first,X.second);
		//printf("; %.8lf", T);
		//cout << endl;
		if(mejora.aptitud>pasMejorAptitud){
			T*=0.99;//*log(double(22000+double(iteration)/14000))/10;
		} else {
			T*=0.9999;
		}
	}
};
