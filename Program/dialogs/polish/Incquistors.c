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
		case "First time":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
					dialog.text = RandPhraseSimple("Bracia, w szeregach Inkwizycji jest wróg!","Podnieść alarm, bracia!");
					link.l1 = "Rzeczywiście, wrogowie Inkwizycji już tu są...";
					link.l1.go = "fight";			
			}
			else
			{	
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Witaj, "+GetSexPhrase("mój synu","moja córko")+". Co cię tu przyprowadziło?..","Cieszę się, że cię widzę w naszym domostwie, "+GetSexPhrase("mój synu","moja córko")+". . Co cię tu przyprowadziło?"),""+GetSexPhrase("Mój synu","Moja córko")+", już rozmawialiśmy dzisiaj. Czy potrzebujesz czegoś jeszcze?",""+GetSexPhrase("Mój synu","Moja córko")+", akolici naszego zakonu nie są znani z nieskończonej cierpliwości. Więc pozwól mi zapytać cię jeszcze raz: czy jest coś, czego potrzebujesz?",RandPhraseSimple("Rozpraszasz innych od ich obowiązków. Nie zamierzam już z tobą rozmawiać.",""+GetSexPhrase("Mój synu","Moja córko")+", Nie lubię bezsensownych i bezcelowych rozmów. Nie zamierzam już z tobą rozmawiać."),"block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Tak tylko wpadłem..","Całkiem pełno interesów..."),"O nie, Ojcze......","Nie, Ojcze, tylko chciałem porozmawiać...",RandPhraseSimple("Hmm...","Cóż, jak sobie życzysz, Ojcze..."),npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);				
			}
			if (CheckAttribute(npchar, "protector.CheckAlways")) //гарды на камерах
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{					
					dialog.text = "Do broni! To szpieg! Łapcie go!";
					link.l1 = "Cholera!";
					link.l1.go = "fight";
				}
				else
				{
					dialog.text = LinkRandPhrase("To jest strzeżona cela. Wejście do środka będzie traktowane jako wtargnięcie.","Nawet nie myśl o wchodzeniu, jest to karane śmiercią.","Postaw choćby jeden krok w tej celi i jesteś skończony.");
					link.l1 = RandPhraseSimple("Rozumiem, żołnierzu.","Rozumiem...");	
					link.l1.go = "exit";
				}
			}
			if (findsubstr(npchar.id, "Prisoner", 0) != -1) //заключенные
			{
				if (LAi_group_IsActivePlayerAlarm())
				{
					dialog.text = LinkRandPhrase("Ho-ho, czy to nie zabawne obserwować jak ci 'święci' idą prosto do piekła?!","O mój Boże, czy ktoś naprawdę odważył się ich wyzwać?!","Zatrudzili mnie prawie na śmierć, i niedługo umrę, ale sprawiłeś mi ostatni raz w życiu radość...");
					link.l1 = RandPhraseSimple("Heh!","Nie ma za co...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("Ci hipokryci są zupełnie nieludzcy. Spłoną w piekle za wszystko, co nam zrobili...","Męczyli i dręczyli mnie każdego dnia! Ale wobec naszego Pana jestem niewinny!","Mój współwięzień zmarł wczoraj... Torturowali go na wieszadle przez dwa dni... Kto wie, jak długo ja wytrzymam...");
					link.l1 = RandPhraseSimple("Hmm... nie wiem...","Ach, rozumiem...");
					link.l1.go = "exit";
				}
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
	}
}
