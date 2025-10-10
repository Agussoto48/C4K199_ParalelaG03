class Tren
{
private:
    int capMaxima;
    int acutales;
    enum {ABORDANDO = 0, DESABORDANDO = 1} state;
public:
    Tren(int n):
        capMaxima(n),
        acutales(0)
        {}
    ~Tren(){

    }
    bool agregarPasajero(){
        if(this->acutales + 1 < this->capMaxima){
            this->acutales++;
            std::cout << "Estuve aqui\n";
            return true;
        }
        return false;
    } 
    void liberarPasajero(){
        this->acutales--;
    }
    int getState(){
        return state;
    }
};


