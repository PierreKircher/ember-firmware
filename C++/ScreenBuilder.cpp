/* 
 * File:   ScreenBuilder.cpp
 * Author: Richard Greene
 * 
 * Builds the screens shown on the front panel.
 * 
 * Created on July 23, 2014, 12:15 PM
 */

#include <ScreenBuilder.h>
#include <PrinterStatus.h>
#include <ScreenLayouts.h>

#define UNDEFINED_SCREEN_LINE1  Center, 64, 10, 1, 0xFFFF, "Screen?"
#define UNDEFINED_SCREEN_LINE2  Center, 64, 30, 1, 0xFFFF, "%s"

/// Create a key into the Screen map for the given print engine state 
/// and UI substate 
ScreenKey ScreenBuilder::GetKey(PrintEngineState state, UISubState subState)
{
    // This implementation assumes we never have more than 256 print
    // engine states or UI substates
    return state | (subState << 8);
}

/// Build the screens and add them to a map keyed by PrintEngine states and UI
/// sub states.
void ScreenBuilder::BuildScreens(std::map<int, Screen*>& screenMap) 
{
    ScreenText* unknown = new ScreenText();
    unknown->Add(new ScreenLine(UNDEFINED_SCREEN_LINE1));
    // TODO: add the following when we can replace %s 
    // with the current state & substate
  //  unknown->Add(ScreenLine(UNDEFINED_SCREEN_LINE2));
    screenMap[UNKNOWN_SCREEN_KEY] =  new Screen(unknown, 0);
    
    // NULL screens for states that shouldn't change what's already displayed
    screenMap[GetKey(PrinterOnState, NoUISubState)] = NULL; 
    screenMap[GetKey(DoorClosedState, NoUISubState)] = NULL;  
    screenMap[GetKey(InitializingState, NoUISubState)] = NULL;
    screenMap[GetKey(HomingState, NoUISubState)] = NULL;
    screenMap[GetKey(PrintSetupState, NoUISubState)] = NULL; 
    screenMap[GetKey(PrintingState, NoUISubState)] = NULL;
    screenMap[GetKey(SeparatingState, NoUISubState)] = NULL; 
    
    ScreenText* readyLoaded = new ScreenText;
    readyLoaded->Add(new ScreenLine(READY_LOADED_LINE1));
    readyLoaded->Add(new ScreenLine(READY_LOADED_LINE2));
    readyLoaded->Add(new ScreenLine(READY_LOADED_LINE3));
    readyLoaded->Add(new ScreenLine(READY_LOADED_LINE4));
    readyLoaded->Add(new ScreenLine(READY_LOADED_BTN1_LINE1));
    readyLoaded->Add(new ScreenLine(READY_LOADED_BTN1_LINE2));
    readyLoaded->Add(new ScreenLine(READY_LOADED_BTN2_LINE1));
    readyLoaded->Add(new ScreenLine(READY_LOADED_BTN2_LINE2));
    screenMap[GetKey(HomeState, Downloaded)] = 
                                new Screen(readyLoaded, READY_LOADED_LED_SEQ);
    
    ScreenText* startLoaded = new ScreenText;
    startLoaded->Add(new ReplaceableLine(START_LOADED_LINE1)); 
    startLoaded->Add(new ScreenLine(START_LOADED_LINE2));
    startLoaded->Add(new ScreenLine(START_LOADED_LINE3));
    startLoaded->Add(new ScreenLine(START_LOADED_LINE4));
    startLoaded->Add(new ScreenLine(START_LOADED_LINE5));
    startLoaded->Add(new ScreenLine(START_LOADED_BTN1_LINE2));
    startLoaded->Add(new ScreenLine(START_LOADED_BTN2_LINE2));
    screenMap[GetKey(HomeState, NoUISubState)] = 
                        new JobNameScreen(startLoaded, START_LOADED_LED_SEQ);
    
    ScreenText* loadFail = new ScreenText;
    loadFail->Add(new ScreenLine(LOAD_FAIL_LINE1));
    loadFail->Add(new ScreenLine(LOAD_FAIL_LINE2));
    loadFail->Add(new ScreenLine(LOAD_FAIL_BTN1_LINE2));
    loadFail->Add(new ScreenLine(LOAD_FAIL_BTN2_LINE2));
    screenMap[GetKey(HomeState, DownloadFailed)] = 
                                new Screen(loadFail, LOAD_FAIL_LED_SEQ);
    
    ScreenText* printing = new ScreenText;
    printing->Add(new ScreenLine(PRINTING_LINE1));
    printing->Add(new ReplaceableLine(PRINTING_LINE2));
    printing->Add(new ScreenLine(PRINTING_LINE3));
    printing->Add(new ScreenLine(PRINTING_BTN1_LINE2));
    printing->Add(new ScreenLine(PRINTING_BTN2_LINE2));
    screenMap[GetKey(ExposingState, NoUISubState)] = new Screen(printing, PRINTING_LED_SEQ);  
    
    ScreenText* paused = new ScreenText;
    paused->Add(new ScreenLine(PAUSED_LINE1));
    paused->Add(new ScreenLine(PAUSED_LINE2));
    paused->Add(new ScreenLine(PAUSED_BTN1_LINE2));
    paused->Add(new ScreenLine(PAUSED_BTN2_LINE1));
    paused->Add(new ScreenLine(PAUSED_BTN2_LINE2));
    screenMap[GetKey(PausedState, NoUISubState)] = new Screen(paused, PAUSED_LED_SEQ);
   
    ScreenText* cancelPrompt = new ScreenText;
    cancelPrompt->Add(new ScreenLine(CANCELPROMPT_LINE1));
    cancelPrompt->Add(new ScreenLine(CANCELPROMPT_LINE2));
    cancelPrompt->Add(new ScreenLine(CANCELPROMPT_BTN1_LINE2));
    cancelPrompt->Add(new ScreenLine(CANCELPROMPT_BTN2_LINE2));
    screenMap[GetKey(ConfirmCancelState, NoUISubState)] = 
                            new Screen(cancelPrompt, CANCELPROMPT_LED_SEQ);

    ScreenText* printComplete = new ScreenText;
    printComplete->Add(new ScreenLine(PRINT_COMPLETE_LINE1));
    printComplete->Add(new ScreenLine(PRINT_COMPLETE_LINE2));
    printComplete->Add(new ScreenLine(PRINT_COMPLETE_LINE3));
    screenMap[GetKey(EndingPrintState, NoUISubState)] = new Screen(printComplete, PRINT_COMPLETE_LED_SEQ);    
    
    ScreenText* startingPrint = new ScreenText;
    startingPrint->Add(new ScreenLine(STARTING_PRINT_LINE1));
    startingPrint->Add(new ScreenLine(STARTING_PRINT_BTN2_LINE2));
    screenMap[GetKey(MovingToStartPositionState, NoUISubState)] = new Screen(startingPrint, STARTING_PRINT_LED_SEQ);        
}
