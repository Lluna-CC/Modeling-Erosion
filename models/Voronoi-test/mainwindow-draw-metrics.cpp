#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <iostream>
#include <queue>

#define ColorRGB(r, g, b) Vector3((r) / 255.0, (g) / 255.0, (b) / 255.0)

LookupPalette MainWindow::paletteLandDW({
    ColorRGB(0, 0, 0),
    ColorRGB(230, 151, 1),      // 1. nose
    ColorRGB(128, 164, 32),     // 2. shoulder slope
    ColorRGB(242, 91, 115),     // 3. hollow shoulder
    ColorRGB(255, 210, 128),    // 4. spur
    ColorRGB(161, 255, 143),    // 5. planar slope
    ColorRGB(255, 87, 255),     // 6. hollow
    ColorRGB(255, 255, 1),      // 7. spur foot
    ColorRGB(57, 168, 1),       // 8. slope foot
    ColorRGB(169, 1, 230),      // 9. hollow foot
    ColorRGB(255, 16, 1),       // 10. peak
    ColorRGB(255, 85, 1),       // 11. ridge
    ColorRGB(192, 192, 192),    // 12. plain
    ColorRGB(159, 252, 255),    // 13. saddle
    ColorRGB(1, 197, 255),      // 14. channel
    ColorRGB(1, 64, 255)        // 15. pit
});
QVector<QString> MainWindow::namesLandDW({
     "unclassified", "nose", "shoulder slope", "hollow shoulder",
     "spur", "planar slope", "hollow", "spur foot",
     "slope foot", "hollow foot", "peak", "ridge",
     "plain", "saddle", "channel", "pit"
});

LookupPalette MainWindow::paletteLandTPI({  // color scheme defined in [Weiss 2001]
    ColorRGB(192, 192, 192),
    ColorRGB(169, 1, 230),    // canyons, deeply incised streams
    ColorRGB(255, 87, 255),   // midslope drainages, shallow valleys
    ColorRGB(1, 112, 255),    // upland drainages, headwaters
    ColorRGB(1, 197, 255),    // U-shape valleys
    ColorRGB(57, 168, 1),     // plains
    ColorRGB(161, 255, 143),  // open slopes
    ColorRGB(255, 255, 1),    // upper slopes, mesas
    ColorRGB(255, 210, 128),  // local ridges/hills in valleys
    ColorRGB(230, 151, 1),    // midslope ridges, small hills in plains
    ColorRGB(255, 85, 1)      // peak
});
QVector<QString> MainWindow::namesLandTPI({
     "unclassified", "canyons, deeply incised streams", "midslope drainages, shallow valleys", "upland drainages, headwaters",
     "U-shape valleys", "plains", "open slopes", "upper slopes, mesas",
     "local ridges/hills in valleys", "midslope ridges, small hills in plains", "peaks, ridges"
});

LookupPalette MainWindow::paletteLandGeomorphons({
    ColorRGB(128, 128, 128), // 0. flat
    ColorRGB(255, 85, 1),    // 1. peak
    ColorRGB(230, 151, 1),   // 2. ridge
    ColorRGB(255, 210, 128), // 3. shoulder
    ColorRGB(161, 255, 143), // 4. hollow
    ColorRGB(57, 168, 1),    // 5. slope
    ColorRGB(255, 255, 1),   // 6. spur
    ColorRGB(1, 197, 255),   // 7. footslope
    ColorRGB(255, 87, 255),  // 8. valley
    ColorRGB(169, 1, 230),   // 9. pit
});
QVector<QString> MainWindow::namesLandGeomorphons({
     "flat", "peak", "ridge", "shoulder",
     "hollow", "slope", "spur", "footslope",
     "valley", "pit"
});


void MainWindow::computeLightmap(bool doShadows)
{
    double aAzimuth  = Math::DegreeToRadian(ui->light_azimuth->value());
    double aAltitude = Math::DegreeToRadian(ui->light_altitude->value());

    // note that azimuth is given CW from N
    lightDirection = Vector3(std::cos(aAltitude)*std::sin(aAzimuth),
                             std::cos(aAltitude)*std::cos(aAzimuth),
                             std::sin(aAltitude));

    lightMap  = hf.DirectLight(lightDirection);
    if (doShadows) {
        shadowMap = hf.SelfShadow(lightDirection);
    }
}

