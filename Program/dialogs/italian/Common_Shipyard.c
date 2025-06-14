// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("Prima visita al cantiere navale " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'allarme è stato dato in città, e tutti ti stanno cercando. Se fossi in te, non resterei qui.","Tutte le guardie della città stanno setacciando la città alla tua ricerca. Non sono un pazzo e non parlerò con te!","Corsa, "+GetSexPhrase("compagno","ragazza")+", prima che i soldati ti trasformino in un setaccio..."),LinkRandPhrase("Di cosa hai bisogno, "+GetSexPhrase("mascalzone","puzzolente")+"?! Le guardie della città hanno già il tuo odore, non andrai lontano, sporco pirata!","Assassino, lascia subito la mia casa! Guardie!","Non ho paura di te, "+GetSexPhrase("birbante","ratto")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti strapperò la lingua!","Eh, "+GetWorkTypeOfMan(npchar,"")+", e anche lì - a catturare pirati! Ecco cosa ti dico, compagno: stai tranquillo e non morirai!"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Desidera qualcosa, Monsieur?";
					Link.l1 = "Sono venuto a dare un'occhiata alle vostre navi... Ma ora sono un po' occupato - ho ancora un affare in sospeso. Tornerò più tardi, una volta che avrò finito.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Desidera qualcosa, Monsieur?";
					Link.l1 = "Ascolta, vorrei acquistare una nave da te.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Desidera qualcos'altro, Monsieur?";
				Link.l1 = "No, suppongo di no.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "Ecco, Capitano. Il lavoro è finito. Ora la parte piacevole - il suono delle monete. Dammi un secondo...";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Ufficiale, aspetta! Per favore! Questo deve essere un qualche tipo di errore. Signore, il Capitano non c'entra nulla con questo, ha solo attraccato qui per riparare la sua nave. Stava proprio per partire. E quali barili? Di cosa stai parlando?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Ufficiale, ripeto: il Capitano è venuto qui per pagare le riparazioni della nave. Questi barili sono di mia proprietà e sono solo per scopi produttivi. Sono un maestro costruttore di navi e questa resina è per le navi che costruisco.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "Oh, Signor Capitano! Non hai idea di quanto fosse terribile per me. Due giorni nelle segrete in compagnia di ratti, topi e personaggi miserabili! Ho dovuto usare ogni connessione che avevo per tirarmi fuori da lì. Ah, l'aria fresca!";
					link.l1 = "Avete la mia simpatia, maestro. Che ne è della nostra resina? E delle mie monete?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "Oh, sei tu di nuovo! Ti riconosco, giovane! Eri tu che recentemente hai chiesto di... aumentare la velocità della tua nave usando la tela di seta per le vele, giusto?";
				link.l1 = "La tua memoria ti fa onore, maestro."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Ha! Un vero vecchio lupo di mare è venuto nel mio modesto laboratorio! Sei nuovo in queste acque locali, Capitano?","Benvenuto, Signore! Se non sei estraneo al mare e hai una nave - sei arrivato proprio nel posto giusto!","Salve, Signore! Siete fortunato - questa è la migliore officina navale di tutto il Nuovo Mondo britannico."),LinkRandPhrase("Signore, presumo che tu sia un Capitano audace, non è vero? Se lo sei, hai fatto bene a visitare il mio modesto cantiere navale!","Prima volta qui, Monsieur Capitano? Entra e incontra questo vecchio maestro d'ascia.","Conosciamoci, Monsieur! Una nave ha bisogno di essere accarezzata, proprio come una donna - e noi, i francesi, siamo esperti in questo! Fidati di me, non rimpiangerai di essere venuto qui!"),LinkRandPhrase("Non ti ho mai visto qui prima, Signore. Piacere di conoscerti!","Saluto un valoroso conquistatore dei mari! Sei un marinaio, vero? E io sono il costruttore navale locale, dovremmo conoscerci.","Salve, Cavaliere! Sono lieto di darvi il benvenuto nella mia officina!"),LinkRandPhrase("Buon pomeriggio, Mynheer. Non ci siamo mai incontrati prima, giusto? Hai affari con me?","Salve, signor capitano. Non sorprenderti, ho incontrato molti capitani, quindi ho capito al primo sguardo che anche tu sei un capitano.","Entra, Signore. Sono il maestro d'ascia locale. Piacere di conoscerti."));
				Link.l1 = LinkRandPhrase("Anche io sono lieto di conoscerti. Il mio nome è "+GetFullName(pchar)+", e sono nuovo in questi luoghi. Quindi, ho deciso di fare un salto.","Semplicemente non potevo passare oltre - sai, quel profumo di tavole appena piallate... Io sono "+GetFullName(pchar)+", Capitano della nave '"+pchar.ship.name+"'. ","Permettimi di presentarmi - "+GetFullName(pchar)+", Capitano della nave '"+pchar.ship.name+"', lieto di conoscerti. Quindi, stai costruendo e riparando navi qui, vero?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Saluti, Capitano MacArthur.";
					link.l1 = "Potete chiamarmi semplicemente Helen, Signore "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh! Il terrore delle acque locali, Capitano "+GetFullName(pchar)+"! Cosa posso fare per te?","Andiamo dritti al punto, "+GetAddress_Form(NPChar)+", Non ho tempo per chiacchierare. Hai bisogno di una riparazione o vuoi solo sostituire la tua vasca?","Oh, non è che "+GetFullName(pchar)+"! Cosa c'è, "+GetAddress_Form(NPChar)+"? È successo qualcosa di brutto alla tua vasca?"),LinkRandPhrase("Cosa ci vuole lì, Capitano? Non un singolo minuto di pace - sempre tutti questi furfanti, che maledetta giornata...","Ciao, "+GetAddress_Form(NPChar)+". Devo dire che la tua visita ha spaventato tutti i miei clienti. Spero che il tuo ordine coprirà i miei danni?","Per affari con me, "+GetAddress_Form(NPChar)+"? Allora, sbrigati e fai in fretta."),LinkRandPhrase("Cosa ti porta da me, Signor "+GetFullName(pchar)+"? Posso capire che la tua nave potrebbe avere delle difficoltà, considerando il tuo stile di vita...","Sono lieto di salutare un nobile... oh, scusami, "+GetAddress_Form(NPChar)+", Ti ho scambiato per qualcun altro. Cosa volevi?","Non mi piace molto il tuo tipo, Capitano, ma non ti caccio via, comunque. Cosa volevi?")),LinkRandPhrase(LinkRandPhrase("Sono molto lieto di vederti, Signor "+GetFullName(pchar)+"! Allora, come va? Hai bisogno di una riparazione o di carenaggio?","Benvenuto, "+GetAddress_Form(NPChar)+"! Capitano "+GetFullName(pchar)+" è sempre un ospite gradito nel mio laboratorio!","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sei venuto a trovarmi di nuovo! Spero che la tua bellezza stia bene, non è vero?"),LinkRandPhrase(""+GetAddress_Form(NPChar)+", Sono così felice di rivederti! Come sta la tua bellissima nave? Hai bisogno di aiuto?","Oh, "+GetAddress_Form(NPChar)+", saluti! Come stai? Forse gli alberi scricchiolano o hai bisogno di svuotare la sentina? I miei ragazzi daranno il massimo per te!","Buon pomeriggio, Capitano "+GetFullName(pchar)+". Sono felice che tu sia passato di nuovo, e sono sempre pronto ad aiutarti."),LinkRandPhrase("Sono felice di averti qui, Capitano! Sei un cliente molto gradito, "+GetAddress_Form(NPChar)+", e spero che tu rimanga tale.","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sono davvero felice di averti qui! Cosa posso fare per te?","Capitano, di nuovo avete visitato "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Credimi, saremo lieti di aiutarti.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Prendi i tuoi strumenti, maestro, e stai zitto, va bene? Non sono dell'umore.","Smettila di chiacchierare, amico! Ho bisogno del tuo aiuto, non delle tue sciocchezze."),RandPhraseSimple("Io sto pagando - e tu stai lavorando. In silenzio. È chiaro?","Ehi, compagno, mandali tutti via - sono io, il tuo cliente preferito!")),RandPhraseSimple(RandPhraseSimple("Sono felice di vederti anche tu, maestro. Ahimè, non ho molto tempo, quindi passiamo ai fatti.","E sono felice di vederti anche tu, amico. Vuoi aiutare il tuo cliente preferito?"),RandPhraseSimple("Buon pomeriggio, amico. Andiamo subito al dunque. Prometto, la prossima volta ci siederemo sicuramente a bere una bottiglia.","Sono lieto di vederti, maestro. È sempre un piacere vederti, ma adesso ho bisogno del tuo aiuto.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "Ho bisogno di cannoni per la mia nave.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Potete offrirmi qualcosa di speciale, qualcosa che non può essere trovato in nessun altro cantiere navale?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "Non hai un lavoro che richiede l'aiuto di uno sconosciuto?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "Voglio comprare un set di attrezzi da costruzione, forgiatura e misurazione di qualità europea. Puoi aiutarmi?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "Porto dei dobloni per un set di attrezzi da costruzione.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "Ti ho consegnato "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", come hai chiesto.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "Sono riuscito a trovare il ladro e a ottenere "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Voglio cambiare l'aspetto delle mie vele.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Volevo solo parlare.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Vorrei parlare con te di questioni finanziarie.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Sono qui su richiesta di un uomo. Il suo nome è Governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato da te. Dovrei ritirare qualcosa...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Ho portato il disegno della nave da "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Ciao, sono venuto su invito di tuo figlio."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "Si tratta di tua figlia...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Devo andare.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "Sono molto lieto di incontrare un nuovo cliente. Il mio cantiere navale è a tua disposizione.";
				Link.l1 = "Eccellente, "+GetFullName(NPChar)+". Diamo un'occhiata a cosa puoi offrirmi.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Mi servono cannoni per la mia nave.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Non hai un lavoro che richiede l'aiuto di uno sconosciuto?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Voglio cambiare l'aspetto delle mie vele.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Volevo solo parlare.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Vorrei parlare con te di questioni finanziarie.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Sono qui su richiesta di un uomo. Il suo nome è Governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha inviato da te. Dovrei ritirare qualcosa...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Ho consegnato il disegno della nave dalla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Salve, sono venuto su invito di vostro figlio."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Questo riguarda tua figlia...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Cosa mi puoi dire sul proprietario di questi documenti?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Devo andare, grazie.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Certo, Capitano MacArthur, come desidera. Di cosa ha bisogno oggi?";
				Link.l1 = "Eccellente, "+GetFullName(NPChar)+". Diamo un'occhiata a cosa puoi offrirmi.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Ho bisogno di cannoni per la mia nave.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Non hai un lavoro che richiede l'aiuto di uno sconosciuto?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Voglio cambiare l'aspetto delle mie vele.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Volevo solo parlare.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Vorrei parlare con te di questioni finanziarie.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Sono qui su richiesta di un uomo. Il suo nome è Governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato da te. Dovrei ritirare qualcosa...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Ho consegnato il disegno della nave dalla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Ciao, sono venuto su invito di tuo figlio."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Si tratta di tua figlia...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Cosa mi puoi dire del proprietario di questi documenti?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Devo andare, Grazie.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "Il nostro cantiere navale è noto per migliorare le navi. Sei interessato, Capitano?";
			Link.l1 = LinkRandPhrase("Eccellente! Forse potresti dare un'occhiata alla mia nave e dirmi come può essere migliorata?","È molto interessante, maestro! E cosa potete fare per la mia nave?","Mmm... Sai, mi sono abituato alla mia nave, ma se mi offri qualcosa di veramente interessante, posso pensarci. Che ne dici?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "Ehhh... Non mi occupo di barche. Un vecchio secchio rimarrà sempre un vecchio secchio, non importa quanto impegno ci metti.";
					Link.l1 = "Capisco...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "Così così... vediamo cosa abbiamo qui... Sì - "+XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName)+". La tua nave ha già il massimo numero di caratteristiche migliorate, temo che ulteriori lavori su di essa non abbiano senso e possano solo fare del male.";
					Link.l1 = "Capisco...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Prima di migliorare una nave, deve essere completamente riparata. Anche questo può essere fatto qui nel mio cantiere navale.";
					Link.l1 = "Capito...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Aumenta la velocità.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Aumenta l'angolo rispetto al vento.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Aspetta! Ho cambiato idea.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Aumenta la velocità.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Aspetta! Ho cambiato idea.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Aumenta l'angolo rispetto al vento.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Aspetta! Ho cambiato idea.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! La mia nave è già stata migliorata in questo modo. Beh, grazie per il tuo tempo!","Grazie, maestro, ma ho già un miglioramento, ed è esattamente quello che mi hai menzionato. Buona fortuna con le altre navi e i loro capitani!","Eh! Immagino che la mia nave sia già stata rinnovata da un precedente proprietario - deve essere stato proprio in questo cantiere navale, Beh, suppongo che dovrei ringraziarlo per la sua lungimiranza, e te e i tuoi ragazzi per il loro eccellente lavoro!");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Aumenta il numero massimo di cannoni.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "Aumenta il peso morto.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Aspetta! Ho cambiato idea.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Aumenta il numero massimo di cannoni.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Aspetta! Ho cambiato idea.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Aumenta il peso morto.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Aspetta! Ho cambiato idea.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! La mia nave è già migliorata in questo modo. Beh, grazie per il tuo tempo!","Grazie, maestro, ma ho già un miglioramento, ed è esattamente quello che mi hai menzionato. Buona fortuna con le altre navi e i loro capitani!","Eh! Immagino che la mia nave sia già stata rinnovata da un precedente proprietario - deve essere stato proprio in questo cantiere navale, Beh, immagino che dovrei ringraziarlo per la sua lungimiranza, e te e i tuoi ragazzi per il loro eccellente lavoro!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Aumenta la durabilità dello scafo.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Aumenta lo spazio dell'equipaggio.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Aspetta! Ho cambiato idea.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Aumenta la resistenza dello scafo.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Aspetta! Ho cambiato idea.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Aumenta lo spazio dell'equipaggio.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Aspetta! Ho cambiato idea.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("Oh! La mia nave è già stata migliorata in questo modo. Beh, grazie per il tuo tempo!","Grazie, maestro, ma ho già un miglioramento, ed è esattamente quello che mi hai menzionato. Buona fortuna con le altre navi e i loro capitani!","Eh! Immagino che la mia nave sia già stata rinnovata da un precedente proprietario - deve essere stato proprio in questo cantiere navale, Beh, suppongo che dovrei ringraziarlo per la sua lungimiranza, e te e i tuoi ragazzi per il loro eccellente lavoro!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Aumenta la manovrabilità.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Riduci la dimensione minima dell'equipaggio.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Aspetta! Ho cambiato idea.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Aumenta la manovrabilità.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Aspetta! Ho cambiato idea.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Riduci la dimensione minima dell'equipaggio.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Aspetta! Ho cambiato idea.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("Oh! La mia nave è già migliorata in questo modo. Beh, grazie per il tuo tempo!","Grazie, maestro, ma ho già un miglioramento, ed è esattamente quello che mi hai menzionato. Buona fortuna con le altre navi e i loro capitani!","Eh! Immagino che la mia nave sia stata già rinnovata da un precedente proprietario - deve essere stato proprio in questo cantiere navale. Beh, suppongo che dovrei ringraziarlo per la sua lungimiranza, e te e i tuoi ragazzi per il loro eccellente lavoro!");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "Dove è la nave? Mi stai prendendo in giro o cosa?";
			    Link.l1 = "Oh, mio errore, certo... Mi dispiace.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "Concordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "No. Questo non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Eccellente. Starò aspettando il materiale.";
			    link.l1 = LinkRandPhrase("Vi assicuro che non dovrete aspettare a lungo. Posso risolvere questi problemi, va bene?","Considera che li hai già e tieni il molo per me. Sarò veloce come il vento.","Certo. Dovrò solo visitare un paio di persone che hanno le cose che hai richiesto, ah-ah!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Il tempo passa, e la nave aspetta. Hai portato tutto quello che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a trovare qualcosa.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "No, ci sto ancora lavorando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Signor"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahimè, sono tutte circostanze! Peccato che il deposito sia stato perso...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora inizierò a lavorare.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Mi serve ancora: legno di ferro - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.65);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...Sembra essere tutto... Ora puoi caricare completamente la tua stiva, garantisco la qualità del mio lavoro.";
			Link.l1 = "Grazie! Lo proverò.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "D'accordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "No. Non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Eccellente. Starò aspettando il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovrete aspettare a lungo. Posso risolvere questi problemi, va bene?","Considera che li hai già e tieni il molo per me. Sarò veloce come il vento.","Certo. Dovrò solo visitare un paio di persone che hanno quello che hai richiesto, ah-ah!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Il tempo passa e la nave aspetta. Hai portato tutto quello che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a trovare qualcosa.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "No, ci sto ancora lavorando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Signore"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahimè, sono tutte le circostanze! Peccato che il deposito sia stato perso...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora, comincio a lavorare.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Mi serve ancora: seta per nave - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.65);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.35 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Tutto è pronto, Capitano. Prendi il vento a vela piena. Controlla se vuoi!";
			Link.l1 = "Grazie! Lo proverò.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "D'accordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "No. Non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Eccellente. Aspetterò il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovrete aspettare a lungo. Posso risolvere questi problemi, va bene?","Considera che li hai già e tienimi il molo. Sarò veloce come il vento.","Certo. Dovrò solo visitare un paio di persone che hanno le cose che hai richiesto, ah-ah!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Il tempo passa e la nave aspetta. Hai portato tutto ciò che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a consegnare qualcosa.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "No, ci sto ancora lavorando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Signor"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahi, sono tutte circostanze! Peccato che il deposito sia stato perso...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora comincio a lavorare.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Mi servono ancora: corde - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... Tutto dovrebbe essere pronto ora... Controlla il timone ora, Capitano!";
			Link.l1 = "Grazie! Lo proverò.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Concordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "No. Questo non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Eccellente. Starò aspettando il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovrete aspettare a lungo. Posso risolvere tali problemi, va bene?","Considera che li hai già e tieni il molo per me. Sarò veloce come il vento.","Certo. Dovrò solo visitare un paio di persone che hanno le cose che hai richiesto, ah-ah!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Il tempo passa e la nave aspetta. Hai portato tutto quello che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a trovare qualcosa.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "No, sto ancora lavorando su di esso.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Signor"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahimè, sono tutte circostanze! Peccato che il deposito sia stato perso...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Comincerò a lavorare, allora.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Mi serve ancora: legno di ferro - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.65);
			}
			else
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
			}
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... È fatto, Capitano. Ora puoi assumere più marinai, ci sarà abbastanza spazio per tutti.";
			Link.l1 = "Grazie! Lo proverò.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "D'accordo. Accetto le tue condizioni. Ti porterò tutto ciò di cui hai bisogno.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "No. Questo non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Eccellente. Starò aspettando il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovrete aspettare a lungo. Posso risolvere tali problemi, capito?","Considera che li hai già e tieni il molo per me. Sarò veloce come il vento.","Certo. Dovrò solo fare visita a un paio di persone che hanno quello che hai richiesto, ah-ah!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Il tempo passa e la nave attende. Hai portato tutto quello che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a trovare qualcosa.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "No, ci sto ancora lavorando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Signor"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Purtroppo, sono tutte circostanze! Peccato che il deposito sia andato perso...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora, comincerò a lavorare.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Mi servono ancora: corde - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.65);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Pronto, Capitano! Ora meno marinai possono gestire la nave con lo stesso risultato complessivo.";
			Link.l1 = "Grazie! Lo proverò.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "D'accordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "No. Non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Eccellente. Starò aspettando il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovrete attendere a lungo. Posso risolvere tali problemi, va bene?","Considera che li hai già e tieni il cantiere navale per me. Sarò veloce come il vento.","Certo. Dovrò solo visitare un paio di persone che hanno la roba che hai richiesto, ah-ah!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Il tempo scorre, e la nave sta aspettando. Hai portato tutto quello che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a trovare qualcosa.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "No, ci sto ancora lavorando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Signorina"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahi, sono tutte circostanze! Peccato che il deposito sia stato perso...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora inizio a lavorare.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Mi serve ancora: resina - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.65);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
				}
				else
				{
					shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				}
			}
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... Questo dovrebbe bastare... Garantisco che d'ora in poi i tuoi nemici avranno molta più difficoltà a fare a pezzi lo scafo della tua nave!";
			Link.l1 = "Eh, mi fiderò della tua parola! Grazie, maestro.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Concordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "No. Questo non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Eccellente. Starò aspettando il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovete aspettare a lungo. Posso risolvere questi problemi, va bene?","Considera che li hai già e tienimi il molo. Sarò veloce come il vento.","Certo. Dovrò solo fare visita a un paio di persone che hanno quello che hai richiesto, ah-ah!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Il tempo passa, e la nave sta aspettando. Hai portato tutto quello che ho richiesto?";
			    Link.l1 = "Sì, sono riuscito a consegnare qualcosa.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "No, ci sto ancora lavorando.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Signor"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahimè, sono tutte circostanze! Peccato che il deposito sia stato perso...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora comincerò a lavorare.";
			    link.l1 = "Sto aspettando.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "Mi serve ancora: seta per nave - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Pronto, Capitano!.. La tua nave navigherà molto più veloce controvento ora.";
			Link.l1 = "Grazie! Lo proverò.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "D'accordo. Accetto le vostre condizioni. Vi porterò tutto ciò di cui avete bisogno.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "No. Questo non mi va bene.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Eccellente. Starò aspettando il materiale.";
				link.l1 = LinkRandPhrase("Vi assicuro che non dovrete aspettare a lungo. Posso risolvere questi problemi, va bene?","Considera che li hai già e tienimi il molo. Sarò veloce come il vento.","Certo. Dovrò solo fare visita a un paio di persone che hanno la roba che hai richiesto, ah-ah!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "Non vedo il deposito...";
				link.l1 = "Passerò più tardi.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Il tempo passa, e la nave aspetta. Hai portato tutto quello che ho richiesto?";
				Link.l1 = "Sì, sono riuscito a trovare qualcosa.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "No, ci sto ancora lavorando.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Signorina"+GetSexPhrase("ter","s")+", hai cambiato la tua nave da quando abbiamo fatto il nostro accordo? Non avresti dovuto.";
			    Link.l1 = "Ahimè, sono tutte circostanze! Peccato che il deposito sia andato perso...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Inizierò a lavorare, quindi.";
				link.l1 = "Sto aspettando.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Mi serve ancora: resina - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Bene.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... Ecco, Capitano. Puoi usare cannoni aggiuntivi - cioè, se li hai, he-he.";
			Link.l1 = "Grazie!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Вы узнали много нового о строении корабля!", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "Ho un problema che deve essere risolto. Ho un ordine per una nave - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". Tuttavia, nel mio cantiere non c'è una tale nave ora e nei prossimi due mesi non avrò la possibilità di procurarmene una.\nSe puoi darmi una tale nave - te ne sarei molto grato, e ti pagherò una somma una volta e mezza superiore al suo prezzo di vendita.";
					link.l1 = "Un'offerta interessante. Accetto!";
					link.l1.go = "Findship";
					link.l2 = "Questo non mi interessa.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "Sei arrivato proprio in tempo. Forse, potresti essere in grado di aiutarmi. Qualcuno mi ha rubato uno strumento molto prezioso proprio ieri - "+pchar.GenQuest.Device.Shipyarder.Type+". Non ho la possibilità di farne un altro e non posso permettermi il tempo o il costo per ordinarlo dall'Europa. E senza di esso non posso costruire normalmente le navi, lo sai?\nE la parte più fastidiosa - questa cosa non è necessaria a nessuno tranne i costruttori di navi, e io sono l'unico costruttore di navi nella colonia. Questo ladro non lo venderà a nessuno e lo butterà via. Forse proverai a rintracciare il ladro, chiedere in giro per la città, ma io semplicemente non ho il tempo di stare lontano dal cantiere navale - ho bisogno urgentemente di completare ordini speciali.";
					link.l1 = "Bene, ci proverò. Dimmi, come sembrava quel... dispositivo tuo?";
					link.l1.go = "Device";
					link.l2 = "Questo non mi interessa.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "Non ho nulla di quel genere.";
			link.l1 = "Come dici tu.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Eccellente! Sono molto contento che tu sia riuscito così rapidamente. Dove è quella nave?";
			link.l1 = "At the moment the vessel is at the roadstead; her name is '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Ecco i tuoi soldi - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+". Grazie per il lavoro. Non dimenticare di venire a trovarmi di nuovo. Arrivederci!";
			link.l1 = "Arrivederci, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Certo, cercherò di spiegarlo in parole semplici. Sembra che "+pchar.GenQuest.Device.Shipyarder.Describe+". È unico nel suo genere, quindi lo riconoscerai molto facilmente. Se mi porterai quell'oggetto, ti ricompenserò generosamente.";
			link.l1 = "Capito. Inizierò la mia ricerca immediatamente!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "L'hai fatto! Non hai idea di quanto io sia grato! Avevo già perso ogni speranza di rivedere il mio strumento.";
			link.l1 = "Eccolo qui.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "Per i tuoi sforzi ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+". Spero che sarebbe una ricompensa degna.";
			link.l1 = "Grazie!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "Inoltre, vorrei farti un'offerta, come ulteriore gratitudine.";
				link.l1 = "È interessante. Bene, vai avanti - mi piacciono le sorprese piacevoli.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "Appena ho lanciato una nuova nave - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType,"Name")+"Acc"))+". Ci sono già diversi clienti per questa nave, ma ti darò la priorità. Se ti piace questa nave, e non ti spaventa il prezzo - puoi comprarla.";
			link.l1 = "Eh! Certo, diamo un'occhiata!";
			link.l1.go = "Device_complete_4";
			link.l2 = "Grazie, ma la mia nave attuale mi va benissimo e non ho intenzione di sostituirla.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "Ebbene, come desideri. Grazie ancora una volta - e buona fortuna!";
			link.l1 = "Buona fortuna anche a te!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Fammi dare un'occhiata... No, non c'era nessuno come lui. Immagino che dovresti vedere il maestro del porto riguardo a quella questione.";
				link.l1 = "Certo...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1 = "No, non credo...";
				link.l1.go = "exit";
				link.l2 = "Grazie, "+GetFullName(NPChar)+"! Per favore, trasmetti i miei rispetti al tuo amico.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Ti ascolto attentamente.";
			link.l1 = "Ho portato il vostro fuggitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Capitano, grazie mille! Come sta? È ferita? Perché è scappata? Perché?\nNon capisce? Lo sposo è un uomo ricco e importante! La gioventù è ingenua e sciocca... persino crudele. Ricorda questo!";
			link.l1 = "Ebbene, tu sei suo padre e la decisione finale è tua, ma io non mi sbrigerei con il matrimonio...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Cosa ne sai tu? Hai dei figli tuoi? No? Quando ne avrai uno, vieni a trovarmi e ne parleremo.\nHo promesso una ricompensa a chiunque la riportasse alla famiglia.";
			link.l1 = "Grazie. Dovresti tenerla d'occhio. Ho il sospetto che non si fermerà a questo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, quindi tu sei quel Capitano che ha portato a mio figlio prodigo una giovane sposa?";
				link.l1 = "Sì, sono stato io.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, ci sei "+GetSexPhrase("lui è, il nostro benefattore","lei è, la nostra benefattrice")+". Aspetti una ricompensa, immagino?";
				link.l1 = "Beh, sto bene senza ricompensa, una tua buona parola andrebbe più che bene.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sono molto grato a te per non aver abbandonato mio figlio in gravi difficoltà e per averlo aiutato a trovare una via d'uscita da una delicata situazione. Permettimi di ringraziarti e, per favore, accetta questa modesta somma e un regalo da me personalmente.";
			link.l1 = "Grazie. Aiutare questa giovane coppia è stato un piacere per me.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Grazie? Che grazie?! È mezzo anno che quel testone se ne sta in giro senza un lavoro - e guardalo, ha abbastanza tempo per le sue avventure amorose! Quando avevo la sua età, gestivo già la mia attività! Pff! Un Governatore ha una figlia nubile - e quel stupido ha portato una sgualdrina senza parenti né famiglia a casa mia e ha osato chiedere la mia benedizione!";
			link.l1 = "Mmm... A quanto pare, non credi nei sentimenti sinceri?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Quali sentimenti? Di che sentimenti stai parlando? Sentimenti... come si può essere così frivoli alla tua età?! Vergognati di assecondare i capricci dei giovani e di comportarti come un ruffiano! Non solo hai portato via una ragazza dalla sua casa, ma hai anche rovinato la vita del mio novellino. Non ci saranno ringraziamenti per te. Addio.";
			link.l1 = "Bene, e altrettanto a te...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Stai scherzando? Dov'è la tua nave? Non la vedo nel porto!","Giuro al diavolo, non mi ingannerai! La tua nave non è nel porto!"),pcharrepphrase("Non vedo la tua nave nel porto, Capitano "+GetFullName(pchar)+". Spero davvero che non sia il 'Olandese Volante'?","Capitano, è molto più facile caricare il carico dal molo. Porta la tua nave al porto e torna."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Che problema! Va bene, vecchio furfante, a presto!","Non volevo ingannarti, "+GetFullName(npchar)+", una nave dall'altra parte dell'isola."),pcharrepphrase("No. La mia nave si chiama 'Perla Nera'! Che cosa è successo al tuo viso? È pallido... Ahah! Scherzo!","Grazie per il consiglio, farò sicuramente così."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Stai scherzando? Dove è la tua nave? Non la vedo nel porto!","Giuro al diavolo, non mi ingannerai! La tua nave non è nel porto!"),pcharrepphrase("Non vedo la tua nave nel porto, Capitano "+GetFullName(pchar)+". Spero che non sia il 'Olandese Volante'?","Capitano, è molto più facile caricare il carico dal molo. Porta la tua nave al porto e torna."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Che guaio! Va bene, vecchio furbo, ci vediamo presto!","Non volevo ingannarti, "+GetFullName(npchar)+", una nave dall'altra parte dell'isola."),pcharrepphrase("No. La mia nave si chiama 'Black Pearl'! Cosa è successo al tuo viso? È pallido... Haha! Scherzo!","Grazie per il consiglio, farò sicuramente così."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Cambiare il colore delle vele costa "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+", cambiare lo stemma costa "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSGERALD_PRICE_RATE))+", sostituendo le vele - dipende dalla tua nave.";
							  
			    link.l1 = "Scegli un nuovo colore.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Dipingi un nuovo stemma.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Installa vele uniche."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "Ho cambiato idea.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Stai scherzando? Dov'è la tua nave? Non la vedo nel porto!","Giuro al diavolo, non mi ingannerai! La tua nave non è nel porto!"),pcharrepphrase("Non vedo la tua nave nel porto, Capitano "+GetFullName(pchar)+". Spero davvero che non sia il 'Olandese Volante'?","Capitano, è molto più facile caricare la merce dal molo. Porta la tua nave al porto e torna."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Che guaio! Va bene, vecchio furfante, a presto!","Non volevo ingannarti, "+GetFullName(npchar)+", una nave dall'altra parte dell'isola."),pcharrepphrase("No. La mia nave si chiama 'Perla Nera'! Cosa è successo al tuo viso? È pallido... Ahah! Scherzo!","Grazie per il consiglio, farò sicuramente così."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Quali vele vuoi installare? Al momento hai "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "Voglio installare "+GetSailsType(6)+".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "Voglio installare "+GetSailsType(7)+".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "Voglio installare "+GetSailsType(8)+".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "Voglio installare "+GetSailsType(9)+".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "Voglio installare "+GetSailsType(10)+".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "Voglio installare "+GetSailsType(11)+".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "Ho cambiato idea.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "Al momento hai "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", hai selezionato "+GetSailsType(sti(NPChar.SailsTypeChooseIDX))+". Il costo della sostituzione è "+FindRussianMoneyString(sti(NPChar.SailsTypeMoney))+". Procedere?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Sì.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "No.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Eccellente! Tutto andrà benissimo.";
		    Link.l9 = "Grazie.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "Che colore dovremmo scegliere? Il prezzo è "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "Ho cambiato idea.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Vieni quando hai i soldi.";
			    Link.l9 = "Bene.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "D'accordo. Dipingeremo le vele in "+GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name))+" colore.";
		    Link.l9 = "Grazie.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "Sfortunatamente, la tua nave non può portare uno stemma.";
				    Link.l9 = "Peccato.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Torna quando avrai i soldi.";
			    Link.l9 = "Bene.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "Mi dispiace deludervi, Monsieur, ma al momento non ho nessuna nave in vendita.";
			link.l1 = "È veramente strano, perché mi è stato detto che avevi una nuova barca a goletta nel tuo cantiere navale.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Sai, è probabilmente riguardo al goletta, per la quale cauzione di tremila pesos da Michel de Monper? Quindi questa nave è già venduta, perché secondo il contratto, l'importo totale doveva essere pagato al più tardi una settimana dopo l'abbassamento della nave in acqua.\nTutti i periodi sono terminati, e non ho ricevuto i soldi quindi il goletta era venduto. Mi dispiace, Signore.";
				link.l1 = "Sì, è stata proprio una sfortuna, davvero... Ma sei sicuro di non avere altre navi in vendita?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Mmm. Sì, infatti. Ma...";
			link.l1 = "E c'è già un acconto su di essa - cinquemila pesos. Michel de Monper, che ha depositato i soldi, mi ha concesso tutti i diritti su questa nave.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "Le restano "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "Ebbene, se è così, allora continuiamo la nostra conversazione, Signore. Come hai giustamente sottolineato, ho ricevuto un acconto di cinquemila pesos per la nave. Ma il valore totale della nave penso sia di quindicimila pesos, munizioni incluse. Quindi pagami diecimila e la nave è tua.\nSecondo il contratto, devi pagare il denaro non oltre una settimana dopo il varo della nave."+sTemp+", e poi sono libero di vendere questa nave a un altro cliente. E, ti avviso, c'è già uno, quindi sarebbe meglio che ti sbrigassi.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "Non c'è bisogno di affrettarsi. Ho con me la somma richiesta. Ecco a te.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Bene, bene. Avrai i tuoi soldi, Monsieur. Non ti farò aspettare a lungo.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Posso aiutarla, Signore?";
				Link.l1 = "Sono solo passato a dare un'occhiata alle navi che avete disponibili... Ma al momento sono un po' occupato - ho una questione in sospeso da risolvere. Tornerò non appena avrò finito.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Signore, vi avevo avvertito che avevate solo tre giorni a disposizione. Sono scaduti, e non mi avete portato ancora nessun denaro, quindi il nostro accordo è scaduto, e ho venduto la nave a un altro cliente. Niente di personale.";
					link.l1 = "Sì, è stato davvero sfortunato, infatti... Ma sei sicuro di non avere altre navi in vendita?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "Mi avete portato diecimila, Signore?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Certo che ho. Ecco a te.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "No, sto ancora lavorando su di esso.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Allora permettimi di congratularmi con te per questo acquisto di successo. La nave è tua. Spero che ti servirà bene.";
			link.l1 = "Grazie!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Mmm... Beh, ne ho uno, in realtà, ma non sono sicuro che ti andrebbe bene.";
					link.l1 = "Bene, non posso permettermi di essere troppo schizzinoso ora. Mostrami quello che hai!";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Ascolta, signore, prima fai un mucchio e poi chiedi delle navi, va bene? Nessuno qui ti darà nulla gratis. Mi sono spiegato chiaro?";
					link.l1 = "Perfettamente chiaro, sebbene non ci fosse bisogno di essere scortesi. Va bene, tornerò una volta che avrò i soldi.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "Allora guarda. Ho recentemente acquistato a un prezzo ragionevole una sloop. Era una vecchia nave pirata, i suoi precedenti proprietari sono già stati impiccati per numerosi crimini. La nave, francamente, non è buona come un lugger e ha anche subito gravi danni, ma può ancora prendere il mare.\nNon ho tempo per ripararla ora - tutti i miei uomini sono impegnati a costruire un brigantino su ordinazione, quindi puoi comprarla da me nello stato in cui si trova. Considerando questo, la venderò più economica del solito, includendo anche il contenuto della stiva - quindicimila pesos.";
			link.l1 = "Affare fatto. È navigabile, ed è tutto ciò che conta. Guadalupa è a due passi - la farò riparare lì se non avete questa possibilità.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Allora permettimi di congratularmi con te per questo acquisto di successo. La nave è tua. Spero che ti serva bene.";
			link.l1 = "Grazie!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, pchar);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew"); */
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "Allora, Monsieur, sei tornato con i soldi?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Sì, credo di avere abbastanza per permettermi una nave fatiscente.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "Non ne ho abbastanza ancora. Sono solo passato a dare un'occhiata...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Ahi, amico mio, ma entrambi abbiamo sofferto qui. Hanno confiscato la resina, in più ho sprecato un'enorme quantità di denaro per la mia cauzione. E come diavolo hanno saputo della nostra operazione? Deve essere uno dei miei lavoratori... Me ne occuperò, Dio abbia pietà del colpevole!";
			link.l1 = "Significa che tutti i miei sforzi sono stati inutili...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "Mi dispiace molto, Capitano. Non possiamo fare nulla qui, a volte il destino è una stronza.";
			link.l1 = "Capisco. Bene, allora me ne andrò. Addio!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "Vorrei tornare a quella conversazione. Sono disposto a dare uno sconto decente... uno sconto molto considerevole per qualsiasi lavoro sulla tua nave... se mi fornisci un po' di seta in più...";
			link.l1 = "Maestro, andiamo dritti al punto. Ti prometto che non sono una spia e nemmeno uno degli uomini del Colonnello D'Oyley. Inoltre, lavoro con Marcus Tyrex, un nome che dovresti conoscere. Quindi, mettiamo le carte in tavola. So che hai bisogno di una fornitura costante di tela di seta per le vele, e Marcus Tyrex è disposto a portartela. Anche costantemente. Tuttavia, solo nel caso in cui concordiamo sul prezzo. Dobbiamo andare dritti a questo, maestro?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "Bene. Sembra che non ho scelta - o lavori per D'Oyley e mi manderai in prigione, o farò bancarotta se non trovo urgentemente una grossa spedizione di seta. Sono disposto a pagare 25 dobloni per pezzo, ma solo per grosse spedizioni, non meno di 100 rotoli.";
			link.l1 = "Allora abbiamo un accordo. Sono sicuro che Tyrex è in grado di fornirti spedizioni di 100 rotoli ogni mese.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "Sarebbe fantastico! Potrei acquistare il primo lotto subito.";
			link.l1 = "Non posso farlo adesso, ma non ci vorrà molto. Una nave con il carico di cui hai bisogno è a Capsterville al momento, sto andando lì immediatamente e te la manderò. Dove dovremmo fare lo scarico?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Organizziamolo così. Tra il 10 e il 15 di ogni mese, di notte, la mia gente aspetterà i tuoi visitatori nella baia... no, aspetta, meglio a Capo Negril. Sarà sicuramente un viaggio lungo, ma ci sono molte meno pattuglie... La parola d'ordine sarà: 'Un mercante di Lione'.";
			link.l1 = "Affare fatto, maestro. Sto andando a Capsterville subito.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "Spero che la tua nave arrivi velocemente, ho un disperato bisogno di nuova seta.";
			link.l1 = "Non preoccuparti, tutto andrà bene. Buon vento!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "No, "+pchar.name+". Non ho nulla contro di te, ma risolvi prima i tuoi problemi con il mio paese. Vendere un inventario così prezioso a un nemico della Corona potrebbe essere frainteso.";
					link.l1 = "Sì, e quando stai contrabbandando merci di origine incerta nelle navi, diventi migliori amici? Aspetta che risolva questo malinteso.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Diciamo. Perché? Stai costruendo qualcosa?";
					link.l1 = "No, sto facendo un incarico molto speciale. Per un gestore di piantagione.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "Non posso aiutarti.";
				link.l1 = "È un peccato!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "Capisco. Spero che questo manager ti abbia fornito abbastanza, perché farei pagare molto per un set come questo. Sei molto fortunato ad aver avuto un recente importazione dalla metropoli.";
			link.l1 = "Quanto?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "Mille dobloni d'oro.";
			link.l1 = "Vedo che stai surriscaldando. Sto bene. Me lo prendo.";
			link.l1.go = "IslaMona_7";
			link.l2 = "È troppo. Dubito che ci sarà un altro acquirente per l'intero set come me. Una parte sarà venduta, una parte sarà rubata dai vagabondi locali. Che ne dici di uno sconto?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Skill Check Failed (60)", SKILL_COMMERCE);
				dialog.text = "Ti garantisco che arriverà. Nessun cambiamento di prezzo. Che ne dici? Non aspetterò a lungo.";
				link.l1 = "Bene, va bene, va bene. Lo prenderò.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "Bene, ne prenderemo cento. Novecento. Non andrò più in basso. Non chiedermelo.";
				link.l1 = "E non lo farò. Sono d'accordo.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Perché non mi dai di più? Come un grossista. E poi ordinerò da te riparazioni e vernici, e la polena più succosa.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Skill Check Failed (85)", SKILL_COMMERCE);
				dialog.text = "Non mi importa se ordini una donna viva. Novecento.";
				link.l1 = "Bene, va bene, va bene. Lo prenderò.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Sei sicuro? Non dimenticherai? Va bene, tagliamo un altro centinaio. Ma è tutto qui!";
				link.l1 = "Non dimenticherò. È un affare!";
				link.l1.go = "IslaMona_7";
				link.l2 = "Beh, come posso dirlo...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Inimmaginabile! "+pchar.name+", hanno dimenticato di rimuovere il pezzo di pallettoni dal tuo cranio? Avvido come uno scorpione! Tutti abbiamo sentito parlare delle tue recenti gesta! Hai già guadagnato il tuo mucchio d'oro, quindi non impedire agli altri di guadagnare il loro. Un'altra parola e non venderò per meno di mille.";
			link.l1 = "Va bene, va bene! Calmati. Sono d'accordo.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Ma, "+npchar.name+", Ho dei bambini piccoli! Devo pensare anche a loro! Non vieni pagato abbastanza per il trasporto onesto, lo sai!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Skill Check Failed (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "I figli delle ragazze del bordello non contano, "+pchar.name+". Sono stufo di te. Mille dobloni sul barile, o ci diciamo addio.";
				link.l1 = "Cosa intendi, non lo sono? Uh-huh. Concordo, sei un truffatore.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "Non sapevo che avessi dei figli. E che le cose fossero così brutte. Va bene, non lamentarti. Settecento. È quasi una perdita.";
				link.l1 = "Non dimenticherò. Abbiamo un accordo!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "Allora, mi devi "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" dobloni.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Ecco, ti sto dando l'ultimo di ciò che ho, non mi resta più nulla.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "Aspetta, sto andando dallo strozzino per indebitarmi.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "Tutto quello che ho con me "+FindRussianDublonString(GetCharacterItem(pchar,"doppione_d'oro"))+". Prendi questo, e andrò dai strozzini.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("You gave "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
            dialog.text = "Non provare pena per me, hai un armadietto pieno d'oro nella tua cabina. Mi sarai debitore "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "Ottimo. L'intero importo è a posto. Gli attrezzi saranno consegnati alla tua nave. Queste sono alcune casse pesanti.";
			link.l1 = "Grazie, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}