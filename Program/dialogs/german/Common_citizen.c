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
            /*if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY && int(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Ein Spion? Wachen!","Alarm! Da ist ein Eindringling!");
				link.l1 = "Halt die Klappe. Ich gehe.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (int(NPChar.nation) == PIRATE)
			{
				if (int(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Man sagt, dass du derjenige bist, der diese Stadt regiert, "+GetSexPhrase("Herr","Fräulein")+".","Welch angenehmes Treffen, der Stadtoberhaupt hat sich mit einer Frage an mich gewandt.");
					link.l1 = RandPhraseSimple("Ich habe meine Meinung geändert.","Ich erkunde einfach diese Stadt. Auf Wiedersehen.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[int(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Ich möchte Geschäfte besprechen.","Bezüglich der Finanzen...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("Was willst du? Mach dich fort.","Steh nicht im Weg, verschwinde!");
					link.l1 = RandPhraseSimple("He, hör auf zu bellen, oder?","Beruhige dich, sonst könntest du es bereuen!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Einen Moment Ihrer Aufmerksamkeit, bitte. Ich habe eine Frage.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[int(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Ich möchte Geschäfte besprechen.","Bezüglich der Finanzen...");
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
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Mein Name ist ","Mein Name ist ","Sie können mich nennen ")+GetFullName(npchar)+LinkRandPhrase(". Was brauchen Sie?",". Ich habe nicht "+NPCharSexPhrase(NPChar,"hier schon mal gesehen","habe dich dort vorher gesehen")+", wer bist du?",". Wer bist du und was brauchst du von mir?"),LinkRandPhrase("Grüße, "+GetAddress_Form(NPChar)+". Mein Name ist "+GetFullName(npchar)+". Was ist deiner?","Hallo, "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(npchar)+". Darf ich Ihren Namen wissen?","Ja, "+GetAddress_Form(NPChar)+". Was willst du? Übrigens, mein Name ist "+GetFullName(npchar)+". Und wer bist du?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Beim Donner! ","Hölle's Glocken! ","Schlechtes Los für dich! ")+"Ja, ich bin Kapitän "+GetFullName(Pchar)+LinkRandPhrase(", hast du wirklich noch nie von mir gehört"+NPCharSexPhrase(NPChar,", Schurke?","?")," und "+GetSexPhrase("der berüchtigtste Pirat","die berüchtigtste Piratenlady")+" in diesen Gewässern! "," und möge ich in der Hölle brennen, wenn das nicht wahr ist!"),LinkRandPhrase("Ich bin der Kapitän"+GetFullName(Pchar)+".","Mein Name ist "+GetFullName(Pchar)+".","Sie können mich Kapitän nennen "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Kapitän, könnten Sie mir bitte helfen?";
					link.l1 = LinkRandPhrase("Entschuldigung, nein. Ich habe wenig Zeit zu verschwenden.","Entschuldigung, ich kann nicht. Zu beschäftigt.","Nein, ich kann nicht. Ich habe dringende Angelegenheiten, die meine Aufmerksamkeit erfordern.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Sicher kann ich. Was ist das Problem?","Ja, ich werde dir helfen. Erzähl mir mehr über dieses Geschäft von dir.","Erzähl mir mehr über dieses Geschäft von dir...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Ja, Kapitän, ich höre zu.";
					link.l1 = NPChar.name+", ich habe Ihren Ehering gefunden.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Ich möchte mehr über diese Stadt erfahren.","Erzähl mir von dieser Stadt.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
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
	                if (Characters[int(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Ich möchte Geschäfte besprechen.","Was die Finanzen angeht...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Halt! Sag mir, wer du bist - sofort! Ich suche einen feindlichen Spion auf Anfrage des Gouverneurs von "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Halt! Ich handle im Interesse der Stadt "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" im Auftrag des Gouverneurs. Ich durchsuche die Stadt nach einem feindlichen Agenten.","Halt, Freund! Lokaler Gouverneur "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" will einen Spion in der Stadt finden."),LinkRandPhrase("Halt, Frau! Sag mir, wer du bist - sofort! Ich suche auf Antrag des Gouverneurs einen feindlichen Spion "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Frau, ich muss Sie festhalten! Ich handle im Interesse der Stadt "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" im Auftrag des Gouverneurs. Ich durchsuche die Stadt nach einem feindlichen Agenten","Halt still, Schönheit! Ein lokaler Gouverneur "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" will einen Spion in der Stadt finden..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Vielleicht können Sie mir einen Rat geben. Ich möchte kaufen "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass es in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf den Straßen verkauft. Wissen Sie etwas darüber?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Bist du dir bewusst","Wusstest du schon","Hast du gehört")+" dass eine örtliche Kirche kürzlich überfallen wurde?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, du bist es, "+GetFullName(Pchar)+" "+GetSexPhrase(", alter Schurke","- scharfe Dame")+"","Schön dich wieder zu sehen, "+GetSexPhrase("alter Kamerad","Schönheit")+" "+Pchar.name,"Oh, es ist der gute alte "+GetSexPhrase("Kapitän","Dame")+" "+GetFullName(Pchar))+LinkRandPhrase(". Ich dachte, du wärst tot!",". Und sicherlich, "+GetSexPhrase("wie üblich betrunken.","schon unter dem Wetter.")+"",". Und wie ich sehe, immer noch auf freiem Fuß!")+LinkRandPhrase("Also, sprich deinen Verstand aus - was brauchst du?"," Was brauchen Sie diesmal?"," Belästigst du mich wieder wegen nichts?"),LinkRandPhrase(TimeGreeting()+", Kapitän ","Hallo, "+GetAddress_Form(NPChar)+" ","Ich grüße Sie, Kapitän ")+GetFullName(Pchar)+LinkRandPhrase(". Was könnte "+GetSexPhrase("so ein galanter Gentleman","so eine schmucke Dame")+", wie? Könnten Sie möglicherweise etwas von mir brauchen?",". Was willst du hier?",". Was möchtest du diesmal wissen?")),PCharRepPhrase(LinkRandPhrase("Hallo, Kapitän ","Hallo. Oh, es bist du "+GetAddress_Form(NPChar)+" ","Oh, Kapitän ")+GetFullName(Pchar)+LinkRandPhrase(", ich dachte"+NPCharSexPhrase(NPChar," "," ")+"wir würden uns nie wieder treffen,",", kann nicht sagen, dass ich froh bin"+NPCharSexPhrase(NPChar," "," ")+"Sie zu sehen, aber",", Ich sehe, du lebst noch. Bedauerlich. Also,")+LinkRandPhrase(" was brauchst du?"," was hast du vor?"," was kann ich "+NPCharSexPhrase(NPChar,"Kann ich Ihnen helfen?","Kann ich Ihnen helfen?")),LinkRandPhrase(TimeGreeting()+", Kapitän "+GetFullName(Pchar)+". Was kann ich für dich tun?","Oh, wenn es nicht ist"+GetSexPhrase("","")+" Kapitän "+GetFullName(Pchar)+"! Was möchten Sie diesmal wissen?","Hallo, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Wollten Sie etwas?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Nein, du hörst Dinge. Ich gehe jetzt.","Nein, nichts - ich war gerade unterwegs"+GetSexPhrase("","")+" zur Taverne."),RandPhraseSimple("Nein, nichts. Viel Glück für Sie!","Nur mal schauen. Auf Wiedersehen."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Welche Fragen?";
			link.l1 = "Erinnert der Name in diesen Papieren an etwas?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Ich habe nichts für fremde Papiere übrig. Außerdem kann ich nicht lesen. Geh zum Wucherer, dieser Teufel kann sicherlich lesen und schreiben.","Ich habe keine Ahnung, wovon Sie sprechen. Fragen Sie die Stadtbewohner, Kapitän "+GetFullName(Pchar)+".","Ich habe wirklich keine Ahnung, wie ich Ihnen helfen kann, Kapitän "+GetFullName(Pchar)+". Versuche es beim Wucherer zu fragen - vielleicht weiß er es.");
			link.l1 = "Ich werde deinen Rat gerne befolgen!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Aber Sie lügen doch, Kapitän "+GetFullName(Pchar)+"?","Und was dann, "+PChar.name+"?","Ich werde dich in Erinnerung behalten, "+GetFullName(Pchar)+".")+"Und nun, was brauchst du?",LinkRandPhrase("Es ist mir eine Freude, Sie zu treffen, Kapitän "+PChar.name,"Froh"+NPCharSexPhrase(NPChar," "," ")+", dich zu treffen, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Schön Sie zu treffen, Kapitän "+PChar.name)+". Aber ich nehme an, du bist hierher gekommen für mehr als nur meinen Namen zu erfahren?");

            link.l1 = PCharRepPhrase("Ich wollte"+GetSexPhrase("","")+" etwas über dieses Loch zu wissen, das du Stadt nennst!","Ich wollte"+GetSexPhrase("","")+" etwas über diese Stadt zu wissen.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Ich habe eine Frage an dich.","Ich brauche Informationen.");
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
                if (Characters[int(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Ich möchte Geschäfte besprechen.","Bezüglich der Finanzen...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Vielleicht kannst du mir einen Rat geben. Ich möchte kaufen "+pchar.GenQuest.Device.Shipyarder.Type+", und mir wurde gesagt, dass es in Ihrer Stadt verkauft wurde. Nun, jemand hat es auf den Straßen verkauft. Wissen Sie etwas darüber?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Halt! Sag mir sofort, wer du bist! Ich suche im Auftrag des Gouverneurs nach einem feindlichen Spion "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Halt! Ich handle im Interesse von"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" im Auftrag des Gouverneurs. Ich durchsuche die Stadt nach einem feindlichen Agenten.","Halt, Freund! Lokaler Gouverneur "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" will einen Spion in der Stadt finden."),LinkRandPhrase("Halt ein, Dame! Sag mir wer du bist - sofort! Ich suche im Auftrag des Gouverneurs einen feindlichen Spion."+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Frau, ich muss Sie festhalten! Ich handle im Interesse der Stadt "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" im Auftrag des Gouverneurs. Ich durchsuche die Stadt nach einem feindlichen Agenten.","Halt, schöne Frau! Lokaler Gouverneur "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" will einen Spion in der Stadt ausfindig machen..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Bist du dir bewusst","Hast du gehört","Hast du gehört")+" dass eine örtliche Kirche kürzlich überfallen wurde?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Nein, du hörst Dinge. Ich gehe jetzt.","Nein, nichts - Ich war gerade auf dem Weg zur Taverne."),RandPhraseSimple("Nein, nichts. Viel Glück für dich!","Nur mal schauen. Auf Wiedersehen."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh ja, ich bin fast so froh"+NPCharSexPhrase(NPChar," "," ")+", dich als Becher Schnaps zu sehen. Frag was du willst.","Redest du gerne, Kapitän? Nun, ich auch... Besonders bei einem Becher Rum.","Ja, "+PChar.name+"?"),LinkRandPhrase("Was brauchen Sie?","Ich verstehe, Kapitän "+PChar.name+". Du bist"+GetSexPhrase("","")+" ziemlich ein Schwätzer. ","Du hast mich ausgepumpt"+GetSexPhrase("","")+" mit deinen Fragen, Kapitän. Hilf mir lieber mit dem Rum.")),PCharRepPhrase(LinkRandPhrase("Was wollen Sie wissen "+GetAddress_Form(NPChar)+"?","Ich höre Ihnen zu, Kapitän.","Ich muss gehen, also bitte beeilen Sie sich, Kapitän."),LinkRandPhrase("Immer froh"+NPCharSexPhrase(NPChar," "," ")+"  gute Gesellschaft zu haben, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Sag, was du denkst.","Ja, "+GetAddress_Form(NPChar)+"?","Sie plaudern gerne, Kapitän? Nun, ich auch...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("Welches Gerede ist in der örtlichen Taverne beliebt?","Was geht in diesen Landen vor sich?","Was gibt's Neues an Land hier?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Können Sie mir den Weg dorthin zeigen?","Ich kann den Weg zu einem bestimmten Ort nicht finden...","Könnten Sie den Weg zeigen...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Ich möchte wissen, was die Leute über eine bestimmte Person sagen.","Kennst du nicht, was die Leute über eine bestimmte Person sagen?","Ich möchte etwas über die Einheimischen erfahren.");
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
				link.l3 = "Erzählen Sie mir mehr über Ihre Kolonie.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("Ich habe wichtige Geschäfte!","Ich habe Geschäfte mit dir.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("Nein, du hörst Dinge. Ich gehe jetzt.","Nein, nichts - Ich war gerade auf dem Weg zur Taverne."),RandPhraseSimple("Nein, nichts. Viel Glück für dich!","Nur mal schauen. Auf Wiedersehen."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Über wen möchtest du etwas wissen?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Über den Gouverneur.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Über den Besitzer der örtlichen Taverne.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Über den Hafenmeister.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Über den Besitzer des örtlichen Ladens.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Macht nichts, vergiss es.";
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
		
		case "colony":
			dialog.text = LinkRandPhrase("Ehrlich gesagt, ich weiß nicht viel darüber, aber ich kann Ihnen trotzdem ein oder zwei Dinge erzählen.","Und was interessiert Sie an unserer Kolonie?","Sicher. Was möchten Sie wissen?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Welche Art von Stadt ist das?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "Was wissen Sie über das Fort, das die Stadt verteidigt?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Lassen wir das Thema wechseln.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Scherzt du? Oder machst du Witze? Sieh dir die rechte Ecke deines Bildschirms an.";
			link.l1 = "Ja, mein Fehler.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Ich weiß nichts darüber.";
			link.l1 = "Schade.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Noch nie davon gehört... Was ist das eigentlich? Ich habe in meiner ganzen Zeit noch nie von so etwas gehört"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Nun, es ist ein Schiffsbauerwerkzeug, "+pchar.GenQuest.Device.Shipyarder.Describe+". Hat jemand so etwas in der Stadt verkauft? Vielleicht. Du hast bemerkt, dass jemand so etwas bei sich hatte?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (int(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && int(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Ja, ich glaube, ich habe eine Person mit einem ähnlich aussehenden Ding gesehen. Er lief dort vor einigen Stunden damit herum. Ein interessantes Gerät, gewiss.";
				link.l1 = "Und wie sah er aus und wohin ist er gegangen? Ich brauche dieses Instrument dringend.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nein, ich habe nichts dergleichen gesehen.";
				link.l1 = "Ich verstehe. Nun - Zeit, sich umzuhören!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"Und was hat das mit mir zu tun? Ich bin ein Einheimischer!","Nun, warum belästigst du mich damit? Ich lebe in dieser Stadt und weiß nichts von solchen Dingen!"),NPCharSexPhrase(npchar,"Was wollen Sie schon wieder von mir? Habe ich Ihnen nicht schon gesagt, dass ich nicht der Spion bin?!","Habe ich dir nicht schon gesagt, dass ich ein Einheimischer bin?!"),NPCharSexPhrase(npchar,"Mein Lieber, du schon wieder! Lass mich in Ruhe - ich bin ein Ortsansässiger!","Warum belästigst du mich schon wieder mit deinen dummen Fragen?"),NPCharSexPhrase(npchar,"Wieder! Nun, das ist ein Skandal!","Hör zu, lass mich einfach in Ruhe, ja? Bitte!"),"Block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wer kann deine Aussage bestätigen?","Oh, es tut mir leid - ich hatte dich schon gefragt...","Es tut mir leid, es gibt so viele Menschen...","In Ordnung, in Ordnung...",npchar,Dialog.CurrentNode);
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
				pchar.GenQuest.SeekSpy.Type = characters[int(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (int(pchar.GenQuest.SeekSpy.Idx) == -1 || int(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Jeder kann! Hör zu, warum belästigst du mich immer wieder?! Wenn du ein Problem hast, geh zum Gouverneur und klär alles!",link.l1 ="Hmm... Es ist wahrscheinlich am besten, ihn nicht über so eine Kleinigkeit zu belästigen. Ich glaube dir.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Jeder in dieser Stadt! "+NPCharSexPhrase(npchar,GetFullName(&characters[int(pchar.GenQuest.SeekSpy.Idx)])+" kann es zum Beispiel jetzt tun, da "+NPCharSexPhrase(&characters[int(pchar.GenQuest.SeekSpy.Idx)],"er","sie")+" steht genau dort.","Oh, Herr, nun, zum Beispiel, "+NPCharSexPhrase(&characters[int(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[int(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[int(pchar.GenQuest.SeekSpy.Idx)]))+" kann es tun.");
			link.l1 = "In Ordnung, lass uns sehen, dann.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[int(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[int(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", float(pchar.GenQuest.SeekSpy.time), 0);
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Ja, "+NPCharSexPhrase(&characters[int(pchar.GenQuest.SeekSpy.BaseIdx)]," ist tatsächlich ein Einheimischer.","sie ist tatsächlich eine Einheimische.");
			link.l1 = RandPhraseSimple("Ich sehe"+GetSexPhrase("","")+". Danke für die Hilfe.","Alles klar. Danke für die Hilfe.");
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
			LAi_SetCitizenTypeNoGroup(&characters[int(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "Verstehen Sie, gestern war ich außerhalb der Stadt, habe einen Spaziergang gemacht und meinen Ehering verloren..."+GetSexPhrase("Kapitän, könnten Sie bitte danach suchen?","Meine Dame, bitte helfen Sie mir, es zu finden!")+"";
			link.l1 = "Natürlich "+GetSexPhrase("Ich kann! Für so ein hübsches Mädchen wie dich, kann ich alles tun!","Ich werde dir helfen. Die Kirche lehrt uns, den Bedürftigen zu helfen.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("Nein, ich kann nicht. Es tut mir leid. Ich habe zu viel zu tun.","Es tut mir leid, das kann ich nicht. Ich habe mich gerade erinnert"+GetSexPhrase("","")+", dass ich noch unerledigte Geschäfte habe...","Ich habe sehr wenig Zeit, also kann ich dir bei nichts helfen...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Kapitän","Dame")+", das ist wirklich großartig! Bitte finde diesen Ring für mich, mein Mann kommt gerade an "+int(NPChar.LifeDay)+" Tage, und ich möchte nicht, dass er mich ohne meinen Ehering sieht.";
			link.l1 = RandPhraseSimple("Wo hast du es verloren, sagst du?","Also, wo hast du es eigentlich verloren?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Gerade vorbei an den Stadttoren...";
			link.l1 = "Nun, dann gehe ich auf die Suche danach...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Ja, bitte tun Sie das. Und beeilen Sie sich - denken Sie daran, dass Sie nur haben "+int(NPChar.LifeDay)+" Tage.";
			link.l1 = "Ich erinnere mich.";
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
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, int(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Kapitän","junge Dame")+"! Ich bin so glücklich! Wie kann ich Ihnen danken?";
			link.l1 = "Oh, kein Dank nötig - ich habe es ganz uneigennützig getan.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Ein paar hundert Pesos würden sicherlich nicht schaden...";
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
			dialog.text = "Oh, "+GetSexPhrase("Kapitän, Sie sind so eine edle Person","Frau, Sie sind so edel")+"! Ich werde sicherlich in der Kirche für dich beten! Lebe wohl...";
			link.l1 = "Auf Wiedersehen, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Oh, aber natürlich. Hier -"+FindRussianMoneyString(iTemp)+". Das ist alles, was ich habe. Bitte nimm dieses Geld... Und leb wohl.";
			link.l1 = "Auf Wiedersehen, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Nein, ich weiß nichts darüber.","Ich weiß diesbezüglich nichts.","Ich weiß nichts.");
					link.l1 = LinkRandPhrase("In Ordnung, danke.","Ich verstehe, danke.","Gut, bitte entschuldigen Sie mich.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Ich weiß nichts darüber, aber du kannst die Gäste in der Taverne fragen - sie werden dir sicherlich ein oder zwei Dinge erzählen.","Ich kann Ihnen nichts sagen. Fragen Sie in der Taverne herum.","Ich weiß nichts Besonderes, aber ich habe gehört, dass es in der Taverne Klatsch gab.");
				link.l1 = "Nun, es ist zumindest etwas.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu - als Bürger dieser Stadt muss ich Sie bitten, nicht mit gezogenem Schwert herumzulaufen.","Hören Sie - als Bürger dieser Stadt muss ich Sie bitten, nicht mit einer gezogenen Klinge herumzulaufen.");
				link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du willst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Halt die Pferde "+GetSexPhrase("Kamerad","Lass")+" wenn man mit einer Waffe in der Hand herumläuft. Das macht mich nervös...","Ich mag es nicht, wenn "+GetSexPhrase("Männer","jemand")+" laufe mit gezogenen Waffen herum. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Habs verstanden.","Ich werde es weglegen.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
