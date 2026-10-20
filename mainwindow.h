#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Plant.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Конструктор
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// protected:
//     void closeEvent(QCloseEvent* event);
//     // Переопределение для обработки закрытия окна

private:
    void setupMenu(); // Настройка меню
    void setupCentralWidget(); // Настройка центрального виджета (таблицы)
    void updateTable(); // Обновление данных в таблице

    Ui::MainWindow *ui;
    QList<Plant> m_plants; // Наш список растений (пока In Memory)

private slots:
    // Слоты для меню
    void onActionAdd();
    void onActionDelete();
    void onActionShowReminders();
};
#endif // MAINWINDOW_H
