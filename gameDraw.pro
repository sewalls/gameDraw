QT += widgets
requires(qtConfig(combobox))

HEADERS       = renderarea.h \
                window.h \
    grelement.h \
    player.h \
    enemy.h \
    food.h
SOURCES       = main.cpp \
                renderarea.cpp \
                window.cpp \
    grelement.cpp \
    player.cpp \
    enemy.cpp \
    food.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target
