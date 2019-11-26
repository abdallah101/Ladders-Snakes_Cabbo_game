/****************************************************************************
** Meta object code from reading C++ file 'game2_scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "game2_scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game2_scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_game2_scene_t {
    QByteArrayData data[16];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_game2_scene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_game2_scene_t qt_meta_stringdata_game2_scene = {
    {
QT_MOC_LITERAL(0, 0, 11), // "game2_scene"
QT_MOC_LITERAL(1, 12, 7), // "setUser"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 1), // "a"
QT_MOC_LITERAL(4, 23, 12), // "startingTurn"
QT_MOC_LITERAL(5, 36, 6), // "change"
QT_MOC_LITERAL(6, 43, 6), // "update"
QT_MOC_LITERAL(7, 50, 9), // "swapCards"
QT_MOC_LITERAL(8, 60, 5), // "first"
QT_MOC_LITERAL(9, 66, 6), // "second"
QT_MOC_LITERAL(10, 73, 11), // "player2turn"
QT_MOC_LITERAL(11, 85, 11), // "player3turn"
QT_MOC_LITERAL(12, 97, 9), // "delayfunc"
QT_MOC_LITERAL(13, 107, 11), // "ReactToSwap"
QT_MOC_LITERAL(14, 119, 14), // "ReactToSwapOne"
QT_MOC_LITERAL(15, 134, 7) // "initial"

    },
    "game2_scene\0setUser\0\0a\0startingTurn\0"
    "change\0update\0swapCards\0first\0second\0"
    "player2turn\0player3turn\0delayfunc\0"
    "ReactToSwap\0ReactToSwapOne\0initial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_game2_scene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       4,    0,   72,    2, 0x0a /* Public */,
       5,    0,   73,    2, 0x0a /* Public */,
       6,    0,   74,    2, 0x0a /* Public */,
       7,    2,   75,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    0,   82,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,
      14,    0,   84,    2, 0x0a /* Public */,
      15,    0,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void game2_scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        game2_scene *_t = static_cast<game2_scene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->startingTurn(); break;
        case 2: _t->change(); break;
        case 3: _t->update(); break;
        case 4: _t->swapCards((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->player2turn(); break;
        case 6: _t->player3turn(); break;
        case 7: _t->delayfunc(); break;
        case 8: _t->ReactToSwap(); break;
        case 9: _t->ReactToSwapOne(); break;
        case 10: _t->initial(); break;
        default: ;
        }
    }
}

const QMetaObject game2_scene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_game2_scene.data,
      qt_meta_data_game2_scene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *game2_scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *game2_scene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_game2_scene.stringdata0))
        return static_cast<void*>(const_cast< game2_scene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int game2_scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
