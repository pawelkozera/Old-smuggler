#include "playercharacter.h"
#include <QDebug>


PlayerCharacter::PlayerCharacter(int screen_width, int screen_height) {
    setFlag(QGraphicsItem::ItemIsFocusable);
    current_index_of_player_img = 0;

    QPixmap player_img;
    for (int i = 1; i <= 6; i++) {
        QString location = "../smuggler/assets/player_character/player" + QString::number(i) + QString(".png");
        player_img.load(location);
        player_imgs.push_back(player_img);
    }

    player_rect = QRect(screen_width, screen_height, player_imgs[0].width(), player_imgs[0].height());
}

QRectF PlayerCharacter::boundingRect() const {
    // outer most edges
    return player_rect;
}

void PlayerCharacter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(player_rect, player_imgs[current_index_of_player_img]);
}

void PlayerCharacter::keyPressEvent(QKeyEvent *event) {
    update();
}
