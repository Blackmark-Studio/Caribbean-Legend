// Чад Каппер - боцман Акулы и тюремщик
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
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Cóż, cóż... Więc to ty jesteś tajemniczym złodziejem? Hm... Nie wyglądasz na nędznego drobnego złodziejaszka.";
			link.l1 = "Słuchaj, panie, jesteś w błędzie. Jestem tu nowy, więc skąd miałbym wiedzieć, że ładownia, w której mnie złapali twoi ludzie, była twoją prywatną strefą?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Naprawdę? Niezła próba, kolego... Skąd więc tu przybyłeś?";
			link.l1 = "Z Głównego... Przez dziwny posąg. Sam nie wiem, jak wyjaśnić to, co się wydarzyło.";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Posąg? Ha-ha! Jesteś zabawnym chłopakiem, prawda... Dobrze, wyjaśnię ci wszystko osobiście: przepłynąłeś przez dziurę w statku i chciałeś zakraść się do naszego magazynu. Jak to się stało, że nie rozpoznaję twojej twarzy? Znam wszystkich Rivados...";
			link.l1 = "Jakie Rivados? Nie wiem, o czym mówisz! Słuchaj, przybyłem tutaj około godzinę temu...";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Nie wrzeszcz, nie jestem idiotą. Aye, nasłuchałem się twoich bzdur o posągu i uważam je za dość zabawne. Uważam je za cholernie śmieszne. Co powiesz na to, żebyśmy się z tego razem pośmiali? Ha-ha-ha!... Dlaczego się nie śmiejesz? To był niezły żart... Rivados. Ale żarty się skończyły. Zostawię cię, żebyś zgnił w więzieniu, kolego.";
			link.l1 = "Nie jestem Rivados! Nazywam się Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Pierwszy raz, co? Hm... może mówisz prawdę. Odpowiedz mi, jesteś jednym z nich?!";
			link.l1 = "Przysięgam ci, nigdy wcześniej nie słyszałem tego imienia, nie jestem jednym z nich!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "„Naprawdę? Dobrze. Udowodnij to. Zejdź na dół, tam siedzi w klatce jeden z Rivados. To niebezpieczny czarownik. Zabij go, tylko wtedy będę przekonany. Zapomnę także o twoim nielegalnym wtargnięciu do naszego magazynu.\nNo i co? Jesteś gotów? Nie bój się, czarownik jest nieuzbrojony i słaby. Cóż, może zamieni cię w pył jakimś zaklęciem, takim jak to, które przyniosło cię do ładowni San Augustine...”";
			link.l1 = "Gdybyś widział to zaklęcie w akcji, nie byłbyś tak sceptyczny. Wątpię, czy w ogóle byś to przeżył...";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Dość gadania! Robisz to, czy nie? Jeśli tak, to weź ten maczeta i rozpraw się z czarodziejem. W przeciwnym razie spędzisz resztę życia w klatce. Zrozumiano?";
			link.l1 = "Z dwóch złych wybieram mniejsze. Daj mi maczetę.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Grzeczny chłopcze. Weź to, idź i zabij czarnego. Jego klatka jest otwarta. Nie próbuj żadnych głupstw, nie zawahamy się cię wykończyć, jeśli choćby pomyślisz o czymś! Teraz idź!";
			link.l1 = "Dlaczego? Boisz się, że wypatroszę was tym zardzewiałym kawałkiem metalowego śmiecia?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "Moja cierpliwość się kończy. Udaj się do ładowni i rób, co ci każą!";
			link.l1 = "Dobrze, dobrze, uspokój się. Już odchodzę...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Testujesz moją cierpliwość, bękarcie! Nie chcesz mnie drażnić...";
			link.l1 = "Dobrze, dobrze, spokojnie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Czy zabiłeś tego czarnego czarownika? Dobrze... Cieszę się. Udowodniłeś, że nie jesteś z Rivados.";
			link.l1 = "Kiedy wreszcie zostanę uwolniony z tej przeklętej łajby? Muszę natychmiast spotkać się z Rekinem.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Spotkasz go, na pewno... Spotkasz go na drodze do piekła!";
			link.l1 = "Co?!";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha!  Tylko spójrz na to. Co ty tutaj robisz w moim więzieniu?";
			link.l1 = "Twoje imię to Chad Kapper, prawda? Nazywam się "+GetFullName(pchar)+" i jestem tu w imieniu Rekina Dodsona. Dał mi klucze.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Od admirała? Hm, rozumiem. Jesteś jego nowym chłopcem na posyłki?";
			link.l1 = "Okazuj trochę szacunku, panie. Nie służę nikomu, ani Rekinowi, ani tobie, i nie zamierzam tolerować takiego języka.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha, lubię cię, kolego! Zapomnij, że coś mówiłem... Więc, co cię tu sprowadza?";
			link.l1 = "Rekin wydał rozkaz uwolnienia Chimiseta, jest tutaj uwięziony.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "Czarodziej Rivados? Hm. To dziwne, naprawdę mnie to zaskakuje, gdy to słyszę...";
			link.l1 = "Rekin wydał rozkaz. Chce zawrzeć pokój z Rivados.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ach, rozumiem teraz. Dobrze, wyślę człowieka do Rivados. Przyjdą tutaj i zabiorą swego błazna.";
			link.l1 = " Dlaczego nie możesz po prostu pozwolić mu odejść?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Mógłbym, ale to byłoby zbyt niebezpieczne dla niego. Chimiset jest tutaj znany, jego życie nie będzie warte nic, gdy wejdzie na 'Esmeraldę' - terytorium jego wrogów, Narwali. Nie ma innej drogi z Tartarusa, nie możemy pozwolić, by stary człowiek pływał wokół wyspy! A jeśli ktoś go zabije, Rivados obwinią nas, konkretnie mnie! Widzisz, nie chcę problemów, które można uniknąć. Więc wypuszczę go tylko pod ochroną wojowników jego klanu. Może chcesz porozmawiać z Chimisetem osobiście? Jest zabawnym typem...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Już z nim rozmawiałem, naprawdę jest dziwnym człowiekiem. Cóż, muszę iść. Do zobaczenia, Chad!";
			else link.l1 = "To właśnie zamierzałem. Pójdę z nim porozmawiać.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Wyślę posłańca do Rivados, a oni zabiorą swojego czarownika. Nie martw się, kumplu, możesz iść.";
			link.l1 = "W porządku.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "...pewnie już otworzył beczkę, jestem pewien. To jego ulubiona whiskey, cholerny Irlandczyk. Niedługo się skończy, włożyłem do niej wystarczająco arszeniku, by zabić stado...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Ah? Cholera, co ty tu robisz? Zjeżdżaj!";
			link.l1 = "Szukam cię od dawna... trucicielu. To dziwne, nie widzę Cyklopa. Chciałeś zająć miejsce Rekina, prawda?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, Rekin musi już nie żyć! A ty wkrótce podążysz za nim, szpieg!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "Aeva_attack_3":
			dialog.text = "Ach, detektywie! Cóż, najpierw ty zginiesz! Chłopcy, do broni!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
