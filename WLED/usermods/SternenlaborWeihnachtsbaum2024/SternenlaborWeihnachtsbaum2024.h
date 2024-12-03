#pragma once

#include "wled.h"

class SternenlaborWeihnachtsbaum2024 : public Usermod
{
private:
public:
    void setup()
    {
        strip.resetSegments();

        uint8_t pins1[5] = {2, 255, 255, 255, 255};
        uint8_t pins2[5] = {4, 255, 255, 255, 255};
        uint16_t start = 0;
        uint16_t length1 = 48;
        uint16_t length2 = 2;
        uint8_t colorOrder = COL_ORDER_GRB;
        bool reversed = false;
        uint8_t skipFirst = 0;
        uint8_t AWmode = RGBW_MODE_MANUAL_ONLY;
        uint16_t freqkHz = 0;
        bool useGlobalLedBuffer = false;

        BusConfig bus1 = BusConfig(TYPE_WS2812_RGB, pins1, start, length1, colorOrder, reversed, skipFirst, AWmode, freqkHz, useGlobalLedBuffer);
        BusConfig bus2 = BusConfig(TYPE_WS2812_RGB, pins2, start, length2, colorOrder, reversed, skipFirst, AWmode, freqkHz, useGlobalLedBuffer);

        busses.removeAll();
        busses.add(bus1);
        busses.add(bus2);

        for (uint8_t i = 0; i < 8; i++)
        {
            uint16_t startLED = i * 6;
            uint16_t stopLED = startLED + 6;
            strip.setSegment(i, startLED, stopLED);
            if (i % 2 != 0)
            {
                strip.getSegment(i).setOption(SEG_OPTION_REVERSED, true);
            }
        }

        strip.setSegment(8, 48, 50);
    }

    void loop()
    {
    }

    /*
     * getId() allows you to optionally give your V2 usermod an unique ID (please define it in const.h!).
     * This could be used in the future for the system to determine whether your usermod is installed.
     */
    uint16_t getId()
    {
        return USERMOD_ID_STERNENLABOR_WEIHNACHTSBAUM_2024;
    }
};