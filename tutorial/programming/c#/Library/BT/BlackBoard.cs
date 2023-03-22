using System.Collections.Generic;


namespace BTLibrary
{
    class BlackBoard
    {
        Dictionary <string, object> _data = new Dictionary<string, object>();

        public void createData<T>(string key, T value) => _data.Add(key, value);
        public void setData<T>(string key, T value) => _data[key] = value;
        public T getData<T>(string key) => (T)_data[key];
    }
}

