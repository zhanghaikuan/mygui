#include "widget.h"
#include "ui_widget.h"
#include"QDebug"
#include <QtGui/QStandardItemModel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    /////////////
 //   this->setMouseTracking(true);

 //      QImage *img=new QImage; //新建一个image对象

 //      img->load("1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
 //      ui->label->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

    QImage Image;
    Image.load("1.png");
    QPixmap pixmap = QPixmap::fromImage(Image);
    int with = ui->labPic->width();
    int height = ui->labPic->height();
   // QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    ui->labPic->setPixmap(fitpixmap);


    QPalette label_palette;
    //label_palette.setColor(QPalette::Background, QColor(0, 0, 0));
    //label_palette.setColor(QPalette::Background,Qt::black);
    label_palette.setColor(QPalette::Background, QColor("blue"));
    ui->labPic->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->labPic->setPalette(label_palette);
    standItemModel = new QStandardItemModel();
        //添加表头
        standItemModel->setColumnCount(6);
        standItemModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("NO"));
        standItemModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("XAxis"));   //设置表头内容
        standItemModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("ZAxis"));
        standItemModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("Radius"));
        standItemModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("Angle"));
        standItemModel->setHeaderData(5, Qt::Horizontal, QStringLiteral("Parameter3"));
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
        ui->_knivesNumberListCtrl->setModel(standItemModel);
        set_dlg=new function_setting_dlg();
       set_dlg->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    connect(set_dlg,SIGNAL(datachange(QString )),this,SLOT(seting_data_change(QString)));
     c_dlg = new calibration_dlg( );
     c_dlg->hide();
    connect(c_dlg,SIGNAL(calibration_change(QString )),this,SLOT(calibration_change(QString)));


}

Widget::~Widget()
{
    delete set_dlg;
    delete ui;
}
void Widget::seting_metric_change(QString str){}
void Widget::seting_dianeter_change(QString str){}
void Widget::calibration_change(QString str)
{
    qDebug()<< "calibration_change ";
}
void Widget::seting_data_change(QString str)
{
    qDebug()<< str;
}
void Widget::on_centerPresetButton_clicked()
{

}

void Widget::on_definitionAdjustButton_clicked()
{

}

void Widget::on_calibrationButton_clicked()
{

 c_dlg->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
 c_dlg->show();
}

void Widget::on_functionSetButton_clicked()
{

  set_dlg->show();
}

void Widget::on_saveCurDataToListButton_clicked()
{

}

void Widget::on_lablePrintButton_clicked()
{

}

void Widget::on_openFileButton_clicked()
{

}

void Widget::on_saveListButton_clicked()
{

}

void Widget::on_printButton_clicked()
{

}

void Widget::on_clearButton_clicked()
{

}

void Widget::on_kinfeStickSelection_currentIndexChanged(int index)
{

}

void Widget::on_kinfeSelection_currentIndexChanged(int index)
{

}

//void Widget::on_tableView_clicked(const QModelIndex &index)
//{
//    qDebug()<< index;
//}

void Widget::on_measureButton_clicked()
{

}
