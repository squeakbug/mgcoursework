#include <string>
#include <memory>

#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

#include "gui/mainwindow.h"
#include "gui/ui_mainwindow.h"

#include "graphics/qt/qt_factory.h"
#include "graphics/glfw/glfw_factory.h"
#include "graphics/dynamic_qt/dynamic_qt_factory.h"
#include "commands/application_commands.h"
#include "shaders/shader_types.h"

const size_t defaultViewportHeight = 480;
const size_t defaultViewportWidth = 720;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setup_scene();

    _app = Application::instance();

    QObject::connect(ui->verticalWidget_2, &LightManagerWidget::recordsChanged, this, &MainWindow::updateSceneByLightSources);
    QObject::connect(ui->verticalWidget_3, &GradientSlider::gradientChanged, this, &MainWindow::updateLandscapePaint);
}

void MainWindow::setup_scene()
{
    heightmap_scene = new QGraphicsScene(this);
    lightmap_scene = new QGraphicsScene(this);

    heightmap_scene->setSceneRect(0, 0, ui->graphicsView_2->width(), ui->graphicsView_2->height());
    lightmap_scene->setSceneRect(0, 0, ui->graphicsView_3->width(), ui->graphicsView_3->height());

    ui->graphicsView_2->setScene(heightmap_scene);
    ui->graphicsView_3->setScene(lightmap_scene);

    ui->graphicsView_2->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView_3->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* Одна фабрика -> несколько drawers; для каждого устанавливается BaseScene */
    std::shared_ptr<GraphicsFactory> main_factory(new GLFWFactory());
    _main_drawer = main_factory->create_graphics(defaultViewportWidth, defaultViewportHeight);
    _shadow_drawer = main_factory->create_graphics(defaultViewportWidth * 2, defaultViewportHeight * 2);

    std::shared_ptr<GraphicsFactory> heightmap_factory(new QtFactory(heightmap_scene));
    _heightmap_drawer = heightmap_factory->create_graphics(heightmap_scene->width(), heightmap_scene->height());

    std::shared_ptr<GraphicsFactory> lightmap_factory(new QtFactory(lightmap_scene));
    _lightmap_drawer = lightmap_factory->create_graphics(lightmap_scene->width(), lightmap_scene->height());

    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetFragmentShaderCommand>(_main_drawer, ShaderType::FRAG_GOURAUD);
    _app->execute(*cmd);

    //TODO get type from ui
    cmd = std::make_shared<SetRandomLandscapeMaskCommand>();
    _app->execute(*cmd);

    std::shared_ptr<Gradient> gradient = ui->verticalWidget_3->getAsGradient();
    cmd = std::make_shared<SetupLandscapeGradientCommand>(gradient);
    _app->execute(*cmd);

    cmd = std::make_shared<SetupShadowDrawCommand>(_shadow_drawer);
    _app->execute(*cmd);

    setup_terrain();

    setup_shadows();
}

