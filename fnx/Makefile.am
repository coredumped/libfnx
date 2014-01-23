h_sources = APNSConstants.h APNSFeedbackThread.h APNSNotificationThread.h \
	GenericException.h GenericThread.h MTLogger.h Mutex.h \
	NotificationPayload.h SharedQueue.h SharedVector.h \
	ThreadDispatcher.h UtilityFunctions.h

cc_sources = APNSFeedbackThread.cpp APNSNotificationThread.cpp \
	GenericException.cpp GenericThread.cpp MTLogger.cpp Mutex.cpp \
	NotificationPayload.cpp SharedQueue.cpp ThreadDispatcher.cpp \
	UtilityFunctions.cpp


library_includedir=$(includedir)/$(GENERIC_LIBRARY_NAME)
library_include_HEADERS = $(h_sources)

AM_CPPFLAGS = -I$(top_srcdir)

lib_LTLIBRARIES=libfnx.la
libfnx_la_SOURCES= $(h_sources) $(cc_sources)
libfnx_la_LDFLAGS= -version-info $(GENERIC_LIBRARY_VERSION) -release $(GENERIC_RELEASE)

rebuild: clean all
