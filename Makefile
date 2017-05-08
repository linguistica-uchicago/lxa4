# To build Linguistica, execute "make".
# Run "make V=1" to see the actual commands being run.
# See ./README for more information.
all: linguistica

# Define CXX to the version of g++ you prefer to use.
#
# Define CFLAGS with flags to pass to g++ during compilation
# (e.g. -Os -Wall -W).
#
# Define LDFLAGS with flags to pass to g++ during linking.
#
# Define NO_PKGCONFIG to disable use of pkg-config during the build
# (e.g. if /usr/lib/pkgconfig/QtCore.pc contains nonsense).
#
# Define MOC to the version of the Qt meta-object compiler command
# you prefer to use (e.g. moc-qt4).
#
# Define UIC to the version of the Qt user-interface compiler you
# prefer to use (e.g. uic-qt4).
#
# Define RCC to the version of the Qt resource compiler you prefer
# to use (e.g. rcc).
#
# Define NO_GRAPHVIZ to disable the morphological finite-state
# machine graphical display.
#
# Define GRAPHVIZ_LIB to flags to link to and GRAPHVIZ_CFLAGS to
# flags to compile with the GraphVizContext library.  Example:
# GRAPHVIZ_LIB = -L/usr/lib/graphviz -Wl,-rpath,/usr/lib/graphviz -lgvc
# GRAPHVIZ_CFLAGS = -I/usr/include/graphviz
#
# Define QT_LIB to flags to link and QT_CFLAGS to flags to
# compile with Qt 4, including the QtGui, Qt3Support, and QtXml
# modules.  Example:
# QT_LIB = -lQt3Support -lQtGui -lQtNetwork -lQtSql -lQtXml -lQtCore
# QT_CFLAGS = -DQT_SHARED -DQT3_SUPPORT -I/usr/include/qt4 \
# 	-I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore \
# 	-I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtNetwork \
# 	-I/usr/include/qt4/QtSql -I/usr/include/qt4/QtXml  

define NO_GRAPHVIZ
endef
CFLAGS = -g -O2 -Wall -W
LDFLAGS =
CXX = g++
RCC = rcc
MOC = moc-qt4
UIC = uic-qt4
QT_LIB = -lQt3Support -lQtGui -lQtXml -lQtCore
QT_CFLAGS = -DQT_SHARED -DQT3_SUPPORT -I/usr/include/qt4 \
	-I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore \
	-I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtXml
GRAPHVIZ_LIB = -L/usr/lib/graphviz -Wl,-rpath,/usr/lib/graphviz -lgvc
GRAPHVIZ_CFLAGS = -I/usr/include/graphviz

ifeq ($(shell type pkg-config > /dev/null 2>&1 || echo n),n)
    NO_PKGCONFIG = YesUnfortunately
endif

-include config.mak

ifndef NO_PKGCONFIG
    pkgconfig_failed = \
        $(error Run “make NO_PKGCONFIG=YesPlease” to disable use of pkg-config)

    define find_qt_command
        $(1) := $$(shell pkg-config --print-errors \
                --variable=$(2)_location QtCore)

        ifeq ($$(shell type "$$($(1))" > /dev/null || echo n),n)
        $$(pkgconfig_failed)
        endif
    endef
    $(eval $(call find_qt_command,MOC,moc))
    $(eval $(call find_qt_command,UIC,uic))

    QT_LIB := $(shell pkg-config --print-errors \
                --libs QtGui Qt3Support QtXml QtCore)
    QT_CFLAGS := $(shell pkg-config --print-errors \
                --cflags QtGui Qt3Support QtXml QtCore) \
                -DQT3_SUPPORT

    ifeq ($(shell pkg-config --exists libgvc || echo n),n)
    NO_GRAPHVIZ = YesUnfortunately
    endif

    ifndef NO_GRAPHVIZ
    GRAPHVIZ_LIB := $(shell pkg-config --print-errors --libs libgvc)
    GRAPHVIZ_CFLAGS := $(shell pkg-config --print-errors --cflags libgvc)
    endif
