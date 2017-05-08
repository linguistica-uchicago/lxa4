/****************************************************************************
** Meta object code from reading C++ file 'GraphicView.h'
**
** Created: Sun Apr 29 16:17:22 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GraphicView.h"
 
QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraphicView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      39,   12,   12,   12, 0x0a,
      55,   51,   12,   12, 0x0a,
     109,  104,   12,   12, 0x0a,
     143,  136,   12,   12, 0x0a,
     161,   12,   12,   12, 0x0a,
     171,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraphicView[] = {
    "GraphicView\0\0Properties()\0PlotStates()\0"
    "PlotStems()\0,,,\0"
    "PlotNVectors(int,int,double**,QMap<int,QString>)\0"
    "data\0PlotNVectors2(VideoFrame*)\0pVideo\0"
    "PlotVideo(Video*)\0Refresh()\0DisplayMe()\0"
};

const QMetaObject GraphicView::staticMetaObject = {
    { &Q3CanvasView::staticMetaObject, qt_meta_stringdata_GraphicView,
      qt_meta_data_GraphicView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraphicView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraphicView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraphicView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicView))
        return static_cast<void*>(const_cast< GraphicView*>(this));
    return Q3CanvasView::qt_metacast(_clname);
}

int GraphicView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3CanvasView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Properties(); break;
        case 1: PlotStates(); break;
        case 2: PlotStems(); break;
        case 3: PlotNVectors((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double**(*)>(_a[3])),(*reinterpret_cast< QMap<int,QString>(*)>(_a[4]))); break;
        case 4: PlotNVectors2((*reinterpret_cast< VideoFrame*(*)>(_a[1]))); break;
        case 5: PlotVideo((*reinterpret_cast< Video*(*)>(_a[1]))); break;
        case 6: Refresh(); break;
        case 7: DisplayMe(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
