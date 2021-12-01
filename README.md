# AutoRobo
A brief foray into state space control systems.

<b>PHASE ONE</b>

First Go (Finished: 1, 2, x)
1)  Im working on normal control first to get my feet wet.
    Currently Im designing a remote to control my robot.
      * SPI OLED display for remote visuals
      * nRF24L01 SPI radio for transmission
      * joystick module for direction
      * seeeduino xiao for control (for initial tests an Arduino Mega was used)

    Board design is also uploaded.
    
2) Integrate receiving nRF24 into robot. Mock up is already
   live to test remote.
      * Arduino Uno - needed to use software SPI because motordriver uses hardware SPI for nonSPI purposes.
      * nRF24L01

3) Write control algorithm for robot.
      * Y position on joystick to control forward/backward speed
      * X position on joystick to control left/right
      * Display to show intended direction of motion with an arrow on remote


The robot body contains a Seeedstudio motordriver v2, Arduino Uno, and Arduino prototype shield (on which lies the nRF).

<b>PHASE TWO</b>
