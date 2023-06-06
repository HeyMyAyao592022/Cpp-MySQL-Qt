#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "student_dao.h"
#include "student_entity.h"

#include <vector>
#include <memory>

#include <QMainWindow>
#include <QtConcurrent>
#include <QFuture>
#include <QTableView>
#include <QStandardItemModel>
#include <QMutex>
#include <QWaitCondition>
#include <QString>
#include <QPushButton>
#include <QSharedPointer>
#include <QFutureWatcher>
#include <QStringList>

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
signals:
    void querySignal();
    void deleteSignal(int row);
    void updateSignal(int row);

private:
    /**
     * @brief crud
     *
     */
    void insertStudent();
    void deleteStudent(int row);
    void updateStudent(int row);
    void queryStudent();

    void iniSys();

private:
    Ui::MainWindow *ui;
    StudentDAO dao;

    std::vector<Student> queryResult;

    QStandardItemModel queryModel;
    QStandardItemModel editModel;
};

#endif // MAINWINDOW_H
