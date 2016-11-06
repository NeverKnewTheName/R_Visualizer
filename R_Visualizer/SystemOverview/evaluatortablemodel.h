#ifndef EVALUATORTABLEMODEL_H
#define EVALUATORTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

#include <../R_Visualizer_Utilities/templatevalueevaluator.h>

class EvaluatorTablemodel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit EvaluatorTablemodel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRow(TemplateValueEvaluator *EvaluatorToRemove);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

public slots:
    bool appendRow(TemplateValueEvaluator *EvaluatorToAdd);
    bool updateRow(TemplateValueEvaluator *EvaluatorToAdd);

private:
    QVector<TemplateValueEvaluator*> EvaluatorStore;
};

#endif // EVALUATORTABLEMODEL_H
