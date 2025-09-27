
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
			
			dialog.text = "Hiba a párbeszédpanel fájl megnyitásakor.";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "Nem lehet megnyitni a " + CharacterRef.Dialog.Filename + " párbeszédpanel fájlt, amely ehhez a karakterhez van rendelve.";
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
