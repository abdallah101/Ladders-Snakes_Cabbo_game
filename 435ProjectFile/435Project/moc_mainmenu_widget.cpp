/****************************************************************************
** Meta object code from reading C++ file 'mainmenu_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainmenu_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmenu_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainMenu_Widget_t {
    QByteArrayData data[9];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainMenu_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainMenu_Widget_t qt_meta_stringdata_MainMenu_Widget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MainMenu_Widget"
QT_MOC_LITERAL(1, 16, 18), // "Open_GameSelection"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "OpenRegisterMenu"
QT_MOC_LITERAL(4, 53, 13), // "keyPressEvent"
QT_MOC_LITERAL(5, 67, 10), // "QKeyEvent*"
QT_MOC_LITERAL(6, 78, 5), // "event"
QT_MOC_LITERAL(7, 84, 6), // "update"
QT_MOC_LITERAL(8, 91, 10) // "RegSuccess"

    },
    "MainMenu_Widget\0Open_GameSelection\0\0"
    "OpenRegisterMenu\0keyPressEvent\0"
    "QKeyEvent*\0event\0update\0RegSuccess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainMenu_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainMenu_Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainMenu_Widget *_t = static_cast<MainMenu_Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Open_GameSelection(); break;
        case 1: _t->OpenRegisterMenu(); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->update(); break;
        case 4: _t->RegSuccess(); break;
        default: ;
        }
    }
}

const QMetaObject MainMenu_Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainMenu_Widget.data,
      qt_meta_data_MainMenu_Widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainMenu_Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainMenu_Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenu_Widget.stringdata0))
        return static_cast<void*>(const_cast< MainMenu_Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainMenu_Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
