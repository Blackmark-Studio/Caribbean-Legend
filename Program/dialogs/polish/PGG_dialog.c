#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Cruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is coming, not 'Beware' you idiot! Ha-ha-ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "Jeśli zauważysz błąd... zgłoś go AT, dla Navy.";
//	link.l1 = "Z pewnością!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hej, znikaj, niech cię! Jeśli zepsujesz mój interes, wypruję ci serce!";
			link.l1 = RandPhraseSimple("Ośmielasz się grozić mi, psie?!","Sprawię, że zakrztusisz się swoimi słowami, łotrzyku!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "O, rozumiem. Biznes to biznes. Powodzenia.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Dzień dobry, nazywam się "+GetFullName(NPChar)+", a twój?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "Mam na imię "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Alkohol dla wszystkich! Jestem kapitanem "+GetFullName(pchar)+".","Jestem kapitanem '"+PChar.Ship.Name+" i kilkaset prawdziwych diabłów! He-he! Moje imię to "+GetFullName(pchar)+"."),RandPhraseSimple("Pozwólcie, że się przedstawię, panowie. Jestem kapitanem "+GetFullName(pchar)+".","Jeszcze się nie poznaliśmy. Jestem kapitanem '"+PChar.Ship.Name+" pod flagą "+NationNameGenitive(sti(PChar.nation))+". Nazywam się "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Cóż, wszyscy mnie tu znają! Jestem "+GetFullName(NPChar)+". Miło cię poznać! Co mogę dla ciebie zrobić?";
		link.l1 = RandPhraseSimple("Mam z tobą interesy!","Chcę z tobą porozmawiać...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Cóż, wszyscy mnie tu znają! Jestem "+GetFullName(NPChar)+", kapitanie "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "Co powiesz na to, abyś do mnie dołączył? Dwa statki są lepsze niż jeden. Możemy razem prowadzić przyzwoity interes.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Czy chciałbyś służyć jako oficer na moim statku?","Myslę, że sprawdziłbyś się jako oficer na moim statku. Co ty na to?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Questy.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-test) Pojedynki.";
			link.l8.go = "outraged";
		}
		link.l9 = "Nic.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hej, zniknij, niech cię! Jeśli zepsujesz mi targ, wypruję ci serce!";
			link.l1 = RandPhraseSimple("Ośmielasz się mi grozić, psiakrze?!","Sprawię, że zakrztusisz się swoimi słowami, łotrzyku!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "O, rozumiem. Biznes to biznes. Powodzenia.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Już ci wszystko na dzisiaj powiedziałem!";
			link.l1 = "Och, tak...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("Czego potrzebujesz"+GetFullName(pchar)+"?","Kto to? Ach, ty... Znikaj, nie jestem w nastroju...");
		link.l1 = RandPhraseSimple("Co powiesz na interes?","Chciałem z tobą porozmawiać...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("O, popatrz kto tu jest! To "+GetFullName(pchar)+". Jakieś nowiny?","Jak się pan ma? Co mogę dla pana zrobić?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase("Co słychać w wiadomościach?","Jakie są wiadomości z archipelagu?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+"Jakie są wiadomości?",PGG_Meet_BadRep[iAns]+"Jakie są wiadomości z archipelagu?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Co powiesz na to, abyś do mnie dołączył? Dwa statki to lepiej niż jeden. Możemy razem dobrze zarobić.","Wyglądasz na doświadczonego kapitana. Chcesz żeglować pod moją flagą?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("O, biada mi... Mój statek zatonął!","Patrz kto tu jest?! Co cię tu przyniosło? Przy okazji zgubiłem mój statek...");
				link.l3 = RandPhraseSimple("Szkoda. Może następnym razem będzie ci lepiej.","Nie mówisz... Cóż, czas dla mnie odejść. Do zobaczenia.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Czy chciałbyś służyć jako oficer na moim statku?","Myślę, że poradziłbyś sobie dobrze jako oficer na moim statku. Co ty na to?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "Jakie są wiadomości?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Co za brzydki ryj. Prosi się o bęcki.","Och, nasz 'przyjaciel'. Chciałbyś kilka nowych dziur w klatce piersiowej?");
			link.l8.go = "outraged";
		}
		link.l9 = "Nic.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Już ci powiedziałem, że mnie to nie interesuje.","Miałem wrażenie, że już wszystko omówiliśmy.");
			link.l1 = RandPhraseSimple("Jak mogłem zapomnieć?","W porządku. Do widzenia.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... może nie. Nie drugi raz.","I myślałeś, że dwa razy wezmę ten przynętę?!");
			link.l1 = RandPhraseSimple("Cóż, jak sobie życzysz...","Dobrze. Do zobaczenia, więc.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Nie, chyba nie.","Nie, jestem kapitanem i nie chcę służyć jako oficer.");
			link.l1 = RandPhraseSimple("Cóż, jak sobie życzysz...","Dobrze. Do zobaczenia, więc.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Już masz pełny zestaw.","Nie sądzę, abyś był gotowy, aby mi wydawać rozkazy.");
			link.l1 = RandPhraseSimple("Szkoda...","Cóż, los postanowił inaczej.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("To jest właśnie to, czego potrzebowałem! Nasze ostrza skosztują krwi naszych wrogów! Ale jest jeden problem - nadal potrzebuję "+NPChar.Quest.Officer.Price+" pesos, aby spłacić moje długi.","Wyglądasz jak prawdziwy stary solenizna. A jeśli jesteś skłonny zapłacić "+NPChar.Quest.Officer.Price+" pesos, możemy dobrze razem pracować."),LinkRandPhrase("Twoja oferta jest dla mnie dość laskawa. Zgodzę się pracować dla ciebie za raczej skromną opłatę "+NPChar.Quest.Officer.Price+" pesos.","Hmm... Wyglądasz na doświadczonego marynarza. Być może powinienem zaakceptować twoją ofertę, jeśli jesteś gotów zapłacić mi "+NPChar.Quest.Officer.Price+" pesos.","Myslę, że będziemy dobrze współpracować, kapitanie. Tylko "+NPChar.Quest.Officer.Price+" pesos, i mamy umowę."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "Hmm... a jak bardzo jesteś wykwalifikowany?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Mam wrażenie, że masz problemy z gotówką, kapitanie.";
			link.l1 = "Oh... rzeczywiście.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("Świetnie!","Nigdy nie wątpiłem w ciebie, kapitanie.");
		link.l1 = "Nie spóźnij się na odjazd.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Błąd, powiadom deweloperów";
		link.l1 = "Zrobię to!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Już ci powiedziałem, że mnie to nie interesuje.","Miałem wrażenie, że już wszystko omówiliśmy.");
			link.l1 = RandPhraseSimple("Jak mogłem zapomnieć?","W porządku. Do widzenia.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Żeglować z tobą?! Najpierw dojrzej trochę!","Nie wydaje mi się, że jestem tym zainteresowany!");
			link.l1 = RandPhraseSimple("Cóż, jak sobie życzysz...","Dobrze. Do zobaczenia, więc.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Nie, chyba nie.","Nie, dziękuję. Nie lubię służyć pod kimkolwiek.");
			link.l1 = RandPhraseSimple("Cóż, jak sobie życzysz...","Dobrze. Do zobaczenia, więc.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Lubię cię! Masz u mnie umowę! Już słyszę dzwięk peso w naszych kieszeniach!","Jesteś mądry "+GetSexPhrase("gość","dziewczyno")+"... Powinniśmy dobrze razem pracować!"),LinkRandPhrase("Podoba mi się twoja oferta. Zgadzam się.","To interesujące. Wiesz, myślę, że razem możemy zrobić więcej!","To powinno być zabawne. Masz umowę!"));
			link.l1 = RandPhraseSimple("Świetnie! Będę na ciebie czekać na morzu!","Zgoda! Będziemy świetną załogą.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Mam wrażenie, że już masz wystarczająco dużo towarzyszy.","Masz już wystarczająco dużo statków - po co ci więcej?");
			link.l1 = "Tak... Być może, masz rację.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Nudzisz mnie!!! Opuszczam twój oddział!","Mój cierpliwość się skończyła! Odchodzę."),RandPhraseSimple("Mam dość twoich eskapad, 'admirał'... Pozwól mi odejść.","Mam dość twojego dowództwa i opuszczam twój szwadron."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Dobrze, znikaj stąd.","Dobrze, idź gdziekolwiek chcesz."),RandPhraseSimple("Dobrze. Nie będę cię zatrzymywać.","To twój wybór. Życzę Ci sprzyjającego wiatru."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... a może mała premia?","Diabli nadali! Och, cholera, może, zostaniesz? Mogę nawet zapłacić twoim marynarzom dodatkowo!"),RandPhraseSimple("Bolałoby mnie rozstać się z tobą... Być może, małe odszkodowanie mogłoby załagodzić nasze spory?","Co powiesz na podwyżkę pensji?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Raz wystarczyło mi. Już więcej nie uwierzę w twoje obietnice!","Nie uwiedziesz mnie żadnymi pieniędzmi! Moja decyzja jest ostateczna!");
			link.l1 = RandPhraseSimple("Dobrze, więc powodzenia dla ciebie.","Wtedy zgub się i upewnij się, że nigdy więcej cię nie zobaczę!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Premia? Dobrze! Suma wynosi "+NPChar.Quest.Companion.Price+" pesos będzie dla mnie w porządku.","No cóż, może, jeśli jesteś gotów zapłacić mojej załodze "+NPChar.Quest.Companion.Price+" pesos, mogę ich przekonać, aby zostali."),RandPhraseSimple("Dobrze! Mogę zostać za niewielką dopłatą "+NPChar.Quest.Companion.Price+" pesos!",NPChar.Quest.Companion.Price+" zaspokoi mnie i moją załogę na jakiś czas."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Czy ty ze mnie drwisz, czy co?! Znikaj, teraz!","Ha! Wolałbym wydać te pieniądze na coś bardziej użytecznego!"),RandPhraseSimple("O nie. Nie jestem taki bogaty!","Żegnaj. Zamierzam zapłacić tyle."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Świetnie! Oto twoja premia!","Nigdy nie wątpiłem, że chodzi tylko o pieniądze!"),RandPhraseSimple("Świetnie! Cieszę się, że zostajesz.","Oto co obiecałem."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Wybierz szablon!";
		link.l1 = "Szablon zadania 1 - morze.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "WYBRANE! Szablon zadania 1 - ląd.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Szablon zadania 1 - morze.";
		link.l1 = "O, tak...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "WYBRANE! Szablon zadania 1 - ląd.";
		link.l1 = "Och, tak...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Już ci wszystko powiedziałem!";
			link.l1 = "O, tak...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Jakie interesy?.. Hic! Czy nie widzisz - ja i kumple dobrze się bawimy!.. Hic...","Ehh... Dziś nie ma interesów!");
		link.l1 = "Rozumiem...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "O czym rozmawiać? Chociaż, jesteś na czas. Jeśli chodzi o interesy, zawsze jestem gotowy!";
					link.l1 = "Hmm. O czym mówisz?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...tylko ja i diabeł znamy to miejsce, a ostatni, który pozostanie przy życiu, dostanie wszystko!..","...a Meinard odpowiedział: 'Nie oczekuję od ciebie litości i sam ci jej nie udzielę'","...a kiedy już byliśmy na otwartym morzu, kiedy był już nieco pijany, zaproponował: 'Stworzymy tam dla siebie piekło i zobaczymy, kto wytrzyma do końca'.")+PCharRepPhrase(LinkRandPhrase("Teraz jest kolejny pirat!","Panowie, mamy szlachcica szczęścia przy naszym stole, zgaduję?","Czuję proch strzelniczy i krew! Filibuster na prawej burcie!"),LinkRandPhrase("Porządni kapitanowie to rzadka rasa na tych wodach.","Szlachectwo jest obecnie niemodne.","O, teraz jest przyzwoity kapitan, nie jak wy, łotrzyki! He-he!"));
						link.l1 = "Nie krzyczę, mówię ci - to korzystna okazja!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "Ostrożnie, ostrożnie! O! Znam cię. Ty jesteś "+GetFullName(PChar)+". Słyszałem dużo o tobie.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Jestem kapitanem "+GetFullName(pchar)+".","Jestem kapitanem '"+PChar.Ship.Name+" i parę setek prawdziwych diabłów! He-he! Moje imię to "+GetFullName(pchar)+".")+" Ale ja cię nie pamiętam.",RandPhraseSimple("Pozwólcie, że się przedstawię, panowie. Jestem kapitanem "+GetFullName(pchar)+".","Jeszcze się nie poznaliśmy. Jestem kapitanem '"+PChar.Ship.Name+" pod flagą "+NationNameGenitive(sti(PChar.nation))+". Nazywam się "+GetFullName(pchar)+".")+" Ale ja cię nie pamiętam.");
