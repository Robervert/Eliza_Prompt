////////////////////>>只有保留了我的编写风格，才能让你知道你看的是我写的源代码<<////////////////////
#define _CRT_SECURE_NO_WARNINGS //无所畏惧，无视风险
////"std::"   不用"using namespace std;"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <filesystem>

/////////////////////↑标准库
#include "ELIZA-TEXTPERFORM.h"
#include "ELIZA.h"

/////////////////////↑相关头文件
#define MAX_PATH 80
void getFiles(std::string path, std::vector<std::string>& files);

/////////////////////↑相关定义
int getRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

// 字符串转小写（方便匹配）
std::string toLower(std::string s)
{
    for (char& c : s) c = tolower(c);
    return s;
}

// 替换人称代词：我 <-> 你
std::string replacePronouns(std::string s)
{
    std::map<std::string, std::string> pronouns = {
        {"i", "you"}, {"me", "you"}, {"my", "your"}, {"mine", "yours"},
        {"you", "i"}, {"your", "my"}, {"am", "are"}, {"we", "you"}, {"our", "your"}, {"ours", "yours"}
    };
    std::string res, word;
    s += " ";
    for (char c : s)
    {
        if (isspace(c))
        {
            if (pronouns.count(word)) res += pronouns[word] + " ";
            else res += word + " ";
            word.clear();
        }
        else word += c;
    }
    if (!res.empty()) res.pop_back();
    return res;
}

//////更复杂的逻辑（需要完善）
//***********************************
//////

// 随机获取回应
std::string getResponse(const std::string& input)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> rules = {
        {"hello", {"Hello! How are you feeling today?"}},
        {"am sad", {"I'm sorry to hear you're sad. Want to talk about it?"}},
        {"is sad", {"Sorry to hear that. Want to talk about it?"}},
        {"are sad", {"Sorry to hear that. Want to talk about it?"}},
        {"happy", {"That's wonderful! What makes you happy?"}},
        {"i feel", {"Why do you feel that?"}},
        {"i think", {"Why do you think that?"}},
        {"i love", {"Oh? Could you please tell me more?"}},
        {"i hate", {"Oops? Why do you hate that?", "What happend?", "Are you Okay?", "What can I help you on that?"}},
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
        ////////////////自定义更多的对话模板
        {"nope", {"Okay, well. Let's talk another topic, okay?", "why not?"}},
        {"huh", {"Uh huh?","hmm..."}},
        {"clean the screen", {"If you want to clean the screen, please just input \"cls\"."}},
        {"cmd", {"If you want to start the cmd, please just input \"cmd\", if not, just say as usual."}},
        {"are you hot", {"In your fascination, am I hot?", "Oh, really?"}},
        ////////////////脚本冲突
        {"cls", {"Hello, I am Eliza", "Talk to me", "You've come back :>", "A brand new day, and a brand new me!"}},
        {"cmd", {""}},
        //{"-name", {""}},
        {"help", {"Here is the simplified helpfile below. You can find the completed one from the \"ElizaHow\".", "Helps come~. You can find the completed one from the \"ElizaHow\".", "Check your helps below."}},
        ////////////////普适模板
        {"", {"Tell me more.", "How does that make you feel?", "Why do you say that?", "I understand.", "Can you elaborate on that?",
        "Can you say it more clearly?", "?", "(⊙o⊙)?"}}, // "Need help? Just input \"help\" or open the ElizaHow to see the help :>",
    };

    std::string low = toLower(input);
    for (auto& rule : rules)
    {
        if (low.find(rule.first) != std::string::npos)
        {
            int idx = rand() % rule.second.size();
            std::string resp = rule.second[idx];
            // 如果回应需要代入用户的话（带*）
            size_t star = resp.find('*');
            if (star != std::string::npos)
            {
                resp.replace(star, 1, replacePronouns(input));
            }
            return resp;
        }
    }
    return "Well, tell me more :>";
}

