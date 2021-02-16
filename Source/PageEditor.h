/*
  ==============================================================================

    CPageEditor.h
    Created: 11 Nov 2020 9:19:53pm
    Author:  Phelan Kane 15inch
 
    This class creates a basic page editor component
 
    (c) Meta Function 2020

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "InterfaceDefines.h"

class CPageEditor :  public juce::Component
{
public:
    CPageEditor();
    ~CPageEditor();
    
    // Methods are pure virtual, so required.
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void boldSelectedText();
    void addBulletSelectedText();
    void addDividerImage();
    void addImage();
    void addComment();
    void addHyperlink();
    void addPageLink();
    
    juce::TextEditor mPageNameTextEditor;
    juce::TextEditor mTargetNameTextEditor;
    juce::TextEditor mLessonTextEditor;
    
private:
    
    juce::Label mPageNameLabel;
    juce::Label mTargetNameLabel;
    juce::Label mLessonLabel;
    
    juce::String mLessonString;
    juce::String mImageFileName;
    juce::String mImageFullPath;
    juce::String mHyperLink;
    juce::String mPageLink;
    
    juce::ImagePreviewComponent mImagePreview;
    std::unique_ptr<juce::FileChooser> mImageFileChooser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CPageEditor)
};
