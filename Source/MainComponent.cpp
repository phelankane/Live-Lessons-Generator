/*
 ==============================================================================
 
    MainComponent.h
    Created: 11 Nov 2020 9:19:53pm
    Author:  Phelan Kane 15inch
 
    This class creates the main component
 
    (c) Meta Function 2020
 
 ==============================================================================
 */

#include "MainComponent.h"

#if JUCE_WINDOWS
    static const juce::String directorySeperator = "\\";
#elif JUCE_MAC
    static const juce::String directorySeperator = "/";
#endif

//==============================================================================
MainComponent::MainComponent()
    :   mPageTab(juce::TabbedButtonBar::Orientation::TabsAtTop)
// mPageTab needed above otherwise the header declares TabbedButtonBar tabs (without orientation!!!)
{
    setSize (MAIN_COMPONENT_WIDTH, MAIN_COMPONENT_HEIGHT);
    
    juce::LookAndFeel::setDefaultLookAndFeel (&mMetaFeel);
    
    addAndMakeVisible (&mPageTab);
    mPageTab.setOrientation(juce::TabbedButtonBar::TabsAtTop);
    mPageTab.setTabBarDepth (30);
    mPageTab.setOutline(0);
    mPageTab.setIndent(0);
    mPageTab.setTabBackgroundColour(0, Colour_3);
    
    mPages.add( new CPageEditor() );
    mPageTab.addTab("Page 1", Colour_3, mPages[0],false );
    mPageTab.setCurrentTabIndex (0);
    
#if JUCE_MAC
    // Add the native menu bar on the Mac OS X platform.
    // Pass our class (which is a menu bar model) to the setMacMainMenu() function.
    MenuBarModel::setMacMainMenu(this);
#else
    // Use an in-window menu bar on other platforms.
    // Pass our class (which is a menu bar model) to the menu bar component.
    mMenuBar = new MenuBarComponent(this);
    
    // Add the menu bar component to this parent component.
    addAndMakeVisible (mMenuBar);
#endif
}

MainComponent::~MainComponent()
{
#if JUCE_MAC
    // We must unset the the native Mac OS X menu bar as this class is destroyed
    //  since it contains the MenuBarModel that is in use.
    MenuBarModel::setMacMainMenu(nullptr);
#endif
    
    mSaveFileChooser = nullptr;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colour_3);
    
    juce::Rectangle<int> titleArea1 (200, 5, 207, 5);
//    juce::Rectangle<int> titleArea1 (JUCE_LIVE_CONSTANT (200),
//                                    JUCE_LIVE_CONSTANT (5),
//                                    JUCE_LIVE_CONSTANT (207),
//                                    JUCE_LIVE_CONSTANT (5));
    
    g.setFont (juce::Font ("Futura", "Medium", 22.f));
    g.setColour(Colour_1);
    g.drawText("Live Lesson Generator", titleArea1, juce::Justification::centredTop);
    
    juce::Rectangle<int> titleArea2 (50, 30, 505, 5);
//    juce::Rectangle<int> titleArea2 (JUCE_LIVE_CONSTANT (50),
//                                     JUCE_LIVE_CONSTANT (30),
//                                     JUCE_LIVE_CONSTANT (505),
//                                     JUCE_LIVE_CONSTANT (5));
    g.setFont (Font_3);
    g.drawText(" (c) 2021 Meta Function", titleArea2, juce::Justification::centredTop);

    g.drawImageAt (mMetaLogoWhite, 540, 10);
    
//    g.drawImageAt (metaLogoWhite,
//                   JUCE_LIVE_CONSTANT (540),
//                   JUCE_LIVE_CONSTANT (10));
}

void MainComponent::resized()
{
    mPageTab.setBounds (7, 45, TAB_WIDTH, TAB_HEIGHT);
    
//    mPageTab.setBounds(JUCE_LIVE_CONSTANT (7),
//                   JUCE_LIVE_CONSTANT (45),
//                   JUCE_LIVE_CONSTANT (TAB_WIDTH),
//                   JUCE_LIVE_CONSTANT (TAB_HEIGHT));
    
    // Position the menu bar component if we have one
    if (mMenuBar != nullptr)
        mMenuBar->setBounds (0, 0, getWidth(), 20);
}

juce::StringArray MainComponent::getMenuBarNames()
{
    // Return a string array of the top-level menu bar names.
    // Create a null-terminated array of C strings first.
    const char* menuNames[] = {"Edit", 0}; //"Number Of Pages", 0 };
    
    // Pass this to the string array which converts it.
    return juce::StringArray (menuNames);
}

