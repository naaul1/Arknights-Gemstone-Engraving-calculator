#include <iostream>
#include <iomanip>

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <unordered_map>
#include <functional>

using std::string;
using std::vector;
using std::cout;
using std::cin;

using IntVec = vector<int>;




//
// Line 40: class GemstoneCalculator {}
//
// Line 250: class CommandSystem {}
//
// Line 400: int main {} 
//
//














class GemstoneCalculator {
public:
    enum Type {
        Red,
        Teal,
        Purple,
        Gold,
        TypeCount
    };
    
    struct CellInfo {
        Type m_type{Red};
        int m_tier{0};
        int m_value{};
        
        CellInfo(Type type, int tier, int value) 
                : m_type(type), m_tier(tier), m_value(value) {}
    };


    




    vector<IntVec> m_gem_count;
    vector<IntVec> m_gem_score;
    vector<IntVec> m_card_level;

    //
    long long m_cummulated_score{0};
    long long m_last_score{0};
    int m_workbenches{2};
    
    int m_used_workbenches{0};
    int m_bonus_per_empty_workbenches{0};






private:
    vector<CellInfo> getAvailablesFromTable(vector<IntVec> table) const {
        vector<CellInfo> availables{};
        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table[0].size(); j++) {
                int value = table[i][j];
                if (value != 0) {
                    CellInfo cell{static_cast<Type>(i), j, value};
                    availables.push_back(cell);
                }
            }
        }
        return availables;
    }
    
    
    string typeToString(int type) const {
        switch (type) {
            case Red:    return "Red";
            case Purple: return "Purp";
            case Teal:   return "Teal";
            case Gold:   return "Gold";
            default:     return "";
        }
    }
    
    
    string typeToLabel(int type) const {
        switch (type) {
            case Red:   return "r";
            case Purple:return "p";
            case Teal:  return "t";
            case Gold:  return "g";
            default:    return "";
        }
    }


    //
    //
    void r1() {
        int level = m_card_level[Red][0];
        if (level < 1 || level > 3) {
            return;
        } 
        
        int converts = m_gem_count[Red][0];
        m_gem_count[Red][0] = 0;
        switch (level) {
        case 3: converts *= 2;
        case 2: // auto activate
        case 1: break;
        }
        
        m_gem_count[Red][1] += converts;
    }
    
    
    void r2() {
        int level = m_card_level[Red][1];
        if (level < 1 || level > 3) {
            return;
        } 
        
        int converts = m_gem_count[Red][1];
        m_gem_count[Red][1] = 0;
        switch (level) {
        case 3: // auto activate
        case 2: converts *= 2;
        case 1: break;
        }
        
        m_gem_count[Red][2] += converts;
    }
    
    
    void r3() {
        int level = m_card_level[Red][2];
        if (level < 1 || level > 3) {
            return;
        } 
        
        int converts = m_gem_count[Red][2];
        m_gem_count[Red][2] = 0;
        switch (level) {
        case 3: // auto activate
        case 2: converts *= 2.4;
        case 1: break;
        }
        
        m_gem_count[Red][3] += converts;
    }
    
    
    void r4() {
        int level = m_card_level[Red][3];
        if (level < 1 || level > 3) {
            return;
        }
        
        int converts = m_gem_count[Red][3];
        m_gem_count[Red][3] = 0;
        switch (level) {
        case 3: m_bonus_per_empty_workbenches = 5000; break;
        case 2: m_bonus_per_empty_workbenches = 1500; break;
        case 1: break;
        }
        
        m_gem_count[Red][4] += converts;
    }
    
    
    void t1() {
        int level = m_card_level[Teal][0];
        if (level < 1 || level > 3) {
            return;
        }
        
        int converts = m_gem_count[Teal][0];
        m_gem_count[Teal][0] = 0;
        switch (level) {
        case 3: 
            m_gem_count[Teal][1] += converts;
            m_gem_count[Gold][0] += converts;
            break;
        case 2:
            m_gem_count[Teal][1] += std::ceil(converts * 4 / 5.0);
            m_gem_count[Gold][0] += std::floor(converts / 5.0);
            break;
        case 1: 
            
            break;
            m_gem_count[Teal][1] += std::ceil(converts / 2.0);
            m_gem_count[Gold][0] += std::floor(converts / 2.0);
        }
    }
    
    
    void t2() {
        int level = m_card_level[Teal][1];
        if (level < 1 || level > 3) {
            return;
        }
        
        int converts = m_gem_count[Teal][1];
        m_gem_count[Teal][1] = 0;
        switch (level) {
        case 3: 
            m_gem_count[Teal][2] += std::ceil(converts * 4 / 5.0);
            m_gem_count[Gold][0] += std::floor(converts * 6 / 5.0);
            break;
        case 2:
            m_gem_count[Teal][2] += std::ceil(converts * 3 / 5.0);
            m_gem_count[Gold][0] += std::floor(converts * 2 / 5.0);
            break;
        case 1: 
            
            m_gem_count[Teal][2] += std::ceil(converts * 2 / 5.0);
            m_gem_count[Gold][0] += std::floor(converts *3 / 5.0);
            break;
        }
    }
    
    
    void t3() {
        int level = m_card_level[Teal][2];
        if (level < 1 || level > 3) {
            return;
        }
        
        int converts = m_gem_count[Teal][2];
        m_gem_count[Teal][2] = 0;
        switch (level) {
        case 3: 
            m_gem_count[Teal][3] += std::ceil(converts * 7 / 10.0);
            m_gem_count[Gold][0] += std::floor(converts * 13 / 10.0);
            break;
        case 2:
            m_gem_count[Teal][3] += std::ceil(converts / 2.0);
            m_gem_count[Gold][0] += std::floor(converts / 2.0);
            break;
        case 1: 
            m_gem_count[Teal][3] += std::ceil(converts * 3 / 10.0);
            m_gem_count[Gold][0] += std::floor(converts * 7 / 10.0);
            break;
        }
    }
    
    
    void p1() {
        int level = m_card_level[Purple][0];
        if (level < 1 || level > 3) {
            return;
        }
        
        int& purples = m_gem_count[Purple][0];
        int& golds = m_gem_count[Gold][0];
        int converts{0};
        
        switch (level) {
        case 3: 
            for (auto& purple_score : m_gem_score[Purple]) {
                purple_score += 5;
            }
        case 2:
            if (purples > 0 && golds > 0) {
                converts = std::ceil((purples + golds) / 2.0);
                purples = 0; 
                golds = 0;
                break;
            }
        case 1: 
            converts += purples < golds ? purples : golds;
            purples -= converts;
            golds -= converts;
        }
        m_gem_count[Purple][1] += converts;
    }
    
    
    void p2() {
        int level = m_card_level[Purple][1];
        if (level < 1 || level > 3) {
            return;
        }
        
        int& purples = m_gem_count[Purple][1];
        int& teals = m_gem_count[Teal][1];
        int converts{0};
        
        switch (level) {
        case 3: 
            if (purples > 0 && teals > 0) {
                converts = std::ceil((purples + teals) / 2.0);
                purples = 0; 
                teals = 0;
            }
        case 2: 
            for (auto& purple_score : m_gem_score[Purple]) {
                purple_score += 15;
            }
        case 1: 
            converts += purples < teals ? purples : teals;
            purples -= converts;
            teals -= converts;
        }
        m_gem_count[Purple][2] += converts;
    }
    
    
    void p3() {
        int level = m_card_level[Purple][2];
        if (level < 1 || level > 3) {
            return;
        }
        
        int& purples = m_gem_count[Purple][2];
        int& reds = m_gem_count[Red][3];
        int converts{0};
        
        switch (level) {
        case 3: 
            if (getAvailablesFromTable(m_gem_count).size() == 1) {
                m_gem_score[Purple][3] += 100;
            }
        case 2: 
            if (purples > 0 && reds > 0) {
                converts = std::ceil((purples + reds) / 2.0);
                purples = 0; 
                reds = 0;
                break;
            }
        case 1: 
            converts += purples < reds ? purples : reds;
            purples -= converts;
            reds -= converts;
        }
        m_gem_count[Purple][2] += converts;
    }
    
    
    void g1() {
        int level = m_card_level[Gold][0];
        if (level < 1 || level > 3) {
            return;
        }
        
        int& golds = m_gem_count[Gold][0];
        switch (level) {
        case 3: golds *= 5; break;
        case 2: golds *= 3; break;
        case 1: golds *= 2; break;
        }
    }
    
    void g2() {
        int level = m_card_level[Gold][1];
        if (level < 1 || level > 3) {
            return;
        }
        
        int& golds = m_gem_count[Gold][0];
        switch (level) {
        case 3: golds *= 8; break;
        case 2: golds *= 5; break;
        case 1: golds *= 3; break;
        }
    }
    
    
    void g3() {
        int level = m_card_level[Gold][2];
        if (level < 1 || level > 3) {
            return;
        }
        
        int& golds = m_gem_count[Gold][0];
        switch (level) {
        case 3: m_gem_score[Gold][0] += 1;
        case 2: golds *= 9; break;
        case 1: golds *= 5; break;
        }
    }
    
    
    
    

