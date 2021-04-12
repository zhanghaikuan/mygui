#ifndef FUNCTION_SETTING_DLG_H
#define FUNCTION_SETTING_DLG_H

#include <QWidget>
#include <QtGui/QStandardItemModel>
namespace Ui {
class function_setting_dlg;
}

class function_setting_dlg : public QWidget
{
    Q_OBJECT

public:
    explicit function_setting_dlg(QWidget *parent = nullptr);
    ~function_setting_dlg();
 public slots:
   void setLineValue(int value) ;
   void setContrastValue(int value);
   void setExposureValue(int value);

   void setRedValue(int value);
   void setGreenValue(int value);
   void setBlueValue(int value);

private slots:
   void on_CircleDiameterBtn_clicked();

   void on_MetricSystem_Btn_clicked();

   void on_LinearCompensation_CHECK_clicked();

   void on_cancle_button_clicked();
signals:
   void  datachange(QString string);
   void signalFunctionSetting_Dianeter(QString str);
   void signalFunctionSetting_Metric(QString str);


private:
    Ui::function_setting_dlg *ui;
     QStandardItemModel *standItemModel;
};

#endif // FUNCTION_SETTING_DLG_H
