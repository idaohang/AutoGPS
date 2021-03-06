#-------------------------------------------------
#  Copyright 2014 ESRI
#
#  All rights reserved under the copyright laws of the United States
#  and applicable international laws, treaties, and conventions.
#
#  You may freely redistribute and use this sample code, with or
#  without modification, provided you include the original copyright
#  notice and use restrictions.
#
#  See the Sample code usage restrictions document for further information.
#-------------------------------------------------

TARGET = AutoGPS 
TEMPLATE = app

QT += gui core opengl xml network declarative

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets serialport multimediawidgets
}

#TRANSLATIONS = myapp.ts
DESTDIR = ./

#release:DEFINES += QT_NO_WARNING_OUTPUT\
#                   QT_NO_DEBUG_OUTPUT

##-------------- Opencv
#INCLUDEPATH += D:/opencv/build/include
#CONFIG(debug,debug|release) {
#LIBS += -LD:/opencv/build/x86/vc11/lib \
#    -lopencv_core249d \
#    -lopencv_highgui249d \
#    -lopencv_imgproc249d \
#    -lopencv_features2d249d \
#    -lopencv_calib3d249d
#} else {
#LIBS += -LD:/opencv/build/x86/vc11/lib \
#    -lopencv_core249 \
#    -lopencv_highgui249 \
#    -lopencv_imgproc249 \
#    -lopencv_features2d249 \
#    -lopencv_calib3d249
#}
# --------------------
##---------------VLD   对vs2012支持不够
#INCLUDEPATH += $$quote(D:/Program Files/Visual Leak Detector/include)
#LIBS += -L$$quote(D:/Program Files/Visual Leak Detector/lib/Win32) \
#    -lvld
##---------------------




# After installing the Runtime SDK for Qt you'll need to copy the
# esri_runtime_qt_10_2_3.prf file from your qt10.2.3/sdk/ideintegration folder
# to your Qt SDK's mkspecs/features folder in order for Qt Creator to locate 
# the ArcGIS Runtime SDK for Qt header files and libraries.
#
CONFIG +=  c++11 esri_runtime_qt_10_2_3

win32:CONFIG += \
  embed_manifest_exe


SOURCES += \
	main.cpp \
        AutoGPS.cpp \ 
    mapcontroller.cpp \
    simplegraphicoverlay.cpp \
    masterthread.cpp \
    camera.cpp \
    mycoordinate.cpp

HEADERS += \
	AutoGPS.h \
    mapcontroller.h \
    simplegraphicoverlay.h \
    masterthread.h \
    camera.h \
    mycoordinate.h

FORMS +=

RESOURCES += \
    AutoGPSResources.qrc

OTHER_FILES += \
    Resources/qml/CompositeControls/NavigationControl2.qml \
    Resources/qml/CompositeControls/StatusBar.qml\
    Resources/qml/Controls/ClassificationBar.qml\
    Resources/qml/Controls/Menu.qml\
    Resources/qml/Controls/ModelObject.qml\
    Resources/qml/Controls/MultiDelegate.qml\
    Resources/qml/Controls/Panel.qml\
    Resources/qml/Controls/PushButton.qml\
    Resources/qml/Controls/Stack.qml\
    Resources/qml/Controls/StackObject.js\
    Resources/qml/Controls/ToggleButton.qml\
    Resources/qml/Controls/ScrollButton.qml\
    Resources/qml/MainOverlay.qml\
    Resources/qml/PanelContainers/MainMenu.qml\
    Resources/qml/Panels/MainMenu/MainPanel.qml \
    Resources/qml/PanelContainers/SerialConfig.qml \
    Resources/qml/PanelContainers/Config.qml \
    Resources/qml/Panels/Config/ConfigPanel.qml \
    Resources/qml/Panels/Config/SerialConfigPanel.qml \
    Resources/qml/Panels/Config/PortNoPanel.qml \
    Resources/qml/Panels/Config/BaudRatePanel.qml \
    Resources/qml/Panels/Config/DataBitsPanel.qml \
    Resources/qml/Panels/Config/StopBitsPanel.qml \
    Resources/qml/Panels/Config/ParityPanel.qml \
    Resources/qml/Panels/Config/TimeOutPanel.qml \
    Resources/qml/PanelContainers/Worker.qml \
    Resources/qml/Panels/Worker/WorkerPanel.qml \
    Resources/qml/Panels/Worker/GeometryPanel.qml \
    Resources/qml/Panels/Worker/PathsPanel.qml \
    Resources/qml/PanelContainers/Camera.qml \
    Resources/qml/PanelContainers/Record.qml \
    Resources/qml/Panels/Record/RecordPanel.qml \
    Resources/qml/Panels/Record/SerialRecordPanel.qml \
    Resources/qml/Panels/Record/XmlRecordPanel.qml \
    Resources/qml/Panels/Record/CropLandPanel.qml \
    Resources/qml/Panels/Record/RoutePanel.qml \
    myapp.ts \
    Resources/qml/PanelContainers/Player.qml\
    Resources/qml/Panels/Player/PlayerPanel.qml \
    Resources/qml/Panels/Player/PlayerCroplandPanel.qml
