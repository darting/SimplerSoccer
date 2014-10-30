using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;

namespace SimplerSoccer {
	public class SoccerPitch {

		private const int NumRegionsHorizontal = 6;
		private const int NumRegionsVertical = 3;

        public Region[] regions;
		public SoccerTeam redTeam;
		public SoccerTeam blueTeam;
		public Goal redGoal;
		public Goal blueGoal;

		private SoccerBall ball;


		public SoccerPitch(int cx, int cy) {
			ClientX = cx;
			ClientY = cy;
			PlayingArea = new Region(20, 20, cx - 20f, cy - 20f);

            regions = new Region[NumRegionsHorizontal * NumRegionsVertical];
			CreateRegions(PlayingArea.Width / (float)NumRegionsHorizontal, PlayingArea.Height / (float)NumRegionsVertical);

			redGoal = new Goal(new Vector2(PlayingArea.Left, (cy - Configuration.GoalWidth) / 2f), 
				new Vector2(PlayingArea.Left, cy - (cy - Configuration.GoalWidth) / 2f), 
				new Vector2(1, 0));

			blueGoal = new Goal(new Vector2(PlayingArea.Right, (cy - Configuration.GoalWidth) / 2f),
				new Vector2(PlayingArea.Right, cy - (cy - Configuration.GoalWidth) / 2f),
				new Vector2(-1, 0));

			ball = new SoccerBall(new Vector2(ClientX / 2.0f, ClientY / 2.0f), Configuration.BallSize, Configuration.BallMass, Walls);

			redTeam = new SoccerTeam(redGoal, blueGoal, this, SoccerTeam.SoccerColor.Red);
			blueTeam = new SoccerTeam(blueGoal, redGoal, this, SoccerTeam.SoccerColor.Blue);

			redTeam.Opponents = blueTeam;
			blueTeam.Opponents = redTeam;

			// walls
			var topLeft = new Vector2(PlayingArea.Left, PlayingArea.Top);
			var topRight = new Vector2(PlayingArea.Right, PlayingArea.Top);
			var bottomRight = new Vector2(PlayingArea.Right, PlayingArea.Bottom);
			var bottomLeft = new Vector2(PlayingArea.Left, PlayingArea.Bottom);

            Walls = new List<Wall2D>();
			Walls.Add(new Wall2D(bottomLeft, redGoal.RightPost));
			Walls.Add(new Wall2D(redGoal.LeftPost, topLeft));
			Walls.Add(new Wall2D(topLeft, topRight));
			Walls.Add(new Wall2D(topRight, blueGoal.LeftPost));
			Walls.Add(new Wall2D(blueGoal.RightPost, bottomRight));
			Walls.Add(new Wall2D(bottomRight, bottomLeft));
		}

		public void Update() {
			if (Paused)
				return;

            ball.Update();
            redTeam.Update();
            blueTeam.Update();

			if (blueGoal.Scored(ball) || redGoal.Scored(ball)) {
				GameOn = false;

				ball.PlaceAtPosition(new Vector2(ClientX / 2.0f, ClientY / 2.0f));

				//redTeam.FSM.ChangeState(new PrepareForKickOff());
				//blueTeam.FSM.ChangeState(new PrepareForKickOff());
			}
		}

        public void CreateRegions(float width, float height) {
			var idx = regions.Length - 1;
			for (var col = 0; col < NumRegionsHorizontal; col++) {
				for (var row = 0; row < NumRegionsVertical; row++) {
					regions[idx--] = new Region(PlayingArea.Left + col * width,
						PlayingArea.Top + row * height,
						PlayingArea.Left + (col + 1) * width,
						PlayingArea.Top + (row + 1) * height);
				}
			}
		}

		public void TogglePause() {
			Paused = !Paused;
		}

		public void Update(GameTime gameTime) {

		}

		public Region GetRegionFromIndex(int idx) {
			if (regions.Length <= idx)
				throw new IndexOutOfRangeException();
			return regions[idx];
		}

		public bool GameOn {
			get;
			set;
		}

		public Region PlayingArea {
			get;
			protected set;
		}

		public List<Wall2D> Walls {
			get;
			protected set;
		}

		public SoccerBall Ball {
			get;
			protected set;
		}

		public bool GoalKeeperHasBall {
			get;
			set;
		}

		public bool Paused {
			get;
			set;
		}

		public int ClientX {
			get;
			protected set;
		}

		public int ClientY {
			get;
			protected set;
		}
	}
}

