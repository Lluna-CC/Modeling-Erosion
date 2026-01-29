/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadPNG;
    QAction *actionLoadASC;
    QAction *actionSaveTexture;
    QAction *actionSaveLayerMetric;
    QAction *actionSaveMetric;
    QAction *actionSaveLayerRivers;
    QAction *actionSaveLayerRidges;
    QWidget *centralwidget;
    QGridLayout *gridLayout_12;
    QFrame *frameL;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *Objects_groupBox_2;
    QVBoxLayout *verticalLayout_10;
    QComboBox *cb_preset;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_48;
    QLabel *label_preset;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_58;
    QDoubleSpinBox *sb_presetFactor;
    QPushButton *btn_loadPreset;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QDoubleSpinBox *hf_elevMin;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_7;
    QDoubleSpinBox *hf_elevMax;
    QSpinBox *hf_gridY;
    QDoubleSpinBox *hf_kmY;
    QLabel *label_8;
    QLabel *label_12;
    QLabel *label_10;
    QDoubleSpinBox *hf_kmX;
    QSpinBox *hf_gridX;
    QLabel *label_4;
    QLabel *label_cellSize;
    QPushButton *btn_updateDEM;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_fillDepressions;
    QPushButton *btn_breaching;
    QGridLayout *gridLayout_6;
    QPushButton *btn_gaussianSmooth;
    QSpinBox *sb_gaussianBlur_radius;
    QLabel *label_21;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *light_altitude;
    QLabel *label_44;
    QDoubleSpinBox *light_azimuth;
    QLabel *label_43;
    QCheckBox *dem_shadows;
    QCheckBox *dem_shading;
    QGroupBox *groupBox_palette;
    QGridLayout *gridLayout_11;
    QComboBox *cb_palette;
    QDoubleSpinBox *sb_paletteMax;
    QCheckBox *fixed_palette;
    QLabel *labelPaletteRange;
    QDoubleSpinBox *sb_paletteMin;
    QPushButton *btn_resetPaletteRange;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLabel *label_27;
    QLineEdit *lineClickInfoCell;
    QLabel *label_26;
    QLineEdit *lineClickInfoElev;
    QLabel *label_30;
    QLineEdit *lineClickInfoMetric;
    QSpacerItem *verticalSpacer;
    QWidget *glWidget;
    QTabWidget *tabWidgetR;
    QWidget *tabDEM;
    QVBoxLayout *verticalLayout_15;
    QToolBox *demToolbox;
    QWidget *pageMorhology;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *dem_uniform;
    QRadioButton *dem_elevation;
    QHBoxLayout *horizontalLayout_39;
    QRadioButton *dem_waterlevel;
    QDoubleSpinBox *dem_waterlevel_m;
    QCheckBox *dem_waterlevel_relief;
    QFrame *line_18;
    QRadioButton *dem_normals;
    QRadioButton *dem_slopeGradient;
    QRadioButton *dem_slopeAvg;
    QRadioButton *dem_aspect;
    QRadioButton *dem_aspect_east;
    QRadioButton *dem_aspect_north;
    QFrame *line_19;
    QRadioButton *dem_laplacian;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *dem_fractLaplacian;
    QHBoxLayout *horizontalLayout_19;
    QDoubleSpinBox *dem_fractLaplacian_s;
    QSpinBox *dem_fractLaplacian_n;
    QFrame *line_20;
    QRadioButton *dem_asymmetry;
    QHBoxLayout *horizontalLayout;
    QSpinBox *dem_asymmetryW;
    QDoubleSpinBox *dem_asymmetryDir;
    QLabel *label_33;
    QDoubleSpinBox *dem_asymmetryDirTol;
    QSpacerItem *verticalSpacer_8;
    QWidget *pageCurvatures;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *dem_curv_fromQuadrics;
    QSpinBox *dem_curv_fromQuadrics_w;
    QLabel *label_14;
    QRadioButton *dem_curvMin;
    QRadioButton *dem_curvMax;
    QRadioButton *dem_curvMean;
    QRadioButton *dem_curvGaussian;
    QRadioButton *dem_curvProfile;
    QRadioButton *dem_curvContour;
    QRadioButton *dem_curvTangent;
    QSpacerItem *verticalSpacer_7;
    QWidget *pageRelief;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_demRelief_radius;
    QSpinBox *dem_localRelief_w;
    QLabel *label_18;
    QRadioButton *dem_tpi;
    QRadioButton *dem_localRelief;
    QRadioButton *dem_localVariance;
    QRadioButton *dem_areaRatio;
    QRadioButton *dem_ruggedness;
    QRadioButton *dem_surfaceRoughness;
    QRadioButton *dem_surfaceRoughnessStd;
    QSpacerItem *verticalSpacer_2;
    QWidget *pageVisibility;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_54;
    QDoubleSpinBox *viewshed_offset;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_23;
    QDoubleSpinBox *viewshed_rescale;
    QRadioButton *dem_viewshedLoc;
    QHBoxLayout *horizontalLayout_17;
    QSpinBox *viewshed_location_x;
    QSpinBox *viewshed_location_y;
    QPushButton *btn_pickViewshedLocation;
    QRadioButton *dem_viewshedTotalOut;
    QRadioButton *dem_viewshedTotalIn;
    QHBoxLayout *horizontalLayout_43;
    QCheckBox *dem_viewshedTotal_sample;
    QSpinBox *dem_viewshedTotal_numSamples;
    QFrame *line_12;
    QHBoxLayout *horizontalLayout_53;
    QRadioButton *dem_posOpenness;
    QRadioButton *dem_negOpenness;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_47;
    QSpinBox *dem_opennessDirs;
    QLabel *label_55;
    QHBoxLayout *horizontalLayout_49;
    QSpinBox *dem_opennessDist;
    QLabel *label_56;
    QFrame *line_15;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_51;
    QSpinBox *dem_accessibilitySamples;
    QLabel *label_17;
    QDoubleSpinBox *dem_accessibilityRadius;
    QRadioButton *dem_accessibility;
    QRadioButton *dem_skyview;
    QRadioButton *dem_skyviewApprox;
    QFrame *line_16;
    QHBoxLayout *horizontalLayout_51;
    QRadioButton *dem_sunlight;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *dem_sunlightLatitude;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_52;
    QRadioButton *dem_dahi;
    QHBoxLayout *horizontalLayout_28;
    QSpinBox *dem_dahiMax;
    QLabel *label_32;
    QSpacerItem *verticalSpacer_11;
    QWidget *pageLandforms;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *dem_showSingleLandform;
    QSpinBox *dem_showSingleLandform_id;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_25;
    QLabel *dem_landformName;
    QFrame *line;
    QGridLayout *gridLayout_4;
    QRadioButton *dem_dikauWoodClass;
    QHBoxLayout *horizontalLayout_13;
    QSpinBox *dem_dikauWoodSolver_w;
    QLabel *label_22;
    QRadioButton *dem_fisher2004;
    QHBoxLayout *horizontalLayout_29;
    QSpinBox *dem_fisher2004_minScale;
    QLabel *label_31;
    QSpinBox *dem_fisher2004_maxScale;
    QRadioButton *dem_fisher2004entropy;
    QRadioButton *dem_tpiClass;
    QHBoxLayout *horizontalLayout_24;
    QSpinBox *dem_tpiClassSmall;
    QLabel *label_34;
    QSpinBox *dem_tpiClassLarge;
    QRadioButton *dem_geomorphons;
    QHBoxLayout *horizontalLayout_20;
    QDoubleSpinBox *dem_geomorphons_km;
    QLabel *label;
    QRadioButton *dem_tophat;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_14;
    QSpinBox *dem_tophat_w;
    QLabel *label_28;
    QLabel *label_16;
    QDoubleSpinBox *dem_tophat_peak;
    QDoubleSpinBox *dem_tophat_valley;
    QSpacerItem *verticalSpacer_10;
    QWidget *pageFlow;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_8;
    QLabel *label_13;
    QComboBox *dem_streamArea_flowAlgorithm;
    QLabel *label_29;
    QDoubleSpinBox *dem_streamArea_mfdExp;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_3;
    QSpinBox *dem_streamArea_rho8iters;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *dem_streamArea_uniqueSource;
    QHBoxLayout *horizontalLayout_40;
    QSpinBox *dem_streamArea_source_x;
    QSpinBox *dem_streamArea_source_y;
    QPushButton *btn_pickStreamAreaSource;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *dem_streamArea;
    QLabel *label_6;
    QDoubleSpinBox *dem_streamArea_exp;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *dem_streamAreaLog;
    QRadioButton *dem_wetness;
    QHBoxLayout *horizontalLayout_35;
    QRadioButton *dem_streamPower;
    QLabel *label_39;
    QDoubleSpinBox *dem_streamPower_m;
    QLabel *label_40;
    QDoubleSpinBox *dem_streamPower_n;
    QHBoxLayout *horizontalLayout_30;
    QCheckBox *dem_streamPower_threshold;
    QDoubleSpinBox *dem_streamPower_t;
    QFrame *line_4;
    QLabel *label_35;
    QRadioButton *dem_depthToWater;
    QRadioButton *dem_hand;
    QRadioButton *dem_riverDistEuclidean;
    QRadioButton *dem_riverDistFlow;
    QHBoxLayout *horizontalLayout_34;
    QRadioButton *dem_branchLength;
    QLabel *label_38;
    QDoubleSpinBox *dem_branchLength_exp;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_9;
    QWidget *pageOrometry;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_15;
    QDoubleSpinBox *dem_orometryRadius;
    QRadioButton *dem_peakedness;
    QRadioButton *dem_ors;
    QGridLayout *gridLayout_3;
    QRadioButton *dem_jut;
    QCheckBox *dem_jut_curvature;
    QRadioButton *dem_rut;
    QRadioButton *dem_zreduced_converging;
    QRadioButton *dem_zreduced_diverging;
    QLabel *label_46;
    QLabel *label_50;
    QSpinBox *dem_zreduced_x;
    QSpinBox *dem_zreduced_y;
    QDoubleSpinBox *dem_jut_planetR;
    QPushButton *btn_pickZReduced;
    QFrame *line_5;
    QGridLayout *gridLayout_9;
    QRadioButton *dem_deng2008_peakProto;
    QRadioButton *dem_deng2008_peakSimil;
    QDoubleSpinBox *dem_deng2008_peakPercent;
    QLabel *label_20;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *dem_nni;
    QDoubleSpinBox *dem_nni_radius;
    QHBoxLayout *horizontalLayout_46;
    QCheckBox *dem_nni_relative;
    QLabel *labelTerrainNNI;
    QLabel *label_53;
    QSpacerItem *verticalSpacer_3;
    QWidget *tabVoro;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuSave;
    QMenu *menuLoad;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1860, 980);
        MainWindow->setMinimumSize(QSize(420, 300));
        actionLoadPNG = new QAction(MainWindow);
        actionLoadPNG->setObjectName("actionLoadPNG");
        actionLoadASC = new QAction(MainWindow);
        actionLoadASC->setObjectName("actionLoadASC");
        actionSaveTexture = new QAction(MainWindow);
        actionSaveTexture->setObjectName("actionSaveTexture");
        actionSaveLayerMetric = new QAction(MainWindow);
        actionSaveLayerMetric->setObjectName("actionSaveLayerMetric");
        actionSaveMetric = new QAction(MainWindow);
        actionSaveMetric->setObjectName("actionSaveMetric");
        actionSaveLayerRivers = new QAction(MainWindow);
        actionSaveLayerRivers->setObjectName("actionSaveLayerRivers");
        actionSaveLayerRidges = new QAction(MainWindow);
        actionSaveLayerRidges->setObjectName("actionSaveLayerRidges");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_12 = new QGridLayout(centralwidget);
        gridLayout_12->setObjectName("gridLayout_12");
        frameL = new QFrame(centralwidget);
        frameL->setObjectName("frameL");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameL->sizePolicy().hasHeightForWidth());
        frameL->setSizePolicy(sizePolicy);
        frameL->setMinimumSize(QSize(300, 0));
        verticalLayout_16 = new QVBoxLayout(frameL);
        verticalLayout_16->setObjectName("verticalLayout_16");
        Objects_groupBox_2 = new QGroupBox(frameL);
        Objects_groupBox_2->setObjectName("Objects_groupBox_2");
        Objects_groupBox_2->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Objects_groupBox_2->sizePolicy().hasHeightForWidth());
        Objects_groupBox_2->setSizePolicy(sizePolicy1);
        Objects_groupBox_2->setFlat(false);
        verticalLayout_10 = new QVBoxLayout(Objects_groupBox_2);
        verticalLayout_10->setObjectName("verticalLayout_10");
        cb_preset = new QComboBox(Objects_groupBox_2);
        cb_preset->setObjectName("cb_preset");

        verticalLayout_10->addWidget(cb_preset);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName("horizontalLayout_37");
        label_48 = new QLabel(Objects_groupBox_2);
        label_48->setObjectName("label_48");

        horizontalLayout_37->addWidget(label_48);

        label_preset = new QLabel(Objects_groupBox_2);
        label_preset->setObjectName("label_preset");

        horizontalLayout_37->addWidget(label_preset);


        verticalLayout_10->addLayout(horizontalLayout_37);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName("horizontalLayout_31");
        label_58 = new QLabel(Objects_groupBox_2);
        label_58->setObjectName("label_58");

        horizontalLayout_31->addWidget(label_58);

        sb_presetFactor = new QDoubleSpinBox(Objects_groupBox_2);
        sb_presetFactor->setObjectName("sb_presetFactor");
        sb_presetFactor->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        sb_presetFactor->setMaximum(1.000000000000000);
        sb_presetFactor->setSingleStep(0.050000000000000);
        sb_presetFactor->setValue(1.000000000000000);

        horizontalLayout_31->addWidget(sb_presetFactor);


        verticalLayout_10->addLayout(horizontalLayout_31);

        btn_loadPreset = new QPushButton(Objects_groupBox_2);
        btn_loadPreset->setObjectName("btn_loadPreset");

        verticalLayout_10->addWidget(btn_loadPreset);


        verticalLayout_16->addWidget(Objects_groupBox_2);

        groupBox_3 = new QGroupBox(frameL);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        hf_elevMin = new QDoubleSpinBox(groupBox_3);
        hf_elevMin->setObjectName("hf_elevMin");
        hf_elevMin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        hf_elevMin->setDecimals(1);
        hf_elevMin->setMinimum(-10000.000000000000000);
        hf_elevMin->setMaximum(10000.000000000000000);
        hf_elevMin->setSingleStep(50.000000000000000);
        hf_elevMin->setValue(0.000000000000000);

        gridLayout->addWidget(hf_elevMin, 2, 1, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");
        label_9->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_11, 1, 2, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        hf_elevMax = new QDoubleSpinBox(groupBox_3);
        hf_elevMax->setObjectName("hf_elevMax");
        hf_elevMax->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        hf_elevMax->setDecimals(1);
        hf_elevMax->setMaximum(20000.000000000000000);
        hf_elevMax->setSingleStep(50.000000000000000);
        hf_elevMax->setValue(3500.000000000000000);

        gridLayout->addWidget(hf_elevMax, 2, 3, 1, 1);

        hf_gridY = new QSpinBox(groupBox_3);
        hf_gridY->setObjectName("hf_gridY");
        hf_gridY->setMinimumSize(QSize(80, 0));
        hf_gridY->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        hf_gridY->setMaximum(10000);
        hf_gridY->setSingleStep(10);
        hf_gridY->setValue(1200);

        gridLayout->addWidget(hf_gridY, 0, 3, 1, 1);

        hf_kmY = new QDoubleSpinBox(groupBox_3);
        hf_kmY->setObjectName("hf_kmY");
        hf_kmY->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        hf_kmY->setDecimals(1);
        hf_kmY->setMaximum(10000.000000000000000);
        hf_kmY->setValue(60.000000000000000);

        gridLayout->addWidget(hf_kmY, 1, 3, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName("label_12");
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_12, 2, 2, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");
        label_10->setMaximumSize(QSize(10, 16777215));
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_10, 0, 2, 1, 1);

        hf_kmX = new QDoubleSpinBox(groupBox_3);
        hf_kmX->setObjectName("hf_kmX");
        hf_kmX->setMinimumSize(QSize(8, 0));
        hf_kmX->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        hf_kmX->setDecimals(1);
        hf_kmX->setMaximum(10000.000000000000000);
        hf_kmX->setValue(60.000000000000000);

        gridLayout->addWidget(hf_kmX, 1, 1, 1, 1);

        hf_gridX = new QSpinBox(groupBox_3);
        hf_gridX->setObjectName("hf_gridX");
        hf_gridX->setMinimumSize(QSize(90, 0));
        hf_gridX->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        hf_gridX->setMaximum(10000);
        hf_gridX->setSingleStep(10);
        hf_gridX->setValue(1200);

        gridLayout->addWidget(hf_gridX, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_cellSize = new QLabel(groupBox_3);
        label_cellSize->setObjectName("label_cellSize");

        gridLayout->addWidget(label_cellSize, 3, 1, 1, 3);

        btn_updateDEM = new QPushButton(groupBox_3);
        btn_updateDEM->setObjectName("btn_updateDEM");
        btn_updateDEM->setMaximumSize(QSize(16777215, 24));

        gridLayout->addWidget(btn_updateDEM, 4, 0, 1, 4);


        verticalLayout_3->addLayout(gridLayout);


        verticalLayout_16->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(frameL);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName("verticalLayout");
        btn_fillDepressions = new QPushButton(groupBox_4);
        btn_fillDepressions->setObjectName("btn_fillDepressions");
        btn_fillDepressions->setCheckable(false);

        verticalLayout->addWidget(btn_fillDepressions);

        btn_breaching = new QPushButton(groupBox_4);
        btn_breaching->setObjectName("btn_breaching");
        btn_breaching->setCheckable(false);

        verticalLayout->addWidget(btn_breaching);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        btn_gaussianSmooth = new QPushButton(groupBox_4);
        btn_gaussianSmooth->setObjectName("btn_gaussianSmooth");

        gridLayout_6->addWidget(btn_gaussianSmooth, 0, 0, 1, 1);

        sb_gaussianBlur_radius = new QSpinBox(groupBox_4);
        sb_gaussianBlur_radius->setObjectName("sb_gaussianBlur_radius");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sb_gaussianBlur_radius->sizePolicy().hasHeightForWidth());
        sb_gaussianBlur_radius->setSizePolicy(sizePolicy2);
        sb_gaussianBlur_radius->setMinimumSize(QSize(64, 0));
        sb_gaussianBlur_radius->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        sb_gaussianBlur_radius->setMaximum(1000);
        sb_gaussianBlur_radius->setValue(2);

        gridLayout_6->addWidget(sb_gaussianBlur_radius, 0, 2, 1, 1);

        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName("label_21");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy3);

        gridLayout_6->addWidget(label_21, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_6);


        verticalLayout_16->addWidget(groupBox_4);

        groupBox_9 = new QGroupBox(frameL);
        groupBox_9->setObjectName("groupBox_9");
        gridLayout_2 = new QGridLayout(groupBox_9);
        gridLayout_2->setObjectName("gridLayout_2");
        light_altitude = new QDoubleSpinBox(groupBox_9);
        light_altitude->setObjectName("light_altitude");
        light_altitude->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        light_altitude->setDecimals(1);
        light_altitude->setMaximum(90.000000000000000);
        light_altitude->setSingleStep(5.000000000000000);
        light_altitude->setValue(60.000000000000000);

        gridLayout_2->addWidget(light_altitude, 1, 3, 1, 1);

        label_44 = new QLabel(groupBox_9);
        label_44->setObjectName("label_44");

        gridLayout_2->addWidget(label_44, 1, 2, 1, 1);

        light_azimuth = new QDoubleSpinBox(groupBox_9);
        light_azimuth->setObjectName("light_azimuth");
        light_azimuth->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        light_azimuth->setDecimals(1);
        light_azimuth->setMaximum(360.000000000000000);
        light_azimuth->setSingleStep(15.000000000000000);
        light_azimuth->setValue(315.000000000000000);

        gridLayout_2->addWidget(light_azimuth, 1, 1, 1, 1);

        label_43 = new QLabel(groupBox_9);
        label_43->setObjectName("label_43");

        gridLayout_2->addWidget(label_43, 1, 0, 1, 1);

        dem_shadows = new QCheckBox(groupBox_9);
        dem_shadows->setObjectName("dem_shadows");

        gridLayout_2->addWidget(dem_shadows, 0, 2, 1, 2);

        dem_shading = new QCheckBox(groupBox_9);
        dem_shading->setObjectName("dem_shading");
        dem_shading->setChecked(true);

        gridLayout_2->addWidget(dem_shading, 0, 0, 1, 2);


        verticalLayout_16->addWidget(groupBox_9);

        groupBox_palette = new QGroupBox(frameL);
        groupBox_palette->setObjectName("groupBox_palette");
        gridLayout_11 = new QGridLayout(groupBox_palette);
        gridLayout_11->setObjectName("gridLayout_11");
        cb_palette = new QComboBox(groupBox_palette);
        cb_palette->addItem(QString());
        cb_palette->addItem(QString());
        cb_palette->addItem(QString());
        cb_palette->setObjectName("cb_palette");

        gridLayout_11->addWidget(cb_palette, 0, 1, 1, 3);

        sb_paletteMax = new QDoubleSpinBox(groupBox_palette);
        sb_paletteMax->setObjectName("sb_paletteMax");
        sb_paletteMax->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        sb_paletteMax->setDecimals(3);
        sb_paletteMax->setMaximum(1.000000000000000);
        sb_paletteMax->setStepType(QAbstractSpinBox::StepType::AdaptiveDecimalStepType);
        sb_paletteMax->setValue(1.000000000000000);

        gridLayout_11->addWidget(sb_paletteMax, 1, 2, 1, 1);

        fixed_palette = new QCheckBox(groupBox_palette);
        fixed_palette->setObjectName("fixed_palette");
        fixed_palette->setChecked(true);

        gridLayout_11->addWidget(fixed_palette, 0, 0, 1, 1);

        labelPaletteRange = new QLabel(groupBox_palette);
        labelPaletteRange->setObjectName("labelPaletteRange");
        labelPaletteRange->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_11->addWidget(labelPaletteRange, 1, 0, 1, 1);

        sb_paletteMin = new QDoubleSpinBox(groupBox_palette);
        sb_paletteMin->setObjectName("sb_paletteMin");
        sb_paletteMin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        sb_paletteMin->setDecimals(3);
        sb_paletteMin->setMaximum(1.000000000000000);
        sb_paletteMin->setStepType(QAbstractSpinBox::StepType::AdaptiveDecimalStepType);

        gridLayout_11->addWidget(sb_paletteMin, 1, 1, 1, 1);

        btn_resetPaletteRange = new QPushButton(groupBox_palette);
        btn_resetPaletteRange->setObjectName("btn_resetPaletteRange");
        sizePolicy2.setHeightForWidth(btn_resetPaletteRange->sizePolicy().hasHeightForWidth());
        btn_resetPaletteRange->setSizePolicy(sizePolicy2);
        btn_resetPaletteRange->setMinimumSize(QSize(24, 24));
        btn_resetPaletteRange->setMaximumSize(QSize(24, 24));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        btn_resetPaletteRange->setFont(font);
        btn_resetPaletteRange->setText(QString::fromUtf8("\342\206\251\357\270\216"));

        gridLayout_11->addWidget(btn_resetPaletteRange, 1, 3, 1, 1);


        verticalLayout_16->addWidget(groupBox_palette);

        groupBox_2 = new QGroupBox(frameL);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName("gridLayout_5");
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName("label_27");

        gridLayout_5->addWidget(label_27, 0, 0, 1, 1);

        lineClickInfoCell = new QLineEdit(groupBox_2);
        lineClickInfoCell->setObjectName("lineClickInfoCell");
        lineClickInfoCell->setReadOnly(true);

        gridLayout_5->addWidget(lineClickInfoCell, 0, 1, 1, 1);

        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName("label_26");

        gridLayout_5->addWidget(label_26, 1, 0, 1, 1);

        lineClickInfoElev = new QLineEdit(groupBox_2);
        lineClickInfoElev->setObjectName("lineClickInfoElev");
        lineClickInfoElev->setReadOnly(true);

        gridLayout_5->addWidget(lineClickInfoElev, 1, 1, 1, 1);

        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName("label_30");

        gridLayout_5->addWidget(label_30, 2, 0, 1, 1);

        lineClickInfoMetric = new QLineEdit(groupBox_2);
        lineClickInfoMetric->setObjectName("lineClickInfoMetric");
        lineClickInfoMetric->setReadOnly(true);

        gridLayout_5->addWidget(lineClickInfoMetric, 2, 1, 1, 1);


        verticalLayout_16->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 121, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_16->addItem(verticalSpacer);


        gridLayout_12->addWidget(frameL, 0, 0, 1, 1);

        glWidget = new QWidget(centralwidget);
        glWidget->setObjectName("glWidget");
        glWidget->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(glWidget->sizePolicy().hasHeightForWidth());
        glWidget->setSizePolicy(sizePolicy4);

        gridLayout_12->addWidget(glWidget, 0, 1, 1, 1);

        tabWidgetR = new QTabWidget(centralwidget);
        tabWidgetR->setObjectName("tabWidgetR");
        sizePolicy.setHeightForWidth(tabWidgetR->sizePolicy().hasHeightForWidth());
        tabWidgetR->setSizePolicy(sizePolicy);
        tabWidgetR->setMinimumSize(QSize(320, 0));
        tabDEM = new QWidget();
        tabDEM->setObjectName("tabDEM");
        verticalLayout_15 = new QVBoxLayout(tabDEM);
        verticalLayout_15->setObjectName("verticalLayout_15");
        demToolbox = new QToolBox(tabDEM);
        demToolbox->setObjectName("demToolbox");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(demToolbox->sizePolicy().hasHeightForWidth());
        demToolbox->setSizePolicy(sizePolicy5);
        pageMorhology = new QWidget();
        pageMorhology->setObjectName("pageMorhology");
        pageMorhology->setGeometry(QRect(0, 0, 316, 472));
        verticalLayout_11 = new QVBoxLayout(pageMorhology);
        verticalLayout_11->setObjectName("verticalLayout_11");
        dem_uniform = new QRadioButton(pageMorhology);
        dem_uniform->setObjectName("dem_uniform");
        dem_uniform->setChecked(true);

        verticalLayout_11->addWidget(dem_uniform);

        dem_elevation = new QRadioButton(pageMorhology);
        dem_elevation->setObjectName("dem_elevation");
        dem_elevation->setChecked(false);

        verticalLayout_11->addWidget(dem_elevation);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName("horizontalLayout_39");
        dem_waterlevel = new QRadioButton(pageMorhology);
        dem_waterlevel->setObjectName("dem_waterlevel");

        horizontalLayout_39->addWidget(dem_waterlevel);

        dem_waterlevel_m = new QDoubleSpinBox(pageMorhology);
        dem_waterlevel_m->setObjectName("dem_waterlevel_m");
        dem_waterlevel_m->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_waterlevel_m->setDecimals(1);
        dem_waterlevel_m->setMinimum(-10000.000000000000000);
        dem_waterlevel_m->setMaximum(10000.000000000000000);
        dem_waterlevel_m->setSingleStep(5.000000000000000);
        dem_waterlevel_m->setValue(0.000000000000000);

        horizontalLayout_39->addWidget(dem_waterlevel_m);

        dem_waterlevel_relief = new QCheckBox(pageMorhology);
        dem_waterlevel_relief->setObjectName("dem_waterlevel_relief");
        dem_waterlevel_relief->setChecked(true);

        horizontalLayout_39->addWidget(dem_waterlevel_relief);


        verticalLayout_11->addLayout(horizontalLayout_39);

        line_18 = new QFrame(pageMorhology);
        line_18->setObjectName("line_18");
        line_18->setFrameShape(QFrame::Shape::HLine);
        line_18->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_11->addWidget(line_18);

        dem_normals = new QRadioButton(pageMorhology);
        dem_normals->setObjectName("dem_normals");
        dem_normals->setChecked(false);

        verticalLayout_11->addWidget(dem_normals);

        dem_slopeGradient = new QRadioButton(pageMorhology);
        dem_slopeGradient->setObjectName("dem_slopeGradient");
        dem_slopeGradient->setChecked(false);

        verticalLayout_11->addWidget(dem_slopeGradient);

        dem_slopeAvg = new QRadioButton(pageMorhology);
        dem_slopeAvg->setObjectName("dem_slopeAvg");

        verticalLayout_11->addWidget(dem_slopeAvg);

        dem_aspect = new QRadioButton(pageMorhology);
        dem_aspect->setObjectName("dem_aspect");

        verticalLayout_11->addWidget(dem_aspect);

        dem_aspect_east = new QRadioButton(pageMorhology);
        dem_aspect_east->setObjectName("dem_aspect_east");

        verticalLayout_11->addWidget(dem_aspect_east);

        dem_aspect_north = new QRadioButton(pageMorhology);
        dem_aspect_north->setObjectName("dem_aspect_north");

        verticalLayout_11->addWidget(dem_aspect_north);

        line_19 = new QFrame(pageMorhology);
        line_19->setObjectName("line_19");
        line_19->setFrameShape(QFrame::Shape::HLine);
        line_19->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_11->addWidget(line_19);

        dem_laplacian = new QRadioButton(pageMorhology);
        dem_laplacian->setObjectName("dem_laplacian");

        verticalLayout_11->addWidget(dem_laplacian);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        dem_fractLaplacian = new QRadioButton(pageMorhology);
        dem_fractLaplacian->setObjectName("dem_fractLaplacian");

        horizontalLayout_5->addWidget(dem_fractLaplacian);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        dem_fractLaplacian_s = new QDoubleSpinBox(pageMorhology);
        dem_fractLaplacian_s->setObjectName("dem_fractLaplacian_s");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(dem_fractLaplacian_s->sizePolicy().hasHeightForWidth());
        dem_fractLaplacian_s->setSizePolicy(sizePolicy6);
        dem_fractLaplacian_s->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_fractLaplacian_s->setMaximum(1.000000000000000);
        dem_fractLaplacian_s->setSingleStep(0.100000000000000);
        dem_fractLaplacian_s->setValue(0.500000000000000);

        horizontalLayout_19->addWidget(dem_fractLaplacian_s);

        dem_fractLaplacian_n = new QSpinBox(pageMorhology);
        dem_fractLaplacian_n->setObjectName("dem_fractLaplacian_n");
        sizePolicy6.setHeightForWidth(dem_fractLaplacian_n->sizePolicy().hasHeightForWidth());
        dem_fractLaplacian_n->setSizePolicy(sizePolicy6);
        dem_fractLaplacian_n->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_fractLaplacian_n->setMaximum(1000);
        dem_fractLaplacian_n->setValue(30);

        horizontalLayout_19->addWidget(dem_fractLaplacian_n);


        horizontalLayout_5->addLayout(horizontalLayout_19);


        verticalLayout_11->addLayout(horizontalLayout_5);

        line_20 = new QFrame(pageMorhology);
        line_20->setObjectName("line_20");
        line_20->setFrameShape(QFrame::Shape::HLine);
        line_20->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_11->addWidget(line_20);

        dem_asymmetry = new QRadioButton(pageMorhology);
        dem_asymmetry->setObjectName("dem_asymmetry");

        verticalLayout_11->addWidget(dem_asymmetry);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(16, -1, -1, -1);
        dem_asymmetryW = new QSpinBox(pageMorhology);
        dem_asymmetryW->setObjectName("dem_asymmetryW");
        dem_asymmetryW->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_asymmetryW->setMinimum(3);
        dem_asymmetryW->setMaximum(1001);
        dem_asymmetryW->setSingleStep(2);
        dem_asymmetryW->setValue(101);

        horizontalLayout->addWidget(dem_asymmetryW);

        dem_asymmetryDir = new QDoubleSpinBox(pageMorhology);
        dem_asymmetryDir->setObjectName("dem_asymmetryDir");
        dem_asymmetryDir->setMinimumSize(QSize(48, 0));
        dem_asymmetryDir->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_asymmetryDir->setDecimals(0);
        dem_asymmetryDir->setMaximum(360.000000000000000);
        dem_asymmetryDir->setSingleStep(45.000000000000000);
        dem_asymmetryDir->setValue(0.000000000000000);

        horizontalLayout->addWidget(dem_asymmetryDir);

        label_33 = new QLabel(pageMorhology);
        label_33->setObjectName("label_33");
        sizePolicy3.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(label_33);

        dem_asymmetryDirTol = new QDoubleSpinBox(pageMorhology);
        dem_asymmetryDirTol->setObjectName("dem_asymmetryDirTol");
        dem_asymmetryDirTol->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_asymmetryDirTol->setDecimals(0);
        dem_asymmetryDirTol->setMaximum(360.000000000000000);
        dem_asymmetryDirTol->setSingleStep(5.000000000000000);
        dem_asymmetryDirTol->setValue(45.000000000000000);

        horizontalLayout->addWidget(dem_asymmetryDirTol);


        verticalLayout_11->addLayout(horizontalLayout);

        verticalSpacer_8 = new QSpacerItem(20, 292, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_8);

        demToolbox->addItem(pageMorhology, QString::fromUtf8("Local: elevation, gradient, laplacian"));
        pageCurvatures = new QWidget();
        pageCurvatures->setObjectName("pageCurvatures");
        pageCurvatures->setGeometry(QRect(0, 0, 300, 260));
        verticalLayout_6 = new QVBoxLayout(pageCurvatures);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        dem_curv_fromQuadrics = new QCheckBox(pageCurvatures);
        dem_curv_fromQuadrics->setObjectName("dem_curv_fromQuadrics");
        dem_curv_fromQuadrics->setChecked(true);

        horizontalLayout_9->addWidget(dem_curv_fromQuadrics);

        dem_curv_fromQuadrics_w = new QSpinBox(pageCurvatures);
        dem_curv_fromQuadrics_w->setObjectName("dem_curv_fromQuadrics_w");
        dem_curv_fromQuadrics_w->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_curv_fromQuadrics_w->setMinimum(7);
        dem_curv_fromQuadrics_w->setMaximum(1001);
        dem_curv_fromQuadrics_w->setSingleStep(2);
        dem_curv_fromQuadrics_w->setValue(7);

        horizontalLayout_9->addWidget(dem_curv_fromQuadrics_w);

        label_14 = new QLabel(pageCurvatures);
        label_14->setObjectName("label_14");
        sizePolicy3.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy3);

        horizontalLayout_9->addWidget(label_14);


        verticalLayout_6->addLayout(horizontalLayout_9);

        dem_curvMin = new QRadioButton(pageCurvatures);
        dem_curvMin->setObjectName("dem_curvMin");

        verticalLayout_6->addWidget(dem_curvMin);

        dem_curvMax = new QRadioButton(pageCurvatures);
        dem_curvMax->setObjectName("dem_curvMax");

        verticalLayout_6->addWidget(dem_curvMax);

        dem_curvMean = new QRadioButton(pageCurvatures);
        dem_curvMean->setObjectName("dem_curvMean");

        verticalLayout_6->addWidget(dem_curvMean);

        dem_curvGaussian = new QRadioButton(pageCurvatures);
        dem_curvGaussian->setObjectName("dem_curvGaussian");

        verticalLayout_6->addWidget(dem_curvGaussian);

        dem_curvProfile = new QRadioButton(pageCurvatures);
        dem_curvProfile->setObjectName("dem_curvProfile");

        verticalLayout_6->addWidget(dem_curvProfile);

        dem_curvContour = new QRadioButton(pageCurvatures);
        dem_curvContour->setObjectName("dem_curvContour");

        verticalLayout_6->addWidget(dem_curvContour);

        dem_curvTangent = new QRadioButton(pageCurvatures);
        dem_curvTangent->setObjectName("dem_curvTangent");

        verticalLayout_6->addWidget(dem_curvTangent);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_7);

        demToolbox->addItem(pageCurvatures, QString::fromUtf8("Local: curvatures"));
        pageRelief = new QWidget();
        pageRelief->setObjectName("pageRelief");
        pageRelief->setGeometry(QRect(0, 0, 278, 260));
        verticalLayout_8 = new QVBoxLayout(pageRelief);
        verticalLayout_8->setObjectName("verticalLayout_8");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_demRelief_radius = new QLabel(pageRelief);
        label_demRelief_radius->setObjectName("label_demRelief_radius");

        horizontalLayout_11->addWidget(label_demRelief_radius);

        dem_localRelief_w = new QSpinBox(pageRelief);
        dem_localRelief_w->setObjectName("dem_localRelief_w");
        dem_localRelief_w->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_localRelief_w->setMinimum(3);
        dem_localRelief_w->setMaximum(1001);
        dem_localRelief_w->setSingleStep(2);
        dem_localRelief_w->setValue(33);

        horizontalLayout_11->addWidget(dem_localRelief_w);

        label_18 = new QLabel(pageRelief);
        label_18->setObjectName("label_18");
        sizePolicy3.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy3);

        horizontalLayout_11->addWidget(label_18);


        verticalLayout_8->addLayout(horizontalLayout_11);

        dem_tpi = new QRadioButton(pageRelief);
        dem_tpi->setObjectName("dem_tpi");

        verticalLayout_8->addWidget(dem_tpi);

        dem_localRelief = new QRadioButton(pageRelief);
        dem_localRelief->setObjectName("dem_localRelief");

        verticalLayout_8->addWidget(dem_localRelief);

        dem_localVariance = new QRadioButton(pageRelief);
        dem_localVariance->setObjectName("dem_localVariance");

        verticalLayout_8->addWidget(dem_localVariance);

        dem_areaRatio = new QRadioButton(pageRelief);
        dem_areaRatio->setObjectName("dem_areaRatio");

        verticalLayout_8->addWidget(dem_areaRatio);

        dem_ruggedness = new QRadioButton(pageRelief);
        dem_ruggedness->setObjectName("dem_ruggedness");

        verticalLayout_8->addWidget(dem_ruggedness);

        dem_surfaceRoughness = new QRadioButton(pageRelief);
        dem_surfaceRoughness->setObjectName("dem_surfaceRoughness");

        verticalLayout_8->addWidget(dem_surfaceRoughness);

        dem_surfaceRoughnessStd = new QRadioButton(pageRelief);
        dem_surfaceRoughnessStd->setObjectName("dem_surfaceRoughnessStd");

        verticalLayout_8->addWidget(dem_surfaceRoughnessStd);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        demToolbox->addItem(pageRelief, QString::fromUtf8("Local: relief, ruggedness, roughness"));
        pageVisibility = new QWidget();
        pageVisibility->setObjectName("pageVisibility");
        pageVisibility->setGeometry(QRect(0, 0, 302, 617));
        verticalLayout_2 = new QVBoxLayout(pageVisibility);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_54 = new QLabel(pageVisibility);
        label_54->setObjectName("label_54");

        horizontalLayout_15->addWidget(label_54);

        viewshed_offset = new QDoubleSpinBox(pageVisibility);
        viewshed_offset->setObjectName("viewshed_offset");
        viewshed_offset->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        viewshed_offset->setMaximum(1000.000000000000000);
        viewshed_offset->setValue(1.700000000000000);

        horizontalLayout_15->addWidget(viewshed_offset);


        verticalLayout_2->addLayout(horizontalLayout_15);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        label_23 = new QLabel(pageVisibility);
        label_23->setObjectName("label_23");

        horizontalLayout_21->addWidget(label_23);

        viewshed_rescale = new QDoubleSpinBox(pageVisibility);
        viewshed_rescale->setObjectName("viewshed_rescale");
        viewshed_rescale->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        viewshed_rescale->setDecimals(3);
        viewshed_rescale->setMaximum(1.000000000000000);
        viewshed_rescale->setSingleStep(0.100000000000000);
        viewshed_rescale->setValue(0.100000000000000);

        horizontalLayout_21->addWidget(viewshed_rescale);


        verticalLayout_2->addLayout(horizontalLayout_21);

        dem_viewshedLoc = new QRadioButton(pageVisibility);
        dem_viewshedLoc->setObjectName("dem_viewshedLoc");

        verticalLayout_2->addWidget(dem_viewshedLoc);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalLayout_17->setContentsMargins(20, -1, -1, -1);
        viewshed_location_x = new QSpinBox(pageVisibility);
        viewshed_location_x->setObjectName("viewshed_location_x");
        viewshed_location_x->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_17->addWidget(viewshed_location_x);

        viewshed_location_y = new QSpinBox(pageVisibility);
        viewshed_location_y->setObjectName("viewshed_location_y");
        viewshed_location_y->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_17->addWidget(viewshed_location_y);

        btn_pickViewshedLocation = new QPushButton(pageVisibility);
        btn_pickViewshedLocation->setObjectName("btn_pickViewshedLocation");
        btn_pickViewshedLocation->setCheckable(false);

        horizontalLayout_17->addWidget(btn_pickViewshedLocation);


        verticalLayout_2->addLayout(horizontalLayout_17);

        dem_viewshedTotalOut = new QRadioButton(pageVisibility);
        dem_viewshedTotalOut->setObjectName("dem_viewshedTotalOut");

        verticalLayout_2->addWidget(dem_viewshedTotalOut);

        dem_viewshedTotalIn = new QRadioButton(pageVisibility);
        dem_viewshedTotalIn->setObjectName("dem_viewshedTotalIn");

        verticalLayout_2->addWidget(dem_viewshedTotalIn);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName("horizontalLayout_43");
        horizontalLayout_43->setContentsMargins(20, -1, -1, -1);
        dem_viewshedTotal_sample = new QCheckBox(pageVisibility);
        dem_viewshedTotal_sample->setObjectName("dem_viewshedTotal_sample");

        horizontalLayout_43->addWidget(dem_viewshedTotal_sample);

        dem_viewshedTotal_numSamples = new QSpinBox(pageVisibility);
        dem_viewshedTotal_numSamples->setObjectName("dem_viewshedTotal_numSamples");
        dem_viewshedTotal_numSamples->setMaximum(1000000);
        dem_viewshedTotal_numSamples->setSingleStep(100);
        dem_viewshedTotal_numSamples->setValue(100);

        horizontalLayout_43->addWidget(dem_viewshedTotal_numSamples);


        verticalLayout_2->addLayout(horizontalLayout_43);

        line_12 = new QFrame(pageVisibility);
        line_12->setObjectName("line_12");
        line_12->setFrameShape(QFrame::Shape::HLine);
        line_12->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_12);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setObjectName("horizontalLayout_53");
        dem_posOpenness = new QRadioButton(pageVisibility);
        dem_posOpenness->setObjectName("dem_posOpenness");

        horizontalLayout_53->addWidget(dem_posOpenness);

        dem_negOpenness = new QRadioButton(pageVisibility);
        dem_negOpenness->setObjectName("dem_negOpenness");

        horizontalLayout_53->addWidget(dem_negOpenness);


        verticalLayout_2->addLayout(horizontalLayout_53);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setObjectName("horizontalLayout_47");
        horizontalLayout_47->setContentsMargins(20, -1, -1, -1);
        dem_opennessDirs = new QSpinBox(pageVisibility);
        dem_opennessDirs->setObjectName("dem_opennessDirs");
        dem_opennessDirs->setMinimumSize(QSize(64, 0));
        dem_opennessDirs->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_opennessDirs->setMinimum(1);
        dem_opennessDirs->setMaximum(256);
        dem_opennessDirs->setValue(8);

        horizontalLayout_47->addWidget(dem_opennessDirs);

        label_55 = new QLabel(pageVisibility);
        label_55->setObjectName("label_55");

        horizontalLayout_47->addWidget(label_55);


        horizontalLayout_2->addLayout(horizontalLayout_47);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setObjectName("horizontalLayout_49");
        dem_opennessDist = new QSpinBox(pageVisibility);
        dem_opennessDist->setObjectName("dem_opennessDist");
        dem_opennessDist->setMinimumSize(QSize(64, 0));
        dem_opennessDist->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_opennessDist->setMinimum(-1);
        dem_opennessDist->setMaximum(50000);
        dem_opennessDist->setSingleStep(1000);
        dem_opennessDist->setValue(1000);

        horizontalLayout_49->addWidget(dem_opennessDist);

        label_56 = new QLabel(pageVisibility);
        label_56->setObjectName("label_56");

        horizontalLayout_49->addWidget(label_56);


        horizontalLayout_2->addLayout(horizontalLayout_49);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line_15 = new QFrame(pageVisibility);
        line_15->setObjectName("line_15");
        line_15->setFrameShape(QFrame::Shape::HLine);
        line_15->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_15);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setObjectName("horizontalLayout_44");
        label_51 = new QLabel(pageVisibility);
        label_51->setObjectName("label_51");

        horizontalLayout_44->addWidget(label_51);

        dem_accessibilitySamples = new QSpinBox(pageVisibility);
        dem_accessibilitySamples->setObjectName("dem_accessibilitySamples");
        dem_accessibilitySamples->setMinimumSize(QSize(0, 0));
        dem_accessibilitySamples->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_accessibilitySamples->setMinimum(1);
        dem_accessibilitySamples->setMaximum(8192);
        dem_accessibilitySamples->setValue(32);

        horizontalLayout_44->addWidget(dem_accessibilitySamples);

        label_17 = new QLabel(pageVisibility);
        label_17->setObjectName("label_17");

        horizontalLayout_44->addWidget(label_17);

        dem_accessibilityRadius = new QDoubleSpinBox(pageVisibility);
        dem_accessibilityRadius->setObjectName("dem_accessibilityRadius");
        dem_accessibilityRadius->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_accessibilityRadius->setDecimals(1);
        dem_accessibilityRadius->setMinimum(-1.000000000000000);
        dem_accessibilityRadius->setMaximum(1000.000000000000000);
        dem_accessibilityRadius->setValue(10.000000000000000);

        horizontalLayout_44->addWidget(dem_accessibilityRadius);


        verticalLayout_2->addLayout(horizontalLayout_44);

        dem_accessibility = new QRadioButton(pageVisibility);
        dem_accessibility->setObjectName("dem_accessibility");
        dem_accessibility->setChecked(false);

        verticalLayout_2->addWidget(dem_accessibility);

        dem_skyview = new QRadioButton(pageVisibility);
        dem_skyview->setObjectName("dem_skyview");

        verticalLayout_2->addWidget(dem_skyview);

        dem_skyviewApprox = new QRadioButton(pageVisibility);
        dem_skyviewApprox->setObjectName("dem_skyviewApprox");

        verticalLayout_2->addWidget(dem_skyviewApprox);

        line_16 = new QFrame(pageVisibility);
        line_16->setObjectName("line_16");
        line_16->setFrameShape(QFrame::Shape::HLine);
        line_16->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_16);

        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setObjectName("horizontalLayout_51");
        dem_sunlight = new QRadioButton(pageVisibility);
        dem_sunlight->setObjectName("dem_sunlight");
        dem_sunlight->setChecked(false);

        horizontalLayout_51->addWidget(dem_sunlight);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(-1, 0, -1, -1);
        dem_sunlightLatitude = new QSpinBox(pageVisibility);
        dem_sunlightLatitude->setObjectName("dem_sunlightLatitude");
        dem_sunlightLatitude->setMinimumSize(QSize(0, 0));
        dem_sunlightLatitude->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_sunlightLatitude->setMinimum(-90);
        dem_sunlightLatitude->setMaximum(90);
        dem_sunlightLatitude->setValue(45);

        horizontalLayout_6->addWidget(dem_sunlightLatitude);

        label_5 = new QLabel(pageVisibility);
        label_5->setObjectName("label_5");

        horizontalLayout_6->addWidget(label_5);


        horizontalLayout_51->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_51);

        horizontalLayout_52 = new QHBoxLayout();
        horizontalLayout_52->setObjectName("horizontalLayout_52");
        dem_dahi = new QRadioButton(pageVisibility);
        dem_dahi->setObjectName("dem_dahi");

        horizontalLayout_52->addWidget(dem_dahi);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName("horizontalLayout_28");
        dem_dahiMax = new QSpinBox(pageVisibility);
        dem_dahiMax->setObjectName("dem_dahiMax");
        dem_dahiMax->setMinimumSize(QSize(0, 0));
        dem_dahiMax->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_dahiMax->setMinimum(0);
        dem_dahiMax->setMaximum(360);
        dem_dahiMax->setValue(202);

        horizontalLayout_28->addWidget(dem_dahiMax);

        label_32 = new QLabel(pageVisibility);
        label_32->setObjectName("label_32");

        horizontalLayout_28->addWidget(label_32);


        horizontalLayout_52->addLayout(horizontalLayout_28);


        verticalLayout_2->addLayout(horizontalLayout_52);

        verticalSpacer_11 = new QSpacerItem(20, 392, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_11);

        demToolbox->addItem(pageVisibility, QString::fromUtf8("Visibility"));
        pageLandforms = new QWidget();
        pageLandforms->setObjectName("pageLandforms");
        pageLandforms->setGeometry(QRect(0, 0, 346, 423));
        verticalLayout_17 = new QVBoxLayout(pageLandforms);
        verticalLayout_17->setObjectName("verticalLayout_17");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, -1, -1, -1);
        dem_showSingleLandform = new QCheckBox(pageLandforms);
        dem_showSingleLandform->setObjectName("dem_showSingleLandform");

        horizontalLayout_10->addWidget(dem_showSingleLandform);

        dem_showSingleLandform_id = new QSpinBox(pageLandforms);
        dem_showSingleLandform_id->setObjectName("dem_showSingleLandform_id");

        horizontalLayout_10->addWidget(dem_showSingleLandform_id);


        verticalLayout_17->addLayout(horizontalLayout_10);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        label_25 = new QLabel(pageLandforms);
        label_25->setObjectName("label_25");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy7);

        horizontalLayout_23->addWidget(label_25);

        dem_landformName = new QLabel(pageLandforms);
        dem_landformName->setObjectName("dem_landformName");
        sizePolicy5.setHeightForWidth(dem_landformName->sizePolicy().hasHeightForWidth());
        dem_landformName->setSizePolicy(sizePolicy5);

        horizontalLayout_23->addWidget(dem_landformName);


        verticalLayout_17->addLayout(horizontalLayout_23);

        line = new QFrame(pageLandforms);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_17->addWidget(line);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        dem_dikauWoodClass = new QRadioButton(pageLandforms);
        dem_dikauWoodClass->setObjectName("dem_dikauWoodClass");

        gridLayout_4->addWidget(dem_dikauWoodClass, 0, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        dem_dikauWoodSolver_w = new QSpinBox(pageLandforms);
        dem_dikauWoodSolver_w->setObjectName("dem_dikauWoodSolver_w");
        dem_dikauWoodSolver_w->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_dikauWoodSolver_w->setMinimum(15);
        dem_dikauWoodSolver_w->setMaximum(1001);
        dem_dikauWoodSolver_w->setSingleStep(2);
        dem_dikauWoodSolver_w->setValue(15);

        horizontalLayout_13->addWidget(dem_dikauWoodSolver_w);

        label_22 = new QLabel(pageLandforms);
        label_22->setObjectName("label_22");

        horizontalLayout_13->addWidget(label_22);


        gridLayout_4->addLayout(horizontalLayout_13, 0, 1, 1, 2);

        dem_fisher2004 = new QRadioButton(pageLandforms);
        dem_fisher2004->setObjectName("dem_fisher2004");
        dem_fisher2004->setEnabled(true);

        gridLayout_4->addWidget(dem_fisher2004, 1, 0, 1, 1);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName("horizontalLayout_29");
        dem_fisher2004_minScale = new QSpinBox(pageLandforms);
        dem_fisher2004_minScale->setObjectName("dem_fisher2004_minScale");
        sizePolicy6.setHeightForWidth(dem_fisher2004_minScale->sizePolicy().hasHeightForWidth());
        dem_fisher2004_minScale->setSizePolicy(sizePolicy6);
        dem_fisher2004_minScale->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_fisher2004_minScale->setMinimum(3);
        dem_fisher2004_minScale->setMaximum(201);
        dem_fisher2004_minScale->setSingleStep(2);
        dem_fisher2004_minScale->setValue(3);

        horizontalLayout_29->addWidget(dem_fisher2004_minScale);

        label_31 = new QLabel(pageLandforms);
        label_31->setObjectName("label_31");
        sizePolicy7.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy7);

        horizontalLayout_29->addWidget(label_31);

        dem_fisher2004_maxScale = new QSpinBox(pageLandforms);
        dem_fisher2004_maxScale->setObjectName("dem_fisher2004_maxScale");
        sizePolicy6.setHeightForWidth(dem_fisher2004_maxScale->sizePolicy().hasHeightForWidth());
        dem_fisher2004_maxScale->setSizePolicy(sizePolicy6);
        dem_fisher2004_maxScale->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_fisher2004_maxScale->setMinimum(3);
        dem_fisher2004_maxScale->setMaximum(201);
        dem_fisher2004_maxScale->setSingleStep(2);
        dem_fisher2004_maxScale->setValue(21);

        horizontalLayout_29->addWidget(dem_fisher2004_maxScale);


        gridLayout_4->addLayout(horizontalLayout_29, 1, 1, 1, 2);

        dem_fisher2004entropy = new QRadioButton(pageLandforms);
        dem_fisher2004entropy->setObjectName("dem_fisher2004entropy");
        dem_fisher2004entropy->setEnabled(true);

        gridLayout_4->addWidget(dem_fisher2004entropy, 2, 0, 1, 1);

        dem_tpiClass = new QRadioButton(pageLandforms);
        dem_tpiClass->setObjectName("dem_tpiClass");

        gridLayout_4->addWidget(dem_tpiClass, 3, 0, 1, 1);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName("horizontalLayout_24");
        dem_tpiClassSmall = new QSpinBox(pageLandforms);
        dem_tpiClassSmall->setObjectName("dem_tpiClassSmall");
        dem_tpiClassSmall->setMinimumSize(QSize(64, 0));
        dem_tpiClassSmall->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_tpiClassSmall->setMaximum(50000);
        dem_tpiClassSmall->setSingleStep(50);
        dem_tpiClassSmall->setValue(300);

        horizontalLayout_24->addWidget(dem_tpiClassSmall);

        label_34 = new QLabel(pageLandforms);
        label_34->setObjectName("label_34");
        sizePolicy3.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy3);

        horizontalLayout_24->addWidget(label_34);

        dem_tpiClassLarge = new QSpinBox(pageLandforms);
        dem_tpiClassLarge->setObjectName("dem_tpiClassLarge");
        dem_tpiClassLarge->setMinimumSize(QSize(64, 0));
        dem_tpiClassLarge->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_tpiClassLarge->setMaximum(50000);
        dem_tpiClassLarge->setSingleStep(50);
        dem_tpiClassLarge->setValue(2000);

        horizontalLayout_24->addWidget(dem_tpiClassLarge);


        gridLayout_4->addLayout(horizontalLayout_24, 3, 1, 1, 2);

        dem_geomorphons = new QRadioButton(pageLandforms);
        dem_geomorphons->setObjectName("dem_geomorphons");

        gridLayout_4->addWidget(dem_geomorphons, 4, 0, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        dem_geomorphons_km = new QDoubleSpinBox(pageLandforms);
        dem_geomorphons_km->setObjectName("dem_geomorphons_km");
        dem_geomorphons_km->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_geomorphons_km->setDecimals(1);
        dem_geomorphons_km->setMaximum(100.000000000000000);
        dem_geomorphons_km->setSingleStep(0.100000000000000);
        dem_geomorphons_km->setValue(1.000000000000000);

        horizontalLayout_20->addWidget(dem_geomorphons_km);

        label = new QLabel(pageLandforms);
        label->setObjectName("label");

        horizontalLayout_20->addWidget(label);


        gridLayout_4->addLayout(horizontalLayout_20, 4, 1, 1, 1);

        dem_tophat = new QRadioButton(pageLandforms);
        dem_tophat->setObjectName("dem_tophat");

        gridLayout_4->addWidget(dem_tophat, 5, 0, 1, 3);

        label_19 = new QLabel(pageLandforms);
        label_19->setObjectName("label_19");
        label_19->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_19, 6, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        dem_tophat_w = new QSpinBox(pageLandforms);
        dem_tophat_w->setObjectName("dem_tophat_w");
        dem_tophat_w->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_tophat_w->setMinimum(1);
        dem_tophat_w->setSingleStep(2);
        dem_tophat_w->setValue(7);

        horizontalLayout_14->addWidget(dem_tophat_w);

        label_28 = new QLabel(pageLandforms);
        label_28->setObjectName("label_28");
        sizePolicy3.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy3);

        horizontalLayout_14->addWidget(label_28);


        gridLayout_4->addLayout(horizontalLayout_14, 6, 1, 1, 1);

        label_16 = new QLabel(pageLandforms);
        label_16->setObjectName("label_16");
        label_16->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_16, 7, 0, 1, 1);

        dem_tophat_peak = new QDoubleSpinBox(pageLandforms);
        dem_tophat_peak->setObjectName("dem_tophat_peak");
        dem_tophat_peak->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_tophat_peak->setDecimals(1);
        dem_tophat_peak->setMaximum(10000.000000000000000);
        dem_tophat_peak->setSingleStep(50.000000000000000);
        dem_tophat_peak->setValue(100.000000000000000);

        gridLayout_4->addWidget(dem_tophat_peak, 7, 1, 1, 1);

        dem_tophat_valley = new QDoubleSpinBox(pageLandforms);
        dem_tophat_valley->setObjectName("dem_tophat_valley");
        dem_tophat_valley->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_tophat_valley->setDecimals(1);
        dem_tophat_valley->setMaximum(10000.000000000000000);
        dem_tophat_valley->setSingleStep(50.000000000000000);
        dem_tophat_valley->setValue(100.000000000000000);

        gridLayout_4->addWidget(dem_tophat_valley, 7, 2, 1, 1);


        verticalLayout_17->addLayout(gridLayout_4);

        verticalSpacer_10 = new QSpacerItem(20, 353, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_10);

        demToolbox->addItem(pageLandforms, QString::fromUtf8("Landforms"));
        pageFlow = new QWidget();
        pageFlow->setObjectName("pageFlow");
        pageFlow->setGeometry(QRect(0, 0, 300, 646));
        verticalLayout_14 = new QVBoxLayout(pageFlow);
        verticalLayout_14->setObjectName("verticalLayout_14");
        groupBox_10 = new QGroupBox(pageFlow);
        groupBox_10->setObjectName("groupBox_10");
        gridLayout_8 = new QGridLayout(groupBox_10);
        gridLayout_8->setObjectName("gridLayout_8");
        label_13 = new QLabel(groupBox_10);
        label_13->setObjectName("label_13");

        gridLayout_8->addWidget(label_13, 0, 0, 1, 1);

        dem_streamArea_flowAlgorithm = new QComboBox(groupBox_10);
        dem_streamArea_flowAlgorithm->addItem(QString());
        dem_streamArea_flowAlgorithm->addItem(QString());
        dem_streamArea_flowAlgorithm->addItem(QString());
        dem_streamArea_flowAlgorithm->addItem(QString());
        dem_streamArea_flowAlgorithm->addItem(QString());
        dem_streamArea_flowAlgorithm->setObjectName("dem_streamArea_flowAlgorithm");
        sizePolicy6.setHeightForWidth(dem_streamArea_flowAlgorithm->sizePolicy().hasHeightForWidth());
        dem_streamArea_flowAlgorithm->setSizePolicy(sizePolicy6);

        gridLayout_8->addWidget(dem_streamArea_flowAlgorithm, 0, 1, 1, 2);

        label_29 = new QLabel(groupBox_10);
        label_29->setObjectName("label_29");
        sizePolicy5.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy5);
        label_29->setMaximumSize(QSize(80, 16777215));

        gridLayout_8->addWidget(label_29, 1, 0, 1, 1);

        dem_streamArea_mfdExp = new QDoubleSpinBox(groupBox_10);
        dem_streamArea_mfdExp->setObjectName("dem_streamArea_mfdExp");
        dem_streamArea_mfdExp->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_streamArea_mfdExp->setDecimals(1);
        dem_streamArea_mfdExp->setMaximum(100.000000000000000);
        dem_streamArea_mfdExp->setValue(1.000000000000000);

        gridLayout_8->addWidget(dem_streamArea_mfdExp, 1, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_9, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox_10);
        label_3->setObjectName("label_3");

        gridLayout_8->addWidget(label_3, 2, 0, 1, 1);

        dem_streamArea_rho8iters = new QSpinBox(groupBox_10);
        dem_streamArea_rho8iters->setObjectName("dem_streamArea_rho8iters");
        dem_streamArea_rho8iters->setMinimumSize(QSize(64, 0));
        dem_streamArea_rho8iters->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_streamArea_rho8iters->setMinimum(1);
        dem_streamArea_rho8iters->setMaximum(1000);
        dem_streamArea_rho8iters->setValue(20);

        gridLayout_8->addWidget(dem_streamArea_rho8iters, 2, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_10, 2, 2, 1, 1);

        dem_streamArea_uniqueSource = new QCheckBox(groupBox_10);
        dem_streamArea_uniqueSource->setObjectName("dem_streamArea_uniqueSource");

        gridLayout_8->addWidget(dem_streamArea_uniqueSource, 3, 0, 1, 3);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName("horizontalLayout_40");
        horizontalLayout_40->setContentsMargins(20, -1, -1, -1);
        dem_streamArea_source_x = new QSpinBox(groupBox_10);
        dem_streamArea_source_x->setObjectName("dem_streamArea_source_x");
        dem_streamArea_source_x->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_40->addWidget(dem_streamArea_source_x);

        dem_streamArea_source_y = new QSpinBox(groupBox_10);
        dem_streamArea_source_y->setObjectName("dem_streamArea_source_y");
        dem_streamArea_source_y->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_40->addWidget(dem_streamArea_source_y);

        btn_pickStreamAreaSource = new QPushButton(groupBox_10);
        btn_pickStreamAreaSource->setObjectName("btn_pickStreamAreaSource");
        btn_pickStreamAreaSource->setCheckable(true);

        horizontalLayout_40->addWidget(btn_pickStreamAreaSource);


        gridLayout_8->addLayout(horizontalLayout_40, 4, 0, 1, 3);


        verticalLayout_14->addWidget(groupBox_10);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        dem_streamArea = new QRadioButton(pageFlow);
        dem_streamArea->setObjectName("dem_streamArea");
        dem_streamArea->setChecked(false);

        horizontalLayout_8->addWidget(dem_streamArea);

        label_6 = new QLabel(pageFlow);
        label_6->setObjectName("label_6");
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(label_6);

        dem_streamArea_exp = new QDoubleSpinBox(pageFlow);
        dem_streamArea_exp->setObjectName("dem_streamArea_exp");
        dem_streamArea_exp->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_streamArea_exp->setMaximum(10.000000000000000);
        dem_streamArea_exp->setSingleStep(0.100000000000000);
        dem_streamArea_exp->setValue(0.200000000000000);

        horizontalLayout_8->addWidget(dem_streamArea_exp);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_14->addLayout(horizontalLayout_8);

        dem_streamAreaLog = new QRadioButton(pageFlow);
        dem_streamAreaLog->setObjectName("dem_streamAreaLog");

        verticalLayout_14->addWidget(dem_streamAreaLog);

        dem_wetness = new QRadioButton(pageFlow);
        dem_wetness->setObjectName("dem_wetness");

        verticalLayout_14->addWidget(dem_wetness);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName("horizontalLayout_35");
        dem_streamPower = new QRadioButton(pageFlow);
        dem_streamPower->setObjectName("dem_streamPower");
        dem_streamPower->setChecked(false);

        horizontalLayout_35->addWidget(dem_streamPower);

        label_39 = new QLabel(pageFlow);
        label_39->setObjectName("label_39");
        sizePolicy3.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy3);

        horizontalLayout_35->addWidget(label_39);

        dem_streamPower_m = new QDoubleSpinBox(pageFlow);
        dem_streamPower_m->setObjectName("dem_streamPower_m");
        dem_streamPower_m->setMinimumSize(QSize(50, 0));
        dem_streamPower_m->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_streamPower_m->setMaximum(10.000000000000000);
        dem_streamPower_m->setSingleStep(0.050000000000000);
        dem_streamPower_m->setValue(0.500000000000000);

        horizontalLayout_35->addWidget(dem_streamPower_m);

        label_40 = new QLabel(pageFlow);
        label_40->setObjectName("label_40");
        sizePolicy3.setHeightForWidth(label_40->sizePolicy().hasHeightForWidth());
        label_40->setSizePolicy(sizePolicy3);

        horizontalLayout_35->addWidget(label_40);

        dem_streamPower_n = new QDoubleSpinBox(pageFlow);
        dem_streamPower_n->setObjectName("dem_streamPower_n");
        dem_streamPower_n->setMinimumSize(QSize(50, 0));
        dem_streamPower_n->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_streamPower_n->setMaximum(10.000000000000000);
        dem_streamPower_n->setSingleStep(0.050000000000000);
        dem_streamPower_n->setValue(1.000000000000000);

        horizontalLayout_35->addWidget(dem_streamPower_n);


        verticalLayout_14->addLayout(horizontalLayout_35);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName("horizontalLayout_30");
        horizontalLayout_30->setContentsMargins(20, -1, -1, -1);
        dem_streamPower_threshold = new QCheckBox(pageFlow);
        dem_streamPower_threshold->setObjectName("dem_streamPower_threshold");

        horizontalLayout_30->addWidget(dem_streamPower_threshold);

        dem_streamPower_t = new QDoubleSpinBox(pageFlow);
        dem_streamPower_t->setObjectName("dem_streamPower_t");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(dem_streamPower_t->sizePolicy().hasHeightForWidth());
        dem_streamPower_t->setSizePolicy(sizePolicy8);
        dem_streamPower_t->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_streamPower_t->setDecimals(1);
        dem_streamPower_t->setMaximum(10000.000000000000000);
        dem_streamPower_t->setSingleStep(10.000000000000000);
        dem_streamPower_t->setValue(200.000000000000000);

        horizontalLayout_30->addWidget(dem_streamPower_t);


        verticalLayout_14->addLayout(horizontalLayout_30);

        line_4 = new QFrame(pageFlow);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_14->addWidget(line_4);

        label_35 = new QLabel(pageFlow);
        label_35->setObjectName("label_35");

        verticalLayout_14->addWidget(label_35);

        dem_depthToWater = new QRadioButton(pageFlow);
        dem_depthToWater->setObjectName("dem_depthToWater");
        dem_depthToWater->setEnabled(true);

        verticalLayout_14->addWidget(dem_depthToWater);

        dem_hand = new QRadioButton(pageFlow);
        dem_hand->setObjectName("dem_hand");
        dem_hand->setChecked(false);

        verticalLayout_14->addWidget(dem_hand);

        dem_riverDistEuclidean = new QRadioButton(pageFlow);
        dem_riverDistEuclidean->setObjectName("dem_riverDistEuclidean");
        dem_riverDistEuclidean->setChecked(false);

        verticalLayout_14->addWidget(dem_riverDistEuclidean);

        dem_riverDistFlow = new QRadioButton(pageFlow);
        dem_riverDistFlow->setObjectName("dem_riverDistFlow");
        dem_riverDistFlow->setChecked(false);

        verticalLayout_14->addWidget(dem_riverDistFlow);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName("horizontalLayout_34");
        dem_branchLength = new QRadioButton(pageFlow);
        dem_branchLength->setObjectName("dem_branchLength");
        dem_branchLength->setEnabled(true);

        horizontalLayout_34->addWidget(dem_branchLength);

        label_38 = new QLabel(pageFlow);
        label_38->setObjectName("label_38");
        sizePolicy3.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy3);

        horizontalLayout_34->addWidget(label_38);

        dem_branchLength_exp = new QDoubleSpinBox(pageFlow);
        dem_branchLength_exp->setObjectName("dem_branchLength_exp");
        dem_branchLength_exp->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_branchLength_exp->setMaximum(10.000000000000000);
        dem_branchLength_exp->setSingleStep(0.100000000000000);
        dem_branchLength_exp->setValue(0.500000000000000);

        horizontalLayout_34->addWidget(dem_branchLength_exp);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_3);


        verticalLayout_14->addLayout(horizontalLayout_34);

        verticalSpacer_9 = new QSpacerItem(20, 500, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_9);

        demToolbox->addItem(pageFlow, QString::fromUtf8("Hydrology"));
        pageOrometry = new QWidget();
        pageOrometry->setObjectName("pageOrometry");
        pageOrometry->setGeometry(QRect(0, 0, 289, 517));
        verticalLayout_13 = new QVBoxLayout(pageOrometry);
        verticalLayout_13->setObjectName("verticalLayout_13");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_15 = new QLabel(pageOrometry);
        label_15->setObjectName("label_15");

        horizontalLayout_12->addWidget(label_15);

        dem_orometryRadius = new QDoubleSpinBox(pageOrometry);
        dem_orometryRadius->setObjectName("dem_orometryRadius");
        dem_orometryRadius->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_orometryRadius->setDecimals(2);
        dem_orometryRadius->setMaximum(1000.000000000000000);
        dem_orometryRadius->setValue(1.500000000000000);

        horizontalLayout_12->addWidget(dem_orometryRadius);


        verticalLayout_13->addLayout(horizontalLayout_12);

        dem_peakedness = new QRadioButton(pageOrometry);
        dem_peakedness->setObjectName("dem_peakedness");

        verticalLayout_13->addWidget(dem_peakedness);

        dem_ors = new QRadioButton(pageOrometry);
        dem_ors->setObjectName("dem_ors");

        verticalLayout_13->addWidget(dem_ors);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        dem_jut = new QRadioButton(pageOrometry);
        dem_jut->setObjectName("dem_jut");

        gridLayout_3->addWidget(dem_jut, 0, 0, 1, 1);

        dem_jut_curvature = new QCheckBox(pageOrometry);
        dem_jut_curvature->setObjectName("dem_jut_curvature");

        gridLayout_3->addWidget(dem_jut_curvature, 0, 1, 1, 3);

        dem_rut = new QRadioButton(pageOrometry);
        dem_rut->setObjectName("dem_rut");

        gridLayout_3->addWidget(dem_rut, 1, 0, 1, 1);

        dem_zreduced_converging = new QRadioButton(pageOrometry);
        dem_zreduced_converging->setObjectName("dem_zreduced_converging");

        gridLayout_3->addWidget(dem_zreduced_converging, 2, 0, 1, 4);

        dem_zreduced_diverging = new QRadioButton(pageOrometry);
        dem_zreduced_diverging->setObjectName("dem_zreduced_diverging");

        gridLayout_3->addWidget(dem_zreduced_diverging, 3, 0, 1, 4);

        label_46 = new QLabel(pageOrometry);
        label_46->setObjectName("label_46");
        label_46->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_3->addWidget(label_46, 5, 0, 1, 1);

        label_50 = new QLabel(pageOrometry);
        label_50->setObjectName("label_50");
        label_50->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_3->addWidget(label_50, 4, 0, 1, 1);

        dem_zreduced_x = new QSpinBox(pageOrometry);
        dem_zreduced_x->setObjectName("dem_zreduced_x");
        dem_zreduced_x->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_3->addWidget(dem_zreduced_x, 4, 1, 1, 1);

        dem_zreduced_y = new QSpinBox(pageOrometry);
        dem_zreduced_y->setObjectName("dem_zreduced_y");
        dem_zreduced_y->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_3->addWidget(dem_zreduced_y, 4, 2, 1, 1);

        dem_jut_planetR = new QDoubleSpinBox(pageOrometry);
        dem_jut_planetR->setObjectName("dem_jut_planetR");
        dem_jut_planetR->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_jut_planetR->setDecimals(1);
        dem_jut_planetR->setMaximum(100000.000000000000000);
        dem_jut_planetR->setValue(6371.000000000000000);

        gridLayout_3->addWidget(dem_jut_planetR, 5, 1, 1, 2);

        btn_pickZReduced = new QPushButton(pageOrometry);
        btn_pickZReduced->setObjectName("btn_pickZReduced");
        btn_pickZReduced->setCheckable(true);

        gridLayout_3->addWidget(btn_pickZReduced, 4, 3, 1, 1);


        verticalLayout_13->addLayout(gridLayout_3);

        line_5 = new QFrame(pageOrometry);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_13->addWidget(line_5);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName("gridLayout_9");
        dem_deng2008_peakProto = new QRadioButton(pageOrometry);
        dem_deng2008_peakProto->setObjectName("dem_deng2008_peakProto");

        gridLayout_9->addWidget(dem_deng2008_peakProto, 0, 0, 1, 1);

        dem_deng2008_peakSimil = new QRadioButton(pageOrometry);
        dem_deng2008_peakSimil->setObjectName("dem_deng2008_peakSimil");

        gridLayout_9->addWidget(dem_deng2008_peakSimil, 1, 0, 1, 1);

        dem_deng2008_peakPercent = new QDoubleSpinBox(pageOrometry);
        dem_deng2008_peakPercent->setObjectName("dem_deng2008_peakPercent");
        dem_deng2008_peakPercent->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_deng2008_peakPercent->setDecimals(0);
        dem_deng2008_peakPercent->setMaximum(100.000000000000000);
        dem_deng2008_peakPercent->setSingleStep(5.000000000000000);
        dem_deng2008_peakPercent->setValue(20.000000000000000);

        gridLayout_9->addWidget(dem_deng2008_peakPercent, 1, 1, 1, 1);

        label_20 = new QLabel(pageOrometry);
        label_20->setObjectName("label_20");

        gridLayout_9->addWidget(label_20, 1, 2, 1, 1);


        verticalLayout_13->addLayout(gridLayout_9);

        line_6 = new QFrame(pageOrometry);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_13->addWidget(line_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        dem_nni = new QRadioButton(pageOrometry);
        dem_nni->setObjectName("dem_nni");

        horizontalLayout_7->addWidget(dem_nni);

        dem_nni_radius = new QDoubleSpinBox(pageOrometry);
        dem_nni_radius->setObjectName("dem_nni_radius");
        dem_nni_radius->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dem_nni_radius->setDecimals(1);
        dem_nni_radius->setMinimum(1.000000000000000);
        dem_nni_radius->setMaximum(100.000000000000000);
        dem_nni_radius->setValue(20.000000000000000);

        horizontalLayout_7->addWidget(dem_nni_radius);


        verticalLayout_13->addLayout(horizontalLayout_7);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setObjectName("horizontalLayout_46");
        horizontalLayout_46->setContentsMargins(20, -1, -1, -1);
        dem_nni_relative = new QCheckBox(pageOrometry);
        dem_nni_relative->setObjectName("dem_nni_relative");
        dem_nni_relative->setToolTipDuration(-2);

        horizontalLayout_46->addWidget(dem_nni_relative);

        labelTerrainNNI = new QLabel(pageOrometry);
        labelTerrainNNI->setObjectName("labelTerrainNNI");
        labelTerrainNNI->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_46->addWidget(labelTerrainNNI);


        verticalLayout_13->addLayout(horizontalLayout_46);

        label_53 = new QLabel(pageOrometry);
        label_53->setObjectName("label_53");
        label_53->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_13->addWidget(label_53);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_3);

        demToolbox->addItem(pageOrometry, QString::fromUtf8("Orometry"));

        verticalLayout_15->addWidget(demToolbox);

        tabWidgetR->addTab(tabDEM, QString());
        tabVoro = new QWidget();
        tabVoro->setObjectName("tabVoro");
        pushButton = new QPushButton(tabVoro);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(90, 20, 146, 36));
        pushButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        tabWidgetR->addTab(tabVoro, QString());

        gridLayout_12->addWidget(tabWidgetR, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1860, 29));
        menuSave = new QMenu(menubar);
        menuSave->setObjectName("menuSave");
        menuLoad = new QMenu(menubar);
        menuLoad->setObjectName("menuLoad");
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(hf_gridX, hf_gridY);
        QWidget::setTabOrder(hf_gridY, hf_kmX);
        QWidget::setTabOrder(hf_kmX, hf_kmY);
        QWidget::setTabOrder(hf_kmY, hf_elevMin);
        QWidget::setTabOrder(hf_elevMin, hf_elevMax);
        QWidget::setTabOrder(hf_elevMax, btn_updateDEM);
        QWidget::setTabOrder(btn_updateDEM, dem_wetness);
        QWidget::setTabOrder(dem_wetness, dem_streamArea);
        QWidget::setTabOrder(dem_streamArea, dem_streamPower);
        QWidget::setTabOrder(dem_streamPower, dem_sunlightLatitude);
        QWidget::setTabOrder(dem_sunlightLatitude, dem_streamArea_exp);

        menubar->addAction(menuLoad->menuAction());
        menubar->addAction(menuSave->menuAction());
        menuSave->addAction(actionSaveTexture);
        menuSave->addAction(actionSaveLayerMetric);
        menuSave->addAction(actionSaveLayerRivers);
        menuSave->addAction(actionSaveLayerRidges);
        menuSave->addAction(actionSaveMetric);
        menuLoad->addAction(actionLoadPNG);
        menuLoad->addAction(actionLoadASC);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(computeVoronoi()));

        cb_preset->setCurrentIndex(-1);
        tabWidgetR->setCurrentIndex(1);
        demToolbox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Terrain descriptors", nullptr));
        actionLoadPNG->setText(QCoreApplication::translate("MainWindow", "PNG...", nullptr));
