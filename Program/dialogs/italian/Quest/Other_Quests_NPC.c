void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Cosa vuoi, forestiero?";
			link.l1 = "Niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Mascalzone! Bella sorpresa per te!";
    		link.l1 = "Cosa?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ah-ah! Qui non trovi schiavi! Sei venuto per loro, vero?";
			link.l1 = "Merda. E io che mi chiedevo perché diavolo ci fossero così tanti soldati su una pinaccia mercantile... Una trappola!";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Sì, bastardo, è una trappola. Non sono un mercante, sono un ufficiale della marina! Anche se hai vinto la battaglia, non sfuggirai alla giustizia!";
			link.l1 = "E perché mai? Ora ti mando all’inferno, affondo la tua nave e nessuno saprà mai nulla.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Ti sbagli. I tuoi affari con quel banchiere sono venuti a galla. Presto il governatore generale verrà a sapere del tuo giochetto e non scapperai alla forca. Ma ti farò un favore: ti mando al Creatore qui e adesso!";
			link.l1 = "Provaci, cane del governatore!";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", in nome della legge, siete in arresto! Consegnate le vostre armi e seguiteci!";
			link.l1 = "Cosa succede, ufficiale? Arrendermi, e per quale motivo?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Non fare il finto tonto, capitano! I tuoi traffici luridi sono venuti a galla. Per il massacro che hai scatenato e per la nave di "+NationNameGenitive(sti(npchar.nation))+"  che hai affondato, ti vedremo penzolare dalla forca!";
			link.l1 = "Ebbene, detta così... Vaffanculo!";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Ehi, che ci fai qui?!";
    		link.l1 = "Perché tanta scortesia, buon signore? Quel topo di Gontier si nasconde forse qui, eh?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "No, non lo è! Fuori dai piedi!";
			link.l1 = "Sembra che tu stia mentendo. Farò perquisire la casa e vedremo...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Vaffanculo! François! Scappa! Ragazzi, datemi una mano!";
			link.l1 = "Maledizione!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Oh! Non mi violentare, ti scongiuro!";
    		link.l1 = "Che diavolo...? Dov'è Francois Gontier? Rispondimi, lurida sgualdrina, o finirai come quei tuoi compari!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "No, no, vi dirò tutto! È saltato dalla finestra ed è corso alla sua nave.";
    		link.l1 = "Che nave? So bene che la sua nave non è in porto. Non mentirmi, ragazza, o finirà peggio per te...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Non sto mentendo, lo giuro! Ha detto d’essersi arenato su una piccola isola e d’essere arrivato qui con una scialuppa... Deve essere ancora laggiù! Non farmi del male!";
    		link.l1 = "D'accordo, pare che tu dica la verità. Resta qui e non fiatare. E la prossima volta, cerca di farti amici con più furbizia. Ma, sai, te lo leggo negli occhi: sei senza cervello, figliolo.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Risparmiaci! Pietà! Ci arrendiamo!";
    		link.l1 = "Oh, davvero? Giù nella stiva, subito! Sparo a chiunque provi a fare il furbo!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Ehi, ehi... Chi abbiamo qui? Non sai che commerciare merci con gente non autorizzata è proibito nella nostra colonia?";
			link.l1 = "Ah sì, ufficiale? A dire il vero, è la prima volta che ne sento parlare. Questo decreto è stato emanato da poco, dico bene?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "Che c'è, traffici "+GetGoodsNameAlt(iCGood)+"? Non vedo proprio nulla "+GetGoodsNameAlt(iCGood)+" in giro, ufficiale. Io vedo solo queste monete luccicanti... E anche lui vede lo stesso. Perché tu e i tuoi soldati non date un'occhiata anche voi alle nostre monete?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Non lo sapevi, eh? Hmm... sembra che tu non stia mentendo. Ma comunque hai infranto la legge. Non ti metterò in catene, ma dovrò farti pagare una multa. E quanto al carico... ne discuteremo col secondo compare dell’affare.";
				link.l1 = "E quanto sarebbe questa multa?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Non fare il finto tonto, capitano! Lo sanno già tutti, e da parecchio tempo per giunta. Vi arresto entrambi per contrabbando e la vostra merce sarà confiscata.";
				link.l1 = "Non mi piacciono le segrete, ufficiale. Amo il mare aperto... e ci sto per salpare proprio adesso. Ma pare che dovrò farlo solo passando sopra il tuo cadavere.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Non ho altra scelta che arrendermi. Ma davvero non ne sapevo nulla!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Adesso parli come si deve... Vediamo il tintinnio delle tue monete... Se non erro, ho udito un numero piuttosto preciso - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+" . Ora che siamo in tre, mi piacerebbe cominciare "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+" . Questo è da parte tua e lo stesso dal tuo compare.";
				link.l1 = "Certo, ufficiale. Ecco le mie monete luccicanti, o, mi scusi, le vostre monete luccicanti – le avete appena perse sulla spiaggia per sbaglio... E non c'è "+GetGoodsNameAlt(iCGood)+" qui, ah-ah, come t’ho già detto.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Ohibò! Sei troppo avido, ufficiale. Tua madre non ti ha mai insegnato che l’avidità porta solo guai? Credo proprio che mi convenga trattare con te a fil di lama.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Scherzi, capitano? Vorresti davvero comprarmi? Sei in arresto! Prendetelo!";
				link.l1 = "Ebbene, se non vuoi guardare i miei dobloni, guarda allora la mia spada!";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Non ho altra scelta che arrendermi. Ma davvero, non ne sapevo nulla!";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Sì, pare proprio che tu abbia ragione... Nulla d’interessante qui, salvo qualche gentiluomo e le mie monete luccicanti. Sei libero di andare, capitano, e noi ci faremo una chiacchierata col tuo compare.";
			link.l1 = "Ci vediamo, ufficiale. Non fargli del male.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Ringrazia il mio buonumore.";
			link.l1 = "Grazie, ufficiale. Davvero, non avevo la minima idea... Ecco, son pronto a pagare la mia multa.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Immagino che nemmeno tu sia poi così onesto, ufficiale. La tua multa è una rapina. Credo che renderò un servizio a questa colonia liberandola della tua presenza.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Bene. Ora puoi andare. E ti consiglio di studiare le leggi locali, così eviterai situazioni come questa in futuro. Vai pure, dobbiamo occuparci del secondo partecipante di questo traffico, quello sapeva tutto, su questo non ci piove.";
			link.l1 = "Ebbene, in tal caso, buona giornata a voi, ufficiale.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "Il comandante si occuperà di te. Seguimi!";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Buongiorno. Cercate qualcosa?";
			link.l1 = "Lo so, compare. Suppongo che tu sia il mio uomo. Sei stato tu a rubare "+pchar.GenQuest.Device.Shipyarder.Type+"  dal cantiere navale locale? Tutte le piste portano a te, quindi niente storie.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Vi supplico, mio signore! Sì, ho rubato quell’arnese strambo dal cantiere navale. Ma non sono riuscito a piazzarlo, nessuno vuole una roba simile. Così me ne sono sbarazzato. Abbiate pietà, buon signore, incolpate la mia fame, non me... Non avrei mai osato rubare, altrimenti!";
					link.l1 = "Questo è un bel guaio... E non ho bisogno neanche di te. Devo trovare quel "+pchar.GenQuest.Device.Shipyarder.Type+". Dimmi dove l’hai gettato?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Vi supplico, mio signore! Sì, ho rubato questa strana cosa dal cantiere navale. Ma non sono riuscito a venderla, a nessuno serve un oggetto simile. Ve la darò. Eccola, prendete, basta che non mi facciate del male e non chiamiate i soldati!";
					link.l1 = "Bene, puoi vivere, furfante. Non mi serve la tua pelle, mi serve quell’aggeggio. Dammi subito quello strumento e sparisci!";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "Cosa vuoi dire? Che cos'è "+pchar.GenQuest.Device.Shipyarder.Type+"?   Non ci capisco un'acca!";
					link.l1 = "Lo prenderò quando verrò a cercarti... o a frugare nel tuo cadavere! Dammi quella cosa, subito!";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Oh... Che diavolo è la "+pchar.GenQuest.Device.Shipyarder.Type+"? Io... e che sarebbe?";
					link.l1 = "Non fare il finto tonto e non provare a svignartela, tanto ti acchiappo lo stesso. Su, fammi rovistare nelle tue tasche...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Proprio dietro le porte della città, non lontano dalla giungla. Ve ne supplico, buon signore! Se davvero vi serve quell’oggetto, potete andare a prenderlo voi stesso. Son certo che sia ancora là, sissignore.";
			link.l1 = "Dovrei costringerti a trovarlo e portarmelo, ma temo che passerei più tempo a rintracciarti che a cercare il "+pchar.GenQuest.Device.Shipyarder.Type+".   Lo farò io stesso. Ma se mi hai mentito, ti troverò, dannato bugiardo!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Ecco, prendi. Grazie, buon signore!";
			link.l1 = "Ebbene, dev’essere proprio ciò che cercavo... ah! Ora sei libero di andartene. Muoviti. E la prossima volta, sta’ più attento.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Ascolta, parli forse di questo strumento? Appartiene a me e non l'ho rubato! E non ho alcuna intenzione di dartelo gratis. Se lo vuoi, pagami "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... Va bene. Ti pagherò. Ecco le tue monete, ora dammi lo strumento!";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Oh, davvero? Davvero pensavi che mi sarei fidato di te, miserabile furfante? Dammi il "+pchar.GenQuest.Device.Shipyarder.Type+" adesso oppure chiamo le guardie, così potremo andare insieme all’arsenale e vedere a chi appartiene davvero questo arnese.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Sei scemo, o cosa? Ascolta, bastardo, hai due opzioni: o mi dai il "+pchar.GenQuest.Device.Shipyarder.Type+" o ti infilzo e prendo lo strumento dal tuo cadavere!";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Bel colpo, capitano! Credo che ci guadagneremo tutti qualcosa, eh eh... prendi, su.";
			link.l1 = "Meno chiacchiere, furfante! Non credere d’avermi ingannato, voglio solo sistemare la faccenda senza rumore e rogne. Queste monete non ti porteranno fortuna comunque. Sparisci!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "No! Non chiamare le guardie! Io... io ti do questo dannato strumento. Prendilo, su!";
				link.l1 = "Questo va molto meglio ora! Sparisci subito! O finirai appeso alla forca, è solo questione di tempo.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Quali guardie, capitano? Siamo solo io e te, qui. Parli troppo, quindi dovrò calmarti... con la mia lama.";
				link.l1 = "Tu osi minacciarmi, feccia?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ah! Aiutatemi! Assassino!";
				link.l1 = "Fermati subito, canaglia!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Ebbene, vediamo chi pugnalerà chi, capitano!";
				link.l1 = "Tu osi minacciarmi, lurido cane?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Cercate qualcosa? Vi prego, buon signore!";
			link.l1 = "Ascolta bene, o mi consegni subito la roba che hai appena rubato dall'arsenale, oppure ti porto dritto dal comandante. In ogni caso quella cosa finirà nelle mie mani, solo che prima ti faranno ballare coi ferri roventi sotto i talloni. Forse dopo ti impiccheranno pure. A te la scelta.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Dammi subito ciò che hai rubato, bastardo, o ti mando dritto all’inferno dove stai!";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Ebbene, dovrai prima acchiapparmi, se vuoi portarmi dall’ufficio del comandante...";
				link.l1 = "Fermati subito, cane!";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "No, non portarmi dal comandante! Te la do io! Tieni, prendi questa, è quello che cerchi, vero? Tanto nessuno la comprerebbe comunque...";
				link.l1 = "Eh, suppongo di poterti portare alla fortezza comunque... Va bene, dammi l’attrezzo e sparisci!";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Ahi! Non farmi del male, ti darò tutto quello che ho! Ecco, prendi!";
			link.l1 = "Bravo, ora ragioni! Sparisci dalla mia vista, o la prossima volta che ti incontro in questa città ti porto dritto dal comandante. Addio!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Fermati subito, compare! Abbiamo bisogno di quella cosa che porti con te. Daccela e poi potrai filartene per la tua strada.";
			link.l1 = "Di che diavolo stai parlando?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Questa marmaglia di strada è diventata troppo insolente... Preparatevi, furfanti!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Non fare il finto tonto! Dacci il pacco e te ne uscirai vivo. Altrimenti... lo prenderemo dal tuo cadavere!";
			link.l1 = "La sorte vi sorride... prendetelo, canaglie, non ho altra scelta.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Ebbene, provaci pure!";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Attento a come parli, amico... Sei stato saggio a non sfidare la sorte. La fine sarebbe stata la stessa, ah-ah! Campa ancora un po'... Ci rivedremo.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Aspetta, "+GetAddress_Form(NPChar)+", non andar così di fretta. Ho un affare da proporti.";
			link.l1 = "Che affari? Non ti conosco.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "So chi sei, capitano. Dunque, veniamo al sodo. Hai appena ricevuto "+pchar.questTemp.WPU.Current.Add+" in "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Non tentare di negarlo, lo sappiamo bene – dopotutto, son giorni che cerchiamo questo documento.";
			link.l1 = "Ah, ora capisco. E quindi?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Dammene il pacco e la nostra breve chiacchierata finisce qui. Non fare lo sbruffone, capitano, vogliamo quei documenti e siamo pronti a menar le mani pure contro la guarnigione cittadina, se serve. \nCapirai bene che sarai tu il primo a lasciarci la pelle se scoppia la rissa. Quindi passa i documenti e ci separeremo da buoni compari.";
			link.l1 = "La sorte è dalla vostra parte... prendetelo, maledetti, non ho altra scelta.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Vuoi forse spaventarmi? Ho visto pesciolini con più fegato di te! Vattene, feccia.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Sono lieto che tu sia stato ragionevole, capitano. Ti sei cacciato in un bel guaio accettando questo incarico. Ora me ne vado, se non ti dispiace.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "È stata una tua scelta...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap();//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Aspetta, "+GetAddress_Form(NPChar)+", non andar così di fretta. Ho un affare da proporti.";
			link.l1 = "Che affari? Sputa subito, che vado di fretta.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "So chi sei. E so anche che hai appena ricevuto una "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+"Questi documenti sono la ragione per cui bramo tanto parlarti.";
			link.l1 = "E non ho voglia di parlare di questa faccenda con chi non conosco. Vuoi mettere le mani su quei documenti? Dammi solo un buon motivo...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Basta così, capitano! Vi sembro forse un brigante? Son un uomo d’affari e rappresento gli interessi di "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+". Voglio proporti un affare assai redditizio, ma non qui. Andiamo nella stanza della taverna e ne parliamo con calma. Non ti porterà via molto tempo.";
			link.l1 = "Questa faccenda puzza troppo... Non voglio aver niente a che fare con te, messere! Sparisci dai piedi!";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm... Vediamo cosa hai da offrirmi. Ma non provare nemmeno ad attaccarmi, non ti conviene. Avanti, ti seguirò.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Sei un uomo testardo e sciocco, capitano! Ti ho offerto l’occasione di guadagnare oro facile. E tu... tu te ne pentirai.";
			link.l1 = "Vattene al diavolo!";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Splendido! Seguimi.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Ora possiamo parlare liberamente.";
			link.l1 = "E qual è la tua proposta?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Come ti ho già detto, si tratta solo dei documenti che hai ricevuto all’ufficio del porto. Tutto ciò che mi serve è una copia, nient’altro.\nTu terrai l’originale, così ti pagheranno per il lavoro. Nessuno saprà mai nulla, e in più ti pagherò profumatamente.";
			link.l1 = "Mi scusi... Ma il pacco è sigillato. Non potrete farne delle copie senza rompere il sigillo!";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Mi aspettavo questa domanda. Dovrò rompere il sigillo, ma non temere, saprò sistemarlo. Ho un cliché duplicato e la ceralacca, ovviamente. Nessuno si accorgerà che il pacco è stato aperto.";
			link.l1 = "Hai forse un'idea storta sull'amministrazione del porto di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Perché lo chiedi, capitano? Sì, ne ho una. Davvero credi che io stia solo perdendo tempo? Ti sto offrendo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" per avere la possibilità di vedere questi documenti. Allora, me lo dai finalmente questo pacco? Ti prego.";
			link.l1 = "Prendili pure, ma li rivoglio indietro ben sigillati!";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Sai, non lo farò. Non mi va a genio.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Non ti crucciare. Sono un vecchio lupo di mare. Siediti e riposa le ossa. Ci vorrà circa un’ora.";
			link.l1 = "Va bene.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... Non mi aspettavo questa. Sei troppo testardo, capitano, quindi dovrò farti fuori qui sul posto e prendermi il pacco a gratis. Prega, perché so maneggiare la lama tanto bene quanto le menzogne.";
			link.l1 = "Se c'è qualcuno che deve pregare qui, spione, quello sei tu!";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Fatto. Come ti dicevo, è stato eseguito con la massima precisione. Prendi il pacco e ciò che ti è stato promesso "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+". E ora devo andare. Buona fortuna, capitano, sono lieto che abbiamo stretto un accordo.";
			link.l1 = "Addio...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Saluti! Oh, che gioia vederti!";
			link.l1 = "Buongiorno. Mh, dimmi un po’, non sei forse il capitano della "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Oh! E come diavolo hai scoperto del "+pchar.questTemp.WPU.Escort.ShipName+"Sì, sono io il suo capitano. O meglio, lo ero... La nave è affondata non lontano da qui.";
			link.l1 = "Ah, allora ti ho trovato... Permettimi di presentarmi - "+GetFullName(pchar)+". Sono qui su richiesta del capo porto di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Mi ha parlato brevemente dei guai della tua carovana e mi ha mandato a cercare la tua nave.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Dunque, sei tu il capitano della spedizione di soccorso?";
			link.l1 = "Qualcosa del genere. Il mio compito era trovare la tua nave o prove che fosse affondata o incapace di navigare. Purtroppo non ho trovato la nave, ma il suo capitano è vivo, ed è già una buona notizia...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Oh, perdonami, mi sono scordato di presentarmi. Io sono "+GetFullName(npchar)+". Sai già come siamo finiti qui? La tempesta ha reso la nostra nave ingovernabile\nQualche giorno dopo, si è schiantata sugli scogli vicino a questa baia e la burrasca l'ha fatta a pezzi in pochi minuti. Solo poche decine del mio equipaggio si sono salvate. Gli altri giacciono sul fondo. Preghiamo per le loro anime ogni giorno...";
			link.l1 = "Accetta le mie condoglianze, capitano "+GetFullName(npchar)+". Mi rincresce davvero.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Grazie... I superstiti hanno allestito un campo sulla riva, sperando in aiuto. Sei arrivato giusto in tempo, capitano! Gli indiani bellicosi della zona sanno che siamo qui, non potremo resistere contro centinaia di loro se ci attaccano.\nC'è anche una nave pirata che pattuglia queste acque, sembra proprio che ci stiano dando la caccia. Hai già incontrato questo pirata, capitano?";
			link.l1 = "No, non l'ho fatto.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Loda il Signore per questo. È uno di quei cani che ci hanno assalito prima di quella maledetta tempesta. Come una iena, brama finire la preda ferita, così è giunto qui, su quest’isola.";
			link.l1 = "Capisco. Ora dobbiamo decidere il nostro prossimo passo.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Decidere cosa, capitano? Portaci a bordo e leviamo le ancore da questo maledetto posto.";
			link.l1 = "Assolutamente. Non sono riuscito a salvare la nave, almeno salverò il suo equipaggio. Smonta il campo e ordinerò di mandare qui le scialuppe. Benvenuti a bordo!";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Grazie, capitano! Non ci vorrà molto. Aspetta... Che diavolo? Argh! Quei dannati diavoli dalla pelle rossa tornano a darci la caccia! Allarme! Alle armi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Fiu, ce l’abbiamo fatta... Vedi, capitano, te l’avevo detto che questa baia è l’inferno in terra. È già il terzo assalto degli indiani! Dobbiamo sgomberare da qui al più presto, non sopravviveremo a un altro attacco.";
			link.l1 = "Sì, hai ragione. Raduna ogni anima viva e salite tutti sulla mia nave! Ordinerò subito di calare le scialuppe!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hic... Cosa vuoi da me? Sparisci, non ho voglia di ciarlare con te.";
			link.l1 = "Sei tu "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Sì, sono io. E tu che diavolo vuoi?";
			link.l1 = "È piuttosto semplice. C’è qualcuno in questa città che si è proprio stufato dei tuoi giochetti. Questa persona non ne può più. Ora che ti guardo capisco il perché. Non farti più vedere nel bordello locale, o ti caccerai nei guai. Capito?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh! Tu... osi minacciarmi, lurido cane? Ti infilzerò sulla mia lama e ti arrostirò come un pollo allo spiedo!";
						link.l1 = "Preparati, bastardo!";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "Cosa? Quali trucchi? Non c’erano inganni. Mi sono ubriacato e ho fatto baldoria un paio di volte al bordello. Nessuno è senza peccato... Va bene, va bene, va bene... Non metterò più piede là dentro. Adesso sei contento? Parola mia.";
						link.l1 = "Spero che la parola d'onore abbia ancora valore per te, e che tu sappia quali saranno le conseguenze se la infrangi. Tienilo a mente. Addio, ora.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Sei un uomo così insolente, signore! Vi giuro che vi pentirete delle vostre parole prima che cali il sole. Vi sfido! Credo sia meglio regolare la questione lontano da occhi indiscreti, in qualche luogo appartato. La giungla andrà a pennello, incontriamoci là fra due ore!";
					link.l1 = "Una gran bella trovata! Almeno non sarebbe un impiccio far sparire il tuo cadavere.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "Cosa? Quali trucchi? Non c’è stato nessun trucco. Mi sono ubriacato e ho fatto baldoria un paio di volte al bordello. Nessuno è senza peccato... Va bene, va bene, va bene... Non metterò più piede lì, mai più. Ora sei contento? Hai la mia parola.";
					link.l1 = "Spero che la parola data significhi ancora qualcosa per te e che tu sappia bene quali siano le conseguenze in caso d'infrazione. Tienilo bene a mente. Addio, ora.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Aspetta! Fermati! Mi arrendo! Abbi pietà!";
			link.l1 = "E così adesso parli così!";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Ti supplico, abbi pietà di me! Farò tutto ciò che vuoi! Non metterò mai più piede in quel bordello!";
			link.l1 = "Questa posa si addice solo a una canaglia come te. Spero che ti serva da lezione per tutta la vita. E ora, comportati come si deve in questa città.";
			link.l1.go = "Badboy_exit";
			link.l2 = "Certo che no. I tuoi inganni finiscono qui e ora.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "È ora di scendere all’inferno, bastardo! Preghiere veloci, che non ho tutta la maledetta giornata...";
			link.l1 = "Meno chiacchiere, più botte, feccia!";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "Eccolo lì, quel bastardo insolente! Facciamogli vedere chi comanda in questa città, ragazzi!";
			link.l1 = "Ah, sei proprio uno svergognato! Ma ti avevo avvisato. Tu e i tuoi scimmioni tra poco andrete tutti dritti all'inferno!";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Salute. Che desideri?";
			link.l1 = "Non sei forse tu "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Non ci crederai, ahah. Voglio la tua testa.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... No... Non è nulla. Pare che mi sia sbagliato. Perdonami per averti importunato.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Che scherzo da quattro soldi, signore! Spiegati subito o ti faccio vedere io...";
			link.l1 = "E che pensi di fare, lurido sgombro? Hai fatto un torto a un brav’uomo e quello è davvero infuriato. Ora prega il tuo Dio e sbrigati, ché ho fretta.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "Che... che state facendo, signore! Aiuto! Qualcuno mi aiuti! Assassino!";
			link.l1 = "E pensavo che avresti speso gli ultimi istanti della tua vita in preghiera, così almeno avresti avuto una speranza di salpare verso il cielo...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Ancora tu? Perché mai non mi dici cosa vuoi?";
			link.l1 = "Non è nulla.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! Cosa? Che diavolo ci fai qui, maledetto? Chi ti ha fatto entrare?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "La Lega ha bisogno della tua vita, capitano...";
			link.l1 = "Cosa? Maledizione!";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiedo di rinfoderare la lama.","Ascolta, sono cittadino di questa città e ti chiedo di rinfoderare la lama.");
			link.l1 = LinkRandPhrase("Bene.","D'accordo.","Certo...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' all'erta, "+GetSexPhrase("compare","ragazza")+", mentre corri con un’arma in pugno. Potrei innervosirmi anch’io...","Non mi va quando ci sono "+GetSexPhrase("uomini che","gente che")+" stanno camminando davanti a me con l’arma sguainata. Mi fanno venire i brividi...");
				link.l1 = LinkRandPhrase("Capito.","Va tutto bene.","Non ti crucciare...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
