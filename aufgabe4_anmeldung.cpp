/*
 * Aufgabe 4 – Flussdiagramm: Anmeldeprozess (5 Punkte)
 *
 * Logik:
 *  - Passwort darf max. 3x eingegeben werden
 *  - Bei 3 Fehlversuchen: 15 Minuten gesperrt
 *  - Danach erneuter Versuch: nochmals falsch → permanent gesperrt → Admin
 *  - Korrekt nach Sperre → Login erfolgreich
 *  - Nutzer bekommt immer eine Rückmeldung
 */

#include <iostream>
#include <string>

const std::string RICHTIGES_PASSWORT = "geheim123";
const int MAX_VERSUCHE = 3;

// Simuliert 15-Minuten-Sperre (hier nur Ausgabe)
void warte15Minuten() {
    std::cout << "Konto ist für 15 Minuten gesperrt." << std::endl;
    std::cout << "[Simuliert: Warte 15 Minuten...]" << std::endl;
}

// Gibt den Benutzer die Möglichkeit, ein Passwort einzugeben
// Gibt true zurück wenn korrekt, sonst false
bool passwortEingabe(const std::string& benutzer) {
    std::string eingabe;
    std::cout << "Passwort für " << benutzer << ": ";
    std::cin >> eingabe;
    return eingabe == RICHTIGES_PASSWORT;
}

int main() {
    std::string benutzer;
    std::cout << "Benutzername: ";
    std::cin >> benutzer;

    int versuche = 0;
    bool eingeloggt = false;

    // Erste Phase: max. 3 Versuche
    while (versuche < MAX_VERSUCHE) {
        versuche++;
        std::cout << "Versuch " << versuche << " von " << MAX_VERSUCHE << std::endl;

        if (passwortEingabe(benutzer)) {
            eingeloggt = true;
            break;
        } else {
            std::cout << "Falsches Passwort." << std::endl;
        }
    }

    if (eingeloggt) {
        std::cout << "\nLogin erfolgreich! Willkommen, " << benutzer << "." << std::endl;
        return 0;
    }

    // 3 Fehlversuche: 15 Minuten Sperre
    warte15Minuten();

    std::cout << "Sie können es erneut versuchen." << std::endl;

    // Zweite Phase: ein letzter Versuch nach der Sperre
    if (passwortEingabe(benutzer)) {
        std::cout << "\nLogin erfolgreich nach Sperre! Willkommen, " << benutzer << "." << std::endl;
    } else {
        std::cout << "\nKonto permanent gesperrt." << std::endl;
        std::cout << "Bitte wenden Sie sich telefonisch an den Administrator." << std::endl;
    }

    return 0;
}
