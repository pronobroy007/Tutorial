using System;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using Human;


namespace PlayerBeh 
{
    class Player : IHuman
    {
        public override void gainHealth()
        {
            health ++;
            Console.WriteLine("Gain Health");
        }


        public override void loseHealth()
        {
            health --;
            Console.WriteLine("Lose Health");
        }


        public override void makeDamage()
        {
            Console.WriteLine("Make Damage");
        }
    }
}

