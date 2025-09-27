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
			dialog.text = "Akarsz valamit?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Hó-hó, nézd csak, ki van itt! Nos, ma van a szerencsenapod, haver. Mi jó fiúk vagyunk, látod, fôzünk kaját meg ilyenek... Nem hívlak meg a vacsoránkra, de tûnj el, amíg még lehet.", "Tûnj el most, és ne zavarj minket. Gyere vissza holnap - és ne felejtsd el magaddal hozni a táskádat, ha-ha-ha!", "Ne idegesíts, tengerész! Emlékszel még, hol van a barlang bejárata? Most azonnal oda kellene menned, nagyon-nagyon gyorsan...", "Na, most átlépted a határt, haver! Azt hiszem, el kell szakadnom a dolgaimtól, és foglalkoznom veled, seggfej!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Nagyon kedves tôled, haver...", "Látom, hogy te egy igazi tréfamester vagy...", "Jól van, akkor süsd csak tovább a lapos süteményeidet...", "Most már beszélgetünk, ha-ha!", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Hûha, te jó ég! Nem kell vadászni a prédára - az már itt van... Hé, srácok - rázzuk meg ezt a fickót, rendben?","Senki sem hívott ide, haver... De azért jó, hogy itt vagy. Lássuk csak, milyen nehéz a pénztárcád!","Senki sem rángatott ide erôszakkal, he-he... De ha már itt vagy, gondolom, csiklandozunk egy kicsit, hogy lássuk, mi esik ki a zsebedbôl...");
				link.l1 = LinkRandPhrase("Most egy kicsit megrövidítem a nyelvedet...","Remélem, hogy a kardforgatásban való jártasságod megegyezik az eszeddel, pofazacskó!","Nos, úgy tûnik, itt az ideje, hogy még néhány lyukat üssek a romlandó testedbe...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Hûha, te jó ég! Nem kell vadászni a prédára - az már itt van... Hé, srácok - rázzuk meg ezt a fickót, rendben?","Senki sem hívott ide, haver... De azért jó, hogy itt vagy. Lássuk csak, milyen nehéz a pénztárcád!","Senki sem rángatott ide erôszakkal, he-he... De ha már itt vagy, gondolom, csiklandozunk egy kicsit, hogy lássuk, mi esik ki a zsebedbôl...");
			link.l1 = LinkRandPhrase("Most egy kicsit megrövidítem a nyelvedet...","Remélem, hogy a kardforgatásban való jártasságod megegyezik az eszeddel, pofazacskó!","Nos, úgy tûnik, itt az ideje, hogy még néhány lyukat üssek a romlandó testedbe...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Tûnj el, haver. Nincs itt semmi keresnivalód!", "Hé, barátságosan kérdezem: tûnj el. Sosem tudhatod, mi történhet...", "Utolsó figyelmeztetés: ha nem tûnsz el most azonnal, megbánod, hogy idejöttél.", "Ennyi, haver, te kérted a bajt.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ne mondd meg nekem, hogy mit tegyek, rendben?", "És mi olyan különleges odalent? Csak egy barlang, semmi több...", "Ó, ugyan már...", "Ha! Na, lássuk, ki a jobb, te féreg!", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Sápadtarcú menj el. Örüljön, hogy "+npchar.name+"  kedves. Az istenek ma megsajnálnak téged.", "Kifelé a barlangomból, mielôtt én és a testvéreim nem haragszunk!", "Kifelé, sápadtarcú kutya!", "Szerencsédnek és életednek vége, fehér kutya!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Köszönöm, haver, nagyon kedves tôled...", "Ez a barlang nem a tiéd, és oda megyek, ahová akarok.", "Vegyél vissza egy kicsit, mocsári ivadék.", "Most visszatömöm ezeket a szavakat a torkodba, állat...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Átkozott sápadtarcú eljött a tábortüzünkhöz! Wheppee! Végeztél!","Buta sápadtarcú eljött a jaguár búvóhelyére. Megsütöm a májadat!","Pimasz sápadtarcú a barlangomba merészkedik? Akkor soha nem jut ki élve!");
				link.l1 = LinkRandPhrase("Most kitépem a nyelvedet...","Most a világnak több kannibállal kevesebb lesz...","Nos, úgy tûnik, itt az ideje, hogy még néhány lyukat üssek a romlandó testedbe, te vörös képû majom.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Büdös sápadtarcú eljött a barlangunkba! Whe-hee! Kivágom a nyelved és megsütöm!","Hülye sápadtarcú eljött a jaguár barlangjába. Testvérek, vágjátok le ezt az átkozott fehér görényt!","Pimasz sápadtarcú a barlangomba merészel jönni? Akkor soha nem jut ki élve!");
			link.l1 = LinkRandPhrase("Levágom a kibaszott fejedet...","Mostantól a világnak több kannibállal kevesebb lesz...","Nos, készülj fel az ôseiddel való találkozásra, vörösbôrû. A pokolba veled!");
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
