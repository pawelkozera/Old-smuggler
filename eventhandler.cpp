#include "eventhandler.h"
#include "movingspeed.h"
#include "wind.h"

#include "qtimer.h"

#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>

#include <random>


EventHandler::EventHandler(std::vector<Island *> islands
                           ,PlayerCharacter *player_character,
                           PlayerPlane *player_plane,
                           Settings *settings,
                           Sounds *sounds,
                           Interface *interface,
                           Menu *menu,
                           Ui::MainWindow *ui,
                           QGraphicsScene *scene,
                           Wind *wind,
                           Compass *compass,
                           HallOfFame *hallOfFame,
                           QList<Cloud*> clouds,
                           std::vector<EnemyPlane *> enemyPlanes)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(my_timer_slot()));
    timerCloud = new QTimer();
    connect(timerCloud, &QTimer::timeout, this,  &EventHandler::moveCloud);
    timerCloud->start(20);
    int ms = 1000;
    int fps = 60;
    timer->start(ms/fps);

    this->islands = islands;
    this->player_character = player_character;
    this->player_plane = player_plane;
    this->settings = settings;
    this->sounds = sounds;
    this->interface = interface;
    this->menu=menu;
    this->ui=ui;
    this->scene=scene;
    this->wind=wind;
    this->compass=compass;
    this->hallOfFame=hallOfFame;
    this->clouds=clouds;
    this->enemyPlanes = enemyPlanes;


    player_plane->set_text_drop();
    scene->addItem(player_plane->text_drop);

    player_character_events = true;
    collision_with_plane = false;
    collision_with_island_borders = false;

    player_last_position.first = 0;
    player_last_position.second = 0;

    player_island = NULL;
    interactive_object_collided = NULL;

    wind->UpdateWindDirection();

}

void EventHandler::my_timer_slot() {
    sounds->music->play();

    for(int i = 0; i < enemyPlanes.size(); i++) {
        enemyPlanes[i]->rotate(settings->window_width, settings->window_height);
        enemyPlanes[i]->follow_player(settings->window_width, settings->window_height, player_plane);
    }

    if (!player_character_events) {
        interface->draw_cockpit(settings->window_height, player_plane);
        UpdateArrowDirection();

        for(int i = 0; i < islands.size(); i++) {
            islands[i]->move_island(MovingSpeed::x_speed, MovingSpeed::y_speed);
        }

        for(int i = 0; i < islands.size(); i++) {
            islands[i]->move_island(MovingSpeed::x_speed, MovingSpeed::y_speed);
        }

        for(int i = 0; i < enemyPlanes.size(); i++) {
            enemyPlanes[i]->move_plane(MovingSpeed::x_speed, MovingSpeed::y_speed);
        }

        player_plane->animation();
        player_plane->set_up_current_speed();
        player_plane->calculate_x_y_speed();
        player_plane->fuel_usage();

        for(int i = 0; i < islands.size(); i++) {
            if (islands[i]->antiAircraftGun != NULL) {
                if (islands[i]->antiAircraftGun->is_in_range(settings->window_width, settings->window_height)) {
                    islands[i]->antiAircraftGun->rotate(settings->window_width, settings->window_height);
                    islands[i]->antiAircraftGun->shoot(player_plane->item, clouds);
                }
            }
        }
    }
    else {
    }

    for(int i = 0; i < islands.size(); i++) {
            if (islands[i]->antiAircraftGun != NULL) {
                islands[i]->antiAircraftGun->move_used_bullets();
                islands[i]->antiAircraftGun->check_used_bullets_collision(player_plane->item);
            }
        }
}

