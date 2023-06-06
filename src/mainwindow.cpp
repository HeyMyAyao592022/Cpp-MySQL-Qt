#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->iniSys();

    this->setMinimumWidth(1550);
    this->setMinimumHeight(800);
    this->ui->edit_table->setFixedHeight(120);
}

MainWindow::~MainWindow()
{
    StudentDAO::getInstance()->disConnect();
    delete ui;
}

void MainWindow::insertStudent()
{
    auto name = editModel.item(0, 1)->text().toStdString();
    auto sex = editModel.item(0, 2)->text().toStdString();
    auto age = editModel.item(0, 1)->text().toUInt();
    auto dept = editModel.item(0, 4)->text().toStdString();

    Student student;
    student.name = name;
    student.sex = sex;
    student.age = age;
    student.dept = dept;

    QtConcurrent::run([=]()
                      { 
                      if(!dao.insertStudent(student)){
                        printf("insert failed\n");
                        return;
                      }
                      printf("insert succeed, reloading...\n");
                      this->queryResult.clear();
                      if(!dao.loadStudents(this->queryResult)){
                        printf("reload failed\n");
                      }
                      emit querySignal();
                      printf("reloaded\n"); });
}

void MainWindow::deleteStudent(int row)
{
    QtConcurrent::run([=]
                      { 
                        if(!dao.deleteStudent((this->queryResult)[row])){
                            printf("delete failed\n");
                            return;
                        }
                        printf("delete succeed, reloading...\n");
                        this->queryResult.clear();
                        if(!dao.loadStudents(this->queryResult)){
                          printf("reload failed\n");
                        }
                        emit querySignal();
                        printf("reloaded\n"); });
}

void MainWindow::updateStudent(int row)
{
    auto name = queryModel.item(row, 1)->text().toStdString();
    auto sex = queryModel.item(row, 2)->text().toStdString();
    auto age = queryModel.item(row, 3)->text().toUInt();
    auto dept = queryModel.item(row, 4)->text().toStdString();

    Student student;
    student.name = name;
    student.sex = sex;
    student.age = age;
    student.dept = dept;
    student.no = queryResult[row].no;

    QtConcurrent::run([=]()
                      { if(!dao.updateStudent(student)){
                        printf("update failed\n");
                        return;
                       }
                        printf("update succeed\n"); });
}

void MainWindow::queryStudent()
{
    queryResult.clear();

    QtConcurrent::run([=]()
                      { 
                        if(!dao.loadStudents(queryResult))
                            printf("load failed\n");
                        else
                            printf("load succeed\n");
                        emit querySignal(); });
}

void MainWindow::iniSys()
{
    QStringList header;
    header << "no"
           << "name"
           << "sex"
           << "age"
           << "dept";
    // ini
    QtConcurrent::run([=]
                      { this->dao.iniDAO(); });
    // edit
    {
        ui->edit_table->verticalHeader()->setVisible(false);
        auto &model = this->editModel;
        ui->edit_table->setModel(&model);
        model.setHorizontalHeaderLabels(header);

        for (size_t i = 0; i < 5; i++)
        {
            model.setItem(0, i, new QStandardItem(""));
        }
    }
    // query
    {
        header << "action"
               << "action";

        auto &model = this->queryModel;
        ui->query_result_table->setModel(&model);
        model.setHorizontalHeaderLabels(header);
    }
    // connect
    connect(ui->query_btn, &QPushButton::clicked, this, &MainWindow::queryStudent);

    connect(this, &MainWindow::querySignal, this, [=]()
            {
        auto& students = this->queryResult;
        int size = students.size();
        auto& model = this->queryModel;

        queryModel.clear();
        QStringList header;
        header << "no"
           << "name"
           << "sex"
           << "age"
           << "dept"
           << " "
           << " ";
       queryModel.setHorizontalHeaderLabels(header);

        auto setItem = [&](QStandardItem* item,int row,int col){
            model.setItem(row,col,item);
            model.item(row,col)->setTextAlignment(Qt::AlignCenter);
        };

        for (int i = 0; i < size; i++)
        {
            const auto &s = (students)[i];
            setItem(new QStandardItem(QString::number(s.no)),i,0);
            setItem(new QStandardItem(s.name.c_str()),i,1);
            setItem(new QStandardItem(s.sex.c_str()),i,2);
            setItem(new QStandardItem(QString::number(s.age)),i,3);
            setItem(new QStandardItem(s.dept.c_str()),i,4);

            auto button1 = new QPushButton("update");
            auto button2 = new QPushButton("delete");

            connect(button1,&QPushButton::clicked,this,[=](){
                updateStudent(i);
            });
            connect(button2,&QPushButton::clicked,this,[=](){
                deleteStudent(i);
            });

            ui->query_result_table->setIndexWidget(model.index(i,5),button1);
            ui->query_result_table->setIndexWidget(model.index(i,6),button2);
        } });

    connect(ui->insert_btn, &QPushButton::clicked, this, &MainWindow::insertStudent);
}
