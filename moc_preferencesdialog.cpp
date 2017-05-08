/****************************************************************************
** Meta object code from reading C++ file 'preferencesdialog.h'
**
** Created: Sun Apr 29 16:17:25 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "preferencesdialog.h"
 

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PreferencesDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x09,
      46,   18,   18,   18, 0x09,
      74,   18,   18,   18, 0x09,
     104,   18,   18,   18, 0x09,
     137,   18,   18,   18, 0x09,
     164,   18,   18,   18, 0x09,
     191,   18,   18,   18, 0x09,
     220,   18,   18,   18, 0x09,
     249,   18,   18,   18, 0x09,
     284,   18,   18,   18, 0x09,
     317,   18,   18,   18, 0x09,
     351,   18,   18,   18, 0x09,
     390,  387,   18,   18, 0x09,
     444,   18,   18,   18, 0x09,
     451,   18,   18,   18, 0x09,
     482,   18,   18,   18, 0x09,
     513,   18,   18,   18, 0x09,
     548,   18,   18,   18, 0x09,
     583,   18,   18,   18, 0x09,
     625,   18,   18,   18, 0x09,
     666,   18,   18,   18, 0x09,
     708,   18,   18,   18, 0x09,
     741,   18,   18,   18, 0x09,
     763,   18,   18,   18, 0x09,
     787,   18,   18,   18, 0x09,
     820,   18,   18,   18, 0x09,
     851,   18,   18,   18, 0x09,
     875,   18,   18,   18, 0x09,
     918,   18,   18,   18, 0x09,
     960,   18,   18,   18, 0x09,
    1003,   18,   18,   18, 0x09,
    1031,   18,   18,   18, 0x09,
    1062,   18,   18,   18, 0x09,
    1097,   18,   18,   18, 0x09,
    1137,   18,   18,   18, 0x09,
    1174,   18,   18,   18, 0x09,
    1208,   18,   18,   18, 0x09,
    1242,   18,   18,   18, 0x09,
    1296,   18,   18,   18, 0x09,
    1358,   18,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PreferencesDialog[] = {
    "PreferencesDialog\0\0mhListBoxHighlightedSlot()\0"
    "mhBoldCheckBoxClickedSlot()\0"
    "mhItalicCheckBoxClickedSlot()\0"
    "mhUnderlineCheckBoxClickedSlot()\0"
    "mhColorButtonClickedSlot()\0"
    "dsfFontButtonClickedSlot()\0"
    "loadPrefsButtonClickedSlot()\0"
    "savePrefsButtonClickedSlot()\0"
    "notificationsCheckBoxClickedSlot()\0"
    "sigDelimiterChangedSlot(QString)\0"
    "resetValuePushButtonClickedSlot()\0"
    "resetAllValsPushButtonClickedSlot()\0"
    ",,\0paramListItemRenamedSlot(Q3ListViewItem*,int,QString)\0"
    "help()\0importRulesButtonClickedSlot()\0"
    "exportRulesButtonClickedSlot()\0"
    "makeLowerCaseCheckBoxToggled(bool)\0"
    "removeNumbersCheckBoxToggled(bool)\0"
    "removePrecedingPunctCheckBoxToggled(bool)\0"
    "removeInternalPunctCheckBoxToggled(bool)\0"
    "removeFollowingPunctCheckBoxToggled(bool)\0"
    "addNewReplacementButtonPressed()\0"
    "moveUpButtonPressed()\0moveDownButtonPressed()\0"
    "removeReplacementButtonPressed()\0"
    "scrubListBoxSelectionChanged()\0"
    "replaceStringsChanged()\0"
    "precedingPunctLineEditTextChanged(QString)\0"
    "internalPunctLineEditTextChanged(QString)\0"
    "followingPunctLineEditTextChanged(QString)\0"
    "newComboButtonClickedSlot()\0"
    "removeComboButtonClickedSlot()\0"
    "comboListBoxSelectionChangedSlot()\0"
    "joinWithoutDashRadioButtonClickedSlot()\0"
    "joinWithDashRadioButtonClickedSlot()\0"
    "doNotJoinRadioButtonClickedSlot()\0"
    "removeHyphenCheckBoxClickedSlot()\0"
    "includeFullHyphenatedWordOnlyRadioButtonClickedSlot()\0"
    "includeSubstringsOfHyphenatedWordOnlyRadioButtonClickedSlot()\0"
    "includeFullHyphenatedWordAndSubstringsRadioButtonClickedSlot()\0"
};

const QMetaObject PreferencesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PreferencesDialog,
      qt_meta_data_PreferencesDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PreferencesDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PreferencesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PreferencesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PreferencesDialog))
        return static_cast<void*>(const_cast< PreferencesDialog*>(this));
    if (!strcmp(_clname, "Ui::PreferencesDialogBase"))
        return static_cast< Ui::PreferencesDialogBase*>(const_cast< PreferencesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PreferencesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mhListBoxHighlightedSlot(); break;
        case 1: mhBoldCheckBoxClickedSlot(); break;
        case 2: mhItalicCheckBoxClickedSlot(); break;
        case 3: mhUnderlineCheckBoxClickedSlot(); break;
        case 4: mhColorButtonClickedSlot(); break;
        case 5: dsfFontButtonClickedSlot(); break;
        case 6: loadPrefsButtonClickedSlot(); break;
        case 7: savePrefsButtonClickedSlot(); break;
        case 8: notificationsCheckBoxClickedSlot(); break;
        case 9: sigDelimiterChangedSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: resetValuePushButtonClickedSlot(); break;
        case 11: resetAllValsPushButtonClickedSlot(); break;
        case 12: paramListItemRenamedSlot((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 13: help(); break;
        case 14: importRulesButtonClickedSlot(); break;
        case 15: exportRulesButtonClickedSlot(); break;
        case 16: makeLowerCaseCheckBoxToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: removeNumbersCheckBoxToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: removePrecedingPunctCheckBoxToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: removeInternalPunctCheckBoxToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: removeFollowingPunctCheckBoxToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: addNewReplacementButtonPressed(); break;
        case 22: moveUpButtonPressed(); break;
        case 23: moveDownButtonPressed(); break;
        case 24: removeReplacementButtonPressed(); break;
        case 25: scrubListBoxSelectionChanged(); break;
        case 26: replaceStringsChanged(); break;
        case 27: precedingPunctLineEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 28: internalPunctLineEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: followingPunctLineEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: newComboButtonClickedSlot(); break;
        case 31: removeComboButtonClickedSlot(); break;
        case 32: comboListBoxSelectionChangedSlot(); break;
        case 33: joinWithoutDashRadioButtonClickedSlot(); break;
        case 34: joinWithDashRadioButtonClickedSlot(); break;
        case 35: doNotJoinRadioButtonClickedSlot(); break;
        case 36: removeHyphenCheckBoxClickedSlot(); break;
        case 37: includeFullHyphenatedWordOnlyRadioButtonClickedSlot(); break;
        case 38: includeSubstringsOfHyphenatedWordOnlyRadioButtonClickedSlot(); break;
        case 39: includeFullHyphenatedWordAndSubstringsRadioButtonClickedSlot(); break;
        default: ;
        }
        _id -= 40;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
