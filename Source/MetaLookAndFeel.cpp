/*
  ==============================================================================

    MetaLookAndFeel.cpp
    Created: 22 Aug 2019 6:48:01pm
    Author:  Phelan Kane
 
    This class provides a custom lookAndFeel
     
    (c) Meta Function 2020
 
  ==============================================================================
*/

#include "MetaLookAndFeel.h"

CMetaLookAndFeel::CMetaLookAndFeel(void)
{    
    // Text Editor Colours
    setColour(juce::TextEditor::backgroundColourId, Colour_3);
    setColour(juce::TextEditor::textColourId, Colour_1);
    setColour(juce::TextEditor::outlineColourId, Colour_2);
    setColour(juce::TextEditor::focusedOutlineColourId, Colour_1);

    // Label Colours
    setColour(juce::Label::backgroundColourId, Colour_3);
    setColour(juce::Label::textColourId, Colour_1);
    
    // Alert Window Colours
    setColour(juce::AlertWindow::backgroundColourId, Colour_3);
    setColour(juce::AlertWindow::textColourId, Colour_1);
    setColour(juce::AlertWindow::outlineColourId, Colour_2);
    
    // Button Text Colours
    setColour(juce::TextButton::buttonColourId, Colour_3);
    setColour(juce::TextButton::buttonOnColourId, Colour_3);
    setColour(juce::TextButton::textColourOffId, Colour_1);
    setColour(juce::TextButton::textColourOnId, Colour_1);
}

CMetaLookAndFeel::~CMetaLookAndFeel(void)
{
    
}


// Override Tabbed Componet Button Text
void CMetaLookAndFeel::drawTabButtonText (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown)
{
    auto area = button.getTextArea().toFloat();
    
    auto length = area.getWidth();
    auto depth  = area.getHeight();
    
    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);
    
    // Replace Font
    juce::Font font (Font_4);
