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
			dialog.text = "Mit akarsz, fehér ember? Zikomo nem beszél veled. Beszélj Fekete Eddie-vel. Ô a fônök.";
			link.l1 = "Ne mondd ezt!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
