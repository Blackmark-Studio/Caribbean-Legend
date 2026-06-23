// Орели Бертин - просто жительница
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
				dialog.text = "Dobry dzień, panie. Co powiesz?";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+",  Jestem tu nowicjuszem, więc poznaję miejscowych.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = LinkRandPhrase("Masz coś ciekawego do powiedzenia?","Zdarzyło się coś nowego na wyspie?","Czy opowiesz mi najnowsze plotki?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Chciałem tylko wiedzieć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Rozumiem. Nazywam się Orelie Bertine. Jak się tu dostałeś?";
			link.l1 = "Powiedzmy, że po prostu chciałem zobaczyć mistyczną Wyspę Sprawiedliwości.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Więc musisz być jednym z tych szaleńców, którzy przybywają tu z własnej woli... Cóż, teraz będziesz miał dość czasu, by zobaczyć Wyspę i najeść się jej 'sprawiedliwości'.";
			link.l1 = " A czy według twojego sarkazmu są jakieś problemy ze sprawiedliwością?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Nie, wszystko jest w porządku. Ale z jakiegoś powodu musimy płacić piratom za nasze jedzenie, które niedawno było darmowe dla wszystkich. A kiedy klany zaczynają walczyć na naszej części Wyspy, mamy siedzieć wewnątrz statków, aby uniknąć postrzałów lub rzezi. \nMam na myśli to, że im wolno robić, co chcą na naszym terytorium, ale my nie możemy robić tego samego na ich. Ale w porządku, już żadnych problemów...";
			link.l1 = "Rozumiem. Dobrze, cieszę się, że cię poznałem. Do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Czy mieszkasz tu od długiego czasu?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Czy na Wyspie jest coś interesującego?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Co sądzisz o klanach?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy piraci cię dręczą?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Wybacz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Od bardzo dawna. Już dawno straciłem rachubę. To musi być siedemnaście lat... nie, może osiemnaście... a może dwadzieścia? Jaki mamy teraz rok?";
			link.l1 = "Widzę... Więc jesteś tu staruszkiem?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Relatywnie. Wciąż pamiętam czasy, gdy bukanierzy handlowali z nami, a najśmielsi i najbystrzejsi Narwale wypływali na kontynent, by wymieniać zapasy na towary z ładowni statków. Ale jest wielu ludzi, którzy nigdy nie widzieli żadnych innych miejsc poza Wyspą, bo tu się urodzili. Nie są tu tylko starzy mieszkańcy, ale tubylcy.";
			link.l1 = "Interesujące...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Tak, to prawda. Wszystko tutaj jest interesujące. Przejdź się i przekonaj się sam. Popływaj wokół centralnej części Wyspy Sprawiedliwości. Odwiedź tawernę, sklep i kościół. Problem w tym, że zainteresowanie spadnie za tydzień, mogę ci to obiecać.";
			link.l1 = "Zrozumiałem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "A co my mamy myśleć o tych bandytach? Staram się trzymać od nich z daleka, to wszystko. Przynajmniej Narwale robią coś dobrego dla Wyspy, mają wśród siebie bardzo utalentowanych rzemieślników, ale Rivados to tylko dzikusy i poganie\nWciąż żyją według swoich afrykańskich praw, tak jak setki lat temu. Zwierzęta. Jedyną rzeczą, której się nauczyli, jest używanie broni palnej. Mówią, że odprawiają rytuały kanibalizmu!";
			link.l1 = "Taki koszmar...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "To, że sprzedają nam nasze własne jedzenie, trochę mnie niepokoi, ale nie robią obywatelom krzywdy. W rzeczywistości, przeciwnie, wprowadzili porządek w klanach i zapobiegają przemocy\nBył tu obywatel, który sprawiał problemy i machał szablą. Nawet zranił dwóch innych miejscowych. Piraci zabrali go do Tartaru na kilka tygodni. Teraz człowiek jest cichy i spokojny. Nie widujemy go często, zewnętrzny pierścień to jego nowy dom...";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co tam robisz, co? Złodziej!","Popatrz tylko! Ledwie pogrążyłem się w rozmyślaniach, a ty już postanowiłeś zajrzeć do mojej skrzyni!","Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera jasna!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się sprawdzić moje skrzynie? Nie ujdziesz z tym na sucho!";
			link.l1 = "Zgłupiała dziewczyna!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj swoją broń. Sprawia, że się denerwuję.","Wiesz, bieganie z ostrzem nie jest tu tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak powiadasz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem miasta i proszę cię, abyś opuścił swój miecz.","Słuchaj, jestem obywatelem miasta i proszę cię, byś schował swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ostrożnie, przyjacielu, gdy biegniesz z bronią. Mogę się zdenerwować...","Nie lubię, gdy mężczyźni chodzą przede mną z gotową bronią. To mnie przeraża...");
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
