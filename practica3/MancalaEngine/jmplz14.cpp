/*
 * jmplz14.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "jmplz14.h"

#include <string>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <map>
using namespace std;

jmplz14::jmplz14(){
	pesos[0] = 0.198649;
	pesos[1] = 0.190084;
	pesos[2] = 0.370793;
	pesos[3] = 1;
	pesos[4] = 0.418841;
	pesos[5] = 0.565937;
}

jmplz14::~jmplz14() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void jmplz14::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string jmplz14::getName() {
	return "jmplz14"; // Sustituir por el nombre del bot
}

Move jmplz14::nextMove(const vector<Move> &adversary, const GameState &state) {

	Move movimiento;
	if (this->getPlayer() == J1 )
		movimiento = buscarConAlfaBeta(state,10);
	else
		movimiento = buscarConAlfaBeta(state,10);

	return movimiento;
}

Move jmplz14::buscarConAlfaBeta(const GameState &state,int niveles){
	Move movimiento= M_NONE;
	Player turno= state.getCurrentPlayer();
	double mejorValor = INT_MIN;
	for (int i = 1; i<=6; i++){
		if(state.getSeedsAt(turno, (Position) i) >0){
			GameState hijo =  state.simulateMove( (Move) i);
			double valorHijo;

			if(turno != hijo.getCurrentPlayer())
				valorHijo = estadoMin(hijo, INT_MIN, INT_MAX, niveles, state, i);
			else
				valorHijo = estadoMax(hijo, INT_MIN, INT_MAX, niveles, state, i);

			if(valorHijo > mejorValor){
				mejorValor = valorHijo;
				movimiento = (Move)i;
			}
			cerr << "movimiento: " << i << ":" << valorHijo << endl;

		}
	}


	return movimiento;
}

double jmplz14::estadoMax(const GameState &state, double alfa, double beta, int profundidad, const GameState &padre, int num_hijo){
	if ( (state.isFinalState() || profundidad == 0) && this->getPlayer() == J1)
		return calcularValorEstadoJ1(state);

	if ( (state.isFinalState() || profundidad == 0) && this->getPlayer() == J2)
			return calcularValorEstadoJ2(state,padre,num_hijo);
	Player turno= state.getCurrentPlayer();
	for (int i = 1; i<=6; i++){
		if(state.getSeedsAt(turno, (Position) i) >0){
			GameState hijo =  state.simulateMove( (Move) i);
			double valorHijo;

			if(turno != hijo.getCurrentPlayer())
				valorHijo = estadoMin(hijo, alfa, beta, profundidad - 1, state, i);
			else
				valorHijo = estadoMax(hijo, alfa, beta, profundidad - 1, state, i);

			if (valorHijo > alfa)
				alfa = valorHijo;

			if(alfa >= beta)
				return beta;


		}
	}

	return alfa;
}

double jmplz14::estadoMin(const GameState &state, double alfa, double beta, int profundidad, const GameState &padre, int num_hijo){
	if ( (state.isFinalState() || profundidad == 0) && this->getPlayer() == J1)
		return calcularValorEstadoJ1(state);

	if ( (state.isFinalState() || profundidad == 0) && this->getPlayer() == J2)
			return calcularValorEstadoJ2(state,padre,num_hijo);

	Player turno= state.getCurrentPlayer();
	for (int i = 1; i<=6; i++){

		if(state.getSeedsAt(turno, (Position) i) >0){
			GameState hijo =  state.simulateMove( (Move) i);
			double valorHijo;
			if(turno != hijo.getCurrentPlayer())
				valorHijo = estadoMax(hijo, alfa, beta, profundidad - 1, state, i);
			else
				valorHijo = estadoMin(hijo, alfa, beta, profundidad - 1, state, i);

			if(valorHijo < beta)
				beta = valorHijo;

			if( beta <= alfa )
				return alfa;


		}
	}

	return beta;
}

double jmplz14::calcularValorEstadoJ2(const GameState &state, const GameState &padre, int num_hijo){
	Player contrario, actual; //= this->getPlayer() == J1 ? J2 : J1 ;
	double h0,h1,h2,h3,h4,h5, i = 1;
	actual = this->getPlayer();
	if (actual == J1 )
		contrario = J2;
	else
		contrario = J1;
	// MAximizar el numero de semillas en el casillero de la izquierda
	h0 = state.getSeedsAt(actual, (Position) 6) * pesos[0];
	//Maximizar el numero de semillas en tus casillero
	h1 = state.getSeedsAt(actual, (Position) 6) + state.getSeedsAt(actual, (Position) 5) + \
	state.getSeedsAt(actual, (Position) 4) + state.getSeedsAt(actual, (Position) 3) + \
	state.getSeedsAt(actual, (Position) 2) + state.getSeedsAt(actual, (Position) 1);
	h1 *= pesos[1];
	//Numero de movimientos posibles
	h2 = 0;
	while(i <= 6){
		if( state.getSeedsAt(actual, (Position) i) > 0)
			h2++;
		i++;
	}
	h2 *= pesos[2];
	//Numero de semillas actual
	h3 = state.getScore(actual) * pesos[3];
	//casillero con semillas mas a la derecha
	h4 = 0;
	i = 1;
	while(i <= 6 && padre.getSeedsAt(actual, (Position) i) > 0)
		i++;
	if(i == num_hijo)
		h4 = 1 * pesos[4];

	//puntos del enemigo
	h5 = state.getScore(contrario) * pesos[5];

	return h0+h1+h2+h3+h4-h5;
}
int jmplz14::calcularValorEstadoJ1(const GameState &state){
	Player contrario; //= this->getPlayer() == J1 ? J2 : J1 ;
	if (this->getPlayer() == J1 )
		contrario = J2;
	else
		contrario = J1;
	//cerr << "no soy jugador " << contrario << endl ;
	return state.getScore(this->getPlayer()) - state.getScore(contrario);
}
