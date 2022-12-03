#include "EventItem.hpp"


EventItem::EventItem(QWidget *parent) : painter(parent)
{
    for (size_t i = 0; i < 8; ++i) {
        switch (i) {
            case 0:
                fieldsMap["description"] = "";
                break;
            case 1:
                fieldsMap["data"] = "";
                break;
            case 2:
                fieldsMap["time"] = "";
                break;
            case 3:
                fieldsMap["peopleNumber"] = "";
                break;
            case 4:
                fieldsMap["eventTime"] = "";
                break;
            case 5:
                fieldsMap["address"] = "";
                break;
            case 6:
                fieldsMap["averageCheck"] = "";
                break;
            case 7:
                fieldsMap["maxPeople"] = "";
                break;
        }
    }
}

EventItem::EventItem(const QString &_userPhoto, const std::initializer_list<QString> &list)
{
    UiLabel* labelFactory = new UiLabel();
    this->userAvatar = *(labelFactory->create(_userPhoto));
    delete labelFactory;
    labelFactory = nullptr;

    size_t i = 0;
    for (const auto& field : list) {
        switch (i) {
            case 0:
                fieldsMap["description"] = field;
                break;
            case 1:
                fieldsMap["data"] = field;
                break;
            case 2:
                fieldsMap["time"] = field;
                break;
            case 3:
                fieldsMap["peopleNumber"] = field;
                break;
            case 4:
                fieldsMap["eventTime"] = field;
                break;
            case 5:
                fieldsMap["address"] = field;
                break;
            case 6:
                fieldsMap["averageCheck"] = field;
                break;
            case 7:
                fieldsMap["maxPeople"] = field;
                break;
        }
        ++i;
    }

}

EventItem::~EventItem()
{

}

EventItem *EventItem::create(const QString &typeEvent)
{
    if (typeEvent == "defaultEvent") {
        return new EventItem();
    }
    return new EventItem();
}