void EventHandler::keyPressEvent(QKeyEvent *event) {
    // player character
    if (player_character_events) {
        if (event->key() == Qt::Key_E && collision_with_plane) {
            entering_plane_event();
            interface->cockpit_item->show();
        }
        else {
            character_on_island_event(event);
        }
    }
    // player plane
    else {
        if (event->key() == Qt::Key_E && MovingSpeed::current_speed == 0) {
            Island *plane_on_island = player_plane->plane_on_island(event, islands);
            if (plane_on_island) {
                player_plane->text_drop->hide();
                leaving_plane_event();
                interface->cockpit_item->hide();
                interface->draw_cockpit(settings->window_height, player_plane);
            }
        }
        else if (event->key() == Qt::Key_Q && player_plane->IsOnTargetIsland(islands))
        {
            if(player_plane->cargo>0)
            {
                score->increase(player_plane->cargo);
                player_plane->drop_cargo();
                drop_cago();
                select_target_island();
            }
        }
        else {
            plane_events(event);
            if(player_plane->IsOnTargetIsland(islands) && player_plane->cargo>0 && !player_character_events)
            {
               player_plane->text_drop->show();
            }
            else{
               player_plane->text_drop->hide();
            }
        }
    }
    // both plane and player character
    if (event->key() == Qt::Key_M) {
        interface->draw_map();
    }
    // menu
    if (event->key() == Qt::Key_Escape)
    {
        if(menu->menuIsEnable==true)
        {
            menu->draw_menu(1408, 800);
            ui->graphicsView->setScene(menu->scene);
            ui->graphicsView->show();
            menu->menuIsEnable=false;
        }
        else
        {
            menu->remove_menu();
            ui->graphicsView->setScene(scene);
            ui->graphicsView->show();
            menu->menuIsEnable=true;
        }
    }

    if(menu->menuIsEnable==false)
    {
        if (event->key() == Qt::Key_Up)
        {
           if(menu->selectedOption==0)
            {
                menu->selectedOption=3;
            }
           else
           {
               menu->selectedOption--;
           }
           menu->change_size(menu->selectedOption);
        }
        if (event->key() == Qt::Key_Down)
        {
           if(menu->selectedOption==3)
            {
                menu->selectedOption=0;
            }
           else
           {
               menu->selectedOption++;
           }
           menu->change_size(menu->selectedOption);
        }

        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space)
        {
            if(menu->PlayEnable)
            {
                menu->remove_menu();
                ui->graphicsView->setScene(scene);
                ui->graphicsView->show();
                menu->menuIsEnable=true;
            }
            else if(menu->PointsEnable)
            {
                if(!hallOfFame->visible)
                {
                    menu->remove_menu();
                    ui->graphicsView->setScene(scene);
                    ui->graphicsView->show();
                    scene->addWidget(hallOfFame->table);
                    hallOfFame->table->show();
                    hallOfFame->drawHallOfFame();
                    hallOfFame->visible=true;
                }
                else
                {
                    menu->draw_menu(1408, 800);
                    ui->graphicsView->setScene(menu->scene);
                    ui->graphicsView->show();
                    hallOfFame->table->setVisible(false);
                    hallOfFame->visible=false;
                    menu->selectedOption=1;

                }
            }
            else if(menu->SettingsEnable)
            {
                qDebug()<<"Settings";
            }
            else if(menu->ExitEnable)
            {
                QApplication::exit();
            }
        }

    }

    update();
}

void EventHandler::entering_plane_event() {
    player_character_events = false;
    player_character->player_item->hide();
    MovingSpeed::x_speed = 0;
    MovingSpeed::y_speed = 0;

    std::pair<int, int> pixels_to_move = player_plane->center_plane_on_screen(player_character);
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island(pixels_to_move.first, pixels_to_move.second);
    }
    player_plane->simple_movement(pixels_to_move.first, pixels_to_move.second);

    // wind vane
    wind->UpdateWindStrength();
    //wind->UpdateWindDirection();
    wind->WindSock->show();
    wind->DirectionPixmap->show();
    scene->addItem(wind->WindSock);
    scene->addItem(wind->DirectionPixmap);

    compass->compassItem->show();
    compass->arroItem->show();
}

