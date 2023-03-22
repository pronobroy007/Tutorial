using System;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using PlayerBeh;


namespace ConsoleApplication
{
    interface Program
    {
        static void Main(string[] argv)
        {
            Player mainPlayer = new Player();            
            mainPlayer.gainHealth();
            mainPlayer.loseHealth();
            mainPlayer.makeDamage();
        }
    }
}

