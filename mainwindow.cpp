#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    balance         = 0.0;
    todayQuota      = 0.0;
    todayExpenses   = 0.0;
    nextPaymentDate = QDate::currentDate();
    int day         = nextPaymentDate.day();
    int month       = nextPaymentDate.month();
    int year        = nextPaymentDate.year();

    ui->line_OutNextPaymentDate->setText(QString::number(day) + "/" + QString::number(month) + "/" + QString::number(year));
    ui->line_InNextPaymentDate->setText("dd/mm/yyyy");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushIncomeAmount_clicked() {
    bool ok;
    double income = ui->line_incomeAmount->text().toDouble(&ok);
    if(ok == false) {
        qDebug() << "Por favor ingrese el monto en numeros";
        return;
    }

    balance += income;

    ui->line_balance->setText(QString::number(balance));
    updateQuota();
}

void MainWindow::updateQuota() {
    int n_days2nextPayment = int(nextPaymentDate.toJulianDay() - QDate::currentDate().toJulianDay());
    if(n_days2nextPayment <= 0) {
        todayQuota = 0.0;
        qDebug() << "No se ha ingresado el nextPaymentDate";
        return;
    }

    todayQuota    = balance/n_days2nextPayment;
    todayExpenses = 0.0;

    printQuota();

}

void MainWindow::printQuota() {
    ui->line_quota->setText(QString::number(todayQuota - todayExpenses) + "/" + QString::number(todayQuota));
}

void MainWindow::on_pushNextPaymentDate_clicked() {
    QStringList dayMonthYear = ui->line_InNextPaymentDate->text().split("/");

    if(dayMonthYear.size() != 3) {
        qDebug() << "se debe ingresar la fecha en el siguiente formato";
        qDebug() << "dd/mm/yyyy";
        return;
    }

    int day   = 0;
    int month = 0;
    int year  = 0;

    foreach(const QString text, dayMonthYear) {
        bool ok;
        double number = text.toDouble(&ok);
        if(ok == false) {
            qDebug() << "Por favor ingresar solo numeros y separadores tipo /";
            return;
        }
        if(day == 0)
            day = int(number);
        else if(month == 0)
            month = int(number);
        else if(year == 0)
            year = int(number);
    }

    if(!nextPaymentDate.setDate(year,month,day)) {
        qDebug() << "Por favor ingrese una fecha valida";
        return;
    } else {
        updateQuota();
    }
}

void MainWindow::on_pushExpenseAmount_clicked() {
    bool ok;
    double expense = ui->line_ExpenseAmount->text().toDouble(&ok);

    if(!ok) {
        qDebug() << "Por favor ingrese el monto en numeros";
        return;
    }

    todayExpenses += expense;

    printQuota();
}
