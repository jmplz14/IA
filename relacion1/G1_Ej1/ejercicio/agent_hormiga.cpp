#include "agent_hormiga.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;
bool anterior_feromona = false;
// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	int accion = 0;

	if(FEROMONA_){
		accion = Agent::actFORWARD;
		anterior_feromona = true;
	}else if(!anterior_feromona){
		accion = Agent::actTURN_L;
	}else{
		anterior_feromona = false;
		accion = Agent::actTURN_R;
	}

	return static_cast<ActionType> (accion);

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	FEROMONA_ = env.isFeromona();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	default: return "????";
	}
}
