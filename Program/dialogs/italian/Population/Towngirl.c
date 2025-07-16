//Jason общий диалог мещанок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
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
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
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
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Dicono che tu possiedi questa città, "+GetSexPhrase("signore","signorina")+".","Che bel incontro! Che bel incontro! Il governatore in persona sta parlando con me!");
					link.l1 = RandPhraseSimple("Ho cambiato idea. Buona fortuna!","Solo passeggiando per la città. Arrivederci.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ho una domanda per te.","Ho bisogno di alcune informazioni.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Voglio discutere di questioni finanziarie.","Sulle finanze...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Cosa vuoi? Vai avanti.","Smetti di ostacolare la mia strada, sparisci.");
					link.l1 = RandPhraseSimple("Cosa stai facendo?","Calma, o lo farò io.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Voglio farti una domanda.","Solo un minuto della vostra attenzione, per favore. Una domanda.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Voglio discutere di questioni finanziarie.","Riguardo alle finanze...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Sono","Il mio nome è ","Potete chiamarmi ")+GetFullName(npchar)+LinkRandPhrase(". Cosa vuoi?",". Non ti ho visto prima "+", chi sei tu?",". Chi sei tu e cosa vuoi da me?"),LinkRandPhrase("Saluti, "+GetAddress_Form(NPChar)+". Il mio nome è "+GetFullName(npchar)+". E come ti chiami?","Ciao "+GetAddress_Form(NPChar)+"! Io sono "+GetFullName(npchar)+". Posso sapere il tuo nome?","Sì, "+GetAddress_Form(NPChar)+". Cosa vuoi? E tra l'altro il mio nome è "+GetFullName(npchar)+". E qual è il tuo nome?"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("Maledizione a me! ","Maledizione! ","Maledetto! ")+"Sì, sono il capitano "+GetFullName(Pchar)+LinkRandPhrase(", non hai mai sentito parlare di me, bastardo?"," e "+GetSexPhrase("il pirata più famoso","la più famosa piratessa")+" in mare!"," e dannami se sbaglio!"),LinkRandPhrase("Sono "+GetFullName(Pchar)+", capitano.","Il mio nome è "+GetFullName(Pchar)+".","Potete chiamarmi capitano "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("L'intera città è sul chi vive - è arrivato don Fernando de Alamida, l'ispettore reale. Sai, ho visto molto qui, ma questo... Non è il dolore che cambia le persone, ma come lo affrontano. Dicono che sia diventato un uomo diverso dopo la morte del padre. Ora non troverai un servitore della Corona più incorruttibile e... spietato in tutto l'Arcipelago.","Guarda solo la 'Santa Misericordia'! Dicono che sia stato il re stesso a ordinarne la costruzione secondo disegni speciali. E nota - non un singolo graffio. Come se la Vergine Maria stessa la proteggesse. Anche se ho sentito voci... forse non è per niente la Vergine.","Sai quante volte hanno cercato di uccidere don Fernando? Dodici attacchi in acque libere - e solo nell'ultimo anno! Beh, con un equipaggio così leale e addestrato, e sotto la protezione del Signore - sopravviverà anche al tredicesimo!"),LinkRandPhrase("Hai sentito? Don Fernando de Alamida è arrivato nella nostra città, e dicono che si trovi da qualche parte nelle strade in questo momento. Mi piacerebbe vederlo con i miei stessi occhi...","Un uomo complicato, questo don Fernando. Alcuni dicono che sia un salvatore, che purifica la Madrepatria dalla sporcizia. Altri sussurrano che qualcosa si è spezzato in lui dopo la morte del padre e presto piangeremo tutti. Ma ti dirò questo: non aver paura di lui. Teme coloro che l'hanno reso ciò che è.","Un uomo così affascinante, questo don Fernando! Ma sai cosa è strano? È come se non notasse nessuno. Tutto dovere e servizio. Ho sentito dire che c'era una ragazza... ma dopo aver incontrato un prete, ha completamente rifiutato i piaceri mondani. Come se avesse fatto un voto."),RandPhraseSimple(RandPhraseSimple("Maledetto ispettore! Mentre lui è qui - la città è come morta. Niente commercio, niente divertimento. Anche respirare, sembra, deve essere più silenzioso. E sai qual è la cosa più spaventosa? È la stessa in ogni porto. Come un orologio. Sua Maestà Reale non avrebbe potuto inventare appositamente questa tortura per tutti noi!","Don Fernando ha visitato nuovamente l'orfanotrofio. Dona generosamente, prega per ore. Un uomo così degno dovrebbe essere preso come esempio da quei maledetti peculatori!"),RandPhraseSimple("Ha! 'Santo' Fernando ha chiuso tutte le case di tolleranza di nuovo. Beh, non importa, presto salperà e riapriranno subito.","È arrivato l'ispett... l'ispettore, ecco cosa! Don Fernando de Almeyda, o come diavolo si chiama, Alamida! Così importante che lo stesso governatore gli va in punta di piedi attorno. Dicono che ti guarda negli occhi e vede tutti i tuoi peccati immediatamente. Terrificante!")));
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = "Volevo solo parlare di questa città.";
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Ho una domanda per te.","Ho bisogno di alcune informazioni.");
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
						link.l3 = RandPhraseSimple("Voglio discutere di questioni finanziarie.","Sulle finanze...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Ascolta, spero che tu possa aiutarmi. Voglio comprare un "+pchar.GenQuest.Device.Shipyarder.Type+", e mi è stato detto che questa cosa è stata venduta nella tua città. Beh, qualcuno la stava vendendo al mercato. Sai qualcosa al riguardo?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Conosci ","Sei consapevole ","Hai sentito ")+"che la chiesa locale è stata derubata di recente?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, sei tu "+GetFullName(Pchar)+" "+GetSexPhrase("- vecchio amico!","- bella!")+"","Sono contento di vederti, "+GetSexPhrase("vecchio amico!","bella!")+" "+Pchar.name,"Oh, questo è il "+GetSexPhrase("il capitano in persona","la capitana stessa")+" "+GetFullName(Pchar))+RandPhraseSimple(". Pensavo che tu fossi morto!",". E forse "+GetSexPhrase("ubriaco come sempre.","un po' ubriaco."))+LinkRandPhrase("Continua, di cosa hai bisogno?","Che cosa è questa volta?","Mi stai disturbando di nuovo?"),LinkRandPhrase(TimeGreeting()+", capitano ","Buongiorno a te, "+GetAddress_Form(NPChar)+" ","Saluti, capitano ")+GetFullName(Pchar)+LinkRandPhrase(". Come posso aiutare a "+GetSexPhrase("un uomo così degno","una ragazza così degna")+", come te?",". Perché sei qui?",". Cosa vuoi sapere questa volta?")),PCharRepPhrase(LinkRandPhrase("Ciao, capitano ","Saluti, ah, sei tu "+GetAddress_Form(NPChar)+" ","Ah, capitano ")+GetFullName(Pchar)+LinkRandPhrase(", pensavo che non ci saremmo mai incontrati di nuovo, e",", Non dirò che sono felice di vederti ma",", vedo che sei ancora vivo, che vergogna e")+LinkRandPhrase(" cosa vuoi?"," perché sei qui?","come posso aiutarti?"),LinkRandPhrase(TimeGreeting()+", capitano "+GetFullName(Pchar)+". Come posso aiutarti?","Oh, quello è il capitano "+GetFullName(Pchar)+"! Come posso aiutarti?","Saluti, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Vuoi qualcosa?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Le tue orecchie ti ingannano. Devo andare.","No, non è niente, ero in viaggio verso la taverna."),RandPhraseSimple("Bene, come vuoi. Buona fortuna!","Solo passeggiando per la città. Addio."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Domande?";
			link.l1 = "Questo nome sui documenti significa qualcosa per te?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Non me ne frega niente di un foglio sconosciuto e non so leggere. Vai dal usuraio, dicono che sa leggere quelle lettere del diavolo.","Non so di cosa stai parlando, chiedi ad altri cittadini della città, capitano"+GetFullName(Pchar)+".","Non so nemmeno come aiutarti, capitano "+GetFullName(Pchar)+". Prova a parlare con l'usuraio, potrebbe saperlo.");
			link.l1 = "Seguirò il tuo consiglio con grande piacere!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Non stai mentendo, capitano "+GetFullName(Pchar)+"?","Allora cosa"+PChar.name+"?","Ti ricorderò, "+GetFullName(Pchar)+".")+"Ora dimmi, cosa vuoi?",LinkRandPhrase("Piacevole conoscervi, capitano "+PChar.name,"Contento del nostro incontro,"+GetAddress_Form(NPChar)+" "+PChar.lastname,"È un piacere, capitano "+PChar.name)+". Ma dubito che volessi solo conoscere il mio nome, giusto?");
            link.l1 = PCharRepPhrase("Volevo solo chiedere qualcosa riguardo a questo buco che chiamate 'la città'.","Voglio chiederti qualcosa su questa città.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Ho una domanda per te.","Mi serve qualche informazione.");
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
					link.l3 = RandPhraseSimple("Voglio discutere questioni finanziarie.","Sulle finanze...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Ascolta, spero che tu possa aiutarmi. Voglio comprare un "+pchar.GenQuest.Device.Shipyarder.Type+" e mi è stato detto che questa cosa è stata venduta nella tua città. Beh, qualcuno la stava vendendo per le strade. Sai qualcosa al riguardo?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("Conosci ","Sei consapevole ","Hai sentito ")+" che la chiesa locale è stata derubata di recente?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Le tue orecchie ti ingannano. Devo andare.","No, non è niente, ero in viaggio verso la taverna."),RandPhraseSimple("Beh, non è niente, Buona fortuna!","Solo passeggiando per la città. Addio."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, e sono felice di vederti come sono felice per un bicchiere di rum, chiedi quello che vuoi.","Ti piace parlare, capitano? Anche a me... Soprattutto con una tazza di rum.","Sì, "+PChar.name+"?"),RandPhraseSimple("Cosa vuoi ancora?","Lo prendo, capitano "+PChar.name+", che ti piace chiacchierare?")),PCharRepPhrase(LinkRandPhrase("Cosa altro vuoi "+GetAddress_Form(NPChar)+"?","Sto ascoltando, capitano.","Devo andare, quindi chiedimi in fretta, capitano."),LinkRandPhrase("Sono sempre contento di una piacevole compagnia, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Parla.","Sì, "+GetAddress_Form(NPChar)+"?","Ti piace parlare, capitano? Anche a me... ")));
			link.l1 = LinkRandPhrase("Quali voci corrono in questa città?","Ci sono novità in queste terre?","Come va la vita sulla terraferma?");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("Potresti mostrarmi la strada?","Non riesco a trovare la strada per un posto...","Aiutami a raggiungere un posto...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Voglio sapere cosa dicono le persone su una persona.","Sai cosa dicono le persone su una persona?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Voglio saperne di più sui locali.","Potete dirmi qualcosa sui locali?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Le tue orecchie ti ingannano. Devo andare.","No, non è niente, ero in viaggio per la taverna."),RandPhraseSimple("Bene, non è niente. Buona fortuna!","Solo passeggiando per la città. Arrivederci."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Di chi sei interessato?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Voglio sapere di più sul governatore.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Vuoi saperne di più sul proprietario della taverna locale.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Voglio saperne di più sul maestro del cantiere navale locale.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Voglio saperne di più sul proprietario del negozio locale.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Non è niente. Dimenticalo.";
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
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Mh, "+pchar.GenQuest.Device.Shipyarder.Type+"? Non ne ho mai sentito parlare... Vivo qui da molto tempo e non ho mai visto nulla del genere.";
			link.l1 = "Ebbene, questo è uno strumento per la costruzione di navi, "+pchar.GenQuest.Device.Shipyarder.Describe+". Qualcuno ha venduto qualcosa del genere in città? O forse l'ha portato in giro e l'hai notato?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Mh... Sì, ho visto un uomo con quella cosa diverse ore fa. Stava camminando per le strade. Uno strumento interessante era.";
				link.l1 = "Come sembrava e dove stava andando? Ho davvero bisogno di qualcosa del genere.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, non ho visto nulla del genere.";
				link.l1 = "Capisco. Continuerò a chiedere allora.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, non so nulla a riguardo.","No, dovrei andare.","Non so nulla.");
					link.l1 = LinkRandPhrase("Bene, grazie.","Capisco, grazie.","Bene, scusatemi.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Non so nulla a riguardo, ma potresti provare a chiedere ad alcuni dei clienti abituali della taverna, ti diranno sicuramente di più.","Non posso dirti nulla, chiedi a qualcuno nella taverna.");
				link.l1 = "Grazie per quello.";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, come cittadino di questa città ti chiedo di infilare la tua spada nel fodero.","Ascolta, come cittadino di questa città ti chiedo di rinfoderare la tua spada.");
				link.l1 = LinkRandPhrase("Bene.","Come desideri.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Stai attento mentre corri con un'arma. Posso diventare nervoso...","Non mi piace quando un uomo sconosciuto cammina davanti a me con un'arma sguainata. Mi spaventa...");
				link.l1 = RandPhraseSimple("L'ho capito.","Non preoccuparti.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
