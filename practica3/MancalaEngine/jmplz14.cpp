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
using namespace std;

jmplz14::jmplz14() {
	// Inicializar las variables necesarias para ejecutar la partida

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

	Move movimiento= bucarConAlfaBeta(state);

	return movimiento;
}
Move jmplz14::bucarConAlfaBeta(const GameState &state){
	Move movimiento= M_NONE;
	Player turno= state.getCurrentPlayer();
	int mejorValor = INT_MIN;
	for (int i = 1; i<=6; i++){

		if(state.getSeedsAt(turno, (Position) i) >0){
			GameState hijo =  state.simulateMove( (Move) i);
			int valorHijo;

			if(turno != hijo.getCurrentPlayer())
				valorHijo = estadoMin(hijo, INT_MIN, INT_MAX, 9);
			else
				valorHijo = estadoMax(hijo, INT_MIN, INT_MAX, 9);

			if(valorHijo > mejorValor){
				mejorValor = valorHijo;
				movimiento = (Move)i;
			}


		}
	}


	return movimiento;
}

int jmplz14::estadoMax(const GameState &state, int alfa, int beta, int profundidad){
	if (state.isFinalState() && profundidad == 0)
		return calcularValorEstado(state);

	Player turno= state.getCurrentPlayer();
	int valor = INT_MIN ;
	for (int i = 1; i<=6; i++){

		if(state.getSeedsAt(turno, (Position) i) >0){
			GameState hijo =  state.simulateMove( (Move) i);
			int valorHijo;

			if(turno != hijo.getCurrentPlayer())
				valorHijo = estadoMin(hijo, alfa, beta, profundidad - 1);
			else
				valorHijo = estadoMax(hijo, alfa, beta, profundidad - 1);

			if (valorHijo > alfa)
				alfa = valorHijo;

			if(alfa >= beta)
				return beta;


		}
	}

	return alfa;
}

int jmplz14::estadoMin(const GameState &state, int alfa, int beta, int profundidad){
	if (state.isFinalState() && profundidad == 0)
		return calcularValorEstado(state);

	Player turno= state.getCurrentPlayer();
	for (int i = 1; i<=6; i++){

		if(state.getSeedsAt(turno, (Position) i) >0){
			GameState hijo =  state.simulateMove( (Move) i);
			int valorHijo;
			if(turno != hijo.getCurrentPlayer())
				valorHijo = estadoMax(hijo, alfa, beta, profundidad - 1);
			else
				valorHijo = estadoMin(hijo, alfa, beta, profundidad - 1);

			if(valorHijo > beta)
				beta = valorHijo;

			if( beta <= alfa )
				return alfa;


		}
	}

	return beta;
}
int jmplz14::calcularValorEstado(const GameState &state){
	Player contrario = this->getPlayer() == J1 ? J2 : J1 ;
	return state.getScore(this->getPlayer()) - state.getScore(contrario);
}
