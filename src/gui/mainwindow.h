#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>

#include "application/application.h"
#include "graphics/graphicsfactory.h"

#include "enums.h"
#include "terrain/generators/dsgenerator.h"
#include "terrain/generators/mdsgenerator.h"
#include "terrain/generators/pngenerator.h"
#include "primitives/clipping_space.h"
#include "shaders/shader_types.h"

namespace Ui
{ class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateSceneByLightSources();
    void updateLandscapePaint();

private slots:
    void on_genLandscapeBtn_clicked();

    void on_closeVPBtn_clicked();

    void on_launch_btn_clicked();

    void keyPressEvent(QKeyEvent *event) override;

    void on_loadBtn_clicked();

    void on_saveBtn_clicked();

    void on_deformBtn_clicked();

    void on_orthoRB_toggled(bool checked);
    void on_perspectiveRB_toggled(bool checked);

    void on_simpleShadingRB_toggled(bool checked);
    void on_gouraudShadingRB_toggled(bool checked);
    void on_frameModelRB_toggled(bool checked);

    void on_addLandscapeWater_toggled(bool checked);
    void on_maxHeightSB_valueChanged(double value);
    void on_waterLevelSB_valueChanged(double value);

    void on_updateSceneBtn_clicked();

    void on_genLightmapsBtn_clicked();
    void on_removeLSBtn_clicked();

    void on_nextLightmapBtn_clicked();
    void on_useLightmapCB_toggled(bool checked);

    void on_shadowEnableCB_toggled(bool checked);

    void on_landTypeIslandRB_toggled(bool checked);
    void on_landTypeAtolRB_toggled(bool checked);
    void on_landTypeRandomRB_toggled(bool checked);

    void on_saveSettingsBtn_clicked();
    void on_takeScreenshotBtn_clicked();

private:
    void setup_scene();
    void update_main_scene();
    void update_heightmap_scene();
    void update_lightmap_scene();
    void setup_terrain();
    void setup_shadows();

    LandscapeGeneratorType getLandscapeType();
    std::size_t getOctavesCnt();
    SurfaceType getSurfaceType();
    CornerHeights getCornerHeights();
    float getRoughness();
    std::string getLoadPath();
    std::string getSavePath();
    ClipSpaceType getClipSpaceType();
    ShaderType getShaderType();
    size_t getSettingsViwportHeight();
    size_t getSettingsViwportWidth();

    vec3<> QColor2vec3(QColor clr);

    std::shared_ptr<QMessageBox> produceWarningMessage(const char *content, const char *title = "Warning!");

private:
    Ui::MainWindow *ui;
    QGraphicsScene *main_scene;
    QGraphicsScene *lightmap_scene;
    QGraphicsScene *heightmap_scene;
    std::shared_ptr<Application> _app;
    std::shared_ptr<BaseDrawer> _main_drawer;
    std::shared_ptr<BaseDrawer> _heightmap_drawer;
    std::shared_ptr<BaseDrawer> _lightmap_drawer;
    std::shared_ptr<BaseDrawer> _shadow_drawer;
};

#endif // MAINWINDOW_H
