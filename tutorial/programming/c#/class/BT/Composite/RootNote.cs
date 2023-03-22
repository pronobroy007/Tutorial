using System.Collections;
using System.Collections.Generic;


namespace BTLibrary
{
    class RootNode : Node
    {
        Node _node;
        Node _resetNode;
        ExecutionStage _nodeStage;

        public RootNode() {}

        public RootNode(Node node, bool wait = false) 
        {
            if(wait == false)
                _node = node;
            else
                _node = new Sequence(new List<Node>{new BT_Wait(0.4f), node});
        }

        public void addReferenceNode(Node node) => _resetNode = node;
        public void reset() => _resetNode?.reset();

        public ExecutionStage evaluate()
        {
            switch(_node.evaluate())
            {
                case ExecutionStage.RUNNING :
                    _nodeStage = ExecutionStage.RUNNING;
                    break;

                case ExecutionStage.SUCCESS:
                    _nodeStage = ExecutionStage.SUCCESS;
                    break;

                case  ExecutionStage.FAILUAR :
                    _nodeStage = ExecutionStage.FAILUAR;
                    break;
            }

            return _nodeStage;
        }
    }

    public class AggressiveRootNode : Node
    {
        Node _node;
        ExecutionStage _nodeStage;

        public AggressiveRootNode(Node node) => _node = node;

        public void reset() {}

        public ExecutionStage evaluate()
        {
            while(true)
            {
                switch(_node.evaluate())
                {
                    case ExecutionStage.RUNNING :
                        _nodeStage = ExecutionStage.RUNNING;
                        break;

                    case ExecutionStage.SUCCESS:
                        _nodeStage = ExecutionStage.SUCCESS;
                        return _nodeStage;

                    case  ExecutionStage.FAILUAR :
                        _nodeStage = ExecutionStage.FAILUAR;
                        return _nodeStage;
                }
            }
        }
    }
}