public:
    GemstoneCalculator() : m_gem_count(TypeCount), m_gem_score(TypeCount), m_card_level(TypeCount) {
        // init m_gem_count
        m_gem_count[Red] = {0, 0, 0, 0, 0};
        m_gem_count[Teal] = {0, 0, 0, 0};
        m_gem_count[Purple] = {0, 0, 0, 0};
        m_gem_count[Gold] = {0};
        
        // init m_gem_score
        m_gem_score[Red] = {1, 2, 10, 35, 85};
        m_gem_score[Teal] = {1, 5, 50, 500};
        m_gem_score[Purple] = {1, 3, 22, 105};
        m_gem_score[Gold] = {1};
        
        // init m_card_level
        m_card_level[Red] = {1, 0, 0, 0};
        m_card_level[Teal] = {0, 0, 0};
        m_card_level[Purple] = {0, 0, 0};
        m_card_level[Gold] = {0, 0, 0};
    }


    void resetIntVec(IntVec& row) {
        std::fill(row.begin(), row.end(), 0);
    }
    
    
    void resetIntTable(vector<IntVec>& table) {
        for (auto& row : table) {
            resetIntVec(row);
        }
    }
    
    
    void resetScoreTable() {
        m_gem_score[Red] = {1, 2, 10, 35, 85};
        m_gem_score[Teal] = {1, 5, 50, 500};
        m_gem_score[Purple] = {1, 3, 22, 105};
        m_gem_score[Gold] = {1};
    }


    void beginRun() {
        resetIntTable(m_gem_count);
        m_cummulated_score = 0;
        m_last_score = 0;
        m_workbenches = 6;

        cout << "=== NEW RUN ===\n";
        printBasicInfo();
    }


    void beginRound(const IntVec& inputs) {
        resetIntTable(m_gem_count);
        m_last_score = 0;

        setT0Gems(inputs);

        cout << "=== NEW ROUND ===\n";
        printGems();
        printBasicInfo();
    }
    
    
    
    
    
    

    void setT0Gems(const IntVec& inputs) {
        for (int i = 0; i < TypeCount && i < inputs.size(); i++) {
            if (!m_gem_count[i].empty()) {
                m_gem_count[i][0] = inputs[i];
            }
        }
    }
    
    IntVec getT0Gems() {
        IntVec t0gems(TypeCount);
        for (int i = 0; i < TypeCount; i++) {
            t0gems[i] = m_gem_count[i][0];
        }
        return t0gems;
    }
    
    
    

    
    
    void activateCard(string card_label) {
        if (card_label.size() != 2) {
            cout << "Invalid parameter (must be 2char long, eg. r1): " << card_label << '\n';
            return;
        }
        
        // using ascii
        int card_code{};
        switch (card_label[0]) {
        case 'r': card_code = 0; break;
        case 't': card_code = 10; break;
        case 'p': card_code = 20; break;
        case 'g': card_code = 30; break;
        }
        card_code += card_label[1] - '0';
        
        switch(card_code) {
        case 1: r1(); break;
        case 2: r2(); break;
        case 3: r3(); break;
        case 4: r4(); break;
        
        case 11: t1(); break;
        case 12: t2(); break;
        case 13: t3(); break;
        
        case 21: p1(); break;
        case 22: p2(); break;
        case 23: p3(); break;
        
        case 31: g1(); break;
        case 32: g2(); break;
        case 33: g3(); break;
        
        default: 
            cout << "Unknown parameter: " << card_label << '\n';
        }
    }
    
    
    void updateScore() {
        m_last_score = 0;
        
        // calculate pure score
        vector<CellInfo> available_gems = getAvailablesFromTable(m_gem_count);
        for (auto cell : available_gems) {
            m_last_score += cell.m_value * m_gem_score[cell.m_type][cell.m_tier];
        }
        
        // add bonuses
        m_last_score += (m_workbenches - m_used_workbenches) * m_bonus_per_empty_workbenches;
    }
    
    
    
    
    
    
    void printGems() const {
        cout << std::left;
        cout << "     T0  T1  T2  T3  T4\n";

        int type{Red};
        for (const auto& gem_row : m_gem_count) {
            cout << std::setw(5) << typeToString(type++);
            for (auto value : gem_row) {
                cout << std::setw(3) << value << ' ';
            }
            cout << '\n';
        }
    }


    void printCards() const {
        auto printTop = []() {
            cout << " ___ ";
        };
        auto printLevel = [](int cell) {
            cout << "/";
            switch (cell) {
            case 3: cout << "ooo"; break;
            case 2: cout << "oo "; break;
            case 1: cout << " o "; break;
            default: cout << "   ";
            }
            cout << "\\";
        };
        auto printFiller = []() {
            cout << "|   |";
        };
        auto printBottom = []() {
            cout << "\\___/";
        };
        auto printLabel = [this](int type, int tier) {
            cout << '|';
            cout << typeToLabel(type) << tier + 1 << ' ';
            cout << '|';
        };
        
        // get cards those are not lv0
        vector<CellInfo> available_cards = getAvailablesFromTable(m_card_level);
        if (available_cards.empty()) {
            cout << "...You have no cards...\n";
            return;
        }

        // print cards
        Type current_type{TypeCount};
        auto printSeparateSpace = [&current_type](Type type) {
            if (type != current_type) {
               current_type = type;
               cout << ' ';
           }
        };

        // printTop
        for (const auto& card : available_cards) {
            printSeparateSpace(card.m_type);
            printTop();
        }
        cout << '\n';
        current_type = TypeCount;
        // printLevel
        for (const auto& card : available_cards) {
            printSeparateSpace(card.m_type);
            printLevel(card.m_value);
        }
        cout << '\n';
        current_type = TypeCount;
        // printFiller
        for (const auto& card : available_cards) {
            printSeparateSpace(card.m_type);
            printFiller();
        }
        cout << '\n';
        current_type = TypeCount;
        // printLabel
        for (const auto& card : available_cards) {
            printSeparateSpace(card.m_type);
            printLabel(card.m_type, card.m_tier);
        }
        cout << '\n';
        current_type = TypeCount;
        // printFiller
        for (const auto& card : available_cards) {
            printSeparateSpace(card.m_type);
            printFiller();
        }
        cout << '\n';
        current_type = TypeCount;
        // printBottom
        for (const auto& card : available_cards) {
            printSeparateSpace(card.m_type);
            printBottom();
        }
        cout << '\n';
    }
    
    
    void printBasicInfo() {
        cout << "+ Cummulated score: " << m_cummulated_score << '\n';
        cout << "+ Workbenches: " << m_workbenches << '\n';
        printCards();
    }
    
    
}; // GemstoneCalculator



































