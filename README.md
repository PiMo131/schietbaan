# 🔌 MOSFET Control System – Arduino + HTML Simulator

Dit project bevat een volledig werkend systeem voor het aansturen van **MOSFET-kanalen via een Arduino Nano ESP32**, met per kanaal een **toggle-schakelaar**, **drukknop** en **tijdgestuurde knipperlogica**.

Daarnaast bevat het project een **mobielvriendelijke HTML-simulator** waarmee het systeem ook in een browser getest kan worden.

---

## 🧠 Werking Arduino-systeem

### Algemeen principe:
- Elk van de 6 kanalen heeft:
  - Een **toggle-schakelaar** (fysiek of virtueel): bepaalt of het MOSFET-kanaal actief mag zijn.
  - Een **drukknop**: activeert het knippergedrag.
  - Een **MOSFET** (via PWM-uitgang): schakelt de belasting aan/uit.

### Standaardgedrag:
- Bij opstarten staan **alle MOSFET-uitgangen AAN** (`HIGH`) → alle belasting is bekrachtigd.
- Wordt een drukknop ingedrukt terwijl de toggle **aan** staat:
  - De bijbehorende uitgang begint te **knipperen (1s aan, 1s uit)** gedurende **exact 5 minuten**.
- Druk je **opnieuw tijdens het knipperen**, dan wordt het knipperen gestopt en de uitgang staat direct weer continu **AAN**.
- Als de toggle wordt uitgezet tijdens het knipperen, wordt het kanaal **uitgeschakeld** (LED uit, uitgang `LOW`).

Alle actieve kanalen knipperen **gesynchroniseerd**: alle leds knipperen tegelijk aan en uit, onafhankelijk van wanneer ze gestart zijn.

---

## 📟 Pinout (Arduino Nano ESP32)

| Kanaal | Drukknop (input) | MOSFET-uitgang (PWM) |
|--------|------------------|-----------------------|
| 1      | D2               | A3                    |
| 2      | D3               | A2                    |
| 3      | D4               | A1                    |
| 4      | D5               | A0                    |
| 5      | D6               | A4                    |
| 6      | D7               | A5                    |

- **Drukknoppen zijn actief laag** (verbonden met GND), en gebruiken `INPUT_PULLUP`.
- **MOSFET-uitgangen zijn digitale outputs** en schakelen `HIGH` bij AAN.

> Toggle-schakelaars zitten **niet direct op de Arduino**, maar worden toegepast in serie met de MOSFET’s voedingslijn — of worden virtueel gesimuleerd in de HTML-pagina.

---

## 💻 HTML-simulator

De `/simulator/index.html` is een volledig werkende browser-simulatie van het gedrag van het systeem.

### Simuleert:
- **6 kanalen** met:
  - Toggle (schakelaar in serie)
  - Drukknop
  - LED-indicatie

### LED-status:
| Kleur/status   | Betekenis                      |
|----------------|-------------------------------|
| 🔘 Grijs        | Kanaal is uitgeschakeld       |
| 🟢 Groen        | Kanaal is continu AAN         |
| 🟢 Knipperend   | Kanaal is aan het knipperen   |

Je kunt de simulator openen op mobiel, tablet of desktop — of hosten vanaf een ESP32 (bijv. met WebServer).

---

## 🧪 Hardwarecomponenten

- Arduino Nano ESP32 (of gelijkwaardig met voldoende digitale IO)
- 6 MOSFET’s (logic-level, N-channel)
- 6 drukknoppen
- 6 toggle-schakelaars (fysiek of virtueel)
- 6 belastingen (bv. LEDs of relais)
- (optioneel) pull-down weerstand op MOSFET-gate

---

## 📈 Mogelijke uitbreidingen

- Logging of status via seriële poort
- WiFi-webinterface op de ESP32 zelf
- Fysieke toggle switches ook via IO-poorten lezen
- Tijd per kanaal instelbaar maken

---

## 📜 Licentie

MIT-licentie – vrij te gebruiken, aan te passen en te verspreiden.

---


