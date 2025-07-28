#include <iostream>
#include <string>
using namespace std;

// Clasa de baza care modeleaza un magazin de carne
class MagazinCarne {
private:
    const int idMagazinCarne;
    static int contor;

    char* tipCarne;
    float pret;
    int zilePanaExpira;
    int nrZile;
    int* stocZilnic; // vector cu stocul zilnic

public:
    // Constructor implicit
    MagazinCarne() : idMagazinCarne(contor++) {
        this->tipCarne = new char[strlen("Necunoscut") + 1];
        strcpy_s(this->tipCarne, strlen("Necunoscut") + 1, "Necunoscut");
        this->pret = 0;
        this->zilePanaExpira = 0;
        this->nrZile = 0;
        this->stocZilnic = NULL;
    }

    // Constructor cu parametri
    MagazinCarne(const char* tipCarne, float pret, int zilePanaExpira, int nrZile, int* stocZilnic)
        : idMagazinCarne(contor++) {
        this->tipCarne = new char[strlen(tipCarne) + 1];
        strcpy_s(this->tipCarne, strlen(tipCarne) + 1, tipCarne);
        this->pret = pret;
        this->zilePanaExpira = zilePanaExpira;
        this->nrZile = nrZile;
        this->stocZilnic = new int[this->nrZile];
        for (int i = 0; i < this->nrZile; i++) {
            this->stocZilnic[i] = stocZilnic[i];
        }
    }

    // Constructor de copiere (deep copy)
    MagazinCarne(const MagazinCarne& m) : idMagazinCarne(contor++) {
        this->tipCarne = new char[strlen(m.tipCarne) + 1];
        strcpy_s(this->tipCarne, strlen(m.tipCarne) + 1, m.tipCarne);
        this->pret = m.pret;
        this->zilePanaExpira = m.zilePanaExpira;
        this->nrZile = m.nrZile;
        this->stocZilnic = new int[this->nrZile];
        for (int i = 0; i < this->nrZile; i++) {
            this->stocZilnic[i] = m.stocZilnic[i];
        }
    }

    // Destructor
    ~MagazinCarne() {
        delete[] this->tipCarne;
        delete[] this->stocZilnic;
    }

    // Operator de atribuire
    MagazinCarne& operator=(const MagazinCarne& m) {
        if (&m != this) {
            delete[] this->tipCarne;
            delete[] this->stocZilnic;
            this->tipCarne = new char[strlen(m.tipCarne) + 1];
            strcpy_s(this->tipCarne, strlen(m.tipCarne) + 1, m.tipCarne);
            this->pret = m.pret;
            this->zilePanaExpira = m.zilePanaExpira;
            this->nrZile = m.nrZile;
            this->stocZilnic = new int[this->nrZile];
            for (int i = 0; i < this->nrZile; i++) {
                this->stocZilnic[i] = m.stocZilnic[i];
            }
        }
        return *this;
    }

    // Getteri
    const char* getTipCarne() { return this->tipCarne; }
    float getPret() { return this->pret; }
    int getZileExpira() { return this->zilePanaExpira; }
    int getNrZile() { return this->nrZile; }
    int* getStocZilnic() { return this->stocZilnic; }

    // Setteri
    void setTipCarne(const char* tipCarne) {
        delete[] this->tipCarne;
        this->tipCarne = new char[strlen(tipCarne) + 1];
        strcpy_s(this->tipCarne, strlen(tipCarne) + 1, tipCarne);
    }
    void setPret(float pret) { this->pret = pret; }
    void setZileExpira(int zilePanaExpira) { this->zilePanaExpira = zilePanaExpira; }
    void setNrZile(int nrZile) { this->nrZile = nrZile; }

    // Seteaza stocul zilnic (cu alocare noua)
    void setStocZilnic(int nrZile, int* stocZilnic) {
        delete[] this->stocZilnic;
        this->stocZilnic = new int[this->nrZile];
        for (int i = 0; i < this->nrZile; i++) {
            this->stocZilnic[i] = stocZilnic[i];
        }
    }

    // Afisare obiect
    friend ostream& operator<<(ostream& out, const MagazinCarne& c) {
        out << "Tip carne: " << c.tipCarne << endl;
        out << "Pret: " << c.pret << endl;
        out << "Expira in: " << c.zilePanaExpira << " zile" << endl;
        out << "Stoc zilnic: ";
        for (int i = 0; i < c.nrZile; i++) {
            out << c.stocZilnic[i] << " ";
        }
        out << endl;
        return out;
    }

