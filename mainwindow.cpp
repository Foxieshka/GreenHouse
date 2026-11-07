#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QMessageBox>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dockEditor->hide(); // Прячем панель
    setWindowTitle("Каталог растений");
    setWindowIcon(QIcon(":/images/images/logo.svg"));    
    setupCentralWidget(); // Настройка центрального виджета
    setupToolBar(); // Настраиваем меню
    setupComboBox(); // Настраиваем ComboBox-ы
    this->seedData(); // Загружаем тестовые данные
    updateTable(); // Обновляем таблицу
    // Подключаем кнопку сохранения
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
}

void MainWindow::setupComboBox(){
    // Настройка ComboBox для Света
    ui->lightCombo->clear(); // На всякий случай очищаем
    ui->lightCombo->addItem("Тень", static_cast<int>(LightRequirement::Low));
    ui->lightCombo->addItem("Полутень", static_cast<int>(LightRequirement::Medium));
    ui->lightCombo->addItem("Яркий свет", static_cast<int>(LightRequirement::High));
    ui->lightCombo->addItem("Прямые лучи", static_cast<int>(LightRequirement::Direct));
    // Настройка ComboBox для Полива
    ui->waterCombo->clear();
    ui->waterCombo->addItem("Редкий", static_cast<int>(WateringFrequency::Rare));
    ui->waterCombo->addItem("Умеренный", static_cast<int>(WateringFrequency::Moderate));
    ui->waterCombo->addItem("Частый", static_cast<int>(WateringFrequency::Frequent));
    ui->waterCombo->addItem("Постоянный", static_cast<int>(WateringFrequency::Constant));
}

void MainWindow::setupToolBar(){
    QToolBar *toolBar = ui->toolBar;
    // Создаем кнопки toolBar
    QPushButton* editButton = new QPushButton(this);
    editButton->setIcon(QIcon(":/images/images/edit_icon.svg"));
    editButton->setText("Редактировать");
    // Убираем рамку кнопки, чтобы она выглядела как элемент тулбара
    editButton->setFlat(true);

    QPushButton* deleteButton = new QPushButton(this);
    deleteButton->setIcon(QIcon(":/images/images/delete_icon.svg"));
    deleteButton->setText("Удалить");
    deleteButton->setFlat(true);

    QPushButton* createButton = new QPushButton(this);
    createButton->setIcon(QIcon(":/images/images/add_icon.svg"));
    createButton->setText("Добавить растение");
    createButton->setFlat(true);

    // Связываем с Action
    connect(editButton, &QPushButton::clicked, this, &MainWindow::onEditClicked);
    connect(createButton, &QPushButton::clicked, this, &MainWindow::onAddClicked    );
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);

    // Заполняем меню
    toolBar->addWidget(editButton);
    toolBar->addWidget(deleteButton);
    toolBar->addWidget(createButton);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupCentralWidget(){
    // Отключаем нумерацию строк
    ui->tableWidget->verticalHeader()->setVisible(false);
    // Выделять строку целиком при клике
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Разрешить выбирать только одну строку за раз
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Растягиваем только текстовые колонки, картинку оставляем фиксированной
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ID
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);            // Вид (растягиваем)
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Свет
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Полив
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);              // Картинка (фиксируем)
    ui->tableWidget->setColumnWidth(4, 120); // Ширина колонки с картинкой
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
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(lightToString(plant.light())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(wateringToString(plant.watering())));

        // Вставляем изображение
        QLabel *imageLabel = new QLabel();
        QPixmap pixmap(plant.imagePath());
        imageLabel->setPixmap(pixmap.scaled(120, 120,
                Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        // Выравниваем по центру
        imageLabel->setAlignment(Qt::AlignCenter);
        // Вставляем виджет в таблицу
        ui->tableWidget->setCellWidget(i, 4, imageLabel);
    }

}

