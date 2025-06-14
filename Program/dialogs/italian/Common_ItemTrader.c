#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
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
			dialog.text = NPCharSexPhrase(npchar,"Vorresti comprare dell'equipaggiamento per te o per i tuoi ufficiali, capitano? Se è così, sei venuto dalla persona giusta!","Oh, capitano, sapevo che mi avresti cercato! Posso offrirti attrezzature per te e i tuoi ufficiali, tra molte altre cose utili.");
			link.l1 = "Mostrami quello che hai.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "Sono venuto per un affare diverso.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Ehi, ho trovato una pianta interessante qui intorno. Potresti dirmi se può essere utilizzata per preparare pozioni o decotti? Mi sembra semplicemente interessante. Puoi dare un'occhiata?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Dimmi, puoi vendermi una bottiglia di buon vino europeo?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Ascolta, so che stai vendendo vino europeo. Ho bisogno di sessanta bottiglie.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Eccomi di nuovo. Che cosa significa tutto questo, eh?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "Ho bisogno di due pistole, insieme a pallottole e polvere per venti colpi.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Ascolta, il nome 'Juan' ti dice qualcosa?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Buon mercante, cerco qualcosa di qualità eccezionale. Non i soliti gingilli che soddisfano la maggior parte, ma un pezzo di vero raffinatezza, forse un paio di orecchini finemente lavorati o un elegante ciondolo degno di gusto aristocratico. Ho bisogno di un regalo che piacerebbe a una signora di stirpe distinta.";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Mi chiedo se tra il tuo inventario potresti possedere qualcosa di significativo valore? Sto cercando un pezzo che soddisferà anche i gusti della più particolare nobildonna: qualcosa di distintivo e raffinato, ben oltre ciò che potrebbe attrarre i cittadini comuni. Forse un pendente di insolita arte o un braccialetto di sofisticato design?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Dimmi, buon mercante, sei esperto in materia di gioielli pregiati? Cerco qualcosa di straordinario da presentare a una signora di qualità. Lascia che sia franco, non ho interesse per le cianfrusaglie comuni. Quello che richiedo è un pezzo di autentica magnificenza: forse una spilla adornata di pietre preziose o un anello di maestria impareggiabile.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Ascolta, tratti ogni sorta di merci... Ieri o oggi - qualcuno ti ha offerto di venderti "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Grazie, non sono interessato.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Certo. Settecento pesos per bottiglia.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Eccellente. Prendi i soldi e dammeli.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Eccellente! Tornerò una volta deciso di comprare qualcosa.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Per favore, prendi la tua bottiglia.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ah! Sono solo un rivenditore, non un grossista. Venderei così tante bottiglie per oltre mezzo anno - quel vino è raro e costoso, e non tutti possono permetterselo, sai. Non ne ho così tante.";
			link.l1 = "Bene, non li hai - nessun problema. Ma te li procuri da qualche parte per te, vero? Forse potresti dirmi il nome del tuo fornitore, e lo comprerei direttamente da lui. O il vino ti viene consegnato dall'Europa?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "No, non lo è. Lo prendo qui. Ma non ti nominerò il mio fornitore così facilmente. Ma per mille pesos... forse, lo farei...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Bene. Ecco il tuo migliaio - e ora dimmi, chi è il tuo fornitore.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Ora voi imbroglioni siete diventati troppo sfacciati! Non sarebbe troppo bello per voi? Me la caverò benissimo senza il vostro fornitore, grazie.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Immagino... va bene allora. Ecco la tua nota, e spero tu ricambi il favore in futuro.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Il nome del mio fornitore di vino è "+pchar.questTemp.Wine.Name+", possiede il negozio locale.";
			link.l1 = "Capito! Grazie!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Il nome del mio fornitore di vino è "+pchar.questTemp.Wine.Name+", lui possiede il negozio locale.";
			link.l1 = "Capito! Grazie!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Come desideri, capitano. Tutto il meglio per te.";
			link.l1 = "Ci vediamo.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Cosa intendi dire con questo? Spiegati.";
			link.l1 = "Mi hai ingannato, mascalzone! Sono appena stato in negozio, "+pchar.questTemp.Wine.Name+" non tratta mai in vino, come lui stesso mi ha detto! Ridammi i miei soldi!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "C'è stato un malinteso... Sono andato dal negoziante, e "+pchar.questTemp.Wine.Name+" ha affermato di non aver mai commerciato in vino. Come puoi spiegarlo?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Eh! Lui tratta in vino, questo è dannatamente certo. Non vende vino a chiunque - come con poche altre merci, anche. E ci sono diverse ragioni per questo... Se vuoi comprare del vino da lui, posso scrivergli un biglietto. Mi conosce e riconosce la mia calligrafia, quindi, dopo averlo letto, ti venderà quel vino. Naturalmente, questo favore non è gratuito, nemmeno.";
			link.l1 = "È uno scandalo! Mi hai appena preso mille!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Ho preso mille da te per le informazioni. E per una lettera dovrai pagare separatamente duemila pesos, e in ogni caso non meno di quello.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Oh... Voi mercanti siete così dannatamente avidi. Non mi sorprende che nessuno vi possa sopportare. Vabbè, ecco i tuoi soldi, quindi vai avanti e scrivi la nota.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Affidabile) Troviamo un compromesso. Tu fornisci una raccomandazione ora, gratuitamente, e io ricambierò con una raccomandazione per te più tardi, anche senza costi. Questo affare del vino è solo l'inizio.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "Ora questo è completamente fuori dai limiti! Preferirei abbandonare tutto l'affare, non arricchirò un avaro così astuto. E con quel avaro intendo te. Addio.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Immagino... va bene allora. Ecco la tua nota, e spero che ricambierai il favore in futuro.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Sei un uccello strano, capitano! Certo, capisco che il tuo intendente si occupa di tutte le finanze, ma dovresti usare anche la tua testa a volte. Avrai l'opportunità di comprare un bel po' di vini all'ingrosso senza il mio sovrapprezzo e fare un bel profitto. Quindi non impediamoci l'un l'altro di fare moneta, perché adesso sembri tu l'avidone.\nGiusto...(scrivendo) Ecco, prendi questa lettera - "+pchar.questTemp.Wine.Name+"  ti venderà il vino senza fare domande.";
			link.l1 = "Certo spero di sì... Se qualcosa dovesse andare storto di nuovo, tornerò. A presto!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "Come desideri, capitano. Addio.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Oh, quindi sei venuto qui per minacciarmi e essere maleducato? Chiamerò le guardie, allora! Ehi, guardie! Proprio qui!";
			link.l1 = "Oh, taci! Hai vinto, me ne vado! Maledizione a te "+NPCharSexPhrase(npchar,"","")+", cormorano, possa tu rovinarti!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Ah, capisco. Stai facendo affari con i nativi? Ho sentito dire che questo ti è già costato un bel po', ah ah!";
			}
			else
			{
				dialog.text = "Ti aspetti guai, Capitano? O stai pianificando un'avventura nella giungla? Ah-ah!";
			}
			link.l1 = "Allora, possiamo fare un affare?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Certo! I clienti sono sempre benvenuti. Per tremila pesos, avrai pistole affidabili, proiettili e polvere come richiesto.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Costoso, ma va bene. Lo prendo.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "Il prezzo sembra ingiusto. Che ne dici di uno sconto per un amico di Fadey Moscovita?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Tre mila? Questo è un furto! Addio, signore!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "Buona fortuna là fuori, Capitano!";
			link.l1 = "Addio, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "Certo, Capitano. Gli amici di Fadey sono sempre benvenuti qui. Duemila trecento per tutto?";
				link.l1 = "Questo suona meglio. Lo prenderò.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				notification("Skill Check Failed (19)", SKILL_COMMERCE); 
				dialog.text = "Gli amici del signor Fadey sono sempre benvenuti, ma i prezzi non hanno amici. Saranno tremila pesos, Capitano.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Caro, ma va bene. Lo prenderò.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Tremila? Questo è un furto! Addio, Monsieur!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Buona fortuna là fuori, Capitano!";
			link.l1 = "Addio, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "No, non lo fa... Ora, per favore non disturbarmi, sono molto occupato... Che domanda idiota...";
			link.l1 = "Capisco. Scusa per aver sprecato il tuo tempo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Mmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Non ne ho mai sentito parlare prima... Ma che cos'è, in realtà? Non ho mai sentito parlare di una cosa del genere in tutta la mia vita"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Beh, è uno strumento del costruttore di navi, "+pchar.GenQuest.Device.Shipyarder.Describe+". Qualcuno ti ha offerto qualcosa del genere?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Sì, c'era un tipo strano. Ma non mi ha detto cosa fosse quella cosa, ha solo cercato di vendermela. Ma a cosa mi servirebbe, se non avessi idea di cosa fosse? Come potrei rivenderla? Quindi, ho semplicemente rifiutato"+NPCharSexPhrase(npchar,"","")+", e se ne andò";
				link.l1 = "E come sembrava e dove se n'è andato? Ho bisogno di quel strumento disperatamente.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, niente del genere. Mi dispiace, non posso aiutarti. Chiedi in giro.";
				link.l1 = "Capisco. Beh, è ora di fare qualche domanda!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Mostramelo... Sì, è una pianta interessante. E molto, molto rara. Si chiama Manga Rosa. Non so a cosa serva, ma c'è un fatto interessante legato ad essa...";
				link.l1 = "Cosa intendi?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Mostramelo... Sì, è una pianta interessante. Ma, purtroppo, non posso dirti più di così. Se effettivamente viene utilizzata per qualche scopo, è sconosciuto a me.","Vediamo... Hmm... Sembra una pianta medicinale, ma non ne so nulla. Mi dispiace, non posso aiutarti.","Dove si trova? Hmm... No, non l'ho mai visto prima. Sembra molto interessante, ma non ho idea di cosa si usa...");
				link.l1 = "Capisco. Beh, chiederò in giro un po' di più. Scusa.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Zingari nomadi e selvaggi mostrano grande interesse per queste piante. Una volta ho visto uno zingaro pagare un pugno d'oro per un solo stelo come questo. Ma non ho idea del perché ne avrebbero bisogno.";
			link.l1 = "Capisco... Beh, è qualcosa almeno! Ora so dove chiedere di più. Grazie mille!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
			dialog.text = "Purtroppo, "+GetAddress_Form(NPChar)+", il mio negozio non ha visto una merce così pregiata da molti mesi. L'appetito per il lusso è diminuito in questi tempi difficili. La gente comune che frequenta il mio negozio può permettersi solo modesti gingilli, mentre i nobili raramente si degnano di esaminare le mie umili merci.";
			link.l1 = "Molto bene...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "Con grande rammarico, Capitano, tali pezzi esquisiti non hanno arricchito il mio negozio da molto tempo. I ricchi patroni di questo porto raramente favoriscono il mio modesto negozio con la loro presenza, e i miei clienti abituali cercano solo ciò che le loro scarse borse possono permettersi.";
			link.l1 = "Molto bene...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "Ah, Capitano, il tuo arrivo è davvero inopportuno... Solo poche ore fa, mi sono separato da una collana veramente magnifica—acquistata da un altro capitano di mare di notevoli mezzi. Il mio negozio acquisisce regolarmente pezzi capaci di sciogliere il cuore di anche la più esigente signora\nForse potresti tornare domani? Giselle... voglio dire... i miei fornitori... potrebbero probabilmente procurare un tesoro che ti farebbe amare per sempre dall'oggetto della tua ammirazione.";
			link.l1 = "Time is a luxury I do not possess; I require such a piece without delay. Pray tell, what is the name of this fortunate captain who acquired the necklace you speak of?";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "Tristan Renier, capitano del 'Gabbiano d'Oro'. La sua nave rimane ancorata nel nostro porto. Devo confessare, però, che mi chiedo se sarebbe disposto a rinunciare a un tale premio. Se si dimostra riluttante, torna da me domani. Sull'onore, capitano, troverai l'accordo molto soddisfacente.";
			link.l1 = "...";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