    // Comparare obiecte
    bool operator==(MagazinCarne& c1) {
        if (strcmp(this->tipCarne, c1.tipCarne) != 0) return false;
        if (this->pret != c1.pret || this->zilePanaExpira != c1.zilePanaExpira || this->nrZile != c1.nrZile)
            return false;
        for (int i = 0; i < this->nrZile; i++) {
            if (this->stocZilnic[i] != c1.stocZilnic[i]) return false;
        }
        return true;
    }

    // Operator ++ prefixat
    MagazinCarne& operator++() {
        this->pret++;
        return *this;
    }

    // Operator ++ postfixat
    MagazinCarne operator++(int) {
        MagazinCarne copie = *this;
        this->zilePanaExpira++;
        return copie;
    }

    // Suma stoc
    int SumaStoc() {
        int suma = 0;
        for (int i = 0; i < nrZile; i++) {
            suma += this->stocZilnic[i];
        }
        return suma;
    }

    int AfiseazaSuma() { return SumaStoc(); }

    // Operator () – returneaza suma stocului
    float operator()() {
        float suma = 0;
        for (int i = 0; i < nrZile; i++)
            suma += this->stocZilnic[i];
        return suma;
    }

    // Operator ! – pret peste 50
    bool operator!() {
        return this->pret > 50;
    }

    // Operator [] – acces stoc
    int& operator[](int index) {
        if (index >= 0 && index < this->nrZile)
            return this->stocZilnic[index];
        else {
            cout << "Index invalid";
            int fallback = -1;
            return fallback;
        }
    }

    // Operator += – adauga o zi de stoc
    MagazinCarne& operator+=(int crestereStoc) {
        int* stocZilnicNou = new int[this->nrZile + 1];
        for (int i = 0; i < this->nrZile; i++) {
            stocZilnicNou[i] = this->stocZilnic[i];
        }
        stocZilnicNou[this->nrZile] = crestereStoc;
        this->nrZile++;
        delete[] this->stocZilnic;
        this->stocZilnic = stocZilnicNou;
        return *this;
    }

    // Operator >= – compara pret si stoc
    bool operator>=(MagazinCarne& c7) {
        return (this->pret >= c7.pret && this->nrZile >= c7.nrZile);
    }

    // Conversie explicita la float
    explicit operator float() {
        return this->pret;
    }
};

int MagazinCarne::contor = 1;

// Clasa derivata cu camp nou: calitate
class MagazinCarneSpecial : public MagazinCarne {
private:
    char* calitate;
public:
    MagazinCarneSpecial() : MagazinCarne() {
        calitate = new char[strlen("Anonim") + 1];
        strcpy_s(calitate, strlen("Anonim") + 1, "Anonim");
    }

    MagazinCarneSpecial(const char* tipCarne, float pret, int zilePanaExpira, int nrZile, int* stocZilnic, const char* calitate)
        : MagazinCarne(tipCarne, pret, zilePanaExpira, nrZile, stocZilnic) {
        this->calitate = new char[strlen(calitate) + 1];
        strcpy_s(this->calitate, strlen(calitate) + 1, calitate);
    }

    friend ostream& operator<<(ostream& out, const MagazinCarneSpecial& f) {
        out << (MagazinCarne&)f << endl;
        out << "Calitate: " << f.calitate << endl;
        return out;
    }
};

// Testare in main
int main() {
    MagazinCarne m0;
    cout << m0;

    int stoc[] = { 75,70,80 };
    MagazinCarne m1("Pui", 30, 5, 3, stoc);
    MagazinCarne m2 = m1;

    int stoc1[] = { 40,60,70,84 };
    MagazinCarne m3("Vita", 40, 5, 4, stoc);

    cout << (m1 == m2 ? "Obiectele sunt egale!\n" : "Obiectele sunt diferite!\n");
    cout << m1.AfiseazaSuma() << endl;

    m1 = ++m3;
    m1 = m3++;

    m1.setTipCarne("Porc");
    cout << m1.getTipCarne() << endl;

    float sumaStoc = m2();
    cout << sumaStoc << endl;

    float stocu = m1[1];
    cout << "Stocul din ziua 1: " << stocu << endl;

    m2 += 10;
    cout << m2;

    float pretCast = (float)m1;
    cout << "Pretul prin cast: " << pretCast << endl;

    int stocnou[] = { 34,60,100,500,32 };
    MagazinCarneSpecial mm("VitaPorc", 14, 3, 5, stocnou, "Wagyu");
    cout << mm << endl;
}
