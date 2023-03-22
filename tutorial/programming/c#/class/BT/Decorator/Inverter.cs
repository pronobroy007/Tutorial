using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    public class Inveter : Node
    {
        Node _node;
        ExecutionStage _nodeStage;

        public Inveter(Node node) => _node = node;

        public void reset() {}

        public ExecutionStage evaluate()
        {
            switch(_node.evaluate())
            {
                case ExecutionStage.RUNNING :
                    _nodeStage = ExecutionStage.RUNNING;
                    break;

                case ExecutionStage.SUCCESS :
                    _nodeStage = ExecutionStage.FAILUAR;
                    break;

                case ExecutionStage.FAILUAR :
                    _nodeStage = ExecutionStage.SUCCESS;
                    break;
            }

            return _nodeStage;
        }
    }
}
