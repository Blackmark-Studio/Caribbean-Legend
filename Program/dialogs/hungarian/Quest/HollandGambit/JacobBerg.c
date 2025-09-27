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
				dialog.text = "Argh! Hic... Ki a fene vagy te? Hol van az az átkozott kínai? Hozzád beszélek, süket vagy? Hic!";
				link.l1 = "Tisztán és világosan hallak, úgyhogy ne kiabálj. Egy kínai sem fog jönni. Én vagyok itt helyette.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Egy bogár. Mondd meg a fejlesztôknek.";
			link.l1 = "Ha te mondod...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "Mi van? - Mi van? Ki vagy te? Mi a faszt keresel itt? Kérdeztem valamit, söpredék!";
			link.l1 = "Ezt nem kell tudnod. Szükségem van a hajódra.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Argh... Mi van?! Te kibaszott... várj! Te egy átkozott angol kutya vagy! Csessze meg! Végül is lenyomoztak... Vége a sorodnak! Nem adom meg magam!";
			link.l1 = "Nos, nekem nem kell, hogy megadd magad...";
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
				dialog.text = "Argh! Bassza meg! Micsoda zûrzavar! Te nem vagy kereskedô, ugye?";
				link.l1 = "Milyen okos fiú. A legénységem tele van válogatott angol tengerészgyalogosokkal, szóval már az elejétôl fogva megszívtad. Richard Fleetwood és én kitaláltuk a kereskedô történetét, és most itt vagy. A kalandjaidnak vége, te szemétláda!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Végre találkoztunk, kapitány. Maga egy okos fickó... Túl régen találkoztam ilyen komoly ellenféllel.";
				link.l1 = "És én vagyok az utolsó ellenfeled, Jacob. Nem fogsz innen élve távozni.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Úgy tûnik. A legénységed elfoglalta a hajót, és nem számítok arra, hogy megkímélnek. De elôbb küldelek a pokolba, minthogy a segítségedre siessenek! Van Berg nagy árat fog fizetni az életéért!";
			link.l1 = "Ez csak a te véleményed. Én úgy gondolom, hogy a te életed egy fillérbe sem kerül. Elég a szavakból, készülj fel!";
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
			dialog.text = "Tényleg? Gondoskodtam róla, hogy ne ússza meg. Meggyújtottam a gyújtózsinórt a púderszobában. Hamarosan az edényeink darabokra fognak robbanni.";
			link.l1 = "Szerintem csak te és az öreg kádad fog felrobbanni. Kibelezlek, elengedem a hajómat, és nézem a tûzijátékot, ahogy elhajózom.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Nem, ha elôbb megöllek, kiugrom az ablakon, kiúszom a partra, és magam nézem a tûzijátékot!";
			link.l1 = "Tét?";
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
