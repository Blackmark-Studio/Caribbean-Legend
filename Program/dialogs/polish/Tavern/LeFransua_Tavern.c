// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"... ","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu...","Więcej pytań, jak przypuszczam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do powiedzenia."),"Umph, gdzież podziała się moja pamięć...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Słuchaj, "+npchar.name+", przybyłem do ciebie w nietypowej sprawie. Muszę znaleźć człowieka, który chciałby spokojnego, cichego życia nad zatoką jako pomocnik kupca w sklepie w Saint-Pierre. Wynagrodzenie jest dobre, a dach nad głową ma zapewniony. Czy mógłbyś zasugerować, do kogo mógłbym się zwrócić?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Przybyłem w sprawie beczek wina, które masz załadować na mój statek do dostarczenia do Gwadelupy...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Wiesz, "+npchar.name+", szukam mojego przyjaciela. Miał tu przybyć i źle się czuł. Może jego przyjaciele mu pomogli...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm.. Mamy tutaj kilku ludzi, którzy chcieliby przejść z życia marynarza do życia szczura lądowego. Mogę ci pomóc, ale powiem od razu: to nie będzie za darmo.";
			link.l1 = "Heh! A ile chcesz?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "Tysiąc sztuk ośmiu. I nie będziesz musiał nic robić, za godzinę twoi kandydaci do pracy będą w mojej tawernie, wielu kandydatów. Będziesz mógł z nimi porozmawiać i wybrać tego, który najbardziej ci odpowiada.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... W porządku, tutaj, weź tysiąc!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Przepraszam, ale nie mam tyle pieniędzy!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Nie martw się, kumplu. Dostaniesz połowę tej sumy z powrotem od kandydata. Powiem mu, że to koszt twoich usług, he he... Nie dadzą więcej niż pięćset. Wpadnij do mojej tawerny za godzinę, do tego czasu znajdę ludzi, których potrzebujesz, czekających na ciebie.";
			link.l1 = "Dobrze. Wrócę za godzinę, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Przykro mi, że też nie masz takiej sumy. Ale wiesz sam, takie sprawy nie załatwia się tylko za 'dziękuję'. Więc...";
			link.l1 = "Rozumiem. Ale naprawdę nie mam pieniędzy. Dobrze, do widzenia...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "O czym ty mówisz, kamracie? O jakim winie mówisz?";
			link.l1 = "Zostałem przysłany do ciebie przez człowieka o imieniu Walter Catcher. Powiedział, że potrzebujesz statku do przewiezienia ładunku wina na Gwadelupę za dziesięć tysięcy pesos. I że potrzebujesz dokładnie mojego statku do tej roboty...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Słuchaj kamracie, nie zajmuję się winem, nie potrzebuję twoich usług i nie znam żadnego Waltera Catchera.";
			link.l1 = "Co za heca! Więc ten Łapacz wcale nie został wysłany przez ciebie... Więc o co chodzi w tej całej komedii?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh! Cóż, to albo jakiś błąd, albo kiepski żart, albo...";
			link.l1 = "Albo co?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Nie rozumiesz sam? Ktoś musiał cię zwabić do Le Francois, po co, tego nie wiem. Na twoim miejscu, pośpieszyłbym się i wyniósł z stąd, będąc jak najbardziej ostrożnym. To pachnie brudnym interesem, przyjacielu...";
			link.l1 = "Chyba masz rację. Nie podobała mi się gęba tego Catchera. Dobra, posłucham twojej rady. Żegnaj, Cesarze!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "Tak, twój przyjaciel tu przybył, kapitanie. Dotarł wczoraj i wynajął pokój na górze. Jego towarzysze też tu są, he-he... Siedzą tam. Zapytaj ich!";
			link.l1 = "I'm looking for a crew.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
