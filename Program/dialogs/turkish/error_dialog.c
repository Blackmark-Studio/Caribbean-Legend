
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
			
			dialog.text = "Dialog dosyası açılırken hata oluştu.";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "Dialog dosyası açılamıyor "+CharacterRef.Dialog.Filename+" bu karaktere atandı.";
			}
			link.l1 = "tamam";
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
