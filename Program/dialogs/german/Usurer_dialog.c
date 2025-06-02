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
					dialog.text = " Es ist vorbei. Verlasse jetzt diesen Ort, "+pchar.name+". Ich werde dieses ganze Durcheinander aufräumen.";
					link.l1 = "Also gut, ich werde auslaufen!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Die Stadt ist in Alarmbereitschaft und sie suchen überall nach dir! Wenn ich du wäre, würde ich hier nicht lange bleiben.","Alle Wachen suchen nach dir. Ich bin kein Idiot und riskiere nicht, mit dir zu sprechen!","Lauf, "+GetSexPhrase("Kumpel","Mädchen")+", bevor Soldaten ein Sieb aus dir machen..."),LinkRandPhrase("Was willst du, abscheuliches Geschöpf?! Die Stadtwache ist über deine Position im Bilde und du wirst nicht entkommen, "+GetSexPhrase("schmutziger Pirat","du Piratenhure")+"!","Dreckiger Mörder, verschwinde von meinem Platz! Wachen!","Ich fürchte dich nicht, abscheuliche Kreatur! Bald wirst du in unserer Festung gehängt, du wirst nicht entkommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, das ist für mich kein Problem...","Sie werden mich nie kriegen."),RandPhraseSimple("Halt dein Maul, "+GetWorkTypeOfMan(npchar,"")+", oder ich schneide deine verfluchte Zunge ab!","Heh, "+GetWorkTypeOfMan(npchar,"")+", willst du auch einen Piraten fangen? Hör zu, Junge, sitz hier ruhig und du wirst leben..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Brauchen Sie etwas, Herr?";
				Link.l1 = "Ich brauche Informationen... Ich möchte Sie etwas fragen.";
				Link.l1.go = "quests";
				Link.l2 = "Wie wäre es mit einem kleinen Darlehen?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Nein, ich habe meine Meinung geändert.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Werfen Sie einen Blick auf diese Ohrringe, Monsieur. Ich habe sie in der Tasche eines Banditen im Dschungel gefunden. Dies ist eindeutig die Arbeit eines feinen Juweliers, der, da bin ich sicher, nicht aus dieser Wildnis stammt. Was sagen Sie dazu?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Ich weiß, dass Sie einen Schuldner namens Folke Deluc haben. Sagen Sie mir, wie schlimm ist seine... Versäumnis?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Ich bin hier wegen Folke Delucs Schuld.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "Ich habe Ihren Auftrag erledigt, Monsieur. Hier ist Ihr... spanischer Freund.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Nun, endlich hat ein würdiger Kapitän meinen Platz besucht, ich war so müde von Idioten, die denken, dass ich einfach ihre Doubloons und Guineas pflanze und jeden Monat Ernte sammle, um ihnen ihre Zinsen zu zahlen\nSie beobachten jeden Pfennig, haben aber keine Ahnung, wie der arme Wucherer zu verschiedenen Tricks greift, um nicht selbst vor Hunger zu sterben und ihnen gleichzeitig die Möglichkeit zu geben, eine Gans zu Weihnachten zu kaufen.";
				Link.l1 = "Ich vermute, dass Ihre Kunden solche Worte von dem Mann, der ihre Ersparnisse hält, nicht gerne hören werden.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Hör zu, alter Hamster, jetzt musst du wirklich dein Bestes geben, um mir alles zu erklären! In der Ladung dieses Schiffes waren keine Sklaven, sondern eine Kompanie Soldaten! Es war eine wirklich harte Mission, mit ihnen fertig zu werden! Ich bin sehr wütend, also erklären Sie sich besser!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ach, da bist du endlich! Das ganze Archipel spricht über deinen kühnen Angriff. Schön, dich zu sehen!";
				Link.l1 = "Ich würde eine Unbekanntheit einer solchen Berühmtheit vorziehen... Es ist zu gefährlich.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hast du meine fünftausend Sklaven gebracht?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Ich habe. Sie sind in meinem Laderaum.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Nein, ich arbeite noch daran.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm.. Du lebst noch? Seltsam. Aber das wird nicht lange dauern. Soldaten! Hilfe! Ich habe hier einen Banditen!";
				link.l1 = "So ein Bastard!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Guten Tag. Mein Name ist "+GetFullName(npchar)+". Wie kann ich dienen?";
				link.l1 = "Oh! Was machen Sie hier, Herr?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hallo da, du Bastard. Hattest du eine brillante Idee? Angeheuerte Schläger, um mich umzubringen? Wolltest du mich mundtot machen? Sprich jetzt!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Oh, Kapitän! Sehen Sie nur, was ich heute habe. Einige Dinge habe ich von Blackwoods Leuten erworben. Sie brauchen Geld für eine neue Expedition - und wir profitieren davon, nicht wahr?";
				link.l1 = "Weiß Blackwood, dass seine Leute ihre Funde verkaufen?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Guten Tag, "+GetAddress_Form(NPChar)+". Wie kann ich Ihnen helfen? Kenne ich Sie?","Kommen Sie herein, Kapitän. Mein Name ist "+GetFullName(npchar)+" und ich bin der örtliche Bankier.","Freut mich, dich zu treffen, "+GetAddress_Form(NPChar)+"! Ich bin ein örtlicher Bankier und wenn du ein Geldproblem hast, dann kann ich dir helfen."),LinkRandPhrase("Haben wir uns schon mal getroffen, Kapitän? Ich bin "+GetFullName(npchar)+", und ich bin ein örtlicher Bankier.","Kommen Sie herein, Kapitän. Mein Name ist "+GetFullName(npchar)+" und ich bin der örtliche Bankier.","Grüße, "+GetAddress_Form(NPChar)+". Ich bin "+GetFullName(npchar)+", der örtliche Bankier."),LinkRandPhrase("Freut mich, dich zu treffen, "+GetAddress_Form(NPChar)+", ich bin "+GetFullName(npchar)+" nur ein bescheidener Bankier in dieser wunderbaren Stadt.","Es liegt in deiner Hand, Kapitän! Willst du von mir etwas Geld leihen oder Geld gegen Zinsen verleihen?","Herr Kapitän! Ich bin so froh, dass Sie mein bescheidenes Büro besucht haben!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Mit Vergnügen! Ich bin gerade durch die Stadt spaziert und habe beschlossen, dich zu besuchen.","Mit Vergnügen, ich bin "+GetFullName(pchar)+", freut mich, dich kennenzulernen.",""+GetFullName(pchar)+" , Kapitän des Schiffes namens "+pchar.ship.name+" , freut mich, Sie zu treffen. Das ist eine Bank, richtig?"),RandPhraseSimple("Schön dich zu treffen. Ich bin "+GetFullName(pchar)+". Ein Kapitän des Schiffes namens "+pchar.ship.name+". Ich wollte dich nur kennenlernen.","Aha, also habt ihr hier eine Bank, nicht wahr? Freut mich, dich zu treffen, ich bin "+GetFullName(pchar)+", ein Kapitän meines eigenen Schiffes."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Frau MacArthur, willkommen, bitte kommen Sie herein.";
					link.l1 = "Und dir, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Du bist es! Was willst du, "+GetAddress_Form(NPChar)+"?","Was führen Sie hier im Schilde, Kapitän? Es tut mir leid, aber Ihr Ruf macht Sie nicht gerade zu einem begehrten Kunden.","Aha, ein weiterer Kunde! Zuerst dachte ich, du wärst ein Räuber... ha-ha Ich mache nur Spaß."),LinkRandPhrase("Oh! Was willst du? Das ist eine Bank, keine Kneipe.","Guten Tag an Sie, Kapitän. Ich muss Ihnen mitteilen, dass ich bei der Auswahl meiner Kunden sehr wählerisch bin.","Was willst du, "+GetFullName(pchar)+"? Ich hoffe, du erinnerst dich daran, dass dein Ruf es dir nicht erlaubt, einen großen Kredit aufzunehmen?"),LinkRandPhrase("Ich hoffe, dass Sie Geld investieren wollen, "+GetAddress_Form(NPChar)+"? Es wird nicht einfach sein, für dich einen Kredit aufzutreiben.","Kapitän "+GetFullName(pchar)+" Was willst du von dem bescheidenen Bankier? Entschuldigung, aber ich kann dir keinen Kredit arrangieren. Du kannst mir nur Geld gegen Zinsen leihen.","Komm rein, "+GetAddress_Form(NPChar)+". Es tut mir leid, Ihnen mitteilen zu müssen, dass Sie nicht der willkommenste Kunde sind, aber ich lehne Leute normalerweise nicht sofort ab.")),LinkRandPhrase(LinkRandPhrase("Hallo, Herr "+GetFullName(pchar)+"! Ich bin immer bereit, Ihnen bei geschäftlichen Problemen zu helfen.","Hallo, Herr "+GetAddress_Form(NPChar)+". Ich bin immer bereit, ein Darlehen aufzunehmen oder jede Investition anzunehmen.","Liebe "+GetFullName(pchar)+"! Froh, dich zu sehen! Was wünschst du dir?"),LinkRandPhrase("Kapitän "+GetFullName(pchar)+"! Ich stehe immer zu Ihren Diensten. Möchten Sie ein Darlehen aufnehmen oder Geld auf Zinsen investieren?","Sei gegrüßt, Kapitän! Sie sind immer ein gewünschter Kunde hier. Sie haben einen ausgezeichneten Geschäftsruf!","Guten Tag, "+GetFullName(pchar)+". Ich bin froh, dass du mich wieder besucht hast. Hoffst du auf eine profitable Geschäftsvereinbarung?"),LinkRandPhrase("Guten Tag an Sie, Kapitän! Was möchten Sie? Möchten Sie einen Kredit aufnehmen oder eine Investition tätigen?","Kapitän "+GetFullName(pchar)+"! Möchten Sie Geld zu vorteilhaften Bedingungen leihen? Ich freue mich immer, einen so respektablen Kunden zu sehen.","Schön, Sie wieder zu sehen, Kapitän! Ich stehe immer bereit, Ihnen zu helfen, sei es ein Darlehen aufzunehmen oder eine Investition zu tätigen.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Kein Scherz, Bankier, ich habe hier ein Geschäft.","Zu viel Gerede, Kumpel. Lass uns gleich zur Sache kommen.","Hast du gehört, dass Geld keinen Geruch hat? Also halt die Nase zu und lass uns zur Sache kommen."),LinkRandPhrase("Und so triffst du deine Kunden? Glück für dich, dass ich heute gut gelaunt bin.","Ha! Bist du nicht froh, mich zu sehen, hm? Und bin ich nicht ein goldenes Dublon, um einen positiven Eindruck auf dich zu machen. Wie auch immer, lass uns Geschäfte machen, Wucherer.","Eh, ich würde dir gerne Respekt beibringen, aber ich habe keine Zeit dafür. Lass uns stattdessen über Geld reden.")),RandPhraseSimple(LinkRandPhrase("Schön, meinen alten Freund zu sehen!","Es ist immer ein Vergnügen, hierher zu kommen, Kumpel. Lass uns gleich zur Sache kommen.","Ich bin auch sehr froh. Lass uns Geschäfte machen, Freund."),LinkRandPhrase("Wirklich froh, Sie zu treffen. Was gibt's Neues in den finanziellen Meeren?","Froh, dass du dich noch an mich erinnerst. Ich habe es eilig, also lass uns gleich zur Sache kommen.","Hallo, alter Freund! Schön, dich wieder zu sehen!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Wie kann ich Ihnen helfen?","Was willst du diesmal?","Hm... was sind Ihre Bedenken?","Eh, "+GetAddress_Form(npchar)+", du kannst dir nicht vorstellen, wie nervig Kunden sein können...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nein danke, ich gehe nur herum und rede.","Wieder ich. Wollte nur mit dir reden.","Jupp, ich bin's wieder. Nichts Ernstes, wollte nur mit dir reden.","Ja, Bankier zu sein ist manchmal nicht so einfach. Ich wollte nur reden...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Ich möchte unsere finanziellen Angelegenheiten besprechen.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Ich interessiere mich für Juwelen und ungewöhnliche Idole oder Edelsteine.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Ich brauche einige Informationen. Nun, ich habe etwas, worüber ich dich fragen möchte.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Ich habe Ihnen die Geschäftspapiere von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Ich bin hier auf Befehl eines Mannes. Er ist ein Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich hierher geschickt. Ich muss etwas von dir bekommen.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Guten Tag, ich wurde von Ihrem Sohn eingeladen."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Ich möchte wissen, wer der Besitzer des Dokuments ist.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Ich möchte über die Schulden Ihres Klienten sprechen. Sein Name ist "+pchar.GenQuest.Noblelombard.Name+". Er hat sein Familienerbstück verpfändet. Ich vertrete hier seine Interessen und habe das Recht, mit Ihnen über seine Rückgabe zu diskutieren.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Wir hatten vor drei Monaten eine Versammlung und sprachen über das Relikt eines Mannes. Sein Name war "+pchar.GenQuest.Noblelombard.Name+". Erinnert ihr euch daran? Er musste eine Einzahlung auf meinen Namen eröffnen. Die Summe beträgt  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"..., Freund.";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Es geht um Ihre ... Sklavenzuweisung.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+NPChar.name+", lass uns über deine Aufgabe sprechen.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+NPChar.name+", lass uns über deine Aufgabe sprechen.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+NPChar.name+", lass uns über deine Aufgabe sprechen.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Ich bin gekommen, wie wir vereinbart haben. Hast du einen Job für mich?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Ich kam, wie ich versprochen habe. Wie wäre es mit einer Arbeit?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Wie geht's dir? Hast du eine neue Aufgabe für mich?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Deine Mission ist erledigt. Ich konnte diese Ausreißer finden. Es war allerdings nicht so einfach.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Ich kam für einen neuen lukrativen Auftrag.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Schlechte Nachrichten,"+npchar.name+". Ich habe es nicht geschafft, die Brigantine zu bekommen.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Schau,  "+npchar.name+". Ich habe die Brigg verfolgt, aber ich habe keine Papiere gefunden. Sind Sie sicher, dass sie da waren?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Gute Nachrichten,"+npchar.name+". Ich konnte diese Brigantine aufspüren und die Papiere finden. Hier sind sie.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Hast du eine neue Aufgabe für mich vorbereitet?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", ich konnte diese sogenannte 'Galeone' abfangen.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", es tut mir so leid, aber ich konnte nicht an Bord dieses Galeons gehen.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Ich bin wegen meines Geldes gekommen.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Ihre Mission ist abgeschlossen. Dieser Bastard Gontier ist tot und ebenso seine Mannschaft.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Es tut mir leid, aber ich habe es nicht geschafft, Francois Gontier zu fangen, obwohl ich ihm nach Tortuga gefolgt bin. Er konnte auf seiner Korvette vor mir fliehen.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag,"+npchar.name+". Erzähl mir von dieser neuen Mission, die du für mich vorbereitet hast.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Ich würde nicht sagen, dass du Geld brauchst oder versuchst, deinen Reichtum zu vermehren. Was bringt dich in mein Büro?","Was willst du diesmal?","Hm... was sind Ihre Bedenken?","Eh, "+GetAddress_Form(npchar)+", du kannst dir nicht vorstellen, wie nervig Kunden sein können...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nein danke, ich gehe nur herum und rede.","Wieder ich. Wollte nur mit dir reden.","Jup, ich bin's wieder. Nichts Ernstes, wollte nur mit dir reden.","Ja, Bankier zu sein ist manchmal nicht so einfach. Ich wollte nur reden...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Ich möchte unsere finanziellen Angelegenheiten besprechen.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Ich interessiere mich für Juwelen und ungewöhnliche Idole oder Edelsteine.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Ich brauche einige Informationen. Nun, ich habe etwas, das ich dich fragen möchte.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Ich habe Ihnen die Geschäftspapiere von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Ich bin hier auf Befehl eines Mannes. Er ist ein Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich hierher geschickt. Ich muss etwas von dir bekommen.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Guten Tag, ich wurde von Ihrem Sohn eingeladen."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Ich möchte wissen, wer der Besitzer des Dokuments ist.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Ich möchte über die Schulden Ihres Kunden sprechen. Sein Name ist "+pchar.GenQuest.Noblelombard.Name+". Er hat sein Familienerbstück verpfändet. Ich vertrete hier seine Interessen und habe das Recht, mit Ihnen über seine Rückgabe zu verhandeln.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Wir hatten vor drei Monaten ein Treffen und sprachen über ein Mannes Relikt. Sein Name war "+pchar.GenQuest.Noblelombard.Name+". Erinnerst du dich daran? Er musste eine Einzahlung auf meinen Namen vornehmen. Die Summe ist  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"..., Freund.";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Es geht um Ihre ... Sklavenaufgabe.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+NPChar.name+", lass uns über deine Aufgabe sprechen.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+NPChar.name+", lass uns über deine Aufgabe sprechen.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+NPChar.name+", lass uns über deine Aufgabe sprechen.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Ich kam, wie wir vereinbart haben. Hast du einen Job für mich?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Ich kam, wie ich versprochen habe. Wie wäre es mit einem Job?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Wie geht es Ihnen? Haben Sie eine neue Aufgabe für mich?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Deine Mission ist erledigt. Ich konnte diese Ausreißer finden. Es war allerdings nicht so einfach.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Ich bin für einen neuen lukrativen Auftrag gekommen.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Schlechte Nachrichten,"+npchar.name+". Ich habe es nicht geschafft, die Brigantine zu bekommen.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Schau,  "+npchar.name+". Ich habe die Brigantine verfolgt, aber ich habe keine Papiere gefunden. Sind Sie sicher, dass sie da waren?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Gute Nachrichten,"+npchar.name+". Ich konnte die Brigantine aufspüren und die Papiere finden. Hier sind sie.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Haben Sie eine neue Aufgabe für mich vorbereitet?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", ich konnte diese sogenannte 'Galeone' abfangen.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", es tut mir so leid, aber ich konnte dieses Galeon nicht betreten.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag, "+npchar.name+". Ich bin wegen meines Geldes gekommen.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", deine Mission ist abgeschlossen. Dieser Bastard Gontier ist tot und seine Crew auch.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Es tut mir leid, aber ich habe es nicht geschafft, Francois Gontier zu fangen, obwohl ich ihm nach Tortuga gefolgt bin. Er hat es geschafft, auf seiner Korvette vor mir zu fliehen.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Guten Tag,"+npchar.name+". Erzähl mir von dieser neuen Mission, die du für mich vorbereitet hast.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Möchten Sie einige goldene Dublonen oder Truhen dafür kaufen? Vertrauen Sie mir, es ist eine sehr wertvolle Investition.";
			link.l1 = "Ja, das ist sehr interessant.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Möchten Sie gegen Pesos oder Dublonen handeln?";
			link.l1 = "Für Pesos.";
			link.l1.go = "items";
			link.l2 = "Für Dublonen.";
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
			dialog.text = "Es wird viel meiner Zeit in Anspruch nehmen, diese Papiere zu lesen und meine Zeit kostet viel.";
			link.l1 = "Vielleicht, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" Pesos werden Ihre Zeit entschädigen?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Wie du wünschst. Lebewohl!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lass mich mal sehen! Nein, diesen Namen habe ich noch nie gesehen. Zeige sie unserem Hafenmeister.";
				link.l1 = "Es tut mir leid, aber wir hatten eine Abmachung! Du hast mir versprochen, mir von diesem Kapitän zu erzählen!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+"Sie sagen, er sei ein erfolgreicher Schmuggler. Ist das das, was du hören wolltest?";
				link.l1 = "Es scheint so...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"Diese Dokumente sind für unser Kolonialpatrouillenschiff unterschrieben und sein Kapitän ist bekannt für seine starken Prinzipien.";
				link.l1 = "Eine Patrouille? Unter dem Befehl des Kommandanten?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Ich habe Ihnen versprochen, einen Blick auf diese Papiere zu werfen und nichts weiter. Sie können gehen.";
			link.l1 = "Danke... Ich nehme an.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "Es liegt bei dir. Unser Kommandant hat schon lange ein 'Interesse' an dieser einen Person gezeigt. Hast du schon Ideen? Und hier haben wir Frachtbriefe ohne Markierungen...";
			link.l1 = "Ich verstehe. Meinen Dank!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"Und wie ich bereits erwähnt habe, ist der Besitzer des Papiers ein Mann von Prinzipien und mag die lokalen Verbrechen nicht wirklich.";
			link.l1 = "Ich verstehe. Meinen Dank!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ach, ich nehme an, dass Sie der Kapitän sind, der meinen verlorenen Sohn mit seiner jungen Braut gebracht hat?";
				link.l1 = "Ja, ich war es, der ihnen geholfen hat zu entkommen.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ach, da bist du ja, mein Wohltäter. Du wartest wohl auf eine Belohnung, vermute ich?";
				link.l1 = "Ein Dankeschön wäre zumindest nett...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Ich bin wirklich dankbar, dass Sie meinem Kind geholfen und es nicht in dieser schwierigen Situation gelassen haben. Bitte erlauben Sie mir, Ihnen so gut ich kann zu danken. Akzeptieren Sie diese bescheidene Summe und ein kleines Geschenk von mir.";
			link.l1 = "Mein Dank. Es war mir eine Freude, diesem jungen Paar zu helfen.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Danke? Wofür? Dieser Tölpel war die Hälfte des Jahres arbeitslos und hat bereits Zeit gefunden, sich ein Mädchen zu schnappen! In seinem Alter führte ich mein eigenes Geschäft. Es gibt eine heiratsfähige Gouverneurstochter und er bringt diese Hure hierher, Herr, vergib mir, dass ich das sage! Und jetzt sucht er meinen Segen!";
			link.l1 = "Ich nehme an, dass du nicht an Gefühle glaubst?";
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
			dialog.text = "Gefühle? Was für Gefühle? Du bist ein erwachsener Mann und redest auch noch von diesen Gefühlen? Es ist eine Schande, dass du ein Zuhälter für die Jugend bist. Hast das Mädchen von ihren Eltern weggenommen und das Leben meines Sohnes zerstört. Von mir bekommst du keinen Dank. Lebewohl.";
			link.l1 = "Auf Wiedersehen dann...";
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
					dialog.text = "Lassen Sie uns darüber sprechen. Ich höre zu.";
				}
				else
				{
					dialog.text = "Uh, uh. Ich fürchte, ich muss Ihnen ablehnen, "+GetAddress_Form(NPChar)+". Es tut mir leid, aber meine Bank bietet keine Dienstleistungen für die Feinde Spaniens an.";
					link.l1 = "Geld hat keine Nationalität, Señor Bankier.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Mm-hmm, "+GetAddress_Form(NPChar)+". Ich muss Ihnen mitteilen, dass Ihre Einzahlung nicht mehr gültig ist.";
							Link.l1 = "Auf welcher Grundlage?!";
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
			dialog.text = "Lass uns darüber reden. Ich höre zu.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Ich schulde dir "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", ich bin bereit, Ihr Geld zurückzugeben",". Ich möchte die Schuld begleichen.",".  Endlich ist es Zeit, die Schulden zu begleichen.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Ich möchte einige Münzen leihen.","Ich muss wirklich einige Pesos bekommen.","Wie wäre es mit einer kleinen Leihe?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Ich möchte mein Geld zum Zinsen anlegen.","Würdest du ein paar Säcke meines Silbers aufbewahren?","Darf ich Ihnen etwas Silber für einen unglücklichen Tag hinterlassen?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Ich möchte einige Dublonen zur Verzinsung anlegen.";
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
				Link.l9 = LinkRandPhrase("Ich bin hier, um meine Investition zurückzubekommen, in Pesos.","Es ist Zeit, mein Silber zurückzubekommen, das du mir schuldest.","Ich brauche meine Investition in Pesos zurück, mit all dem Zins.");
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
				Link.l10 = LinkRandPhrase("Ich möchte meine Investition in Dublonen zurücknehmen.","Es ist Zeit, mein Gold zurückzubekommen, das du mir schuldest.","Ich brauche meine Investition in Dublonen mit allem Zinsen zurück.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Ich erinnere mich an meine Schuld, bin aber noch nicht bereit zu zahlen...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Mein Fehler, ich habe keine finanziellen Angelegenheiten mit dir. Lebewohl.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Nein, ich kann Ihnen nicht helfen. Ich kann nur Investitionen an diesem schwierigen Ort akzeptieren. Sie können Silberpesos oder Gold-Dublonen investieren.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Ich möchte Pesos investieren und über die Summe sprechen.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Ich möchte Dublonen investieren. Lassen wir die Summe klären.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Nicht interessiert.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Dein Name ist "+GetFullName(pchar)+", richtig? Du hast "+RandPhraseSimple("ein schlechter Ruf ","ein schlechter Ruf ")+" und ich möchte keine Geschäfte mit dir machen.";
				link.l1 = RandPhraseSimple("Kann ein Mann nicht einen Fehler machen?",RandSwear()+"Wie auch immer!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, du bist immer willkommen. Welche Summe brauchst du?";
			Link.l1 = "Eine kleine.";
			Link.l1.go = "Small";
			Link.l2 = "Mäßig.";
			Link.l2.go = "Medium";
			Link.l3 = "So groß wie möglich.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Ausgezeichnet! Es ist immer viel einfacher, mit kleinen Summen umzugehen - weniger Risiko für beide Seiten. Ich kann Ihnen anbieten "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"..., Freund.";
			Link.l1 = "Abgemacht. Was ist mit deinem Interesse?";
			Link.l1.go = "Interest";
			Link.l2 = "Es wird für mich nicht funktionieren. Lass uns das ändern.";
			Link.l2.go = "Loan";
			Link.l3 = "Ich nehme an, es ist besser für mich, keine Schulden zu machen. Lebewohl.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Kein Problem. Ich hoffe, dass "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" wird Ihnen helfen, Ihre Probleme zu lösen. Das ist eine ziemlich beträchtliche Summe.";
			Link.l1 = "Abgemacht. Was ist mit Ihrem Interesse?";
			Link.l1.go = "Interest";
			Link.l2 = "Das wird bei mir nicht funktionieren. Lass es uns ändern.";
			Link.l2.go = "Loan";
			Link.l3 = "Ich vermute, es ist besser für mich, mich von Schulden fernzuhalten. Auf Wiedersehen.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Nun... es ist riskant. Gut, ich bin bereit, für dich einen Kredit aufzunehmen für "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". Ich hoffe, Sie verstehen, Kapitän, das ist eine wirklich erhebliche Summe. Ich bitte Sie, das ernst zu nehmen.";
			Link.l1 = "Abgemacht. Was ist mit deinem Interesse?";
			Link.l1.go = "Interest";
			Link.l2 = "Es wird nicht für mich funktionieren. Lass es uns ändern.";
			Link.l2.go = "Loan";
			Link.l3 = "Ich nehme an, dass es besser für mich ist, mich von Schulden fernzuhalten. Auf Wiedersehen.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest+"%% pro Monat. Ich kann Ihnen keine besseren Konditionen anbieten, basierend auf dem, was ich über Sie weiß."; 
			Link.l1 = "Funktioniert für mich. Lass uns über die Zeit sprechen.";
			Link.l1.go = "Period";
			Link.l3 = "Ich vermute, es ist besser für mich, mich von Schulden fernzuhalten. Auf Wiedersehen.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Unter Berücksichtigung meiner Informationen über Sie, "+Pchar.name+", ich werde auf die Rückzahlung dieses Darlehens warten "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+". Danach werde ich bestimmte Maßnahmen ergreifen. Hoffe, dass du das verstehst."; 
			Link.l1 = "Ich akzeptiere gerne Ihre Bedingungen... und Ihre Münzen.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Entschuldigen Sie, aber das wird bei mir nicht klappen. Lebewohl.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Ich bin aufrichtig erfreut. Aber lass mich dich warnen. Ich mache das schon lange und ich weiß, wie ich meine Investitionen zurückbekomme. Also, wenn du jemals irgendwelche dummen Ideen hattest, schlage ich vor, du lässt sie sein\nNichts für ungut, nur eine Warnung.";
			Link.l1 = "Hm.. Nun. Lebewohl.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "Es ist Ihre Wahl, Kapitän. Mein Interesse wächst und Sie haben nicht viel Zeit.";
			Link.l1 = "Mach dir keine Sorgen darum. Wir sehen uns.";
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
			dialog.text = LinkRandPhrase("Wunderbar! Kommt zu mir, wenn ihr Münzen braucht. Ich stehe jederzeit zu eurem Dienst.","Mein Dank. Es ist immer eine Freude, mit einem Mann zu verhandeln, der in der Lage ist, seine Schulden rechtzeitig zurückzuzahlen. Manchmal passieren Dinge, und ich kann es verstehen, wissen Sie... aber ich bevorzuge es, wenn Probleme gelöst werden.","Oh, ich habe richtig getan, dir zu vertrauen, "+GetAddress_Form(NPChar)+"! Ich hoffe, dass es nicht das letzte Mal ist, dass du meine Dienste in Anspruch nimmst. Vielleicht können wir sogar bessere Geschäfte für dich machen, da ich jetzt weiß, dass du ein ehrlicher Mann bist.");
			Link.l1 = LinkRandPhrase("Ich möchte etwas Geld leihen.","Ich muss wirklich einige Pesos bekommen.","Wie wäre es mit einer kleinen Leihe?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Ich möchte mein Geld investieren.","Wirst du etwas Piratenbeute behalten?","Darf ich Ihnen etwas Silber für einen unglücklichen Tag hinterlassen?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Ich möchte einige Dublonen zum Zins anlegen";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Auf Wiedersehen, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Ich sehe einen weisen Mann! Welchen Betrag möchten Sie investieren?","Gut. Vertraue mir, diese Summe wird hier sicher und mit all ihren Zinsen auf dich warten.","Ich sehe, dass Sie wissen, was im Leben wirklich wichtig ist. Wie viel möchten Sie investieren?");
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
				dialog.text = "Scherzt du, huh?";
				link.l1 = "Mein Fehler.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, leider hast du nicht so viel Geld. Lass uns ernst sein...";
				link.l1 = "Gut.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "In Ordnung. Ich kann dir anbieten... sagen wir mal..."+Pchar.QuestTemp.Deposits.(sDepositType1).Interest+" %. Pro Monat, natürlich.";
			Link.l1 = "Es funktioniert für mich.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Ich sollte besser die Summe ändern.";
			Link.l2.go = "Deposit";
			Link.l3 = "Sieht so aus, als wäre das eine schlechte Idee gewesen... Auf Wiedersehen.";
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
			    dialog.text = "Verzeihen Sie mir, Kapitän, aber diese Summe ist zu groß für meine Kolonialbank. Ich werde nicht in der Lage sein, Ihnen Ihre Zinsen zu zahlen. Und das Fehlen einer zuverlässigen Wache... Ich hoffe, Sie verstehen. Jedenfalls ist die maximale Summe, die ich von Ihnen annehmen kann, "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Schade, ich muss dann einen anderen Bankier finden.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Sie können jetzt sicher sein, dass selbst der stärkste Sturm Sie nicht ohne eine Münze lassen würde.";
				Link.l1 = "In Ordnung. Wir sehen uns.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Unter Berücksichtigung des versprochenen Zinses und der vergangenen Zeit schulde ich Ihnen "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Bist du sicher, dass du das Geld nehmen willst?";
			Link.l1 = "Auf jeden Fall. Gib es mir.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Ich möchte einen Teil meines Geldes nehmen.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Du hast recht. Ich lasse es für eine Weile bei dir. Hab einen guten Tag.";			
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
			dialog.text = "Und wie viel?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Das war so ein dummer Witz, Herr!";			
				link.l1 = "Verdammt! Es tut mir so leid... Lass uns den Betrag ändern.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Sie haben nicht so viel Geld auf Ihrem Konto.";			
				link.l1 = "Verdammt! Mein Fehler. Lass uns die Summe ändern.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Alles? Gut, wie du willst. Hier ist dein Geld.";			
				link.l1 = "Dankbarkeit!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Gut. Nimm es. Hier ist dein Geld.";			
			link.l1 = "Danke!";	
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
			dialog.text = "Oh... Es ist so hart, es zu verlieren. Ich habe mich wirklich an dieses Geld gewöhnt. Komme trotzdem wieder.";			
			Link.l1 = "Ich werde es tun, wenn ich muss. Lebewohl.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Ich sehe einen weisen Mann! Welchen Betrag möchten Sie investieren?","Gut. Vertrau mir, diese Summe wird hier sicher auf dich warten und mit all deinen Zinsen.","Ich sehe, dass Sie wissen, was im Leben wirklich wichtig ist. Wie viel möchten Sie investieren?");
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
				dialog.text = "Scherzen, huh?";
				link.l1 = "Hm, mein Fehler...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, leider hast du nicht so viel Geld. Lass uns ernst sein...";
				link.l1 = "Hm... gut.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "In Ordnung. Ich kann dir anbieten... sagen wir mal..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Pro Monat, natürlich.";
			Link.l1 = "Funktioniert für mich.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Ich sollte besser die Summe ändern.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Ich vermute, es ist besser, mein Gold zu behalten. Lebewohl.";
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
			    dialog.text = "Verzeihen Sie mir, Kapitän, aber diese Summe ist zu groß für meine Kolonialbank. Ich werde nicht in der Lage sein, Ihnen Ihre Zinsen zu zahlen. Und das Fehlen eines zuverlässigen Wächters... Ich hoffe, Sie verstehen. Wie auch immer, die maximale Summe, die ich von Ihnen annehmen kann, ist "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Schade, dann muss ich wohl einen anderen Bankier finden.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Du kannst jetzt sicher sein, dass dich selbst der stärkste Sturm nicht ohne einen Groschen lassen würde.";
				Link.l1 = "Gut. Lebewohl.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Unter Berücksichtigung des versprochenen Zinses und der vergangenen Zeit schulde ich Ihnen "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Bist du sicher, dass du das Geld nehmen willst?";
			Link.l1 = "Auf jeden Fall. Gib es mir.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Ich möchte einen Teil meines Geldes nehmen.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Du hast recht. Ich lasse es eine Weile bei dir. Habe einen guten Tag.";			
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
			dialog.text = "Und wie viel?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "So ein dummer Witz, Herr!";			
				link.l1 = "Verdammt! Es tut mir so leid... Lass uns die Summe ändern...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Sie haben nicht so viel Gold auf Ihrem Konto, mein Herr.";			
				link.l1 = "Verdammt! Mein Fehler. Lass uns die Summe ändern...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Alles? Gut, wie du willst. Hier ist dein Geld.";			
				link.l1 = "Danke!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Gut. Nimm es. Hier ist dein Geld.";			
			link.l1 = "Dankbarkeit!";	
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
			dialog.text = "Oh... Es ist so schwer, es zu verlieren. Ich habe mich wirklich an dieses Geld gewöhnt. Komm trotzdem wieder.";			
			Link.l1 = "Ich werde es tun, wenn ich muss. Lebewohl.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Du lebst noch? Willst du mir vielleicht mein Geld zurückgeben? Zum Teufel mit dir! Ich habe so viel Geld verloren, dass du es mir nie zurückzahlen könntest! Und ich werde keine Ruhe finden, bis ich deinen leblosen Körper sehe!";
            Link.l1 = "Ich möchte die Dinge einfach auf friedliche Weise regeln.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Sehr gut, lass uns sehen! Wisse, dass du auch nicht vor dem Tod geschützt bist!","Eine Bedrohung?! Dann lass uns mal sehen, was du tun wirst...","Geld ist nicht das Wichtigste in unserem Leben. Trauere nicht zu sehr darüber und töte Menschen, komm schon, ich fordere dich heraus.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Verschwinde! Ich wünschte, ich würde dich nie wieder sehen.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Ach wirklich? Und was sind Ihre Bedenken?";
			Link.l1 = "Für heute schulde ich dir "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". Und ich biete dir dieses Geld an.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Ich biete dir meine Schuld an, um gute Beziehungen zu dir wiederherzustellen. Es ist "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Jetzt reden wir! Schließlich kann ich Geschäfte mit dir machen.";
			Link.l1 = "Danke. Ich werde dich nicht mehr enttäuschen.";
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
			dialog.Text = "Ach, komm schon! Wir sind ernsthafte Leute, du und ich, wir sind besser als diese Idioten, die bereit sind, für einen einzigen Dublon zu sterben, aber niemals versuchen, zwei Dublonen daraus zu machen\nIch suche einen Mann, dem ich ein ernsthaftes Geschäft anbieten kann. Einen tapferen und aktiven Mann, ehrlich und pünktlich, aber nicht belastet mit... eh... zu viel Skrupel in Bezug auf moralische Dilemmata. Und ich hoffe, dass du der Mann bist, den ich suche.";
			Link.l1 = "Es wird davon abhängen, was für ein 'Angebot' du mir machen wirst.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Sehr gut, hör zu. Sklaverei ist heutzutage das profitabelste Geschäft in der Karibik. Ich bin kein Pflanzer, aber ich habe vertrauenswürdige Kunden\nAlso, ich brauche die folgende Anzahl von Sklaven - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" Köpfe. Ich bin bereit, Ihnen 250 Pesos für jeden zu zahlen. Glauben Sie mir, das ist ein guter Preis. Insgesamt werden Sie verdienen "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+" Pesos.";
			Link.l1 = "Nein, ich bin kein Sklavenhändler. Such dir einen anderen Gehilfen, dem sein Gewissen egal ist.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Ein verlockendes Angebot. Ich würde das gerne tun. Wann benötigen Sie die Sklaven?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, es scheint, dass niemand Lust hat, seinen Hintern zu bewegen und das Gold unter seinen Füßen zu nehmen. Ich bin enttäuscht, sehr sogar. Lebewohl und denk nicht einmal daran, Gerüchte über unser Gespräch zu verbreiten. Mein Arm hat eine lange Reichweite...";
			Link.l1 = "Deine Reichweite ist 'schmutzig'... genau wie deine Zunge. Lebewohl.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Ich werde Ihre Zeit nicht begrenzen, aber versuchen Sie, Ihre Mission so schnell wie möglich zu erfüllen. Die Nachfrage nach dem 'schwarzen Elfenbein' ist enorm. Wenn Sie Ihre Arbeit gut machen, werde ich Ihnen in Zukunft immer wieder solche Aufträge geben.";
			Link.l1 = "Klingt gut. Nun, warte auf die guten Nachrichten.";
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
			dialog.Text = "Haben Sie es geschafft, diese Lieferung von 'schwarzem Elfenbein' zu bekommen?";
            if (amount < 0)
			{
				Link.l1 = "Noch nicht. Ich überprüfe nur, ob unsere Vereinbarung noch aktiv ist.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Ich habe. Sie sind alle in meiner Fracht.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Herrlich. Meine Männer werden sie übernehmen... Mach dir keine Sorgen um den Zoll oder den Kommandanten der Festung. Ich leite hier eine riesige Operation, also erwarte keine Probleme und niemand wird dich des Schmuggels beschuldigen.";
			Link.l1 = "Es scheint, dass Sie eine starke Position hier haben... Wie wäre es also mit meiner Bezahlung?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Hier ist es. Ich rede nicht umsonst. Bleib bei mir, Kapitän, und bald wirst du so viel Gold besitzen, dass du eine Galeone brauchst, um es zu bewegen!";
			Link.l1 = "Das wäre großartig ha-ha... Was kommt als nächstes?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Nächster? Kommt in drei Wochen wieder her. Ich bereite gerade einen Handel vor und er sollte zu dieser Zeit fertig sein.";
			Link.l1 = "Sehr gut, abgemacht. Auf Wiedersehen.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Ich habe einen Job, aber dein Schiff ist zu schwach. Ich möchte nicht, dass du die Mission versagst und ich möchte dich auch nicht in den Tod schicken. Es ist noch Zeit, also besorg dir ein größeres Schiff wie eine Barkentine, Brigantine, Brig oder Flöte mindestens. Verschwende die Zeit nicht!";
				Link.l1 = "Ich verstehe, ich werde mich darum kümmern. Bis dann.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Endlich! Ich habe auf dich gewartet. Jetzt kommen wir direkt zur Sache. Wie du weißt, gibt es in jedem Geschäft immer Konkurrenten... und ich habe meine eigenen. Diese gierigen und skrupellosen Bastarde sind immer bereit, mir einen Kunden wegzunehmen! Eigentlich möchte ich einen von ihnen beseitigen und gleichzeitig eine gute Münze verdienen.";
				Link.l1 = "Ich bin ganz Ohr.";
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
			dialog.text = "Sehr gut. Jetzt hör zu. Dieser Schurke namens "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", hat Sklaven aus Afrika gebracht und den Anker bei "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", es liegt auf einer Insel namens "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Er wartet dort auf Schmuggler. Sein Galeone heißt '"+pchar.questTemp.Slavetrader.ShipName+". Ihr Deal muss um jeden Preis gebrochen werden!";
			link.l1 = "Und was ist mit den Sklaven? Es wäre so eine Verschwendung, sie sinken zu lassen!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Warum würdest du das tun? Es besteht kein Bedarf daran. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" hat einen schlechten Ruf und niemand wird über sein Verschwinden verärgert sein. Entere sein Galeon, töte den Mann und sorge dafür, dass er tot bleibt, bring mir die Ladung und ich werde sie verkaufen. Meinen Quellen zufolge sind es etwa tausendfünfhundert Sklaven.";
			Link.l1 = "Wahnsinn. Das ist eine beachtliche Summe. Und was ist mit meiner Bezahlung?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Nein, Herr, diese Intrigen sind nichts für mich. Warum sollte ich meine Beziehungen zu Schmugglern ruinieren?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Nun.. Es scheint, als hätte ich mich in dir getäuscht... Lebewohl und vergiss unser Gespräch. Und verbreite keine Gerüchte über das, was du hier gehört hast. Ich besitze diese Stadt. Und wenn du vorhast, das Schiff 'zu betreten"+pchar.questTemp.Slavetrader.ShipName+" für dich selbst... Ich werde dafür sorgen, dass du am Galgen endest. Bedenke es.";
			Link.l1 = "Macht euch keine Sorgen, ich werde es den Behörden nicht melden und ich brauche eure Galeone nicht. Lebewohl.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Angesichts der Tatsache, dass ich dir den Standort der Ladung gegeben habe und du nicht auf der Suche nach 'einem Preis' segeln musst, ist die Bezahlung etwas niedriger - 200 Pesos pro Kopf. Und dennoch ist das eine große Summe - dreihunderttausend Pesos im Falle eines Erfolgs und das Schiff.";
			Link.l1 = "Abgemacht. Wie viel Zeit habe ich?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! Du sagst das, als ob diese Sklaven von selbst zu meinem Schiff schwimmen würden, in der Hoffnung, so schnell wie möglich in meine Fracht zu gelangen! Willst du wirklich, dass meine Leute für eine so kleine Summe ihren Kopf riskieren? Erhöhe meine Belohnung oder ich bin raus aus dem Geschäft.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Du hast zwei Wochen. Sei nicht zu spät, sonst wird er seine Ladung umladen und alles wird vorbei sein.";
			link.l1 = "Muss mich dann beeilen. Erwarte mich mit guten Nachrichten.";
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
			dialog.text = "Nun, "+GetFullName(pchar)+", was ist mit unserer Mission? Dein freudloses Gesicht sagt mir, dass du es vermasselt hast.";
			link.l1 = "Verdammt, du hast recht... Ich... nun, du weißt... Ich war zu spät. Es schien, dass er den Ort bereits verlassen hatte, denn ich fand dort niemanden. Musste den ganzen Weg mit dem Wind segeln, verdammt nochmal...";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Nun, "+GetFullName(pchar)+", was hast du heute gefangen? Sie haben mir gesagt, dass "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" füttert die Fische! Ha-ha-ha!";
			link.l1 = "Ja, ich war gerade noch rechtzeitig! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" hat Sklaven auf das Schmugglerschiff überführt. Musste sie beide entern und sie persönlich zu Davy Jones schicken, damit du jetzt weniger Konkurrenten hast.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Ja, ich schätze, ich habe mich in dir geirrt. Du warst zu spät? Oder hattest du einfach zu viel Angst zu kämpfen? Wie auch immer. Jetzt hat es keine Bedeutung mehr. Verschwinde. Ich bin fertig mit dir. Vergiss alles, was du hier gesehen oder gehört hast.";
			link.l1 = "Lebewohl dann.";
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
				dialog.text = "Ich hatte recht mit dir - "+GetSexPhrase("du bist ein fescher Schurke","du bist eine wilde Maid")+"! Ich brauche Männer wie dich. Du hast deine Mission auf hervorragende Weise erfüllt - du hast mehr als eineinhalbtausend Sklaven gebracht! Leider kann ich dir nur für eintausendsechshundert Sklaven bezahlen. Ich habe nicht genug Münzen, um dich für den Rest zu bezahlen, also musst du sie selbst verkaufen. Deine Belohnung beträgt 320 000 Pesos.";
				link.l1 = "Dankbarkeit. Schön, Geschäfte mit dir zu machen, "+npchar.name+"!";
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
				dialog.text = "Ich hatte recht mit dir - "+GetSexPhrase(" du bist ein fescher Schurke"," du bist eine wilde Maiden")+"! Ich brauche Männer wie Sie. Sie haben Ihre Mission auf hervorragende Weise erfüllt - Sie haben mir gebracht "+sTemp+" Sklaven. Deine Belohnung ist "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Dankbarkeit. Schön, Geschäfte mit dir zu machen, "+npchar.name+"!";
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
				dialog.text = "Immerhin hast du die schwierigste Situation mit aller Ehre überlebt. Obwohl der Preis geringer ist als ich erwartet habe, bin ich immer noch zufrieden. Du hast gebracht "+sTemp+" Sklaven. Deine Belohnung ist "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Dankbarkeit. Schön, Geschäfte mit dir zu machen, "+npchar.name+"!";
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
				dialog.text = "Ich verstehe... Ich kann das nachvollziehen, aber ich habe viel mehr erwartet. Du hast nur "+sTemp+" Sklaven. Zumindest hast du meine Konkurrenten zerstört und das ist etwas wert. Deine Belohnung ist  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Mein Dank. Ich schätze dein Verständnis, "+npchar.name+"!";
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
				dialog.text = "Klingt gut, aber... hmm. Sieht aus, als hätte ich mich in dir geirrt. Was hast du mitgebracht? "+sTemp+" Sklaven? Und was ist mit dem Rest? Und erzähl mir nicht, dass du sie versenkt hast. Ich bin sicher, du hast sie an Schmuggler verkauft, oder noch schlimmer - an diesen Bastard Lavoisier. Verpiss dich, ich will nichts mehr mit dir zu tun haben!";
				link.l1 = "Wie du wünschst, tschüss.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Klingt großartig, aber ... wo sind unsere Sklaven? Wo ist unsere Fracht? Und sag mir nicht, dass du es versenkt hast. Du musst es an die Schmuggler verkauft haben oder schlimmer noch, an diesen Bastard Lavoisier. Verschwinde, ich habe genug von dir.";
			link.l1 = "Wie du willst, Tschüss.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Das ist noch nicht vorbei. Niemand wagt es, mich zum Narren zu halten! Und du wirst für deinen Versuch bezahlen - ich werde dafür sorgen, dass du Probleme bekommst. Jetzt verschwinde von hier!";
			link.l1 = "Verfluchte Sei du und dein Sklavenhandel! Ich sollte dich dort und jetzt aufschlitzen, aber ich bin ein besserer Mann, als du je sein wirst.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Es sieht so aus, als ob wir gut miteinander auskommen, "+pchar.name+". Ich bin sehr erfreut. Sieh mich in einem Monat und vielleicht finde ich eine Arbeit nur für dich. Ich habe schon ein paar Ideen.";
			link.l1 = "Sicher, wir sehen uns in einem Monat. Meine Arbeit mit dir ist sehr profitabel.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "Es wird dir ein Vermögen machen... Noch eine letzte Frage, "+pchar.name+", haben Sie etwas Ungewöhnliches in der Kajüte der Galeone gefunden?";
			link.l1 = "Nichts Besonderes wirklich... Habe ich etwas verpasst?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Du meinst diesen alten Gürtel, irgendein 'Skorpion'-Amulett?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Vielleicht hast du es getan, und vielleicht auch nicht ... Es spielt jetzt keine Rolle mehr. Wir sehen uns in einem Monat. Auf Wiedersehen!";
			link.l1 = "Bis dann, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Genau! Das ist eine Medici-Fibula... Hast du jemals von ihnen gehört? Das bedeutet, dass sie wirklich in der Bastard-Kabine war... Darf ich mal sehen?";
			link.l1 = "Sicher, nimm es.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nun-nun... Das ist es wirklich. Hör zu, "+pchar.name+", verkaufe es mir. Ich bin bereit, hunderttausend Pesos zu zahlen.";
			link.l1 = "Einhunderttausend? Hm.. Ich stimme zu. Hier hast du es!";
			link.l1.go = "Buystatue";
			link.l2 = "Nein, ich werde es nicht verkaufen. Der wahre Preis dieser Fibel kann nicht in Silber oder Gold bewertet werden. Ich weiß, wie solche Dinge funktionieren.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Perfekt! Ich bin froh, dass wir einen Deal haben. Nimm dein Geld. Ich freue mich darauf, dich in einem Monat zu sehen.";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Sie sehen, ich brauche diese Fibel verzweifelt! Ich stimme Ihnen voll und ganz zu, sie kann nicht mit Geld bewertet werden, irgendein dummer Verkäufer wird Ihnen nicht einmal fünftausend dafür bezahlen. Aber es scheint, dass Sie wirklich wissen, was sie tun kann, da Sie sich weigern, sie für eine solche Summe zu verkaufen.\nDarf ich Ihnen einen Tausch anbieten, wenn Sie kein Geld wollen. Ich habe etwas, das Sie interessieren könnte. Hier, schauen Sie mal. Eine erstaunliche leichte Rüstung! Sehen Sie selbst! Ich biete sie Ihnen im Austausch gegen die Fibel an.\nSie ist übrigens nicht einzigartig. Ihr Seeleute, ihr könnt immer mehr für euch selbst finden und ich kann es nicht. Stimmen Sie jetzt zu?";
			link.l1 = "Heh... Ich nehme an. Gib mir die Rüstung und nimm diese Fibel.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Nein, diese Fibel hat für mich einen viel größeren Preis als diese Rüstung. Ich werde sie für mich behalten.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Hervorragend! Schön, dass wir einen Deal haben. Dies ist nun deine Rüstung. Nimm sie. Bis in einem Monat. Lebewohl.";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Schade.. Wirklich schade. Na ja, nimm es. Ich verurteile dich nicht. Wir sehen uns in einem Monat. Lebewohl.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Du kommst gerade rechtzeitig, "+pchar.name+". Ich habe eine Mission für dich, wenn du bereit bist, sie zu beginnen.";
			link.l1 = "Sicher, ich bin bereit.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Ausgezeichnet! Jetzt, direkt zur Sache. Haben Sie die neuesten Nachrichten gehört?";
			link.l1 = "Hm, was meinst du? Es kommen jeden Tag viele Neuigkeiten.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Es geht alles um unser Geschäft. Es gab die größte Sklavenflucht in der Geschichte der Neuen Welt! Mehr als tausend Seelen sind entkommen und haben in der Zwischenzeit einige Außenposten Hollands zerstört und verbrannt.";
			link.l1 = "Faszinierend. Mach weiter.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Aber sie sind nicht einfach weggelaufen, irgendwie haben sie es geschafft, die Insel zu verlassen! Keine Spuren hinterlassen. Mathias Beck ist empört. Aber das ist nicht der Punkt... Der Punkt ist, dass ich dich bitte, nach Curacao zu segeln, herauszufinden, was dort passiert ist, die Flüchtlinge zu finden und sie zu fangen\nUnd natürlich, um sie vor der gnadenlosen niederländischen Justiz zu retten. Ich zahle 300 Pesos pro Kopf - Ich habe gehört, dass sie sehr gute Sklaven sind.";
			link.l1 = "Verstanden. Ich mache mich auf den Weg nach Curacao. Erwarte mich mit guten Nachrichten.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Weißt du, ich werde die Mission nicht annehmen. Ich werde den Leuten ihre Freiheit nicht nehmen. Sie haben ihr Leben aufs Spiel gesetzt, um sie zu bekommen. Sie haben es verdient.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Wie schade... das hätte ich nicht von dir erwartet... und zu der unpassendsten Zeit. Ich nehme an, es ist dir klar, dass unsere Partnerschaft vorbei ist. Lebewohl.";
			link.l1 = "Hab einen schönen Tag.";
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
				dialog.text = "Ha! Du hast nicht nur deine schwere Mission erfüllt, sondern hast mehr Sklaven mitgebracht, als ich angefordert habe - "+sTemp+" Sklaven. Aber "+sNum+" Sklaven sind nicht von Curacao geflohen. Ich bezahle dir 100 Pesos für einen Kopf. Ich nehme an, das wird für dich funktionieren. Deine Belohnung ist 330 000 Pesos und "+FindRussianMoneyString(iSlaveMoneyH)+" für einen Überschuss, ha-ha.";
				link.l1 = "Ha! Man kann dich definitiv nicht betrügen. Ich stimme zu, was auch immer du sagst, "+npchar.name+"!";
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
				dialog.text = "Sie haben diese heikle Mission auf hervorragende Weise abgeschlossen und mir gebracht "+sTemp+" Sklaven. Deine Belohnung ist "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Mein Dank. Es war ein Vergnügen, Geschäfte mit dir zu machen, "+npchar.name+"!";
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
				dialog.text = "Du hast diese schwere Mission erfolgreich abgeschlossen. Der Preis ist nicht so reich, wie ich erwartet habe, aber ich bin trotzdem zufrieden. Also hast du hierher gebracht "+sTemp+" Sklaven. Ihre Belohnung ist "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Danke. Schön, Geschäfte mit dir zu machen, "+npchar.name+"!";
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
				dialog.text = "Du hast sie gefunden? Hm... was hast du mir gebracht?"+sTemp+" Sklaven? Wo ist der Rest der Fracht? Und versuch mir nicht einmal zu erzählen, dass du sie versenkt hast. Du musst sie an Schmuggler verkauft haben, oder noch schlimmer - an diesen Bastard Lavoisier von Isla-Tesoro. Verschwinde von hier, ich habe keine Lust mehr, mit dir zu arbeiten.";
				link.l1 = "Auf Wiedersehen.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Gefunden? Und was ist mit den Sklaven? Wo ist unsere Ladung? Und versuch mir nicht zu sagen, dass du es versenkt hast. Du musst es an Schmuggler verkauft haben oder noch schlimmer - an diesen Bastard Lavoisier von Isla-Tesoro. Verschwinde von hier, ich habe keine Lust mehr, mit dir zusammenzuarbeiten.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Ich schätze dich wirklich, "+pchar.name+". Wirklich. Kommen Sie in einem Monat wieder her und ich werde ein neues Geschäft vorbereiten, das für uns beide profitabel ist.";
			link.l1 = "Ich bin auch zufrieden mit unserer Partnerschaft, "+npchar.name+". Bis in einem Monat.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Du bist gerade rechtzeitig, "+pchar.name+". Ich suche einen mutigen und skrupellosen Seemann, ha-ha. Bist du bereit, meinen Auftrag zu erledigen?";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Es ist diesmal ganz einfach. Heute ist eine Pinasse '"+pchar.questTemp.Slavetrader.ShipName+"' unter der Flagge von "+NationNameGenitive(sti(npchar.nation))+" hat einen Anker bei "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" Bucht. Es war mit einer großen Ladung 'Ebenholz' beladen, mit Hilfe der lokalen Schmuggler. Zwei Tausend Köpfe, nicht weniger\nKeine Soldaten in der Besatzung und der Kapitän ist ein Händler. Insgesamt überhaupt keine Bedrohung. Entere das Schiff und bring mir die Ladung. 200 Pesos pro Kopf wie üblich.";
			link.l1 = "Hm... Es ist nicht dasselbe wie beim letzten Auftrag. Du schlägst mir vor, ein Schiff deiner eigenen Nation anzugreifen!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Ich verstehe es nicht, "+pchar.name+". Spielt die Schiffsfahne eine Rolle? Kümmert es dich wirklich darum?";
			link.l1 = "Mache ich? Nein, mir ist das scheißegal, Gold hat keine Nationalität. Es war nur ein bisschen unerwartet...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Es ist mir wichtig. Ich möchte nicht haben "+NationNameAblative(sti(npchar.nation))+" unter meinen Feinden.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Bist du ernst? Du machst wohl Witze, man kann heutzutage niemandem mehr vertrauen... In diesem Fall, verschwinde. Und vergiss alles, was du hier gesehen oder gehört hast!";
			link.l1 = "Bis dann,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Warum sind Sie überrascht? Weil es mir egal ist, welche Nationalität die Münzen haben? Ich versichere Ihnen, dass es mir tatsächlich egal ist. Um ehrlich zu sein, ist Patriotismus schlecht für einen professionellen Bankier, es sei denn, er ist bereit, eines Tages pleite zu gehen\nAber genug der Philosophie. Kommen wir zur Sache - das Schiff wird hier bis Mitternacht bleiben, also haben Sie nicht mehr viel Zeit. Sind Sie bereit fortzufahren?";
			link.l1 = "Ja, "+npchar.name+", ich bin auf dem Weg.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Hervorragend. Ich zweifle nicht daran, dass du unsere Mission erfolgreich erfüllen wirst. Viel Glück."+pchar.name+".";
			link.l1 = "Danke! Leb wohl.";
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
		dialog.text = "Nun, "+GetFullName(pchar)+", was ist mit deiner Mission? Dein trostloses Gesicht sagt mir, dass du gescheitert bist.";
			link.l1 = "Du hast verdammt recht... Ich.. Nun... Ich war zu spät dran. Ich war in der Taverne und als ich auslief, war niemand mehr auf dem Meer.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", bitte beruhigen Sie sich. Es ist nicht meine Schuld! Verdammt, ich habe den Bericht zu spät erhalten... Es gab einen Verrat! Einer meiner vertrauenswürdigen Männer hat mich verraten!";
			link.l1 = "Gut, ich sehe, dass du die Wahrheit sprichst. Du hast Glück, dass der Kapitän der Pinasse mir erzählt hat, dass unser 'Geschäft' aufgedeckt wurde. Ich hätte dich schon getötet, wenn er nicht geplaudert hätte. Aber du, verfluchter Geldsack, hast mir die ganze Zeit erzählt, dass du 'diese Stadt besitzt'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "Der Hinterhalt wurde nicht von den örtlichen Behörden organisiert, sonst hätte ich es gewusst... "+pchar.name+", es ist nicht die richtige Zeit für Streitereien. Beide von uns sind in Gefahr, einer meiner ehemaligen Auftragnehmer hat uns hereingelegt\nIch habe herausgefunden, dass alle gesammelten Beweise - ein Paket von Papieren - zu unserem Gouverneur-General transportiert werden. Wenn er sie hat, sind wir erledigt! Du wirst übrigens am meisten leiden.";
			link.l1 = "Jetzt verstehe ich, was dieser Bastard von Kapitän gemeint hat!";
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
			dialog.text = "Hör gut zu. Wir haben immer noch eine Chance. Das Paket wurde auf die Brigantine 'gesendet"+pchar.questTemp.Slavetraderbrig.ShipName+". Das ist das einzige, dessen ich mir sicher bin. Papiere werden zum Gouverneur-General in seine Residenz geliefert "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". Du musst es abfangen, an Bord gehen und diese diskreditierenden Beweise finden.";
			link.l1 = "Haben nicht viel Auswahl hier. Beten Sie für mich, für sich selbst und hoffen Sie, dass ich es fangen kann. Wir werden wieder über all dies sprechen, wenn ich zurück bin. Denken Sie nicht, dass ich es einfach loslassen werde.";
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
			dialog.text = "Dieses Paket zu bekommen ist deine Hauptpriorität! Ich werde mich nicht sicher fühlen, bis du es mir lieferst... Verdammt..."+pchar.name+", sieht so aus, als hätten wir hier ein Problem...";
			link.l1 = "Was ist los?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Verdammt... Ich habe auf dich gezählt, "+pchar.name+". Gut dann. Aber wir werden keine Geschäfte mehr machen. Wenn ich keinen Ermittler bestechen kann, muss ich fliehen. Und ich empfehle dir nicht, hier zu bleiben - Soldaten könnten jederzeit hierher kommen. Lebewohl.";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Sie waren da. Nun, wir können keine Geschäfte mehr zusammen machen, es ist nicht mehr sicher. Lebewohl.";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Ausgezeichnet! Ich hatte keinen Zweifel an dir, "+pchar.name+". Bitte gib mir die Papiere, ich bin zu nervös.";
			link.l1 = "Nimm sie.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Gut... Jetzt bin ich sicher. Der Generalgouverneur wird nichts erfahren und ich habe bereits alle Probleme mit den örtlichen Behörden gelöst, aber es war teuer, sage ich dir.";
			link.l1 = "Klingt gut, aber denkst du nicht, dass du mir für meine Unannehmlichkeiten aufgrund deiner unüberlegten Handlungen entschädigen musst?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Sicher, "+pchar.name+". Noch mehr, ich schulde dir viel. Und ich erwarte wirklich, unser Geschäft fortzusetzen. Aber ich bitte dich, mich zu verstehen - ich habe eine riesige Summe ausgegeben - die Loyalität des Gouverneurs und des Kommandanten kostet viel. Und ich musste mich mit diesem Mord an der ganzen Patrouille in meiner Bank auseinandersetzen...";
			link.l1 = "Du meinst, dass du meine Kosten nicht erstatten wirst?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Sei nicht so hart, "+pchar.name+". Ich habe wirklich Schwierigkeiten mit Geld jetzt, also biete ich Ihnen eine andere Art der Bezahlung an.";
			link.l1 = "Ich höre dir dann zu.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Mein Gefährte und ich wurden vor einem Jahr nahe der südlichen Küsten von Main von einem Sturm erwischt. Unsere Schiffe wurden an die Felsen der Küste von Boca de la Serpienta geworfen, obwohl sie bald sanken, konnten wir unsere Ladung an Land ziehen. Kisten gefüllt mit Edelsteinen und Schmuck. Die Bucht schien ziemlich gemütlich zu sein, also versteckten wir ohne Probleme Schätze\nAber am nächsten Morgen, sobald der Sturm vorbei war, wurden wir von den Indianern angegriffen. So starb die Mehrheit der Überlebenden, einschließlich meines Gefährten. Ich und einige Seefahrer konnten auf einem Langboot entkommen\nWir erreichten sicher Cumana, doch ich wagte es nicht, wegen der Schätze zurückzukehren. Ich bin sicher, dass die einheimischen Wilden immer noch ihre Küste ebenso wie meine Kisten schützen. Aber du kannst mit diesem Haufen Rothäute fertig werden\nDer Schmuck, den du dort findest, reicht aus, um all deine Ausgaben zu decken, einschließlich einer Expedition in den südlichen Main.";
			link.l1 = "Hm ... gut. Dann gehe ich nach Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Du kannst zuversichtlich sein, "+pchar.name+", dass alles, was ich gesagt habe, die Wahrheit war. Ich erwarte dich in einem Monat. Ich habe bereits eine weitere Geschäftsidee im Kopf und wie ich mein ins Wanken geratenes Geschäft unterstützen sollte. Lebewohl.";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "Und hier bist du, "+pchar.name+". Schön, du bist wie immer genau zur rechten Zeit da. Ich möchte dir mehr Informationen über den karibischen Sklavenmarkt geben, bevor ich dir eine nächste Mission gebe. Weißt du, was das Wort 'repartimiento' bedeutet?";
			link.l1 = "Hm, nein, "+npchar.name+", ich weiß es nicht. Aber ich vermute, es geht darum, jemandem etwas wegzunehmen. Liege ich richtig?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Du überraschst mich. Was hast du von mir erwartet? Geh weg!";
			link.l1 = "Ein illegales Geschäft ist zu hart für meine Moral. Besonders der Sklavenhandel.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Du hast es fast geschafft,"+pchar.name+". Jemandem die Freiheit zu nehmen. Repartimiento ist eine heikle und legale Art, einheimische Indianer zu versklaven. Sozusagen. Spanische Behörden wenden es gegen die einheimischen Menschen von Main an. Möchten Sie mehr darüber erfahren?";
			link.l1 = "Warum nicht?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Vertreter der spanischen Krone besuchen indische Siedlungen. Mit zynischer Täuschung und direkten Drohungen zwingen sie die Indianer, allerlei Müll wie verfaultes Fleisch und alte Rasierer zu fantastischen Preisen zu kaufen. Auf Kredit\nEinige Zeit später, sagen wir ein Jahr, kehren die Vertreter zurück und fordern eine Zahlung. Wenn die Indianer nicht zahlen können, was meistens der Fall ist, nehmen die Spanier einen Teil ihrer arbeitsfähigen Männer mit, angeblich für eine Weile und um 'ihnen beizubringen, wie man Land bewirtschaftet'\nWie du verstehst, kehren sie nie zurück zu ihren Siedlungen. So kommen unsere gutgläubigen Rothäute zu Zuckerplantagen und Redwood-Fabriken.";
			link.l1 = "Verdammt... wirklich... Was machen die Indianer dagegen? Wehren sie sich, wenn die Spanier sie versklaven? Oder verstehen sie einfach nicht, was vor sich geht?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Ich nehme an, dass sie es immer kommen sehen, aber nur wenige wagen es, offen Widerstand zu leisten, besonders wenn die Spanier ein Papier mit dem Fingerabdruck des Häuptlings zeigen. Sicher, solche Taktiken werden normalerweise auf friedliche Stämme wie Arawaks oder Miskitos angewendet. Ein solcher Trick wird bei kriegerischen Itza oder Akawoys nicht funktionieren\nNun, lass uns über deine Mission sprechen.";
			link.l1 = "Ich rieche schon den Duft von vielen Münzen! Ich höre dir zu, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Bald wird ein schwerer Galeone aus Caracas auslaufen. Er heißt "+pchar.questTemp.Slavetrader.ShipName+". Es enthält eine riesige Menge an Sklaven - etwa 3000 Männer - Indianer von Orinoco, gefangen genommen gemäß der Repartimientos-Politik. Die Galeone segelt nach Santiago, die Zuckerplantagen von Kuba brauchen viele Arbeiter. Du musst die Galeone mit ihrer Ladung erobern. Ich würde mindestens zwei Schiffe mitnehmen, wenn ich du wäre, sie sagen, dass die Galeone die beste ihrer Art ist. Die Bezahlung bleibt wie gewohnt - 200 Pesos pro Kopf. ";
			link.l1 = "Heh! Klingt gut. Ich stimme zu.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Du weißt, dass ich diese Repartimiento von dir nicht mag. Es ist zu zynisch. Ich werde das nicht tun.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Ich wünsche Ihnen dann viel Glück. Wissen Sie, dass der Kapitän dieser Galeone ein sehr erfahrener und geschickter Kriegsseemann ist. Es wird kein leichter Kampf sein, also bereiten Sie sich vor. Vergeuden Sie keine Zeit, er braucht fünfzehn oder zwanzig Tage, um anzukommen "+sTemp+" Santiago. Versuchen Sie es nicht zu verpassen, obwohl diese Galeone wirklich schwer zu übersehen ist\nJa! Fast vergessen! Es gibt jede Menge indianischer Trinkets auf dem Schiff, die Rothäute begleichen ihre Schulden oft mit ihren Kultgegenständen und Handwerk. Bringen Sie mir alles Besondere, was Sie finden könnten, ich werde Ihnen viel für jeden wertvollen Gegenstand zahlen, den Sie bringen.";
			link.l1 = "Ich verstehe.";
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
			dialog.text = "Nun, "+pchar.name+", es war meine letzte Hoffnung... Deshalb habe ich Ihnen diesen Job angeboten. Niemand außer Ihnen kann das... und ich sehe, dass Sie auch nicht dazu in der Lage sind. Lassen Sie uns dann Abschied nehmen. Nach dem letzten Misserfolg und all diesen Gerüchten sind alle meine Kunden weg. Und ich bin fast bankrott, vielleicht muss ich diese Stadt verlassen. Ich mache Ihnen keine Vorwürfe - dieser Job war zu hart. Eh... Lebewohl,"+pchar.name+".";
			link.l1 = "Es tut mir so leid, "+npchar.name+", das ging zu weit. Es tut mir wirklich leid. Vielleicht beruhigt sich alles wieder. Auf Wiedersehen.";
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
				dialog.text = "Puh, jetzt geht es mir besser... Ich habe richtig gemacht, dir zu vertrauen... Woher kommt diese Ironie? Was ist los?";
				link.l1 = "Lieber Herr, es war kein Galeone... oder eine sehr große Galeone... Verdammt! Es war ein Linienschiff! Und du hast mich nicht einmal gewarnt! Aber ich habe es geschafft, sie zu entern. Ich habe "+sTemp+" Sklaven und ich bin bereit, sie an dich zu übergeben. Gemäß unserem Abkommen schuldest du mir - "+FindRussianMoneyString(iSlaveMoney)+". Es wäre großartig, eine Entschädigung für Ihre Fehlinformationen zu erhalten.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Hast du die Galeone gefunden? Und was ist mit den Sklaven? Es sollen dreitausend von ihnen sein und nicht weniger! Verdammt, jeder ist eine Ratte und ein Verräter! Das habe ich von dir nicht erwartet... du warst meine letzte Hoffnung\nSehr gut... ich schwöre, ich werde jeden letzten Taler ausgeben, um dich zu vernichten, dich zu töten! Die ganze Flotte von "+NationNameGenitive(sti(npchar.nation))+" wird dich jagen! Verschwinde von hier!";
				link.l1 = "Nun...";
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
			dialog.text = "So sagt man das! Ich schwöre, ich hatte keine Ahnung. Eine schwere Galeone sollte segeln, nicht ein verdammt großes Kriegsschiff! Es scheint, dass sie ihre Pläne im letzten Moment geändert haben... Aber dennoch hast du Erfolg gehabt!\nIch stimme dir voll und ganz zu über das Geld und die Erstattung deiner Ausgaben, das Problem ist, dass ich gerade nicht so eine Summe besitze. Du weißt über meine jüngsten Probleme... Aber werde nicht wütend, "+pchar.name+", um Gottes willen. Du gibst mir die Ladung und ich verkaufe sie, mein Kunde wartet bereits\nIch werde die ganze Summe in fünf Tagen haben, also wirst du bekommen, was du verdienst. Du kannst dich auf mich verlassen. Hier, nimm all das Bargeld, das ich gerade habe.";
			link.l1 = "Hm... Ich hatte erwartet, das Geld jetzt zu bekommen. Ich wünschte, du wüsstest, durch was für einen Kampf ich gehen musste! Ach, was auch immer... Ich werde mit dir sympathisieren. Aber behalte im Kopf, dass wenn du versuchst, mich zu betrügen, ich dich sogar in Europa finden werde!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Du weißt, "+npchar.name+", zum Teufel mit dir! Es war kein Deal. Du kannst dir gar nicht vorstellen, was für einen Kampf ich durchstehen musste. Ich nehme alle Sklaven für mich und verkaufe sie ohne deine Vermittlung.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Also, jetzt sprichst du! Sieht aus wie nichtsahnend "+npchar.name+" war nur eine Kuh zum Melken, eine einfache Verzögerung reicht aus, damit du mich über den Tisch ziehst und eine eigene Operation startest. Es scheint, dass du vergessen hast, dass ich derjenige war, der dir den Job und den Tipp über die Beute gegeben hat\nSehr gut... Ich schwöre, ich werde jeden Münze, die ich noch habe, darauf verwenden, dich zu zerstören, dich zu töten! Die gesamte Flotte von "+NationNameGenitive(sti(npchar.nation))+" wird dich jagen! Verschwinde aus meinen Augen!";
			link.l1 = "Versuche nicht, mich mit einer leeren Geldtruhe zu erschrecken. Ich werde all deine Flotten versenken und die Krabben damit füttern.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Danke für Ihr Verständnis, "+pchar.name+". Ich verspreche, dass alles gut wird, keine Notwendigkeit für deine Drohungen\nNimm das als Vorschuss. Fünfzehn Kisten. Fünf davon werden als Entschädigung für moralischen Schaden dienen. Komm in fünf Tagen zu mir, um den Rest zu bekommen.\nVergiss nicht, alle indischen Gegenstände mitzubringen, die du auf dem Schiff gefunden hast... wenn du sie überhaupt gefunden hast, natürlich. Ich habe sowieso nichts, um dich für sie zu bezahlen.";
			link.l1 = "In fünf Tagen,"+npchar.name+". In fünf Tagen...";
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
			dialog.text = "Wie ich versprochen habe, "+pchar.name+", ich bin bereit, Ihnen zu zahlen. Sklaven werden verkauft, der Kunde ist glücklich und wir auch. Nach Abzug eines Vorschusses ist Ihre Belohnung"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". Bitte nehmen Sie Ihr Geld.";
			link.l1 = "Prächtig, "+npchar.name+". Es ist gut, mit einem Mann zu verhandeln, der sein Wort halten kann...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Du kannst dich immer auf mein Wort verlassen, "+pchar.name+". Ich habe dir nie einen Grund gegeben, an mir zu zweifeln. Partner müssen ehrlich zueinander sein, das ist das Geheimnis des Geschäfts\nLass uns jetzt über indische Artefakte sprechen. Zeig mir, was du hast, lass einen Sammler wie mich nicht warten.";
			link.l1 = "Hm... Schau mal.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Ja! Ausgezeichnet! Ein goldenes Ritualmesser! Das ist eine seltene Sache. Ich wollte schon immer so etwas in meiner Sammlung haben. Ich biete Ihnen 30 000 dafür oder ein 'Ehecatl' Amulett im Austausch. Ich habe sowieso zwei davon.";
				link.l1 = "Ich würde Geld nehmen.";
				link.l1.go = "BG_money";
				link.l2 = "Ich würde im Austausch ein Amulett von 'Ehecatl' nehmen.";
				link.l2.go = "BG_change";
				link.l3 = "Ich sollte dieses Messer besser bei mir behalten.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Lassen Sie uns sehen.. Leider haben Sie nichts Interessantes für mich.";
				link.l1 = "Was auch immer du sagst.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Prächtig. Nimm deine 30 000 und dieses indische Messer gehört jetzt mir.";
			link.l1 = "Gut. Und ist das alles, woran du interessiert bist...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Prächtig! Hier ist dein Amulett und dieses indische Messer gehört jetzt mir.";
			link.l1 = "Gut. Und ist das alles, woran Sie interessiert sind...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Was auch immer. Aber es ist trotzdem so schade...";
			link.l1 = "Gut. Und ist das alles, woran Sie interessiert sind...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Warte! Lass mich noch einmal nachsehen...";
			link.l1 = "Sicher. Komm schau dir an und wähle was du willst.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Das! Und ich habe es zuerst gar nicht bemerkt. Ich interessiere mich für diesen Knochen mit einem Ring aus Kupfer. So eine interessante Sache, sage ich dir... Ich kann dir 20 000 Pesos zahlen oder dir einen 'Cimaruta'-Amulett im Austausch geben.";
				link.l1 = "Ich würde Geld nehmen.";
				link.l1.go = "PF_money";
				link.l2 = "Ich würde einen 'Cimaruta' Amulett im Austausch nehmen.";
				link.l2.go = "PF_change";
				link.l3 = "Ich würde dieses Artefakt bei mir behalten.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Nein... du hast hier sonst nichts von Interesse.";
				link.l1 = "Wie auch immer!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Ausgezeichnet! Hier sind Ihre 20 000 Pesos und dieser Knochen gehört jetzt mir.";
			link.l1 = "Schön. Ich fühle mich gut bei unserem Handel.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Prächtig! Hier ist dein Amulett und dieser Knochen gehört jetzt mir.";
			link.l1 = "Schön. Ich fühle mich gut bei unserem Handel.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Was auch immer. Aber es ist so schade...";
			link.l1 = "Ich brauche diesen Knochen für mich selbst, es tut mir so leid.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Nun... durch das Entern der Galeone, oh ich bitte um Verzeihung, des Linienschiffes hast du mich gerettet. Ich schätze unsere Partnerschaft sehr, "+pchar.name+". Du bist mein bester Agent.";
			link.l1 = "Ich fühle mich geschmeichelt. Sie überschätzen meine Errungenschaften...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Ich bin völlig ernst. Und ich werde dich bitten, eine weitere Mission zu erfüllen, aufgrund deiner außergewöhnlichen Fähigkeiten und weil ich dir vertraue.";
			link.l1 = "Heh! Überraschend! Ich höre zu. Wo ist eine andere Galeone mit Salben?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Es geht diesmal nicht um Sklaven. Überrascht? Ich werde dich gut für die Mission bezahlen... Sehr gut.";
			link.l1 = "Gehen wir direkt zum Geschäft.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Dieses Geschäft ist mit den jüngsten Ereignissen verbunden, an denen auch du teilgenommen hast... Also, wie du vielleicht weißt, betreibe ich ein ziemlich illegales Geschäft - den Sklavenhandel. Du weißt vielleicht auch, dass ich Freibeuter wie dich für alle Arten von Aufgaben einstelle\nEiner meiner Leute hat mich vor nicht allzu langer Zeit aus unbekannten Gründen verraten. Er sammelte Beweise und erstattete Bericht bei den Behörden. Du hattest das Vergnügen, die Konsequenzen mit eigenen Augen zu sehen. Ein Schiff mit Soldaten ist hier angekommen... du weißt den Rest\nEs hat mich einiges an Mühe gekostet, die Situation zu klären. Wie du sicher verstehst, kann ich diesen Verrat nicht unbeantwortet lassen. Außerdem kann ich nicht ruhig leben und arbeiten, wenn ich weiß, dass die Ratte noch lebt. Ich habe Kopfgeldjäger geschickt, aber es gibt noch kein Ergebnis\nIch bitte dich, dich persönlich um diese Angelegenheit zu kümmern. Umso mehr, als seine Handlungen auch dich betroffen haben.";
			link.l1 = "Hm... dieser Schurke muss am Rahbaum aufgehängt werden! Erzähl mir mehr über ihn und natürlich über meine Bezahlung für den Job.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Mach dir keine Sorgen darum. Ich werde viel für seine Beseitigung bezahlen und ich spreche nicht nur von Geld. Ich werde die besten Stücke meiner Sammlung nicht verschonen. Lass uns über den Mann sprechen. Sein Name ist Francois Gontier\nEr weiß von meiner Jagd, also hat er seine Fregatte verkauft, um seine Spuren zu verbergen. Meine Kollegen haben mir gesagt, dass er in Panama gesehen wurde. Ich glaube, du solltest deine Suche dort beginnen.";
			link.l1 = "Nun, ich bin dann auf meinem Weg.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Ich wünsche Ihnen dann viel Glück. Wissen Sie, dass dieser Gontier ein sehr erfahrener Seemann ist und er hat eine Crew von rücksichtslosen Halsabschneidern. Er hat nichts zu verlieren, also wird er auf eine sehr verzweifelte Art und Weise kämpfen.";
			link.l1 = "Ich habe keine Angst vor Leuten wie ihm, aber ich werde überlegen, was du gesagt hast. Lebewohl, und sei dir sicher, dass ich ihn sogar in der Hölle erwischen werde.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Prächtig! Jetzt kann er seine Berichte an die Quallen schreiben. Niemand wagt es, sich mit mir anzulegen. Mein Dank an dich, "+pchar.name+", du bist ein unverzichtbarer Mann.";
			link.l1 = "Danke, "+npchar.name+", für eine so positive Bewertung meiner Taten. Was ist mit meiner Bezahlung?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Sicher. Ich würde den richtigen Preis für eine so schwere Arbeit zahlen. Zuerst präsentiere ich Ihnen dieses ausgezeichnete Fernglas.";
			link.l1 = "Wahnsinn, was für ein Geschenk!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Außerdem sind hier 100 000 Pesos als Ihre primäre Zahlung und 50 000 als Ausgleich für Ihre eigenen Kosten.";
			link.l1 = "Danke, "+npchar.name+". Ich sage es noch einmal, es ist ein echtes Vergnügen, mit dir zu handeln.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Ich werde wie immer in einem Monat auf dich warten. Es ist ein sehr großes Geschäft auf der Reihe und du wirst eine gut ausgestattete Staffel brauchen. Ich bitte dich, das zu verstehen und dich gut vorzubereiten. Wenn mein Plan funktioniert, werden wir reich sein.";
			link.l1 = "Gut,"+npchar.name+". Ich komme zurück, wenn ich bereit bin.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Schade, was für eine Schande... Nun, ärgere dich nicht, du bist nicht der erste Mann, den dieser Abschaum getäuscht hat. Eines Tages werde ich ihn zur Strecke bringen\nKomm in einem Monat zu mir. Das wird groß, also sammle ein gut ausgestattetes und bewaffnetes Geschwader. Bitte nimm das ernst und tu dein Bestes zur Vorbereitung. Wenn mein Plan funktioniert, werden wir reich sein.";
			link.l1 = "Gut, "+npchar.name+". Ich komme zurück, wenn ich bereit bin.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Du bist gerade rechtzeitig, "+pchar.name+"! Ich war kurz davor, mir Sorgen zu machen, ich wollte einen Mann losschicken, um dich zu finden\nLass uns anfangen! Deine Mission ist jetzt wirklich groß und riskant, aber die Belohnung ist angemessen. Du wirst mehr als eine Million Pesos erhalten, nachdem die Arbeit erledigt ist.";
			link.l1 = "Jetzt reden wir! Ich höre zu, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Die versklavten Indianer wurden in kleinen Gruppen aus dem gesamten Main nach Havanna gebracht, auch kamen einige Galeonen aus Afrika und wurden entladen. Mittlerweile befinden sich fast fünftausend Sklaven hinter den hohen Mauern der Festung von Havanna.";
			link.l1 = "Ich habe das Gefühl, dass es bei dem Geschäft darum geht, Havanna zu stürmen.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Du hast ein richtiges Gefühl, "+pchar.name+". Das ist genau das, was ich Sie bitten möchte zu tun. Sie und nur Sie. Ich bezweifle, dass irgendeiner meiner Agenten dazu in der Lage ist\nGlauben Sie, dass Sie dabei sind?";
			link.l1 = "Um ehrlich zu sein, "+npchar.name+", Ich bin ein bisschen verblüfft. Ich hatte keine Ahnung, dass deine Aktivität so... groß angelegt ist. Sicher, ich bin dabei. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Weißt du was, "+npchar.name+", das geht zu weit. Ich habe genug von deinen Überraschungen. Das nächste Mal wird deine Gier mich dazu bringen, einen Krieg gegen Spanien zu erklären und ich müsste ganz alleine gegen sie kämpfen. Wenn du wirklich diese Sklaven brauchst, dann stürme doch selbst Havanna.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Hätte das nicht von dir erwartet... Verdammt, was soll ich bloß meinem Kunden sagen? Gut. Es ist deine Entscheidung und ich muss einen neuen Partner finden. Leb wohl, "+pchar.name+". Und ich werde Ihre Dienste in der Zukunft nicht nutzen. Denken Sie daran, dass Sie den Deal fallen gelassen haben, der Ihre Nachkommen bis zur siebten Generation reich machen könnte.";
			link.l1 = "Du kannst nicht alles Geld der Welt bekommen, und du beißt mehr ab, als du kauen kannst. Lebewohl, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Ich wusste, dass du zustimmen würdest. Jetzt hör dir die Details an. Das Fort von Havanna war schon immer ein hartes Ziel, aber jetzt ist es noch härter\nZwei Linienschiffe bewachen die Küsten von Kuba und du musst dich zuerst mit ihnen auseinandersetzen, bevor du das Fort stürmst...";
			link.l1 = "Ich verstehe. Es wird nicht das erste Mal sein, dass ich Linienschiffe bekämpfe, ha-ha. Wie viel Zeit habe ich?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Nicht viel. Höchstens drei Wochen, danach werden die Sklaven zu den spanischen Außenposten in Kuba verlegt. Du musst dich beeilen. ";
			link.l1 = "Lassen wir dann keine Zeit verschwenden. Ich bin auf dem Weg!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Einen Moment!"+pchar.name+", du und ich hatten nie irgendwelche Missverständnisse und Meinungsverschiedenheiten. Trotzdem möchte ich, dass du weißt, was hier vor sich geht. Ich zähle auf dich, und der Kunde zählt auf mich\nWir haben viel Aufwand und Geld in diese Operation gesteckt. Jeder einzelne Sklave, alle fünftausend müssen mir ausgeliefert werden\nAndernfalls werden wir sehr radikale Maßnahmen gegen dich ergreifen. Nichts für ungut, dies ist nur eine Warnung. ";
			link.l1 = "Mach dir keine Sorgen, "+npchar.name+", Ich verstehe, was Geschäft bedeutet, deshalb solltest du auch daran denken, mich zu bezahlen, sobald ich sie abliefer. Lebewohl.";
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
				dialog.text = "Nun.. Und was ist mit dem Preis deines Sieges?";
				link.l1 = "Ich habe "+sTemp+" Sklaven.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Nun, nun. Hast du vergessen, was ich gesagt habe? Du musstest mir hier nicht weniger als fünftausend Sklaven bringen und du hast "+sTemp+". Warum ist das so?";
				link.l1 = "Hmm.. Ein Teil von ihnen hat den Weg von Havanna nicht überlebt... Essen und Medikamente gingen zur Neige.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "So-so... Willst du mich betrügen? Hast du vergessen, was ich gesagt habe? Wo sind meine Sklaven, frage ich dich! Wo sind sie?!";
			link.l1 = "Hm.. Nun, du siehst...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Gut. Ich brauche deine Erklärungen nicht. Wir hatten einen Deal und ich gebe dir eine Woche Zeit, um nicht weniger als fünftausend Sklaven zu beschaffen. Andernfalls wirst du viele Probleme haben.";
			link.l1 = "Gut, gut, beruhige dich nur, ich werde sie für dich holen.";
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
			dialog.text = "Prächtig! Du hast meine Aufgabe wie immer erfüllt. Ich bin sehr zufrieden mit dir.";
			link.l1 = "So bin ich... Aber ich wäre noch zufriedener, wenn ich mein Geld für die Fracht erhalten würde.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Ich bin sehr froh darüber. Du warst spät dran, aber du hast meine Aufgabe auf hervorragende Weise erledigt.";
			link.l1 = "Und nun möchte ich Geld für die Fracht bekommen.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Sicher. Ich werde die Sklaven an meinen Kunden verkaufen, er wird bezahlen und ihr bekommt eure Münzen. Genau wie beim letzten Mal. Mal sehen, ihr habt hierher gebracht "+sTemp+" Sklaven. Die Summe beträgt "+FindRussianMoneyString(iSlaveMoney)+". Komm in einer Woche wegen der Bezahlung hierher.";
			link.l1 = "Gut, "+npchar.name+", wir haben einen Deal. Ich werde in einer Woche hier sein. Aber sei sehr vorsichtig...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", bitte, tue das nicht. Wir sind Partner und es ist kein Platz für Betrug und Misstrauen zwischen uns. Ich habe dir viele Münzen versprochen und du hast sie bekommen. Ich habe dir interessante Aufgaben versprochen und du hast sie auch bekommen. Ich habe immer deine Kosten ausgeglichen, sogar in den dunkelsten Tagen für mein Geschäft. Habe ich nicht immer mein Wort gehalten?";
			link.l1 = "Hmm... Nein... Ich möchte nur bezahlt werden, das ist alles.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Sieh jetzt..."+pchar.name+", du bist der beste Agent von mir und ich zähle darauf, in der Zukunft wieder Geschäfte mit dir zu machen. ";
			link.l1 = "Gut, "+npchar.name+". Aber Sie müssen mich auch verstehen - eine Million Pesos ist eine riesige Summe.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Ich verstehe Sie sehr gut, aber ich muss zuerst die Sklaven verkaufen und erst dann bekomme ich Geld.";
			link.l1 = "Gut. Ich denke, wir haben uns verstanden.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Prächtig. Bis in einer Woche. Und jetzt muss ich mich vorbereiten und losfahren, um mit meinem Kunden zu handeln.";
			link.l1 = "Ich werde dich dann nicht stören. Bis in einer Woche, "+npchar.name+".";
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
			dialog.text = "Wo bin ich hier? Nun... das ist meine Bank. Ich habe sie vor zwei Tagen gekauft. Du bist mein erster Kunde und ich kann dir sehr verlockende Kreditkonditionen anbieten...";
			link.l1 = "Verdammt sei das Gold! Wo ist "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Beruhige dich bitte! Er ist schon vor langer Zeit weggelaufen.";
			link.l1 = "Wie?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Weißt du das nicht? Er ist vor einer Woche verschwunden. Es stellte sich heraus, dass er alle Investitionen seiner Kunden genommen hat. Sie sagen, dass sogar der Gouverneur gelitten hat. Dieses Haus blieb übrig und ich kaufte es von der Kolonie.";
			link.l1 = "Verschwunden? Wie?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Ich habe gehört, dass er aus unserer Kolonie geflohen ist... Schuldet er dir auch etwas? Viel?";
			link.l1 = "Mehr als eine Million! Aber ich werde diese Ratte sowieso bekommen! Wo ist er hin? Name seines Schiffes?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Niemand ist sich bewusst. Wirklich. Er ist einfach verschwunden. Das Schiff namens 'Mauritius' oder 'Maurdius' hatte an diesem Tag abgelegt, vielleicht hat er es zur Flucht genutzt.";
			link.l1 = "Verdammt! Und ich habe diesem Bastard vertraut! Er roch vom ersten Tag an nach Verrat! Und ich war dumm genug zu glauben, dass wir echte Partner sind! Aber ich werde ihm eines Tages bereuen lassen... Also gut,"+npchar.name+", Ich entschuldige mich für mein Verhalten... Wenn du ein guter Mann bist, werde ich in Zukunft mit dir handeln, dessen sei sicher, aber für jetzt, auf Wiedersehen.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Es ist in Ordnung. Ich verstehe. Wenn du etwas Geld brauchst oder investieren möchtest, stehe ich immer zu deinem Dienst.";
			link.l1 = "Danke. Aber ich behalte mein Geld lieber bei mir. Auf Wiedersehen.";
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
			dialog.text = "Ach wirklich? Es scheint, dass er nicht selbst mit mir reden will.... Gut, dann diskutieren wir die Angelegenheit mit dir. "+pchar.GenQuest.Noblelombard.Name+" schuldet mir "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" und auch mein Interesse - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" seit drei Monaten. Wenn ich das Geld nicht im nächsten Tag sehe, dann werde ich sein Relikt verkaufen und es ist mir egal, was es ihm wert ist. Geschäft ist Geschäft.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Prächtig! In diesem Fall werde ich Ihnen sofort die gesamte Summe mit allen Zinsen zahlen - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Er wird seine Reliquie selbst nehmen. Hier ist dein Geld.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Mein Kunde wird das Geld in drei Monaten haben. Lass uns einen Deal machen, ich werde dir die Zinsen für die letzten drei Monate und für die nächsten drei Monate bezahlen."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". Und die Schuld selbst wird Ihnen später bezahlt.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Mein Klient wird in drei Monaten Geld haben. Wie wäre es, wenn ich Ihnen die Zinsen für die letzten drei Monate zahle und Sie warten, bis mein Klient genug Geld hat?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Dieses Kleinod kostet ein Vermögen! Es sieht so aus, als müsste mein Kunde es selbst bezahlen.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Ausgezeichnet! Alles lief gut, ich habe mein Geld und "+pchar.GenQuest.Noblelombard.Name+" wird sein Relikt zurückbekommen.";
			link.l1 = "Schön, Geschäfte mit Ihnen zu machen, "+npchar.name+"! Lebewohl jetzt.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm.. Gut. Das passt für mich. Aber wenn "+pchar.GenQuest.Noblelombard.Name+" findet in drei Monaten kein Geld, dann werde ich keine Verzögerung mehr machen. Stell sicher, dass er das weiß.";
				link.l1 = "Ich werde! Ich bin froh, dass wir einen Deal gemacht haben. Leb wohl jetzt.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "Nein. Das wird nicht funktionieren. Ich brauche den gesamten Betrag und das vor Sonnenuntergang. Stelle sicher, dass dein 'Kunde' das weiß. Ich habe dir nichts mehr zu sagen.";
				link.l1 = "Hm... gut. Schade, dass du nicht kompromissbereit bist.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm.. Gut. Ich akzeptiere es nur wegen meiner Achtung vor Ihrem Kunden. Aber wenn "+pchar.GenQuest.Noblelombard.Name+" findet in drei Monaten kein Geld, dann werde ich keine Verzögerung mehr machen. Stellen Sie sicher, dass er das weiß.";
				link.l1 = "Ich werde! Ich bin froh, dass wir einen Deal hatten. Lebewohl jetzt.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Nein. Das wird nicht funktionieren. Ich brauche die gesamte Summe und das vor Sonnenuntergang. Stellen Sie sicher, dass Ihr 'Kunde' das weiß. Ich habe Ihnen nichts mehr zu sagen.";
				link.l1 = "Hm... gut. Schade, dass du keinen Kompromiss eingehen willst.";
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
				dialog.text = "Das sagst du nicht! "+pchar.GenQuest.Noblelombard.Name+" hat kein Depot auf deinen Namen eröffnet. Er ist nicht einmal in unserer Kolonie - segelte weg nach Europa. Ich sage dir, dass ich noch nie einen so unehrlichen Mann gesehen habe. Er wollte mich betrügen, aber scheiterte - ich habe meine eigenen Tricks...";
				link.l1 = "Drecksack! Er hat mir sein Wort gegeben....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Richtig. "+pchar.GenQuest.Noblelombard.Name+" hat eine Einzahlung auf Ihren Namen gemacht. Bitte, nehmen Sie es...";
				link.l1 = "Herrlich! Lebewohl, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Für Leute wie uns gibt es so etwas nicht "+pchar.GenQuest.Noblelombard.Name+" weil sie keine Ehre und kein Gewissen haben. Ich nehme an, dass er dich betrogen hat?";
			link.l1 = "Er hat, nehme ich an. Was auch immer, "+npchar.name+", Ich werde auch nicht lange hier bleiben und Europa ist klein... Vielleicht treffen wir uns eines Tages. Lebewohl!";
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
			dialog.text = "Herr, ich kenne Sie nicht. Ich verleihe Geld nur an die Einheimischen oder an die Kapitäne. Entschuldigen Sie mich bitte...";
			link.l1 = "Ich verstehe. Schade aber.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "Wh-was... Was meinst du?";
			link.l1 = "Du bist eine verdammte Ratte! Jetzt hör mir gut zu: Ich bin nicht so dumm. Pinette hat zwei Kopien des Briefes geschrieben. Ich habe dir eine davon gegeben, die zweite hat mein vertrauenswürdiger Agent. Wenn mir etwas passiert - wird mein Kerl ihn direkt in die Hände des Gouverneurs liefern...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Also schlage ich vor, dass du jeden Morgen in der Kirche für meine gute Gesundheit betest, anstatt Attentäter auf mein Leben zu hetzen. Eine letzte Warnung! Mache einen Zug gegen mich und du bist gefickt. Kapiert? Gut. Atme tief durch und zähle weiter deine Dublonen.";
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
			dialog.text = "Ich will nicht mit dir reden.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Natürlich! Viele wollen einfach nur ihr Geld und verschwinden. Besonders bei den jüngsten Gerüchten...";
			link.l1 = "Welche Gerüchte?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "Man sagt, die Bedingungen in der Mannschaft verschlechtern sich. Monsieur Blackwood soll sogar regelmäßige Verluste in Kauf nehmen - was früher nie vorkam. Aber das geht mich nichts an. Ich verkaufe nur. Also, was interessiert Sie?";
			link.l1 = "Kommen wir zur Sache.";
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
