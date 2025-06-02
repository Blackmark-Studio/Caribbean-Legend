// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Questo è un maledetto bug. Avvisate quei diavoli degli sviluppatori.";
			link.l1 = "Certo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Che ti serve?";
			link.l1 = "Sei tu "+pchar.questTemp.Shadowtrader.Guardername+"? Il mercante locale mi manda. Sta aspettando la tua presenza con impazienza proprio in questo momento.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, ma l'ho aspettato proprio qui! Mi dissero che sarebbe venuto in taverna! Scusatemi, corro subito da lui.";
			link.l1 = "Benissimo!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Buonasera, capitano. Vuoi mettere le mani su un po' di merce a buon mercato, eh? Seguimi!";
			link.l1 = "Avanti, guida tu.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Buonasera, signore. È sempre un piacere incontrare un nuovo cliente, ah! Permettetemi di presentarmi: io sono "+GetFullName(npchar)+". Ho la merce più a buon mercato di tutta questa città, te lo garantisco.";
			link.l1 = "Finalmente ci incontriamo..."+npchar.name+"Suppongo che ti deluderò: non sono venuto a trattare, ma a mettere fine alle tue luride manfrine. Sei stato una gran spina nel fianco di un uomo importante. Il fastidio è ormai tale che vuole fartela pagare... con ogni mezzo necessario.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "Fermo lì, mascalzone! Non sai che bisogna pagare le tasse per fare affari qui? Nessuno infrange la legge sotto il mio naso! "+GetFullName(npchar)+", hai infranto la legge e la tua refurtiva è ora confiscata! Ci sono soldati armati dietro di me fuori dalla porta, quindi non provare nemmeno a fare il finto tonto!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Davvero? Non me l’aspettavo... Chi diavolo sei tu?! È una trappola! Credo di sapere chi c’è dietro tutto questo! A qualunque costo... ragazzi, ammazzatelo!";
			link.l1 = "Balla, furfante!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Oh Dio... ufficiale, ascolta! Facciamo un patto. Sei un uomo saggio e misericordioso! Ti darò 5000 pezzi da otto e ci lasci sgattaiolare dal secondo piano. Prenditi anche la merce, ti serve, vero? A cosa ti servo io? Lascio la città subito, nessuno ci vedrà mai più. E tu avrai il tuo denaro. Che ne dici, ufficiale?";
		link.l1 = "Pensi davvero, feccia, che macchierei il mio onore per una somma così misera?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "D'accordo, d'accordo, ufficiale, prendi tutto quello che ho – 10.000 pesos. È tutto ciò che possiedo, lo giuro!";
		link.l1 = "Hm... Se ti faccio arrestare, tutti i tuoi dobloni andranno sequestrati... Va bene! Questo covo di contrabbandieri è chiuso e tutta la mercanzia è requisita... Dammi la grana e sparisci. E non farti più vedere da queste parti!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Grazie, grazie, grazie capitano! Ecco i tuoi dobloni, e non mi vedrai più da queste parti. Andiamo via!";
			link.l1 = "Fuori dai piedi o sarò costretto ad arrestarti!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ah! Pietà, non uccidermi! Ti darò tutto quello che ho!";
			link.l1 = "Tutta la tua mercanzia verrà requisita dalle autorità. Davvero credi che avrò pietà di te dopo ciò che è appena successo qui?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Io... io ti darò tutti i miei soldi e averi! Lasciami andare! Oggi stesso lascerò l’isola e non mi vedrai mai più da queste parti!";
			link.l1 = "Va bene. Dammi tutto quello che hai addosso e sparisci. E non provare mai più a fare affari qui – la prossima volta non sarai così fortunato, mascalzone.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Nemmeno per sogno, bastardo, non mi comprerai. L’unico modo di trattare con gente come te è con il freddo dell’acciaio e il piombo rovente!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
