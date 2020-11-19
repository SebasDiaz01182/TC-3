#include<iostream>

using namespace std;
class NodoBinario {
   public:
	NodoBinario(int v,int pindice){
		valor = v;
		indice= pindice;
		Hder = NULL;
		Hizq = NULL;
		siguiente = NULL;
		anterior = NULL;
	}
	
	//Atributos
    int indice,valor;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;
    
};

typedef NodoBinario *pNodoBinario;


void InsertarCedula(pNodoBinario &raiz,int valor,int indice){
	if(raiz==NULL){
		raiz = new NodoBinario(valor,indice);
	}
	else{
		if(valor<=raiz->valor){
			InsertarCedula(raiz->Hizq,valor, indice);
		}
		else{
			InsertarCedula(raiz->Hder,valor, indice);
		}
	}
}

void PreordenR(NodoBinario *R){
    
    if(R==NULL){
        return;
    }
	else{
		cout<<R->valor<<" -> ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
        
    }
}
