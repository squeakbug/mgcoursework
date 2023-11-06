#include "gui/light_manager_widget.h"
#include "gui/ui_light_manager_widget.h"

#include "commands/light_sources_commands.h"

LightManagerWidget::LightManagerWidget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LightManagerWidget)
{
    ui->setupUi(this);

    _records.reserve(defaultSourceCnt);

    for (size_t i = 0; i < defaultSourceCnt; ++i)
        _records.push_back(addNewEntry());
}

LightManagerWidget::~LightManagerWidget()
{
    delete ui;
}


void LightManagerWidget::removeById(quint64 id)
{
    auto it = _records.begin();
    for (auto &record : _records)
    {
        if (record->getId() == id)
        {
            delete record;
            _records.erase(it);
            emit recordsChanged();
            updateRecordsIndexes();
            return ;
        }
        it++;
    }
    /* throw exception */           // widget with same indx must be in list    // TODO
}

void LightManagerWidget::takeRecordChange(quint64 recordId)
{
    emit recordsChanged();
}


ColorEditRecord *LightManagerWidget::addNewEntry()
{
    ColorEditRecord *newRecord = new ColorEditRecord(this, findUniqueNumber(), _records.size());
    QObject::connect(newRecord, &ColorEditRecord::timeToRemoveSelf, this, &LightManagerWidget::removeById);
    QObject::connect(newRecord, &ColorEditRecord::dataChanged, this, &LightManagerWidget::takeRecordChange);
    ui->verticalLayout_2->addWidget(newRecord);
    return newRecord;
}

quint64 LightManagerWidget::findUniqueNumber() const
{
    for (size_t i = 0; i < _records.size(); i++)
    {
        bool isFinded = false;

        for (size_t j = 0; j < _records.size(); ++j)
        {
            if (_records[j]->getId() == i)
            {
                isFinded = true;
                break;
            }
        }

        if (!isFinded)
            return quint64(i);
    }

    return quint64(_records.size());
}

size_t LightManagerWidget::getEntryPositionById(quint64 id)
{
    size_t pos = 0;
    for (const auto &record : _records)
    {
        if (record->getId() == id)
            return pos;
        pos++;
    }

    /* Throw exception */           // widget with same indx must be in list    //TODO

    return 0;
}

void LightManagerWidget::updateRecordsIndexes()
{
    for (size_t i = 0; i < _records.size(); ++i)
        _records[i]->updateSelfIndex(i);
}


void LightManagerWidget::on_addBtn_clicked()
{
    _records.push_back(addNewEntry());
}

void LightManagerWidget::on_removeBtn_clicked()
{
    for (auto &record : _records)
    {
        // Удалить records.size() раз первый источник
        RemoveLightSourceCommand cmd(0);
        cmd.execute();
        delete record;
    }

    _records.clear();
    emit recordsChanged();
}
