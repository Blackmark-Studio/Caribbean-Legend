// телохранитель лидера ривадос Эдди - Зикомо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você quer, homem branco? Zikomo não vai falar com você. Fale com o Eddie Preto. Ele é o chefe.";
			link.l1 = "Não me diga!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
