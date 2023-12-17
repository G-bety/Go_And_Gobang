HEADERS += \
    Chessboard.h \
    Chessboardpoint.h \
    Controller.h \
    GameTurn.h \
    Gamestate.h \
    Go.h \
    GoMoment.h \
    Gobang.h \
    GobangMoment.h \
    MomentIF.h \
    PointState.h \
    boardshow.h \
    caretaker.h \
    consturtgame.h \
    creator.h \
    gameif.h \
    go_caretaker.h \
    gobang_caretaker.h \
    gobangboardshow.h \
    goboardshow.h \
    minwindow.h \
    oldgamelistshow.h \
    operationwithfile.h \
    select_gobangsize.h \
    select_gosize.h \
    select_neworold.h \
    select_sizeif.h

SOURCES += \
    Chessboard.cpp \
    Controller.cpp \
    Go.cpp \
    GoMoment.cpp \
    Gobang.cpp \
    GobangMoment.cpp \
    boardshow.cpp \
    caretaker.cpp \
    consturtgame.cpp \
    creator.cpp \
    gameif.cpp \
    go_caretaker.cpp \
    gobang_caretaker.cpp \
    gobangboardshow.cpp \
    goboardshow.cpp \
    main.cpp \
    minwindow.cpp \
    oldgamelistshow.cpp \
    operationwithfile.cpp \
    select_gobangsize.cpp \
    select_gosize.cpp \
    select_neworold.cpp \
    select_sizeif.cpp

QT += widgets gui

FORMS += \
    minwindow.ui \
    select_gobangsize.ui \
    select_gosize.ui \
    select_neworold.ui
