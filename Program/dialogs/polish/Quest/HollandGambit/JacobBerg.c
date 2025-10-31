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
				dialog.text = "Argh! Hic... Kimże jesteś, do diabła? Gdzie ten przeklęty Chińczyk? Mówię do ciebie! ...Głuchy jesteś?! Hic!";
				link.l1 = "Słyszę cię doskonale, więc nie krzycz. Żaden Chińczyk nie przyjdzie. Jestem tu zamiast niego.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Robak. Powiedzcie deweloperom.";
			link.l1 = "Jeśli tak mówisz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "Co? Kim ty jesteś? Co ty tu, do cholery, robisz?! ...Zadałem ci pytanie, łajdaku!";
			link.l1 = "Tego już wiedzieć nie musisz. Potrzebuję twojego statku.";
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
				dialog.text = "Argh! Cholera... Co za bałagan! Ty nie jesteś żadnym kupcem, co?";
				link.l1 = "Brawo, bystrzaku. Moja załoga to elita angielskich marines - od początku byłeś na straconej pozycji. Richard Fleetwood i ja uknuliśmy tę historyjkę o kupcu... a ty ją łyknąłeś jak pelikan. Brawo. A teraz twoja przygoda właśnie się skończyła, bękarcie!

";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Nareszcie się spotykamy, kapitanie. Sprytny z ciebie gość... Dawno nie miałem tak godnego przeciwnika.";
				link.l1 = "I będę twoim ostatnim, Jacob. Z tej kajuty nie wyjdziesz już żywy.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Na to wygląda. Twoi ludzie przejęli pokład, więc nawet nie łudzę się, że mnie oszczędzicie. Ale zanim ktoś przyjdzie ci na pomoc - poślę cię prosto do piekła!
Van Berg nie umrze tanio! Van Berg potrafi skończyć z klasą, tak łatwo mnie nie dostaniesz!";
			link.l1 = "Heh, widzę, że jesteś nieźle oderwany od rzeczywistości. Ale uwierz mi - twój żałosny żywot nie jest wart nawet złamanego grosza. Dobra, koniec gadania! En garde!";
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
			dialog.text = "Hah, takiś pewny?! Zadbałem o to, byś nie uciekł. Podpaliłem lont do prochowni. Za parę sekund nasze statki rozerwą się na strzępy!";
			link.l1 = "A ja myślę, że tylko ty i twój głupawy ryj wylecicie w powietrze. Zatłukę cię, a potem odpłynę i obejrzę sobie ten twój śmieszny pokaz fajerwerków przy butelce rumu. Hah!";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Spróbuj tylko! To ja cię zatłukę, a potem wyskoczę i popłynę do brzegu, by delektować się pokazem!";
			link.l1 = "Hah, zakład?!";
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
