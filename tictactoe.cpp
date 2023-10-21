#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define pb push_back

// positions for simplicity are represented as integers
// this function converts an integer to the corresponding position
vector<vector<int>> get_arr(int state)
{
    vector<vector<int>> arr(3, vector<int>(3));
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            arr[i][j] = state % 3;
            state /= 3;
        }
    }
    return arr;
}

// convert position to its integer representation
int convert(vector<vector<int>> &arr)
{
    int state = 0;
    for (int i = 2; i >= 0; --i)
    {
        for (int j = 2; j >= 0; --j)
        {
            state *= 3;
            state += arr[i][j];
        }
    }
    return state;
}

// function to print current position
void print_state(int state)
{

#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif

    vector<vector<int> > arr = get_arr(state);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            arr[i][j] = state % 3;
            state /= 3;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        cout << "+";
        for (int j = 0; j < 3; ++j)
            cout << "---+";
        cout << "\n|";
        for (int j = 0; j < 3; ++j)
        {
            cout << " ";
            if (arr[i][j] == 0)
                cout << " ";
            if (arr[i][j] == 1)
                cout << "X";
            if (arr[i][j] == 2)
                cout << "O";
            cout << " |";
        }
        cout << "\n";
    }
    cout << "+";
    for (int i = 0; i < 3; ++i)
        cout << "---+";
    cout << "\n";
}

// function to check who is the winner in the given position
// no one : 0, tie : -1, X : 1, O : 2
int who_wins(int state)
{
    int arr[3][3];
    int is_free = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            arr[i][j] = state % 3;
            is_free |= (arr[i][j] == 0);
            state /= 3;
        }
    }
    // rows and columns
    for (int i = 0; i < 3; ++i)
    {
        if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
            return arr[i][0];
        if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i])
            return arr[0][i];
    }
    // diagonals
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
        return arr[1][1];
    if (arr[2][0] == arr[1][1] && arr[1][1] == arr[0][2])
        return arr[1][1];
    if (!is_free)
        return -1;
    return 0;
}

int gamestate;
vector<vector<int>> board(3, vector<int>(3));
bool whose_move;

// function to make move
void make_move(int x, int y, bool who)
{
    board[x][y] = (who ? 2 : 1);
    gamestate = convert(board);
}

// minimax implementation that explores graph of game positions
// in order to find the best move in the given position
pii move_to_make;
int minimax(vector<vector<int>> arr, bool who)
{
    int res = who_wins(convert(arr));
    if (res == -1)
        return 0;
    if (res == 1)
        return -1;
    if (res == 2)
        return 1;
    int best_val = (who ? -2 : 2);
    pii best_move = {-1, -1};
    if (!who)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (arr[i][j])
                    continue;
                arr[i][j] = 1;
                int tmp = minimax(arr, !who);
                if (best_val > tmp)
                {
                    best_val = tmp;
                    best_move = {i, j};
                }
                arr[i][j] = 0;
            }
        }
    }
    else
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (arr[i][j])
                    continue;
                arr[i][j] = 2;
                int tmp = minimax(arr, !who);
                if (best_val < tmp)
                {
                    best_val = tmp;
                    best_move = {i, j};
                }
                arr[i][j] = 0;
            }
        }
        move_to_make = best_move;
    }
    return best_val;
}

// reset all variables
void new_game()
{
    gamestate = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            board[i][j] = 0;
    }
    whose_move = 0;
}

// function to handle communication with the user
void play_a_game()
{
    new_game();
    while (who_wins(gamestate) == 0)
    {
        if (!whose_move)
        {
            int row, col;
            do
            {
                print_state(gamestate);
                cout << "Your move " << (whose_move ? "O" : "X") << ": ";
                cin >> row >> col;
                --row;
                --col;
            } while (board[row][col]);
            make_move(row, col, whose_move);
        }
        else
        {
            minimax(board, whose_move);
            make_move(move_to_make.first, move_to_make.second, whose_move);
        }
        whose_move ^= 1;
    }
    print_state(gamestate);
    int winner = who_wins(gamestate);
    if (winner == -1)
        cout << "TIE!\n";
    if (winner == 1)
        cout << "X Won!\n";
    if (winner == 2)
        cout << "O Won!\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    play_a_game();
}
