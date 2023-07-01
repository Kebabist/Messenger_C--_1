#ifndef DTO_H
#define DTO_H

#include <QString>
#include <QMultiMap>

class DTO
{
public:
    DTO();
    DTO(QString name, QString title);
    DTO(const DTO& other);
    virtual ~DTO();

    DTO& operator=(const DTO& other);

    // Getters
    const QString getName() const;
    const QString getTitle() const ;
    const QMultiMap<QString, QPair<QString, QString>> &getMessages() const;

    // Setters
    void setMessage(QString src, QString message, QString date);

protected:
    QString name;
    QString title;
    QMultiMap<QString, QPair<QString, QString>> messages;
};

#endif // DTO_H
