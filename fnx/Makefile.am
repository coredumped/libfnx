h_sources = APNSConstants.h APNSFeedbackThread.h APNSNotificationThread.h \
	GenericException.h GenericThread.h MTLogger.h Mutex.h \
	NotificationPayload.h SharedQueue.h SharedVector.h \
	ThreadDispatcher.h UtilityFunctions.h PendingNotificationStore.h \
	RWLock.h SharedSet.h SharedMap.h Atomic.h fnxconfig.h

cc_sources = APNSFeedbackThread.cpp APNSNotificationThread.cpp \
	GenericException.cpp GenericThread.cpp MTLogger.cpp Mutex.cpp \
	NotificationPayload.cpp SharedQueue.cpp ThreadDispatcher.cpp \
	UtilityFunctions.cpp PendingNotificationStore.cpp \
	RWLock.cpp Atomic.cpp


#library_includedir=$(includedir)/@PACKAGE_NAME@
#library_include_HEADERS = $(h_sources)

AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES=libfnx.la
libfnx_la_SOURCES= $(h_sources) $(cc_sources)
libfnx_la_LDFLAGS= -release @PACKAGE_VERSION@
pkginclude_HEADERS = $(h_sources)


rebuild: clean all
