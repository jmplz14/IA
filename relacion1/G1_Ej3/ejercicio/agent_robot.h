#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		CNY70_=false;
		BUMPER_=false;
		CHOQUEARRIBA_=false;
		CHOQUEDERECHA_=false;
		TAMANOLATERAL_=0;
		TAMANOTOTAL_=0;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
		actBACKWARD,
		actPUSH,
		actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();

private:
	bool CNY70_;
	bool BUMPER_;
	bool CHOQUEARRIBA_;
	bool CHOQUEDERECHA_;
	int TAMANOLATERAL_;
	int TAMANOTOTAL_;
};

string ActionStr(Agent::ActionType);

#endif
