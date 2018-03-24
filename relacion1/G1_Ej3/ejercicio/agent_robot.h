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
		CHOQUEPARED_=false;
		CHOQUEESQUINA_=false;
		GIRODERECHA_=false;
		TAMANOLATERAL_=0;
		TAMANOTOTAL_=0;
		CAMBIARTIRA_=false;
		RECOLOCAR_ = false;
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
	ActionType colocarEsquina();
	ActionType recorrerTira();
	ActionType cambiarTira();

private:
	bool CNY70_;
	bool BUMPER_;
	bool CHOQUEPARED_;
	bool CHOQUEESQUINA_;
	bool GIRODERECHA_;
	bool CAMBIARTIRA_;
	bool RECOLOCAR_;
	int TAMANOLATERAL_;
	int TAMANOTOTAL_;
};

string ActionStr(Agent::ActionType);

#endif
