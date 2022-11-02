#include "playercharacter.h"

#include <QDebug>
#include <QKeyEvent>


PlayerCharacter::PlayerCharacter(int x, int y) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    current_index_of_player_img = 0;
    delay_animation_counter = 0;
    delay_animation = 7;

    QPixmap player_img;
    for (int i = 1; i <= 12; i++) {
        QString location = "../smuggler/assets/player_character/player" + QString::number(i) + QString(".png");
        player_img.load(location);
        player_imgs.push_back(player_img);
    }

    player_rect = QRect(x, y, player_imgs[0].width(), player_imgs[0].height());
}

QRectF PlayerCharacter::boundingRect() const {
    // outer most edges
    return player_rect;
}

void PlayerCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(player_rect, player_imgs[current_index_of_player_img]);
}

void PlayerCharacter::player_animation(QKeyEvent *event) {
    // moving left
    if (event->key() == Qt::Key_A) {
        if (delay_animation_counter == delay_animation) {
            if (current_index_of_player_img < 11 && current_index_of_player_img >= 9) {
                current_index_of_player_img++;
            }
            else {
                current_index_of_player_img = 9;
            }
            delay_animation_counter = 0;
        }
    }

    // moving right
    if (event->key() == Qt::Key_D) {
        if (delay_animation_counter == delay_animation) {
            if (current_index_of_player_img < 5 && current_index_of_player_img >= 3) {
                current_index_of_player_img++;
            }
            else {
                current_index_of_player_img = 3;
            }
            delay_animation_counter = 0;
        }
    }

    // moving up
    if (event->key() == Qt::Key_W) {
        if (delay_animation_counter == delay_animation) {
            if (current_index_of_player_img < 8 && current_index_of_player_img >= 6) {
                current_index_of_player_img++;
            }
            else {
                current_index_of_player_img = 6;
            }
            delay_animation_counter = 0;
        }
    }

    // moving down
    if (event->key() == Qt::Key_S) {
        if (delay_animation_counter == delay_animation) {
            if (current_index_of_player_img < 2 && current_index_of_player_img >= 0) {
                current_index_of_player_img++;
            }
            else {
                current_index_of_player_img = 0;
            }
            delay_animation_counter = 0;
        }
    }
    delay_animation_counter++;
}