endif

ifdef NO_GRAPHVIZ
    GRAPHVIZ_LIB :=
    GRAPHVIZ_CFLAGS :=
    ALL_GRAPHVIZ_CFLAGS :=
else
    ALL_GRAPHVIZ_CFLAGS ?= $(GRAPHVIZ_CFLAGS) -DUSE_GRAPHVIZ
endif

ifdef CXXFLAGS
    CFLAGS := $(CXXFLAGS)
endif

# The compiler should not rely on strict aliasing rules,
# since QMap violates them.

ALL_CFLAGS ?= $(CFLAGS) -fno-strict-aliasing \
		$(QT_CFLAGS) $(ALL_GRAPHVIZ_CFLAGS)
ALL_LDFLAGS ?= $(LDFLAGS)
LIBS ?= $(GRAPHVIZ_LIB) $(QT_LIB)

OBJECTS += Affix.o
OBJECTS += Alignment.o
OBJECTS += Allomorphy.o
OBJECTS += Biphone.o
OBJECTS += BiphoneCollection.o
OBJECTS += canvasdialog.o
OBJECTS += CommandLine.o
OBJECTS += CompareFunc.o
OBJECTS += Compound.o
OBJECTS += CompoundCollection.o
OBJECTS += corpusviewdialog.o
OBJECTS += CorpusWord.o
OBJECTS += CorpusWordCollection.o
OBJECTS += Datum.o
OBJECTS += DescriptionLength.o
OBJECTS += DLHistory.o
OBJECTS += EarleyParser.o
OBJECTS += Edge.o
OBJECTS += exportwizard.o
OBJECTS += exportwizard_exporting.o
OBJECTS += FSA.o
OBJECTS += GrammarRule.o
OBJECTS += GUI_Lexicon.o
OBJECTS += GUIclasses.o
OBJECTS += helpaboutdialog.o
OBJECTS += HTML.o
OBJECTS += Lexicon.o
OBJECTS += Lexicon_Allomorphy.o
OBJECTS += Lexicon_Compounds.o
OBJECTS += linepropertiesdialog.o
OBJECTS += linguisticamainwindow.o
OBJECTS += linguisticamainwindow_collectionview.o
OBJECTS += linguisticamainwindow_commandline.o
OBJECTS += linguisticamainwindow_goldstandard.o
OBJECTS += linguisticamainwindow_preferences.o
OBJECTS += linguisticamainwindow_treeview.o
OBJECTS += Linker.o
OBJECTS += LinkerCollection.o
OBJECTS += listbuilderdialog.o
OBJECTS += LParse.o
OBJECTS += LPreferences.o
OBJECTS += main.o
OBJECTS += MiniLexicon.o
OBJECTS += MiniLexicon_Allomorphy.o
OBJECTS += MiniLexicon_CheckAffixes.o
OBJECTS += MiniLexicon_Core.o
OBJECTS += MiniLexicon_SingletonSignatures.o
OBJECTS += MiniLexicon_SuccessorFreqs.o
OBJECTS += MonteCarlo.o
OBJECTS += Morpheme.o
OBJECTS += MorphemeCollection.o
OBJECTS += mTVolca.o
OBJECTS += Parse.o
OBJECTS += Phone.o
OBJECTS += PhoneCollection.o
OBJECTS += Phonology.o
OBJECTS += POS.o
OBJECTS += POSCollection.o
OBJECTS += preferencesdialog.o
OBJECTS += Prefix.o
OBJECTS += PrefixCollection.o
OBJECTS += Sequencer.o
OBJECTS += Signature.o
OBJECTS += SignatureCollection.o
OBJECTS += SignatureCollection_PartsOfSpeech.o
OBJECTS += Slice.o
OBJECTS += SparseIntVector.o
OBJECTS += SparseVector.o
OBJECTS += StateEmitHMM.o
OBJECTS += Stats.o
OBJECTS += Stem.o
OBJECTS += StemCollection.o
OBJECTS += StringEditGrid.o
OBJECTS += StringFunc.o
OBJECTS += StringSurrogate.o
OBJECTS += Suffix.o
OBJECTS += SuffixCollection.o
OBJECTS += Template.o
OBJECTS += TemplateCollection.o
OBJECTS += TerminalRuleCollection.o
OBJECTS += TreeViewItem.o
OBJECTS += Trie.o
OBJECTS += verifydialog.o
OBJECTS += Version.o
OBJECTS += VeryLong.o
OBJECTS += Word.o
OBJECTS += WordCollection.o
OBJECTS += moc_canvasdialog.o
OBJECTS += moc_corpusviewdialog.o
OBJECTS += moc_exportwizard.o
OBJECTS += moc_helpaboutdialog.o
OBJECTS += moc_linepropertiesdialog.o
OBJECTS += moc_linguisticamainwindow.o
OBJECTS += moc_listbuilderdialog.o
OBJECTS += moc_preferencesdialog.o
OBJECTS += moc_verifydialog.o

