# Aufgabe 1 – Softwareentwicklung (5 Punkte)
## IoT-System: Büropflanzenschutz (Feuchtigkeitssensor + Alarm)

---

## Analyse und Spezifikation

### 1. User Story (Sicht Mitarbeiter im Büro)
> **Als** Mitarbeiter im Büro  
> **möchte ich** benachrichtigt werden, wenn die Erde meiner Büropflanze zu trocken ist,  
> **damit** ich die Pflanze rechtzeitig giessen kann und sie nicht eingeht.

### 2. Erfolgskriterium
Das Projekt gilt als erfolgreich abgeschlossen, wenn:
- Der Feuchtigkeitssensor zuverlässig zu trockene Erde erkennt (unter definiertem Schwellenwert).
- Der Nutzer innerhalb von 60 Sekunden nach Unterschreitung des Schwellenwerts eine Benachrichtigung (z. B. Alarm-LED, Buzzer oder App-Push) erhält.
- Das System mindestens 7 Tage ohne Neustart stabil läuft.

---

## Design und Architektur

### 1. Datenpfad (3–4 Schritte)
1. **Messen:** Analoger Feuchtigkeitssensor liefert Spannung (0–3.3 V) an den ADC des Microcontrollers.
2. **Verarbeiten:** Microcontroller liest ADC-Wert, vergleicht ihn mit Schwellenwert (z. B. < 30 % Feuchte).
3. **Senden:** Bei Trockenheit sendet der Microcontroller per HTTP-POST den Messwert an den Server.
4. **Benachrichtigen:** Server wertet den Wert aus und schickt Alarm (Push-Notification / E-Mail) an den Nutzer.

### 2. API-Endpunkt & JSON-Datenstruktur

**HTTP-Methode & URL:**
```
POST /api/v1/sensor/moisture
```

**JSON-Body (Microcontroller → Server):**
```json
{
  "device_id": "plant-sensor-01",
  "moisture_percent": 18.5,
  "timestamp": "2026-06-06T11:30:00Z",
  "alert": true
}
```

---

## Implementation (Ablauf auf dem Microcontroller in C++)

```
1. Setup: ADC-Pin initialisieren, WiFi verbinden
2. Loop (alle 60 Sekunden):
   a. ADC-Wert lesen → in Prozentwert umrechnen
   b. Wenn moisture_percent < THRESHOLD (z. B. 30):
      - JSON-Payload erstellen
      - HTTP-POST an Server senden
      - LED / Buzzer aktivieren
   c. Sonst: LED aus, weiter warten
3. Fehlerbehandlung: Bei fehlgeschlagenem HTTP-Request → 3x retry, danach lokaler Alarm
```

---

## Test und Fehlerbehebung

**Kritisches Risiko:** Der Sensor liefert fehlerhafte Werte (z. B. durch Korrosion oder Kabelbruch) und gibt permanent „trocken" zurück.

**Reaktion der Software:**
- Plausibilitätsprüfung: Wenn der ADC-Wert für > 24 h ununterbrochen unter 5 % bleibt, wird ein Sensor-Fehler-Alarm ausgelöst (statt normaler Trocken-Alarm), damit der Nutzer den Sensor prüft – und kein Systemabsturz entsteht.

---

## Dokumentation
*(Diese Phase ist laut Aufgabenstellung für diese Übung ignoriert.)*
