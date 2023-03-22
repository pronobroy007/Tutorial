using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    class BT_BBRepeater : Node
    {
        Node _node;
        BlackBoard _bb;
        string _bbRepeaterKey;
        ExecutionStage _nodeStage;

        public BT_BBRepeater(Node node, BlackBoard bb, string bbRepeaterKey) 
        {
            _bb = bb;
            _node = node;
            _bbRepeaterKey = bbRepeaterKey;
        }

        public void reset() => _node.reset();

        public ExecutionStage evaluate()
        {
            int totalIteration = _bb.getData<int>(_bbRepeaterKey);
            if(totalIteration <= 0) return ExecutionStage.FAILUAR;

            _nodeStage = _node.evaluate();
            if(_nodeStage != ExecutionStage.RUNNING)
            {
                totalIteration --;
                _bb.setData<int>(_bbRepeaterKey, totalIteration);

                if(totalIteration > 0)
                    _nodeStage = ExecutionStage.RUNNING;
                else
                    _nodeStage = ExecutionStage.SUCCESS;
            }

            return _nodeStage;
        }
    }


    class BT_Repeater : Node
    {
        Node _node;
        ExecutionStage _nodeStage;
        int _amount, _totalIteration;

        public BT_Repeater(Node node, int anount = 0) 
        {
            _node = node;
            _amount = anount;
            _totalIteration = 0;
        }

        public void reset() => _node.reset();

        public ExecutionStage evaluate()
        {
            _nodeStage = _node.evaluate();
            if(_nodeStage != ExecutionStage.RUNNING)
            {
                _totalIteration ++;

                if(_totalIteration == _amount)
                {
                    _totalIteration = 0;
                    _nodeStage = ExecutionStage.SUCCESS;
                }
                else
                    _nodeStage = ExecutionStage.RUNNING;
            }

            return _nodeStage;
        }
    }
}
