// Сесил Галард - бабулька
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zmykaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Chcesz czegoś, młodzieńcze?";
				link.l1 = TimeGreeting()+"Pozwól, że się przedstawię - "+GetFullName(pchar)+"Jestem nowicjuszem.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy coś nowego wydarzyło się na wyspie?","Czy powiesz mi ostatnie plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chciałbym zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się miewasz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, więc poznajesz naszą Wyspę i jej mieszkańców, prawda?";
			link.l1 = "Dokładnie, pani?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Miło mi cię poznać, pani Halard! To dla mnie przyjemność.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Mój także... A jak ty się tu dostałeś, młodzieńcze? Nie pamiętam żadnego niedawnego rozbicia statku...";
			link.l1 = "Przygnało mnie tu z Kontynentu na barku... ale zatonął tuż przy brzegach Wyspy. Tak oto zostałem bez statku.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Barka? Trudno mi w to uwierzyć... W takim razie masz naprawdę szczęście, że dopłynąłeś aż do Wyspy na takiej łajbie i nie wpadłeś w burzę. Burze to rzadkie zjawiska wewnątrz wyspy, ale na zewnątrz są zagrożeniem, bardzo nagłym zagrożeniem\nWięc uznaj się za szczęśliwca i przyzwyczaj się do lokalnego sposobu życia! Nie chcę cię zasmucać, ale dotarcie tutaj jest łatwe, jednak opuszczenie Wyspy jest prawie niemożliwe. Nie myśl, że narzekam, nikt nie zdołał opuścić Wyspy żywy przez ostatnie dziesięć lat.";
			link.l1 = "I tak spróbuję być nieco bardziej optymistyczny. Miło cię poznać i do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Tak, młody człowieku?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "A jakże tu się dostałaś, pani?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Żyjesz tu już od dawna, prawda?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Co możesz mi powiedzieć o miejscowych?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy możesz mi opowiedzieć o interesujących ludziach, którzy tu mieszkają?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Żadnych pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "To było tak dawno temu, że naprawdę nie pamiętam, jak to się stało. Wrak statku i tyle...";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Czasami myślę, że urodziłem się tutaj... Ale to oczywiście nieprawda. Mieszkam tutaj przez całą drugą połowę mojego życia. A było ono długie. I umrę tutaj, bo nie zamierzam opuszczać tego miejsca.";
			link.l1 = "Rozumiem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I niewiele mogę rzec, młodzieńcze... wszyscy są różni. Mamy tu wszystkich - białych, czarnych, Indian, byłych niewolników i szlachciców, skazańców państwowych i żołnierzy. A kiedyś było ich więcej. Każdy ma swoją historię i swoje nawyki. Niektórym to nie przeszkadza, ale inni wciąż pragną powrócić. Tak tu żyjemy...";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Najciekawszymi ludźmi tutaj są: narwalowy mechanik-inżynier, Herr Schmidt - narwalowy rusznikarz, Sancho Carpentero - miejscowy barman. A teraz mamy jeszcze admirała z jego zastępcą.";
			link.l1 = "Rozważę to...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w rozmyślaniach, a ty postanowiłeś sprawdzić moją skrzynię!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Do diabła!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewucha!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. To mnie niepokoi.","Wiesz, bieganie z ostrzem tutaj nie jest tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Pewnie.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i poprosiłbym cię, byś schował swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, schowaj swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Jasne.","Jak powiadasz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, gdy biegniesz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z gotową bronią. To mnie przeraża...");
				link.l1 = RandPhraseSimple("Zrozumiano.","Zabieram to.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
