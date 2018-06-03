/**
 * @file /include/mygui/main_window.hpp
 *
 * @brief Qt based gui for mygui.
 *
 * @date November 2010
 **/
#ifndef mygui_MAIN_WINDOW_H
#define mygui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace mygui {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();
Q_SIGNALS:
    void setMode();
    void getMode();
    void GetAllMap();
    void GetCurrentMap();
     void ChangeMap(std::string);
public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);

    /******************************************
    ** Manual connections
    *******************************************/
    void updateLoggingView(); // no idea why this can't connect automatically

private Q_SLOTS:
    void on_Button_SetMode_clicked();

    void on_Buttom_Getmode_clicked();

    void on_Button_GetAllMap_clicked();

    void on_Button_CurrentMap_clicked();

    void on_Button_changeMap_clicked();

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace mygui

#endif // mygui_MAIN_WINDOW_H
