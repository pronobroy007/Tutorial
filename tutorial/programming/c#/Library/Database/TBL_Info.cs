using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DatabaseLibrary;


namespace HoldingTax
{
    struct TabeData
    {
        public string ID;
        public string Name;
        public string Gardient;
        public string House_NO;
        public string VLG;
        public string PARA;
        public string DAYAL;
        public string CHALA;
        public string HA;
        public string YC;
        public string TA;
        public string UPT;
        public string M;

        public void clear()
        {
            ID = "";
            Name = "";
            Gardient = "";
            House_NO = "";
            VLG = "";
            PARA = "";
            DAYAL = "";
            CHALA = "";
            HA = "";
            YC = "";
            TA = "";
            UPT = "";
            M = "";
        }
    }



    class TBL_Info : IQuery
    {
        public TabeData tableData;
        const string _tableName = "Info";

        public TBL_Info(IDBConnection conn) : base(conn, _tableName)
        {
            tableData.clear();
        }

        public void insert()
        {
            string sql = "INSERT INTO "+_tableName+
             " (Name, Gardient, House_No, VLG, PARA, DAYAL, CHALA, HA, YC, TA, UPT, M ) VALUE ('"
                +tableData.Name+"', '"
                +tableData.Gardient+"', '"
                +tableData.House_NO+"', '"
                +tableData.VLG+"', '"
                +tableData.PARA+"', '"
                +tableData.DAYAL+"', '"
                +tableData.CHALA+"', '"
                +tableData.HA+"', '"
                +tableData.YC+"', '"
                +tableData.TA+"', '"
                +tableData.UPT+"', '"
                +tableData.M+"')";

            _conn.executeDBQuery(sql, _query.columnName, dataTable);
            tableData.clear();
        }
    }
}
