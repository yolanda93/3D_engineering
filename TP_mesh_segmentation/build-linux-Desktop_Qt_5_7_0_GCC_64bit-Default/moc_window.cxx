/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../linux/window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   12,   11,   11, 0x0a,
      45,   11,   11,   11, 0x2a,
      73,   64,   11,   11, 0x0a,
      87,   64,   11,   11, 0x0a,
     106,   11,   11,   11, 0x0a,
     161,   11,   11,   11, 0x09,
     168,   11,   11,   11, 0x09,
     183,   11,   11,   11, 0x09,
     205,  199,   11,   11, 0x09,
     228,  199,   11,   11, 0x09,
     253,  199,   11,   11, 0x09,
     286,   11,   11,   11, 0x09,
     319,   11,   11,   11, 0x09,
     350,   11,   11,   11, 0x09,
     385,   11,   11,   11, 0x09,
     420,   11,   11,   11, 0x09,
     452,   11,   11,   11, 0x09,
     485,   11,   11,   11, 0x09,
     517,   11,   11,   11, 0x09,
     553,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0input_type\0updateViewerBBox(int)\0"
    "updateViewerBBox()\0filename\0open(QString)\0"
    "open_mesh(QString)\0"
    "setAddKeyFrameKeyboardModifiers(Qt::KeyboardModifiers)\0"
    "quit()\0readSettings()\0writeSettings()\0"
    "event\0dropEvent(QDropEvent*)\0"
    "closeEvent(QCloseEvent*)\0"
    "dragEnterEvent(QDragEnterEvent*)\0"
    "on_actionLoad_points_triggered()\0"
    "on_actionLoad_mesh_triggered()\0"
    "on_actionCopy_snapshot_triggered()\0"
    "on_actionSave_snapshot_triggered()\0"
    "on_actionView_edges_triggered()\0"
    "on_actionView_points_triggered()\0"
    "on_actionParameters_triggered()\0"
    "on_actionClassification_triggered()\0"
    "on_actionPlane_Extraction_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->updateViewerBBox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateViewerBBox(); break;
        case 2: _t->open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->open_mesh((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setAddKeyFrameKeyboardModifiers((*reinterpret_cast< Qt::KeyboardModifiers(*)>(_a[1]))); break;
        case 5: _t->quit(); break;
        case 6: _t->readSettings(); break;
        case 7: _t->writeSettings(); break;
        case 8: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 9: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 10: _t->dragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 11: _t->on_actionLoad_points_triggered(); break;
        case 12: _t->on_actionLoad_mesh_triggered(); break;
        case 13: _t->on_actionCopy_snapshot_triggered(); break;
        case 14: _t->on_actionSave_snapshot_triggered(); break;
        case 15: _t->on_actionView_edges_triggered(); break;
        case 16: _t->on_actionView_points_triggered(); break;
        case 17: _t->on_actionParameters_triggered(); break;
        case 18: _t->on_actionClassification_triggered(); break;
        case 19: _t->on_actionPlane_Extraction_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &CGAL::Qt::DemosMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    typedef CGAL::Qt::DemosMainWindow QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef CGAL::Qt::DemosMainWindow QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
