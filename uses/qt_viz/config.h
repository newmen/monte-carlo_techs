#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

struct Config
{
public:
    Config() : shotDataPath(""), shotDirPath(""), cellSideLength(1) {}

    QString shotDataPath;
    QString shotDirPath;
    int cellSideLength;
};

#endif // CONFIG_H
