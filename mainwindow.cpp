#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Каталог растений");

    // Связываем действия меню со слотами
    connect(ui->actionAdd, &QAction::triggered, this, &MainWindow::onActionAdd);
    connect(ui->actionShow, &QAction::triggered, this, &MainWindow::onActionShowReminders);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);

    setupCentralWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupCentralWidget(){
    // Настраиваем заголовки таблицы (если не сделали в дизайнере)
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Вид", "Свет", "Полив"});

    // Растягиваем колонки по ширине окна
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// Временная функция для обновления таблицы
void MainWindow::updateTable(){
    // Устанавливаем количество строк
    ui->tableWidget->setRowCount(m_plants.size());

    for(int i = 0; i < m_plants.size(); ++i){
        const Plant& plant = m_plants[i];
        // Заполняем ячейки
        ui->tableWidget->setItem(i, 0, new
            QTableWidgetItem(QString::number(plant.id())));
        ui->tableWidget->setItem(i, 1, new
            QTableWidgetItem(plant.species()));
        // Пока просто пишем "Свет" и "Полив", позже сделаем красивые строки
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem("Свет (enum)"));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem("Полив (enum)"));
    }

}

// Добавить растение
void MainWindow::onActionAdd()
{
    qDebug() << "Нажата кнопка Добавить";
    // Пока просто добавим тестовое растение
    Plant testPlant(m_plants.size() + 1, "Тестовый Барвинок малый", LightRequirement::High, WateringFrequency::Moderate);
    testPlant.setLastWateredDate(QDate::currentDate());
    m_plants.append(testPlant);

    updateTable(); // Обновляем таблицу
}

// Удалить растение
void MainWindow::onActionDelete()
{
    qDebug() << "Нажата кнопка Удалить";
    // Пока ничего не делаем
}

// Показать уведомления
void MainWindow::onActionShowReminders()
{
    qDebug() << "Нажата кнопка Напоминания";
    // Пока ничего не делаем
}

