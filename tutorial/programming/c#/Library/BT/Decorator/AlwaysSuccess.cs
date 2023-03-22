using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    public class BT_AlwaysSuccess : Node
    {
        Node _node;
        ExecutionStage _nodeStage;

        public BT_AlwaysSuccess(Node node) => _node = node;

        public void reset() {}

        public ExecutionStage evaluate()
        {
            switch(_node.evaluate())
            {
                case ExecutionStage.RUNNING :
                    _nodeStage = ExecutionStage.RUNNING;
                    break;

                case ExecutionStage.SUCCESS :
                    _nodeStage = ExecutionStage.SUCCESS;
                    break;

                case ExecutionStage.FAILUAR :
                    _nodeStage = ExecutionStage.SUCCESS;
                    break;
            }

            return _nodeStage;
        }
    }
}
