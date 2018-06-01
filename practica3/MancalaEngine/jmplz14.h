/*
 * jmplz14.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

class jmplz14:Bot {
public:
	jmplz14();
	~jmplz14();


	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
private:
	double pesos[6];
	Move buscarConAlfaBeta(const GameState &state, int niveles);
	double estadoMax(const GameState &state, double alfa, double beta, int profundidad, const GameState &padre, int num_hijo);
	double estadoMin(const GameState &state, double alfa, double beta, int profundidad, const GameState &padre, int num_hijo);
	int calcularValorEstadoJ1(const GameState &state);
	double calcularValorEstadoJ2(const GameState &state,const GameState &padre, int num_hijo);
};

#endif /* MANUPCBOT_H_ */
