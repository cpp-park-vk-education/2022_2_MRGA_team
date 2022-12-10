#include "Loader.hpp"


UiLoader::UiLoader(const QString& pathToImage, QWidget *parent) : painter(parent), loader(new QLabel()), movie(new QMovie(pathToImage)), layout(new QVBoxLayout(this))
{
    loader->setMovie(movie);
    layout->addWidget(loader);
}

UiLoader::UiLoader(const UiLoader &other) : painter(new QWidget)
{
    this->loader = other.loader;
    this->movie = other.movie;
    this->layout = other.layout;
}

UiLoader &UiLoader::operator=(const UiLoader& other)
{
    this->loader = other.loader;
    this->movie = other.movie;
    this->layout = other.layout;
    return *this;
}

UiLoader::~UiLoader()
{
    delete loader;
    delete movie;
    delete layout;
}

UiLoader::UiLoader(const QString &styleSheet, const QString &pathToImage) : loader(new QLabel()), movie(new QMovie(pathToImage)), layout(new QVBoxLayout(this))
{
    loader->setMovie(movie);
    loader->setStyleSheet(styleSheet);
    layout->addWidget(loader);
}

UiLoader::UiLoader(const QString &pathToImage, int labelOffsetX, int labelOffsetY, int width, int height) : loader(new QLabel()), movie(new QMovie(pathToImage)), layout(new QVBoxLayout(this))
{
    loader->setMovie(movie);
    loader->setGeometry(labelOffsetX, labelOffsetY, width, height);
    layout->addWidget(loader);
}
