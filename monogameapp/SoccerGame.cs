using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using SimplerSoccer;

namespace monogameapp {
	/// <summary>
	/// This is the main type for your game
	/// </summary>
	public class SoccerGame : Game {
		GraphicsDeviceManager graphics;
		SpriteBatch spriteBatch;

		SoccerPitch soccerPitch;

		private Texture2D soccerField;

		public SoccerGame() {
			graphics = new GraphicsDeviceManager(this);
			graphics.PreferredBackBufferWidth = 800;
			graphics.PreferredBackBufferHeight = 600;
			graphics.ApplyChanges();
			Content.RootDirectory = "Content";
		}

		/// <summary>
		/// Allows the game to perform any initialization it needs to before starting to run.
		/// This is where it can query for any required services and load any non-graphic
		/// related content.  Calling base.Initialize will enumerate through any components
		/// and initialize them as well.
		/// </summary>
		protected override void Initialize() {
			// TODO: Add your initialization logic here
			var viewport = graphics.GraphicsDevice.Viewport;

			soccerPitch = new SoccerPitch(new Rectangle(10, 10, viewport.Width - 20, viewport.Height - 20));

			base.Initialize();
		}

		/// <summary>
		/// LoadContent will be called once per game and is the place to load
		/// all of your content.
		/// </summary>
		protected override void LoadContent() {
			// Create a new SpriteBatch, which can be used to draw textures.
			spriteBatch = new SpriteBatch(GraphicsDevice);

			// TODO: use this.Content to load your game content here
			soccerField = Content.Load<Texture2D>("soccer_field");
		}

		/// <summary>
		/// UnloadContent will be called once per game and is the place to unload
		/// all content.
		/// </summary>
		protected override void UnloadContent() {
			// TODO: Unload any non ContentManager content here
		}

		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update(GameTime gameTime) {
			// TODO: Add your update logic here
			soccerPitch.Update(gameTime);

			base.Update(gameTime);
		}

		/// <summary>
		/// This is called when the game should draw itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Draw(GameTime gameTime) {
			GraphicsDevice.Clear(Color.CornflowerBlue);

			// TODO: Add your drawing code here
			var screenWidth = Window.ClientBounds.Width;
			var screenHeight = Window.ClientBounds.Height;
			var rectangle = new Rectangle(0, 0, screenWidth, screenHeight);

			spriteBatch.Begin();

			// field
			spriteBatch.Draw(soccerField, rectangle, Color.White);

			//regions

			//goals

			//pitch markings

			//the ball

			//the teams

			//the walls

			//score


			spriteBatch.End();


			base.Draw(gameTime);
		}
	}
}
