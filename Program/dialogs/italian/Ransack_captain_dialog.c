// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "Cosa vuoi, capitano? Discutere del mio riscatto? Vorrei che tu sapessi che mi preoccupo del destino della ragazza...";
			link.l1 = "Parli di Katerine Rayner? Sono già informato a riguardo, "+pchar.questTemp.FalseTrace.CapName+". Lei mi ha chiesto di parlare con te.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Vedi, don Juan, la tradizione è una cosa brutta...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"Sono il tuo prigioniero, "+GetAddress_Form(NPChar)+". Ma voglio che tu sappia che "+NationNameNominative(sti(NPChar.nation))+" non paga mai per la sua gente. Siamo tutti per noi stessi.";
				link.l1 = "Beh... Vedo che non trarrò alcun profitto da te. Almeno posso riscattarti come criminale in qualsiasi colonia.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Guarda, sei un combattente abile e ho bisogno di persone come te. Vorresti servire sotto il mio comando?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"Sono il tuo prigioniero, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" pagherà un buon prezzo per la mia libertà.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Guarda, sei un abile marinaio e ho bisogno di persone come te. Vorresti servire sotto il mio comando?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Non siamo lontani da "+GetConvertStr(attrLoc+" Città","LocLables.txt")+". E potrei lasciarti andare qui.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Vai dal nostromo, digli di darti un armadietto. Puoi sbarcare nel prossimo porto.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Suppongo che farò di te un grande schiavo - forte e devoto.";
			link.l4.go = "Slave_1";
			link.l5 = "Hai ignorato l'ordine di ammainare le tue vele e hai resistito con forza. Sarai impiccato per questo. Il nostromo ha già ricevuto i miei ordini.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Lo so.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Capitano, vorresti sentire la mia proposta su una variante più redditizia del mio riscatto?","Capisco che non c'è spazio per il baratto nel mio posto ma vorresti ascoltare la mia proposta?");
						link.l1 = "Sto ascoltando.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Capitano, perché non mi lasci andare? Non ho valore per te. Se mi vendi agli schiavisti, otterrai solo poche monete e una cattiva reputazione.";
						link.l1 = "E se ti liberassi semplicemente, non otterrei nulla...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Hai ignorato l'ordine di abbassare le tue vele e hai resistito con forza. Sarai impiccato per questo. Il nostromo ha già ricevuto i miei ordini.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Sei davvero insistente quindi penso che posso darti quello che vuoi. Sei un uomo libero ora. Lascia la mia nave.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Non mettere alla prova la mia pazienza. Sei già un uomo fortunato a restare vivo.","Ho i miei piani per te.","Suppongo che tu possa ancora essere utile per me in futuro.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Capitano, questa incertezza mi sta uccidendo. Posso sapere cosa prevedi di fare con me?";
						link.l1 = "Hai qualcosa da offrirmi?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Non ho ancora idee su di te.",RandPhraseSimple("Piani? Una palla di cannone sul tuo collo? Sto scherzando, ah!","Sei il mio prigioniero e ho tutti i diritti di fare con te quello che voglio. La tua opinione non ha valore qui."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Capitano, perché non mi lasci andare? Non hai bisogno di me. Scegliere di essere un pirata era l'unica opzione per me perché non ho competenze utili o istruzione. Il mio desiderio era di fare qualche moneta e poi ritirarmi.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Guarda, sei un combattente abile e ho bisogno di tagliagole come te. Vorresti essere il mio ufficiale?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Nessuna pietà per te. Ci sono un sacco di teppisti in mare. Almeno ora ce ne sarà uno in meno a navigare.","Qualsiasi problema, 'lupo di mare'? Rimani qui e stai zitto.","La forca aspetta tutti della tua razza. Ti venderò alle autorità e sarà una grande lezione per ogni pirata.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Capitano, vi prego... Liberatemi. Ho una famiglia e dei bambini e non ce la faranno senza di me.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Guarda, sei un marinaio esperto e ho bisogno di persone come te. Vorresti servire sotto il mio comando?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("Ho i miei piani su di te.","Suppongo che tu possa ancora essere utile per me in futuro.","Sei il mio prigioniero e ho tutti i diritti di fare con te quello che voglio.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Capitano, ho perso una lotta e ti imploro pietà.","Capitano, imploro la vostra generosità. Comprendo che non c'è motivo per trattarmi come un prigioniero di guerra, quindi vi chiedo di risparmiarmi. Vi do la mia parola che eviterò di incontrarvi in mare.");
						link.l2 = LinkRandPhrase("Non mettere alla prova la mia pazienza. Sei già un uomo fortunato a restare in vita.",RandPhraseSimple("Ho i miei piani per te.","Immagino che tu possa ancora essere utile per me in futuro."),RandPhraseSimple("Sei mio prigioniero e ho tutti i diritti di fare con te quello che voglio. La tua opinione non ha valore qui.","Tu eri... beh, eri il capitano di una nave da guerra e conoscevi i rischi. Non cercare di dipingerti come un santo qui."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Guarda, sei un combattente abile e ho bisogno di te, uno spietato come te. Vorresti essere il mio ufficiale?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Non siamo lontani da "+GetConvertStr(attrLoc+" Città","LocLables.txt")+". E potrei lasciarti andare qui.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Vai dal nostromo, digli di darti un armadietto. Puoi sbarcare nel prossimo porto.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Che ti maledica! Vai dal nostromo, digli di darti un armadietto. Puoi sbarcare nel prossimo porto. E ricorda che il nostro prossimo incontro sarà l'ultimo.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Hai ignorato un ordine di ammainare le tue vele e hai resistito con forza. Sarai impiccato per questo. Il nostromo ha già ricevuto i miei ordini.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Criminale? Mi stai prendendo in giro,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "Non scherzo. Sei un pirata.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Servire sotto il tuo comando? Preferirei nutrire gli squali!";
				link.l1 = "Guarda la lingua o la darai in pasto a loro.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Essere il tuo ufficiale, "+GetAddress_Form(NPChar)+"? Sono d'accordo. Conosco il mio lavoro e non ho nulla da perdere.";
				link.l1 = "Affare fatto! Vai e fai il tuo lavoro.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Aspetta un attimo, ho cambiato idea.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("È un'offerta allettante... ma devo rifiutarla. Per principio.","Mi dispiace, ma dopo quello che hai fatto ai miei amici... È impossibile.","No, capitano. Dopo tutto questo terrore non posso più fare questo lavoro. Ho fatto un voto che se la Beata Vergine ascolterà le mie preghiere e mi concederà la libertà, non navigherò più.");
				link.l1 = "È la tua scelta. Non insisterò.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Perché no? Sono un pessimo capitano, ho perso la mia nave e non mi resta nulla sulla terraferma. Tranne bollette e debiti...";
				link.l1 = "Affare fatto! Vai dal nostromo e prendi le tue razioni. Ti darò un posto sulla mia nave un po' più tardi.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Aspetta un attimo, ho cambiato idea.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "Ma "+GetAddress_Form(NPChar)+", non puoi farlo! Mi sono arreso.";
            link.l1 = "Chiudi la bocca! ... Legatelo.";
			link.l1.go = "Slave_2";
			link.l99 = "Bene. Rimani qui finché non decido...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Assolutamente no! Preferirei uccidermi piuttosto che diventare uno schiavo!";
                link.l1 = "Fermati! È un ordine!... Nostromo! Pulisci la stiva...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Macellaio! Ragazzi unitevi a me, non abbiamo nulla da perdere!";
                        link.l1 = "Sbagliato, signore. Io gestisco le ammutinamenti da solo e in modo molto rapido...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "Assolutamente no! Preferirei morire in battaglia!";
						link.l1 = "Come desideri...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Oh, sono d'accordo. Non ho scelta.";
                    link.l1 = "Splendido. È meglio essere uno schiavo che respira piuttosto che un eroe morto.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", sei davvero così gentile, e mi stai liberando senza un riscatto?";
            link.l1 = "Sì, lo sono. Ora sei libero,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Mh... Hai un punto! Ho bisogno di più tempo per decidere.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Grazie, "+GetFullName(PChar)+"! Prego per te.";
            link.l1 = "Vai ora, e cerca di restare vivo, altrimenti la mia generosità sarà inutile.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Grazie, capitano. Non dimenticherò mai la tua gentilezza. Sto per lasciare questo lavoro e riparare piccole barche in porti tranquilli. Posso farlo.","Grazie, capitano! Lo giuro, abbandonerò questa ingratitudine di occupazione e diventerò un pescatore.");
					link.l1 = "Se stai dicendo la verità allora ti auguro buona fortuna, e se no, allora prega di non incontrarmi mai più...";	
				break;
				case "trade":
					dialog.text = "Non so nemmeno come ringraziarti, capitano. Avevo già perso la speranza. Racconterò a tutti della tua gentilezza. Ti do la mia parola che accenderò una candela per te! Basta che mi lasci arrivare in una chiesa.";
					link.l1 = "Addio. E la prossima volta nemmeno provare a resistere. Sparami e sarà una sentenza di morte per te e il tuo equipaggio.";
				break;
				case "war":
					dialog.text = "Grazie, capitano. Prego per te.";
					link.l1 = "Buona fortuna, e ricorda, se decidi di cacciarmi sarà la tua fine.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Ma "+GetAddress_Form(NPChar)+", non puoi farlo! Mi sono arreso.";
			link.l1 = "Solo dopo che i tuoi uomini se ne sono andati. Li hai traditi... Contramaestro! Prendilo.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Bene... Ho bisogno di tempo per pensarci. Rimani qui.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Macellaio! Ragazzi, non abbiamo nulla da perdere!";
                    link.l1 = "Sbagliato, signore. Io gestisco le ammutinamenti da solo e in modo molto veloce...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Assolutamente no! Preferirei morire in battaglia!";
					link.l1 = "Come desideri...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Almeno dammi del tempo per pregare...";
                link.l1 = "Prega, se vuoi.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "Ho ottenuto un'informazione interessante che può essere utile per un uomo come te. Ma ho bisogno delle tue garanzie che otterrò la mia libertà in cambio.";
			link.l1 = "Come posso darti le mie garanzie se nemmeno conosco la tua proposta? Dubito che le tue informazioni mi daranno qualcosa.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Posso solo darti la mia parola.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Bene. È sufficiente per me. Ora passiamo direttamente agli affari, in "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" vive un ricco mercante "+NPChar.Hold_GenQuest.Name+". "+"Ha fatto la sua fortuna sulla sua nave '"+NPChar.Hold_GenQuest.ShipName+" vendendo "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" con percorso : "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"Quando ha troppo carico, paga per una scorta."+sTmp+"Sono sicuro che queste informazioni valgano più per te che la vita di un singolo uomo.";
			link.l1 = "Dubito che queste informazioni possano essere utili per me. Non caccio mercanti pacifici.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Non sono sicuro che queste informazioni mi saranno utili, ma ti ho dato la mia parola. Il nostromo ti metterà con il mio equipaggio e ti lascerà andare nel porto più vicino.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Grazie, capitano! Non ho mai dubitato della tua onestà!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Vorrei poter dire lo stesso di te","Mi dispiace ma non posso dire lo stesso di te."),RandPhraseSimple("Vai e ricorda che la prossima volta non sarò così generoso.","Vai e stai fuori dalla mia strada. La prossima volta non ti crederò così facilmente."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "E ho una proposta per te. In "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" vive il mio amico, "+NPChar.Hold_GenQuest.Name+" è il suo nome. Una volta abbiamo fatto affari insieme."+"Trovalo là. Sono sicuro che ti pagherà una grande somma. Mi deve e me la vedrò con lui personalmente.";
			link.l1 = "Un tuo amico, eh? Facciamolo vedere.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Perché dovrei cercare il tuo amico se posso ottenere un riscatto nel primo porto che trovo?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Effettivamente conosco un uomo che ha un bel tesoro ma non ha il coraggio di usarlo.";
			link.l1 = "Cosa intendi?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Risparmiami le tue storie. Faresti meglio a preoccuparti della tua anima.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Ti sto raccontando la storia che porta a grandi tesori. Ho bisogno della tua parola in cambio che mi lascerai andare nel prossimo porto.";
			link.l1 = "Deciderò io quando e cosa fare con te. Le tue 'storie' non faranno la differenza.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Sto ascoltando. Hai la mia parola.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Mi fido di un tale onorevole "+GetSexPhrase("uomo","donna")+". Persone come te mantengono sempre la loro parola! Non importa se il mondo intero sta bruciando, tu manterrai la tua parola! Ho ragione, capitano?";
			link.l1 = "Raccontami la tua storia o ti lascio andare subito... oltre bordo e senza testa.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ah-ah, bello scherzo... Ora ascolta. C'è un amico in "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" nominato "+NPChar.Hold_GenQuest.Name+", era davvero un tipo spericolato nella sua gioventù. Aveva un sacco di 'affari' in quei giorni..."+"Così una volta nella taverna mi ha detto che era un membro di "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" banda e ha visto come quei pirati stavano seppellendo un tesoro."+"Ha perso cinque dei suoi compagni per quel tesoro... Si mormorava che fosse stato preso e impiccato, ma la verità è che si è ritirato dagli affari e ha fondato una famiglia. Ricordava la posizione del tesoro, aveva persino disegnato una mappa. Mi ha proposto di accompagnarlo a trovare il tesoro. È un uomo superstizioso, il tesoro era coperto di sangue, quindi teme di andarci da solo. Lo ammetto, nemmeno io ho avuto il coraggio di avventurarmi per lo stesso motivo."+"Era pronto a vendere la mappa, ma perché ne avrei bisogno se tanto non ci andrò mai...\nQuesta è la mia storia... Penso che un uomo coraggioso come te la troverà utile, e a proposito la mappa è abbastanza economica.";
			link.l1 = "E davvero mi suggerisci di comprare quello? La tua storia non è vera quindi rompo il nostro accordo.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Storia interessante, anche se non ci credo veramente. Ma hai la mia parola, vai e di al nostromo di darti un armadietto. Sei libero.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Grazie, capitano! Ora vedo il prezzo della parola di uno "+GetSexPhrase("signore!","signora!");
			link.l1 = "Vai e stai fuori dai miei piedi. La prossima volta non ti lascerò andare così facilmente.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "Ma, "+GetAddress_Form(NPChar)+", siamo in mare aperto! È come se mi avessi giustiziato!";
			link.l1 = "Questo è ciò che volevi. Addio. Il nostromo eseguirà il mio ordine.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Bene, non ho ancora deciso.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! Davvero ti ha chiesto di venire qui? Che ragazza meravigliosa...";
			link.l1 = "Restiamo lontani dalla poesia capitano, e parliamo di cose più serie. Sto per raccontarti la situazione attuale e mi aspetto una risposta da te. La tua risposta determinerà il tuo destino e quello di Katerine.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Sto ascoltando, capitano.";
			link.l1 = "Sono salito sul tuo galeone perché Adam Rayner, il marito di Katerin, mi ha detto che c'era molto argento sulla tua nave. Questo trucco gli ha permesso di riprendersi una donna che una volta era sua, e che è scappata da lui a te.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? Quel bastardo? Era tutto il suo piano! Ora capisco... Sì, ho aiutato Katrine a scappare tre mesi fa. Povera ragazza, non hai idea di come la trattasse...";
			link.l1 = "Era sua moglie e non mi importava affatto di quello che è successo, non sono affari miei. Ho commesso un errore salendo sulla tua galea, ma è troppo tardi per parlarne. Adam mi ha promesso di pagarmi per il mio aiuto.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam ha fatto una promessa? Ah-ah! E tu gli hai creduto? Capitano, sai nemmeno che tipo di persona sia? Lui...";
			link.l1 = "Katerine mi ha già detto molto su di lui e ha messo molto impegno in questo. Ma la sua proposta ha senso e anche se non ho motivo di fidarmi di questo bastardo forse questa volta dice la verità. Quindi andiamo dritti al punto...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "Stavo per riscattarti alle autorità e consegnare Adam con Katerine a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", poi ottieni da Adam le informazioni sull'oro di Squint-Eyed Solly e naviga fino ad esso. Ma Katerine mi ha convinto a parlare prima con te, ha detto che potresti offrirmi qualcosa di meglio e più affidabile di quanto ha fatto Adam, in cambio delle vostre vite e libertà.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "Ecco perché sto qui a parlarti. Ho finito. Ora è il tuo turno. Pensa alle mie parole e alle parole di Katerine, e dammi le tue idee. Non hai molto tempo.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Capitano! Anche se non penso che tu sia un buon uomo, hai ascoltato le suppliche di una povera ragazza e sei venuto qui. Mi dimostra che puoi essere onorevole e provare pietà. Non ho bisogno di tempo, sono pronta a farti la mia proposta.";
			link.l1 = "Davvero? Eccellente! Allora, sto ascoltando.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Arresterai Adam Rayner e lo metterai in catene. Poi mi porterai me e Katerine a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Non attraccare in città, dopotutto, sei stato tu a affondare il mio galeone, lascia tutti e tre noi a "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nTi chiederei anche un'arma. Andremo in città attraverso la giungla e mi assicurerò che quel fetente paghi non solo per i suoi crimini ma anche per i tuoi. Se lo merita.\nHai la mia parola che il tuo nome non verrà menzionato. In cambio, ti darò informazioni vere su una nave con l'oro del nemico.\nNon sarà una grande sfida per te ma ha i suoi denti, otterrai un bel bottino. Molto meglio del mio riscatto e dei cosiddetti tesori di Solly Strabico. Abbiamo un accordo?";
			link.l1 = "Non mi piace il tuo piano. Credo che le autorità locali organizzino una caccia per me non appena lascio le coste di "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+". No, capitano, non sto per rischiare la mia testa. La nostra conversazione è finita.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Ebbene, sembra che Katerine avesse ragione. Mi piace la tua proposta. Adam Rayner sarà arrestato. Lo farò subito. Sarai liberato dopo che arresteremo Adam. Ci vediamo, capitano!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Sei qui per predicare o per fare affari?";
			link.l1 = "Per fare affari. Ho bisogno del tuo complice - Bertrand Pinette. Sono nei guai fino al collo a causa sua. Dove posso trovarlo, eh?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Perché pensi che ti dirò questo?";
			link.l1 = "È il tuo culo sulla linea. Ti porterò a Basse-Terre, ti consegnerò al governatore e riceverò una ricompensa per aver catturato un disertore che ha organizzato la fuga di Carlos de Milyar. È la tua chiamata. O mi stai dicendo dove si trova Pinette o entrambi ci stiamo dirigendo verso Guadeloupe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Allora sai tutto... Va bene, ti dirò tutto quello che so su Bertrand Pinette ma in cambio mi libererai.";
			link.l1 = "Vai, raccontami. Ti porterò nella baia dei Mosquito, come ho fatto l'ultima volta. Ma se mi menti, tornerò e incendierò quella piantagione che don Carlos ti ha regalato, informerò anche Basse-Terre della tua posizione, quindi non sarò l'unico a darti la caccia.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Prima, portami lì. Mi farà sentire più sicuro e giuro che ti dirò tutto.";
			link.l1 = "Bene. Non è che tu stia andando da qualche parte.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
