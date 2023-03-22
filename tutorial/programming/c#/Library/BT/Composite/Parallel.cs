using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace BTLibrary
{
    public class Parallel : Node
    {
        ExecutionStage _nodeStage;
        protected List<Node> _nodes = new List<Node>();

        public Parallel(List<Node> nodes) => _nodes = nodes;

        public void reset() {}

        public ExecutionStage evaluate()
        {
            foreach(Node n in _nodes)
            {
                switch(n.evaluate())
                {
                    case ExecutionStage.RUNNING :
                        break;

                    case ExecutionStage.SUCCESS:
                        _nodeStage = ExecutionStage.SUCCESS;
                        return ExecutionStage.SUCCESS;

                    case ExecutionStage.FAILUAR :
                        _nodeStage = ExecutionStage.FAILUAR;
                        return ExecutionStage.FAILUAR;
                }
            } 

            return ExecutionStage.RUNNING;
        }

    }

    //If one success then sotp evaluate.
    class ParallelSuccess : Node
    {
        ExecutionStage _nodeStage;
        protected List<Node> _nodes = new List<Node>();

        public ParallelSuccess(List<Node> nodes) => _nodes = nodes;

        public void reset() {}

        public ExecutionStage evaluate() 
        { 
            foreach(Node n in _nodes)
            {
                switch(n.evaluate())
                {
                    case ExecutionStage.RUNNING :
                        break;

                    case ExecutionStage.SUCCESS:
                        _nodeStage = ExecutionStage.SUCCESS;
                        return ExecutionStage.SUCCESS;

                    case ExecutionStage.FAILUAR :
                        break;
                }
            } 

            return ExecutionStage.RUNNING;
        }
    }



    //If one fail then sotp evaluate.
    class ParallelFailure : Node
    {
        ExecutionStage _nodeStage;
        protected List<Node> _nodes = new List<Node>();

        public ParallelFailure(List<Node> nodes) => _nodes = nodes;

        public void reset() {}

        public ExecutionStage evaluate() 
        { 
            foreach(Node n in _nodes)
            {
                switch(n.evaluate())
                {
                    case ExecutionStage.RUNNING :
                        break;

                    case ExecutionStage.SUCCESS:
                        break;

                    case ExecutionStage.FAILUAR :
                        _nodeStage = ExecutionStage.FAILUAR;
                        return ExecutionStage.FAILUAR;
                }
            } 

            return ExecutionStage.RUNNING;
        }
    }
}
