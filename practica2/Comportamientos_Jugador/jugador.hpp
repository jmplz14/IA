#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <stdlib.h>
#include <time.h>
#include <list>
struct casillaMapa {
  int fila;
  int columna;
};
struct estado {
  int fila;
  int columna;
  int orientacion;
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      ultimaAccion = actIDLE;
      hayPlan = false;
      obstaculoDelante = false;
      recibidaLocalizacion = false;
      numeroPasadasAleatorias = 0;
      encontradoPK = false;
      numeroPasadasMaximo = (mapaResultado.size() / 10);
      srand (time(NULL));
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      ultimaAccion = actIDLE;
      hayPlan = false;
      obstaculoDelante = false;
      recibidaLocalizacion = false;
      numeroPasadasAleatorias = 0;
      encontradoPK = false;
      numeroPasadasMaximo = (mapaResultado.size() / 10);
      srand (time(NULL));
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);

    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado destino;
    list<Action> plan;
    list<Action> planPK;

    // Nuevas Variables de Estado
    Action ultimaAccion;
    bool hayPlan, obstaculoDelante, recibidaLocalizacion, encontradoPK;
    int numeroPasadasAleatorias,numeroPasadasMaximo;


    bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);
    void PintaPlan(list<Action> plan);
    bool esCasillaValida(casillaMapa casilla, const std::vector< std::vector< unsigned char> > &mapa);
    void construirPlan(const list<casillaMapa> &camino, list<Action> &plan, int orientacionInicial);
    bool esValidoAvanzar(unsigned char terreno, unsigned char aldeano);
    bool buscarCaminoPkSensores(Sensores sensores);
    bool pintarSensores(Sensores sensores);
    bool buscarCaminoAnchura(const estado &origen, const estado &destino, list<Action> &plan, const std::vector< std::vector< unsigned char> > &mapa);
};

#endif
