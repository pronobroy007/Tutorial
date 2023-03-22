using System;
using System.Linq;
using System.Text;
using System.Collections.Generic;


namespace Human
{
    abstract class IHuman
    {
        public int health;
        public abstract void gainHealth();
        public abstract void loseHealth();
        public abstract void makeDamage();
    }
}
