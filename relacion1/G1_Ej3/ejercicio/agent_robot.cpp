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

	/*if(BUMPER_){
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
	}*/

	//apartado c
	if(BUMPER_ && !EMPUJAROBSTACULO_){
		accion = Agent::actTURN_R;
	}else{
		if(CONTARTIRA_){
			accion = contarTira();
		}else{
			if(VOLVER_){
				accion = volverObjeto();
			}else{
				if(CARAACTUAL_ < 3){
					if(CAMBIARCARA_ && RECOLOCAR_ && CAMBIARTIRA_){
						CONTARTIRA_ = true;
						ACTUAL_ = 0;
						CARAACTUAL_++;
					}
					accion = cambiarCara();

				}else{
					if(!EMPUJAROBSTACULO_){
						accion = recolocar();
					}else{
						accion = empujar();
					}
				}
			}
		}


	}


	return static_cast<ActionType> (accion);

}
Agent::ActionType Agent::empujar(){
	int accion = 0;
	if(CNY70_)
		accion = Agent::actIDLE;
	else
		accion = Agent::actPUSH;
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



Agent::ActionType Agent::contarTira(){
	int accion = 0;
	if(!CNY70_ && ACTUAL_ < MINIMO_){
		if(!GIRODERECHA_){
			accion = Agent::actTURN_R;
			GIRODERECHA_ = true;
		}else{
			accion = Agent::actFORWARD;
			ACTUAL_++;
		}
	}else{

		if(ACTUAL_ < MINIMO_){
			NUMCARAMINIMO_ = CARAACTUAL_;
			MINIMO_ = ACTUAL_;
			CARAFINAL_ = (NUMCARAMINIMO_ + 2)%4;
			NUMCAMBIOSCARA_ = (CARAFINAL_ + 1)%4;
		}

		ACTUAL_--;
		if(ACTUAL_ >= 0){
			accion = Agent::actBACKWARD;
			VOLVER_ = true;
		}else{
			CAMBIARCARA_ = true;
			accion = Agent::actTURN_L;
		}

		GIRODERECHA_ = false;
		CONTARTIRA_ = false;
	}
	return static_cast<ActionType> (accion);
}

Agent::ActionType Agent::volverObjeto(){
	int accion = 0;
	if(ACTUAL_ > 0){
		accion = Agent::actBACKWARD;
		ACTUAL_--;
	}else{
		VOLVER_ = false;
		CAMBIARCARA_ = true;
		accion = Agent::actTURN_L;

	}
	return static_cast<ActionType> (accion);
}
int Agent::minimo(){
	return NUMCAMBIOSCARA_;
}
Agent::ActionType Agent::recolocar(){
	int accion = 0;
	if( NUMCAMBIOSCARA_ > 0 ){
		if(!CAMBIARCARA_ && !RECOLOCAR_ && !CAMBIARTIRA_){
			CAMBIARCARA_ = true;
		}
		if(CAMBIARCARA_ && RECOLOCAR_ && CAMBIARTIRA_){
			NUMCAMBIOSCARA_--;
		}
		accion = cambiarCara();

	}else{
		accion = Agent::actTURN_L;
		EMPUJAROBSTACULO_ = true;
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

Agent::ActionType Agent::cambiarCara(){
	int accion = 0;
	if(CAMBIARCARA_ && !RECOLOCAR_ && !CAMBIARTIRA_){
		accion = Agent::actFORWARD;
		RECOLOCAR_ = true;
	}else if(CAMBIARCARA_ && RECOLOCAR_ && !CAMBIARTIRA_){
		accion = Agent::actTURN_L;
		CAMBIARTIRA_ = true;
	}else{
		accion = Agent::actFORWARD;
		CAMBIARTIRA_ = false;
		RECOLOCAR_ = false;
		CAMBIARCARA_ = false;

	}



	return static_cast<ActionType> (accion);
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
