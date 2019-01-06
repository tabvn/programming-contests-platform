/****************************************************************************
** Meta object code from reading C++ file 'dashboardwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dashboardwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dashboardwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DashboardWindow_t {
    QByteArrayData data[20];
    char stringdata0[478];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DashboardWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DashboardWindow_t qt_meta_stringdata_DashboardWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DashboardWindow"
QT_MOC_LITERAL(1, 16, 25), // "on_actionQuit_2_triggered"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 30), // "on_userTableWidget_itemChanged"
QT_MOC_LITERAL(4, 74, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(5, 92, 4), // "item"
QT_MOC_LITERAL(6, 97, 16), // "slotRemoveRecord"
QT_MOC_LITERAL(7, 114, 23), // "slotCustomMenuRequested"
QT_MOC_LITERAL(8, 138, 3), // "pos"
QT_MOC_LITERAL(9, 142, 36), // "on_maxScoreTextField_editingF..."
QT_MOC_LITERAL(10, 179, 35), // "on_problemTextField_editingFi..."
QT_MOC_LITERAL(11, 215, 39), // "on_memoryLimitTextField_editi..."
QT_MOC_LITERAL(12, 255, 35), // "on_descriptionTextField_textC..."
QT_MOC_LITERAL(13, 291, 30), // "on_deleteProblemButton_clicked"
QT_MOC_LITERAL(14, 322, 37), // "on_timelimitTextField_editing..."
QT_MOC_LITERAL(15, 360, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(16, 384, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(17, 408, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(18, 435, 37), // "on_problemComboBox_currentTex..."
QT_MOC_LITERAL(19, 473, 4) // "arg1"

    },
    "DashboardWindow\0on_actionQuit_2_triggered\0"
    "\0on_userTableWidget_itemChanged\0"
    "QTableWidgetItem*\0item\0slotRemoveRecord\0"
    "slotCustomMenuRequested\0pos\0"
    "on_maxScoreTextField_editingFinished\0"
    "on_problemTextField_editingFinished\0"
    "on_memoryLimitTextField_editingFinished\0"
    "on_descriptionTextField_textChanged\0"
    "on_deleteProblemButton_clicked\0"
    "on_timelimitTextField_editingFinished\0"
    "on_actionSave_triggered\0on_actionOpen_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_problemComboBox_currentTextChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DashboardWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    1,   85,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void DashboardWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DashboardWindow *_t = static_cast<DashboardWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionQuit_2_triggered(); break;
        case 1: _t->on_userTableWidget_itemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->slotRemoveRecord(); break;
        case 3: _t->slotCustomMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->on_maxScoreTextField_editingFinished(); break;
        case 5: _t->on_problemTextField_editingFinished(); break;
        case 6: _t->on_memoryLimitTextField_editingFinished(); break;
        case 7: _t->on_descriptionTextField_textChanged(); break;
        case 8: _t->on_deleteProblemButton_clicked(); break;
        case 9: _t->on_timelimitTextField_editingFinished(); break;
        case 10: _t->on_actionSave_triggered(); break;
        case 11: _t->on_actionOpen_triggered(); break;
        case 12: _t->on_actionSave_as_triggered(); break;
        case 13: _t->on_problemComboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DashboardWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_DashboardWindow.data,
    qt_meta_data_DashboardWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DashboardWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DashboardWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DashboardWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
