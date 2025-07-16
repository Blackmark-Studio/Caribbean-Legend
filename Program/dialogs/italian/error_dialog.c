
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
			
			dialog.text = "Errore nell'apertura del file di dialogo.";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "Impossibile aprire il file di dialogo "+CharacterRef.Dialog.Filename+" assegnato a questo personaggio.";
			}
			link.l1 = "va bene";
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
