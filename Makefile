#############################################################################
# Makefile for building: duplicateFinder
# Generated by qmake (2.01a) (Qt 4.5.2) on: ?? ????. 14 22:40:45 2009
# Project:  duplicateFinder.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile duplicateFinder.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -march=x86-64 -mtune=generic -O2 -pipe -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -march=x86-64 -mtune=generic -O2 -pipe -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt/mkspecs/linux-g++-64 -I. -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -L/usr/lib -L/usr/X11R6/lib64 -pthread -lpng -lfreetype -lgobject-2.0 -lSM -lICE -pthread -pthread -lXrender -lfontconfig -lXext -lX11 -lQtCore -lz -lm -pthread -lgthread-2.0 -lrt -lglib-2.0 -ldl -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		progresswidget.cpp \
		scanthread.cpp \
		deletelist.cpp \
		common.cpp \
		deletetreewidget.cpp \
		optionsdialog.cpp moc_mainwindow.cpp \
		moc_progresswidget.cpp \
		moc_scanthread.cpp \
		moc_deletelist.cpp \
		moc_deletetreewidget.cpp \
		moc_optionsdialog.cpp \
		qrc_icons.cpp
OBJECTS       = main.o \
		mainwindow.o \
		progresswidget.o \
		scanthread.o \
		deletelist.o \
		common.o \
		deletetreewidget.o \
		optionsdialog.o \
		moc_mainwindow.o \
		moc_progresswidget.o \
		moc_scanthread.o \
		moc_deletelist.o \
		moc_deletetreewidget.o \
		moc_optionsdialog.o \
		qrc_icons.o
DIST          = /usr/share/qt/mkspecs/common/g++.conf \
		/usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		duplicateFinder.pro
QMAKE_TARGET  = duplicateFinder
DESTDIR       = 
TARGET        = duplicateFinder

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: duplicateFinder.pro  /usr/share/qt/mkspecs/linux-g++-64/qmake.conf /usr/share/qt/mkspecs/common/g++.conf \
		/usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile duplicateFinder.pro
/usr/share/qt/mkspecs/common/g++.conf:
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
/usr/share/qt/mkspecs/features/release.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile duplicateFinder.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/duplicateFinder1.0.0 || $(MKDIR) .tmp/duplicateFinder1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/duplicateFinder1.0.0/ && $(COPY_FILE) --parents mainwindow.h tfile.h progresswidget.h scanthread.h deletelist.h common.h deletetreewidget.h optionsdialog.h global.h .tmp/duplicateFinder1.0.0/ && $(COPY_FILE) --parents icons.qrc .tmp/duplicateFinder1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp progresswidget.cpp scanthread.cpp deletelist.cpp common.cpp deletetreewidget.cpp optionsdialog.cpp .tmp/duplicateFinder1.0.0/ && (cd `dirname .tmp/duplicateFinder1.0.0` && $(TAR) duplicateFinder1.0.0.tar duplicateFinder1.0.0 && $(COMPRESS) duplicateFinder1.0.0.tar) && $(MOVE) `dirname .tmp/duplicateFinder1.0.0`/duplicateFinder1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/duplicateFinder1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_progresswidget.cpp moc_scanthread.cpp moc_deletelist.cpp moc_deletetreewidget.cpp moc_optionsdialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_progresswidget.cpp moc_scanthread.cpp moc_deletelist.cpp moc_deletetreewidget.cpp moc_optionsdialog.cpp
moc_mainwindow.cpp: tfile.h \
		global.h \
		scanthread.h \
		progresswidget.h \
		deletelist.h \
		common.h \
		deletetreewidget.h \
		optionsdialog.h \
		mainwindow.h
	/usr/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_progresswidget.cpp: global.h \
		progresswidget.h
	/usr/bin/moc $(DEFINES) $(INCPATH) progresswidget.h -o moc_progresswidget.cpp

moc_scanthread.cpp: tfile.h \
		global.h \
		scanthread.h
	/usr/bin/moc $(DEFINES) $(INCPATH) scanthread.h -o moc_scanthread.cpp

moc_deletelist.cpp: tfile.h \
		global.h \
		common.h \
		deletetreewidget.h \
		deletelist.h
	/usr/bin/moc $(DEFINES) $(INCPATH) deletelist.h -o moc_deletelist.cpp

moc_deletetreewidget.cpp: global.h \
		deletetreewidget.h
	/usr/bin/moc $(DEFINES) $(INCPATH) deletetreewidget.h -o moc_deletetreewidget.cpp

moc_optionsdialog.cpp: global.h \
		optionsdialog.h
	/usr/bin/moc $(DEFINES) $(INCPATH) optionsdialog.h -o moc_optionsdialog.cpp

compiler_rcc_make_all: qrc_icons.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_icons.cpp
qrc_icons.cpp: icons.qrc \
		translations/translation_ru.qm \
		icons/help-about.png \
		icons/process-stop.png \
		icons/edit-delete.png \
		icons/dialog-cancel.png \
		icons/application-exit.png \
		icons/edit-find.png \
		icons/document-open-folder.png \
		icons/dialog-ok-apply.png \
		icons/view-refresh.png \
		icons/edit-clear.png \
		icons/list-add.png \
		icons/inode-directory.png
	/usr/bin/rcc -name icons icons.qrc -o qrc_icons.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		tfile.h \
		global.h \
		scanthread.h \
		progresswidget.h \
		deletelist.h \
		common.h \
		deletetreewidget.h \
		optionsdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		tfile.h \
		global.h \
		scanthread.h \
		progresswidget.h \
		deletelist.h \
		common.h \
		deletetreewidget.h \
		optionsdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

progresswidget.o: progresswidget.cpp progresswidget.h \
		global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o progresswidget.o progresswidget.cpp

scanthread.o: scanthread.cpp scanthread.h \
		tfile.h \
		global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scanthread.o scanthread.cpp

deletelist.o: deletelist.cpp deletelist.h \
		tfile.h \
		global.h \
		common.h \
		deletetreewidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o deletelist.o deletelist.cpp

common.o: common.cpp common.h \
		global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o common.o common.cpp

deletetreewidget.o: deletetreewidget.cpp deletetreewidget.h \
		global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o deletetreewidget.o deletetreewidget.cpp

optionsdialog.o: optionsdialog.cpp optionsdialog.h \
		global.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o optionsdialog.o optionsdialog.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_progresswidget.o: moc_progresswidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_progresswidget.o moc_progresswidget.cpp

moc_scanthread.o: moc_scanthread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scanthread.o moc_scanthread.cpp

moc_deletelist.o: moc_deletelist.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_deletelist.o moc_deletelist.cpp

moc_deletetreewidget.o: moc_deletetreewidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_deletetreewidget.o moc_deletetreewidget.cpp

moc_optionsdialog.o: moc_optionsdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_optionsdialog.o moc_optionsdialog.cpp

qrc_icons.o: qrc_icons.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_icons.o qrc_icons.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
