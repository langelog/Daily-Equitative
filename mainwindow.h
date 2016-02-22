#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateQuota();

private slots:
    void on_pushIncomeAmount_clicked();

    void on_pushNextPaymentDate_clicked();

private:
    Ui::MainWindow *ui;

    double balance;
    double todayExpenses;
    double todayQuota;
    QDate  nextPaymentDate;

    void   printQuota();

};

#endif // MAINWINDOW_H
