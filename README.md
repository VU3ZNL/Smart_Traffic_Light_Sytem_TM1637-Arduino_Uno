# Smart_Traffic_Light_Sytem_TM1637-Arduino_Uno
“Arduino-based Smart Traffic Light System using IR sensors and TM1637 display.”
# 🚦 Smart Traffic Light System using Arduino
A fully functional **Smart Traffic Management System** designed to control traffic density intelligently using **IR sensors** and a **TM1637 4-digit display**.  
Developed collaboratively by high school students and guided by TARRL (Tulunadu Amateur Radio Relay League)

---

👩‍🔬 Developed By
- **Shravana & Team — Sri Ramakrishna High School, Puttur — R&D**  
- **Mr. Vaibhav V K Naik** — **President & E&TW Intelligence, TARRL , Department Electronics ,Science Forum President, St. Philomena PU College, Puttur.**

---

## 🧩 Components Used

| SL No | Component           | Quantity | Description                              |
|-------|---------------------|-----------|------------------------------------------|
| 1     | IR Sensor           | 2 pcs     | Vehicle detection (East & West)          |
| 2     | Arduino UNO         | 1 pcs     | Main microcontroller                     |
| 3     | Breadboard          | 1 pcs     | Circuit connections                      |
| 4     | Red LED             | 2 pcs     | Signal light                             |
| 5     | Yellow LED          | 2 pcs     | Signal light                             |
| 6     | Green LED           | 2 pcs     | Signal light                             |
| 7     | **OR** Traffic Light Module | 1 pcs | Prebuilt 3-color signal                  |
| 8     | TM1637 Display      | 1 pcs     | Countdown and status display             |

---

## ⚙️ Working Principle
1. **No Vehicle Detected:**  
   Signal alternates between both sides automatically (R → Y → G and G → Y → R sequence).  

2. **Vehicle on West Side:**  
   - West gets green priority (Left side).  
   - East shows red and "STOP" on TM1637 display.  
   - Display counts down `3, 2, 1`, then shows `GO`.

3. **Vehicle on East Side:**  
   - East gets green priority.  
   - West shows red and "STOP" on display.  
   - Countdown `3, 2, 1`, then `GO`.

4. **Vehicles on Both Sides:**  
   - Display shows `"CA"` (Caution).  
   - Both sides blink **Yellow** to warn.

---

## 🎯 Purpose
- Reduce traffic congestion at intersections.  
- Improve vehicle flow efficiency.  
- Promote road safety awareness using automation.

---

## ⚙️ Pin Configuration

| SL No | Pin  | Connection             | Description                              |
|-------|------|------------------------|------------------------------------------|
| 1     | D2   | IR Sensor (West)       | Vehicle detection                        |
| 2     | D3   | IR Sensor (East)       | Vehicle detection                        |
| 3     | D6   | Red (East Signal)      | LED / Light                              |
| 4     | D7   | Yellow (East Signal)   | LED / Light                              |
| 5     | D8   | Green (East Signal)    | LED / Light                              |
| 6     | D9   | Red (West Signal)      | LED / Light                              |
| 7     | D10  | Yellow (West Signal)   | LED / Light                              |
| 8     | D11  | Green (West Signal)    | LED / Light                              |
| 9     | A4   | TM1637 Display DIO     | Data pin                                 |
| 10    | A5   | TM1637 Display CLK     | Clock pin                                |

> ⚙️ **Note:**  
> Provide **+5V VCC** for TM1637 Display and ensure a **common GND** for all connections (LEDs, IR sensors, and Arduino).

## 🧠 Libraries Required
- `TM1637Display.h` — for controlling the 4-digit display  
(Install via **Arduino Library Manager**)

---

## ⚙️ How It Works
This project demonstrates the use of **basic automation and sensor logic** to manage real-world traffic flow using **Arduino Uno**.  
It can be extended using:
- Ultrasonic or camera-based detection  
- Bluetooth or IoT integration  
- Real-time data monitoring for smart cities

---

## 🏁 Project Credits
> Built under **TARRL (Tulunadu Amateur Radio Relay League)** initiative for innovation and awareness in embedded systems and traffic automation.
**For more information visit - www.tarrltulunadu.in**
