#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <math.h>

//hpp
#include "ArbolBinario.hpp"
using namespace std;

void Indice(int cedula, int &indice){
    ofstream archivo;
    archivo.open("Indices.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
    indice++;
    archivo<<indice<<";"<<cedula<<endl;
}

void Clientes(){
	ifstream archivo;
	string texto;
	ofstream archivoSalida;
	//Se inicializa la lista de indices
	archivoSalida.open("Indices.txt", ios::app);
	if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	//Se abre la lista de clientes
	archivo.open("Clientes.txt",ios::in);
	if (archivo.fail()){
	    cout<<"No se pudo abrir el archivo";
	    exit(1);
	}else{
		int largo = 0;
		while(!archivo.eof()){
			getline(archivo,texto);
			largo++;
		}
		archivo.close();
		archivo.open("Clientes.txt",ios::in);
		int lineas[largo];
		int z = 0;
    	while(!archivo.eof()){
    		getline(archivo,texto);
			int posPC = texto.find(";");
	        int cedula = atoi(texto.substr(0, posPC).c_str()); string nombre = texto.substr(posPC + 1, texto.length());
    		lineas[z] = cedula;
    		z++;
    	}
    	archivo.close();
    	
    	int i,j,k;
    	int tam = largo;
    	for(i = 0; i < tam; i++){
			for(j = i+1; j < tam; j++){
				if(lineas[i] == lineas[j]){
					k = j;
					while(k < tam){
						lineas[k] = lineas[k+1];
						++k;
					}
					--tam;
					--j;
				}
			}
		}
		int indice = 0;
		for(int x = 0;x<tam;x++){
			Indice(lineas[x],indice);
		}
 
	}
}
pNodoBinario CrearArbol(){
	ifstream archivo;
	string texto;
	pNodoBinario raiz = NULL;
	archivo.open("Indices.txt",ios::in);
	if (archivo.fail()){
	    cout<<"No se pudo abrir el archivo";
	    exit(1);
	}else{
		while(!archivo.eof()){
			getline(archivo,texto);
			cout<<"Texto: "<<texto<<endl;
			int posPC = texto.find(";");
	        int indice = atoi(texto.substr(0, posPC).c_str()); int cedula = atoi((texto.substr(posPC + 1, texto.length())).c_str());
	        cout<<indice<<"-"<<cedula<<endl;
	        if(raiz==NULL){
	        	raiz = new NodoBinario(cedula,indice);
			}
			else{
				InsertarCedula(raiz,cedula,indice);
			}
		}
		archivo.close();
	}
	return raiz;
}


int main(){
	Clientes(); 
	pNodoBinario raiz = CrearArbol();
	
   return 0;
}
