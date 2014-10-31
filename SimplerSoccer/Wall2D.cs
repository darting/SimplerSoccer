using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {
    public class Wall2D {
        public Vector2 A { get; set; }

        public Vector2 B{ get; set; }

        public Wall2D(Vector2 a, Vector2 b) {
            A = a;
            B = b;
        }
    }

}

