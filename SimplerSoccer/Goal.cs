using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {
    public class Goal {

        public Goal(Vector2 left, Vector2 right, Vector2 facing) {
            LeftPost = left;
            RightPost = right;
            Center = (left + right) / 2f;
            NumGoalsScored = 0;
            Facing = facing;
        }

        public bool Scored(SoccerBall ball) {
            if (Collision2D.LineIntersection(ball.Position, ball.OldPosition, LeftPost, RightPost)) {
                NumGoalsScored++;
                return true;
            }
            return false;
        }

        public void ResetGoalsScored() {
            NumGoalsScored = 0;
        }

        public Vector2 LeftPost{ get; set; }

        public Vector2 RightPost{ get; set; }

        public Vector2 Facing{ get; set; }

        public Vector2 Center{ get; set; }

        public int NumGoalsScored{ get; set; }
    }
}

