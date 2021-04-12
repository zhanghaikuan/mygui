#include "function_setting_dlg.h"
#include "ui_function_setting_dlg.h"
#include <QDebug>
#include<string>
function_setting_dlg::function_setting_dlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::function_setting_dlg)
{
    ui->setupUi(this);
    ui->Brightness_SLIDER->setMinimum(0);
      //设置滑动条控件的最大值
    ui->Brightness_SLIDER->setMaximum(100);
      //设置滑动条控件的值
    // ui->Brightness_SLIDER->setValue(50);
     ui->Contrast_SLIDER->setMinimum(0);
     ui->Contrast_SLIDER->setMaximum(100);
     ui->ExposureTime_SLIDER->setMinimum(0);
     ui->ExposureTime_SLIDER->setMaximum(100);
     ui->Red_SLIDER->setMinimum(0);
     ui->Red_SLIDER->setMaximum(100);
     ui->Green_SLIDER->setMinimum(0);
     ui->Green_SLIDER->setMaximum(100);
     ui->Blue_SLIDER->setMinimum(0);
     ui->Blue_SLIDER->setMaximum(100);
     ui->LinearCompensation_CHECK->setChecked(true);
    connect(ui->Brightness_SLIDER, SIGNAL(valueChanged(int)), this, SLOT(setLineValue(int)));
    connect(ui->Contrast_SLIDER, SIGNAL(valueChanged(int)), this, SLOT(setContrastValue(int)));
    connect(ui->ExposureTime_SLIDER, SIGNAL(valueChanged(int)), this, SLOT(setExposureValue(int)));

    connect(ui->Red_SLIDER, SIGNAL(valueChanged(int)), this, SLOT(setRedValue(int)));
    connect(ui->Green_SLIDER, SIGNAL(valueChanged(int)), this, SLOT(setGreenValue(int)));
    connect(ui->Blue_SLIDER, SIGNAL(valueChanged(int)), this, SLOT(setBlueValue(int)));
    standItemModel = new QStandardItemModel();
        //添加表头
        standItemModel->setColumnCount(3);
        standItemModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("XAxis"));   //设置表头内容
        standItemModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("ZAxis"));
        standItemModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("FAxis"));

    for (int i = 0; i < 5; i++)
        {

            QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(i + 1));
            QStandardItem *standItem2 = new QStandardItem(tr(" %1 ").arg(i + 1));
            standItemModel->setItem(i, 0, standItem1);                                //表格第i行，第0列添加一项内容
            standItemModel->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));      //设置字符颜色
            standItemModel->item(i, 0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
            standItemModel->setItem(i, 1, standItem2);
            //表格第i行，第1列添加一项内容
        }
        ui->Compensation_list->setModel(standItemModel);
}

function_setting_dlg::~function_setting_dlg()
{
    delete ui;
}
void function_setting_dlg::setLineValue(int value)
{
  int pos = ui->Brightness_SLIDER->value();
  QString str = QString("%1").arg(pos);
  ui->Brightness_show->setText(str);
  emit datachange("Brightness_SLIDER");
}
void function_setting_dlg::setContrastValue(int value)
{
    int pos= ui->Contrast_SLIDER->value();
 QString str = QString("%1").arg(pos);
 ui->Contrast_show->setText(str);
}
void function_setting_dlg::setExposureValue(int value)
{
  int pos = ui->ExposureTime_SLIDER->value();
  QString str = QString("%1").arg(pos);
  ui->ExposureTime_show->setText(str);
}


void function_setting_dlg::setRedValue(int value){
    int pos = ui->Red_SLIDER->value();
    QString str = QString("%1").arg(pos);
    ui->Red_show->setText(str);
}
void function_setting_dlg::setGreenValue(int value)
{
    int pos= ui->Green_SLIDER->value();
    QString str = QString("%1").arg(pos);
    ui->Green_show->setText(str);
}
void function_setting_dlg::setBlueValue(int value)
{
    int pos=ui->Blue_SLIDER->value();
    QString str = QString("%1").arg(pos);
    ui->Blue_show->setText(str);
}

void function_setting_dlg::on_CircleDiameterBtn_clicked()
{
    if (ui->CircleDiameterBtn->checkState())
       qDebug()<<"CircleDiameterBtn "<<1;
    else{
        qDebug()<<"CircleDiameterBtn "<<0;
    }
}

void function_setting_dlg::on_MetricSystem_Btn_clicked()
{
    if (ui->MetricSystem_Btn->checkState())
       qDebug()<<"MetricSystem_Btn "<<1;
    else{
        qDebug()<<"MetricSystem_Btn "<<0;
    }
}

void function_setting_dlg::on_LinearCompensation_CHECK_clicked()
{
    if (ui->LinearCompensation_CHECK->checkState())
       qDebug()<<"LinearCompensation "<<1;
    else{
        qDebug()<<"LinearCompensation "<<0;
    }
}

void function_setting_dlg::on_cancle_button_clicked()
{
      standItemModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("ZAxis/2"));
      auto item = standItemModel->item(1,1);
      auto data= item->data(0).toString();
     std::string str=  data.toStdString();
//      item->setData(QVariant(data/2.0),0);
//      standItemModel->setItem(1, 1, item);
}
