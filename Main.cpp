#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <math.h>


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

void ImprimirCache(){
	ifstream archivo;
	string texto;
	pNodoBinario raiz = NULL;
	archivo.open("Cache.txt",ios::in);
	if (archivo.fail()){
	    cout<<"La memoria no ha sido creada, primero debe de cargarla";
	}else{
		cout<<"\n\n Memoria cache" << endl;
		while(!archivo.eof()){
			getline(archivo,texto);
			int posPC = texto.find(";");
	        int cedula = atoi(texto.substr(0, posPC).c_str()); string nombre = texto.substr(posPC + 1, texto.length());
	        cout<<"Cedula: "<<cedula<<" , Nombre: "<<nombre<<endl;
		}archivo.close();
	}
}

void EliminarCliente(){
	int cedula; cout<<"Ingrese la cedula del usuario a elminar: "; cin>>cedula; cout<<endl;
}

int main(){
	int opcion;
	pNodoBinario raiz;
	do { 
		system("cls");      // Para limpiar la pantalla 
		cout << "Tarea Corta #3" << endl; 
		cout << "\nMenu" << endl<<endl; 
		cout << "1. Cargar los archivos" << endl;
		cout << "2. Memoria cache" << endl; 
		cout << "3. Busqueda" << endl; 
		cout << "4. Insertar Cliente" << endl; 
		cout << "5. Eliminar " << endl; 
		cout << "6. Purgar " << endl; 
		cout << "7. Reindexar " << endl; 
		cout << "8. Salir" << endl; 
		cout << "\nIngrese una opcion: "; 
		cin >> opcion; 
		cout<<endl; 
		switch (opcion) {  
		    case 1:
		    	Clientes(); 
				raiz = CrearArbol();
				cout<<"Los archivos se han cargado exitosamente"<<endl;
				system("pause>nul"); 
				break;  
		    case 2:
		    	ImprimirCache();
		    	system("pause>nul"); 
		        break;    
			case 3:
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
			case 7:
		        system("pause>nul"); 
		        break;        
		}	
	}
	while (opcion!=8);
		cout<<"Gracias por utilizar el programa"<<endl;			
   return 0;
}
