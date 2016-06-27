#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcolordialog.h"
#include "qinputdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionE_xit_triggered()
{
    qApp->exit();
}

void MainWindow::on_action_Toolbar_toggled(bool arg1)
{
    if(arg1) ui->mainToolBar->show();
    else ui->mainToolBar->hide();
}

void MainWindow::on_action_Color_triggered()
{
    QColorDialog dlg(ui->centralWidget->palette().color(QWidget::backgroundRole()));

    if(dlg.exec() == QDialog::Accepted){

        QPalette pal(palette());
        pal.setColor(QPalette::Background, dlg.selectedColor());
        ui->centralWidget->setPalette(pal);

    }
}

void MainWindow::on_actionStatus_triggered()
{
    QInputDialog dlg;
    dlg.setLabelText(tr("Status text"));

    if(dlg.exec() == QDialog::Accepted){
        statusBar()->showMessage(tr("User says: %1").arg(dlg.textValue()),5000);
    }

}
