TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp HTTPClient.cpp HTTPHandler.cpp HTTPServer.cpp PythonModule.cpp
HEADERS += HTTPClient.h HTTPCodes.h HTTPHandler.h HTTPServer.h PythonModule.h

LIBS += -lws2_32 -lboost_system -lboost_thread
QMAKE_CXXFLAGS += -DBOOST_THREAD_USE_LIB
