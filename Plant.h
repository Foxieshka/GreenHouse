#ifndef PLANT_H
#define PLANT_H

#include <QObject>
#include <QString>
#include <QDate>

// Перечисление для освещения
enum class LightRequirement{
    Low, // Тень
    Medium, // Полутень
    High, // Яркий свет
    Direct // Прямые солнечные лучи
};

// Перечисление для полива
enum class WateringFrequency {
    Rare,       // Редкий (кактусы)
    Moderate,   // Умеренный
    Frequent,   // Частый
    Constant    // Постоянно влажная почва
};

class Plant : QObject{
    Q_OBJECT // Макрос, который активирует метасистему (сигналы/слоты)
public:
    // Геттеры
    QString species(){ return m_species; }
    LightRequirement light(){return m_light; }
    WateringFrequency watering() const { return m_watering; }
    QDate lastWateredDate() const { return m_lastWateredDate; }
    int wateringIntervalDays() const { return m_wateringIntervalDays; }
    // Сеттеры
private:
    int id; // Идентификатор
    QString m_species; // Вид растения
    LightRequirement m_light; // Освещение
    WateringFrequency m_watering; // Полив
    QDate m_lastWateredDate; // Для напоминаний
    int m_wateringIntervalDays; // Интервал полива
};

#endif // PLANT_H
