// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nie mam ochoty z tobą rozmawiać. Atakujesz spokojnych mieszkańców bez powodu i prowokujesz ich do walki. Zjeżdżaj, bezbożniku!";
				link.l1 = "Jak sobie życzysz...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Nie dziwi mnie, że przetrwałeś. Tajemnicze są ścieżki Pana. Życie i śmierć są w Jego rękach.";
				link.l1 = "Całkowicie się z tobą zgadzam, bracie Julianie.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Witaj w świętym kościele naszej Wyspy, mój synu. Drzwi są zawsze otwarte dla ciebie. Jestem brat Julian i cieszę się, widząc każdego sługę naszego wielkiego Pana.";
				link.l1 = TimeGreeting()+". Nazywam się "+GetFullName(pchar)+"Miło cię poznać, bracie Julianie.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"!"+TimeGreeting()+"Chcesz czegoś?";
				link.l1 = "Chcę zadać ci kilka pytań o wyspę.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = " Czy mogę kupić od ciebie mikstury?";
				link.l2.go = "potion";
				link.l3 = "Masz jakieś święte przedmioty na sprzedaż?";
				link.l3.go = "amulet";
				link.l5 = "Chciałem się tu pomodlić i zobaczyć, jak się masz. Do zobaczenia!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mam nadzieję, że będziesz częściej odwiedzał nasz kościół. Zadbaj o swoją duszę, mój synu. Potrafię także uleczyć twoje ciało, pracuję tutaj nie tylko jako pastor, ale także jako lekarz.";
			link.l1 = "Chciałbym zadać kilka pytań o wyspę.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Czy mogę kupić od ciebie jakieś mikstury?";
			link.l2.go = "potion";
			link.l3 = "Masz jakieś święte przedmioty na sprzedaż?";
			link.l3.go = "amulet";
			link.l4 = "Muszę iść, bracie Julianie. Do zobaczenia!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Oczywiście, synu. Jakiego eliksiru potrzebujesz?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Prosta mikstura lecznicza.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Eliksir leczniczy.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Antidotum.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Mieszanka ziołowa.";
				link.l4.go = "potion4";
			}
			link.l5 = "Przykro mi, bracie Julianie, zmieniłem zdanie.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Eliksir? 90 peso, mój synu.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Weź ich, bracie Julian.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Nie mam teraz wystarczająco monet... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Eliksir? 500 pesos, mój synu.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Weź ich, bracie Julianie.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Nie mam teraz wystarczającej ilości monet... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Antidotum? 200 pesos, mój synu.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Weź je, bracie Julianie.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Nie mam teraz wystarczająco monet... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Mieszanka? 900 pesos, mój synu.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Weź je, bracie Julianie.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Nie mam teraz wystarczająco monet... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Proszę. Weź swoje lekarstwo. Niech cię Bóg prowadzi!";
			link.l1 = "Dziękuję, bracie Julian.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Tak, mogę dać ci kilka świętych amuletów, które chronią ludzi przed ranami i chorobami. Cena jest taka sama dla każdego amuletu - dziesięć złotych dublonów. Mogę ci zaoferować "+XI_ConvertString(npchar.quest.amulet)+" dzisiaj.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Tak, chcę kupić ten amulet. Oto twoje złoto.";
					link.l1.go = "amulet_pay";
					link.l2 = "Nie potrzebuję tego amuletu, bracie Julianie. Poczekam, aż zdobędziesz to, czego potrzebuję.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Nie mam teraz wystarczająco monet... Wrócę później.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Niestety, synu, nie mam nic więcej. Przyjdź do mnie innego dnia, może coś dla ciebie znajdę.";
				link.l1 = "Umowa, bracie Julianie.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dziękuję, mój synu. Twoje pieniądze dobrze posłużą. Weź swój amulet i niech Bóg cię błogosławi!";
			link.l1 = "Wdzięczność, bracie Julian.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Słucham.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Jak się tu dostałeś, bracie Julianie?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Ilu ludzi jest w twojej parafii?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Kto tutaj sprzedaje rzeczy?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Czy istnieje ryzyko zniszczenia Wyspy? Może burze?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Bez pytań. Przykro mi...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Tak jak wielu miejscowych, mój synu. Mój statek został zatopiony przez burzę podczas rejsu z Hawany do Nowej Hiszpanii. Dzięki Bogu, przeżyłem to i teraz służę Jemu tutaj, pomagając biednym duszom znaleźć ich prawdziwą drogę.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Mniej niż bym chciał. Większość Narwali woli przemoc niż miłosierdzie, a Rivados to biedne i zagubione owieczki. Ślepo wykonują swoje pogańskie rytuały, narażając swoje nieśmiertelne dusze na niebezpieczeństwo. Wśród nich jest jeden niebezpieczny czarodziej, który musi być oczyszczony przez Świętą Inkwizycję.";
			link.l1 = "Widzę...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero jest właścicielem tawerny na Fleron, tam znajdziesz jedzenie, napitki i ciepłe łóżko. Axel Yost sprzedaje szeroki asortyment towarów na 'Esmeraldzie'. Zapytaj ludzi na ulicach, mój synu, wielu z nich znajduje ciekawe rzeczy na zewnętrznym pierścieniu.";
			link.l1 = "Dziękuję!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "To wszystko jest w rękach naszego Pana, mój synu. Wierzymy w Niego i ufamy Mu. Poważne kłopoty zawsze trzymały się z dala od naszej Wyspy - burze często zdarzają się poza nią, ale tutaj zawsze jest spokojnie.";
			link.l1 = "Dzięki. Uspokoiłeś mnie.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Co ty tam robisz, co? Złodzieju!","Spójrz tylko na to! Ledwie pogrążyłem się w zadumie, a ty postanowiłeś sprawdzić moje skrzynie!","Postanowiłeś zajrzeć do moich skrzyń? Nie ujdzie ci to na sucho!");
			link.l1 = "Cholera!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Co?! Zdecydowałeś się przeszukać moje skrzynie? Nie ujdzie ci to na sucho!";
			link.l1 = "Głupia dziewka!";
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
			dialog.text = LinkRandPhrase("Słuchaj, lepiej schowaj broń. Denerwuje mnie.","Wiesz, bieganie z ostrzem nie jest tutaj tolerowane. Schowaj je.","Słuchaj, nie udawaj średniowiecznego rycerza biegającego z mieczem. Odłóż go, to do ciebie nie pasuje...");
			link.l1 = LinkRandPhrase("Świetnie.","Dobrze.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i proszę cię, abyś schował swój miecz.","Słuchaj, jestem obywatelem tego miasta i proszę cię, schowaj swój miecz.");
				link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak mówisz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bądź ostrożny, kumplu, biegając z bronią. Mogę się zdenerwować...","Nie lubię, gdy ludzie chodzą przede mną z gotową bronią. To mnie przeraża...");
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

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
