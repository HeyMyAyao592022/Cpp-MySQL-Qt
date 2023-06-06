#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->iniSys();
    this->setMinimumWidth(1080);
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
    using student_array = std::vector<Student>;
    using students_ptr = QSharedPointer<student_array>;

    auto watcher = QSharedPointer<QFutureWatcher<students_ptr>>(new QFutureWatcher<students_ptr>(), &QObject::deleteLater);
    connect(watcher.get(), &QFutureWatcher<students_ptr>::finished, this, [=]()
            {
        auto students = (watcher->future()).result();
        auto model = new QStandardItemModel(this);
        int size = students->size();
        for (int i = 0; i < size; i++)
        {
            const auto &s = (*students)[i];
            model->setItem(i, 0, new QStandardItem(QString::number(s.no)));
            model->setItem(i, 1, new QStandardItem(s.name.c_str()));
            model->setItem(i, 2, new QStandardItem(s.sex.c_str()));
            model->setItem(i, 3, new QStandardItem(QString::number(s.age)));
            model->setItem(i, 4, new QStandardItem(s.dept.c_str()));
        }
        ui->query_result_table->setModel(model); });

    auto future = QtConcurrent::run([=]() -> students_ptr
                                    { 
                        auto students = QSharedPointer<student_array>(new student_array());
                        if(!dao.loadStudents(*students))
                            printf("load failed\n");
                        else
                            printf("load succeed\n");
                        return students; });
    watcher->setFuture(future);
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
}