QImage MainWindow::shadeMap(const QImage& img, int shadeType, bool shadows) const
{
    QImage shading = img.copy();
    for (int i = 0; i < shading.width(); i++) {
        for (int j = 0; j < shading.height(); j++) {
            QColor qc = img.pixelColor(i, j);
            Vector3 cz = Vector3(qc.redF(), qc.greenF(), qc.blueF());

            Vector3 c;
            switch(shadeType) {
            case 1: { // Cosine like
                double s = lightMap.at(i, j);
                s *= s;
                c = 0.2 * Vector3(1.0, 1.0, 1.0) + 0.6 * s * cz + 0.2 * s * Vector3(1.0, 1.0, 1.0);
                break;
            }
            case 2: { // Normal
                Vector3 n = hf.Normal(i, j);
                double s = n * lightDirection; //Normalized(Vector3(-2.0, 1.0, 4.0));
                s = 0.5 * (1.0 + s);
                s *= s;
                s *= s;
                Vector3 cn = Math::Lerp(Vector3(52, 78, 118)/255.0, cz, s);
                c = 0.15 * Vector3(0.975, 0.975, 0.975) + 0.85 * cn;
                break;
            }
            case 3: { // Relief
                Vector3 n = hf.Normal(i, j);
                double s = n * lightDirection; //Normalized(Vector3(1.0, 0.5, 2.5));
                s = 0.5 * (1.0 + s);
                s *= s;
                s *= s;
                double t = Vector2(n) * Normalized(Vector2(1, 1));
                t = 0.5 * (1.0 + t);
                Vector3 cn = s * Math::Lerp(Vector3(0.65, 0.75, 0.85), Vector3(1.00, 0.95, 0.80), t);
                c = 0.25 * Vector3(0.975, 0.975, 0.975) + 0.25 * cz + 0.50 * cn;
                break;
            }
            default:
                c = cz;
                break;
            }

            if (shadows) {
                c = c * (0.7*shadowMap.at(i, j) + 0.3);
            }

            shading.setPixelColor(i, j, toQColor(c).rgb());
        }
    }

    return shading;
}


QImage singleLandformImage(const IntField2& lands, int v, const QColor& colorLand = Qt::red, const QColor& colorBg = Qt::white)
{
    QImage img(lands.getSizeX(), lands.getSizeY(), QImage::Format_RGBA8888);
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            if (lands.at(i, j) == v) {
                img.setPixelColor(i, j, colorLand);
            }
            else {
                img.setPixelColor(i, j, colorBg);
            }
         }
    }
    return img;
}

QImage thresholdImage(const ScalarField2& field, int v, const QColor& colorPos = Qt::red, const QColor& colorNeg = Qt::white)
{
    QImage img(field.getSizeX(), field.getSizeY(), QImage::Format_RGBA8888);
    for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
            if (field.at(i, j) > v) {
                img.setPixelColor(i, j, colorPos);
            }
            else {
                img.setPixelColor(i, j, colorNeg);
            }
         }
    }
    return img;
}


ColorPalette MainWindow::getPalette(const ColorPalette& preferred) const
{
    if (!ui->fixed_palette->isChecked())
        return preferred;

    switch (ui->cb_palette->currentIndex()) {
        case 0: return ColorPalette::CoolWarm();
        case 1: return ColorPalette::Reds();
        case 2: return ColorPalette::Blues();
        default: return ColorPalette::CoolWarm();
    }
}

void getPaletteRange(const std::vector<double>& range, bool centered, double& rMin, double& rMax)
{
    if (centered) {
        double r = std::max(std::abs(range[0]), std::abs(range[1]));
        rMin = -r;
        rMax =  r;
    }
    else {
        rMin = range[0];
        rMax = range[1];
    }
}


