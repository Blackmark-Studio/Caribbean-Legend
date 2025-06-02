//Jason общий диалог мещан
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
    string sTemp, sCity, sTitle;
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
				    dialog.text = RandPhraseSimple("Man sagt, dass du diese Stadt besitzt, "+GetSexPhrase("Herr","Fräulein")+".","Solch eine nette Begegnung, "+GetSexPhrase("Herr","Fräulein")+"!");
					link.l1 = RandPhraseSimple("Ich habe meine Meinung geändert. Viel Glück!","Nur durch die Stadt spazieren. Auf Wiedersehen.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche einige Informationen.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Ich möchte finanzielle Angelegenheiten besprechen.","Über Finanzen...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Alarm! Ein bewaffneter Wahnsinniger ist hier! Zu den Waffen!","Zu den Waffen! Ein bewaffneter Wahnsinniger ist hier!");
						link.l1 = RandPhraseSimple("Was?!","Was machst du da?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("Was willst du? Geh weiter.","Hör auf, mir den Weg zu versperren, verschwinde.");
						link.l1 = RandPhraseSimple("Weißt du was? Bell nicht!","Beruhige dich. Oder ich werde es selbst tun!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Ich möchte dich etwas fragen.","Nur eine Minute Ihrer Aufmerksamkeit, bitte. Eine Frage.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Ich möchte finanzielle Angelegenheiten besprechen.","Über Finanzen...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Guten Tag, "+GetAddress_Form(NPChar)+". Ich sehe, dass du Kapitän deines eigenen Schiffes bist. Ich möchte dich um einen Gefallen bitten...";
					link.l1 = "Ich höre zu, "+GetAddress_FormToNPC(NPChar)+". Was willst du?";
					link.l1.go = "passenger";
					link.l2 = "Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+", aber ich habe es eilig.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ich bin ","Mein Name ist ","Du kannst mich nennen ")+GetFullName(npchar)+LinkRandPhrase(". Was willst du?",". Ich habe dich noch nie gesehen. Wer bist du?",". Wer sind Sie und was wollen Sie von mir?"),LinkRandPhrase("Grüße, "+GetAddress_Form(NPChar)+". Mein Name ist "+GetFullName(npchar)+". Und wie ist dein Name?","Hallo, "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(npchar)+". Kann ich Ihren Namen wissen?","Ja, "+GetAddress_Form(NPChar)+". Was willst du? Übrigens ist mein Name "+GetFullName(npchar)+". Und wie ist dein Name?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Verdammt noch mal! ","Verdammt! ","Verdammt seist du! ")+"Ja, ich bin der Kapitän "+GetFullName(Pchar)+LinkRandPhrase(", hast du noch nie gehört "+NPCharSexPhrase(NPChar,", Schurke?","?")," und "+GetSexPhrase("der berühmteste Pirat","das berühmteste Mädchen-Pirat")+" auf dem Meer!"," und verdammt sei ich, wenn ich mich irre!"),LinkRandPhrase("Ich bin "+GetFullName(Pchar)+", Kapitän.","Mein Name ist "+GetFullName(Pchar)+".","Sie können mich Kapitän nennen "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Die ganze Stadt ist in Aufruhr - Don Fernando de Alamida, der königliche Inspektor, ist angekommen. Sie wissen, ich habe hier viel gesehen, aber das... Es ist nicht der Kummer, der die Menschen verändert, sondern wie sie damit umgehen. Sie sagen, er wurde ein anderer Mann nach dem Tod seines Vaters. Jetzt finden Sie keinen unbestechlicheren und... gnadenloseren Diener der Krone im gesamten Archipel.","Schau dir nur die 'Heilige Barmherzigkeit' an! Sie sagen, der König selbst habe sie nach speziellen Plänen bauen lassen. Und bemerke - nicht ein einziger Kratzer. Als ob die Jungfrau Maria selbst sie schützt. Obwohl ich Gerüchte gehört habe... vielleicht ist es überhaupt nicht die Jungfrau.","Wissen Sie, wie oft sie versucht haben, Don Fernando zu töten? Zwölf Angriffe auf offener See - und das allein im letzten Jahr! Nun, mit einer so treuen und ausgebildeten Crew und unter dem Schutz des Herrn - er wird auch den dreizehnten überleben!"),LinkRandPhrase("Haben Sie gehört? Don Fernando de Alamida ist in unserer Stadt angekommen, und sie sagen, er sei gerade irgendwo auf den Straßen. Würde ihn gerne mit meinen eigenen Augen sehen...","Ein komplizierter Mann, dieser Don Fernando. Manche sagen, er sei ein Retter, der das Mutterland von Dreck säubert. Andere flüstern, dass etwas in ihm zerbrochen ist nach dem Tod seines Vaters und wir alle bald weinen werden. Aber ich sage dir dies: Fürchte ihn nicht. Fürchte diejenigen, die ihn zu dem gemacht haben, was er ist.","Was für ein hübscher Mann, dieser Don Fernando! Aber wissen Sie, was seltsam ist? Es ist, als würde er niemanden bemerken. Alles Pflicht und Dienst. Ich habe gehört, es gab ein Mädchen... aber nach einem Treffen mit einem Priester hat er weltliche Freuden völlig abgelehnt. Als ob er ein Gelübde abgelegt hätte."),RandPhraseSimple(RandPhraseSimple("Verdammter Inspektor! Solange er hier ist, ist die Stadt wie tot. Kein Handel, kein Spaß. Selbst das Atmen, so scheint es, muss leiser sein. Und wissen Sie, was am erschreckendsten ist? Es ist in jedem Hafen dasselbe. Wie ein Uhrwerk. Seine Königliche Majestät könnte diese Folter für uns alle nicht absichtlich erfunden haben!","Don Fernando hat das Waisenhaus wieder besucht. Spendet großzügig, betet stundenlang. So ein würdiger Mann sollte den verfluchten Unterschlagern als Beispiel dienen!"),RandPhraseSimple("Ha! 'Heiliger' Fernando hat wieder alle Bordelle geschlossen. Macht nichts, er wird bald absegeln und sie werden wieder öffnen.","Der Inspektor... Inspektor ist angekommen, das ist es! Don Fernando de Almeyda oder wie heißt er, Alamida! So wichtig, dass der Gouverneur selbst um ihn herumschleicht. Man sagt, er schaut dir in die Augen und sieht sofort all deine Sünden. Furchteinflößend!")));
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
				link.l1 = PCharRepPhrase("Ich möchte nur etwas über dieses Loch fragen, das ihr 'die Stadt' nennt.","Ich möchte Sie etwas über diese Stadt fragen.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche einige Informationen.");
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
						link.l3 = RandPhraseSimple("Ich möchte über finanzielle Angelegenheiten sprechen.","Über Finanzen...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Hör zu, ich hoffe, dass du mir helfen kannst. Ich möchte ein kaufen "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass dieses Ding in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf den Straßen verkauft. Wissen Sie etwas?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Kennen Sie ","Bist du dir bewusst ","Hast du gehört ")+" dass die örtliche Kirche kürzlich ausgeraubt wurde?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ach, du bist es "+GetFullName(Pchar)+" "+GetSexPhrase("- Alter Freund!","- hübsche Dame!")+"","Ich freue mich, dich zu sehen, "+GetSexPhrase("alter Freund!","hübsches Ding!")+" "+Pchar.name,"Ach, das ist der "+GetSexPhrase("der Kapitän selbst","Kapitänin selbst")+" "+GetFullName(Pchar))+RandPhraseSimple(". Ich dachte, du wärst tot!",". Und vielleicht "+GetSexPhrase("wie immer betrunken.","ein bisschen betrunken."))+LinkRandPhrase(" Mach weiter, was brauchst du?","Was ist diesmal?"," Störst du mich schon wieder?"),LinkRandPhrase(TimeGreeting()+", Kapitän ","Guten Tag für dich, "+GetAddress_Form(NPChar)+" ","Grüße, Kapitän ")+GetFullName(Pchar)+LinkRandPhrase(". Wie kann ich helfen zu "+GetSexPhrase("so ein würdiger Mann","so ein würdiges Mädchen")+", wie du?",". Warum bist du hier?",". Was möchtest du diesmal wissen?")),PCharRepPhrase(LinkRandPhrase("Hallo, Kapitän ","Grüße, ah, du bist es "+GetAddress_Form(NPChar)+" ","Ach, Kapitän ")+GetFullName(Pchar)+LinkRandPhrase(", Ich dachte, wir würden uns nie wieder treffen, und",", Ich würde nicht sagen, dass ich froh bin, dich zu sehen, aber",", Ich sehe, dass du noch am Leben bist, was für eine Schande und")+LinkRandPhrase(" was willst du?"," warum bist du hier?"," wie kann ich Ihnen helfen?"),LinkRandPhrase(TimeGreeting()+", Kapitän "+GetFullName(Pchar)+". Wie kann ich Ihnen helfen?","Oh, das ist der Kapitän "+GetFullName(Pchar)+"! Wie kann ich Ihnen helfen?","Grüße, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Wollen Sie etwas?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Deine Ohren täuschen dich. Ich muss gehen.","Nein, es ist nichts, ich war auf dem Weg zur Taverne."),RandPhraseSimple("Gut, wie auch immer. Viel Glück!","Nur durch die Stadt schlendern. Lebewohl."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Fragen?";
			link.l1 = "Bedeutet der Name auf diesen Papieren etwas für Sie?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Ich gebe einen Dreck auf irgendein zufälliges Papier und außerdem kann ich nicht lesen. Geh zum Wucherer, sie sagen, er weiß, wie man Scheiße mit Buchstaben anstellt, ha!","Ich weiß nicht, wovon Sie sprechen, fragen Sie jemand anderen, Kapitän"+GetFullName(Pchar)+".","Ich weiß nicht, wie ich Ihnen helfen kann, Kapitän "+GetFullName(Pchar)+". Versuche mit dem Wucherer zu sprechen, er könnte es wissen.");
			link.l1 = "Danke.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Lügst du nicht, Kapitän "+GetFullName(Pchar)+"?","Na und "+PChar.name+"?","Ich werde mich an dich erinnern, "+GetFullName(Pchar)+".")+" Jetzt sag mir, was willst du?",LinkRandPhrase("Schön Sie zu treffen, Kapitän "+PChar.name,"Freut mich, unsere Begegnung, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Es ist eine Freude, Kapitän "+PChar.name)+". Aber ich bezweifle, dass Sie nur meinen Namen wissen wollten, oder?");
            link.l1 = PCharRepPhrase("Ich möchte nur etwas über dieses Drecksloch fragen, das ihr 'Stadt' nennt.","Ich möchte Sie etwas über diese Stadt fragen.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Ich habe eine Frage an Sie.","Ich brauche einige Informationen.");
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
					link.l3 = RandPhraseSimple("Ich möchte finanzielle Angelegenheiten besprechen.","Über Finanzen...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Hör zu, ich hoffe, du kannst mir helfen. Ich möchte ein "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass dieses Ding in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf den Straßen verkauft. Wissen Sie etwas darüber?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Kennen Sie ","Sind Sie sich bewusst ","Hast du gehört ")+" dass die örtliche Kirche vor kurzem ausgeraubt wurde?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Deine Ohren täuschen dich. Ich muss gehen.","Nein, es ist nichts, ich war auf dem Weg zur Taverne."),RandPhraseSimple("Nun, es ist nichts, Viel Glück!","Nur ein Spaziergang durch die Stadt. Auf Wiedersehen."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, und ich freue mich, dich zu sehen, wie ich mich über einen Schnaps freue, frag, was du willst.","Wie reden, Kapitän? Ich auch... Besonders mit einem Becher Rum.","Ja, "+PChar.name+"?"),LinkRandPhrase("Was willst du noch?","Ich nehme es, Kapitän "+PChar.name+", dass Sie gerne plaudern?")),PCharRepPhrase(LinkRandPhrase("Was willst du noch, "+GetAddress_Form(NPChar)+"?","Ich höre zu, Kapitän.","Ich muss gehen, also frag mich schnell, Kapitän."),LinkRandPhrase("Ich freue mich immer über angenehme Gesellschaft, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Sprich.","Ja, "+GetAddress_Form(NPChar)+"?","Wie das Reden, Kapitän? Ich auch... ")));
			link.l1 = LinkRandPhrase("Welche Gerüchte gibt es in dieser Stadt?","Gibt es Neuigkeiten in diesem Land?","Wie läuft das Leben an Land?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Können Sie mir den Weg zeigen?","Ich kann den Weg zu einem Ort nicht finden...","Hilf mir, einen Platz zu bekommen...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Ich möchte wissen, was die Leute über eine Person sagen.","Weißt du, was die Leute über eine Person sagen?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Ich möchte mehr über die Einheimischen erfahren.","Können Sie mir etwas über die Einheimischen erzählen?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Deine Ohren täuschen dich. Ich muss gehen.","Nein, es ist nichts, ich bin auf dem Weg zur Taverne."),RandPhraseSimple("Nun, es ist nichts. Viel Glück!","Nur ein Spaziergang durch die Stadt. Auf Wiedersehen."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Wen interessiert dich?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Möchten Sie mehr über den Gouverneur erfahren.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Möchten Sie mehr über den Besitzer der örtlichen Taverne erfahren.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Möchten Sie mehr über den Meister der örtlichen Werft erfahren.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Möchten Sie mehr über den Besitzer des örtlichen Ladens erfahren.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Es ist nichts. Vergiss es.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Danke.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Noch nie davon gehört... Ich lebe schon lange hier und habe noch nie so etwas gesehen.";
			link.l1 = "Nun, das ist ein Schiffbauwerkzeug, "+pchar.GenQuest.Device.Shipyarder.Describe+". Hat jemand so etwas in der Stadt verkauft? Oder vielleicht herumgetragen und Sie haben es bemerkt?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Ja, ich habe vor einigen Stunden einen Mann mit diesem Ding gesehen. Er lief durch die Straßen. Ein interessantes Werkzeug war es.";
				link.l1 = "Wie sah er aus und wohin ging er? Ich brauche wirklich so etwas.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nein, ich habe so etwas nicht gesehen.";
				link.l1 = "Ich verstehe. Ich werde dann weiter fragen.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nein, ich weiß nichts darüber.","Nein, ich sollte gehen.","Ich weiß gar nichts.");
					link.l1 = LinkRandPhrase("Gut, danke.","Ich verstehe, danke.","In Ordnung, entschuldigen Sie mich.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Ich weiß nichts darüber, aber Sie könnten versuchen, die Stammgäste in der Taverne zu fragen, die werden Ihnen definitiv mehr erzählen.","Ich kann Ihnen nichts sagen, fragen Sie jemanden in der Taverne.");
				link.l1 = "Danke dafür.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "Kapitän, ich muss in die Kolonie namens "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", so schnell wie möglich, es ist an "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", in "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Ihr Schiff sieht solide aus im Vergleich zu der Mehrheit dieser kleinen Boote, die hier segeln. Ich kann Ihnen zahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". Was sagst du dazu?";
			}
			else
			{
				dialog.text = "Kapitän, ich muss zur Kolonie "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", es ist auf einem "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", in einem "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Ich weiß, das klingt äußerst riskant, aber vielleicht "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+" wäre ein netter Schub für dich?";
			}
			link.l1 = "Hm. Ich gehe auch in diese Richtung, also bin ich bereit, dich unter diesen Bedingungen an Bord zu nehmen.";
			link.l1.go = "passenger_1";
			link.l2 = "Es tut mir leid,  "+GetAddress_FormToNPC(NPChar)+", aber ich segle in die andere Richtung. Ich kann dir nicht helfen.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Schade. Nun, ich werde auf ein anderes Schiff warten. Lebewohl.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Großartig, denn ich bin es leid zu warten. Du bekommst deine Bezahlung, wenn wir dort sein werden.";
			link.l1 = "Geh zu meinem Schiff, "+GetAddress_FormToNPC(NPChar)+". Wir gehen bald.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Hier sind wir, hervorragend! Diese Reise auf Ihrem Schiff war durchaus zufriedenstellend. Meinen Dank. Nehmen Sie Ihr Geld, Herr.";
			link.l1 = "Viel Glück, "+GetAddress_FormToNPC(NPChar)+"! Lebewohl.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, als Bürger dieser Stadt bitte ich dich, deine Klinge zu verbergen.","Hört mal, als Bürger dieser Stadt bitte ich Euch, Euer Schwert zu verbergen.");
				link.l1 = LinkRandPhrase("Gut.","Wie du wünschst.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, wenn du mit einer Waffe rennst. Ich kann nervös werden...","Es gefällt mir nicht, wenn irgendein Fremder vor mir mit einem nackten Schwert herumläuft...");
				link.l1 = RandPhraseSimple("Ich habe es.","Mach dir keine Sorgen.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}
