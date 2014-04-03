/* 
 * File:   EventHandler.h
 * Author: greener
 *
 * Created on March 31, 2014, 1:48 PM
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

#include <Event.h>
#include <vector>
#include <Hardware.h>

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();                            
    void Subscribe(EventType eventType, CallbackInterface* pObject);
    void Begin();
    
    
private:
    /// array of collections of subscriptions for each event type
    std::vector<Subscription> _subscriptions[MaxEventTypes];
    
    /// file descriptors for receiving each event type
    int _fileDescriptors[MaxEventTypes];
    
    int GetInterruptDescriptor(EventType eventType);
    void SetFileDescriptor(EventType eventType, int fd);
    void UnexportPins();  
    int GetInputPinFor(EventType et);
};


#endif	/* EVENTHANDLER_H */
