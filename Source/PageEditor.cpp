/*
  ==============================================================================

    CPageEditor.cpp
    Created: 11 Nov 2020 9:19:53pm
    Author:  Phelan Kane 15inch
 
    This class creates a basic page editor component
 
    (c) Meta Function 2020

  ==============================================================================
*/

#include "PageEditor.h"

CPageEditor::CPageEditor()
{
    addAndMakeVisible (mPageNameTextEditor);
    mPageNameTextEditor.setFont(Font_3);
    mPageNameTextEditor.setText ("Enter your page name here...");

    addAndMakeVisible (mPageNameLabel);
    mPageNameLabel.setText("Page Name", juce::dontSendNotification);
    mPageNameLabel.setJustificationType (juce::Justification::centredLeft);
    mPageNameLabel.attachToComponent (&mPageNameTextEditor, false);

    addAndMakeVisible (mTargetNameTextEditor);
    mTargetNameTextEditor.setFont(Font_3);
    mTargetNameTextEditor.setText ("Enter your target name here...");

    addAndMakeVisible (mTargetNameLabel);
    mTargetNameLabel.setText("Target Name", juce::dontSendNotification);
    mTargetNameLabel.setJustificationType (juce::Justification::centredLeft);
    mTargetNameLabel.attachToComponent (&mTargetNameTextEditor, false);

    addAndMakeVisible (mLessonTextEditor);
    mLessonTextEditor.setFont(Font_3);
    mLessonTextEditor.setText ("Enter your chapter info here...");
    mLessonTextEditor.setMultiLine(true, true);
    mLessonTextEditor.setReturnKeyStartsNewLine(true);
    mLessonTextEditor.setScrollbarsShown(true);
    
    addAndMakeVisible (mLessonLabel);
    mLessonLabel.setText("Lesson Info", juce::dontSendNotification);
    mLessonLabel.setJustificationType (juce::Justification::centredLeft);
    mLessonLabel.attachToComponent (&mLessonTextEditor, false);
    
}

CPageEditor::~CPageEditor()
{
    mImageFileChooser = nullptr;
}

void CPageEditor::paint (juce::Graphics& g)
{
    g.fillAll (Colour_3);

}

void CPageEditor::resized()
{
    mPageNameTextEditor.setBounds (10, 30, 570, 30);

//    mPageNameTextEditor.setBounds(JUCE_LIVE_CONSTANT (10),
//                   JUCE_LIVE_CONSTANT (30),
//                   JUCE_LIVE_CONSTANT (570),
//                   JUCE_LIVE_CONSTANT (30));

    mTargetNameTextEditor.setBounds (10, 90, 570, 30);

//    mTargetNameTextEditor.setBounds(JUCE_LIVE_CONSTANT (10),
//                   JUCE_LIVE_CONSTANT (90),
//                   JUCE_LIVE_CONSTANT (570),
//                   JUCE_LIVE_CONSTANT (30));

   mLessonTextEditor.setBounds (10, 150, 570, 450);

//    mLessonTextEditor.setBounds(JUCE_LIVE_CONSTANT (10),
//                   JUCE_LIVE_CONSTANT (150),
//                   JUCE_LIVE_CONSTANT (570),
//                   JUCE_LIVE_CONSTANT (450));
}

void CPageEditor::boldSelectedText()
{
    mLessonString = mLessonTextEditor.getHighlightedText();
    juce::String val = "*";
    val += mLessonString;
    mLessonTextEditor.insertTextAtCaret(val += "*");
}

void CPageEditor::addBulletSelectedText()
{
    mLessonString = mLessonTextEditor.getHighlightedText();
    juce::String val = "-> ";
    val += mLessonString;
    mLessonTextEditor.insertTextAtCaret(val);
}

void CPageEditor::addDividerImage()
{
    mLessonString = mLessonTextEditor.getHighlightedText();
    juce::String val = "Divider.tif";
    mLessonTextEditor.insertTextAtCaret(val);
}

void CPageEditor::addImage()
{
    mImageFileChooser.reset (new juce::FileChooser ("Choose an image to open...", juce::File::getCurrentWorkingDirectory(),
                                     "*.jpg;*.jpeg;*.png;*.gif", true));

    // Cast all lambda vars by ref
    mImageFileChooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                     [&] (const juce::FileChooser& chooser)
                     {
                         auto results = chooser.getURLResults();

                         for (auto result : results)
                         {
                             mImageFileName << (result.isLocalFile() ? result.getLocalFile().getFileName()
                                               : result.toString (false)) << "\n";

                             mImageFullPath << (result.isLocalFile() ? result.getLocalFile().getFullPathName()
                                               : result.toString (false)) << "\n";

                             // Populate highlighted text
                             mLessonString = mLessonTextEditor.getHighlightedText();
                             mLessonTextEditor.insertTextAtCaret(mImageFileName);
                         }
                     });
}

void CPageEditor::addComment()
{
    mLessonString = mLessonTextEditor.getHighlightedText();
    juce::String val = "$Comment ";
    val += mLessonString;
    mLessonTextEditor.insertTextAtCaret(val);
}

void CPageEditor::addHyperlink()
{
    mLessonString = mLessonTextEditor.getHighlightedText();
    juce::String val = "$Link ";
    juce::String hyperlink;
    juce::String whiteSpace = " ";
    juce::String leftBracket = "<";
    juce::String rightBracket = ">";
    
    juce::AlertWindow window ("Add Hyperlink To Selected Text", "Please enter the full URL for your hyperlink", juce::AlertWindow::NoIcon);
    
    window.centreAroundComponent(this, getWidth(), getHeight());
    window.addTextEditor("hyperlink", "", "Hyperlink:");
    window.addButton("Confirm", 1);
    window.addButton("Cancel", 0);
    
    if(window.runModalLoop())
    {
         hyperlink = window.getTextEditor("hyperlink")->getText();
    }
    
    mLessonString += whiteSpace;
    mLessonString += leftBracket;
    mLessonString += hyperlink;
    mLessonString += rightBracket;
    val += mLessonString;
    
    mHyperLink = val;
    
    mLessonTextEditor.insertTextAtCaret(mHyperLink);
}

void CPageEditor::addPageLink()
{
    mLessonString = mLessonTextEditor.getHighlightedText();
    juce::String val = "$Link ";
    juce::String pageLink;
    juce::String whiteSpace = " ";
    juce::String leftBracket = "<GoToPage:";
    juce::String rightBracket = ">";
    
    juce::AlertWindow window ("Add Page Link To Selected Text", "Please enter the Target Name for your Page Link", juce::AlertWindow::NoIcon);
    
    window.centreAroundComponent(this, getWidth(), getHeight());
    window.addTextEditor("pageLink", "", "Page Link:");
    window.addButton("Confirm", 1);
    window.addButton("Cancel", 0);
    
    if(window.runModalLoop())
    {
        pageLink = window.getTextEditor("pageLink")->getText();
    }
    
    mLessonString += whiteSpace;
    mLessonString += leftBracket;
    mLessonString += pageLink;
    mLessonString += rightBracket;
    val += mLessonString;
    
    mPageLink = val;
    
    mLessonTextEditor.insertTextAtCaret(mPageLink);
}
