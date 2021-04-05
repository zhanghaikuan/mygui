#ifndef CALIBRATION_DLG_H
#define CALIBRATION_DLG_H

#include <QWidget>

namespace Ui {
class calibration_dlg;
}

class calibration_dlg : public QWidget
{
    Q_OBJECT

public:
    explicit calibration_dlg(QWidget *parent = nullptr);
    ~calibration_dlg();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_resetButton_clicked();

    void on_doneButton_clicked();

private:
    Ui::calibration_dlg *ui;
};

#endif // CALIBRATION_DLG_H
