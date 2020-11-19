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

void Indice(int cedula, int &indice, bool bandera){
    ofstream archivo;
    archivo.open("Indices.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo crear el archivo"<<endl;
        exit(1);
    }
    if(bandera){
    	indice++;
    	archivo<<indice<<";"<<cedula<<endl;
	}
	else{
		indice++;
    	archivo<<indice<<";"<<cedula;
	}
    
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
		bool bandera = true;
		for(int x = 0;x<tam;x++){
			if(x==tam-1){
				bandera = false;
			}
			Indice(lineas[x],indice,bandera);
		}
 		ofstream archivo;
    	archivo.open("ClientesRN.txt", ios::app);
    	int y;
    	for(int x = 0;x<tam-1;x++){
    		archivo<<lineas[x]<<";"<<lineasNom[x]<<endl;
    		y=x;
		}
		archivo<<lineas[y+1]<<";"<<lineasNom[y+1];
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
		if(!cacheInt[e]==0){
			cout<<"Cedula: "<<cacheInt[e]<<" Nombre: "<<cacheStr[e]<<endl;	
		}
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


bool BuscarEnCache(int cedula, int cacheInt[], string cacheStr[], string &nombre){
	for(int x=0; x<20; x++){
		if(cacheInt[x] == cedula){
			nombre = cacheStr[x];
			return true;
		}
	}
	return false;
}
void CambiarCache(int indice,int cedula, int cacheInt[], string cacheStr[]){
	ifstream archivo , archivoAux;
	string texto, textoAux;
	archivo.open("ClientesRN.txt",ios::in);
	archivoAux.open("ClientesRN.txt",ios::in);
	if (archivo.fail()){
	    cout<<"No se pudo abrir el archivo";
	    exit(1);
	}
	else{
		int x = 1 , indicador = 0, pos = 0;
		string lineasAux[20];
		while(!archivo.eof()){
			getline(archivo,texto);
			if(pos==20){
				break;
			}
			if(x>=indice){
				if(texto[texto.length()-1]!='1'){
					lineasAux[pos] = texto;
					pos++;
					indicador++;
				}
			}
			x++;
		}
		archivo.close();
		if(indicador<20){
			int temp = 20-indicador,lineasExtra[temp];
			while(!archivoAux.eof()){
				getline(archivoAux,textoAux);
				if(temp==0){
					break;
				}
				else{
					if(textoAux[textoAux.length()-1]!='1'){
						lineasAux[indicador] = textoAux;
						indicador++;
						temp--;
					}
				}
			}
			archivoAux.close();
		}
		for(int w = 0;w<20;w++){
			int posPC = lineasAux[w].find(";");
        	int cedula = atoi(lineasAux[w].substr(0, posPC).c_str()); string nombre = lineasAux[w].substr(posPC + 1, lineasAux[w].length());
        	cacheInt[w]=cedula;
        	cacheStr[w]=nombre;
		}
	}
}

void CambiarCacheInsert(int indice, int cacheInt[], string cacheStr[]){
	ifstream archivo ;
	string texto;
	archivo.open("ClientesRN.txt",ios::in);
	if (archivo.fail()){
	    cout<<"No se pudo abrir el archivo";
	    exit(1);
	}
	else{
		int x = 1 , indicador = 0, pos = 19;
		string lineasAux[20];
		while(!archivo.eof()){
			getline(archivo,texto);
			if(x>=indice){
				cout<<"Texto: "<<texto<<endl;
				if(texto[texto.length()-1]!='1'){
					cout<<"No borrado"<<endl;
					lineasAux[pos] = texto;
					pos--;
					indicador++;
				}
			}
			if(pos==0){
				break;
			}
			x++;
		}
		archivo.close();
		for(int w = 0;w<20;w++){
			int posPC = lineasAux[w].find(";");
        	int cedula = atoi(lineasAux[w].substr(0, posPC).c_str()); string nombre = lineasAux[w].substr(posPC + 1, lineasAux[w].length());
        	cacheInt[w]=cedula;
        	cacheStr[w]=nombre;
		}
	}
}

void BuscarCliente(pNodoBinario &raiz , int cacheInt[], string cacheStr[]){
	int cedula; cout<<"Ingrese la cedula del usuario a buscar: "; cin>>cedula; cout<<endl;
	int indice; string nombre;
	if(ExisteCliente(raiz,cedula,indice)){
		if(BuscarEnCache(cedula,cacheInt,cacheStr,nombre)){
			cout<<"El cliente solicitado es "<< nombre<< " de cedula "<<cedula<<endl;	
		}
		else{
			CambiarCache(indice,cedula,cacheInt,cacheStr);
			if(BuscarEnCache(cedula,cacheInt,cacheStr,nombre)){
				cout<<"El cliente solicitado es "<< nombre<< " de cedula "<<cedula<<endl;	
			}
		}	
	}
	else{
		cout<<"El usuario ingresado no existe"<<endl;
	}
}

pNodoBinario unirABB(pNodoBinario izq, pNodoBinario der){
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    pNodoBinario centro = unirABB(izq->Hder, der->Hizq);
    izq->Hder = centro;
    der->Hizq = izq;
    return der;
}

void elimina(pNodoBinario &raiz, int x){
     if(raiz==NULL) return;

     if(x<raiz->valor)
         elimina(raiz->Hizq, x);
     else if(x>raiz->valor)
         elimina(raiz->Hder, x);

     else{
         pNodoBinario p = raiz;
         raiz = unirABB(raiz->Hizq, raiz->Hder);
         delete p;
     }
}

bool ExisteClienteAux(pNodoBinario &raiz, int cedula){
	if(raiz==NULL){
        return false;
    }
	else if (raiz->valor== cedula) {
		return true; 
    }
	else if(cedula<raiz->valor){
    	ExisteClienteAux(raiz->Hizq,cedula);
	}
	else{
		ExisteClienteAux(raiz->Hder,cedula);
	}
}
void eliminarCache(int cedula, int cacheInt[], string cacheStr[]){
        for (int x = 0; x<20; x++){
            if(cacheInt[x] == cedula){
                 cacheInt[x] = 0 ;
                 cacheStr[x] = "Cliente Borrado";
            }
       }
}
void EliminarCliente(pNodoBinario &raiz,int cacheInt[], string cacheStr[]){
	int cedula; cout<<"Ingrese la cedula del usuario a eliminar: "; cin>>cedula; cout<<endl;
	if(ExisteClienteAux(raiz,cedula)){
		elimina(raiz,cedula);
		eliminarCache(cedula,cacheInt,cacheStr);
		
		ifstream archivo,archAux;
		string texto,textoAux;
		archivo.open("ClientesRN.txt",ios::in);
		int largo = 0,t = 0;
		while(!archivo.eof()){
			getline(archivo,texto);
			largo++;
		}archivo.close();
		string lineasNuevas[largo];
		archAux.open("ClientesRN.txt",ios::in);
		while(!archAux.eof()){
			getline(archAux,textoAux);
			lineasNuevas[t] = textoAux ;
			t++;
		}archAux.close();
		remove("ClientesRN.txt");
		// Se reescribe el archivo con la bandera de borrado
		ofstream archivoNuevo;
		archivoNuevo.open("ClientesRN.txt",ios::out);
		int y;
		for(int e = 0;e<largo-1;e++){
			//cortamos el texto
			int posPC = lineasNuevas[e].find(";");
        	int cedulaAux = atoi(lineasNuevas[e].substr(0, posPC).c_str()); string nombre = lineasNuevas[e].substr(posPC + 1, lineasNuevas[e].length());
			if(cedula==cedulaAux){
				archivoNuevo<<lineasNuevas[e]<<"1"<<endl;
			}
			else{
				archivoNuevo<<lineasNuevas[e]<<endl;
			}
			y=e;
		}
		y++;
		int posPC = lineasNuevas[y].find(";");
    	int cedulaAux = atoi(lineasNuevas[y].substr(0, posPC).c_str()); string nombre = lineasNuevas[y].substr(posPC + 1, lineasNuevas[y].length());
		if(cedula==cedulaAux){
			archivoNuevo<<lineasNuevas[y]<<"1";
		}
		else{
			archivoNuevo<<lineasNuevas[y];
		}
		cout<<"Cliente eliminado con exito."<<endl;
		archivoNuevo.close();
	}
	else{
		cout<<"El cliente que usted desea eliminar no existe."<<endl;
	}
	
}

void InsertarCliente(pNodoBinario &raiz, int cacheInt[], string cacheStr[]){
	int cedula; cout<<"Ingrese la cedula del usuario a insertar: "; cin>>cedula; cout<<endl;
	string nombre; cout<< "Ingrese el nombre del usuario a insertar: "; cin>>nombre; cout<<endl;
	if(!ExisteClienteAux(raiz,cedula)){
		ifstream archivo;
		//Con este iclo deterimanos el indice del cliente
		string texto;
		archivo.open("ClientesRN.txt",ios::in);
		int largo = 0,t = 0;
		while(!archivo.eof()){
			getline(archivo,texto);
			largo++;
		}archivo.close();
		//Escribo el nuevo cliente
		ofstream archivoNuevo;
		archivoNuevo.open("ClientesRN.txt",ios::app);
		archivoNuevo<<endl<<cedula<<";"<<nombre;
		archivoNuevo.close();
		//Insertar en el arbol
		InsertarCedula(raiz,cedula,largo+1);
		//Cache
		int indice = (largo+1)-19;
		ifstream archivoC, archivoC2 ;
		string textoC, textoC2;
		archivoC.open("ClientesRN.txt",ios::in);
		archivoC2.open("ClientesRN.txt",ios::in);
		if (archivoC.fail()){
		    cout<<"No se pudo abrir el archivo";
		    exit(1);
		}
		else{
			int x = 0 , pos = 19, x2= 0;
			string lineasAux[20];
			indice--;
			int indice2 = indice;
			while(!archivoC2.eof()){
				getline(archivoC2,textoC2);
				if(pos==0){
					break;
				}
				if(x2>=indice2){
					if(textoC2[textoC2.length()-1]=='1'){
						indice--;
					}
				}
				x2++;
			}
			archivoC2.close();
			while(!archivoC.eof()){
				getline(archivoC,textoC);
				if(pos==0){
					lineasAux[pos] = textoC;
					break;
				}
				if(x>=indice){
					if(textoC[textoC.length()-1]!='1'){
						lineasAux[pos] = textoC;
						pos--;
					}
				}
				x++;
			}
			archivoC.close();
			for(int w = 0;w<20;w++){
				int posPC = lineasAux[w].find(";");
	        	int cedula = atoi(lineasAux[w].substr(0, posPC).c_str()); string nombre = lineasAux[w].substr(posPC + 1, lineasAux[w].length());
	        	cacheInt[w]=cedula;
	        	cacheStr[w]=nombre;
			}
		}
		cout<<"Cliente ingresado con exito"<<endl;
	}else{
		cout<<"La cedula ingresada ya existe"<<endl;
	}
	
}


void Reindexar(){
	ifstream archivo;
	string texto;
	ofstream archivoSalida;
	//Se inicializa la lista de indices
	remove("Indices.txt");
	archivoSalida.open("Indices.txt", ios::app);
	if(archivoSalida.fail()){
		cout<<"No se pudo crear el archivo"<<endl;
		exit(1);
	}
	//Se abre la lista de clientes
	archivo.open("ClientesRN.txt",ios::in);
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
		archivo.open("ClientesRN.txt",ios::in);
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
		int indice = 0;bool bandera = true;
		for(int x = 0;x<tam;x++){
			if(x==tam-1){
				bandera = false;
			}
			Indice(lineas[x],indice,bandera);
		}
	}cout<<"Se ha reindexado con exito"<<endl;
}


