#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

using namespace std;


void setColor(const string& color) 
{
    cout << color;
}

// Define some common colors
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";


// Utility function to trim spaces
/*
Delete Any Space Founed In The String
*/


string manualTrim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    // Finding the first is space ( ) = string::npos
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// First LinkedList
// for : 
// Player Node Class
class PlayerNode {
public:
    int id; // Number Of Everyplayer  Shenawy #1 ..
    string name;
    string position;
    string salary;
    int age;
    PlayerNode* next; // To Move for Everyplayer
    // Empty Constructor 
     //PlayerNode(){}
    // Basic Counstructor 
    PlayerNode(int p_id, string p_name, string p_position, string p_salary, int p_age) {
        id = p_id;
        name = p_name;
        position = p_position;
        salary = p_salary;
        age = p_age;
        next = nullptr;
    }
};
// Second Linkedlist
// for :
// Team Node Class
class TeamNode {
private:
    int id;
    string name;
    string owner;
    PlayerNode* playerList;
    TeamNode* next;

public:
    TeamNode(int t_id, string t_name, string t_owner) {
        id = t_id;
        name = t_name;
        owner = t_owner;
        playerList = nullptr;
        next = nullptr;
    }
    // Getters 
    PlayerNode* getPlayerList() const 
    { 
        return playerList; 
    }
    int getID() const
    { 
        return id;
    }
    string getName() const 
    { 
        return name;
    }
    string getOwner() const 
    { 
        return owner;
    }
    TeamNode* getNext() const {
        return next;
    }

    // Setters
    void setPlayerList(PlayerNode* newPlayerList) { playerList = newPlayerList; }
    void setNext(TeamNode* nextNode) { next = nextNode; }
    void setName(const string& newName) { name = newName; }
    void setOwner(const string& newOwner) { owner = newOwner; }

    // Functions : 
    // توضيح بسيط : احنا شغالين بفكرة الكونستراكتور لتوفير الوقت و المجهود الكبير لو شغال على كل داتا لوحدها 

    void addPlayer(int p_id, string p_name, string p_position, string p_salary, int p_age) {
        PlayerNode* newPlayer = new PlayerNode(p_id, p_name, p_position, p_salary, p_age);
        if (!playerList) {
            playerList = newPlayer;
        }
        else {
            PlayerNode* temp = playerList;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newPlayer;
        }
    }

     //Function to remove a player by ID عشان موضحش يتمسح ب اني طريقة

    void removePlayer(int playerID) {
        PlayerNode* temp = playerList;
        PlayerNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->id == playerID) {
                if (prev == nullptr) {  // Player is the first one
                    playerList = temp->next;
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
                cout << "Player with ID " << playerID << " removed." << endl;
                cout << "His Name is " << temp->name << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Player with ID " << playerID << " not found." << endl;
    }
};


// Global vector to hold all teams (pointers) using STLS

vector<TeamNode*> teams;

// Egyptian League Class
class EgyptianLeague {
private:
    TeamNode* selectedTeam; // we will use it in adding to any team or removing from any team ( using any selected team )

public:
    EgyptianLeague()
    {
        selectedTeam = nullptr;
    }

    // Load Players form file

// Function to load players from a team-specific file
    // using library fstream

    void loadPlayersFromFile(TeamNode* team, const string& fileName) {
        ifstream file(fileName);
        if (!file) // if the file not exist 
        {
            cout << "Error: Unable to open file " << fileName << "!" << endl;
            return;
        }
         //else

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue; // Skip empty lines == Law feh lines fadya

            // Check if the line starts with a number (player ID) == Number of player
            /*
            The stringstream class in C++ is a versatile tool for handling strings as streams. It is part of the <sstream> header
            and is used for both input and output operations on strings.
            This class is particularly useful for tasks such as string manipulation, parsing, and type conversion.
            */
            stringstream ss(line);
            string idStr;
            getline(ss, idStr, ',');

            // If the first part of the line is not a valid integer, skip the line
            try
            {
                // stoi == String TO Integer
                int id = stoi(idStr); // Try to convert the id to an integer
            }
            catch (const std::invalid_argument& e) {
                // If it fails, it's not a valid player line, so skip it
                continue;
            }

            // Parse the rest of the player details == getting the extra informations 
            // We Separte the informations with ',' comma --> 1,Mohab,Goalkeeper,20,1m

            string name, position, ageStr, salaryStr;
            getline(ss, name, ',');
            getline(ss, position, ',');
            getline(ss, ageStr, ',');
            getline(ss, salaryStr, ',');

            try
            {
                // Convert strings to appropriate types
                // The std::stoi function in C++ converts a string to an integer -> tb3 #include String
                int age = stoi(ageStr);

                // Parse and adjust the salary field
                salaryStr = manualTrim(salaryStr); // if i found anyspace the func that we have made in first
                // The std::stod function in C++ converts a string to an double -> tb3 #include String
                double salary = stod(salaryStr);
                if (salary < 10)
                {
                    salary *= 1'000'000; // Assume it's in millions
                }
                else
                {
                    salary *= 1000; // Assume it's in thousands
                }

                // Format salary to display in millions with 2 decimal places
                stringstream formattedSalary;
                // tb3 library #include iomanip
                // To Display The Salary in 2m or 0.05m

                formattedSalary << fixed << setprecision(2) << salary / 1'000'000;

                // Add the player to the team
                team->addPlayer(stoi(idStr), name, position, formattedSalary.str(), age);
            }
            catch (const std::exception& e) // Throw Exception If Any Error Happen To Handle it 
            {
                cout << "Error: Invalid data format in file for player line: " << line << endl;
                cout << "Exception: " << e.what() << endl;
            }
        }

