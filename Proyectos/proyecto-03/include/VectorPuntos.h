#include "Punto.h"


class VectorPuntos {
   public:
      VectorPuntos( long, double );
      VectorPuntos( long );
      ~VectorPuntos();
      long demeTamano();
      long masCercano( Punto * );
      double variabilidad( Punto *, long, long * );
      double disimilaridad( VectorPuntos *, long * );
      void genEpsFormat( VectorPuntos *, long *, char * );
      Punto * operator [] ( long );

   private:
      long elementos;
      Punto ** bloque;

};

