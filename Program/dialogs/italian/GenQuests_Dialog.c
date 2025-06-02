void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Questo è un errore. Contatta gli sviluppatori e fagli sapere come e dove l'hai trovato";
					link.l1 = RandSwear()+"Farò loro sapere!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Non sono autorizzato a trattare con te. Parla con il nostro ufficiale.";
					link.l1 = LinkRandPhrase("Certo...","Capisco.","Certo!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Presentati! Voglio sapere con chi sto parlando!";
					link.l1 = "Il mio nome è "+GetFullName(PChar)+". Cosa sta succedendo qui?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Capitano, il tuo nome è "+GetFullName(PChar)+", non è vero?";
					link.l1 = "Sì, hai ragione.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "No. Mi avete scambiato per un altro.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", grazie mille! Se non fosse per te, il mio destino sarebbe invidiabile... Come posso ringraziarti?";
					link.l1 = "Non ho bisogno di niente...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Non rifiuterei una piccola ricompensa.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, è lui, davvero... Grazie, "+GetSexPhrase("compagno","ragazza")+", senza il tuo aiuto avremmo avuto molte difficoltà, non c'è modo per noi di uscire dalla città. Ecco, prendi "+FindRussianMoneyString(iMoney)+" e tu puoi perderti. E noi avremo un 'discorso' con il nostro amico...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, è proprio lui, effettivamente... Grazie, "+GetSexPhrase("compagno","ragazza")+", senza il tuo aiuto avremmo avuto un brutto momento, non c'è modo per noi di uscire dalla città. Ecco, prendi "+FindRussianMoneyString(iMoney)+" e tu puoi andartene. Ora squarciamo questo sporco traditore!";
						link.l1 = "Certo. Fino al nostro prossimo incontro, signori...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Cosa?! No, non permetterò che uccidi un uomo, non importa chi sia... E non ho bisogno dei tuoi maledetti soldi!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Allora... Cosa abbiamo qui? Pirati?! Dovrete venire con noi nell'ufficio del comandante per un'indagine...";
					link.l1 = "Non siamo affatto pirati! Non conosco nemmeno quest'uomo! Ha appena affittato e traslocato in questa stanza e non ho avuto tempo di fare le mie valigie e andare via!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Allora cosa stavi dicendo? Hai un messaggio per me?! Sto aspettando!";
					link.l1 = "Eccoti...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Ehi, tu! Sì, tu. Vedo che sei un uomo decente e ricco.";
					link.l1 = "Non posso dire lo stesso di te.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Fermati! Ehi, "+GetSexPhrase("compagno","ragazza")+", mostraci quanto pesante è la tua borsa!";
					link.l1 = "Allora, hai già sperperato tutti i soldi della chiesa?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Ehi, in barca! Hic... Lascia il passaggio - Devo parlare con i ragazzi...";
					link.l1 = "Non sei un po' stordito, amico? Vai a dormire.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Ehi, capo! Lascia cadere l'ancora!";
					link.l1 = "E perché diavolo dovrei....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Non sei un po' troppo maleducato!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Salve a te! Finalmente, il Signore ha ascoltato le nostre preghiere e ha inviato un coraggioso capitano a questa spiaggia abbandonata!","Grazie alla Provvidenza! Ora i predatori locali non si nutriranno delle nostre ossa marce!");
				link.l1 = "Ciao, buon uomo, sono il capitano "+GetFullName(PChar)+". Vedo che sei proprio nei guai qui.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Buon uomo, ho i miei affari di cui occuparmi e non ho tempo da perdere con i tuoi problemi.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("Oh, capitano! È solo una buona fortuna che Dio ti ha inviato un vento favorevole e ti ha guidato in questo luogo deserto!","Capitano! Grazie alla Provvidenza che hai deciso di gettare l'ancora su questa riva deserta!");
				link.l1 = "Ciao, buon uomo, sono il capitano "+GetFullName(pchar)+". Vedo che sei in seri guai qui.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Buon uomo, ho i miei affari di cui occuparmi e non ho tempo da sprecare per i tuoi problemi.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Aspetta, "+GetAddress_Form(pchar)+"! Ci concederesti un minuto del tuo prezioso tempo?","Sarebbe un nobile errore"+GetSexPhrase("ter","s")+" ascolta una umile richiesta di questi uomini indegni?","Nobile missione"+GetSexPhrase("ter","s")+", per favore, concedi solo un po' del tuo prezioso tempo per parlare con l'infelice.");
				link.l1 = LinkRandPhrase("Non ho tempo per questo.","Vattene, ho molto da fare senza di te.","Lasciami stare, non ho tempo per te.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Cosa vuoi?","Di cosa hai bisogno?","Qual è il problema?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Ciao, cap! Sei interessato a gingilli e merci indiani che non possono essere comprati nei negozi ordinari. O forse contanti?";
					link.l1 = "Canaglie come te di solito pretendono - non offrono nulla. Perché sei così stranamente cortese?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "La mia pistola di solito parla con i bastardi come te!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Ti sto ascoltando, capitano. Sei qui per affari?";
			link.l1 = "Sto cercando il signor "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Sono il signore "+pchar.GenQuest.Hold_GenQuest.Name+". A chi devo l'onore?","Lo avete trovato. Cosa posso fare per voi?");
			link.l1 = "Sono il capitano "+GetFullName(pchar)+", volevo parlarti riguardo a "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "E chi sarebbe?";
					link.l1 = "Aspetta... Sei "+pchar.GenQuest.Hold_GenQuest.Name+", e tu non sai di "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "Caspita! È passato un bel po' di tempo dall'ultima volta che ho sentito parlare di quella vecchia volpe? Cosa gli è successo stavolta?";
					link.l1 = "Questa volta è nei guai seri... È tenuto prigioniero, e ha bisogno del tuo aiuto.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Bene, sono tutto orecchie.";
					link.l1 = "La sua nave è stata attaccata dai pirati, ed ora è tenuto prigioniero. Mi ha consigliato di vederti riguardo al riscatto.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Sì, sono lieto di sentire parlare di un vecchio amico. Come sta andando?";
					link.l1 = "La sua situazione è così disperata che è difficile anche solo immaginare.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "Infatti, io sono "+pchar.GenQuest.Hold_GenQuest.Name+"! Ma perché dovrei sapere qualcosa a riguardo "+pchar.GenQuest.Hold_GenQuest.CapName+"?!";
			dialog.text = "Esatto, io sono "+pchar.GenQuest.Hold_GenQuest.Name+"! Ma nome "+pchar.GenQuest.Hold_GenQuest.CapName+" non mi dice nulla."; // belamour gen
			link.l1 = "Mi dispiace. Forse mi sono sbagliato...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Wow! E come dovrei aiutarlo? Liberandolo uccidendo tutti i suoi nemici o cosa? Ah-ah-ah!";
			link.l1 = "No-no, non è necessario. Devi solo consegnare "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos come riscatto.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Che impudenza! E perché dovrei pagare il riscatto per lui?! Non è né un mio parente né un amico!";
			link.l1 = "Mmm... Mi ha detto che tu eri la sua unica speranza. E ha anche menzionato qualche tuo debito...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Che tipo arrogante! È lui che mi deve dei soldi, per tua informazione! Ma questo non è un motivo per cui dovrei riscattarlo sperando che saldi entrambi i debiti.","Che canaglia! Mi ha fregato quando stavamo dividendo i nostri affari, e ora ha il coraggio di chiedermi di pagare il riscatto per lui!","Ecco una sorpresa! Perché dovrei pagare il riscatto per lui?! Non siamo così intimi.");
			link.l1 = "Allora, posso dirgli che hai rifiutato di pagare il suo riscatto e non hai riconosciuto il tuo debito?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "Oh mio! Di quale debito stai parlando? Ho già spiegato tutto! E se non hai altre domande oltre a questa sciocca storia, allora permettimi di prendere congedo.";
			link.l1 = "Capisco. Beh, non ho più domande per te, ma ne ho parecchie per quel tuo compagno.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Mmm... E tu, come capisco, sei quello che lo tiene... Beh, suppongo che lo aiuterò.";
			link.l1 = "Molto bene. Il riscatto sarà "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Mi hai frainteso: sono un membro del consiglio cittadino. Vegliamo sul rispetto dello statuto.\n"+"Guardie!!! Guardie! Arrestatelo con l'accusa di tratta di schiavi e di saccheggio di navi di "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "Ebbene, 'amico', lascia solo che ti raggiunga...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Cosa stai dicendo?! E come posso aiutarlo?";
			link.l1 = "Lui è tenuto prigioniero e mi ha chiesto di parlarti riguardo al suo riscatto.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Certo, certo. Farò tutto il possibile. Dove li tengono? E qual è l'ammontare del riscatto?";
			link.l1 = "I pirati esigono "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos. Devo consegnare i soldi al porto, e poi il tuo amico sarà liberato.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Ecco i soldi. Fortunatamente, ne avevo abbastanza con me.";
			link.l1 = "Sì, è davvero fortunato. Vai al porto, allora, e presto rivedrai il tuo compagno.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Salve, capitano, mi dispiace che non ho avuto l'onore di essere presentato. Hanno detto che mi stavi cercando.";
			link.l1 = "Infatti, se tu sei il signore "+pchar.GenQuest.Hold_GenQuest.Name+". Sono il capitano "+GetFullName(pchar)+", volevo parlare con te.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "E che tipo di affari è, capitano "+GetFullName(pchar)+"?";
			link.l1 = "Sentito dire che possiedi qualcosa di cui non ti dispiacerebbe separarti.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Cosa stai insinuando?";
			link.l1 = "Non essere così ostinato, mio buon uomo, conosco molto bene il tuo passato oscuro e una mappa improvvisata, sulla quale è indicata la posizione del tesoro"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" è indicato.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Maledizione! Ho sempre saputo che quel furfante"+pchar.GenQuest.Hold_GenQuest.CapName+" avrebbe sparato questa fuori prima o poi! Cosa stavo pensando quando gli ho offerto questo affare?";
			link.l1 = "Smetti di lamentarti. Non voglio farti del male... Basta vendere questa mappa a me e vivere la vita a cui sei abituato.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Se solo potessi esserne così sicuro... E quanto mi offrirai per questo? Devi sapere che c'era molto oro in quel forziere. Era portato da quattro uomini, che il Signore li abbia in gloria...";
			link.l1 = "Ma "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" avrebbe già potuto reclamare il suo tesoro...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Vero pure... Va bene, sono disposto a vendertelo per "+pchar.GenQuest.Hold_GenQuest.Sum+" pesos. Non oserò comunque disturbare i morti.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Bene. Hai concluso un affare.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "No, mio buon uomo, quel pezzetto di carta non vale questi soldi. Addio...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Come può essere possibile, capitano?! Dio non perdonerà mai un tale peccato.";
			link.l1 = "È a Lui decidere.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Ciao, sono "+pchar.GenQuest.ShipWreck.Name+", capitano del "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+", la mia nave si è schiantata sugli scogli non lontano dalla costa."+"Solo pochi marinai di tutto l'equipaggio sono riusciti a sopravvivere. La marea ci ha spinto su questa desolata spiaggia. Siamo stati affamati e assetati per "+(5+hrand(7))+" settimane ormai","Ciao, sono "+pchar.GenQuest.ShipWreck.Name+", capitano del "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". La nostra nave si è schiantata non lontano da qui."+"Siamo riusciti a raggiungere questa riva sui relitti, ma questo posto sembra disabitato. Siamo stati costretti a sopravvivere con frutti di mare e palme per "+(5+hrand(7))+" settimane ormai.");
				link.l1 = RandPhraseSimple("E quanti di voi sono rimasti?","E quanti di voi sono riusciti a sopravvivere?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "Oh, capitano, le nostre perdite sono davvero terribili... Ciao, io sono "+pchar.GenQuest.ShipWreck.Name+", capitano e proprietario del "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". O, dovrei dire, ex capitano e proprietario. "+"Questo bastardo "+pchar.GenQuest.ShipWreck.BadName+" chi ho assunto in "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" aveva provocato la mia ciurma a ammutinarsi. Alla fine, siamo approdati in questo luogo perduto. È successo "+(5+hrand(7))+" settimane fa.";
				link.l1 = "E poi che cosa? L'intero equipaggio si è unito ai ribelli?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("Dall'intero equipaggio, solo "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("Sì, è un destino invidiabile. Ma questa è la sorte del marinaio - chiunque potrebbe finire al tuo posto.","Capisco... Dio tiene ogni vita, è solo che è troppo occupato per ricordarsi di tutti.","Certo. L'uomo propone, ma Dio dispone.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Certo che no! Coloro che hanno rifiutato di unirsi ai ammutinati erano molti, ma questi malviventi hanno catturato l'arsenale, ed è bene che non abbiamo opposto resistenza, altrimenti saremmo stati uccisi sul posto. Molti qui sono già caduti a causa della febbre e del veleno degli insetti velenosi, solo "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" sopravvissuto. Grazie a Dio, le nostre prove sono finalmente terminate.";
			link.l1 = RandPhraseSimple("Sì, quella è stata sicuramente una sfortuna.","Beh, molte cose strane possono succedere in questi luoghi dimenticati da Dio.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Aspetta, amico. E come dovrei sapere che non sei stato messo a terra come l'istigatore di una rivolta?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Capitano, spero davvero che tu abbia diversi armadietti liberi sulla tua nave. Tutti noi abbiamo famiglie, e probabilmente stanno piangendo la nostra perdita mentre stiamo parlando. Ti saremmo molto grati.","Capitano, siamo completamente disperati, sei la nostra unica speranza. Per favore, non negarci il tuo aiuto, portaci via da questa terra dimenticata da Dio.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... e dove vorresti che ti portassi?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Mi dispiace davvero, ma non c'è nemmeno un'amaca libera, per non parlare delle cabine. I marinai dormono sul ponte, non possono nemmeno riposare bene dopo un turno di guardia...","Mi dispiacerebbe davvero deludervi, ma la nave è sovraccarica e la gente deve dormire con il brutto tempo. Se dovesse scoppiare una malattia, perderei metà dell'equipaggio."),RandPhraseSimple("Mi dispiace davvero, ma non c'è assolutamente più spazio per l'equipaggio sulla mia nave. Non posso prendere a bordo altri passeggeri.","Devo deluderti, ma la mia nave è sovraccarica. Temo l'epidemia."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Sei un marinaio esperto e dovresti sapere che la presenza di qualcuno che ha subito un naufragio è un segno molto cattivo. I miei marinai ti getteranno semplicemente per bordo.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Cosa stai dicendo, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! Abbiate un cuore! Sono un negoziante, conosciuto in tutto i Caraibi! Beh... credo di essere stato uno. Non ora, senza una nave o soldi...";
			link.l1 = "Come mai... Scommetto che siete stati voi i veri istigatori della rivolta, e ora avete ottenuto ciò che meritavate.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Ma che mascalzone è quello "+pchar.GenQuest.ShipWreck.BadName+"! Davvero lascerai che se la cavi così e ti rassegnerai al tuo destino?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "A qualsiasi insediamento di "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Bene, ho abbastanza armadietti liberi e amache. Caricati sulla barca.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Abbiamo battaglie davanti a noi, e non so dove sarai più al sicuro, a bordo della mia nave o in questa accogliente baia.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "A Dunkerque! Mia madre vive lì...";
					link.l1 = "Sei pazzo o cosa?! Capisco che hai preso troppi colpi alla testa...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Dove vuoi, non importa davvero a noi. Comunque non abbiamo nulla per pagarti...";
				link.l1 = "Beh, ho abbastanza armadietti liberi e amache. Caricati sulla barca.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Abbiamo battaglie davanti a noi, e non so dove sarai più al sicuro, a bordo della mia nave o in questa accogliente baia.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Ma rifiutando ci condanni certamente alla morte! Beh, proveremo a farci strada verso la nave, anche se ci costerà la vita!";
					link.l1 = "Cosa? Guardatevi, a malapena riuscite a stare in piedi...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Potresti provare...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Ma non puoi semplicemente lasciarci qui! Senza il tuo aiuto tutti noi periremo presto!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "L'unica cosa che posso fare per te è lasciarti abbastanza provviste e medicine e darti una barca. Almeno non morirai di fame e di sete. Per quanto riguarda la navigazione, non ho bisogno di insegnarti.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "L'unica cosa che posso fare per te è lasciarti abbastanza provviste e medicine e darti una barca. Almeno non morirai di fame e sete. Per quanto riguarda la navigazione, non ho bisogno di insegnartela.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Posso lasciarti abbastanza medicine, munizioni, rum e provviste per un mese. Tornerò io stesso o manderò qualcuno a cercarti.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "Ma rifiutando ci condannerai sicuramente a morte! Beh, tenteremo di aprirci un varco verso la nave, anche se ci costerà la vita!";
						link.l1 = "Cosa? Guardatevi, a malapena riuscite a stare in piedi...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Potresti provare...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "Ma rifiutando ci condannerai sicuramente a morte! Bene, cercheremo di aprirci la strada verso la nave, anche se ci costa la vita!";
							link.l1 = "Cosa? Guardatevi, a malapena riuscite a stare in piedi...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Potresti provare...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Come hai potuto farci questo?!.. Non solo hai ignorato il Codice del Mare, ma hai anche macchiato il tuo onore!";
							link.l1 = "Certo che non sei tu quello di parlare del mio onore, gamberetto!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "L'unica cosa che posso fare per te è lasciarti abbastanza provviste e medicinali e darti una barca. Almeno non morirai di fame e sete. Per quanto riguarda la navigazione, non ho bisogno di insegnartela.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Hai ragione, non abbiamo speranza. Va bene, che Dio sia il tuo giudice, e che a ciascuno sia dato ciò che gli è dovuto.";
			link.l1 = "Bene, posso occuparmene...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Ebbene... Non ci lasci altra scelta... Pregheremo che le tempeste e la sete non ci tolgano la vita prima di raggiungere luoghi abitati...";
			link.l1 = "Addio. Che il Signore vegli su di te...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Sembra che non abbiamo scelta... Ma ti prego capitano, torna appena possibile o mandaci una nave da spedizione.";
			link.l1 = "Penserò a qualcosa. Aspetta solo.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Capitano, per favore ricorda che sei la nostra unica speranza...","Perché stai indugiando? Ogni minuto trascorso qui è insopportabile per noi...");
			link.l1 = "Fare tutto il possibile. Addio...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Addio, capitano... Dobbiamo prepararci per il viaggio.","Addio... E accendete le candele per salvare le nostre anime...");
			link.l1 = "Addio. Che il Signore vegli su di te...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Come hai potuto farci questo?! Non hai solo ignorato il Codice del Mare, hai anche macchiato il tuo onore!";
			link.l1 = "Certo che non sei tu quello a parlare del mio onore, gamberetto!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Grazie, capitano! Il carico non dovrebbe richiedere troppo tempo. Dio, come abbiamo pregato per l'arrivo di questo momento!";
			link.l1 = "Questo è fantastico. Spero che le tue prove finiranno presto.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Grazie, capitano! Il carico non dovrebbe richiedere troppo tempo. Dio, come abbiamo pregato perché arrivasse quel momento!";
			link.l1 = "È fantastico. Spero che le tue prove finiranno presto.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Avanti! Davvero, capitano?! Abbiamo paura della morte?! L'abbiamo ingannata una volta, possiamo farlo di nuovo. Semplicemente non vogliamo perdere le nostre vite così. Marcire qui, soli\nCi uniremmo volentieri al tuo equipaggio e combatteremmo coraggiosamente sotto la tua bandiera. Semplicemente non ci lasciare qui...";
			link.l1 = "Vedo che siete pronti a fare qualsiasi cosa pur di uscire da qui. Ma guardatevi, che tipo di marinai potreste essere?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "È una buona idea. Suppongo, posso assumerti.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "No-no, non sto scherzando! Per favore, portami via da questo mattatoio dei Caraibi... fuori da questo inferno! Sai, sono un uomo ricco... un uomo molto ricco. Nemmeno un Papa avrebbe visto così tanto oro in tutta la sua vita. Ti coprirò d'oro...";
			link.l1 = "Oh mio... Va bene, sali sulla barca...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Perché indugi, capitano? Ordina di salpare.","Ci dispiace, capitano, ma dobbiamo prepararci per salpare.","Siamo così fortunati che hai deciso di venire qui!");
			link.l1 = "Sbrigati. La nave non aspetterà nessuno.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Capitano, non abbiamo nulla da perdere. La morte ci segue già a ogni passo... Preferiremmo morire in un combattimento leale piuttosto che essere divorati da coyotes puzzolenti...";
			link.l1 = "Oh, è una sfida, allora?! Va bene, risolviamo le nostre dispute"+GetSexPhrase(", come uomini","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Lo giuro, capitano, non te ne pentirai. Saremo i migliori marinai in tutto l'arcipelago.";
			link.l1 = "Ottimo! Salta sulla barca...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Lo giuro, capitano, non te ne pentirai.","Hai fatto la scelta giusta, capitano.","Capitano, siate certi che siete stati fortunati quanto noi!");
			link.l1 = RandPhraseSimple("Spero proprio di sì.","Sbrigati. La nave non aspetterà nessuno.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Capitano, perché offendere la gente onesta con tanta sfiducia? Guarda le loro facce, pensi davvero che potrebbero essere ammutinati?";
			link.l1 = "Bene, ma cosa dovrei fare con te adesso?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "E cosa posso fare? Almeno ora, sono vivo... e ringrazio Dio che ce l'ho fatta a uscire! Ma se mi aiuti a recuperare la mia nave e a vendicarmi per la mia umiliazione, sono disposto a darti tutto ciò che questo mascalzone avrà rubato e nascosto nella stiva.";
			link.l1 = "Bene, abbiamo un accordo.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Non siamo in posizione di dare ordini. Sta a te, ci porti solo in qualsiasi insediamento o ci accetti nella tua ciurma.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Bene, ti prenderò nel mio equipaggio. Ma niente scherzi! Ho una disciplina rigorosa sulla mia nave!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Non ti porterò da nessuna parte. Ho già abbastanza teppisti nel mio equipaggio.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Bene, sali sulla barca, ti porterò da qualche parte.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "Vabbè... Non ci lasci scelta... Pregheremo che la Provvidenza mostri pietà per noi e ci permetta di uscire da questo luogo pericoloso. Se Dio vorrà, potremmo ancora raggiungere la terra abitata...";
			link.l1 = "Addio. Possa il Signore vegliare su di te...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Grazie mille, capitano "+GetFullName(pchar)+"! Hai fatto tanto per noi che nessuna gratitudine potrebbe essere sufficiente per ripagarti. E mentre tutti i nostri averi non valgono un rame, permettimi di presentarti questo amuleto. Sarebbe molto utile per un capitano che è spesso impegnato in battaglie navali.";
				link.l1 = "Grazie per il tuo dono! Questo gingillo è molto utile, davvero! Addio, capitano "+pchar.GenQuest.ShipWreck.Name+" e buona fortuna nei tuoi viaggi.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Capitano, grazie mille. Hai fatto molto per noi, e qualsiasi ricompensa sarebbe inferiore rispetto alla nostra gratitudine. Per favore, accetta questo modesto dono come segno del nostro ringraziamento.";
				link.l1 = "Davvero, non avresti dovuto disturbarti... Hai molto più bisogno di denaro di me. Comunque, è molto gentile da parte tua. Grazie, e arrivederci.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Capitano, sappi che ci sono persone che andrebbero fino alla fine del mondo per te, d'ora in poi. È un peccato che non ho nulla con cui ringraziarti. Ancora... Per favore, accetta questo gingillo, l'ho trovato in quella cala maledetta. Spero ti porti fortuna.";
			link.l1 = "Chiunque avrebbe fatto lo stesso al mio posto. Addio.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitano, siamo già a Dunkerque?","Siamo davvero a Dunkerque, capitano?"),RandPhraseSimple("Capitano, è l'Europa?","Abbiamo navigato verso l'Europa così velocemente?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Non ancora...","Che Dunkirk? Che Europa? Guardati attorno!","Oh mio Dio!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Ma, capitano, hai fatto una promessa!","Come potresti aver infranto la tua parola, capitano?","E quando arriviamo in Europa?");
			if(rand(100) < 70)
			{
				link.l1 = "Bene. Signore, raduna i tuoi uomini e i tuoi averi e vai dove preferisci.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Sei sicuro che dobbiamo davvero andare a Dunkerque?","Sai, la mia nave non è fatta per navigare attraverso l'oceano.","Capitano, e cosa c'è che non va nei Caraibi?"),LinkRandPhrase("Ma avevo piani diversi...","Perché vuoi andare in Europa in primo luogo...","Pensa solo a tutte quelle seducenti donne mulatte! Non le incontrerai mai in Europa..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Ma come?.. Come osi?! Che tipo di tradimento è questo?! Ti insegnerò a mantenere la parola!";
			link.l1 = "Ebbene, l'hai chiesto tu...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("No! Devo arrivare a Dunkerque!","Invece di insegnarmi geografia dovresti piuttosto adempiere al tuo dovere!"),RandPhraseSimple("Non voglio sentire nulla al riguardo! Mi hai promesso di portarmi in Europa!","No, capitano, non va bene. Stiamo navigando verso l'Europa."),"Non intendo condurre una vita misera per il resto dei miei giorni in questo buco!");
			link.l1 = "Oh, non so se questo finirà mai...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Guarda! Questo è un uomo decente! Europa! Maledetta vecchia Europa! Sì-sì-sì!\nOh, sì! Hai mantenuto la tua parte del patto e così farò io. Prendi questa metà della mappa. L'altra metà era di mio partner. Riposa in pace, o riposa in acqua? Comunque. Era lui che mi ha convinto a partecipare a questa avventura.";
			link.l1 = "Aspetta, quindi non sei un marinaio? Il tuo compagno era un capitano?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "Oh mio!.. Naturalmente, no! Beh, sì, non sono un marinaio. Ed è stato spazzato via da un'onda enorme, quando ha deciso di navigare più lontano dalla costa. Poi ho assunto il comando e ordinato di navigare nella baia... E ci siamo comportati bene facendo strada attraverso gli scogli, fino a quando tutto è stato deciso da un incidente fatale. La nave ha colpito un frammento di roccia ed è affondata...";
			link.l1 = "Ecco una vera dimostrazione di incompetenza...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Ascolta, è davvero Dunkerque? Ci pensa, sono passati solo sei mesi e tutto il posto è cambiato\nPrendi la mappa, o la sua parte, per essere più precisi. Il tesoro è dentro una grotta! Non ho idea di quale sia l'isola, ma tu sei un marinaio esperto, un giorno troverai la posizione esatta... Ti garantisco che ci sono innumerevoli ricchezze del pirata chiamato aaarrrrrhg...";
			link.l1 = "Grazie, buon uomo. Anche se non c'è affatto tesoro, non sarò troppo contrariato. Addio, e spero davvero che non ci vedremo mai più...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Capitano, è fantastico che non ci hai dimenticati! Tutti noi abbiamo pregato per te!","Capitano, è vicina la nostra salvezza? Come abbiamo pregato affinché arrivasse! Alcune persone hanno già iniziato a disperare...");
			link.l1 = "Saluti, "+pchar.GenQuest.ShipWreck.Name+"! Come potrei lasciare i miei colleghi in uno stato simile? Dove andare?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Saluti, "+pchar.GenQuest.ShipWreck.Name+"! Tema che ho brutte notizie per te. C'è stato un cambiamento di piani e non sarò in grado di portarti a bordo.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Non ci importa dove andare, purché sia abbastanza lontano da questo maledetto posto... Ci permetteresti di iniziare a imbarcarci?";
			link.l1 = "Sì, vai avanti con quello. Presto i tuoi problemi saranno finiti.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Grazie, capitano. Avevamo già cominciato a disperarci, ma tu ci hai letteralmente riportato in vita.";
			link.l1 = "Non era niente... Addio.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Cosa diavolo vuoi da me?";
			link.l1 = "Sono arrivato"+GetSexPhrase("","")+" per inviarti saluti da una persona chiamata"+pchar.GenQuest.ShipWreck.Name+". Lo conosci?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Peccato che non ho strozzato quel mascalzone prima. Beh, allora, suppongo, è giunto il momento di pagare per la mia benevolenza...";
			link.l1 = "Certo... E il tempo è appena scaduto...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Ottimo lavoro, capitano! Tutto come abbiamo concordato, allora? Noi otteniamo la nave e tu ottieni il carico?";
			link.l1 = "Certo. Prendi la nave e falle buon uso.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Ti saluto, capitano "+GetFullName(pchar)+".";
			link.l1 = "Allora, come ti piace la tua nave?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Eh, sta stridendo e cigolando, proprio come me. Penso che entrambi non abbiamo molto tempo per navigare i mari aperti...";
			link.l1 = "Buona fortuna, allora...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Capitano, per favore aiutaci a trovare una nave o una barca lunga, un tartan, qualsiasi cosa, non importa davvero. Siamo in tali circostanze che dobbiamo fuggire da questo luogo inospitale, ma non possiamo apparire nel insediamento.";
					link.l1 = "E quali sarebbero queste circostanze?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Capitano, potresti prestarci un paio di centinaia di pesos? Non te lo chiederemmo, ma siamo veramente in grave necessità.";
					link.l1 = "In grave bisogno, dici? Scommetto che hai solo finito il rum e questo è sicuramente un grave bisogno.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Capitano, potresti essere così gentile da portare la nostra umile compagnia al faro di "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "Guardandoti, non direi che sei troppo umile.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Non do elemosine il venerdì.","Non ho tempo per queste sciocchezze.","Non aiuto persone strane.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Siamo fuggitivi... da "+GetStrSmallRegister(XI_ConvertString("TipoMiniera"+pchar.GenQuest.Convict.MineType+"Quello"))+". Presto l'ex padrone se ne accorgerà... e allora siamo sicuramente morti.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Allora sai come gestire le vele?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "E con cosa intendi pagare?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "Non è il momento giusto per pensare al rum. È passata una settimana da quando siamo scappati, ora ci nascondiamo nelle giungle e stiamo morendo di fame.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Beh, supponiamo, posso darti dei soldi... e poi? Continuerai a nasconderti, fino a quando alla fine verrai scoperto da una pattuglia?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Bene, di quanto hai bisogno?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Parlo brevemente con te, teste sul block del boia, e basta!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "E cosa altro possiamo fare? Saremmo lieti di trovare lavoro come marinai, ma considerando che siamo fuggitivi, chi ci assumerà?";
				link.l1 = "Ti assumerò se sai come gestire le vele e non mostrerai segni di codardia.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Abbiamo già raggiunto un accordo con i marinai locali. Per partire da qui, ci mancano solo tre mila.";
				link.l1 = "Ecco, qui ci sono i tuoi tre mila, se davvero ti aiuteranno.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Beh, non lo so... Sono i tuoi problemi, e non ho intenzione di aiutarti a risolverli.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Per favore, capitano, assumici, sicuramente non te ne pentirai! Abbiamo fatto i pirati con "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" nelle Adriatiche, finché finalmente fu impiccato e noi, "+pchar.GenQuest.Convict.ConvictQty+" uomini, siamo stati esiliati in questo luogo.";
			link.l1 = "Bene. C'è un posto qui vicino, noto come "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Verso mezzanotte passerò a prenderti. Spero davvero che non ti perderai.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Certo, ci aiuterà molto! Prenderemo il largo oggi, se il vento è favorevole e i pescatori non ci deludono. Grazie, capitano, e che Dio ti assista...";
				link.l1 = "Buona fortuna anche a te.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Ecco un colpo di fortuna! Non speravamo nemmeno di ottenere i soldi così rapidamente. Capitano, permettimi di presentarti un gingillo che abbiamo preso dal nostro ex capo. Forse, porterà anche a te buona fortuna.";
				link.l1 = "Grazie, è sicuramente una cosa decente. Buona fortuna a te.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Ecco un uomo generoso che non teme di spendere moneta, perché sa come guadagnarla!\nLa scorsa notte abbiamo visto i contrabbandieri locali che caricavano "+MerPrm.QuestGoodsIdx+". Era buio, ma siamo riusciti a distinguere il nome della nave sul fianco di una delle barche, '"+MerPrm.ShipName+"'... e quella nave naviga sotto la bandiera di "+MerPrm.nation+". Forse, troveresti queste informazioni utili, he-he.";			
				link.l1 = "Mmm... Beh, forse lo farò. Addio a voi, cercatori.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "Oh mamma mia, non siamo nella posizione di fare richieste. Qualunque cosa tu possa risparmiare, saremo grati per qualsiasi cosa.";
			link.l1 = "300 pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Grazie, capitano, e che Dio ti protegga...";
			link.l1 = "Buona fortuna a te, anche.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "Ecco un colpo di fortuna! Non potevamo nemmeno sperare di ottenere i soldi così rapidamente. Capitano, permettimi di presentarti un cimelio che abbiamo preso dal nostro ex capo. Forse, porterà anche a te buona fortuna.";
				link.l1 = "Grazie, è sicuramente una cosa decente. Buona fortuna a te.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Grazie, capitano, e che Dio vegli su di te...";
				link.l1 = "Buona fortuna anche a te.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Ecco un colpo di fortuna! Non speravamo nemmeno di ottenere i soldi così in fretta. Capitano, permettimi di proporti un gingillo che abbiamo preso dal nostro ex capo. Forse, porterà anche a te buona fortuna.";
				link.l1 = "Grazie, è un gesto nobile, di sicuro. Buona fortuna a te.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Ecco un uomo generoso che non ha paura di spendere, perché sa come guadagnarlo!\nIeri sera abbiamo visto i contrabbandieri locali a caricare "+MerPrm.QuestGoodsIdx+". Era buio, ma siamo riusciti a discernere il nome della nave sul fianco di una delle barche '"+MerPrm.ShipName+"'... e quella nave naviga sotto la bandiera di "+MerPrm.nation+". Forse, troveresti queste informazioni utili, he-he.";
				link.l1 = "Mmm... Beh, forse lo farò. Addio a voi, ricercatori.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Non portarci sventura, capitano! Abbiamo un gingillo decente, per favore, accettalo come riscatto e lasciaci andare...";
				link.l1 = "Consegnalo, poi, e sparisci, mentre puoi ancora farlo.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Ora non abbiamo altra scelta, un uomo non morirà due volte. Alla battaglia finale, ragazzi!";
				link.l1 = "Ecco una storia diversa!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Ebbene, certo non siamo santi, ma non stiamo cercando una rissa per nulla... Siamo fuggitivi, e dobbiamo andarcene da qui il più presto possibile.";
			link.l1 = "Hai qualcosa per pagare il passaggio?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "Oh, capisco... No, non macchierò la mia reputazione per causa tua. Addio.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Certo! Siamo abbastanza abituati alle imbarchi e roba del genere. Per quasi due anni noi e il defunto "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" terrorizzavano i mercanti locali, ma ahimè! Fu impiccato, e "+pchar.GenQuest.Convict.ConvictQty+" uomini di noi sono stati condannati alla servitù penale.";
			link.l1 = "Che ne dici di unirti al mio equipaggio? Sono generoso"+GetSexPhrase("","")+", ma non ti prometto una vita tranquilla.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Sì, abbiamo preso qualcosa con "+GetStrSmallRegister(XI_ConvertString("TipoMiniera"+pchar.GenQuest.Convict.MineType+"Gen"))+", quindi possiamo pagare il doppio. QUINDI confido che il prezzo sia concordato. E non osare portare le guardie. Non perdoniamo il tradimento..."; // belamour gen
			link.l1 = "Bene, aspettami sulla spiaggia "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". Verso la mezzanotte ci sarà una barca per te ... E non voglio vedere nessun trucco!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "No, amici miei. E se vi do la nave e voi mi pugnalate alle spalle? No, non vi aiuterò in questa faccenda.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Con grande piacere, "+GetSexPhrase("signore","mancato")+"capitano. Siamo abbastanza familiari con quello, e sicuramente non saremo ammessi in Marina con tali raccomandazioni comunque, eh-eh.";
			link.l1 = "Bene. C'è un posto nelle vicinanze, noto come "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Dopo la mezzanotte verrò a prenderti lì. Spero davvero che non ti perderai.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Ma, "+GetSexPhrase("signore","mancato")+"capitano, stiamo correndo un rischio ancora maggiore? E se decidessi di consegnarci al comandante?";
			link.l1 = "È vero... Va bene, se non arrivo all'alba, allora l'affare è annullato.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "Oh, capitano, contavamo su di te...";
				link.l1 = "Non è un problema. Se hai soldi, troverai passaggio. Addio.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Sei un astuto, capitano, come posso vedere. Sono sicuro che correrai direttamente dal comandante, non è vero? E pensi di farla franca?";
				link.l1 = "E stai pianificando di fermarmi, come posso vedere?! Allora avrai ciò che meriti!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "C'è qualcosa. Abbiamo rovistato nei forzieri del nostro capo, ma poi c'è stata una confusione per questo, e abbiamo dovuto farci strada con una lotta. Solo "+PChar.GenQuest.Convict.ConvictQty+" uomini sono riusciti a sopravvivere.";
			link.l1 = "Considerando le circostanze, non ti concederò un passaggio più economico di "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" pesos a persona.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Vedo che non siete codardi. Vi unireste al mio equipaggio?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "E abbiamo una scelta? Va bene, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "Allora vai a "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+". Manderò una barca per te dopo la mezzanotte."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "E perché no? Sappiamo come funziona, abbiamo fatto i pirati con "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" in "+RandPhraseSimple("Gibilterra","Canale della Manica")+" prima che rimanessimo bloccati qui.";
			link.l1 = "Bene. C'è un posto qui vicino, conosciuto come "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". Verso la mezzanotte passerò a prenderti lì. Spero davvero che non ti perderai.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, capitano, anche tu una volta eri povero, avevi le tasche vuote. E ora disprezzi la gente semplice come noi."),RandPhraseSimple("Eh, la gente sta davvero diventando troppo egoista in questi giorni. Vivi come se avessi ancora due secoli davanti a te.","Oh, vedo che sei appena arrivato dall'Europa, non hai ancora fiutato la puzza del nostro discarico tropicale."));
			link.l1 = LinkRandPhrase("Stai cercando di mettermi in imbarazzo? Ti accorcerò la lingua di un paio di centimetri!","Mi stai intimidendo? Tieniti forte al cappello ora!","Sei un filosofo o cosa? Ti picchierò fino a farti tornare il senso della realtà!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Allora, capitano? Hai portato una nave per noi?","Saluti, capitano. Allora, cosa ne pensi del nostro accordo?","Ciao, capitano. Abbiamo già iniziato a preoccuparci. Immagino che tutto sia andato bene?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Sì, ecco la tua tinozza. E non dimenticare del pagamento. Ho pagato "+pchar.GenQuest.Convict.ShipPrice+" monete per questo, quindi mi devi "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", proprio come abbiamo concordato.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "No, ho cambiato idea. Trovati un altro aiutante. Addio...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Ma certo! Hanno preso la nostra libertà, ma non la nostra coscienza! Per favore, accetta i tuoi soldi insieme alla nostra infinita gratitudine. Ci hai davvero aiutato. Ti dispiace se ti paghiamo in lingotti d'argento?";
					link.l1 = "Certo che no. Buona fortuna nel tuo viaggio. E prega che non ti incontri in mare aperto, farò di te un boccone.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Capitano, sai, abbiamo pensato che il denaro in realtà non è così importante nella vita. E, francamente, ne abbiamo molto più bisogno di te in questo momento. Ma abbiamo una cosa che abbiamo rubato al nostro ex capo. Forse ti interesserebbe molto più dell'oro. Vuoi dare un'occhiata?...";
					link.l1 = "Sì, hai ragione. Questa è davvero una cosa meravigliosa. Va bene, abbiamo un accordo, grazie e addio.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Perché diavolo avresti bisogno di così tanti soldi, capitano? Sei già ricco, e noi siamo spacciati se non prendiamo questa nave. Quindi... semplicemente te la prenderemo. Niente di personale.";
					link.l1 = "Questo è stato il tuo ultimo errore. Senza una nave potresti ancora nuotare via, ma ora o galleggerai o affonderai.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Allora, capitano? Possiamo iniziare a caricarci?","Finalmente! Abbiamo già iniziato a preoccuparci, pensavamo che avessi cambiato idea.");
			link.l1 = "Mi dispiace, ho cambiato i miei piani. Dovrai cercare un altro capitano adesso.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Salite sulla barca, non ho molto tempo.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Salite sulla barca, non ho molto tempo.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Maledetto! Sicuramente hai già mandato una pattuglia dietro di noi?! Non te la caverai così facilmente!";
				link.l1 = "Di cosa stai parlando?! Vuoi morire o cosa?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Capitano "+GetSexPhrase(", sei un uomo di parola o no?","?")+"O sei solo un maledetto chiacchierone...";
				link.l1 = "È meglio che tu stia attento a come parli...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("Oh, grazie, "+GetSexPhrase("uomo gentile","bella ragazza")+".","Grazie, capitano, mi hai davvero salvato dal cappio.","Apprezzo molto un viaggio così bello.");
			link.l1 = LinkRandPhrase("Va tutto bene, ma sto aspettando i soldi.","È ora di pagare, lo sai.","Contanti in mano, come abbiamo concordato.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Certo, che domande! Ecco i tuoi soldi in lingotti d'oro e per favore accetta la nostra gratitudine più sincera.";
					link.l1 = "Buona fortuna anche a te. Addio.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Capitano, sai, abbiamo pensato che i soldi non siano poi così importanti nella vita. E, francamente, ne abbiamo molto più bisogno noi di te in questo momento. Ma abbiamo una cosa che abbiamo rubato al nostro ex capo. Forse, ti interesserebbe molto più dell'oro. Vuoi darci un'occhiata?...";
					link.l1 = "Sì, hai ragione. È davvero una cosa meravigliosa. Va bene, abbiamo un accordo, grazie e arrivederci.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Perché hai bisogno di così tanti soldi? Sei già ricco. Ci hai aiutato, ti aiuteremo in un'altra occasione.";
					link.l1 = "Non ci sarà una tale occasione. Dite le vostre preghiere, mascalzoni, non tollero debiti.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Sono stato mandato qui da "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" lui stesso...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ti sta aspettando con una risposta da un paio d'ore già. Mi ha mandato subito dopo di te.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Ti ho seguito nel tuo sillage per un bel po' di tempo, ma sei semplicemente troppo veloce.";
			link.l1 = "E quindi?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Meglio dirmi quanto paga il governatore ai suoi sottoposti?";
			link.l1 = "Cavolo!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Non ho bevuto! Stavo cercando il nostromo...";
			link.l1 = "Vai ora... Dirò "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", che ti sei perso nella giungla.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "E tu sei uno sveglio. Prega il Dio che i tuoi trucchi non diventino noti a "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "Non lo saprà se non glielo dici... E tu non lo farai, vero?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Perché? Certo, lo farò, e con grande piacere!";
			link.l1 = "Ti impiccherà comunque per quella follia. Quindi non perdiamo tempo, e ti aiuterò a sfuggire alla forca.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Mmm... E come pensi di farlo?";
			link.l1 = "Ti ucciderò io stesso...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Hai affari qui, "+GetSexPhrase("signore","signorina")+"?";
			link.l1 = "No-no, sono qui su invito dell'affascinante moglie del governatore, sto dando un'occhiata a questa residenza veramente lussuosa.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Ho un messaggio da persone che conosci.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Sì. Voglio portarti davanti alla giustizia!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Oh sì, sono stato davvero fortunato a servire in una casa così bella.";
			link.l1 = "Nessuna sorpresa...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Non dimenticare di dare un'occhiata al nostro giardino!";
			link.l1 = "Grazie, bravo uomo!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Non te la caverai con questa, traditore!";
			link.l1 = "Fermo lì, mascalzone!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Veloce ora! Prendi tutto ciò che è di valore e scappa!";
				link.l1 = "Credo che dovresti scappare anche tu.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Mmm, scusatemi, devo prendere il mio congedo.";
				link.l1 = "Fermo là, mascalzone!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sei "+GetSexPhrase("un ladro, vedo! Guardie, afferratelo","un ladro, vedo! Guardie, prendetela")+"!","Non posso crederci! Mi sono girato per un secondo, e tu stai frugando nel mio baule! Fermate il ladro!","Guardie! Furto! Fermate il ladro!");
			link.l1 = "Aaaah, diavolo!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Ciao, "+GetSexPhrase("compagno","ragazza")+"! Ho preparato una sorpresa per te, ho acceso la miccia della polveriera. Sta per scoppiare in mille pezzi!","Perché stai lì immobile? C'è un incendio nella camera da polvere! Sta per esplodere, e i fuochi d'artificio saranno visibili fino in Europa!");
			link.l1 = RandPhraseSimple("Brigante, non mi ingannerai! Combatti, vigliacco!","Vedo i ratti che abbandonano la nave, e tu sei tra i primi?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Dovresti scappare anche tu, se tieni alla tua vita... Oh, vabbè, non ho tempo, una barca mi sta aspettando. Buona pesca!","Non ho tempo per fare l'eroe, i ragazzi sulla barca mi stanno aspettando. Buona pesca, vincitore!");
			link.l1 = RandPhraseSimple("Maledizione! Taglia i parafanghi! Vattene!","Oh, dio, come potremmo finire in un pasticcio del genere! Apri le bocche di mare! Tirare via!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "Allora che?! Pensi di aver vinto la lotta?! Neanche per sogno. Ho dato fuoco alla polveriera, non scapperai vivo da questa nave.";
			link.l1 = RandPhraseSimple("Pezzo di canaglia, non mi ingannerai! Combatti, vigliacco!","Vedo i ratti che abbandonano la nave, e tu sei tra i primi?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Sono legato da un giuramento, ma ciò non significa che debba morire invano. Mi dispiace per non avervi offerto un posto nella barca, i marinai non capirebbero.","Le navi sono legate l'una all'altra nella battaglia, quindi il tuo destino è sigillato. Mi scuso, ma la mia barca mi aspetta...");
			link.l1 = RandPhraseSimple("Maledizione! Tagliate i parafanghi! Andatevene!","Oh, Dio, come abbiamo potuto cacciarsi in un tale guaio! Apri gli ingressi del mare! Allontanati!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Sei vittorioso! Benvenuto all'inferno! Ho appiccato il fuoco alla polveriera.","Eccoti qua, mio buon uomo! E sei finito, ho dato fuoco alla polveriera.");
			link.l1 = RandPhraseSimple("Brigante, non riuscirai a ingannarmi! Combatti, vigliacco!","Vedo i ratti che abbandonano la nave, e tu sei tra i primi?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Ti stavo inseguendo da un bel po' di tempo. Peccato che ho dovuto sacrificare la mia nave, ma la tua testa vale due navi nuove, comunque. Divertiti a pescare!","Vedi come te ne andrai? Con i fuochi d'artificio, come un principe indiano"+GetSexPhrase("ce","cessare")+". Ma non sarò un perdente, la tua testa vale molto di più della mia nave. Addio ora, la mia barca non aspetterà troppo a lungo...");
			link.l1 = RandPhraseSimple("Maledizione! Taglia le paratie! Vattene!","Oh, dio, come abbiamo potuto cacciarsi in un tale pasticcio! Aprire gli ingressi del mare! Tirarsi indietro!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Aspetta, capitano! Per un paio di parole.","Aspetta, capitano! Credo che questo potrebbe interessarti.");
			link.l1 = LinkRandPhrase("Perché parlare durante una lotta?!","E di che dovrebbe parlare un uomo con un morto?","Qual è l'affare? Vuoi fare un testamento a mio nome?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "C'è un'epidemia a bordo. Ho perso un quarto del mio equipaggio durante il viaggio. Siete tutti condannati...";
			link.l1 = RandPhraseSimple("Sei una canaglia marcita! Perché non hai segnalato che c'è una catastrofe sulla tua nave?!","Hai dimenticato il codice del mare? Avresti dovuto mostrare un segnale sull'albero che c'è un disastro sulla tua nave!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Eravamo destinati a morire, comunque. Ecco perché non ci siamo arresi, volevamo portare te e i tuoi diavoli nel prossimo mondo con noi! Ora sono completamente soddisfatto. Puoi finire la tua sporca azione.";
			link.l1 = RandPhraseSimple("Ti farò rispondere per questo!..","Mi piace l'idea che tu muoia per primo. E lo guarderò.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Non macchierò la mia lama con il tuo sangue immondo, puoi vivere, anche se... a che proposito? Sto portando il mio equipaggio lontano da quella vecchia carcassa marcia.","Dovresti essere mandato alla forca per quello, ma non c'è bisogno di quello ora. Sto portando via i miei uomini... Puoi vivere, anche se il tuo tempo dovrebbe essere breve...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Ciao, capitano, mi è stato detto che stavi cercando me.";
			link.l1 = "Sono - se tu sei "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "Esatto sono io. Qualcosa di importante?";
			link.l1 = "Non so se sia importante per te, ma ho portato "+pchar.GenQuest.EncGirl.name+". Lei è scappata di casa ed ora ti sta aspettando non lontano dalla taverna.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "Oh mio... Sapevo che tutto finirebbe così... E perché è scappata? Te l'ha detto?";
			link.l1 = "Suo padre vuole darla in sposa al figlio dell'usuraio.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "Oh no, non possiamo permettere che ciò accada! Capitano, sai, mi trovo in una situazione così stupida... Volevo chiederti di portarci a "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" alla città chiamata "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", ma al momento non ho soldi e non ho ancora trovato un lavoro. Ho una famiglia benestante e una carriera promettente in "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\nVi assicuro, i miei genitori saranno felici di vedermi con una giovane fidanzata e vi ricompenseranno generosamente. Allora, sei dentro?";
			link.l1 = "...Ascolta ora, ho piani completamente diversi. Posso darti un consiglio per trovare un lavoro come marinaio e affittare una cabina per la tua sposa con il tuo salario. Le persone arrivano in Europa in questo modo, e quel tuo insediamento è a un volo notturno di uccello.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Oh, la gioventù... Ti rendi conto di quello che mi stai chiedendo di fare? Portare via una ragazza dai suoi genitori senza la loro benedizione? ... E che tipo di uomo rifiuterebbe una cosa del genere, ovviamente che ci sto!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Grazie, capitano. Ricorderemo il tuo aiuto per il resto dei nostri giorni.";
			link.l1 = "Non è stato niente. Spero che tutto andrà bene per te.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Ti ho promesso di presentarti ai miei genitori. Se dovessi avere un minuto libero, per favore vieni a "+sTemp+", mio padre lavora lì, e gli dirò quello che hai fatto per noi. Sono sicuro che sarà felice di vederti.";
			link.l1 = "Va bene, passerò non appena avrò un momento. Siate felici e prendetevi cura l'uno dell'altro, entrambi...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Aspetta! Aspetta, capitano! Per favore.","Capitano, per favore, aspetta, ti prego...");
			link.l1 = LinkRandPhrase("Cosa? Hai perso il fiato?","Alza la tua lama, codardo!","Cosa succede? Hai dimenticato di fare un testamento?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Aspetta... Sono ferito e troppo debole per continuare a combattere... Non sto chiedendo pietà, ma ho un affare in sospeso. Ti prego, promettimi che esaudirai l'ultima volontà di un uomo morente.";
			link.l1 = RandPhraseSimple("Non fare il fifone, capitano, accetta la morte come si conviene a un uomo!","Capitano, che sentimentalismo? Una battaglia infuria intorno, quindi finiamo ciò che abbiamo iniziato.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Parla ora e fai in fretta.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Racconta "+pchar.GenQuest.CaptainComission.Name+" dal insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", che non sono riuscito a esaudire la sua richiesta... prima che avessi tempo di... Possa perdonarmi...";
				link.l1 = RandPhraseSimple("E questo è tutto?! Bene, posso farlo. Ehi, amico...","Va bene, glielo dirò se avrò tempo. Ehi, amico...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Non credo proprio. Non ho tempo per tali sciocchezze. Finiamo quello che abbiamo iniziato.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Per favore, informa il capitano di una pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'"+pchar.GenQuest.CaptainComission.Name+", che non dovrebbe mostrare il suo volto in "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"Le autorità sono a conoscenza delle vere circostanze della sua morte "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"... il tempo è breve, sarà arrestato... navigando verso "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" da "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", il viaggio richiederà quasi quindici giorni... ahh ... dobbiamo affrettarci..."; // belamour gen
				link.l1 = RandPhraseSimple("Non prometto nulla, ma proverò all'occasione. Ehi, amico...","Bene, glielo dirò se avrò tempo. Ehi, amico...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Quale crudeltà! Spero che ne risponderai.";
			link.l1 = "E per molto di più...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Ti sto ascoltando, "+GetAddress_Form(pchar)+".","Cosa volevi?","Come posso aiutarti?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Sei tu "+pchar.GenQuest.CaptainComission.Name+"? Ho affari con te. Capitano "+pchar.GenQuest.CaptainComission.CapName+" mi ha chiesto di passarti un'informazione importante.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "No, niente...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Lo ha fatto? Va bene. Allora, cosa vuole quel capitano "+pchar.GenQuest.CaptainComission.CapName+"voleva che sapessi?";
			link.l1 = "Mi ha chiesto di dirti che non sarà in grado di esaudire la tua richiesta.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "Di cosa stai parlando?! Lo conosco da una vita, è un uomo molto onesto. Semplicemente non avrebbe potuto dirti una cosa del genere!";
			link.l1 = "Diciamo, è stato per motivi al di fuori del suo controllo. In altre parole - quella era la sua ultima volontà.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ah, è completamente fuori luogo! Quanto tempo sprecato\n"+"Capitano, in tal caso, devo chiederti di aiutarmi. Pirati di  "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+"hanno catturato il mio parente "+pchar.GenQuest.CaptainComission.SlaveName+" e stanno chiedendo un riscatto per lui. Potresti occuparti di questa missione? La ricompensa dovrebbe essere piuttosto generosa.";
				link.l1 = "Sfortunatamente, ho altri piani.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Cercherò di aiutarti se mi spieghi più in dettaglio.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ah, questo è completamente fuori luogo! Tanto tempo sprecato\nE che dire dei bauli?";
				link.l1 = "Umm... quali casse?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "Un peccato, capitano... È un peccato che tu non sia disposto ad aiutarmi.";
			link.l1 = "Non è una questione della mia volontà, amico mio. Devi capire. Addio.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Ieri ho ricevuto una lettera da "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", in cui mi avvertiva che il riscatto sarebbe stato più alto, e minacciava anche di venderlo come schiavo. Il defunto capitano avrebbe dovuto avvisare "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", che sono d'accordo con le condizioni precedenti e faccio un pagamento anticipato. Ma ora capisco perché i pirati hanno alzato la posta in gioco.";
			link.l1 = "E cosa stai suggerendo?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("compagno","ragazza")+", Avverto brutti giochi qui. Ti avverto che è molto pericoloso e può causare gravi conseguenze. Capitano "+pchar.GenQuest.CaptainComission.CapName+" aveva tre casse piene d'oro, che avrebbe dovuto consegnare a "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" su "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" come riscatto per un uomo -  "+pchar.GenQuest.CaptainComission.SlaveName+". E se volesse che tu venissi da noi, non avrebbe potuto dimenticarsi di dirti dei bauli.";
			link.l1 = "Mentre diceva l'ultimo, non sembrava che avesse finito la sua frase. Speravo che mi avresti detto di più.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Non mi resta altra scelta... Ho già raccolto la somma richiesta, 150 000 pesos. Ti chiedo di consegnarla a "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" e porta qui il mio parente. Ti pagherò 40 000 non appena sarà fatto.";
			link.l1 = "Bene, sono pronto.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Sfortunatamente, ho altri piani.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "Allora prendi i soldi e possa il nostro Signore benedirti. Ma per favore, sbrigati. Ho paura che "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" non aspetterà e venderà la povera anima in schiavitù.";
			link.l1 = "Aspettami qui. Non penso che ci vorrà molto tempo.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "Non importa\nA chi ha raccolto il riscatto non importa. Hanno solo bisogno del risultato, vivo e in un pezzo - "+pchar.GenQuest.CaptainComission.SlaveName+". Quindi non perdere tempo.";
			link.l1 = "E se rifiuto?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Infatti, non ho bisogno del tuo consenso. Sto solo avvisandoti che se non consegni "+pchar.GenQuest.CaptainComission.SlaveName+" vivo e vegeto alla taverna, manderò cacciatori di taglie dopo di te...";
			link.l1 = "Mmm... È grave. E se lo faccio?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "Allora ne discuteremo ulteriormente.";
			link.l1 = "Bene... Vediamo come va.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Ciao, capitano "+GetFullName(pchar)+". Qualche notizia?","Allora, capitano, hai già consegnato il riscatto?","Ciao, spero che tu sia venuto con buone notizie?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Sfortunatamente, i miei piani sono cambiati, quindi devo rompere il nostro accordo.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Non ancora. Sono ancora occupato con quello.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("Oh, lieto di salutarti, capitano "+GetFullName(pchar)+". Ci sono buone notizie?","Allora, capitano, hai salvato il nostro amico sofferente?","Contento di vederti vivo e vegeto, capitano. Qual è lo stato della nostra faccenda comune?");
					link.l1 = "Nessuna novità per ora, ma ci sto lavorando.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Ascolta, amico, e perché stai cercando di rendere me responsabile di quel affare?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Ciao, capitano "+GetFullName(pchar)+". Qualche notizia?","Allora, capitano, hai già consegnato il riscatto?","Ciao, spero che tu sia venuto con delle buone notizie?");
					link.l1 = "Sì. La tua richiesta è stata esaudita, "+pchar.GenQuest.CaptainComission.SlaveName+" è a bordo della mia nave e si sta preparando a venire a riva.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, lieto di salutarti, capitano "+GetFullName(pchar)+". Ci sono buone notizie?","Allora, capitano, hai salvato il nostro amico sofferente?","Contento di vederti vivo e vegeto, capitano. Qual è lo stato del nostro affare comune?");	
					link.l1 = "Ho portato l'uomo di cui abbiamo parlato. È a bordo della mia nave.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Ciao, capitano "+GetFullName(pchar)+". Novità?","Allora, capitano, hai già consegnato il riscatto?","Ciao, spero che tu sia venuto con delle buone notizie?");
					link.l1 = "Saluti, "+pchar.GenQuest.CaptainComission.Name+", Devo deluderti.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("Oh, lieto di salutarti, capitano "+GetFullName(pchar)+". Ci sono buone notizie?","Allora, capitano, hai salvato il nostro amico sofferente?","Contento di vederti vivo e vegeto, capitano. Qual è lo stato del nostro affare comune?");
					link.l1 = "L'uomo per il quale stavi intercedendo, è morto.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Grazie, capitano, hai reso un grande favore alla nostra famiglia. Ecco la tua ricompensa... Ci sono tre cassette - che equivalgono esattamente a 40 000 pesos. Per favore, scusami, devo vederlo ora.";
			link.l1 = "Certo, fatevi un caloroso incontro e buona fortuna a entrambi.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Capisco perfettamente la tua impazienza, ma ci sono state circostanze impreviste, che mi hanno costretto a sopportare costi aggiuntivi.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "Non capisco... Non abbiamo già concordato l'importo del tuo pagamento?";
			link.l1 = "Abbiamo, ma invece di 150000 pesos sono stato costretto a pagare 200000, senza contare il viaggio fino a Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Capitano, questo è solo il risultato della tua stessa lentezza. I pirati non hanno fatto ulteriori richieste con me. Che strano individuo, che cerca di ottenere qualcosa a spese delle difficoltà altrui?";
			link.l1 = "Bene, vedo che è inutile cercare di spiegarti qualcosa...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Eccellente! E avevi dei dubbi che avremmo lavorato bene insieme.";
			link.l1 = "Ma ho dovuto spendere molto per questa faccenda.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Lo so, lo so... Ma c'è anche la tua colpa in questo. Come hai potuto affondare tre casse d'oro, che abbiamo dovuto letteralmente scuotere fuori dal tesoro, così che "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" potrebbe avere un tale specialista "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Sappi, che non te lo darò senza una giusta ricompensa.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "Ebbene, sei un uomo intelligente, di sicuro capisci che è troppo tardi per trattare. Avremmo potuto arrestare la tua nave con il suo carico.\nMa la compensazione è stata fornita prima. Pertanto, il governo di "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"ti congratula per un'operazione riuscita e ti presenta questo prezioso dono e una modesta ricompensa.";
			link.l1 = "Hmm... Beh, comunque meglio di niente. Prendi il tuo prezioso specialista.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Oh, che peccato! Ho già perso troppo tempo. Mi hai proprio abbattuto, capitano!";
			link.l1 = "Capisco, ma le circostanze non potevano essere superate. Ecco i tuoi soldi.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Potresti sbrigarti per favore? Temo che i pirati cambieranno ancora una volta le condizioni dell'accordo.";
			link.l1 = "Non preoccuparti, ce la faremo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Spero che tu capisca che stai lavorando contro il tempo?";
			link.l1 = "Di nuovo! Ci sto lavorando. Abbi pazienza.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Dio ci salvi! Nessuna pressione, solo un aiuto dal modesto Puritano\nÈ colpa tua. Hai ucciso il capitano "+pchar.GenQuest.CaptainComission.CapName+", abbiamo perso il nostro oro e fallito il riscatto di un uomo molto prezioso. È un vero rompiscatole ora e la tua responsabilità. Non pensare nemmeno di essere perdonato... Pagherai per tutto.";
			link.l1 = "Fottiti!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Ciao, volevi qualcosa?";
			link.l1 = "Posso vedere il proprietario di questa piantagione?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Lui non è qui, sta cercando un schiavo fuggitivo, Lama, o Sangue, non ricordo... E io sono l'intendente locale "+npchar.name+" e sono autorizzato a risolvere tutte le questioni mentre il capo è in ferie.";
			link.l1 = "Sei tu? Bene... E vendere schiavi sono anche questi i tuoi affari?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Certo. Quanti ne vuoi comprare?";
			link.l1 = "Solo uno.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Sei sicuro di aver bisogno solo di uno schiavo?";
			link.l1 = "Certo, lo sono. Il suo nome è "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Ma certamente ti rendi conto che il prezzo di uno schiavo sarà più alto rispetto al prezzo di uno schiavo in un lotto più grande?";
				link.l1 = "Certo che posso. Puoi nominare il prezzo?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Mmm... Spero tu sappia per chi stai intercedendo?";
					link.l1 = "Cosa intendi?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Oh, quel fannullone. Non darei un rame per lui. Da quando è stato portato qui, non ha mai fatto un vero lavoro. Non ho idea di perché il colonnello sprechi soldi per questi detenuti statali. Ora, i ragazzi di colore sono un'altra storia. Sono ottimi lavoratori, è nel loro sangue sia forte che docile. E credimi, possono fare assolutamente qualsiasi lavoro. La raccolta della canna da zucchero o il servizio come steward - lo faranno nel miglior modo possibile, basta dargli un po' di 'convincimento'...";
					link.l1 = "Amico mio, non me ne importa nulla dei tuoi uomini di colore. Sono solo interessato a quel fannullone di cui parlavi, tanto non vivrà a lungo, mi serve come carne da cannone e pagherò di più per lui.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Certo, certo. Fammi vedere il prezzo\nOh!!! 150000 pesos.";
			link.l1 = "Caspita...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Il prezzo dovrebbe essere nell'elenco dei prezzi. Eccolo. Sai, non lo capisco proprio. Gli altri schiavi sono venduti a prezzi ragionevoli, ma quello viene venduto per una fortuna...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Credo di capire cosa sta succedendo qui... Va bene, ecco i soldi, e lo porto via con me.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Mmm... Ma non sto riscattando un ostaggio, voglio comprare uno schiavo ordinario. Non pensi che con una somma del genere si potrebbe comprare una decente nave completamente equipaggiata?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "Non è uno schiavo ordinario. Il colonnello Bishop ha persino ordinato di proteggerlo.";
			link.l1 = "Allora non posso nemmeno comprarlo?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Certo che puoi. Il colonnello ha fissato un prezzo per lui - 200000 pesos, secondo la lista dei prezzi.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "Caspita! Beh, di sicuro quel colonnello deve sapere che tipo di persona sia quel schiavo...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Mmm... Ma non sto pagando un riscatto per un ostaggio, voglio comprare un semplice schiavo. Non pensi che con una somma del genere potrei comprare una decente nave completamente attrezzata?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ah, sì. Perdonami. Lascia che guardi il prezzo che Bishop ha lasciato.\nAha, eccolo qui. Bene. Oh!.. 150 000 pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Sembra che ci sia qualche tipo di errore. Sicuramente capisci che nessuno schiavo può costare tanto. Suppongo che ci sia uno zero in più, e la somma dovrebbe essere 15000 pesos. E è ancora troppo, considerando che è un fannullone e un idiota.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Ma non sto riscattando un ostaggio, voglio comprare un semplice schiavo. Non pensi che con quella somma si potrebbe comprare una decente nave completamente attrezzata?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Ottimo! Fantastico! Lo porteranno qui subito... Ehh... Tè, forse?";
			link.l1 = "No, grazie... Saluta il colonnello Bishop...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "E da chi, posso sapere?";
			link.l1 = "Mmm... Lascia stare, non disturbarti. Addio.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Mi dispiace, ma non c'è niente che io possa fare. Ecco la lista dei prezzi.";
			link.l1 = "Oh, smettetela, 'lista dei prezzi, lista dei prezzi...' Non riuscite a decidere la cosa più semplice senza il Vescovo. Digli... Ma no, non dirgli nulla.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Allora non comprerai quel schiavo.";
			link.l1 = "No. Addio.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Non so nulla a riguardo. Ho solo istruzioni specifiche riguardo alla vendita di quel particolare schiavo.";
			link.l1 = "Sciocchezze... Va bene, qualsiasi cosa. Ecco i soldi. Porta lo schiavo.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Certo. Sarà qui in un attimo.";
			link.l1 = "Addio.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Sì, forse hai ragione. Dovrebbe essere un errore.";
			link.l1 = "Bene, se abbiamo concordato il prezzo, posso portarlo via con me ora?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Sì, certo. Sarà portato qui tra un momento.";
			link.l1 = "Molto bene. Ecco i tuoi soldi... Addio.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Vuoi un po' di tè, capitano?";
			link.l1 = "No, grazie.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Hai deciso di comprarlo.";
			link.l1 = "No. Addio.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Ciao, capitano. Come posso aiutarti? Non posso credere che questo tormento sia finalmente finito.";
				link.l1 = "Dovresti ringraziare non me, ma piuttosto il tuo parente "+pchar.GenQuest.CaptainComission.Name+" da "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Ha raccolto il riscatto.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Ciao, capitano. Mi è stato detto che hai pagato il riscatto per me. Devo ringraziarti per questo, anche se capisco che eri solo un corriere.";
				link.l1 = "Non sembri così felice con la tua libertà appena riacquistata. Sei preoccupato per qualcosa?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Per favore, se non interferisce troppo con i tuoi piani, portami da lui. Vorrei ringraziarlo personalmente.";
			link.l1 = "Certo, lo farò. Vieni, ti porterò alla nave.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "Per essere sicuro della mia libertà, ho bisogno di sapere i nomi di coloro che l'hanno pagata.";
			link.l1 = "Beh, sono stato io a pagare, anche se non era mia intenzione.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Allora, i miei sospetti erano confermati. Sei stato costretto a farlo da "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Sì, è "+pchar.GenQuest.CaptainComission.Name+" da "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Capisco. Non ho idea di cosa ti abbiano promesso, ma ecco l'accordo: portami alla taverna di "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", Sarò davvero al sicuro lì. In cambio, condividerò con te alcune informazioni che possiedo.";
			link.l1 = "Va bene, tanto più che non hanno promesso nulla finora. Vieni con me, ti porto alla mia nave.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Non rischio di attirare guai su di me a causa di alcune informazioni discutibili.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Sfortunatamente, non posso rivelartelo adesso. Potrebbe significare guai per entrambi.";
			link.l1 = "Anche di più... Seguimi e niente cose stupide, per favore. Considerati sotto arresto ancora una volta.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Cosa?! I pirati hanno cambiato di nuovo l'accordo? Ma non posso più togliere soldi dall'attività! In questo modo sarò presto in bancarotta!";
			link.l1 = "No... Il tuo parente è morto nelle piantagioni di Barbados durante un tentativo di fuga fallito.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Oh... Sono completamente distrutto... Come è potuto succedere?";
			link.l1 = "I pirati non hanno aspettato il riscatto e lo hanno venduto come schiavo. Sono andato a prenderlo a Barbados, ma non sono riuscito a salvarlo...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Gesù! Cosa sta succedendo?\nBene, capitano, grazie per la tua partecipazione. E per favore, restituisci i soldi che ti ho dato.";
			link.l1 = "Le mie spese hanno superato tutte le aspettative, quindi terrò i tuoi soldi... Addio.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Certo, prendilo... Mi dispiace di non essere riuscito ad aiutarti... Addio.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "Che peccato. Non hai idea di quanto sia realmente brutto...";
			link.l1 = "Non posso fare nulla al riguardo. Sono anche contento che tutto sia successo in questo modo. Addio.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Bevi... capitano, porta un po' d'acqua...";
			link.l1 = "Ehi, compagno, non sei tu "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Sì... Quello sono io...";
			link.l1 = "Ascolta! Se non vuoi perire qui, come un pesce piatto su una secca, riprenditi e ascoltami. Sai dove si trova il Faro di Barbados?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Faccio...";
			link.l1 = "Una volta che avrai l'opportunità, scappa lì. Cercherò di organizzare tale opportunità per te.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Vai avanti e chiedi, capitano, ma fai presto, sono in servizio.","Parla, ma sbrigati e non infastidirmi con sciocchezze.");
			link.l1 = RandPhraseSimple("Potresti dirmi come posso trovare un certo schiavo? Si chiama "+pchar.GenQuest.CaptainComission.SlaveName+".","Da qualche parte in questa piantagione dovrebbe esserci uno schiavo di nome "+pchar.GenQuest.CaptainComission.SlaveName+". Puoi dirmi come potrei parlare con lui?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Oggi è punito e sotto guardia.";
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Grazie... capitano, hai salvato la mia vita...";
			link.l1 = "Corsa al faro di Barbados e aspettami lì.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Capitano, come posso ringraziarti? Ancora non riesco a credere che questo tormento sia finalmente finito.";
				link.l1 = "Sono già stato ringraziato dal tuo parente "+pchar.GenQuest.CaptainComission.Name+" da "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". Agisco su suoi ordini.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Grazie, capitano. Non so per conto di chi agisci, ma anche una cattiva libertà è meglio di una buona schiavitù.";
				link.l1 = "Cosa intendi?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Se non disturba troppo i tuoi piani, per favore portami da lui. Sono solo troppo stanco di tutto questo.";
			link.l1 = "Certo che lo farò... se riusciremo a uscire vivi da qui.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "E posso sapere i nomi delle persone che hanno pagato per la mia libertà?";
			link.l1 = "Beh, in realtà, non sono stato pagato. Non mi avevano lasciato alcuna scelta.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Allora, i miei sospetti erano confermati. Sei stato costretto a farlo da "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Sì, è "+pchar.GenQuest.CaptainComission.Name+" da "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Non ho idea di ciò che ti hanno promesso, ma ecco l'accordo: portami alla taverna di "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", Sarò veramente al sicuro lì. In cambio, condividerò con te alcune informazioni che possiedo.";
			link.l1 = "Va bene, tanto più che finora non hanno promesso nulla. Vieni con me, ti accompagno alla mia nave.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Non rischio di attirare guai su di me per via di alcune informazioni discutibili.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Sfortunatamente, non posso rivelarlo a te adesso. Questo può significare guai per entrambi noi.";
			link.l1 = "Anche di più... Seguimi e niente stupidaggini, per favore. Considerati di nuovo sotto arresto.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Grazie, capitano. Ora sono finalmente al sicuro. Non ti offro denaro, perché sono sicuro che la conoscenza e la sua abile applicazione valgono molto più di un metallo perituro.";
			link.l1 = "Sto aspettando le informazioni";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "La questione è che io sono uno scienziato, specialista di "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" e "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" mi aveva offerto la sua cooperazione per un bel po', "+"ma sono un ingegnere militare e mantengo i miei giuramenti di fedeltà. Hanno cercato di rubarmi, sebbene i veri problemi siano iniziati quando i pirati hanno scoperto la mia vera identità e importanza\n"+"Alla fine, sono riusciti a catturarmi, ma volevano solo l'oro, non avevano bisogno delle mie conoscenze. I miei amici e nemici non sono riusciti a riscattarmi in tempo e sono stato venduto alle piantagioni. Conosci il resto.";
			link.l1 = "Sì, guai a chi ha senno, come dicono, infatti.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Beh, potresti dire così. Quindi, se presti attenzione a ciò che posso dirti, diventerai molto più abile nell'abilità di "+sTemp;
			link.l1 = "Grazie, queste informazioni sono davvero utili.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Ebbene, addio e grazie per tutto.";
			link.l1 = "Grazie anche a te. Addio, e cerca di non farti prendere la prossima volta.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ciao, sono il capitano "+GetFullName(NPChar)+", cosa ti ha portato sul ponte della mia nave '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?","Ahoy, sono sempre felice di avere ospiti sulla mia nave. Capitano "+GetFullName(NPChar)+" al vostro servizio.");
			link.l1 = "Ciao, sono il capitano "+GetFullName(pchar)+", agendo per conto di qualche capitano "+pchar.GenQuest.CaptainComission.CapName+". Ha chiesto di dirti che saresti stato arrestato in "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Le autorità sanno di "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Che diavolo stai facendo qui? Abbiamo organizzato tutto! Torna sulla tua nave!";
			link.l2 = "Ehh..Sì, certo!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ah, che peccato! Facciamo un pensiero\nE dov'è il capitano "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "È morto.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Maledizione! Le cose stanno solo peggiorando... Ascolta, "+GetFullName(pchar)+", Non sono pronto ad affrontare un tale svolgimento degli eventi. Capitano "+pchar.GenQuest.CaptainComission.CapName+" e ho accettato di incontrarmi a "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". Il piano era di caricare della merce sulla sua nave. Ora che il capitano è morto, non posso presentarmi nel insediamento\nSembra che non mi resti altro che chiederti un favore.";
			link.l1 = "Il mio consenso dipenderà dal tipo di aiuto di cui hai bisogno.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Aiutami con uomini e lance. Ho bisogno che il carico venga portato via da "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". Puoi tenere la parte del carico del defunto capitano.";
			link.l1 = "Hmm... A quanto pare, hai preso un boccone più grande di quello che potresti masticare. Ho bisogno di più informazioni.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Sfortunatamente, non sono nella posizione di perdere tempo su quello.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Bene, ti darò i dettagli\n"+"Durante una delle pattuglie regolari ho incontrato una nave sotto la bandiera di "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Hanno ignorato i miei ordini di arrendersi."+"Quando dopo un breve inseguimento ci siamo aggiunti con "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' e così alzarono la bandiera nera. Il forte era abbastanza lontano, quindi abbiamo dovuto combattere da soli. Hanno distrutto il nostro bompresso, ecco perché non siamo riusciti a evitare l'abbordaggio.\n"+"È stato un pelo, ma siamo riusciti a ucciderli tutti grazie alla Santa Vergine Maria e a un'unità di moschettieri. Immagina la nostra felicità quando abbiamo scoperto che "+sTemp+" era pieno di. "+"Abbiamo deciso che questa è una ricompensa decente per le nostre ferite e le morti dei nostri compagni\nEra già buio, abbiamo preso "+sTemp+" alla baia più vicina e nascondi la merce sulla riva. Poi abbiamo fatto esplodere "+sTemp+" e ho riferito del vascello pirata affondato. Naturalmente, non ho menzionato il carico.";
			link.l1 = "Sembra che qualcuno lo abbia ancora sparato in giro...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Peccato, capitano... È un peccato che tu non sia disposto ad aiutarmi.";
			link.l1 = "Non è questione della mia volontà, mia cara. Devi capire. Addio.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Non credo che fossero i miei uomini. Molto probabilmente, il proprietario del carico è ansioso di alleviare il dolore della perdita\nQuindi? Posso contare sul tuo aiuto?";
			link.l1 = "Sì, suona bene.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "No, amico mio. Prima: non so quanta merce entrerà nella mia stiva. E secondo: non c'è garanzia che le autorità non l'abbiano già trovata e portata via, lasciando un'imboscata vicino alla cache.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Incontriamoci a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" allora, proprio dopo la mezzanotte. La mia posizione attuale richiede di essere segreti. Dobbiamo evitare le pattuglie."; // belamour gen
			link.l1 = "Bene, aspettami lì.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Peccato, ma non mi lasci scelta. Una sola nave non basta per prelevare tutto il carico. Ho rischiato per esso la mia carriera e la mia stessa vita. Sicuramente, il tuo equipaggio sarà felice di aiutarmi in cambio di una buona parte.";
			link.l1 = "E cosa stai suggerendo?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Prenderò la tua nave e ti lascerò a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "Il tuo successo mi sembra improbabile. Ritornerò sulla mia nave anche se devo abbattere tutto il tuo equipaggio.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Sembra che non ho scelta. Beh, mi sottometterò alla violenza...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Capitano, dobbiamo affrettarci. Temo che una pattuglia potrebbe avvistarci.";
			link.l1 = "Bene, affrettiamoci.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Capitano, ordina di lanciare tutte le scialuppe. Dovremo andare più volte, e temo che una pattuglia possa venire alla cala.";
			link.l1 = "Non preoccuparti, tutto dovrebbe andare bene. Le barche stanno già arrivando alla riva.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "Oh, accidenti. Ora abbiamo compagnia...";
			link.l1 = "Veramente, se menzioni qualche sciocco, si presenterà subito...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Capitano, stiamo cercando un criminale di guerra "+pchar.GenQuest.CaptainComission.Name+", che ha nascosto un carico prezioso dalle autorità. I vostri documenti, per favore.";
			link.l1 = "Quali documenti, ufficiale? Siamo sbarcati per rifornire le nostre scorte di acqua fresca.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "Ecco lui, "+pchar.GenQuest.CaptainComission.Name+" se stesso . Arrendetevi le vostre armi e seguitemi, entrambi!";
			link.l1 = "Quello era un momento davvero sfortunato, ufficiale...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Dobbiamo affrettarci prima che arrivino i rinforzi. Il caricamento sta per finire, e la tua parte è "+pchar.GenQuest.CaptainComission.GoodsQty+" unità di "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "Eccellente. È ora di andare. È stato un piacere fare affari con te.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "E solo un'altra richiesta. Le autorità ci inseguiranno di sicuro, potresti per favore scortare la mia nave fino a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", che si trova su "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "No, amico mio, d'ora in poi ogni uomo per se stesso. Addio...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Certo, potrei farlo per una buona ricompensa.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Certo. Per la scorta sono disposto a pagare  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" pesos. Ma c'è un'altra condizione, non dovrebbe richiedere più di "+pchar.GenQuest.CaptainComission.iDay+" giorni. È importante.";	
			link.l1 = "Affare fatto. Partiamo immediatamente.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Capitano, stiamo perdendo tempo. Potrebbero trovarci da un momento all'altro.","Capitano, stiamo correndo contro il tempo. Non dimenticare che mi stanno cercando.","Capitano, non dobbiamo indugiare. La mia nave è troppo grande per evitare l'attenzione della pattuglia.");
			link.l1 = LinkRandPhrase("Sì, hai ragione. Dobbiamo sbrigare.","Allora imbarcatevi sulle barche senza ulteriori indugi.","Ecco... Raduna i tuoi uomini. Stiamo partendo.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Capitano, devo parlare con i miei uomini.";
			link.l1 = "Vai avanti.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Ti saluto, capitano "+pchar.CaptainComission.Name+". Allora, hai portato tutto il carico? E dov'è il capitano "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" è morto. Ho dovuto chiedere "+NPCharSexPhrase(sld,"questo signore","questa signora")+" per aiuto. Ti presento, questo è il capitano "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "E "+NPCharSexPhrase(sld,"chi è lui? È lui","chi è lei? È lei")+" consapevole dei nostri affari?";
			link.l1 = "In generale, sì. Ma c'è un problema -"+NPCharSexPhrase(sld,"è certo","lei è certa")+", che metà del carico appartiene a "+NPCharSexPhrase(sld,"lui","lei")+". Dobbiamo convincere "+NPCharSexPhrase(sld,"lui","lei")+", che questo non è esattamente il caso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Amico mio "+GetFullName(pchar)+", hai già sentito tutto quello che dovevi sapere. Dobbiamo accedere alla tua stiva.";
			link.l1 = "E pensi che i miei ragazzi resteranno lì a guardare, mentre dei pezzenti svuotano la loro stiva?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Hai ragione. Denaro contante per l'importo, diciamo, "+pchar.GenQuest.CaptainComission.GoodsSum+" pesos, ci libererà dalla necessità di scontrarci con il tuo equipaggio. Tieni presente che questo copre metà del nostro carico, quindi tutto è giusto. Se accetti, nessuno si farà male.";
			link.l1 = "E se rifiuto?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "In tal caso la violenza è inevitabile. Sarai la prima vittima e troverai pace in questa accogliente baia, e il tuo equipaggio non sarà in grado di venirti in aiuto... Ti piacerebbe?";
			link.l1 = "Mi state lasciando senza scelta. Bene, vi ucciderò tutti.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Credo di non avere scelta. Va bene, ecco i tuoi soldi.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Ebbene, questa è una decisione adatta per "+GetSexPhrase("un nobile gentiluomo","una dama galante")+".";
			link.l1 = "Smettila di filosofeggiare! Passiamo ai fatti!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Una decisione saggia. Buona fortuna a te.";
			link.l1 = "Possa tu soffocarci...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Capitano "+GetFullName(pchar)+", siamo in ritardo. Spero che tu capisca che ora non hai diritto a una ricompensa.";
			link.l1 = "Certo che lo faccio. Ho già guadagnato un bel po' di monete, grazie a te. Addio...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Acquisteresti del rum per un vecchio soldato che ha sofferto molto nelle battaglie per la gloria della Corona?";
			link.l1 = "Oste! Versaci un po' di rum!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Oh, grazie, "+GetAddress_Form(pchar)+", molto gentile da parte tua trattare un disabile che ha completamente perso la memoria...";
			link.l1 = "Completamente, dici?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Certo, signora"+GetSexPhrase("ter","s")+"capitano... completamente. Non ricordo nulla tranne un knippel che volava dritto verso la mia testa. Guarda che buco ha fatto, immagino che tutta la mia memoria debba essere fuoriuscita da lì.";
			link.l1 = "Amico, risparmia le tue patetiche storie per le casalinghe. Ho visto gente che ha subito un colpo diretto di mitraglia, la loro memoria è stata completamente cancellata... con le loro teste... E tu qui parli di qualche catena di colpi immaginari. Parliamo piuttosto del capitano "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Oh, beh, sai. Devo guadagnarmi da vivere in qualche modo. Per quanto riguarda il capitano "+pchar.GenQuest.CaptainComission.Name+", non ci guadagno niente a chiacchierare... Se avessi preso un centinaio di monete per ogni domanda su di lui, avrei più oro ora di quanto il governatore riscuote dai suoi sudditi in un anno... ";
			link.l1 = "E hai provato a vendere il carico, nascosto da quel capitano?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Cosa? Un altro segugio? Ti dico ancora una volta, non ricordo nessun capitano "+pchar.GenQuest.CaptainComission.Name+"! Sono confuso e ho il certificato medico che lo conferma! Cosa altro ti serve?!";
			link.l1 = "Oh, non farti prendere dall'eccitazione. Sai... Era troppo tardi. Capitano "+pchar.GenQuest.CaptainComission.CapName+" mi ha chiesto di dire che "+pchar.GenQuest.CaptainComission.Name+"non dovrebbe mostrare il suo volto in quel insediamento, le autorità sanno delle circostanze della distruzione di "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+", e sarà arrestato.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Uffa. Avresti dovuto dirlo subito e non girarci attorno. Sono stato io a chiedere al capitano "+pchar.GenQuest.CaptainComission.CapName+" per intercettare la nostra nave al suo ritorno. "+"È stato spostato ai moli subito dopo quella maledetta lotta. Cosa stava facendo quel maledetto pirata lì con le sue merci?! Tanti ragazzi sono morti a causa sua.";
			link.l1 = "E come sei riuscito a sopravvivere?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Per errore. Per essere onesto, per mio proprio maledetto errore. Non ero abbastanza veloce, quindi la nostra scialuppa non è riuscita a uscire dalla zona pericolosa. Sono stato l'unico a soffrire. Sono stato colpito da qualche relitto e gettato in acqua. Non ricordo nemmeno come ho raggiunto la riva.";
			link.l1 = "E come sei riuscito a sfuggire all'inchiesta?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Disse loro che fui contuso durante l'imbarco e non sapevo niente su nessun carico. Ho anche finto di essere debole di mente, sai, mi sono appena alzato, giusto prima dell'arrivo di "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+". Non potevo muovermi correttamente, la mia coordinazione era a pezzi.";
			link.l1 = "Ehi, ma chi ha sparso il segreto sul carico, comunque?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "I pirati hanno inviato una lettera al governatore, presumibilmente a nome del mercante ferito. Hanno deciso di vendicarsi del capitano per la sua persistenza. È stata colpa sua, la sua stupida ostinazione a condurci in questo pasticcio.";
			link.l1 = "Ma come hai incontrato quel pirata in primo luogo?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Non lo so. Era una pattuglia ordinaria e c'era una nave ordinaria che navigava sotto la bandiera di "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Non ho idea del perché il capitano abbia deciso di ispezionarlo, ma non hanno prestato attenzione a un colpo di avvertimento, e quando li abbiamo raggiunti, hanno issato il 'Jolly Roger'. "+"Non avevamo il supporto del forte, quindi la lotta non è stata facile. Poi la parte dell'abbordaggio. Ancora non so come siamo riusciti a sconfiggerli.\n"+"Ebbene, e abbiamo visto tutto quel prezioso carico. Il diavolo stesso deve avercelo dato. Dovevamo nascondere il carico a terra e far saltare in aria la nave catturata. Era troppo danneggiata.";
			link.l1 = "Non hai paura che tutti i tuoi sforzi e sacrifici saranno vani, se gli uomini del governatore scoprono la cache?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "Non lo troveranno. Ho fatto saltare in aria l'entrata della grotta alla grande, dopotutto, ero il miglior esperto di esplosivi dell'intero squadrone. Solo i contrabbandieri possono trovare il mio nascondiglio, conoscono ogni centimetro di questo posto.\n"+"Guarda, io stesso non ho idea di cosa fare con il bottino. Non posso né venderlo né spostarlo da solo. Inoltre, nessuno farà affari con un teschio crepato. Non voglio fare soldi sulla morte dei miei compagni di equipaggio, ma posso dirti la posizione del nascondiglio per "+pchar.GenQuest.CaptainComission.Sum+"  pesos se mi porti a "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Sono d'accordo. Ecco i tuoi soldi. Ora parla.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Maledizione! Va bene, aspetta qui, andrò a prendere i soldi.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "È troppo, compagno. Inoltre, non ho una nave adatta. Beh, buona fortuna a te e arrivederci...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Bene, d'accordo. Ci incontriamo stasera dopo la mezzanotte nei dintorni "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". E assicurati di avere spazio nella tua stiva per "+pchar.GenQuest.CaptainComission.GoodsQty+" pezzi. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Sarebbe un peccato gettare via una parte di esso..."; // belamour gen
			link.l1 = "Me ne occuperò io. Ci vediamo nella baia...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "Eccoti qui, finalmente. Ho già iniziato a preoccuparmi. Pensavo che mi avresti semplicemente consegnato alle autorità.";
				link.l1 = "Non sono ancora impazzito. Ecco i tuoi soldi. Ora tocca a te mantenere la parola.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Allora, dov'è il denaro?";	
				link.l1 = "Maledizione! Va bene, aspetta qui, vado a prenderlo.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Capitano, a quanto pare, siamo in ritardo. I contrabbandieri hanno trovato la cache.";
			link.l1 = "Non rinuncerò al mio bottino, nemmeno il diavolo stesso potrà prendermelo.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Mi arrendo, occupati dei tuoi concorrenti da solo.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Capitano, abbiamo un affare serio qui. Ti consiglio di portare via la tua squadriglia, prima che arrivino le nostre navi.";
			link.l1 = "Signori, sembra che stiate cercando di prendere ciò che non vi appartiene.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "Oh, davvero?! Hai idea di con chi stai parlando?";
			link.l1 = "Sto parlando a te, amico. Quel carico, ha un legittimo proprietario, e io lo rappresento.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Non ti permetteremo di interferire con i nostri affari, anche se fossi il Messia del nostro Dio! Libera la rotta, se tieni alla tua vita?";
			link.l1 = "Non mi sono spiegato chiaramente? Quel carico è mio, e non me ne vado senza di esso!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "All'inferno con lui! Se lo desideri così tanto allora aspetterai qui, per sempre!";
			link.l1 = "La sorte deciderà chi resterà qui per sempre.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Capitano, ordina ai tuoi uomini di affrettarsi, una pattuglia potrebbe arrivare in qualsiasi momento. Inoltre, è chiaro che i contrabbandieri stavano aspettando i loro trasporti.";
			link.l1 = "Sì, dobbiamo sbrigarsi... Caricate la merce nelle stive e leviamoci di torno.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Grazie, capitano "+GetFullName(pchar)+". Se non fosse stato per te, i contrabbandieri avrebbero preso il nostro carico, e quei ragazzi che sono caduti difendendolo sarebbero morti invano...";
			link.l1 = "E grazie per avermi fatto confidenza.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Ho un cimelio, qui, devo la mia vita a esso. Per favore, accettalo, potrebbe essere il tuo portafortuna. E grazie ancora, amico. Che i venti siano sempre dalla tua parte.";
			link.l1 = "Grazie per il regalo, non me lo aspettavo. E faresti meglio a prenderti cura della tua salute mentre hai monete in tasca.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Sembra che oggi sia il mio giorno di visita. Hai bisogno di me?";
			link.l1 = "Se tu sei il capitano "+pchar.GenQuest.CaptainComission.Name+", allora sì.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...ex capitano"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "Sono "+GetFullName(pchar)+", e ho un paio di domande per te.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "E perché pensi che risponderei alle tue domande?";
			link.l1 = "Capitano "+pchar.GenQuest.CaptainComission.CapName+" mi ha chiesto di avvertirti che le circostanze della distruzione di "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" è diventato noto alle autorità, "+"ma non ho visto la tua nave nel viaggio da "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "E dove si trova il capitano "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "È morto.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Capisco... Quindi è così, eh? Molte cose ora sono al loro posto. Quindi, qualcuno ha sparso la voce che abbiamo saccheggiato "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"Prima o poi, troveranno il carico e mi impiccheranno. Capitano "+pchar.GenQuest.CaptainComission.CapName+" è morto, significa che nessuno può aiutarmi\nTranne te\n "+GetFullName(pchar)+", tirami fuori da qui e ne varrà la pena per te.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Il governatore ha ricevuto un messaggio dal proprietario del carico. E i numeri in esso sono piuttosto impressionanti, sai.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Ma sicuramente non pensi che ti aiuterò bendato?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Il governatore ha ricevuto un messaggio dal proprietario del carico. E sai, i numeri in esso sono piuttosto impressionanti.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Ci sono pettegolezzi nella colonia che tu abbia trattative con i contrabbandieri...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Sembra che dovrò raccontarti tutta la storia.\n"+"Durante una delle pattuglie regolari ho incontrato una nave sotto la bandiera di "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Avevano ignorato i miei ordini di arrendersi. "+"Avevamo raggiunto "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' dopo un breve inseguimento hanno issato la bandiera nera. Il forte era abbastanza lontano, quindi abbiamo dovuto combattere da soli. Hanno distrutto il nostro bompresso, ecco perché non siamo riusciti a evitare l'arrembaggio.\n"+"È stato un soffio, ma siamo riusciti a ucciderli tutti grazie alla Santa Maria e a un'unità di moschettieri. Immagina la nostra felicità quando abbiamo scoperto che "+sTemp+" era pieno di preziosi. "+"Abbiamo deciso che questa è una ricompensa decente per le nostre ferite e le morti dei nostri uomini\nEra già buio, siamo riusciti a prendere "+sTemp+" alla baia più vicina e nascondi la merce sulla riva. Poi abbiamo bruciato "+sTemp+" e ho riferito di una nave pirata affondata. Ovviamente, non ho menzionato il carico.";		
			link.l1 = "Credo che non ci sia motivo per te di ingannarmi. Quindi, ti propongo un accordo, mi mostri il tesoro, e ti porterò in qualsiasi posto dell'arcipelago tu voglia.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "A-ha-ha... No, capitano, non lascio l'insediamento senza la mia quota, anche se devo finire sulla forca.";
			link.l1 = "Bene. Riceverai la tua metà.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Mmm... Sai, non sono disposto a rischiare la mia testa per il tuo benessere. Addio...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Ora stai parlando. Sono pronto\nPrima, dovresti nascondermi a bordo della tua nave. Ti mostrerò la baia dove è nascosto il nascondiglio.";
			link.l1 = "Allora agiamo rapidamente e in modo coordinato. Aprirò la tua cella, e tu seguimi. Non indietreggiare e nessuna domanda fino a quando non usciremo dal forte.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Grazie per il salvataggio. Andiamo a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", Indicherò la posizione del nascondiglio. Dobbiamo affrettarci prima che i selvaggi trovino il posto.";	// belamour gen	
			link.l1 = "Sei sicuro che riusciremo a recuperare tutto il carico?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Hai ragione, assicurati di avere abbastanza spazio per "+pchar.GenQuest.CaptainComission.GoodsQty+" pezzi di "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Sarebbe un peccato perdere un bottino così prezioso con tanto sangue su di esso. Non ci daranno una seconda possibilità.";
			link.l1 = "Me ne occuperò io.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Capitano, non abbiamo bisogno di testimoni. Per favore, cerca di convincere queste persone a lasciare la baia.";
			link.l1 = "Bene, facciamolo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Capitano, mi dispiace, ma questo non è il posto migliore per i tuoi esercizi. Quel molo è già occupato.";
			link.l1 = "Signori, non sono venuto qui per fare turismo. Ho affari qui.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Ebbene, non stiamo qui a pescare meduse, girate le vostre navi e sparite da qui.";
			link.l1 = "Non voglio sprecare il mio tempo a convincerti ad andartene. O lo fai di tua spontanea volontà e vivi, o rimani qui per sempre.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Vedo che hai difficoltà a capire le mie parole. Va bene, sarà il tuo funerale...";
			link.l1 = "Ecco, meglio così!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Siamo qui. La cache si trova in una nicchia in quel dirupo. L'entrata è bloccata con delle rocce. Nella cache, c'è "+pchar.GenQuest.CaptainComission.GoodsQty+" unità di "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Ricorda che una metà è mia?";
			link.l1 = "Certo che sì. Abbiamo un po' di tempo mentre i miei uomini stanno caricando le merci. Parliamo di dove devi essere portato tu e il tuo carico.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Molto bene. Ora dimmi, c'è qualche motivo per cui dovrei condividere?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Capitano "+pchar.GenQuest.CaptainComission.Name+", Devo dirti qualcosa di sgradevole. Lavoro per il governatore. E intendo consegnargli tutto il carico che hai nascosto. Dovresti tornare in prigione e aspettare lì il tuo destino.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Molto bene. Ma ecco il punto... All'inizio volevo consegnarti alle autorità, ma perché dovrei farlo ora? E perché dovrei condividere con te?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Ho bisogno di arrivare a "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", a "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" per "+pchar.GenQuest.CaptainComission.iDay+" giorni. Il mio equipaggio lì deve aver preparato il carico per la vendita."; // belamour gen
			link.l1 = "Bene. È ora di partire, allora.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Giusto. Si dovrebbe sempre fidarsi della mente, non del cuore. Vivere e imparare\nAnche se non me lo aspettavo, sono sempre pronto per una lotta. Risponderai per il tuo tradimento.";
			link.l1 = "Ebbene, se sei fortunato...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Giusto. Si dovrebbe sempre fidarsi della mente e non del cuore. Vivere e imparare\nAnche se non me lo aspettavo, sono sempre pronto per una battaglia. Pagherai per il tuo tradimento.";
			link.l1 = "Sono al vostro servizio...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Sembra che siamo arrivati tardi... I clienti non hanno aspettato, e non ho l'opportunità di organizzare lo stoccaggio e la vendita del carico da solo...";
			link.l1 = "Hai qualche proposta particolare a riguardo?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitano "+GetFullName(pchar)+", Lo so che è un po' strano, ma... potresti darmi un equivalente monetario della mia quota? Suppongo, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos potrebbero essere un buon compromesso.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Sì, è un prezzo equo. Non mi dispiace. Ecco i tuoi soldi, e addio.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "Oh, no, amico mio, non va bene. Non posso continuare a prenderti per mano. Se non vuoi ritirare la tua merce, la terrò io. Puoi starne sicuro, troverò il modo di immagazzinarla e alla fine di venderla.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Aspetta, capitano. Voglio ringraziarti per il mio salvataggio. Sai, avevo quasi perso la speranza... Ecco, sono sicuro che troverai questo cimelio molto utile in molte situazioni difficili... Addio ora.";
			link.l1 = "Grazie. Non me l'aspettavo. È stato un piacere fare affari con te.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Non me lo aspettavo da te... A quanto pare, non ho altra scelta che sfidarti a duello.";
			link.l1 = "Sono al vostro servizio...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Capitano, devo parlare con i miei uomini.";
			link.l1 = "Vai avanti.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Vi saluto, capitano "+GetFullName(pchar)+". Quindi, hai portato tutto il carico? E dov'è il capitano "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" è morto, e sono stato arrestato su una denuncia. E se il capitano "+pchar.CaptainComission.FullName+" non mi avessi aiutato, non avresti visto né me né il carico.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "E "+NPCharSexPhrase(sld,"chi è lui? È lui","chi è lei? È lei")+" consapevole dei nostri affari?";
			link.l1 = "Certo. "+NPCharSexPhrase(sld,"Ha estratto","Ha estratto")+" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, capitano, proprio no. Sono i tuoi problemi! Ho suggerito di portare via la nave, ma ti preoccupavi troppo della tua maledetta carriera. Ed eccoti qui, il tuo amato governatore ti ha messo in prigione."+"La tua parte era molto più piccola di una metà! Non abbiamo messo le nostre teste sotto i colpi d'uva per permetterti di rubare l'intera metà per te!";
			link.l1 = "Ascolta, nostromo, non ti ricordi che la nave era completamente distrutta? Che era quasi sott'acqua? Non capisci che se non avessi dato a quest'uomo la metà, non avresti mai più visto nemmeno un piccolo pezzo del carico?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Non ci prenderai in giro! Come potremmo sapere che non eri in combutta? E se non ci fosse stato affatto un arresto? E se fossi stato solo troppo avido e avessi deciso di rubare le nostre cose? O pensi che abbiamo dimenticato come maneggiare una lama?!";
			link.l1 = "Vedo che sei impazzito. Non senti altro che il tintinnio delle monete nelle tue orecchie.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Ragazzi! Guardate come parla ora il nostro capitano! Infatti, l'avidità lo ha totalmente consumato! Ha venduto la nostra quota a "+NPCharSexPhrase(sld,"un mascalzone","un'avventuriera")+"!!";
			link.l1 = "Chiudi quella sporca bocca adesso, o ti farò tacere per sempre!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Mi dispiace, capitano, che tu abbia dovuto assistere a questa scena ridicola e persino parteciparvi. È difficile credere che solo un mese fa eravamo un equipaggio unito, e ognuno di noi avrebbe sacrificato volentieri la sua vita per salvare un amico.";
			link.l1 = "Devo ammettere, non riesco a immaginare, senza offesa.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Sfortunatamente, non ho l'opportunità di organizzare da solo l'immagazzinamento e la vendita del carico...";
			link.l1 = "Hai qualche proposta particolare a riguardo?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Capitano "+GetFullName(pchar)+", Lo so che è un po' strano, ma... potresti darmi un equivalente monetario della mia quota? Suppongo, "+pchar.GenQuest.CaptainComission.GoodsPrice+" potrebbe essere un buon compromesso.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Va bene, non mi importa. Ecco i tuoi soldi, e arrivederci.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "No, non funzionerà. Puoi prendere il tuo carico o lasciarlo nella stiva, ma non ti darò nemmeno una moneta.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Aspetta, capitano. Voglio ringraziarti per il mio salvataggio. Sai, avevo quasi perso la speranza... Ecco, sono sicuro che troverai questo gingillo molto utile in molte situazioni difficili... Addio ora.";
				link.l1 = "Grazie. Non me l'aspettavo. È stato un piacere fare affari con te.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Aspetta... Ho appena pensato... Sai, la mia carriera è finita, non ho equipaggio e sono in esilio nella mia terra natale. Certamente avrai bisogno di uomini fidati con una mano ferma, che sappiano tenere la bocca chiusa. Per favore accettami nel tuo equipaggio, prometto che non te ne pentirai.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Onestamente, aspettavo il tuo consenso da un po'. Certo. Ci vediamo a bordo.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Mmm... sai, mi sembra che tu sia troppo intelligente per servire sotto qualcuno. Addio...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Ebbene, a quanto pare, oggi chiaramente non è il mio giorno fortunato... Va bene capitano, sguainiamo le nostre spade e finiamola con tutto questo una volta per tutte...";
			link.l1 = "Sono al vostro servizio...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Non sono affari tuoi. Ora dimmi, cosa stai fiutando qui? Non stai cercando un uomo che è appena stato arrestato?!";
				link.l1 = "Un uomo?! No...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Bene per te. Altrimenti finiresti anche tu in prigione, insieme a lui. Quindi non fare casino qui, marinaio. Sparisci!";
				link.l1 = "Sì, sarebbe meglio che me ne vada...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Bene! Dovremmo andare alla taverna da quel contrabbandiere ora. Non vorrei indugiare qui!";
				link.l1 = "Nessun problema con questo. Andiamo...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "Ehehe... Sembra, "+GetSexPhrase("compagno","ragazza")+", andrai all'inferno con lui molto presto... Ehi, compagno - squartiamoli entrambi!";
				link.l1 = "Porco sporco! Difenditi!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Grazie ancora una volta, "+PChar.name+". Addio...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Una ricompensa?! Certo. Ecco - prendi "+FindRussianMoneyString(iMoney)+" e arrivederci...";
				link.l1 = "Arrivederci...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Eh! Ci aspettate di credere a questa stronzata?! Ragazzi, prendete questi due corvi della forca!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Ufficiale, state facendo un grave errore cercando di trattenere due persone innocenti. Credetemi, non conosco quell'uomo e non mi potrebbe importare di meno di lui."+"Sono certo che il vostro comandante sarà piuttosto scontento di voi, se trattenete due cittadini rispettosi della legge...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Mmm... Sì, forse hai ragione. Al comandante non piacerà di certo questo. Sai che c'è - dimentichiamoci di questo piccolo incidente.";
				link.l1 = "Grazie, ufficiale, ci avete risparmiato tempo. Vorrei chiedervi di essere più attenti la prossima volta, sicuramente non vorreste essere degradati, vero?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "No, assolutamente no. In tal caso, per favore disperditi. Ci vediamo...";
				link.l1 = "Ecco meglio!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Eccellente! E ora puoi perderti!";
					link.l1 = "Cosa?! E che ne sarà dei soldi? Avevamo un accordo...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Grazie per la consegna. Ora puoi andartene... aspetta, sta arrivando qualcuno...";
						link.l1 = "Cosa?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Ottimo. Grazie per la consegna. Ecco, prendi "+FindRussianMoneyString(iMoney)". E ricorda che i contrabbandieri ricorderanno sempre le persone buone...";
					link.l1 = "Spero proprio di sì. Addio.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Ascolta... tra te e me non c'è stato alcun accordo. Richiedi i tuoi soldi a chiunque abbia stretto quel patto con te.";
				link.l1 = "Beh, certamente non è il mio giorno fortunato, cosa altro posso dire?! Va bene, ci vediamo...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"Risponderai per questo! Preparati a morire!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Hai osato sfidarmi, "+GetSexPhrase("moccioso","sporcizia")+"? Beh, sicuramente non hai idea di cosa sia buono per te. Ti sventrerò!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Mezzo migliaio di uomini! E un baule di un uomo morto! Hic!","Bevi! Hic! E il diavolo ha fatto fuori il - Hic! - resto!");
						link.l1 = "Ohh... Beh. Ciao, signore "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Bene, vediamo ora... Tre pezzi di tela da vele, assi per la pelle della nave, sostituzione dei puntelli e delle corde sulle sartie...";
							link.l1 = "Ciao, signore "+GetFullName(NPChar)+". Sono il capitano "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Lascia immediatamente la mia nave, ho molto da fare senza di te!","Hai ricevuto i tuoi libri, cosa vuoi ancora?!","Ho fatto tutto quello che volevi, cosa vuoi ancora da me?!");
							link.l1 = "Non agitarti così tanto o avrai un infarto!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, rum! Dammi del rum... Hic!","È passato un bel po'... hic... da quando mi sono ubriacato così...");
					link.l1 = "Sì, la tua stiva è piena... forse è il momento di dirigersi verso una caletta?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Per favore, prendi un posto, cap-hic-itano! Qual è il tuo veleno?","Prendi posto, cap! Cosa ti piacerebbe bere? Hic...");
					link.l1 = "Grazie, ma preferirei una bella conversazione con un uomo decente.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Stai cercando - hic! - di insultarmi?.. Non c'è un solo uomo decente in quella taverna! Hic! Solo banditi e tagliagole! Tutti estorsori, e quello... il primo tra loro! Il loro capobanda, una murena in gola!";
				link.l1 = "Intendevo te. Sei tu quello con cui voglio parlare. E chi è il capo dei banditi e perché dovrebbe...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Signora"+GetSexPhrase("ter","s")+"! Cara mia! Come ti chiamavi, ancora una volta? Ti rispetto! Nessuna anima ha finora chiamato un vecchio lupo di mare un uomo decente! Farei qualsiasi cosa per te! Ti darei tutti i miei soldi, fino all'ultimo peso!.. Ah, giusto, ho dimenticato. Non ho soldi. Non ho nemmeno più un centesimo. Quel bastardo, quel rackettaro mi ha preso l'ultimo rotolo, che gli imp di caricare i loro cannoni con le sue viscere all'inferno!";
				link.l1 = "Signor capitano? Sta bene? Si rende conto che delira? Quali pergamene?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "No, no! Questo vecchio cappello potrebbe essere ubriaco, ma mantiene ancora la sua saggezza. I libri e i rotolini mi sono stati dati da Padre "+PChar.GenQuest.ChurchQuest_1.ToName+", li stavo portando a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+". E la mattina sono andato alla chiesa locale e ho parlato di questi libri al prete locale. Naturalmente, lui voleva vederli, conosci la loro specie, sono semplicemente pazzi per la vita dei loro santi e tutte quelle cose. Così, ho mandato un mozzo a prendere il baule con loro. E mentre aspettavo, ho deciso di giocare un po'... e in qualche modo ho perso tutti i miei soldi. Tutto! Niente con cui pagare l'alcol! Così, il proprietario della taverna ha preso i libri in pegno, e poi gli ho dato anche i rotoli...";
				link.l1 = "Allora, hai venduto libri, i libri sacri che ti sono stati affidati dal prete  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Lo so, lo so... Brucerò all'inferno per l'eternità. Ora non posso mostrare il mio volto né al Padre, che mi ha dato quel compito, né a colui che stava consegnando i documenti, né al locale... Chi pregherà ora per la mia anima? E se mi scomunicano? Oh, guai a me... Ho bisogno di un drink... ";
				link.l1 = "Woah rilassati, non è così male. Le tue azioni erano scadenti e empie, eppure sono pronto ad aiutarti. Pagherò il tuo debito e comprerò questi manoscritti. Inoltre, dato che conosco già entrambi i preti menzionati, salperò direttamente verso  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" per consegnare i documenti lì. Affare?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Salvatore! Angelo di Dio... Certo, accetto! Ti darei tutto... tutto! Se solo potessi avere un altro drink...";
				link.l1 = "Immagino che tu ne abbia già abbastanza... Oh, non importa. Ti comprerò un altro rum dal barista.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...e le vele! Dobbiamo sostituire anche le vele!.. Oh, ciao. Per favore, non te la prendere, signore"+GetSexPhrase("ter","s")+" qualunque-tuo-nome-sia, ma adesso, come puoi vedere, sono piuttosto occupato, quindi se hai affari con me, per favore sbrigati.";
				link.l1 = "Per quanto ne so, padre "+PChar.GenQuest.ChurchQuest_1.ToName+" ti ha dato alcuni documenti sacri in "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". Hai promesso di consegnarli a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" perché stavi navigando in quella direzione comunque."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Stavo andando in quella direzione, fino a quando quella maledetta tempesta ha quasi distrutto la mia vecchia vasca, e sono rimasto bloccato qui per chissà quanto tempo! Questi truffatori al molo continuano a cercare di darmi tavole marce portate dalla marea per lo scafo della nave, e per le vele, un vecchio sacco di tela, su cui dormivano le loro nonne quando erano ancora giovani.";
				link.l1 = "Signore, la prossima volta ascolterò volentieri le tue magnifiche storie, ma ora vorrei saperne di più sul destino dei libri e manoscritti che hai ricevuto a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Quel")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Nessuno, mi senti? Nessuno osa incolparmi per il ritardo con la consegna di questi maledetti documenti!";
				link.l1 = "Oh, no, certo non intendevo quello. Volevo solo alleggerire il tuo fardello. Il fatto è, che "+PChar.GenQuest.ChurchQuest_1.ToName+" è molto preoccupato per i libri e i documenti da consegnare a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+". In realtà, sto per navigare lì proprio adesso.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Mi sembra, signorina"+GetSexPhrase("ter","s")+", che hai un consigliere spirituale in ogni porto. Anche se non è affar mio. Se ci tieni a quella roba, allora prendi i tuoi libri e sparisci! Buon viaggio!";
				link.l1 = "Grazie, signor capitano. Buona fortuna con le vostre riparazioni.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Non preoccuparti di quello, signorina"+GetSexPhrase("ter","s")+", e viaggia a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"leggermente, dal momento che sono stato io a impegnarmi a consegnare quei documenti, e sarò io a farlo ad ogni costo, in modo che nessuno gridi ad ogni angolo che il capitano "+NPChar.name+" non è rimasto fedele alla sua parola!";
				link.l1 = "Ma signor capitano, il punto in realtà è...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Infatti, il punto è che non ho affari con te. Il Santo Padre mi ha dato un compito, consegnare i libri a "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" e consegnali al prete locale. E non ti vedo lì. Per niente! Buona fortuna.";
