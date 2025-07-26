
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------第一个对话 - 初次见面
		case "First time":
			
			dialog.text = "打开对话文件时出错。 ";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "无法打开分配给此角色的对话文件 " + CharacterRef.Dialog.Filename + "。 ";
			}
			link.l1 = "ok";
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}