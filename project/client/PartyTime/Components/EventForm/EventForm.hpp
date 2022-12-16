#pragma once // pragma once

#include "Button.hpp"
#include "Input.hpp"

class EventForm : public painter {
    Q_OBJECT
public:
    explicit EventForm(QWidget* parent = nullptr);
    EventForm(const QString& inputType, int inputSize, const QString& buttonType, const int buttonsSize = 0);
    EventForm(const EventForm& other);
    EventForm& operator=(const EventForm& other);
   ~EventForm();
    EventForm* create(const QString& objType);

    void updateState(){}; // const std::initializer_list<QString>&
private:
    QVBoxLayout* mainLayout;
    QGridLayout* inputLayout;
    QGridLayout* buttonsLayout;
    std::vector<UiButton*> formButtons;
    std::vector<UiInput*> inputList;
};
