#ifndef MYTEXTSTREAM_H
#define MYTEXTSTREAM_H

#include <QString>
#include <QStringBuilder>
#include <QTextStream>

class MyTextStream : public QTextStream
{
public:
    // Constructor
    MyTextStream(QString* str) : QTextStream(str) {}

    // Overloaded stream extraction operator
    MyTextStream& operator>>(QString& str)
    {
        QChar ch;

        // Read characters until a tab or space is encountered
        while (!atEnd())
        {
            QTextStream::operator>>(ch);

            if (ch == '\t' || ch == ' ')
                break;

            str = str % ch; // Append the character to the string
        }

        return *this;
    }
};

#endif // MYTEXTSTREAM_H