//				link.l1 = "Bene, allora. Sei un uomo molto responsabile, anche se è il tuo unico merito. Buona fortuna a te, mio amico scortese";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Ne ho abbastanza del tuo comportamento insolente. La tua stupida bocca può spingere anche un angelo a fare violenza. Devo adempiere alla volontà del mio santo padre e userò la mia arma se necessario!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Silenzio, silenzio, capitano "+PChar.name+"! Che succede con te? Oh, capisco, vedo che se non porti questi documenti, tutti quei Santi Padri sarebbero piuttosto arrabbiati con te, per non parlare di nostro Padre in Cielo. Va bene, prendi i tuoi preziosi teologici e vai con la benedizione di Dio.";
				link.l1 = "Sono contento che non solo hai capito la mia posizione, ma hai anche ricordato il mio nome. Ti suggerisco di ricordarlo ogni volta che stai per fare qualcosa di sciocco.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Vattene...","Non disturbarmi!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"Non avresti dovuto dire questo! Ora dovrò mandarti dal Signore a pregare per il perdono dei miei peccati!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"Non avresti dovuto dire questo! Ora dovrò mandarti dal Signore a pregare per il perdono dei nostri peccati!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"Non avresti dovuto dire questo! Ora dovrò mandarti dal Signore a pregare per il perdono di tutti i nostri peccati!";
			}
			
				link.l1 = "Difficilmente, compagno. Ognuno risponderà di sé a Dio!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Ehi, perché bestemmi? E se avessi affari con te.";
				link.l1 = "Ecco una novità! Sai, ho brevi chiacchierate con gente come te!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Ebbene, non ho intenzione di fare lunghe chiacchierate con te, nemmeno. Ma, forse, saresti interessato a comprare un paio di cianfrusaglie per un buon prezzo?";
				link.l1 = "Sembro forse un maledetto ricettatore?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Piano, piano, non ci sono ladri tra noi! Questo vaso ci è stato dato per lavoro onesto! Guarda solo... oro puro, adornato di perle. Ma il punto è che non ne abbiamo bisogno. Quindi vogliamo solo venderlo e dividere i soldi.";
					link.l1 = "Lasciami dare un'occhiata più da vicino... Oh mio! Questo è il calice della comunione!!! Quindi, voi siete quei blasfemi che hanno saccheggiato la chiesa di "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Eccoti qua!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Taci, signorina"+GetSexPhrase("ter","s")+"ipocrita! Sai, siamo un po' a corto di soldi, quindi abbiamo deciso di vendere qualcosa. Guarda questo vaso... oro puro, adornato di perle. Prezzo speciale per te, diciamo, mille monete.";
				link.l1 = "Permettimi di dare un'occhiata più da vicino... Santo cielo! Questo è il calice dell'Eucaristia!!! Quindi, voi siete quei blasfemi che hanno saccheggiato la chiesa di "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! Eccoti qua!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Frena un po', signorina"+GetSexPhrase("ter","s")+"!.. Accidenti, ho detto a quel testone di non fare storie fino a quando non è il momento giusto...";
				link.l1 = "Cosa stai blaterando? Va bene, fai la tua scelta: o mi dai volontariamente il tuo bottino rubato, o chiamo le guardie.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Ascolta, "+GetSexPhrase("bravo uomo","giovane signora")+", non abbiamo bisogno di litigi, quindi risolviamo questa faccenda pacificamente. Devi crederci, in realtà non abbiamo saccheggiato quella chiesa, né abbiamo dei soldi. Sì, abbiamo ricevuto diversi pesos e quel gingillo d'oro per aver simulato la rapina. E questa coppa d'oro era l'unica cosa che ci era rimasta dopo aver pagato i contrabbandieri...";
				link.l1 = "Allora, stai cercando di dire che...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Quel maledetto prete ci ha assunti, è quello che sto dicendo! Ma perché ha dovuto mandarti da noi?.. Beh, siamo pari ora. Prendi questo vaso e mostralo a quel ipocrita, vedrai da solo che si contorcerà come un calamaro sulla secca!";
				link.l1 = "Dammi la coppa e sparisci, prima che cambi idea.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Parli in modo liscio, ma non sono così facile da ingannare. Se vuoi convincermi, allora convinci prima la mia lama.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"Non ho detto a quei straccioni: tieni le tue zampette avide e non prendere nulla dal prete tranne i soldi!";
			}
			else
			{
				dialog.text = RandSwear()+"Non ho detto a quegli insaziabili stracci: tenete le vostre zampette lontane e non prendete niente dal prete tranne i soldi!";
			}
			
					link.l1 = "Cosa stai blaterando? Bene, fai la tua scelta: o mi dai il tuo bottino rubato volentieri, o chiamo le guardie.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Faccio una scelta diversa, tu chiudi la tua bocca chiacchierona e dammi la tua borsa, e risparmio la tua vita.";
				link.l1 = "Vi aiuterò ad ottenere un'udienza con il nostro Signore ora!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Va bene, ti darò del denaro, ma solo di mia spontanea volontà, affinché tu e i tuoi amici possiate condurre una vita onesta e non dobbiate umiliarvi con la rapina.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Va bene, mettiamo da parte le nostre divergenze e torniamo all'inizio della nostra conversazione. Quindi, quanto volevi per quella cosa?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Non ho bisogno di altri problemi, neanche io, "+GetAddress_Form(pchar)+", ma ora il prezzo è salito. Per quella preziosa coppa avrò bisogno di tutto quello che hai con te.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Sei uno sporco avido! Ho solo "+FindRussianMoneyString(iMoney)+" con me. Prendilo e sparisci!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Sbagliata scelta, ratto avido. Non avrai alcun beneficio a mie spese!"+GetSexPhrase("Sono libero come il vento - ora qui, il giorno dopo là, oggi sono povero - domani sarò ricco...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Non stai cercando di dire che proprio oggi "+GetSexPhrase("sei povero","non hai soldi")+"?!";
				link.l1 = "Esattamente, mio avido amico, a tua grande delusione. E ora devo scusarmi, ho molto da fare.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Fermati! Stiamo per verificare, e se non hai detto la verità, metterò la tua lingua bugiarda dentro una colonia di formiche!";
				link.l1 = "Dopo aver detto questo, sei spacciato!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Oh, non c'è nulla da decidere. Possiamo decidere tutto da soli. Ma prenderemo la tua nave e usciremo da qui.";
			link.l1 = "C'è una condizione, prima dovrai prendermi la mia spada...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Ciao, capitano! A quanto pare, la Provvidenza stessa ti ha inviato per salvare "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" e i suoi ragazzi. Abbiamo un disperato bisogno qui."+"La nostra "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" naufragato nella tempesta sugli scogli locali, e le onde hanno portato a riva i superstiti dell'equipaggio."+"Per "+(5+hrand(7))+" settimane che scrutavamo l'orizzonte sperando di vedere la vela di una nave che sarebbe venuta a salvarci.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Sì, è un destino invidiabile. Ma tale è la sorte della vita dei marinai, chiunque potrebbe finire al tuo posto.","Capisco... Dio tiene ogni vita, è solo che è troppo occupato per ricordarsi di tutti."),RandPhraseSimple("Infatti. L'uomo propone, ma Dio dispone.","Sì, quella è stata sicuramente una sfortuna."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "È stato molto grave! Quel mascalzone "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" non potevo pensare ad una punizione diversa che lasciare "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" su un'isola disabitata, come un cagnaccio rognoso! "+"Sperava che il sole e la sete ci disseccassero come una sgombro secco su uno stand di un pescatore! Ma si sbagliava, perché la Provvidenza stessa era dalla nostra parte, poiché ci ha inviato te qui per salvarci...";
				link.l1 = RandPhraseSimple("Non così veloce, amico. Per quanto posso dire, siete uomini di una professione libera, e siete finiti qui non per caso.","Già si parla di salvezza? Per quanto ne capisco, sei qui per via di alcune realizzazioni speciali.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Capitano, per favore sii un'anima gentile e aiuta  "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" uomini indigenti. Sei la nostra unica speranza, a parte il nostro Signore più misericordioso.","Capitano, avreste armadietti liberi sulla vostra nave per "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" uomini indigenti?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... e dove vorresti che ti portassi?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Mi dispiace davvero, ma non c'è nemmeno un'amaca libera, per non parlare delle cabine. I marinai dormono sul ponte, non possono nemmeno avere un buon riposo notturno dopo un turno di guardia...","Mi dispiacerebbe davvero deluderti, ma la nave è sovraccarica, e la gente deve dormire con il cattivo tempo. Se ci fosse un'epidemia, perderei metà dell'equipaggio."),RandPhraseSimple("Mi dispiace davvero, ma non c'è assolutamente più posto per l'equipaggio sulla mia nave. Non posso prendere a bordo altri passeggeri.","Devo deluderti, ma la mia nave è sovraccarica di uomini dell'equipaggio. Temo l'epidemia..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Sei un marinaio esperto e dovresti sapere che la presenza di qualcuno che ha subito un naufragio è un segno molto cattivo. I miei marinai ti getteranno semplicemente fuori bordo.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Mmm... Sai, per varie ragioni preferiremmo rimanere il più lontano possibile dalle autorità... Per favore, consegnaci in una qualsiasi insenatura su un'isola abitata o nel Main, e poi saremo in grado di provvedere a noi stessi.";
			link.l1 = "Ebbene, ho abbastanza armadietti liberi e amache. Carica te stesso sulla barca.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Mmm... sfortuna... Ci aspettano battaglie e non so dove sarai più al sicuro, a bordo della mia nave o in questa accogliente baia.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "Oh, capitano! Questi sono i tempi in cui uno non può sentirsi al sicuro nemmeno in un letto con sua moglie, ah-ah, figuriamoci in mare... Guarda questi teppisti, ognuno di loro è pronto a combattere a mani nude contro i cannoni. Non bramano affatto sicurezza e comfort, lo puoi leggere sui loro volti!";
			link.l1 = "Sui loro volti, posso solo leggere la volontà di pugnalare il loro sciocco benefattore alle spalle.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... Questa, in realtà, è una buona idea. Dimmi amico, i tuoi teppisti sono disposti a servire nella mia ciurma?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Peccato, capitano... Vedo che non possiamo risolverlo in modo amichevole. Credo che dovrò ricordarti il codice del mare. E ricorda, quando si tratta di abbordaggio, non siamo secondi a nessuno...";
			link.l1 = "Ebbene, ora posso finalmente vederti per chi sei veramente...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Ma certo! Saranno felici di far parte della tua squadra d'abbordaggio! Nessuno li supererà in un combattimento, forse solo Davy Jones stesso! Ah-ah-ah!";
			link.l1 = "Bene, allora. Caricatevi sulle barche...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Grazie, capitano! Il caricamento non dovrebbe richiedere troppo tempo. Dio, come abbiamo pregato perché quel momento arrivasse!";
			link.l1 = "Molto bene, allora.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Perché indugi, capitano? Ordina di salpare.","Ci dispiace, capitano, ma dobbiamo prepararci per salpare.","Siamo così fortunati che tu abbia deciso di venire qui!");
			link.l1 = "Sbrigati. La nave non aspetterà nessuno.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Grazie, capitano. Infatti, abbiamo fatto bene a credere nella nostra fortuna... Per favore, accetta questa gemma, l'ho trovata in quella baia maledetta. Spero che ti porti fortuna.";
				link.l1 = "Non mi aspettavo un tale regalo.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Capitano, per favore, non pensare che siamo troppo impudenti, ma siamo davvero a corto di soldi. Sai, abbiamo perso tutto quello che avevamo. Potresti prestarci un paio di manciate di pesos? Ti ripagheremo di sicuro... quando si presenterà l'occasione...";
				link.l1 = "Caspita! Davvero, la sfacciataggine non conosce limiti. Beh, l'unica cosa che potrei fare per te ora dopo tutto quello che ho già fatto, sarebbe non raccontare alle autorità di te.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Non ci posso credere... E quanto vuoi?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Grazie, capitano.","Capitano, siamo così grati a te.","Pregheremo per te, capitano "+PChar.name+"!");
			link.l1 = "Buona fortuna a te. Addio...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Ehi, capitano... Sai, ci siamo trovati bene... Sarebbe davvero un peccato ucciderti...";
			link.l1 = "Potresti provare!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "Beh, diciamo, "+iMoney+" dei pesos a ciascuno di noi sarebbe bello... Ovviamente, se non pensi che questa compensazione per tutte le nostre sofferenze sia troppo piccola, he-he...";
			link.l1 = RandPhraseSimple("Al contrario, sono certo che sia decisamente troppo... Una forca al collo sarebbe la cosa migliore per ognuno di voi.","Ti impiccherò come scimmie sulle palme per questo denaro da solo!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Bene, prendilo. Spero di non doverti altro, giusto?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Che generosità! Francamente, pensavo che avessi già avuto l'opportunità di vedere che noi otteniamo sempre ciò che desideriamo. E questa volta non ci tireremo indietro, neanche...";
			link.l1 = "Potresti provare!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "Oh no, capitano, cosa stai dicendo?! Accenderemo sicuramente una candela nel tuo nome, se mai entreremo in una chiesa... ahah!";
			link.l1 = "Spero proprio di sì...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "Oh no, capitano, cosa stai dicendo?! Accenderemo sicuramente una candela nel tuo nome, se mai entreremo in una chiesa...ahah!";
				link.l1 = "Spero proprio di sì...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Ehi, capitano, sai, non è un gran problema. Io e i miei ragazzi siamo disposti a liberare una dozzina di amache sulla tua nave da coloro che le stanno attualmente occupando...";
				link.l1 = "Hmm... suona come una minaccia...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Beh, in realtà, è una minaccia. Ho bisogno della tua nave, e uscirò da questo posto, con o senza il tuo consenso!";
			link.l1 = "Ebbene, ora posso finalmente vederti per quello che sei realmente...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "La capisco, capitano. La capisco perfettamente... Chi vorrebbe accudire poveri pirati che chiedevano la forca?.. Ma... e se le offrissi uno scambio? Ci porti in una cala su un'isola abitata o nel continente, e le darò una mappa del tesoro per questo. Abbiamo un accordo?";
			link.l1 = "Mmm... E come puoi garantire che questa mappa non sia un falso?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ah, sono sicuro che la tua mappa costa tanto quanto il pezzo di carta su cui è stata disegnata...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Ebbene... Ci lasci senza scelta... Comunque, usciremo da questo posto, con o senza il tuo consenso!";
			link.l1 = "Ebbene, ora posso finalmente vederti per chi sei veramente...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "E come puoi garantire che non ci consegnerai alle autorità nel porto più vicino? Stiamo entrambi giocando senza vedere le carte dell'altro...";
			link.l1 = "Bene, abbiamo un accordo.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Grazie, capitano "+PChar.name+". Hai adempiuto"+GetSexPhrase("","")+" la tua promessa, è ora "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" per adempiere il mio. Non ho la mappa con me, ma ti dirò dove si trova il tesoro. Vai alla baia...";
			link.l1 = "Oh, quindi è così che la metti ora! Vedo che intendevi ingannarmi fin dall'inizio...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Ho capito subito che non potevi essere fidato...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Ecco cosa succede quando ti fidi di un pirata. Che razza di persone siete? Non c'è nulla di sacro per voi!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Non fare una scenata... Non sono un santo, ma mantengo la mia parola!";
			link.l1 = "E ti aspetti che ti creda di nuovo? Così che domani tutto l'arcipelago si prenderà gioco di me?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Mmm... A quanto pare, non ci sarà una risoluzione pacifica. Ma, Dio sa, non la volevo...";
			link.l1 = "Sguaina la tua spada, o ti schiaccerò come il ratto che sei!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "E cosa altro avrei potuto fare? Restare in quella pozza puzzolente con i miei ragazzi e marcire fino alla morte? Faresti meglio ad ascoltarmi..."+XI_ConvertString(sTitle+"Gen")+" capitano "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" c'è una cache dove tiene il suo bottino. Ma fai attenzione"+GetSexPhrase("","")+", lui visita spesso quel posto. Trovare la cache non sarà difficile, se mantieni la testa sulle spalle..."; // belamour gen
			link.l1 = "E ti aspetti che ti creda ancora una volta? Così che domani tutto l'arcipelago si prenderà gioco di me?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Va bene. Ma se mi prendi in giro ancora una volta, ti troverò.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Ascolta a "+sTemp+", lui sta parlando con senso.","Non essere arrabbiato con "+sTemp+", semplicemente non aveva altra scelta.","Grazie, capitano.");
			link.l1 = "Buona fortuna a te...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "E cosa altro avrei potuto fare? Restare in quella pozza puzzolente con i miei ragazzi e marcire fino alla morte? Faresti meglio ad ascoltarmi..."+XI_ConvertString(sTitle+"Gen")+" capitano "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" c'è una cache dove tiene il suo bottino. Ma fai attenzione, ci va spesso. Trovare la cache non sarà difficile, se mantieni la testa sulle spalle..."; // belamour gen
			link.l1 = "E ti aspetti che ti creda ancora una volta? Così che domani l'intero arcipelago si prenderà gioco di me?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Chi sei tu,"+GetSexPhrase(" compagno","ragazza")+"? E cosa ti ha portato in questo luogo deserto?";
			link.l1 = "Mi sono fermato per rifornire la mia scorta d'acqua fresca.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Sono qui per conto di "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Hai scelto un brutto posto per farlo... Va bene, prenditi il tuo tempo.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "E chi sei tu per dirmi cosa dovrei fare?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Dico a tutti cosa fare. E coloro che si credono troppo intelligenti saranno impiccati alla palma.";
			link.l1 = "Ti taglierò la lingua, canaglia.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "E perché non è venuto da solo?";
			link.l1 = "Non voleva, è rimasto a "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" e aspettando me."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Quel vecchio furfante! Cerca di fregarci ancora una volta, vero? Non può essere. Digli che può riscuotere i soldi solo insieme a noi!";
			link.l1 = "Mi ha detto di non tornare senza denaro e di non prendere nessuno a bordo...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Ebbene, se ti fidi tanto di lui, puoi rimanere qui. Ma noi prenderemo la tua nave, i tuoi soldi e ci dirigeremo verso "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+". Stiamo morendo dalla voglia di vedere la faccia di "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Se ti manca così tanto, puoi nuotare là... o puoi morire qui.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Sei una persona astuta. Ma permettimi di assicurarti che il nostro conflitto con il capitano "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" è puramente di natura ideologica. L'ho avvertito, che un giorno le sue sporche operazioni sarebbero state punite e ora io e il mio "+iBanditsCount+" i nostri amici soffrono a causa del nostro amore per Dio e la giustizia.";
			link.l1 = "Come mai... Scommetto che voi siete stati i veri istigatori dell'ammutinamento, e avete ottenuto quello che meritavate.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Certo... Sarebbe bello però sentire l'opinione del capitano "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" riguardo ai vostri disaccordi.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Capitano, perché vorresti offendere persone oneste con la tua diffidenza? Guarda solo i loro volti... pensi davvero che siano ammutinati? Sono umili quanto un uomo può essere... Ma non hanno eguali in una lotta per una giusta causa sotto un buon comando! Posso personalmente garantire per ognuno di loro.";
			link.l1 = "Bene, ma cosa dovrei fare con te adesso?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Qualunque cosa tu desideri. Sta a te, portaci in un insediamento o accettaci nella tua ciurma, mi sembri un buon capitano.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Bene, ti accoglierò nel mio equipaggio. Ma niente scherzi! Ho una disciplina rigorosa sulla mia nave!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Non ti porto da nessuna parte. Ho già abbastanza teppisti nella mia ciurma.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Bene, sali sulla barca, ti porterò da qualche parte.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Lo giuro, capitano, non te ne pentirai.","Hai fatto la scelta giusta, capitano.","Capitano, sii certo che sei stato fortunato tanto quanto noi!");
			link.l1 = RandPhraseSimple("Spero proprio di sì.","Sbrigati. La nave non aspetterà nessuno.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "Questo può essere facilmente organizzato. Lui naviga su  "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" e si occupa di commercio di schiavi... Facciamo così: se lo troviamo, tu prendi il carico e noi prendiamo la nave. Ah, e puoi anche chiedergli se sa qualcosa su "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". Spero che non si caghi addosso quando sente quel nome, perché è la mia nave..."; // belamour gen
			link.l1 = "Bene, abbiamo un accordo.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Cosa diavolo vuoi da me?";
			link.l1 = "Sono venuto a salutare a nome di "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+". Immagino che tu lo conosca?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Peccato che non abbia strangolato quel mascalzone prima. Beh, allora credo che sia giunto il momento di pagare per la mia benevolenza...";
			link.l1 = "Infatti... E il tempo è proprio scaduto...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Ottimo lavoro, capitano! Tutto come abbiamo concordato, quindi? Noi prendiamo la nave e tu prendi il carico?";
			link.l1 = "Certo. Prendi la nave e fai buon uso di essa.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Ti saluto, capitano "+PChar.name+".";
			link.l1 = "Allora, come ti piace la tua nave?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Eh... sta cigolando e scricchiolando, proprio come me. Penso che entrambi non abbiamo molto tempo per navigare i mari aperti...";
			link.l1 = "Buona fortuna, allora...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Perché hai affondato la mia nave?! Ti ricordi del nostro accordo?";
			link.l1 = "Cosa, non volevo che mi affondasse al posto suo. Non vedi che ce l'ho fatta a malapena?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Chi lotta così? Hai perso una tale nave! Che diavolo! Che tipo di bambino come te sta persino facendo qui?";
				link.l1 = "Ti taglierò la lingua, cane.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Chi lotta così? Hai perso una nave del genere! Hai idea di quanto mi sia costata?"+FindRussianMoneyString(iMoney)+"! Ora mi devi...";
				link.l1 = "Non sarebbe troppo per te? Non dimenticare che ti ho già fatto un favore.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Maledetto tu e quella tua dannata nave! Prendi i tuoi soldi e non ricascare mai più sotto il mio occhio!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "E a che mi serve quel favore adesso?! Se il capitano "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" è ora sul fondo del mare con la mia nave! Ora non ottengo né la mia quota, né la mia nave indietro! Che destino, morire nel rigagnolo, come un vagabondo!!!";
			link.l1 = "Ma perché? Posso organizzare un funerale spettacolare per te. Proprio qui, se ti va bene...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Pensavo che potremmo... raggiungere un accordo, forse? Se ci fai un favore, te lo ricambieremo, he-he.";
			link.l1 = "Un favore? E qual è l'accordo e cosa offri in cambio?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = " Il nostro capitano "+PChar.GenQuest.JusticeOnSale.SmugglerName+" è stato preso dalla pattuglia locale di "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+". Lo hanno imprigionato ma non hanno abbastanza prove per impiccarlo. Non possiamo tirarlo fuori noi stessi\n"+"Sei un uomo rispettato. La gente ti conosce. Forse, potresti negoziare, pagare una cauzione o semplicemente comprarlo? Fidati di noi, lasceremo l'isola non appena avremo il nostro uomo, quindi la tua reputazione non soffrirà!"; // belamour gen
			link.l1 = "Diciamo che posso aiutarti. Ma che ne è del mio pagamento?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Vai all'inferno, prole diabolica! Non voglio avere a che fare con te!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Desideri diversi amuleti e talismani indiani? Sono piuttosto rari... O preferisci contanti sul momento? Diversi migliaia di pesos, dico?";
			link.l1 = "Vai all'inferno, prole del diavolo! Non ho niente a che fare con te!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Sono interessato ai monili indiani. Credo che accetterò.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "I contanti sono il miglior amico di un marinaio. I soldi non hanno odore, come tutti sappiamo. Sono d'accordo.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Grazie, cap. Ti compenseremo la somma della cauzione oltre alla tua ricompensa. Immagino che dovresti parlare con il comandante del nostro capitano. Forse, sarai in grado di persuaderlo. Una volta tirato fuori, vieni a "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", è lì che la nostra nave ha gettato l'ancora - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"'. Ti aspetteremo sulla riva."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Grazie, cap. Ti compenseremo la somma della cauzione oltre alla tua ricompensa. Immagino che dovresti parlare con il comandante riguardo al nostro capitano. Forse, riuscirai a persuaderlo. Una volta che lo avrai tirato fuori, vieni da "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Quello")+", è lì che la nostra nave ha gettato l'ancora - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+". Ti aspetteremo sulla riva."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Siamo qui, capitano! Hai fatto un ottimo lavoro ingannando questi burocrati panciuti! Ecco la tua ricompensa. Ragazzi, andate a prendere gli oggetti!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Siamo qui, capitano! Hai fatto un grande lavoro ingannando questi burocrati panciuti! Ecco la tua ricompensa. Ragazzi, prendete il baule!";
				}
				
				link.l1 = "Dammi la mia parte e sparisci!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Siamo arrivati, capitano! Vedo che hai organizzato tutto molto bene. Ma vedi... non abbiamo bisogno di testimoni, quindi... Ringraziamo il capitano, ragazzi!";
				link.l1 = RandSwear()+"Avrei dovuto spararti proprio quando ti ho incontrato!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Chi sei tu? E perché stai irrompendo nella mia stanza?","Caspita. Chi sei? Questa è la mia stanza, ovviamente, ma non mi dispiace una compagnia del genere. È una consegna d'amore?")+"";
			link.l1 = ""+GetSexPhrase("Non è più tua. L'oste ha affittato la stanza a me, e dato che non stai pagando per essa, stai per uscire da qui. Ora possiamo farlo nel modo facile o nel modo difficile. La scelta è tua.","Stai sognando. Nel nostro caso, si tratta di pulire. Quindi pulisci questo posto da te stesso. Questa è la mia stanza ora, dato che a differenza di te, io pago sempre gli osti.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("Credo di aver sentito parlare di te. Va bene, hai vinto, me ne andrò, voglio ancora vivere...","Mmm, ho sentito molto parlare di te. Immagino che non sia solo la tua lingua ad essere affilata. Va bene, non arrabbiarti, la stanza è tua.")+"";
				link.l1 = ""+GetSexPhrase("Hai preso una buona decisione.","Bravo ragazzo.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("È così, eh? Beh, scelgo la strada difficile.","Maledetta! Volevo comportarmi bene con te...")+"";
			link.l1 = ""+GetSexPhrase("Come desideri...","E tu lo chiami 'bene'? Mi fai pena. Anche se, forse no.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Bene, va bene, basta! Non uccidermi. Me ne vado.","Fermati! Cosa dovremmo fare ora, ucciderci a vicenda per questa stanza?! Ingoia tutto, è tutto tuo. Puzzolente...")+"";
			link.l1 = ""+GetSexPhrase("Decisione giusta. Un'altra volta, pensa con la tua testa: non tutti sono gentili come me, possono uccidere senza volerlo.","Uomini.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("Allora, mi hai sfrattato? Vattene da qui prima che ti taglio.","Allora tutto quello che sai fare è solo chiacchierare. Sii grato che sono ancora di buon umore, altrimenti avrei fatto qualcosa di ancora peggio a te. Fuori di qui!")+"";
			link.l1 = ""+GetSexPhrase("Maledizione...","Maledizione, ti ho sottovalutato... Va bene, va bene, me ne vado adesso.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ah?.. Vattene, pivello, non bevo.... hic!.. con nessuno.";
			link.l1 = "Ti colpirò così forte adesso che non berrai per un'altra settimana.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "Cosa?! Sai con chi stai parlando? Sono un marinaio della nave '"+pchar.ship.name+"'! Devo solo dire al capitano, e non avrai nemmeno il tempo di uscire dalla città! Vattene da qui mentre sei ancora intero."; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Capitano?..";
			link.l1 = "Farai pulizia del ponte per un mese.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Mi dispiace, capitano!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Saluti capitano! So che sei il capitano, sì.";
			link.l1 = "Saluti. Come sai che sono il capitano?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ah, sono un vecchio lupo di mare, navigo per i mari da più di un decennio. Mi occupavo principalmente di navigazione: ho navigato in calma, in tempesta, su un goletta, e persino su una nave da guerra. È vero, il mese scorso sono stato ferito dopo una dura battaglia, c'era una forte tempesta e nessuno osava salire sulla vela così ho dovuto farlo io, ma ho pagato un prezzo per questo, per fortuna mi sono solo storto la caviglia e non ho potuto camminare per alcune settimane. Così mi hanno mandato a terra. Ora sto meglio e sto seduto qui, aspettando un'occasione.";
			link.l1 = "Interessante. Non mi dispiacerebbe un esperto in materia. Ti piacerebbe unirti alla mia squadra?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "Perché no? Mi manca già il ponte della nave e il rumore delle vele gonfie di vento fresco. Potrei anche allenare la tua squadra, se necessario. Ma ti chiederò subito mille pesos, altrimenti le mie tasche sono già vuote. Poi di nuovo, come il resto della squadra. Sono una persona onesta.";
			link.l1 = "No, probabilmente rifiuterò. Se tutti i marinai vengono pagati mille pesos per l'assunzione, andrò in rovina. Non incolparmi.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Affare fatto. Non mi dispiace mille pesos per un bravo specialista. Aspetta... ecco qui. E ti aspetto sulla nave.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ah, sono un lupo di mare esperto, ho navigato il mare per più di un decennio. Soprattutto stavo vicino ai cannoni: ho sparato con falconetti, carronate, culverine, saker... ho servito su un goletta, e addirittura su una nave da guerra. È vero, il mese scorso sono stato ferito dopo una dura battaglia, una scheggia di mitraglia mi ha colpito, niente di serio solo un graffio sulla mia gamba, quindi mi hanno mandato a riva. Ora sto meglio e sono qui seduto, aspettando un'opportunità.";
			link.l1 = "Interessante. Non mi dispiacerebbe un esperto in materia. Vorresti unirti alla mia squadra?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Perché no? Mi manca già la santabarbara, l'odore della polvere da sparo che brucia e il rombo delle salve di cannoni. Potrei anche allenare la tua squadra, se necessario. Ma ti chiederò subito mille pesos, altrimenti le mie tasche sono già vuote. Poi, come il resto della squadra sono un uomo onesto.";
			link.l1 = "No, probabilmente rifiuterò. Se tutti i marinai vengono pagati mille pesos per l'assunzione, andrò in rovina. Non incolparmi.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Affare fatto. Non mi dispiace mille pesos per un buon specialista. Aspetta... ecco. E ti aspetto sulla nave.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ah, sono un vecchio lupo di mare, navigo per mare da più di un decennio. Ho combattuto principalmente in battaglie di abbordaggio: ho combattuto contro pirati e armate regolari, so come maneggiare ogni tipo di arma, sono stato su una goletta e persino su una nave da guerra. È vero, il mese scorso sono stato ferito dopo una dura battaglia, era solo un piccolo graffio di sciabola sulla mia schiena, il codardo non poteva affrontarmi, ma l'ho ucciso in cambio, oh avresti dovuto vedere le loro facce quando hanno visto il graffio ah-ah. Così, mi hanno mandato a terra. Ora sto meglio e sto qui aspettando un'opportunità.";
			link.l1 = "Interessante. Non mi dispiacerebbe un esperto in questa materia. Vorresti unirti alla mia squadra?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Perché no? Mi manca già il suono delle sciabole, il crepitio delle navi che si scontrano ai lati, e l'adrenalina della battaglia. Potrei anche allenare la tua squadra, se necessario. Ma ti chiederò subito mille pesos, altrimenti le mie tasche sono già vuote. Poi, come il resto della squadra sono un uomo onesto.";
			link.l1 = "No, probabilmente rifiuterò. Se tutti i marinai vengono pagati mille pesos per l'assunzione, finirò in bancarotta. Non incolpare.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Affare fatto. Non mi dispiace mille pesos per un buon specialista. Aspetta... ecco. E ti aspetto sulla nave.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Buona fortuna in mare, capitano!";
			link.l1 = "Anche tu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "C-chi sei tu?";
			link.l1 = "Sono il capitano "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Scusa, amico, sono di fretta.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "Capitano? .. hic! C-capitano ... accompagnami alla t-taverna ... hic! .. eh? Per favore. Sembra ... Mi sono p-perso in questa c-colonia, sì ... hic! ..";
			link.l1 = "Lasciami in pace, non ho tempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bene, andiamo. Non sembri in grado di arrivarci da solo.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Solo... hic!.. lentamente, per favore. Non sono... hic!.. in grado... di stare... in piedi...";
			link.l1 = "Bene, andiamo, lentamente.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Capitano?.. hic!.. C-capitano... aiutami!";
			link.l1 = "Lasciami in pace, non ho tempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Cosa c'è che non va in te?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Lì... in taverna... hic!.. il Baro!";
			link.l1 = "Ebbene, qual è il problema? In qualsiasi taverna di qualsiasi colonia ci sono imbroglioni, come sporcizia.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "C-capitano, tu... non capisci... hic!... Mi ha lasciato... senza un solo peso! Hic!.. E poi... mi ha cacciato via... hic!..";
			link.l1 = "Allora, cosa vuoi da me ora?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Vieni con me... hic!... Affrontalo! F-fallo... hic!.. restituirmi i miei soldi! hic!..";
			link.l1 = "Non devi essere un baro per battere una persona ubriaca al tavolo. Bevi meno la prossima volta.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Ebbene, perché mi serve questo, eh? .. Va bene, andiamo, diamo un'occhiata al tuo baro.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Solo... hic!.. lentamente, per favore. Non... hic!.. sono... capace di...stare in piedi...";
			link.l1 = "Bene, procediamo lentamente.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "C-capitano... hic!.. grazie mille... mi hai aiutato! Io... ecco a te... hic!.. È per te.";
			link.l1 = "Su, non importa... Non bere più così. O almeno non cercare avventure.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "C-capitano!.. Il... Hic!.. Baro!..";
				link.l1 = "Chi, io? Baro?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "Eccolo là, capitano! Hic!.. S-seduto al tavolo...";
				link.l1 = "Avanti...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "No... hic!... Più forte!... È sparito!...";
			link.l1 = "Ebbene, se n'è andato, quindi non ha aspettato te.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "E cosa c'è... d-dopo? Hic!..";
			link.l1 = "Ebbene, non c'è nulla che tu possa fare ora. Di sicuro non andrò a cercarlo di notte in tutta la colonia. Non bere più così. O almeno non scommettere mentre sei ubriaco.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Propongo una partita a dadi. Sei dentro?";
			link.l1 = "Assolutamente no. Sono il capitano della nave e non gioco con i baro. Ma posso facilmente spezzarti le costole se non restituisci i soldi a quel bravo uomo laggiù.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Con i baro?! Sono io un baro? A chi devo restituire i soldi, a quel ubriacone?! Mi offendi, capitano...";
			link.l1 = "Posso offendere di più. Restituisci i soldi.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Sì, non sono un baro! Sono un giocatore onesto. Vince la fortuna, e il tuo amico è stato solo sfortunato, tutto qui.";
			link.l1 = "Fortuna, eh? Dammi i tuoi dadi, e vedremo quanto fortunato sarà il risultato.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "Va bene, va bene, calmati, capitano. Beh, ho battuto l'ubriaco, e ho barato un po', e questo è ciò che fa ogni secondo giocatore. Ecco i suoi soldi.";
				link.l1 = "Ecco meglio. E, spero tu capisca che se il mio amico dirà ora che questa non è l'intera somma, allora tornerò da te?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Sì per favore, ecco i miei dadi. Entrambi i set. Controlla. Non ho nulla da nascondere.";
				link.l1 = "Allora... Coppia... Nulla... Coppia... Full... Nulla... Nulla... Due Coppie... Tris... Nulla... Coppia...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Sì per favore, ecco i miei dadi. Entrambi i set. Controlla. Non ho nulla da nascondere.";
				link.l1 = "Allora... Quattro di un tipo... Quattro di un tipo... Full... Full... Quattro di un tipo... Poker... Full... Poker... Quattro di un tipo... Full... Hmm, e come me lo spiegherai questo?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Capisco tutto, ecco l'intera somma. Buona fortuna a te e al tuo amico.";
			link.l1 = "Anche tu.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "Ma... lui n-non voleva ammetterlo! Hic!..";
			link.l1 = "Sì, ho cercato di evitarlo. Ecco, tieni i tuoi soldi.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "C-capitano... hic!.. grazie mille... mi hai aiutato! Io...'vomita da parte'... ecco a te... hic!.. È per te.";
			link.l1 = "Avanti, ugh... lascia perdere... Non bere più così. O almeno non giocare d'azzardo quando sei ubriaco.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "Ebbene? Convinto?";
			link.l1 = "Mmm, sembra davvero un dado ordinario ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Te l'ho detto. E il tuo amico è solo ubriaco. Non ha nemmeno ammesso la sua sconfitta, quindi ti ha portato qui.";
			link.l1 = "Bene, mi dispiace per l'incidente. Buona fortuna.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Allora... hic!.. che cos'è?.. Lui... hic!.. non è un f-furfante?..";
			link.l1 = "Beh, sembra che abbia giocato onestamente.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "E cosa c'è... d-dopo? Hic!..";
			link.l1 = "Ebbene, non c'è niente che tu possa fare ora. Ti ha davvero battuto onestamente. Non bere più così. O almeno non giocare d'azzardo quando sei ubriaco.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Fortuna. Sei solo stato fortunato, ecco tutto. La fortuna è una signora capricciosa.";
			link.l1 = "Hmm, davvero. Bene, allora giochiamo, ma tieni a mente che gioco con questi dadi!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Queste?.. Cioè... No, non voglio giocare con te! Mi hai insultato. E comunque, sono al verde...";
			link.l1 = "Forse vuoi che racconti a tutti in questa taverna dei tuoi dadi? O forse mostrarli? E poi spiega loro della fortuna. Che ne pensi?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "Cosa?! Chi ti credi di essere?! Stai cercando di ricattarmi?! Ti farò un paio di buchi adesso, se non te ne vai!";
			link.l1 = "Preferirei restare qui e mostrare a tutti i tuoi dadi.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Ebbene, vieni qui, carogna!";
			link.l1 = "Non perdere i pantaloni.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "C-capitano?.. Tu... hic!.. sei entrato in una lotta?.. E questo... hic!.. è più... acuto?";
			link.l1 = "Ha preso un pugno lui stesso. Non giocherà più con nessun altro.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Ma... lui n-non voleva ammetterlo! Hic!..";
			link.l1 = "Sì, ha cercato di evitarlo. Semplicemente non aveva i tuoi soldi. Probabilmente li ha spesi.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Sì, ha cercato di evitarlo. Ecco, i tuoi soldi.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "E cosa... c'è dopo? Hic!..";
			link.l1 = "Ebbene, non c'è niente che tu possa fare ora. Ti ha battuto onestamente. Non bere più in questo modo. O almeno non giocare d'azzardo quando sei ubriaco.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "C-capitano... hic!.. grazie mille... mi hai aiutato! Io...'vomita da parte'... ecco a te... hic!.. È per te.";
			link.l1 = "Andiamo, ugh... lascia perdere... Non bere più in questo modo. O almeno non giocare d'azzardo quando sei ubriaco.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Capitano?.. hic!.. C-capitano... accompagnami al p-p-pontile... hic!.. huh? Per favore. Io... hic!.. h-ho bisogno di andare... alla nave... Il nocchiero... maledirà... hic!.. se sono in r-ritardo...";
			link.l1 = "Lasciami in pace, non ho tempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bene, andiamo. Non sembri in grado di arrivarci da solo";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Solo... hic!.. lentamente, p-per favore. Non sono... hic!.. in grado... di stare... in piedi...";
			link.l1 = "Bene, procediamo lentamente.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "C-capitano... hic!.. grazie mille... mi hai aiutato! Io...'vomita da parte'... ecco a te... hic!.. È per te.";
			link.l1 = "Andiamo, ugh... lascia perdere... Non bere così tanto. O almeno non cercare avventure.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "C-capitano!.. Nave!";
			link.l1 = "Che 'nave'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "N-nave!.. Dove è?.. hic!..";
			link.l1 = "Ovviamente se n'è andato. Devi bere di meno nelle taverne. L'intera nave non aspetterà un marinaio ubriaco.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Ma io... hic!... non sono ubriaco... quasi... forse...";
			link.l1 = "Ah, sì, infatti. Buona fortuna.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Aspetta, c-capitano! P-portami... hic!.. sulla tua n-nave! Non b-berrò più... hic!..";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Bene, cosa puoi fare al riguardo. Ma devi andare subito sulla nave. E Dio non voglia, se ti vedo da qualche parte ubriaco, pulirai il ponte fino alla prossima sosta al porto.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Così che tu possa ubriacarti con il mio stipendio, e poi io ti cerchi in tutte le taverne e portoni della colonia? No, non ho bisogno di tale felicità.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Sì, c-capitano!.. hic!..";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Capitano?.. hic!.. Tu sei... un topo t-terra... hic!.. non un capitano!..";
				link.l1 = "Ho tagliato a pezzi centinaia di persone come te nelle lotte di imbarco, quindi vattene, ubriaco.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Capitano... hic!.. C-capitano di quella t-trogha nella razzia?.. hic!..";
				link.l1 = "Se vedi questa scia all'orizzonte quando sei in mare, è meglio tuffarti immediatamente nell'acqua: con gli squali avrai più possibilità di sopravvivere che contro la mia nave. Ora vattene!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Capitano?.. hic!.. Sei un bevitore di latte, non un capitano!.. Tua m-madre era ancora una ragazza... hic!.. quando navigavo il mare...";
				link.l1 = "Ma tua madre sarebbe probabilmente felice di sapere che un bambino come me è diventato un capitano, e tu sei rimasto un marinaio ubriaco, buono solo per strofinare i ponti.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Capitano?.. Attento... hic!.. capitano... Ti spengo i denti... hic!.. non avrai il tempo di battere ciglio!..";
				link.l1 = "Il rinculo ucciderà. Vattene! Sfondami i denti se ne hai il coraggio...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Capitano?.. Sembra che... hic!.. s-sia una specie di straccione...";
				link.l1 = "Sembra che tu non ti sia ancora guardato allo specchio...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "C-capitano?.. Non avrei... hic!.. nemmeno accettato di s-servire... sulla tua nave... hic!..";
				link.l1 = "E nessuno ti ha offerto di andare sulla mia nave perché accettassi. Togliti dalla mia strada.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hic!..";
			link.l1 = "Vai a dormire.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hic!.. Sì... ancora lontano?..";
			link.l1 = "Siamo vicini, sii paziente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "C-chi... hic!.. sei tu?..";
			link.l1 = "Sono il capitano "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Scusa, amico, sono di fretta.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Capitano?.. hic!.. C-capitano... aiutami! Io... intendo... hic!.. il mio amico... ha davvero bisogno del tuo a-aiuto! Per favore.";
			link.l1 = "Non intendo risolvere i problemi di ogni ubriacone che incontro nel bel mezzo della notte..";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bene, dimmi cosa è successo al tuo amico lì.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Il mio amico ... lui, in generale ... si è ubriacato. Proprio in generale ... hic! .. si è ubriacato ...";
			link.l1 = "Certo, ho sobriato i marinai che bevevano durante il servizio, ma con metodi piuttosto radicali. Non credo che il tuo amico ne abbia bisogno.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "No! Lui... lui è con la g-guardia! Ha lit...litigato con lui. E si è messo a combattere. E lui... hic!.. è stato portato in prigione... è solo ubr... ubriaco!";
			link.l1 = "E cosa vuoi da me adesso? Lui stesso è da biasimare: dovrebbe bere di meno. O almeno non cercare avventure da solo...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Parla con il carceriere, cap ... hic! .. capitano! Lui lo lascerà andare... lascialo andare! Hmm... eccolo qui... hic!.. che fortuna hai... Il mio amico appena... ha discusso... beh... e voleva colpirmi in faccia... ma... hic!.. non ha preso l'arma...";
			link.l1 = "Ora non ho altro da fare, se non tirare fuori dall'ergastolo ubriaconi notturni che hanno avuto una rissa con le guardie. No, lascialo seduto per qualche giorno. Forse la prossima volta ci penserai.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Sì, al diavolo con te. Va bene, parlerò con il carceriere.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Non sono sicuro che al carceriere piacerebbe il mio accento. Lo riporterebbe solo più tardi al governatore. Quindi vai avanti senza di me.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Temo, amico, che la strada per le casematte locali sia bloccata per me. Il custode tiene il mio ritratto come un'icona, e non ho intenzione di sistemarmi in questi loro appartamenti ospitali. Quindi mi dispiace, ma non posso aiutarti.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "G-grazie... capitano. E anche per il mio a-amico. E-ecco... è per te.";
			link.l1 = "La prossima volta, tieni d'occhio il tuo amico quando si ubriaca e decide di andare a combattere con le guardie. Non tutte le notti i capitani camminano per le strade, pronti a negoziare con il custode per qualche ubriacone. Buona fortuna.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Oh!.. Quindi so come... hic!.. liberare il mio... a-amico... hic!.. Guardie! Uno s-spia in città!.. hic!..";
				link.l1 = "Hai scelto una pessima opzione per liberare il tuo amico.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ah, s-straniero ... hic! .. Tu... avrai problemi ... hic! .. Va bene... Ho qui ... hic! .. tutto sotto controllo.";
				link.l1 = "Certo. Se succede qualcosa, verrò da te immediatamente.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... quindi tu ... hic! .. Sei un criminale! Guardie!";
				link.l1 = "Ah, quindi ora parli così!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Oh, come ... hic! .. scusa. E se ... mi lasci ... negoziare per te con ... hic! .. il custode, e tu ... hic! .. per il mio amico?..";
				link.l1 = "No, non hai bisogno di negoziare per me, grazie. Buona fortuna.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "C-chi... hic!.. sei tu?...";
			link.l1 = "Sono il capitano "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Scusa, compagno, ho fretta.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "Capitano?.. hic!.. C-capitano... ascolta, accompagnami alla grotta vicino alla città... hic!.. eh? P-per favore.";
			link.l1 = "Alla grotta? Non capisco. Perché stai andando alla grotta? E perché hai bisogno di me?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Vedi... c-capitano... hic!.. Ho finito i s-soldi per i drink... E in... hic!.. in una grotta ho... un nascondiglio, quindi... hic! .. Ma io... è... Ho paura di andare da solo attraverso la g... g... giungla... hic!.. di notte... Quindi...";
			link.l1 = "Lasciami stare, non ho tempo!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Bene, andiamo. Non sembri essere in grado di arrivarci da solo";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Solo... hic!.. lentamente, per favore. Io... hic!.. non... riesco a...stare in piedi...";
			link.l1 = "Bene, andiamo lentamente.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "C-capitano... hic!.. grazie mille... mi hai aiutato! Io... ecco a te... hic!.. È per te.";
				link.l1 = "Avanti, ugh... lascia perdere... Non bere più così.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Eccellente, capitano! Sono contento che tu abbia accettato.";
				link.l1 = "Ebbene, dov'è il tuo nascondiglio? Aspetta un minuto, sembra che non sei ubriaco.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Sì, non ho bevuto molto, non preoccuparti per me. E riguardo al nascondiglio ... Ragazzi!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Ragazzi, ho portato qui un nascondiglio. Dovete aprirlo. A meno che, ovviamente, questo nascondiglio si apra da solo, in un buon senso. Capitano, che ne pensi?";
			link.l1 = LinkRandPhrase("Credo sarebbe meglio se ti ubriacassi fino a perdere la memoria. Almeno resteresti in vita. E ora c'è solo una strada...","Penso che tu non sia molto bravo con la tua testa, visto che hai deciso di derubare il capitano di una nave da guerra...","Penso che probabilmente sei stanco di vivere, visto che hai deciso di provare questo...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Bene, immagino sia meglio lasciare in buoni termini. E quanti ne hai bisogno?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Allora, non apriremo la scorta in un modo lecito?";
			link.l1 = "Temerei che quella fosse l'ultima scorta della tua vita.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "Oh, non siamo avidi. Solo "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "Temerei che fosse l'ultima scorta della tua vita.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Bene, fai come vuoi. Non aiuterò mai più un ubriacone...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Capitano, mi sorprende la tua generosità. Vuoi condividere di più con noi?";
			link.l1 = "Ti ho già dato tutto. Me ne vado...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "C-chi... hic!.. sei tu?...";
			link.l1 = "Sono il capitano "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Scusa, compagno, ho fretta.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Capitano?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... Mi s-scuso... hic!.. per il mio... c-condizione. Vorresti unirti a m-me? hic!.. P-per favore."; 
			link.l1 = "Mi dispiace, "+GetAddress_Form(NPChar)+", ma sono occupato."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Unirti? Mi dispiace, ma oggi non bevo.."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Oh, non hai bisogno... hic!.. di b-bevere! Ecco una cosa... Beh... Ho bevuto con un mio amico... Quindi... Sono già brillo... capisci?";
			link.l1 = "Bene. Quindi, hai bisogno di aiuto per smettere di bere?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Non proprio! Sto bene. Ora voglio g-giocare... a carte, in generale voglio giocare... hic!.. Ma non per miserabili... p-pesos... con questi straccioni in... hic!.. t-taverna... Ma con un vero nobile! hic!.. Per vere scommesse!.."; 
			link.l1 = "Mi dispiace, "+GetAddress_Form(NPChar)+", che posso dire... Non sono un fan del gioco d'azzardo. È necessario pagare gli stipendi ai marinai, mantenere la nave, sai..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Mmm, va bene, giochiamo. Andiamo alla taverna?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Bene! Solo... hic!.. lentamente, per favore. Io... hic!.. non... riesco... a...stare in piedi..."; 
			link.l1 = "Bene, andiamo lentamente."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "P-per quel tavolo... hic!.. andiamo!"; 
			link.l1 = "Bene, andiamo."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Non hai... idea, c-capitano, come... hic!.. come sono felice di incontrare un vero nobile! hic!.. In questa selvaggia... solitamente solo... hic!.. s-scartoffie..."; 
			link.l1 = "Sì, è dimezzato nelle colonie locali. Allora, giochiamo?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Sì, giochiamo! hic!.. Quali scommesse?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "Giochiamo per 1000 pesos."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Giochiamo per 2000 pesos."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Uh, mi dispiace, sembra che la mia tasca sia vuota al momento..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "C-che?.. Tu hai... hic!.. nessun soldo per giocare... con me?.."; 
			link.l1 = "Ebbene, succede. Giocheremo la prossima volta, non preoccuparti."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hic!.. Mi sono divertito un mondo, c-capitano! hic!.."; 
			link.l1 = "Sono d'accordo con te. Almeno prenditi una pausa dagli affari."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hic!.. Mi sono divertito alla grande, c-capitano! hic!.."; 
			link.l1 = "Sono d'accordo con te. Almeno prenditi una pausa dagli affari."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "A volte devi solo... hic!.. p-passare del tempo con una bella... hic!.. compagnia. Grazie mille... hic!.. per la tua compagnia!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Sì, ho appena perso in frantumi. E come è successo che hai vinto anche in quei casi in cui avevo tutte le possibilità di vincere?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Reciprocamente, grazie per il gioco e per la conversazione."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "A volte hai solo bisogno di... hic!.. p-passare del tempo con una bella... hic!.. compagnia. Grazie mille... hic!.. per la tua compagnia!"; 
			link.l1 = "Reciprocamente, ti ringrazio per il gioco e per la conversazione."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Solo fortuna, c-capitano... hic!.."; 
			link.l1 = "Non sembra solo fortuna...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "A cosa stai alludendo? Vuoi dire che ho giocato disonestamente? Hai visto tutto tu stesso, abbiamo preso le carte dallo stesso mazzo!"; 
			link.l1 = "Sì, ho visto. E ho notato che un minuto fa la tua lingua a malapena si muoveva, e ora parli come se non fossi ubriaco."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Ah, maledizione! E mi hai preso bene! Va bene, ammetto, non mi nasconderò. Non ero ubriaco. Ma sai quanto le persone cadono facilmente per quelli che si fingono ricchi e ubriachi che vogliono giocare a carte? Chiunque abbia qualcosa da scommettere è quasi il primo a correre alla taverna per ottenere rapidamente una vittoria indubbiamente grande da un nobile indubbiamente ricco ma ubriaco. Lascia che ti dica che sei il primo che ha capito il mio vero io."; 
			link.l1 = "Allora, che facciamo ora? Mi restituisci i miei soldi in modo pacifico?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ah ah ah, non farmi ridere, capitano. Naturalmente, non ti restituirò nulla! E non pensare di potermi costringere. Posso facilmente fingere di essere un nobile rispettato che viene aggredito da qualche capitano randagio. Quindi il mio consiglio per te è: accetta la tua sconfitta e semplicemente vattene."; 
			link.l1 = "Ebbene, spero sinceramente che tu non venga catturato da me in circostanze meno fortunate, perché allora non riderai più così. Addio."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "E il mio consiglio per te, cerca di trovare il tempo per procurarti una spada."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Non oseresti... È una taverna, piena di gente..."; 
			link.l1 = "Allora sono solo un capitano randagio, che mi importa delle regole della decenza. E nella taverna del porto di notte, cosa può succedere ... Maneggio una spada in ogni modo meglio di te."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Ah quindi è così?! Bene, ora controlleremo chi lo possiede meglio!"; 
			link.l1 = "Al vostro servizio..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Capitano?.. hic!.. oh, "+GetAddress_Form(NPChar)+" ... m-mi dispiace... hic!.. per il mio... c-condizione. Puoi aiutarmi? hic!.. P-per favore."; 
			link.l1 = "Scusa, "+GetAddress_Form(NPChar)+", ma sono occupato."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh... ascoltando."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "È una di quelle cose... In generale... Sono... già brillo... Puoi vedere... hic!.. sì?"; 
			link.l1 = "Ad essere onesto, sì. Hai bisogno di aiuto per rinsavire?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Non proprio! Sto b-bene. Voglio una dama. Ma sono così ub-ubriaco... hic!.. La m-madama mi caccerebbe via, quindi. Potresti... hic!... t-trattare per me? Darò dei soldi."; 
			link.l1 = "Mi dispiace, "+GetAddress_Form(NPChar)+", ma come posso dirtelo... Non vado nei bordelli. Onore, reputazione... sai ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Oh, va bene, ti aiuterò."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Solo... hic!.. lentamente, p-per favore. Non sono... hic!.. in grado di...stare in piedi..."; 
			link.l1 = "Bene, andiamo lentamente."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Ecco i soldi... hic!... Ti aspetterò q-qui."; 
			link.l1 = "Bene, tornerò presto."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "S-solo... portami... hic!.. il... migliore!.. Sì..."; 
			link.l1 = "Bene, capito, ho capito."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hic!.. Quanto ancora?"; 
			link.l1 = "La migliore ragazza di questa colonia ti sta aspettando al piano di sopra."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Sì!.. Questa sera... è grandiosa... G-grazie, "+GetAddress_Form(NPChar)+". Il resto dei soldi... hic!... prendilo. E io affondo... nel... mio..... bellissima... signora...";
			link.l1 = "Beh, divertiti."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hic!.. Quanto ancora?";
			link.l1 = "Presto negozierò, sii paziente.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hic!..";
			link.l1 = "Hai bisogno di dormire.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hic!.. Sì... è ancora lontano?..";
			link.l1 = "Siamo quasi arrivati, sii paziente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Eh? Chi sei? Cosa stai facendo qui?";
			link.l1 = "Potrei farti la stessa domanda.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "Noi? Oh, noi... um... Stiamo raccogliendo fiori qui...";
			link.l1 = "Fiori per la tomba? Bene, com'è che sta andando l'erbario?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Erbe... Ha a che fare con le erbe?";
			link.l1 = "Allora... Credo di capire cosa sta succedendo qui.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Non siamo malfattori! Non parlare di noi in questo modo! Siamo solo...";
			link.l1 = "Solo cosa?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Beh, noi... Mio padre ci vieta di vederci! E anche suo padre! Quindi noi... cercavamo un posto senza testimoni. Per stare soli. La serratura sulla porta è comunque rotta, quindi è facile entrare qui...";
			link.l1 = "Capisco ora cosa fossero quei lamenti spaventosi dell'anima irrequieta...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Ebbene, se hai capito tutto, forse ci lascerai in pace?";
			link.l1 = "Non hai paura di organizzare i tuoi appuntamenti in una cripta? Non è il miglior posto...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Non siamo superstiziosi! E anche se fosse spaventoso - quale scelta abbiamo? In città, i genitori l'avrebbero scoperto subito. Ma qui nessuno ci spiffera. Quindi, per ora, è la migliore opzione.";
			link.l1 = "Mi dispiace davvero, ma potresti cercare un altro posto? Non fraintendermi, capisco tutto - la gioventù e tutto il resto - ma i tuoi appuntamenti hanno spaventato a morte il guardiano del cimitero, con tutti i rumori e i gemiti che provengono dalla cripta ogni notte.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Beh... Spaventare la guardia non era parte del nostro piano. Ma allora dove possiamo incontrarci? O suggerisci che abbiamo i nostri appuntamenti sotto il cielo aperto?";
			link.l1 = "L'amore non conosce confini. Trova un altro posto dove sicuramente non disturberai nessuno. Allora nessuno ti disturberà. Probabilmente. Ed è meglio sistemare le cose con i tuoi genitori - non pensi di nasconderti per sempre, vero?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Fine, we'll think of something... We won't be scaring the guard anymore; you have my word.";
			link.l1 = "Meraviglioso. Buona fortuna a te!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "Cosa?!";
			link.l1 = "Oh, niente...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono un cittadino della città e ti chiederei di abbassare la tua lama.","Ascolta, sono un cittadino della città e ti chiederei di abbassare la tua lama.");
			link.l1 = LinkRandPhrase("Bene.","Come desideri...","Come dici tu...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