//        Font font (getTabButtonFont (button, depth));
    
    font.setUnderline (button.hasKeyboardFocus (false));
    
    juce::AffineTransform t;
    
    switch (button.getTabbedButtonBar().getOrientation())
    {
        case juce::TabbedButtonBar::TabsAtLeft:   t = t.rotated (juce::MathConstants<float>::pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case juce::TabbedButtonBar::TabsAtRight:  t = t.rotated (juce::MathConstants<float>::pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case juce::TabbedButtonBar::TabsAtTop:
        case juce::TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }
    
    juce::Colour col;
    
    // Override colour of selected tab
    //
    if (button.isFrontTab())
    {
        // Override colours & set font to bold
        col = Colour_1;
        font = Font_6;
    }
    //    if (button.isFrontTab() && (button.isColourSpecified (TabbedButtonBar::frontTextColourId)
    //                                || isColourSpecified (TabbedButtonBar::frontTextColourId)))
    //        col = findColour (TabbedButtonBar::frontTextColourId);
    
    else if (button.isColourSpecified (juce::TabbedButtonBar::tabTextColourId)
             || isColourSpecified (juce::TabbedButtonBar::tabTextColourId))
        col = findColour (juce::TabbedButtonBar::tabTextColourId);
    else
        col = button.getTabBackgroundColour().contrasting();
    
    auto alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
    
    g.setColour (col.withMultipliedAlpha (alpha));
    g.setFont (font);
    g.addTransform (t);
    
    g.drawFittedText (button.getButtonText().trim(),
                      0, 0, (int) length, (int) depth,
                      juce::Justification::centred,
                      fmax (1, ((int) depth) / 12));
}

// Override Tabbed Componet Tab Shape & Drop Shadow
void CMetaLookAndFeel::drawTabButton (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown)
{
    // Remove shape & drop shadow
    //
    
//    Path tabShape;
//    createTabButtonShape (button, tabShape, isMouseOver, isMouseDown);
    
//    auto activeArea = button.getActiveArea();
//    tabShape.applyTransform (AffineTransform::translation ((float) activeArea.getX(),
//                                                           (float) activeArea.getY()));
//    DropShadow (Colours::black.withAlpha (0.5f), 2, Point<int> (0, 1)).drawForPath (g, tabShape);

//    fillTabButtonShape (button, g, tabShape, isMouseOver, isMouseDown);
    
    // Just draw text
    drawTabButtonText (button, g, isMouseOver, isMouseDown);
}

// Override Tabbed Componet Tab Area Behind Button i.e. line
void CMetaLookAndFeel::drawTabAreaBehindFrontButton (juce::TabbedButtonBar& bar, juce::Graphics& g, const int w, const int h)
{
    // No area behind button required so removed
    //
    
//    auto shadowSize = 0.2f;
//    
//    Rectangle<int> shadowRect, line;
//    ColourGradient gradient (Colours::black.withAlpha (bar.isEnabled() ? 0.25f : 0.15f), 0, 0,
//                             Colours::transparentBlack, 0, 0, false);
//    
//    switch (bar.getOrientation())
//    {
//        case TabbedButtonBar::TabsAtLeft:
//            gradient.point1.x = (float) w;
//            gradient.point2.x = w * (1.0f - shadowSize);
//            shadowRect.setBounds ((int) gradient.point2.x, 0, w - (int) gradient.point2.x, h);
//            line.setBounds (w - 1, 0, 1, h);
//            break;
//            
//        case TabbedButtonBar::TabsAtRight:
//            gradient.point2.x = w * shadowSize;
//            shadowRect.setBounds (0, 0, (int) gradient.point2.x, h);
//            line.setBounds (0, 0, 1, h);
//            break;
//            
//        case TabbedButtonBar::TabsAtTop:
//            gradient.point1.y = (float) h;
//            gradient.point2.y = h * (1.0f - shadowSize);
//            shadowRect.setBounds (0, (int) gradient.point2.y, w, h - (int) gradient.point2.y);
//            line.setBounds (0, h - 1, w, 1);
//            break;
//            
//        case TabbedButtonBar::TabsAtBottom:
//            gradient.point2.y = h * shadowSize;
//            shadowRect.setBounds (0, 0, w, (int) gradient.point2.y);
//            line.setBounds (0, 0, w, 1);
//            break;
//            
//        default: break;
//    }
    
    // Remove fills
//        g.setGradientFill (gradient);
//        g.fillRect (shadowRect.expanded (2, 2));
//    
//        g.setColour (Colour (0x80000000));
//        g.fillRect (line);
}

// Override Tabbed Component Overlap
int CMetaLookAndFeel::getTabButtonOverlap (int tabDepth)
{
    // Overlap reduced
    return 1 + tabDepth / 3;
//    return 1 + tabDepth;
}

// Custom function to get Common Font i.e. not overridden
juce::Font CMetaLookAndFeel::getCommonFont()
{
    return juce::Font (Font_1);
}

// Custom function to get Common Bold Font i.e. not overridden
juce::Font CMetaLookAndFeel::getCommonBoldFont()
{
    return juce::Font (Font_2);
}

// Override Label Font
juce::Font CMetaLookAndFeel::getLabelFont (juce::Label& label)
{
    return juce::Font (Font_3);
}

// Override CommboBox PopUpMenu Label Font
juce::Font CMetaLookAndFeel::getPopupMenuFont()
{
    return getCommonFont();
}

// Override AlertWindow Button Height
int CMetaLookAndFeel::getAlertWindowButtonHeight()
{
    return 20;
}

// Override AlertWindow Fonts
juce::Font CMetaLookAndFeel::getAlertWindowTitleFont()
{
    return juce::Font (Font_3);
}

juce::Font CMetaLookAndFeel::getAlertWindowMessageFont()
{
    return juce::Font (Font_2);
}

juce::Font CMetaLookAndFeel::getAlertWindowFont()
{
    return juce::Font (Font_1);
}
