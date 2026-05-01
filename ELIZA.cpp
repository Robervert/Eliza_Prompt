#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <windows.h>
#include <ctime>

/////////////////////相关头文件
#include "ELIZA-TEXTPERFORM.h"
/////////////////////

// 字符串转小写（方便匹配）
std::string toLower(std::string s) {
    for (char& c : s) c = tolower(c);
    return s;
}

// 替换人称代词：我 <-> 你
std::string replacePronouns(std::string s) {
    std::map<std::string, std::string> pronouns = {
        {"i", "you"}, {"me", "you"}, {"my", "your"}, {"mine", "yours"},
        {"you", "i"}, {"your", "my"}, {"am", "are"}, {"we", "you"}, {"our", "your"}, {"ours", "yours"}
    };
    std::string res, word;
    s += " ";
    for (char c : s) {
        if (isspace(c)) {
            if (pronouns.count(word)) res += pronouns[word] + " ";
            else res += word + " ";
            word.clear();
        }
        else word += c;
    }
    if (!res.empty()) res.pop_back();
    return res;
}

// 随机获取回应
std::string getResponse(const std::string& input) {
    std::vector<std::pair<std::string, std::vector<std::string>>> rules = {
        {"hello", {"Hello! How are you feeling today?"}},
        {"am sad", {"I'm sorry to hear you're sad. Want to talk about it?"}},
        {"is sad", {"Sorry to hear that. Want to talk about it?"}},
        {"are sad", {"Sorry to hear that. Want to talk about it?"}},
        {"happy", {"That's wonderful! What makes you happy?"}},
        {"i feel", {"Why do you feel that?"}},
        {"i think", {"Why do you think that?"}},
        {"because", {"Is that the real reason?"}},
        {"no", {"Why not?", "Really?", "Oh, come on!"}},
        {"yes", {"Good job.", "Alright.", "Okay."}},
        {"mom", {"Tell me more about your mother."}},
        {"dad", {"Tell me more about your father."}},
        {"father", {"Tell me more about your mother."}},
        {"mother", {"Tell me more about your father."}},
        {"girlfriend", {"Tell me more about your girlfriend, okay?", "I'm curious what she likes", "Do you think your grilfriend lovely?"}},
        {"boyfriend", {"Could you tell me more about your boyfriend?", "A handsome man or boy？"}},
        {"husband", {"Tell me more about your husband."}},
        {"wife", {"Tell me more about your wife."}},
        {"grandpa", {"Tell me more about your grandparents."}},
        {"gramdma", {"Tell me more about your grandparents."}},
        {" ex", {"Want to talk about your ex?"}},
        {"i love", {"Oh? Could you please tell me more?"}},
        ////////////////自定义更多的对话模板
        {"nope", {"Okay, well. Let's talk another topic, okay?", "why not?"}},
        {"huh", {"Uh huh?","hmm..."}},
        {"clean the screen", {"If you want to clean the screen, please just input \"cls\"."}},
        {"cmd", {"If you want to start the cmd, please just input \"cmd\", if not, just say as usual."}},
        {"are you hot", {"In your fascination, am I hot?", "Oh, really?"}},
        ////////////////脚本冲突
        {"cls", {"Hello, I am Eliza", "Talk to me", "You've come back :>", "A brand new day, and a brand new me!"}},
        {"cmd", {""}},
        ////////////////
        {"", {"Tell me more.", "How does that make you feel?", "Why do you say that?", "I understand.", "Can you elaborate on that?", "Can you say it more clearly?", "?", "Need help? Just input \"help\" or open the ElizaHow to see the help :>"}},
    };

    std::string low = toLower(input);
    for (auto& rule : rules) {
        if (low.find(rule.first) != std::string::npos) {
            int idx = rand() % rule.second.size();
            std::string resp = rule.second[idx];
            // 如果回应需要代入用户的话（带*）
            size_t star = resp.find('*');
            if (star != std::string::npos) {
                resp.replace(star, 1, replacePronouns(input));
            }
            return resp;
        }
    }
    return "Well, tell me more :>";
}

int main()
{
    system("color 0f");
    GREETINGS();
    srand(time(0));
    std::cout << "ELIZA: Hello! I am Eliza. (type 'quit' to exit)\n";
    std::string input;

    while (true)
    {
        std::cout << "You: ";
        getline(std::cin, input);
        if (input == "quit")
        {
            std::cout << "\nELIZA: Good bye!" << std::endl;
            Sleep(2000);
            break;
        }
        else if (input == "cmd")
        {
            std::cout << "\nELIZA: Okay, I will start the cmd." << std::endl;
            system("cmd");
        }
        else if (input == "cls")
        {
            std::cout << "\nELIZA: I would clean the screen in 2 seconds." << std::endl;
            Sleep(2000);
            system("cls");
            GREETINGS();
        }
        std::cout << "ELIZA: " << getResponse(input) << "\n\n";
    }
    return 0;
}