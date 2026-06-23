// Куранай - индеец
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
				dialog.text = "Nie chcę z tobą rozmawiać. Atakujesz spokojnych cywilów bez powodu i prowokujesz ich do walki. Zjeżdżaj!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Czego chce biały brat?";
				link.l1 = TimeGreeting()+" Biały bracie? Powiedz mi, dlaczego wy, Indianie, nazywacie nas albo białymi braćmi, albo blade twarze, co?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz coś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Czy wydarzyło się coś nowego na wyspie?","Czy opowiesz mi najnowsze plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać Ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Pokaż, co udało ci się znaleźć. Być może coś kupię...";
					link.l3.go = "trade";
				}
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mieszkamy tu wszyscy w pokoju, biały bracie. Curanai nie nazywa białego brata bladolicym psem. Nie wszyscy bladolice - psy. Mogę nazwać wielu Indian czerwonoskórym psem.";
			link.l1 = "Hm. Zakładam, że jesteś filozofem...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Curanai nie rozumie ciebie, biały bracie. Co znaczy filozof?";
			link.l1 = "Nie ma znaczenia, czerwonoskóry bracie. Po prostu podoba mi się, jak myślisz. Mówisz, że nazywasz się Curanai? Moje imię to "+GetFullName(pchar)+" . Miło cię poznać.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai cieszy się, że zna imię białego brata.";
			link.l1 = "Dobrze. Do zobaczenia wkrótce!";
			link.l1.go = "exit";
			link.l3 = "Chcę zadać ci kilka pytań o wyspę.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Zapytaj, blade oblicze, Curanai odpowie.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak tu dotarłeś?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Co robisz na Wyspie Sprawiedliwości?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Chcesz wrócić do domu?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Mieszkasz tu spokojnie na Wyspie Sprawiedliwości? Czy zdarzają się tu walki lub kłótnie?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przepraszam...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ja i kilku wojowników z mojego plemienia postanowiliśmy popłynąć na małą wysepkę blisko naszej ziemi, widoczną w pogodny dzień. Zrobiliśmy tratwę z bambusa i żagiel. Lecz burza zaskoczyła nas nagle i wyrzuciła na otwarte morze. Nie zdaliśmy sobie sprawy, jak szybko nasza ziemia i wyspa zniknęły. Żeglowaliśmy po morzu przez wiele, wiele nocy i dni. Wszyscy moi bracia umarli z pragnienia i głodu. Zostałem sam - duchy zlitowały się nad Curanai i przyprowadziły tratwę na tę wyspę. Przetrwałem.";
			link.l1 = "Tak... Smutna historia.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "„Curanai łowi ryby. Curanai uderza rybę harpunem. Rzadko-rzadko trafia na dużego kraba. Wtedy Curanai jest szczęśliwy - krab jest smaczny, bardzo smaczny. Jeden szczypiec wystarcza na kilka dni. A Curanai również nurkuje na dno do jednego miejsca. Tam nie ma dużych krabów. Curanai zbiera żółty kamień, niebieski kamień, czarny kamień i perłę. Duże i małe. Potem Curanai sprzedaje je bladolicy.”";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Curanai chce wrócić do domu. Ale gdzie jest mój dom? Curanai nie wie, gdzie jest jego wioska i jak się tam dostać.";
			link.l1 = "Hm. Co mogę rzec...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narwale i Rivaosi często walczą ze sobą. Żyjemy w pokoju i nikomu nie szkodzimy. Czasem bladolice piją ognisty napój i klną, ale nie zabijają. Są dwa oficerowie-wojownicy, jeden nienawidzi drugiego. Pewnego dnia jeden zabije drugiego. Curanai wie.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodzieju!","Spójrz tylko na to! Gdy tylko pogrążyłem się w zadumie, postanowiłeś przeszukać moją skrzynię!","Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Postanowiłeś sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewucho!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. Przyprawia mnie o nerwy.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj to.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem wokół. Odłóż to, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Z pewnością.","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.","Słuchaj, jestem obywatelem miasta i prosiłbym cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Cokolwiek więc.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Uważaj, kumplu, gdy biegasz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni przechodzą przede mną z gotową bronią. To mnie przeraża...");
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
