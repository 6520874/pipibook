#include <sqliteFile/sqlite3.h>
#include <iostream>
#include <cocos2d.h>
#include <string.h>

#define DB_FILE "tangtouge.db"
//

#define TBL_CATEGORY "CREATE TABLE IF NOT EXISTS category(\
_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
category     TEXT);"

#define TBL_CONTENT "CREATE TABLE IF NOT EXISTS content(\
_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
category_id     INTEGER,\
title           TEXT,\
info            TEXT,\
detail          TEXT);"

using namespace cocos2d;
using namespace std;

class DBService
{
public:
	DBService();
	~DBService();

    static sqlite3 *openDB();
    static void closeDB(sqlite3 *db);
    
    static vector<map<std::string, std::string> > getCategory();//获取汤剂列表
    static vector<map<std::string, std::string> > getContent(string category_id);//获取内容列表
//    
private:
//    string m_dbPath;

    
};

