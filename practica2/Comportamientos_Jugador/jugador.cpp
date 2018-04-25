#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"


#include <iostream>
#include <assert.h>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;


void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}
casillaMapa rellenarCasillaMapa(int fila, int columna){

	casillaMapa casilla;
	casilla.fila = fila;
	casilla.columna = columna;

	return casilla;
}

estado rellenarEstado(int fila, int columna, int orientacion){

	estado e;
	e.fila = fila;
	e.columna = columna;
	e.orientacion = orientacion;

	return e;
}

bool ComportamientoJugador::esCasillaValida(casillaMapa casilla){
	bool estado = false;
	int tamano = mapaResultado.size();
	char terreno;
	bool dentro = casilla.fila >= 0 && casilla.columna < tamano && casilla.columna >= 0 && casilla.columna < tamano;
	if(dentro){
		terreno = mapaResultado[casilla.fila][casilla.columna];
		estado = terreno == 'S' || terreno == 'K' || terreno == 'T';
	}
	return estado;
}
void ComportamientoJugador::construirPlan( const list<casillaMapa> &camino, list<Action> &plan, int orientacionInicial){
	list<casillaMapa>::const_iterator it = camino.begin();
	casillaMapa actual, siguiente;

	actual = *it;
	++it;
	int calculoFila, calculoColumna, orientacion;
	estado estadoAnterior = rellenarEstado(actual.fila, actual.columna, orientacionInicial);

	while(it != camino.end()){
		siguiente = *it;
		calculoFila = siguiente.fila - actual.fila;
		calculoColumna = siguiente.columna - actual.columna;
		if(calculoColumna == 0)
			if(calculoFila == -1)
				orientacion = 0;
			else
				orientacion = 2;
		else if( calculoColumna == -1)
				orientacion = 3;
		else
				orientacion = 1;

		//Si el estado anterior es dinstino al de ahora hay que girar
		if(estadoAnterior.orientacion != orientacion){

			int destino = (estadoAnterior.orientacion + 1) % 4;
			if( destino == orientacion){
				plan.push_back(actTURN_R);
				estadoAnterior.orientacion = destino;
			}else
				while( orientacion != estadoAnterior.orientacion ){
					estadoAnterior.orientacion = (estadoAnterior.orientacion + 3) % 4;
					plan.push_back(actTURN_L);
				}

		}
		estadoAnterior = rellenarEstado(siguiente.fila, siguiente.columna, estadoAnterior.orientacion);
		plan.push_back(actFORWARD);

		actual = siguiente;
		++it;
	}


}

bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	plan.clear();
	int tamanoMapa = mapaResultado.size();
	vector<vector<bool>> mapaCasillasVisitadas(tamanoMapa,vector<bool>(tamanoMapa, false));
	int incrementosFila[4] = {-1,0,1,0};
	int incrementosColumna[4] = {0,1,0,-1};

	//mirar si hay un aldeano enfrente
	if(aldeanoDelante){
		mapaCasillasVisitadas[ origen.fila + incrementosFila[origen.orientacion] ][ origen.columna + incrementosColumna[origen.orientacion] ] = true;
		aldeanoDelante = false;
	}
	//Creamos la cola para la busqueda en anchura
	queue <list<casillaMapa>> casillasAVisitar;

	//Preparamaos la lista necesaria para ir alamacenando el camino
	casillaMapa casillaInicio;
	casillaInicio = rellenarCasillaMapa(origen.fila, origen.columna);
	list<casillaMapa> caminoInicial,caminoActual;
	caminoInicial.push_back(casillaInicio);

	//iniciamos la cola de casillas a visitar con la lista en la que estado
	//la casilla de origen
	casillasAVisitar.push(caminoInicial);
	mapaCasillasVisitadas[origen.fila][origen.columna] = true;


	bool encontradoDestino = false;

	while (!casillasAVisitar.empty() && !encontradoDestino){
		caminoActual = casillasAVisitar.front();
		casillasAVisitar.pop();
		casillaMapa ultimaCasilla = caminoActual.back();

		if(ultimaCasilla.fila == destino.fila && ultimaCasilla.columna == destino.columna)
			encontradoDestino = true;
		else{

			casillaMapa casillaSiguiente;
			for(int i = 0; i < 4; i++){
				casillaSiguiente=rellenarCasillaMapa(ultimaCasilla.fila + incrementosFila[i],ultimaCasilla.columna + incrementosColumna[i]);

				if(!mapaCasillasVisitadas[casillaSiguiente.fila][casillaSiguiente.columna])
					if(esCasillaValida(casillaSiguiente)){
						mapaCasillasVisitadas[casillaSiguiente.fila][casillaSiguiente.columna] = true;
						caminoActual.push_back(casillaSiguiente);
						casillasAVisitar.push(caminoActual);
						caminoActual.pop_back();

					}

			}

		}
	}

	if(encontradoDestino)
		construirPlan(caminoActual,plan,origen.orientacion);


	// Descomentar para ver el plan en el mapa
	VisualizaPlan(origen, plan);

	return encontradoDestino;
}

Action ComportamientoJugador::think(Sensores sensores) {
  if (sensores.mensajeF != -1){
		fil = sensores.mensajeF;
		col = sensores.mensajeC;
	}

	// Actualizar el efecto de la ultima accion
	switch (ultimaAccion){
		case actTURN_R: brujula = (brujula+1)%4; break;
		case actTURN_L: brujula = (brujula+3)%4; break;
		case actFORWARD:
			switch (brujula){
				case 0: fil--; break;
				case 1: col++; break;
				case 2: fil++; break;
				case 3: col--; break;
			}
			cout << "fil: " << fil << "  col: " << col << " Or: " << brujula << endl;
	}



	// Determinar si ha cambiado el destino desde la ultima planificacion
	if (hayPlan and (sensores.destinoF != destino.fila or sensores.destinoC != destino.columna)){
		cout << "El destino ha cambiado\n";
		hayPlan = false;
	}

	//mirar si hay aldeano delante
	if (hayPlan && sensores.superficie[2] == 'a' && plan.front() == 0){
		cout << "Tienes un aldenado enfrente\n";
		hayPlan = false;
		aldeanoDelante = true;
	}



	// Determinar si tengo que construir un plan
	if (!hayPlan){
		estado origen;
		origen.fila = fil;
		origen.columna = col;
		origen.orientacion = brujula;

		destino.fila = sensores.destinoF;
		destino.columna = sensores.destinoC;

    hayPlan = pathFinding(origen,destino,plan);
	}


	// Ejecutar el planmapaConPlan
	Action sigAccion;
	if (hayPlan and plan.size()>0){
		sigAccion = plan.front();
		plan.erase(plan.begin());
	}
	else {
		sigAccion = actIDLE;
	}

	ultimaAccion = sigAccion;
	return sigAccion;
}


void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}

void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