void MainWindow::updateSceneByLightSources()
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<UpdateFragmentShadersLightMapSourcesCommand>();
    _app->execute(*cmd);
    
    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::update_main_scene()
{
    ClipSpaceType type;

    /* Switch problem */
    if (ui->orthoRB->isChecked())
        type = ClipSpaceType::ORTHO;
    else if (ui->perspectiveRB->isChecked())
        type = ClipSpaceType::PERSPECTIVE;
    else
        type = ClipSpaceType::PERSPECTIVE;

    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<MainDrawCommand>(_main_drawer, type);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::update_heightmap_scene()
{
    HeightmapDrawCommand draw_command(_heightmap_drawer);
    _app->execute(draw_command);
}

void MainWindow::update_lightmap_scene()
{
    LightmapDrawCommand draw_command(_lightmap_drawer);
    _app->execute(draw_command);
}

void MainWindow::setup_terrain()
{
    std::shared_ptr<BaseCommand> cmd;
    cmd = std::make_shared<SetWaterStateCommand>(ui->addLandscapeWater->isChecked());
    _app->execute(*cmd);
}

void MainWindow::setup_shadows()
{
    std::shared_ptr<BaseCommand> cmd;
    cmd = std::make_shared<SetShadowmapUsingCommand>(ui->shadowEnableCB->isChecked());
    _app->execute(*cmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_genLandscapeBtn_clicked()
{
    std::size_t height, width;
    height = width = ui->mapSizeSB->value();

    LandscapeGeneratorType type = getLandscapeType();

    /* Потом лучше сделать поиск по словарю вместо switch; Сделать shared_ptr */
    std::shared_ptr<FormLandscapeCommand> cmd;
    /* Подумать над тем, где задавать delta параметр для diamond-square и midpoint displacement */
    const float delta = 1.f;

    switch (type)
    {
    case LandscapeGeneratorType::DSGenerator:
        cmd = std::shared_ptr<FormLandscapeCommand>(
            new FormDSLandscapeCommand(height, width, getRoughness(), delta, getSurfaceType(), getCornerHeights()));
        break;
    case LandscapeGeneratorType::MDSGenerator:
        cmd = std::shared_ptr<FormLandscapeCommand>(
            new FormMDSLandscapeCommand(height, width, getRoughness(), delta, getCornerHeights()));
        break;
    case LandscapeGeneratorType::PNGenerator:
        cmd = std::shared_ptr<FormLandscapeCommand>(new FormPNLandscapeCommand(height, width, getOctavesCnt()));
        break;
    default:
        break;
    }

    try
    {
        cmd->execute();
    }
    catch(BaseException &ex)
    {
        std::shared_ptr<QMessageBox> msg = produceWarningMessage(ex.what());
        msg->exec();
        return ;
    }

    update_heightmap_scene();
}

void MainWindow::on_closeVPBtn_clicked()
{
    CloseViewportCommand cmd(_main_drawer);
    _app->execute(cmd);
}

void MainWindow::on_launch_btn_clicked()
{
    update_main_scene();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    std::shared_ptr<BaseCommand> cmd = nullptr;


    if (event->key() == Qt::Key_W)
        cmd = std::shared_ptr<BaseCommand>(new MoveCameraCommand(CameraMovement::FORWARD));
    if (event->key() == Qt::Key_S)
        cmd = std::shared_ptr<BaseCommand>(new MoveCameraCommand(CameraMovement::BACKWARD));
    if (event->key() == Qt::Key_A)
        cmd = std::shared_ptr<BaseCommand>(new MoveCameraCommand(CameraMovement::LEFT));
    if (event->key() == Qt::Key_D)
        cmd = std::shared_ptr<BaseCommand>(new MoveCameraCommand(CameraMovement::RIGHT));
    if (event->key() == Qt::Key_Z)
        cmd = std::shared_ptr<BaseCommand>(new MoveCameraCommand(CameraMovement::DOWN));
    if (event->key() == Qt::Key_X)
        cmd = std::shared_ptr<BaseCommand>(new MoveCameraCommand(CameraMovement::UP));

    if (event->key() == Qt::Key_R)
        cmd = std::shared_ptr<BaseCommand>(new RotateCameraCommand(CameraRotation::UP));
    if (event->key() == Qt::Key_F)
        cmd = std::shared_ptr<BaseCommand>(new RotateCameraCommand(CameraRotation::DOWN));
    if (event->key() == Qt::Key_Q)
        cmd = std::shared_ptr<BaseCommand>(new RotateCameraCommand(CameraRotation::LEFT));
    if (event->key() == Qt::Key_E)
        cmd = std::shared_ptr<BaseCommand>(new RotateCameraCommand(CameraRotation::RIGHT));

    if (event->key() == Qt::Key_T)
        cmd = std::shared_ptr<BaseCommand>(new ZoomCameraCommand(CameraZooming::FURTHER));
    if (event->key() == Qt::Key_G)
        cmd = std::shared_ptr<BaseCommand>(new ZoomCameraCommand(CameraZooming::CLOSER));

    if (event->key() == Qt::Key_C)
        cmd = std::shared_ptr<BaseCommand>(new RespawnCameraCommand(getClipSpaceType(), _main_drawer));

    if (cmd != nullptr)
    {
        try
        {
            cmd->execute();
        }
        catch (NoSceneCameraException &ex)
        {
            return ;
        }

        UpdateScreenCommand ucmd(_main_drawer);
        ucmd.execute();
    }
}

void MainWindow::on_loadBtn_clicked()
{
    LoadLandscapeFromFile cmd(getLoadPath());

    try
    {
        _app->execute(cmd);
    }
    catch(BaseException &ex)
    {
        std::shared_ptr<QMessageBox> msg = produceWarningMessage(ex.what());
        msg->exec();
        return;
    }

    update_heightmap_scene();
}

void MainWindow::on_saveBtn_clicked()
{
    SaveLandscapeToFile cmd(getSavePath(), EImageFileExtension::PNG);

    try
    {
        _app->execute(cmd);
    }
    catch(BaseException &ex)
    {
        std::shared_ptr<QMessageBox> msg = produceWarningMessage(ex.what());
        msg->exec();
        return;
    }
}

void MainWindow::on_deformBtn_clicked()
{
    const float dflDeformStrange = 1.0;
    std::shared_ptr<BaseCommand> cmd;

    try
    {
        cmd = std::make_shared<DeformLandscapeCommand>(dflDeformStrange);
        _app->execute(*cmd);

        cmd = std::make_shared<UpdateTerrainObjectsCommand>();
        _app->execute(*cmd);

        cmd = std::make_shared<UpdateShadowmapPoolCommand>();
        _app->execute(*cmd);

        cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
        _app->execute(*cmd);
    }
    catch (BaseException &ex)
    {
        std::shared_ptr<QMessageBox> msg = produceWarningMessage(ex.what());
        msg->exec();
        return ;
    }
}

void MainWindow::on_orthoRB_toggled(bool checked)
{   
    if (checked)
    {
        SetProjectionCommand cmd(ClipSpaceType::ORTHO, _main_drawer);
        cmd.execute();

        UpdateScreenCommand ucmd(_main_drawer);
        ucmd.execute();
    }
}

void MainWindow::on_perspectiveRB_toggled(bool checked)
{
    if (checked)
    {
        SetProjectionCommand cmd(ClipSpaceType::PERSPECTIVE, _main_drawer);
        cmd.execute();

        UpdateScreenCommand ucmd(_main_drawer);
        ucmd.execute();
    }
}

LandscapeGeneratorType MainWindow::getLandscapeType()
{
    /* Потом лучше сделать поиск по словарю вместо if else */

    LandscapeGeneratorType type;
    QString strType = ui->genTypeCB->itemText(ui->genTypeCB->currentIndex());
    if (strType == "Diamond-square")
        type = LandscapeGeneratorType::DSGenerator;
    else if (strType == "Метод смещения средней точки")
        type = LandscapeGeneratorType::MDSGenerator;
    else if (strType == "Шум Перлина")
        type = LandscapeGeneratorType::PNGenerator;
    else
        type = LandscapeGeneratorType::PNGenerator;

    return type;
}

float MainWindow::getRoughness()
{
    float roughtness = ui->roughtnessSB->value();
    return roughtness;
}

std::size_t MainWindow::getOctavesCnt()
{
    std::size_t octavesCnt = ui->octavesCntSB->value();
    return octavesCnt;
}

SurfaceType MainWindow::getSurfaceType()
{
    SurfaceType type;

    if (ui->landTypeAtolRB->isEnabled())
        type = SurfaceType::Atol;
    else if (ui->landTypeIslandRB->isEnabled())
        type = SurfaceType::Island;
    else if (ui->landTypeRandomRB->isEnabled())
        type = SurfaceType::Random;
    else
        type = SurfaceType::Random;

    return type;
}

CornerHeights MainWindow::getCornerHeights()
{
    CornerHeights output;

    output.leftUp = ui->leftUpSB->value();
    output.rightUp = ui->rightUpSB->value();
    output.rightDown = ui->rightDownSB->value();
    output.leftDown = ui->leftDownSB->value();

    return output;
}

std::string MainWindow::getSavePath()
{
    return ui->savePathLE->text().toStdString();
}

std::string MainWindow::getLoadPath()
{
    return ui->loadPathLE->text().toStdString();
}

ClipSpaceType MainWindow::getClipSpaceType()
{
    if (ui->orthoRB->isChecked())
        return ClipSpaceType::ORTHO;
    else
        return ClipSpaceType::PERSPECTIVE;
}

ShaderType MainWindow::getShaderType()
{
    if (ui->simpleShadingRB->isChecked())
        return ShaderType::FRAG_SIMPLE;
    else if (ui->gouraudShadingRB->isChecked())
        return ShaderType::FRAG_GOURAUD;
    else
        return ShaderType::FRAG_SIMPLE;
}

size_t MainWindow::getSettingsViwportHeight()
{
    return ui->viewportHeight->value();
}

size_t MainWindow::getSettingsViwportWidth()
{
    return ui->viewportWidth->value();
}

vec3<> MainWindow::QColor2vec3(QColor clr)
{
    return vec3<>(clr.redF(), clr.greenF(), clr.blueF()) * 255.f;
}

std::shared_ptr<QMessageBox> MainWindow::produceWarningMessage(const char *content, const char *title)
{
    std::shared_ptr<QMessageBox> msg = std::make_shared<QMessageBox>(this);
    msg->setText(content);
    msg->setWindowTitle(title);
    return msg;
}

void MainWindow::on_simpleShadingRB_toggled(bool checked)
{
    if (checked)
    {
        std::shared_ptr<BaseCommand> cmd(new ConvertSceneObjectsToPolygonCommand());
        try
        {
            cmd->execute();
        }
        catch (NoGridYetException &ex)
        {
            return ;
        }

        cmd = std::make_shared<SetFragmentShaderCommand>(_main_drawer, ShaderType::FRAG_SIMPLE);
        cmd->execute();

        cmd = std::make_shared<UpdateFragmentShadersLightMapSourcesCommand>();
        _app->execute(*cmd);

        cmd = std::shared_ptr<BaseCommand>(new UpdateScreenCommand(_main_drawer));
        cmd->execute();
    }
}

void MainWindow::on_gouraudShadingRB_toggled(bool checked)
{
    if (checked)
    {
        std::shared_ptr<BaseCommand> cmd(new ConvertSceneObjectsToPolygonCommand());
        try
        {
            _app->execute(*cmd);
        }
        catch (NoGridYetException &ex)
        {
            return ;
        }

        cmd = std::make_shared<SetFragmentShaderCommand>(_main_drawer, ShaderType::FRAG_GOURAUD);
        _app->execute(*cmd);

        cmd = std::make_shared<UpdateFragmentShadersLightMapSourcesCommand>();
        _app->execute(*cmd);

        cmd = std::shared_ptr<BaseCommand>(new UpdateScreenCommand(_main_drawer));
        _app->execute(*cmd);
    }
}

void MainWindow::on_frameModelRB_toggled(bool checked)
{
    if (checked)
    {
        std::shared_ptr<BaseCommand> cmd(new ConvertSceneObjectsToFrameCommand());
        try
        {
            cmd->execute();
        }
        catch (NoGridYetException &ex)
        {
            return ;
        }

        cmd = std::shared_ptr<BaseCommand>(new UpdateScreenCommand(_main_drawer));
        cmd->execute();
    }
}

void MainWindow::on_addLandscapeWater_toggled(bool checked)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetWaterRenderCommand>(checked);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateTerrainObjectsCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_maxHeightSB_valueChanged(double value)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetMaxLandscapeHeightCommand>((float) value);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateTerrainObjectsCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_waterLevelSB_valueChanged(double value)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetLandscapeWaterLevelCommand>((float) value);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateTerrainObjectsCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_updateSceneBtn_clicked()
{
    /*TODO Swich problem */
    std::shared_ptr<BaseCommand> cmd;

    if (ui->frameModelRB->isChecked())
        cmd = std::shared_ptr<UpdadeLandscapeCommand>(new AddFrameLandscapeCommand);
    else
        cmd = std::shared_ptr<UpdadeLandscapeCommand>(new AddPolygonLandscapeCommand);  

    try
    {
        _app->execute(*cmd);
    }
    catch (NoGridYetException &ex)
    {
        std::shared_ptr<QMessageBox> msg = produceWarningMessage(ex.what());
        msg->exec();
        return ;
    }

    cmd = std::make_shared<SetFragmentShaderCommand>(_main_drawer, getShaderType());
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateFragmentShadersLightMapSourcesCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    UpdateScreenCommand ucmd(_main_drawer);
    _app->execute(ucmd);
}

void MainWindow::on_genLightmapsBtn_clicked()
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<GenerateLightmapsCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<LightmapDrawCommand>(_lightmap_drawer);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_removeLSBtn_clicked()
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<RemoveTerrainLightmapCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<RemoveTerrainCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_nextLightmapBtn_clicked()
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<NextLightMapCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<LightmapDrawCommand>(_lightmap_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_useLightmapCB_toggled(bool checked)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetupLightmapUsingCommand>(checked);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_shadowEnableCB_toggled(bool checked)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetShadowmapUsingCommand>(checked);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_landTypeIslandRB_toggled(bool checked)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetHillLandscapeMaskCommand>();
    _app->execute(*cmd);
}

void MainWindow::on_landTypeAtolRB_toggled(bool checked)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetTorusLandscapeMaskCommand>();
    _app->execute(*cmd);
}

void MainWindow::on_landTypeRandomRB_toggled(bool checked)
{
    std::shared_ptr<BaseCommand> cmd;

    cmd = std::make_shared<SetRandomLandscapeMaskCommand>();
    _app->execute(*cmd);
}

void MainWindow::on_saveSettingsBtn_clicked()
{
    std::shared_ptr<BaseCommand> cmd;

    size_t newWidth = getSettingsViwportWidth();
    size_t newHeight = getSettingsViwportHeight();
    cmd = std::make_shared<ResizeDrawerCommand>(_main_drawer, newWidth, newHeight);
    _app->execute(*cmd);

    cmd = std::make_shared<ResizeDrawerCommand>(_shadow_drawer, newWidth, newHeight);
    _app->execute(*cmd);

    cmd = std::make_shared<SetBackgroundColorCommand>(_main_drawer, QColor2vec3(ui->verticalWidget_5->getColor()));
    _app->execute(*cmd);

    cmd = std::make_shared<SetDefaultLinesColorCommand>(_main_drawer, QColor2vec3(ui->verticalWidget_4->getColor()));
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateShadowmapPoolCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}

void MainWindow::on_takeScreenshotBtn_clicked()
{
    
}

void MainWindow::updateLandscapePaint()
{
    std::shared_ptr<BaseCommand> cmd;

    std::shared_ptr<Gradient> gradient = ui->verticalWidget_3->getAsGradient();
    cmd = std::make_shared<SetupLandscapeGradientCommand>(gradient);
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateTerrainObjectsCommand>();
    _app->execute(*cmd);

    cmd = std::make_shared<UpdateScreenCommand>(_main_drawer);
    _app->execute(*cmd);
}
