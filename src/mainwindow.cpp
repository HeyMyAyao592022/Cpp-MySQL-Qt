#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->iniSys();
}

MainWindow::~MainWindow()
{
    StudentDAO::getInstance()->disConnect();
    delete ui;
}

void MainWindow::insertStudent()
{
}

void MainWindow::deleteStudent()
{
}

void MainWindow::updateStudent()
{
}

void MainWindow::queryStudent()
{
    QtConcurrent::run([=]
                      { 
                        if(!dao.loadStudents(temp)){
                            printf("load failed\n");
                            return; 
                        }
                        printf("load succeed\n");
                        emit querySignal(); });
}

void MainWindow::iniSys()
{
    QtConcurrent::run([=]
                      { this->dao.iniDAO(); });
    {
        auto model = new QStandardItemModel(this);
        model->setHorizontalHeaderItem(0, new QStandardItem("no"));
        model->setHorizontalHeaderItem(1, new QStandardItem("name"));
        model->setHorizontalHeaderItem(2, new QStandardItem("sex"));
        model->setHorizontalHeaderItem(3, new QStandardItem("age"));
        model->setHorizontalHeaderItem(4, new QStandardItem("dept"));
        ui->query_result_table->setModel(model);
    }
    // connect
    connect(ui->query_btn, &QPushButton::clicked, this, &MainWindow::queryStudent);
    connect(this, &MainWindow::querySignal, this, [=]()
            {
            auto model = new QStandardItemModel(this);
            int size = this->temp.size();
            for (int i = 0; i < size; i++)
            {
                const auto &s = temp[i];
                model->setItem(i, 0, new QStandardItem(QString::number(s.no)));
                model->setItem(i, 1, new QStandardItem(s.name.c_str()));
                model->setItem(i, 2, new QStandardItem(s.sex.c_str()));
                model->setItem(i, 3, new QStandardItem(QString::number(s.age)));
                model->setItem(i, 4, new QStandardItem(s.dept.c_str()));
            }
            ui->query_result_table->setModel(model); });
}
