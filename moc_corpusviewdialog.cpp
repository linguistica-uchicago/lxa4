/****************************************************************************
** Meta object code from reading C++ file 'corpusviewdialog.h'
**
** Created: Sun Apr 29 16:17:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "corpusviewdialog.h"


QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CorpusViewDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      43,   41,   17,   17, 0x0a,
      66,   41,   17,   17, 0x0a,
      88,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CorpusViewDialog[] = {
    "CorpusViewDialog\0\0showMarkedUpText(bool)\0"
    ",\0moveRightView(int,int)\0moveLeftView(int,int)\0"
    "wordWrap(bool)\0"
};

const QMetaObject CorpusViewDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CorpusViewDialog,
      qt_meta_data_CorpusViewDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CorpusViewDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CorpusViewDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CorpusViewDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CorpusViewDialog))
        return static_cast<void*>(const_cast< CorpusViewDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CorpusViewDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showMarkedUpText((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: moveRightView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: moveLeftView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: wordWrap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
