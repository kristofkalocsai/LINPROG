#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionE_xit_triggered();

    void on_action_Toolbar_toggled(bool arg1);

    void on_action_Color_triggered();

    void on_actionStatus_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
