#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Plant.h"
#include <QList>
#include <QDockWidget>
#include <QToolBar>

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

private:
    // Настройка интерфейса (вызывается один раз в конструкторе)
    void setupCentralWidget(); // Настройка центрального виджета (таблицы)     
    void seedData(); // Генерируем тестовые данные
    void setupComboBox(); // Настройка ComboBox
    void setupToolBar(); // Настройка меню

    void updateTable(); // Обновление данных в таблице
    Ui::MainWindow *ui;
    QList<Plant> m_plants; // Cписок растений (пока In Memory)
    int m_editingRow = -1; // -1 = добавление, >=0 = редактирование

private slots:
    // CRUD операции
    void onAddClicked();      // Нажали "Добавить" (очищает панель и показывает)
    void onEditClicked();     // Нажали "Редактировать" (заполняет панель и показывает)
    void onDeleteClicked();   // Нажали "Удалить"
    void onSaveClicked();     // Нажали "Сохранить" в панели (Добавляет ИЛИ Обновляет)
    void onShowReminders();   // Нажали "Напоминания"
};
#endif // MAINWINDOW_H
