TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc
#LIBS += -lopencv_core -lopencv_videoio -lopencv_imgcodecs -lopencv_highgui -lopencv_objdetect
#LIBS += -lopencv_imgproc

#LIBS:= -L/usr/local/lib -lopencv_calib3d -lopencv_video -lopencv_ml -lopencv_contrib -lopencv_core -lopencv_imgproc -lopencv_objdetect -lopencv_highgui

SOURCES += main.cpp \
    gamewindow.cpp \
    ball.cpp

HEADERS += \
    ball.hpp \
    gamewindow.hpp
