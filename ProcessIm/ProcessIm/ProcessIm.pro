#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T15:36:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcessIm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    infowindows.cpp \
    imagewindows.cpp \
    morphologie.cpp \
    transformation.cpp \
    filtrage.cpp \
    qlabel_image.cpp \
    comptage.cpp \
    distance.cpp \
    fenetretraitement.cpp \
    histogramme.cpp \
    lecturecb.cpp \
    seuillage.cpp \
    signatures.cpp \
    signatureform.cpp \
    conversion.cpp \
    conversion.cpp

HEADERS  += mainwindow.h \
    infowindows.h \
    imagewindows.h \
    morphologie.h \
    transformation.h \
    filtrage.h \
    comptage.h \
    distance.h \
    fenetretraitement.h \
    histogramme.h \
    lecturecb.h \
    qlabel_image.h \
    seuillage.h \
    signatures.h \
    signatureform.h \
    conversion.h \
    conversion.h

FORMS    += mainwindow.ui \
    infowindows.ui \
    imagewindows.ui \
    morphologie.ui \
    transformation.ui \
    filtrage.ui \
    comptage.ui \
    distance.ui \
    fenetretraitement.ui \
    histogramme.ui \
    lecturecb.ui \
    seuillage.ui \
    signatures.ui \
    signatureform.ui \
    conversion.ui \
    conversion.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../traitement/build/release/ -ltraitement
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../traitement/build/debug/ -ltraitement

INCLUDEPATH += $$PWD/../../traitement
DEPENDPATH += $$PWD/../../traitement

DISTFILES += \
    Image/im0002.bmp
    actions/document-save-3.ico
    actions/zoom-in-3.ico
    actions/zoom-out-3.ico
