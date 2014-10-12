#region Using Statements
using System;
using MonoMac.AppKit;
using MonoMac.Foundation;
#endregion

namespace monogameapp
{
	class Program
	{
		static void Main (string[] args)
		{
			NSApplication.Init ();

			using (var p = new NSAutoreleasePool ()) {
				NSApplication.SharedApplication.Delegate = new AppDelegate ();

				// Set our Application Icon
				NSImage appIcon = NSImage.ImageNamed ("Icon.png");
				NSApplication.SharedApplication.ApplicationIconImage = appIcon;

				NSApplication.Main (args);
			}
		}
	}

	class AppDelegate : NSApplicationDelegate
	{
		private SoccerGame game;

		public override void FinishedLaunching (MonoMac.Foundation.NSObject notification)
		{
			game = new SoccerGame();
			game.Run();
		}

		public override bool ApplicationShouldTerminateAfterLastWindowClosed (NSApplication sender)
		{
			return true;
		}
	}
}