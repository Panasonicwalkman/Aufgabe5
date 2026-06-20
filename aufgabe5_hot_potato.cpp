#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

enum class Status {
    normal,
    gesperrt
};

class Spieler {
private:
    std::string name;
    int leben;
    Status status;

public:
    Spieler(std::string name)
        : name(name), leben(15), status(Status::normal) {}

    std::string getName() const { return name; }
    int getLeben() const { return leben; }
    Status getStatus() const { return status; }
    bool istGesperrt() const { return status == Status::gesperrt; }

    void setLeben(int l) { leben = l; }
    void setStatus(Status s) { status = s; }

    void lebenAbziehen(int menge) {
        leben -= menge;
        if (leben < 0) leben = 0;
    }

    void ausgeben() const {
        std::cout << name << ": " << leben << " Leben";
        if (status == Status::gesperrt) std::cout << " [GESPERRT]";
        std::cout << std::endl;
    }
};

int wuerfeln() {
    return rand() % 6 + 1;
}

void spielzugAusfuehren(Spieler& aktiver, Spieler& gegner) {
    if (aktiver.istGesperrt()) {
        std::cout << aktiver.getName() << " ist gesperrt. Freiwuerfeln? (1 druecken): ";
        int eingabe;
        std::cin >> eingabe;
        int befreiungswurf = wuerfeln();
        std::cout << aktiver.getName() << " wuerfelt: " << befreiungswurf << std::endl;

        if (befreiungswurf == 6) {
            std::cout << "  -> Eine 6! " << aktiver.getName() << " ist befreit und spielt normal weiter!" << std::endl;
            aktiver.setStatus(Status::normal);
        } else {
            std::cout << "  -> Keine 6. " << aktiver.getName() << " bleibt noch gesperrt." << std::endl;
            return;
        }
    }

    std::cout << aktiver.getName() << " ist am Zug. (1 druecken zum Wuerfeln): ";
    int eingabe;
    std::cin >> eingabe;

    int wurf = wuerfeln();
    std::cout << aktiver.getName() << " wuerfelt: " << wurf << std::endl;

    if (wurf == 6) {
        std::cout << "  -> EINE 6! " << gegner.getName()
                  << " verliert 6 Leben und wird fuer 1 Runde gesperrt!" << std::endl;
        gegner.lebenAbziehen(6);
        gegner.setStatus(Status::gesperrt);
    } else {
        std::cout << "  -> " << gegner.getName() << " verliert " << wurf << " Leben." << std::endl;
        gegner.lebenAbziehen(wurf);

        if (gegner.istGesperrt()) {
            gegner.setStatus(Status::normal);
            std::cout << "  (" << gegner.getName() << "'s Sperre ist abgelaufen.)" << std::endl;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    std::string name1, name2;
    std::cout << "=== HOT POTATO SPIEL ===" << std::endl;
    std::cout << "Name Spieler 1: ";
    std::cin >> name1;
    std::cout << "Name Spieler 2: ";
    std::cin >> name2;

    Spieler spieler1(name1);
    Spieler spieler2(name2);

    std::cout << "\nSpiel beginnt! Beide Spieler starten mit 15 Leben.\n" << std::endl;

    int runde = 1;

    while (spieler1.getLeben() > 0 && spieler2.getLeben() > 0) {
        std::cout << "--- Runde " << runde << " ---" << std::endl;
        spieler1.ausgeben();
        spieler2.ausgeben();
        std::cout << std::endl;

        if (spieler2.getLeben() > 0) {
            spielzugAusfuehren(spieler1, spieler2);
        }
        if (spieler2.getLeben() <= 0) break;

        std::cout << std::endl;

        if (spieler1.getLeben() > 0) {
            spielzugAusfuehren(spieler2, spieler1);
        }
        if (spieler1.getLeben() <= 0) break;

        std::cout << std::endl;
        runde++;
    }

    std::cout << "\n=== SPIELENDE nach Runde " << runde << " ===" << std::endl;
    spieler1.ausgeben();
    spieler2.ausgeben();

    if (spieler1.getLeben() <= 0 && spieler2.getLeben() <= 0) {
        std::cout << "Unentschieden!" << std::endl;
    } else if (spieler1.getLeben() <= 0) {
        std::cout << "\nGewinner: " << spieler2.getName() << "! Herzlichen Glueckwunsch!" << std::endl;
    } else {
        std::cout << "\nGewinner: " << spieler1.getName() << "! Herzlichen Glueckwunsch!" << std::endl;
    }

    return 0;
}