//			link.l1 = "Hmm... a ty kim jesteś? Nie pamiętam cię.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Cześć, "+GetFullName(NPChar)+". Jak się pan ma?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Jestem "+GetFullName(NPChar)+", kapitanie "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". Najbardziej notoryczny korsarz na całym Hiszpańskim Głównym.",". Tylko marynarz.");
		link.l1 = "Tak, teraz cię zapamiętam.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Mam do ciebie sprawę, "+GetSexPhrase("kumpel","dziewczyno")+". Wiem, że mogę ci zaufać, ale po prostu nie mogę o tym rozmawiać w karczmie - zbyt wiele niewłaściwych uszu. Będę na ciebie czekał na pokładzie mojego statku. Moja stara kadź nazywa się '"+NPChar.Ship.Name+"'.'";
//			link.l1 = "Wypłuj to teraz, nie mam czasu na wizyty.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Mam interesującą sprawę dla ciebie i twoich łotrów.","Jeśli połączymy siły, możemy rzeczywiście zdobyć naprawdę dużą nagrodę! Oczywiście, będziemy musieli kogoś w tym procesie zabić. He-he."),RandPhraseSimple("Mam dla ciebie propozycję biznesową, kapitanie.","Kapitanie, twoja reputacja jest niezrównana, dlatego proponuję ci udział w jednej kuszącej sprawie."))+RandPhraseSimple("Tylko między nami. Porozmawiajmy o tym w mesie '"+NPChar.Ship.Name+" nad beczką najwyboristszego piwa. Dzisiaj.","Nie powinniśmy tego omawiać tutaj, omówmy szczegóły na '"+NPChar.Ship.Name+" w spokoju i ciszy. I proszę, nie zanadto się ociągaj.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Do diabła z tymi opóźnieniami! Jeśli to dobre wiadomości, chcę to wiedzieć od razu, a tym bardziej jeśli to złe!","Nie ma sensu w tak krótkich drutach! Jest odpowiedni pokój w karczmie - chodźmy tam!"),RandPhraseSimple("A dlaczego nie możemy omówić twojej oferty teraz, w pokoju karczmy?","Obawiam się, że mało pragnę odwiedzić twój statek. Jeśli czegoś potrzebujesz, wypluj to tutaj i teraz!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... Nie powinniśmy omawiać biznesu w tawernie - zbyt wiele niewłaściwych uszu. Czekam na ciebie na moim statku '"+NPChar.Ship.Name+". Porozmawiamy tam.";
			link.l1 = "Nie mam czasu i nie lubię odwiedzin.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Przyjdę. Ale jeśli tylko marnowałeś mój czas, wyrwę ci język!",RandSwear()+"Dobrze, poczekaj na mnie. Mam nadzieję, że twoja oferta jest tego warta. I nawet nie myśl o robieniu mi kawałów!"),RandPhraseSimple("Chętnie przyjmę twoje zaproszenie, kapitanie.","Zaintrygowałeś mnie. Oczywiście, przyjdę."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Och, jesteś chory na morzu, prawda? Pobiegnij i schowaj się pod spódnicą swojej mamusi!","Za straszne?! Spadaj!"),RandPhraseSimple("Nie da rady. Jeśli nie zależy ci na złocie, to twoja decyzja.","To ta droga i żadna inna. Jeśli nie chcesz - dobrze, jest wielu innych."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha! Jesteś odważny, co nie? Dobrze, idę!","Widzę, że potrafisz trzymać się swoich broni, kapitanie. Dobrze, poczekaj na mnie."),RandPhraseSimple("Dobrze, zgadzam się.","Jesteś całkiem elokwentny. Jestem gotowy do dyskusji o biznesie na twoim statku."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha! Myślałeś, że zwabiłeś mnie na swój statek i tam mnie zabijesz? To nie przejdzie!","Twoje słowa nie są warte ani grosza! Nie będę miał z tobą żadnych interesów!"),"Wątpliwa oferta. Muszę odmówić.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Rum dla mnie! A ty znikaj mi z oczu!","Czyż nie omówiliśmy już wszystkiego?"),RandPhraseSimple("Zajmij się swoimi sprawami. Mam co robić.","Nie sądzę, abyśmy mieli coś do omówienia."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Powiedziałem ci, że będę na ciebie czekać na moim statku!";
		link.l1 = "Oh... pewnie...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Och, nie, to nie zadziała... Czy to nie za dużo statków dla ciebie, "+GetSexPhrase("kumpel","dziewczyna")+"?","Ha! W tak dużym towarzystwie nie ma mowy o utrzymaniu tajemnicy. Zgub się.");
			link.l1 = RandPhraseSimple("Jak sobie życzysz!","Dobrze. Nie żeby mi na tym zależało.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Świetnie. Teraz jestem pewien, że wokół nie ma niepowołanych uszu, a moi marynarze już są poinformowani. Więc moja oferta to zdobycie pewnych rzeczy bez właściciela.";
//			link.l1 = "A co w tym takiego trudnego? Po co ci ja do tego, na samym początku?";
			Dialog.Text = RandPhraseSimple("Witamy na pokładzie, kapitanie!","Świetnie. Teraz jestem pewien, że wokół nie ma niewłaściwych uszu, a moi marynarze już zostali poinformowani. Więc moja oferta to zdobycie pewnych rzeczy bez właściciela.")+"Więc moja oferta to zdobycie kilku rzeczy bez właściciela.";
			link.l1 = RandPhraseSimple("I co w tym takiego trudnego? Dlaczego w ogóle potrzebujesz mnie do tego?","Bez właściciela?! Musisz żartować!");
		}
		else
		{
			Dialog.Text = "Teraz jestem pewien, że nie ma w pobliżu żadnych niepowołanych uszu - dalej, wypluj to!";
			link.l1 = "Więc moją ofertą jest zdobycie jakiegoś bezpańskiego dobytku.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Cóż, są ludzie, którzy uważają to za swoje i trzeba ich przekonać inaczej.","Oczywiście, ktoś będzie musiał zostać zabity - ale na pewno to nie będzie problem?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Do interesów!","To pachnie rzezią! A gdzie oni są?"),RandPhraseSimple("Chciałbym dowiedzieć się więcej szczegółów na temat twojej oferty.","Co dokładnie mi oferujesz?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Robisz ze mnie durnia. Nie będę brał w tym udziału!","To wydaje się łatwe, ale nie ufam ci! Chcesz, żebym dla ciebie wyjmował kasztany z ognia? No, nie zgadzam się!"),RandPhraseSimple("Brzmi obiecująco, ale podziękuję.","Nie, nie kradnę, wolę kiedy dają mi prezenty."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "I co w tym takiego trudnego? Po co ci ja do tego, na samym początku?";
			link.l1 = "No, są ludzie, którzy uważają to za swoje i muszą być przekonani inaczej.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + 
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Nie zwlekaj, wykrztuś to!","Miałem rację na twój temat, co jeszcze wiesz?"),RandPhraseSimple("To bardzo interesujące, proszę kontynuować!","Jestem "+GetSexPhrase("wszystko","wszystko")+" uszy!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("To brzmi jak kusząca propozycja, ale nadal odmawiam. Nie potrzebuję wdawać się w kłótnie z "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","Karawana? Bez właściciela?! Powinno być tam tysiąc żołnierzy na straży! Nie, to nie jest w porządku. Wyjeżdżam."),RandPhraseSimple("Nie, nie jestem w stanie wojny z "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", więc nie jestem zainteresowany.","Moja odpowiedź brzmi nie! Nie zamierzam psuć swoich relacji z "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "To pachnie masakrą! Co z detalami?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Mamy tylko "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+", aby ich przechwycić.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("W "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" karawana zajedzie za daleko i nie będziemy mogli jej dogonić.","Mamy dokładnie "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" dni, aby ich wszystkich zabić i zdobyć łup!"),RandPhraseSimple("Mamy tylko "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" dni na całą operację do naszej dyspozycji.","Powinniśmy się pospieszyć, "+PChar.Name+". Mamy tylko "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("Zrobimy to na czas! Wypływamy dzisiaj.","Nie marnujmy czasu, zatem. Wydaj rozkaz wypłynięcia dzisiaj.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "To bardzo interesujące, proszę kontynuować.";
			link.l1 = "Mamy tylko "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+", aby ich przechwycić.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Nie marnujmy czasu! Idziemy!";
		link.l1 = "W drogę!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"Zawiodłeś mnie, kapitanie. Myślałeś, że zaproszę cię na "+RandPhraseSimple("Niedzielna msza?!!","dziecięca zabawa!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("To twoja sprawa. A to do mnie należy decyzja.","Nie zamierzam wisieć na linie za parę peso."),RandPhraseSimple("Moja decyzja jest ostateczna, kapitanie.","Nie mamy już nic więcej do omówienia."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("Och, daj spokój! Wszystko pójdzie gładko, a nikt niczego nie będzie wiedział. Zabijemy wszystkich."),RandPhraseSimple("Dokąd idziesz, kapitanie? Do władz, może?","To dość nierozsądne, wchodząc do tygrysiego legowiska, myśleć, że łatwo z niego wyjdziesz."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Pocałuj morskiego diabła! Ja jestem kapitanem "+GetFullName(PChar)+" a mnie nic do ciebie nie zależy! Wychodzę!","Przysięgam na diabła, naprawdę mnie drażnisz!"),RandPhraseSimple("Twoja propozycja nie jest dla mnie interesująca, i nie ma już nic więcej do omówienia. Do widzenia.","Myślę, że nie ma już nic więcej do omówienia między nami. Przepraszam, jestem zajęty i muszę iść."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Chwytać "+GetSexPhrase("on","jej")+"! Wiąż "+GetSexPhrase("jego","jej")+" do działa! Zobaczmy jaki kolor "+GetSexPhrase("jego","jej")+" flaki są!!!","Hej! Johnny! Henderson! Złap to "+GetSexPhrase("łotr","dziewczyno")+"! Nie pozwól "+GetSexPhrase("jego","jej")+" do łodzi ratunkowej!!!"),RandPhraseSimple("Szkoda, kapitanie! Mam nadzieję, że spodoba ci się nasz ładownia. A potem zdecydujemy, co z tobą zrobić.","Biali niewolnicy nie są znani z długiego życia, kapitanie, więc dokonaj wyboru: albo Hends zastrzeli cię w głowę, albo spędzisz resztę życia w kamieniołomie."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Zmuszę cię do zjedzenia własnych plugawych wnętrzności, "+GetFullName(NPChar)+"!!!","Zejdźcie z drogi! Szubrawcy! Zabiję was na miejscu!"),RandPhraseSimple("Twoja oferta jest nie do przyjęcia... I najbardziej niemądra!!!","Nie jesteś tak gościnny, jak widzę... Zróbcie miejsce!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "No więc, "+GetFullName(PChar)+", Widzę, że zrobiłem błąd, mieszając się z tobą. Teraz nie ma dla nas łupów. Żegnaj!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Cholera jasna! Spóźniliśmy się - i wszystko przez tych leniwych durniów! Teraz nie ma łupu, którym moglibyśmy się z tobą podzielić, "+GetFullName(PChar)+". Podnieś żagiel! Wydostajemy się stąd! ","Więc, "+GetFullName(PChar)+", Widzę, że zrobiłem błąd, mieszając się z tobą. Teraz nie ma dla nas żadnej zdobyczy. Do widzenia!"),RandPhraseSimple("Zniknęli - a wszystko przez twoją opieszałość! Teraz idziemy różnymi drogami, "+GetFullName(PChar)+".","Nie ma szans, żebyśmy teraz dogonili karawan. Popełniłem błąd, wdając się z tobą w to. Żegnaj!"))link.l1 = PCharRepPhrase(RandPhraseSimple("Do diabła z tym karawanem! Nurkowie po perły są nawet lepsi, a ryzyko jest znikome!","Szczęście jest z nami, a jutro to nowy dzień! Morza pełne są żałosnych kupców, którzy czekają tylko, abyśmy zabrali ich pieniądze!"),RandPhraseSimple("Szkoda, rzeczywiście, że taka genialna operacja okazała się totalną porażką! Do widzenia!","Człowiek proponuje, a Bóg rozporządza... Do widzenia!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Och, dlaczego do diabła się z tobą mieszałem. Zrujnowałeś wszystko. Więc teraz musisz mi zapłacić karę "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Krwiożerczy "+GetSexPhrase("łotr","brud")+"! Wszystko poszło prosto do morskiego diabła!"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos na gwoździu, i znikaj mi z oczu!","Czy wyobrażałeś sobie siebie jako admirała Nelsona? Zatopiłeś cały łup, "+GetSexPhrase("idiota","głupia kobieta")+"! Daj mi teraz "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos i znikaj!"),RandPhraseSimple("Czy zdecydowałeś się tu prowadzić wojnę! To jest całkowicie nie do przyjęcia! Ale, przypuszczam, możemy o tym zapomnieć, jeśli nam zapłacisz "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos.","Twoje metody są całkowicie nie do przyjęcia! Zrujnowałeś całą sprawę! Natychmiast zapłać nam naszą część w kwocie "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos i idź, gdziekolwiek zechcesz!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Gdyby nie ja, teraz byś karmił kraby, chciwy łajdaku!","O tak, powinienem był pozwolić ich okrętowi flagowemu na abordaż - wtedy nie zatruwałbyś teraz powietrza, kołysząc się na rei!"),RandPhraseSimple("Twoje żądania są nie na miejscu, a insynuacje obraźliwe!","Nie uzgodniliśmy kary, więc nie zapłacę ci nic!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Nie mogę teraz z tobą walczyć, a ty to wiesz! Udław się swoimi pesos!"," pesos?!! Cóż, Pani Fortuna na pewno nie uśmiecha się do mnie w ten dzień. Zgadzam się."),RandPhraseSimple("Twoje wymagania są skandaliczne, ale wydaje mi się, że nie mam wyboru.","Twoje apetyty są nadmierne, ale muszę się zgodzić!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "O, dlaczego do diabła się z tobą wymieszałem. Zepsułeś wszystko.";
			link.l1 = "Och, daj spokój! Sam widziałeś, że nie było innego wyjścia.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Cóż, nasza zdobycz wynosi "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Rozdzielmy się.";
			Dialog.Text = PCharRepPhrase("To był gorący interes! Więc, nasz łup wynosi "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Doskonała robota, kapitanie! Nasz łup wynosi "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" Mój udział to "," Udział mojego statku - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" Twój udział to ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Wszystko jest w porządku! Łodzie są już ładowane!","Tak, wszystko jest poprawne. Umowa to umowa."),RandPhraseSimple("Twoje obliczenia są prawidłowe. Zgadzam się.","Jeśli chodzi o dzielenie, jesteś nienaganny."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Ośmielasz się domagać swojej części? Powinni cię natychmiast powiesić na rei!","Twój udział? Tutaj każdy jest za siebie. Jeśli dla ciebie nic nie zostało, to twój problem!"),RandPhraseSimple("Nie sądzę, żebyś mógł liczyć na jakąkolwiek część.","Moja odpowiedź brzmi nie! Nie dzielę się z łotrzykami jak ty!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("No, dobrze więc, nie zamierzam się kłócić! Do widzenia!","Nie rozlewajmy krwi i nie pogarszajmy sytuacji! Następnym razem będziemy mieli więcej szczęścia!"),RandPhraseSimple("Cóż, żegnaj, kapitanie, nie jestem w stanie stawiać wymagań...","Straty i uszkodzenia mojego statku nie pozwalają mi nalegać na sprawiedliwą decyzję. Zostawię to na twoim sumieniu, kapitanie!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Szczęśliwego wiatru!","Siedem stóp pod kilem!"),RandPhraseSimple("Żegnaj! Mam nadzieję, że świeże morskie powietrze będzie dla ciebie dobre!","Mam nadzieję, że nasze nieszczęścia nie uczynią cię jeszcze bardziej nieznośnym, kapitanie! Do widzenia!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Czy ty tego nie rozumiesz! Mogłeś kupić swoje życie zamiast tego! Złapcie tego skurczybyka!","Czy myślisz, że bawimy się z tobą w gry? Cóż, jak tylko cię wyciągniemy na kile, powinieneś stać się bardziej uległy!"),RandPhraseSimple("Będziemy musieli skrócić twoje życie, kapitanie! Jeśli nie zamierzasz odejść w przyjazny sposób, wkrótce spotkasz się ze Świętym Martinem!","Nie zostawiasz mi wyboru, "+GetFullName(PChar)+"! Wezmę to, co moje, czy ci się to podoba, czy nie!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Przysięgam na diabła, zapłacisz za to!!!","Yo-ho! Więc idź i złap mnie, kapitanie "+GetFullName(PChar)+"! "),RandPhraseSimple("Rana będzie długa i głęboka!","Czy chciałbyś umrzeć szybko czy z odrobiną cierpienia?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "Nie chcę już z tobą mieć do czynienia!";
		link.l1 = "Żaden problem.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Miło było robić z tobą interesy. Powodzenia.";
		link.l1 = "I to samo dla ciebie.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("To była prawdziwa rzeź! Szkoda, że nie było z nimi dziewczyn! Ale zdobycz wynagradza  "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Nieźle, kapitanie! Łup to wynagradza "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" Mój udział wynosi ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" Twój udział to ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Całkiem sprawiedliwie, do cholery!","Wszystko jest doskonale w porządku, pieprzony kurde!"),RandPhraseSimple("Twoje obliczenia są poprawne. Zgadzam się.","Jeśli chodzi o podział, jesteś nienaganny."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
