using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {
    public class SoccerTeam {

        public Goal HomeGoal{ get; set; }

        public Goal OpponentGoal{ get; set; }

        public SoccerPitch Pitch{ get; set; }

        public SoccerColor Color{ get; set; }

        public SoccerTeam Opponents { get; set; }


        public SoccerTeam(Goal homeGoal, Goal opponentGoal, SoccerPitch pitch, SoccerColor color) {
            HomeGoal = homeGoal;
            OpponentGoal = opponentGoal;
            Pitch = pitch;
            Color = color;
        }

        public void Update() {
        }

        public enum SoccerColor {
            Red,
            Blue
        }

    }

}

