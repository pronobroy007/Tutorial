using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    class BT_CheckBBValue<T> : Node
    {
        T _value;
        Node _node;
        string _key;
        BlackBoard _bb;
        bool _equalType;
        ExecutionStage _nodeStage;
        ExecutionStage _returnOnFailure;

        public BT_CheckBBValue(Node node, BlackBoard bb, string key, T value, bool equalType = true, ExecutionStage returnOnFailure = ExecutionStage.FAILUAR) 
        {
            _bb = bb;
            _key = key;
            _node = node;
            _value = value;
            _equalType = equalType;
            _returnOnFailure = returnOnFailure;
        }

        public void reset() => _node.reset();

        public ExecutionStage evaluate()
        {
            if(_bb.getData<T>(_key).Equals(_value) == _equalType)
                _nodeStage = _node.evaluate();
            else 
                _nodeStage = _returnOnFailure;
                
            return _nodeStage;
        }
    }
}
