#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T20:32:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = caffeTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    cafe_net.h

FORMS    += mainwindow.ui


INCLUDEPATH += /usr/include \
              /usr/include/opencv \
              /usr/include/opencv2

# caffe
INCLUDEPATH += /home/zou/GitHub/caffe/include \
               /home/zou/GitHub/caffe/build/src

LIBS += -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/home/zou/GitHub/caffe -L/home/zou/GitHub/caffe/build/lib \
        -lopencv_highgui -lopencv_core -lopencv_imgproc \   #opencv
        -lglog -lgflags -lprotobuf -lboost_system -lboost_thread -llmdb -lleveldb -lstdc++ -lcblas -latlas \ #others lib
        -lcaffe

CONFIG += console c++11


DEFINES += CPU_ONLY

#DEFINES += _GLIBCXX_USE_CXX11_ABI=0 -D_GLIBCXX_USE_CXX11_ABI=0





#-lswscale -lboost_system -lboost_thread -lglog -lgomp -lpthread \    #others lib

#LIBS += /home/zou/GitHub/caffe /build/lib/libcaffe.so
#LIBS += lcaffe

#LIBS +=/usr/lib/x86_64-linux-gnu/libopencv_calib3d.so \
#/usr/lib/x86_64-linux-gnu/libopencv_core.so \
#/usr/lib/x86_64-linux-gnu/libopencv_features2d.so \
#/usr/lib/x86_64-linux-gnu/libopencv_flann.so \
#/usr/lib/x86_64-linux-gnu/libopencv_highgui.so \
#/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so \
#/usr/lib/x86_64-linux-gnu/libopencv_ml.so \
#/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so \
#/usr/lib/x86_64-linux-gnu/libopencv_photo.so \
#/usr/lib/x86_64-linux-gnu/libopencv_stitching.so \
#/usr/lib/x86_64-linux-gnu/libopencv_superres.so \
#/usr/lib/x86_64-linux-gnu/libopencv_video.so \
#/usr/lib/x86_64-linux-gnu/libopencv_videostab.so
