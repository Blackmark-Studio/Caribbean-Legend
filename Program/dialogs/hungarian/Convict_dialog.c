// диалог каторжников в шахте
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("Sajnálom, de mindkettônknek jobb lenne, ha nem beszélnénk többet egymással. Meg fognak büntetni, és téged pedig megkérnek, hogy távozz.", "Már mindent elmondtam neked, barátom. Vagy azt akarod, hogy miattad megkorbácsoljanak?", "Nem figyelek...", "A spa-ade lecsap és klán-angolja a csákányt...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Kemény szabályok vannak itt...", "Nem, természetesen nem akarom.", "Hmmm...", "Papa, hallasz engem...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Kapitány, mit csinálsz? Rejtsd el a fegyvered, mielôtt nagy bajba kerülsz!";
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ne aggódj, elrejtem...");
			link.l1.go = "exit";
		break;  
	}
}
