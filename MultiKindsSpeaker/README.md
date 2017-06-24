# SonicSensorSoundPlayer
A project to play mp3 file by ultora sonic sensor value.

# Connection
- A1 - SonicSensor1 Trigger
- A2 - SonicSensor1 Echo
- A3 - SonicSensor2 Trigger
- A4 - SonicSensor2 Echo
- D9 - DFPlayer play detect
- D10 - SoftSerial RX
- D11 - SoftSerial TX

# Files on SD
```
mp3
 |- 01
 |  |- 001.mp3 // music
 |  \- 002.mp3 // stop sound
 \- 02
    |- 001.mp3 // music
    \- 002.mp3 // stop sound
```

# Requirement
[DFRobotDFPlayerMini](https://github.com/DFRobot/DFRobotDFPlayerMini)

# License
MIT

# References
- [DFPlayer](https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299)
- [sound effect](http://soundeffect-lab.info/sound/anime/)
- [シリアル通信で制御可能なMP3プレーヤー](http://www.ne.jp/asahi/shared/o-family/ElecRoom/AVRMCOM/MP3module/MP3module.html)