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
    mainLayout(new QVBoxLayout(this)), inputLayout(new QGridLayout()), buttonsLayout(new QGridLayout())
{
    this->setStyleSheet("max-width: 800px; max-height: 800px; background-color: rgba(111, 81, 174, 1); border-radius: 15px;");

    if (inputSize == 0 && buttonType == "" && buttonsSize == 0) {} // заглушка

    if (inputType == "settingsInput") {
        inputList.push_back(new UiInput(inputType, "UserName", "username"));
        inputList.push_back(new UiInput(inputType, "Password", "password"));
        inputList.push_back(new UiInput(inputType, "Email", "email"));
        inputList.push_back(new UiInput(inputType, "Birth Date", "birth date"));
        inputList.push_back(new UiInput(inputType, "Description", "description"));
        formButtons.push_back(new UiButton("", "text-align: center; padding: 0px; margin: 0px; max-width: 250px; max-height: 50px; background-color: #42c0c2;", "Save"));
    }

    if (inputType == "settingsInputRight") {
        inputList.push_back(new UiInput(inputType, "Country", "country"));
        inputList.push_back(new UiInput(inputType, "City", "city"));
        inputList.push_back(new UiInput(inputType, "Street", "Street"));
        inputList.push_back(new UiInput(inputType, "House", "house"));
        inputList.push_back(new UiInput(inputType, "Apartment", "apartment"));
        formButtons.push_back(new UiButton("", "text-align: center; padding: 0px; margin: 0px; max-width: 250px; max-height: 50px; background-color: #42c0c2;", "Save address"));
    }

    if (inputType == "createFormInput") {
        inputList.push_back(new UiInput(inputType, "Event name", ""));
    }

    size_t rowNumber = 0;
    for (const auto& input: inputList) {
        inputLayout->addWidget(input, rowNumber++, 0, Qt::AlignTop);
    }

    rowNumber = 0;
    for (const auto& button: formButtons) {
        buttonsLayout->addWidget(button, rowNumber++, 0, Qt::AlignTop);
    }

    mainLayout->addLayout(inputLayout, Qt::AlignTop);
    mainLayout->addLayout(buttonsLayout, Qt::AlignTop);
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
