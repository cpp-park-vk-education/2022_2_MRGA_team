#include "EventForm.hpp"


EventForm::EventForm(QWidget *parent) : painter(parent),
    mainLayout(new QVBoxLayout()), inputLayout(new QGridLayout), buttonsLayout(new QGridLayout)
{
    UiInput* inputFactory = new UiInput();
    UiButton* buttonFactory = new UiButton();
    inputList.push_back(inputFactory->create("defaultInput"));
    formButtons.push_back(buttonFactory->create("defaultButton"));

    delete inputFactory;
    delete buttonFactory;

    for (const auto& input: inputList) {
        inputLayout->addWidget(input);
    }

    for (const auto& button: formButtons) {
        inputLayout->addWidget(button);
    }

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);
}

EventForm::EventForm(const QString& inputType, int inputSize, const QString& buttonType, int buttonsSize) :
    mainLayout(new QVBoxLayout()), inputLayout(new QGridLayout()), buttonsLayout(new QGridLayout())
{
    UiInput* factory = new UiInput();
    for (int i = 0; i < inputSize; ++i) {
        inputList.push_back(factory->create(inputType));
    }
    delete factory;
    factory = nullptr;

    UiButton* buttonFactory = new UiButton();
    for (int i = 0; i < buttonsSize; ++i) {
        formButtons.push_back(buttonFactory->create(buttonType));
    }
    delete buttonFactory;
    buttonFactory = nullptr;

    for (const auto& input: inputList) {
        inputLayout->addWidget(input);
    }

    for (const auto& button: formButtons) {
        inputLayout->addWidget(button);
    }

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);
}

EventForm::EventForm(const EventForm &other) : painter(new QWidget)
{
    size_t inputListSize = this->inputList.size();
    size_t i = 0;
    for (const auto& otherInput: other.inputList) {
        if (i >= inputListSize) {
            this->inputList.push_back(otherInput);
        } else {
            this->inputList[i] = otherInput;
        }
        this->inputLayout->addWidget(inputList[i]);
        ++i;
    }

    size_t buttonListSize = this->formButtons.size();
    i = 0;
    for (const auto& otherButton: other.formButtons) {
        if (i >= buttonListSize) {
            this->formButtons.push_back(otherButton);
        } else {
            this->formButtons[i] = otherButton;
        }
        this->buttonsLayout->addWidget(formButtons[i]);
        ++i;
    }

    this->inputLayout = other.inputLayout;
    this->buttonsLayout = other.buttonsLayout;
    this->mainLayout = other.mainLayout;
}

EventForm &EventForm::operator=(const EventForm &other)
{
    size_t inputListSize = this->inputList.size();
    size_t i = 0;
    for (const auto& otherInput: other.inputList) {
        if (i >= inputListSize) {
            this->inputList.push_back(otherInput);
        } else {
            this->inputList[i] = otherInput;
        }
        this->inputLayout->addWidget(inputList[i]);
        ++i;
    }

    size_t buttonListSize = this->formButtons.size();
    i = 0;
    for (const auto& otherButton: other.formButtons) {
        if (i >= buttonListSize) {
            this->formButtons.push_back(otherButton);
        } else {
            this->formButtons[i] = otherButton;
        }
        this->buttonsLayout->addWidget(formButtons[i]);
        ++i;
    }

    this->inputLayout = other.inputLayout;
    this->buttonsLayout = other.buttonsLayout;
    this->mainLayout = other.mainLayout;

    return *this;
}

EventForm::~EventForm()
{
    delete inputLayout;
    delete buttonsLayout;
    delete mainLayout;
}

EventForm *EventForm::create(const QString &objType)
{
    if (objType == "defaultForm") {
        return new EventForm();
    }
    return new EventForm();
}