int main() /////////////////////////////////////////////
{
    system("color 0f"); //什么时候改成不要用cmd命令的...
    ASCLLIMG();
    std::cout << "\nINITIALIZING";
    time_t now = time(0); //当前时间
    tm* localTime = localtime(&now); // 转换为本地时间
    std::cout << ".";
    char UserName[150];
    char UserAge[30];
    char UserGender[8];
    char UserEI[200];
    char Q4[200];
    char Q5[200];// {}; //???怎么初始化???
    std::cout << ".";
    int cy = 0;
    int respondcount = 0;
    std::string EI;
    std::string SEX;
    std::string USER_INPUT;
    std::ofstream ofsUserProf;//加密 加密 加密 加密 要加密！！！
    std::ofstream ofsUserProfPath;
	std::ofstream ofsErrorLog;
    system("cls");
    std::string UserProfilesPath = ".//UserProfiles//"; // 指定目录路径

    //std::vector<std::string> files;
    //const char* filePath = ".\\UserProfiles";
    ////////获取该路径下的所有文件  
    //getFiles(filePath, files);
    //char str[30]{};
    //int size = files.size();
    //for (int i = 0; i < size; i++)
    //{
    //    std::cout << files[i].c_str() << std::endl;
    //}
    //if (!ofsUserProfPath)
   // {
    //    void();
    //}
    //else
   // {
        
    //}
    
    std::error_code ec;
    try
    {
        // Ensure source and target directories exist (avoid exceptions or silent failures)
        if (!std::filesystem::exists(UserProfilesPath) || !std::filesystem::is_directory(UserProfilesPath))
        {
            // If the user profiles path doesn't exist, create it so iteration will succeed (or remain empty)
            std::filesystem::create_directories(UserProfilesPath);
        }

        // Ensure processing directory exists and open output file once
        std::filesystem::create_directories(".//Processing//");
        std::ofstream ofsUserProfPath(".//Processing//UserMaps.txt", std::ios::out | std::ios::trunc);
        if (!ofsUserProfPath)
        {
            std::cerr << "\n\n>>[ERROR] Failed to open \".//Processing//UserMaps.txt\" for appending.\n";
        }
        else
        {
            for (const auto& entry : std::filesystem::directory_iterator(UserProfilesPath))
            {
                // Write path once per entry; file already opened
                ofsUserProfPath << entry.path().string() << std::endl;
            }
            ofsUserProfPath.close();
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "[ERROR] filesystem error while scanning '" << UserProfilesPath << "': " << e.what() << std::endl;
    }
    if (ec) /* 记录错误并返回/跳过 */
    {
        std::ofstream ofsErrorLog(".//Processing//UserMaps.txt", std::ios::app);
    }
    else
    {
        std::ofstream ofsUserProfPath(".//Processing//UserMaps.txt", std::ios::app);
        for (const auto& entry : std::filesystem::directory_iterator(UserProfilesPath))
        {
            ofsUserProfPath << entry.path().string() << '\n';
        }
    }

    std::cout << "." << std::endl;
    gotoxy(0, 0);
    std::cout << "                ";
    gotoxy(0, 0);
    GREETINGS();
    system("title Eliza [Psychotherapist Script]");
    std::cout << "ELIZA: Hello! I am Eliza, may I have your name? (type 'quit' to exit)\n";
    std::cout << "Enter your name (in 20 letters) below(You can enter \"Eliza\" to check something funny. Please do not enter other contents, which may cause embarrasment.)\n";
    std::cout << "Your name:";
    
    scanf("%s", UserName);
    if (strcmp(UserName, "Eliza") == 0)
    {
        Eggs();
    }
    else
    {
        srand(time(0)); // 使用当前时间作为种子
        int randomnum = getRand(1, 9); // 生成1到9之间的随机数
        if (randomnum <= 3)
        {
            std::cout << "\nELIZA: Oh, nice to meet you, " << UserName << "." << std::endl;
        }
        else if (randomnum >= 7)
        {
            std::cout << "\nELIZA: Welcome, " << UserName << "!" << std::endl;
        }
        else
        {
            std::cout << "\nELIZA: " << UserName << ", I think we have met before." << std::endl;
        }
        std::cout << "\nELIZA: What's your age?\n";
        std::cout << "You (" << UserName << "):";
        scanf("%s", UserAge); std::cin.ignore();
        std::cout << "\nELIZA: Okay. What's your gender? Enter \"M\" or \"F\" or \"O\".\n>>According to the policies, you could only choose between Male(M) and Female(F) and Others(O):\n";
        std::cout << "You (" << UserName << "):";
        scanf("%s", UserGender); std::cin.ignore();
        SEX = UserGender;
		if (strcmp(UserGender, "M") == 0 || strcmp(UserGender, "F") == 0 || strcmp(UserGender, "O") == 0)
        {
            srand(time(0));
            int randomnum = getRand(1, 9);
            if (randomnum <= 6)
            {
                std::cout << "ELIZA: Okay.\n";
            }
            else
            {
                std::cout << " ELIZA: Got it.\n";
            }
        }
        else
        {
			std::cout << "\nELIZA: Naughty.\n"; //still need to add some random responses here, but I am too lazy to do that now, so just one response for now
        }
        std::cout << "\nELIZA: In your opinion, are you an \"Extrovert\" or an \"Introvert\"?\nPlease enter \"E\" or \"I\":\n";
        std::cout << "You (" << UserName << "):";
        scanf("%s", UserEI); std::cin.ignore();
        EI = UserEI;
        if (strcmp(UserEI, "E") != 0 && strcmp(UserEI, "I") !=0)
        {
            srand(time(0));
            int randomnum = getRand(1, 9);
            if (randomnum <= 6)
            {
                std::cout << "ELIZA: Naughty.\n";
            }
            else
            {
                std::cout << " ELIZA: ╮(╯▽╰)╭\n";
            }
            EI = "[*Unknown]";
            std::cout << ">>==================>>>>BASIC-INFO-ABOVE<<<<==================<<\n\n" << std::endl;
        }
        else
        {
            std::cout << "Eliza: Okay, finished. Let's start our talk.\n";
            std::cout << ">>==================>>>>BASIC-INFO-ABOVE<<<<==================<<\n\n" << std::endl;
        }
        //////////////////////////////////////
        std::string UserProfileName, UserProfileRoot, UserNames, tailtxt;
        UserProfileRoot = ".//UserProfiles//";
        tailtxt = ".txt";
        UserNames = UserName;
        UserProfileName = UserProfileRoot + UserNames + tailtxt;
        //////////////////////////////////////
        ofsUserProf.open(UserProfileName, std::ios::app);
        ofsUserProf << "USER_NAME:" << UserName << "\n" << std::endl;
        ofsUserProf << "\nUSER_AGE:" << UserAge << std::endl;
        ofsUserProf << "USER_GENDER:" << SEX << std::endl; //是不是可以去掉<<endl然后在开头加\n，下一次直接接在后面
        ofsUserProf << "USER_PERSONALITY[E/I]:" << EI << std::endl;
        ofsUserProf.close();

        /* 
        std::ifstream file{}; //add check files inquiries.
        file.open(UserProfileName, std::ios::in);
        if (!file)
        {
            std::cerr << ">>failed to open this file." << std::endl;
            std::cerr << ">>please check if your file path is correct." << std::endl;
        }
        std::string line;
        while (std::getline(file, line)) //以行为变量
        {
            //显示文件内容 std::cout << line << std::endl; //check if line =... ,then ... .
        }
        file.close();
        */


        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        {
            std::cout << "ELIZA: " << getResponse("input") << "\n\n"; //回答也记录吧。
            ofsUserProf.open(UserProfileName, std::ios::app);
            ofsUserProf << "USER_INPUT:" << std::endl;//测试
            while (true)
            {
                std::string UserInput;
                std::cout << "You (" << UserName << "):";
                getline(std::cin, UserInput);
                USER_INPUT = UserInput;
                ofsUserProf << USER_INPUT << "\n" << std::endl; //测试

                if (UserInput == "quit")
                {
                    std::cout << "\nELIZA: Good bye, " << UserName << ". See you again!" << std::endl;
					system("pause");
                    break;
                    ofsUserProf.close();
                }
                else if (UserInput == "cmd")
                {
                    std::cout << "\nELIZA: Okay, I will start the cmd." << std::endl;
                    system("cmd");
                }
                else if (UserInput == "cls")
                {
                    std::cout << "\nELIZA: The screen will be cleared in 2 seconds." << std::endl;
					system("pause");
                    system("cls");
                    GREETINGS();
                }
                else if (UserInput == "help")
                {
                    system("pause");
					system("cls");
                    ASCLLIMG();
                    std::cout << "\n" << std::endl;
                    GREETINGS();
                    std::cout << "\nELIZA: Here is the simplified helpfile below. You can find the completed one from the \"./ELIZAROOM/ElizaHow.chm\".\n" << std::endl;
                    
					std::ifstream file(".\\ELIZAROOM\\mHelps.hlp"); // 打开名为 mHelps.hlp 的文件，其实就是个.txt文本文件，放在ELIZAROOM文件夹里
                    if (file.is_open()) // 检查文件是否成功打开
                    {
                        std::string helpfileline;
                        while (std::getline(file, helpfileline)) // 逐行读取文件内容
                        {
                            std::cout << helpfileline << std::endl; // 输出每一行内容
                        }
                        file.close(); // 关闭文件
                    }
                    else
                    {
						std::cerr << "\n>>[Error] Failed to open the help file. Please check if the file exists and the path is correct.\n" << std::endl;
                    }
                }
				else if (UserInput == "version" || UserInput == "modcheck")//modcheck不应该放在这里，应该放在ELIZA-TEXTPERFORM里，或者干脆放在一个新的文件里，专门用来检查版本和模块的。先放在这里吧，反正也没用。
                {
					version();
                }
                else
                {
                    std::cout << "ELIZA: " << getResponse(UserInput) << "\n\n";
                }
                if (respondcount == 0) //*num 为问题数
                {
                    gotoxy(0 , csbi.dwCursorPosition.Y);
                    for (int mask{}; mask <= 6; mask++)
                    {
                        std::cout << "                                                                                   " << std::endl;//清屏用的
                    }
                    respondcount = respondcount + 1;
                    gotoxy(0, csbi.dwCursorPosition.Y);
                    //std::cout << "You (" << UserName << "):";
                }
            }
            ofsUserProf.close();
        }
        else
        {
            ofsUserProf.open(UserProfileName, std::ios::app);
            ofsUserProf << "[ERROR]*GEI_CURSOR_POSITION: FAILED" << std::endl;
            ofsUserProf.close();
            std::cerr << "[ERROR] Could NOT get cursor position.\n" << std::endl;
            //return 0;
        }
    }
    return 0;
}
//                gotoxy(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);

/*C++11及以上的随机数生成：
#include <iostream>
#include <random>
#include <ctime>

int main()
{
    std::default_random_engine e(time(0)); // 使用当前时间作为种子
    std::uniform_int_distribution<int> u(2, 20); // 定义一个2到20之间的均匀分布
    for (int i = 0; i < 10; i++)
        {
        std::cout << u(e) << std::endl; // 生成随机数并输出
        }
    return 0;
}
*/
