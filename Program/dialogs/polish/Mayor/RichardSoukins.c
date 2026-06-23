// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Masz do mnie jakąś sprawę? Nie? To wynoś się!";
			link.l1 = "Już odchodzę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == int(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Czy masz dla mnie jakąś robotę?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Złapałem trop, ale potrzebuję trochę monet - 30.000 pesos, by wywabić szczura z jego nory.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Spójrz na ten list, który znalazłem przy zwłokach przemytnika";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Zrobione. Norman Vigo i jego statek poszli do morskiego diabła.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... praca, powiadasz? Właściwie dobrze, że zapytałeś. Potrzebuję kogoś z zewnątrz. Chcę dowiedzieć się czegoś w najbliższym mieście, ale moi ludzie są tam znani. Nie mogę obiecać wiele, ale coś dostaniesz.";
			link.l1 = "Świetnie! Jaka jest misja?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Przykro mi, ale nie zaryzykuję dla kilku skrawków. Żegnaj.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "W takim razie posłuchaj, miesiąc temu miałem umowę na dostarczenie 200 niewolników z kapitanem szkunera 'Saintblue'. Chciałem je sprzedać lokalnemu właścicielowi plantacji. Czas minął i klient zaczął się niepokoić, ale wczoraj powiedziano mi, że szkuner widziano niedaleko wyspy. Ale! Kapitan się nie pojawił. Dziś mój klient zażądał ode mnie zwrotu zaliczki i powiedział, że zaproponowano mu zakup niewolników od innego sprzedawcy. Droższych, ale cały tłum niewolników i od razu.";
			link.l1 = "I co? Mam znaleźć 200 niewolników w kilka dni, by uratować cię przed utratą zaliczki? Za parę monet?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Na pewno nie. Czy wyglądam na idiotę? I tak mu nie zwrócę jego zaliczki. Ale potrzebuję dowodu, że ci niewolnicy, którzy mu zostali zaoferowani, są moimi. Znajdź tych, którzy zaoferowali mu nową umowę, a dostaniesz swoje 10 000 pesos. Umowa?";
			link.l1 = "Zgadzam się. Masz jakieś podejrzenia? Kto mógł to zrobić?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Nie ma szans. Poszukaj kogoś innego. Tylko za 10.000? Przykro mi, ale to nie zadziała.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Gdybym miał jakieś pomysły, nigdy nie skorzystałbym z twoich usług. Ci ludzie już byliby martwi. Ale jestem ciekaw, skąd się dowiedzieli o ładunku 'Saintblue' i moim kliencie. Wygląda na to, że było to dla nich dość łatwe. Widzisz teraz?";
			link.l1 = "Tak, ktoś cię zdradził.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Dokładnie! Szukam go. Zabijanie moich konkurentów i zwracanie moich niewolników nie jest twoim priorytetem. Potrzebuję tej szczury, szczerze mówiąc, jego głowy na szpikulcu. Widzisz teraz, dlaczego moi ludzie nie powinni wiedzieć nic o twojej misji? Będę podejrzewać wszystkich, dopóki nie dowiem się, kto sprzedaje informacje. I naprawdę tego nie chcę...";
			link.l1 = "Rozumiem. W takim razie będę się trzymał na uboczu. Już idę.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trzydzieści tysięcy powiadasz? To duża suma... Mogę ci dać tylko 5.000 pesos, to wszystko, co mam teraz. I nawet nie próbuj uciekać z pieniędzmi, bo cię znajdę i powieszę na najbliższym płocie! Zrozumiano?";
			link.l1 = "Dobrze, daj mi wtedy pięć tysięcy...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Weź to. Czekam na wynik twoich poszukiwań.";
			link.l1 = "Wszystko będzie dobrze.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Doskonałe wieści! Byłem pewien, że ci się uda. Mam pewne intrygujące informacje.";
			link.l1 = "Zrobiłem swoją robotę i chcę dostać moje dziesięć tysięcy.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Jasne, oto twoja nagroda. Ale nie uciekaj, mam jeszcze jedno zadanie dla ciebie.\nPfaifer jest członkiem załogi Normana Vigo z lugra 'Septima'. Jestem pewien, że Norman Vigo to szczur, nawet jeśli jest jednym z nas. Ostatnio widziano go na wodach wyspy. Twoim zadaniem jest wysłać tego szczura do diabla morskiego. Nie zawiodłeś mnie za pierwszym razem, więc chcę cię poprosić, byś zajął się tą sprawą również. Zapłacę ci 15.000 pesos. Umowa?";
			link.l1 = "Już się za to biorę! Uważaj zdrajcę Normana Vigo za martwego.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Wiesz, nie chcę brać w tym udziału... Nie mam na to czasu. Przykro mi, ale muszę odmówić.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Tak, tak. Moi ludzie obserwowali bitwę i już zdali raport o twoim bezbłędnym zwycięstwie. Dobrze, wykonałeś swoją robotę doskonale. Oto 15.000 pesos, które obiecałem. I dziękuję, bardzo mi pomogłeś.";
			link.l1 = "W porządku, cieszyłem się, że mogłem pomóc! Ale teraz muszę iść, byłem tu zbyt długo, a mam wiele rzeczy do zrobienia. Żegnaj!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