        file.close();
        cout << "Players loaded successfully for team: " << team->getName() << endl; // here we used getters & setters
    }

    // Function to add a new player to a selected team
    void addPlayerToSelectedTeam() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        int p_id, p_age;
        string p_name, p_position, p_salary;

        cout << "Enter Player ID: ";
        cin >> p_id;
        cin.ignore();  // Ignore the newline after reading integer
        cout << "Enter Player Name: ";
        getline(cin, p_name);
        cout << "Enter Player Position: ";
        getline(cin, p_position);
        cout << "Enter Player Salary (e.g., 1m for millions, 100k for thousands): ";
        getline(cin, p_salary);
        cout << "Enter Player Age: ";
        cin >> p_age;

        selectedTeam->addPlayer(p_id, p_name, p_position, p_salary, p_age);
        cout << "Player added to " << selectedTeam->getName() << endl;
    }

    // Function to remove a player by player ID عشان محددش اللاعب يتمسح ازاي

    void removePlayerFromSelectedTeam() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        int playerId;
        cout << "Enter Player ID to remove: ";
        cin >> playerId;

        PlayerNode* prev = nullptr;
        PlayerNode* current = selectedTeam->getPlayerList(); // Note : Player List Contain all thing about the player

        while (current) // Not Equal Null
        {
            if (current->id == playerId) 
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else 
                {
                    // If the player to be removed is the head of the list
                    selectedTeam->setPlayerList(current->next);
                }

                delete current;  // Free the memory for the removed player
                cout << "Player with ID " << playerId << " removed." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Player with ID " << playerId << " not found." << endl;
    }
    // Function to display data of a player by player ID
    void displayPlayerData() 
    {
        if (!selectedTeam)
        {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        int playerId;
        cout << "Enter Player ID to display: ";
        cin >> playerId;

        PlayerNode* current = selectedTeam->getPlayerList();
        while (current) 
        {
            if (current->id == playerId) {
                cout << "Player ID : " << current->id << endl;
                cout << "Name : " << current->name << endl;
                cout << "Position : " << current->position << endl;
                cout << "Salary : " << current->salary << endl;
                cout << "Age : " << current->age << endl;
                return;
            }
            current = current->next;
        }
        // Else
        cout << "Player with ID " << playerId << " not found." << endl;
    }
    // Function to search for a team by name
    void searchTeamByName()
    {
        string teamName;
        cout << "Enter Team Name to search : ";
        cin.ignore(); // Ignore any leftover newline character
        getline(cin, teamName);
        // Iterator to move on all the vector teams to find the team that we want
        for (auto& team : teams) 
        {
            if (team->getName() == teamName) {
                cout << "Team found!" << endl;
                cout << "Team ID: " << team->getID() << endl;
                cout << "Team Name: " << team->getName() << endl;
                cout << "Team Owner: " << team->getOwner() << endl;
                return;
            }
        }

        cout << "Team with name '" << teamName << "' not found." << endl;
    }
    // Function to update team information (name and owner)
    void updateTeamInformation() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        string newName, newOwner;
        cout << "Enter new Team Name: ";
        cin.ignore();
        getline(cin, newName);
        cout << "Enter new Team Owner: ";
        getline(cin, newOwner);

        selectedTeam->setName(newName);   //  we used setter function for name
        selectedTeam->setOwner(newOwner); //  we used setter function for owner

        cout << "Team information updated successfully!" << endl;
    }


    // Load teams from file
    // Same As Load Players From File

    void loadTeamsFromFile()
    {
        ifstream file("teams.txt");
        if (!file) {
            cout << "Error: File not found!" << endl;
            return;
        }

        string line, name, owner;
        int id;
        while (getline(file, line))
        {
            // We use manualTrim ( + 1 ) to get anything after the coloum : 
            if (line.empty()) continue;

            if (line.find("Team name") != string::npos)
            {
                // To Remove anyspaces

                name = manualTrim(line.substr(line.find(":") + 1));
            }
            else if (line.find("Team id") != string::npos)
            {
                id = stoi(line.substr(line.find(":") + 1));
            }
            else if (line.find("Team Owner") != string::npos) {
                owner = manualTrim(line.substr(line.find(":") + 1));

                // Add team
                TeamNode* newTeam = new TeamNode(id, name, owner);
                teams.push_back(newTeam);

                // Load players for this team (assuming filenames are like "teamname.txt") == Al ahly .txt

                string fileName = name + ".txt"; // Create filename dynamically
                loadPlayersFromFile(newTeam, fileName);
                // Linked Between Teams And Players Using Vectors "" STLS ""
            }
        }
        file.close();
        cout << "Teams and players loaded successfully!" << endl;
    }


    // Add a new team
    void addTeam(int id, string name, string owner) {
        TeamNode* newTeam = new TeamNode(id, name, owner);
        teams.push_back(newTeam);
        cout << "Team added successfully!" << endl;
    }

    // Display all teams
    void displayTeams() {
        if (teams.empty()) {
            cout << "No teams available." << endl;
            return;
        }

        cout << "Teams List:" << endl;
        for (const auto& team : teams) {
            cout << "  Ranking : " << team->getID() << " -- "
                << " Name : " << team->getName() << " -- "
                << " Coach : " << team->getOwner() << endl;
            cout << endl;
        }
        cout << endl;
    }

    // Display players of the selected team
    void displaySelectedTeamPlayers() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        cout << "Team Name: " << selectedTeam->getName() << endl;
        cout << "Players:" << endl;

        if (!selectedTeam->getPlayerList()) {
            cout << "  No players in this team." << endl;
            return;
        }

        PlayerNode* player = selectedTeam->getPlayerList();
        while (player) {
            cout << "  Player Number : " << player->id << " "
                << " , Name : " << player->name << " "
                << " , Position : " << player->position << " "
                << " , Salary : " << player->salary << " "
                << " , Age : " << player->age << endl;
            player = player->next;
        }
    }

    // Select a team by ID
    void selectTeamById(int id)
    {
        for (const auto& team : teams) {
            if (team->getID() == id) {
                selectedTeam = team;
                cout << "Selected Team: " << team->getName() << " (ID: " << team->getID() << ")" << endl;
                displaySelectedTeamPlayers();
                return;
            }
        }
        cout << "Team with ID " << id << " not found." << endl;
        selectedTeam = nullptr;
    }

    // Destructor to free all teams from Memory
    ~EgyptianLeague() {
        for (auto team : teams) // Iterator 34an y3dy 3 kol el teams
        {
            delete team;
        }
        teams.clear();
    }
};

