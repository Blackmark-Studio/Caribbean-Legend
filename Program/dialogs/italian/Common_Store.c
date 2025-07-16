// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'allarme è stato dato in città, e tutti ti stanno cercando. Se fossi in te, non resterei lì.","Tutte le guardie della città stanno setacciando la città alla tua ricerca. Non sono uno sciocco e non parlerò con te!","Corsa, "+GetSexPhrase("compagno","ragazza")+", prima che i soldati ti trasformino in un setaccio..."),LinkRandPhrase("Di cosa hai bisogno, "+GetSexPhrase("birbante","birbante")+"?! Le guardie cittadine hanno già il tuo odore, non andrai lontano, "+GetSexPhrase("sporco pirata","sporcizia assassina")+"!","Sporco assassino, lascia subito la mia casa! Guardie!","Non ho paura di te, "+GetSexPhrase("striscio","puzzola")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è mai un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi quella cazzo di bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti strappo quella sporca lingua!!","Eh, "+GetWorkTypeOfMan(npchar,"")+", e tutti lì - sono qui per catturare i pirati! Ecco cosa ti dirò, amico: siediti tranquillo e non morirai..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Ehi, bastardo! Pensi di poter prendere tutto quello che vuoi? Certamente no! Ragazzi! Alle armi! Tagliate il pazzo!","Se vuoi qualcosa, comprala, bestia! Ora ti farò vedere io! Ragazzi, prendete le vostre armi! Allerta!");
				link.l1 = RandPhraseSimple("Eh? Cosa?","Eh, perché stai facendo questo?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Vorrei acquistare un lotto di vino europeo da te - cinquanta-sei bottiglie. Mi è stato detto che ne avevi abbastanza in magazzino."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Ciao di nuovo. Per favore dai un'occhiata a questa lettera - forse riconsidereresti la tua posizione riguardo la vendita di vino a me?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Sono di nuovo io. Possiamo riprendere il nostro affare sul vino interrotto? Sono riuscito a racimolare abbastanza soldi."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Desiderava comprare qualcosa, signore?";
				Link.l1 = "Certo che l'ho fatto - a cosa servono altrimenti i negozi? Mostrami le tue merci.";
				Link.l1.go = "trade_1";
				Link.l2 = "Sono venuto per un affare particolare...";
				Link.l2.go = "quests";
				Link.l3 = "Mi dispiace, ma devo andare.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Ascolta, signore, sto cercando un lavoro. Non un lavoro a tempo pieno o di trasporto pesante, ma più come fare commissioni, per così dire. Hai per caso bisogno di assistenza?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "Ho completato il tuo incarico. Ho trovato Gralam Lavoie.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Incontra il tuo nuovo assistente, signore.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "Sono di nuovo qui, signore. Sono venuto per la mia ricompensa.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Dai un'occhiata a questi orecchini, signore. Li ho trovati sul corpo di un bandito ucciso nella giungla. Questo è chiaramente il lavoro di un fine gioielliere che, sono sicuro, non è di queste parti. C'è qualcosa che puoi dire su questi orecchini?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Capitano, grazie per avermi salvato.";
				Link.l1 = "Oh, sei il benvenuto.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Cosa c'è, capitano? Hai perso qualcosa? Perché stai girando così nel mio negozio?";
				Link.l1 = "Ebbene, immagina un po' - ce l'ho fatta davvero! Dove diavolo è quel maledetto Gerard LeCroix? Ho completato tutti i compiti dati da Florian Shoke, e, possa lo squalo inghiottirmi intero, ho avuto un maledetto brutto momento per farlo! E ora, quando vengo a riscuotere la mia ricompensa, si scopre che questo uccello è volato via!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Come posso dirtelo... Perso. Hai visto il mio cliente? Si chiama Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Capitano, vorrei chiederti un favore. Mi aiuterai?";
				link.l1 = "Come posso aiutarti?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Piacere di conoscerti, signore! Sei nuovo in queste terre?","Benvenuto, capitano! Il mio negozio è al tuo servizio, signore.","Signore, per favore entrate! Sono felice di offrirvi le migliori merci che potete comprare su quest'arcipelago."),LinkRandPhrase("Oh, monsieur capitano! Le migliori merci in tutte le colonie francesi - proprio qui e ora e esclusivamente per te!","Che piacere vederti, signore! Il miglior negozio con i migliori prodotti francesi - al tuo servizio!","Ci siamo già incontrati prima, signor capitano? Sai, il mio negozio è raffinato quanto i migliori negozi della madrepatria!"),LinkRandPhrase("Oh! Signor capitano! Sono così felice di vederti nel mio negozio!","Sono felice di accogliere un così brillante cavaliere nel miglior negozio di tutte le colonie spagnole!","Oh, nobile hidalgo! Il destino stesso ti ha portato nel mio umile negozio! Qui troverai tutto ciò che potresti desiderare!"),LinkRandPhrase("Buon pomeriggio, signor capitano. È la vostra prima visita qui?","Salve, signore. È la sua prima visita qui? Le assicuro che la qualità dei nostri prodotti olandesi la sorprenderà piacevolmente!","Prego, entrate, signor capitano! Le merci migliori al prezzo più basso disponibile - questa è la via olandese al commercio!"));
			Link.l1 = LinkRandPhrase("Piacevole incontrarti anche tu. Il mio nome è "+GetFullName(pchar)+" e sono piuttosto nuovo in queste terre. Bene, mostrami le ricchezze dell'arcipelago!","Piacevole conoscervi, anche io. Io sono "+GetFullName(pchar)+". capitano della nave '"+pchar.ship.name+"'. Allora, quali sono le offerte imperdibili?",""+GetFullName(pchar)+", capitano della nave '"+pchar.ship.name+"', piacere di conoscerti. Allora, cosa puoi offrirmi?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Capitano Helen! Sempre un piacere.";
				link.l1 = "Come lo sono io per te, grazie.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'allarme è stato dato in città, e tutti ti stanno cercando. Se fossi in te, non ci resterei.","Tutte le guardie della città stanno setacciando la città alla tua ricerca. Non sono un idiota e non parlerò con te!","Corsa, "+GetSexPhrase("compagno","ragazza")+", prima che i soldati ti trasformino in un setaccio..."),LinkRandPhrase("Di cosa hai bisogno, "+GetSexPhrase("birbante","birbante")+"?! Le guardie della città hanno già il tuo odore, non andrai lontano, "+GetSexPhrase("sporco pirata","sporcizia omicida")+"!","Sporco assassino, lascia subito la mia casa! Guardie!","Non ho paura di te, "+GetSexPhrase("verme","puzzolente")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è mai un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti strapperò quella sporca lingua!","Eh, "+GetWorkTypeOfMan(npchar,"")+", e tutti lì - sono qui per catturare i pirati! Ecco cosa ti dico, amico: siediti tranquillo e non morirai..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Per favore, perdonami, ma ora non ho tempo per te.";
				link.l1 = "Sì, certo. Passerò un'altra volta, allora.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Capitano, grazie per avermi salvato.";
				Link.l1 = "Oh, sei il benvenuto.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Cosa c'è, capitano? Hai perso qualcosa? Perché stai correndo in giro per il mio negozio in questo modo?";
				Link.l1 = "Ebbene, immagina un po' - l'ho fatto davvero! Dove diavolo si trova quel maledetto Gerard LeCroix? Ho completato tutti i compiti dati da Florian Shoke, e, che lo squalo mi ingoia intero, mi sono davvero impegnato per farlo! E ora, quando vengo a raccogliere la mia ricompensa, si scopre che questo uccellino è volato via!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Come posso dirlo... Perso. Hai visto il mio cliente? Si chiama Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Capitano, vorrei chiederti un favore. Mi aiuterai?";
				link.l1 = "Come posso aiutarti?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, guarda chi c'è! Beh, come si suol dire, i soldi non hanno odore, quindi entra, capitano, e facciamo affari...","Non posso dire che sono felice di vederti, "+GetFullName(pchar)+"... Ma posso ancora commerciare con te.","Eh-eh... Beh, non ti inviterei a casa mia, capitano - ma il mio negozio è sempre a tua disposizione."),LinkRandPhrase("Oh, guarda chi c'è! Non è quello "+GetFullName(pchar)+"! Vuoi fare affari o semplicemente prendere qualcosa gratis? Ehi, sto solo scherzando...","Non posso dire che sono felice di vederti qui, "+GetAddress_Form(NPChar)+". Ma se hai soldi da spendere - entra, entra...","Vuoi commerciare, capitano "+GetFullName(pchar)+"? Se è così, potresti per favore sbrigarti? Gli altri clienti ti stanno evitando, e questo è cattivo per il mio business,"),LinkRandPhrase("Vuoi fare affari, signore? Solo un secondo, farò i conti - sai, ci sono tipi loschi in giro... Naturalmente, non mi riferisco a te, capitano!","Se ti vedessi in mare aperto, "+GetAddress_Form(NPChar)+", Probabilmente ordinerò di aggiungere vele... Ma qui, nel mio negozio, posso offrirti di fare affari.","Capitano, ti avverto subito: se il tessuto è macchiato di sangue e il caffè puzza di polvere da sparo, non lo prenderò. Altrimenti dai un'occhiata e fai la tua scelta.")),LinkRandPhrase(LinkRandPhrase("E sono lieto di salutarti di nuovo, "+GetAddress_Form(NPChar)+"! Acquistare o vendere - sono sempre felice di aiutarti.","Ti prego, "+GetAddress_Form(NPChar)+", entra! Sono sempre felice di vedere il mio cliente preferito qui. Cosa sarà questa volta - comprare o vendere?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sono così felice di rivederti! Cosa sarà questa volta - comprare o vendere?"),LinkRandPhrase("Ti piacciono i nostri prodotti, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Sono sempre al tuo servizio - dai un'occhiata e fai la tua scelta.","Ciao, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Sono felice di rivederti! Vuoi dare un'occhiata all'assortimento delle nostre merci?","Contento di vederti, capitano! Sapevo che i nostri prodotti di qualità ti sarebbero piaciuti. Vuoi dare un'occhiata alle novità?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Prego, entrate! Tutta la merce solo per voi - e con grandi sconti per questa occasione!","Capitano "+GetFullName(pchar)+", ancora una volta mi hai reso felice con la tua visita! Per favore, fai la tua scelta, quel che preferisci!","Cosa vorresti questa volta, capitano? Sono lieto che tu ricordi ancora come trovarmi. Abbiamo tutte le merci di cui potresti aver bisogno - di qualità superiore!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Così mi stai dando il benvenuto, amico? Bene, me lo ricorderò se ci incontriamo in mare... Smetti di tremare, stavo solo scherzando. Mostrami quello che hai.","Bene, compagno. Potrei aver bisogno delle tue merci, ma non ho bisogno della tua lingua. Puoi tenerla a freno o hai bisogno di aiuto per farlo? Taci e mostrami le tue merci."),RandPhraseSimple("Avviciniamoci agli affari, mercante. Non ho tempo per discutere questioni morali con te, quindi commerciamo semplicemente come persone perbene.","Frena un po', amico. Scherzare va bene, ma ricorda che posso arrabbiarmi... Quindi smetti di irritarmi e mostrami semplicemente la tua merce.")),RandPhraseSimple(RandPhraseSimple("Sono sempre felice di farti visita, amico. Cosa hai in magazzino che potrebbe meritare la mia attenzione?","Sempre un piacere vederti, amico. Allora, cosa c'è di nuovo per i vagabondi del mare che non hanno messo piede sulla terraferma per mesi?"),RandPhraseSimple("E di nuovo mi trovo in "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Meno male che non ero qui per dimenticare. Ma c'è ancora qualcosa nei vostri magazzini per me? È tutto sistemato?","Come hai potuto non venire? Mi fai sempre più piacere di quello. Bene, cosa hai lì?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("Tutti in coperta! ","Tieni l'ispezione! ")+LinkRandPhrase("Cosa fa un "+GetSexPhrase("signore","signore, oh, mi scuso - una signora")+" di fortuna necessario nel mio negozio, eh-eh?","Che sorpresa per un povero vecchio negoziante! Eh-eh!","Allora, quale vento favorevole ti ha portato nel mio negozio?"),LinkRandPhrase("Apri i porti!","Uncini a lato!","Vai dritto avanti!")+RandPhraseSimple("Qui troverai"," Il mio negozio ha")+LinkRandPhrase("i migliori prezzi su tutta l'isola.","un assortimento eccellente di merci."," merci della migliore qualità disponibile.")+RandPhraseSimple("Sono al vostro servizio","Qualunque cosa tu voglia")+", capitano!"),pcharrepphrase(RandPhraseSimple("Qualsiasi merce per "+GetSexPhrase("signori","signori e signore")+" della fortuna! Eheh! Fino a quando non vengono impiccati ad asciugare al sole!","Il vento fa oscillare gli impiccati nel porto e porta il tintinnio delle catene. Ma i soldi non hanno odore, vero?"),"Vorresti "+LinkRandPhrase("acquista i migliori prodotti di "+NationNameGenitive(sti(NPChar.nation)),"compra o vendi il tuo carico","hai un carico profittevole?")+RandPhraseSimple("? Sono al tuo servizio!","! Il mio negozio è al tuo servizio!")+RandPhraseSimple("Contento di vederti","Come vuoi")+", capitano!")),NPCharRepPhrase(npchar,pcharrepphrase("Se vuoi un consiglio, capitano - non risparmiare denaro sulle mitraglie. Sai, i morti sono molto più facili da cercare!","Ho notato subito che sei un "+GetSexPhrase("compagno astuto","ragazza astuta")+". "+RandPhraseSimple("Ma ora posso vedere che sei un vero "+GetSexPhrase("eroe","temerario")+".","Sei giovane, ma "+RandPhraseSimple("mantieni il tuo ingegno con te.","certamente non puoi essere ingannato facilmente."))),pcharrepphrase("Sono disposto a comprare da voi tutto il carico dai premi catturati. Vuoi in argento o in oro? Quella roba è sempre costosa.","La navigazione commerciale è un affare redditizio, capitano "+GetFullName(pchar)+", non è vero?")),NPCharRepPhrase(npchar,RandPhraseSimple("Li abbiamo avvolti tutti stretti in una vela principale Con il doppio di dieci giri di una corda robusta E li abbiamo gettati oltre la vista!",RandPhraseSimple("Quindici uomini su un petto d'uomo morto!","Bevi e il diavolo si è occupato del resto!")+"Yo ho ho e una bottiglia di rum!")+RandPhraseSimple("Cosa c'è, cap?","Cercando di comprare qualcosa, capitano?"),pcharrepphrase("Vedo che sei un abile contrattatore, capitano "+GetFullName(pchar)+". Dato che sei un cliente abituale, ti offro prezzi molto vantaggiosi!","Bene, capitano "+GetFullName(pchar)+", per rispetto a te posso offrire solo un po' di più! Cosa vorresti?")),NPCharRepPhrase(npchar,"Ti giuro, parlare con te mi fa sentire malato."+LinkRandPhrase("Compra un paio di arachidi. Ai maiali piace quella roba.","Ti aspetti che qualcuno lustra i tuoi stivali con del rum qui?",pcharrepphrase("Conosco il tuo tipo. Ti ubriachi di rum - e poi dritto alla forca.","Mi chiedo come tua madre ti abbia permesso di diventare un marinaio! Un marinaio! Saresti stato un sarto molto migliore...")),pcharrepphrase(RandPhraseSimple("Pensavo che ","Speravo che ")+RandPhraseSimple("pensavo che avessi lasciato la nostra isola per sempre.","Non pensavo di rivederti mai più.")+RandPhraseSimple(" I morti ti pendono al collo come macine da mulino...","Ma quanti marinai hai lasciato marcire tra i coralli?!"),"Capitano "+GetFullName(pchar)+", la tua passione per il commercio ha superato tutte le mie aspettative!"+RandPhraseSimple("Vuoi fare acquisti dell'ultimo minuto prima di salpare?","Stai cercando qualcosa di speciale?"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, guarda chi c'è! Beh, come si suol dire, i soldi non hanno odore, quindi entra, capitano, e facciamo affari...","Non posso dire di essere felice di vederti, "+GetFullName(pchar)+"... Ma posso ancora commerciare con te.","Eh-eh... Beh, non ti inviterei a casa mia, capitano - ma il mio negozio è sempre al tuo servizio."),LinkRandPhrase("Oh, guarda chi c'è! Non è quello "+GetFullName(pchar)+"! Vuoi fare un affare o semplicemente prendere qualcosa gratis? Ehi, sto solo scherzando...","Non posso dire che sono felice di vederti qui, "+GetAddress_Form(NPChar)+". Ma se hai soldi da spendere - entra, entra...","Vuoi commerciare, capitano "+GetFullName(pchar)+"? Se sì, potresti per favore fare in fretta? Altri clienti ti stanno evitando, e questo è cattivo per i miei affari,"),LinkRandPhrase("Vuoi fare affari, signore? Solo un secondo, farò quadrare i conti - sai, ci sono tipi poco raccomandabili in giro... Ovviamente, non intendo te, capitano!","Se ti avessi visto in mare aperto, "+GetAddress_Form(NPChar)+", Probabilmente avrei ordinato di aggiungere delle vele... Ma qui, nel mio negozio, posso offrirti di fare affari.","Capitano, ti avverto subito: se il tessuto è macchiato di sangue e il caffè puzza di polvere da sparo, non lo prenderò. Altrimenti dai un'occhiata e fai la tua scelta.")),LinkRandPhrase(LinkRandPhrase("E sono lieto di salutarti di nuovo, "+GetAddress_Form(NPChar)+"! Acquisto o vendita - sono sempre felice di aiutarti.","Ti prego, "+GetAddress_Form(NPChar)+", entra! Sono sempre felice di vedere il mio cliente preferito qui. Cosa sarà questa volta - comprare o vendere?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sono così felice di rivederti! Cosa sarà questa volta - comprare o vendere?"),LinkRandPhrase("Ti piacciono i nostri prodotti, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Sono sempre a vostra disposizione - date un'occhiata e fate la vostra scelta.","Ciao, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Sono lieto di rivederti! Vuoi dare un'occhiata all'assortimento delle nostre merci?","Contento di vederti, capitano! Sapevo che ti sarebbero piaciuti i nostri prodotti di qualità. Vuoi dare un'occhiata alle novità?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Per favore, entra! Tutta la merce solo per te - e con grandi sconti in questa occasione!","Capitano "+GetFullName(pchar)+", ancora una volta mi hai reso felice con la tua visita! Per favore, fai la tua scelta, qualunque cosa ti piaccia!","Cosa gradirebbe stavolta, capitano? Sono lieto che ricordi ancora come trovarmi. Abbiamo tutte le merci di cui potresti aver bisogno - della migliore qualità!")));
					link.l14 = "Ascolta, sto per partire per Porto Bello ora e vorrei comprare da te una spedizione di caffè e cacao. Diciamo, trecento unità di entrambi."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, guarda chi c'è! Beh, come si suol dire, i soldi non hanno odore, quindi entra, capitano, e facciamo affari...","Non posso dire che sono lieto di vederti, "+GetFullName(pchar)+"... Ma posso ancora commerciare con te.","Eh eh... Beh, non ti inviterei a casa mia, capitano - ma il mio negozio è sempre a tua disposizione."),LinkRandPhrase("Oh, guarda chi c'è! Non è quello "+GetFullName(pchar)+"! Vuoi fare affari o prendere roba gratis? Ehi, sto solo scherzando...","Non posso dire che sono felice di vederti qui, "+GetAddress_Form(NPChar)+". Ma se hai soldi da spendere - entra, entra...","Vuoi fare affari, capitano "+GetFullName(pchar)+"? Se sì, potresti per favore sbrigarti? Gli altri clienti ti stanno evitando, e questo è cattivo per il mio business,"),LinkRandPhrase("Vuoi fare affari, signore? Solo un secondo, farò quadrare i conti - sai, ci sono individui loschi in giro... Naturalmente, non mi riferisco a te, capitano!","Se ti avessi visto in mare aperto, "+GetAddress_Form(NPChar)+", Probabilmente ordinerò di aggiungere delle vele... Ma qui, nel mio negozio, posso offrirti di fare affari.","Capitano, ti avverto subito: se la stoffa è macchiata di sangue e il caffè puzza di polvere da sparo, non lo prenderò. Altrimenti dai un'occhiata e fai la tua scelta.")),LinkRandPhrase(LinkRandPhrase("E sono lieto di salutarti di nuovo, "+GetAddress_Form(NPChar)+"! Acquisto o vendita - sono sempre felice di aiutarti.","Ti prego, "+GetAddress_Form(NPChar)+", entra pure! Sono sempre felice di vedere il mio cliente preferito qui. Cosa sarà questa volta - acquistare o vendere?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sono così felice di rivederti! Che cosa sarà questa volta - comprare o vendere?"),LinkRandPhrase("Ti piacciono i nostri beni, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Sono sempre a tua disposizione - dai un'occhiata e scegli.","Ciao, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Sono felice di rivederti! Vuoi dare un'occhiata all'assortimento delle nostre merci?","Contento di vederti, capitano! Sapevo che ti sarebbero piaciuti i nostri prodotti di qualità. Vuoi dare un'occhiata alle novità?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Prego, entrate! Tutti i beni solo per voi - e con grandi sconti in questa occasione!","Capitano "+GetFullName(pchar)+", ancora una volta mi hai reso felice con la tua visita! Per favore, scegli quello che preferisci!","Cosa desideri questa volta, capitano? Sono lieto che tu ricordi ancora come trovarmi. Abbiamo tutte le merci di cui potresti aver bisogno - della migliore qualità!")));
				link.l14 = "Sono qui per il caffè e il cacao."; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Mostrami cosa hai, vecchio pirata!","Volevo solo dare un'occhiata alle tue merci, buon uomo."),pcharrepphrase("Giuro sul patibolo, "+GetFullName(npchar)+", Non mi farai desistere! Mostrami le tue merci subito!","Diamo un'occhiata ai tuoi beni, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Certo! I morti non mordono! Ora, cosa hai nella tua stiva?","È meglio se passi ai tuoi affari, buon uomo. Che tipo di merci puoi offrirmi?"),pcharrepphrase("Verrà un giorno in cui diventerai il mio premio, he-he. Sto solo scherzando. Mostrami le tue merci.","Discutiamo le nostre questioni commerciali, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Cosa voglio? Voglio comprare qualcosa!","Bere ti porterà alla tua tomba, "+GetFullName(npchar)+". Voglio dare un'occhiata alle tue merci."),pcharrepphrase("Conosco i tuoi sconti! Due chili di cacao al prezzo di tre! Ora mostrami la tua merce.","Sempre buono. Allora contrattiamo.")),"Mostrami le tue merci. Meno si dice, prima si risolve. Sono di fretta.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Oh, vorrei davvero pugnalare qualcuno, Va bene, andiamo al dunque.","Passiamo ad altri affari, buon uomo."),pcharrepphrase("Caspita! Sono qui per un affare diverso!","Voglio parlarti di un affare particolare, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Ho affari con te, vecchio pirata!","Andiamo al dunque, compagno!"),pcharrepphrase("Giuro per il diavolo, non mi ingannerai, mascalzone! Ho affari diversi con te!","Sono assolutamente d'accordo, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", volevo discutere altre questioni con te.")),NPCharRepPhrase(npchar,pcharrepphrase("Già carico? Ho affari con te.","Non sono venuto qui per fare affari, mio buon uomo. Ho altre questioni da risolvere."),pcharrepphrase("Che il tuono ti colpisca per prezzi del genere! Ho affari con te.","Gli sconti sono sempre graditi, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ma ho affari diversi con te.")),NPCharRepPhrase(npchar,pcharrepphrase("Tieni a freno la lingua, vecchio ubriacone, ho affari con te","Sei malato a causa del rum, immagino. Non che io sia particolarmente affezionato a te, comunque. Andiamo al dunque."),pcharrepphrase("Mi hai già truffato, mascalzone! Ho affari con te.","La tua ironia è fuori luogo. Ho altri affari con te.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Prima gli affari, poi il divertimento. Voglio chiederti qualcosa.","Non ora. Ho bisogno di informazioni."),pcharrepphrase("All'inferno con i tuoi prezzi! Prima mi dirai tutto ciò di cui ho bisogno.","Con piacere. Volevo chiedere qualcosa.")),NPCharRepPhrase(npchar,pcharrepphrase("Grazie per il consiglio, vecchio assassino. Volevo chiederti qualcosa.","Avevo una domanda particolare."),pcharrepphrase("L'oro può aspettare. Volevo chiederti qualcosa.","Sì, sono d'accordo. Volevo chiederti qualcosa.")),NPCharRepPhrase(npchar,pcharrepphrase("Credo tu sappia, cosa stavo per chiedere.","Spero che risponderai alla mia domanda."),pcharrepphrase("Riesci a pensare a qualcosa oltre alle tue etichette di prezzo? Perché è di quello che volevo parlarti.","Questo non mi interessa. Ho bisogno di informazioni.")),NPCharRepPhrase(npchar,pcharrepphrase("Non farti troppe illusioni, amico! Stavo solo per farti una domanda.","Non farti prendere troppo dall'entusiasmo, o avrai un colpo. Rispondi solo a una domanda e me ne andrò"),pcharrepphrase("Non mi aspetto che tu dica qualcosa di intelligente, visto che hai il cervello di una scarafaggia. Ma sicuramente devi sapere qualcosa.","Non ti tratterrò a lungo. Solo una domanda.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "Sono qui per un'altra questione.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Vi ho portato una lista dei prezzi dalla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Vorrei acquistare un lotto di vino europeo da te - cinquanta-sessanta bottiglie. Mi è stato detto che ne avete abbastanza in magazzino.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Ciao di nuovo. Per favore, dai un'occhiata a questa lettera - forse riconsidereresti la tua posizione riguardo la vendita di vino a me?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Sono di nuovo io. Possiamo riprendere il nostro affare interrotto sul vino? Sono riuscito a racimolare abbastanza soldi."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Ascolta, signore, sto cercando un lavoro. Non come un lavoro a tempo pieno o il trasporto di sacchi di merce, ma più come fare commissioni, per così dire. Hai per caso bisogno di assistenza?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "Ho completato il tuo incarico. Ho trovato Gralam Lavoie.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Incontra il tuo nuovo assistente, signore.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "Sono io di nuovo, signore. Sono venuto per la mia ricompensa.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Dai un'occhiata a questi orecchini, signore. Li ho trovati sul corpo di un bandito che è stato ucciso nella giungla. Questo è chiaramente il lavoro di un fine gioielliere che, sono sicuro, non è da queste parti. C'è qualcosa che puoi dire su questi orecchini?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Salve, sono venuto su invito di vostro figlio."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Si tratta di tua figlia...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Arrivederci, vecchio ubriacone.","Buona giornata, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Non andare da nessuna parte, tornerò di nuovo.","È stato bello averti qui, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Arrivederci!")),NPCharRepPhrase(npchar,pcharrepphrase("Salpa!","Addio, buon uomo."),pcharrepphrase("Ehi! Cosa stai nascondendo lì? Rum? No?! Va bene, vado a inumidire la gola.","Mi dispiace, ma ho affari urgenti in città.")),NPCharRepPhrase(npchar,pcharrepphrase("Eh! Beh, ci vediamo!","Devo andare. Addio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("E non osare nemmeno di discutere con me! Non ho tempo per questo!","Forse, devo andare a controllare cosa succede sulla mia nave. Addio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Come stai, vecchio amico? Sono io - "+GetFullName(pchar)+"! Riposati e smaltisci l'ubriacatura, tornerò più tardi.","Temerei che il tuo fegato ti finirà prima che io abbia l'opportunità di tornare da te."),pcharrepphrase("Continua a contare i tuoi guinei e dobloni, vecchia volpe! Tornerò.","Ero felice di vederti, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "Cosa posso fare per te? Rifornire l'Arcobaleno, vendere qualche bottino? Dubito che tu sia interessato alle attuali spedizioni redditizie, ah-ah.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Mostrami cosa hai, vecchio pirata!","Volevo solo dare un'occhiata alle vostre merci, mio buon uomo."),pcharrepphrase("Giuro sulla forca, "+GetFullName(npchar)+", Non ti permetterò di sviarmi! Mostrami le tue merci adesso!","Diamo un'occhiata ai tuoi beni, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Questo è certo! I morti non mordono! Ora, cosa hai nella tua stiva?","È meglio che ti dedichi ai tuoi affari, mio buon uomo. Che tipo di merci puoi offrirmi?"),pcharrepphrase("Verrà il giorno in cui diventerai il mio premio, he-he. Sto solo scherzando. Mostrami i tuoi beni.","Discutiamo dei nostri affari commerciali, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Cosa voglio? Voglio comprare qualcosa!","Bere ti porterà alla tua tomba, "+GetFullName(npchar)+". Voglio dare un'occhiata alle tue merci."),pcharrepphrase("Conosco i tuoi sconti! Due chili di cacao al prezzo di tre! Ora mostrami le tue merci.","È sempre una buona cosa. Allora, contrattiamo.")),"Mostrami la tua merce. Meno si dice, meglio è. Sono di fretta.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Oh, mi piacerebbe davvero pugnalare qualcuno, bene, passiamo ai fatti.","Passiamo ad altri affari, mio buon uomo."),pcharrepphrase("Caspita! Sono qui per un affare diverso!","Voglio parlarti di un affare particolare, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Ho affari con te, vecchio pirata!","Andiamo al dunque, amico!"),pcharrepphrase("Giuro per il diavolo, non mi ingannerai, mascalzone! Ho affari diversi con te!","Sono assolutamente d'accordo, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", Volevo discutere di altre questioni con te.")),NPCharRepPhrase(npchar,pcharrepphrase("Già carico? Ho affari con te.","Non sono venuto qui per commerciare, mio buon uomo. Ho altri affari."),pcharrepphrase("Che il tuono ti colpisca per prezzi come questi! Ho affari con te.","Gli sconti sono sempre graditi, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ma ho affari diversi con te.")),NPCharRepPhrase(npchar,pcharrepphrase("Tieni a freno la lingua, vecchio ubriacone, ho affari con te","Sei malato a causa del rum, immagino. Non che io sia particolarmente affezionato a te, comunque. Facciamo sul serio."),pcharrepphrase("Mi hai già fregato, furfante! Ho affari con te.","La tua ironia è fuori luogo. Ho altri affari con te.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Prima gli affari, poi il divertimento. Voglio chiederti qualcosa.","Non ora. Ho bisogno di informazioni."),pcharrepphrase("All'inferno con i tuoi prezzi! Prima mi dirai tutto quello di cui ho bisogno.","Con piacere. Volevo chiedere qualcosa.")),NPCharRepPhrase(npchar,pcharrepphrase("Grazie per il consiglio, vecchio assassino. Volevo chiederti qualcosa.","Avevo una domanda particolare."),pcharrepphrase("L'oro può aspettare. Volevo chiederti qualcosa.","Sì, sono d'accordo. Volevo chiederti qualcosa.")),NPCharRepPhrase(npchar,pcharrepphrase("Credo proprio che tu sappia, cosa stavo per chiedere.","Spero che risponderai alla mia domanda."),pcharrepphrase("Riesci a pensare a qualcosa oltre alle tue etichette dei prezzi? Perché era quello di cui volevo parlarti.","Non mi interessa. Ho bisogno di informazioni.")),NPCharRepPhrase(npchar,pcharrepphrase("Non farti prendere troppo dall'entusiasmo, amico! Stavo solo per farti una domanda.","Non ti eccitare troppo, o avrai un colpo. Rispondi solo a una domanda, e me ne andrò"),pcharrepphrase("Non mi aspetto che tu dica qualcosa di intelligente, dato che hai il cervello di una scarafaggia. Ma sicuramente devi sapere qualcosa.","Non ti tratterrò a lungo. Solo una domanda.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Arrivederci, vecchio ubriacone.","Buona giornata, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Non andare da nessuna parte, tornerò di nuovo.","È stato un piacere averti qui, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Arrivederci!")),NPCharRepPhrase(npchar,pcharrepphrase("Salpate!","Arrivederci, buon uomo."),pcharrepphrase("Ehi! Cosa stai nascondendo lì? Rum? No?! Va bene, vado a inumidire la gola.","Mi dispiace, ma ho degli affari urgenti in città.")),NPCharRepPhrase(npchar,pcharrepphrase("Eh! Beh, ci vediamo!","Devo andare. Addio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("E non osare nemmeno discutere con me! Non ho tempo per questo!","Forse, ho bisogno di andare a controllare cosa succede sulla mia nave. Addio, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Cosa c'è, vecchio amico? Sono io - "+GetFullName(pchar)+"! Dormi fino a sobriarti, tornerò più tardi.","Temo che il tuo fegato ti farà fuori prima che io abbia l'opportunità di tornare da te."),pcharrepphrase("Continua a contare i tuoi guinei e dobloni, vecchia volpe! Tornerò.","Ero felice di vederti, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Mi dispiace, ma sono troppo occupato ora. Così tanti clienti! Torna domani.";
				link.l1 = "Oh, davvero? Beh, allora tornerò più tardi.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("Ho palle di cannone, tela da vele, medicine, legname pregiato e altre merci! Cosa ti interessa?","Vuoi comprare zucchero e spezie? O, forse, rum e polvere da sparo?");
			link.l1 = pcharrepphrase(LinkRandPhrase("Ho un sacco di bottino nella mia stiva! I soldi non hanno odore, vero?","Devo scaricare il bottino nella mia stiva e riempirla con il tuo oro. Ah-ah!","Oh, so che venderesti tua madre per un sacco di dobloni pieni! Ma ho solo bisogno di rifornire le mie scorte."),LinkRandPhrase("Voglio vendere il mio carico e rifornire le scorte.","Voglio acquistare merci da vendere.","Mostrami le palle di cannone, le bombe e roba del genere."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Il mio cassiere farà tutti gli acquisti necessari...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Me ne vado senza fare affari. Ci vediamo!","Vado a inumidire la mia gola. Tu resta lì!"),RandPhraseSimple("No, non ho tempo per il commercio al momento. Addio.","Mi dispiace, ho affari urgenti da sbrigare. Arrivederci!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Sono tutto orecchie.";
			link.l1 = "Ho portato il vostro fuggitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitano, grazie mille! Come sta? È ferita? È passato un giorno da quando è scappata, quella birba. Sembra che le farò del male? Le ho trovato un marito. Ho organizzato un matrimonio. Un ricco, giovane fidanzato. Potrebbe avere un brutto aspetto, ma chi se ne importa delle fattezze del viso. No! Cerca sempre di avere tutto a modo suo. Proprio come sua madre ha sempre fatto, per l'amor del cielo!\nSebbene, non sarebbe nemmeno nata se sua madre non fosse scappata con qualche idiota promettente tempo fa... beh, non importa... La gioventù è ingenua, stupida e crudele.";
			link.l1 = "Certo, sei tu il padre e tocca a te decidere, ma non mi sbrigerei con il matrimonio...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Cosa ne sai tu? Hai figli tuoi? No? Parlami quando ne avrai...\nSì... Ho promesso una ricompensa a chi me la riporterà, ecco, prendila.";
			link.l1 = "Grazie. E tieni d'occhio lei. Ho il sospetto che non si fermerà a questo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, quindi tu sei "+GetSexPhrase("quel capitano, che ha portato","quella ragazza, che ha portato")+" mio figlio prodigo con una giovane sposa?";
				link.l1 = "Sì, li ho aiutati a scappare.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, eccoti "+GetSexPhrase("lui è, il nostro benefattore","lei è, la nostra benefattrice")+". Mi aspetto una ricompensa, vero?";
				link.l1 = "Beh, mi basta senza ricompensa, ma un tuo ringraziamento sarebbe sufficiente.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sono molto grato a voi che non avete abbandonato mio figlio in una situazione disperata e lo avete aiutato a trovare una via d'uscita da una situazione delicata. Permettetemi di ringraziarvi e per favore accettate questa modesta somma e un regalo da parte mia personale.";
			link.l1 = "Grazie. Aiutare questa giovane coppia è stato un piacere per me.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Grazie? Che grazie?! Quel testone è rimasto senza lavoro per mezzo anno - e guardalo, ha tutto il tempo per gli amori! Quando avevo la sua età, gestivo già il mio business! Pff! Un governatore ha una figlia da maritare - e quel stupido ha portato una sgualdrina senza parenti o amici a casa mia e ha osato chiedere la mia benedizione!";
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
			dialog.text = "Quali sentimenti? Di che tipo di sentimenti stai parlando? Sentimenti... come si può essere così frivoli alla tua età?! Vergognati di assecondare i capricci dei giovani e di comportarti come un ruffiano! Non solo hai preso una ragazza dalla sua casa, ma hai anche rovinato la vita del mio giovane inesperto. Non ci saranno ringraziamenti per te. Addio.";
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
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...Già fatto. Ora tutto ciò che resta è decidere, quale nave caricare.","Il vostro tesoriere ha già fatto ciò. Decidiamo ora, quale nave deve essere caricata.","Sì, "+PChar.name+", Lo so. Mi ha già fatto visita. Ora, quale nave stiamo per caricare?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "Mi sono fatto un pensiero, non ho bisogno di nulla.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Stai scherzando con me? Dov'è la tua nave? Non la vedo al molo!","Giuro al diavolo, non mi ingannerai! La tua nave non è al molo!"),pcharrepphrase("Non vedo la tua nave nel porto, capitano "+GetFullName(pchar)+". Spero davvero che non sia il 'Olandese Volante'?","Capitano, è molto più facile caricare il carico dal molo. E preferisco farlo in quel modo. Porta la tua nave velocemente e torna indietro."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Che problema! Va bene, vecchio furfante, a presto!","Non volevo ingannarti, "+GetFullName(npchar)+", una nave è dall'altra parte dell'isola."),pcharrepphrase("No. La mia nave si chiama 'Perla Nera'. Perché sei diventato pallido? Ahah! Sto solo scherzando!","Grazie per il consiglio, lo utilizzerò sicuramente."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Allora, capitano, quale nave stiamo per caricare?","Allora, quale nave deve essere caricata?",PChar.name+", in quale stiva della nave dovremmo caricare le merci?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "Ho cambiato idea, non ho bisogno di nulla.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Tutto è pronto! Il caricamento della nave selezionata è iniziato.","Bene, il carico delle merci sulla nave selezionata è iniziato.","Capitano, l'imbarco delle merci sulla nave selezionata è iniziato.");
					link.l1 = "Grazie. È stato un piacere fare affari con te.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Capitano, tutte le merci richieste dal vostro tesoriere, sono già presenti a bordo della nave che avete indicato!","Capitano, tutte le merci sono già presenti a bordo della nave che hai indicato!","Capitano, quella nave non ha bisogno di servizi, dato che tutte le merci ci sono già.");
					link.l1 = "Sì, certo.";
					link.l1.go = "exit";
					link.l2 = "Immagino che dovrò scegliere un'altra nave, allora.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Temerei, una nave di quel tipo semplicemente non può contenere così tanto.","Capitano, la tua nave non potrà contenere così tanto carico!","Capitano, la stiva della tua nave non può contenere così tanto carico!");
				link.l1 = "Sì, hai ragione. Dovrò scegliere un'altra nave.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Ho riflettuto... Non ho bisogno di comprare nulla.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Stai scherzando? Dov'è la tua nave? Non la vedo al molo!","Giuro al diavolo, non mi ingannerai! La tua nave non è al molo!"),pcharrepphrase("Non vedo la tua nave nel porto, capitano "+GetFullName(pchar)+". Spero davvero che non sia il 'Olandese Volante'?","Capitano, è molto più facile caricare il carico dal molo. Porta la tua nave veloce e torna."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Che guaio! Va bene, vecchio furfante, ci vediamo presto!","Non volevo ingannarti, "+GetFullName(npchar)+", una nave è sull'altro lato dell'isola."),pcharrepphrase("No. La mia nave si chiama 'Perla Nera'. Perché sei diventato pallido? Ahaha! Sto solo scherzando!","Grazie per il consiglio, lo utilizzeranno."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Per quanto riguarda l'affitto, mi devi ancora "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Bene, pagherò l'affitto ora.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Torno più tardi.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Vieni.";
				link.l1 = "Grazie.";
				link.l1.go = "storage_2";
			}
			link.l2 = "No, ho cambiato idea.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Sì, ho un magazzino nel porto - può contenere 50000 quintali di merce. Per "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" ogni mese posso garantire la custodia sicura delle tue merci. "+"Questo include la sorveglianza, la protezione dall'inondazione e la lotta contro i ratti. Cosa ne dici? Inoltre... Avrò bisogno di un pagamento anticipato di un mese.";	
			link.l1 = "Va bene. Posso darci un'occhiata? Ci sono molti ratti lì?";
			link.l1.go = "storage_1";
			link.l2 = "No, sto solo chiedendo. Posso usarlo quando necessario...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Così come ho detto, richiedo il pagamento per un mese in anticipo. E niente ratti!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Devo dire... sei molto mercantile. Ecco i tuoi soldi - affitterò questo capanno.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Devo dire... sei molto mercantile. Va bene, tornerò presto con i soldi.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Te ne vai già? Che peccato - è davvero un ottimo posto a ottime condizioni. Ti assicuro che non troverai un affare come questo da nessun'altra parte nei Caraibi.";
			link.l1 = "Ho detto - assolvi. O stai suggerendo che io paghi per lo stoccaggio dell'aria? Cerca un altro affittuario.";
			link.l1.go = "storage_4";
			link.l2 = "Nessuna parte nei Caraibi, dici? Va bene, lo metterò da parte per un po', allora.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "E per l'affitto, mi devi ancora "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Bene.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Raccogli i tuoi beni, e chiuderò il magazzino.";
				link.l1 = "Bene.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Oh! Sei arrivato proprio in tempo, capitano. Vorrei chiederti di farmi un favore.";
					link.l1 = "Ascoltiamo."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Sono tutto orecchie, capitano.";
				link.l5 = "Ho portato il vostro ordine."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh! Sei arrivato proprio in tempo, capitano. Ho bisogno di un favore speciale.";
				link.l5 = "Ascoltiamo."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Sono tutto orecchie, capitano.";
				link.l5 = "Vi ho portato gli schiavi."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Ascolta, stai commerciando in tutti i tipi di merci... Ieri o oggi - qualcuno ti ha offerto di comprare "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_block")) 
			{
				dialog.text = "Capitano, vorrei chiederti un favore, e sono disposto a pagarti generosamente, se accetti.";
				link.l1 = "Interessante. Beh, qual è il problema?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Capitano, sono lieto di vederti. So già che hai esaudito la mia richiesta riguardo "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Eh! Questo è certo. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" e il carico - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", non appartiene più al tuo rivale."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Mio Signore, capitano... Perché l'hai ucciso? Ti ho solo chiesto di affondare la sua nave! Santa Vergine, ora ho il sangue di un uomo innocente sulle mie mani...";
				link.l1 = "Ehi! Qual è il tuo problema, "+npchar.name+"? Chi se ne importa - non ti darà più fastidio, ed è questo ciò che conta!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Avevo un lavoro, ma "+GetFullName(&Characters[iTmp])+" ha già preso l'impegno di farlo per me.";
				link.l1 = "Oh, davvero? Beh, allora tornerò più tardi.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Che affari?! Dimmi tutto!","Sto ascoltando. Di che affare stai parlando?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("Ho un carico di merci per il tuo negozio nella stiva della mia nave.","La mia nave è stata noleggiata per consegnare la merce al tuo negozio. Le merci stanno venendo scaricate ora.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Sfortunatamente, sono costretto a rinunciare ai loro impegni. La situazione politica non mi permette di consegnare la merce.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Posso offrirti di affittare la mia nave per il trasporto di merci.","Ho una grande nave e posso consegnare qualsiasi carico ovunque tu possa averne bisogno.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Vorresti noleggiare una nave, "+GetAddress_FormToNPC(NPChar)+"? Ho una nave affidabile e un equipaggio esperto.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Sono qui per un'altra questione.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, ero davvero sfinito in mare... Beh, amico, i soldi sono un vero problema per me adesso.","Bene, vecchia volpe, parliamo dei nostri affari finanziari."),RandPhraseSimple("Vorrei discutere con te delle questioni finanziarie.","Parliamo di questioni finanziarie, dobbiamo discuterne."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Sono qui su richiesta di un uomo. Il suo nome è governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato da te. Dovrei ritirare qualcosa...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Potresti dirmi gli ultimi pettegolezzi? Comunque passi tutto il giorno qui.","Non fare storie, vecchio truffatore - meglio dirmi cosa c'è di nuovo sulla terraferma?"),RandPhraseSimple("Sembra che abbia passato un'eternità in mare. Cosa c'è di nuovo nella tua regione?","Probabilmente conosci tutte le ultime notizie? Cosa di importante è successo?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Portami al magazzino. Voglio vedere in che condizioni si trova.";
						link.l7.go = "storage_0";
						link.l8 = "Ho deciso di liberare il magazzino. Non ne ho bisogno ora.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Scusami, mio buon uomo - per caso, non stai affittando magazzini?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Vedi, sto cercando di trovare il mio compagno, "+pchar.GenQuest.FindFugitive.Name+" è il suo nome. A Port-Royal, la gente della taverna mi ha detto che stava andando verso il tuo insediamento. L'hai incontrato, per caso?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Ma non c'è tempo per parlare ora.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Ho lasciato la nave dall'altra parte dell'isola. Tornerò più tardi!","Chiedo scusa, "+GetFullName(npchar)+", Verrò più tardi. La mia nave non ha ancora raggiunto il molo."),pcharrepphrase("Dannazione! Questi idioti non hanno preparato la nave per il carico! Tornerò più tardi!","Scusami, devo dare ordini per ormeggiare la mia nave al molo!"));
                link.l1.go = "exit";
				link.l22 = "Sono qui per un altro affare.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, ero davvero esausto in mare... Beh, compagno, i soldi sono un problema reale per me in questo momento.","Bene, vecchia volpe, discutiamo dei nostri affari finanziari."),RandPhraseSimple("Vorrei discutere con te delle questioni finanziarie.","Parliamo di questioni finanziarie, dobbiamo discuterne."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Sono qui su richiesta di un uomo. Il suo nome è governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato da te. Dovrei ritirare qualcosa...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Vedi, sto cercando di trovare il mio compagno, "+pchar.GenQuest.FindFugitive.Name+" è il suo nome. A Port-Royal, le persone alla taverna mi hanno detto che si stava dirigendo verso il tuo insediamento. L'hai incontrato, per caso?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "No, non ho bisogno dei tuoi servizi! Almeno, finché sei nemico con "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "In tal caso, addio.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"Sei "+GetFullName(pchar)+", vero? Dicono "+RandPhraseSimple("molte cose spaventose su di te","molte cose brutte su di te")+", e non voglio avere a che fare con te.";
						link.l1 = RandPhraseSimple("Certo - fai un errore una volta, e tutti saranno felici di sputarti addosso.",RandSwear()+"Beh, ci sono cose migliori da fare in mare, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"Eh, "+GetAddress_Form(NPChar)+", non ho tempo per i carichi oggi. Torna domani.","Torna domani. Forse, ti farò un'offerta vantaggiosa.");
						link.l1 = "Bene, tornerò domani.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"La tua patetica vecchia tinozza non può contenere l'intero carico, quindi non ci sarà nessun affare oggi.","Sfortunatamente, capitano "+GetFullName(pchar)+", Avrò bisogno di una nave più capiente per la mia consegna.");
    							link.l1 = NPCharRepPhrase(npchar,"La mia nave è decente, ma capisco il tuo punto di vista. Arrivederci.","Capisco il tuo punto di vista, gli affari sono affari. Addio.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text = "Oh! Stavo proprio per chiederti un favore. Vedi, ho bisogno di consegnare il carico di "+GetGoodsNameAlt(iTradeGoods)+" nella quantità di "+FindRussianQtyString(iQuantityGoods)+" alla città di "+sNation+sTemp+", e quanto prima, meglio è. Se riesci a farlo per "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", allora all'arrivo riceverai "+FindRussianMoneyString(iMoney)+" come tua ricompensa. Che ne dici?";
    							link.l1 = "Credo di essere d'accordo.";
    							link.l1.go = "exit_trade";
    							link.l2 = "Probabilmente questo non fa per me.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Le realtà politiche nell'arcipelago non mi permettono di commerciare. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"cacciatore")+" è in ostilità con tutti e mi ha lasciato solo nel negozio.";
    						link.l1 = "Oh! Mi dispiace. Buona fortuna.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"Vattene, non ho tempo per chiacchiere inutili!","Ti ho già detto che non ho nulla per te.");
				link.l1 = NPCharRepPhrase(npchar,"Dovrai essere cortese, o ti insegnerò a essere educato!","Oh, mi dispiace!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"Non credi di aver ricordato quel affare un po' troppo tardi? Ho dovuto ordinare di nuovo la merce. Addio.";
				link.l1 = "Perdonami, ma ero di fretta. Forse se copro le tue perdite, la mia reputazione sarà ripristinata?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Tutto il meglio.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Certo! L'ho aspettato per un bel po' di tempo. Devi consegnarmi un carico di "+GetGoodsNameAlt(iTradeGoods)+" in quantità di "+FindRussianQtyString(iQuantityGoods)+" e ricevi in cambio "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "Esattamente.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"Devo scusarmi con te, "+GetAddress_Form(NPChar)+". Vedi, il problema è che io ero "+RandPhraseSimple("in una situazione imbarazzante e non sarò in grado di pagarti","ho già acquistato quel carico da un altro venditore a un prezzo migliore")+". Come pagamento per la tua carta ti suggerisco di tenere tutto il carico che stavi consegnando.";
				link.l1 = RandSwear()+RandPhraseSimple("E ho protetto quel maledetto carico da tutti i pericoli! Ho ucciso duecento ratti per causa sua!","Mi metti in stallo, e dovrò accettare.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Non è l'intero lotto! Secondo il nostro accordo, ho bisogno "+FindRussianQtyString(iTmp)+" unità in più.";
				link.l9 = RandPhraseSimple("Sì, infatti. Dovrò compensare per la carenza allora. Ci vediamo dopo.",RandSwear()+"Questi maledetti ratti hanno rovinato il carico. Compenserò la mancanza e tornerò di nuovo.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Eccellente! Ecco la tua ricompensa, capitano "+GetFullName(pchar)+".";
				link.l1 = "È stato un piacere lavorare con te.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Bene... La somma di "+FindRussianMoneyString(iMoney)+" coprirà appena i danni causati dalla violazione dei termini del nostro accordo.";
			link.l1 = "Caspita! No, non può andare! Non consegnerò mai più alcun carico! Ce n'è abbastanza di quella roba in mare!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Ecco l'importo richiesto";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Eccellente. Ora posso dire ai miei colleghi che sei ancora una persona ragionevole con cui trattare.";
			link.l1 = "Grazie! Non ti deluderò di nuovo.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Mmm. Ho sentito dire che non hai adempiuto ai tuoi obblighi stabiliti nel contratto precedente - e stai chiedendo un altro? Dovevi consegnare il carico di "+LanguageConvertString(iSeaGoods,"seg_"+Goods[iTradeGoods].Name)+" a "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "Sì, infatti! Hai ragione!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", mi stai deludendo!!! Forse farai qualcosa per risolvere questo problema?";
			link.l1 = "Bene. Farò del mio meglio per consegnare la spedizione.";
			link.l1.go = "exit";
			link.l2 = "No, non posso. Mi dispiace";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Aspetta! Non ci sono abbastanza merci a bordo della tua nave! Non ne hai "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" unità di carico.";
				link.l9 = RandPhraseSimple("Sì, infatti. Dovrò compensare per la carenza allora.",RandSwear()+"I ratti hanno rovinato il carico. Comprerò la quantità mancante e tornerò di nuovo.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Capisco, capisco... Accetterò la spedizione di ritorno.";
    			link.l1 = "Grazie! Non ti deluderò di nuovo!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "Di cosa stai parlando? Chiaramente, sei stato ingannato - non ho mai commerciato vino europeo in tali quantità. Uno-due bottiglie, non di più. Ma il vino locale è un'altra storia - ne ho abbastanza, e lo vendo a damigiane, non a bottiglie!";
			link.l1 = "Maledizione! Ma mi avevano detto...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Non ho idea di cosa ti abbiano detto, ma lo dirò di nuovo: non ho vini europei in magazzino. Questo è tutto quello che ho da dire riguardo a questa questione.";
			link.l1 = "Bene... Allora andrò a sistemare la questione, allora!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ecco una storia diversa. Sai, vengono qui vari tipi, fanno domande inutili. Allora, facciamo affari, d'accordo?";
			link.l1 = "Certo!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Quante bottiglie ti servono? Il prezzo di una bottiglia è di 500 pesos, e il lotto minimo è di 20 bottiglie.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Non ho abbastanza soldi al momento. Tornerò più tardi.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Non sono un venditore ambulante, capitano. Se ricordo bene, stavi parlando di un lotto più grande?";
				link.l1 = "Mi dispiace... Riconsideriamo l'importo, allora.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Sfortunatamente, non ho così tanto.";
				link.l1 = "Peccato... Riconsideriamo l'importo, allora.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Bottiglie? Bene. Ti costerà "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Eccoti.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Non ho abbastanza soldi adesso. Tornerò più tardi.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "Va bene, ma cerca di non impiegare troppo tempo. Questa roba è molto popolare qui.";
			link.l1 = "Torno presto!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Vediamo... Sembra tutto a posto. Puoi ritirare il tuo acquisto.";
			link.l1 = "Grazie! Buona fortuna!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "Avevo in mente di fare un buon affare, ma mi serve ancora una merce particolare per farlo - "+GetGoodsNameAlt(iCGood)+". Il problema è che questa merce è un contrabbando nella nostra colonia, quindi non posso contare sull'acquisto da parte dei capitani di commercio\nTutto ciò di cui ho bisogno sono "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" unità di esso. Forse, potresti consegnarmelo? Ti pagherò bene, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" per unità, che ammonta a "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Oh, e ne ho bisogno non più tardi di "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". Quindi, mi aiuterai?";
			link.l1 = "Mmm... Sembra interessante. Accetto!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Consegna di merci di contrabbando? Mi dispiace, non sono interessato.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Eccellente. Sono contento che tu abbia accettato. Quindi, aspetterò il tuo ritorno con la merce.";
			link.l1 = "Presto tornerò!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Scherzi? Non hai la quantità completa di merce di cui ho bisogno!";
				link.l1 = "Mi dispiace, la mia colpa...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Vediamo, allora. Dovevi consegnare un carico di "+GetGoodsNameAlt(iCGood)+" in quantità di "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". Corretto?";
				link.l1 = "Esattamente, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Grazie per il tuo lavoro. Per favore, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "Grazie! È stato un piacere fare affari con te.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Oops... Capitano, sembra che abbiamo un problema qui...";
				link.l1 = "Cosa c'è ancora?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "Ho urgentemente bisogno di un lotto di schiavi - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" teste. Sono pronto a pagare "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" monete per anima, che ammonta a "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Credo che andrò d'accordo. È un affare noioso, ma molto redditizio.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Non sono interessato.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Esattamente - è davvero molto redditizio. Allora, aspetterò il tuo ritorno con i miei schiavi.";
			link.l1 = "Non ti farò aspettare a lungo. A presto!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Stai scherzando? Non hai tutti gli schiavi di cui ho bisogno!";
				link.l1 = "Mi dispiace, è colpa mia...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Vediamo, allora. Dovevi consegnarmi un gruppo di schiavi per un totale di "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". Corretto?";
				link.l1 = "Esattamente, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Grazie per il tuo lavoro. Per favore, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+". Inoltre, accetta questo. Sono certo che lo troverai utile.";
			link.l1 = "Grazie! È stato un piacere fare affari con te.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Mmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Mai sentito prima... Ma che cos'è, in realtà? Non ho mai sentito parlare di una cosa del genere in tutta la mia vita.";
			link.l1 = "Ebbene, è uno strumento del costruttore navale, "+pchar.GenQuest.Device.Shipyarder.Describe+". Qualcuno ti ha offerto qualcosa del genere?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Mmm... Sì, c'era un tipo strano. Ma non mi ha detto cosa fosse quella cosa, ha solo cercato di vendermela. Ma a cosa mi servirebbe, se non ho idea di a cosa serve? Come potrei rivenderla? Quindi, ho semplicemente rifiutato.";
				link.l1 = "E come sembrava e dove è andato? Ho davvero bisogno di quel strumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, niente del genere. Mi dispiace, non posso aiutarti. Chiedi in giro.";
				link.l1 = "Capisco. Beh - è ora di chiedere in giro!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Concorrenza... Non esiste affari senza di essa. Bastardi avidi che cercano di intrufolarsi nel tuo accogliente business e usano tutti i tipi di metodi nefandi per attirare clientela a se stessi\nMa sono discorsi. E infatti, vorrei chiederti di aiutarmi a sbarazzarmi di uno di questi miei concorrenti. No, non è necessario ucciderlo. Basta catturare o affondare la sua nave con il carico.";
			link.l1 = "Mmm... beh, se paghi bene, posso organizzare questo.";
			link.l1.go = "Sunplace_1";
			link.l2 = "No, non interferirò nelle vostre liti mercantili. Affonda il tuo rivale senza il mio aiuto.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Molto bene. Allora, il nome del tuo uomo è "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Di recente ha mandato fuori "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")+"Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"' con un carico di "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+". Ha pagato una somma piuttosto decente per questo carico, quindi perderlo sarà un bel colpo al suo portafoglio.";
			link.l1 = "E potresti dirmi, dove esattamente cercare quel 'amico' tuo?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "Il mio 'amico' è attualmente a casa sua a "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Non hai bisogno di lui - hai bisogno della sua nave, che, come ho scoperto dopo circa "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" passerà vicino a "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". Puoi affondarlo, puoi prenderlo abordandolo - non importa. L'importante è assicurarsi che la nave e il carico non siano più proprietà di "+pchar.GenQuest.Sunplace.Trader.Enemyname+". E non mi importa, chi lo reclamerà - tu o il mare. Per quel lavoro ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = "Capito. Beh, è ora di partire allora!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Eccellente! Sapevo di poter contare su di te. Immagino che non chiederò dove si trova quella nave e il carico. Dopotutto, non sono affari miei. E il mio amico avrà bisogno di molto tempo per riprendersi da un colpo così, he-he. Ecco, per favore prendi i tuoi soldi - e grazie per l'ottimo lavoro.";
			link.l1 = "Prego... Arrivederci, "+npchar.name+"!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Povero "+pchar.GenQuest.Sunplace.Trader.Enemyname+", che destino orribile! E sebbene indirettamente, sono la causa della sua fine! Non capisci, capitano! Ti ho chiesto di ucciderlo? Avevo pianificato che dopo la perdita di denaro speso per il carico avrebbe dovuto... beh, non importa... Tu...";
			link.l1 = "Ehi, ascolta - smetti di lamentarti, va bene? Mi hai chiesto di liberarti di un rivale - l'ho fatto. Ancora meglio - avendo perso il carico, avrebbe potuto ancora arricchirsi e continuare a danneggiare il tuo affare. Ora non può fare molto essendo un morto.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Basta così! Basta! Non voglio più sentire questi discorsi blasfemi! Prendi i tuoi maledetti soldi e lascia subito il mio negozio!";
			link.l1 = "Ehi, "+npchar.name+", calmati, vuoi? O ti raffredderò io il temperamento - la mia sciabola è sempre al mio fianco! Va bene, non spaventarti, stavo solo scherzando. Ascolta, mi dispiace che sia andata così - ma sei stato tu a traviarmi in primo luogo. Addio.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? Sì, lo conosco. Ha comprato da me le provviste per la sua lunga barca. Durante il giorno solitamente pesca da qualche parte in calette nascoste, ma ogni sera può essere trovato nella taverna.","Mi hai già chiesto di quell'uomo, e ti ho detto tutto quello che sapevo!","Stai scherzando con me o sei davvero un idiota?! Stai facendo le stesse domande per la terza volta!","Proprio per pensare, come un tale idiota è diventato capitano...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Grazie, mi hai aiutato immensamente!","Sì, sì, va bene.","Ora, ora, non agitarti così. Ho solo dimenticato.","Ebbene, come puoi vedere, lui l'ha fatto...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Non so cosa dicevano le persone nella taverna di Port Royal, ma non ho mai incontrato quell'uomo nel mio negozio. In realtà, non l'ho mai visto da nessuna parte. Chiedi in giro per il villaggio - forse, qualcuno ti dirà...","Mi hai già chiesto di quell'uomo, e ti ho detto: Non lo so!","Stai scherzando con me o sei davvero un idiota?! Stai facendo le stesse domande per la terza volta!","Giusto a pensare, come un tale idiota sia diventato capitano...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Capisco. Beh, grazie comunque.","Sì, sì, va bene.","Ora, ora, non eccitarti così tanto. Ho solo dimenticato.","Ebbene, come puoi vedere, lui lo ha fatto...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "Mio Signore, cosa ti prende, giovane uomo! Per favore, sii più riservato e scegli attentamente le tue parole quando parli di persone rispettabili! Gerard LeCroix ha lasciato Guadalupa con una spedizione per la terraferma, ma ha lasciato qui la tua ricompensa per te. Sei soddisfatto ora?";
			link.l1 = "Hm... Per favore, scusami, signore. Mi sono un po' riscaldato...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Molto bene. Il signor Lecroix ha lasciato il tuo premio al custode del faro locale - sono vecchi amici. Devi solo visitarlo e ritirare il pagamento dovuto. Il signor Lecroix è un uomo onesto, quindi penso che sarai soddisfatto del tuo premio.";
			link.l1 = "Capito, grazie! Allora vado dal guardiano del faro. Ora lasciami fare una pausa.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "Sì, era qui, ad aspettarti. Ma, probabilmente, l'incarico che ti ha affidato si è rivelato più difficile del previsto, quindi non ha aspettato ed è partito per una spedizione verso la terraferma. Ha lasciato la tua ricompensa con una persona di fiducia.";
			link.l1 = "Sì, ho davvero avuto circostanze impreviste, ma ho completato con successo l'incarico. Sono contento di sentire che il mio pagamento mi sta aspettando. Da chi posso prenderlo?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "Il signor Lecroix ha lasciato la tua ricompensa al custode del faro locale - sono vecchi amici. Devi solo andare da lui e riscuotere il pagamento dovuto. Monsieur Lecroix è un uomo onesto, quindi penso che sarai soddisfatto della tua ricompensa.";
			link.l1 = "Capito, grazie! Allora vado dal custode del faro. Ora lasciami fare una pausa.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "Buona fortuna, signore.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "Dio, perché sei così rumoroso, giovane! Calmati, e guarda la tua lingua quando parli di persone rispettate! Gerard LeCroix ha lasciato la Guadalupa con una spedizione per la terraferma, ma per te ha lasciato un messaggio\nTi sei calmato, signore? Pronto ad ascoltarmi?";
			link.l1 = "Hm... Mi scusi, signore. Mi sono un po' alterato. Sto ascoltando.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Molto bene. La prossima volta prova a chiedere prima e poi a gridare. Bene... Conosci un uomo di nome Simon Maurois?";
			link.l1 = "Ah! Tutti hanno sentito parlare di Simon Maurois! Certamente lo conosco.";
			link.l1.go = "trial_2";
			link.l2 = "Mai sentito parlare di lui. Chi è?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Eccellente. Allora vai da lui. È lui che ha finanziato l' spedizione del signor Shoke, quindi puoi ritirare la tua ricompensa da lui. Ma era davvero necessario agitarsi così tanto?";
			link.l1 = "Di nuovo, chiedo il vostro perdono... Grazie per il vostro aiuto, signore. Andro' a vedere il signor Maurois immediatamente!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "È il proprietario della casa bancaria di Maurois e il capo della filiale di Capsterville. Quindi dovrai andare a Saint-Christopher e visitare la banca di Capsterville. È stato il signor Maurois a finanziare la spedizione del signor Shoke, quindi puoi ritirare la tua ricompensa da lui. Quindi, era davvero necessario agitarsi così tanto?";
			link.l1 = "Di nuovo, chiedo il vostro perdono... Grazie per il vostro aiuto, signore. Andrò da monsieur Maurois subito!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "Ah, l'intraprendente mercante! Si può vedere subito l'approccio commerciale. Lo rispetto. Certo, ho la merce di cui hai bisogno.";
			link.l1 = "Sono sicuro di poterlo vendere con profitto. Per quanto ne so, c'è una buona domanda per questo bene a Porto Bello. Quanto mi costerà?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "Così così... Allora, trecento unità di caffè... E la stessa quantità di cacao... Ti costerà..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" pesos!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Mmm... Mi scusi, sembra che non abbia abbastanza contanti. Aspetta, per favore: sto correndo alla nave per prendere i soldi - e torno subito!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Eccolo qui.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Aspetta un minuto, signore. Sembra che tu non abbia abbastanza spazio sulla tua nave per un simile carico. Svuota la stiva e torna.";
				link.l1 = "Oh, ho dimenticato di scaricare! Aspetta un minuto - sarò lì subito!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ottimo! Darò immediatamente l'ordine di caricare le merci sulla tua nave. È un piacere fare affari con te!";
				link.l1 = "Reciprocamente, signore! E ora permettetemi di prendere congedo: le cose non aspettano.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "Le merci ti stanno aspettando. Hai portato i soldi?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Non ancora. Volevo solo assicurarmi che la tua offerta sia valida. E i soldi arriveranno presto.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Eccolo.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "Al momento non ho bisogno dei tuoi servizi.";
			link.l1 = "Peccato. Cambiamo argomento.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
