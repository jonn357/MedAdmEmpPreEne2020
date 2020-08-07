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
 //  string matriz[630][8];
struct Persona{
	 string orden;
	 string periodo;
	 string nombre;
	 string evaluacion;
	 string curso;
	 string competencia;
	 string nivelCompetenciaAlcanzado;
	 string resultadoCalificacion;
 };
map<string, vector<Persona>> personas;
void leer();
void escribirCSV();
void imprimir(map<string, vector<Persona>>);
void cargarDatos(vector<string>);
void cargarPersonas(Persona);
void contarNivelCompetencia();
void extraerVariables();
void split();
int main() {
	leer();

	escribirCSV();
	extraerVariables();
	contarNivelCompetencia();
	//imprimir(personas);
	split();
	return 0;
}
//lee el archivo csv, los datos los almacena en una matriz.
void leer(){
	vector<string> entradaRegistro;
	//string matriz[630][8];
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
			  //cout << "i; "<< i << " j: "<<j << endl;
		  entradaRegistro.push_back(texto);
		   j++;
		  }else{
			  cout << "i fuera de rango, columnas" <<  endl;
		  }
	   }
	   cargarDatos(entradaRegistro);
	   /*for (auto n=begin(entradaRegistro); n != end(entradaRegistro); n++){
		   cout << *n << endl;
	   }*/
	   entradaRegistro.clear();
	   //cout << "i:" << i << endl;
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
	persona.competencia=entradaRegistro[5];
	persona.nivelCompetenciaAlcanzado=entradaRegistro[6];
	persona.resultadoCalificacion=entradaRegistro[7];
	cargarPersonas(persona);
	//cout << "prueba: " << personas.size()<< "-" << endl;
	//cout << persona.orden << " " <<  persona.nombre << endl;
}
void cargarPersonas( Persona persona){
	personas[persona.periodo].push_back(persona);
}
void escribirCSV(){
		//int i=0,j=0;
	   ofstream outfile("C://Desarrollo//AcrhivosPlanos//tablas.csv");
	   if (outfile.good()) {
	           cout << "el fichero out se ha abierto correctamente" << endl;
	       }
	   if (outfile.fail()) {
	           cout << "ERROR abriendo el fichero" << endl;
	       }
	   string line = "";
	   for(auto n = begin(personas); n != end(personas); n++){
	       	//cout << endl << "periodo: " << n->first << endl;
	       	for(auto per = begin(n->second); per != end(n->second); per++){
	       		outfile << n->first << "," << per->nombre<< endl;
	       		//cout << "nombre: " << per->nombre << endl;
	       	}
	       }
	   outfile.close();
	   //cout << "correctamente" << endl;
	   //cout << "i: " << i << "j: " << j <<endl;
}
void contarNivelCompetencia(){
	/*por periodo,por evaluacion, por competencia*/
	int contador=0;
	for(auto n = begin(personas); n != end(personas); n++){
	    	//cout << endl << "periodo: " << n->first << endl;
	    	for(auto per = begin(n->second); per != end(n->second); per++){

	    		/*if(n->first=="201810" and per->evaluacion=="Formativa" and per->competencia=="Gestión de Personas" and per->nivelCompetenciaAlcanzado=="Intermedio"){
	    			contador++;
	    		}*/
	    	}
	    }
	cout << "CONTADOR: " << contador << endl;
}
void extraerVariables(){
	/*con vectores*/
	vector<string> evaluacion,competencia,nivelCompetenciaAlcanzado;
	bool esIgualEvaluacion=false;
	bool esIgualCompetencia=false;
	bool esIgualNivelCompetenciaAlcanzado=false;
	int contarEvaluacion=0,contarCompetencia=0,contarNivelCompetenciaAlcanzado=0;
	for(auto n = begin(personas); n != end(personas); n++){                              //iterar por periodos (clave del mapa)
	    	//cout << endl << "periodo: " << n->first << endl;
	    	for(auto per = begin(n->second); per != end(n->second); per++){             //iterar por persona en el vector(valor mapa) segun el periodo
	    		if(evaluacion.empty()){
	    		    evaluacion.push_back(per->evaluacion);
	    		    esIgualEvaluacion=false;
	    		    //cout << per->orden << "vacio, per->evaluacio: " << per->evaluacion << endl;
	    		}else if(!evaluacion.empty()){
	    			esIgualEvaluacion=false;
	    			for(auto r = begin(evaluacion); r != end(evaluacion); r++){
	    				if(*r == per->evaluacion){
	    					 esIgualEvaluacion=true;
	    					 //cout << "*r" << *r << endl;
	    				}
	    			 }
	    			if(esIgualEvaluacion!=true){
	    				evaluacion.push_back(per->evaluacion);
	    				//cout << "entro1" << endl;
	    				//esIgualValor=true;
	    			}
	    		}
	    		if(competencia.empty()){
	    			    		    competencia.push_back(per->competencia);
	    			    		    esIgualCompetencia=false;
	    			    		    //cout << per->orden << "vacio, per->evaluacio: " << per->evaluacion << endl;
	    			    		}else if(!competencia.empty()){
	    			    			esIgualCompetencia=false;
	    			    			for(auto r = begin(competencia); r != end(competencia); r++){
	    			    				if(*r == per->competencia){
	    			    					esIgualCompetencia=true;
	    			    					 //cout << "*r" << *r << endl;
	    			    				}
	    			    			 }
	    			    			if(esIgualCompetencia!=true){
	    			    				competencia.push_back(per->competencia);
	    			    				//cout << "entro1" << endl;
	    			    				//esIgualValor=true;
	    			    			}
	    			    		}
	    		if(nivelCompetenciaAlcanzado.empty()){
	    			    		    nivelCompetenciaAlcanzado.push_back(per->nivelCompetenciaAlcanzado);
	    			    		    esIgualNivelCompetenciaAlcanzado=false;
	    			    		    //cout << per->orden << "vacio, per->evaluacio: " << per->evaluacion << endl;
	    			    		}else if(!nivelCompetenciaAlcanzado.empty()){
	    			    			esIgualNivelCompetenciaAlcanzado=false;
	    			    			for(auto r = begin(nivelCompetenciaAlcanzado); r != end(nivelCompetenciaAlcanzado); r++){
	    			    				if(*r == per->nivelCompetenciaAlcanzado){
	    			    					esIgualNivelCompetenciaAlcanzado=true;
	    			    					 //cout << "*r" << *r << endl;
	    			    				}
	    			    			 }
	    			    			if(esIgualNivelCompetenciaAlcanzado!=true){
	    			    				nivelCompetenciaAlcanzado.push_back(per->nivelCompetenciaAlcanzado);
	    			    				//cout << "entro1" << endl;
	    			    				//esIgualValor=true;
	    			    			}
	    			    		}
	    		/*if(n->first=="201810" and per->evaluacion=="Formativa" and per->competencia=="Gestión de Personas" and per->nivelCompetenciaAlcanzado=="Intermedio"){
	    			contador++;
	    		}*/
	    		//cout << "r: " << *r << ". per->evaluacion: " << per->evaluacion << endl;
	    	}
	    	//cout << "extraer evaluacion: " << evaluacion.size() << endl;
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
void split(){
	char str[]="hola, mundo";
	char *pch;

	pch = strtok(str, ",");
	cout << pch << endl;
	while(pch != NULL){
        pch = strtok(NULL, ",");
        if(pch[0]==32){
        	for(int i=0; i < strlen(pch); i++){
        		pch[i]=pch[i+1];
        	}
        }
        cout << pch << endl;
	}
}