void EventHandler::character_on_island_event(QKeyEvent *event) {
    player_island = player_character->player_on_island(event, islands);
    if (player_island) {
        InteractiveObject *object_collided_bufor = player_character->collision_with_island_objects(event, player_island);
        collision_with_plane = player_character->collision(event, player_plane->item);
        collision_with_island_borders = player_character->collision(event, player_island->island_item, true);

        bool collision_with_antiaircraftgun = false;
        if (player_island->antiAircraftGun != NULL)
            collision_with_antiaircraftgun = player_character->collision(event, player_island->antiAircraftGun->item, true);

        if (!object_collided_bufor && !collision_with_plane && collision_with_island_borders && !collision_with_antiaircraftgun) {
            character_moving(event);
        }
        else if (object_collided_bufor) {
            set_interactive_object_collided(object_collided_bufor);
        }

        if (interactive_object_collided) {
            interactive_objects_handler(event);
        }
    }

    player_character->player_animation(event);
    player_character->change_character_img();
}

void EventHandler::character_moving(QKeyEvent *event) {
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island_event(event);
    }
    for(int i = 0; i < enemyPlanes.size(); i++) {
        enemyPlanes[i]->move_plane_event(event);
    }
    player_plane->simple_movement_event(event);
    for (Cloud* cloud : clouds)
        cloud->move_cloud_event(event);
}

void EventHandler::leaving_plane_event() {
    player_character_events = true;
    player_character->player_item->show();
    wind->WindSock->hide();
    wind->DirectionPixmap->hide();
    compass->compassItem->hide();
    compass->arroItem->hide();

    MovingSpeed::x_speed = 3;
    MovingSpeed::y_speed = 3;

    std::pair<int, int> pixels_to_move = player_plane->leave_plane(player_character);
    for(int i = 0; i < islands.size(); i++) {
        islands[i]->move_island(pixels_to_move.first, pixels_to_move.second);
    }
    player_plane->simple_movement(pixels_to_move.first, pixels_to_move.second);
}

void EventHandler::plane_events(QKeyEvent *event) {
    player_plane->change_power(event);
    player_plane->rotate(event);
}

void EventHandler::set_interactive_object_collided(InteractiveObject *object_collided_bufor) {
    player_last_position.first = player_plane->item->x();
    player_last_position.second = player_plane->item->y();
    interactive_object_collided = object_collided_bufor;
    interactive_object_collided->alert->show_alert_for_object = true;

    if (interactive_object_collided->cargo_alert)
        interactive_object_collided->show_alert(player_plane->cargo);
    else if (interactive_object_collided->fuel_alert)
        interactive_object_collided->show_alert(player_plane->fuel);
    else
        interactive_object_collided->show_alert(player_plane->cargo);
}

void EventHandler::interactive_objects_handler(QKeyEvent *event) {
    bool player_position_changed = (player_last_position.first != player_plane->item->x() || player_last_position.second != player_plane->item->y());

    if (event->key() == Qt::Key_E) {
        if (interactive_object_collided->cargo_alert) {
            player_plane->add_cargo(interactive_object_collided->max_amount_of_cargo());
            interactive_object_collided->show_alert(player_plane->cargo);
            sounds->add_resources->play();
        }
        else if (interactive_object_collided->fuel_alert) {
            player_plane->add_fuel(interactive_object_collided->max_amount_of_fuel());
            interactive_object_collided->show_alert(player_plane->fuel);
            sounds->add_resources->play();
        }
        else {
            if (player_island->target_island) {
                if (player_plane->cargo > 0) {
                    score->increase(player_plane->cargo);
                    player_plane->cargo = 0;
                    interactive_object_collided->show_alert(player_plane->cargo);
                    select_target_island(player_island);
                }
            }
        }
    }
    else if (event->key() == Qt::Key_Q) {
        if (interactive_object_collided->cargo_alert) {
            player_plane->remove_cargo();
            interactive_object_collided->show_alert(player_plane->cargo);
            sounds->add_resources->play();
        }
        else if (interactive_object_collided->fuel_alert) {
            player_plane->remove_fuel();
            interactive_object_collided->show_alert(player_plane->fuel);
            sounds->add_resources->play();
        }
    }
    else if (interactive_object_collided->alert->show_alert_for_object && player_position_changed) {
        interactive_object_collided->alert->show_alert_for_object = false;
        interactive_object_collided->hide_alert();
        interactive_object_collided = NULL;
    }
    // TODO: tymczasowo, zanim znajdziemy miejsce na koniec gry itp.

       if (event->key() == Qt::Key_H) {
           hallOfFame->show(score->getScore());
       }
}

