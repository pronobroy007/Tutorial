using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    public class BT_ConvertToRunning : Node
    {
        Node _node;
        ExecutionStage _nodeStage, _convertFrom;

        public BT_ConvertToRunning(Node node, ExecutionStage convertFrom) 
        {
            _node = node;
            _convertFrom = convertFrom;
        }

        public void reset() {}

        public ExecutionStage evaluate()
        {
            _nodeStage = _node.evaluate();

            if(_nodeStage == _convertFrom)
                _nodeStage = ExecutionStage.RUNNING;

            return _nodeStage;
        }
    }
}