bool isNatural(const string& str) {
    return std::all_of(str.begin(), str.end(), 
                      [](unsigned char c) { return (c >= '0' && c <= '9'); });
}

int toNatural(const string& str) {
    return isNatural(str) ? std::stoi(str) : 0;
}






class CommandSystem {
private:
    using ArgsVec = const vector<string>&;
    using CommandHandler = std::function<void(ArgsVec)>;
    std::unordered_map<string, CommandHandler> commands;
    
    bool running{true};
    
    
    
    
    
    
    void addCommand(const string& name, CommandHandler handler) {
        commands[name] = handler;
    }
    
    
    
    
    
    
public:
    CommandSystem(GemstoneCalculator& calc) {
        addCommand("help", [](ArgsVec) {
            cout << "=== COMMAND LIST ===\n";
            cout << "\"newrun\": Reset all cards, scores, and workbenches.\n";
            cout << "\"newround\": Initialize a round with materials you enter.\n";
            cout << "\"try\": Show result of a card combination you enter.\n";
            cout << "\"sumbit\": Add the score of your last try this round to commulated score.\n";
            cout << '\n';
            cout << "\"setred\"/\"setteal\"/\"setpurple\"/\"setgold\": Set level for your red/teal/purple/gold cards.\n";
            cout << "\"setmin\"/\"setmax\": Remove / max out all of your cards.";
            cout << "\"setscore\"/\"setbenches\": Set cummulated_score/number_of_workbenches.\n";
            cout << "\"gems\": Show your gemstones.\n";
            cout << "\"cards\": Show your cards.\n";
            cout << "\"help\": Show this command list.\n";
        });
        
        
        addCommand("stop", [this](ArgsVec) {
            running = false;
        });
        
        
        addCommand("newrun", [&calc](ArgsVec) {
            calc.beginRun();
        });
        
        
        addCommand("newround", [&calc](ArgsVec args) {
            if (args.size() < 4) {
                cout << "Usage: newround <reds> <teals> <purples> <golds>\n";
                return;
            }
            int r = toNatural(args[0]);
            int t = toNatural(args[1]);
            int p = toNatural(args[2]);
            int g = toNatural(args[3]);
            calc.beginRound({r, t, p, g});
        });
        
        
        addCommand("setred", [&calc](ArgsVec args) {
            if (args.size() < 4) {
                cout << "Usage: setred <r1 lv> <r2 lv> <r3 lv> <r4 lv>\n";
                return;
            }
            int r1 = toNatural(args[0]); r1 *= (r1 <= 3);
            int r2 = toNatural(args[1]); r2 *= (r2 <= 3);
            int r3 = toNatural(args[2]); r3 *= (r3 <= 3);
            int r4 = toNatural(args[3]); r4 *= (r4 <= 3);
            calc.m_card_level[GemstoneCalculator::Red] = {r1, r2, r3, r4};
            
            calc.printCards();
        });
        
        
        addCommand("setteal", [&calc](ArgsVec args) {
            if (args.size() < 3) {
                cout << "Usage: setteal <t1 lv> <t2 lv> <t3 lv>\n";
                return;
            }
            int t1 = toNatural(args[0]); t1 *= (t1 <= 3);
            int t2 = toNatural(args[1]); t2 *= (t2 <= 3);
            int t3 = toNatural(args[2]); t3 *= (t3 <= 3);
            calc.m_card_level[GemstoneCalculator::Teal] = {t1, t2, t3};
            
            calc.printCards();
        });
        
        
        addCommand("setpurple", [&calc](ArgsVec args) {
            if (args.size() < 3) {
                cout << "Usage: setpurple <p1 lv> <p2 lv> <p3 lv>\n";
                return;
            }
            int p1 = toNatural(args[0]); p1 *= (p1 <= 3);
            int p2 = toNatural(args[1]); p2 *= (p2 <= 3);
            int p3 = toNatural(args[2]); p3 *= (p3 <= 3);
            calc.m_card_level[GemstoneCalculator::Purple] = {p1, p2, p3};
            
            calc.printCards();
        });
        
        
        addCommand("setgold", [&calc](ArgsVec args) {
            if (args.size() < 3) {
                cout << "Usage: setgold <g1 lv> <g2 lv> <g3 lv>\n";
                return;
            }
            int g1 = toNatural(args[0]); g1 *= (g1 <= 3);
            int g2 = toNatural(args[1]); g2 *= (g2 <= 3);
            int g3 = toNatural(args[2]); g3 *= (g3 <= 3);
            calc.m_card_level[GemstoneCalculator::Gold] = {g1, g2, g3};
            
            calc.printCards();
        });
        
        
        addCommand("setmin", [&calc](ArgsVec) {
            calc.m_card_level[GemstoneCalculator::Red] = {0, 0, 0};
            calc.m_card_level[GemstoneCalculator::Teal] = {0, 0, 0};
            calc.m_card_level[GemstoneCalculator::Purple] = {0, 0, 0};
            calc.m_card_level[GemstoneCalculator::Gold] = {0, 0, 0};
            
            calc.printCards();
        });
        
        
        addCommand("setmax", [&calc](ArgsVec) {
            calc.m_card_level[GemstoneCalculator::Red] = {3, 3, 3};
            calc.m_card_level[GemstoneCalculator::Teal] = {3, 3, 3};
            calc.m_card_level[GemstoneCalculator::Purple] = {3, 3, 3};
            calc.m_card_level[GemstoneCalculator::Gold] = {3, 3, 3};
            
            calc.printCards();
        });
        
        
        addCommand("setscore", [&calc](ArgsVec args) {
            if (args.size() < 1) {
                cout << "Usage: setscore <value>\n";    
                return;
            }
            calc.m_cummulated_score = toNatural(args[0]);
            cout << "Cummulated score: " << calc.m_cummulated_score << '\n';
        });
        
        
        addCommand("setbenches", [&calc](ArgsVec args) {
            if (args.size() < 1) {
                cout << "Usage: setbenches <value>\n";    
                return;
            }
            int benches = toNatural(args[0]);
            benches = benches <= 6 ? benches : 6;
            calc.m_workbenches = benches;
            cout << "Workbenches: " << calc.m_workbenches << '\n';
        });


        addCommand("try", [&calc](ArgsVec args) {
            // validate
            if (args.size() > calc.m_workbenches) {
                cout << "Not enough workbenches\n";
                return;
            }
            
            // save state of m_gem_count
            IntVec saved_t0gems = calc.getT0Gems();
            
            // add r1 r2 r3 to card_queue if enough lv
            vector<string> used_cards{};
            if (calc.m_card_level[GemstoneCalculator::Red][0] >= 2) {
                calc.activateCard("r1");
                used_cards.push_back("r1");
            }
            if (calc.m_card_level[GemstoneCalculator::Red][1] >= 3) {
                calc.activateCard("r2");
                used_cards.push_back("r2");
            }
            if (calc.m_card_level[GemstoneCalculator::Red][2] >= 3) {
                calc.activateCard("r3");
                used_cards.push_back("r3");
            }
            
            // activate cards
            for (const auto& param : args) {
                calc.m_used_workbenches++;
                
                if (std::find(used_cards.begin(), used_cards.end(), param) == used_cards.end()) {
                    calc.activateCard(param);
                }
            }
            
            // print result
            calc.printGems();
            calc.updateScore();
            cout << "Score: " << calc.m_last_score << '\n';
            
            // reset m_gem_count and m_gem_score to its original state
            calc.resetIntTable(calc.m_gem_count);
            calc.setT0Gems(saved_t0gems);
            calc.resetScoreTable();
            
            // reset bonuses
            calc.m_bonus_per_empty_workbenches = 0;
            calc.m_used_workbenches = 0;
        });
        
        
        addCommand("submit", [&calc](ArgsVec) {
            calc.m_cummulated_score += calc.m_last_score;
            cout << "Summited with score: " << calc.m_last_score << '\n';
            cout << "Cummulated score: " << calc.m_cummulated_score << "\n";
        });
        
        addCommand("gems", [&calc](ArgsVec) {
            calc.printGems();
        });
        
        addCommand("cards", [&calc](ArgsVec) {
            calc.printCards();
        });
    }
    
    
    void execute(const string& input) {
        std::istringstream iss(input);
        string cmd;
        vector<string> args;
        
        // parse input into command and args
        string token;
        while (iss >> token) {
            if (cmd.empty()) {
                cmd = token;
            }
            else {
                args.push_back(token);
            }
        }
        
        // execute command
        auto iter = commands.find(cmd);
        if (iter != commands.end()) {
            iter->second(args);
        }
        else if (!cmd.empty()) {
            cout << "Unknown command: " << cmd << '\n';
        }
    }
    
    
    bool isRunning() const {
            return running;
    }
    
        
}; // CommandSystem











































































int main() {
    GemstoneCalculator calc;
    CommandSystem command_system(calc);
    
    command_system.execute("help");
    cout << '\n';
    command_system.execute("newrun");
    cout << '\n';
    
    string input;
    while (command_system.isRunning()) {
        cout << "\n> ";
        if (!std::getline(cin, input)) {
            break; // ctrl+D
        }
        command_system.execute(input);
    }
    
    return 0;
}