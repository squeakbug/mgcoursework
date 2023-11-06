#include "gui/direct_light_setup_widget.h"
#include "gui/ui_direct_light_setup_widget.h"

#include "commands/light_sources_commands.h"

DirectLightSetupWidget::DirectLightSetupWidget(size_t indx, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirectLightSetupWidget),
    _indx(indx)
{
    ui->setupUi(this);

    vec3<> color;
    float ambient;
    float diffuse;
    float specular;
    vec3<> direction;
    SelectDirectLightSourceDataCommand cmd(_indx, color, ambient, diffuse, specular, direction);
    cmd.execute(); //TODO Send comand through application

    ui->ambientSB->setValue(ambient);
    ui->diffuseSB->setValue(diffuse);
    ui->specularSB->setValue(specular);

    ui->xSB->setValue(direction.x);
    ui->ySB->setValue(direction.y);
    ui->zSB->setValue(direction.z);
}

DirectLightSetupWidget::~DirectLightSetupWidget()
{
    delete ui;
}

double DirectLightSetupWidget::getAmbientCoeff() const
{
    return ui->ambientSB->value();
}

double DirectLightSetupWidget::getDiffuseCoeff() const
{
    return ui->diffuseSB->value();
}

double DirectLightSetupWidget::getSpecularCoeff() const
{
    return ui->specularSB->value();
}

double DirectLightSetupWidget::getXDirection() const
{
    return ui->xSB->value();
}

double DirectLightSetupWidget::getYDirection() const
{
    return ui->ySB->value();
}

double DirectLightSetupWidget::getZDirection() const
{
    return ui->zSB->value();
}


void DirectLightSetupWidget::on_deleteBtn_clicked()
{
    RemoveLightSourceCommand cmd(_indx);
    cmd.execute();

    emit timeToRemoveSelf();
}

void DirectLightSetupWidget::updateIndx(size_t indx)
{
    _indx = indx;
}