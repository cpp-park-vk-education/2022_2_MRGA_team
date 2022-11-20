#pragma once // pragma once

#include "../painter.hpp"


class UiEdit : public painter {
    Q_OBJECT
public:
    explicit UiEdit(QWidget* parent = nullptr);
    UiEdit(const UiEdit& other);
    UiEdit& operator=(const UiEdit&);
    ~UiEdit();

    UiEdit(const QString& styleSheet, const QString& placeHolder = nullptr, const QFont& font = QFont()); // создание стилизованного input-a с placeholder-ом
    UiEdit(const QString& styleSheet, int width, int height, int coordX, int coordY); // создание стилизованного input-a с конкретным расположением в layout-e и заданными размерами

    UiEdit* create(const QString& objectType); // паттерн псевдофабрика
    void updateState(){}; // const std::initializer_list<QString>&
private:
    QLineEdit* value;
    QHBoxLayout* editLayout;
};
