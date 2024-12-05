#pragma once

#define DEFAULT_LED_COUNT 50

#include "wled.h"

class SternenlaborWeihnachtsbaum2024 : public Usermod
{
private:
    bool needsToRun = true;

    String colorToHexString(uint32_t c)
    {
        char buffer[9];
        sprintf(buffer, "%06X", c);
        return buffer;
    }

public:
    void setup()
    {
        strip.resetSegments();

        uint8_t pins1[5] = {2, 255, 255, 255, 255};
        uint8_t pins2[5] = {4, 255, 255, 255, 255};
        uint16_t start1 = 0;
        uint16_t start2 = 48;
        uint16_t length1 = 48;
        uint16_t length2 = 2;
        uint8_t colorOrder = COL_ORDER_GRB;
        bool reversed = false;
        uint8_t skipFirst = 0;
        uint8_t AWmode = RGBW_MODE_MANUAL_ONLY;
        uint16_t freqkHz = 0;
        bool useGlobalLedBuffer = false;

        BusConfig bus1 = BusConfig(TYPE_WS2812_RGB, pins1, start1, length1, colorOrder, reversed, skipFirst, AWmode, freqkHz, useGlobalLedBuffer);
        BusConfig bus2 = BusConfig(TYPE_WS2812_RGB, pins2, start2, length2, colorOrder, reversed, skipFirst, AWmode, freqkHz, useGlobalLedBuffer);

        busses.removeAll();
        busses.add(bus1);
        busses.add(bus2);
        busses.show();

        strip.setRange(0, 50, 0x00FF00);

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

        // Get the main segment
        Segment &seg = strip.getMainSegment();

        // Get the current effect
        uint8_t currentEffect = seg.mode;

        char effectName[17];
        extractModeName(currentEffect, JSON_mode_names, effectName, 16);

        // Get the current colors
        uint32_t primaryColor = seg.colors[0];
        uint32_t secondaryColor = seg.colors[1];
        uint32_t tertiaryColor = seg.colors[2];

        StaticJsonDocument<300> j;
        JsonObject preset = j.createNestedObject();
        preset["on"] = true;
        preset["bri"] = 127;
        preset["transition"] = 7;
        preset["mainseg"] = 0;
        JsonArray presetSeg = preset.createNestedArray("seg");

        for (uint8_t i = 0; i < 8; i++)
        {
            uint16_t startLED = i * 6;
            uint16_t stopLED = startLED + 6;

            JsonObject presetSeg0 = presetSeg.createNestedObject();

            presetSeg0["id"] = i;
            presetSeg0["start"] = startLED;
            presetSeg0["stop"] = stopLED;
            presetSeg0["grp"] = 1;
            presetSeg0["spc"] = 0;
            presetSeg0["of"] = 0;
            presetSeg0["on"] = true;
            presetSeg0["frz"] = false;
            presetSeg0["bri"] = 10;
            presetSeg0["cct"] = 127;
            presetSeg0["set"] = 0;
            presetSeg0["n"] = "";

            JsonArray col0 = presetSeg0.createNestedArray("col");
            JsonArray col00 = col0.createNestedArray();
            col00.add(0);
            col00.add(0);
            col00.add(100);

            presetSeg0["fx"] = 0;
            presetSeg0["sx"] = 128;
            presetSeg0["ix"] = 128;
            presetSeg0["pal"] = 0;
            presetSeg0["c1"] = 128;
            presetSeg0["c2"] = 128;
            presetSeg0["c3"] = 16;
            presetSeg0["sel"] = true;
            presetSeg0["rev"] = i % 2 != 0;
            presetSeg0["mi"] = false;
            presetSeg0["o1"] = false;
            presetSeg0["o2"] = false;
            presetSeg0["o3"] = false;
            presetSeg0["si"] = 0;
            presetSeg0["m12"] = 0;
        }

        JsonObject presetSeg0 = presetSeg.createNestedObject();

        presetSeg0["id"] = 8;
        presetSeg0["start"] = 48;
        presetSeg0["stop"] = 50;
        presetSeg0["grp"] = 1;
        presetSeg0["spc"] = 0;
        presetSeg0["of"] = 0;
        presetSeg0["on"] = true;
        presetSeg0["frz"] = false;
        presetSeg0["bri"] = 10;
        presetSeg0["cct"] = 127;
        presetSeg0["set"] = 0;
        presetSeg0["n"] = "";

        JsonArray col0 = presetSeg0.createNestedArray("col");
        JsonArray col00 = col0.createNestedArray();
        col00.add(0);
        col00.add(0);
        col00.add(100);

        presetSeg0["fx"] = 0;
        presetSeg0["sx"] = 128;
        presetSeg0["ix"] = 128;
        presetSeg0["pal"] = 0;
        presetSeg0["c1"] = 128;
        presetSeg0["c2"] = 128;
        presetSeg0["c3"] = 16;
        presetSeg0["sel"] = true;
        presetSeg0["rev"] = false;
        presetSeg0["mi"] = false;
        presetSeg0["o1"] = false;
        presetSeg0["o2"] = false;
        presetSeg0["o3"] = false;
        presetSeg0["si"] = 0;
        presetSeg0["m12"] = 0;

        savePreset(1, "SL Weihnachtsbaum 2024", preset);

        if (currentEffect == 0 && primaryColor == 16755200)
        {
            applyPreset(1, CALL_MODE_DIRECT_CHANGE);
        }

        applyPreset(1);
        colorUpdated(CALL_MODE_FX_CHANGED);
    }

