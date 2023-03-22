using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    class BT_Reset : Node
    {
        Node _node;

        public BT_Reset(Node node) => _node = node;

        public void reset() {}

        public ExecutionStage evaluate()
        {
            _node.reset();
            return ExecutionStage.SUCCESS;
        }

    }


    class BT_AddToReference : Node
    {
        Node _node;
        RootNode _rootNode;

        public BT_AddToReference(RootNode rootNode, Node node) 
        {
            _node = node;
            _rootNode = rootNode;
        }

        public void reset() {}

        public ExecutionStage evaluate()
        {
            _rootNode.addReferenceNode(_node);
            return ExecutionStage.SUCCESS;
        }

    }
}
