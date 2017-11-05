# UltraSonicForMusicAndLed
A project to play mp3 and control LED by ultora sonic sensor.

# Connection
- A1 - SonicSensor1 Trigger
- A2 - SonicSensor1 Echo
- A3 - [10K rotary register + 1K register]
- D8 - LED control
- D9 - DFPlayer play detect
- D10 - DFPlayer TX
- D11 - DFPlayer RX through 0.3~1.0 register

# Files on SD
```
mp3
 |- 01
 |  |- 0001.mp3 // music
 |  \- 0002.mp3 // stop sound
 |- 02
 |  \- 0001.mp3 // music
 \- 03
    \- 0001.mp3 // music
```

# Requirement
[DFRobotDFPlayerMini](https://github.com/DFRobot/DFRobotDFPlayerMini)

# License
MIT

# References
- [DFPlayer](https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299)
- [sound effect](http://soundeffect-lab.info/sound/anime/)
- [シリアル通信で制御可能なMP3プレーヤー](http://www.ne.jp/asahi/shared/o-family/ElecRoom/AVRMCOM/MP3module/MP3module.html)
