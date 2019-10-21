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
    game1_scene.cpp


QT += \
    widgets \
    core




HEADERS += \
    user.h \
registermenu.h \
    mainmenu_widget.h \
    mainscreen.h \
    settings.h \
    gameone.h \
    dice.h \
    game1_scene.h \
    players.h


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
