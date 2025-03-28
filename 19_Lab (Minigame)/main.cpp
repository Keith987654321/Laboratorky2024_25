#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <thread>
//#include <chrono>
#include "list_array.hpp"

#define FIELD_SIZE 10

static double lastUpdateTime = 0;

class Snake {
    private:
        short speed = 2;
        short length;
        char direction, prev_direction, next_direction;
        Node* body_info = nullptr;
    public:
        Snake() {
            length = 1;
            direction = 'D';
            body_info = MakeList();
            PushBack(body_info, 0, 0);
        }

        Snake(short len) {
            length = len;
            direction = 'D';
            body_info = MakeList();
            for (int i = 0; i < length; i++) {
                PushBack(body_info, length - i - 1, 0);
            }
        }

        ~Snake() {
            if (body_info != nullptr) {
                ClearList(body_info);
                delete body_info;
            }
        }

        short len() { return length; }

        const Node* operator[](short index) {
            return GetElemByIndex(body_info, index);
        }

        short get_speed() { return speed; }

        char get_direction() { return direction; }

        char get_prev_direction() { return prev_direction; }

        char get_next_direction() { return next_direction; }

        void set_next_direction(char next_dir) {
            next_direction = next_dir;
        }
        
        void set_direction(char new_dir) { 
            if (new_dir == direction) { return; }
            prev_direction = direction;
            direction = new_dir; 
        }
        
        bool WillMeetSelf(short x_next, short y_next) {
            for (int i = 0; i < length - 1; i++) {
                if (GetElemByIndex(body_info, i)->x_coord == x_next && GetElemByIndex(body_info, i)->y_coord == y_next) {
                    std::cout << GetElemByIndex(body_info, i)->x_coord << " == " << x_next << std::endl;
                    std::cout << GetElemByIndex(body_info, i)->y_coord << " == " << y_next << std::endl;
                    return true;
                }
            }
            return false;
        }

        void MoveRight() {
            short x_prev = GetElemByIndex(body_info, 0)->x_coord;
            short y_prev = GetElemByIndex(body_info, 0)->y_coord;
            if (GetElemByIndex(body_info, 0)->x_coord + 1 >= FIELD_SIZE) { std::cout << "You're dead!\n"; return; }
            if (WillMeetSelf(x_prev + 1, y_prev)) {std::cout << "You've killed your self\n"; return;}
            else { GetElemByIndex(body_info, 0)->x_coord++; }

            for (int i = 1; i < length; i++) {
                std::swap(GetElemByIndex(body_info, i)->x_coord, x_prev);
                std::swap(GetElemByIndex(body_info, i)->y_coord, y_prev);
            }
        }

        void MoveLeft() {
            short x_prev = GetElemByIndex(body_info, 0)->x_coord;
            short y_prev = GetElemByIndex(body_info, 0)->y_coord;
            if (GetElemByIndex(body_info, 0)->x_coord - 1 < 0) { std::cout << "You're dead!\n"; return; }
            if (WillMeetSelf(x_prev - 1, y_prev)) {std::cout << "You've killed your self\n"; return;}
            else { GetElemByIndex(body_info, 0)->x_coord--; }

            for (int i = 1; i < length; i++) {
                std::swap(GetElemByIndex(body_info, i)->x_coord, x_prev);
                std::swap(GetElemByIndex(body_info, i)->y_coord, y_prev);
            }
        }

        void MoveUp() {
            short x_prev = GetElemByIndex(body_info, 0)->x_coord;
            short y_prev = GetElemByIndex(body_info, 0)->y_coord;
            if (GetElemByIndex(body_info, 0)->y_coord - 1 < 0) { std::cout << "You're dead!\n"; return; }
            if (WillMeetSelf(x_prev, y_prev - 1)) {std::cout << "You've killed your self\n"; return;}
            else { GetElemByIndex(body_info, 0)->y_coord--; }

            for (int i = 1; i < length; i++) {
                std::swap(GetElemByIndex(body_info, i)->x_coord, x_prev);
                std::swap(GetElemByIndex(body_info, i)->y_coord, y_prev);
            }
        }

        void MoveDown() {
            short x_prev = GetElemByIndex(body_info, 0)->x_coord;
            short y_prev = GetElemByIndex(body_info, 0)->y_coord;
            if (GetElemByIndex(body_info, 0)->y_coord + 1 >= FIELD_SIZE) { std::cout << "You're dead!\n"; return; }
            if (WillMeetSelf(x_prev, y_prev + 1)) {std::cout << "You've killed your self\n"; return;}
            else { GetElemByIndex(body_info, 0)->y_coord++; }

            for (int i = 1; i < length; i++) {
                std::swap(GetElemByIndex(body_info, i)->x_coord, x_prev);
                std::swap(GetElemByIndex(body_info, i)->y_coord, y_prev);
            }
        }

        void MoveSnake() {
            std::cout << "Direction: " << get_direction() << " Prev_Direction: " << get_prev_direction() << std::endl;
            if (direction == 'D' && prev_direction != 'A') { MoveRight(); }
            else if (direction == 'A' && prev_direction != 'D') { MoveLeft(); }
            else if (direction == 'S' && prev_direction != 'W') { MoveDown(); }
            else if (direction == 'W' && prev_direction != 'S') { MoveUp(); }
            else {
                direction = prev_direction;
                MoveSnake();
            }
        }
};

void FillField(sf::RectangleShape field[FIELD_SIZE][FIELD_SIZE]) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            sf::RectangleShape temp(sf::Vector2f(80.f, 80.f));
            //float x_coord = 50.f + (80.f * j) + (10.f * j);
            float x_coord = 50.f + (90.f * j);
            float y_coord = 50.f + (90.f * i);
            temp.setPosition(x_coord, y_coord); //
            field[i][j] = temp;
        }
    }
}

void DrawField(sf::RectangleShape field[FIELD_SIZE][FIELD_SIZE], sf::RenderWindow &window, Snake &snake) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field[i][j].setFillColor(sf::Color(80, 80, 80, 255));
        }
    }

    const Node *p = snake[0];
    field[p->y_coord][p->x_coord].setFillColor(sf::Color(0, 240, 0, 255));
    for (int i = 1; i < snake.len(); i++) {
        const Node *p = snake[i];
        field[p->y_coord][p->x_coord].setFillColor(sf::Color(255, 255, 0, 255));
    }

    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            window.draw(field[i][j]);
        }
    }
}

void CheckInput(Snake &snake) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { snake.set_next_direction('A'); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { snake.set_next_direction('D'); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { snake.set_next_direction('W'); }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { snake.set_next_direction('S'); }
    return;
}

void UpdateMovement(Snake &snake, sf::Clock &clock) {
    if (clock.getElapsedTime().asMilliseconds() >= (1000.f / snake.get_speed()) ) { 
        snake.set_direction(snake.get_next_direction());
        snake.MoveSnake();
        clock.restart();
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Snake the game");
    window.setFramerateLimit(60);

    sf::RectangleShape field[FIELD_SIZE][FIELD_SIZE];
    FillField(field);

    Snake snake(10);
    sf::Clock clock;
    
    while (window.isOpen())
    {   
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
      
        DrawField(field, window, snake);
        
        CheckInput(snake);
        
        UpdateMovement(snake, clock);

        window.display();
        
        
    }

    return 0;
}

//auto start = std::chrono::steady_clock::now();
//std::this_thread::sleep_until(start + std::chrono::seconds(1));
