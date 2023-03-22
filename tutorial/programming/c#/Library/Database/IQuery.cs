using System;
using System.Data;
using System.Collections.Generic;

namespace DatabaseLibrary
{

    class QUERY
    {
        public string select;
        public string from;
        public string where;
        public string orderBy;
        public string limit;
        public List<string> columnName;

        public QUERY() { columnName = new List<string>(); }

        public void clear()
        {
            select = "";
            where = "";
            orderBy = "";
            limit = "";
            columnName.Clear();
        }
    };

    class IQuery 
    {
        protected QUERY _query;
        protected string tableName;
        protected IDBConnection _conn;
        protected List<string> tableColumnName;

        public DataTable dataTable;

        public IQuery(IDBConnection conn, string tblName) 
        {
            _conn = conn;
            tableName = tblName;

            _query = new QUERY();
            dataTable = new DataTable();
            tableColumnName = new List<string>();

            //_query.from = "FROM PRAGMA_TABLE_INFO('"+tableName+"')";
            //_query.from = "FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'holdingtax' AND TABLE_NAME = 'Info';";
            string columnName = conn.getCollumName(ref _query.from);
            select(new string[]{columnName}).get();
            foreach(DataRow dr in dataTable.Rows)
                tableColumnName.Add(dr[columnName].ToString());

            dataTable.Rows.Clear();
            dataTable.Columns.Clear();
            _query.from = "FROM "+ tableName +" ";
        }



        public string get()
        {
            string sql;
            if(String.IsNullOrEmpty(_query.select))
            {
                sql = "SELECT * ";
                _query.columnName = new List<string>(tableColumnName);
            }
            else
                sql = _query.select;
            sql += _query.from;
            sql += (String.IsNullOrEmpty(_query.where)) ? "" : _query.where;
            sql += (String.IsNullOrEmpty(_query.orderBy)) ? "" : _query.orderBy;
            sql += (String.IsNullOrEmpty(_query.limit)) ? "" : _query.limit;

            _conn.executeDBQuery(sql, _query.columnName, dataTable);
            _query.clear();
            return sql;
        }

        public bool update(Dictionary<string, string> elements)
        {
            //..............................
            string sql = "UPDATE "+tableName+" SET ";
            int index = 1;
            foreach (var value in elements)
            {
                //Sqlite Syntex.
                //sql += value.Key + " = "+ value.Value + (index == elements.Count ? " " : ", ");

                //MYSQL Syntex.
                sql += value.Key + " = '"+ value.Value + "'" + (index == elements.Count ? " " : ", ");
                index++;
            }
            sql += _query.where;

            _conn.executeDBQuery(sql, _query.columnName, dataTable);
            _query.clear();
            return true;
        }

        public bool deleteRow()
        {
            string sql = "DELETE "+ _query.from +_query.where;
            _conn.executeDBQuery(sql, _query.columnName, dataTable);
            _query.clear();
            return false;
        }



        public IQuery select(string[] items)
        {
            _query.select = "SELECT ";
            for (int i = 0; i < items.Length; i++)
            {
                _query.select += items[i] + ((i == items.Length - 1) ? " " : ", ");
                _query.columnName.Add(items[i]);
            }
            return this;
        }
        //......................................................................................
         
        //......................................................................................
        public IQuery where(string columnName, string value, string condition = "=")
        {
            if(string.IsNullOrEmpty(_query.where))
                _query.where = "WHERE "+columnName + condition + value + " ";
            else 
                _query.where += "AND " + columnName + condition + value + " ";

            return this;
        }


        public IQuery orWhere(string columnName, string value, string condition = "=")
        {
            _query.where += "OR " + columnName + condition + value + " ";
            return this;
        }
        //......................................................................................
         
        //......................................................................................
        public IQuery between(string columnName, string value1, string value2)
        {
            if(String.IsNullOrEmpty(_query.where))
                _query.where = "WHERE "+columnName+" BETWEEN "+ value1 +" AND "+ value2 +" ";
            else 
                _query.where += "AND "+columnName+" BETWEEN "+ value1 +" AND "+ value2 +" ";

            return this;
        }

