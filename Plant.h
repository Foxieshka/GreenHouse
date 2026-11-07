#ifndef PLANT_H
#define PLANT_H

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

class Plant{
public:
    // Конструктор
    Plant() = default;

    Plant(int id, const QString& species, LightRequirement light,
        WateringFrequency water, const QString& imagePath) : m_id(id), m_species(species),
        m_light(light), m_watering(water), m_imagePath(imagePath) {}

    // Геттеры
    int id() const { return m_id; }
    QString species() const { return m_species; }
    LightRequirement light() const {return m_light; }
    WateringFrequency watering() const { return m_watering; }
    QDate lastWateredDate() const { return m_lastWateredDate; }
    QString imagePath() const {return m_imagePath; }
    int wateringIntervalDays() const { return m_wateringIntervalDays; }
    
    // Сеттеры
    void setId(int id) {m_id = id; }
    void setSpecies(const QString& species) { m_species = species; }
    void setLight(LightRequirement light) { m_light = light; }
    void setWatering(WateringFrequency water) { m_watering = water; }
    void setLastWateredDate(const QDate& date) { m_lastWateredDate = date; }
    void setWateringIntervalDays(int days) { m_wateringIntervalDays = days; }
    void setImagePath(const QString& imagePath){ m_imagePath = imagePath; }

private:
    int m_id = -1; // Идентификатор, -1 значит, что растение еще не сохранено в базе
    QString m_species; // Вид растения
    LightRequirement m_light = LightRequirement::Medium; // Освещение
    WateringFrequency m_watering = WateringFrequency::Moderate; // Полив
    QDate m_lastWateredDate; // Для напоминаний
    QString m_imagePath; // Путь к изображению
    int m_wateringIntervalDays = 7; // Интервал полива, по умолчанию раз в неделю
};

#endif // PLANT_H
