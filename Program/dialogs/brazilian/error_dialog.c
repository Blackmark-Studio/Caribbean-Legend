
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
			
			dialog.text = "Erro ao abrir o arquivo de diálogo.";
			if(CheckAttribute(CharacterRef, "Dialog.Filename"))
			{
				dialog.text = "Não foi possível abrir o arquivo de diálogo "+CharacterRef.Dialog.Filename+" atribuído a este personagem.";
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