// Main Function
int main() {
    EgyptianLeague league;

    int choice;
    do {
        // Clear the screen (use "cls" for Windows)
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // Display the menu with colors
        setColor(CYAN);
        cout << "\n" << string(40, '=') << endl;
        cout << "     === Egyptian League Management System ===            " << endl;
        cout << string(40, '=') << RESET << endl;

        setColor(YELLOW);
        cout << "1. Load teams from file" << endl;
        cout << "2. Add a new team" << endl;
        cout << "3. Display all teams" << endl;
        cout << "4. Select a team by ID" << endl;
        cout << "5. Exit" << endl;
        cout << "6. Load players from file" << endl;
        cout << "7. Add a new player to selected team" << endl;
        cout << "8. Remove a player from selected team" << endl;
        cout << "9. Display player data" << endl;
        cout << "10. Search for a team by name" << endl;
        cout << "11. Update team information" << endl;
        setColor(RESET);

        setColor(GREEN);
        cout << "Enter your choice: ";
        cin >> choice;
        setColor(RESET);

        switch (choice) {
        case 1:
            setColor(BLUE);
            cout << "Loading teams from file..." << RESET << endl;
            league.loadTeamsFromFile();
            break;
        case 2: {
            int id;
            string name, owner;
            setColor(BLUE);
            cout << "Enter Team ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Team Name: ";
            getline(cin, name);
            cout << "Enter Team Owner: ";
            getline(cin, owner);
            league.addTeam(id, name, owner);
            setColor(GREEN);
            cout << "Team added successfully!" << RESET << endl;
            break;
        }
        case 3:
            setColor(BLUE);
            cout << "Displaying all teams..." << RESET << endl;
            league.displayTeams();
            break;
        case 4: {
            int id;
            setColor(BLUE);
            cout << "Enter Team ID to select: ";
            cin >> id;
            league.selectTeamById(id);
            break;
        }
        case 5:
            setColor(RED);
            cout << "Exiting... Goodbye!" << RESET << endl;
            break;
        case 6: {
            int teamId;
            setColor(BLUE);
            cout << "Enter Team ID to load players: ";
            cin >> teamId;
            TeamNode* team = nullptr;
            for (auto& t : teams)
            {
                if (t->getID() == teamId)
                {
                    team = t;
                    break;
                }
            }
            if (team) {
                league.loadPlayersFromFile(team, team->getName() + ".txt");
            }
            else 
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 7:
            league.addPlayerToSelectedTeam();
            break;
        case 8:
            league.removePlayerFromSelectedTeam();
            break;
        case 9:
            league.displayPlayerData();
            break;
        case 10:
            league.searchTeamByName();
            break;
        case 11:
            league.updateTeamInformation();
            break;
        default:
            setColor(RED);
            cout << "Invalid choice! Please try again." << RESET << endl;
        }

        // Pause for the user to read output
        setColor(YELLOW);
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        setColor(RESET);

    } while (choice != 5);

    return 0;
}