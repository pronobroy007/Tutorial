using System;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using Human;


namespace PlayerBeh 
{
    class Player : IHuman
    {
        int health;
        public void gainHealth()
        {
            health ++;
            Console.WriteLine("Gain Health");
        }


        public void loseHealth()
        {
            health --;
            Console.WriteLine("Lose Health");
        }


        public void makeDamage()
        {
            Console.WriteLine("Make Damage");
        }
    }
}

