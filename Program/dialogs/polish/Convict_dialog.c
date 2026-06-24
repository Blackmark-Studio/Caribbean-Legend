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
			dialog.text = NPCStringReactionRepeat("Przykro mi, ale lepiej będzie dla nas obu, jeśli już nie będziemy ze sobą rozmawiać. Oni mnie ukarzą, a ciebie poproszą o wyjście.","Już ci wszystko powiedziałem, przyjacielu. Czy chcesz, żebym był chłostany przez ciebie?","Nie słucham...","Miecz uderza i klan-gi wybierają...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ciężkie zasady macie tutaj...","Nie, oczywiście, nie chcę tego.","Hmmm...","Tato, czy mnie słyszysz...",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Kapitanie, co robisz? Schowaj swoją broń, zanim narobisz dużo kłopotów!";
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Nie martw się, chowam to...");
			link.l1.go = "exit";
		break;  
	}
}