#if QT_CONFIG(tooltip)
        actionLoadPNG->setToolTip(QCoreApplication::translate("MainWindow", "Load terrain from grayscale PNG", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLoadASC->setText(QCoreApplication::translate("MainWindow", "ASCII grid...", nullptr));
#if QT_CONFIG(tooltip)
        actionLoadASC->setToolTip(QCoreApplication::translate("MainWindow", "Load terrain from ASC format", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveTexture->setText(QCoreApplication::translate("MainWindow", "Combined texture...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveTexture->setToolTip(QCoreApplication::translate("MainWindow", "Save texture as PNG", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveLayerMetric->setText(QCoreApplication::translate("MainWindow", "Layer metric...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveLayerMetric->setToolTip(QCoreApplication::translate("MainWindow", "Save metric layer as a PNG", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveMetric->setText(QCoreApplication::translate("MainWindow", "Metric values...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveMetric->setToolTip(QCoreApplication::translate("MainWindow", "Save metric matrix as TXT", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveLayerRivers->setText(QCoreApplication::translate("MainWindow", "Layer rivers...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveLayerRivers->setToolTip(QCoreApplication::translate("MainWindow", "Save rivers layer as PNG", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveLayerRidges->setText(QCoreApplication::translate("MainWindow", "Layer ridges...", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveLayerRidges->setToolTip(QCoreApplication::translate("MainWindow", "Save ridges layer as PNG", nullptr));
#endif // QT_CONFIG(tooltip)
        Objects_groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Preset terrains", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "Dimensions", nullptr));
        label_preset->setText(QCoreApplication::translate("MainWindow", "0x0 cells, 0x0km", nullptr));
        label_58->setText(QCoreApplication::translate("MainWindow", "Rescale factor", nullptr));
        btn_loadPreset->setText(QCoreApplication::translate("MainWindow", "Load preset", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Terrain dimensions", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Cells", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Range", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Km", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Cellsize", nullptr));
        label_cellSize->setText(QCoreApplication::translate("MainWindow", "0 x 0 m", nullptr));
        btn_updateDEM->setText(QCoreApplication::translate("MainWindow", "Update height field", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Terrain modifiers", nullptr));
        btn_fillDepressions->setText(QCoreApplication::translate("MainWindow", "Fill depressions", nullptr));
        btn_breaching->setText(QCoreApplication::translate("MainWindow", "Breach depressions", nullptr));
        btn_gaussianSmooth->setText(QCoreApplication::translate("MainWindow", "Gaussian smoothing", nullptr));
        sb_gaussianBlur_radius->setSuffix(QCoreApplication::translate("MainWindow", " cells", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "radius", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "Light", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "Altitude", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "Azimuth", nullptr));
        dem_shadows->setText(QCoreApplication::translate("MainWindow", "Self-shadows", nullptr));
        dem_shading->setText(QCoreApplication::translate("MainWindow", "Terrain shading", nullptr));
        groupBox_palette->setTitle(QCoreApplication::translate("MainWindow", "Colormap", nullptr));
        cb_palette->setItemText(0, QCoreApplication::translate("MainWindow", "CoolWarm", nullptr));
        cb_palette->setItemText(1, QCoreApplication::translate("MainWindow", "Reds", nullptr));
        cb_palette->setItemText(2, QCoreApplication::translate("MainWindow", "Blues", nullptr));

        fixed_palette->setText(QCoreApplication::translate("MainWindow", "Fix palette", nullptr));
        labelPaletteRange->setText(QCoreApplication::translate("MainWindow", "Range", nullptr));
        sb_paletteMin->setSuffix(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Info cursor (right mouse button)", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Cell id", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Elevation", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "Metric", nullptr));
#if QT_CONFIG(tooltip)
        tabWidgetR->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        dem_uniform->setText(QCoreApplication::translate("MainWindow", "Uniform color", nullptr));
        dem_elevation->setText(QCoreApplication::translate("MainWindow", "Hypsometric gradient color", nullptr));
        dem_waterlevel->setText(QCoreApplication::translate("MainWindow", "Water level", nullptr));
        dem_waterlevel_m->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        dem_waterlevel_relief->setText(QCoreApplication::translate("MainWindow", "water depth", nullptr));
        dem_normals->setText(QCoreApplication::translate("MainWindow", "Normals", nullptr));
        dem_slopeGradient->setText(QCoreApplication::translate("MainWindow", "Slope (gradient norm)", nullptr));
        dem_slopeAvg->setText(QCoreApplication::translate("MainWindow", "Slope (average)", nullptr));
        dem_aspect->setText(QCoreApplication::translate("MainWindow", "Aspect (CW from N)", nullptr));
        dem_aspect_east->setText(QCoreApplication::translate("MainWindow", "Eastness", nullptr));
        dem_aspect_north->setText(QCoreApplication::translate("MainWindow", "Northness", nullptr));
        dem_laplacian->setText(QCoreApplication::translate("MainWindow", "Laplacian", nullptr));
        dem_fractLaplacian->setText(QCoreApplication::translate("MainWindow", "Fract Laplacian", nullptr));
        dem_fractLaplacian_s->setPrefix(QCoreApplication::translate("MainWindow", "s = ", nullptr));
        dem_fractLaplacian_n->setPrefix(QCoreApplication::translate("MainWindow", "n = ", nullptr));
        dem_asymmetry->setText(QCoreApplication::translate("MainWindow", "Hillslope asymmetry", nullptr));
        dem_asymmetryW->setPrefix(QCoreApplication::translate("MainWindow", "w = ", nullptr));
        dem_asymmetryDir->setSuffix(QCoreApplication::translate("MainWindow", " \302\272", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        dem_asymmetryDirTol->setSuffix(QCoreApplication::translate("MainWindow", " \302\272", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageMorhology), QCoreApplication::translate("MainWindow", "Local: elevation, gradient, laplacian", nullptr));
        dem_curv_fromQuadrics->setText(QCoreApplication::translate("MainWindow", "Curv. from quadric fit on w = ", nullptr));
        dem_curv_fromQuadrics_w->setSuffix(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "^2", nullptr));
        dem_curvMin->setText(QCoreApplication::translate("MainWindow", "Min curvature", nullptr));
        dem_curvMax->setText(QCoreApplication::translate("MainWindow", "Max curvature", nullptr));
        dem_curvMean->setText(QCoreApplication::translate("MainWindow", "Mean curvature", nullptr));
        dem_curvGaussian->setText(QCoreApplication::translate("MainWindow", "Gaussian curvature", nullptr));
        dem_curvProfile->setText(QCoreApplication::translate("MainWindow", "Profile curvature", nullptr));
        dem_curvContour->setText(QCoreApplication::translate("MainWindow", "Contour curvature", nullptr));
        dem_curvTangent->setText(QCoreApplication::translate("MainWindow", "Tangential curvature", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageCurvatures), QCoreApplication::translate("MainWindow", "Local: curvatures", nullptr));
        label_demRelief_radius->setText(QCoreApplication::translate("MainWindow", "Neighborhood window w =", nullptr));
        dem_localRelief_w->setSuffix(QString());
        label_18->setText(QCoreApplication::translate("MainWindow", "^2", nullptr));
        dem_tpi->setText(QCoreApplication::translate("MainWindow", "Topographic Position Index (TPI)", nullptr));
        dem_localRelief->setText(QCoreApplication::translate("MainWindow", "Local relief (h_max - h_min)", nullptr));
        dem_localVariance->setText(QCoreApplication::translate("MainWindow", "Local Variance", nullptr));
        dem_areaRatio->setText(QCoreApplication::translate("MainWindow", "Rugosity (area ratio)", nullptr));
        dem_ruggedness->setText(QCoreApplication::translate("MainWindow", "Terrain Ruggedness Index (TRI)", nullptr));
        dem_surfaceRoughness->setText(QCoreApplication::translate("MainWindow", "Surface Roughness (normals dispersion)", nullptr));
        dem_surfaceRoughnessStd->setText(QCoreApplication::translate("MainWindow", "Surface Roughness (normals spherical std)", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageRelief), QCoreApplication::translate("MainWindow", "Local: relief, ruggedness, roughness", nullptr));
        label_54->setText(QCoreApplication::translate("MainWindow", "Observer's height", nullptr));
        viewshed_offset->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
#if QT_CONFIG(tooltip)
        label_23->setToolTip(QCoreApplication::translate("MainWindow", "Downsamples the terrain before computing visibility, to speed up computations", nullptr));
#endif // QT_CONFIG(tooltip)
        label_23->setText(QCoreApplication::translate("MainWindow", "DEM rescale factor", nullptr));
        dem_viewshedLoc->setText(QCoreApplication::translate("MainWindow", "Viewshed from location", nullptr));
        btn_pickViewshedLocation->setText(QCoreApplication::translate("MainWindow", "Cursor pos", nullptr));
        dem_viewshedTotalOut->setText(QCoreApplication::translate("MainWindow", "Total viewshed (out, viewed area)", nullptr));
        dem_viewshedTotalIn->setText(QCoreApplication::translate("MainWindow", "Total viewshed (in, visible from)", nullptr));
        dem_viewshedTotal_sample->setText(QCoreApplication::translate("MainWindow", "Sample rays:", nullptr));
        dem_posOpenness->setText(QCoreApplication::translate("MainWindow", "Openness (positive)", nullptr));
        dem_negOpenness->setText(QCoreApplication::translate("MainWindow", "Openness (negative)", nullptr));
        label_55->setText(QCoreApplication::translate("MainWindow", "dirs", nullptr));
        dem_opennessDist->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        label_56->setText(QCoreApplication::translate("MainWindow", "radius", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "Samples", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", " Max dist", nullptr));
        dem_accessibilityRadius->setSuffix(QCoreApplication::translate("MainWindow", " km", nullptr));
        dem_accessibility->setText(QCoreApplication::translate("MainWindow", "Accessibility", nullptr));
        dem_skyview->setText(QCoreApplication::translate("MainWindow", "Sky-view factor (horizon)", nullptr));
        dem_skyviewApprox->setText(QCoreApplication::translate("MainWindow", "Sky-view factor approximation", nullptr));
        dem_sunlight->setText(QCoreApplication::translate("MainWindow", "Sunlight ", nullptr));
        dem_sunlightLatitude->setSuffix(QCoreApplication::translate("MainWindow", " \302\272", nullptr));
        dem_sunlightLatitude->setPrefix(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "latitude", nullptr));
        dem_dahi->setText(QCoreApplication::translate("MainWindow", "DAHI", nullptr));
        dem_dahiMax->setSuffix(QCoreApplication::translate("MainWindow", " \302\272", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "direction", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageVisibility), QCoreApplication::translate("MainWindow", "Visibility", nullptr));
        dem_showSingleLandform->setText(QCoreApplication::translate("MainWindow", "Mask single landform", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "      Name: ", nullptr));
        dem_landformName->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        dem_dikauWoodClass->setText(QCoreApplication::translate("MainWindow", "Curvatures", nullptr));
        dem_dikauWoodSolver_w->setPrefix(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "^2 window", nullptr));
        dem_fisher2004->setText(QCoreApplication::translate("MainWindow", "Fuzzy curvatures", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        dem_fisher2004entropy->setText(QCoreApplication::translate("MainWindow", "Fuzzy entropy", nullptr));
        dem_tpiClass->setText(QCoreApplication::translate("MainWindow", "TPI landforms", nullptr));
        dem_tpiClassSmall->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "vs", nullptr));
        dem_tpiClassLarge->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        dem_geomorphons->setText(QCoreApplication::translate("MainWindow", "Geomorphons", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "km", nullptr));
        dem_tophat->setText(QCoreApplication::translate("MainWindow", "Black/White Top Hat (Ridges / Rivers)", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "window", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "^2", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "t ridge / valley", nullptr));
        dem_tophat_peak->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        dem_tophat_valley->setSuffix(QCoreApplication::translate("MainWindow", " m", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageLandforms), QCoreApplication::translate("MainWindow", "Landforms", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "Flow algorithm", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Routing", nullptr));
        dem_streamArea_flowAlgorithm->setItemText(0, QCoreApplication::translate("MainWindow", "Steepest (D8)", nullptr));
        dem_streamArea_flowAlgorithm->setItemText(1, QCoreApplication::translate("MainWindow", "Multiple (MFD)", nullptr));
        dem_streamArea_flowAlgorithm->setItemText(2, QCoreApplication::translate("MainWindow", "Dinfinity", nullptr));
        dem_streamArea_flowAlgorithm->setItemText(3, QCoreApplication::translate("MainWindow", "Stochastic (Rho8)", nullptr));
        dem_streamArea_flowAlgorithm->setItemText(4, QCoreApplication::translate("MainWindow", "Kinematic", nullptr));

        label_29->setText(QCoreApplication::translate("MainWindow", "MFD exponent", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Rho8 iterations", nullptr));
        dem_streamArea_uniqueSource->setText(QCoreApplication::translate("MainWindow", "Downstream flow from source point:", nullptr));
        btn_pickStreamAreaSource->setText(QCoreApplication::translate("MainWindow", "Pick", nullptr));
        dem_streamArea->setText(QCoreApplication::translate("MainWindow", "Stream area", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        dem_streamAreaLog->setText(QCoreApplication::translate("MainWindow", "Stream area (log view)", nullptr));
        dem_wetness->setText(QCoreApplication::translate("MainWindow", "Wetness Index (TWI)", nullptr));
        dem_streamPower->setText(QCoreApplication::translate("MainWindow", "Stream power:", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "A ^", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "* S ^", nullptr));
        dem_streamPower_threshold->setText(QCoreApplication::translate("MainWindow", "Threshold SP >", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Using the D8 derived Rivers net (see tab)", nullptr));
        dem_depthToWater->setText(QCoreApplication::translate("MainWindow", "Depth to water (DTW)", nullptr));
        dem_hand->setText(QCoreApplication::translate("MainWindow", "Height above nearest drainage", nullptr));
        dem_riverDistEuclidean->setText(QCoreApplication::translate("MainWindow", "Distance to river (euclidean)", nullptr));
        dem_riverDistFlow->setText(QCoreApplication::translate("MainWindow", "Distance to river (along flow)", nullptr));
        dem_branchLength->setText(QCoreApplication::translate("MainWindow", "Branch length max", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageFlow), QCoreApplication::translate("MainWindow", "Hydrology", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Computation radius: ", nullptr));
        dem_orometryRadius->setSuffix(QCoreApplication::translate("MainWindow", " km", nullptr));
        dem_peakedness->setText(QCoreApplication::translate("MainWindow", "Peakedness (percentile)", nullptr));
        dem_ors->setText(QCoreApplication::translate("MainWindow", "ORS", nullptr));
        dem_jut->setText(QCoreApplication::translate("MainWindow", "Jut", nullptr));
        dem_jut_curvature->setText(QCoreApplication::translate("MainWindow", "Account for planet curvature", nullptr));
        dem_rut->setText(QCoreApplication::translate("MainWindow", "Rut", nullptr));
        dem_zreduced_converging->setText(QCoreApplication::translate("MainWindow", "Angle-reduced height (converging)", nullptr));
        dem_zreduced_diverging->setText(QCoreApplication::translate("MainWindow", "Angle-reduced height (diverging)", nullptr));
        label_46->setText(QCoreApplication::translate("MainWindow", "Planet R", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "Cell", nullptr));
        dem_jut_planetR->setSuffix(QCoreApplication::translate("MainWindow", " km", nullptr));
        btn_pickZReduced->setText(QCoreApplication::translate("MainWindow", "Pick", nullptr));
        dem_deng2008_peakProto->setText(QCoreApplication::translate("MainWindow", "Peak prototypicality", nullptr));
        dem_deng2008_peakSimil->setText(QCoreApplication::translate("MainWindow", "Peakness similarity", nullptr));
        dem_deng2008_peakPercent->setSuffix(QCoreApplication::translate("MainWindow", " %", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "centroid", nullptr));
        dem_nni->setText(QCoreApplication::translate("MainWindow", "Nearest Neighbor Index", nullptr));
        dem_nni_radius->setSuffix(QCoreApplication::translate("MainWindow", " km", nullptr));
        dem_nni_relative->setText(QCoreApplication::translate("MainWindow", "Relative to terrain NNI: ", nullptr));
        labelTerrainNNI->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_53->setText(QCoreApplication::translate("MainWindow", "Uses peaks filtered by prominence (see Ridges)", nullptr));
        demToolbox->setItemText(demToolbox->indexOf(pageOrometry), QCoreApplication::translate("MainWindow", "Orometry", nullptr));
        tabWidgetR->setTabText(tabWidgetR->indexOf(tabDEM), QCoreApplication::translate("MainWindow", "Metric", nullptr));
#if QT_CONFIG(accessibility)
        tabVoro->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pushButton->setText(QCoreApplication::translate("MainWindow", "Compute Voronoi Cells", nullptr));
        tabWidgetR->setTabText(tabWidgetR->indexOf(tabVoro), QCoreApplication::translate("MainWindow", "Voronoi", nullptr));
        menuSave->setTitle(QCoreApplication::translate("MainWindow", "Save", nullptr));
        menuLoad->setTitle(QCoreApplication::translate("MainWindow", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
