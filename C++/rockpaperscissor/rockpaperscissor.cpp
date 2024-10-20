#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Player {
  // only works on c++11 and later
  public:
    int rounds_won = 0;
    int picks[3] = {0, 0, 0}; // 0 = ROCK, 1 = PAPER, 2 = SCISSOR
    void restoreRoundsWon(int rounds);
    int pick(bool random);
};

void Player::restoreRoundsWon(int rounds = 3) {
  this->rounds_won = rounds;
};

int Player::pick(bool random = false) {
  string picks[3] = {"ROCK", "PAPER", "SCISSOR"};
  string s;

  if (random) {
    int c = rand() % 3;
    this->picks[c]++;
    return c;
  }

  do {
    cout << "Pick one! (Rock, Paper, Scissor): ";
    cin >> s;

    // transform to uppercase
    for (int i = 0; i < s.length(); i++) {
      if (islower(s[i])) {
        s[i] = toupper(s[i]);
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
    int getChoice(int n, int m, string prompt);                                      // get choices from input range 1-3
    void comparePicks(int user_pick, Player& user, int computer_pick, Player& computer); // compare picks of two Players
    void startGame(Player& user, Player& computer, int rounds);                          // start game of rock paper scissors
    void run();                                           // run game

    Game(bool verbose) {
      this->verbose = verbose;
    }
};

void Game::printMenu() {
  cout << "########################" << endl;
  cout << "## ROCK PAPER SCISSOR ##" << endl;
  cout << "########################" << endl;
  cout << endl;
  cout << "-------------------------------------------------" << endl;
  cout << "- (1) Start Game, (2) Show Statistics, (3) Quit -" << endl;
  cout << "-------------------------------------------------" << endl;
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
  cout << "ROCK: " << user.picks[0] << endl;
  cout << "PAPPER: " << user.picks[1] << endl;
  cout << "SCISSOR: " << user.picks[2] << endl;
  cout << endl;

  cout << "COMPUTER PICKS HISTORY: " << endl;
  cout << "ROCK: " << computer.picks[0] << endl;
  cout << "PAPER: " << computer.picks[1] << endl;
  cout << "SCISSOR: " << computer.picks[2] << endl;
  cout << endl;
};

int Game::getChoice(int n, int m, string prompt) {
  int c;
  cout << prompt;
  do {
    cin >> c;
    if (c < n || c > m) {
      cout << "Invalid input, try again." << endl;
      cin.clear();
      cin.ignore(1000, '\n');
      if (this->verbose) {
        cout << "int c: " << c << endl;
      }
      cout << prompt;
    } 
  } while (c < n || c > m);

  return c;
}

// 0 ROCK 1 PAPER 2 SCISSOR
void Game::comparePicks(const int user_pick, Player& user, const int computer_pick, Player& computer) {
  if (user_pick == 0 && computer_pick == 2 ||
      user_pick == 1 && computer_pick == 0 ||
      user_pick == 2 && computer_pick == 1) {
    user.rounds_won++;
  } else {
    computer.rounds_won++;
  }
};

void Game::startGame(Player& user, Player& computer, int rounds = 3) {
  string picks[3] = {"Rock", "Paper", "Scissor"}; // for cleaner printing
  int user_pick;
  int computer_pick;
  int round_count = 1;

  cout << "------------------------------" << endl;
  cout << "- Starting game of " << rounds << " rounds! -" << endl;
  cout << "------------------------------" << endl;
  cout << endl;

  do {
    cout << "###########" << endl;
    cout << "# ROUND " << round_count << " #" << endl;
    cout << "###########" << endl;
    cout << endl;

    user_pick = user.pick();
    computer_pick = computer.pick(true);

    cout << "User picks: " << picks[user_pick] << "!" << endl;
    cout << "Computer picks: " << picks[computer_pick] << "!" << endl;
    cout << endl;

    if (user_pick == computer_pick) {
      cout << "Draw! Go again!" << endl;
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
  int rounds;
  Player user;
  Player computer;

  do {
    this->printMenu();
    choice = this->getChoice(1, 3, "Enter choice: ");

    if (choice == 1) {
      rounds = this->getChoice(1, 20, "Enter amount of rounds(1-20): ");
      cout << endl;
      this->startGame(user, computer, rounds);
    }

    if (choice == 2) {
      this->printStatistics(user, computer);
    }

  } while (choice != 3);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  bool verbose = false;

  if (argc > 1) {
    string v = argv[1];
    if (v == "-v") {
      cout << "verbose: true" << endl;
      verbose = true;
    }
  }

  Game Game(verbose);
  Game.run();

	return 0;
}
