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
		//apartado c
		CAMBIARCARA_ = false;
		VOLVER_ = false;
		CONTARTIRA_ = true;
		MINIMO_ = 100;
		ACTUAL_ = 0;
		CARAACTUAL_ = 0;
		NUMCARAMINIMO_;

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
	ActionType cambiarCara();
	ActionType volverObjeto();
	ActionType rotar();
	ActionType contarTira();

private:
	bool CNY70_;
	bool BUMPER_;
	bool CHOQUEPARED_;
	bool CHOQUEESQUINA_;
	bool GIRODERECHA_;
	bool CAMBIARTIRA_;
	bool RECOLOCAR_;
	bool CONTARTIRA_;
	bool CAMBIARCARA_;
	bool VOLVER_;
	int TAMANOLATERAL_;
	int TAMANOTOTAL_;
	int MINIMO_;
	int ACTUAL_;
	int CARAACTUAL_;
	int NUMCARAMINIMO_;


};

string ActionStr(Agent::ActionType);

#endif
