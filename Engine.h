#pragma once
#include "Arduino.h"

class Engine {

    private:

    const int noteDel = 100;

    const int buzzer = 3;
    
    const int buttonStartPin = 4;
    const int buttonRightPin = 5;
    const int buttonLeftPin = 6;

    bool buttonStart = false;
    bool buttonRight = false;
    bool buttonLeft = false;
    
    const int indicatorLED = 7;

    const int motorPinOne = 8;
    const int motorPinTwo = 9;

    const int scoreHighPin = 10;
    const int scoreMedPin = 11;
    const int scoreLowPin = 12;

    int time = 0;
    int frequency = 50;
    int timesFlashed = 0;
    int timeOverAll = 0;


    public:

    bool doTimer = false;
    bool ledOn = false;
    bool on = false;
    bool previouslyOn = false;
    bool resetMode = false;
    int pressDurration = 0;
    int scoreObtained = 0;

    Engine();

    void timer();
    int decreaseFrequency(int lastSpeed);
    void handleInput();
    void controlMotor();
    void resetTimer();

    void startUpSequence();
    void startSequence();
    void highSequence();
    void medSequence();
    void lowSequence();
    void playNote(char note, int del);
    void playNote(int freq, int del);
    void playSong(char notes[], int size, int del);

};