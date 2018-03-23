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

	if(!CHOQUEARRIBA_){
		if(!CNY70_){
			accion = Agent::actFORWARD;
		}else{
			accion = Agent::actTURN_R;
			CHOQUEARRIBA_ = true;
		}
	}else{
		if(!CHOQUEDERECHA_){
			if(!CNY70_){
				accion = Agent::actFORWARD;
			}else{
				accion = Agent::actTURN_R;
				CHOQUEDERECHA_ = true;
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
