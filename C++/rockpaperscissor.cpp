#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Player {
  // only works on c++11 and later
  public:
    int rounds_won = 0;
    int picks[3] = {0, 0, 0}; // 0 = sten, 1 = sax, 2 = påse
    void restoreRoundsWon(int rounds);
    int pick(bool random);
};

void Player::restoreRoundsWon(int rounds = 3) {
  this->rounds_won = rounds;
};

int Player::pick(bool random = false) {
  string picks[3] = {"sten", "sax", "påse"};
  string s;

  if (random) {
    int c = rand() % 3;
    this->picks[c]++;
    return c;
  }

  do {
    cout << "Välj! (Sten, Sax, Påse): ";
    cin >> s;

    // transform to lowercase
    for (int i = 0; i < s.length(); i++) {
      if (isupper(s[i])) {
        s[i] = tolower(s[i]);
      }
    }

    // check if available choice
    for (int i = 0; i < 3; i++) {
      if (s == picks[i]) {
        this->picks[i]++;
        return i;
      }
    }

  } while (1);
};

class Game {
  // only works on c++11 and later
  public:
    bool verbose = false;                                 // enable/disable simple verbose mode
    void printMenu();                                     // print out the menu
    void printScore(Player& user, Player& computer);      // print out rounds won between two Players
    void printStatistics(Player& user, Player& computer); // print out statistics from current session
    int getChoice();                                      // get choices from input range 1-3
    void comparePicks(int user_pick, Player& user, int computer_pick, Player& computer); // compare picks of two Players
    void startGame(Player& user, Player& computer, int rounds);                          // start game of rock paper scissors
    void run();                                           // run game

    Game(bool verbose) {
      this->verbose = verbose;
    }
};

void Game::printMenu() {
  cout << "###################" << endl;
  cout << "## STEN SAX PÅSE ##" << endl;
  cout << "###################" << endl;
  cout << endl;
  cout << "Välj ett alternativ: " << endl;
  cout << "(1) Starta spel, (2) Visa statistik, (3) Avsluta" << endl;
  cout << "------------------------------------------------" << endl;
  cout << endl;
}

void Game::printScore(Player& user, Player& computer) {
  cout << "User total rounds won: " << user.rounds_won << endl;
  cout << "Computer total rounds won: " << computer.rounds_won << endl;
  cout << endl;
};

void Game::printStatistics(Player& user, Player& computer) {
  cout << "################" << endl;
  cout << "## STATISTICS ##" << endl;
  cout << "################" << endl;
  cout << endl;

  cout << "USER PICKS HISTORY: " << endl;
  cout << "STEN: " << user.picks[0] << endl;
  cout << "SAX: " << user.picks[1] << endl;
  cout << "PÅSE: " << user.picks[2] << endl;
  cout << endl;

  cout << "COMPUTER PICKS HISTORY: " << endl;
  cout << "STEN: " << computer.picks[0] << endl;
  cout << "SAX: " << computer.picks[1] << endl;
  cout << "PÅSE: " << computer.picks[2] << endl;
  cout << endl;
};

int Game::getChoice() {
  int c;
  do {
    cin >> c;
    if (c < 1 || c > 3) {
      cout << "Ogiltligt val, försök igen." << endl;
      cin.clear();
      cin.ignore(1000, '\n');
      if (this->verbose) {
        cout << "int c: " << c << endl;
      }
      this->printMenu();
    } 
  } while (c < 1 || c > 3);

  return c;
}

void Game::comparePicks(int user_pick, Player& user, int computer_pick, Player& computer) {
  if (user_pick == 0 && computer_pick == 1 ||
      user_pick == 1 && computer_pick == 2 ||
      user_pick == 2 && computer_pick == 0) {
    user.rounds_won++;
  } else {
    computer.rounds_won++;
  }
};

void Game::startGame(Player& user, Player& computer, int rounds = 3) {
  string picks[3] = {"Sten", "Sax", "Påse"}; // for cleaner printing
  int user_pick;
  int computer_pick;
  int round_count = 1;

  do {
    cout << "##########" << endl;
    cout << "# ROUND " << round_count << "#" << endl;
    cout << "##########" << endl;
    cout << endl;

    user_pick = user.pick();
    computer_pick = computer.pick(true);

    cout << "User pick: " << picks[user_pick] << endl;
    cout << "Computer pick: " << picks[computer_pick] << endl;
    cout << endl;

    if (user_pick == computer_pick) {
      cout << "Lika! Kör igen!" << endl;
      if (this->verbose) {
        cout << "user_pick: " << user_pick << ", computer_pick: " << computer_pick << endl;
      }
      continue;
    } else {
      this->comparePicks(user_pick, user, computer_pick, computer);
    }

    this->printScore(user, computer);

    round_count++;
  } while (round_count <= rounds);
}

void Game::run() {
  int choice;
  Player user;
  Player computer;

  do {
    this->printMenu();
    choice = this->getChoice();

    if (choice == 1) {
      this->startGame(user, computer);
    }

    if (choice == 2) {
      this->printStatistics(user, computer);
    }

  } while (choice != 3);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  bool verbose = false;

  if (argc > 1 && argv[1][1] == 'v') {
    verbose = true;
  }

  Game Game(verbose);
  Game.run();

	return 0;
}
