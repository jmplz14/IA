#include "agent_robot.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	int accion = 0;
//Apartado a
/*
	if(!CHOQUEPARED_){
		if(!CNY70_){
			accion = Agent::actFORWARD;
		}else{
			accion = Agent::actTURN_R;
			CHOQUEESQUINA_ = true;
		}
	}else{
		if(!CHOQUEESQUINA_){
			if(!CNY70_){
				accion = Agent::actFORWARD;
			}else{
				accion = Agent::actTURN_R;
				CHOQUEESQUINA_ = true;
			}
		}else{

			if(!CNY70_){
				TAMANOLATERAL_++;
				accion = Agent::actFORWARD;
			}else{
				TAMANOTOTAL_ = TAMANOLATERAL_ * 2;
				accion = Agent::actIDLE;
			}

		}
	}*/
	//Apartado b

	if(BUMPER_){
		accion = Agent::actIDLE;
	}else if(!CHOQUEPARED_ || !CHOQUEESQUINA_)
		accion = colocarEsquina();

	else if(CHOQUEPARED_ && CHOQUEESQUINA_ && !CAMBIARTIRA_ && !RECOLOCAR_)
		accion = recorrerTira();

	else if(CHOQUEPARED_ && CHOQUEESQUINA_ && RECOLOCAR_){
		if(GIRODERECHA_)
			accion = Agent::actTURN_R;
		else
			accion = Agent::actTURN_L;

		RECOLOCAR_ = false;
		GIRODERECHA_ = GIRODERECHA_ ? false : true;

	}else if(CHOQUEPARED_ && CHOQUEESQUINA_ && CAMBIARTIRA_){
		if(!CNY70_){
			accion = Agent::actFORWARD;
			CAMBIARTIRA_ = false;
			RECOLOCAR_ = true;
		}else
			accion = Agent::actIDLE;


	}else{
		accion = Agent::actIDLE;
	}

	return static_cast<ActionType> (accion);

}
Agent::ActionType Agent::colocarEsquina(){
	int accion = 0;
	if(!CHOQUEPARED_){
		if(!CNY70_){
			accion = Agent::actFORWARD;
		}else{
			accion = Agent::actTURN_R;
			CHOQUEPARED_ = true;
		}
	}else{
		if(!CHOQUEESQUINA_){
			if(!CNY70_){
				accion = Agent::actFORWARD;
			}else{
				accion = Agent::actTURN_R;
				CHOQUEESQUINA_ = true;
			}
		}
	}
	return static_cast<ActionType> (accion);
}

Agent::ActionType Agent::recorrerTira(){
	int accion = 0;
	if(!CNY70_){
		accion = Agent::actFORWARD;
	}else{
		if(GIRODERECHA_)
			accion = Agent::actTURN_R;
		else
			accion = Agent::actTURN_L;

		CAMBIARTIRA_ = true;
	}
	return static_cast<ActionType> (accion);
}
Agent::ActionType Agent::cambiarTira(){

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	CNY70_ = env.isFrontier();
	BUMPER_ = env.isBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actBACKWARD: return "BACKWARD";
	case Agent::actPUSH: return "PUSH";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
