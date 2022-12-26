#include "settings.hpp"

settings::settings(QWidget* parent)
    : painter(parent),
      m_settings_page(new QVBoxLayout(this)),
      m_scrolls_layout(new QHBoxLayout),
      m_first_scroll(new QScrollArea),
      m_first_settings_scroll_widget(new painter),
      m_first_settings_scroll_layout(new QVBoxLayout),
      m_second_scroll(new QScrollArea),
      m_second_settings_scroll_widget(new painter),
      m_second_settings_scroll_layout(new QVBoxLayout),
      m_user_settings(new QLabel("Настройки профиля")),
      m_name_header(new information_field("Имя:")),
      m_second_name_header(new information_field("Фамилия:")),
      m_age_header(new information_field("Возраст:")),
      m_phone_number_header(new information_field("Телефон:")),
      m_status_header(new information_field("Статус:")),
      m_mail_header(new information_field("Почта:")),
      m_save(new QPushButton("Cохранить")),
      m_country_header(new information_field("Страна:")),
      m_district_header(new information_field("Регион:")),
      m_city_header(new information_field("Город:")),
      m_street_header(new information_field("Улица:")),
      m_housing_header(new information_field("Корпус:")),
      m_index_header(new information_field("Индекс:")),
      m_save_address(new QPushButton("Сохранить адрес"))
{
    // выдаём id-ки виджетам
    this->setObjectName("settings_page");
    m_save->setObjectName("save_button");
    m_save_address->setObjectName("save_adress_button");
    m_user_settings->setObjectName("user_settings");
    m_save->setObjectName("save_button");
    m_save_address->setObjectName("save_addres_button");
    m_user_settings->setAlignment(Qt::AlignCenter);

    // задаём свойства main_layout
    m_settings_page->setSpacing(20);

    // задаём свойства layout, который содержит два скролла
    m_scrolls_layout->setSpacing(200);

    // для стилизация и возможности изменения размеров через qss скролла
    m_first_scroll->setWidgetResizable(true);
    m_second_scroll->setWidgetResizable(true);
    // установим отступы у скроллов
    m_first_settings_scroll_layout->setContentsMargins(50, 40, 50, 30);
    m_second_settings_scroll_layout->setContentsMargins(50, 40, 50, 30);
    // установим отступы между information_field у скроллов
    m_first_settings_scroll_layout->setSpacing(40);
    m_second_settings_scroll_layout->setSpacing(40);

    // зададим id для компонентов первого скролла
    m_first_settings_scroll_widget->setObjectName("groups_widget_first_scroll_title");
    m_first_scroll->setObjectName("first_scroll");
    // зададим id для компонетов второго скролла
    m_second_settings_scroll_widget->setObjectName("groups_widget_second_scroll_title");
    m_second_scroll->setObjectName("second_scroll");

    // скорее всего необходимо задать setObjectName непосредственно скроллу

    // добавляем элементы в layout скролла(1-го) c данными пользователя
    m_first_settings_scroll_layout->addWidget(m_name_header, 0, Qt::AlignLeft | Qt::AlignTop);
    m_first_settings_scroll_layout->addWidget(m_second_name_header, 1, Qt::AlignLeft | Qt::AlignTop);
    m_first_settings_scroll_layout->addWidget(m_age_header, 2, Qt::AlignLeft | Qt::AlignTop);
    m_first_settings_scroll_layout->addWidget(m_phone_number_header, 3, Qt::AlignLeft | Qt::AlignTop);
    m_first_settings_scroll_layout->addWidget(m_status_header, 4, Qt::AlignLeft | Qt::AlignTop);
    m_first_settings_scroll_layout->addWidget(m_mail_header, 5, Qt::AlignLeft | Qt::AlignTop);
    m_first_settings_scroll_layout->addWidget(m_save, 6, Qt::AlignCenter | Qt::AlignTop);

    // добавляем элементы в layout скролла(2-го) c адресом пользователя
    m_second_settings_scroll_layout->addWidget(m_country_header, 7, Qt::AlignLeft | Qt::AlignTop);
    m_second_settings_scroll_layout->addWidget(m_district_header, 8, Qt::AlignLeft | Qt::AlignTop);
    m_second_settings_scroll_layout->addWidget(m_city_header, 9, Qt::AlignLeft | Qt::AlignTop);
    m_second_settings_scroll_layout->addWidget(m_street_header, 10, Qt::AlignLeft | Qt::AlignTop);
    m_second_settings_scroll_layout->addWidget(m_housing_header, 11, Qt::AlignLeft | Qt::AlignTop);
    m_second_settings_scroll_layout->addWidget(m_index_header, 12, Qt::AlignLeft | Qt::AlignTop);
    m_second_settings_scroll_layout->addWidget(m_save_address, 13, Qt::AlignCenter | Qt::AlignTop);

    // запаковываем виджет и layout в скролл(формируем 1-ый скролл)
    m_first_settings_scroll_widget->setLayout(m_first_settings_scroll_layout);              // установим layout, в котором будет располагаться скролл
    m_first_scroll->setWidget(m_first_settings_scroll_widget);                              // поскольку класс виджет не имеет своего скролла, установим ему виджет

    // запаковываем виджет и layout в скролл(формируем 2-ой скролл)
    m_second_settings_scroll_widget->setLayout(m_second_settings_scroll_layout);              // установим layout, в котором будет располагаться скролл
    m_second_scroll->setWidget(m_second_settings_scroll_widget);                              // поскольку класс виджет не имеет своего скролла, установим ему виджет

    // связываем обработчкики
//    connect(this->m_save, &QPushButton::clicked, this, &settings::on_save_button_pressed);
//    connect(this->m_save, &QPushButton::released, this, &settings::on_save_button_released);

//    this->set_interface_style();

    // формируем горизонтальный layout
    m_scrolls_layout->addWidget(m_first_scroll);
    m_scrolls_layout->addWidget(m_second_scroll);

//    m_settings_page->addWidget(m_navbar);
    m_settings_page->addWidget(m_user_settings);
    m_settings_page->addLayout(m_scrolls_layout); // добавляем горизонтальный layout, в котором содержаться два вертикальных
}

settings::~settings()
{

}

QPushButton *settings::get_save_btn()
{
    return nullptr;
}

QPushButton *settings::get_save_addres_btn()
{
    return nullptr;
}

//QPushButton *settings::get_shedule_btn()
//{
//    return m_navbar->get_shedule_button();
//}

//QPushButton *settings::get_friends_btn()
//{
//    return m_navbar->get_friends_button();
//}

//QPushButton *settings::get_groups_btn()
//{
//    return m_navbar->get_groups_button();
//}

//QPushButton *settings::get_settings_btn()
//{
//    return m_navbar->get_settings_button();
//}

//QPushButton *settings::get_logout_btn()
//{
//    return m_navbar->get_logout_button();
//}

//QPushButton *settings::get_user_avatar_btn()
//{
//    return m_navbar->get_user_avatar_button();
//}

//void settings::set_interface_style()
//{
//    return this->setStyleSheet(stylehelper::get_settings_background());
//}

//void settings::on_save_button_pressed()
//{
//    return this->setStyleSheet(stylehelper::get_save_button_pressed());
//}

//void settings::on_save_button_released()
//{
//    this->setStyleSheet(stylehelper::get_save_button_released());
//    this->setStyleSheet(stylehelper::get_save_button_hover_released());
//}

//void settings::on_save_address_button_pressed()
//{

//}

//void settings::on_save_address_button_released()
//{

//}
