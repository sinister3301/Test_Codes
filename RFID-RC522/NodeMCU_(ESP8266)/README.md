# NodeMCU RFID Card Reader using RC522

This project demonstrates how to interface the **RC522 RFID Reader** with a **NodeMCU (ESP8266)** to scan RFID cards and print their UID and card type on the **Serial Monitor**.

---

## 🔌 Circuit Connections

| RC522 RFID | NodeMCU (ESP8266) |
|------------|-------------------|
| SDA        | D2 (GPIO4)        |
| SCK        | D5 (GPIO14)       |
| MOSI       | D7 (GPIO13)       |
| MISO       | D6 (GPIO12)       |
| RST        | D1 (GPIO5)        |
| 3.3V       | 3.3V              |
| GND        | GND               |

> ⚠️ **Do not connect the RC522 to 5V**, it may damage the module or NodeMCU.

---

## 🧰 Required Libraries

Install the following libraries from the Arduino Library Manager:

- **MFRC522 by GithubCommunity**
- **SPI** (Built-in)

---

## 🧾 How It Works

1. Upload the code to your NodeMCU.
2. Open the **Serial Monitor** at **115200 baud**.
3. Bring a 13.56 MHz RFID card/tag near the RC522 reader.
4. The UID and card type will be printed on the Serial Monitor.

---

## 🧑‍💻 Author

- **Faizul**
- Project Date: **20 June 2025**

---


## 📄 License

This project is open-source and free to use under the [MIT License](LICENSE).
