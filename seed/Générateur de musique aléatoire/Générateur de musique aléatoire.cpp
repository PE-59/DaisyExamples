#include "daisy_seed.h"
#include "daisysp.h"
#include <random>
#include <iostream>

// Use the daisy namespace to prevent having to type
// daisy:: before all libdaisy functions
using namespace daisy;
using namespace daisysp;

// Declare a DaisySeed object called hardware
DaisySeed hardware;
Oscillator osc;


const int size = 1;
int tab[] = {65,65,65,65,68,68,68,65,0,65,70,70,65,65,63,63,65,65,65,65,72,72,72,65,0,65,73,73,72,72,68,68,65,65,72,72,77,77,65,63,0,63,60,60,67,67,65,65,65,65,0,0,0,0,0,0,77,0,0,0,77,0,0,0};
int i=0;
int gamme[]={36, 38,41,43,45,48,50,53,55,57};



//int blanches []; //toutes les notes sauf les noires 
//différentes games, aléatoire...

void MyCallback(AudioHandle::InputBuffer in,
                AudioHandle::OutputBuffer out,
                size_t size)
{
    // Make sound here!
    for (int i = 0; i < size; i++){
        float outOsc= osc.Process();
        out[0][i]=outOsc;
        out[1][i]=outOsc;
    }
}

int main(void)
{
    // Declare a variable to store the state we want to set for the LED.
    bool led_state;
    led_state = true;


    // Configure and Initialize the Daisy Seed
    // These are separate to allow reconfiguration of any of the internal
    // components before initialization.
    hardware.Configure();
    hardware.Init();

    float sr = hardware.AudioSampleRate();

    osc.Init(sr);
    
    hardware.StartAudio(MyCallback);

    int size = sizeof(tab) / sizeof(tab[0]);
    int note;
    int rythme;
    int Size_tableau=10;

    // Loop forever
    while(1)
    { 
        // Set the onboard LED
        hardware.SetLed(led_state);
        note=rand()%Size_tableau;
        //std::uniform_int_distribution<> uniform_int(0, 9);
        

        rythme= rand()%4;
        osc.SetFreq(mtof(gamme[note]));

        // Toggle the LED state for the next time around.
        led_state = !led_state;

        // Wait 500ms
        System::Delay(200*rythme);
        // i++;
        // if (i>size){
        //     i=0;
        // }
    }
}
