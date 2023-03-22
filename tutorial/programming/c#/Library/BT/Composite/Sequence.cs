using System.Collections;
using System.Collections.Generic;

namespace BTLibrary
{
    class Sequence : Node
    {
        int _currentIndex = 0;
        ExecutionStage _nodeStage;

        List<Node> _nodes = new List<Node>();

        public Sequence(List<Node> nodes) => _nodes = nodes;
        //.....................................
        //  while(true) 
        //    pointer _ptr = _nodes[i]
        //          SUCCESS 
        //              -> i++
        //    
        //          FAILUAR
        //              -> reset _ptr
        //              -> return FAILUAR
        //    
        //          RUNNING
        //              -> return RUNNING
        //
        //  if(_ptr == _nodes.count)
        //      -> reset _ptr
        //      -> return SUCCESS
        //......................................
        

        public void reset()
        {
            _currentIndex = 0;
            foreach(Node n in _nodes) n.reset();
        }

        public ExecutionStage evaluate()
        {
            ExecutionStage ns = _nodes[_currentIndex].evaluate();
            switch(ns)
            {
                case ExecutionStage.RUNNING :
                    //do nothing return................
                    _nodeStage = ExecutionStage.RUNNING;
                    return _nodeStage;

                case ExecutionStage.SUCCESS:
                    _currentIndex ++;
                    //Exit Sequence Node As SUCCESS.
                    if(_currentIndex == _nodes.Count) 
                    {
                        _currentIndex = 0;
                        _nodeStage = ExecutionStage.SUCCESS;
                        return _nodeStage;
                    }
                    _nodeStage = ExecutionStage.RUNNING;
                    return _nodeStage;

                case ExecutionStage.FAILUAR :
                    //Exit Sequence Node As FAILUAR.
                    _currentIndex = 0;
                    _nodeStage = ExecutionStage.FAILUAR;
                    return _nodeStage;

                default :
                    _nodeStage = ExecutionStage.RUNNING;
                    return _nodeStage;
            }
        }//End of evaluate()
    }
}