void EventHandler::select_target_island(const Island *previous_target_island) {
    for (int i = 0; i < islands.size(); i++) {
        islands[i]->target_island = false;
    }

    // random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, islands.size() - 1);

    int island_index;
    do {
       island_index = distr(gen);
    }
    while (islands[island_index] == previous_target_island);


    islands[island_index]->target_island = true;
    target_island=islands[island_index];
    map->generate_img_of_map(islands);
    interface->map_img.load("../smuggler/assets/interface/map.png");

    interface->map_img = interface->map_img.scaled(1408, 792);
    interface->map_item->setPixmap(interface->map_img);
    compass->prevoious_distance=compass->caluclateDistance(player_plane, target_island);
}

void EventHandler::drop_cago()
{
    QImage box;
    box.load("../smuggler/assets/objects/box.png");
    cargo_item=new QGraphicsPixmapItem(QPixmap::fromImage(box));
    cargo_item->setPos(player_plane->item->x(), player_plane->item->y());
    scene->addItem(cargo_item);

    timer2=new QTimer();
    QAction::connect(timer2, &QTimer::timeout, this, &EventHandler::cargo_item_update);
    timer2->start(30);
}

void EventHandler::cargo_item_update()
{
    cargo_item->setScale(cargo_item->scale()*0.9);
    if(cargo_item->scale()<=0)
    {
        timer2->stop();
    }
}

void EventHandler::UpdateArrowDirection()
{
    qreal distance=QLineF(player_plane->item->pos(), target_island->island_item->pos()).length();

    if(distance<compass->prevoious_distance)
    {
        setArrow();
    }
    else
    {
        compass->arroItem->setRotation(compass->arroItem->rotation()+10);
    }
    compass->prevoious_distance=distance;
}

void EventHandler::setArrow()
{
    compass->arroItem->setRotation(0);
    QVector2D direction=QVector2D(target_island->island_item->pos()-player_plane->item->pos());
    qreal angle= atan2(direction.y(), direction.x());
    compass->arroItem->setRotation(angle * 180.0 / M_PI);
}

void EventHandler::moveCloud()
{
    QVector2D windDirection=wind->GetWindDirection().normalized();
    for (Cloud* cloud : clouds)
    {
        cloud->cloudPixmap->setPos(cloud->cloudPixmap->x() - 2*windDirection.x(), cloud->cloudPixmap->y()- 2*windDirection.y());
        //qDebug()<<"x: "<<cloud->cloudPixmap->x()<<"  y: "<<cloud->cloudPixmap->y();
        if(cloud->cloudPixmap->x()>10000)
            cloud->cloudPixmap->setPos(-10000, cloud->cloudPixmap->y());
        if(cloud->cloudPixmap->x()<-10000)
            cloud->cloudPixmap->setPos(10000, cloud->cloudPixmap->y());
        if(cloud->cloudPixmap->y()>10000)
            cloud->cloudPixmap->setPos(cloud->cloudPixmap->x(), -10000);
        if(cloud->cloudPixmap->y()<-10000)
            cloud->cloudPixmap->setPos(cloud->cloudPixmap->x(), 10000);
    }
}


