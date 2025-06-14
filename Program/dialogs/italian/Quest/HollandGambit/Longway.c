// китаец Лонгвэй, подручный Роденбурга
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
			dialog.text = "Capitano. Io mi chiamo Longway. Longway consegna la sua nave al tuo comando. Anche Longway stesso ora sotto i tuoi ordini. È ordine del signor Rodenburg.";
			link.l1 = "Salute, Longway. Charles de Maure, al vostro servizio. Avete qualche notizia sulla faccenda per far fuori Jacob van Berg?";
			link.l1.go = "Longway_friend";
			link.l2 = "Felice d’incontrarti, Longway. Mi chiamo Charles de Maure. Non perdiamo tempo – il signor Rodenburg apprezza lavori rapidi e ben fatti. Dove si nasconde adesso Jacob van Berg?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Ebbene, il mio nome è Charles de Maure! Speriamo che la nostra collaborazione vada a gonfie vele! Allora, signor Longway, ditemi un po’, dove dovremmo cercare Jacob van Berg?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Longway è certo che lavoreremo bene insieme, chuanzhang. Jacob van Berg attualmente si trova a "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+"Ho fissato un incontro con lui nella taverna del posto. Lì ti aspetterà.";
			link.l1 = "Salpiamo, ciurma!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "Ordine di monsieur Rodenburg secondo la legge per Longway... Jacob van Berg attualmente a "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Ho organizzato un incontro con lui nella taverna del posto. Lì ti aspetterà.";
			link.l1 = "Salpiamo, avanti!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			notification("Longway disapproves", "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway farà tutto il possibile, chuanzhang. E Jacob van Berg si trova attualmente a "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"Ho organizzato un incontro con lui nella taverna del posto. Lo troverai là.";
			link.l1 = "Salpiamo!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			notification("Longway approves", "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Che sa fare Longway, capitano?";
			link.l1 = "Niente per ora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Stupido idiota, mongolo, chuanzhang! Avevamo un compito semplice: prendere la 'Mirage' senza perdere la 'Meifeng'. Era un bersaglio facile senza il suo chuanzhang, eppure hai fallito.\nLongway non ti servirà più, né vorrà più vederti. Longway è certo che il signor Rodenburg approverà la sua scelta.";
				link.l1 = "Al diavolo te e il tuo padrone!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Sei proprio un babbeo, Mongol, chuanzhang! Abbiamo perso fin troppo tempo a risolvere le tue faccende invece di incontrare Jacob van Berg. Ormai se n’è già andato da "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nHai fallito nel compito. Longway non desidera più né servirti, né vederti mai più. Longway è certo che il signor Rodenburg approverà la sua decisione.";
				link.l1 = "Al diavolo te e il tuo padrone!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Capitano, hai perso troppo tempo senza combinare nulla. Questa non è la tua nave, e Longway non è il tuo facchino. Longway torna a Willemstad.\nLongway non ti servirà più, né vorrà più vederti. Longway è certo che il signor Rodenburg approverà questa decisione.";
				link.l1 = "Al diavolo tu e il tuo padrone!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Capitano, Longway ha lasciato il signor Rodenburg. Longway non tornerà mai più da lui. Sei stato gentile con Longway e sei un capitano coraggioso. Longway desidera unirsi al tuo equipaggio come tuo servitore, mio signore Capitano.";
			link.l1 = "Non come servo, ma come ufficiale! Benvenuto a bordo, compare!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "No grazie, Longway. Sei un uomo libero. Non ho bisogno dei tuoi servigi.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "Perché ti fermi? Uccidi. Longway è stanco, Longway vuole morire. Xing... perdonami.";
			link.l1 = "Non così in fretta, cinese. Ti farò fuori se mi va, ma prima voglio scambiare due parole con te. Il tuo destino dipende da quello che farai d’ora in avanti. Per ora, benvenuto nella stiva della mia nave!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Ora possiamo parlare senza che il clangore delle spade mi rimbombi nelle orecchie. Ascolta, Longway, mi serve qualche informazione e non ho dubbi che tu sappia benissimo ciò che voglio sapere. La domanda è: me la darai di buon grado, o devo fartela sputare?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Zitto, eh? D’accordo. Ti propongo un patto. Ti risparmio la vita e ti sbarco alla prossima costa. In cambio, mi dirai dove e perché ti ha mandato Lucas Rodenburg. Affare fatto?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "So che capisci l’inglese, l’olandese e il francese. E sei anche un buon ascoltatore. Ora però è il momento di parlare. Alla fine mi racconterai tutto quello che sai. So che voi cinesi andate fieri della vostra arte della tortura, ma anche noi dell’Occidente abbiamo fatto passi avanti in quell’antica scienza. Alonso qui è un vero maestro nello sciogliere le lingue. Prima di imbarcarsi sulla mia nave, interrogava per conto della Santa Inquisizione a Santiago. Conosce ogni sorta di trucco imparato dai santi padri, veri artisti nel far confessare la gente... e non serve nemmeno essere protestanti!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "La mia arguzia è sprecata con te. Tu mi racconterai tutto, occhi a mandorla... Tutto quanto... Ma non camperai a lungo dopo, no, perbacco. Il tuo corpo patirà assai dopo che avrai incontrato Alonso/. Quindi la scelta è tua. O mi sveli tutta la verità e vivi, oppure mi sveli tutta la verità e crepi straziato sulla ruota. Strappato dal dolore, capisci? Non temere, m’assicurerò che un prete ti battezzi cristiano, così la tua anima pagana forse scamperà alle fiamme eterne dell’inferno.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Vedo il dubbio che si insinua nei tuoi occhi scuri. Perché dovresti crepare per i peccati del tuo padrone? Ne vale la pena? Rodenburg merita davvero che ti strappino l’anima dal corpo fra mille tormenti?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Longway parlerà. Ma prima, Longway vuole esser certo che manterrai la parola, chuanzhang.";
			link.l1 = "Ah! Parole sagge! Ti do la mia parola, ragazzo.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Mi spiace, capitano, la tua parola non basta. Tu prendi informazioni e poi ammazzi Longway! Longway vuole garanzie.";
			link.l1 = "Contratti come un mercante genovese. Che garanzie vuoi, eh?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "C’è una piccola isola a sud della Guadalupa. Capo Inaccessibile. Sbarca Longway laggiù e consegnagli l’arma. Solo allora Longway ti rivelerà tutto ciò che sa su Lucas Rodenburg.";
			link.l1 = "Non sei in condizione di mercanteggiare con me, cinese.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Faresti lo stesso se fossi Longway, chuanzhang. Non sarebbe facile per i tuoi uomini strapparmi una parola, neanche con le torture. Longway non è un debole uomo bianco.";
			link.l1 = "Va bene. Affare fatto. Ma ti avverto: non provare a fregarmi o ti faccio a pezzi con le mie stesse mani. Mille tagli, e piano... proprio come fanno i tuoi imperatori. Alonso!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Parli da saggio. Ma bada bene: sono arrivato troppo lontano perché tu possa rovinare всё. Se tenterai d’intralciarmi, ti schiaccerò come una cimice, senza pensarci due volte.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Siamo approdati a Guadalupa, chuanzhang?";
			link.l1 = "Calma i bollori, tra poco ci arriviamo.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Hai mantenuto la parola, chuanzhang. Così farà anche Longway. Vuoi sapere qualcosa sulla missione di Longway?";
			link.l1 = "Sì. Ma lascia che ti rammenti la tua promessa: mi racconterai *tutto* quello che sai.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway ricorda. Risponderà a tutto ciò che chiedi su Rodenburg, chuanzhang.";
			link.l1 = "Inizia a parlare.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' stava salpando dal porto di Willemstad verso nord, alle coste di Saint Christopher. Tra cinque giorni lì ci sarebbe stato un galeone al comando di Pieter Stuyvesant. L’ordine di Longway era d’affondare quella nave col capitano a bordo.";
			link.l1 = "Dio in cielo! Rodenburg ti ha ordinato di far fuori Stuyvesant? È pura follia!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway dice la verità, capitano. Era un ordine di Mynheer Rodenburg. A Longway non piaceva, ma Longway non mette mai in discussione gli ordini.";
			link.l1 = "Proprio da cinese, questa. Quale gioco trama il tuo padrone?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Non più il mio padrone, chuanzhang. Longway non tornerà da Mynheer Rodenburg. Rodenburg ha preso il potere a Curaçao. Mathias Beck è stato facile da far fuori, l’autorità di Rodenburg e le sue conoscenze col comandante sono bastate a sbattere il governatore in prigione.\nL’unico ostacolo rimasto è il direttore della Compagnia delle Indie Occidentali, Mynheer Stuyvesant. Quando Stuyvesant cadrà, Rodenburg comanderà ogni poltrona delle colonie olandesi.";
			link.l1 = "Dimmi, Longway, cosa ha spinto un uomo rispettato e potente come Rodenburg a compiere azioni tanto estreme contro la sua compagnia e la repubblica? E non dirmi che è stato per un colpo di sole o un attacco di follia.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway voleva sentire da te stesso, chuanzhang. Sei stato tu a catturare la nave postale della Compagnia e a portare la lettera a Rodenburg, giusto? Il motivo era in quella lettera.";
			link.l1 = "Adesso capisco... Pare che nell’archivio di John Murdock ci siano tante meraviglie da far tremare Rodenburg al punto di замышлять una rivolta contro la sua stessa patria.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Vuoi sapere altro, capitano?";
			link.l1 = "Sì.   Che altro ha combinato Rodenburg?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Monsieur Rodenburg ha ordinato di farti fuori. Longway era a Caracas prima di mettersi sulle tracce di Stuyvesant e ha incontrato Chuanzhang Jacob per dargli ordini.";
			link.l1 = "Capitano Jacob van Berg?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Sei ben informato. Sì. Il chuanzhang Jacob van Berg ti dà la caccia, capitano. Prima o poi ti troverà. Nessuno riesce a sfuggire a van Berg a lungo.";
			link.l1 = "Se sanguina, posso finirlo. Mi occuperò di van Berg e della sua tanto decantata nave fantasma.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Sai molte cose, capitano. Longway non ha altro da dire. Chiedi pure, se hai ancora domande.";
			link.l1 = "Stuyvesant si farà vedere vicino alle coste di San Cristoforo?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Sì, chuanzhang. Potrai trovare il suo galeone vicino alle coste di quest’isola tra circa una settimana.";
			link.l1 = "Bene! Acchiappiamo questa volpe con la sua stessa tagliola... Non ho altre domande. Ho scoperto tutto quel che mi premeva sapere.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Un ultimo consiglio, chuanzhang. Devi prendere 'Meifeng' se vuoi avvicinarti al galeone senza farti attaccare.";
			link.l1 = "Capito. Grazie per le tue dritte.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway parte ora. Addio, chuanzhang.";
			link.l1 = "Buon vento, mio compagno d’Oriente.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Longway ascolta, chuanzhang.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, sto per partire verso l’antica città indiana di Tayasal. Sarò schietto: è un viaggio maledettamente pericoloso, e per di più, intriso di mistero – ci arriveremo passando attraverso un idolo che ci teletrasporterà. Vuoi... venire con me?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, dammi un rapporto completo della nave.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Voglio che tu procuri certe merci ogni volta che attracchiamo in porto.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Son giunto secondo i vostri ordini, capitano.";
				Link.l2 = "Devo impartirti diversi ordini.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ascoltate il mio comando!";
            Link.l1.go = "stay_follow";
			link.l2 = "Niente. Sei congedato!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway non è mai stato intendente, chuanzhang. Longway può dirti come navigare da Trinidad a Havana e quanto ci vorrà. Ma Longway mai contato merce, vendite e commerci.";
			Link.l1 = "Immagino tu abbia ragione. Sarebbe un vero peccato sprecare un navigatore così abile.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Longway non commercia con i gwailo, capitano. Longway ha sempre tenuto il timone, non va nei bazar dove i vecchi nasoni tirano sul prezzo fino all’ultimo reale.";
			link.l1 = "Hm, hai ragione. Probabilmente faresti fuggire i mercanti.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ascolto.";
			Link.l1 = "Parliamo di abbordaggio.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Parliamo della tua nave.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Vorrei che lasciassi la mia squadra per un po’ e andassi a cercare fortuna per conto tuo.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Niente finora.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Qual è il vostro desiderio.";
			Link.l1 = "Non abbordare le navi nemiche. Pensa alla tua pelle e a quella dell’equipaggio.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Voglio che abbordi le navi nemiche senza paura.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Che desiderate, messere?";
			Link.l1 = "Non cambiare la tua nave dopo averla abbordata. Vale troppo oro, quella.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando assalti le navi nemiche, puoi reclamarle per te stesso, se valgono la pena.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Sissignore.";
			Link.l1 = "Riposati.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Sarà fatto.";
			Link.l1 = "A tuo agio.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aye aye.";
			Link.l1 = "Sarà fatto.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Sarà fatto.";
			Link.l1 = "A riposo.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Ordini, capitano?";
            Link.l1 = "State saldi!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Seguimi e non restare indietro!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Cambia il tipo di munizioni per le tue armi da fuoco.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Cambia il tipo di munizioni per il tuo moschetto.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Cambia la tua arma principale per il combattimento.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Voglio che tu apra il fuoco sui nemici da una certa distanza, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Scegliendo il tipo di munizioni:";
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
			Dialog.Text = "Seleziona il tipo di munizioni:";
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
            dialog.Text = "C'è un mutamento d'umore!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "C’è stato un mutamento d’umore!";
            Link.l1 = "Congedato.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "E quale distanza sarebbe, Capitano? Tieni a mente, signor Capitano, che con un moschetto non colpisci nemmeno un barile oltre venti passi.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Cosa intende, mio Capitano?";
				link.l1 = "Scusa, a volte mi scordo che non sei proprio uno spasso con le battute.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Mi tengo saldo e sparo a chiunque osi avvicinarsi troppo. È questo che vuoi?";
				link.l1 = "Sì, proprio così, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Troppo lontano, mio Capitano. Puoi far fuoco su una folla, ma colpire un bersaglio solo? Non se ne parla.";
				link.l1 = "Vale la pena tentare, d'accordo.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Capisco, mio Capitano.";
			link.l1 = "Eccellente.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway ti segue da molto tempo. Longway ti seguirà come sempre. Longway non abbandona mai il suo chuanzhang.";
			link.l1 = "Grazie, Longway! Son lieto che non mi sia sbagliato su di te.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quando si salpa?";
			link.l1 = "Un po' più tardi. Dobbiamo prepararci per questo.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
