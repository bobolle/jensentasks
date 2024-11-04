#include <iostream>
#include <random>

using namespace std;

const string rpsMoves[3] = {"Rock", "Paper", "Scissors"};

class Player {
  public:
    int score = 0;
    int move;
    int pick(int random);
};

int Player::pick(int random = false) {
  int move;

  if (random) {
    return rand() % 3;
  }

  do {
    cout << "Rock (0), Paper (1) or Scissors (2)?\n";
    cin >> move;
    if (!cin >> move) {
      cout << " error " << endl;
    }
    cin.clear();
    cin.ignore(10000, '\n');
  } while (move < 0 || move > 2);

  return move;
}

class Game {
  private:
    int player_total = 0;
    int pc_total = 0;
    int moves_counter[3] = {0,0,0};

  public:
    void print_statistics();
    void startGame();
    void menu();
    void comparePicks();
};

void Game::print_statistics() {
  
}

void Game::startGame() {
  Player user;
  Player computer;

  while (user.score < 3 && computer.score << 3) {
    user.pick();
    computer.pick(true);

    cout << "Player: " << rpsMoves[user.move] << "\n";
    cout << "Computer: " << rpsMoves[computer.move] << "\n";

    this->player_total++;
    this->pc_total++;

    moves_counter[user.move];
    moves_counter[computer.move];

    if (user.move == computer.move) {
      cout << "It's a tie!\n";
    }
  }

}

void Game::menu() {
  int menu_answ;

  while (1) {
    cout << "------------------------------" << endl;
    cout << "\nWELCOME TO ROCK PAPER SCISSOR!" << endl;
    cout << "------------------------------" << endl;
    cout << "NEW GAME (1)" << endl;
    cout << "SHOW STATISTICS (2)" << endl;
    cout << "QUIT (3)" << endl;
    cout << "------------------------------" << endl;

    cout << "What do you want to do?" << endl;
    cin >> menu_answ;
    switch (menu_answ)
    {
      case 1:
        Game::startGame();
        break;

      case 2:
        Game::print_statistics();
        break;

      case 3:
          cout << "Thank you for playing!" << endl;
          exit(0);

      default:
          cin.clear();
          cin.ignore(10000, '\n');
          cout << "Try again!" << endl;
    }
  }
}

void Game::comparePicks() {}



int main() {
  srand(time(0));
  Game game;
  game.menu();

  return 0;
}
