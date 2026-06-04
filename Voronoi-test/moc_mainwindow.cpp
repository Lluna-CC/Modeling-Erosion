/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "updateHeightfield",
        "",
        "resetCam",
        "setStatusText",
        "s",
        "updateLightmap",
        "updateTexture",
        "redrawBaseTexture",
        "modifyPalette",
        "resetPaletteRange",
        "computeVoronoi",
        "computeWaterPath",
        "changeRenderCells",
        "changeRenderParticles",
        "changeRenderOriginal",
        "changeRenderLinkViz",
        "changeRenderPathViz",
        "changeErosionDirection",
        "changeAlphaOirignal",
        "changeAlphaCells",
        "changeAlphaParticles",
        "changeAlphaLinks",
        "changeAlphaPaths",
        "changeRenderLayer",
        "loadPNG",
        "loadASC",
        "updateDEM",
        "recommendedDEM",
        "loadToy",
        "loadPreset",
        "updatePresetInfo",
        "saveLayersCombined",
        "saveLayerMetric",
        "saveLayerRivers",
        "saveLayerRidges",
        "saveMetric",
        "editFillDepressions",
        "editBreaching",
        "editGaussianSmooth",
        "queryRay",
        "Ray",
        "ray",
        "updateViewshedLocation"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'updateHeightfield'
        QtMocHelpers::SlotData<void(bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Slot 'updateHeightfield'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void),
        // Slot 'setStatusText'
        QtMocHelpers::SlotData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Slot 'updateLightmap'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateTexture'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'redrawBaseTexture'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'modifyPalette'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'resetPaletteRange'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'computeVoronoi'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'computeWaterPath'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeRenderCells'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeRenderParticles'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeRenderOriginal'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeRenderLinkViz'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeRenderPathViz'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeErosionDirection'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeAlphaOirignal'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeAlphaCells'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeAlphaParticles'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeAlphaLinks'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeAlphaPaths'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeRenderLayer'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadPNG'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadASC'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateDEM'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'recommendedDEM'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadToy'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadPreset'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updatePresetInfo'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveLayersCombined'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveLayerMetric'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveLayerRivers'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveLayerRidges'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveMetric'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'editFillDepressions'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'editBreaching'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'editGaussianSmooth'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'queryRay'
        QtMocHelpers::SlotData<void(const Ray &)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 41, 42 },
        }}),
        // Slot 'updateViewshedLocation'
        QtMocHelpers::SlotData<void()>(43, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->updateHeightfield((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->updateHeightfield(); break;
        case 2: _t->setStatusText((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->updateLightmap(); break;
        case 4: _t->updateTexture(); break;
        case 5: _t->redrawBaseTexture(); break;
        case 6: _t->modifyPalette(); break;
        case 7: _t->resetPaletteRange(); break;
        case 8: _t->computeVoronoi(); break;
        case 9: _t->computeWaterPath(); break;
        case 10: _t->changeRenderCells(); break;
        case 11: _t->changeRenderParticles(); break;
        case 12: _t->changeRenderOriginal(); break;
        case 13: _t->changeRenderLinkViz(); break;
        case 14: _t->changeRenderPathViz(); break;
        case 15: _t->changeErosionDirection(); break;
        case 16: _t->changeAlphaOirignal(); break;
        case 17: _t->changeAlphaCells(); break;
        case 18: _t->changeAlphaParticles(); break;
        case 19: _t->changeAlphaLinks(); break;
        case 20: _t->changeAlphaPaths(); break;
        case 21: _t->changeRenderLayer(); break;
        case 22: _t->loadPNG(); break;
        case 23: _t->loadASC(); break;
        case 24: _t->updateDEM(); break;
        case 25: _t->recommendedDEM(); break;
        case 26: _t->loadToy(); break;
        case 27: _t->loadPreset(); break;
        case 28: _t->updatePresetInfo(); break;
        case 29: _t->saveLayersCombined(); break;
        case 30: _t->saveLayerMetric(); break;
        case 31: _t->saveLayerRivers(); break;
        case 32: _t->saveLayerRidges(); break;
        case 33: _t->saveMetric(); break;
        case 34: _t->editFillDepressions(); break;
        case 35: _t->editBreaching(); break;
        case 36: _t->editGaussianSmooth(); break;
        case 37: _t->queryRay((*reinterpret_cast<std::add_pointer_t<Ray>>(_a[1]))); break;
        case 38: _t->updateViewshedLocation(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 39;
    }
    return _id;
}
QT_WARNING_POP
