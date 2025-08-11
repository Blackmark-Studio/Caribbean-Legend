// Якоб ван Берг - злодей и пират, капитан Миража
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Argh! Hic... Kimże jesteś, do diabła? Gdzie ten przeklęty Chińczyk? Mówię do ciebie, czy jesteś głuchy? Hic!";
				link.l1 = "Słyszę cię doskonale, więc nie krzycz. Żaden Chińczyk nie przyjdzie. Jestem tu zamiast niego.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Błąd. Powiedzcie deweloperom.";
			link.l1 = "Jeśli tak mówisz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "Co? Kimże jesteś? Co, do cholery, tu robisz? Zadałem ci pytanie, łajdaku!";
			link.l1 = "Nie musisz tego wiedzieć. Potrzebuję twojego statku.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Argh... Co?! Czy ty kurwa... czekaj! Jesteś cholernym angielskim psem! Do diabła z tym! W końcu mnie dopadli... To koniec dla ciebie! Nie zamierzam się poddać!";
			link.l1 = "Cóż, nie potrzebuję, abyś się poddał...";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//снять таймер
			chrDisableReloadToLocation = true;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "HollJacob_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "JacobBerg_abordage":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Argh! Cholera! Co za bałagan! Nie jesteś kupcem, prawda?";
				link.l1 = "Taki mądry chłopak. Moja załoga składa się z wybranych angielskich marines, więc od początku byłeś na straconej pozycji. Richard Fleetwood i ja wymyśliliśmy historię handlarza, i oto jesteś. Twoje przygody się skończyły, bękarcie!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Nareszcie się spotkaliśmy, kapitanie. Jesteś sprytnym gościem... Minęło zbyt wiele czasu, odkąd spotkałem tak poważnego przeciwnika.";
				link.l1 = "I jestem twoim ostatnim przeciwnikiem, Jacob. Nie opuścisz tego miejsca żywym.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Wygląda na to. Twoja załoga przejęła statek i nie liczę na to, że zostanę oszczędzony. Ale wyślę cię do piekła, zanim przyjdą ci na pomoc! Van Berg sprzeda swoje życie za wysoką cenę!";
			link.l1 = "To tylko twoja opinia. Myślę, że twoje życie nie jest warte ani grosza. Dość tych słów, przygotuj się!";
			link.l1.go = "JacobBerg_abordage_2";			
		break;
		
		case "JacobBerg_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "JacobBerg_abordage_3":
			dialog.text = "Naprawdę? Upewniłem się, że nie uciekniesz. Podpaliłem lont prowadzący do prochowni. Wkrótce nasze statki zostaną rozerwane na strzępy.";
			link.l1 = "Myślę, że tylko ty i twój stary kociołek wyleci w powietrze. Zamierzam cię wypatroszyć, uwolnić mój statek i oglądać fajerwerki, gdy będę odpływał.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Nie, jeśli najpierw cię zabiję, wyskoczę przez okno, popłynę do brzegu i sam będę oglądać fajerwerki!";
			link.l1 = "Zakład?";
			link.l1.go = "JacobBerg_abordage_5";			
		break;
		
		case "JacobBerg_abordage_5":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
}
}
