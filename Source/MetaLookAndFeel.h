/*
  ==============================================================================

    MetaLookAndFeel.h
    Created: 22 Aug 2019 6:48:01pm
    Author:  Phelan Kane
 
    This class provides a custom lookAndFeel
     
    (c) Meta Function 2020

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "InterfaceDefines.h"

class CMetaLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CMetaLookAndFeel();
    ~CMetaLookAndFeel();
    
    juce::Colour outline;
    juce::Colour fill;
    juce::Colour tick;
    juce::Colour thumbColour;
    
    // Override Tabbed Component Text
    void drawTabButtonText (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown) override;
    
    // Override Tabbed Componet Tab Drop Shadow
    void drawTabButton (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown) override;
    
    // Override Tabbed Componet Tab Area Behind Button i.e. line
    void drawTabAreaBehindFrontButton (juce::TabbedButtonBar&, juce::Graphics&, int w, int h) override;
    
    // Override Tabbed Component Overlap
    int getTabButtonOverlap (int tabDepth) override;
    
    // Custom function to get Common Font i.e. not overridden
    juce::Font getCommonFont();
    
    // Custom function to get Common Bold Font i.e. not overridden
    juce::Font getCommonBoldFont();
    
    // Override Label Font
    juce::Font getLabelFont (juce::Label& label) override;
    
    // Override CommboBox PopUpMenu Label Font
    juce::Font getPopupMenuFont() override;
    
    // Override AlertWindow Button Height
    int getAlertWindowButtonHeight() override;
    
    // Override AlertWindow Fonts
    juce::Font getAlertWindowTitleFont() override;
    juce::Font getAlertWindowMessageFont() override;
    juce::Font getAlertWindowFont() override;
};
