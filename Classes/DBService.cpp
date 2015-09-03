#include "DBService.h"
#include "Utils.h"
#include "Global.h"

//static string dbPath = FileUtils::getInstance()->fullPathForFilename(DB_FILE);
//static string dbPath = FileUtils::getInstance()->getWritablePath() + DB_FILE;
//
DBService::DBService(){
    //    m_dbPath = FileUtils::getInstance()->getWritablePath() + DB_FILE;
}
//
sqlite3 *DBService::openDB(){
	sqlite3 * conn = NULL;
//    log("==%s==",(FileUtils::getInstance()->getWritablePath() + DB_FILE).c_str());
	if (sqlite3_open((FileUtils::getInstance()->getWritablePath() + DB_FILE).c_str(), &conn) != SQLITE_OK)
	{
		log("open failed!");
	}
    return conn;
}

void DBService::closeDB(sqlite3 *db){
	if (sqlite3_close(db) != SQLITE_OK)
	{
		log("close falied, erro code:%s\n", sqlite3_errmsg(db));
	}
}

vector<map<std::string, std::string> > DBService::getCategory(){
    vector<map<string, string> > results;
    
    sqlite3 *conn = openDB();
    char* err_msg;
    sqlite3_exec(conn, TBL_CATEGORY, NULL, NULL, &err_msg);
    
    char **dbresult;
    int nrow, ncolumn, index;
    
    string checkSql = "select * from category";
    sqlite3_get_table(conn, checkSql.c_str(), &dbresult, &nrow, &ncolumn, &err_msg);
    
    index = ncolumn;
    for (int i=0; i<nrow; i++) {
        map<string, string> result;
        result["_id"]           = dbresult[index];
        result["category"]      = dbresult[index + 1];
        result["star"]          = dbresult[index + 2];
        index += ncolumn;
        results.push_back(result);
    }
    
    sqlite3_free_table(dbresult);
    closeDB(conn);
    return results;
}

vector<map<std::string, std::string> > DBService::getContent(string category_id){
    vector<map<string, string> > results;
    
    sqlite3 *conn = openDB();
    char* err_msg;
    sqlite3_exec(conn, TBL_CONTENT, NULL, NULL, &err_msg);
    
    char **dbresult;
    int nrow, ncolumn, index;
    
    string checkSql = "select * from content where category_id = '" + category_id + "'";
    sqlite3_get_table(conn, checkSql.c_str(), &dbresult, &nrow, &ncolumn, &err_msg);
    
    index = ncolumn;
    for (int i=0; i<nrow; i++) {
        map<string, string> result;
        result["_id"]               = dbresult[index];
        result["category_id"]       = dbresult[index + 1];
        result["title"]             = dbresult[index + 2];
        result["info"]              = dbresult[index + 3];
        result["detail"]            = dbresult[index + 4];
        index += ncolumn;
        results.push_back(result);
    }
    
    sqlite3_free_table(dbresult);
    closeDB(conn);
    return results;
}

DBService::~DBService(){
    
}





