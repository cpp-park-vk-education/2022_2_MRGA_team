#ifndef INFORMATION_FIELD_H
#define INFORMATION_FIELD_H

#include <painter.hpp>

class information_field : public painter
{
    Q_OBJECT

public:
    explicit information_field(QString header = nullptr, QWidget* parrent = nullptr);
    ~information_field();

private:
    QLabel* m_header;    
    QLineEdit* m_value;

    void set_interface_style();
};

#endif // INFORMATION_FIELD_H
