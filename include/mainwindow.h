#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student_dao.h"
#include "student_entity.h"

#include <vector>

#include <QMainWindow>
#include <QtConcurrent>
#include <QFuture>
#include <QTableView>
#include <QStandardItemModel>
#include <QMutex>
#include <QWaitCondition>
#include <QString>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief crud
     *
     */
    void insertStudent();
    void deleteStudent();
    void updateStudent();
    void queryStudent();

    void iniSys();

private:
    Ui::MainWindow *ui;
    StudentDAO dao;
};

#endif // MAINWINDOW_H
