using System;
using Microsoft.Xna.Framework;

namespace SimplerSoccer {
    public class Collision2D {
        public static bool LineIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
            double rTop = (A.Y - C.Y) * (D.X - C.X) - (A.X - C.X) * (D.Y - C.Y);
            double sTop = (A.Y - C.Y) * (B.X - A.X) - (A.X - C.X) * (B.Y - A.Y);
            double bot = (B.X - A.X) * (D.Y - C.Y) - (B.Y - A.Y) * (D.X - C.X);
            if (bot == 0) {
                return false;
            }

            double invBot = 1.0 / bot;
            double r = rTop * invBot;
            double s = sTop * invBot;
            if ((r > 0) && (r < 1) && (s > 0) && (s < 1)) {
                return true;
            }

            return false;
        }
    }
}

