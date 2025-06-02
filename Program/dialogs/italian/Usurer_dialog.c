// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "È finita. Ora lascia questo posto, "+pchar.name+". Pulirò tutto questo pasticcio.";
					link.l1 = "Bene, salperò!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("La città è in allarme e ti stanno cercando ovunque! Se fossi in te, non resterei qui a lungo.","Tutte le guardie ti stanno cercando. Non sono un idiota e non rischierò di parlare con te!","Corri, "+GetSexPhrase("amico","ragazza")+", prima che i soldati ti facciano a pezzi..."),LinkRandPhrase("Cosa vuoi, vile creatura?! Le guardie della città sono a conoscenza della tua posizione e non scapperai, "+GetSexPhrase("sporco pirata","puttana pirata")+"!","Sporco assassino, allontanati dal mio posto! Guardie!","Non ti temo, vile creatura! Presto sarai impiccato nella nostra fortezza, non ti sfuggirai..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, per me non è un problema...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti taglierò la maledetta lingua!","Eh, "+GetWorkTypeOfMan(npchar,"")+", vuoi catturare anche un pirata? Ascolta, ragazzo, siediti qui tranquillo e vivrai..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Hai bisogno di qualcosa, signore?";
				Link.l1 = "Mi serve un'informazione... Voglio chiederti qualcosa.";
				Link.l1.go = "quests";
				Link.l2 = "Che ne dici di un piccolo prestito?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "No, ho cambiato idea.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Dai un'occhiata a questi orecchini, signore. Li ho trovati nella tasca di un bandito nella giungla. Questa è chiaramente l'opera di un fine gioielliere che, ne sono certo, non viene da questa selvaggia. Cosa ne dici?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "So che avete un debitore di nome Folke Deluc. Ditemi, quanto è grave la sua... insolvenza?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Sono qui per il debito di Folke Deluc.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "Ho completato il vostro incarico, signore. Ecco il vostro... amico spagnolo.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ebbene, finalmente un capitano degno ha visitato il mio posto, sono così stanco di idioti che pensano che io semplicemente pianti i loro dobloni e ghinee e raccolga il raccolto ogni mese per pagare loro gli interessi\nOsservano ogni centesimo, mentre non hanno idea di come il povero usuraio ricorra a vari trucchi per evitare di morire di fame e, allo stesso tempo, fornire loro l'opportunità di comprare un'oca per Natale.";
				Link.l1 = "Immagino che i tuoi clienti non saranno felici di sentire tali parole dall'uomo che detiene i loro risparmi.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Ascolta, vecchio criceto, devi davvero fare del tuo meglio ora per spiegarmi tutto! Non c'erano schiavi nel carico di quella nave, ma una compagnia di soldati! È stata una missione davvero difficile da affrontare! Sono molto arrabbiato, quindi faresti meglio a spiegarti!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, finalmente eccoti qui! L'intero arcipelago sta spettegolando sul tuo audace attacco. Felice di vederti!";
				Link.l1 = "Preferirei l'oscurità a quel tipo di fama... È troppo pericoloso.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hai portato i miei cinquemila schiavi?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Certo. Sono nella mia stiva.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "No, sto ancora lavorando su questo.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm.. Sei ancora vivo? Strano. Ma non durerà a lungo. Soldati! Aiuto! Ho un bandito qui!";
				link.l1 = "Che bastardo!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Buon giorno. Il mio nome è "+GetFullName(npchar)+". Come posso essere d'aiuto?";
				link.l1 = "Oh! Cosa stai facendo qui, signore?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Ehi là, bastardo. Hai avuto una brillante idea? Hai assoldato sicari per uccidermi? Volevi farmi fuori? Parla, ora!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Oh, Capitano! Per favore, guarda cosa ho oggi. Alcuni articoli che ho acquisito dagli uomini di Blackwood. Hanno bisogno di soldi per una nuova spedizione, e per noi - profitto, giusto?";
				link.l1 = "Blackwood sa che i suoi uomini stanno vendendo i loro ritrovamenti?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Buongiorno a te, "+GetAddress_Form(NPChar)+". Come posso aiutarti? Ti conosco?","Entra, capitano. Il mio nome è "+GetFullName(npchar)+" e io sono il banchiere locale.","Piacere di conoscerti, "+GetAddress_Form(NPChar)+"! Sono un banchiere locale e se hai un problema con i soldi, posso aiutarti."),LinkRandPhrase("Ci siamo già incontrati prima, capitano? Io sono "+GetFullName(npchar)+", e sono un banchiere locale.","Entra, capitano. Il mio nome è "+GetFullName(npchar)+" e io sono il banchiere locale.","Saluti, "+GetAddress_Form(NPChar)+". Io sono "+GetFullName(npchar)+", il banchiere locale."),LinkRandPhrase("Un piacere conoscerti, "+GetAddress_Form(NPChar)+", Io sono "+GetFullName(npchar)+"solo un modesto banchiere in questa meravigliosa città.","È una tua decisione, capitano! Vuoi prendere in prestito un po' di moneta da me o prestare denaro con interesse?","Signor capitano! Sono così contento che tu abbia visitato il mio modesto ufficio!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Un piacere! Stavo solo passeggiando per la città e ho deciso di venirti a trovare.","Il mio piacere, io sono "+GetFullName(pchar)+", piacere di conoscerti.",""+GetFullName(pchar)+" , capitano della nave chiamata "+pchar.ship.name+" , lieto di incontrarti. Questa è una banca, giusto?"),RandPhraseSimple("Piacere di conoscerti. Io sono "+GetFullName(pchar)+". Un capitano della nave chiamata "+pchar.ship.name+". Volevo solo conoscerti.","Aha, quindi avete una banca qui, vero? Piacere di conoscerti, sono "+GetFullName(pchar)+", un capitano della mia stessa nave."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Signora MacArthur, benvenuta, prego entri.";
					link.l1 = "E anche a te, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Sei tu! Cosa desideri, "+GetAddress_Form(NPChar)+"?","Qual è il tuo affare qui, capitano? Mi dispiace ma la tua reputazione non ti rende un cliente molto desiderato.","Aha, un altro cliente! All'inizio pensavo che tu fossi un ladro... ah-ah sto solo scherzando."),LinkRandPhrase("Oh! Cosa vuoi? È una banca, non una taverna.","Buon giorno a lei, capitano. Devo informarla che sono molto selettivo nella scelta dei miei clienti.","Cosa vuoi, "+GetFullName(pchar)+"? Spero che tu ricordi che la tua fama non ti permetterà di ottenere un prestito elevato?"),LinkRandPhrase("Spero che tu voglia investire dei soldi, "+GetAddress_Form(NPChar)+"? Non sarà facile concederti un prestito.","Capitano "+GetFullName(pchar)+"cosa desideri dal modesto banchiere? Mi dispiace, ma non sarò in grado di organizzare un prestito per te. Puoi solo prestarmi dei soldi con interessi.","Entra, "+GetAddress_Form(NPChar)+". Mi dispiace informarti che non sei il cliente più gradito, ma di solito non rifiuto le persone immediatamente.")),LinkRandPhrase(LinkRandPhrase("Salve, signore "+GetFullName(pchar)+"! Sono sempre pronto ad aiutarvi nei problemi di affari.","Buongiorno, signore "+GetAddress_Form(NPChar)+". Sono sempre pronto a concedere un prestito o accettare qualsiasi investimento.","Caro "+GetFullName(pchar)+"! Felice di vederti! Cosa desideri?"),LinkRandPhrase("Capitano "+GetFullName(pchar)+"! Sono sempre al vostro servizio. Volete richiedere un prestito o investire denaro con interesse?","Saluti a te capitano! Sei sempre un cliente desiderato qui. Hai una eccellente reputazione commerciale!","Buongiorno, "+GetFullName(pchar)+". Sono lieto che tu mi abbia fatto visita di nuovo. Spero che tu sia venuto per un accordo d'affari proficuo?"),LinkRandPhrase("Buongiorno a te, capitano! Cosa desideri? Vuoi ottenere un prestito o fare un investimento?","Capitano "+GetFullName(pchar)+"! Vuoi prestare denaro a condizioni vantaggiose? Sono sempre lieto di vedere un cliente così rispettabile.","Contento di rivederti, capitano! Sono sempre pronto ad aiutarti, sia che si tratti di ottenere un prestito o di fare un investimento.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Non sto scherzando, banchiere, ho un affare qui.","Troppo chiacchierare, amico. Andiamo direttamente al punto.","Hai sentito dire che i soldi non hanno odore? Quindi chiudi il naso e passiamo agli affari."),LinkRandPhrase("E così è come incontri i tuoi clienti? Fortunato per te che sono di buon umore oggi.","Ah! Non sei contento di vedermi, eh? E non sono forse un doppione d'oro per fare una buona impressione su di te. Comunque, facciamo affari, usuraio.","Eh, mi piacerebbe insegnarti un po' di rispetto, ma non ho tempo per questo. Parliamo invece di soldi.")),RandPhraseSimple(LinkRandPhrase("Contento di vedere il mio vecchio amico!","È sempre un piacere venire qui, amico. Andiamo dritti al punto.","Sono molto contento anch'io. Parliamo di affari, amico."),LinkRandPhrase("Davvero felice di incontrarti. Cosa c'è di nuovo nei mari finanziari?","Contento che tu mi ricordi ancora. Ho fretta quindi andiamo subito al sodo.","Ciao, vecchio amico! Felice di rivederti!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Come posso aiutarti?","Cosa vuoi questa volta?","Mm... quali sono le tue preoccupazioni?","Eh, "+GetAddress_Form(npchar)+", non puoi nemmeno immaginare quanto possano essere fastidiosi i clienti...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No grazie, sto solo passeggiando e parlando.","Sono io di nuovo. Volevo solo parlare con te.","Sì, sono io di nuovo. Niente di serio, volevo solo parlarti.","Sì, essere un banchiere non è sempre così facile. Volevo solo parlare...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Voglio discutere delle nostre questioni finanziarie.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Sono interessato a gioielli e idoli insoliti o gemme.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Mi serve qualche informazione. Beh, ho qualcosa da chiederti.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Ti ho portato i documenti commerciali da "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Sono qui per ordini di un uomo. È un governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato qui. Devo prendere qualcosa da te.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Buongiorno, sono stato invitato da vostro figlio."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Sono interessato a sapere chi è il proprietario del documento.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Voglio parlare del debito del vostro cliente. Il suo nome è "+pchar.GenQuest.Noblelombard.Name+". Ha impegnato il suo cimelio di famiglia. Rappresento i suoi interessi qui e ho il diritto di discutere con te del suo ritorno.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Abbiamo avuto un incontro tre mesi fa e abbiamo parlato di un reliquia di un uomo. Il suo nome era "+pchar.GenQuest.Noblelombard.Name+". Ricordi quello? Ha dovuto aprire un deposito a mio nome. La somma è  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Si tratta del tuo ... incarico di schiavo.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+NPChar.name+", parliamo del tuo incarico.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buon giorno, "+NPChar.name+", parliamo del tuo incarico.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buon giorno, "+NPChar.name+", parliamo del tuo incarico.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Sono venuto, come abbiamo concordato. Hai un lavoro per me?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Sono venuto come promesso. Che ne dici di un lavoro?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buon giorno, "+npchar.name+". Come stai? Hai un nuovo incarico per me?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "La tua missione è compiuta. Sono riuscito a trovare quei fuggitivi. Non è stato però così facile.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+npchar.name+". Sono venuto per un nuovo incarico redditizio.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Cattive notizie,"+npchar.name+". Non sono riuscito a prendere la brigantina.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guarda,  "+npchar.name+". Ho inseguito la brigantina, ma non ho trovato nessun documento. Sei sicuro che fossero lì?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buone notizie,"+npchar.name+". Sono riuscito a cacciare quella brigantina e trovare i documenti. Eccoli qui.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+npchar.name+". Hai preparato un nuovo incarico per me?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Sono riuscito a intercettare quella cosiddetta 'galeone'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Mi dispiace tanto ma non ho potuto imbarcarmi su questo galeone.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+npchar.name+". Sono venuto per i miei soldi.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", la tua missione è completa. Quel bastardo di Gontier è morto e lo è anche il suo equipaggio.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Mi dispiace ma non sono riuscito a catturare Francois Gontier, nonostante lo stessi seguendo fino a Tortuga. È riuscito a sfuggirmi sulla sua corvetta.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno,"+npchar.name+". Parlami di quella nuova missione che hai preparato per me.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Non direi che hai bisogno di denaro o che stai cercando di aumentare la tua ricchezza. Cosa ti porta nel mio ufficio?","Cosa desideri questa volta?","Mh... quali sono le tue preoccupazioni?","Eh, "+GetAddress_Form(npchar)+", non puoi nemmeno immaginare quanto possano essere fastidiosi i clienti...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No grazie, sto solo passeggiando e parlando.","Sono di nuovo qui. Volevo solo parlare con te.","Sì, sono io di nuovo. Niente di grave, volevo solo parlare con te.","Sì, a volte non è facile essere un banchiere. Volevo solo parlare...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Voglio discutere delle nostre questioni finanziarie.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Sono interessato a gioielli e idoli insoliti o gemme.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Ho bisogno di alcune informazioni. Beh, ho qualcosa da chiederti.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Ti ho portato i documenti commerciali da "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Sono qui per ordini di un uomo. È un governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato qui. Devo prendere qualcosa da te.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Buon giorno, sono stato invitato da vostro figlio."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Sono interessato a sapere chi è il proprietario del documento.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Voglio parlare del debito del tuo cliente. Si chiama "+pchar.GenQuest.Noblelombard.Name+". Ha impegnato il suo cimelio di famiglia. Rappresento i suoi interessi qui e ho il diritto di discutere con te del suo ritorno.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Abbiamo avuto un incontro tre mesi fa e abbiamo parlato di una reliquia di un uomo. Il suo nome era "+pchar.GenQuest.Noblelombard.Name+". Ricordi quello? Doveva aprire un deposito a mio nome. La somma è  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Si tratta della tua ... assegnazione di schiavi.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buon giorno, "+NPChar.name+", parliamo del tuo incarico.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+NPChar.name+", parliamo del tuo incarico.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+NPChar.name+", parliamo del tuo incarico.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Sono venuto, come abbiamo concordato. Hai un lavoro per me?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Sono venuto come promesso. Che ne dici di un lavoro?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+npchar.name+". Come stai? Hai un nuovo incarico per me?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "La vostra missione è compiuta. Sono riuscito a trovare quei fuggitivi. Non è stato però così facile.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buon giorno, "+npchar.name+". Sono venuto per un nuovo incarico redditizio.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Cattive notizie,"+npchar.name+". Non sono riuscito a prendere la brigantina.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guarda,  "+npchar.name+". Ho inseguito la brigantina, ma non ho trovato nessun documento. Sei sicuro che erano lì?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buone notizie,"+npchar.name+". Sono riuscito a dare la caccia a quella brigantina e a trovare i documenti. Eccoli qui.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+npchar.name+". Hai preparato un nuovo incarico per me?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Sono riuscito a intercettare quella cosiddetta 'galea'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Mi dispiace molto, ma non sono riuscito a salire su questo galeone.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buongiorno, "+npchar.name+". Sono venuto per i miei soldi.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", la tua missione è completa. Quel bastardo di Gontier è morto e con lui anche il suo equipaggio.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Mi dispiace ma non sono riuscito a catturare Francois Gontier, anche se lo stavo seguendo fino a Tortuga. È riuscito a sfuggirmi sulla sua corvetta.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buon giorno,"+npchar.name+". Parlami di quella nuova missione che hai preparato per me.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Vuoi comprare alcuni dobloni d'oro o casse per loro? Credimi, è un investimento molto prezioso.";
			link.l1 = "Sì, è molto interessante.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Vuoi fare affari in pesos o dobloni?";
			link.l1 = "Per pesos.";
			link.l1.go = "items";
			link.l2 = "Per dobloni.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Mi ci vorrà molto tempo per leggere questi documenti e il mio tempo costa molto.";
			link.l1 = "Forse, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos compenseranno il tuo tempo?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Come desideri. Addio!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Fammi dare un'occhiata! No, non ho mai visto questo nome prima. Mostrali al nostro maestro del porto.";
				link.l1 = "Mi dispiace, ma abbiamo fatto un accordo! Mi hai promesso di parlarmi di questo capitano!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+"Dicono che sia un contrabbandiere di successo. È quello che volevi sentire?";
				link.l1 = "Sembra di sì...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"Questi documenti sono firmati per la nostra nave da pattuglia coloniale e il suo capitano è noto per i suoi forti principi.";
				link.l1 = "Una pattuglia? Sotto il comando del comandante?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Ti ho promesso di dare un'occhiata a quei documenti e nient'altro. Puoi andare.";
			link.l1 = "Grazie... Suppongo.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "È una tua decisione. Il nostro comandante ha mostrato un certo 'interesse' per questa persona, da molto tempo. Hai già qualche idea? E qui abbiamo delle bolle di carico senza marchi...";
			link.l1 = "Capisco. La mia gratitudine!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"E come ho menzionato prima, il proprietario della carta è un uomo di principi e non apprezza veramente i crimini locali.";
			link.l1 = "Capisco. La mia gratitudine!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, capisco che sei il capitano che ha riportato mio figlio prodigo con la sua giovane sposa?";
				link.l1 = "Sì, sono stato io a aiutarli a fuggire.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, eccoti qui, mio benefattore. Stai aspettando una ricompensa, suppongo?";
				link.l1 = "Almeno un ringraziamento sarebbe gradito...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sono davvero grato per aver aiutato mio figlio e per non averlo lasciato in quella situazione problematica. Per favore, permettimi di ringraziarti nel miglior modo possibile. Accetta questa modesta somma e un piccolo regalo da parte mia.";
			link.l1 = "Grazie. È stato un piacere aiutare questa giovane coppia.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Grazie? Per cosa? Questo idiota è stato disoccupato per metà dell'anno ed è già riuscito a trovare una ragazza! A la sua età, gestivo già la mia attività. C'è una figlia del governatore nubile e lui ha portato questa prostituta qui, Signore, perdonami per averlo detto! E ora cerca la mia benedizione!";
			link.l1 = "Presumo che non credi nei sentimenti?";
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
			dialog.text = "Sentimenti? Che tipo di sentimenti? Sei un uomo adulto e parli anche tu di questi sentimenti? Che vergogna essere un ruffiano per la gioventù. Hai portato via la ragazza dai suoi genitori e distrutto la vita di mio figlio. Non riceverai alcun ringraziamento da me. Addio.";
			link.l1 = "Allora addio...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Discutiamone. Sto ascoltando.";
				}
				else
				{
					dialog.text = "Eh, eh. Temo di dovervi rifiutare, "+GetAddress_Form(NPChar)+". Mi dispiace, ma la mia banca non fornisce servizi ai nemici della Spagna.";
					link.l1 = "Il denaro non ha nazionalità, signor banchiere.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Mm-hmm, "+GetAddress_Form(NPChar)+". Devo informarvi che il vostro deposito non è più valido.";
							Link.l1 = "Su quali basi?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Parliamone. Sto ascoltando.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Ti devo "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", Sono pronto a restituire i tuoi soldi",". Voglio ripagare il debito.",".  Finalmente, è ora di saldare il debito.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Voglio prendere in prestito alcune monete.","Ho davvero bisogno di ottenere alcuni pesos.","Che ne dici di un piccolo prestito?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Vorrei depositare i miei soldi per interesse.","Accetteresti di tenere alcuni sacchi del mio argento?","Posso lasciarti un po' di argento per un giorno sfortunato?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Voglio depositare alcuni dobloni per interesse.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Sono qui per riavere il mio investimento, in pesos.","È tempo di riavere il mio argento che mi devi.","Mi serve indietro il mio investimento in pesos con tutti gli interessi.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Voglio ritirare il mio investimento in dobloni.","È ora di riavere il mio oro che mi devi.","Devo riavere il mio investimento in dobloni con tutto l'interesse.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Ricordo il mio debito, ma non sono ancora pronto a saldare...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Mi scuso, non ho alcun affare finanziario con te. Addio.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "No, non posso aiutarti. Posso solo accettare investimenti in questo luogo problematico. Puoi investire pesos d'argento o dobloni d'oro.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Voglio investire pesos e parliamo della somma.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Voglio investire dobloni. Chiarifichiamo la somma.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Non sono interessato.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Il tuo nome è "+GetFullName(pchar)+", giusto? Hai "+RandPhraseSimple("una cattiva reputazione ","una cattiva reputazione ")+" e non voglio fare affari con te.";
				link.l1 = RandPhraseSimple("Non può un uomo commettere un errore?",RandSwear()+"Comunque!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, sei sempre il benvenuto. Di quale somma hai bisogno?";
			Link.l1 = "Una piccola.";
			Link.l1.go = "Small";
			Link.l2 = "Moderato.";
			Link.l2.go = "Medium";
			Link.l3 = "Grande quanto possibile.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Eccellente! È sempre molto più semplice trattare con somme piccole - meno rischio per entrambe le parti. Posso offrirti "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Affare. E riguardo ai tuoi interessi?";
			Link.l1.go = "Interest";
			Link.l2 = "Non funzionerà per me. Cambiamolo.";
			Link.l2.go = "Loan";
			Link.l3 = "Suppongo che sia meglio per me non indebitarmi. Addio.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Nessun problema. Spero che "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" ti aiuterà a risolvere i tuoi problemi. È una somma piuttosto sostanziosa.";
			Link.l1 = "Affare. E a proposito del tuo interesse?";
			Link.l1.go = "Interest";
			Link.l2 = "Non funziona per me. Cambiamolo.";
			Link.l2.go = "Loan";
			Link.l3 = "Suppongo che sia meglio per me stare lontano dai debiti. Addio.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Bene... è rischioso. Va bene, sono pronto a concederti un prestito per "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". Spero che capisca, capitano, è veramente una somma sostanziale. Le chiedo di prenderla seriamente.";
			Link.l1 = "Affare. E riguardo al tuo interesse?";
			Link.l1.go = "Interest";
			Link.l2 = "Non funziona per me. Cambiamolo.";
			Link.l2.go = "Loan";
			Link.l3 = "Suppongo che sia meglio per me stare lontano dai debiti. Addio.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest+"%% al mese. Non posso offrirti condizioni migliori basate su quello che so di te."; 
			Link.l1 = "Va bene per me. Parliamo del tempo.";
			Link.l1.go = "Period";
			Link.l3 = "Presumo che sia meglio per me stare lontano dai debiti. Addio.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Tenendo conto delle mie informazioni su di te, "+Pchar.name+", Aspetterò il ritorno di questo prestito per "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+". Dopo di ciò prenderò certe misure. Spero che tu capisca."; 
			Link.l1 = "Accetto volentieri le vostre condizioni... e le vostre monete.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Mi scusi, ma non funzionerà per me. Addio.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Sono sinceramente contento. Ma lascia che ti avverta. Faccio questo da molto tempo e so come recuperare i miei investimenti. Quindi, se hai mai avuto idee sciocche, ti suggerisco di lasciarle stare\nNessun offesa, solo un avvertimento.";
			Link.l1 = "Mm.. Bene. Addio.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "La scelta è tua, capitano. Il mio interesse sta crescendo e non hai molto tempo.";
			Link.l1 = "Non preoccuparti. Ci vediamo.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Meraviglioso! Vieni da me quando hai bisogno di monete. Sarò al tuo servizio in qualsiasi momento.","La mia gratitudine. È sempre un piacere trattare con un uomo capace di restituire i suoi debiti in tempo. A volte succedono cose, e posso capirlo, lo sai... ma preferisco che i problemi vengano risolti.","Oh, ho fatto bene a fidarmi di te, "+GetAddress_Form(NPChar)+"! Spero che non sia l'ultima volta che utilizzi i miei servizi. Forse possiamo persino fare offerte migliori per te, visto che ora so che sei un uomo onesto.");
			Link.l1 = LinkRandPhrase("Voglio prendere in prestito un po' di denaro.","Ho davvero bisogno di avere qualche peso.","Che ne dici di un piccolo prestito?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Vorrei investire i miei soldi.","Terrai un po' di bottino pirata?","Posso lasciarvi un po' di argento per un giorno sfortunato?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Voglio investire alcuni dobloni per interesse";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Addio, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Vedo un uomo saggio! Quale somma vorresti investire?","Bene. Fidati di me, questa somma ti aspetterà qui al sicuro e con tutti i suoi interessi.","Vedo che sai cosa è veramente importante in questa vita. Quanto vorresti investire?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Scherzi, eh?";
				link.l1 = "È stato un mio errore.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Mm, purtroppo non hai così tanti soldi. Siamo seri...";
				link.l1 = "Bene.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bene. Posso offrirti... diciamo..."+Pchar.QuestTemp.Deposits.(sDepositType1).Interest+" %. Al mese, ovviamente.";
			Link.l1 = "Funziona per me.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "È meglio che cambi la somma.";
			Link.l2.go = "Deposit";
			Link.l3 = "Sembra che questa fosse una cattiva idea... Addio.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Mi scusi, capitano, ma questa somma è troppo grande per la mia banca coloniale. Non sarò in grado di pagarti il tuo interesse. E la mancanza di una guardia affidabile... Spero che tu capisca. Comunque, la somma massima che posso accettare da te è "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Peccato, dovrò trovare un altro banchiere.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Ora puoi essere sicuro che nemmeno la tempesta più forte ti lascerà senza un soldo.";
				Link.l1 = "Bene. Ci vediamo.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considerando l'interesse promesso e il tempo trascorso, ti devo "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Sei sicuro di voler prendere i soldi?";
			Link.l1 = "Certo. Dammi.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Voglio ritirare una parte dei miei soldi.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Hai ragione. Lo lascerò stare con te per un po'. Buona giornata.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "E quanto costa?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "È stata una battuta così stupida, signore!";			
				link.l1 = "Maledizione! Mi dispiace tanto... Cambiamo la somma.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Non hai così tanti soldi sul tuo conto.";			
				link.l1 = "Accidenti! Il mio errore. Cambiamo la somma.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Tutto? Va bene, come dici. Ecco i tuoi soldi.";			
				link.l1 = "Grazie!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Bene. Prendilo. Ecco i tuoi soldi.";			
			link.l1 = "Grazie!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... È così difficile perderli. Mi sono davvero abituato a questi soldi. Comunque, torna di nuovo.";			
			Link.l1 = "Lo farò se ne avrò bisogno. Addio.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Vedo un uomo saggio! Quale somma vorresti investire?","Bene. Fidati di me, questa somma ti aspetterà qui al sicuro e con tutti i tuoi interessi.","Vedo che sai cosa è veramente importante in questa vita. Quanto vorresti investire?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Scherzi, eh?";
				link.l1 = "Ehm, il mio errore...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Mh, purtroppo non hai così tanti soldi. Siamo seri...";
				link.l1 = "Mh... buono.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bene. Posso offrirti... diciamo..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Al mese, naturalmente.";
			Link.l1 = "Funziona per me.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "È meglio che cambi l'importo.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Suppongo che sia meglio tenere il mio oro. Addio.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Mi scusi, capitano, ma questa somma è troppo grande per la mia banca coloniale. Non sarò in grado di pagarti il tuo interesse. E la mancanza di una guardia affidabile... Spero che tu capisca. Ad ogni modo, la somma massima che posso accettare da te è "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Peccato, dovrò trovare un altro banchiere allora.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Ora puoi essere sicuro che nemmeno la tempesta più forte ti lascerebbe senza una moneta.";
				Link.l1 = "Bello. Addio.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considerando gli interessi promessi e il tempo trascorso, ti devo "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Sei sicuro di voler prendere i soldi?";
			Link.l1 = "Certo. Dammi quello.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Voglio ritirare una parte dei miei soldi.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Hai ragione. Lo lascerò con te per un po'. Buona giornata.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "E quanto?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Una tale stupida barzelletta, signore!";			
				link.l1 = "Accidenti! Mi dispiace tanto... Cambiamo la cifra...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Non avete così tanto oro sul vostro conto, signore.";			
				link.l1 = "Maledizione! Ho sbagliato. Cambiamo la somma...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Tutto? Bene, come dici tu. Ecco i tuoi soldi.";			
				link.l1 = "Grazie!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Bene. Prendilo. Ecco i tuoi soldi.";			
			link.l1 = "Grazie!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... È così difficile perderli. Mi sono davvero abituato a questi soldi. Torna comunque.";			
			Link.l1 = "Lo farò se ne avrò bisogno. Addio.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Sei ancora vivo? Vuoi forse restituire i miei soldi? Al diavolo! Ho perso così tanti soldi che non mi ripagheresti mai! E non troverò riposo finché non vedrò il tuo corpo senza vita!";
            Link.l1 = "Voglio solo risolvere le cose in modo pacifico.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Molto bene, vediamo allora! Sappi che neanche tu sei al riparo dalla morte!","Una minaccia?! Vediamo allora cosa intendi fare...","I soldi non sono la cosa più importante nella nostra vita. Non disperarti troppo per questo e uccidi persone, dai ti sfido.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Vattene! Spero di non rivederti mai più.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Davvero? E quali sono le tue preoccupazioni?";
			Link.l1 = "Per oggi ti devo "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". E offro questi soldi a te.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Ti offro il mio debito per ristabilire buone relazioni con te. È "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Adesso stiamo parlando! Dopo tutto posso fare affari con te.";
			Link.l1 = "Grazie. Non ti deluderò più.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ah, suvvia! Noi siamo persone serie, tu ed io, siamo migliori di quegli idioti pronti a morire per un singolo doblone, eppure non cercano mai di farne due.\nSto cercando un uomo a cui proporre un affare serio. Un uomo coraggioso e attivo, onesto e puntuale, ma non appesantito da... eh... troppa scrupolosità riguardo ai dilemmi morali. E spero che tu sia l'uomo che sto cercando.";
			Link.l1 = "Dipenderà dal tipo di 'affare' che intendi offrirmi.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Molto bene, allora ascolta. La schiavitù è l'attività più redditizia ai Caraibi in questi giorni. Non sono un coltivatore, ma ho clienti di fiducia\nQuindi, ho bisogno della seguente quantità di schiavi - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" teste. Sono pronto a pagarti 250 pesos per ciascuna. Credimi, è un prezzo onesto. In totale guadagnerai "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+" pesos.";
			Link.l1 = "No, non sono un mercante di schiavi. Trovati un altro assistente che non si preoccupa della sua coscienza.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Un'offerta allettante. Mi piacerebbe farlo. Quando avrai bisogno degli schiavi?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, sembra che nessuno sia ansioso di muovere il sedere e prendere l'oro sotto i suoi piedi. Sono deluso, molto. Addio e nemmeno pensare di diffondere pettegolezzi sulla nostra conversazione. Il mio braccio ha una lunga portata...";
			Link.l1 = "La tua portata è 'sporca'... proprio come la tua lingua. Addio.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Non limiterò il tuo tempo, ma cerca di compiere la tua missione il più presto possibile. La domanda per l''avorio nero' è enorme. Se farai bene il tuo lavoro, allora ti darò questo tipo di lavori ogni tanto in futuro.";
			Link.l1 = "Sembra bello. Beh, aspetta le buone notizie.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Hai avuto successo nel procurarti quella spedizione di 'avorio nero'?";
            if (amount < 0)
			{
				Link.l1 = "Non ancora. Sto solo controllando se il nostro accordo è ancora attivo.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Ce l'ho. Sono tutti nel mio carico.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Splendido. I miei uomini se ne occuperanno... Non preoccuparti della dogana o del comandante del forte. Sto gestendo una grande operazione qui, quindi non aspettarti problemi e nessuno ti accuserà di contrabbando.";
			Link.l1 = "Sembra che tu abbia una posizione forte qui... Quindi che ne dici del mio pagamento?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Eccolo qui. Non parlo a vanvera. Rimani con me, capitano, e presto avrai così tanto oro che avrai bisogno di una galea per spostarlo!";
			Link.l1 = "Sarebbe fantastico ah-ah... Cosa c'è dopo?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Prossimo? Torna qui tra tre settimane. Sto preparando un affare adesso e dovrebbe essere pronto all'incirca in quel periodo.";
			Link.l1 = "Molto bene, affare fatto. Addio.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Ho un lavoro per te, ma la tua nave è troppo debole. Non voglio che fallisca la missione e nemmeno che ti mando a morire. C'è ancora tempo, quindi procurati una nave più grande come una barca a vela, una brigantina, una brig o una flauta almeno. Non sprecare il tempo!";
				Link.l1 = "Capisco, me ne occuperò. Ci vediamo.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Finalmente! Ti stavo aspettando. Ora andiamo dritti al punto. Come sai, in qualsiasi affare ci sono sempre dei concorrenti... e io ho i miei. Questi bastardi avidi e senza scrupoli sono sempre pronti a portarmi via un cliente! In realtà, voglio eliminarne uno e allo stesso tempo fare un bel guadagno.";
				Link.l1 = "Sono tutto orecchie.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Eccellente. Ora ascolta. Questo mascalzone chiamato "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", ha portato schiavi dall'Africa e ha gettato l'ancora a "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", si trova su un'isola chiamata "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Lì sta aspettando i contrabbandieri. Il suo galeone si chiama '"+pchar.questTemp.Slavetrader.ShipName+". Il loro accordo deve essere rotto a tutti i costi!";
			link.l1 = "E che dire degli schiavi? Sarebbe un tale spreco farli affondare!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Perché dovresti farlo? Non c'è bisogno di questo. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" ha una cattiva reputazione e a nessuno importerà della sua scomparsa. Salta sulla sua galea, uccidi l'uomo e assicurati che rimanga morto, portami la merce e io la venderò. Secondo le mie fonti ci sono circa millecinquecento schiavi.";
			Link.l1 = "Wow. Questo è un bel numero. E il mio pagamento?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "No, signore, queste intrighi non fanno per me. Perché dovrei rovinare i miei rapporti con i contrabbandieri?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Ebbene.. Sembra che mi sia sbagliato su di te... Addio e dimentica il nostro discorso. E non spargere pettegolezzi su quello che hai sentito qui. Io possiedo questa città. E se stai pianificando di salire a bordo del '"+pchar.questTemp.Slavetrader.ShipName+" per te stesso... Mi assicurerò che tu finisca sulla forca. Consideralo.";
			Link.l1 = "Non preoccuparti, non denuncerò alle autorità e non ho bisogno della tua galea. Addio.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Considerando che ti ho dato la posizione del carico e non devi navigare alla ricerca di 'un premio', il pagamento è un po' più basso - 200 pesos a testa. E comunque quella è una grande somma - trecentomila pesos in caso di successo e la nave.";
			Link.l1 = "Affare. Quanto tempo ho?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ah-ah! Parli come se quei schiavi nuotassero da soli verso la mia nave, sperando di entrare nel mio carico il prima possibile! Vuoi davvero che la mia gente rischi la pelle per una somma così misera? Aumenta la mia ricompensa o io lascio gli affari.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Hai due settimane. Non fare tardi o trasferirà il suo carico e tutto sarà finito.";
			link.l1 = "Devo affrettarmi allora. Aspettami con le buone notizie.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Bene, "+GetFullName(pchar)+", cosa ne è stato della nostra missione? Il tuo volto cupo mi dice che l'hai fallita.";
			link.l1 = "Maledizione, hai ragione... Io... beh, sai... Sono arrivato tardi. Sembra che se ne fosse già andato, perché non ho trovato nessuno lì. Ho dovuto navigare con il vento per tutto il tempo, dannazione...";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Bene, "+GetFullName(pchar)+", qual è la tua cattura di oggi? Mi hanno detto che "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" nutre i pesci! Ah-ah-ah!";
			link.l1 = "Sì, sono arrivato proprio in tempo! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+"stava trasferendo schiavi sulla nave del contrabbandiere. Ho dovuto salire su entrambe e mandarli direttamente da Davy Jones, quindi ora hai meno concorrenti.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Sì, immagino di aver sbagliato su di te. Sei arrivato in ritardo? O avevi solo troppa paura di combattere? Comunque sia. Non ha più importanza adesso. Vattene. Ho finito con te. Dimentica tutto quello che hai visto o sentito qui.";
			link.l1 = "Addio allora.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Avevo ragione su di te - "+GetSexPhrase("sei un teppista affascinante","sei una Fanciulla feroce")+"! Ho bisogno di uomini come te. Hai completato la tua missione nel modo più eccellente - hai portato più di millecinquecento schiavi! Purtroppo, posso pagarti solo per milleseicento schiavi. Non ho abbastanza monete per pagarti per il resto, quindi devi venderli da solo. La tua ricompensa è di 320 000 pesos.";
				link.l1 = "Grazie. È stato un piacere fare affari con te, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Avevo ragione su di te - "+GetSexPhrase("sei un teppista affascinante","sei una Fanciulla feroce")+"! Ho bisogno di uomini come te. Hai portato a termine la tua missione nel modo più eccellente - mi hai portato "+sTemp+" schiavi. La tua ricompensa è "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Grazie. È stato un piacere fare affari con te, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Almeno sei sopravvissuto alla situazione più difficile con tutto l'onore. Anche se il premio è inferiore a quello che mi aspettavo, sono comunque soddisfatto. Hai portato "+sTemp+" schiavi. La tua ricompensa è "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Grazie. È stato un piacere fare affari con te, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Capisco... Posso comprendere questo ma mi aspettavo molto di più. Hai portato solo "+sTemp+" schiavi. Almeno hai distrutto i miei concorrenti e questo vale qualcosa. La tua ricompensa è  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Grazie. Apprezzo la vostra comprensione, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Sembra fantastico ma... hmm. Sembra che mi fossi sbagliato su di te. Cosa hai portato?"+sTemp+" schiavi? E il resto? E non dirmi che li hai affondati. Sono sicuro che li hai venduti ai contrabbandieri, o peggio ancora - a quel bastardo di Lavoisier. Vattene a fanculo, non voglio più avere niente a che fare con te!";
				link.l1 = "Come desideri, addio.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Sembra fantastico ma... dove sono i nostri schiavi? Dove si trova il nostro carico? E non dirmi che lo hai affondato. Devi averlo venduto ai contrabbandieri o peggio, a quel bastardo di Lavoisier. Sparisci, ho finito con te.";
			link.l1 = "Come desideri, arrivederci.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Questa non è finita. Nessuno osa prendermi in giro! E pagherai per il tuo tentativo - mi assicurerò che tu abbia problemi. Ora vai via da qui!";
			link.l1 = "Fottiti e il tuo commercio di schiavi! Dovrei tagliarti dove stai, ma sono un uomo migliore di quanto tu sarai mai.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Sembra che stiamo andando bene insieme, "+pchar.name+". Sono molto contento. Vediamoci tra un mese e, forse, troverò un lavoro solo per te. Ho già alcune idee.";
			link.l1 = "Certo, ci vediamo tra un mese. Il mio lavoro con te è molto redditizio.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "Ti farà una fortuna... Un'ultima domanda, "+pchar.name+", hai trovato qualcosa di insolito nella cabina del galeone?";
			link.l1 = "Niente di speciale davvero... Mi sono perso qualcosa?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Intendi questa vecchia fibbia, un amuleto 'scorpione'?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Forse l'hai fatto, e forse no ... Non importa ora. Ci vediamo tra un mese. Addio!";
			link.l1 = "Arrivederci, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Esattamente! Questo è una fibula dei Medici... ne hai mai sentito parlare? Significa che era davvero nella cabina del bastardo... Posso darci un'occhiata?";
			link.l1 = "Certo, prendilo.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Beh-beh... Davvero. Ascolta, "+pchar.name+", vendilo a me. Sono pronto a pagare centomila pesos.";
			link.l1 = "Cento mila? Hm.. Sono d'accordo. Ecco a te!";
			link.l1.go = "Buystatue";
			link.l2 = "No, non la venderò. Il vero prezzo di questa fibula non può essere valutato in argento o oro. So come funzionano queste cose.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Perfetto! Sono contento che abbiamo fatto un accordo. Prendi i tuoi soldi. Non vedo l'ora di rivederti tra un mese.";
			link.l1 = "Addio, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Vedi, ho disperatamente bisogno di questa fibula! Sono completamente d'accordo con te, non può essere valutata con denaro, qualsiasi venditore stupido non ti pagherebbe nemmeno cinquemila per essa. Ma sembra che tu sappia davvero cosa può fare, dal momento che rifiuti di venderla per una cifra del genere.\n Posso offrirti uno scambio, se non vuoi denaro. Ho qualcosa che potrebbe interessarti. Guarda qui. Un'armatura leggera incredibile! Vedi da solo! Te la offro in cambio della fibula.\nNon è unica, tra l'altro. Voi marinai, potete sempre trovarne di più per voi stessi e io non posso. Sei d'accordo ora?";
			link.l1 = "Eh... Suppongo. Dammi l'armatura e prendi questa fibula.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "No, questa fibula ha un prezzo molto più grande per me rispetto a quest'armatura. La terrò per me.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Splendido! Felice che abbiamo fatto un affare. Questa è la tua armatura ora. Prendila. Ci vediamo tra un mese. Addio.";
			link.l1 = "Arrivederci, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Peccato.. Davvero un peccato. Bene, prendilo. Non ti giudico. Ci vediamo tra un mese. Addio.";
			link.l1 = "Arrivederci.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Sei arrivato proprio in tempo, "+pchar.name+". Ho una missione per te se sei pronto a iniziarla.";
			link.l1 = "Certo, sono pronto.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Eccellente! Ora, dritto al punto. Hai sentito le ultime notizie?";
			link.l1 = "Ehm, cosa intendi? Arrivano molte notizie ogni giorno.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Questo riguarda i nostri affari. C'è stata la più grande fuga di schiavi nella storia del Nuovo Mondo! Più di mille anime sono scappate e nel frattempo hanno distrutto e bruciato alcuni avamposti olandesi.";
			link.l1 = "Intrigante. Continua.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Ma non si sono semplicemente dileguati, in qualche modo sono riusciti a lasciare l'isola! Nessuna traccia rimasta. Mathias Beck è furioso. Ma non è questo il punto... Il punto è, che ti chiedo di salpare per Curacao, scoprire cosa è successo lì, trovare i rifugiati e catturarli\nE, ovviamente, per salvarli dalle grinfie della giustizia olandese, che sarebbe spietata con loro. Pagherò 300 pesos a testa - ho sentito dire che sono degli ottimi schiavi.";
			link.l1 = "Capito. Sto andando a Curacao. Attendimi con le buone notizie.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Sai, non accetterò la missione. Non priverò il popolo della loro libertà. Hanno messo a rischio le loro vite per ottenerla. Se la sono meritata.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Che peccato... non me lo aspettavo da te... e nel momento più inopportuno. Immagino sia chiaro per te che la nostra collaborazione è finita. Addio.";
			link.l1 = "Buona giornata.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ah! Non solo sei riuscito nella tua difficile missione, ma hai portato più schiavi di quanti ne ho richiesti - "+sTemp+" schiavi. Ma "+sNum+"gli schiavi non sono scappati da Curacao. Ti pago 100 pesos a testa. Suppongo che ti andrà bene. La tua ricompensa è di 330 000 pesos e "+FindRussianMoneyString(iSlaveMoneyH)+" per un eccesso, ah-ah.";
				link.l1 = "Ha! Sicuramente non puoi essere ingannato. Sono d'accordo, qualunque cosa tu dica, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "Hai completato quella difficile missione nel modo più eccellente e mi hai portato "+sTemp+" schiavi. La tua ricompensa è "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Grazie. È stato un piacere fare affari con te, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Hai avuto successo in quella difficile missione. Il premio non è così ricco come mi aspettavo, ma sono soddisfatto comunque. Quindi hai portato qui "+sTemp+" schiavi. La tua ricompensa è "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Grazie. È stato un piacere fare affari con te, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Li hai trovati? Hm... cosa mi hai portato?"+sTemp+" schiavi? Dove è il resto del carico? E nemmeno provare a dirmi che lo hai affondato. Devi averlo venduto a contrabbandieri, o peggio ancora - a quel bastardo di Lavoisier dall'Isla-Tesoro. Vattene da qui, non ho più voglia di lavorare con te.";
				link.l1 = "Addio.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Li hai trovati? E gli schiavi? Dov'è il nostro carico? E non provare nemmeno a dirmi che l'hai affondato. Devi averlo venduto a contrabbandieri o peggio ancora - a quel bastardo di Lavoisier da Isla-Tesoro. Vattene da qui, non ho più voglia di lavorare con te.";
			link.l1 = "Addio.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Ti apprezzo davvero, "+pchar.name+". Davvero. Torna qui tra un mese e preparerò un nuovo affare, profittevole per entrambi.";
			link.l1 = "Sono anche io soddisfatto della nostra partnership, "+npchar.name+". Ci vediamo tra un mese.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Sei arrivato proprio in tempo, "+pchar.name+". Sto cercando un marinaio coraggioso e senza scrupoli, ah-ah. Sei pronto a occuparti del mio lavoro?";
			link.l1 = "Sono tutto orecchie.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "È molto semplice questa volta. Oggi, una pinnace '"+pchar.questTemp.Slavetrader.ShipName+"' sotto la bandiera di "+NationNameGenitive(sti(npchar.nation))+" ha gettato l'ancora a "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" baia. Era carico di un grande lotto di 'ebano' con l'aiuto dei contrabbandieri locali. Duemila teste, non meno\nNessun soldato in equipaggio e il capitano è un commerciante. In generale, nessuna minaccia. Salite a bordo della nave e portatemi il carico. 200 pesos a testa come al solito.";
			link.l1 = "Mh... Non è lo stesso dell'ultimo lavoro. Mi stai suggerendo di attaccare una nave della tua stessa nazione!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Non capisco, "+pchar.name+". Conta la bandiera della nave? Ti importa davvero?";
			link.l1 = "Lo faccio? No, non me ne frega niente, l'oro non ha nazionalità. È stato solo un po' inaspettato...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Mi interessa. Non voglio avere "+NationNameAblative(sti(npchar.nation))+" tra i miei nemici.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Sei serio? Devi scherzare, non si può fidare di nessuno in questi giorni... In tal caso, vai via. E dimentica tutto quello che hai visto o sentito qui!";
			link.l1 = "Arrivederci,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Perché sei sorpreso? Perché non mi importa della nazionalità delle monete? Ti assicuro, infatti, che non mi importa. Ad essere onesti, il patriottismo è dannoso per un banchiere professionista, a meno che non sia ansioso di finire in rovina un giorno. \nMa basta con la filosofia. Andiamo al dunque - la nave resterà qui fino a mezzanotte, quindi non ti resta molto tempo. Sei pronto a procedere?";
			link.l1 = "Sì, "+npchar.name+", sono in viaggio.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Splendido. Non ho dubbi che riuscirai nella nostra missione. Buona fortuna."+pchar.name+".";
			link.l1 = "Grazie! Addio.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Bene, "+GetFullName(pchar)+", cosa ne è stato della tua missione? Il tuo volto sconsolato mi dice che l'hai fallita.";
			link.l1 = "Hai dannatamente ragione... Io.. Beh... Sono arrivato troppo tardi. Ero nella taverna e quando ho salpato non c'era nessuno in mare.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", per favore, calmati. Non è colpa mia! Accidenti, ho ricevuto il rapporto troppo tardi... C'è stata una tradimento! Uno dei miei uomini di fiducia mi ha venduto!";
			link.l1 = "Bene, vedo che stai dicendo la verità. Sei fortunato che il capitano della pinnace mi abbia detto che il nostro 'affare' era scoperto. Ti avrei già ucciso se non avesse sparato la lingua. Ma tu, sacco di soldi maledetto, mi hai sempre detto che 'possiedi questa città'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "L'imboscata non è stata organizzata dalle autorità locali, altrimenti lo avrei saputo..."+pchar.name+", non è il momento giusto per litigare. Entrambi siamo in pericolo, uno dei miei ex committenti ci ha incastrato\nSono riuscito a scoprire che tutte le prove raccolte - un pacchetto di documenti - vengono trasportate al nostro governatore generale. Se le avrà, siamo finiti! Sarai tu a soffrire di più, tra l'altro.";
			link.l1 = "Ora capisco cosa intendeva quel bastardo di capitano!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Ascolta attentamente. Abbiamo ancora una possibilità. Il pacco è stato inviato sulla brigantina '"+pchar.questTemp.Slavetraderbrig.ShipName+". Questa è l'unica cosa di cui sono certo. I documenti vengono consegnati al governatore generale nella sua residenza su "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". Devi intercettarlo, salire a bordo e trovare quelle prove screditanti.";
			link.l1 = "Non ho molta scelta qui. Prega per me, per te stesso e spera che riuscirò a prenderlo. Parleremo di nuovo di tutto questo quando tornerò. Non pensare che lo lascerò semplicemente andare.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Ottenere questo pacco è la tua priorità principale! Non sarò sicuro della mia sicurezza fino a quando non me lo consegnerai... Dannazione..."+pchar.name+", sembra che abbiamo un problema qui...";
			link.l1 = "Cosa c'è?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Maledizione... contavo su di te, "+pchar.name+". Bene allora. Ma non faremo più affari. Se non riesco a corrompere un investigatore dovrò scappare. E non ti consiglio di restare qui - i soldati potrebbero arrivare qui in qualsiasi momento. Addio.";
			link.l1 = "Addio, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Erano lì. Beh, non possiamo più fare affari insieme, non è più sicuro. Addio.";
			link.l1 = "Addio, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Eccellente! Non avevo dubbi su di te, "+pchar.name+". Per favore dammi quei documenti, sono troppo nervoso.";
			link.l1 = "Prendile.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Bene... Ora sono al sicuro. Il governatore generale non saprà nulla e ho già risolto tutti i problemi con le autorità locali, ma ti dico, è stato costoso.";
			link.l1 = "Sembra fantastico, ma non pensi di dovermi compensare per i miei problemi a causa delle tue azioni sconsiderate?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Certo, "+pchar.name+". Ancora di più, ti devo molto. E veramente spero di continuare il nostro affare. Ma ti chiedo di capirmi - ho speso una somma enorme - la fedeltà del governatore e del comandante costa molto. E ho dovuto occuparmi di quel omicidio dell'intera pattuglia nella mia banca...";
			link.l1 = "Vuoi dire che non compenserai le mie spese?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Non essere così duro, "+pchar.name+". Ho davvero problemi con i soldi ora quindi ti offro un tipo di pagamento diverso.";
			link.l1 = "Allora ti sto ascoltando.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Io e il mio compagno siamo stati colti da una tempesta vicino alle coste meridionali di Main un anno fa. Le nostre navi sono state sbattute contro le rocce della costa di Boca de la Serpienta, sebbene siano affondate presto, siamo riusciti a trascinare il nostro carico a riva. Cassoni pieni di pietre preziose e gioielli. La baia sembrava abbastanza accogliente, quindi abbiamo nascosto i tesori senza problemi\nMa siamo stati attaccati dagli indiani la mattina successiva appena la tempesta era finita. Ecco come la maggior parte dei sopravvissuti è morta, incluso il mio compagno. Io e alcuni marinai siamo riusciti a fuggire su una lancia\nSiamo arrivati a Cumana sani e salvi, ma non ho osato ritornare a cercare i tesori. Sono sicuro che gli indigeni locali stanno ancora proteggendo la loro costa così come i miei cassoni. Ma tu puoi occuparti di quel gruppo di pellirosse\nI gioielli che troverai lì sono abbastanza per coprire tutte le tue spese, incluso una spedizione a Main meridionale.";
			link.l1 = "Hm... va bene. Allora sto andando a Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Potete essere sicuri, "+pchar.name+", tutto ciò che ho detto era la verità. Mi aspetto di vederti tra un mese. Ho già in mente un altro affare e come dovrei aiutare la mia impresa traballante. Addio.";
			link.l1 = "Arrivederci, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "Eccoti qui, "+pchar.name+". Bene, sei sempre puntuale come sempre. Vorrei darti più informazioni sul mercato degli schiavi dei Caraibi prima di darti la prossima missione. Sai cosa significa la parola 'repartimiento'?";
			link.l1 = "Mm, no, "+npchar.name+", No, non lo faccio. Ma suppongo che si tratti di togliere qualcosa a qualcuno. Ho ragione?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Mi sorprendi. Cosa ti aspettavi da me? Vattene!";
			link.l1 = "Un affare illegale è troppo duro per la mia moralità. Specialmente il commercio di schiavi.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Ci sei quasi,"+pchar.name+". Prendere la libertà di qualcuno. Il Repartimiento è un modo ingegnoso e legale per schiavizzare gli indiani locali. Per così dire. Le autorità spagnole lo usano contro la popolazione indigena del Main. Sei interessato a saperne di più?";
			link.l1 = "Perché no?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Rappresentanti della corona spagnola visitano insediamenti indiani. Utilizzando inganno cinico e minacce dirette, costringono gli indiani a comprare ogni sorta di rifiuti come carne marcia e vecchi rasoi a prezzi favolosi. A credito\nDopo un po' di tempo, diciamo un anno, i rappresentanti ritornano e esigono un pagamento. Se gli indiani non possono pagare, cosa che di solito succede, gli spagnoli prendono una parte dei loro uomini capaci di lavorare, presumibilmente per un po' di tempo e per 'insegnarli a coltivare la terra'\nCome capisci, non tornano mai indietro nei loro insediamenti. Ecco come i nostri fiduciosi pellirosse finiscono nelle piantagioni di zucchero e nelle fabbriche di legno rosso.";
			link.l1 = "Maledizione... davvero... E gli indiani come reagiscono? Resistono quando gli spagnoli li schiavizzano? O semplicemente non capiscono cosa sta succedendo?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Immagino che lo vedano sempre arrivare, ma solo pochi osano opporsi apertamente, soprattutto quando gli spagnoli mostrano un documento con l'impronta del capo. Certo, tali tattiche sono normalmente applicate a tribù pacifiche come gli Arawak o i Miskito. Questo trucco non funzionerà con gli bellicosi Itza o Akawoys. Bene, parliamo della tua missione.";
			link.l1 = "Già sento l'odore di un sacco di monete! Ti sto ascoltando, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Presto partirà da Caracas un pesante galeone. Si chiama "+pchar.questTemp.Slavetrader.ShipName+". Contiene un'enorme quantità di schiavi - circa 3000 uomini - Indiani dell'Orinoco, catturati secondo la politica dei repartimientos. Il galeone sta navigando verso Santiago, le piantagioni di zucchero di Cuba hanno bisogno di molti lavoratori. Devi catturare il galeone con il suo carico. Io prenderei almeno due navi con me se fossi in te, dicono che il galeone è il migliore della sua specie. Le tariffe restano le solite - 200 pesos a testa. ";
			link.l1 = "Eh! Suona bene. Sono d'accordo.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Sai che non mi piace quel tuo repartimiento. È troppo cinico. Non lo farò.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Ti auguro buona fortuna allora. Sappi che il capitano di questo galeone è un marinaio di guerra molto abile ed esperto. Non sarà una lotta facile, quindi preparati. Non perdere tempo, ci vorranno quindici o venti giorni per raggiungerlo "+sTemp+" Santiago. Cerca di non mancarlo, anche se questo galeone è davvero difficile da non notare\nSì! Quasi dimenticavo! Ci sono molti amuleti indiani sulla nave, i pellirosse spesso pagano i loro debiti con i loro oggetti di culto e artigianato. Portami qualcosa di speciale che potresti trovare, ti pagherò molto per ogni oggetto di valore che porti.";
			link.l1 = "Capisco.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Bene, "+pchar.name+", era la mia ultima speranza... Ecco perché ti ho proposto questo lavoro. Nessun altro che tu può farlo... e vedo che nemmeno tu sei capace. Diciamo addio, allora. Dopo l'ultimo fallimento e tutti quei pettegolezzi, tutti i miei clienti se ne sono andati. E io sono quasi in bancarotta, forse, devo lasciare questa città. Non ti biasimo - questo lavoro era troppo duro. Eh... Addio,"+pchar.name+".";
			link.l1 = "Mi dispiace tanto, "+npchar.name+", quello è andato troppo oltre. Mi dispiace davvero. Forse, tutto si calmerà. Addio.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Fuh, mi sento meglio adesso... Ho fatto bene a fidarmi di te... Da dove viene questa ironia? Cosa c'è che non va?";
				link.l1 = "Gentile signore, non era una galea... o una grande galea... Accidenti! Era una Nave di Linea! E tu nemmeno mi hai avvertito! Ma sono riuscito a salire a bordo. Ho "+sTemp+" schiavi e sono pronto a trasferirli a te. Secondo il nostro accordo, mi devi - "+FindRussianMoneyString(iSlaveMoney)+". Sarebbe fantastico ottenere un risarcimento per le vostre informazioni errate.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Hai trovato il galeone? E gli schiavi? Dovrebbero essercene almeno tremila, maledizione! Tutti sono dei ratti e dei traditori! Non me lo aspettavo da te... eri la mia ultima speranza\nVa bene... giuro, spenderò ogni moneta che mi rimane per distruggerti, per ucciderti! L'intera flotta di "+NationNameGenitive(sti(npchar.nation))+" ti darà la caccia! Vattene da qui!";
				link.l1 = "Bene...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Non mi dire! Ti giuro, non ne avevo idea. Doveva salpare una pesante galea, non una dannata nave di linea! Sembra che abbiano cambiato i loro piani all'ultimo momento... Ma ancora sei riuscito!\nSono completamente d'accordo con te riguardo ai soldi e al rimborso delle tue spese, il problema è che al momento non possiedo una tale somma. Sai dei miei recenti problemi... Ma non arrabbiarti, "+pchar.name+", per l'amor di Dio. Mi dai la merce e io la venderò, il mio cliente sta già aspettando\nAvrò l'intera somma tra cinque giorni, quindi avrai ciò che meriti. Puoi fare affidamento su di me. Ecco, prendi tutto il contante che ho adesso.";
			link.l1 = "Mh... Mi aspettavo di ricevere i soldi adesso. Vorrei che sapeste che tipo di lotta ho dovuto affrontare! Ah, comunque... Sarò solidale con voi. Ma tenete a mente che se cercate di fregarmi, vi troverò anche in Europa!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Sai, "+npchar.name+", fottiti! Non era un affare. Non puoi nemmeno immaginare che tipo di lotta ho dovuto affrontare. Prendo tutti gli schiavi per me e li vendo senza la tua agenzia.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Allora, ora stai parlando! Sembra che tu sia ignaro "+npchar.name+" ero solo una mucca da mungere, un semplice ritardo è sufficiente per fregarmi e per iniziare un'operazione da solo. Sembra che tu abbia dimenticato che sono stato io a darti il lavoro e a informarti sul bottino\nMolto bene... Lo giuro, spenderò ogni moneta che mi resta per distruggerti, per ucciderti! L'intera flotta di "+NationNameGenitive(sti(npchar.nation))+" ti darà la caccia! Sparisci dalla mia vista!";
			link.l1 = "Non osare spaventarmi, un forziere vuoto. Affonderò tutte le tue flotte e le darò in pasto ai granchi.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Grazie per la vostra comprensione, "+pchar.name+". Prometto che tutto andrà bene, non c'è bisogno delle tue minacce\nPrendi questo come un anticipo. Quindici casse. Cinque di loro serviranno come risarcimento del danno morale. Vieni a trovarmi tra cinque giorni per avere il resto.\nNon dimenticare di portare tutti gli oggetti indiani che hai trovato sulla nave... se li hai trovati, ovviamente. Non ho nulla per pagarti per loro comunque.";
			link.l1 = "Tra cinque giorni,"+npchar.name+". Tra cinque giorni...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Come ho promesso, "+pchar.name+", Sono pronto a pagarti. Gli schiavi sono venduti, il cliente è felice e così siamo noi. Dopo la detrazione di un anticipo, la tua ricompensa è"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". Per favore, prendi i tuoi soldi.";
			link.l1 = "Splendido, "+npchar.name+". È bello trattare con un uomo che sa mantenere la sua parola...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Potete sempre fidarvi della mia parola, "+pchar.name+". Non ti ho mai dato motivo di dubitare di me. I partner devono essere onesti l'uno con l'altro, questa è la chiave del business\nParliamo ora di reperti indiani. Mostrami ciò che hai, non far aspettare un collezionista come me.";
			link.l1 = "Mh... Dai un'occhiata.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Sì! Eccellente! Un coltello rituale d'oro! È una cosa rara. Ho sempre desiderato avere qualcosa del genere nella mia collezione. Ti offro 30 000 per questo o un amuleto di 'Ehecatl' in cambio. Ne ho comunque due.";
				link.l1 = "Prenderei dei soldi.";
				link.l1.go = "BG_money";
				link.l2 = "Prenderei un amuleto di 'Ehecatl' in cambio.";
				link.l2.go = "BG_change";
				link.l3 = "È meglio se tengo questo coltello con me.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Vediamo.. Sfortunatamente, non hai nulla di interessante per me.";
				link.l1 = "Come vuoi tu.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Splendido. Prendi i tuoi 30 000 e questo coltello indiano è mio adesso.";
			link.l1 = "Bene. E questo è tutto ciò che ti interessa...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Splendido! Ecco il tuo amuleto e questo coltello indiano è ora mio.";
			link.l1 = "Bene. E questo è tutto ciò che ti interessa...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Comunque. Ma è davvero un peccato...";
			link.l1 = "Bene. E questo è tutto ciò che ti interessa...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Aspetta! Lasciami dare un'occhiata di nuovo...";
			link.l1 = "Certo. Vieni a dare un'occhiata e scegli quello che desideri.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Questo! E non me ne sono nemmeno accorto all'inizio. Sono interessato a quest'osso con un anello di rame. Una cosa così interessante ti dico... Posso pagarti 20 000 pesos o darti in cambio un amuleto 'Cimaruta'.";
				link.l1 = "Prenderei dei soldi.";
				link.l1.go = "PF_money";
				link.l2 = "Prenderei un amuleto di 'Cimaruta' in cambio.";
				link.l2.go = "PF_change";
				link.l3 = "Conserverei quest'artefatto con me.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "No... non hai nulla di altro di interessante qui.";
				link.l1 = "Comunque!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Eccellente! Ecco i tuoi 20.000 pesos e questo osso è ora mio.";
			link.l1 = "Bene. Mi sento a mio agio con il nostro accordo.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Splendido! Ecco il tuo amuleto e quest'osso è mio ora.";
			link.l1 = "Bene. Mi sento bene riguardo al nostro accordo.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Comunque. Ma è davvero un peccato...";
			link.l1 = "Ho bisogno di quella ossa per me, mi dispiace molto.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Beh... salendo a bordo del galeone, oh mi scuso, la Nave di Linea mi hai salvato. Apprezzo davvero la nostra collaborazione, "+pchar.name+". Sei il mio miglior agente.";
			link.l1 = "Sono lusingato. Stai decisamente sopravvalutando le mie realizzazioni...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Sono completamente serio. E sto per chiederti di compiere un'altra missione a causa delle tue straordinarie abilità e perché ho fiducia in te.";
			link.l1 = "Eh! Sorprendente! Sto ascoltando. Dove si trova un'altra galea con gli schiavi?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Questa volta non si tratta di schiavi. Sorpreso? Ti pagherò bene per la missione... Molto bene.";
			link.l1 = "Andiamo dritti al punto.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Questo affare è collegato ai recenti eventi di cui anche tu sei stato parte... Quindi, come potresti sapere, gestisco un affare piuttosto illegale - il traffico di schiavi. Potresti anche sapere che assumo corsari come te per ogni tipo di incarico\nUno dei miei uomini mi ha tradito non molto tempo fa per ragioni sconosciute. Ha raccolto prove e ha fatto rapporto alle autorità. Hai avuto il piacere di vedere le conseguenze con i tuoi stessi occhi. Una nave con soldati è arrivata qui... sai il resto\nMi ci è voluto un bel po' di tempo per sistemare la situazione. Come capirai, non posso lasciare che questo tradimento resti impunito. Inoltre, non posso vivere e lavorare tranquillamente sapendo che il traditore è ancora vivo. Ho mandato dei cacciatori di taglie, ma non c'è ancora nessun risultato\nTi chiedo di occuparti personalmente di questa questione. Tanto più che le sue azioni ti hanno riguardato anche te.";
			link.l1 = "Hm... questo bastardo deve essere impiccato al pennone! Parlami di più di lui e del mio compenso per il lavoro, naturalmente.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Non preoccuparti di questo. Pagherò molto per la sua eliminazione e non sto parlando solo di soldi. Non risparmierò i migliori pezzi delle mie collezioni. Parliamo dell'uomo. Il suo nome è Francois Gontier\nÈ consapevole della mia caccia, quindi ha venduto la sua fregata per nascondere le sue tracce. I miei colleghi mi hanno detto che è stato visto a Panama. Credo che dovresti iniziare le tue ricerche da lì.";
			link.l1 = "Bene, allora sono sulla mia strada.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Ti auguro buona fortuna allora. Sappi che questo Gontier è un marinaio molto esperto e ha un equipaggio di spietati tagliagole. Non ha nulla da perdere, quindi combatterà in modo molto disperato.";
			link.l1 = "Non ho paura di persone come lui, ma considererò ciò che hai detto. Addio, e sii certo che lo prenderò anche all'inferno.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Splendido! Ora può scrivere i suoi rapporti alle meduse. Nessuno osa mettersi contro di me. Ti ringrazio, "+pchar.name+", sei un uomo indispensabile.";
			link.l1 = "Grazie, "+npchar.name+", per una valutazione così positiva delle mie azioni. E per il mio pagamento?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Certo. Pagherei il giusto prezzo per un lavoro così difficile. Prima di tutto, ti presento questo eccellente cannocchiale.";
			link.l1 = "Caspita, che regalo!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Inoltre, ecco 100 000 pesos come pagamento iniziale e 50 000 come risarcimento per le vostre spese personali.";
			link.l1 = "Grazie, "+npchar.name+". Lo dico di nuovo, è un vero piacere fare affari con te.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Ti aspetterò tra un mese come sempre. È un affare molto importante in fila e avrai bisogno di una squadra ben equipaggiata. Ti chiedo di capire questo e di prepararti bene. Se il mio piano funziona, saremo ricchi.";
			link.l1 = "Bene,"+npchar.name+". Torno quando sono pronto.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Peccato, che vergogna... Beh, non ti abbattere, non sei il primo uomo che quella feccia ha ingannato. Un giorno lo inchioderò comunque\nPer quanto riguarda te, vieni a trovarmi tra un mese. Sarà un grosso affare, quindi raduna una squadra ben equipaggiata e armata. Per favore, prendilo sul serio e fai del tuo meglio per prepararti. Se il mio piano funziona, saremo ricchi.";
			link.l1 = "Bene, "+npchar.name+". Tornerò quando sarò pronto.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Sei arrivato proprio in tempo, "+pchar.name+"! Stavo per iniziare a preoccuparmi, stavo per mandare un uomo a cercarti\nIniziamo! La tua missione è davvero grande e rischiosa ora, ma la ricompensa è adeguata. Riceverai più di un milione di pesos dopo aver completato il lavoro.";
			link.l1 = "Ora stiamo parlando! Sto ascoltando, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Gli indiani schiavizzati venivano trasportati a piccoli gruppi a L'Avana da tutto il continente, e anche alcuni galeoni provenivano dall'Africa e venivano scaricati. Ormai ci sono quasi cinquemila schiavi dietro le alte mura del forte dell'Avana.";
			link.l1 = "Ho la sensazione che l'affare riguardi l'assalto all'Avana.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Hai un buon intuito, "+pchar.name+". È esattamente quello che voglio chiederti di fare. Tu e solo tu. Dubito che qualcun altro dei miei agenti sia in grado di farlo\nCredo che tu sia dentro?";
			link.l1 = "Ad essere onesto, "+npchar.name+", Sono un po' sbalordito ora. Non avevo idea che la tua attività fosse così... su larga scala. Certo, sono dentro. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Sai cosa, "+npchar.name+", questo sta andando troppo lontano. Ne ho abbastanza delle tue sorprese. La prossima volta la tua avidità vorrà che dichiari guerra alla Spagna e dovrò combatterli tutto da solo. Se hai davvero bisogno di quegli schiavi, allora assedia L'Avana da solo.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Non me l'aspettavo da te... Accidenti, cosa dovrei dire al mio cliente? Va bene. È la tua decisione e devo trovare un nuovo partner. Addio, "+pchar.name+". E non utilizzerò i tuoi servizi in futuro. Ricorda che hai lasciato scappare l'affare che avrebbe potuto rendere ricchi i tuoi discendenti fino alla settima generazione.";
			link.l1 = "Non puoi avere tutto il denaro del mondo, e mordi più di quanto puoi masticare. Addio, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Sapevo che saresti stato d'accordo. Ora, ascolta i dettagli. Il forte dell'Avana è sempre stato un obiettivo difficile, ma ora è ancora più difficile\nDue navi di linea stanno sorvegliando le coste di Cuba e devi occupartene prima di assaltare il forte...";
			link.l1 = "Capisco. Non sarà la prima volta che combatto contro le Navi di Linea, ah-ah. Quanto tempo ho?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Non molto. Non più di tre settimane, dopodiché gli schiavi verranno trasferiti agli avamposti spagnoli di Cuba. Devi sbrigarti. ";
			link.l1 = "Allora non perdiamo tempo. Sono sulla mia strada!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Un momento!"+pchar.name+", tu ed io non abbiamo mai avuto incomprensioni o disaccordi. Tuttavia, voglio che tu sappia cosa sta succedendo qui. Io conto su di te, e il cliente conta su di me\nAbbiamo investito molto impegno e denaro in questa operazione. Ogni singolo schiavo, tutti i cinquemila devono essere consegnati a me\nAltrimenti, prenderemo misure molto radicali contro di te. Nessun offesa, è solo un avvertimento. ";
			link.l1 = "Non preoccuparti, "+npchar.name+", Capisco cosa sia il business, motivo per cui dovresti anche ricordarti di pagarmi, una volta che li consegno. Addio.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Ebbene.. E riguardo al premio della tua vittoria?";
				link.l1 = "Ho "+sTemp+" schiavi.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Ebbene, ebbene. Hai dimenticato quello che ho detto? Dovevi portarmi qui non meno di cinquemila schiavi e tu hai portato "+sTemp+". Perché è così?";
				link.l1 = "Mmm.. Una parte di loro non ha sopravvissuto al viaggio da L'Avana... il cibo e le medicine scarseggiavano.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Bene-bene... Vuoi ingannarmi? Hai dimenticato quello che ho detto? Dove sono i miei schiavi ti chiedo! Dove sono?!";
			link.l1 = "Mh.. Beh, vedi...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Bene. Non ho bisogno delle tue spiegazioni. Avevamo un accordo e ti darò una settimana per procurare non meno di cinquemila schiavi. Altrimenti avrai un sacco di problemi.";
			link.l1 = "Bene, bene, rilassati, te li procurerò io.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Splendido! Hai svolto il mio compito come sempre. Sono molto soddisfatto di te.";
			link.l1 = "Così sono io... Ma sarei ancora più contento quando riceverò i miei soldi per il carico.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Sono molto contento di questo. Sei arrivato tardi, ma hai svolto il mio compito nel modo più eccellente.";
			link.l1 = "E ora voglio ottenere denaro per il carico.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Certo. Venderò gli schiavi al mio cliente, lui pagherà e tu otterrai le tue monete. Proprio come l'ultima volta. Vediamo, hai portato qui "+sTemp+" schiavi. La somma è "+FindRussianMoneyString(iSlaveMoney)+". Vieni qui per il pagamento tra una settimana.";
			link.l1 = "Bene, "+npchar.name+", abbiamo un accordo. Sarò qui tra una settimana. Ma fai molto attenzione...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", per favore, non farlo. Siamo partner e non c'è spazio per imbrogli e diffidenza tra di noi. Ti ho promesso un sacco di monete e le hai ottenute. Ti ho promesso compiti interessanti e anche quelli li hai ottenuti. Ho sempre compensato le tue spese anche nei giorni più bui per la mia attività. Non ho mai mantenuto la mia parola?";
			link.l1 = "Uhmm... No... Voglio solo essere pagato, tutto qui.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Vediamo ora..."+pchar.name+", sei il mio miglior agente e conto di fare affari con te anche in futuro. ";
			link.l1 = "Bene, "+npchar.name+". Ma devi capirmi anche tu - un milione di pesos è una somma enorme.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Capisco molto bene, ma prima devo vendere gli schiavi e solo dopo riceverò denaro.";
			link.l1 = "Bene. Penso che ci siamo capiti.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Splendido. Ci vediamo tra una settimana. E ora devo prepararmi e partire per commerciare con il mio cliente.";
			link.l1 = "Non ti disturberò allora. Ci vediamo tra una settimana, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Cosa sto facendo qui? Beh... è la mia banca. L'ho comprata due giorni fa. Sei il mio primo cliente e posso offrirti delle condizioni di credito molto allettanti...";
			link.l1 = "Fanculo ai crediti! Dov'è "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Calmati, per favore! È scappato molto tempo fa.";
			link.l1 = "Come?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Non lo sai? È scomparso una settimana fa. Si è scoperto che ha preso tutti gli investimenti dei suoi clienti. Dicono che anche il governatore ne abbia risentito. Questa casa è rimasta e l'ho comprata dalla colonia.";
			link.l1 = "Sparito? Come?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Ho sentito dire che è scappato dalla nostra colonia... Immagino che anche a te debba molto, vero?";
			link.l1 = "Più di un milione! Ma prenderò comunque questo ratto! Dove se n'è andato? Il nome della sua nave?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nessuno sa nulla. Sul serio. È semplicemente sparito. La nave chiamata 'Mauritius' o 'Maurdius' era salpata quel giorno, forse l'ha usata per scappare.";
			link.l1 = "Cazzo! E ho fidato quel bastardo! Aveva un odore di traditore fin dal primo giorno! Ed ero abbastanza stupido da credere che fossimo veri partner! Ma un giorno lo farò pentire... Va bene,"+npchar.name+", Mi scuso per il mio comportamento... Se sei un buon uomo, tratterò con te in futuro, ne sono sicuro, ma per ora, addio.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Va bene. Capisco. Se avrai bisogno di denaro o vorrai investire, sono sempre al tuo servizio.";
			link.l1 = "Grazie. Ma preferirei tenere i miei soldi con me. Arrivederci.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Davvero? Sembra che non voglia parlare con me di persona.... Va bene, discutiamo la questione con te. "+pchar.GenQuest.Noblelombard.Name+" mi deve "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" e anche il mio interesse - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+"per tre mesi. Se non vedo soldi nel giorno più vicino allora venderò il suo reliquiario e non mi importa del suo valore per lui. Gli affari sono affari.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Splendido! In tal caso ti pagherò l'intera somma con tutti gli interessi immediatamente - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Prenderà il suo reliquario da solo. Ecco i tuoi soldi.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Il mio cliente avrà i soldi tra tre mesi. Facciamo un accordo, ti pagherò gli interessi per gli ultimi tre mesi e per i prossimi tre mesi."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". E il debito stesso ti sarà pagato più tardi.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Il mio cliente avrà i soldi tra tre mesi. Che ne dici se ti pago gli interessi degli ultimi tre mesi e aspetti finché il mio cliente avrà abbastanza denaro?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Questa rarità costa una fortuna! Sembra che il mio cliente debba pagarlo da solo.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Eccellente! Tutto è andato bene, ho ricevuto i miei soldi e "+pchar.GenQuest.Noblelombard.Name+" riavrà indietro il suo reliquiario.";
			link.l1 = "È stato un piacere fare affari con te, "+npchar.name+"! Addio ora.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Mm.. Va bene. Questo mi va bene. Ma se "+pchar.GenQuest.Noblelombard.Name+" se non trova i soldi in tre mesi, non farò più ritardi. Assicurati che lo sappia.";
				link.l1 = "Lo farò! Sono contento che abbiamo fatto un accordo. Addio ora.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "No. Non funzionerà. Ho bisogno dell'intera somma e prima del tramonto. Assicurati che il tuo 'cliente' lo sappia. Non ho altro da dirti.";
				link.l1 = "Mh... bene. Peccato che tu non voglia scendere a compromessi.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Mh.. Va bene. Lo accetto solo per rispetto del tuo cliente. Ma se "+pchar.GenQuest.Noblelombard.Name+"se non trova i soldi in tre mesi, non farò un altro ritardo. Assicurati che lo sappia.";
				link.l1 = "Lo farò! Sono contento che abbiamo fatto un accordo. Addio ora.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "No. Non funzionerà. Ho bisogno dell'intera somma e prima del tramonto. Assicurati che il tuo 'cliente' lo sappia. Non ho altro da dirti.";
				link.l1 = "Mm... va bene. Peccato che non vuoi fare compromessi.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Davvero!"+pchar.GenQuest.Noblelombard.Name+" non ha aperto un deposito a tuo nome. Non è nemmeno nella nostra colonia - è salpato per l'Europa. Ti dico che non ho mai visto un uomo così disonesto. Voleva ingannarmi ma non ci è riuscito - ho alcuni trucchi miei...";
				link.l1 = "Bastardo! Mi aveva dato la sua parola....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Corretto. "+pchar.GenQuest.Noblelombard.Name+" ha effettuato un deposito a tuo nome. Per favore, prendilo...";
				link.l1 = "Splendido! Addio, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Non esiste una cosa del genere per persone come "+pchar.GenQuest.Noblelombard.Name+" perché non hanno onore né coscienza. Immagino che ti abbia truffato?";
			link.l1 = "Suppongo che abbia. Comunque, "+npchar.name+", Non ho intenzione di restare qui per molto tempo e l'Europa è piccola... Forse, ci incontreremo un giorno. Addio!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard"); // лесник с нпчара на пчара
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard");// с нпчара на пчара  лесник
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Signore, non la conosco. Presto soldi solo ai cittadini locali o ai capitani. Mi perdoni...";
			link.l1 = "Capisco. Peccato però.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "Ch-che... Cosa intendi?";
			link.l1 = "Sei un maledetto ratto! Ora ascoltami attentamente: non sono così stupido. Pinette ha scritto due copie della lettera. Te ne ho dato una, la seconda è in possesso del mio agente di fiducia. Se mi succede qualcosa - il mio uomo la consegnerà direttamente nelle mani del governatore...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Allora ti suggerisco di pregare per la mia buona salute in chiesa ad ogni sermone mattutino invece di mandare assassini per la mia vita. Un ultimo avvertimento! Muovi un dito contro di me e sei fottuto. Capito? Bene. Fai un respiro profondo e continua a contare i tuoi dobloni.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "Non voglio parlare con te.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Certo! Molti vogliono solo prendere i loro soldi e andarsene. Soprattutto considerando le recenti voci...";
			link.l1 = "Quali voci?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "Dicono che le condizioni dell'equipaggio stiano peggiorando. Monsieur Blackwood ha persino iniziato a tollerare perdite regolari - una cosa che non era mai successa prima. Ma non è affare mio. Io vendo solo merci. Quindi, cosa ti interessa?";
			link.l1 = "Passiamo ai fatti.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
