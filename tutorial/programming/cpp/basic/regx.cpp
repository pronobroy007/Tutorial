#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>


void printMatches(std::string str, std::regex reg);
std::vector<std::string> getMatches(std::string str, std::regex reg);
int main()
{

    std::string str = "<h1>This</h1> ((Is)) <h1>a {simple} string} is't</h1>it";
    //For ignore case.
    //std::regex reg(R"(<h1>(.*)</h1>)"); 

    //Reading file :
    //--------------
        std::vector<std::string> msg, items, details;
        std::ifstream inputFile("error");

        inputFile.seekg(0, std::ios::end);
        int fsize = inputFile.tellg();
        //Make input pointer to the begining
        inputFile.seekg(0, std::ios::beg);
        str = std::string(fsize, ' ');

        inputFile.read((char*)str.c_str(), fsize);
        inputFile.close();
    std::regex reg(R"(\(\(([^\(\)]*)\)\))"); 

    /*
    while(true)
    {
        std::cin >> str;
        bool match = std::regex_match(str, reg);
        std::cout << (match ? "Match" : "Not Match") << std::endl;
        std::cout << std::endl;
    }
    */
    std::vector<std::string> buff = getMatches(str, reg);
    for(int i = 0; i < buff.size(); i++)
        std::cout << buff[i] << std::endl;
}


std::vector<std::string> getMatches(std::string str, std::regex reg)
{
    std::smatch matchs;
    std::vector<std::string> buff;
    //0 = full match
    //1 = 1st group from "reg" if we have any. 
    //2 = 2st group from "reg" if we have any. 
    std::sregex_token_iterator pos(str.begin(), str.end(), reg, 1);
    std::sregex_token_iterator end;
    for(;pos != end; pos++)
        buff.push_back(pos->str());
    return buff;
}


void printMatches(std::string str, std::regex reg)
{
    std::smatch matchs;
    while(std::regex_search(str, matchs, reg))
    {
        std::cout << "Is there any match : " << matchs.ready() << std::endl;
        std::cout << "Total matchs : " << matchs.size() << std::endl;
        for(int i = 0; i < matchs.size(); i++)
            std::cout << i << " match : " << matchs.str(i) << std::endl;
        str = matchs.suffix().str();
        std::cout << std::endl;
    }
}


/*
 * Parttern :
 * ----------
 *      ^           =>  Begining of string.
 *      $           =>  End of string.
 *
 *      .           =>  Any charecter except newline.
 *
 *      ?           =>  0 or 1 preceding charecter
 *      EX : "abc?"  = "abc" is match. "ab" also a match.
 *
 *      *           =>  0 or more preceding charecter
 *      EX : "abc*"  = "abc" is match. "ab" also a match, "abcc" also a match
 *
 *      +           =>  1 or more preceding charecter
 *      EX : "abc+"  = "abc" is match. "abcc" also a match, "ab" is not a match
 *
 *      ab[cd]*     =>  afetr "ab" 0 or more c or d 
 *      Ex :        match : ab, abc, abd, abcccd, abdddccd      not match : adddc, abde, abcce
 *
 *      ab[^cd]*     =>  afetr "ab" 0 or more c or d 
 *      Ex :        match : ab, abil, aberlml, abl          no match : ab, abc, abd, abcccd, abdddccd      
 *
 *      ab[cd]{4}     =>  afetr "ab" exect 4 preceding charecter of c or d
 *      Ex :        match : abcccc, abcddc, abddcc          no match : abccccc, abcdddc, abd, abe
 *
 *      ab[cd]{4, }     =>  afetr "ab" 4 or more preceding charecter of c or d
 *      ab[cd]{4, 6}    =>  afetr "ab" 4/5/6 preceding charecter of c or d
 *
 *      abc|ef        => Either match "abc" or "ef"
 *      Ex :        match : abc, ef
 *
 *      (abc).*\\1        => () use for define group and /1 if for match 1s group 
 *                          In this case we have only one group. and also we use 2 backslash 
 *                          because 1st one is for scape charecter.
 *      Ex :        match : abcfabc, abcHHHHHabc, abclkdflkjalfabc      not match : abclksjdf
 *
 *
 *      [[:w:]]         => This mean word charecter like digit, number or underscore.
 *      [[:alpha:]]     => alphabetic letter.
 *      [[:punct:]]     => punctuation mark charecter.
 *      [[:upper:]]     => uppercase letter     (isUpper).
 *      [[:xdigit:]]    => Hex digit            (isxDigit).
 *      [[:d:]]         => Decimal digit        (isDigit).
 *      [[:s:]]         => White space          (isSpace).
 *      [[:blank:]]     => Blank charecte       (space and tab).
 */
