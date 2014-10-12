using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {
    public class Region {

        public Region(float left, float top, float right, float bottom, int id = -1) {
            Left = left;
            Top = top;
            Right = right;
            Bottom = bottom;
            Center = new Vector2((left + right) * 0.5f, (top + bottom) * 0.5f);
            Width = Math.Abs(right - left);
            Height = Math.Abs(bottom - top);
            ID = id;
        }

        public bool Inside(Vector2 pos, RegionModifier modifier) {
            if (modifier == RegionModifier.Normal) {
                return ((pos.X > Left) && (pos.X < Right) && (pos.Y > Top) && (pos.Y < Bottom));
            } else {
                double marginX = Width * 0.25;
                double marginY = Height * 0.25;
                return ((pos.X > (Left + marginX)) && (pos.X < (Right - marginX)) &&
                (pos.Y > (Top + marginY)) && (pos.Y < (Bottom - marginY)));
            }
        }

        public Vector2 GetRandomPosition() {
            var rand = new RandomGenerator();
            return new Vector2(rand.InRange(Left, Right), rand.InRange(Top, Bottom));
        }

        public float Left { get; set; }

        public float Top{ get; set; }

        public float Right{ get; set; }

        public float Bottom{ get; set; }

        public Vector2 Center { get; set; }

        public float Width{ get; protected set; }

        public float Height{ get; protected set; }

        public int ID{ get; set; }

        public enum RegionModifier {
            HalfSize,
            Normal
        }
    }

}

