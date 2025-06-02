// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! Jestem "+GetFullName(NPChar)+", nowy gubernator tej dziury. Nie będzie łatwo zaprowadzić porządek wśród miejscowych łotrów, ale nie stanowią już zagrożenia dla hiszpańskich kolonii.";
					Link.l1 = "Jestem rad, że mogę cię poznać. Jestem kapitanem "+GetFullName(Pchar)+"Przykro mi, ale muszę iść.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+"Jestem zajęty, naprawdę zajęty, muszę kontrolować lokalnych oprychów, aby zapobiec wszelkim zagrożeniom dla hiszpańskich kolonii.";
					Link.l1 = "Nie będę cię wtedy niepokoić.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Masz mi coś do powiedzenia? Nie? Więc "+GetSexPhrase("zmykaj stąd!","Proszę cię, byś mi nie przeszkadzał.")+" ","Myślę, że wyraziłem się jasno...","Chociaż wyraziłem się jasno, wciąż mnie irytujesz!","Cóż, jesteś niezmiernie "+GetSexPhrase("zbyt niegrzeczne, mon cheri","taka nieuprzejmość, dziewczyno","taka niegrzeczność, dziewczyno")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Odchodzę.","Tak, "+npchar.name+"Widzę to.","Przepraszam, "+npchar.name+"...","Ała...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Czy masz dla mnie jakieś zadanie?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Znalazłem trop, ale potrzebuję trochę monet – 30.000 pesos, by wywabić szczura z jego nory.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Oto list, który znalazłem przy trupie przemytnika";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Zrobione. Norman Vigo i jego statek należą do morskiego diabła.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm.. Praca, mówisz? Właściwie, dobrze, że mnie zapytałeś. Potrzebuję człowieka z zewnątrz. Chcę się czegoś dowiedzieć w najbliższym mieście, ale moi ludzie są tam znani. Nie mogę obiecać dużo, ale coś dostaniesz.";
			link.l1 = "Jaka jest misja?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Przykro mi, ale nie zaryzykuję dla kilku strzępów. Żegnaj.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "W takim razie słuchaj, miesiąc temu zawarłem umowę na dostarczenie 200 niewolników z kapitanem szkunera 'Saintblue'. Chciałem je sprzedać lokalnemu właścicielowi plantacji. Czas minął, a klient zaczął się niepokoić, ale wczoraj powiedziano mi, że szkuner widziano niedaleko wyspy. Ale! Kapitan się nie pojawił. Dziś mój klient zażądał zwrotu zaliczki i powiedział, że zaproponowano mu zakup niewolników od innego sprzedawcy. Drożej, ale cała grupa niewolników od razu.";
			link.l1 = "I co? Mam znaleźć 200 niewolników w kilka dni, żeby uratować cię przed utratą zaliczki? Dla kilku monet?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Oczywiście, że nie. Wyglądam na idiotę? I tak mu nie zwrócę zaliczki. Ale potrzebuję dowodu, że te niewolnicy, które mu zaoferowano, są moimi. Znajdź tych, którzy zaproponowali mu nową umowę, a otrzymasz swoje 10 000 pesos. Zgoda?";
			link.l1 = "Jestem w. Masz jakieś podejrzenia, kto to może być?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Nie ma mowy. Szukaj kogoś innego, tylko za 10.000? Przykro mi, ale to nie zadziała.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Gdybym miał jakiekolwiek pomysły, nigdy nie skorzystałbym z twoich usług. Ci ludzie już byliby martwi. Ale jestem ciekaw, jak dowiedzieli się o ładunku 'Saintblue' i moim kliencie. Wygląda na to, że było to dla nich całkiem łatwe. Widzisz teraz?";
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
			dialog.text = "Dokładnie! Szukam go. Zabijanie moich konkurentów i zwracanie moich niewolników nie jest Twoim priorytetem. Potrzebuję tego szczura, a tak naprawdę jego głowy na rożnie, jeśli mam być szczery. Teraz widzisz, dlaczego moi ludzie nie powinni wiedzieć nic o twojej misji? Będę podejrzewał każdego, dopóki nie dowiem się, kto sprzedaje informacje. I naprawdę tego nie chcę...";
			link.l1 = "Rozumiem. W takim razie będę się trzymać w cieniu. Wyruszam w drogę.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trzydzieści tysięcy mówisz? To duża suma... Mogę ci dać tylko 5.000 peso, to wszystko, co teraz mam. I nawet nie próbuj uciekać z pieniędzmi, bo cię znajdę i powieszę na najbliższym płocie! Rozumiesz?";
			link.l1 = "Dobrze, daj mi wtedy pięć tysięcy...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Weź to. Czekam na wynik twoich poszukiwań.";
			link.l1 = "Będzie dobrze.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Doskonałe wieści! Byłem pewny, że ci się uda. Mam pewne intrygujące informacje.";
			link.l1 = "Zrobiłem swoją robotę i chcę otrzymać moje dziesięć tysięcy.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Jasne, oto twoja nagroda. Ale nie uciekaj, mam dla ciebie jeszcze jedno zadanie.\nPfaifer jest członkiem załogi Normana Vigo z lugra 'Septima'. Jestem pewien, że Norman Vigo to szczur, nawet jeśli jest jednym z nas. Ostatnio widziano go w wodach wyspy. Twoim zadaniem jest posłać tego szczura do morskiego diabła. Nie zawiodłeś mnie za pierwszym razem, dlatego chcę cię poprosić, byś zajął się tą sprawą również. Zapłacę ci 15.000 pesos. Zgoda?";
			link.l1 = "Zajmę się tym! Uważaj zdrajcę za martwego.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Wiesz, nie chcę brać w tym udziału... i tak nie mam czasu. Przepraszam, ale muszę iść.";
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
			dialog.text = "Ja wiem, ja wiem. Moi ludzie obserwowali bitwę i już zdali mi raport o twoim bezbłędnym zwycięstwie. Dobrze, wykonałeś swoje zadanie dobrze. Oto 15.000 pesos, jak obiecałem. I dziękuję, pomogłeś mi z wielką sprawą.";
			link.l1 = "To dobrze, cieszyłem się, że mogłem pomóc! Ale teraz muszę iść, byłem tu zbyt długo i mam wiele rzeczy do zrobienia. Żegnaj!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Witam, nazywam się Alistair Good. Zostałem wybrany na głowę bukanierów po śmierci Mansfelda.";
			link.l1 = "Miło cię poznać, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Nie mam czasu, aby z tobą rozmawiać. Odwiedź mnie później.";
			link.l1 = "Już odchodzę.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Weź","Zdobyć")+" precz!","Odejdź z mojego domu!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Nie zawracaj mi głowy, pamiętaj o tym.";
        			link.l1 = "Rozumiem.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
