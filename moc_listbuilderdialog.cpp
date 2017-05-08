/****************************************************************************
** Meta object code from reading C++ file 'listbuilderdialog.h'
**
** Created: Sun Apr 29 16:17:24 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "listbuilderdialog.h"
 

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ListBuilderDialog[] = {

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
      19,   18,   18,   18, 0x0a,
      52,   18,   18,   18, 0x0a,
      70,   18,   18,   18, 0x0a,
     106,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ListBuilderDialog[] = {
    "ListBuilderDialog\0\0addListItemSlot(Q3ListViewItem*)\0"
    "addListItemSlot()\0removeListItemSlot(Q3ListViewItem*)\0"
    "removeListItemSlot()\0"
};

const QMetaObject ListBuilderDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ListBuilderDialog,
      qt_meta_data_ListBuilderDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ListBuilderDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ListBuilderDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ListBuilderDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ListBuilderDialog))
        return static_cast<void*>(const_cast< ListBuilderDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ListBuilderDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addListItemSlot((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 1: addListItemSlot(); break;
        case 2: removeListItemSlot((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 3: removeListItemSlot(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
