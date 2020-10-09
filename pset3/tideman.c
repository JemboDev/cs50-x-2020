// https://cs50.harvard.edu/x/2020/psets/3/tideman/
// Program that runs a Tideman election (30.04.20)

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool is_cycle(int winner, int loser, int pair_rank);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Placeholders for p1 and p2 strength and temp var for sorting
    int pair1_str, pair2_str;
    pair pair_temp;

    // Bubble sorting pairs (fuck merge, mb later)
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            pair1_str = preferences[pairs[j].winner][pairs[j].loser];
            pair2_str = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            if (pair1_str < pair2_str)
            {
                pair_temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = pair_temp;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner, loser = pairs[i].loser;

        // Checking for cycle creation
        if (!is_cycle(winner, loser, i))
        {
            locked[winner][loser] = true;
        }
    }
}

// Recursively finding if there is a cycle if we lock a pair
bool is_cycle(int winner, int loser, int pair_rank)
{
    if (pair_rank < 0)
    {
        return false;
    }

    // Checking for A->B if there's B->...->A
    for (int i = 0; i < pair_rank; i++)
    {
        if (pairs[i].winner == loser && locked[pairs[i].winner][pairs[i].loser])
        {
            if (pairs[i].loser == winner)
            {
                return true;
            }
            else
            {
                return is_cycle(pairs[i].loser, loser, pair_rank - 1);
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool loser[candidate_count];

    // Marking pointed candidates as losers
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                loser[j] = true;
            }
        }
    }

    // Looking for graph source
    for (int i = 0; i < candidate_count; i++)
    {
        if (!loser[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
}