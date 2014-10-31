using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {

    public class SoccerBall : MovingEntity {

        public SoccerBall(Vector2 pos, float ballSize, float mass, List<Wall2D> pitchBoundary)
            : base(pos, ballSize, new Vector2(), -1f, new Vector2(0f, 1f), mass, new Vector2(1f, 1f), 0, 0) {

        }

        public void TestCollisionWithWalls(List<Wall2D> walls) {

        }

        public void PlaceAtPosition(Vector2 newPos) {
            // ???
            Position = newPos;
            OldPosition = Position;
            Velocity.Zero();
        }

        public override void Update() {
        }

        public List<Wall2D> PitchBoundary{ get; set; }

        public Vector2 OldPosition{ get; set; }
    }
}
