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
				    dialog.text = RandPhraseSimple("Man sagt, dass du diese Stadt besitzt, "+GetSexPhrase("Herr","Fräulein")+".","So ein nettes Treffen! So ein nettes Treffen! Der Gouverneur selbst spricht mit mir!");
					link.l1 = RandPhraseSimple("Ich habe es mir anders überlegt. Viel Glück!","Nur durch die Stadt schlendern. Auf Wiedersehen.");
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
				    dialog.text = RandPhraseSimple("Was willst du? Geh weiter.","Hör auf, mir im Weg zu stehen, verschwinde.");
					link.l1 = RandPhraseSimple("Was machst du?","Beruhige dich. Oder ich werde es selbst tun.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ich möchte dich etwas fragen.","Nur eine Minute Ihrer Aufmerksamkeit, bitte. Eine Frage.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Ich möchte finanzielle Angelegenheiten besprechen.","Über die Finanzen...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Ich bin","Mein Name ist ","Du kannst mich nennen ")+GetFullName(npchar)+LinkRandPhrase(". Was willst du?",". Ich habe dich noch nie gesehen "+", wer bist du?",". Wer bist du und was willst du von mir?"),LinkRandPhrase("Grüße, "+GetAddress_Form(NPChar)+". Mein Name ist "+GetFullName(npchar)+". Und wie ist dein Name?","Hallo "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(npchar)+". Kann ich Ihren Namen erfahren?","Ja, "+GetAddress_Form(NPChar)+". Was willst du? Und übrigens ist mein Name "+GetFullName(npchar)+". Und wie heißt du?"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("Verdammt noch mal! ","Verdammt! ","Verdammt seist du! ")+"Ja, ich bin der Kapitän "+GetFullName(Pchar)+LinkRandPhrase(", hast du noch nie von mir gehört, Bastard?"," und "+GetSexPhrase("der berühmteste Pirat","das berühmteste Mädchen-Pirat")+" auf See!"," und verdamme mich, wenn ich falsch liege!"),LinkRandPhrase("Ich bin "+GetFullName(Pchar)+", Kapitän.","Mein Name ist "+GetFullName(Pchar)+".","Sie können mich Kapitän nennen "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Die ganze Stadt ist angespannt - Don Fernando de Alamida, der königliche Inspektor, ist angekommen. Sie wissen, ich habe hier viel gesehen, aber das... Es ist nicht die Trauer, die die Menschen verändert, sondern wie sie damit umgehen. Sie sagen, er sei nach dem Tod seines Vaters ein anderer Mensch geworden. Jetzt finden Sie keinen unbestechlicheren und... gnadenloseren Diener der Krone im gesamten Archipel.","Schau dir nur die 'Heilige Barmherzigkeit' an! Sie sagen, der König selbst habe sie nach speziellen Entwürfen bauen lassen. Und bemerke - nicht ein einziger Kratzer. Als ob die Jungfrau Maria selbst sie schützt. Obwohl ich Gerüchte gehört habe... vielleicht ist es gar nicht die Jungfrau.","Wissen Sie, wie oft sie versucht haben, Don Fernando zu töten? Zwölf Angriffe auf hoher See - und das allein im letzten Jahr! Nun, mit einer so treuen und ausgebildeten Mannschaft und unter dem Schutz des Herrn - er wird auch den dreizehnten überleben!"),LinkRandPhrase("Haben Sie gehört? Don Fernando de Alamida ist in unserer Stadt angekommen, und man sagt, er sei gerade jetzt irgendwo auf den Straßen. Würde ihn gerne mit meinen eigenen Augen sehen...","Ein komplizierter Mann, dieser Don Fernando. Einige sagen, er sei ein Retter, der das Mutterland von Dreck reinigt. Andere flüstern, dass etwas in ihm nach dem Tod seines Vaters gebrochen ist und wir bald alle weinen werden. Aber ich sage dir dies: Fürchte ihn nicht. Fürchte diejenigen, die ihn zu dem gemacht haben, was er ist.","Was für ein hübscher Mann, dieser Don Fernando! Aber wissen Sie, was seltsam ist? Es ist, als ob er niemanden bemerken würde. Alles Pflicht und Dienst. Ich hörte, es gab ein Mädchen... aber nach einem Treffen mit einem Priester lehnte er weltliche Freuden völlig ab. Als hätte er ein Gelübde abgelegt."),RandPhraseSimple(RandPhraseSimple("Verdammter Inspektor! Solange er hier ist, ist die Stadt wie tot. Kein Handel, kein Spaß. Selbst das Atmen, so scheint es, muss leiser sein. Und wissen Sie, was am beängstigendsten ist? Es ist in jedem Hafen gleich. Wie ein Uhrwerk. Seine Königliche Majestät hätte diese Folter für uns alle nicht absichtlich erfinden können!","Don Fernando hat das Waisenhaus wieder besucht. Spendet großzügig, betet stundenlang. So ein würdiger Mann sollte den verfluchten Unterschlagern als Beispiel dienen!"),RandPhraseSimple("Ha! 'Heiliger' Fernando hat wieder alle Bordelle geschlossen. Nun, macht nichts, er wird bald absegeln und sie werden sofort wieder öffnen.","Der Insp... Inspektor ist angekommen, das ist es! Don Fernando de Almeyda, oder, wie heißt er, Alamida! So wichtig, dass der Gouverneur selbst um ihn herumschleicht. Sie sagen, er schaut dir in die Augen und sieht sofort all deine Sünden. Schrecklich!")));
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
				link.l1 = "Ich wollte nur über diese Stadt sprechen.";
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
						link.l3 = RandPhraseSimple("Ich möchte finanzielle Angelegenheiten besprechen.","Über Finanzen...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Hör zu, ich hoffe, dass du mir helfen kannst. Ich möchte ein "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass dieses Ding in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf dem Straßenmarkt verkauft. Wissen Sie etwas darüber?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Kennst du ","Bist du dir bewusst ","Hast du gehört ")+"dass die örtliche Kirche kürzlich beraubt wurde?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ach, du bist es "+GetFullName(Pchar)+" "+GetSexPhrase("- alter Freund!","- hübsches Ding!")+"","Ich freue mich, dich zu sehen, "+GetSexPhrase("alter Freund!","hübsche Dame!")+" "+Pchar.name,"Oh, das ist der "+GetSexPhrase("der Kapitän selbst","Kapitänin selbst")+" "+GetFullName(Pchar))+RandPhraseSimple(". Ich dachte, du bist tot!",". Und vielleicht "+GetSexPhrase("wie immer betrunken.","ein bisschen betrunken."))+LinkRandPhrase("Mach weiter, was brauchst du?"," Was ist diesmal?"," Störst du mich schon wieder?"),LinkRandPhrase(TimeGreeting()+", Kapitän ","Guten Tag, "+GetAddress_Form(NPChar)+" ","Grüße, Kapitän ")+GetFullName(Pchar)+LinkRandPhrase(". Wie kann ich zu "+GetSexPhrase("so ein würdiger Mann","so ein würdiges Mädchen")+", wie du?",". Warum bist du hier?",". Was möchten Sie diesmal wissen?")),PCharRepPhrase(LinkRandPhrase("Hallo, Kapitän ","Grüße, ah, du bist es "+GetAddress_Form(NPChar)+" ","Ach, Kapitän ")+GetFullName(Pchar)+LinkRandPhrase(", Ich dachte, wir würden uns nie wieder treffen, und",", Ich würde nicht sagen, dass ich froh bin, dich zu sehen, aber",", Ich sehe, dass du noch am Leben bist, was für eine Schande und")+LinkRandPhrase(" was willst du?"," warum bist du hier?"," wie kann ich Ihnen helfen?"),LinkRandPhrase(TimeGreeting()+", Kapitän "+GetFullName(Pchar)+". Wie kann ich Ihnen helfen?","Oh, das ist der Kapitän "+GetFullName(Pchar)+"! Wie kann ich Ihnen helfen?","Grüße, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Wünschen Sie etwas?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Deine Ohren täuschen dich. Ich muss gehen.","Nein, das ist nichts, ich war auf dem Weg zur Taverne."),RandPhraseSimple("Gut, was auch immer. Viel Glück!","Nur in der Stadt herumwandern. Lebewohl."));
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
			dialog.text = LinkRandPhrase("Ich gebe einen Dreck auf unbekanntes Papier und ich kann nicht lesen. Geh zum Wucherer, sie sagen, dass er diese Teufelsbuchstaben lesen kann.","Ich weiß nicht, wovon Sie sprechen, fragen Sie andere Bürger der Stadt, Kapitän"+GetFullName(Pchar)+".","Ich weiß nicht einmal, wie ich Ihnen helfen kann, Kapitän "+GetFullName(Pchar)+". Versuche mit dem Wucherer zu sprechen, er könnte es wissen.");
			link.l1 = "Ich werde Ihrem Rat mit großem Vergnügen folgen!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Lügst du nicht, Kapitän "+GetFullName(Pchar)+"?","Na und"+PChar.name+"?","Ich werde mich an dich erinnern, "+GetFullName(Pchar)+".")+" Jetzt sag mir, was willst du?",LinkRandPhrase("Freut mich, Sie kennenzulernen, Kapitän "+PChar.name,"Freut mich, unsere Begegnung,"+GetAddress_Form(NPChar)+" "+PChar.lastname,"Es ist ein Vergnügen, Kapitän "+PChar.name)+". Aber ich bezweifle, dass Sie nur meinen Namen wissen wollten, oder?");
            link.l1 = PCharRepPhrase("Ich möchte nur etwas über dieses Loch fragen, das ihr 'die Stadt' nennt.","Ich möchte Sie etwas über diese Stadt fragen.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche einige Informationen.");
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
					link.l3 = RandPhraseSimple("Ich möchte finanzielle Angelegenheiten besprechen.","Über die Finanzen...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Hör zu, ich hoffe, du kannst mir helfen. Ich möchte kaufen ein "+pchar.GenQuest.Device.Shipyarder.Type+" und mir wurde gesagt, dass dieses Ding in eurer Stadt verkauft wurde. Nun, jemand hat es auf den Straßen verkauft. Wissen Sie etwas darüber?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("Kennst du ","Bist du dir bewusst ","Hast du gehört ")+" dass die örtliche Kirche kürzlich ausgeraubt wurde?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Deine Ohren täuschen dich. Ich muss gehen.","Nein, es ist nichts, ich war auf dem Weg zur Taverne."),RandPhraseSimple("Nun, es ist nichts, Viel Glück!","Nur durch die Stadt spazieren. Auf Wiedersehen."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, und ich freue mich, dich zu sehen, wie ich mich über einen Schnaps freue, frag was du willst.","Wie reden, Kapitän? Ich auch... Besonders mit einem Becher Rum.","Ja, "+PChar.name+"?"),RandPhraseSimple("Was willst du noch?","Ich nehme an, Kapitän "+PChar.name+", dass du gerne plauderst?")),PCharRepPhrase(LinkRandPhrase("Was willst du noch "+GetAddress_Form(NPChar)+"?","Ich höre zu, Kapitän.","Ich muss gehen, also fragen Sie mich schnell, Kapitän."),LinkRandPhrase("Ich freue mich immer über angenehme Gesellschaft, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Sprich.","Ja, "+GetAddress_Form(NPChar)+"?","Wie reden, Kapitän? Ich auch... ")));
			link.l1 = LinkRandPhrase("Welche Gerüchte gibt es in dieser Stadt?","Gibt es Neuigkeiten in diesem Land?","Wie läuft das Landleben?");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("Können Sie mir den Weg zeigen?","Ich kann den Weg zu einem Ort nicht finden...","Hilf mir, an einen Ort zu gelangen...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Ich möchte wissen, was die Leute über eine Person sagen.","Wissen Sie, was die Leute über eine Person sagen?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Ich möchte mehr über die Einheimischen wissen.","Können Sie mir etwas über die Einheimischen erzählen?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Deine Ohren täuschen dich. Ich muss gehen.","Nein, es ist nichts, ich war auf dem Weg zur Taverne."),RandPhraseSimple("Nun, es ist nichts. Viel Glück!","Einfach nur in der Stadt herumlaufen. Auf Wiedersehen."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Wen interessieren Sie?";
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
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Noch nie davon gehört ... Ich lebe schon lange hier und habe noch nie so etwas gesehen.";
			link.l1 = "Nun, das ist ein Schiffbauwerkzeug, "+pchar.GenQuest.Device.Shipyarder.Describe+". Hat vielleicht jemand so etwas in der Stadt verkauft? Oder vielleicht herumgetragen und Sie haben es bemerkt?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Ja, ich habe vor einigen Stunden einen Mann mit diesem Ding gesehen. Er ging durch die Straßen. Ein interessantes Werkzeug war es.";
				link.l1 = "Wie sah er aus und wohin ging er? Ich brauche wirklich so etwas.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nein, ich habe nichts dergleichen gesehen.";
				link.l1 = "Ich verstehe. Ich werde dann weiter fragen.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nein, ich weiß nichts darüber.","Nein, ich sollte gehen.","Ich weiß nichts.");
					link.l1 = LinkRandPhrase("Gut, danke.","Ich verstehe, danke.","Also gut, entschuldigen Sie mich.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Ich weiß nichts darüber, aber Sie könnten versuchen, einige der Stammgäste in der Taverne zu fragen, sie werden Ihnen definitiv mehr erzählen.","Ich kann Ihnen nichts sagen, fragen Sie jemanden in der Taverne.");
				link.l1 = "Danke dafür.";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, als Bürger dieser Stadt bitte ich dich, deine Klinge zu scheiden.","Hör zu, als Bürger dieser Stadt bitte ich dich, deine Klinge zu scheiden.");
				link.l1 = LinkRandPhrase("Gut.","Wie du wünschst.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn irgendein unbekannter Mann vor mir mit gezogenem Schwert geht. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Ich habe es.","Mach dir keine Sorgen.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