void MainWindow::computeMetric()
{
    // LOCAL
    if (ui->dem_slopeGradient->isChecked()) {
        currentMetric = hf.GradientNorm();
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_slopeAvg->isChecked()) {
        currentMetric = hf.SlopeAverage();
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_aspect->isChecked()) {
        currentMetric = hf.Aspect();
        paletteDefault = ColorPalette::CoolWarm();
        paletteMin = 0;
        paletteMax = 2*Math::Pi;
    }
    else if (ui->dem_aspect_east->isChecked()) {
        currentMetric = hf.Aspect();
        for (int i = 0; i < currentMetric.getNumElements(); i++)
            currentMetric[i] = std::sin(currentMetric[i]);
        paletteDefault = ColorPalette::Reds();
        paletteMin = -1;
        paletteMax = 1;
    }
    else if (ui->dem_aspect_north->isChecked()) {
        currentMetric = hf.Aspect();
        for (int i = 0; i < currentMetric.getNumElements(); i++)
            currentMetric[i] = std::cos(currentMetric[i]);
        paletteDefault = ColorPalette::Reds();
        paletteMin = -1;
        paletteMax = 1;
    }

    // LAPLACIAN
    else if (ui->dem_laplacian->isChecked()) {
        currentMetric = hf.Laplacian();
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.01, 0.99}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_fractLaplacian->isChecked()) {
        currentMetric = hf.FractLaplacian(ui->dem_fractLaplacian_s->value(), ui->dem_fractLaplacian_n->value());
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.01, 0.99}), true, paletteMin, paletteMax);
    }

    // ASYMMETRY
    else if (ui->dem_asymmetry->isChecked()) {
        currentMetric = hf.HillslopeAsymmetry(ui->dem_asymmetryW->value(), ui->dem_asymmetryDir->value(), ui->dem_asymmetryDirTol->value());
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.01, 0.99}), true, paletteMin, paletteMax);
    }

    // CURVATURES
    else if (ui->dem_curvMin->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::MIN,
                                     ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.1, 0.9}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_curvMax->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::MAX,
                                     ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.1, 0.9}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_curvMean->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::MEAN,
                                     ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.1, 0.9}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_curvGaussian->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::GAUSSIAN,
                                     ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.01, 0.99}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_curvProfile->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::PROFILE,
                                     ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.1, 0.9}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_curvContour->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::CONTOUR,
                                     ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.1, 0.9}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_curvTangent->isChecked()) {
        currentMetric = hf.Curvature(HeightField::CurvatureType::TANGENTIAL,
                                         ui->dem_curv_fromQuadrics->isChecked() ? ui->dem_curv_fromQuadrics_w->value() : 0);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.1, 0.9}), true, paletteMin, paletteMax);
    }

    // RELIEF
    else if (ui->dem_localRelief->isChecked()) {
        currentMetric = hf.LocalRelief(ui->dem_localRelief_w->value());
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_localVariance->isChecked()) {
        currentMetric = hf.LocalVariance(ui->dem_localRelief_w->value());
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_areaRatio->isChecked()) {
        currentMetric = hf.AreaRatio(ui->dem_localRelief_w->value());
        paletteDefault = ColorPalette::Reds();
        paletteMin = 1;
        paletteMax = currentMetric.percentile(0.999);
    }
    else if (ui->dem_tpi->isChecked()) {
        currentMetric = hf.TopographicPositionIndexSAT(ui->dem_localRelief_w->value());
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_ruggedness->isChecked()) {
        currentMetric = hf.RuggednessIndex(ui->dem_localRelief_w->value());
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_surfaceRoughness->isChecked()) {
        currentMetric = hf.SurfaceRoughnessSAT(ui->dem_localRelief_w->value(), false);
        paletteDefault = ColorPalette::Reds();
        paletteMin = 0;
        paletteMax = currentMetric.percentile(0.999);
    }
    else if (ui->dem_surfaceRoughnessStd->isChecked()) {
        currentMetric = hf.SurfaceRoughnessSAT(ui->dem_localRelief_w->value(), true);
        paletteDefault = ColorPalette::Reds();
        paletteMin = 0;
        paletteMax = currentMetric.percentile(0.999);
    }

    // VISIBILITY
    else if (ui->dem_viewshedTotalIn->isChecked()) {
        double s = ui->viewshed_rescale->value();
        HeightField hfLow = hf.setResolution(int(s*hf.getSizeX()), int(s*hf.getSizeY()));
        ScalarField2 view;
        if (ui->dem_viewshedTotal_sample->isChecked() && ui->dem_viewshedTotal_numSamples->value() < hf.getNumElements())
            view = hfLow.ViewshedTotalSampled(ui->dem_viewshedTotal_numSamples->value(), false, ui->viewshed_offset->value());
        else
            view = hfLow.ViewshedTotal(false, ui->viewshed_offset->value());
        view *= 1.0/view.getNumElements();
        currentMetric = view.setResolution(hf.getSizeX(), hf.getSizeY());
        paletteDefault = ColorPalette::Reds();
        currentMetric.getRange(paletteMin, paletteMax);
        paletteMin = 0;
    }
    else if (ui->dem_viewshedTotalOut->isChecked()) {
        double s = ui->viewshed_rescale->value();
        HeightField hfLow = hf.setResolution(int(s*hf.getSizeX()), int(s*hf.getSizeY()));
        ScalarField2 view;
        if (ui->dem_viewshedTotal_sample->isChecked() && ui->dem_viewshedTotal_numSamples->value() < hf.getNumElements())
            view = hfLow.ViewshedTotalSampled(ui->dem_viewshedTotal_numSamples->value(), true, ui->viewshed_offset->value());
        else
            view = hfLow.ViewshedTotal(true, ui->viewshed_offset->value());
        view *= 1.0/view.getNumElements();
        currentMetric = view.setResolution(hf.getSizeX(), hf.getSizeY());
        paletteDefault = ColorPalette::Reds();
        currentMetric.getRange(paletteMin, paletteMax);
        paletteMin = 0;
    }
    else if (ui->dem_accessibility->isChecked()) {
        double r = ui->dem_accessibilityRadius->value();
        if (r <= 0) r = 2*hf.getDomain().radius();
        currentMetric = hf.Accessibility(r, ui->dem_accessibilitySamples->value());
        paletteDefault = ColorPalette::Reds();
        paletteMin = 0.5;
        paletteMax = 1.0;
    }
    else if (ui->dem_skyview->isChecked()) {
        double r = ui->dem_accessibilityRadius->value();
        if (r <= 0) r = 2*hf.getDomain().radius();
        currentMetric = hf.Accessibility(r, ui->dem_accessibilitySamples->value(), true);
        paletteDefault = ColorPalette::Reds();
        paletteMin = 0.5;
        paletteMax = 1.0;
    }
    else if (ui->dem_skyviewApprox->isChecked()) {
        currentMetric = hf.SkyViewFactorApproximation();
        paletteDefault = ColorPalette::Reds();
        paletteMin = 0.5;
        paletteMax = 1.0;
    }
    else if (ui->dem_posOpenness->isChecked()) {
        currentMetric = hf.Openness(true, ui->dem_opennessDist->value(), ui->dem_opennessDirs->value());
        paletteDefault = ColorPalette::CoolWarm();
        paletteMin = Math::Pi / 3;
        paletteMax = 2 * Math::Pi / 3;
    }
    else if (ui->dem_negOpenness->isChecked()) {
        currentMetric = hf.Openness(false, ui->dem_opennessDist->value(), ui->dem_opennessDirs->value());
        paletteDefault = ColorPalette::CoolWarm();
        paletteMin = Math::Pi / 3;
        paletteMax = 2 * Math::Pi / 3;
    }
    else if (ui->dem_sunlight->isChecked()) {
        currentMetric = hf.Sun(ui->dem_sunlightLatitude->value(), 14, 24, 7, 12);
        paletteDefault = ColorPalette::Reds();
        currentMetric.getRange(paletteMin, paletteMax);
        paletteMin = 0;
    }
    else if (ui->dem_dahi->isChecked()) {
        currentMetric = hf.DiurnalAnisotropicHeatIndex(Math::DegreeToRadian(ui->dem_dahiMax->value()));
        paletteDefault = ColorPalette::Reds();
        paletteMin = -0.65;
        paletteMax =  0.65;
    }

    // HYDROLOGY
    else if (ui->dem_streamArea->isChecked() || ui->dem_streamAreaLog->isChecked()
             || ui->dem_wetness->isChecked() || ui->dem_streamPower->isChecked())
    {
        std::vector<Index2> sources;
        if (ui->dem_streamArea_uniqueSource->isChecked()) {
            sources.push_back(Index2(ui->dem_streamArea_source_x->value(), ui->dem_streamArea_source_y->value()));
        }

        ScalarField2 sa;
        switch (ui->dem_streamArea_flowAlgorithm->currentIndex()) {
            case 0: sa = hf.StreamAreaD8(sources); break;
            case 1: sa = hf.StreamAreaMFD(sources, ui->dem_streamArea_mfdExp->value()); break;
            case 2: sa = hf.StreamAreaDinf(sources); break;
            case 3: sa = hf.StreamAreaRho8(sources, ui->dem_streamArea_rho8iters->value()); break;
            case 4: sa = hf.StreamAreaKinematic(sources); break;
        }

        if (ui->dem_wetness->isChecked()) {
            currentMetric = hf.WetnessIndex(sa);
            getPaletteRange(currentMetric.percentiles({0.01, 0.99}), false, paletteMin, paletteMax);
        }
        else if (ui->dem_streamPower->isChecked()) {
            currentMetric = hf.StreamPower(sa, ui->dem_streamPower_m->value(), ui->dem_streamPower_n->value());
            getPaletteRange(currentMetric.percentiles({0.01, 0.99}), false, paletteMin, paletteMax);
        }
        else {
            for (int i = 0; i < sa.getNumElements(); i++) {
                if (ui->dem_streamArea->isChecked())
                    sa[i] = std::pow(sa.at(i), ui->dem_streamArea_exp->value());
                else if (ui->dem_streamAreaLog->isChecked())
                    sa[i] = std::log(sa.at(i));
            }
            currentMetric = sa;
            paletteMin = 1;
            paletteMax = currentMetric.percentile(0.999);
        }
        paletteDefault = ColorPalette::Blues();
    }
   

    else if (ui->dem_peakedness->isChecked()) {
        currentMetric = hf.PeakPercentage(ui->dem_orometryRadius->value()*1000);
        paletteDefault = ColorPalette::Reds();
        paletteMin = 0;
        paletteMax = 1;
    }
    else if (ui->dem_ors->isChecked()) {
        currentMetric = hf.ORS(ui->dem_orometryRadius->value()*1000);
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_jut->isChecked()) {
        if (ui->dem_jut_curvature->isChecked())
            currentMetric = hf.JutCurved(ui->dem_orometryRadius->value()*1000, ui->dem_jut_planetR->value()*1000);
        else
            currentMetric = hf.JutPlanar(ui->dem_orometryRadius->value()*1000);
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_rut->isChecked()) {
        if (ui->dem_jut_curvature->isChecked())
            currentMetric = hf.RutCurved(ui->dem_orometryRadius->value()*1000, ui->dem_jut_planetR->value()*1000);
        else
            currentMetric = hf.RutPlanar(ui->dem_orometryRadius->value()*1000);
        paletteDefault = ColorPalette::Reds();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), false, paletteMin, paletteMax);
    }
    else if (ui->dem_zreduced_converging->isChecked()) {
        currentMetric = hf.AngleReducedHeight(ui->dem_jut_planetR->value()*1000,
                                              ui->dem_zreduced_x->value(), ui->dem_zreduced_y->value(), true);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_zreduced_diverging->isChecked()) {
        currentMetric = hf.AngleReducedHeight(ui->dem_jut_planetR->value()*1000,
                                              ui->dem_zreduced_x->value(), ui->dem_zreduced_y->value(), false);
        paletteDefault = ColorPalette::CoolWarm();
        getPaletteRange(currentMetric.percentiles({0.001, 0.999}), true, paletteMin, paletteMax);
    }
    else if (ui->dem_deng2008_peakProto->isChecked() || ui->dem_deng2008_peakSimil->isChecked()) {
        ScalarField2 peakProto;
        ScalarField2 peakSimil = hf.Peakness(peakProto, ui->dem_deng2008_peakPercent->value()/100.0);
        if (ui->dem_deng2008_peakProto->isChecked())
            currentMetric = peakProto;
        else
            currentMetric = peakSimil;
        paletteDefault = ColorPalette::Reds();
        currentMetric.getRange(paletteMin, paletteMax);
    }

  
}

