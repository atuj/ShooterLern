// Project Shooter with c++

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterLernEditorTarget : TargetRules
{
	public ShooterLernEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShooterLern" } );
	}
}
