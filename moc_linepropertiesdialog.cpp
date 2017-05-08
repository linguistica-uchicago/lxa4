/****************************************************************************
** Meta object code from reading C++ file 'linepropertiesdialog.h'
**
** Created: Sun Apr 29 16:17:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "linepropertiesdialog.h"
 

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LinePropertiesDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   22,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LinePropertiesDialog[] = {
    "LinePropertiesDialog\0\0item\0"
    "exec(Q3CanvasItem*)\0"
};

const QMetaObject LinePropertiesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LinePropertiesDialog,
      qt_meta_data_LinePropertiesDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LinePropertiesDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LinePropertiesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LinePropertiesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LinePropertiesDialog))
        return static_cast<void*>(const_cast< LinePropertiesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LinePropertiesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: exec((*reinterpret_cast< Q3CanvasItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