void MainWindow::computeBaseTexture(bool updateMetric)
{
    shadeType = 1;
    const QColor whiteFill = QColor(232, 232, 232);

    // first the descriptors with a fixed palette, then the general case with UI-configurable palette

    // plain model
    if (ui->dem_uniform->isChecked()) {
        baseTexture = QImage(hf.getSizeX(), hf.getSizeY(), QImage::Format_RGBA8888);
        baseTexture.fill(whiteFill);
        shadeType = 1;
        currentMetric = hf;
    }

    // hypsometric gradient
    else if (ui->dem_elevation->isChecked()) {
        double zmin = hf.getBox().getMin()[2];
        double zmax = hf.getBox().getMax()[2];
        baseTexture = hf.createImage(zmin, zmin + (zmax - zmin)/0.75, ColorPalette::Relief());
        shadeType = 3;
        currentMetric = hf;
    }

    // water level
    else if (ui->dem_waterlevel->isChecked()) {
        double waterLevel = ui->dem_waterlevel_m->value();
        bool relief = ui->dem_waterlevel_relief->isChecked();
        baseTexture = QImage(hf.getSizeX(), hf.getSizeY(), QImage::Format_RGBA8888);
        baseTexture.fill(whiteFill);
        for (int i = 0; i < baseTexture.width(); i++) {
            for (int j = 0; j < baseTexture.height(); j++) {
                if (hf.at(i, j) < waterLevel) {
                    if (relief) {
                        double u = std::max(0.0, 1 - (waterLevel - hf.at(i, j)) / 1000.0);
                        Vector3 col = Math::Lerp(Vector3(18, 53, 102), Vector3(52, 135, 255), u)/255.0;
                        baseTexture.setPixelColor(i, j, toQColor(col));
                    }
                    else {
                        baseTexture.setPixelColor(i, j, QColor(48, 128, 255, 255));
                    }
                }
            }
        }
        shadeType = 1;
        currentMetric = hf;
    }

    // normal map
    else if (ui->dem_normals->isChecked()) {
        baseTexture = QImage(hf.getSizeX(), hf.getSizeY(), QImage::Format_RGBA8888);
        for (int i = 0; i < hf.getSizeX(); i++) {
            for (int j = 0; j < hf.getSizeY(); j++) {
                Vector3 n = 0.5 * (hf.Normal(i, j) + Vector3(1));
                baseTexture.setPixelColor(i, j, toQColor(Vector3(n[0], n[1], n[2])));
            }
        }
        shadeType = 0;
        currentMetric = hf;
    }

    // binary viewshed
    else if (ui->dem_viewshedLoc->isChecked()) {
        double s = ui->viewshed_rescale->value();
        HeightField hfLow = hf.setResolution(int(s*hf.getSizeX()), int(s*hf.getSizeY()));

        int vpx = ui->viewshed_location_x->value();
        int vpy = ui->viewshed_location_y->value();
        double offset = ui->viewshed_offset->value();

        int visCells;
        ScalarField2 view = hfLow.Viewshed(hf.Vertex(vpx, vpy) + Vector3(0, 0, offset), visCells);

        baseTexture = QImage(hfLow.getSizeX(), hfLow.getSizeY(), QImage::Format_RGBA8888);
        baseTexture.fill(whiteFill);
        for (int i = 0; i < baseTexture.width(); i++) {
            for (int j = 0; j < baseTexture.height(); j++) {
                if (view.at(i, j) > 0) baseTexture.setPixelColor(i, j, Qt::red);
            }
        }
        baseTexture = baseTexture.scaled(QSize(hf.getSizeX(), hf.getSizeY()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        baseTexture.setPixelColor(vpx, vpy, Qt::green);
        currentMetric = view.setResolution(hf.getSizeX(), hf.getSizeY());
    }

    // landforms
    else if (ui->dem_dikauWoodClass->isChecked()) {
        ui->dem_showSingleLandform_id->setMaximum(namesLandDW.size() - 1);
        ui->dem_landformName->setText(namesLandDW[ui->dem_showSingleLandform_id->value()]);

        IntField2 lands = hf.LandformsDikauWood(ui->dem_dikauWoodSolver_w->value(), 0.1, 0.0001);
        if (ui->dem_showSingleLandform->isChecked())
            baseTexture = singleLandformImage(lands, ui->dem_showSingleLandform_id->value());
        else
            baseTexture = lands.createImage(paletteLandDW);
        currentMetric = lands.toScalarField();
    }
    else if (ui->dem_fisher2004->isChecked() || ui->dem_fisher2004entropy->isChecked()) {
        ScalarField2 entropy(hf.getDomain(), hf.getSizeX(), hf.getSizeY());
        double tCurv = 0.0001;
        double tSlope = 0.1;
        int minScale = ui->dem_fisher2004_minScale->value();
        int maxScale = ui->dem_fisher2004_maxScale->value();
        IntField2 lands = hf.LandformsFuzzyDW(entropy, minScale, maxScale, tSlope, tCurv);

        if (ui->dem_fisher2004entropy->isChecked()) {
            ui->dem_showSingleLandform_id->setMaximum(0);
            ui->dem_landformName->setText("-");

            baseTexture = entropy.createImage(ColorPalette::Reds());
            currentMetric = entropy;
        }
        else {
            ui->dem_showSingleLandform_id->setMaximum(namesLandDW.size() - 1);
            ui->dem_landformName->setText(namesLandDW[ui->dem_showSingleLandform_id->value()]);

            if (ui->dem_showSingleLandform->isChecked())
                baseTexture = singleLandformImage(lands, ui->dem_showSingleLandform_id->value());
            else
                baseTexture = lands.createImage(paletteLandDW);
            currentMetric = lands.toScalarField();
        }
    }
    else if (ui->dem_tpiClass->isChecked()) {
        ui->dem_showSingleLandform_id->setMaximum(namesLandTPI.size() - 1);
        ui->dem_landformName->setText(namesLandTPI[ui->dem_showSingleLandform_id->value()]);

        IntField2 lands = hf.LandformsTPI(ui->dem_tpiClassSmall->value(), ui->dem_tpiClassLarge->value());
        if (ui->dem_showSingleLandform->isChecked())
            baseTexture = singleLandformImage(lands, ui->dem_showSingleLandform_id->value());
        else
            baseTexture = lands.createImage(paletteLandTPI);
        currentMetric = lands.toScalarField();
    }
    else if (ui->dem_geomorphons->isChecked()) {
        ui->dem_showSingleLandform_id->setMaximum(namesLandGeomorphons.size() - 1);
        ui->dem_landformName->setText(namesLandGeomorphons[ui->dem_showSingleLandform_id->value()]);

        IntField2 lands = hf.Geomorphons(ui->dem_geomorphons_km->value() * 1000.0);
        if (ui->dem_showSingleLandform->isChecked())
            baseTexture = singleLandformImage(lands, ui->dem_showSingleLandform_id->value());
        else
            baseTexture = lands.createImage(paletteLandGeomorphons);
        currentMetric = lands.toScalarField();
    }
    else if (ui->dem_tophat->isChecked()) {
        ui->dem_showSingleLandform_id->setMaximum(0);
        ui->dem_landformName->setText("-");

        int w = ui->dem_tophat_w->value();
        double tPeak = ui->dem_tophat_peak->value();
        double tValley = ui->dem_tophat_valley->value();
        currentMetric = hf.BlackWhiteTopHatTransform(w, tPeak, tValley);
        baseTexture = currentMetric.createImage(ColorPalette::CoolWarm());
    }

    // all the rest, the palette is controlled via UI so we do not want
    // to recompute the metric every time the range is modified
    else {
        if (updateMetric) {
            computeMetric();
            updatePaletteRangeSelectors();
            updateCursorInfoTexts();
        }
        baseTexture = currentMetric.createImage(ui->sb_paletteMin->value() * paletteScale,
                                                ui->sb_paletteMax->value() * paletteScale,
                                                getPalette(paletteDefault));

        // some metrics still require a special treatment
        if (ui->dem_streamPower->isChecked() && ui->dem_streamPower_threshold->isChecked()) {
            baseTexture = thresholdImage(currentMetric, ui->dem_streamPower_t->value());
        }
        else if (ui->dem_zreduced_converging->isChecked() || ui->dem_zreduced_diverging->isChecked()) {
            baseTexture.setPixelColor(ui->dem_zreduced_x->value(), ui->dem_zreduced_y->value(), Qt::green);
        }
    }

}



inline QPointF getScaledPoint(const Index2& off, int scale = 1)
{
  return QPointF(scale * (off.x() + 0.5), scale * (off.y() + 0.5));
}

QColor interpolateColor(const QColor &color1, const QColor &color2, double t) {
    t = Math::Clamp(t, 0.0, 1.0);
    int r = static_cast<int>(color1.red() + (color2.red() - color1.red()) * t);
    int g = static_cast<int>(color1.green() + (color2.green() - color1.green()) * t);
    int b = static_cast<int>(color1.blue() + (color2.blue() - color1.blue()) * t);
    return QColor(r, g, b);
}

