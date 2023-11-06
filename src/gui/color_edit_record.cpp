#include "gui/color_edit_record.h"
#include "gui/direct_light_setup_widget.h"
#include "commands/application_commands.h"

const vec3<> defaultColor = { 1.f, 1.f, 1.f };
const float defaultAmbient = 0.2f;
const float defaultDiffuse = 1.f;
const float defaultSpecular = 0.f;
const vec3<> defaultDirection = {-1.f, -1.f, -1.f};
const bool defaultState = false;

ColorEditRecord::ColorEditRecord(QWidget *parent, quint64 id, size_t indx)
    : QWidget(parent),
      _id(id),
      _indx(indx)
{
    _layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(this));
    _layout->setSpacing(6);

    _checkBox = std::shared_ptr<QCheckBox>(new QCheckBox(this));
    _checkBox->resize(10, 10);
    _layout->addWidget(_checkBox.get());

    _colorPushBtn = std::shared_ptr<QPushButton>(new QPushButton(this));
    _layout->addWidget(_colorPushBtn.get());

    _editLightBtn = std::shared_ptr<QPushButton>(new QPushButton(this));
    _editLightBtn->setText("Редактировать");
    _editLightBtn->setFont(QFont("Times", 12));
    _layout->addWidget(_editLightBtn.get());

    //TODO make config with predefined default color
    _colorPushBtn->setStyleSheet(
        "QPushButton {"
        "background-color: white;"      // TODO bacground color должен зависеть от defaultColor
        "border-style: outset;"
        "border-width: 2px;"
        "border-radius: 10px;"
        "border-color: black;"
        "min-width: 10em;"
        "min-height: 24px; }"
    );

    // TODO in future it could be possible to select proper type of source according to certain pushbutton
    // TODO make cmd executing through application 
    AddNewDirectLightSourceCommand cmd(defaultColor, defaultAmbient, defaultDiffuse, defaultSpecular, defaultState, defaultDirection);
    cmd.execute();

    QObject::connect(_checkBox.get(), &QCheckBox::toggled, this, &ColorEditRecord::on_checkBox_toggled);

    QObject::connect(_colorPushBtn.get(), &QPushButton::clicked, this,
        [=](){ ColorEditRecord::setPushButtonClr(_colorPushBtn.get()); });

    QObject::connect(_editLightBtn.get(), &QPushButton::clicked, this,
        [=](){ ColorEditRecord::createSettings(); });

    /* Subscribe on toggle event */ //TODO
}

ColorEditRecord::ColorEditRecord(const ColorEditRecord &other)
{
    _checkBox = other._checkBox;
    _colorPushBtn = other._colorPushBtn;
    _editLightBtn = other._editLightBtn;
    _layout = other._layout;
    _id = other._id;
    _indx = other._indx;
}

quint64 ColorEditRecord::getId()
{
    return _id;
}

void ColorEditRecord::setPushButtonClr(QPushButton *btn)
{
    QColorDialog *dialog = new QColorDialog(this);
    QColor clr = dialog->getColor();

    btn->setStyleSheet(
        "QPushButton {"
        "background-color: " + clr.name() + ";"
        "border-style: outset;"
        "border-width: 2px;"
        "border-radius: 10px;"
        "border-color: black;"
        "min-height: 24px;"
        "min-width: 10em; }"
    );

    EditLightSourceColorCommand cmd({(float) clr.redF(), (float) clr.greenF(), (float) clr.blueF()}, _indx);
    cmd.execute();

    emit dataChanged(_id);
}

//TODO Подумать как проще всего потом добавить функционал добавления источников света другого типа
void ColorEditRecord::createSettings()
{
    DirectLightSetupWidget *dialog = new DirectLightSetupWidget(_indx, this);

    QObject::connect(dialog, &DirectLightSetupWidget::timeToRemoveSelf, this, &ColorEditRecord::removeSelf);
    QObject::connect(this, &ColorEditRecord::updateSetuper, dialog, &DirectLightSetupWidget::updateIndx);

    int result = dialog->exec();
    if (result == 1)
    {
        double ambient = dialog->getAmbientCoeff();
        double diffuse = dialog->getDiffuseCoeff();
        double specular = dialog->getSpecularCoeff();
        double xDir = dialog->getXDirection();
        double yDir = dialog->getYDirection();
        double zDir = dialog->getZDirection();

        EditDirectLightSourceCommand cmd((float) ambient, (float) diffuse, (float) specular, _indx,
            { (float) xDir, (float) yDir, (float) zDir });
        cmd.execute();
        
        /* edit data in view by id */       //TODO
        emit colorChanged(_id);
        emit dataChanged(_id);
    }
    else if (result == 0)
    {
        /* do nothing */
    }
}

void ColorEditRecord::removeSelf()
{
    emit timeToRemoveSelf(_id);
}

void ColorEditRecord::updateSelfIndex(size_t indx)
{
    _indx = indx;
    emit updateSetuper(_indx);
}

void ColorEditRecord::on_checkBox_toggled(bool checked)
{
    if (checked)
    {
        EnableLightSourceCommand cmd(_indx);
        cmd.execute();
    }
    else
    {
        DisableLightSourceCommand cmd(_indx);
        cmd.execute();
    }

    emit dataChanged(_id);
}
