using System.Collections;
using System.Collections.Generic;


namespace BTLibrary
{
    class Selector : Node
    {
        int _currentIndex = 0;
        ExecutionStage _nodeStage;

        List<Node> _nodes = new List<Node>();
        //.....................................
        //  while(true) 
        //    pointer _ptr = _nodes[i]
        //          SUCCESS 
        //              -> reset _ptr
        //              -> return SUCCESS
        //    
        //          FAILUAR
        //              -> i++
        //              -> return RUNNING
        //    
        //          RUNNING
        //              -> return RUNNING
        //
        //  if(_ptr == _nodes.count)
        //      -> reset _ptr
        //      -> return FAILUAR
        //......................................

        public Selector(List<Node> nodes) => _nodes = nodes;

        public void reset()
        {
            _currentIndex = 0;
            foreach(Node n in _nodes) n.reset();
        }

        public ExecutionStage evaluate()
        {
            switch(_nodes[_currentIndex].evaluate())
            {
                case ExecutionStage.RUNNING :
                    //do nothing return................
                    _nodeStage = ExecutionStage.RUNNING;
                    return _nodeStage;

                case ExecutionStage.SUCCESS:
                    _currentIndex = 0;
                    //Exit Sequence Node As SUCCESS.
                    _nodeStage = ExecutionStage.SUCCESS;
                    return _nodeStage;

                case ExecutionStage.FAILUAR :
                    _currentIndex ++;
                    //Exit Sequence Node As FAILUAR.
                    if(_currentIndex == _nodes.Count) 
                    {
                        _currentIndex = 0;
                        _nodeStage = ExecutionStage.FAILUAR;
                        return _nodeStage;
                    }
                    _nodeStage = ExecutionStage.RUNNING;
                    return _nodeStage;

                default :
                    _nodeStage = ExecutionStage.RUNNING;
                    return _nodeStage;
            }
        }
    }
}
