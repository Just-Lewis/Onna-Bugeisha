// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class OnnaBugeishaEditorTarget : TargetRules
{
	public OnnaBugeishaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "OnnaBugeisha" } );
	}
}
