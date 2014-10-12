using System;
using Microsoft.Xna.Framework;

namespace SimplerSoccer {

    public class Vector2D {
    
        public static int Sign(Vector2 v1, Vector2 v2) {
            if (v1.Y * v2.X > v1.X * v2.Y) {
                return -1; //anticlockwise
            } else {
                return 1; //clockwise
            }
        }

        public static Vector2 Perp(Vector2 src) {
            return new Vector2(-src.Y, src.X);
        }
    }
}

