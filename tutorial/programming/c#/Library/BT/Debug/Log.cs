using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    class Log : Node
    {
        Node _node;
        string _msg;
        ExecutionStage _nodeStage;

        public Log(Node node, string msg = "null") 
        {
            _node = node;
            _msg = (msg == "null") ? "Node" : msg;
        }

        public void reset() {}

        public ExecutionStage evaluate()
        {
            _nodeStage = _node.evaluate();
            Debug.Log(_msg + "    :   " + _nodeStage);
            return _nodeStage;
        }
    }


    public class LogSuccess : Node
    {
        Node _node;
        ExecutionStage _nodeStage;

        public LogSuccess(Node node) 
        {
            _node = node;
        }

        public void reset() {}

        public ExecutionStage evaluate()
        {
            _nodeStage = _node.evaluate();
            if(_nodeStage == ExecutionStage.SUCCESS)
                Debug.Log("Node    :   " + _nodeStage);
            return _nodeStage;
        }
    }


    public class LogFailuar : Node
    {
        Node _node;
        ExecutionStage _nodeStage;

        public LogFailuar(Node node) 
        {
            _node = node;
        }

        public void reset() {}

        public ExecutionStage evaluate()
        {
            _nodeStage = _node.evaluate();
            if(_nodeStage == ExecutionStage.FAILUAR)
                Debug.Log("Node    :   " + _nodeStage);
            return _nodeStage;
        }
    }
}
