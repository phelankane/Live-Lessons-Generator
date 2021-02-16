/*
 ==============================================================================
 
    MainComponent.h
    Created: 11 Nov 2020 9:19:53pm
    Author:  Phelan Kane 15inch
 
    This class creates the main component
 
    (c) Meta Function 2020
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PageEditor.h"
#include "InterfaceDefines.h"
#include "MetaLookAndFeel.h"

//==============================================================================
class MainComponent  :  public juce::Component,
                        public juce::MenuBarModel // Act as a menu bar model
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Menu bar model pure virtual functions.
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex (int index, const juce::String& name) override;
    void menuItemSelected (int menuID, int index) override;
    
    void openAboutHelp();
    void exportLesson();
    void writeFile(juce::File const& file);
    void outputPageString( int index );
    
    void outputAllPageStrings();
    void outputPageOneStrings();
    void outputPageTwoStrings();
    void outputPageThreeStrings();
    void outputPageFourStrings();
    void outputPageFiveStrings();
    void outputPageSixStrings();
    void outputPageSevenStrings();
    void outputPageEightStrings();
    
    // Convenient constant IDs for the menu items.
    enum MenuIDs {
        AddPage = 1000,
        DeleteSelectedPage,
        Bold,
        Bullet,
        Divider,
        Image,
        Comment,
        Hyperlink,
        PageLink,
        ExportLesson,
        AboutHelp
    };

private:
    //==============================================================================
    juce::TabbedComponent mPageTab;
    
    juce::OwnedArray<CPageEditor> mPages;
    
    juce::ScopedPointer<juce::MenuBarComponent> mMenuBar;
    
    juce::String mMainOutputText;
    juce::String mExportFullPath;
    
    // Load Meta Logo White
    juce::Image mMetaLogoWhite = juce::ImageCache::getFromMemory (BinaryData::MetafunctionLogoWhite_png, BinaryData::MetafunctionLogoWhite_pngSize);
    
    std::unique_ptr<juce::FileChooser> mSaveFileChooser;
    
    CMetaLookAndFeel mMetaFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