void Purgar(){
	ifstream archivo;
	//Con este c	iclo deterimanos el indice del cliente
	string texto;
	archivo.open("ClientesRN.txt",ios::in);
	int largo = 0, t =0;
	while(!archivo.eof()){
		getline(archivo,texto);
		if(texto[texto.length()-1]!='1'){
			largo++;
		}
		else{
			continue;
		}
	}archivo.close();
	
	string arrayLineas[largo];
	
	archivo.open("ClientesRN.txt",ios::in);
	while(!archivo.eof()){
		getline(archivo,texto);
		if(texto[texto.length()-1]!='1'){
			arrayLineas[t] = texto;
			t++;
		}
		else{
			continue;
		}
	}archivo.close();
	remove("ClientesRN.txt");
	ofstream archivoNuevo;
	archivoNuevo.open("ClientesRN.txt",ios::app);
	int y;
	for(int x = 0;x<largo-1;x++){
		archivoNuevo<<arrayLineas[x]<<endl;
		y=x;
	}
	archivoNuevo<<arrayLineas[y+1];
	archivoNuevo.close();
	cout<<"Purga realizada con exito."<<endl;
	
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
		    	cout<<endl;
		    	MostrarCache(cacheInt,cacheStr);
				system("pause>nul"); 
				break;
		    case 2:
		    	BuscarCliente(raiz , cacheInt, cacheStr);
		    	cout<<endl;
				MostrarCache(cacheInt,cacheStr);
				cout<<endl<<"Preorden del arbol: "<<endl;
				PreordenR(raiz);
		    	system("pause>nul");
		        break;    
			case 3:
				InsertarCliente(raiz, cacheInt, cacheStr);
				cout<<endl;
				MostrarCache(cacheInt,cacheStr);
				cout<<endl<<"Preorden del arbol: "<<endl;
				PreordenR(raiz);
		        system("pause>nul"); 
		        break;                 
		 	case 4:
		 		EliminarCliente(raiz,cacheInt,cacheStr);
		 		cout<<endl;
				MostrarCache(cacheInt,cacheStr);
				cout<<endl<<"Preorden del arbol: "<<endl;
				PreordenR(raiz);
		        system("pause>nul"); 
		        break;    
		    case 5:
		    	Purgar();
		    	cout<<endl;
				MostrarCache(cacheInt,cacheStr);
				cout<<endl<<"Preorden del arbol: "<<endl;
				PreordenR(raiz);
		        system("pause>nul"); 
		        break;  
			case 6:
				Reindexar();
				raiz = CrearArbol();
				cout<<endl;
				MostrarCache(cacheInt,cacheStr);
				cout<<endl<<"Preorden del arbol: "<<endl;
				PreordenR(raiz);
		        system("pause>nul"); 
		        break;       
		}	
	}
	while (opcion!=7);
		cout<<"Gracias por utilizar el programa"<<endl;			
   return 0;
}