        public IQuery orBetween(string columnName, string value1, string value2)
        {
            _query.where += "OR "+columnName+" BETWEEN "+ value1 +" AND "+ value2 +" ";
            return this;
        }

        public IQuery notBetween(string columnName, string value1, string value2)
        {
            if(String.IsNullOrEmpty(_query.where))
                _query.where = "WHERE "+columnName+" NOT BETWEEN "+ value1 +" AND "+ value2 +" ";
            else 
                _query.where += "AND "+columnName+" NOT BETWEEN "+ value1 +" AND "+ value2 +" ";

            return this;
        }

        public IQuery orNotBetween(string columnName, string value1, string value2)
        {
            _query.where += "OR "+columnName+" NOT BETWEEN "+ value1 +" AND "+ value2 +" ";
            return this;
        }
        //......................................................................................
         
        //......................................................................................
        public IQuery like(string columnName, string pattern)
        {
            if(String.IsNullOrEmpty(_query.where))
                _query.where = "WHERE "+columnName+" LIKE "+ pattern +" ";
            else
                _query.where += "AND "+columnName+" LIKE "+ pattern +" ";

            return this;
        }

        public IQuery orLike(string columnName, string pattern)
        {
            _query.where += "OR "+columnName+" LIKE "+ pattern +" ";
            return this;
        }

        public IQuery notLike(string columnName, string pattern)
        {
            if(String.IsNullOrEmpty(_query.where))
                _query.where = "WHERE "+columnName+" NOT LIKE "+ pattern +" ";
            else
                _query.where += "AND "+columnName+" NOT LIKE "+ pattern +" ";

            return this;
        }

        public IQuery orNotLike(string columnName, string pattern)
        {
            _query.where += "OR "+columnName+" NOT LIKE "+ pattern +" ";
            return this;
        }
        //......................................................................................
         
        //......................................................................................
        public IQuery In(string columnName, string[] item)
        {
            if(String.IsNullOrEmpty(_query.where))
                _query.where = "WHERE " + columnName + " IN(";
            else
                _query.where += "AND " + columnName + " IN(";

            for(int i = 0; i < item.Length; i++)
                _query.where += (i == item.Length -1) ? item[i] : item[i] + ", ";

            _query.where += ") ";
            return this;
        }

        public IQuery orIn(string columnName, string[] item)
        {
            _query.where += "OR " + columnName + " IN(";

            for(int i = 0; i < item.Length; i++)
                _query.where += (i == item.Length -1) ? item[i] : item[i] + ", ";
            _query.where += ") ";
            return this;
        }

        public IQuery notIn(string columnName, string[] item)
        {
            if(String.IsNullOrEmpty(_query.where))
                _query.where = "WHERE " + columnName + " NOT IN(";
            else
                _query.where += "AND " + columnName + " NOT IN(";

            for(int i = 0; i < item.Length; i++)
                _query.where += (i == item.Length -1) ? item[i] : item[i] + ", ";
            _query.where += ") ";
            return this;
        }


        public IQuery orNotIn(string columnName, string[] item)
        {
            _query.where += "OR " + columnName + " NOT IN(";

            for(int i = 0; i < item.Length; i++)
                _query.where += (i == item.Length -1) ? item[i] : item[i] + ", ";
            _query.where += ") ";
            return this;
        }
        //......................................................................................
         
        //......................................................................................
        public IQuery orderBy(string[] item, string order)
        {
            _query.orderBy = "ORDER BY ";
            for(int i = 0; i < item.Length; i++)
                _query.orderBy += item[i] + ((i == item.Length - 1) ? " " : ", ");
            _query.orderBy += order + " ";
            return this;
        }
        //......................................................................................
         
        //......................................................................................
        public IQuery limit(string num1, string num2)
        {
            _query.limit = "LIMIT " + num1 + ((String.IsNullOrEmpty(num2)) ? " " : "," + num2);
            return this;
        }



        public void printData()
        {
            foreach(DataRow dr in dataTable.Rows)
                foreach(string columnName in tableColumnName)
                    Console.WriteLine(columnName + " : " + dr[columnName]);
        }
    }
}
