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
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Der Alarm wurde in der Stadt ausgelöst, und jeder sucht nach dir. Wenn ich du wäre, würde ich dort nicht bleiben.","Alle Stadtwachen durchkämmen die Stadt auf der Suche nach dir. Ich bin kein Narr und werde nicht mit dir reden!","Lauf, "+GetSexPhrase("Kumpel","lass")+", bevor die Soldaten dich in ein Sieb verwandeln..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Schurke")+"?! Die Stadtwachen haben schon deine Witterung aufgenommen, du wirst nicht weit kommen, "+GetSexPhrase("schmutziger Pirat","mörderischer Dreck")+"!","Dreckiger Mörder, verlasse sofort mein Haus! Wachen!","Ich fürchte dich nicht, "+GetSexPhrase("Schleicher","Stinker")+"! Bald wirst du in unserem Fort gehängt, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich nie ein Problem...","Sie werden mich nie kriegen."),RandPhraseSimple("Halt verdammt nochmal dein Maul, "+GetWorkTypeOfMan(npchar,"")+", oder ich reiß dir deine verdammte Zunge raus!!","Heh, "+GetWorkTypeOfMan(npchar,"")+", und jeder hier - sie sind alle da, um Piraten zu fangen! Hier ist, was ich dir sagen werde, Kumpel: sitz ruhig und du wirst nicht sterben..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("He, Mistkerl! Denkst du, du kannst einfach nehmen, was du willst? Sicherlich nicht! Leute! Zu den Waffen! Schneidet den Verrückten!","Wenn du etwas willst, kauf es, du Biest! Jetzt zeige ich dir, wo der Hammer hängt! Jungs, holt eure Waffen! Alarm!");
				link.l1 = RandPhraseSimple("Hä? Was?","Äh, warum tust du das?");
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
					link.l13 = "Ich möchte eine Charge europäischen Weins von Ihnen kaufen - fünfzig-sechzig Flaschen. Mir wurde gesagt, dass Sie genug davon auf Lager haben."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Hallo nochmal. Bitte schauen Sie sich diesen Brief an - vielleicht überdenken Sie Ihre Position bezüglich des Weinverkaufs an mich?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Es bin wieder ich. Können wir unseren unterbrochenen Weinhandel fortsetzen? Ich habe es geschafft, genug Geld aufzutreiben."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Wollten Sie etwas kaufen, Monsieur?";
				Link.l1 = "Natürlich habe ich - wofür sind sonst die Läden da? Zeig mir deine Waren.";
				Link.l1.go = "trade_1";
				Link.l2 = "Ich komme für einen bestimmten geschäftlichen Zweck...";
				Link.l2.go = "quests";
				Link.l3 = "Es tut mir leid, aber ich muss gehen.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Hören Sie, Monsieur, ich suche eine Arbeit. Nicht so eine Vollzeitbeschäftigung oder das Schleppen von Fracht, sondern eher Botengänge, sozusagen. Brauchen Sie zufällig Unterstützung?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "Ich habe Ihren Auftrag erledigt. Ich habe Gralam Lavoie gefunden.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Treffen Sie Ihren neuen Assistenten, Monsieur.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "Es bin wieder ich, Monsieur. Ich bin für meine Belohnung gekommen.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Nehmen Sie einen Blick auf diese Ohrringe, Monsieur. Ich habe sie auf dem Körper eines Banditen gefunden, der im Dschungel getötet wurde. Dies ist eindeutig das Werk eines feinen Juweliers, der, wie ich sicher bin, nicht von hier ist. Können Sie etwas zu diesen Ohrringen sagen?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kapitän, danke für deine Rettung.";
				Link.l1 = "Oh, du bist willkommen.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Was ist los, Kapitän? Haben Sie etwas verloren? Warum laufen Sie so in meinem Laden herum?";
				Link.l1 = "Nun, stellt euch das vor - Das habe ich tatsächlich! Wo ist dieser verfluchte Gerard LeCroix? Ich habe alle Aufgaben erfüllt, die mir von Florian Shoke gegeben wurden, und, möge der Hai mich ganz verschlingen, ich hatte verdammt viel Mühe damit! Und jetzt, wo ich komme, um meine Belohnung zu holen, stellt sich heraus, dass dieser Vogel geflogen ist!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Wie soll ich es Ihnen sagen... Verloren. Haben Sie meinen Kunden gesehen? Sein Name ist Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kapitän, ich möchte Sie um einen Gefallen bitten. Werden Sie mir helfen?";
				link.l1 = "Wie kann ich Ihnen helfen?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Freut mich, Sie kennenzulernen, Herr! Sind Sie neu in diesen Landen?","Willkommen, Kapitän! Mein Laden steht zu Ihren Diensten, Herr.","Herr, bitte kommen Sie herein! Ich freue mich, Ihnen die allerbesten Waren anzubieten, die Sie auf diesem Archipel kaufen können."),LinkRandPhrase("Oh, Herr Kapitän! Die besten Waren in allen französischen Kolonien - direkt hier und jetzt und exklusiv für Sie!","Welch angenehme Begegnung, Monsieur! Der beste Laden, der die besten französischen Waren anbietet - zu Ihren Diensten!","Haben wir uns schon einmal getroffen, Monsieur Kapitän? Wissen Sie, mein Laden ist genauso gut wie die besten Geschäfte in der Mutterland!"),LinkRandPhrase("Oh! Senor Kapitän! Ich bin so froh, Sie in meinem Laden zu sehen!","Ich freue mich, einen so brillanten Caballero im besten Laden aller spanischen Kolonien begrüßen zu dürfen!","Oh, edler Hidalgo! Das Schicksal selbst hat dich zu meinem bescheidenen Laden gebracht! Hier findest du alles, was du möchtest!"),LinkRandPhrase("Guten Nachmittag, Herr Kapitän. Ist dies Ihr erster Besuch hier?","Hallo, mein Herr. Sind Sie zum ersten Mal hier? Ich versichere Ihnen, dass die Qualität unserer niederländischen Waren Sie angenehm überraschen wird!","Bitte kommen Sie herein, mein Herr Kapitän! Die allerbesten Waren zu den niedrigsten Preisen - das ist der niederländische Handelsweg!"));
			Link.l1 = LinkRandPhrase("Freut mich auch, dich kennenzulernen. Mein Name ist "+GetFullName(pchar)+" und ich bin ziemlich neu in diesen Landen. Nun, zeig mir die Reichtümer des Archipels!","Freut mich auch, dich kennenzulernen. Ich bin "+GetFullName(pchar)+". Kapitän des Schiffes '"+pchar.ship.name+"'. Also, was sind die heißen Angebote?",""+GetFullName(pchar)+", Kapitän des Schiffes '"+pchar.ship.name+"', schön, dich zu treffen. Also, was kannst du mir anbieten?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Kapitän Helen! Immer ein Vergnügen.";
				link.l1 = "Ebenso bin ich Ihnen dankbar.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Der Alarm wurde in der Stadt ausgelöst und jeder sucht nach dir. Wenn ich du wäre, würde ich dort nicht bleiben.","Alle Stadtwachen durchkämmen die Stadt auf der Suche nach dir. Ich bin kein Narr und werde nicht mit dir sprechen!","Lauf, "+GetSexPhrase("Kamerad","lass")+", bevor die Soldaten dich in ein Sieb verwandeln..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Schurke")+"?! Die Stadtwache hat bereits deine Witterung aufgenommen, du wirst nicht weit kommen, "+GetSexPhrase("schmutziger Pirat","mörderischer Dreck")+"!","Dreckiger Mörder, verlasse sofort mein Haus! Wachen!","Ich fürchte dich nicht, "+GetSexPhrase("Schleicher","Stinktier")+"! Bald wirst du in unserem Fort gehängt, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich nie ein Problem...","Sie werden mich nie kriegen."),RandPhraseSimple("Halt den Mund, "+GetWorkTypeOfMan(npchar,"")+", oder ich reiße deine dreckige Zunge heraus!","Heh, "+GetWorkTypeOfMan(npchar,"")+", und jeder dort - ist hier, um Piraten zu fangen! Hier ist, was ich dir sagen werde, Kumpel: sitz ruhig und du wirst nicht sterben..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Bitte entschuldigen Sie, aber ich habe jetzt keine Zeit für Sie.";
				link.l1 = "Ja, sicher. Ich schaue ein andermal vorbei, dann.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kapitän, danke für meine Rettung.";
				Link.l1 = "Ach, gern geschehen.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Was ist los, Kapitän? Haben Sie etwas verloren? Warum laufen Sie so in meinem Laden herum?";
				Link.l1 = "Nun, stell dir das vor - das habe ich tatsächlich! Wo ist dieser verfluchte Gerard LeCroix? Ich habe alle Aufgaben erfüllt, die mir von Florian Shoke gegeben wurden, und, möge der Hai mich ganz verschlingen, ich hatte verdammt hart daran zu arbeiten! Und jetzt, wenn ich komme, um meine Belohnung einzusammeln, stellt sich heraus, dass dieser Vogel geflogen ist!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Wie soll ich es Ihnen sagen... Verloren. Haben Sie meinen Klienten gesehen? Sein Name ist Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kapitän, ich möchte Sie um einen Gefallen bitten. Werden Sie mir helfen?";
				link.l1 = "Wie kann ich Ihnen helfen?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, sieh mal wer da ist! Nun, wie man so schön sagt, Geld stinkt nicht, also komm rein, Kapitän, und lass uns Handel treiben...","Ich kann nicht sagen, dass ich froh bin, dich zu sehen, "+GetFullName(pchar)+"... Aber ich kann immer noch mit dir handeln.","He-he... Nun, ich würde Sie nicht zu mir nach Hause einladen, Kapitän - aber mein Laden steht Ihnen dennoch zur Verfügung."),LinkRandPhrase("Oh, schau mal wer da ist! Ist das nicht "+GetFullName(pchar)+"! Wollen Sie handeln oder einfach etwas umsonst nehmen? Hey, nur ein Scherz...","Kann nicht sagen, dass ich froh bin, dich hier zu sehen, "+GetAddress_Form(NPChar)+". Aber wenn du Geld zum Ausgeben hast - komm rein, komm rein...","Möchten Sie handeln, Kapitän "+GetFullName(pchar)+"? Wenn ja, könnten Sie bitte schnell damit sein? Andere Kunden meiden Sie und das ist schlecht für mein Geschäft,"),LinkRandPhrase("Möchtest du handeln, Mynheer? Nur eine Sekunde, ich werde abkassieren - du weißt, es gibt zwielichtige Typen hier... Natürlich meine ich nicht dich, Kapitän!","Wenn ich dich auf offener See sähe, "+GetAddress_Form(NPChar)+", Ich würde wahrscheinlich befehlen, Segel hinzuzufügen... Aber hier, in meinem Laden, kann ich Ihnen anbieten zu handeln.","Käpt'n, ich warne dich gleich: Wenn der Stoff mit Blut befleckt und der Kaffee nach Schießpulver stinkt, nehme ich es nicht. Ansonsten schau dich um und such dir etwas aus.")),LinkRandPhrase(LinkRandPhrase("Und ich freue mich, Sie wieder zu begrüßen, "+GetAddress_Form(NPChar)+"! Kaufen oder verkaufen - Ich helfe Ihnen immer gerne.","Ich bitte dich, "+GetAddress_Form(NPChar)+", komm rein! Ich freue mich immer, meinen Lieblingskunden hier zu sehen. Was wird es diesmal sein - kaufen oder verkaufen?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Ich bin so froh, dich wieder zu sehen! Was wird es diesmal sein - Kaufen oder Verkaufen?"),LinkRandPhrase("Gefallen Ihnen unsere Waren, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Ich stehe immer zu Ihren Diensten - schauen Sie sich um und machen Sie Ihre Wahl.","Hallo, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Ich freue mich, dich wiederzusehen! Möchtest du dir das Sortiment unserer Waren anschauen?","Schön dich zu sehen, Kapitän! Ich wusste, dass dir unsere Qualitätswaren gefallen würden. Möchtest du einen Blick auf das Neue werfen?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Bitte kommen Sie herein! Alle Waren nur für Sie - und zu diesem Anlass mit großen Rabatten!","Kapitän "+GetFullName(pchar)+", wieder einmal hast du mich mit deinem Besuch glücklich gemacht! Bitte, such dir aus, was du magst!","Was möchtest du diesmal, Kapitän? Ich bin froh, dass du dich immer noch daran erinnerst, wie du mich findest. Wir haben alle Waren, die du brauchen könntest - allerbeste Qualität!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("So begrüßt du mich, Kumpel? Nun, das werde ich mir merken, wenn wir uns auf See treffen... Hör auf zu zittern, ich habe nur gescherzt. Zeig mir, was du drauf hast.","In Ordnung, Kumpel. Ich könnte deine Waren brauchen, aber nicht deine Zunge. Kannst du sie halten oder brauchst du dabei Hilfe? Halte den Mund und zeig mir deine Waren."),RandPhraseSimple("Lassen wir uns dem Geschäft nähern, Händler. Ich habe keine Zeit, moralische Fragen mit dir zu diskutieren, also handeln wir einfach wie anständige Leute.","Halt die Klappe, Kumpel. Scherzen ist gut, aber denk daran, dass ich wütend werden kann... Also hör auf, mich zu ärgern und zeig mir einfach deine Waren.")),RandPhraseSimple(RandPhraseSimple("Immer froh, dich zu besuchen, Kumpel. Was hast du auf Lager, was meine Aufmerksamkeit wert wäre?","Immer gut dich zu sehen, Kumpel. Also, was gibt's Neues für Seefahrer, die seit Monaten kein trockenes Land gesehen haben?"),RandPhraseSimple("Und schon wieder bin ich in "+XI_ConvertString("Colony"+npchar.City+"Akk")+"! Froh, dass ich nicht hier war, um zu vergessen. Aber gibt es noch etwas in euren Lagern für mich? Ist alles sortiert?","Wie konntest du nicht kommen? Du erfreust mich immer mehr als das. Nun, was hast du dort?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("Alle Mann an Deck! ","Haltet die Inspektion! ")+LinkRandPhrase("Was macht ein "+GetSexPhrase("Herr","Herr, oh, verzeihen Sie mir - eine Dame")+" des Glücks brauchen in meinem Laden, he-he?","Was für eine Überraschung für einen armen alten Ladenbesitzer! He-he!","Also, welcher günstige Wind hat dich zu meinem Laden gebracht?"),LinkRandPhrase("Öffnet die Häfen!","Haken zur Seite!","Segel geradeaus!")+RandPhraseSimple(" Hier wirst du finden"," Mein Laden hat")+LinkRandPhrase(" die besten Preise auf der ganzen Insel."," ausgezeichnete Auswahl an Waren."," Waren von bester verfügbarer Qualität.")+RandPhraseSimple(" Ich stehe zu Ihren Diensten"," Was auch immer du willst")+", Kapitän!"),pcharrepphrase(RandPhraseSimple("Gibt es Waren für "+GetSexPhrase("Herren","Meine Damen und Herren")+" des Glücks! He-he! Bis sie in der Sonne zum Trocknen aufgehängt werden!","Der Wind schwingt die Gehängten im Hafen und trägt das Klirren der Ketten mit sich. Aber Geld hat keinen Geruch, oder?"),"Möchten Sie "+LinkRandPhrase("kaufe die besten Waren von "+NationNameGenitive(sti(NPChar.nation)),"kaufen oder verkaufen Sie Ihre Ladung","hast du eine profitable Fracht?")+RandPhraseSimple("? Ich stehe zu Ihren Diensten!","? Mein Laden steht zu Eurem Dienst!")+RandPhraseSimple(" Schön dich zu sehen"," Wie du willst")+", Kapitän!")),NPCharRepPhrase(npchar,pcharrepphrase("Wenn Sie meinen Rat wollen, Kapitän - sparen Sie nicht am Traubenschuss. Sie wissen, die Toten sind viel einfacher zu durchsuchen!","Ich habe sofort bemerkt, dass du ein "+GetSexPhrase("listiger Kamerad","schlaues Mädchen")+". "+RandPhraseSimple("Aber jetzt kann ich sehen, dass du ein echter "+GetSexPhrase("Held","Draufgänger")+".","Du bist jung, aber "+RandPhraseSimple("behalte deinen Verstand bei dir.","sie lassen sich sicherlich nicht leicht täuschen."))),pcharrepphrase("Ich bin bereit, dir die gesamte Fracht aus den erbeuteten Preisen abzukaufen. Möchtest du Silber oder Gold? Das Zeug ist immer teuer.","Handelsschifffahrt ist ein lukratives Geschäft, Kapitän "+GetFullName(pchar)+", nicht wahr?")),NPCharRepPhrase(npchar,RandPhraseSimple("Wir haben sie alle fest in ein Hauptsegel gewickelt Mit zwanzig Umdrehungen einer Ankerleine Und wir haben sie über Bord geworfen und aus den Augen verloren! ",RandPhraseSimple("Fünfzehn Männer auf der Truhe eines toten Mannes!","Trinken und der Teufel haben den Rest erledigt!")+" Yo ho ho und eine Flasche Rum! ")+RandPhraseSimple("Was ist los, Käpt'n?","Möchten Sie etwas kaufen, Kapitän?"),pcharrepphrase("Ich sehe, Sie sind ein ziemlicher Feilscher, Kapitän "+GetFullName(pchar)+". Da Sie ein wiederkehrender Kunde sind, biete ich Ihnen sehr gute Preise an!","In Ordnung, Kapitän "+GetFullName(pchar)+", aus Respekt vor Ihnen kann ich ein bisschen mehr anbieten! Was möchten Sie?")),NPCharRepPhrase(npchar,"Ich schwöre, mit dir zu reden macht mich krank. "+LinkRandPhrase("Kauf ein paar Erdnüsse. Schweine mögen diese Sachen. ","Erwartest du, dass hier jemand deine Stiefel mit Rum poliert? ",pcharrepphrase("Ich kenne deine Sorte. Mit Rum vollsaufen - und ab zum Galgen.","Ich frage mich, wie deine Mutter dich hat zum Seemann werden lassen! Ein Seemann! Du würdest ein viel besserer Schneider sein...")),pcharrepphrase(RandPhraseSimple("Ich dachte, dass ","Ich hoffte, dass ")+RandPhraseSimple("du hattest unsere Insel für immer verlassen.","Ich würde dich nie wieder sehen.")+RandPhraseSimple(" Die Toten hängen wie Mühlsteine an deinem Hals..."," Wie viele Matrosen hast du denn bei den Korallen verrotten lassen?!"),"Kapitän "+GetFullName(pchar)+", Ihre Leidenschaft für den Handel hat alle meine Erwartungen übertroffen!"+RandPhraseSimple(" Möchtest du noch letzte Einkäufe machen, bevor wir in See stechen?"," Suchen Sie etwas Besonderes?"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, schau mal wer da ist! Nun, wie man so schön sagt, Geld stinkt nicht, also komm rein, Kapitän, und lass uns handeln...","Ich kann nicht sagen, dass ich mich freue, dich zu sehen, "+GetFullName(pchar)+"... Aber ich kann trotzdem mit dir handeln.","He-he... Nun, ich würde Sie nicht zu mir nach Hause einladen, Kapitän - aber mein Laden steht Ihnen immer noch zur Verfügung."),LinkRandPhrase("Oh, schau mal wer da ist! Ist das nicht "+GetFullName(pchar)+"! Wollen Sie handeln oder einfach etwas kostenlos nehmen? Hey, ich mache nur Spaß...","Kann nicht sagen, dass ich froh bin, dich hier zu sehen, "+GetAddress_Form(NPChar)+". Aber wenn du Geld zum Ausgeben hast - komm rein, komm rein...","Möchten Sie handeln, Kapitän "+GetFullName(pchar)+"? Wenn ja, könnten Sie bitte schnell darüber sein? Andere Kunden meiden Sie, und das ist schlecht für mein Geschäft,"),LinkRandPhrase("Wollen Sie handeln, Mynheer? Nur eine Sekunde, ich werde abkassieren - Sie wissen, es gibt hier zweifelhafte Typen... Natürlich meine ich nicht Sie, Kapitän!","Wenn ich dich auf offener See sähe, "+GetAddress_Form(NPChar)+", ich würde wahrscheinlich anordnen, Segel hinzuzufügen... Aber hier, in meinem Laden, kann ich Ihnen anbieten zu handeln.","Käpt'n, ich warne Sie gleich: wenn der Stoff mit Blut befleckt und der Kaffee nach Schießpulver stinkt, nehme ich ihn nicht. Ansonsten schauen Sie sich um und suchen Sie sich etwas aus.")),LinkRandPhrase(LinkRandPhrase("Und ich freue mich, Sie wieder zu begrüßen, "+GetAddress_Form(NPChar)+"! Kaufen oder verkaufen - Ich helfe Ihnen immer gerne.","Ich bitte Sie, "+GetAddress_Form(NPChar)+", kommen Sie herein! Ich freue mich immer, meinen Lieblingskunden hier zu sehen. Was wird es diesmal sein - Kaufen oder Verkaufen?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Ich bin so froh, dich wieder zu sehen! Was wird es diesmal sein - Kaufen oder Verkaufen?"),LinkRandPhrase("Gefallen Ihnen unsere Waren, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Ich stehe Ihnen immer zur Verfügung - schauen Sie sich um und treffen Sie Ihre Auswahl.","Hallo, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Ich freue mich, Sie wieder zu sehen! Möchten Sie einen Blick auf das Sortiment unserer Waren werfen?","Schön Sie zu sehen, Kapitän! Ich wusste, dass Ihnen unsere Qualitätswaren gefallen würden. Möchten Sie einen Blick auf die Neuheiten werfen?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Bitte kommen Sie rein! Alle Waren nur für Sie - und zu diesem Anlass mit tollen Rabatten!","Kapitän "+GetFullName(pchar)+", noch einmal hast du mich glücklich gemacht mit deinem Besuch! Bitte, such dir aus, was du möchtest!","Was wünscht Ihr diesmal, Kapitän? Ich freue mich, dass Ihr Euch noch daran erinnert, wie Ihr mich finden könnt. Wir haben alle Waren, die Ihr benötigen könntet - allerhöchste Qualität!")));
					link.l14 = "Hör zu, ich werde jetzt nach Porto Bello aufbrechen und möchte eine Lieferung Kaffee und Kakao bei dir kaufen. Sagen wir, dreihundert Einheiten von beidem."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, schau mal wer da ist! Nun, wie man so sagt, Geld stinkt nicht, also komm herein, Kapitän, und lass uns handeln...","Ich kann nicht sagen, dass ich froh bin, dich zu sehen, "+GetFullName(pchar)+"... Aber ich kann immer noch mit dir handeln.","He-he... Nun, ich würde Sie nicht zu mir nach Hause einladen, Kapitän - aber mein Geschäft steht Ihnen immer noch zur Verfügung."),LinkRandPhrase("Oh, schau mal wer da ist! Ist das nicht "+GetFullName(pchar)+"! Möchtest du handeln oder einfach etwas kostenlos nehmen? Hey, nur ein Scherz...","Kann nicht sagen, dass ich froh bin, dich hier zu sehen, "+GetAddress_Form(NPChar)+". Aber wenn du Geld zum Ausgeben hast - komm rein, komm rein...","Möchten Sie handeln, Kapitän "+GetFullName(pchar)+"? Wenn ja, könnten Sie bitte schnell damit sein? Andere Kunden meiden Sie, und das ist schlecht für mein Geschäft,"),LinkRandPhrase("Möchten Sie handeln, mein Herr? Nur eine Sekunde, ich werde Kasse machen - Sie wissen, es gibt zwielichtige Typen herum... Natürlich meine ich nicht Sie, Kapitän!","Wenn ich dich auf offener See sähe, "+GetAddress_Form(NPChar)+", ich würde wahrscheinlich befehlen, Segel hinzuzufügen... Aber hier, in meinem Laden, kann ich Ihnen anbieten zu handeln.","Käpt'n, ich warne Sie gleich vorweg: wenn der Stoff mit Blut befleckt und der Kaffee nach Schießpulver stinkt, nehme ich ihn nicht. Ansonsten schauen Sie sich um und treffen Sie Ihre Wahl.")),LinkRandPhrase(LinkRandPhrase("Und ich freue mich, Sie wieder zu begrüßen, "+GetAddress_Form(NPChar)+"! Kaufen oder verkaufen - Ich helfe Ihnen immer gerne.","Ich flehe dich an, "+GetAddress_Form(NPChar)+", komm rein! Ich freue mich immer, meinen Lieblingskunden hier zu sehen. Was wird es diesmal sein - kaufen oder verkaufen?","Ach, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Ich bin so glücklich, dich wieder zu sehen! Was wird es diesmal sein - Kaufen oder Verkaufen?"),LinkRandPhrase("Gefallen Ihnen unsere Waren, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Ich bin immer zu Ihren Diensten - schauen Sie sich um und treffen Sie Ihre Wahl.","Hallo, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Ich freue mich, dich wiederzusehen! Möchtest du dir unser Sortiment ansehen?","Schön dich zu sehen, Kapitän! Ich wusste, dass Ihnen unsere Qualitätswaren gefallen würden. Möchten Sie einen Blick auf das Neue werfen?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Bitte kommen Sie herein! All die Waren nur für Sie - und zu diesem Anlass mit großen Rabatten!","Kapitän "+GetFullName(pchar)+", einmal mehr hast du mich mit deinem Besuch erfreut! Bitte, such dir aus, was immer du magst!","Was wünschen Sie diesmal, Kapitän? Ich freue mich, dass Sie sich noch daran erinnern, wie Sie mich finden können. Wir haben alle Waren, die Sie benötigen könnten - allerbeste Qualität!")));
				link.l14 = "Ich bin hier für Kaffee und Kakao. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Zeig mir, was du drauf hast, du alter Pirat!","Ich wollte mir nur mal Ihre Waren ansehen, mein guter Mann."),pcharrepphrase("Ich schwöre beim Galgen, "+GetFullName(npchar)+", Ich lasse mich nicht von dir abwimmeln! Zeige mir jetzt deine Waren!","Lassen Sie uns einen Blick auf Ihre Waren werfen, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Das ist sicher! Die Toten beißen nicht! Nun, was hast du in deinem Frachtraum?","Sie sollten besser zu Ihrem Geschäft kommen, mein guter Mann. Welche Waren können Sie mir anbieten?"),pcharrepphrase("Es wird ein Tag kommen, an dem du meine Beute wirst, he-he. Nur ein Scherz. Zeige mir deine Waren.","Lassen Sie uns über unsere Handelsangelegenheiten sprechen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Was will ich? Ich möchte etwas kaufen!","Das Trinken wird dich ins Grab bringen, "+GetFullName(npchar)+". Ich möchte einen Blick auf Ihre Waren werfen."),pcharrepphrase("Ich kenne Ihre Rabatte! Zwei Pfund Kakao zum Preis von drei! Zeigen Sie mir jetzt Ihre Waren.","Das ist immer gut. Dann lass uns handeln.")),"Zeig mir deine Waren. Je weniger gesagt wird, desto schneller ist es repariert. Ich habe es eilig.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Oh, ich würde wirklich gerne jemanden erstechen, Also, lass uns zur Sache kommen.","Lassen wir uns auf andere Geschäfte ein, mein guter Mann."),pcharrepphrase("Verdammt! Ich bin hier mit einem anderen Geschäft!","Ich möchte mit dir über ein bestimmtes Geschäft sprechen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Ich habe Geschäfte mit dir, alter Pirat!","Lass uns zur Sache kommen, Kumpel!"),pcharrepphrase("Ich schwöre beim Teufel, du wirst mich nicht täuschen, Schurke! Ich habe anderes Geschäft mit dir!","Ich stimme absolut zu, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ich wollte andere Angelegenheiten mit Ihnen besprechen.")),NPCharRepPhrase(npchar,pcharrepphrase("Bist du schon beladen? Ich habe Geschäfte mit dir.","Ich bin nicht zum Handeln hierher gekommen, mein guter Mann. Ich habe andere Geschäfte."),pcharrepphrase("Möge dich der Donner für solche Preise niederstrecken! Ich habe Geschäfte mit dir.","Rabatte sind immer schön, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", aber ich habe andere Geschäfte mit dir.")),NPCharRepPhrase(npchar,pcharrepphrase("Halt die Klappe, du alter Säufer, ich habe Geschäfte mit dir","Du bist wohl wegen des Rums krank, schätze ich. Nicht dass ich von dir begeistert wäre. Lassen wir uns auf das Geschäft ein."),pcharrepphrase("Du hast mich schon abgezockt, Schurke! Ich habe Geschäfte mit dir.","Deine Ironie ist unangebracht. Ich habe andere Geschäfte mit dir.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Erst Geschäft, dann Vergnügen. Ich möchte dich etwas fragen.","Nicht jetzt. Ich brauche Informationen."),pcharrepphrase("Zum Teufel mit deinen Preisen! Zuerst wirst du mir alles erzählen, was ich brauche.","Mit Vergnügen. Ich wollte etwas fragen.")),NPCharRepPhrase(npchar,pcharrepphrase("Danke für den Rat, alter Mörder. Ich wollte dich etwas fragen.","Ich hatte eine besondere Frage."),pcharrepphrase("Gold kann warten. Ich wollte dich etwas fragen.","Ja, ich stimme zu. Ich wollte Sie etwas fragen.")),NPCharRepPhrase(npchar,pcharrepphrase("Ich glaube tatsächlich, dass Sie wissen, was ich fragen wollte.","Ich hoffe, du wirst meine Frage beantworten."),pcharrepphrase("Kannst du an etwas anderes denken außer an deine Preisschilder? Denn genau danach wollte ich dich fragen.","Das interessiert mich nicht. Ich brauche Informationen.")),NPCharRepPhrase(npchar,pcharrepphrase("Mach dich nicht zu aufgeregt, Kumpel! Ich wollte dir nur eine Frage stellen.","Lass dich nicht zu sehr aufregen, sonst bekommst du einen Schlaganfall. Beantworte nur eine Frage, und ich werde gehen"),pcharrepphrase("Ich erwarte nicht, dass du etwas Kluges sagst, da du das Gehirn einer Kakerlake hast. Aber sicherlich musst du etwas wissen.","Ich werde Sie nicht lange aufhalten. Nur eine Frage.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "Ich bin mit einer anderen Angelegenheit beschäftigt.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Ich habe Ihnen eine Preisliste aus der Stadt gebracht "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Ich möchte eine Charge europäischen Weins bei Ihnen kaufen - etwa sechzig Flaschen. Mir wurde gesagt, dass Sie genug davon auf Lager haben.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Hallo nochmal. Bitte, schauen Sie sich diesen Brief an - vielleicht würden Sie Ihre Position bezüglich des Weinverkaufs an mich überdenken?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Es bin wieder ich. Können wir unser unterbrochenes Weinhandelsgeschäft fortsetzen? Ich habe es geschafft, genug Geld aufzutreiben."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Hören Sie, Monsieur, ich suche nach Arbeit. Nicht wie eine Vollzeitbeschäftigung oder das Schleppen von Frachttaschen, sondern eher wie das Erledigen von Besorgungen, sozusagen. Brauchen Sie zufällig Hilfe?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "Ich habe Ihre Besorgung erledigt. Ich habe Gralam Lavoie gefunden.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Treffen Sie Ihren neuen Assistenten, Monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "Es ist wieder ich, Monsieur. Ich bin wegen meiner Belohnung gekommen.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Werfen Sie einen Blick auf diese Ohrringe, Monsieur. Ich habe sie auf dem Körper eines Banditen gefunden, der im Dschungel getötet wurde. Dies ist ganz klar die Arbeit eines feinen Juweliers, der, da bin ich sicher, nicht von hier stammt. Können Sie etwas über diese Ohrringe sagen?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Hallo, ich bin auf Einladung Ihres Sohnes gekommen."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Es geht um Ihre Tochter...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Bis dann, alter Säufer.","Hab einen schönen Tag, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Verdammt! Geh nirgendwo hin, ich komme wieder.","Es war schön, dich hier zu haben, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Auf Wiedersehen!")),NPCharRepPhrase(npchar,pcharrepphrase("Macht los!","Auf Wiedersehen, mein guter Mann."),pcharrepphrase("He! Was versteckst du da? Rum? Nein?! Na gut, ich gehe meinen Hals befeuchten.","Es tut mir leid, aber ich habe dringende Geschäfte in der Stadt.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Nun, wir sehen uns!","Ich muss gehen. Lebewohl, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Und denke nicht einmal daran, mit mir zu streiten! Ich habe keine Zeit dafür!","Vielleicht muss ich nachsehen, was auf meinem Schiff vor sich geht. Lebewohl, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Was ist los, alter Kamerad? Ich bin's - "+GetFullName(pchar)+"! Schlaf dich nüchtern, ich komme später zurück.","Ich fürchte, deine Leber wird dich dahinraffen, bevor ich die Chance bekomme, wieder zu dir zu kommen."),pcharrepphrase("Zähl weiter deine Guineen und Dublonen, du alter Fuchs! Ich werde zurückkommen.","Ich war froh, dich zu sehen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "Was kann ich für Sie tun? Den Regenbogen bestücken, Beute verkaufen? Ich bezweifle, dass Sie an den derzeit profitablen Frachten interessiert sind, ha-ha.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Zeig mir, was du hast, du alter Pirat!","Ich wollte mir nur mal Ihre Waren ansehen, mein guter Mann."),pcharrepphrase("Ich schwöre beim Galgen, "+GetFullName(npchar)+", Ich werde mich nicht von dir abwimmeln lassen! Zeig mir jetzt deine Waren!","Lass uns einen Blick auf deine Waren werfen, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Das ist sicher! Die Toten beißen nicht! Nun, was hast du in deinem Laderaum?","Sie sollten besser zu Ihrem Geschäft kommen, mein guter Mann. Welche Waren können Sie mir anbieten?"),pcharrepphrase("Es wird ein Tag kommen, an dem du meine Beute wirst, he-he. Nur ein Scherz. Zeig mir deine Waren.","Lassen wir über unsere Handelsangelegenheiten sprechen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Was will ich? Ich möchte etwas kaufen!","Das Trinken wird dich zu deinem Grab führen, "+GetFullName(npchar)+". Ich möchte einen Blick auf Ihre Waren werfen."),pcharrepphrase("Ich kenne deine Rabatte! Zwei Pfund Kakao zum Preis von drei! Zeige mir jetzt deine Waren.","Das ist immer gut. Lassen wir uns dann feilschen.")),"Zeige mir deine Waren. Wenig gesagt, schnell verbessert. Ich habe es eilig.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Oh, ich würde wirklich gerne jemanden erstechen, Also, lass uns zur Sache kommen.","Lassen wir uns auf andere Geschäfte ein, mein guter Mann."),pcharrepphrase("Verdammt! Ich bin hier mit einem anderen Geschäft!","Ich möchte mit dir über ein bestimmtes Geschäft sprechen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Ich habe Geschäfte mit dir, alter Pirat!","Lass uns zur Sache kommen, Kumpel!"),pcharrepphrase("Ich schwöre beim Teufel, du wirst mich nicht täuschen, Schurke! Ich habe anderes Geschäft mit dir!","Ich stimme absolut zu, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ich wollte andere Angelegenheiten mit dir besprechen.")),NPCharRepPhrase(npchar,pcharrepphrase("Bereits beladen? Ich habe Geschäfte mit dir.","Ich bin nicht hier zum Handeln, mein guter Mann. Ich habe andere Geschäfte."),pcharrepphrase("Möge der Donner dich für solche Preise niederstrecken! Ich habe Geschäfte mit dir.","Rabatte sind immer schön, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", aber ich habe andere Geschäfte mit dir.")),NPCharRepPhrase(npchar,pcharrepphrase("Halt deine Zunge, du alter Säufer, ich habe Geschäfte mit dir","Du bist wohl wegen des Rums krank, schätze ich. Nicht dass ich von dir begeistert wäre, auch nicht. Lass uns zur Sache kommen."),pcharrepphrase("Du hast mich schon abgezockt, Schurke! Ich habe Geschäfte mit dir.","Deine Ironie ist unangebracht. Ich habe andere Geschäfte mit dir.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Erst Geschäft, dann Vergnügen. Ich möchte dich etwas fragen.","Nicht jetzt. Ich brauche Informationen."),pcharrepphrase("Zum Teufel mit deinen Preisen! Zuerst wirst du mir alles erzählen, was ich wissen muss.","Mit Vergnügen. Ich wollte etwas fragen.")),NPCharRepPhrase(npchar,pcharrepphrase("Danke für den Rat, alter Mörder. Ich wollte dich etwas fragen.","Ich hatte eine besondere Frage."),pcharrepphrase("Gold kann warten. Ich wollte dich etwas fragen.","Ja, ich stimme zu. Ich wollte Sie etwas fragen.")),NPCharRepPhrase(npchar,pcharrepphrase("Ich glaube tatsächlich, dass du weißt, was ich fragen wollte.","Ich hoffe, Sie werden meine Frage beantworten."),pcharrepphrase("Kannst du an etwas anderes denken als an deine Preisschilder? Denn das wollte ich dich fragen.","Das interessiert mich nicht. Ich brauche Informationen.")),NPCharRepPhrase(npchar,pcharrepphrase("Mach dich nicht zu aufgeregt, Kumpel! Ich wollte dir nur eine Frage stellen.","Mach dich nicht zu aufgeregt, oder du wirst einen Schlaganfall haben. Beantworte einfach eine Frage, und ich werde gehen"),pcharrepphrase("Ich erwarte nicht, dass du etwas Kluges sagst, da du das Gehirn einer Kakerlake hast. Aber sicherlich musst du etwas wissen.","Ich werde Sie nicht lange aufhalten. Nur eine Frage.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Bis dann, alter Säufer.","Hab einen schönen Tag, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Donnerwetter! Geh nirgendwohin, ich komme wieder.","Es war schön, dich hier zu haben, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Auf Wiedersehen!")),NPCharRepPhrase(npchar,pcharrepphrase("Leinen los!","Auf Wiedersehen, mein guter Mann."),pcharrepphrase("Hallo! Was versteckst du dort? Rum? Nein?! Gut, dann geh ich mir mal den Hals befeuchten.","Es tut mir leid, aber ich habe dringende Geschäfte in der Stadt.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Nun, wir sehen uns!","Ich muss gehen. Lebewohl, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Und denk nicht einmal daran, mit mir zu streiten! Ich habe keine Zeit dafür!","Vielleicht sollte ich gehen und nachsehen, was auf meinem Schiff vor sich geht. Lebewohl, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Was ist los, alter Kamerad? Ich bin's - "+GetFullName(pchar)+"! Schlaf dich nüchtern, ich komme später wieder.","Ich fürchte, deine Leber wird dich erledigen, bevor ich die Chance habe, wieder zu dir zu kommen."),pcharrepphrase("Bleib bei deinen Guineen und Dublonen, du alter Fuchs! Ich komme wieder.","Ich habe mich gefreut, dich zu sehen, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Entschuldigung, aber ich bin gerade zu beschäftigt. So viele Kunden! Komm morgen wieder.";
				link.l1 = "Oh, wirklich? Nun, dann komme ich später wieder.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("Ich habe Rundschuss, Segeltuch, Medizin, wertvolles Holz und andere Waren! Was interessiert dich?","Möchtest du Zucker und Gewürze kaufen? Oder vielleicht Rum und Schießpulver?");
			link.l1 = pcharrepphrase(LinkRandPhrase("Ich habe viel Beute in meinem Frachtraum! Geld stinkt nicht, oder?","Ich muss die Beute in meinem Frachtraum loswerden und ihn mit deinem Gold füllen. Ha-ha!","Oh, ich weiß, dass du deine Mutter für einen Sack voller Doubloons verkaufen würdest! Aber ich muss nur meine Vorräte auffüllen."),LinkRandPhrase("Ich möchte meine Ladung verkaufen und Vorräte auffüllen.","Ich möchte Waren zum Verkauf kaufen.","Zeig mir die Kanonenkugeln, Bomben und so Zeug."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Mein Zahlmeister wird alle notwendigen Einkäufe tätigen...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Ich gehe ohne Handel. Bis dann!","Ich werde meinen Hals befeuchten. Du bleibst da!"),RandPhraseSimple("Nein, ich habe im Moment keine Zeit zum Handeln. Lebewohl.","Es tut mir leid, ich habe dringende Geschäfte zu erledigen. Auf Wiedersehen!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Ich bin ganz Ohr.";
			link.l1 = "Ich habe Ihren Flüchtling gebracht.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Kapitän, vielen Dank! Wie geht es ihr? Ist sie verletzt? Es ist ein Tag vergangen, seit sie weggelaufen ist, dieses böse Mädchen. Sieht es so aus, als würde ich ihr etwas antun? Ich habe ihr einen Ehemann gefunden. Eine Ehe arrangiert. Ein reicher, junger Verlobter. Er mag hässlich sein, aber wer kümmert sich um Gesichtszüge. Nein! Sie versucht immer, alles auf ihre Weise zu machen. Genau wie ihre Mutter es immer getan hat, Flammen!\nObwohl, sie wäre nicht geboren worden, wenn ihre Mutter nicht vor langer Zeit mit irgendeinem vielversprechenden Idioten weggelaufen wäre... nun, was auch immer... Jugend ist naiv, dumm und grausam.";
			link.l1 = "Natürlich bist du der Vater und es liegt an dir zu entscheiden, aber ich würde mit der Hochzeit nicht hetzen...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Was wissen Sie schon? Haben Sie eigene Kinder? Nein? Sprechen Sie mit mir, wenn Sie welche haben...\nJa... Ich habe eine Belohnung versprochen für den Mann, der sie zurückbringen wird, hier, nehmen Sie es.";
			link.l1 = "Danke. Und behalte sie im Auge. Ich habe das Gefühl, dass sie nicht damit aufhören würde.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, also bist du "+GetSexPhrase("der Kapitän, der gebracht hat","das Mädel, das gebracht hat")+" mein verlorener Sohn mit einer jungen Braut?";
				link.l1 = "Ja, ich habe ihnen bei der Flucht geholfen.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, da "+GetSexPhrase("er ist, unser Wohltäter","sie ist es, unsere Wohltäterin")+". Erwartest du eine Belohnung, nehme ich an?";
				link.l1 = "Nun, ich komme ohne Belohnung aus, aber ein einfaches Dankeschön würde genügen.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Ich bin Ihnen sehr dankbar, dass Sie mein Kind in seiner Not nicht im Stich gelassen und ihm geholfen haben, einen Ausweg aus einer heiklen Situation zu finden. Erlauben Sie mir, Ihnen zu danken und bitte nehmen Sie diese bescheidene Summe und ein Geschenk von mir persönlich an.";
			link.l1 = "Danke. Es war mir eine Freude, diesem jungen Paar zu helfen.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Danke? Welcher Dank?! Dieser Tölpel hängt schon ein halbes Jahr ohne Job herum - und sieh ihn dir an, er hat genug Zeit für Liebschaften! Als ich in seinem Alter war, leitete ich bereits mein eigenes Geschäft! Pff! Ein Gouverneur hat eine heiratsfähige Tochter - und dieser Dummkopf hat eine Dirne ohne Sippe oder Verwandtschaft in mein Haus gebracht und es gewagt, meinen Segen zu erbitten!";
			link.l1 = "Hmm... Anscheinend glaubst du nicht an aufrichtige Gefühle?";
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
			dialog.text = "Welche Gefühle? Von welchen Gefühlen sprichst du? Gefühle... wie kann man in deinem Alter so leichtsinnig sein?! Schande über dich, die Launen der Jugend zu verwöhnen und als Kuppler zu handeln! Du hast nicht nur ein Mädchen aus ihrem Zuhause genommen, sondern auch das Leben meines Grünschnabels ruiniert. Es wird kein Dank an dich geben. Lebewohl.";
			link.l1 = "Also gut, und dir das Gleiche...";
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
				dialog.text = LinkRandPhrase("...Schon erledigt. Jetzt bleibt nur noch zu entscheiden, welches Schiff beladen werden soll.","Ihr Schatzmeister hat das bereits erledigt. Lassen Sie uns jetzt entscheiden, welches Schiff beladen werden soll.","Ja, "+PChar.name+", ich weiß. Er hat mich bereits besucht. Nun, welches Schiff werden wir beladen?");
					
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
				
				Link.l99 = "Ich habe mir Gedanken gemacht, nichts ist nötig.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Machst du Witze? Wo ist dein Schiff? Ich sehe es nicht am Pier!","Ich schwöre beim Teufel, du wirst mich nicht täuschen! Dein Schiff ist nicht am Pier!"),pcharrepphrase("Ich sehe Ihr Schiff nicht im Hafen, Kapitän "+GetFullName(pchar)+". Ich hoffe, sie ist nicht der 'Fliegende Holländer'?","Kapitän, es ist viel einfacher, die Ladung vom Pier zu laden. Und ich bevorzuge es auf diese Weise. Bring dein Schiff schnell und komm zurück."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Was für ein Ärger! Also gut, alter Schlawiner, bis bald!","Ich wollte dich nicht täuschen, "+GetFullName(npchar)+", ein Schiff ist auf der anderen Seite der Insel."),pcharrepphrase("Nein. Mein Schiff heißt 'Schwarze Perle'. Warum bist du blass geworden? Haha! Nur ein Scherz!","Danke für den Rat, ich werde ihn auf jeden Fall nutzen."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Also, Kapitän, welches Schiff werden wir beladen?","Also, welches Schiff soll dann beladen werden?",PChar.name+", in welchen Schiffsbauch sollen wir die Waren laden?");
				
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
			
			Link.l99 = "Ich habe meine Meinung geändert, ich brauche nichts.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Alles ist bereit! Das Laden des ausgewählten Schiffes hat begonnen.","Gut, das Verladen der Waren auf das ausgewählte Schiff hat begonnen.","Käpt'n, das Verladen der Waren auf das ausgewählte Schiff hat begonnen.");
					link.l1 = "Danke. Es war ein Vergnügen, Geschäfte mit Ihnen zu machen.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Kapitän, alle von Ihrem Schatzmeister angeforderten Waren sind bereits an Bord des von Ihnen angegebenen Schiffes!","Käpt'n, alle Waren sind bereits an Bord des von Ihnen angegebenen Schiffes!","Käpt'n, das Schiff braucht keine Wartung, da alle Waren schon da sind.");
					link.l1 = "Ja, klar.";
					link.l1.go = "exit";
					link.l2 = "Dann muss ich wohl ein anderes Schiff auswählen.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Ich fürchte, ein Schiff dieses Typs kann einfach nicht so viel tragen.","Käpt'n, Ihr Schiff kann nicht so viel Fracht tragen!","Kapitän, der Laderaum Ihres Schiffes kann so viel Fracht nicht aufnehmen!");
				link.l1 = "Ja, du hast recht. Ich muss ein anderes Schiff auswählen.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Ich habe nachgedacht... Ich muss nichts kaufen.";
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
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Machst du Witze? Wo ist dein Schiff? Ich sehe es nicht am Pier!","Ich schwöre beim Teufel, du wirst mich nicht täuschen! Dein Schiff ist nicht am Pier!"),pcharrepphrase("Ich sehe dein Schiff nicht im Hafen, Kapitän "+GetFullName(pchar)+". Ich hoffe doch, sie ist nicht der 'Fliegende Holländer'?","Kapitän, es ist viel einfacher, die Ladung vom Pier zu laden. Bringen Sie Ihr Schiff schnell und kommen Sie zurück."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Was für ein Ärger! Also gut, alter Schlitzohr, bis bald!","Ich wollte dich nicht täuschen, "+GetFullName(npchar)+", ein Schiff ist auf der anderen Seite der Insel."),pcharrepphrase("Nein. Mein Schiff heißt 'Schwarze Perle'. Warum bist du so blass geworden? Haha! Nur ein Scherz!","Danke für den Rat, sie werden ihn verwenden."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Was die Miete angeht, schuldest du mir immer noch "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "In Ordnung, ich bezahle jetzt die Miete.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Ich komme später zurück.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Komm.";
				link.l1 = "Danke.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Nein, ich habe meine Meinung geändert.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Ja, ich habe ein Lagerhaus im Hafen - es kann 50000 Zentner Fracht aufnehmen. Für "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" pro Monat kann ich die sichere Aufbewahrung Ihrer Waren gewährleisten. "+"Das beinhaltet Wache halten, Schutz vor Wasserschaden und den Kampf gegen die Ratten. Was sagst du? Außerdem... ich werde eine Monatszahlung im Voraus benötigen.";	
			link.l1 = "Anzug. Kann ich es mir ansehen? Habt ihr dort viele Ratten?";
			link.l1.go = "storage_1";
			link.l2 = "Nein, ich frage nur. Ich kann es verwenden, wenn es notwendig ist...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Wie ich schon sagte, verlange ich die Bezahlung für einen Monat im Voraus. Und keine Ratten!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Du bist... ziemlich geschäftstüchtig, muss ich sagen. Hier ist dein Geld - ich werde diesen Schuppen mieten.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Du bist... ziemlich geschäftstüchtig, muss ich sagen. Gut, ich komme bald mit dem Geld zurück.";
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
			dialog.text = "Schon am Gehen? Welch ein Bedauern - das ist wirklich ein hervorragender Ort zu großartigen Bedingungen. Ich versichere Ihnen, dass Sie nirgendwo sonst in der Karibik ein solches Angebot bekommen werden.";
			link.l1 = "Ich sagte - freistellen. Oder schlägst du mir vor, für die Lagerung von Luft zu bezahlen? Such dir einen anderen Mieter.";
			link.l1.go = "storage_4";
			link.l2 = "Nirgendwo in der Karibik, sagst du? Gut, dann werde ich es eine Weile unter die Lupe nehmen.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "Und für die Miete, du schuldest mir immer noch "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Gut.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Sammle deine Waren ein und ich werde das Lagerhaus schließen.";
				link.l1 = "Gut.";
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
					dialog.text = "Oh! Sie kommen gerade rechtzeitig, Kapitän. Ich möchte Sie bitten, mir einen Gefallen zu tun.";
					link.l1 = "Lass uns zuhören."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Ich bin ganz Ohr, Kapitän.";
				link.l5 = "Ich habe Ihre Bestellung gebracht."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh! Sie kommen gerade rechtzeitig, Kapitän. Ich benötige einen besonderen Gefallen.";
				link.l5 = "Lass uns zuhören."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Ich bin ganz Ohr, Kapitän.";
				link.l5 = "Ich habe euch die Sklaven gebracht."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Hör zu, du handelst mit allerlei Waren... Hat dir gestern oder heute jemand angeboten zu kaufen "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_block")) 
			{
				dialog.text = "Kapitän, ich möchte Sie um einen Gefallen bitten und ich bin bereit, Sie fürstlich zu entlohnen, sollten Sie einverstanden sein.";
				link.l1 = "Interessant. Nun, was ist das Problem?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Kapitän, ich freue mich, Sie zu sehen. Ich weiß bereits, dass Sie meine Bitte bezüglich "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh! Das ist sicher. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" und die Ladung - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", gehören nicht länger deinem Rivalen."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Mein Herr, Kapitän... Warum haben Sie ihn getötet? Ich habe Sie nur gebeten, sein Schiff zu versenken! Heilige Jungfrau, jetzt habe ich das Blut eines unschuldigen Mannes an meinen Händen...";
				link.l1 = "Heh! Was ist los mit dir, "+npchar.name+"? Wen kümmert's - er wird dich nie wieder belästigen, und das ist es, was zählt!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Ich hatte einen Job, aber "+GetFullName(&Characters[iTmp])+" hat sich bereits bereit erklärt, es für mich zu tun.";
				link.l1 = "Ach, wirklich? Nun, dann komme ich später wieder.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Was für Geschäfte?! Erzähl mir alles!","Ich höre zu. Wovon für ein Handel sprichst du?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("Ich habe eine Ladung Waren für Ihren Laden im Laderaum meines Schiffes.","Mein Schiff wurde gechartert, um die Waren zu Ihrem Geschäft zu liefern. Die Waren werden gerade entladen.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Leider bin ich gezwungen, ihre Verpflichtungen aufzugeben. Die politische Situation erlaubt es mir nicht, die Waren zu liefern.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Ich kann Ihnen anbieten, mein Schiff für den Warentransport zu chartern.","Ich habe ein großartiges Schiff und kann jede Fracht liefern, wo immer Sie es benötigen.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Möchten Sie ein Schiff chartern, "+GetAddress_FormToNPC(NPChar)+"? Ich habe ein zuverlässiges Schiff und eine erfahrene Crew.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Ich bin mit einer anderen Angelegenheit beschäftigt.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, ich war wirklich erschöpft auf See... Nun, Kumpel, Geld ist gerade ein echtes Problem für mich.","Also gut, alter Fuchs, lass uns unsere finanziellen Angelegenheiten besprechen."),RandPhraseSimple("Ich möchte die finanziellen Angelegenheiten mit Ihnen besprechen.","Lassen wir über finanzielle Angelegenheiten sprechen, wir müssen darüber reden."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Ich bin hier auf Antrag eines Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich zu dir geschickt. Ich soll etwas abholen...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Kannst du mir die neuesten Klatsch und Tratsch erzählen? Du hängst sowieso den ganzen Tag hier rum.","Mach keine Aufhebens, du alter Schwindler - erzähl mir lieber, was es Neues an Land gibt?"),RandPhraseSimple("Es scheint, als hätte ich eine Ewigkeit auf See verbracht. Was gibt's Neues in deiner Region?","Du weißt wahrscheinlich all die neuesten Nachrichten? Was wichtiges passiert?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Nimm mich zum Lagerhaus. Ich möchte sehen, in welchem Zustand es ist.";
						link.l7.go = "storage_0";
						link.l8 = "Ich habe beschlossen, das Lager freizugeben. Ich brauche es jetzt nicht.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Entschuldigen Sie, mein guter Mann - vermieten Sie zufällig Lagerhäuser?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Sie sehen, ich versuche meinen Gefährten zu finden, "+pchar.GenQuest.FindFugitive.Name+" ist sein Name. In Port-Royal haben mir Leute in der Taverne erzählt, dass er zu eurer Siedlung unterwegs war. Habt ihr ihn zufällig getroffen?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Aber jetzt ist keine Zeit zum Reden.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Ich habe das Schiff auf der anderen Seite der Insel verlassen. Ich komme später zurück!","Ich bitte um Verzeihung, "+GetFullName(npchar)+", Ich komme später. Mein Schiff hat den Pier noch nicht erreicht."),pcharrepphrase("Teufel! Diese Idioten haben das Schiff nicht für die Beladung vorbereitet! Ich komme später wieder!","Entschuldigung, ich muss Befehle geben, um mein Schiff am Pier anzulegen!"));
                link.l1.go = "exit";
				link.l22 = "Ich bin mit einer anderen Angelegenheit beschäftigt.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Oh, ich war wirklich erschöpft auf dem Meer... Nun, Kumpel, Geld ist gerade ein echtes Problem für mich.","Also gut, alter Fuchs, lass uns über unsere finanziellen Angelegenheiten sprechen."),RandPhraseSimple("Ich möchte mit Ihnen über die finanziellen Angelegenheiten sprechen.","Lassen Sie uns über finanzielle Angelegenheiten sprechen, wir müssen darüber reden."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Ich bin hier auf Anfrage eines Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich zu dir geschickt. Ich soll etwas abholen...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Sie sehen, ich versuche meinen Kameraden zu finden, "+pchar.GenQuest.FindFugitive.Name+" ist sein Name. In Port-Royal haben mir Leute in der Taverne erzählt, dass er auf dem Weg zu Ihrer Siedlung war. Haben Sie ihn zufällig getroffen?";
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
					dialog.text = "Nein, ich brauche deine Dienste nicht! Zumindest solange du Feinde mit "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "In diesem Fall, auf Wiedersehen.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"Du bist "+GetFullName(pchar)+", nicht wahr? Man sagt "+RandPhraseSimple("viel beängstigendes über dich","viel hässliches Zeug über dich")+", und ich will nichts mit dir zu tun haben.";
						link.l1 = RandPhraseSimple("Natürlich - du machst einmal einen Fehler, und jeder wird dir gerne ins Gesicht spucken.",RandSwear()+"Nun, es gibt bessere Dinge zu tun auf See, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"Heh, "+GetAddress_Form(NPChar)+", Ich habe heute keine Zeit für Fracht. Komm morgen wieder.","Komm morgen wieder. Vielleicht mache ich dir ein vorteilhaftes Angebot.");
						link.l1 = "In Ordnung, ich komme morgen zurück.";
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
    							dialog.text = NPCharRepPhrase(npchar,"Dein erbärmlicher alter Trog kann die ganze Ladung nicht aufnehmen, also wird es heute keinen Handel geben.","Leider, Kapitän "+GetFullName(pchar)+", Ich werde ein geräumigeres Schiff für meine Lieferung benötigen.");
    							link.l1 = NPCharRepPhrase(npchar,"Mein Schiff ist anständig, aber ich verstehe, was du meinst. Auf Wiedersehen.","Ich verstehe Ihre Sichtweise, Geschäft ist Geschäft. Auf Wiedersehen.");
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
                                dialog.text = "Oh! Ich wollte dich gerade um einen Gefallen bitten. Siehst du, ich muss die Fracht liefern von "+GetGoodsNameAlt(iTradeGoods)+" in der Menge von "+FindRussianQtyString(iQuantityGoods)+" zur Stadt von "+sNation+sTemp+", und je eher, desto besser. Wenn es Ihnen gelingt, es für "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", dann bei der Ankunft erhalten Sie "+FindRussianMoneyString(iMoney)+" als deine Belohnung. Was sagst du dazu?";
    							link.l1 = "Ich glaube, ich stimme zu.";
    							link.l1.go = "exit_trade";
    							link.l2 = "Das ist wahrscheinlich nicht für mich.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Politische Realitäten im Archipel erlauben es mir nicht zu handeln. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter")+" ist feindselig gegenüber jedem und hat nur mich im Laden gelassen.";
    						link.l1 = "Oh! Es tut mir leid. Viel Glück.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"Verschwinde, ich habe keine Zeit für nutzloses Geschwätz!","Ich habe dir schon gesagt, dass ich nichts für dich habe.");
				link.l1 = NPCharRepPhrase(npchar,"Du musst höflich sein, sonst bringe ich dir Manieren bei!","Oh, es tut mir Leid!");
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
				dialog.text = RandSwear()+"Glaubst du nicht, dass du dich ein bisschen zu spät an diesen Deal erinnert hast? Ich musste die Waren erneut bestellen. Lebewohl.";
				link.l1 = "Verzeih mir, aber ich hatte es eilig. Vielleicht wird mein Ruf wiederhergestellt, wenn ich deine Verluste decke?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Alles Gute.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Tatsächlich! Ich warte schon eine ganze Weile darauf. Du musst mir eine Ladung liefern "+GetGoodsNameAlt(iTradeGoods)+" in Höhe von "+FindRussianQtyString(iQuantityGoods)+" und erhalten dafür "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "Genau.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"Ich muss mich bei Ihnen entschuldigen, "+GetAddress_Form(NPChar)+".  Sie sehen, das Problem ist, dass ich war "+RandPhraseSimple("in einer peinlichen Situation und ich werde nicht in der Lage sein, dich zu bezahlen"," habe diese Ladung bereits zu einem besseren Preis von einem anderen Verkäufer gekauft")+". Als Bezahlung für Ihre Charta schlage ich vor, dass Sie die gesamte Fracht behalten, die Sie geliefert haben.";
				link.l1 = RandSwear()+RandPhraseSimple("Und ich habe diese verfluchte Ladung vor allen Gefahren geschützt! Ich habe wegen ihr zweihundert Ratten getötet!","Du bringst mich in eine Pattsituation, und ich muss zustimmen.");
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
                dialog.text = "Das ist nicht die ganze Lieferung! Laut unserer Abmachung brauche ich "+FindRussianQtyString(iTmp)+" Einheiten mehr.";
				link.l9 = RandPhraseSimple("Ja, in der Tat. Ich werde dann für den Mangel entschädigen müssen. Bis später.",RandSwear()+"Diese verfluchten Ratten haben die Ladung verdorben. Ich werde den Mangel ausgleichen und wieder kommen.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Ausgezeichnet! Hier ist deine Belohnung, Kapitän "+GetFullName(pchar)+".";
				link.l1 = "Es war ein Vergnügen, mit Ihnen zu arbeiten.";
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
			dialog.text = "In Ordnung... Die Summe von "+FindRussianMoneyString(iMoney)+" wird gerade die Schäden decken, die durch die Verletzung der Bedingungen unseres Deals verursacht wurden.";
			link.l1 = "Wow! Nein, das wird nicht gehen! Nie wieder werde ich irgendeine Ladung liefern! Davon gibt es genug Mist auf See!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Hier ist der geforderte Betrag";
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
			dialog.text = "Ausgezeichnet. Jetzt kann ich meinen Kollegen sagen, dass du immer noch vernünftig zu handhaben bist.";
			link.l1 = "Danke! Ich werde Sie nicht noch einmal enttäuschen.";
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

            dialog.text = "Hmm. Ich habe gehört, dass du deine Verpflichtungen aus dem vorherigen Vertrag nicht erfüllt hast - und du fragst nach einem anderen? Du musstest die Fracht liefern von "+LanguageConvertString(iSeaGoods,"seg_"+Goods[iTradeGoods].Name)+" zu "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "Ja, in der Tat! Du hast recht!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", du enttäuschst mich!!! Vielleicht wirst du etwas tun, um dieses Problem zu lösen?";
			link.l1 = "In Ordnung. Ich werde mein Bestes tun, um die Sendung zu liefern.";
			link.l1.go = "exit";
			link.l2 = "Nein, ich kann nicht. Es tut mir leid";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Halt! Es gibt nicht genug Waren an Bord Ihres Schiffes! Du hast nicht "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" Einheiten der Ladung.";
				link.l9 = RandPhraseSimple("Ja, in der Tat. Ich muss dann für den Mangel aufkommen.",RandSwear()+"Die Ratten haben die Ladung verdorben. Ich werde die fehlende Menge kaufen und wieder zurückkommen.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Ich verstehe, ich verstehe... Ich nehme die Lieferung zurück.";
    			link.l1 = "Danke! Ich werde Sie nicht noch einmal enttäuschen!";
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
			dialog.text = "Wovon redest du? Offensichtlich wurdest du irregeführt - ich habe nie in solchen Mengen europäischen Wein gehandelt. Ein-zwei Flaschen, nicht mehr. Aber der lokale Wein ist eine andere Geschichte - davon habe ich genug, und er wird in Ballons verkauft, nicht in Flaschen!";
			link.l1 = "Verdammt! Aber mir wurde gesagt...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Ich habe keine Ahnung, was man Ihnen erzählt hat, aber ich sage es noch einmal: Ich habe keinen europäischen Wein auf Lager. Das ist alles, was ich zu diesem Thema zu sagen habe.";
			link.l1 = "In Ordnung... Ich werde es dann regeln, dann!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Das ist eine andere Geschichte. Sie wissen, verschiedene Typen kommen hierher und stellen unnötige Fragen. Also, wollen wir verhandeln?";
			link.l1 = "Sicher!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Wie viele Flaschen brauchen Sie? Der Preis für eine Flasche beträgt 500 Pesos, und die Mindestmenge sind 20 Flaschen.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Ich habe im Moment nicht genug Geld. Ich komme später zurück.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Ich bin kein Händler, Kapitän. Wenn ich mich recht erinnere, sprachen Sie von einer größeren Partie?";
				link.l1 = "Es tut mir leid... Lass uns dann den Betrag nochmal überdenken.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Leider habe ich nicht so viel.";
				link.l1 = "Schade... Lass uns dann den Betrag noch einmal überdenken.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Flaschen? Gut. Das kostet dich "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Hier, bitte.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Ich habe gerade nicht genug Geld. Ich komme später wieder.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "Das ist in Ordnung, aber versuch nicht zu lange zu brauchen. Diese Sachen sind hier ziemlich beliebt.";
			link.l1 = "Ich komme bald zurück!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Lassen Sie uns sehen... Alles scheint in Ordnung zu sein. Sie können Ihren Kauf abholen.";
			link.l1 = "Danke dir! Viel Glück!";
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
			dialog.text = "Ich hatte vor, ein gutes Geschäft zu machen, aber ich brauche noch eine bestimmte Ware dafür - "+GetGoodsNameAlt(iCGood)+". Das Problem ist, dass diese Ware in unserer Kolonie verboten ist, daher kann ich nicht darauf zählen, sie von Handelskapitänen zu kaufen\nAlles, was ich brauche, sind "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" Einheiten davon. Vielleicht könnten Sie es mir liefern? Ich werde Sie gut bezahlen, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" pro Einheit, was sich auf "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Oh, und ich brauche es nicht später als in "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". Also, wirst du mir helfen?";
			link.l1 = "Hmm... Klingt interessant. Ich stimme zu!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Lieferung von geschmuggelten Waren? Tut mir leid, nicht interessiert.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Ausgezeichnet. Ich bin froh, dass Sie zugestimmt haben. Also, ich werde auf Ihre Rückkehr mit den Waren warten.";
			link.l1 = "Ich werde bald zurück sein!";
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
				dialog.text = "Machst du Witze? Du hast nicht die volle Menge an Waren, die ich brauche!";
				link.l1 = "Es tut mir leid, mein Fehler...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lassen Sie uns sehen, dann. Du solltest eine Ladung liefern "+GetGoodsNameAlt(iCGood)+" in Höhe von "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". Richtig?";
				link.l1 = "Genau, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Danke für Ihre Arbeit. Bitte, nehmen Sie Ihre Bezahlung - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "Danke! Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen.";
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
				dialog.text = "Ups... Kapitän, es scheint, wir haben hier ein Problem...";
				link.l1 = "Was ist es schon wieder?";
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
			dialog.text = "Ich brauche dringend eine Gruppe Sklaven - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" Köpfe. Ich bin bereit zu zahlen "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" Münzen pro Seele, was sich auf "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Ich denke, ich werde zustimmen. Es ist ein lästiges, aber sehr lukratives Geschäft.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Ich bin nicht interessiert.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Genau - es ist sehr profitabel. Nun, dann werde ich auf deine Rückkehr mit meinen Sklaven warten.";
			link.l1 = "Ich werde Sie nicht lange warten lassen. Auf Wiedersehen!";
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
				dialog.text = "Machst du Witze? Du hast nicht alle Sklaven, die ich brauche!";
				link.l1 = "Es tut mir leid, mein Fehler...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lassen Sie uns sehen, dann. Sie sollten mir eine Ladung Sklaven in der Anzahl von "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". Richtig?";
				link.l1 = "Genau, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Danke für Ihre Arbeit. Bitte nehmen Sie Ihre Bezahlung - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+". Also, bitte akzeptieren Sie dies. Ich bin sicher, Sie werden es nützlich finden.";
			link.l1 = "Danke! Es war ein Vergnügen, Geschäfte mit Ihnen zu machen.";
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
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Noch nie davon gehört... Was ist das eigentlich? Ich habe in meiner ganzen Zeit noch nie von so etwas gehört.";
			link.l1 = "Nun, es ist ein Schiffbauerwerkzeug, "+pchar.GenQuest.Device.Shipyarder.Describe+". Hat dir jemand so etwas angeboten?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hmm... Ja, es gab einen seltsamen Kerl. Aber er hat mir nicht gesagt, was das Ding war, er hat nur versucht, es mir zu verkaufen. Aber wofür würde ich es brauchen, wenn ich keine Ahnung habe, wofür es ist? Wie könnte ich es weiterverkaufen? Also, ich habe einfach abgelehnt.";
				link.l1 = "Und wie sah er aus und wohin ist er gegangen? Ich brauche dieses Instrument dringend.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nein, nichts dergleichen. Entschuldigung, ich kann dir nicht helfen. Frag herum.";
				link.l1 = "Ich verstehe. Nun - es ist Zeit, herumzufragen!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Wettbewerb... Ohne ihn gibt's kein Geschäft. Gierige Bastarde, die versuchen, in dein gemütliches Geschäft einzudringen und alle möglichen niederträchtigen Methoden verwenden, um Kundschaft an sich zu ziehen\nAber das sind nur Worte. Tatsächlich möchte ich dich bitten, mir zu helfen, einen meiner Konkurrenten loszuwerden. Nein, töten ist nicht nötig. Einfach sein Schiff mit Ladung kapern oder versenken.";
			link.l1 = "Hmm... nun, wenn du gut bezahlst, kann ich das arrangieren.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Nein, ich mische mich nicht in eure kaufmännischen Streitereien ein. Versenkt euren Rivalen ohne meine Hilfe.";
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
			dialog.text = "Sehr gut. Also, der Name Ihres Mannes ist "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Vor kurzem hatte er ausgesandt "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")+"Konto"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"mit einer Ladung von "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+". Er hat ziemlich viel Geld für diese Ladung bezahlt, also wird der Verlust ganz schön an seinem Geldbeutel kratzen.";
			link.l1 = "Und könnten Sie mir sagen, wo genau ich diesen 'Freund' von Ihnen suchen soll?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "Mein 'Freund' ist derzeit in seinem Zuhause in "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Du brauchst ihn nicht - du brauchst sein Schiff, das, wie ich herausgefunden habe, nach etwa "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" wird in der Nähe vorbeifahren "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". Sie können es versenken, können es durch Entern nehmen - das spielt keine Rolle. Die Hauptsache ist, sicherzustellen, dass das Schiff und die Ladung nicht mehr im Besitz von "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Und es ist mir egal, wer es beansprucht - du oder das Meer. Für diese Arbeit werde ich dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = "Ich habe es. Nun, dann ist es Zeit zu gehen!";
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
			dialog.text = "Ausgezeichnet! Ich wusste, dass ich mich auf dich verlassen konnte. Ich werde wohl nicht nach dem Verbleib dieses Schiffes und der Ladung fragen. Das geht mich schließlich nichts an. Und mein Freund wird einige Zeit brauchen, um sich von so einem Schlag zu erholen, he-he. Hier, bitte nimm dein Geld - und danke für die großartige Arbeit.";
			link.l1 = "Gerne... Bis dann, "+npchar.name+"!";
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
			dialog.text = "Armer "+pchar.GenQuest.Sunplace.Trader.Enemyname+", was für ein grässliches Schicksal! Und obwohl indirekt, bin ich die Ursache seines Untergangs! Du verstehst nicht, Kapitän! Habe ich dich gebeten, ihn zu töten? Ich hatte geplant, dass er nach dem Verlust des Geldes, das für die Ladung ausgegeben wurde, wieder... nun, egal... Du...";
			link.l1 = "Hör zu, hör auf zu jammern, ja? Du hast mich gebeten, dich von einem Rivalen zu befreien - ich habe es getan. Noch besser - selbst wenn er die Ladung verloren hat, könnte er immer noch reich werden und dein Geschäft weiter schädigen. Jetzt kann er als toter Mann nicht mehr viel tun.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Das ist es! Genug! Ich will diese blasphemischen Reden nicht mehr hören! Nehmen Sie Ihr verdammtes Geld und verlassen Sie sofort meinen Laden!";
			link.l1 = "He, "+npchar.name+", beruhige dich, willst du? Oder ich werde dein Temperament selbst abkühlen - mein Säbel ist immer an meiner Seite! Nun ja, erschrick nicht, ich habe nur Spaß gemacht. Hör zu, es tut mir leid, dass es so gekommen ist - aber du hast mich zuerst in die Irre geführt. Lebewohl.";
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
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? Ja, ich kenne ihn. Er hat Proviant für sein Langboot bei mir gekauft. Tagsüber fischt er meistens irgendwo in abgelegenen Buchten, aber jeden Abend ist er in der Taverne zu finden.","Du hast mich bereits über diesen Mann befragt, und ich habe dir alles erzählt, was ich wusste!","Bist du am Scherzen oder bist du wirklich ein Idiot?! Du stellst zum dritten Mal dieselben Fragen!","Nur zu denken, wie so ein Idiot zum Kapitän wurde...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Danke, du hast mir ungemein geholfen!","Ja, ja, gut.","Nun, nun, reg dich nicht so auf. Ich habe es einfach vergessen.","Nun, er hat es getan, wie du sehen kannst...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Ich weiß nicht, was die Leute in der Taverne von Port Royal gesagt haben, aber ich habe diesen Mann nie in meinem Laden getroffen. Tatsächlich habe ich ihn nirgendwo gesehen. Frag im Dorf herum - vielleicht wird dir jemand etwas erzählen...","Du hast mich schon nach diesem Mann gefragt, und ich habe dir gesagt: Ich weiß es nicht!","Bist du am Scherzen oder bist du wirklich ein Idiot?! Du stellst schon zum dritten Mal dieselben Fragen!","Nur zu denken, wie so ein Trottel Kapitän wurde...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ich verstehe. Nun, danke trotzdem.","Ja, ja, gut.","Jetzt, jetzt, reg dich nicht so auf. Ich habe es einfach vergessen.","Nun, er hat, wie du sehen kannst...",npchar,Dialog.CurrentNode); 
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
			dialog.text = "Mein Herr, was ist los mit Ihnen, junger Mann! Bitte, seien Sie zurückhaltender und wählen Sie Ihre Worte sorgfältig, wenn Sie über angesehene Leute sprechen! Gerard LeCroix hat Guadeloupe mit einer Expedition zum Festland verlassen, aber er hat Ihre Belohnung hier für Sie hinterlassen. Sind Sie jetzt zufrieden?";
			link.l1 = "Hm... Entschuldigen Sie mich bitte, Monsieur. Ich habe mich ein wenig erhitzt...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Sehr gut. Herr Lecroix hat Ihre Belohnung dem örtlichen Leuchtturmwärter überlassen - sie sind alte Freunde. Sie müssen ihn nur besuchen und die fällige Zahlung einsammeln. Monsieur Lecroix ist ein ehrlicher Mann, also denke ich, dass Sie mit Ihrer Belohnung zufrieden sein werden.";
			link.l1 = "Habe es verstanden, danke! Dann gehe ich zum Leuchtturmwärter. Jetzt lass mich eine Pause machen.";
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
			dialog.text = "Ja, er war hier und hat auf dich gewartet. Aber wahrscheinlich war die Aufgabe, die er dir anvertraut hat, schwieriger als ursprünglich erwartet, also hat er nicht gewartet und ist auf eine Expedition zum Festland aufgebrochen. Er hat deine Belohnung bei einer vertrauenswürdigen Person hinterlassen.";
			link.l1 = "Ja, ich hatte wirklich unvorhergesehene Umstände, aber ich habe die Aufgabe erfolgreich abgeschlossen. Schön zu hören, dass meine Zahlung auf mich wartet. Bei wem kann ich sie abholen?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "Herr Lecroix hat Ihre Belohnung dem örtlichen Leuchtturmwärter überlassen - sie sind alte Freunde. Sie müssen ihn nur besuchen und die fällige Zahlung einsammeln. Monsieur Lecroix ist ein ehrlicher Mann, also denke ich, dass Sie mit Ihrer Belohnung zufrieden sein werden.";
			link.l1 = "Habe verstanden, danke! Dann gehe ich zum Leuchtturmwärter. Jetzt lasst mich eine Pause machen.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "Viel Glück, Monsieur.";
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
			dialog.text = "Gott, warum bist du so laut, junger Mann! Beruhige dich und hüte deine Zunge, wenn du über angesehene Leute sprichst! Gerard LeCroix hat Guadeloupe mit einer Expedition zum Festland verlassen, aber für dich hat er eine Nachricht hinterlassen\nHaben Sie sich beruhigt, Herr? Bereit, mir zuzuhören?";
			link.l1 = "Hm... Entschuldigen Sie bitte, mein Herr. Ich habe mich ein wenig erhitzt. Ich höre zu.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Sehr gut. Versuchen Sie das nächste Mal zuerst zu fragen und dann laut zu schreien. Also... Kennen Sie einen Mann namens Simon Maurois?";
			link.l1 = "Ha! Jeder hat von Simon Maurois gehört! Natürlich kenne ich ihn.";
			link.l1.go = "trial_2";
			link.l2 = "Noch nie von ihm gehört. Wer ist er?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Ausgezeichnet. Dann geh zu ihm. Er hat die Expedition von Monsieur Shoke finanziert, daher kannst du deine Belohnung von ihm einholen. Also, war es wirklich notwendig, sich so aufzuregen?";
			link.l1 = "Noch einmal, ich bitte um Ihre Verzeihung... Danke für Ihre Hilfe, monsieur. Ich werde sofort Monsieur Maurois sehen!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "Er ist der Besitzer des Maurois Bankhauses und der Leiter der Filiale in Capsterville. Also musst du nach Saint-Christopher gehen und die Bank von Capsterville besuchen. Es war Monsieur Maurois, der die Expedition von Monsieur Shoke finanzierte, so kannst du deine Belohnung von ihm einholen. Also, war es wirklich nötig, sich so aufzuregen?";
			link.l1 = "Noch einmal bitte ich um Ihre Verzeihung... Danke für Ihre Hilfe, mein Herr. Ich werde sofort Monsieur Maurois aufsuchen!";
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
			dialog.text = "Ach, der unternehmungslustige Händler! Man sieht sofort den geschäftlichen Ansatz. Ich respektiere es. Sicher, ich habe die Ware, die du brauchst.";
			link.l1 = "Ich bin sicher, dass ich es mit Gewinn verkaufen kann. Soweit ich weiß, besteht eine gute Nachfrage nach diesem Gut in Porto Bello. Wie viel wird es mich kosten?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "So lala... Also, dreihundert Einheiten Kaffee... Und die gleiche Menge Kakao... Das wird dich kosten..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" Pesos!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Hmm... Entschuldigen Sie, ich scheine nicht genug Geld zu haben. Warten Sie bitte: Ich laufe jetzt zum Schiff um Geld zu holen - und ich komme gleich wieder!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Hier, bitte.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Warten Sie eine Minute, Senor. Es scheint, dass Sie nicht genug Platz auf Ihrem Schiff für solch eine Party haben. Räumen Sie den Laderaum aus und kommen Sie zurück.";
				link.l1 = "Oh, ich habe vergessen zu entladen! Warte eine Minute - Ich komme gleich!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Großartig! Ich werde sofort den Befehl geben, die Waren auf Ihr Schiff zu laden. Es ist ein Vergnügen, Geschäfte mit Ihnen zu machen!";
				link.l1 = "Gegenseitig, senor! Und jetzt lasst mich gehen: Dinge warten nicht.";
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
			dialog.text = "Die Waren warten auf Sie. Haben Sie Geld mitgebracht?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Noch nicht. Ich wollte nur sicherstellen, dass Ihr Angebot noch steht. Und das Geld wird bald kommen.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Hier, bitte.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "Im Moment benötige ich Ihre Dienste nicht.";
			link.l1 = "Schade. Lass uns das Thema wechseln.";
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
