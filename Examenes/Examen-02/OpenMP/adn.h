#include <string>
#include <random>
class ADN
{
private:
   std::string sequence;

public:
   ADN(int = 100);
   ADN(std::string palabra);
   ~ADN();
   std::string toString();
   void printSeqs();
   void printSeqs(std::string, int, int, std::string = "");
   static int rng(int min, int max);

   static std::string compararADN(const std::string& X,const std::string& Y);

   inline long getSize() const { return sequence.size(); }
   inline std::string getSequence() {return sequence;}

   std::string Palindromo();
};
