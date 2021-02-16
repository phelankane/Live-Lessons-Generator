/*
  ==============================================================================

    InterfaceDefines.h
    Created: 19 Aug 2020 5:40:02pm
    Author:  Phelan Kane
 
    This file provides interface defines
 
    (c) Meta Function 2020

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define MAIN_COMPONENT_WIDTH        600
#define MAIN_COMPONENT_HEIGHT       700

#define TAB_WIDTH                   780
#define TAB_HEIGHT                  630

const juce::Colour Colour_1 = juce::Colours::black;
const juce::Colour Colour_2 = juce::Colours::white;
const juce::Colour Colour_3 (juce::Colour::fromFloatRGBA (0.529412f, 0.529412f, 0.529412f, 1.0f)); // Ableton Mid Light

// Fonts
const juce::Font  Font_1 ("Futura", "Medium", 12.f);
const juce::Font  Font_2 ("Futura", "Bold", 12.f);
const juce::Font  Font_3 ("Futura", "Medium", 14.f);
const juce::Font  Font_4 ("Futura", "Bold", 14.f);
const juce::Font  Font_5 ("Futura", "Medium", 16.f);
const juce::Font  Font_6 ("Futura", "Bold", 16.f);