juce::PopupMenu MainComponent::getMenuForIndex (int index, const juce::String& name)
{
    juce::PopupMenu menu;
    
    if (name == "Edit")
    {
        menu.addItem (AddPage, "Add Page");
        menu.addItem (DeleteSelectedPage, "Delete Selected Page");
        menu.addItem (Bold, "Set Text Selection To Bold");
        menu.addItem (Bullet, "Add Bullet Point To Text Selection");
        menu.addItem (Divider, "Add Divider Image At Selection");
        menu.addItem (Image, "Add Image File At Selection");
        menu.addItem (Comment, "Add Comment Before Selected Text");
        menu.addItem (Hyperlink, "Add Hyperlink To Selected Text");
        menu.addItem (PageLink, "Add Page Link To Selected Text");
        menu.addItem (ExportLesson, "Export Lesson As LessonsEN.txt File");
        menu.addItem (AboutHelp, "About / Help");
    }
//    else if (name == "Number Of Pages")
//    {
//        menu.addItem (OnePage, "1", true, true);
//        menu.addItem (TwoPages, "2", true, false);
//        menu.addItem (ThreePages, "3", true, false);
//        menu.addItem (ThreePages, "4", true, false);
//    }
    return menu;
}

void MainComponent::menuItemSelected (int menuID, int index)
{
    auto numPages = mPageTab.getNumTabs();
    auto selectedPage = mPageTab.getCurrentTabIndex();

    switch (menuID)
    {
        case AddPage:
            if (numPages <= 7)
            {
                mPages.add(new CPageEditor());
                mPageTab.addTab("Page " + juce::String(numPages + 1), Colour_3, mPages[numPages],false );
            }
            break;
            
        case DeleteSelectedPage:
            if (selectedPage)
            {
                mPageTab.setCurrentTabIndex(selectedPage - 1);
                mPageTab.removeTab(selectedPage);
            }
            break;
            
        case Bold:
            mPages[selectedPage]->boldSelectedText();
            break;
            
        case Bullet:
            mPages[selectedPage]->addBulletSelectedText();
            break;
            
        case Divider:
            mPages[selectedPage]->addDividerImage();
            break;
            
        case Image:
            mPages[selectedPage]->addImage();
            break;
            
        case Comment:
            mPages[selectedPage]->addComment();
            break;
            
        case Hyperlink:
            mPages[selectedPage]->addHyperlink();
            break;
            
        case PageLink:
            mPages[selectedPage]->addPageLink();
            break;
            
        case ExportLesson:
            exportLesson();
            break;
            
        case AboutHelp:
            openAboutHelp();
            break;
    }
}

void MainComponent::openAboutHelp()
{
    juce::URL("https://www.metafunction.co.uk/post/live-lessons-generator").launchInDefaultBrowser( );
}

void MainComponent::exportLesson()
{
//    mSaveFileChooser.reset (new juce::FileChooser ("Choose a directory...",
//                                     juce::File::getCurrentWorkingDirectory(),
//                               "*", true));

//    mSaveFileChooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
//                                   [&] (const juce::FileChooser& chooser)
//                     {
//                         auto result = chooser.getURLResult();
//                         mExportFullPath = result.isLocalFile() ? result.getLocalFile().getFullPathName()
//                         : result.toString (true);
//                     });
    
//    mSaveFileChooser->launchAsync (juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectDirectories,
//                                   [&] (const juce::FileChooser& chooser)
//                                   {
//                                       auto result = chooser.getURLResult();
//                                       mExportFullPath = result.isLocalFile() ? result.getLocalFile().getFullPathName()
//                                       : result.toString (true);
//                                   });
    
    // Set output path to Desktop
    mExportFullPath = (juce::File::getSpecialLocation(juce::File::userDesktopDirectory)).getFullPathName();
    
    juce:: String name = "LessonsEN.txt";
    juce::String directory = (mExportFullPath + directorySeperator + name);
    
    // Call the function to write to the file.
    writeFile (directory);
    
}

// A function to write some text to a file
void MainComponent::writeFile(juce::File const& file)
{
    juce::Logger *log = juce::Logger::getCurrentLogger();
    
    // Create the output stream from the file
    juce::FileOutputStream stream (file);
    
    // Check that the stream opened successfully
    if (!stream.openedOk()) {
        log->writeToLog ("failed to open stream");
        return;
    }
    
    // Set the stream position to the start of the file
    stream.setPosition (0);
    
    // Discard any content after the current position
    stream.truncate();
    
    // A function to concatenate strings
    outputPageString(-1);
    
    // Write the string to the stream
    bool asUTF16 = false;
    bool byteOrderMark = false;
    stream.writeText (mMainOutputText, asUTF16, byteOrderMark, nullptr);
}

// A function to concatenate strings for all pages
void MainComponent::outputPageString( int index)
{
    /* -1 for all pages */ 
    for (int i = 0; i < mPages.size(); i++)
    {
        if (index == -1 || index == i)
        {
            juce::String pageOutputText;
            const auto *p_page = mPages[i];
            
            pageOutputText += ("$Page " + p_page->mPageNameTextEditor.getText() + "\n");
            pageOutputText += ("$TargetName " + p_page->mTargetNameTextEditor.getText() + "\n" + "\n");
            pageOutputText += p_page->mLessonTextEditor.getText() + "\n" + "\n";
            mMainOutputText += pageOutputText;
        }
    }
}
