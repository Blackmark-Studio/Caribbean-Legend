void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, proszę mi wybaczyć, ale poproszono mnie, abym pani powiedział, że ma pani... randkę w środku starej pogańskiej piramidy.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jezu! Taki nikczemny człowiek w moich komnatach! Odejdź stąd, albo wezwę straże!","To się nie dzieje... Kto pozwolił temu szczurowi wejść do mojego domu? Wynoś się stąd, ty draniu! Nie masz tu nic do roboty! Znikaj!","Takie dziwne czasy nadeszły. Szczury dostają się do mojej sypialni! Idź stąd!");
				link.l1 = RandPhraseSimple("Spokojnie tam...","Uważaj na swoje słowa...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Co robisz w mojej sypialni? Znikaj stąd!","Proszę cię, opuść to miejsce natychmiast!","Przepraszam, panie, ale nie byłeś tu zaproszony. Proszę, opuść mój pokój!");
				link.l1 = RandPhraseSimple("Przepraszam... już wychodze.","Przepraszam, złe drzwi. Muszę iść.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "O, co to było?! Jestem taka głupia! Chodzę wokół, nic nie widzę... Strażnicy!!!";
			link.l1 = "Zamknij się!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Znikaj stąd, szczurze!","Odejdź natychmiast od rezydencji gubernatora, szczurze!","Nie obchodzi mnie, co robisz w domu gubernatora "+XI_ConvertString("Colony"+npchar.city+"Gen")+", Ale moja rada brzmi następująco: znikaj, teraz!");
				link.l1 = RandPhraseSimple("Trzymaj się na wodzie, kolego...","Uważaj na swoje słowa!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Pozdrowienia! Jestem sługą gubernatora. Nazywam się "+GetFullName(NPChar)+".","Strzegę tego miejsca, "+GetAddress_Form(NPChar)+".","Wiesz, "+GetAddress_Form(NPChar)+", nasz gubernator to dobry człowiek i dobrze nam płaci...");
				link.l1 = RandPhraseSimple("Miło.","Hm, bardzo dobrze...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Więc zdecydowałeś się obrabować gubernatora?! Strażnicy, złapać złodzieja!!";
			link.l1 = "Zamknij swoją gębę!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Lepiej stąd uciekaj, "+GetSexPhrase("kolego","dziewczyno")+"...","Odejdź!","Pominąłeś drzwi, "+GetSexPhrase("kolego","dziewczyno")+"? ? Ten majątek należy do gubernatora "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("Odejdę, kiedy tylko zechcę!","To nie twoja sprawa...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Dziś dostałem rozkaz stania na warcie. Miłe miejsce...","Chronię majątek "+GetAddress_Form(NPChar)+".","Moim zadaniem jest ochrona posiadłości gubernatora.");
				link.l1 = RandPhraseSimple("Powodzenia, więc...","Hmm, rozumiem...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ach, tak. Wreszcie! Jestem gotów iść z tobą, kapitanie.";
				link.l1 = "Tak po prostu? Senora, czy jesteś pewna, że tego chcesz?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Co?! Jesteś pijany, señor? Co za idiotyczny żart! Proszę, odejdź, błagam cię!"+sld.name+"! Strażnicy! Pomocy!";
				link.l1 = "Cholera, czas się zbierać.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "No cóż, oczywiście! Ach, Senor Aruba i ja utrzymujemy korespondencyjny związek od dawna!";
			link.l1 = "Skoro tak jest, proszę na pokład!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Nie, senora, to nie przystoi. Moja cześć nie pozwoli narażać kobiety na ryzyko, a ty ewidentnie zostałaś wprowadzona w błąd!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "W takim razie, mój drogi kapitanie, weź swoje wiejskie poczucie honoru i wsadź je sobie w tyłek! Poczekam na innego posłańca, kogoś nie tak ograniczonego jak ty!";
			link.l1 = "Nawet tego nie skomentuje...";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
