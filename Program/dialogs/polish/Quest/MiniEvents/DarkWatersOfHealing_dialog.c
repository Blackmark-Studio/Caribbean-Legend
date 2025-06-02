void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Co sprowadza cię do mojego domu?";
			link.l1 = "Jestem kapitanem, nazywam się "+GetFullName(pchar)+". Przyszedłem na prośbę cyganki. Nie rozumie, dlaczego odrzuciłeś jej pomoc, i chce poznać powód. Czy naprawdę jesteś w takiej sytuacji, by odrzucać jakąkolwiek, choćby najmniejszą szansę na ratunek?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_1":
			dialog.text = "Ach, kapitanie... Zrozum, musiałem odmówić, ale nie z własnej woli. Wierz mi, oddałbym wszystko, żeby Esther wyzdrowiała.";
			link.l1 = "Co mogło cię zmusić do odrzucenia pomocy, której tak bardzo potrzebujesz?";
			link.l1.go = "Tomas_2";
		break;
		
		case "Tomas_2":
			dialog.text = "Widzisz, nasza rodzina zawsze była pobożna. Po śmierci mojej żony Olivii trzymam się tylko dzięki wierze. Kiedy cyganka zaproponowała pomoc, zgodziłem się – byle tylko uratować córkę. Ale... dowiedział się o tym nasz pastor.";
			link.l1 = "Niech zgadnę: jest przeciwnikiem takich usług?";
			link.l1.go = "Tomas_3";
		break;
		
		case "Tomas_3":
			dialog.text = "Dokładnie tak. Przekonał mnie, że tylko modlitwa i wola Boża mogą uleczyć moją córkę. A jeśli z tego zboczę – skorzystam z pomocy 'wiedźmy', zagroził ekskomuniką. Rozumiesz? Ekskomuniką!";
			link.l1 = "Czyli zdrowie Esther zależy tylko od słowa pastora?";
			link.l1.go = "Tomas_4";
		break;
		
		case "Tomas_4":
			dialog.text = "Żyjemy z córką w wierze. Ona jest naszym wszystkim. Jeśli cyganka nie pomoże, stracę nie tylko córkę, ale i swoje miejsce w tym świecie. Ludzie się odwrócą, Kościół odrzuci. Zostaniemy sami.";
			link.l1 = "A gdyby pastor dał zgodę? Pozwoliłbyś jej spróbować?";
			link.l1.go = "Tomas_5";
		break;
		
		case "Tomas_5":
			dialog.text = "Tak. Gdyby Kościół pobłogosławił jej działania... wtedy zaufałbym. Jestem gotów spróbować wszystkiego, co może pomóc.";
			link.l1 = "Rozumiem. Dobrze, Thomasie, pomogę ci. Porozmawiam z twoim pastorem. Może uda mi się go przekonać.";
			link.l1.go = "Tomas_6";
		break;
		
		case "Tomas_6":
			dialog.text = "Naprawdę chcesz nam pomóc? Kapitanie, będę się modlił o twój sukces. Ale miej na uwadze... nasz pastor to uparty i zasadniczy człowiek, trudno będzie go przekonać.";
			link.l1 = "Zasady można pokonać mocnymi argumentami. Czekaj, wrócę wkrótce.";
			link.l1.go = "Tomas_7";
		break;
		
		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Co sprowadza cię do mojego domu?";
			link.l1 = "Jestem kapitanem, nazywam się "+GetFullName(pchar)+". Przyszedłem na prośbę cyganki. Nie rozumie, dlaczego odrzuciłeś jej pomoc, i chce poznać powód. Czy naprawdę jesteś w takiej sytuacji, by odrzucać jakąkolwiek, choćby najmniejszą szansę na ratunek?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_1":
			dialog.text = "Ach, kapitanie... Zrozum, musiałem odmówić, ale nie z własnej woli. Wierz mi, oddałbym wszystko, żeby Esther wyzdrowiała.";
			link.l1 = "Co mogło cię zmusić do odrzucenia pomocy, której tak bardzo potrzebujesz?";
			link.l1.go = "Tomas_2";
		break;
		
		case "Tomas_2":
			dialog.text = "Widzisz, nasza rodzina zawsze była pobożna. Po śmierci mojej żony Olivii trzymam się tylko dzięki wierze. Kiedy cyganka zaproponowała pomoc, zgodziłem się – byle tylko uratować córkę. Ale... dowiedział się o tym nasz pastor.";
			link.l1 = "Niech zgadnę: jest przeciwnikiem takich usług?";
			link.l1.go = "Tomas_3";
		break;
		
		case "Tomas_3":
			dialog.text = "Dokładnie tak. Przekonał mnie, że tylko modlitwa i wola Boża mogą uleczyć moją córkę. A jeśli z tego zboczę – skorzystam z pomocy 'wiedźmy', zagroził ekskomuniką. Rozumiesz? Ekskomuniką!";
			link.l1 = "Czyli zdrowie Esther zależy tylko od słowa pastora?";
			link.l1.go = "Tomas_4";
		break;
		
		case "Tomas_4":
			dialog.text = "Żyjemy z córką w wierze. Ona jest naszym wszystkim. Jeśli cyganka nie pomoże, stracę nie tylko córkę, ale i swoje miejsce w tym świecie. Ludzie się odwrócą, Kościół odrzuci. Zostaniemy sami.";
			link.l1 = "A gdyby pastor dał zgodę? Pozwoliłbyś jej spróbować?";
			link.l1.go = "Tomas_5";
		break;
		
		case "Tomas_5":
			dialog.text = "Tak. Gdyby Kościół pobłogosławił jej działania... wtedy zaufałbym. Jestem gotów spróbować wszystkiego, co może pomóc.";
			link.l1 = "Rozumiem. Dobrze, Thomasie, pomogę ci. Porozmawiam z twoim pastorem. Może uda mi się go przekonać.";
			link.l1.go = "Tomas_6";
		break;
		
		case "Tomas_6":
			dialog.text = "Naprawdę chcesz nam pomóc? Kapitanie, będę się modlił o twój sukces. Ale miej na uwadze... nasz pastor to uparty i zasadniczy człowiek, trudno będzie go przekonać.";
			link.l1 = "Zasady można pokonać mocnymi argumentami. Czekaj, wrócę wkrótce.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomasie, udało mi się przekonać pastora.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Naprawdę? Niesamowite! W takim razie sprowadźmy cygankę jak najszybciej.";
			link.l1 = "Z pewnością to zrobimy, ale jest jeden szczegół. Pastor ma nadzieję, że to wszystko nie zachwieje twojej wiary i oczekuje od ciebie szczerego żalu i dobrych uczynków. Pierwszym z nich może być zakup nowego dzwonu dla parafii.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Ach, kapitanie... Dzwon to spory wydatek. Być może będę musiał rozstać się z czymś z biżuterii mojej zmarłej żony. Ale dla Esther oddam wszystko, co mam, a nawet więcej. Oczywiście, będę błagać Boga o przebaczenie. Pójdę do kowala, złożę zamówienie i odnajdę cygankę. Proszę, przekaż pastorowi, że dzwon będzie. Zdobyłbym go nawet spod ziemi, jeśli trzeba.";
			link.l1 = "Dobrze, Thomasie.";
			link.l1.go = "Tomas_14";
		break;

		case "Tomas_14":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Przekazałem pastorowi twoje słowa. Już nie będzie stawiać przeszkód, więc możecie zaczynać.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Dziękuję, kapitanie, za twoje zaangażowanie! Weź te pięćdziesiąt dublonów, to najmniejsze, co mogę dla ciebie zrobić, ale to wszystko, co mam w tej chwili...";
			link.l1 = "Ależ skąd! Pomagam ci nie dla pieniędzy. Teraz wszystko gotowe do... hmm... leczenia?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Skoro nalegasz... Czy mogę pomóc jeszcze jakoś?";
			link.l2.go = "Tomas_16_2";
		break;

		
		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Aby przygotować miksturę, która przywróci dziewczynce zdrowie, potrzebuję mangarosy — rzadkiej rośliny rosnącej w miejscach, gdzie człowiek rzadko stąpa. Znam jedną jaskinię za miastem, gdzie często kręcą się... wszelkiej maści szumowiny. Marnują mangarosę na palenie, nie rozumiejąc jej mocy. Pomóż mi, "+GetSexPhrase("Sokole","Gołąbeczku")+", zdobądź dla mnie mangarosę, bez niej nic się nie uda.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa? Znam tę roślinę.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Jak wygląda ta roślina?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "To dość wysoka roślina z pierzastymi liśćmi i przyjemnym, odurzającym zapachem. Na pewno jej nie pomylisz.";
			link.l1 = "Dobrze, znajdę tę mangarosę.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Też mieszasz ją z tytoniem?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Nie, co ty! Jest pewna znachorka, Amelia. Przygotowuje z tej rośliny mikstury, które — bez przesady — potrafią odmienić świadomość.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Nie, ale kilka razy miałem ją w rękach.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		
		case "gypsy_VD_manga_1_2":
			dialog.text = "Znasz Amelię, mówisz? No proszę, "+GetSexPhrase("Sokole","Gołąbeczku")+", niedługo zaczniesz mi robić konkurencję. Ale to nie czas na pogadanki. Idź, przynieś mangarosę, a ja przygotuję wszystko, co trzeba.";
			link.l1 = "Już lecę.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;
		
		case "gypsy_VD_manga_2":
			dialog.text = "Widzę, że nie jesteś taki zwyczajny, "+GetSexPhrase("Sokole","Gołąbeczku")+". Twoja wiedza jest ogromna, a umysł ostry jak brzytwa! Nie boisz się nieznanego i chcesz zrozumieć to, co ukryte. Thomas miał szczęście, gdy prosił cie o pomoc. Teraz idź, przynieś mi mangarosę, a ja uleczę dziewczynkę.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			AddQuestRecord("DWH", "5");
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ha ha. Mówię ci, Mark, to naiwniak. Nawet domu nie zamyka.";
			link.l1 = "A jesteś pewien, że jego kury nie będzie w domu?";
			link.l1.go = "Bandit_2";
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "No proszę, świeżynka wpłynęła! No dalej, nie stój jak słup. Kieszenie na wierzch i szybko, póki jesteśmy mili.";
			link.l1 = "Spokojnie, rzezimieszki. Przyszedłem w interesach, przysłała mnie do was "+sld.name+". Potrzebuję mangarosy.";
			link.l1.go = "Bandit_4";
			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;
		
				case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = ""+sld.name+" mówisz? Dobrze, mamy mangarosę. Daj dziesięć dublonów, i jest twoja.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Masz.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Pieniądze? Po co wam pieniądze? Ja nie rozdaje jałmużny. Ale dwa funty stali pod żebra – to mogę zafundować!";
			link.l2.go = "Bandit_7";
		break;
		
		case "Bandit_5":
			dialog.text = "W porządku, oto twoja mangarosa. I zapamiętaj – nie widziałeś nas.";
			link.l1 = "Heh. Nie musiałeś mnie ostrzegać.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice")) SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Spójrz, "+npchar.name+", czy to ta roślina, której potrzebujesz?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Przyniosłeś to, o co prosiłam?";
				link.l1 = "Jeszcze nie, pracuję nad tym.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Tak, to właśnie ona. Teraz mam wszystko, co potrzebne, i mogę zaczynać.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Chodźmy szybko, nie ma czasu do stracenia.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Kapitanie, jeśli nie ma pan nic przeciwko, zobaczymy się później. Teraz czeka nas najważniejsza część... leczenia.";
			link.l1 = "Oczywiście, Thomasie. Mam nadzieję, że pańska córka szybko wróci do zdrowia.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Thomas wyrzucił cię z domu nie z własnej woli. Pastor zagroził mu ekskomuniką, jeśli przyjmie twoją pomoc.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_7":
			dialog.text = "Od razu to wiedziałam, "+GetSexPhrase("kochanie","piękności")+", że odmówił mi z ciężkim sercem.";
			link.l1 = "Czy można mu pomóc, nie zwracając uwagi kościoła?";
			link.l1.go = "gypsy_8";
		break;
		
		case "gypsy_8":
			dialog.text = "Och, "+GetSexPhrase("kochanie","piękności")+", sprawa nie jest prosta, ale drogi są mi znane, wiem, co trzeba zrobić. Tylko bez twojej pomocy się nie obejdzie, sam rozumiesz.";
			link.l1 = "Oczywiście, możesz na mnie liczyć.";
			link.l1.go = "gypsy_10";
			link.l2 = "Przykro mi, czarnobrewa, ale zupełnie nie mam teraz na to czasu. Zrobiłem wszystko, co mogłem, teraz muszę zająć się swoimi sprawami.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Potrzebuję następujących rzeczy: przedmiotu należącego do dziewczynki, dwóch łodyg bielunia, jednej łodygi ipekakuany i jednej werbeny. Jeśli mi to wszystko przyniesiesz, będę mogła przygotować dla niej leczniczy eliksir.";
			link.l1 = "Dobrze, zdobędę wszystko, co potrzebne.";
			link.l1.go = "gypsy_11";
		break;
		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomasie, niestety pastor nie wysłuchał moich argumentów. Ale ja i cyganka możemy wam pomóc. Potrzebuję...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_22":
			dialog.text = "Chce pan, żebym wystąpił przeciwko Kościołowi?";
			link.l1 = "Zrobimy to po cichu, nikt się nie dowie. Wkrótce pana córka znów będzie mogła cieszyć się życiem i swobodnie spacerować po mieście, jak przystało młodej damie.";
			link.l1.go = "Tomas_23";
			link.l2 = "Na Boga, Thomasie Morrisonie, chce pan, żeby pana córka wyzdrowiała, czy nie?";
			link.l2.go = "Tomas_24";
		break;
		
		case "Tomas_23":
			dialog.text = "Dobrze, zgadzam się. Ale proszę działać ostrożnie. Nie chcę żadnych plotek ani kłopotów.";
			link.l1 = "Oczywiście. Potrzebuję osobistego przedmiotu pańskiej córki, czegoś, do czego jest przywiązana.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;
		
		case "Tomas_24":
			dialog.text = "Dobrze, zgadzam się. Ale proszę działać ostrożnie. Nie chcę żadnych plotek ani kłopotów.";
			link.l1 = "Oczywiście. Potrzebuję osobistego przedmiotu pańskiej córki, czegoś, do czego jest przywiązana.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Tomas_25":
			dialog.text = "Hmm... Tak! Wiem, co się nada. Proszę chwilę poczekać, zaraz wrócę.";
			link.l1 = "Czekam...";
			link.l1.go = "Tomas_26";
		break;
		
		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("Minęło kilka minut...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Proszę. To nefrytowy naszyjnik. Esther nigdy go nie zdejmowała, jest jej bardzo drogi.";
			link.l1 = "Świetnie. Teraz pozostaje wam tylko czekać. Do zobaczenia wkrótce, Thomasie.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;
		
		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "gypsy_21":
			dialog.text = "Przyniosłeś to, o co prosiłam?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "Zebrałem wszystko, co potrzebne.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Przypomnij mi, co mam przynieść.";
			link.l2.go = "gypsy_napomni";
		break;
		
		case "gypsy_napomni":
			dialog.text = "Potrzebuję następujących rzeczy: przedmiotu należącego do dziewczynki, dwóch łodyg bielunia, jednej łodygi ipekakuany i jednej werbeny. Jeśli mi to wszystko przyniesiesz, będę mogła przygotować dla niej leczniczy eliksir.";
			link.l1 = "Dobrze, zdobędę wszystko, co potrzebne.";
			link.l1.go = "gypsy_napomni_2";
		break;
		
		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;
		
		case "gypsy_22":
			dialog.text = "Doskonale. Teraz będę mogła przygotować eliksir dla dziewczynki. Gotowy będzie nie wcześniej niż jutro rano. Jak zwykle znajdziesz mnie na ulicach miasta.";
			link.l1 = "Dobrze, do zobaczenia.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			AddQuestUserData("DWH", "sSex", GetSexPhrase("em","am"));
			AddQuestUserData("DWH", "sSex1", GetSexPhrase("em","am"));
			AddQuestUserData("DWH", "sSex2", GetSexPhrase("em","am"));
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "No i co, "+npchar.name+", czy twoja mikstura jest gotowa?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_32":
			dialog.text = "Oto jest, "+GetSexPhrase("kochanie","piękności")+". Dziewczynka musi założyć ten naszyjnik i wypić zawartość fiolki do ostatniej kropli. W ciągu miesiąca będzie całkowicie zdrowa.";
			link.l1 = "Natychmiast zanoszę to Thomasowi. Do zobaczenia, czarnobrewa.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;
		
		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomasie, wszystko gotowe. Esther musi założyć te korale i wypić eliksir za jednym razem.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;
		
		case "Tomas_32":
			dialog.text = "Dziękuję ci, "+pchar.name+"! Proszę mi wybaczyć, nie chcę tracić ani minuty...";
			link.l1 = "Oczywiście, oczywiście.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Dzień dobry, "+pchar.name+"! Moja Esther wyzdrowiała! Jest całkowicie zdrowa i teraz modli się w kościele, dziękując Panu Bogu za to, że zesłał nam ciebie i cygankę!";
			link.l1 = "Thomasie, cieszę się, że wszystko się udało! Dbaj o dziewczynkę, teraz czeka ją długie i szczęśliwe życie.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Weź te trzysta dublonów. Niestety, więcej nie mogę zaoferować, musiałem się zadłużyć, by zebrać tę sumę. Ale wiedz, że żadne słowa ani złoto nie oddadzą mojej wdzięczności, kapitanie. Nie tylko wybawiłeś mnie od strachu o jej życie, ale dałeś naszej rodzinie szansę na przyszłość. Zawsze będę ci wdzięczny!";
			link.l1 = "Dziękuję! Trzysta dublonów to bardzo hojna nagroda, nie martw się – wynagrodziłeś mnie w pełni!";
			link.l1.go = "Tomas_43";
			link.l2 = "Nie przyjmę twoich pieniędzy, Thomasie. Nawet nie próbuj nalegać! Pomogłem ci nie dla zysku. Kup Esther ładną sukienkę za te pieniądze – zasłużyła na to.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", odwiedzaj nas w każdej chwili. Zawsze będziesz mile widziany w naszym domu. I jeszcze jedno – porozmawiaj z cyganką, chciała cię zobaczyć.";
			link.l1 = "To dla mnie zaszczyt! A teraz wybacz, Thomasie – obowiązki wzywają.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Oczywiście, oczywiście. Niech Bóg będzie z tobą, "+GetFullName(pchar)+"!";
			link.l1 = "Do widzenia.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Jesteś człowiekiem wielkiej szlachetności, "+GetFullName(pchar)+"! Niech Matka Boska będzie z tobą! Wpadnij do nas, nasz dom jest zawsze dla ciebie otwarty. I jeszcze jedno, "+pchar.name+", porozmawiaj z cyganką – chciała cię widzieć.";
			link.l1 = "Oczywiście! A teraz wybacz, obowiązki.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Słyszeliście? "+GetFullName(pchar)+" zdobył dla córki Thomasa Morrisona miksturę, która w mig postawiła biedną dziewczynę na nogi!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison codziennie zapala świecę w kościele za zdrowie "+GetFullName(pchar)+". Mówią, że uratował swoją córkę przed przewlekłą chorobą.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison rozkwitła na oczach wszystkich. Jakby nigdy nie była chora. Nikt tak naprawdę nie wie, co zmusiło chorobę do odwrotu.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "A oto i ty, "+GetSexPhrase("Sokole","Gołąbeczku")+"! Wiedziałam, że znowu się tutaj pojawisz. Dzięki twoim staraniom dziewczyna wyzdrowiała i teraz fruwa jak gołębica. Całe miasto się nią zachwyca.";
			link.l1 = "No, czarnobrewa, to nie tylko moja zasługa, nie przesadzaj. To twoja mikstura postawiła ją na nogi, więc nie ukrywaj swojego udziału.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_42":
			dialog.text = "Masz dobre serce, "+GetSexPhrase("Sokole","Gołąbeczku")+", i bystry umysł! Będziesz wielkim człowiekiem – takie jest moje proroctwo.";
			link.l1 = "Heh... dzięki, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;

		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "A oto i ty, "+GetSexPhrase("Sokole","Gołąbeczku")+"! Wiedziałam, że znowu się tutaj pojawisz. Dzięki twoim staraniom dziewczynka wyzdrowiała i teraz fruwa jak gołębica. Całe miasto się nią zachwyca.";
			link.l1 = "No proszę cię, to ty ją uzdrowiłaś, a chcesz, by mnie przypisywano zasługi? Tak nie będzie! Ty przygotowałaś miksturę, ty postawiłaś ją na nogi – zasługa należy się tobie.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_45":
			dialog.text = "Masz dobre serce, "+GetSexPhrase("Sokole","Gołąbeczku")+", i szlachetną duszę. Mam dla ciebie prezent – taki, który każdy kapitan doceni. Trzymaj. Teraz szczury na twoim statku nie zaznają ani chwili spokoju!";
			link.l1 = "Prezent? Tego się nie spodziewałem!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;
		
		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Twoja dusza jest czysta, widzę, że nie będziesz palił mangarosy dla chwilowej przyjemności. Jeśli będziesz jej pilnie potrzebować, przyjdź do mnie, "+GetSexPhrase("Sokole","Gołąbeczku")+". Pięć łodyg będzie cię kosztować dwieście dubloonów\nTo kapryśne ziele, sam wiesz – nie każdy potrafi je znaleźć. Więc nie ponaglaj mnie – nie pytaj częściej niż raz w miesiącu, bo i tak wcześniej nie zdobędę.";
			}
			else
			{
				dialog.text = "Masz jasną duszę, sokole – widzę, że znasz się na ziołach lepiej niż niejedna znachorka. Dużo potrafisz znaleźć, ale szczęście nie zawsze dopisuje. Jest jedno rzadkie ziele, które nie każdemu się poddaje. Mangarosa się zwie. Jeśli będzie trzeba, przyjdź do mnie, "+GetSexPhrase("Sokole","Gołąbeczku")+". Pięć łodyg dam, ale za darmo nie oddam – dwieście dubloonów biorę\nTo kapryśne ziele, sam wiesz – nie każdy potrafi je znaleźć, więc nie ponaglaj mnie. Nie pytaj częściej niż raz na miesiąc – choćbyś nie wiem jak wróżył, szybciej nie znajdę.";
			}
			link.l1 = "Dzięki ci, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			AddQuestUserData("DWH", "sSex", GetSexPhrase("","a"));
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Kapitanie, wciąż myślę, że to sam Pan skierował was do nas we właściwej chwili! Uratowaliście moją córkę i nigdy tego nie zapomnę.";
			link.l1 = "Może tak, Thomasie. Niezbadane są wyroki boskie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;
		
		case "Tomas_52":
			dialog.text = "Może kieliszek wina, kapitanie? Mam coś wyjątkowego dla specjalnych gości.";
			link.l1 = "Dziękuję, Thomasie, ale niestety muszę już iść.";
			link.l1.go = "exit";
		break;
		
		case "gypsy_Mangarosa":
			dialog.text = "Czego chcesz, sokole?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Powiedz mi, czarnooka, masz może mangarosę?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Wpadłem tylko się przywitać. Muszę lecieć!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Kto, jak nie ja, "+GetSexPhrase("kochanie","piękności")+", zdobędzie ci taką rzadkość? Dwieście dublonów – i masz pięć łodyg, ani mniej, ani więcej.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Masz swoje dubloony.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Cholera. Nie mam tyle. Przyjdę później.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_2":
			dialog.text = "No, tak to lepiej, "+GetSexPhrase("Sokole","Gołąbeczku")+". Bierz. Ale nie marnuj jej, wiesz przecież – mangarosa to nie byle jaka roślinka, skrywa siłę, z którą nie każdy sobie poradzi.";
			link.l1 = "Nie martw się, czarnooka, znajdę dla niej godne zastosowanie.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 5);
			RemoveDublonsFromPCharTotal(300);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}