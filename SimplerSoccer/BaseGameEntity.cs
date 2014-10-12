using System;
using Microsoft.Xna.Framework;

namespace SimplerSoccer {
    public abstract class BaseGameEntity {
        public static int NextValidID;

        public static void ResetNextValidID() {
            NextValidID = 0;
        }

        public BaseGameEntity(int id) {
            ID = id;
        }

        public abstract void Update();

        public virtual bool HandleMessage(Telegram msg) {
            return false;
        }

        public int ID{ get; set; }

        public int Type{ get; set; }

        public bool Tagged{ get; set; }

        public Vector2 Position{ get; set; }

//        public Vector2 Scale{ get; set; }
//
//        public float BoundingRadius{ get; set; }
    }
}

