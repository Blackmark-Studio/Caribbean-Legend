// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czy chcesz coś?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Whoa-ho, popatrz kto tu jest! No cóż, dzisiaj jest twój szczęśliwy dzień, kumplu. Jesteśmy dobrzy, widzisz, gotujemy jedzenie i tak dalej... Nie zapraszam cię na naszą kolację, ale powinieneś zniknąć póki jeszcze możesz.","Znikaj teraz i nas nie przeszkadzaj. Wróć jutro - i nie zapomnij przynieść ze sobą swojego portfela, ha-ha-ha!","Nie denerwuj mnie, marynarzu! Czy nadal pamiętasz, gdzie jest wejście do jaskini? Powinieneś tam teraz iść, bardzo, bardzo szybko...","No cóż, teraz przekroczyłeś granicę, kumplu! Chyba będę musiał oderwać się od moich spraw i zająć tobą, dupku!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Bardzo miło z twojej strony, kumplu...","Widzę, że jesteś całkiem żartownisiem...","Dobrze, nadal smaż swoje placki, wtedy...","Teraz rozmawiamy, ha-ha!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("O rety, na Boga! Nie ma potrzeby polować na zdobycz - ona już tu jest... Hej, chłopaki - potrząśnijmy tym fircykiem, co?","Nikt cię tu nie zaprosił, kumplu... Ale dobrze, że jednak jesteś. Zobaczmy teraz, jak ciężki jest twój sakiewka!","Nikt cię tutaj na siłę nie ciągnął, he-he... Ale skoro już tu jesteś, chyba trochę cię pożartujemy, żeby zobaczyć, co ci z kieszeni wypadnie...");
				link.l1 = LinkRandPhrase("Teraz trochę skrócę twój język...","Mam nadzieję, że twoje umiejętności szermierki dorównują twojemu dowcipowi, gadatliwy!","Cóż, wygląda na to, że nadszedł czas, aby zrobić kilka dodatkowych dziur w twoim znikomym ciele...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("O rety, na Boga! Nie ma potrzeby polować na zdobycz - ona jest już tutaj... Hej, chłopaki - potrząśnijmy tym fircykiem, co wy na to?","Nikt cię tu nie zaprosił, kolego... Ale to tak dobrze, że tu jesteś, tak czy inaczej. Zobaczmy teraz, jak ciężka jest twoja sakiewka!","Nikt cię tu siłą nie ciągnął, he-he... Ale skoro już tu jesteś, chyba trochę cię pośwędzimy, żeby zobaczyć, co ci z kieszeni wypadnie...");
			link.l1 = LinkRandPhrase("Teraz trochę skrócę twój język...","Mam nadzieję, że twoje umiejętności szermierki dorównują twojemu dowcipowi, gadatliwy!","Cóż, wygląda na to, że nadszedł czas, aby zrobić kilka dodatkowych dziur w twoim przemijającym ciele...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Spadaj, kumplu. Nie ma tu dla ciebie nic do roboty!","Hej, pytam w przyjazny sposób: spadaj. Nigdy nie wiadomo, co może się zdarzyć...","Ostatnie ostrzeżenie: jeśli teraz nie znikniesz, pożałujesz, że tu przyszedłeś.","To jest to, kumpel, poprosiłeś o kłopoty.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nie mów mi, co mam robić, dobrze?","I co takiego szczególnego tam na dole? To tylko jaskinia, nic więcej...","Oh, daj spokój teraz...","Ha! No to zobaczymy, kto jest lepszy, robaku!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Białotwarz, odejdź. On będzie szczęśliwy, że "+npchar.name+"  dobroduszny. Bogowie mają dla ciebie litość dzisiaj.","Wyjdź z mojej jaskini, zanim ja i moi bracia się nie rozzłościmy!","Wyjdź, blady pies!","Twój szczęście i życie skończyło się, biały pies!","blokada",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Cóż, dziękuję ci, kumplu, bardzo miło z twojej strony...","Ta jaskinia nie jest twoja, a ja idę tam, gdzie chcę.","Złagodź to trochę, potwore z bagien.","Teraz zatłukę ci te słowa z powrotem do gardła, zwierzę...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Przeklęta blada twarz przyszła do naszego ogniska! Wheppee! Skończyłeś!","Głupi bladolicy przyszedł do legowiska jaguara. Usmażę twoją wątrobę!","Bezczelny bladolicy ośmiela się przyjść do mojej jaskini? W takim razie nigdy nie wyjdzie stąd żywy!");
				link.l1 = LinkRandPhrase("Teraz wyrywę ci język...","Teraz na świecie będzie kilku kanibali mniej...","Cóż, wygląda na to, że czas zrobić kilka dodatkowych dziur w twoim marnym ciele, ty czerwonolicy małpo.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Plugawy białoskóry przyszedł do naszej jaskini! Whe-hee! Wyrwę ci język i usmażę go!","Głupi bladotwarz przybył do legowiska jaguara. Bracia, pokrójcie tego przeklętego białego psa!","Bezczelna blada twarz ośmiela się przyjść do mojej jaskini? Nigdy stamtąd nie wyjdzie żywy!");
			link.l1 = LinkRandPhrase("Odrąbę cię od cholery głowę...","Teraz na świecie będzie kilku kanibali mniej...","No cóż, przygotuj się na spotkanie z twoimi przodkami, czerwonoskóry. Do diabła z tobą!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
