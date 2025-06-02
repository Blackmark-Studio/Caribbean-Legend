// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Cosa vuoi, eh?";
			link.l1 = "Niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Cosa vuoi, muso pallido? Tichingitu non ha nulla da dirti.";
			link.l1 = "Il tuo nome è Tichingitu? Mh. Ascolta, guerriero, non sono venuto fin qui per rimirarti. Ho una domanda per тебя: perché mai ti sei introdotto nella casa di quel grassone?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Non dici nulla? Poco furbo, ragazzo. Ti impiccheranno per furto e tutte le altre tue bravate. Dimmi perché hai fatto una cosa simile, e forse potrò darti una mano.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu arriva nella città dei visi pallidi dopo molti, molti sentieri, attraversando grandi acque, dalle vaste foreste e paludi. Tichingitu è stanco e vuole mangiare. Tichingitu sta morendo di fame. Nessuno vuole aiutare Tichingitu. Urlano: 'Vattene, cane dalla pelle rossa'. Il locandiere caccia l’indiano come se fosse un cane rognoso. Tichingitu vuole mangiare.";
			link.l1 = "Accidenti, ma perché sei venuto in questo villaggio dalla tua... foresta?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu scacciato dalla tribù. Tichingitu ha litigato col vecchio stregone, lo stregone l’ha detto al capo, lo stregone ha maledetto Tichingitu, Tichingitu ha dovuto lasciare la tribù, lontano, lontano dalla sua terra. Tichingitu senza casa, senza armi, senza nulla.";
			link.l1 = "Ecco che sfortuna, per mille balene. Ma che diavolo ti ha spinto a metterti contro la tua stessa gente?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Lo stregone della tribù, maledetto sia, dice che uno spirito maligno si è infilato nel corpo di mia moglie. Mia moglie deve morire, dice lui. Ma lei è solo malata, nessun demonio l’ha presa. Tichingitu voleva curarla, lo stregone voleva ucciderla. Tichingitu si è ribellato allo stregone, allora tutti si sono rivoltati contro Tichingitu. Così Tichingitu se n’è andato.";
			link.l1 = "Hai provato a salvare tua moglie? È per questo che ti hanno cacciato dal villaggio?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Sì, faccia di latte. Tichingitu non ha scelta. O ruba, o crepa di fame...";
			link.l1 = "Ebbene, dico io... Una forca per qualche misera moneta rubata da un affamato... Tichingitu, cercherò di aiutarti. Conosco Fadey, quel marcantonio in casa del quale ti sei intrufolato. Forse riuscirò a combinare qualcosa... Andrò a parlare col comandante.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu aspetta. L’indiano non teme la morte. Lo stregone ha maledetto Tichingitu, Tichingitu deve morire.";
			link.l1 = "Non tutto è perduto. Farò un tentativo per aiutare...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu aspetta. Indiano non teme la morte. Sciamano maledice Tichingitu, Tichingitu deve morire.";
			link.l1 = "Nessun bisogno d'essere così cupo. La tua prigionia è finita. Ti ho aiutato a riconquistare la libertà.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Scherzo da faccia pallida? Tichingitu è libero?";
			link.l1 = "No, non sto scherzando. Stanno per aprire la tua cella e lasciarti andare. Seguimi, ti porterò fuori da questa lurida prigione.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Eccoti qua, di nuovo libero. Su, Tichingitu, bada a non rubare più nulla e non cacciarti in altri guai! Fareste meglio a trovare un villaggio d’indiani e vivere coi tuoi pari, dubito che ti negherebbero accoglienza.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu non va. Il padrone ha salvato la vita di Tichingitu. Tichingitu resta. La vita di Tichingitu appartiene al padrone.";
			link.l1 = "Eh? Di che diavolo parli? Quale padrone, quale vita? Non capisci quello che ti dico? Sei libero! Vai, sparisci!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "L’indiano ha un debito, padrone bianco. Tichingitu ti serve con lealtà e sincerità. Tichingitu sa combattere. Tichingitu morirebbe in battaglia per il padrone. Lui resta.";
			link.l1 = "Oh Signore! Maledizione... Che razza di padrone sarei io per te, Tichingitu? Ti ho aiutato, non certo per farti diventare uno schiavo.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu non schiavo. Tichingitu indiano libero. Tichingitu vuole servire voi. Tichingitu sa come combattere, nessun cane si avvicina al padrone senza cadere. Tichingitu sa pulire e caricare il moschetto. Tichingitu sa sparare col moschetto.";
			link.l1 = "Sebbene... Sai, Tichingitu, non è affatto una cattiva idea. Ho bisogno di gente fidata e tu non mi sembri un uomo malvagio. E poi sai maneggiare un moschetto. E che farai mai da solo? Finirai per rubare di nuovo qualcosa e la prossima volta ti impiccheranno di sicuro... Va bene, puoi restare. Ma rammenta: la vita con me sarà tutt'altro che tranquilla.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "D'accordo, basta così. Va' in pace, fratello dalla pelle rossa. Che i tuoi dèi veglino su di te!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu non teme nulla, nobile padrone. Tichingitu sarà lieto di servirvi. Tichingitu vi resterà fedele fino all’ultimo respiro.";
			link.l1 = "D’accordo. Benvenuto a bordo, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Cocoa";
			sld.lastname = "Leaf";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu ti ascolta, Capitano "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, sto per partire verso un antico villaggio indiano chiamato Tayasal. Non ti nasconderò nulla, è un viaggio estremamente pericoloso e fuori dal comune: si passa attraverso un idolo di teletrasporto. Tu... Verresti con me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, fammi un resoconto completo della nave.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu procuri certe merci ogni volta che attracchiamo al porto.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Ascolta il mio comando!";
            Link.l1.go = "stay_follow";
			link.l2 = "Niente per ora. A riposo!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Rapporto della nave? Tichingitu non porta nessun rapporto, padrone. Solo lame e stracci. Tichingitu non ha preso nessun rapporto da nessuna parte.";
			Link.l1 = "D'accordo, come vuoi.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Padrone, Tichingitu non mette mai piede in una colonia senza di te. Quando Tichingitu entra in una bottega – tutti pensano subito che Tichingitu sia un ladro di nuovo. Poi, prigione.";
			link.l1 = "Sì, probabilmente hai ragione. Non quella storia della prigione di nuovo. E poi, nessuno crederebbe mai che tu sia un cassiere di bordo.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Quali ordini porti?";
            Link.l1 = "Fermati qui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e non restare indietro!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Devi cambiare il tipo di munizioni per la tua arma da fuoco.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Cambia il tipo di munizione per il tuo moschetto.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Cambia la tua arma principale per il combattimento.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Voglio che tu mantenga le distanze dal bersaglio.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegli il tipo di munizione:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Seleziona il tipo di munizione:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "All'inizio dello scontro userai:";
			Link.l1 = "Lama";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Moschetto";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Cambio di rotta!";
            Link.l1 = "A tuo agio.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Cambio di rotta!";
            Link.l1 = "Riposati.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Quanto manca, Capitano? Dica a Tichingitu quante iarde, ma non più di venti.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitano, perdoni Tichingitu ma io non comprendo ciò che dice.";
				link.l1 = "Perdona, colpa mia...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu resta fermo, non si muove. È questo che vuoi, Capitano?";
				link.l1 = "Sì, proprio così.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu non può restare a più di venti passi dal bersaglio. Altrimenti sbaglia.";
				link.l1 = "Va bene, tieniti a venti iarde di distanza.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu capisce tutto. Tichingitu prende il posto che dici tu.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "La vita di Tichingitu è ormai intrecciata a quella del mio Capitano. L’indiano non dimentica ciò che il Capitano ha fatto per lui. Tichingitu lo seguirà ovunque ordini il Capitano, senza domande, senza esitazione.";
			link.l1 = "Grazie, amico mio!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quando salpiamo?";
			link.l1 = "Un po’ più tardi. Per ora dovremo prepararci al viaggio.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Paghiamo quell’uomo bianco cento dobloni, ce ne andiamo e portiamo a termine il nostro lavoro in santa pace.";
			link.l1 = "E se ci beccano di nuovo?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Paghiamo mille dobloni.";
			link.l1 = "Cinico ma di gran perspicacia.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadeloupe è pure peggio.";
			link.l1 = "Come sarebbe?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Là, vogliono impiccare solo Tichingitu. Qui invece vogliono far penzolare più di одного. Non è poi così male.";
			link.l1 = "Questa sì che è proprio una bella dose di cinismo!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Colpo a bruciapelo. Capitano, il vecchio è tosto, possiamo salvarlo se ci muoviamo in fretta.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "L'uomo bianco non conosce pietà. Molti miei sono caduti, Capitano. Troppi. Ma i tuoi ancor di più.";
			link.l1 = "Sono della tua ciurma?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Alcuni... alcuni miei.";
			link.l1 = "Resisti, amico mio.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Ancora cento dobloni?";
			link.l1 = "Eh? Mi stai chiedendo se pagherò ancora per far uscire Deluc di prigione?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Sì.";
			link.l1 = "Non ne sono affatto sicuro... Che ne pensi tu?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Dobbiamo tirarlo fuori da quella topaia.";
			link.l1 = "È nobile, questo. Mai abbandonare i propri, eh?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "O lascialo. Lascia che il debole venga sbranato dal giaguaro nella giungla.";
			link.l1 = "Chi?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "Il grosso felino.";
			link.l1 = "Tichingitu, faccio fatica a capirti. Dimmi soltanto: che dovrei fare in questa situazione?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Usa il cervello tuo.";
			link.l1 = "Molto d'aiuto, davvero!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			Return_TichingituOfficer();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
