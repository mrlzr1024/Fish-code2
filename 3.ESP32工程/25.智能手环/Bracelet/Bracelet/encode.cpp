#include "encode.h"




// Functions prototyping to be handled on each Encoder Event

// Create a global pointer for the encoder object
Versatile_RotaryEncoder *versatile_encoder;

int Rotation[3] = {0, 0, 0};
int level = 0;
mode Mode_1;



void Encode_init()
{

    // display.begin(115200);
    versatile_encoder = new Versatile_RotaryEncoder(clk, dt, sw);

    // Load to the encoder all nedded handle functions here (up to 9 functions)
    versatile_encoder->setHandleRotate(handleRotate);
    versatile_encoder->setHandlePressRotate(handlePressRotate);
    versatile_encoder->setHandleHeldRotate(handlePressRotate);
    //versatile_encoder->setHandleHeldRotate(handleHeldRotate);
    versatile_encoder->setHandlePress(handlePress);
    versatile_encoder->setHandlePressRelease(handlePressRelease);
    versatile_encoder->setHandleLongPress(handleLongPress);
    versatile_encoder->setHandleLongPressRelease(handleLongPressRelease);
    versatile_encoder->setHandlePressRotateRelease(handlePressRotateRelease);
    versatile_encoder->setHandleHeldRotateRelease(handleHeldRotateRelease);

    Display("Ready!");

    // set your own defualt values (optional)
    // versatile_encoder->setReadIntervalDuration(1); // set 2ms as long press duration (default is 1ms)
    // versatile_encoder->setShortPressDuration(35); // set 35ms as short press duration (default is 50ms)
    // versatile_encoder->setLongPressDuration(550); // set 550ms as long press duration (default is 1000ms)
}





void handleHeldRotate(int8_t rotation)
{
    Rotation[2] += rotation; //       #==>
}



void handlePressRelease()
{
    level = 0;
    // Display("-");
}

void handleLongPress()
{
    level = 3;
    // if(Mode_1==Step){
    //     step=0;
    //     Step_detect();
    // }
    // Display("#");
}

void handleLongPressRelease()
{
    level = 0;
    // Display("@");
}

void handlePressRotateRelease()
{
    level = 0;
    // Display("#8");
}

void handleHeldRotateRelease()
{
    level = 0;
    // Display("#9");
}