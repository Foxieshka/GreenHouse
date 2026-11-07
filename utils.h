#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include "Plant.h"

QString lightToString(LightRequirement light) {
    switch (light) {
    case LightRequirement::Low:    return "Тень";
    case LightRequirement::Medium: return "Полутень";
    case LightRequirement::High:   return "Яркий свет";
    case LightRequirement::Direct: return "Прямые лучи";
    }
    return "Неизвестно"; // На всякий случай
}

QString wateringToString(WateringFrequency water) {
    switch (water) {
    case WateringFrequency::Rare:     return "Редкий";
    case WateringFrequency::Moderate: return "Умеренный";
    case WateringFrequency::Frequent: return "Частый";
    case WateringFrequency::Constant: return "Постоянный";
    }
    return "Неизвестно";
}

#endif // UTILS_H
