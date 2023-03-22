using System;
using System.Data;
using MySql.Data.MySqlClient;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DatabaseLibrary
{
    class MySqlDBCon : IDBConnection
    {
        MySqlCommand cmd;
        MySqlDataReader reader;
        MySqlConnection connection;
        string _server, _userID, _password, _database;

        public MySqlDBCon(ConnectionString connectionString)
        {
            _server = connectionString.server;
            _userID = connectionString.userID;
            _password = connectionString.password;
            _database = connectionString.database;
        }

        public MySqlDBCon(String server, string userID, string password, string database)
        {
            _server = server;
            _userID = userID;
            _password = password;
            _database = database;
        }

        public string getCollumName(ref string from)
        {
            from = "FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'holdingtax' AND TABLE_NAME = 'Info';";
            return "COLUMN_NAME";
        }

        public void executeDBQuery(string sql, List<string> columnName, DataTable dt)
        {
            dt.Clear();

            try
            {
                MySqlConnectionStringBuilder builder = new MySqlConnectionStringBuilder();
                builder.Server = _server;
                builder.UserID = _userID;
                builder.Password = _password;
                builder.Database = _database;
                builder.SslMode = MySqlSslMode.None;

                // Open connection.
                connection = new MySqlConnection(builder.ToString());
                connection.Open();

                // Create Command.
                cmd = new MySqlCommand(sql, connection);
                cmd.Prepare();

                //Data Reader.
                reader = cmd.ExecuteReader();
                dt.Load(reader);

                reader.Close();
                reader = null;
                cmd.Dispose();
                cmd = null;
                //MessageBox.Show("Success to connect database");
            }
            catch(Exception ex)
            {
                MessageBox.Show("Faield to connect database :  " + ex);
            }

            connection.Close();
            connection = null;
            //MessageBox.Show(sql);
        }
    }
}
