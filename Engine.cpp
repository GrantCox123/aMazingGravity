#include "Engine.h"

Engine :: Engine() {

    pinMode(buttonStartPin, INPUT);
    pinMode(buttonRightPin, INPUT);
    pinMode(buttonLeftPin, INPUT);

    pinMode(scoreHighPin, INPUT);
    pinMode(scoreMedPin, INPUT);
    pinMode(scoreLowPin, INPUT);
    
    pinMode(buzzer, OUTPUT);
    pinMode(indicatorLED, OUTPUT);
    pinMode(motorPinOne, OUTPUT);
    pinMode(motorPinTwo, OUTPUT);

}

void Engine :: timer() {
    controlMotor();
    time++;
    if (time % frequency == 0) {
        ledOn = !ledOn;
        if (ledOn) {
            if (frequency <= 20) tone(buzzer, 523);
            digitalWrite(indicatorLED, HIGH);
        } else {
            if (frequency <= 20) noTone(buzzer);
            digitalWrite(indicatorLED, LOW);
        }
    }
    if (time == 100) {
        time = 0;
        timesFlashed++;
        if (timesFlashed == 8) {
            timesFlashed = 0;
            frequency = decreaseFrequency(frequency);
        }
        timeOverAll++;
        if (timeOverAll == 32) {
            resetTimer();
            playNote('h', 1000);
            delay(500);
            lowSequence();
        }

    }
    delay(10);
}

void Engine :: handleInput() {

    buttonStart = (digitalRead(buttonStartPin) == HIGH) ? true : false;
    buttonRight = (digitalRead(buttonRightPin) == HIGH) ? true : false;
    buttonLeft = (digitalRead(buttonLeftPin) == HIGH) ? true : false;

    if (!doTimer) {
        delay(10);
        if (buttonStart) pressDurration++;
    }
    
    if (pressDurration > 300 && !resetMode) {
        pressDurration = 0;
        resetMode = true;
        digitalWrite(indicatorLED, HIGH);
        playNote('h', 200);
    }
    if (pressDurration > 100 && resetMode) {
        pressDurration = 0;
        resetMode = false;
        digitalWrite(indicatorLED, LOW);
        playNote('h', 200);
        delay(3000);
    }

    if (!buttonStart && pressDurration < 200 && pressDurration != 0 && !resetMode) {
        pressDurration = 0;
        if (!doTimer) startSequence();
        doTimer = true;
    }

    if (doTimer) {
        if (digitalRead(scoreHighPin) == HIGH && digitalRead(scoreMedPin) == LOW && digitalRead(scoreLowPin) == LOW) { 
            on = true;
            doTimer = false;
            resetTimer();
            scoreObtained = 3;
        } else if (digitalRead(scoreHighPin) == LOW && digitalRead(scoreMedPin) == HIGH && digitalRead(scoreLowPin) == LOW) { 
            on = true;
            scoreObtained = 2;
            resetTimer();
            doTimer = false;
        } else if (digitalRead(scoreHighPin) == LOW && digitalRead(scoreMedPin) == LOW && digitalRead(scoreLowPin) == HIGH) { 
            on = true;
            scoreObtained = 1;
            resetTimer();
            doTimer = false;
        } else {
            on = false;
            scoreObtained = 0;
        }
    }
}

void Engine :: controlMotor() {

    if (buttonRight) {
        analogWrite(motorPinOne, 255);
        digitalWrite(motorPinTwo, LOW);
    } if (buttonLeft) {
        digitalWrite(motorPinOne, LOW);
        analogWrite(motorPinTwo, 255);
    } if (!buttonRight && !buttonLeft) {
        digitalWrite(motorPinOne, LOW);
        digitalWrite(motorPinTwo, LOW);
    }

}

int Engine :: decreaseFrequency(int lastSpeed) {
    if (lastSpeed == 10) return lastSpeed;
    int newSpeed = lastSpeed - 5;
    if (100 % newSpeed == 0) return newSpeed;
    else return decreaseFrequency(newSpeed);
}

void Engine :: startUpSequence() {
    char notes[] = {'h', 'i', 'j'};
    playSong(notes, 3, 50);
}

void Engine :: startSequence() {
    digitalWrite(indicatorLED, HIGH);
    playNote('g', 750);
    digitalWrite(indicatorLED, LOW);
    delay(500);
    digitalWrite(indicatorLED, HIGH);
    playNote('g', 750);
    digitalWrite(indicatorLED, LOW);
    delay(500);
    digitalWrite(indicatorLED, HIGH);
    playNote('i', 1000);
    digitalWrite(indicatorLED, LOW);
}

void Engine :: highSequence() {
    playNote('j', 100);
    delay(100);
    playNote('j', 100);
    playNote('j', 100);
    delay(100);
    playNote(739, 750);

}

void Engine :: medSequence() {
    char notes[] = {'g', 'g', 'g', 'g', 'g', 'g'};
    playSong(notes, 6, 75);
}

void Engine :: lowSequence() {
    playNote(80, 200);
    delay(100);
    playNote(70, 200);
    delay(100);
    playNote(60, 200);
}


void Engine :: playNote(char note, int del) {

    switch (note) {
        case 'a':
            tone(buzzer, 261);
            break;
        case 'b':
            tone(buzzer, 293);
            break;
        case 'c':
            tone(buzzer, 329);
            break;
        case 'd':
            tone(buzzer, 349);
            break;
        case 'e':
            tone(buzzer, 392);
            break;
        case 'f':
            tone(buzzer, 440);
            break;
        case 'g':
            tone(buzzer, 493);
            break;
        case 'h':
            tone(buzzer, 523);
            break;
        case 'i':
            tone(buzzer, 587);
            break;
        case 'j':
            tone(buzzer, 659);
            break;
        case 'k':
            tone(buzzer, 698);
            break;
    }
    delay(del);
    noTone(buzzer);

}

void Engine :: playNote(int freq, int del) {

    tone(buzzer, freq);
    delay(del);
    noTone(buzzer);

}

void Engine :: resetTimer() {
    timeOverAll = 0;
    frequency = 50;
    doTimer = false;
    digitalWrite(indicatorLED, LOW);
    digitalWrite(motorPinOne, LOW);
    digitalWrite(motorPinTwo, LOW);
}

void Engine :: playSong(char notes[], int size, int del) {
    for (int i = 0; i < size; i++) {
        playNote(notes[i], del);
        delay(del);
    }
}