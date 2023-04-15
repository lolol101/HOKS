#ifndef MSG_H
#define MSG_H

#include <QString>

struct msg {
    QString author;
    QString time;
    QString text_message;
    bool media;

    msg() = default;
    msg(QString author_, QString time_, QString text_, bool media_) : author(std::move(author_)), time(std::move(time_)), text_message(std::move(text_)), media(media_) {}
};

#endif // MSG_H