// Тестовые данные
void MainWindow::seedData(){
    QString periwinkleImage = ":/images/images/periwinkle.jpg";
    QString oleanderImage = ":/images/images/oleander.jpg";
    QString kaktusImage = ":/images/images/kaktus.jpg";
    QString orangeImage = ":/images/images/orange.jpg";

    Plant periwinkle(m_plants.size() + 1, "Барвинок малый", LightRequirement::High, WateringFrequency::Moderate,
        periwinkleImage);
    m_plants.append(periwinkle);
    Plant oleander(m_plants.size() + 1, "Олеандр", LightRequirement::High, WateringFrequency::Moderate,
                     oleanderImage);
    m_plants.append(oleander);
    Plant kaktus(m_plants.size() + 1, "Кактус домашний", LightRequirement::High, WateringFrequency::Rare,
                   kaktusImage);
    m_plants.append(kaktus);
    Plant orange(m_plants.size() + 1, "Апельсин Корругато", LightRequirement::High, WateringFrequency::Frequent,
                 orangeImage);
    m_plants.append(orange);
}

// Добавить растение
void MainWindow::onAddClicked()
{
    m_editingRow = -1; // Сбрасываем режим редактирования
    ui->saveButton->setText("Сохранить");
    // Очищаем поля
    ui->editSpecies->clear();
    ui->lightCombo->setCurrentIndex(0);
    ui->waterCombo->setCurrentIndex(0);
    // Прячем поля картинки (если нужно) и показываем панель
    ui->dockEditor->show();
}

// Удалить растение
void MainWindow::onDeleteClicked()
{
    qDebug() << "Нажата кнопка Удалить";
    // Получаем индекс текущей выбранной строки
    int row = ui->tableWidget->currentRow();
    // Не выбрана ни одна строка
    if (row < 0 || row >= m_plants.size()){
        QMessageBox::warning(this, "Внимание",
            "Сначала выберите растение в таблице!");
        return;
    }
    // Берем имя растения
    QString plantName = m_plants[row].species();
    auto reply = QMessageBox::question(
        this, "Подтверждение",
        QString("Вы точно хотите удалить %1?").arg(plantName),
        QMessageBox::Yes | QMessageBox::No);

    // Если нажали "Да"
    if (reply == QMessageBox::Yes) {
        m_plants.removeAt(row); // Удаляем из списка
        updateTable();          // Обновляем таблицу
        //checkWateringReminders(); // Обновляем уведомления (вдруг удалили "просроченное")
    }
}

// Редактировать
void MainWindow::onEditClicked(){
    qDebug() << "Нажата кнопка Редактировать";
    // Получаем индекс текущей выбранной строки
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= m_plants.size()) {
        QMessageBox::warning(this, "Внимание", "Выберите растение для редактирования!");
        return;
    }
    // Запоминаем индекс редактируемой строки
    m_editingRow = row;
    Plant& plant = m_plants[row];

    // Заполняем Dock панель
    ui->editSpecies->setText(plant.species());

    // Выставляем нужный индекс в ComboBox
    int lightData = static_cast<int>(plant.light());
    ui->lightCombo->setCurrentIndex(ui->lightCombo->findData(lightData));

    int waterData = static_cast<int>(plant.watering());
    ui->waterCombo->setCurrentIndex(ui->waterCombo->findData(waterData));

    // Меняем текст кнопки
    ui->saveButton->setText("Обновить");

    // Показываем панель
    ui->dockEditor->show();
}

// Главный слот сохранения
void MainWindow::onSaveClicked(){
    QString species = ui->editSpecies->text().trimmed();
    // Проверка не пуст ли Вид растения
    if (species.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название растения!");
        return;
    }
    int lightData = ui->lightCombo->currentData().toInt();
    int waterData = ui->waterCombo->currentData().toInt();
    LightRequirement light = static_cast<LightRequirement>(lightData);
    WateringFrequency water = static_cast<WateringFrequency>(waterData);

    if(m_editingRow == -1){
        // Режим создания
        Plant p;
        p.setSpecies(species);
        p.setId(m_plants.size()+1);
        p.setLight(light);
        p.setWatering(water);
        // Устанавливаем изображение - заглушку
        QString emptyImage = ":/images/images/empty_image.svg";
        p.setImagePath(emptyImage);
        m_plants.append(p);
    }else{
        // Режим редактирования
        Plant& p = m_plants[m_editingRow];
        p.setSpecies(species);
        p.setLight(light);
        p.setWatering(water);
        m_editingRow = -1; // Сбрасываем флаг
    }
    updateTable(); // Обновляем таблицу
    // checkWateringReminders();
    ui->dockEditor->hide();
}

// Показать уведомления
void MainWindow::onShowReminders()
{
    qDebug() << "Нажата кнопка Напоминания";
    // Пока ничего не делаем
    updateTable(); // Обновляем таблицу
}

