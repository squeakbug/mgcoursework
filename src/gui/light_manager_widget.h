#ifndef LIGHT_MANAGER_WIDGET_H
#define LIGHT_MANAGER_WIDGET_H

#include <QWidget>

#include <vector>
#include <memory>

#include "color_edit_record.h"

namespace Ui
{
    class LightManagerWidget;
}

class LightManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightManagerWidget(QWidget *parent = 0);
    ~LightManagerWidget();

public slots:
    void removeById(quint64 id);
    void takeRecordChange(quint64 recordId);

signals:
    void recordsChanged();

private:
    ColorEditRecord *addNewEntry();
    quint64 findUniqueNumber() const;
    size_t getEntryPositionById(quint64 id);
    void updateRecordsIndexes();

private slots:
    void on_addBtn_clicked();
    void on_removeBtn_clicked();

private:
    Ui:: LightManagerWidget *ui;
    std::vector<ColorEditRecord*> _records;
    static constexpr size_t defaultSourceCnt = 1;
};

#endif