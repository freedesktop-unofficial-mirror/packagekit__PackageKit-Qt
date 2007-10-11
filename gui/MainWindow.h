#include <QtGui>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {

	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

};
