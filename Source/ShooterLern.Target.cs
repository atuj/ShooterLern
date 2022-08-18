// Project Shooter with c++

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterLernTarget : TargetRules
{
	public ShooterLernTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShooterLern" } );
	}
}
