#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <math.h>
#include <cstdio>

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
		string lineasNom[largo];
		int z = 0;
    	while(!archivo.eof()){
    		getline(archivo,texto);
			int posPC = texto.find(";");
	        int cedula = atoi(texto.substr(0, posPC).c_str()); string nombre = texto.substr(posPC + 1, texto.length());
			lineas[z] = cedula;
			lineasNom[z] = nombre;
			z++;
    	}
    	archivo.close();
    	int i,j,k;
    	int tam = largo-1;
    	for(i = 0; i < tam; i++){
			for(j = i+1; j < tam; j++){
				if(lineas[i] == lineas[j]){
					k = j;
					while(k < tam){
						lineas[k] = lineas[k+1];
						lineasNom[k]= lineasNom[k+1];
						++k;
					}
					--tam;
					--j;
				}
			}
		//cout<<"Cedula: "<<lineas[i]<<" Nombre: "<<lineasNom[i]<<endl;
		}
		int indice = 0;
		for(int x = 0;x<tam;x++){
			Indice(lineas[x],indice);
		}
 		ofstream archivo;
    	archivo.open("ClientesRN.txt", ios::app);
    	for(int x = 0;x<tam;x++){
    		archivo<<lineas[x]<<";"<<lineasNom[x]<<endl;
    		
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
			int posPC = texto.find(";");
	        int indice = atoi(texto.substr(0, posPC).c_str()); int cedula = atoi((texto.substr(posPC + 1, texto.length())).c_str());
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

void CrearCache(int cacheInt[],string cacheStr[]){
	ifstream archivo;
	string texto;
	archivo.open("ClientesRN.txt",ios::in);
	if (archivo.fail()){
	    cout<<"No se pudo abrir el archivo";
	    exit(1);
	}
	else{
		int largo = 0;
		while(!archivo.eof()){
			if(largo!=20){
				getline(archivo,texto);
				int posPC = texto.find(";");
	        	int cedula = atoi(texto.substr(0, posPC).c_str()); string nombre = texto.substr(posPC + 1, texto.length());
	        	cacheInt[largo]= cedula;
				cacheStr[largo]= nombre;
				largo++;
			}
			else{
				break;
			}
			
		}
	}
}

void MostrarCache(int cacheInt[],string cacheStr[]){
	cout<<"Memoria cache"<<endl<<endl;
	for(int e = 0;e<20;e++){
		cout<<"Cedula: "<<cacheInt[e]<<" Nombre: "<<cacheStr[e]<<endl;
	}
}


bool ExisteCliente(pNodoBinario &raiz, int cedula, int &indice){
	if(raiz==NULL){
        return false;
    }
	else if (raiz->valor== cedula) {
		indice= raiz->indice;
		return true; 
    }
	else if(cedula<raiz->valor){
    	ExisteCliente(raiz->Hizq,cedula,indice);
	}
	else{
		ExisteCliente(raiz->Hder,cedula,indice);
	}
}


void EliminarCliente(){
	int cedula; cout<<"Ingrese la cedula del usuario a elminar: "; cin>>cedula; cout<<endl;
}

bool BuscarEnCache(int cedula, int cacheInt[], string cacheStr[], string &nombre){
	for(int x=0; x<20; x++){
		if(cacheInt[x] == cedula){
			nombre = cacheStr[x];
			return true;
		}
	}
	return false;
}
void CambiarCache(int indice, string &nombre, int cacheInt[], string cacheStr[]){
	
}

void BuscarCliente(pNodoBinario &raiz , int cacheInt[], string cacheStr[]){
	int cedula; cout<<"Ingrese la cedula del usuario a buscar: "; cin>>cedula; cout<<endl;
	int indice; string nombre;
	if(ExisteCliente(raiz,cedula,indice)){
		if(BuscarEnCache(cedula,cacheInt,cacheStr,nombre)){
			cout<<"El cliente solicitado es "<< nombre<< " de cedula "<<cedula<<endl;	
		}else{
			//Renovar Cache
		}
	}else{
		cout<<"El usuario ingresado no existe"<<endl;
	}
}

int main(){
	int opcion;
	int cacheInt[20];string cacheStr[20];
	pNodoBinario raiz;
	Clientes(); 
	raiz = CrearArbol();
	CrearCache(cacheInt,cacheStr);
	do { 
		system("cls");      // Para limpiar la pantalla 
		cout << "Tarea Corta #3" << endl; 
		cout << "\nMenu" << endl<<endl; 
		cout << "1. Memoria cache" << endl; 
		cout << "2. Busqueda" << endl; 
		cout << "3. Insertar Cliente" << endl; 
		cout << "4. Eliminar " << endl; 
		cout << "5. Purgar " << endl; 
		cout << "6. Reindexar " << endl; 
		cout << "7. Salir" << endl; 
		cout << "\nIngrese una opcion: "; 
		cin >> opcion; 
		cout<<endl; 
		switch (opcion) {  
		    case 1:
				system("pause>nul"); 
				break;
		    case 2:
		    	MostrarCache(cacheInt,cacheStr);
		    	system("pause>nul"); 
		        break;    
			case 3:
				BuscarCliente(raiz , cacheInt, cacheStr);
		        system("pause>nul"); 
		        break;                 
		 	case 4:
		        system("pause>nul"); 
		        break;    
		    case 5:
		    	EliminarCliente();
		        system("pause>nul"); 
		        break;  
			case 6:
		        system("pause>nul"); 
		        break;       
		}	
	}
	while (opcion!=7);
		cout<<"Gracias por utilizar el programa"<<endl;			
   return 0;
}
