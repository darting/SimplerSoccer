using System;
using Microsoft.Xna.Framework;

namespace SimplerSoccer {
    public abstract class MovingEntity : BaseGameEntity {
        public MovingEntity(Vector2 position, float radius, Vector2 velocity, float maxSpeed, Vector2 heading, float mass, Vector2 scale, float turnRate, float maxForce)
            : base(NextValidID++) {
            Heading = heading;
            Velocity = velocity;
            Mass = mass;
            Side = Vector2D.Perp(heading);
            MaxSpeed = maxSpeed;
            MaxTurnRate = turnRate;
            MaxForce = maxForce;
            Position = position;
            //boundary/scale
        }

        public bool IsSpeedMaxedOut {
            get { 
                return MaxSpeed * MaxSpeed >= Velocity.LengthSquared();
            }
        }

        public bool RotateHeadingToFacePosition(Vector2 target) {
            var clone = target.Clone();

            var toTarget = clone - Position;
            toTarget.Normalize();

            var dot = MathHelper.Clamp(Vector2.Dot(Heading, toTarget), -1.0f, 1.0f);
            var angle = Math.Acos(dot);
            if (angle < 0.00001)
                return true;
            if (angle > MaxTurnRate)
                angle = MaxTurnRate;
            Matrix matrix = Matrix.CreateRotationZ((float)angle * Vector2D.Sign(Heading, toTarget));
            Vector2.Transform(Heading, matrix);
            Vector2.Transform(Velocity, matrix);
            Side = Vector2D.Perp(Heading);

            return false;
        }

        public Vector2 Velocity{ get; set; }

        public double Speed{ get { return Velocity.Length(); } }

        public double SpeedSquared{ get { return Velocity.LengthSquared(); } }

        private Vector2 heading;

        public Vector2 Heading {
            get{ return heading; }
            set { 
                if (value.LengthSquared() - 1.0 > 0.00001) {
                    throw new ArgumentException();
                }
                heading = value;
                Side = Vector2D.Perp(heading);
            }
        }

        public Vector2 Side{ get; set; }

        public float Mass{ get; set; }

        public float MaxSpeed{ get; set; }

        public float MaxForce{ get; set; }

        public float MaxTurnRate{ get; set; }
    }
}

