//============================================================================
// Name        : MedAdmEmpPreEne2020.cppc
// Author      : juan Alexis Prieto Bohorquez
// Version     : Alfha 0.1
// Copyright   : Your copyright notice
// Description : Procesar base de datos para tablas estadisticas con sus graficas, in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <map>
using namespace std;
struct Persona{
	 string orden;
	 string periodo;
	 string nombre;
	 string evaluacion;
	 string curso;
	 vector<string> competencia;//string competencia; // vector<string> competencia;debe ser un vector de competencias.z
	 string nivelCompetenciaAlcanzado;
	 string resultadoCalificacion;
 };
map<string, vector<Persona>> personas;
vector<string> evaluacion,competencia,nivelCompetenciaAlcanzado,competenciaPrueba;
void leer();
void escribirCSV();
void imprimir(map<string, vector<Persona>>);
void cargarDatos(vector<string>);
void cargarPersonas(Persona);
void contarNivelCompetencia(map<string, vector<Persona>>& personas, vector<string>& evaluacion, vector<string>& competencia, vector<string>& nivelCompetenciaAlcanzado);
void extraerVariables(vector<string>& evaluacion, vector<string>& competencia, vector<string>&   nivelCompetenciaAlcanzado);
void split(vector<string>& competencia, string competenciaStr);
string arrayAstring(char* , int);
void esIgual(vector<string>& competencia, string competenciaStr);
void generarTablas();
int main() {
	leer();

	escribirCSV();
	extraerVariables(evaluacion, competencia, nivelCompetenciaAlcanzado);
	contarNivelCompetencia(personas, evaluacion, competencia, nivelCompetenciaAlcanzado);
	return 0;
}
void leer(){                              //lee el archivo csv, los datos los almacena en una matriz.
	vector<string> entradaRegistro;
	string valor="";
	int i=0,j=0;
   ifstream infile("C://Desarrollo//AcrhivosPlanos//MedAdmEmpPreEne2020.csv");
   if (infile.good()) {
           cout << "el fichero input se ha abierto correctamente" << endl;
       }
   if (infile.fail()) {
           cout << "ERROR abriendo el fichero" << endl;
       }
   string line = "";
   while(getline(infile, line)){
	   stringstream strstr(line); //un string que trabaja sobre un string
	   string texto= "";
	   while(getline(strstr, texto, ';')){
		  if (i<630 && j<8) {
		  entradaRegistro.push_back(texto);
		   j++;
		  }else{
			  cout << "i fuera de rango, columnas" <<  endl;
		  }
	   }
	   cargarDatos(entradaRegistro);
	   entradaRegistro.clear();
	   i++;
	   j=0;
   }
   infile.close();
}
//contar por nivelCompetencia, cuantos insuficientes, cuantos intermedio y cuantos avanzados hay?.
//segun el tipo de evaluacion: sumatoria o formativa para cada competencia: gestion de mercadeo, gestion de organizaciones,
//gestion financiera y gestion de personas.
void imprimir(map<string, vector<Persona>> personaMap){
	cout << "imprimiendo" << endl;
    for(auto n = begin(personaMap); n != end(personaMap); n++){
    	cout << endl << "periodo: " << n->first << endl;
    	for(auto per = begin(n->second); per != end(n->second); per++){
    		cout << "nombre: " << per->nombre << endl;
    	}
    }
}
void cargarDatos( vector<string> entradaRegistro){
	Persona persona;
	persona.orden=entradaRegistro[0];
	persona.periodo=entradaRegistro[1];
	persona.nombre=entradaRegistro[2];
	persona.evaluacion=entradaRegistro[3];
	persona.curso=entradaRegistro[4];
	split(persona.competencia,entradaRegistro[5]);
	//persona.competencia=entradaRegistro[5];    //VECTOR + split
	persona.nivelCompetenciaAlcanzado=entradaRegistro[6];
	persona.resultadoCalificacion=entradaRegistro[7];
	cargarPersonas(persona);
}
void cargarPersonas( Persona persona){
	personas[persona.periodo].push_back(persona);
}
void escribirCSV(){
	   ofstream outfile("C://Desarrollo//AcrhivosPlanos//tablas.csv");
	   if (outfile.good()) {
	           cout << "el fichero out se ha abierto correctamente" << endl;
	       }
	   if (outfile.fail()) {
	           cout << "ERROR abriendo el fichero" << endl;
	       }
	   string line = "";
	   for(auto n = begin(personas); n != end(personas); n++){
	       	for(auto per = begin(n->second); per != end(n->second); per++){
	       		outfile << n->first << "," << per->nombre<< endl;
	       	}
	       }
	   outfile.close();
}
void contarNivelCompetencia(map<string, vector<Persona>>& personas, vector<string>& evaluacion, vector<string>& competencia, vector<string>& nivelCompetenciaAlcanzado){                  /*por periodo,por evaluacion, por competencia*/
	int contador=0;
	for(auto e = begin(evaluacion); e != end(evaluacion); e++){
        for(auto c = begin(competencia); c != end(competencia); c++){
	        for(auto p = begin(personas); p != end(personas); p++){
	    	    for(auto nCa = begin(nivelCompetenciaAlcanzado); nCa != end(nivelCompetenciaAlcanzado); nCa++){
	    	    	cout << "e;"<< *e << ";c;"<< *c << ";p;"<< p->first << ";nCa;"<< *nCa;
                    for(auto pers = begin(p->second); pers != end(p->second); pers++){
                    	contador++;
                    }
                    cout << ";CONTADOR;" << contador << endl;
	    	    }
	        }
        }
    }
}
void extraerVariables(vector<string>& evaluacion, vector<string>& competencia, vector<string>&   nivelCompetenciaAlcanzado){
	bool esIgualEvaluacion=false;
	bool esIgualCompetencia=false;
	bool esIgualNivelCompetenciaAlcanzado=false;
	int contarEvaluacion=0,contarCompetencia=0,contarNivelCompetenciaAlcanzado=0;
	for(auto n = begin(personas); n != end(personas); n++){                              //iterar por periodos (clave del mapa)
	    for(auto per = begin(n->second); per != end(n->second); per++){             //iterar por persona en el vector(valor mapa) segun el periodo
	    	if(evaluacion.empty()){                                                 //(primera iteracion)el vector 'evaluacion' esta vacio?
	    		evaluacion.push_back(per->evaluacion);                              //agregar el primer valor, se debe usar split()
	    		esIgualEvaluacion=false;
	    	}else if(!evaluacion.empty()){                                          //(segunda iteracion o mas)el vector 'evaluacion' ya tiene almenos un valor?
	    	    esIgualEvaluacion=false;
	    		for(auto r = begin(evaluacion); r != end(evaluacion); r++){         //verifica que el nuevo valor a ingresar no exista en el vector.
	    			if(*r == per->evaluacion){                                     //los dos string son diferentes?
	    				esIgualEvaluacion=true;                                   //nuevo valor no existe
	    			}
	    		}
	    		if(esIgualEvaluacion!=true){                                      //si el valor no existe lo ingresa en el vector!
	    			evaluacion.push_back(per->evaluacion);
	    		}
	    	}
	    	//split(competencia, per->competencia);//
	    	if(competencia.empty()){
	    		for(auto c = begin(per->competencia); c != end(per->competencia); c++){
	    			competencia.push_back(*c);
	    		}
	    		    		esIgualCompetencia=false;
	    	}else if(!competencia.empty()){
	    		esIgualCompetencia=false;
	    		for(auto r = begin(competencia); r != end(competencia); r++){
	    			for(auto c = begin(per->competencia); c != end(per->competencia); c++){
	    		        if(*r == *c){
	    		            esIgualCompetencia=true;
	    		        }
	    			}
	    		}
	    		if(esIgualCompetencia!=true){
	    			for(auto c = begin(per->competencia); c != end(per->competencia); c++){
	    			    competencia.push_back(*c);
	    		    }
	    		}
	        }
	    	if(nivelCompetenciaAlcanzado.empty()){
	    		nivelCompetenciaAlcanzado.push_back(per->nivelCompetenciaAlcanzado);
	    		esIgualNivelCompetenciaAlcanzado=false;
	    	}else if(!nivelCompetenciaAlcanzado.empty()){
	    		esIgualNivelCompetenciaAlcanzado=false;
	    		for(auto r = begin(nivelCompetenciaAlcanzado); r != end(nivelCompetenciaAlcanzado); r++){
	    			if(*r == per->nivelCompetenciaAlcanzado){
	    			    esIgualNivelCompetenciaAlcanzado=true;
	    			}
	    		}
	    		if(esIgualNivelCompetenciaAlcanzado!=true){
	    			nivelCompetenciaAlcanzado.push_back(per->nivelCompetenciaAlcanzado);
	    		}
	    	}
	    }
	}
	for(auto n=begin(evaluacion); n!=end(evaluacion); n++){
		contarEvaluacion++;
		cout << "evaluacion: " << *n << endl;
	}
	cout << "Total Evaluacion: " << contarEvaluacion << "total: "<< evaluacion.size() << endl;
	for(auto n=begin(competencia); n != end(competencia); n++){
		contarCompetencia++,
		cout << "competencia: " << *n << endl;
	}
	cout << "Total Competencia: " << contarCompetencia << "total: "<< competencia.size() << endl;
	for(auto n = begin(nivelCompetenciaAlcanzado); n != end(nivelCompetenciaAlcanzado); n++){
		cout << "nivelCompetenciaAlcanzado: " << *n << endl;
		contarNivelCompetenciaAlcanzado++;
	}
	cout << "Total NivelCompetenciaAlcanzado: " << contarNivelCompetenciaAlcanzado << "total: "<< nivelCompetenciaAlcanzado.size() << endl;
}
string arrayAstring(char* arregloChar, int sizeChar){     //convierte array en string
	int i;
	string s = "";
	for(i=0; i<sizeChar; i++){
		s = s + arregloChar[i];
	}
	return s;
}
void split(vector<string>& competencia, string competenciaStr){
	int pch_size=0;
	string pchStr;
	char * str=new char[competenciaStr.length()+1];
	strcpy(str, competenciaStr.c_str());
	char * pch = strtok(str, ",");
	if(competencia.empty()){
		competencia.push_back(pch);
	}else if(!competencia.empty()){
	    esIgual(competencia, pch);//competencia.push_back(pch);
	}
	while(pch != NULL){
        pch = strtok(NULL, ",");
        if(pch != NULL){
        if(pch[0]==32){
        	for(int i=0; i < strlen(pch)-1; i++){
        		pch_size=i;
        		pch[i]=pch[i+1];
        	}
        }
        pch_size=pch_size+1;
        pchStr = arrayAstring(pch, pch_size);
        competenciaStr=pchStr;
        esIgual(competencia, competenciaStr);//competencia.push_back(competenciaStr);      //*****************************************
        }
	}
	delete[] str;
}
void esIgual(vector<string>& competencia, string competenciaStr){
	bool esIgual=false;
	for(auto r = begin(competencia); r != end(competencia); r++){
		if(*r == competenciaStr){
			esIgual=true;
		}
	}
	if(esIgual==false){competencia.push_back(competenciaStr);}
}
void generarTablas(){

}
