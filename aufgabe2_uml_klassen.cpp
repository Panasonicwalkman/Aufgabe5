/*
 * Aufgabe 2 – UML und Klassenstellung (10 Punkte)
 *
 * Beschreibung (Portal-System):
 *   - Personen: ID, Name, E-Mail
 *   - Unterschied: Lehrperson vs. Schüler
 *   - Lehrperson kann Noten erfassen
 *   - Schüler besucht mindestens 1 Fach (z.B. Mathematik)
 *   - Fach besteht aus mehreren Leistungsnachweisen
 *   - Leistungsnachweis: Note (Dezimalzahl), Datum, Gewichtung
 *
 * ============================================================
 * UML-KLASSENDIAGRAMM (Textdarstellung)
 * ============================================================
 *
 *  +------------------+
 *  |     Person       |
 *  +------------------+
 *  | - id: int        |
 *  | - name: string   |
 *  | - email: string  |
 *  +------------------+
 *  | + getId(): int   |
 *  | + getName(): str |
 *  | + getEmail(): str|
 *  +------------------+
 *         ^
 *         | (Vererbung)
 *    _____|_____
 *   |           |
 * +-----------+  +-----------+
 * |Lehrperson |  |  Schüler  |
 * +-----------+  +-----------+
 * |           |  |           |
 * +-----------+  +-----------+
 * |noteErteil:|  | faecher:  |
 * |en(Leist.) |  |vector<Fa.>|
 * +-----------+  +-----------+
 *                     |
 *                     | 1..* (besucht)
 *                     v
 *              +--------------+
 *              |    Fach      |
 *              +--------------+
 *              | - name: str  |
 *              +--------------+
 *              | + addLN()    |
 *              | + getName()  |
 *              +--------------+
 *                     |
 *                     | 1..* (besteht aus)
 *                     v
 *         +----------------------+
 *         | Leistungsnachweis    |
 *         +----------------------+
 *         | - note: double       |
 *         | - datum: string      |
 *         | - gewichtung: double |
 *         +----------------------+
 *         | + getNote(): double  |
 *         | + getDatum(): string |
 *         | + getGewicht(): dbl  |
 *         +----------------------+
 */

#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------
// Klasse: Leistungsnachweis
// -------------------------------------------------------
class Leistungsnachweis {
private:
    double note;
    std::string datum;
    double gewichtung;

public:
    Leistungsnachweis(double note, std::string datum, double gewichtung)
        : note(note), datum(datum), gewichtung(gewichtung) {}

    double getNote() const { return note; }
    std::string getDatum() const { return datum; }
    double getGewichtung() const { return gewichtung; }
};

// -------------------------------------------------------
// Klasse: Fach
// -------------------------------------------------------
class Fach {
private:
    std::string name;
    std::vector<Leistungsnachweis> leistungsnachweise;

public:
    Fach(std::string name) : name(name) {}

    void addLeistungsnachweis(const Leistungsnachweis& ln) {
        leistungsnachweise.push_back(ln);
    }

    std::string getName() const { return name; }

    double getDurchschnitt() const {
        if (leistungsnachweise.empty()) return 0.0;
        double summe = 0, gewichtSumme = 0;
        for (const auto& ln : leistungsnachweise) {
            summe += ln.getNote() * ln.getGewichtung();
            gewichtSumme += ln.getGewichtung();
        }
        return gewichtSumme > 0 ? summe / gewichtSumme : 0.0;
    }

    void anzeigen() const {
        std::cout << "  Fach: " << name << std::endl;
        for (const auto& ln : leistungsnachweise) {
            std::cout << "    Note: " << ln.getNote()
                      << " | Datum: " << ln.getDatum()
                      << " | Gewichtung: " << ln.getGewichtung() << std::endl;
        }
        std::cout << "    Durchschnitt: " << getDurchschnitt() << std::endl;
    }
};

// -------------------------------------------------------
// Basisklasse: Person
// -------------------------------------------------------
class Person {
private:
    int id;
    std::string name;
    std::string email;

public:
    Person(int id, std::string name, std::string email)
        : id(id), name(name), email(email) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

    virtual void anzeigen() const {
        std::cout << "ID: " << id << " | Name: " << name << " | E-Mail: " << email << std::endl;
    }

    virtual ~Person() {}
};

// -------------------------------------------------------
// Abgeleitete Klasse: Schüler
// -------------------------------------------------------
class Schueler : public Person {
private:
    std::vector<Fach> faecher;

public:
    Schueler(int id, std::string name, std::string email)
        : Person(id, name, email) {}

    void addFach(const Fach& fach) {
        faecher.push_back(fach);
    }

    void anzeigen() const override {
        std::cout << "[Schüler] ";
        Person::anzeigen();
        for (const auto& f : faecher) {
            f.anzeigen();
        }
    }
};

// -------------------------------------------------------
// Abgeleitete Klasse: Lehrperson
// -------------------------------------------------------
class Lehrperson : public Person {
public:
    Lehrperson(int id, std::string name, std::string email)
        : Person(id, name, email) {}

    void noteErteilen(Fach& fach, double note, std::string datum, double gewichtung) {
        fach.addLeistungsnachweis(Leistungsnachweis(note, datum, gewichtung));
        std::cout << "Note " << note << " in Fach '" << fach.getName()
                  << "' erfasst." << std::endl;
    }

    void anzeigen() const override {
        std::cout << "[Lehrperson] ";
        Person::anzeigen();
    }
};

// -------------------------------------------------------
// Main
// -------------------------------------------------------
int main() {
    // Lehrperson erstellen
    Lehrperson lehrer(1, "Herr Müller", "mueller@schule.ch");
    lehrer.anzeigen();

    // Fach erstellen
    Fach mathe("Mathematik");

    // Schüler erstellen
    Schueler schueler(2, "Anna Meier", "anna@schule.ch");

    // Lehrperson erteilt Noten
    lehrer.noteErteilen(mathe, 5.5, "2026-03-15", 1.0);
    lehrer.noteErteilen(mathe, 4.0, "2026-05-20", 2.0);

    // Fach dem Schüler zuweisen
    schueler.addFach(mathe);

    // Ausgabe
    std::cout << "\n--- Schüleransicht ---" << std::endl;
    schueler.anzeigen();

    return 0;
}