OBJECTS += qrc_linguistica.o

RESOURCES += images/splash.png
RESOURCES += images/new.xpm
RESOURCES += images/reload.xpm
RESOURCES += images/save.xpm
RESOURCES += images/open.xpm
RESOURCES += images/favicon.xpm

ifeq ($(V),1)
    quiet_link =
    quiet_compile =
    quiet_metaobject =
    quiet_resource =
    quiet_uiheader =
else
    quiet_link = @echo "  LINK" $@ &&
    quiet_compile = @echo "  CXX" $@ &&
    quiet_metaobject = @echo "  MOC" $@ &&
    quiet_resource = @echo "  RCC" $@ &&
    quiet_uiheader = @echo "  UIC" $@ &&
endif

linguistica: $(OBJECTS)
	$(quiet_link) $(CXX) -o $@ $(OBJECTS) $(ALL_LDFLAGS) $(LIBS)

dep_args = -MF .$@.d -MMD -MP

%.o: %.cpp
	$(quiet_compile) $(CXX) -c $< $(dep_args) $(ALL_CFLAGS)

dep_files := $(wildcard .*.d)
ifneq ($(dep_files),)
    include $(dep_files)
endif

moc_%.cpp: %.h
	$(quiet_metaobject) $(MOC) -o $@ $<

qrc_linguistica.cpp: images/linguistica.qrc $(RESOURCES)
	$(quiet_resource) $(RCC) -o $@ $< -name linguistica

$(OBJECTS): ui_canvasdialogbase.h
$(OBJECTS): ui_corpusviewdialogbase.h
$(OBJECTS): ui_exportwizardbase.h
$(OBJECTS): ui_helpaboutdialogbase.h
$(OBJECTS): ui_linepropertiesdialogbase.h
$(OBJECTS): ui_linguisticamainwindowbase.h
$(OBJECTS): ui_listbuilderdialogbase.h
$(OBJECTS): ui_preferencesdialogbase.h
$(OBJECTS): ui_propertiesdialogbase.h
$(OBJECTS): ui_verifydialogbase.h

ui_%.h: %.ui
	$(quiet_uiheader) $(UIC) -o $@ $<

linguistica.app: linguistica macosx/Info.plist macosx/linguistica.icns
	rm -rf $@ $@+
	mkdir -p $@+/Contents/MacOS
	mkdir -p $@+/Contents/Resources
	cp macosx/Info.plist $@+/Contents
	cp macosx/linguistica.icns $@+/Contents/Resources
	cp linguistica $@+/Contents/MacOS
	mv $@+ $@

clean:
	rm -f .*.o.d
	rm -f *.o
	rm -f ui_*.h
	rm -f moc_*.cpp
	rm -f qrc_*.cpp
	rm -f linguistica
	rm -rf linguistica.app linguistica.app+

.PHONY: all clean
