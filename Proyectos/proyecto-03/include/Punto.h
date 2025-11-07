#include <string>

class Punto {
   public:
      Punto();
      Punto( double, double, double = 0 );
      double getX();
      double getY();
      void modificar( double, double, double = 0 );
      double dist2( Punto * );
      void sume( Punto * );
      void divida( double );
      std::string ver();

   private:
      double x, y, z;

};

