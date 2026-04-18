#ifndef TERRAINWIDGET_H
#define TERRAINWIDGET_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include "core.h"
#include "heightfield.h"
#include "celldecomposition.h"


class TerrainWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    TerrainWidget(QWidget* = nullptr);
    ~TerrainWidget();

    void setCamera(const Camera& cam) { camera = cam; };
    Camera getCamera() { return camera; }

    void setHeightfield(const HeightField& hf, bool centerCamera = true);
    void setTexture(const QImage& img);

    void setCursorStyle(float radius, const Vector3& color);
    void showCursor(const Vector3& worldPos);
    void hideCursor();

    void setDecomposition(CellDecomposition* decomp); 
    void changeRenderMode();
    void changeRenderCells();
    void changeRenderParticles();
    void changeRenderOriginal();
    
public slots:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void wheelEvent(QWheelEvent* event);

    void resetCamera();

signals:
    void glInitialized();
    void rayQueried(const Ray&);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int, int);
    virtual void paintGL();
    void checkGLError();

protected:

    // OpenGL render
    Box3 terrainBBox;
    GLuint meshVAO = 0;
    GLuint bufferVerts = 0, bufferIndices = 0;
    GLuint numTriangles = 0;
    GLuint texId = 0;
    GLuint skyboxVAO = 0;    
    QOpenGLShaderProgram shaderTerrain, shaderSkybox, shaderVoro;

    // Camera
    Camera camera;
    bool MoveAt = false;
    int x0 = 0, y0 = 0;
    Vector3 currentAt = Vector3(0);
    Vector3 toAt = Vector3(0);
    int stepAt = 0;
   

    // Cursor
    bool cursorEnabled;
    float cursorRadius;
    Vector3 cursorColor;
    Vector3 cursorPos;

    CellDecomposition* cellDecomp = nullptr;
    bool renderCells = true;
    bool renderParticles = false;
    bool renderOriginal = false;
};

#endif // TERRAINWIDGET_H
