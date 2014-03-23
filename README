# fn(x) C++ Wrappers Classes

Provides a set of usable classes that will allow you to create programs that are easily portable between Linux and Mac. These set of classes where originally intended to be used as a foundation for [PushMeMail's](https://itunes.apple.com/us/app/push-me-mail/id449511589?ls=1&mt=8) e-mail poller daemons.

## Features
* POSIX based multithreading classes
 Classes
 * **GenericThread**: implements the basic building block for a thread, just override the operator()() method and start with ThreadDispatcher::start()
 * **Mutex**: a MUtual EXclussion mechanism class, implements lock/unlock.
 * **RWLock**: our implementation of read/write locks.
 * **AtomicFlag**: allows to have a shared boolean object, very useful for those times when you need a flag to be shared among threads.
 * **AtomicVar**: is a template that can be use to have shared numeric values between threads, shared counters perhaps?
* Thread-safe data-structures
 * **SharedSet**: template class that allows to implement thread-safe shared sets.
 * **SharedMap**: template class that implements thread-safe shared maps.
 * **SharedVector**: Allows to implement vectors that can be shared between threads.
 * **SharedQueue**: A template that allows to implement shared queues between threads.
* Exception handling (this one is pretty primitive)
 * **GenericException**: is the basic building block for all types of exceptions.
 * **MutexLockException**: thrown when an attempt to lock a previously locked mutex is made, very handy!!!
 * **ThreadExecutionException**: throws when an attempt to launch a thread fails.
* APNS (Apple© Push Notification Server) integration
 * **APNSNotificationThread**: A thread that takes care of dispatching push notification messages to the APNS cloud, it only needs a queue of NotificationPayload objects and the mandatory certificates to do its magic, easy as eating a piece of cake.
 * **APNSFeedbackThread**: still a work in progress but it is intended as an interface with the APNS feedback service, the one that tells you back if a delivery failed.
* Thread-safe logging facilities
 * **MTLogger**: a mechanism that allows you to write logs to a single file from any thread concurrently while keeping the coherence and registering which thread originated the message.
