using System;
using System.Data;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DatabaseLibrary
{
    struct ConnectionString
    {
        public string server, userID, password, database;
        public ConnectionString(string server, string userID, string password, string database)
        {
            this.server = server;
            this.userID = userID;
            this.password = password;
            this.database = database;
        }
    }

    interface IDBConnection
    {
        void executeDBQuery(string sql, List<string> columnName, DataTable dt);
        string getCollumName(ref string from);
    }
}
