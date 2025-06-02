#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("Первое посещение таверны " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'allarme è stato dato in città, e tutti ti stanno cercando. Se fossi in te, non resterei qui.","Tutte le guardie della città stanno setacciando la città alla tua ricerca. Non sono un idiota e non parlerò con te!","Corri, "+GetSexPhrase("compagno","ragazza")+", prima che i soldati ti trasformino in polpettone..."),LinkRandPhrase("Di cosa hai bisogno, "+GetSexPhrase("birbante","puzzolente")+"?! Le guardie della città hanno il tuo odore, non andrai lontano"+GetSexPhrase(", sporco pirata!","")+"","Assassino, lascia subito il mio posto! Guardie!","Non ho paura di te, "+GetSexPhrase("birbante","ratto")+"! Presto sarai impiccato nella nostra fortezza, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è mai un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o ti strappo la lingua!","Eh, "+GetWorkTypeOfMan(npchar,"")+", e tutti là - a catturare pirati! Ecco cosa ti dico, compagno: siediti tranquillo e non morirai..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("E sei tu, mascalzone! Pensi che qui ti stiamo versando rum? Certamente no! Ragazzi! Alle armi! Uccidete questo furfante!","Vuoi un drink, pirata? Ah! No! Ora ti mostreremo noi! Ragazzi, sguainate le vostre spade!");
				link.l1 = RandPhraseSimple("Eh? Cosa?","Fermati!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Signore, sto cercando lavoro. Avete qualche lavoro?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "Ho completato il tuo incarico. La lancia con il rum è stata consegnata alla Baia di Le Francois e consegnata ai tuoi uomini.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Desiderava qualcosa, signore?";
				Link.l1 = "Salve oste, ho bisogno di assumere un equipaggio per la mia nave. Puoi aiutarmi con questo?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Ciao di nuovo. Cosa desidera questa volta, signore?";
				Link.l1 = ""+npchar.name+", Mi rendo conto di disturbarti, ma solo un'altra domanda. Ho bisogno di un navigatore - hai idea di dove posso trovarne uno?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Cosa desidera, signore?";
				Link.l1 = "Speravo che tu potessi rispondere a un paio di domande.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Vorrei affittare una stanza.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Sono lieto di vedervi signore! Come posso esservi utile? Rum, brandy, whisky scozzese?";
				Link.l1 = "Vorrei una bottiglia del vostro miglior vino francese e la chiave di una stanza.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Hai già pagato signore, la tua stanza è al piano di sopra.";
				Link.l1 = "Grazie.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Come posso servirti, Capitano? Probabilmente vorrai un drink dopo quello che è successo.";
				Link.l1 = "Questo può aspettare. Voglio effettivamente discutere su quello che è successo.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Chiedo scusa, "+GetAddress_Form(NPChar)+", ma oggi non posso offrirti nemmeno una goccia di liquore.";
				Link.l1 = "Cosa? Quale tipo di taverna non può risparmiare nemmeno una goccia di rum? Ho perso qualche grande festa che ha svuotato le vostre scorte?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Benvenuto nella mia umile taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"', signore. Sono contento di vederti.","Al vostro servizio, signore! Nella nostra taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"' siamo sempre lieti di accogliere nuovi visitatori.","Prima volta qui, signore? Non esitate, qui al '"+XI_ConvertString(NPChar.City+"TavernName")+"' ti senti sempre a casa!"),LinkRandPhrase("Avanti, signor capitano. Non ti riconosco quindi deve essere la tua prima volta a '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Mai incontrato prima, signore. Facciamo conoscenza: Io sono "+GetFullName(npchar)+", l'oste di '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Sono lieto di dare il benvenuto al nostro nuovo ospite, Monsieur Capitano! Nella mia taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"' il primo drink è sempre offerto dalla casa! Sono il proprietario di questo posto, "+GetFullName(npchar)+", ti dà il benvenuto."),LinkRandPhrase("Signor Capitano! Benvenuto alla taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","Oh, che splendido hidalgo ha visitato la nostra taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'! È la sua prima volta qui, signore?","Buongiorno, signore! Sono "+GetFullName(npchar)+", umile proprietario di '"+XI_ConvertString(NPChar.City+"TavernName")+"', siamo lieti di darti il benvenuto qui!"),LinkRandPhrase("Ciao, signor capitano. Sono il proprietario della taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'. È la tua prima volta da noi?","Buon pomeriggio, signore. Benvenuto alla taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'.'","Molto bene vederti mio signore capitano! La nostra stessa taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"' ti saluta! Rum, vino, o se potessi tentarti, abbiamo un nuovo piccolo spirito olandese chiamato gin?"));
				Link.l1 = LinkRandPhrase("Un posto accogliente che hai qui... Permettimi di presentarmi - "+GetFullName(pchar)+", è un piacere conoscerti.",""+GetFullName(pchar)+", è un piacere conoscerti. Allora, cosa puoi offrirmi?","Il mio nome è "+GetFullName(pchar)+" e sono nuovo in questo porto. Dimmi, per cosa è più conosciuta questa taverna?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Ciao, Rumba! Tornato da un viaggio, o stai partendo per uno nuovo?";
					link.l1 = "Ciao, "+npchar.name+". Ho solo deciso di passare.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Allora, cap'n, mi hai portato "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Sì, li ho. Eccoli qui...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "No, non ancora...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Cosa desideri, mio buon "+GetSexPhrase("signore","signora")+"?";
						link.l1 = "Una bottiglia di rum per il mio compagno a quel tavolo là.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, ospiti onorevoli! Ehi, tu - spostati e fai spazio per un capitano galante! E sbrigati, prima che ti cacci fuori, haha!","Misericordioso Dio sopra! Se non è "+GetFullName(pchar)+"! Ho appena ricevuto una nuova spedizione di vini pregiati, ti prego di entrare!","Oh, "+GetAddress_Form(NPChar)+", hai dei problemi? Posso offrirti da bere? Questa bottiglia è offerta della casa. Fidati di me, è il miglior vino del posto..."),LinkRandPhrase("Oh, è il Capitano "+GetFullName(pchar)+"! Ehi, tu! Mostra un po' di rispetto al buon capitano! Questo non è un granaio! Mi scusi, cap'n, le loro madri chiaramente non gli hanno mai insegnato le buone maniere.","Beh beh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Siamo in per una lunga notte, haha! Ragazze, sarebbe meglio indossare i vostri abiti migliori!","Buon pomeriggio, "+GetFullName(pchar)+", sono felice di vederti! Per favore signore, ho una richiesta. Ho appena comprato dei nuovi tavoli, quindi per favore niente combattimenti stasera."),LinkRandPhrase("Ciao, capitano. Mettiti comodo, ma ricorda che anche il Capitano Sharp stesso osserva le buone maniere nel mio locale.","O-ho-ho! Guarda chi c'è? È "+GetFullName(pchar)+" proprio lui! E noi che cominciavamo proprio a annoiarci senza di te! Che ne dici di intrattenere i compagni con un'avventura mentre apro un nuovo barile di rum, cap'n?","O-ho-ho! È "+GetFullName(pchar)+" lui stesso! Spero che non stia per portare via i miei clienti in alto mare di nuovo con le storie delle tue grandiose avventure?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Questo vecchio lupo di mare è sempre felice di vederti nella sua taverna! Per favore signore, prendi un posto e le ragazze si prenderanno cura di te!","Per favore capitano, mettiti comodo! Sempre felice di accogliere il mio ospite preferito. Qual è il tuo veleno?","Contento di rivederti, "+GetFullName(pchar)+"! Desideri un tavolo per te? O preferiresti sederti al bancone?"),LinkRandPhrase("Buon pomeriggio, capitano. C'è un freddo nell'aria, permettimi di offrirti un eccellente vino caldo che ho appena fatto, tutto casa mia!","Ciao, capitano "+GetFullName(pchar)+"! Sono contento che tu sia venuto a farci visita di nuovo. Cosa vorresti?","Sono contento di averti, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sono lieto che frequenti il mio modesto locale! Facciamo tutto il possibile per accontentare."),LinkRandPhrase("Capitano! Benvenuto, benvenuto! Ho del magnifico d'Anjou degno del Re Luigi stesso e l'ho riservato specialmente per te!",""+GetFullName(pchar)+"! Sono così contento che tu sia venuto. Dovrei cacciare via tutti questi ratti di mare o preferiresti che rimanessero? Credimi, sgombrerei volentieri l'intera taverna per te!","Mio Dio, ecco il Capitano "+GetFullName(pchar)+"! Ehi, donnaioli - portate la tovaglia più bella al tavolo del capitano!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Oh, vedo che mi ricordano qui... Avast, riempi il mio bicchiere compagno, mentre do un'occhiata in giro...","Calmati, compagno, oggi sono di buon umore. Cominciamo con il rum, che ne dici?..."),RandPhraseSimple("Oh... non sei troppo felice di avermi qui? Spero di averti frainteso, eh!","Ehi. Spero che il tuo vino sia migliore del tuo saluto? Altrimenti potrei arrabbiarmi, sai...")),RandPhraseSimple(RandPhraseSimple("Sono sempre contento di venirti a trovare, compagno. Cosa hai per riscaldare un vecchio lupo di mare?","Ahoy compagno, il tuo stabilimento migliora con ogni giorno che passa! Venire a visitare qui è sempre un piacere..."),RandPhraseSimple("Non hai dimenticato un vecchio vagabondo? Sono lusingato, amico.","È bello rivedere un vecchio amico... Hai ancora un po' di rum?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Sto ascoltando, capitano.","La mia taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"' al vostro servizio, Capitano!","Tutto orecchie, Cap'n! Cosa vorresti oggi?");
				Link.l1 = "Ci sono ragazzi sull'isola pronti a tentare la fortuna in mare?";
				Link.l1.go = "crew hire";
				Link.l2 = "Speravo che tu potessi rispondere a un paio di domande.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Vorrei parlare di questioni finanziarie.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Potresti dirmi qualcosa sulla recente rapina nella chiesa?","Cosa sai del recente furto in chiesa?","Hai sentito qualcosa riguardo l'ultimo furto nella chiesa?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "La gente dice che tu sai praticamente tutto in questa colonia. Voglio comprare "+pchar.GenQuest.Device.Shipyarder.Type+", e mi è stato detto che era stato venduto nella tua città. Beh, qualcuno lo stava vendendo al mercato di strada. Puoi dirmi qualcosa al riguardo?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Cercando un racketeer di nome "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Dove posso trovarlo?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Ciao, "+npchar.name+". Ho bisogno di trovare Jacob van Berg - dove si trova? Non lo vedo nella tua taverna...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Ciao, "+npchar.name+". Sto cercando un cavaliere di nome Fernando Rodriguez. È apparso nella tua città?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Sono venuto a riscuotere le mie vincite, che sono state tenute al sicuro da te."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Mi chiedevo dove potrei trovare un uomo di nome "+pchar.GenQuest.Marginpassenger.q2Name+"? Vive nella tua città.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Hai una stanza libera, amico?","Hai una stanza libera, vorrei restare qui per un po'.");
					link.l3.go = "room";
				}
				Link.l4 = "Purtroppo, sto già partendo, "+NPChar.name+". Ci vediamo.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, bene, entra pure, entra pure. Sei sempre il benvenuto qui.";
			link.l1 = "Sì, grazie. È stato bello vederti. Addio.";
			link.l1.go = "exit";
			Link.l2 = "Avrei bisogno di nuovi uomini. Assicurati solo che siano capaci, va bene?";
			Link.l2.go = "crew hire";
			link.l3 = "Vorrei riposarmi su terra ferma e raccogliere i miei pensieri, non quando mia madre si agita per casa.";
			link.l3.go = "Helen_room";
			Link.l4 = "Potrei chiederti qualcosa? ";
			Link.l4.go = "quests";
			link.l5 = " Ho un problema da discutere con te, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Cosa desideri, gentile "+GetSexPhrase("signore","signora")+"?";
				link.l1 = "Una bottiglia di rum per il mio compagno di tavolo là in fondo.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Sto ascoltando, capitano.","Cosa posso offrirti, capitano?","Allora capo, cosa sarà?");
			Link.l1 = "Ho bisogno di un equipaggio, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", facciamo due chiacchiere...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Vorrei parlare di affari finanziari.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Potresti dirmi qualcosa sul recente furto nella chiesa?","Cosa sai del recente furto nella chiesa?","Hai sentito qualcosa riguardo alla recente rapina in chiesa?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "La gente dice che tu sai praticamente tutto in questa colonia. Voglio comprare "+pchar.GenQuest.Device.Shipyarder.Type+", e mi è stato detto che era stato venduto nella tua città. Beh, qualcuno lo stava vendendo per le strade. Puoi dirmi qualcosa al riguardo?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Parlami di un rackettista di nome "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Dove posso trovarlo?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Ciao, "+npchar.name+". Ho bisogno di trovare Jacob van Berg - dove si trova? Non lo vedo nella tua taverna...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Ciao, "+npchar.name+". Sto cercando un caballero di nome Fernando Rodriguez. È apparso nella tua città?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Sono venuto a riscuotere le mie vincite, che sono al sicuro con te."+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Mi chiedevo dove potrei trovare un uomo chiamato "+pchar.GenQuest.Marginpassenger.q2Name+"? Vive nella tua città.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Hai una stanza libera, compagno?","Hai una stanza libera, vorrei restare qui per un po'.");
				link.l3.go = "room";
			}
			Link.l4 = "Immagino che tornerò più tardi.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "E a cosa ti servirebbero dei marinai, capitano? Non vedo la tua nave nel porto.";
				link.l1 = RandPhraseSimple("Esattamente... Avevo attraccato nel posto sbagliato.","Mi sono dimenticato di entrare nel porto...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Di solito ci sono molti uomini che cercano di diventare marinai, ma ormai è troppo tardi - inizieranno a presentarsi al mattino. Forse vorresti affittare una stanza e aspettarli?";
				link.l1 = "Bene. Avete stanze libere?";
				link.l1.go = "room";
				link.l2 = "Non sono interessato a una stanza al momento. Ci vediamo.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Pensi che serviamo qui dei criminali ricercati? Sii grato che non sto chiamando le guardie.";
					link.l1 = "Grazie.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Capitano, non c'è anima viva nella taverna oggi. Tutti quelli disposti sono partiti con il Capitano Blackwood.";
						link.l1 = "Che peccato!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, mi dispiace capitano, sei solo un po' troppo in ritardo. Tutti i ragazzi che cercavano di parlare appena imbarcati con il valoroso capitano "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "Che peccato!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Capitano, la gente dice che sei piuttosto avaro. Non abbiamo nessuno qui che vorrebbe unirsi al tuo equipaggio.";
									link.l1 = "Capisco...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Sono tutto orecchi.";
			//link.l1 = "Cerco lavoro. Puoi aiutarmi?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Potresti dirmi le ultime notizie?","Cosa succede in queste terre?","Cosa c'è di nuovo sulla terra?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Sono venuto per un affare diverso.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Sai dove posso trovare "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Potresti dirmi dove potrei cercare "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Salve, sono venuto su invito di tuo figlio."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Allora, hai visto  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Mi può dire dove dovrei cercare  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Sai dove posso trovare il capitano di una pattuglia"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Allora, hai visto "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Sai qualcosa del capitano di una pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Potresti dirmi dove posso trovare un uomo chiamato "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Per caso ho trovato non lontano da qui alcuni documenti di nave....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Ascolta, sto cercando un vecchio amico mio, "+pchar.GenQuest.FindFugitive.Name+" è il suo nome. Un altro capitano mi ha detto che stava dirigendosi verso la tua colonia. L'hai incontrato per caso?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Niente, grazie, .";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Cosa hai detto? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Non ne ho mai sentito parlare.","Sei sicuro che lui provenga dalla nostra città? Non ho mai sentito parlare di una tale persona.","Non c'era nessuno del genere nella nostra piccola colonia. Non ne ho mai sentito parlare in tutto il tempo che sono stato qui.");
					link.l1 = "Sei sicuro?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Dai un'occhiata "+pchar.GenQuest.Hold_GenQuest.foundStr+", si trova spesso lì.";
					link.l1 = "Grazie, farò proprio così.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("Cosa hai detto? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Mai sentito parlare di lui. Sei sicuro che viene dal nostro villaggio? Non ho mai sentito parlare di una tale persona.","Eh-eh... Beh, ora solo il Signore stesso sa dove cercarlo - all'inferno o in paradiso. È morto più di un anno fa, ma la gente continua a chiedere di lui... Nessun riposo per il povero disgraziato..."),RandPhraseSimple("Non lo troverai lì - nel mondo dei vivi almeno. È morto non molto tempo fa - febbre gialla... Dio riposi la sua anima... Che coraggioso era! Quando era giovane, era un grande avventuriero! Ma quando la morte ti insegue, non c'è molto che tu possa fare...","Oh, ti sei perso lui? Ha lasciato questi luoghi molto tempo fa. Nessuno sa dove sia andato - forse nelle colonie nordamericane, forse a casa in Europa. Ha semplicemente raccolto i suoi averi e se n'è andato."),"Oh, stai cercando quello "+pchar.GenQuest.Hold_GenQuest.Name+" chi si è arricchito e si è comprato una casa in Nuova Inghilterra? Sai, c'erano momenti in cui gli vendeva rum a credito - mi deve ancora. La gente è così ingrata, lo sai.");
					link.l1 = "Capisco. Beh, grazie comunque.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Ebbene, dove altro cercarlo, se non nella taverna? È un visitatore frequente lì - annega i suoi peccati nel vino, he-he. Torna un po' più tardi - se si presenta, gli dirò di aspettarti.";	
					link.l1 = "Grazie, lo farò.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Come posso non essere sicuro se conosco personalmente tutti qui. Non è il primo anno che gestisco la taverna qui."+"Li ho visti tutti in tutte le condizioni possibili. A volte veniva la moglie a prendere suo marito, a volte se ne andavano da soli, e in alcune occasioni ho dovuto cacciarli. 'Sono sicuro?!' Certo che lo sono!";
			link.l1 = "Bene, grazie comunque...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("È un visitatore frequente qui, ma al momento non c'è. Torna di tanto in tanto - gli dirò di aspettarti qui se si presenta.","È un visitatore abituale qui. Se torni più tardi, sei certo di trovarlo lì.","Torna di tanto in tanto - è un visitatore frequente qui. Gli farò sapere che lo stavi cercando.");
			link.l1 = "Grazie, tornerò più tardi...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "È già arrivato qui, quindi dovrebbe essere da qualche parte...";
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "C'è qualcuno che non lo conosce? L'intero insediamento ne parla da diversi giorni.";
			link.l1 = "Potresti dirmi di più?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Un po', il capitano è stato giustiziato, lo stesso si può dire di alcuni dei suoi membri dell'equipaggio. Il resto sono stati dispersi nei Caraibi privati di grado e posizione... Per cosa? Secondo un giudice, aveva affondato un pirata durante una pattuglia e nascosto il bottino per sé\n"+"Ecco il punto, né il proprietario di questo vascello né i beni sono stati trovati... hanno setacciato le baie e i fiordi locali alla loro ricerca, ma senza successo.";
			link.l1 = "Cosa, nessuno dell'equipaggio ha rivelato la posizione della cache?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Neanche uno! Nemmeno sotto tortura! Ancora non riesco a capire, perché il governatore avrebbe creduto così facilmente a quella calunnia. Capitano "+pchar.GenQuest.CaptainComission.Name+" aveva una buona reputazione, e il suo equipaggio era ben addestrato e disciplinato, tale che qualsiasi ammiraglio lo avrebbe invidiato.";
			link.l1 = "E dove dovrei cercare i membri dell'equipaggio sopravvissuti?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Questo non lo so - si sono dispersi ai quattro venti... Anche se... ce n'è ancora uno, ma dubito che tu possa imparare molto da lui. È stato gravemente concusso. Sai, ha servito come cannoniere sotto "+pchar.GenQuest.CaptainComission.Name+". È stato trovato privo di sensi in una cala due giorni dopo quell'incidente. Prima è stato mandato all'ospedale e trattato come un eroe, ma con l'infittirsi della trama, l'hanno gettato nel calabrone e hanno cercato di interrogarlo, ma poi hanno deciso che prima doveva essere curato medicalmente, comunque.";
			link.l1 = "È ancora qui ora?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Sì, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" è il suo nome. Entra di tanto in tanto, spende i soldi che guadagna mendicando per il rum. Povera anima. Se lo vedo, gli dirò di aspettarti qui.";
			link.l1 = "Grazie, tornerò più tardi.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Lo conosco? Certo che sì. E perché ne hai bisogno?";
			link.l1 = "Ho affari con lui...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", dovresti stare attento con quel 'affare'. "+pchar.GenQuest.CaptainComission.Name+" è detenuto con l'accusa di pirateria, e gli uomini del governatore stanno ora setacciando l'isola alla ricerca dei suoi complici.";
			link.l1 = "Davvero! E cosa ha fatto?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Non so se sia vero o no, ma dicono che avesse nascosto il carico confiscato da una nave pirata di passaggio e non l'ha consegnato. Eppure nessuno ha ancora trovato né quel pirata, né il carico. Non riesco ancora a capire perché il governatore credesse così facilmente a quella calunnia. Capitano "+pchar.GenQuest.CaptainComission.CapName+"  aveva una reputazione decente, ed era un grande soldato, puoi fidarti della mia parola, "+GetAddress_Form(pchar)+".";
			link.l1 = "Bene, grazie per l'avvertimento. Ci vediamo.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "E per cosa te ne hai bisogno di lei?";
			link.l1 = "Ho affari con lei...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "La metà degli uomini del nostro insediamento sembra avere affari con lei. Se le nostre donne l'avessero presa, l'avrebbero gettata fuori dalle porte della città, nuda.";
			link.l1 = "Vabbè... "+GetSexPhrase("Sembra che mi sia messo in una lunga fila, allora. Beh, se qualcun altro viene a cercarla, digli di mettersi in fila dietro di me.","Capisco")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "È un visitatore frequente qui - di solito viene in cerca di un lavoro, ma ora non c'è. Torna di tanto in tanto - gli dirò di aspettarti qui se si fa vedere.";
			link.l1 = "Grazie, tornerò più tardi...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, quindi tu sei "+GetSexPhrase("quel capitano, che ha portato","quella ragazza, che ha portato")+" mio figlio prodigo con una giovane sposa?";
				link.l1 = "Sì, sono stato io ad aiutare.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, ci sei "+GetSexPhrase("lui è, il nostro benefattore","lei è, la nostra benefattrice")+". Aspetti una ricompensa, immagino?";
				link.l1 = "Beh, sto bene senza una ricompensa, ma un semplice ringraziamento sarebbe apprezzato.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sono molto grato a voi che non avete abbandonato mio figlio in situazioni difficili e lo avete aiutato a trovare una via d'uscita da una situazione delicata. Permettetemi di ringraziarvi e accettate questa modesta somma e un regalo da me personalmente.";
			link.l1 = "Grazie. Aiutare questa giovane coppia è stato un piacere per me.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Grazie? Che grazie?! Sono passati sei mesi da quando quel testone gira senza un lavoro - e guardalo, ha abbastanza tempo per una relazione! Quando avevo la sua età, già gestivo la mia attività! Pfft! Un governatore ha una figlia nubile - e quel stupido ha portato una sgualdrina senza famiglia né parenti a casa mia e ha osato chiedere la mia benedizione!";
			link.l1 = "Immagino che tu non creda nell'amore a prima vista?";
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
			dialog.text = "Amore? Amore!? Ti stai prendendo gioco di me o sei stupido? Vergognati di assecondare i capricci dei giovani e di comportarti come un ruffiano! Non solo hai portato via una ragazza da casa sua, ma hai anche rovinato la vita del mio ragazzo. Non ci saranno ringraziamenti per te. Addio.";
			link.l1 = "Altrettanto a te allora.";
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
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lasciami dare un'occhiata! Hmm... Ma sei un capitano te stesso. Credo che dovresti parlare di questo con il capo del porto.";
				link.l1 = "Grazie per il tuo consiglio.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Fammi dare un'occhiata! Oh! A giudicare dal nome, questo appartiene a uno dei miei clienti, un signore molto rispettato. Posso io stesso consegnare questi documenti al proprietario. Me li darai?";
				link.l1 = "Alla fine...";
				link.l1.go = "exit";
				link.l2 = "Prendili. Sono felice di essere stato d'aiuto.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Non mi importa a chi servire poiché i soldi non hanno nazionalità. Ma non ti aiuterò poiché sei arrivato sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+".","Sono solo un semplice proprietario di taverna, ma la collaborazione con "+NationNameAblative(sti(pchar.nation))+" non mi sembra attraente.");
				link.l1 = RandPhraseSimple("Bene, come desideri...","Beh, come preferisci...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Di solito abbiamo molti passeggeri qui. Tuttavia, non credo che ci sia anche solo un pollo tra loro, che potrebbe accettare di viaggiare sulla tua nave. La tua cattiva reputazione ti precede, solo un folle salirebbe a bordo con un mascalzone del genere.","Vengo abbastanza spesso avvicinato da commercianti che hanno bisogno di scorta. Ma la tua cattiva reputazione ti precede, e non ti raccomanderò a nessuno. Tengo alla mia reputazione, sai. Nessuno vuole assumere un lupo per guardare le proprie pecore.");
				link.l1 = RandPhraseSimple("Oh, davvero, non dovresti credere a tutti quei pettegolezzi...","Capisco. È difficile far tacere tutti.","La gente è troppo morbida al giorno d'oggi...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "E dove si trova la tua nave? O intendi portare i passeggeri sulla schiena e nuotare?";
				link.l1 = "Ehi, hai un punto...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Potrei avere un lavoro se non hai paura di venire nei insediamenti dei pirati o nei porti delle nazioni nemiche. Stai cercando qualcosa in particolare?";
			link.l1 = "Non dovrebbe essere un problema. Suppongo che potrei fornire scorta.";
			link.l1.go = "work_1";
			link.l2 = "Hai qualche passeggero? Posso portarli dove vogliono, se pagano per questo.";
			link.l2.go = "work_2";
			link.l3 = "No, tale lavoro non fa per me. Grazie.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Di solito non mi chiedono di fare da scorta. Chiedi ai mercanti nella taverna - forse avrebbero bisogno dei tuoi servizi.";
				link.l1 = "Bene, come dici tu.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Mi dispiace, ma non ho nessuno disposto a viaggiare con te.";
					link.l1 = "Capisco.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "C'è un uomo, appena entrato - stava chiedendo di recente di un vascello di passaggio. Puoi parlargli, se vuoi.";
					link.l1 = RandPhraseSimple("Chi è lui? Forse è un mascalzone? O, ancora peggio, un pirata ricercato?","E chi è lui? Ci saranno problemi con lui?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "No, oggi nessuno ha chiesto di questo. Forse, un altro giorno.";
					link.l1 = RandPhraseSimple("Ebbene, se non c'è, non c'è...","Proprio la mia fortuna... Oh, beh, ci vediamo, allora.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Non c'è nessuno per oggi. Torna tra un paio di giorni.";
				link.l1 = "Bene, come dici tu.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Chi potrebbe saperlo? Hai chiesto - ho risposto.","Ebbene, questo è un problema per te da risolvere. Non darei garanzie per nessuno lì.","Qui arrivano tutti i tipi. Questa è una taverna cap'n, non il maniero del governatore.");
			Link.l1 = "Grazie, allora tratteremo.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Chi potrebbe saperlo? Hai chiesto - ho risposto.","Ebbene, questo è per te da risolvere. Non mi fiderei di nessuno lì.","Qui viene ogni sorta di gente. Questa è una taverna cap'n, non il maniero del governatore.");
			Link.l1 = "Capisco. Scopriamo chi è quest'uomo...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Certo, Helen. Quanto tempo rimani? E che è successo, hai avuto una discussione con la vecchia Gladys?";
			if(!isDay())
			{
				link.l1 = "Solo per dormire fino al mattino. Se torno a casa ora, la sveglierò sicuramente.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "No, no, ho solo bisogno di salpare di notte, e non voglio svegliarla.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Voglio un bel sonno lungo e prendermi il mio tempo per alzarmi. Prenderò una stanza per un giorno.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "La stanza è occupata, "+GetAddress_Form(NPChar)+", non c'è nulla che posso fare per te.";
				link.l1 = "Beh, che peccato...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Il signor Henri Thibaut ha affittato la stanza al momento, e ha pagato per un mese in anticipo, quindi non c'è nulla che io possa fare per te, capitano.";
				link.l1 = "Beh, che peccato...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "La stanza è occupata, "+GetAddress_Form(NPChar)+", non c'è nulla che io possa fare per te.";
				link.l1 = "Beh, che peccato...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "La stanza è occupata, "+GetAddress_Form(NPChar)+", non c'è nulla che io possa fare per te.";
				link.l1 = "Beh, che peccato...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Purtroppo no, Capitano. Tutte le stanze sono occupate da Blackwood e i suoi uomini.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ah, che peccato!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Tutte le stanze? Ci sono più di una stanza qui?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Vuoi affittare una stanza? Nessun problema. 100 pezzi di otto ed è tua.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Ecco i tuoi soldi.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Mmm... Credo che tornerò più tardi...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "La stanza è tutta tua. Entra e rilassati.";
				link.l1 = "Grazie, compagno.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Vuoi affittare una stanza? Nessun problema. 100 pezzi di otto ed è tua.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Ecco i tuoi soldi.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Mmm... Credo che tornerò più tardi...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "La stanza è tutta tua. Entra e rilassati.";
					link.l1 = "Grazie, compagno.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Mi scusi, capitano, sfortunatamente non c'è nessuna stanza disponibile. L'ospite non se ne vuole andare. E ancora non mi ha pagato...";
				link.l1 = "Sembra che dovremo passare la notte nella sala comune...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Scusa. Parliamo d'altro.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Allora chiama le guardie. Che tipo di ospite è questo: non paga soldi, non vuole andarsene...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Quanto tempo prevedi di restare qui?";
			if(!isDay())
			{
				link.l1 = "Fino al mattino.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Fino alla notte.";
				link.l1.go = "room_night";
				link.l2 = "Fino alla prossima mattina.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexblock = true;
				SetTimerFunction("Mary_DeleteSexblock", 0, 0, 1);
			}
		break;

		case "room_day":
			dialog.text = "Ti costerà 5 pezzi di otto.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Affare fatto. Ecco a te.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("A quel prezzo? Stai affittando camere reali? Preferirei stare nella sala comune gratuitamente.","Aimè, sembra che il lusso di dormire su un letto sia al di là dei miei attuali mezzi. Immagino dovrò dormire nella sala comune su una panchina.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Non adesso. Cambiamo argomento.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			dialog.text = "Ti costerà 10 pezzi di otto.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Affare fatto. Ecco a te.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("A quel prezzo? Stai affittando camere reali? Preferirei stare nella sala comune gratuitamente.","Purtroppo, sembra che il lusso di dormire su un letto sia al di là dei miei attuali mezzi. Immagino che dovrò dormire nella sala comune su una panca.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Non adesso. Cambiamo argomento.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			dialog.text = "Ti costerà 5 pezzi di otto.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Affare fatto. Ecco a te.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("A quel prezzo? State affittando stanze reali? Preferirei stare nella sala comune gratuitamente.","Ahimè, sembra che il lusso di dormire su un letto sia oltre i miei attuali mezzi. Immagino che dovrò dormire nella sala comune su una panchina.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Non proprio adesso. Cambiamo argomento.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Vattene all'inferno da qui, mascalzone! La sala comune può essere libera, ma ci aspettiamo un comportamento decente!";
				link.l1 = "Va bene, va bene, me ne sto andando.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Sparisci di qui, mascalzone! La sala comune può essere libera ma ci aspettiamo un comportamento decente!";
				link.l1 = "Bene, bene, me ne sto andando.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Ferma questo comportamento oltraggioso nella mia taverna immediatamente o chiamerò le guardie!";
			link.l1 = "Bene, bene, me ne sto andando.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Non ne so molto... Sarebbe meglio chiedere ai clienti.";
			link.l1 = "Capisco, grazie.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Non forniamo servizi a credito, "+GetSexPhrase("signore","signorina")+".";
			link.l1 = "Pago in buona moneta. Non accetti più oro o argento?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Mi dispiace, "+GetSexPhrase("signore","signorina")+"capitano, ma il tuo amico aveva un debito, e ho pensato...";
			link.l1 = "Pensa di meno e lavora più velocemente, compagno. Ora, quanto deve il mio valoroso amico a te?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", signor"+GetSexPhrase("ter","s")+" capitano, e ha anche impegnato alcuni libri di chiesa - è tutto ciò che aveva con sé, che aveva un certo valore.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Ecco le tue monete. Consegnami i manoscritti. E stai attento con loro - non si tratta di un libro di incisioni osceni, ma di Sacre Scritture!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Aspetta un po'... Torno subito con i soldi";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", signore"+GetSexPhrase("ter","s")+" capitano.";
				link.l1 = "Saldarò il suo debito e prenderò ciò che ha lasciato come garanzia.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "No, signora"+GetSexPhrase("ter","s")+", non funzionerà così.";
			link.l1 = "Cosa intendi dire con 'non funzionerà così'? Un debito di capitano è saldato - lui sta bene. Hai indietro i tuoi soldi - tu stai bene. Prendo il suo pegno - sto bene. Tutti stanno bene - quindi perché 'non funzionerà così'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Perché, signora"+GetSexPhrase("ter","s")+"capitano, non ho bisogno dei soldi. Perché conosco fin troppo bene quel capitano, quindi non mi aspettavo realmente che lui mi ripagasse e prendesse questi manoscritti da me.";
			link.l1 = "Cosa intendi - non hai bisogno di soldi? Quindi avevi intenzione di tenere questi libri fin dall'inizio? Ma perché, nel nome di Dio?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "In nome di Dio - esattamente, ecco perché, signorina"+GetSexPhrase("ter","s")+". Mio figlio era molto malato, e io e mia moglie abbiamo fatto un voto per fare una donazione alla Chiesa se il nostro Signore Benedetto avesse curato il bambino dalla febbre. La misericordia del Signore è senza fine, mio figlio è vivo e sta bene, e ora dobbiamo mantenere il nostro voto. Ed è proprio il momento capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+" si presenta e impegni questi libri di chiesa. Non potevo permettere una tale oscenità - pagare per i drink con la Parola - e quindi ho deciso di consegnare questi libri al parroco della nostra parrocchia.";
			link.l1 = "Ebbene, certamente questa è una buona azione, ma dovresti anche sapere che questi libri appartengono in realtà a un altro prete - anzi, non solo a un prete, ma a un vescovo e al mio pastore spirituale. E potrebbe arrabbiarsi e addirittura maledire coloro che oserebbero donare la proprietà della Chiesa rubata. Vorrei comprarli da te e riportarli al sicuro a casa. Puoi donare il denaro alla tua parrocchia, sono sicuro che Dio l'apprezzerà lo stesso.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Signorina"+GetSexPhrase("ter","s")+"... Signorina"+GetSexPhrase("ter","s")+"capitano... Naturalmente, non ne avevo idea! Glieli restituirò, e non richiederò alcun denaro in cambio. Basta che ci metta una buona parola con il vescovo - forse, potrebbe benedirci e liberarci dal nostro voto...";
			link.l1 = "Certo che il tuo voto sarà considerato mantenuto! Dopotutto, hai rinunciato al tuo profitto per restituire i libri al loro legittimo proprietario. La chiesa particolare non conta, perché c'è solo un Dio e una Santa Chiesa Cattolica Apostolica, giusto? Bene, dammeli, e buona fortuna a te...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Uhm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Mai sentito parlare prima... Cos'è esattamente? Non ho mai sentito parlare di una cosa del genere in tutta la mia vita.";
			link.l1 = "Beh, è uno strumento del costruttore navale, "+pchar.GenQuest.Device.Shipyarder.Describe+". Qualcuno ti ha offerto qualcosa del genere?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Mmm... Sì, un tipo strano mi ha davvero portato quella cosa. Non mi ha detto cosa fosse, però - ha solo cercato di scambiarla per alcol. Naturalmente, ho rifiutato - non avevo bisogno di quel gingillo.";
				link.l1 = "E come si presentava e dove è andato? Ho davvero bisogno di quel strumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, niente del genere. Mi dispiace, non posso aiutarti. Chiedi in giro.";
				link.l1 = "Capisco. Beh - è ora di fare qualche domanda!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Era lì di recente, e ormai dovrebbe essere arrivato dal suo compagno - il negoziante. Prova a cercarlo al negozio - sicuramente deve essere lì.";
				link.l1 = "Grazie! Mi hai aiutato molto!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Oggi, di primo mattino, è salpato sulla sua lancia per una marina. Scommetto che ora sta in piedi al parapetto, ammirando il panorama. Se hai bisogno di lui, puoi cercare di trovarlo in mare o aspettare che torni tra un paio di giorni...";
				link.l1 = "Grazie! Credo che non aspetterò - sarà più facile trovarlo in mare. Buona fortuna!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Perché stai urlando? Ti sta aspettando da un bel po'. Ha già bevuto un litro intero di rum. Vai al piano di sopra nella stanza, lo troverai lì.";
			link.l1 = "Oh, capisco. Speriamo che sia ancora sveglio.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Sì, conosco quel signore. Dovrebbe essere da qualche parte in città - l'ho appena visto passare davanti alla mia finestra.";
				link.l1 = "Grazie! Andrò a cercarlo!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Sì, conosco quel signore. Dovrebbe essere da qualche parte in città - l'ho appena visto passare davanti alla mia finestra.";
					link.l1 = "Grazie! Andrò a cercarlo!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Sì, lui è ora in visita nella nostra città. Al momento non è qui - è salpato sulla sua brigantino. È probabile che non sia lontano da qui, nelle acque della nostra isola.";
					link.l1 = "Grazie compagno! Mi hai aiutato molto!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Mai sentito parlare di lui. No, non so nulla di quest'uomo.";
				link.l1 = "Capisco... Beh, la ricerca continua....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Sì, certo. Congratulazioni capitano. Sono già a conoscenza della tua vittoria. Ecco i tuoi soldi.";
			link.l1 = "Grazie, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, signore, "+pchar.GenQuest.Marginpassenger.q2Name+" è morto circa "+LinkRandPhrase("un mese","tre settimane","due mesi")+" fa. "+LinkRandPhrase("Improvvisamente caduto in febbre","È stato accoltellato alle porte della città - banditi o quei selvaggi dalla pelle rossa","È stato colpito in un duello")+". Possa Dio riposare la sua anima...";
				link.l1 = "Maledizione!.. E cosa dovrei fare con il suo... Vabbè, grazie per l'informazione. Ci vediamo, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Sì, dovrebbe essere da qualche parte in città. Cerca per le strade. Ma tieni presente che ogni giorno fino a mezzogiorno si trova nell'ufficio del governatore, e dopo le nove di sera si rinchiude in casa sua.";
				link.l1 = "Grazie! Andrò a cercarlo...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Sembra che il tuo capitano stesse dicendo la verità. "+pchar.GenQuest.FindFugitive.Name+" è effettivamente arrivato di recente nel nostro insediamento. Cercalo per le strade durante il giorno - di solito se ne sta a perdere tempo.","Mi hai già chiesto di quell'uomo, e ti ho detto tutto quello che sapevo!","Stai scherzando con me o sei davvero un idiota?! Stai facendo la stessa domanda per la terza volta!","Chissà come un tale idiota potrebbe diventare capitano...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Grazie, amico, mi hai aiutato molto!","Sì, sì, va bene.","Wow, Wow, non agitarti così tanto. Ho solo dimenticato.","Ebbene, lo ha fatto, come puoi vedere...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("No, compagno, non ho mai sentito quel nome prima. Chiedi in giro - forse qualcuno lo conosce...","Mi hai già chiesto di quell'uomo, e ti ho detto: non lo so!","Stai scherzando con me o sei davvero un idiota?! Mi stai facendo la stessa domanda per la terza volta!","Chissà come un idiota del genere potrebbe diventare capitano...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Capisco. Beh, grazie comunque.","Sì, sì, va bene.","Wow, Wow, non agitarti così tanto. Ho solo dimenticato.","Ebbene, come puoi vedere, lo ha fatto...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Sfortunatamente, non posso aiutarti ora - nessuno di quelli che conosco servirebbe sotto di te. Ma posso darti un consiglio - parla con quel marinaio che ha appena preso il tavolo proprio dietro di te. Lui e i suoi amici hanno appena lasciato una nave mercantile. Forse, accetteranno di venire con te.";
			link.l1 = "Bene, farò proprio così! Grazie mille!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "citiz_36", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Non posso dirti nulla di specifico, amico. Al momento nessun navigatore frequenta il mio posto. Prova a chiedere in giro nel porto - forse, la gente saprebbe di più.";
			link.l1 = "Capisco. Va bene, andrò a parlare con la gente.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Subito, signore!.. Il miglior vino francese! "+sld.name+"! Prepara la migliore stanza per gli ospiti! Saranno 1000 pesos, signore.";
			link.l1 = "Eccolo.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Vattene, mascalzone! Stai occupando uno spazio prezioso per i clienti che pagano!";
				link.l1 = "Bene, va bene... Me ne sto andando.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Sì - e spaventare tutti i miei clienti con il fatto che le mie guardie trascinano le persone fuori dalla taverna? E alcuni dei miei clienti non amano stare attorno ai soldati. Li rende nervosi, capisci? Non voglio rovinare la mia reputazione...";
				link.l1 = "Mmm, e se risolvessi il tuo problema?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Hai preso una decisione? È armato, sembra una sorta di mercenario professionista...";
				link.l1 = "Mmm, hai ragione, non mi va di discutere con un mercenario armato...";
				link.l1.go = "Exit";
				link.l2 = "Ebbene, non sono neanche una monaca di clausura... E voglio ancora affittare una stanza.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Ebbene, se riesci, ehm... a convincerlo ad andarsene, allora la stanza è tua fino al mattino. Naturalmente, gratis.";
				link.l1 = "Sai, ho cambiato idea. Non ho voglia di convincere nessuno.";
				link.l1.go = "Exit";
				link.l2 = "Vorrai guardare questo. Il tuo ospite indesiderato sta per volare fuori dalla tua taverna come un gabbiano gigante.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Capisco. Saranno cinque argenti.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Certo, ecco a te.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Effettivamente, sai cosa... Forse un'altra volta. Passerò il resto della giornata in piedi.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Saggia decisione. Saranno cinque argenti, e buona notte a te.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Ecco a te, e grazie - buona notte.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "Ripensandoci, non ho voglia di dormire. Mi aggirerò per la città, prenderò un po' d'aria notturna.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Certo, Helen. Saranno dieci pesos.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Certo, ecco a te.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Effettivamente... potrei fare qualcosa di utile con un'intera giornata. Forse un'altra volta.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Come desideri, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Potresti addirittura sentirti sonnolento dopo una buona passeggiata.";
			link.l1 = "Ah-ah, forse.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Come ritieni opportuno.";
			link.l1 = "Bene, alla prossima.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Certo, Helen, sono tutto orecchie.";
			link.l1 = "Quali sono le ultime notizie o voci interessanti in città?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Paga il triplo del prezzo usuale, quindi... capisci. E non ti consiglierei di rifiutare - ha un temperamento difficile. Soprattutto ultimamente.";
			link.l1 = "Cosa c'è che non va con lui?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Ossessione, ecco cosa. All'inizio, era un tipo generoso, gentile. I suoi marinai spendevano soldi nelle taverne, compravano regali per le ragazze. Una vera festa iniziava quando la 'Lady Beth' entrava in porto. E adesso? Ora comprano solo provviste e reclutano persone indiscriminatamente. Come se non avessero bisogno di marinai, ma solo di mani da lavoro. Beh, puoi parlargli tu stesso.";
			link.l1 = "Forse lo farò. Grazie.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
