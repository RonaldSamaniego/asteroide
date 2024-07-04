#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include "Animation.h"
#include "Entity.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Constants.h"  
#include "Explosion.h"
#include "Score.h"
#include <SFML/Audio.hpp>

int main() {
    srand(time(0));

    sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    sf::Sprite background(t2);

    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

    std::list<Entity*> entities;

    for (int i = 0; i < 15; i++) {
        Asteroid* a = new Asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    Player* p = new Player();
    p->settings(sPlayer, 200, 200, 0, 20);
    entities.push_back(p);

    Score score;

    sf::Music music;
    if (!music.openFromFile("Music/audio.mp3")) {
        return -1;  
    }
    music.setLoop(true);  
    music.play();

    //  sonido de disparo
        sf::SoundBuffer shootBuffer;
    if (!shootBuffer.loadFromFile("sounds/disparo.mp3")) {
        
        return -1;  
    }

    sf::Sound shootSound;
    shootSound.setBuffer(shootBuffer);

    //  sonido de explosión de asteroides
    sf::SoundBuffer asteroidExplosionBuffer;
    if (!asteroidExplosionBuffer.loadFromFile("sounds/asteexplo.mp3")) {
        
        return -1;  
    }

    sf::Sound asteroidExplosionSound;
    asteroidExplosionSound.setBuffer(asteroidExplosionBuffer);

    // sonido de explosión de la nave
    sf::SoundBuffer shipExplosionBuffer;
    if (!shipExplosionBuffer.loadFromFile("sounds/Explonave.mp3")) {
        
        return -1;  
    }
    sf::Sound shipExplosionSound;
    shipExplosionSound.setBuffer(shipExplosionBuffer);

    

    
    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space) {
                    Bullet* b = new Bullet();
                    b->settings(sBullet, p->x, p->y, p->angle, 10);
                    entities.push_back(b);
                    shootSound.play();         
                }
            
        }

        


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle += 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p->angle -= 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p->thrust = true;
        else p->thrust = false;

        for (auto a : entities)
            for (auto b : entities) {
                if (a->name == "asteroid" && b->name == "bullet")
                    if (isCollide(a, b)) {
                        a->life = false;
                        b->life = false;

                        Entity* e = new Explosion();  
                        e->settings(sExplosion, a->x, a->y);
                        e->name = "explosion";
                        entities.push_back(e);

                        asteroidExplosionSound.play();

                        score.addPoints(100);

                        for (int i = 0; i < 2; i++) {
                            if (a->R == 15) continue;
                            Asteroid* e = new Asteroid();  
                            e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                            entities.push_back(e);
                        }
                    }

                if (a->name == "player" && b->name == "asteroid")
                    if (isCollide(a, b)) {
                        b->life = false;

                        Entity* e = new Explosion();  
                        e->settings(sExplosion_ship, a->x, a->y);
                        e->name = "explosion";
                        entities.push_back(e);

                        shipExplosionSound.play();

                        p->settings(sPlayer, W / 2, H / 2, 0, 20);
                        p->dx = 0;
                        p->dy = 0;
                    }
            }

        if (p->thrust) p->anim = sPlayer_go;
        else p->anim = sPlayer;

        for (auto e : entities)
            if (e->name == "explosion")
                if (e->anim.isEnd()) e->life = 0;

        if (rand() % 150 == 0) {
            Asteroid* a = new Asteroid();
            a->settings(sRock, 0, rand() % H, rand() % 360, 25);
            entities.push_back(a);
        }

        for (auto i = entities.begin(); i != entities.end();) {
            Entity* e = *i;

            e->update();
            e->anim.update();

            if (e->life == false) {
                i = entities.erase(i);
                delete e;
            }
            else i++;
        }

        
        app.draw(background);
        for (auto i : entities) i->draw(app);
        score.draw(app);
        app.display();
    }

    return 0;
}
