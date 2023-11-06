#ifndef DIRECT_LIGHT_SETUP_WIDGET_H
#define DIRECT_LIGHT_SETUP_WIDGET_H

#include <QDialog>

namespace Ui
{
    class DirectLightSetupWidget;
}

class DirectLightSetupWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DirectLightSetupWidget(size_t indx, QWidget *parent = 0);
    ~DirectLightSetupWidget();

public:
    double getAmbientCoeff() const;
    double getDiffuseCoeff() const;
    double getSpecularCoeff() const;

    double getXDirection() const;
    double getYDirection() const;
    double getZDirection() const;

public slots:
    void updateIndx(size_t indx);

private slots:
    void on_deleteBtn_clicked();

signals:
    void timeToRemoveSelf();

private:
    Ui::DirectLightSetupWidget *ui;
    size_t _indx;
};

#endif