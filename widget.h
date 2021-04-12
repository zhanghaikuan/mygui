#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>

#include <QtGui/QStandardItemModel>
#include <QtCore/QTextCodec>
#include "calibration_dlg.h"
#include "function_setting_dlg.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_centerPresetButton_clicked();

    void on_definitionAdjustButton_clicked();

    void on_calibrationButton_clicked();

    void on_functionSetButton_clicked();

    void on_saveCurDataToListButton_clicked();

    void on_lablePrintButton_clicked();

    void on_openFileButton_clicked();

    void on_saveListButton_clicked();

    void on_printButton_clicked();

    void on_clearButton_clicked();
    void on_measureButton_clicked();


    void on_kinfeStickSelection_currentIndexChanged(int index);

    void on_kinfeSelection_currentIndexChanged(int index);

private slots:
       void seting_metric_change(QString str);
        void seting_dianeter_change(QString str);
        void seting_data_change(QString str);
        void calibration_change(QString set);


private:
    Ui::Widget *ui;
    QStandardItemModel *standItemModel;
    function_setting_dlg *set_dlg;
     calibration_dlg* c_dlg;
};
#endif // WIDGET_H
