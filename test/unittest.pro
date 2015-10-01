TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += DEBUG

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
QMAKE_LFLAGS += -pthread -Wl,--no-as-needed

INCLUDEPATH += ../src/

SOURCES += \
    ../src/error.cpp \
    main.cpp \
    tst_behavior.cpp \
    tst_capturestorage.cpp \
    tst_configurationchangecallback.cpp \
    tst_event.cpp \
    tst_eventcallback.cpp \
    tst_eventlist.cpp \
    tst_exceptions.cpp \
    tst_functionstate.cpp \
    tst_hierarchy.cpp \
    tst_iteration.cpp \
    tst_multithreading.cpp \
    tst_state.cpp \
    tst_statecallbacks.cpp \
    tst_statemachine.cpp \
    tst_threadedstate.cpp \
    tst_threadpool.cpp \
    tst_transition.cpp \
    tst_transitionconflict.cpp \
    tst_transitionconflictcallback.cpp

HEADERS += \
    ../src/error.hpp \
    ../src/exitrequest.hpp \
    ../src/functionstate.hpp \
    ../src/historystate.hpp \
    ../src/options.hpp \
    ../src/state.hpp \
    ../src/statemachine.hpp \
    ../src/statemachine_fwd.hpp \
    ../src/threadedstate.hpp \
    ../src/threadedfunctionstate.hpp \
    ../src/threadpool.hpp \
    ../src/transition.hpp \
    ../src/detail/callbacks.hpp \
    ../src/detail/capturestorage.hpp \
    ../src/detail/eventdispatcher.hpp \
    ../src/detail/multithreading.hpp \
    ../src/detail/notifications.hpp \
    ../src/detail/options.hpp \
    ../src/detail/scopeguard.hpp

HEADERS += catch.hpp \
           fsm11_user_config.hpp \
           testutils.hpp
