# RumiCar-for-Node-RED-MCU

## 試作

### 車体

[部品表](./部品表.xlsx)  
本で見つけたアッカーマン・ジャントー方式を取り入れてみました。  
内部構造
![試作前面](./Fusion360/試作前面.jpg)
![試作背面](./Fusion360/試作背面.jpg)
![試作裏面](./Fusion360/試作裏面.jpg)

外装  
![試作外装前面](./Fusion360/試作外装前面.jpg)
![試作外装断面](./Fusion360/試作外装断面.jpg)

3Dプリンターで作ったもの  
![試作２内部](./image/試作２内部.jpg)
![試作２外装](./image/試作２外装.jpg)

動画：<https://youtu.be/6bydSzUHpmo>
[![試作１](./image/試作１.jpg)](https://youtu.be/6bydSzUHpmo)

### 回路図

![回路図試作](./Quadcept/20240113_17_36_30.png)

## 車体について

Fusion360で設計しています。  
3DプリンターはPrusa MK4、フィラメントはPLAで出力しています。  

## 回路について

### DRV8835

<https://404background.com/circuit/drv8835/>  
<https://youtu.be/BTHzUvILtWA>  
![DRV8835回路図](./image/DRV8835回路図.jpg)  

### VL53L0X

### WiFi AP(XIAO ESP32C3)

スマートフォンからコントロールするためのプログラムです。  
<https://404background.com/program/esp32c3-4/>
