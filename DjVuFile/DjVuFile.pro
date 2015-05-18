#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T16:30:42
#
#-------------------------------------------------

QT       -= core gui

TARGET = DjVuFile
TEMPLATE = lib
CONFIG += staticlib

DEFINES += UNICODE
DEFINES += _UNICODE
DEFINES += _USE_LIBXML2_READER_
DEFINES += LIBXML_READER_ENABLED

SOURCES += djvufile.cpp \
    libdjvu/Arrays.cpp \
    libdjvu/atomic.cpp \
    libdjvu/BSByteStream.cpp \
    libdjvu/BSEncodeByteStream.cpp \
    libdjvu/ByteStream.cpp \
    libdjvu/DataPool.cpp \
    libdjvu/debug.cpp \
    libdjvu/DjVmDir.cpp \
    libdjvu/DjVmDir0.cpp \
    libdjvu/DjVmDoc.cpp \
    libdjvu/DjVmNav.cpp \
    libdjvu/DjVuAnno.cpp \
    libdjvu/DjVuDocEditor.cpp \
    libdjvu/DjVuDocument.cpp \
    libdjvu/DjVuDumpHelper.cpp \
    libdjvu/DjVuErrorList.cpp \
    libdjvu/DjVuFile.cpp \
    libdjvu/DjVuFileCache.cpp \
    libdjvu/DjVuGlobal.cpp \
    libdjvu/DjVuGlobalMemory.cpp \
    libdjvu/DjVuImage.cpp \
    libdjvu/DjVuInfo.cpp \
    libdjvu/DjVuMessage.cpp \
    libdjvu/DjVuMessageLite.cpp \
    libdjvu/DjVuNavDir.cpp \
    libdjvu/DjVuPalette.cpp \
    libdjvu/DjVuPort.cpp \
    libdjvu/DjVuText.cpp \
    libdjvu/DjVuToPS.cpp \
    libdjvu/GBitmap.cpp \
    libdjvu/GContainer.cpp \
    libdjvu/GException.cpp \
    libdjvu/GIFFManager.cpp \
    libdjvu/GMapAreas.cpp \
    libdjvu/GOS.cpp \
    libdjvu/GPixmap.cpp \
    libdjvu/GRect.cpp \
    libdjvu/GScaler.cpp \
    libdjvu/GSmartPointer.cpp \
    libdjvu/GString.cpp \
    libdjvu/GThreads.cpp \
    libdjvu/GUnicode.cpp \
    libdjvu/GURL.cpp \
    libdjvu/IFFByteStream.cpp \
    libdjvu/IW44EncodeCodec.cpp \
    libdjvu/IW44Image.cpp \
    libdjvu/JB2EncodeCodec.cpp \
    libdjvu/JB2Image.cpp \
    libdjvu/JPEGDecoder.cpp \
    libdjvu/MMRDecoder.cpp \
    libdjvu/MMX.cpp \
    libdjvu/UnicodeByteStream.cpp \
    libdjvu/XMLParser.cpp \
    libdjvu/XMLTags.cpp \
    libdjvu/ZPCodec.cpp \
    DjVu.cpp \
    DjVuFileImplementation.cpp

HEADERS += djvufile.h \
    libdjvu/Arrays.h \
    libdjvu/atomic.h \
    libdjvu/BSByteStream.h \
    libdjvu/ByteStream.h \
    libdjvu/DataPool.h \
    libdjvu/debug.h \
    libdjvu/DjVmDir.h \
    libdjvu/DjVmDir0.h \
    libdjvu/DjVmDoc.h \
    libdjvu/DjVmNav.h \
    libdjvu/DjVuAnno.h \
    libdjvu/DjVuDocEditor.h \
    libdjvu/DjVuDocument.h \
    libdjvu/DjVuDumpHelper.h \
    libdjvu/DjVuErrorList.h \
    libdjvu/DjVuFile.h \
    libdjvu/DjVuFileCache.h \
    libdjvu/DjVuGlobal.h \
    libdjvu/DjVuImage.h \
    libdjvu/DjVuInfo.h \
    libdjvu/DjVuMessage.h \
    libdjvu/DjVuMessageLite.h \
    libdjvu/DjVuNavDir.h \
    libdjvu/DjVuPalette.h \
    libdjvu/DjVuPort.h \
    libdjvu/DjVuText.h \
    libdjvu/DjVuToPS.h \
    libdjvu/GBitmap.h \
    libdjvu/GContainer.h \
    libdjvu/GException.h \
    libdjvu/GIFFManager.h \
    libdjvu/GMapAreas.h \
    libdjvu/GOS.h \
    libdjvu/GPixmap.h \
    libdjvu/GRect.h \
    libdjvu/GScaler.h \
    libdjvu/GSmartPointer.h \
    libdjvu/GString.h \
    libdjvu/GThreads.h \
    libdjvu/GURL.h \
    libdjvu/IFFByteStream.h \
    libdjvu/IW44Image.h \
    libdjvu/JB2Image.h \
    libdjvu/JPEGDecoder.h \
    libdjvu/MMRDecoder.h \
    libdjvu/MMX.h \
    libdjvu/UnicodeByteStream.h \
    libdjvu/XMLParser.h \
    libdjvu/XMLTags.h \
    libdjvu/ZPCodec.h \
    DjVu.h \
    DjVuFileImplementation.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}