#ifndef COLOR_EDIT_RECORD_H
#define COLOR_EDIT_RECORD_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QColorDialog>
#include <QDebug>

#include <memory>

class ColorEditRecord : public QWidget
{
    Q_OBJECT
public:
    explicit ColorEditRecord(QWidget *parent = nullptr, quint64 id = 0, size_t indx = 0);
    ColorEditRecord(const ColorEditRecord &other);

    quint64 getId();

public slots:
    void removeSelf();
    void updateSelfIndex(size_t indx);

signals:
    void timeToRemoveSelf(quint64);
    void sendMeMyIndex(quint64);
    void updateSetuper(quint64);
    void colorChanged(quint64);
    void dataChanged(quint64);

private:
    void setPushButtonClr(QPushButton *btn);
    void createSettings();

private slots:
    void on_checkBox_toggled(bool);

private:
    std::shared_ptr<QHBoxLayout> _layout;
    std::shared_ptr<QCheckBox> _checkBox;
    std::shared_ptr<QPushButton> _colorPushBtn;
    std::shared_ptr<QPushButton> _editLightBtn;
    quint64 _id;

    size_t _indx;
};

#endif