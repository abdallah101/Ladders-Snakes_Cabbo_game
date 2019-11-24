SOURCES += \
    main.cpp \
    user.cpp \
registermenu.cpp \
    mainmenu_widget.cpp \
    mainscreen.cpp \
    settings.cpp \
    gameone.cpp \
    players.cpp \
    dice.cpp \
    game1_scene.cpp \
    dicecust.cpp \
    game1_scenecust.cpp \
    custWid.cpp \
    snakesladders.cpp \
    game1_modes.cpp \
    starter.cpp \
    winlose.cpp \
    gametwo.cpp \
    game2_scene.cpp \
    cards.cpp \
    viewgametwo.cpp \
    game2details.cpp \
    xtostart.cpp


QT += \
    widgets \
    core


CONFIG += C++11 \

HEADERS += \
    user.h \
registermenu.h \
    mainmenu_widget.h \
    mainscreen.h \
    settings.h \
    gameone.h \
    dice.h \
    game1_scene.h \
    players.h \
    dicecust.h \
    game1_scenecust.h \
    custWid.h \
    snakesladders.h \
    game1_modes.h \
    starter.h \
    winlose.h \
    gametwo.h \
    game2_scene.h \
    cards.h \
    viewgametwo.h \
    game2details.h \
    xtostart.h


OTHER_FILES +=

RESOURCES += \
    UserProfilePics/ProfilePics.qrc \
    Images/Images.qrc

DISTFILES += \
    UserData.txt \
    ../../../../Downloads/istockphoto-455302535-612x612.jpg \
    ../../../../Downloads/SL.jpg \
    Images/black.jpg \
    Images/white.jpeg

FORMS += \
    dices.ui
