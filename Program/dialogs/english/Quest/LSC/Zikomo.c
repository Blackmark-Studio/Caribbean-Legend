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
			dialog.text = "What do you want, white man? Zikomo will not talk to you. Talk to Black Eddie. He is the boss.";
			link.l1 = "You don't say!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
