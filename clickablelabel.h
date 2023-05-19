#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QtWidgets>

// Classe dérivée de QLabel pour gérer les clics personnalisés
class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(const QString& text, QWidget* parent = nullptr)
        : QLabel(text, parent)
    {
    }

signals:
    // Signal personnalisé pour le clic
    void clicked();

protected:
    // Implémentation du gestionnaire d'événements de clic
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            emit clicked(); // Émettre le signal de clic personnalisé
        }
        QLabel::mousePressEvent(event); // Appel à la fonction de la classe de base
    }
};

#endif // CLICKABLELABEL_H
