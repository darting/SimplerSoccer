using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {

    public class SoccerBall {

        public SoccerBall(Vector2 pos, float ballSize, float mass, List<Wall2D> pitchBoundary) {

        }

        public void TestCollisionWithWalls(List<Wall2D> walls) {

        }

        public List<Wall2D> PitchBoundary{ get; set;}
        public Vector2 OldPos{get;set;}
    }
}
