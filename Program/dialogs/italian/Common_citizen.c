// boal 25/04/04 общий диалог горожан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Una spia? Guardie!","Allarme! C'è un intruso!");
				link.l1 = "Taci. Me ne vado.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Dicono che tu sei quello che governa questa città, "+GetSexPhrase("signore","signorina")+".","Che piacevole incontro, il capo della città mi ha rivolto una domanda.");
					link.l1 = RandPhraseSimple("Ho cambiato idea.","Sto semplicemente esplorando questa città. Addio.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ho una domanda per te.","Mi serve informazione.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Voglio discutere di affari.","Riguardo alle finanze...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Cosa vuoi? Passa avanti.","Non stare sulla strada, sparisci!");
					link.l1 = RandPhraseSimple("Ehi, smetti di abbaiare, non lo farai?","Calmati, o potresti pentirtene!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ho una domanda per te.","Un momento della tua attenzione, per favore. Ho una domanda.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Voglio discutere di affari.","Riguardo alle finanze...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Il mio nome è ","Il mio nome è ","Potete chiamarmi ")+GetFullName(npchar)+LinkRandPhrase(". Di cosa hai bisogno?",". Non ho "+NPCharSexPhrase(NPChar,"ti ho visto qui prima","ti ho visto lì prima")+", chi sei tu?",". Chi sei tu e cosa vuoi da me?"),LinkRandPhrase("Saluti, "+GetAddress_Form(NPChar)+". Il mio nome è "+GetFullName(npchar)+". Qual è il tuo?","Ciao, "+GetAddress_Form(NPChar)+"! Io sono "+GetFullName(npchar)+". Posso sapere il tuo nome?","Sì, "+GetAddress_Form(NPChar)+". Cosa vuoi? A proposito, il mio nome è "+GetFullName(npchar)+". E tu chi sei?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Per tuono! ","Cavolo! ","Malocchio su di te! ")+"Sì, io sono il Capitano "+GetFullName(Pchar)+LinkRandPhrase(", davvero non hai sentito parlare di me"+NPCharSexPhrase(NPChar,", furfante?","?")," e "+GetSexPhrase("il pirata più notorio","la piratessa più famigerata")+" in queste acque! "," e possa bruciare all'inferno se non è vero!"),LinkRandPhrase("Sono il Capitano"+GetFullName(Pchar)+".","Il mio nome è "+GetFullName(Pchar)+".","Potete chiamarmi Capitano "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Capitano, potresti per favore aiutarmi?";
					link.l1 = LinkRandPhrase("Mi dispiace, no. Ho poco tempo da risparmiare.","Scusa, non posso. Troppo occupato.","No, non posso. Ho questioni urgenti che richiedono la mia attenzione.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Certo che posso. Qual è il problema?","Sì, ti aiuterò. Dimmi di più su quel tuo affare.","Raccontami di più su quel tuo affare...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Sì, Capitano, sto ascoltando.";
					link.l1 = NPChar.name+", ho trovato il tuo anello di matrimonio.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Voglio saperne di più su questa città.","Raccontami di questa città.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Ho una domanda per te.","Ho bisogno di informazioni.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Voglio discutere di affari.","Riguardo alle finanze...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Fermati! Dimmi chi sei - subito! Sto cercando una spia nemica su richiesta del governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Fermati! Agisco nell'interesse della città "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"per ordine del governatore. Sto cercando in città un agente ostile.","Fermati, amico! Il governatore locale "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" vuole trovare una spia in città."),LinkRandPhrase("Fermati, signora! Dimmi chi sei - subito! Sto cercando una spia nemica su richiesta del governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Donna, devo trattenerti! Agisco nell'interesse della città "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"per ordine del governatore. Sto cercando in città un agente ostile","Fermati, bellezza! Un governatore locale "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" vuole trovare una spia in città..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Forse puoi darmi un consiglio. Voglio comprare "+pchar.GenQuest.Device.Shipyarder.Type+", e mi è stato detto che veniva venduto nella tua città. Beh, qualcuno lo stava vendendo per le strade. Sai qualcosa a riguardo?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Sei consapevole","Sapevi che","Hai sentito")+"che una chiesa locale è stata saccheggiata di recente?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, sei tu, "+GetFullName(Pchar)+" "+GetSexPhrase(", vecchio mascalzone","- donna di successo")+"","Buono vederti di nuovo, "+GetSexPhrase("vecchio amico","bellezza")+" "+Pchar.name,"Oh, è il buon vecchio "+GetSexPhrase("Capitano","signora")+" "+GetFullName(Pchar))+LinkRandPhrase(". Credevo che tu fossi morto!",". E, certamente, "+GetSexPhrase("ubriaco come al solito.","già sotto la pioggia.")+"",". E, come vedo, ancora in libertà!")+LinkRandPhrase("Allora, parla liberamente - di cosa hai bisogno?","Di che cosa hai bisogno questa volta?","Mi stai disturbando di nuovo per niente?"),LinkRandPhrase(TimeGreeting()+", Capitano ","Ciao, "+GetAddress_Form(NPChar)+" ","Ti saluto, Capitano ")+GetFullName(Pchar)+LinkRandPhrase(". Cosa potrebbe "+GetSexPhrase("un così galante gentiluomo","una signora così affascinante")+", piace? Potresti aver bisogno di qualcosa da me?",". Per cosa sei venuto?",". Cosa vuoi sapere questa volta?")),PCharRepPhrase(LinkRandPhrase("Ciao, Capitano ","Ciao. Ah, sei tu "+GetAddress_Form(NPChar)+" ","Oh, Capitano ")+GetFullName(Pchar)+LinkRandPhrase(", ho pensato"+NPCharSexPhrase(NPChar," "," ")+"non ci saremmo mai più incontrati,",", non posso dire che sono contento"+NPCharSexPhrase(NPChar," "," ")+"vederti, ma",", vedo, sei ancora vivo. Spiacente. Quindi,")+LinkRandPhrase("di cosa hai bisogno?","per cosa sei venuto?"," cosa posso "+NPCharSexPhrase(NPChar,"può aiutarti?","di cosa posso aiutarti?")),LinkRandPhrase(TimeGreeting()+", Capitano "+GetFullName(Pchar)+". Con cosa posso aiutarti?","Oh, se non è"+GetSexPhrase("","")+" Capitano "+GetFullName(Pchar)+"! Cosa vorresti sapere questa volta?","Ciao, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Volevi qualcosa?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("No, stai sentendo cose. Me ne vado adesso.","No, niente - stavo solo andando"+GetSexPhrase("","")+" alla taverna."),RandPhraseSimple("No, niente. Buona fortuna a te!","Solo guardandomi attorno. Arrivederci."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Quali domande?";
			link.l1 = "Ti suona familiare il nome su questi documenti?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Non mi importa dei documenti sconosciuti. Inoltre, non so come leggere. Vai dal usuraio, quel diavolo sicuramente sa come leggere e scrivere.","Non ho la minima idea di cosa stai parlando. Chiedi in giro ai cittadini, Capitano "+GetFullName(Pchar)+".","Non ho davvero idea di come aiutarti, Capitano "+GetFullName(Pchar)+". Prova a chiedere all'usuraio - forse, potrebbe saperlo.");
			link.l1 = "Seguirò volentieri il tuo consiglio!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ma non stai mentendo, Capitano "+GetFullName(Pchar)+"?","E allora che, "+PChar.name+"?","Ti ricorderò, "+GetFullName(Pchar)+".")+"E ora, di cosa hai bisogno?",LinkRandPhrase("Un piacere incontrarti, Capitano "+PChar.name,"Contento"+NPCharSexPhrase(NPChar," "," ")+" per incontrarti, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Un piacere conoscerti, Capitano "+PChar.name)+". Ma, suppongo, sei venuto qui per più che solo conoscere il mio nome?");

            link.l1 = PCharRepPhrase("Volevo"+GetSexPhrase("","")+" per sapere qualcosa su questo buco che chiamate città!","Volevo"+GetSexPhrase("","")+" per sapere qualcosa su questa città.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Ho una domanda per te.","Ho bisogno di informazioni.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Voglio discutere di affari.","Riguardo alle finanze...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Forse puoi darmi qualche consiglio. Voglio acquistare "+pchar.GenQuest.Device.Shipyarder.Type+", e mi è stato detto che veniva venduto nella tua città. Beh, qualcuno lo stava vendendo per le strade. Sai qualcosa a riguardo?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Fermati! Dimmi chi sei - subito! Sto cercando una spia nemica su richiesta del governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Fermati! Agisco nell'interesse di"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" per ordine del governatore. Sto cercando in città un agente ostile.","Fermati, amico! Il governatore locale "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" vuole trovare una spia in città."),LinkRandPhrase("Ferma, signora! Dimmi chi sei - subito! Sto cercando una spia nemica su richiesta del governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Donna, devo trattenerti! Agisco nell'interesse della città "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"per ordine del governatore. Sto cercando in città un agente ostile.","Fermati, bella donna! Governatore locale "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" vuole cercare una spia in città..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Sei consapevole","Hai sentito","Hai sentito")+"che una chiesa locale è stata saccheggiata di recente?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("No, stai sentendo cose. Me ne vado adesso.","No, niente - stavo solo andando alla taverna."),RandPhraseSimple("No, niente. Buona fortuna a te!","Solo guardandomi attorno. Addio."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh sì, sono quasi altrettanto contento"+NPCharSexPhrase(NPChar," "," ")+" vederti come una tazza di alcol. Chiedi quello che vuoi.","Ti piace parlare, Capitano? Beh, anche a me... Soprattutto davanti a una tazza di rum.","Sì, "+PChar.name+"?"),LinkRandPhrase("Di cosa hai bisogno?","Capisco, Capitano "+PChar.name+". Sei tu"+GetSexPhrase("","")+" un gran chiacchierone. ","Mi hai stancato"+GetSexPhrase("","")+" con le tue domande, Capitano. Meglio aiutarmi con il rum.")),PCharRepPhrase(LinkRandPhrase("Cosa vuoi sapere "+GetAddress_Form(NPChar)+"?","Ti sto ascoltando, Capitano.","Devo andare, quindi per favore sbrigati, Capitano."),LinkRandPhrase("Sempre lieto"+NPCharSexPhrase(NPChar," "," ")+"  avere una buona compagnia, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Parla liberamente.","Sì, "+GetAddress_Form(NPChar)+"?","Ti piace chiacchierare, Capitano? Beh, anche a me...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("Quali pettegolezzi sono popolari nell'osteria locale?","Cosa sta succedendo in queste terre?","Cosa c'è di nuovo a terra qui?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Potresti indicarmi la strada?","Non riesco a trovare una via per un certo posto...","Potresti mostrare la strada...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Voglio sapere cosa dice la gente su una certa persona.","Non sai cosa dicono le persone su una certa persona?","Vorrei conoscere qualcosa sui locali.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "Per favore, dimmi di più sulla tua colonia.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("Ho degli affari importanti!","Ho degli affari con te.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("No, stai sentendo cose. Me ne vado adesso.","No, niente - stavo solo andando alla taverna."),RandPhraseSimple("No, niente. Buona fortuna a te!","Solo sto dando un'occhiata. Addio."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Di chi vorresti sapere?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Sul governatore.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Sul proprietario della taverna locale.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Sul capitano del porto.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Sul proprietario del negozio locale.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Mai mente, dimenticalo.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("Onestamente, non ne so molto, ma posso comunque raccontarti una cosa o due.","E cosa ti interessa della nostra colonia?","Certo. Cosa vorresti sapere?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Che tipo di città è questa?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "Cosa sai del forte che difende la città?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Cambiamo argomento.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Stai scherzando? O prendendo in giro? Guarda l'angolo destro del tuo schermo.";
			link.l1 = "Sì, colpa mia.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Non so nulla a riguardo.";
			link.l1 = "Peccato.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Mmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Non ne ho mai sentito parlare prima... Ma cos'è, in realtà? Non ho mai sentito parlare di una cosa del genere in tutta la mia vita"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Ebbene, è uno strumento del costruttore navale, "+pchar.GenQuest.Device.Shipyarder.Describe+". Qualcuno stava vendendo una cosa del genere in città? Forse. Hai notato che qualcuno aveva una cosa del genere su di sé?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Mmm... Sì, suppongo di aver visto una persona con un oggetto simile. Se ne andava in giro con esso diverse ore fa. Un dispositivo interessante, certamente.";
				link.l1 = "E come sembrava e dove è andato? Ho davvero bisogno di quel strumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, non ho visto nulla del genere.";
				link.l1 = "Capisco. Beh - è ora di chiedere in giro!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"E cosa c'entra con me? Sono del posto!","Ebbene, perché mi disturbi con questo? Vivo in questa città e non so nulla di simili cose!"),NPCharSexPhrase(npchar,"Cosa vuoi di nuovo da me? Non ti ho già detto che non sono la spia?!","Non ti ho già detto che sono del posto?!"),NPCharSexPhrase(npchar,"Mia cara, sei tu di nuovo! Lasciami in pace - sono un locale!","Perché mi infastidisci di nuovo con le tue domande stupide?"),NPCharSexPhrase(npchar,"Di nuovo! Questo è uno scandalo!","Ascolta, lasciami stare, va bene? Per favore!"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Chi può confermare la tua affermazione?","Oh, mi dispiace - ti avevo già chiesto...","Mi dispiace, ci sono così tante persone...","Va bene, va bene...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Chiunque può! Ascolta, perché continui a tormentarmi?! Se hai un problema, vai a vedere il governatore e risolvi tutto!",link.l1 ="Mmm... Probabilmente è meglio non disturbarlo per una cosa così insignificante. Ti credo.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Chiunque in questa città! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" può farlo, per esempio, ora che "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"lui","lei")+" è proprio lì.","Oh, Signore, beh, per esempio, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" posso farlo.");				
			link.l1 = "Bene, vediamo allora.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Sì, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," è davvero un locale.","è davvero del posto.");
			link.l1 = RandPhraseSimple("Vedo"+GetSexPhrase("","")+". Grazie per l'aiuto.","Tutto chiaro. Grazie per l'aiuto.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "Vedi, ieri ero fuori città, stavo facendo una passeggiata, e ho perso il mio anello di matrimonio..."+GetSexPhrase("Capitano, potresti per favore cercarlo?","Signora, per favore, aiutami a trovarlo!")+"";
			link.l1 = "Certo "+GetSexPhrase("Posso! Per una ragazza bella come te, posso fare qualsiasi cosa!","Ti aiuterò. La Chiesa ci insegna ad aiutare coloro che sono in bisogno.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("No, non posso. Mi dispiace. Ho troppo da fare.","Mi dispiace, non posso. Mi sono appena ricordato"+GetSexPhrase("","")+", che ho ancora affari incompleti...","Ho pochissimo tempo, quindi non posso aiutarti con niente...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Capitano","Signora")+", è davvero fantastico! Per favore, trova questo anello per me, mio marito arriva solo "+sti(NPChar.LifeDay)+" giorni, e non vorrei che mi vedesse senza la mia fede nuziale.";
			link.l1 = RandPhraseSimple("Dove dici di averlo perso?","Dove l'hai effettivamente perso?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Proprio oltre le porte della città...";
			link.l1 = "Bene, allora me ne vado a cercarlo...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Sì, per favore. E sbrigati - ricorda che hai solo "+sti(NPChar.LifeDay)+" giorni.";
			link.l1 = "Mi ricordo.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Capitano","signorina")+"! Sono così felice! Come posso ringraziarti?";
			link.l1 = "Oh, non c'è bisogno di ringraziamenti - l'ho fatto del tutto disinteressatamente.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Un paio di centinaia di pesos sicuramente non farebbero male...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "Oh, "+GetSexPhrase("Capitano, sei una persona così nobile","signora, sei così nobile")+"! Sicuramente pregherò per te in chiesa! Addio...";
			link.l1 = "Addio, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Oh, ma certo. Ecco -"+FindRussianMoneyString(iTemp)+". Questo è tutto quello che ho. Per favore, prendi questi soldi... E addio.";
			link.l1 = "Addio, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, non so nulla a riguardo.","Non so nulla a riguardo.","Non so nulla.");
					link.l1 = LinkRandPhrase("Bene, grazie.","Capisco, grazie.","Bene, per favore scusami.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Non so nulla a riguardo, ma puoi chiedere ai clienti della taverna - sicuramente sapranno dirti una cosa o due.","Non posso dirti nulla. Chiedi in giro alla taverna.","Non so nulla in particolare, ma ho sentito dire che c'era pettegolezzo nella taverna.");
				link.l1 = "Bene, è qualcosa almeno.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta - come cittadino di questa città, devo chiederti di astenerti dal camminare in giro con una lama sguainata.","Ascolta - come cittadino di questa città, devo chiederti di astenerti dal girare con una spada sguainata.");
				link.l1 = LinkRandPhrase("Bene.","Bene.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Frena i tuoi cavalli "+GetSexPhrase("compagno","ragazza")+" quando corri in giro con un'arma in mano. Mi rende nervoso...","Non mi piace quando "+GetSexPhrase("uomini","chiunque")+" cammina in giro con le armi pronte. Mi spaventa...");
				link.l1 = RandPhraseSimple("Capito.","Lo metterò via.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
