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
    this->setStyleSheet("max-height: 600px; background-color: rgba(111, 81, 174, 1); border-radius: 15px;");

    std::vector<QString> initInputTitleList1(inputSize);
    std::vector<QString> initInputTitleList;

    if (inputType == "settingsInput") {
        initInputTitleList.push_back("UserName");
        initInputTitleList.push_back("Birth Date");
        initInputTitleList.push_back("Lol");
        initInputTitleList.push_back("Kek");
        initInputTitleList.push_back("Amfkaflkamfklamsfkaf");
    }

    for (const auto& title : initInputTitleList) {
        if (inputType == "") {
            inputList.push_back(new UiInput(inputType, ""));
        }
        inputList.push_back(new UiInput(inputType, title));
    }

    for (int i = 0; i < buttonsSize; ++i) {
        if (buttonType == "") {
            formButtons.push_back(new UiButton("", "min-width: 200px; min-height: 50; border-radius: 10px;"));
        }
        formButtons.push_back(new UiButton("Save", "min-width: 200px; min-height: 50; border-radius: 10px; background-color: green;"));
    }

    size_t rowNumber = 0;
    for (const auto& input: inputList) {
        inputLayout->addWidget(input, rowNumber++, 0);
    }

    for (const auto& button: formButtons) {
        buttonsLayout->addWidget(button);
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
