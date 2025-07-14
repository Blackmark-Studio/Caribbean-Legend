// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
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
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat("Czy masz mi coś do powiedzenia? Nie? To wynoś się stąd!","Myślę, że wyraziłem się jasno, przestań mnie denerwować.","Chociaż jasno się wyraziłem, nadal mnie denerwujesz!","Racja, zaczynam mieć dość tej bezczelności.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Już odchodzę.","Oczywiście, Jacques...","Przykro mi, Jacques...","Auć...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Czyś ty oszalał? Chciałeś się zabawić w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce...","Wygląda na to, że oszalałeś, chłopcze. Chciałeś trochę rozprostować ręce? Bez urazy, ale nie masz tu nic do roboty. Zgiń przepadnij!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomóż mi rozwiązać ten problem...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Muszę z tobą porozmawiać, Jacques... Na osobności.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Przybywam z Saint Martin, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "Kiedy przestaniesz szczekać i zaczniesz mówić jak człowiek, Jacques? Nie spodziewałeś się mnie zobaczyć?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Przychodzę w sprawie waszego więźnia.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Witaj, Jacques, jestem tutaj z powodu twojej misji.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Jestem tu w sprawie waszego więźnia.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Słyszałem, że zajmujesz się interesami związanymi z więźniami...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! Czego potrzebujesz tym razem?","Zapomniałeś mi coś powiedzieć? Słucham.","Jak długo to będzie trwało... Jeśli nie masz nic do roboty, to nie zawracaj innym głowy!","Prosiłeś mnie o uprzejmość. Ale ja żądam tego samego od ciebie!","powtórz",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("To nic. Po prostu wizyta.","Niczego...","Dobrze...","Masz rację. Przepraszam.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Czyś ty oszalał? Chciałeś pobawić się w rzeźnika? Wszyscy piraci są na ciebie wściekli, chłopcze, lepiej opuść to miejsce...","Wydaje się, że oszalałeś, chłopcze. Chciałeś trochę rozprostować ręce? Bez urazy, ale nie masz tu nic do roboty. Zjeżdżaj!");
				link.l1 = RandPhraseSimple("Słuchaj, chcę naprawić sytuację...","Pomóż mi rozwiązać ten problem...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Przyszedłem w sprawie twojego więźnia.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Cześć, Jacques, chodzi o twoją misję.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Przyszedłem porozmawiać o twoim więźniu.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Słyszałem, że zajmujesz się interesami związanymi z więźniami...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Czy wiesz, że zawracanie mi głowy jest ryzykowne? Dobrze, słucham cię.";
			link.l1 = "Mam dług. Duży. Czas spłaty zbliża się szybko, a ja nie mam monet. Życzliwi ludzie szeptali, że masz talent do układania planów i zawsze wiesz, gdzie złapać dużą wygraną...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Słuchaj, chłopcze! Jestem Jacques the Kindman tylko dla tych, którzy są mi lojalni. Dla innych jestem Barbazonem, a czasem samym Lucyferem. Skąd mogę wiedzieć, że mogę ci zaufać?";
			link.l1 = "Spróbuj mnie. Przysięgam, że tego nie pożałujesz!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Przypuszczam, że wiesz, co Jacques Dobroduszny robi ludziom, którzy go oszukują, prawda? Tak czy inaczej, oszczędzę ci strasznych szczegółów. Mam dla ciebie małą misję. Jeśli ci się powiedzie, wszystkie twoje finansowe problemy znikną.";
			link.l1 = "Nie wątp we mnie, brałem udział w wielu bitwach i...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Zamknij się i słuchaj mnie! Kilka tygodni temu holenderski patrol złapał jednego z moich ludzi niedaleko Saint Martin. Dostarczał mi holenderski jedwab. Jest bardzo rzadki, Holendrzy przywożą go tutaj tylko w małych partiach na potrzeby marynarki Kompanii.\nWięc, udało mi się zdobyć sześć bel jedwabiu, a Simon Morel miał mi je dostarczyć na swojej brygantynie 'Salt Dog', ale przypadkiem napotkał holenderski patrol. Albo i nie przypadkiem. Tak przynajmniej powiedział mi nawigator Morela, który twierdzi, że był jedynym, który przeżył walkę.\nOn również dał mi dziennik pokładowy Morela, który potwierdza tę historię. Według dziennika, Morel wyrzucił jedwab podczas próby ucieczki. To dziwne, prawda? Jedwab jest lekki. Powinni byli wyrzucić swoje działa, i tak nie mieli szans przeciw patrolowi.";
			link.l1 = "Coś tu naprawdę jest nie w porządku.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Wszystko jest możliwe. Wiele odważnych ludzi dla mnie pracuje, a dużo mniej mądrych. Bez urazy, heh. Musisz sprawdzić miejsce, gdzie Morel pozbył się ładunku. To jest 21 stopni 10' na północ i 61 stopni 30' na zachód według dziennika kapitańskiego.\nHolendrzy nawijają jedwab na korkowe pręty, więc bele muszą wciąż unosić się nad wodą. Musi być sześć bel. Wyrusz natychmiast, czas jest kluczowy.";
			link.l1 = "Jestem w drodze!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Świetnie! Czy znalazłeś mój jedwab?";
			link.l1 = "Tak, sześciu z nich, jak mówiłeś.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Tak. Ale było ich więcej, niż mówiłeś, dziewięciu, a nie sześciu. Przyprowadziłem ich wszystkich tutaj, twoja część to dowiedzieć się, jak to się mogło stać.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Niewłaściwa odpowiedź. Powinno być dziewięć bel. A jeśli znalazłeś sześć z nich, to musiałeś znaleźć resztę. Więc albo jesteś szczurem, albo po prostu leniwym idiotą. Jesteś mi winien trzy bele jedwabiu i trzy więcej jako... 'moralne zadośćuczynienie' za próbę oszukania mnie.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Taki sprytny dupek! Zapamiętam to. Oto twoja jedwab i zapomnijmy o mojej winie.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Powiedziano mi, że było sześć bel, ani jednej więcej. Dałem ci wszystko, co znalazłem i gówno mnie obchodzą twoje myśli. Nie mam więcej jedwabiu.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Dobrze. Mam nadzieję, że to się nie powtórzy, bo chcę zlecić ci ważne zadanie. Ile pieniędzy chcesz zarobić?";
			link.l1 = "Pieniądze zawsze są mile widziane, na teraz pięćdziesiąt tysięcy pesos wystarczy.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "O, tak teraz mówisz! Nie ujdzie ci to na sucho. Ostrzegałem cię - nie próbuj mnie oszukać, do cholery! Straż! Jest cholerny szczur w rezydencji!";
			link.l1 = "Gówno!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Dobra robota. Sprawdzałem twoją chciwość i zdałeś mój test. Musiało być dziewięć beli. Jedna z nich jest twoja. Teraz możemy porozmawiać poważnie. Ile pieniędzy potrzebujesz?";
			link.l1 = "Pieniądze zawsze są mile widziane, na razie pięćdziesiąt tysięcy pesos będzie w sam raz.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Masz okazję zarobić jeszcze więcej. Jeden poważny człowiek poprosił mnie, abym znalazł zaufanego faceta takiego jak ty do jednej delikatnej i niebezpiecznej misji. Ten człowiek jest bardzo bogaty i hojnie cię nagrodzi, jeśli go nie zawiedziesz.";
			link.l1 = "Jestem gotów.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Dobrze. Słuchaj teraz. Musisz znaleźć jego agenta o imieniu 'Knave'. Jest kapitanem polakry 'Marlin', to wszystko, co o nim wiem. Znajdziesz go w Kapsterville. Hasło to 'polowanie się rozpoczęło'. Powie ci, co robić. Nie jesteś mi nic winien. Chcę ci po prostu pomóc. Jeśli będziesz miał szczęście, spotkamy się ponownie.";
			link.l1 = "Dzięki za pomoc. Już się zbieram!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Co?! Wyrwę ci twoje...";
			link.l1 = "Nie zrobisz tego, Barbazon. Sprawdźmy nasze karty! Pracuję dla Jana Svensona. Odkryłem twoje spiski z Jackmanem. Wiem wszystko, co planowałeś i jaką rolę też miałeś. Jackman i jego brat są martwi, pierwszy zabił Blaze'a Sharpa i to zadecydowało o jego losie, drugi nie był wystarczająco rozmowny, obawiam się...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Cholera! Tyrex nigdy mi tego nie wybaczy, ale ja wciąż..";
			link.l1 = "Nie rób nic głupiego, Jacques. Wiedziałem, że to nie będzie łatwa rozmowa, więc się zabezpieczyłem. Spójrz za okno... twoja chata jest otoczona przez moich muszkieterów. Moi ludzie są wokół twojej wioski, a grupa szturmowa stoi tuż za bramami. Chcesz zacząć rzeź? Łatwizna!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Cholera! Czego chcesz?";
			link.l1 = "Nie uwierzysz mi, Barbazonie, ale wszystko, czego chcę, to... Pokój! Chcę pokoju. Dlatego nie powiem Tyrexowi o twoim udziale w tej spisku przeciwko niemu. Ale tylko jeśli zrobisz, co chcę...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Czego ode mnie chcesz? Pieniędzy? Ile?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "O nie, zostaw to swoim agentom bez mózgu. Potrzebuję czegoś innego. Potrzebuję twojego głosu dla Stevena Dodsona.";
			}
			else
			{
				link.l1 = "O nie, zostaw to swoim agentom bez mózgu. Potrzebuję czegoś innego. Potrzebuję Twojego głosu na Marcusa Tyrexa.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Serio? Niech pomyślę... a co, jeśli powiem nie?";
			link.l1 = "Wtedy staniesz sam. Absolutnie sam. Svenson, Tyrex i Hawk wystąpią przeciwko tobie."+sTemp+" Pokażę im tylko list Knave'a, brata Jackmana, a moje słowo także będzie uznane. A jak myślisz, jak długo będziesz siedział na swoim wygodnym miejscu po tym?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Jastrząb? On żyje?!";
			link.l1 = "Tak jest. Uratowałem go z pułapki zastawionej przez Jackmana. Zatem najbliższy przyjaciel Jacoba stanie się jego krwawym wrogiem. I dołączę do nich, pamiętaj o tym, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman nie jest moim przyjacielem! Do diabła z tobą! Zagoniliście mnie w kozi róg!";
			link.l1 = "Bzdura. Oddaj swój głos na człowieka, o którym ci mówiłem, a nic się dla ciebie nie zmieni. Już ci mówiłem, Jacques, chcę pokoju. Mogę sprawić, że wszyscy baronowie cię znienawidzą, ale tego nie zrobię... jeszcze.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Dobrze. Zgoda. Masz moje słowo. Oto, weź mój kawałek kamienia, potrzebujesz go, prawda?";
			link.l1 = "Dokładnie. Cieszę się, że doszliśmy do porozumienia, Jacques. Weź list 'Nikczemnika' jako słodką pamiątkę. A najlepiej spal go, nie chcesz, żeby go znaleziono. Ach, i jeszcze jedno...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Jeszcze jedna rzecz?! Czego jeszcze ode mnie chcesz?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Przypomnę ci coś. Niezbyt dawno temu wysłałeś swego psa Ignacio Marco, by mnie zabił. To ja go zabiłem. To ja pogrzebałem twój plan splądrowania hiszpańskiego galeonu ze złotem. To ja wysłałem twoich przyjaciół w hiszpańską zasadzkę pod Saint Martin. Nazywam się Charlie Prince! Już skończyliśmy, Jacques, i bądź bardziej uprzejmy następnym razem, gdy się zobaczymy. Wierz mi, 'chłopcze', spotkamy się ponownie, i to więcej niż raz, jak sądzę.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Przypomnę ci coś. Niedawno wysłałeś swojego psa Ignacia Marco, by mnie zabił. To ja go zabiłem. To ja pogrzebałem twój plan splądrowania hiszpańskiego galeonu ze złotem. Nazywam się Charlie Prince! Teraz jesteśmy załatwieni, Jacques, i bądź dla mnie milszy przy następnym spotkaniu. Wierz mi, 'chłopcze', spotkamy się ponownie, i to nie raz. Nie zapominaj, że mam po swojej stronie każdego barona piratów. Żegnaj, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Bądź bardziej uprzejmy następnym razem, gdy się spotkamy. Wierz mi, 'chłopcze', jeszcze się spotkamy, i to nie raz, zgaduję. Nie zapominaj, każdy piracki baron jest po mojej stronie. Żegnaj, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "Nie zapomnij, że każdy piracki baron jest po mojej stronie. Żegnaj, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Myślisz, że mam tu tylko jednego więźnia? Nazwij go.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Jest tutaj?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Był. Sprzedałem go temu właścicielowi plantacji z Barbadosu - pułkownikowi Bishopowi, kiedy był tutaj tydzień temu.";
				link.l1 = "Cholera...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ach, w końcu. Myślałem, żeby sprzedać go właścicielowi plantacji z Barbadosu, będzie tu za tydzień lub dwa... Masz okup?";
				link.l1 = "Spójrz, jest mały problem... Właściwie, nie mam aż tyle pieniędzy. Ale jestem gotów do pracy.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "To dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 pesos. Gdzie mogę go znaleźć?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Byłeś za wolny... A dlaczego w ogóle się nim przejmujesz? Rozmawiałem tylko z jego krewnymi.";
			link.l1 = "Poprosili mnie, abym tu przyszedł.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "No cóż, jesteś spóźniony. Nic nie mogę zrobić.";
			link.l1 = "Słuchaj, za ile go sprzedałeś, jeśli to nie tajemnica?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, nie jest. Ale nie powiem ci... Będziesz się śmiał, jeśli to zrobię. Ha-ha-ha-ha! Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Cóż, "+pchar.name+", wiesz, to tak nie działa. Wróć z pieniędzmi, a dostaniesz swojego słabeusza, ha-ha.";
				link.l1 = "Dobrze. Do zobaczenia.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Cóż, cóż... Mam pewien interes... Nawet nie wiem, jak zacząć. Muszę zatopić jednego pirata, który przekroczył granicę.";
				link.l1 = "Czy nie można go po prostu zabić w dżungli?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "To nie tak działa interes, wiesz... Nie potrzebuję jego śmierci, muszę nauczyć niektórych, by nie kradli mojej części łupu. Ale jeśli pójdzie na karmę dla rekinów, nie będę zasmucony.";
			link.l1 = "Czemu nie wyślesz swoich ludzi za nim?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Cóż, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" przekonał kilku piratów, że ich część łupu jest przechowywana w naszej kryjówce niedaleko "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Generał")+". Ich dwa statki '"+pchar.GenQuest.CaptainComission.ShipName1+"' i '"+pchar.GenQuest.CaptainComission.ShipName2+"podniósł kotwice niedawno i odpłynął do "+sLoc+"Teraz widzisz, dlaczego nie mogę ufać moim ludziom, że wykonają tę robotę?";
			link.l1 = "Tak. Ile mam czasu?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 do 15 dni, nie więcej, to dla mnie ważne, jeśli nie dotrą do skrytki, albo będzie to nonsens zatopić ich z cennym ładunkiem. W takim razie lepiej, żeby to tutaj przywieźli...";
			link.l1 = "Dobrze, wchodzę w to. Spróbuję ich złapać.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Nie martw się. Moi ludzie dostarczą go na twój statek. A dlaczego ci na nim zależy?";
			link.l1 = "Nie znam go. Jego krewni poprosili mnie, bym go dostarczył.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, to dobrze. Prawie było mi przykro, że dałem tak niską cenę za twojego człowieka. Ha-ha-ha-ha! Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Więc, , "+GetFullName(pchar)+", zatopiłeś moich kumpli? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nie. Nie udało mi się ich złapać. I nie spotkałem ich po powrocie.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Tak zrobiłem. Wysłałem ich na pożarcie rekinom.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Cholera! Spotkałeś ich czy nie, teraz to nie ma znaczenia! A jaka będzie twoja następna propozycja?";
			link.l1 = "Może masz dla mnie łatwiejszą robotę?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Słuchaj, "+NPChar.name+", obniż cenę za więźnia...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nie.";
			link.l1 = "Żegnaj zatem...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Obniżyć cenę?! Właśnie straciłem swój skarb przez twoją nieudolność! A teraz mogę podnieść cenę! Możesz go wziąć za 200.000 peso, jeśli chcesz, albo możesz się stąd wynosić.";
			link.l1 = "To za drogo... Żegnaj...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Cholera, weź swoje monety.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Możesz zabrać tego słabeusza...";
			link.l1 = "Żegnaj.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Dobra robota! Weź swojego słabeusza i powodzenia.";
			link.l1 = "Dzięki. Żegnaj.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Przywiozłeś okup"+GetSexPhrase("","ла")+"Nie żartowałem, kiedy powiedziałem, że sprzedam go plantatorom.";			
			link.l1 = "Słuchaj, "+NPChar.name+", tu taka sprawa... W sumie, nie mam takich pieniędzy. Ale jestem gotów"+GetSexPhrase(" ","а")+"odpracować.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150000 pesos. Gdzie mogę go znaleźć?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Czy przyniosłeś pieniądze? Nie żartowałem, mówiąc o sprzedaniu tego człowieka na plantację.";			
			link.l1 = "Nie mam pieniędzy, "+NPChar.name+", ale nad tym pracuję.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 pesos. Gdzie mogę go znaleźć?"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "A dlaczego cię obchodzi, co robię? Wiesz co, lepiej zmykaj...";
			link.l1 = "Tshh, uspokój się. Mam z tobą interesy. Chodzi o twojego więźnia.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "A, dobrze. Kogo chcesz wykupić?";
			link.l1 = "Poczekaj. Nie jestem tu, by wykupić, jestem tu, by zaoferować ci zakup więźnia. A cóż, będziesz miał okazję dostać za niego okup.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. A czemu potrzebujesz mojego pośrednictwa? Czemu nie chcesz sam zgarnąć tych pieniędzy?";
			link.l1 = "Mogę mieć z tym problemy z władzami.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... dobrze więc. Spójrzmy. Kto jest twoim więźniem?";
			link.l1 = "To jest "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Widzę... byłby to dobry handel, jeśli nie kłamiesz. Przypuszczam, że mogę ci zapłacić za tego człowieka "+iTemp+" pesos albo dać ci jakieś ciekawe informacje zamiast tego. To twój wybór.";
			link.l1 = "Lepiej wezmę pesos. Mam dość tego interesu...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Opowiadaj dalej. Jestem pewien, że dasz mi coś interesującego.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Pieniądze zatem. Weź je. Teraz to nie twój problem. Dostarcz tu przedmiot sprzedaży.";
			link.l1 = "On już musi być gdzieś przy bramach miasta. Dzięki! Naprawdę mi pomogłeś.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Proszę bardzo, przynieś mi więcej... Do zobaczenia!";
			link.l1 = "Powodzenia...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "To dobrze robić interesy z mądrym człowiekiem. Teraz słuchaj: za kilka dni do "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"To")+" hiszpańska ekspedycja przybędzie z Kontynentu, załadowana cennymi towarami. Będą czekać na statek, który ma zabrać ładunek. Jeśli dotrzesz tam w ciągu tygodnia, będziesz miał szansę przejąć ładunek dla siebie.\nNa twoim miejscu już bym wyruszał na mój statek. I przyprowadź tu więźnia.";
					link.l1 = "Dzięki! Towary będą miłym zadośćuczynieniem za moje kłopoty. A mój pasażer musi już być blisko bram miasta. Zostanie do ciebie przyprowadzony.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "To dobrze robić interesy z mądrym człowiekiem. Teraz słuchaj: za około tydzień hiszpańska brygantyna '"+pchar.GenQuest.Marginpassenger.ShipName1+" załadowany cennymi towarami wypłynie z "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Generał")+" do "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Jeśli się pospieszysz, złapiesz go bez trudu.\nWciąż tu jesteś? Na twoim miejscu już bym szedł na swój statek. I przyprowadź tu więźnia.";
					link.l1 = "Dzięki! Towary będą miłą rekompensatą za moje kłopoty. A mój pasażer musi już być blisko bram miasta. Zostanie do Ciebie przyprowadzony.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rabunek!!! To jest nie do przyjęcia! Szykuj się, "+GetSexPhrase("chłopcze","dziewczyna")+"...","Hej, co do cholery tam robisz?! Myślałeś, że możesz mnie okraść? Jesteś skończony... ","Poczekaj, co do diabła? Zabierz ręce! Okazuje się, że jesteś złodziejem! Koniec dla ciebie, łajdaku...");
			link.l1 = LinkRandPhrase("Cholera!","Carramba!!","Cholera!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = " Wynoś się stąd!";
			link.l1 = "O, kurde...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Nie zawracaj mi głowy swoimi tanimi gadkami. Następnym razem, wynik ci się nie spodoba...";
        			link.l1 = "Zrozumiałem.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("To koniec, bez gadania.","Nie chcę już z tobą rozmawiać, więc lepiej mnie nie niepokój.");
			link.l1 = RandPhraseSimple("Jak sobie życzysz...","Hm, dobrze więc...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Mam nadzieję, że okażesz więcej szacunku i przestaniesz być niegrzeczny?";
        			link.l1 = "Możesz być pewien, Jacques, zrobię to.";
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
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Rozwiązać problem? Rozumiesz, co zrobiłeś? Tak czy inaczej, przynieś mi milion pesos, a przekonam chłopaków, żeby zapomnieli o twoich 'wyczynach'. Jeśli ci się to nie podoba, to możesz iść do diabła.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Dobrze, jestem gotów zapłacić.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Zrozumiałem. Wychodzę.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Dobrze! Uważaj się znów za czystego. Ale mam nadzieję, że nie zrobisz już takich obrzydliwych rzeczy.";
			link.l1 = "Nie będę. Zbyt drogie dla mnie. Żegnaj...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
