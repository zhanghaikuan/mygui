#include "calibration_dlg.h"
#include "ui_calibration_dlg.h"

calibration_dlg::calibration_dlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calibration_dlg)
{
    ui->setupUi(this);
}

calibration_dlg::~calibration_dlg()
{
    delete ui;
}

void calibration_dlg::on_addButton_clicked()
{

}

void calibration_dlg::on_deleteButton_clicked()
{

}



void calibration_dlg::on_resetButton_clicked()
{

}

void calibration_dlg::on_doneButton_clicked()
{

}