    void loop()
    {
        return;
        if (strip.isUpdating())
            return;

        /*
        if (!needsToRun)
        {
            return;
        }
        */

        // Get the main segment
        Segment &seg = strip.getMainSegment();

        // Get the current effect
        uint8_t currentEffect = seg.mode;

        char effectName[17];
        extractModeName(currentEffect, JSON_mode_names, effectName, 16);

        // Get the current colors
        uint32_t primaryColor = seg.colors[0];
        uint32_t secondaryColor = seg.colors[1];
        uint32_t tertiaryColor = seg.colors[2];

        /*
        if (currentEffect == 0)
        {
            DEBUG_PRINTLN("CURRENT EFFECT IS 0");
        }
        DEBUG_PRINTLN(primaryColor);
        if (primaryColor == 16755200)
        {
            DEBUG_PRINTLN("PRIMARY COLOR IS FFAA00");
        }
        */

        if (currentEffect == 0 && primaryColor == 16755200)
        {

            strip.getSegment(0).setOption(2, true);
            applyPreset(1);
            colorUpdated(CALL_MODE_FX_CHANGED);

            /*
            applyPreset(1, CALL_MODE_FX_CHANGED);

            // Output the values for debugging
            DEBUG_PRINT(F("Current Effect Index: "));
            DEBUG_PRINTLN(currentEffect);

            DEBUG_PRINT(F("Current Effect Name: "));
            DEBUG_PRINTLN(effectName);

            DEBUG_PRINT(F("Primary Color: "));
            DEBUG_PRINTLN(colorToHexString(primaryColor));
            DEBUG_PRINT(F("Secondary Color: "));
            DEBUG_PRINTLN(colorToHexString(secondaryColor));
            DEBUG_PRINT(F("Tertiary Color: "));
            DEBUG_PRINTLN(colorToHexString(tertiaryColor));
            */

            /*
            for (uint8_t i = 0; i < 8; i++)
            {
                Segment &seg1 = strip.getSegment(i);

                // Set the colors
                seg1.setColor(0, 0x00FF00);
                seg1.setColor(1, 0x0000FF);
                seg1.setColor(2, 0xFF00FF);

                // Set the effect
                seg1.setMode(1);
            }

            colorUpdated(CALL_MODE_FX_CHANGED);
            strip.trigger(); // force strip refresh
            */
        }
        /*
        else
        {
            needsToRun = false;
        }
        */
    }

    /*
     * Writes the configuration to internal flash memory.
     */
    void addToConfig(JsonObject &root)
    {
        JsonObject config = root["SL_Weihnachtsbaum_2024"];
        if (config.isNull())
        {
            config = root.createNestedObject("SL_Weihnachtsbaum_2024");
        }
        config["needsToRun"] = needsToRun;

        DEBUG_PRINTLN(F("Sternenlabor Weihnachtsbaum 2024 config saved."));
    }

    /*
     * Reads the configuration to internal flash memory before setup() is called.
     *
     * The function should return true if configuration was successfully loaded or false if there was no configuration.
     */
    bool readFromConfig(JsonObject &root)
    {
        JsonObject config = root["SL_Weihnachtsbaum_2024"];
        if (config.isNull())
        {
            DEBUG_PRINT(F("SL_Weihnachtsbaum_2024: No config found. (Using defaults.)"));
            return false;
        }

        return getJsonValue(config, needsToRun, true);
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