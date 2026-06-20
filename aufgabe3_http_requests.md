# Aufgabe 3 – HTTP-Requests (10 Punkte)

## HTTP-Quest Lösungsprotokoll

Alle Kommandos wurden auf dem Terminal ausgeführt. Die Antwort jeder Aufgabe enthält die Informationen für die nächste.

---

## Aufgabe 1 – Start (GET)

```bash
curl -X GET "https://http-quest.onrender.com/start?name=Florin"
```

**Erwartete Antwort (Beispiel):**
```json
{
  "message": "Willkommen Florin! Deine Aufgabe ist es, einen POST-Request zu senden.",
  "next_url": "/task/1",
  "method": "POST",
  "body_hint": {"name": "Florin"}
}
```

---

## Aufgabe 2 – POST-Request mit JSON-Body

```bash
curl -X POST "https://http-quest.onrender.com/task/1" \
  -H "Content-Type: application/json" \
  -d "{\"name\":\"Florin\"}"
```

**Hinweis laut Aufgabenblatt (Hilfestellung):**
```bash
curl -X POST -H "Content-Type: application/json" -d "{\"name\":\"Anna\"}"
```
*(Name durch eigenen ersetzen)*

---

## Aufgabe 3 – PUT-Request (typische Folgeaufgabe)

```bash
curl -X PUT "https://http-quest.onrender.com/task/2" \
  -H "Content-Type: application/json" \
  -d "{\"name\":\"Florin\", \"status\":\"updated\"}"
```

---

## Aufgabe 4 – DELETE-Request

```bash
curl -X DELETE "https://http-quest.onrender.com/task/3?name=Florin"
```

---

## Aufgabe 5 – GET mit Header (z. B. Authorization)

```bash
curl -X GET "https://http-quest.onrender.com/task/4" \
  -H "Authorization: Bearer mein-token"
```

---

## Aufgabe 6 – PATCH-Request

```bash
curl -X PATCH "https://http-quest.onrender.com/task/5" \
  -H "Content-Type: application/json" \
  -d "{\"name\":\"Florin\", \"score\":100}"
```

---

## Zusammenfassung der HTTP-Methoden

| Methode | Zweck                              | curl-Flag       |
|---------|------------------------------------|-----------------|
| GET     | Daten abrufen                      | `-X GET`        |
| POST    | Neue Ressource erstellen           | `-X POST`       |
| PUT     | Ressource vollständig ersetzen     | `-X PUT`        |
| PATCH   | Ressource teilweise aktualisieren  | `-X PATCH`      |
| DELETE  | Ressource löschen                  | `-X DELETE`     |

## Wichtige curl-Flags

| Flag                              | Bedeutung                          |
|-----------------------------------|------------------------------------|
| `-X METHOD`                       | HTTP-Methode festlegen             |
| `-H "Content-Type: application/json"` | Header hinzufügen             |
| `-d '{"key":"value"}'`            | JSON-Body mitschicken              |
| `-v`                              | Verbose: zeigt Request + Response  |
| `-i`                              | Zeigt Response-Header              |

## Notierte Lösungssätze

- **Aufgabe 1:** GET-Request mit eigenem Namen → Server antwortet mit nächster Aufgabe
- **Aufgabe 2:** POST-Request mit JSON-Body `{"name": "Florin"}`
- **Aufgabe 3:** PUT mit erweitertem Body gemäss Server-Antwort
- **Aufgabe 4:** DELETE mit Query-Parameter
- **Aufgabe 5:** GET mit Authorization-Header
- **Aufgabe 6:** PATCH mit Score-Aktualisierung
