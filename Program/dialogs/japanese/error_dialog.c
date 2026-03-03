
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
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			
			dialog.text = "ダイアログファイルの読み込みエラー。";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "ダイアログファイルを開けません "+CharacterRef.Dialog.Filename+" このキャラクターに割り当てられている。";
			}
			link.l1 = "了解";
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
