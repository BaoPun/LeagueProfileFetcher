/****************************************************************************
** Meta object code from reading C++ file 'ApiProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LeagueProfileFetcher/ApiProcessor.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApiProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSApiProcessorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSApiProcessorENDCLASS = QtMocHelpers::stringData(
    "ApiProcessor",
    "read_data",
    "",
    "retrieve_data",
    "open_secondary_window",
    "add_image_from_api",
    "vector<QImage>&",
    "open_champion_window"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSApiProcessorENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[13];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[22];
    char stringdata5[19];
    char stringdata6[16];
    char stringdata7[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSApiProcessorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSApiProcessorENDCLASS_t qt_meta_stringdata_CLASSApiProcessorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ApiProcessor"
        QT_MOC_LITERAL(13, 9),  // "read_data"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 13),  // "retrieve_data"
        QT_MOC_LITERAL(38, 21),  // "open_secondary_window"
        QT_MOC_LITERAL(60, 18),  // "add_image_from_api"
        QT_MOC_LITERAL(79, 15),  // "vector<QImage>&"
        QT_MOC_LITERAL(95, 20)   // "open_champion_window"
    },
    "ApiProcessor",
    "read_data",
    "",
    "retrieve_data",
    "open_secondary_window",
    "add_image_from_api",
    "vector<QImage>&",
    "open_champion_window"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSApiProcessorENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    1,   45,    2, 0x08,    2 /* Private */,
       4,    0,   48,    2, 0x08,    4 /* Private */,
       5,    1,   49,    2, 0x08,    5 /* Private */,
       7,    1,   52,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject ApiProcessor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSApiProcessorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSApiProcessorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSApiProcessorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ApiProcessor, std::true_type>,
        // method 'read_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'retrieve_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'open_secondary_window'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'add_image_from_api'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<vector<QImage> &, std::false_type>,
        // method 'open_champion_window'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void ApiProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiProcessor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->read_data(); break;
        case 1: _t->retrieve_data((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->open_secondary_window(); break;
        case 3: _t->add_image_from_api((*reinterpret_cast< std::add_pointer_t<vector<QImage>&>>(_a[1]))); break;
        case 4: _t->open_champion_window((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ApiProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSApiProcessorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApiProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
