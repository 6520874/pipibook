//
//  utils.h
//
//

#ifndef TangTouGe_Utils_h
#define TangTouGe_Utils_h

#include "Global.h"
//#include "SimpleAudioEngine.h"

class Utils
{
    
public:
    static string itoa(int val)//int 转 strign
    {
        char buffer [30];
        sprintf (buffer, "%d", val);
        return buffer;
    }
    static vector<std::string> split(std::string str, std::string pattern)
    {
        string::size_type pos;
        vector<string> result;
        str += pattern;
        int size = str.size();
        
        for (int i = 0; i < size; i++) {
            pos = str.find(pattern, i);
            if (pos < size) {
                string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }
        
        return result;
    }
    
    static vector<std::string> splitContent(std::string str)
    {
        vector<string> resultTem = split(str, "\n");
        vector<string> result;
        
        for (int i = 0; i < resultTem.size(); i++) {
            vector<string> oneResult = split(resultTem[i], "  ");
            result.push_back(oneResult[0]);
            result.push_back(oneResult[1]);
        }
        return result;
    }
    
    //获得系统当前时间
    static string getCurrentTimeYYMMDDHHMMSS(){
        struct timeval now;
        gettimeofday(&now, NULL);  // get seconds
        struct tm* tm;
        time_t timep = now.tv_sec;
        tm = localtime(&timep);
        char currentTime[30];
        sprintf(currentTime, "%04d-%02d-%02d %02d:%02d:%02d",tm->tm_year + 1900,tm->tm_mon + 1,tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        return currentTime;
    }
};

#endif
