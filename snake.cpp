#include <conio.h>
#include <ctime>
#include <iostream>
#include <windows.h>

struct Coords {
  int x, y, dir;
};

int main() {
  const int height = 13, weight = 24, Up = 119, Left = 97, Down = 115,
            Right = 100, Esc = 27;
  int points = 0, bufp = 0, foodX = 0, foodY = 0;
  char field[height][weight], buffield[height - 1][weight - 2];
  Coords head, tail;
  head.x = height / 2;
  head.y = weight / 2 - 1;
  tail.x = head.x;
  tail.y = head.y;
  head.dir = Right;
  tail.dir = Right;
  srand(time(NULL));
  for (int i = 0; i < height - 1; i++) {
    for (int j = 0; j < weight - 2; j++)
      buffield[i][j] = ' ';
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < weight; j++) {
      if ((i == 0 && j != weight - 1) || (i == height - 1 && j != weight - 1) ||
          j == 0 || j == weight - 2)
        field[i][j] = char(219);
      else if (i == height - 1 && j == weight - 1)
        field[i][j] = '\0';
      else if (j == weight - 1)
        field[i][j] = '\n';
      else
        field[i][j] = ' ';
    }
  }
  field[head.x][head.y] = char(254);
  foodX = 1 + rand() % (height - 2);
  foodY = 1 + rand() % (weight - 3);
  field[foodX][foodY] = '*';
  std::cout << "Use WASD to move, Esc to exit\nYour score : " << points
            << std::endl
            << *field;
  while (head.dir != Esc) {
    head.dir = getch();
    buffield[head.x][head.y] = head.dir;
    while (!kbhit()) {
      Sleep(300);
      switch (head.dir) {
      case Right:
        head.y++;
        break;
      case Left:
        head.y--;
        break;
      case Down:
        head.x++;
        break;
      case Up:
        head.x--;
      }
      if (field[head.x][head.y] == '*')
        points++;
      if (field[head.x][head.y] == char(219) ||
          field[head.x][head.y] == char(254)) {
        head.dir = Esc;
        break;
      }
      field[head.x][head.y] = char(254);
      if (points == bufp) {
        field[tail.x][tail.y] = ' ';
        if (buffield[tail.x][tail.y] != ' ') {
          tail.dir = buffield[tail.x][tail.y];
          buffield[tail.x][tail.y] = ' ';
        }
        switch (tail.dir) {
        case Right:
          tail.y++;
          break;
        case Left:
          tail.y--;
          break;
        case Down:
          tail.x++;
          break;
        case Up:
          tail.x--;
        }
      } else {
        do {
          foodX = (1 + rand() % (height - 2));
          foodY = (1 + rand() % (weight - 3));
        } while (field[foodX][foodY] == char(254));
        field[foodX][foodY] = '*';
      }
      system("cls");
      std::cout << "Use WASD to move, Esc to exit\nYour score : " << points
                << std::endl
                << *field;
      bufp = points;
    }
  }
  system("cls");
  std::cout << "\tGAME OVER\nYour finale score = " << points << std::endl;
  system("pause");
}
