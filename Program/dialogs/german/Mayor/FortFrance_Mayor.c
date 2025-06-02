// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was wünscht Ihr? Fragt nur.","Ich höre Ihnen zu, was ist die Frage?"),"Es ist das zweite Mal, dass Sie versuchen zu fragen...","Es ist das dritte Mal, dass Sie wieder versuchen zu fragen...","Wann wird es enden?! Ich bin ein beschäftigter Mann, der an den Angelegenheiten der Kolonie arbeitet und Sie versuchen immer noch, etwas zu fragen!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Herr, ich habe eine Banditenleiche im Dschungel gefunden. Er wurde von den Indianern getötet. Es gab Ohrringe an seinem Körper, sieht so aus, als wären sie aus Europa hierher gebracht worden. Vielleicht gehörten sie einem der Adligen in Ihrer Stadt?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Eure Exzellenz, die Tat ist vollbracht! Ich bedauere jedoch, Ihnen mitteilen zu müssen, dass der Verbrecher das Gefecht nicht überlebt hat und daher nicht hingerichtet wird.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Eure Exzellenz, die Aufgabe ist erledigt! Der Gefangene erwartet sein Schicksal in meinem Verlies.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Ich bin auf Befehl von Gouverneur General Philippe de Poincy eingetroffen, um das Kommando über Ihre bewaffnete Fregatte zu übernehmen.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Ich bin bereit, die Fregatte in mein Geschwader aufzunehmen.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Ich bin auf Ihre Einladung hin gekommen, Monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "Es war bedauernswert, Monsieur";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Exzellenz, ich bin in den Besitz von Informationen über unerlaubten Handel gelangt, der bald an diesen Ufern stattfinden wird. Ich wage zu behaupten, dass diese Angelegenheit Ihrer Aufmerksamkeit würdig sein könnte.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Exzellenz, ich komme, um Neuigkeiten über jenes Schmugglerschiff zu erfahren, über das wir gesprochen haben.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Lassen Sie uns sehen, was Sie haben... Unglaublich! Es ist einfach unglaublich, Charles! Das sind die Ohrringe meiner Frau. Ich hatte sie ihr geschenkt, bevor ich Europa verließ und in die Kolonien kam. Sie verschwanden vor ein paar Monaten unter mysteriösen Umständen. Ich wusste, sie waren gestohlen!\nCharles, ich bin sehr froh, dass Sie direkt zu mir gekommen sind und das, was mir so lieb ist, nicht an die Händler verkauft haben. Ich werde Ihnen Ihren Gefallen vergelten. Wie ich gehört habe, wollen Sie ein Schiff kaufen? Da Sie sich entschieden haben, zur See zu fahren, werden Sie zweifellos eine Karte unseres Archipels benötigen. Hier, nehmen Sie sie. Ich bin sicher, sie wird Ihnen nützlich sein!";
			link.l1 = "Danke, Eure Gnaden!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "Das ist bedauerlich, Charles, aber wir müssen mit der gegebenen Situation zurechtkommen. Hier ist deine Belohnung: fünftausend Pesos, nach Steuern.";
			link.l1 = "Ich freue mich, St. Pierre und Sie persönlich zu dienen. Obwohl die Schlacht schwierig war, fand ich doch etwas Vergnügen darin.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "Es war eine herausfordernde Schlacht, Euer Exzellenz. Mein Schiff hat erheblichen Schaden erlitten. Wäre es möglich, mich für meine Verluste zu entschädigen?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravo, Charles! Ich habe keinen Zweifel, dass du in unseren Reihen weit aufsteigen wirst.";
			link.l1 = "Bis wir uns wiedersehen, Eure Exzellenz.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Ich muss sagen, ich bin ein wenig überrascht von Ihrer Anfrage, Charles... Nun gut, betrachten Sie weitere zweitausend Pesos von mir persönlich als Zeichen des guten Willens. Lebewohl.";
			link.l1 = "Danke, Eure Exzellenz.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Ausgezeichnet, Charles! Sie werden erfreut sein zu erfahren, dass Ihr Erfolg Ihren maltesischen Freunden bei einer heiklen Operation helfen wird... Hier ist Ihre Belohnung: achttausend Pesos, nach Steuern.";
			link.l1 = "Ich freue mich, St. Pierre, den Orden und Sie persönlich zu dienen. Obwohl der Kampf herausfordernd war, fand ich doch eine gewisse Zufriedenheit darin.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "Es war eine harte Schlacht, Eure Exzellenz. Mein Schiff erlitt erheblichen Schaden. Könnte ich um Entschädigung für meine Verluste bitten?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravo, Charles! Ich bin zuversichtlich, dass du weit kommen wirst.";
			link.l1 = "Bis wir uns wiedersehen, Eure Exzellenz";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Ich nehme an, Sie haben es verdient. Behalten Sie weitere zweitausend von mir persönlich als Zeichen des guten Willens. Danke, mein Freund.";
			link.l1 = "Danke, Eure Exzellenz.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Das Schiff ist bereit, aber Sie haben keinen freien Platz dafür in Ihrer Staffel. Kapitän, verkleinern Sie Ihre Staffel und kehren Sie zurück, dann werde ich Ihnen sofort die Fregatte geben.";
				link.l1 = "Gut.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Ja, natürlich, das Schiff ist bereit zum Auslaufen. Sein Kapitän ist informiert und wird all Ihren Befehlen folgen.";
				link.l1 = "Dann brechen wir auf. Auf Wiedersehen, Euer Gnaden.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Ausgezeichnet. Bereiten Sie sich darauf vor, Ihr neues Schiff zu begrüßen. Der Kapitän ist informiert und wird all Ihren Befehlen folgen.";
			link.l1 = "Dann brechen wir auf. Auf Wiedersehen, Eure Gnaden.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Kapitän Charles de Maure, endlich! Ich habe Sie sehnsüchtig erwartet! Bitte, kommen Sie herein, gesellen Sie sich zu mir.";
			link.l1 = "Einen guten Tag auch Ihnen, Eure Exzellenz. Hinter solch einer Höflichkeit von Ihnen steckt immer ein Grund. Was ist es diesmal? Piraten, Spanier, Rothäutige Kannibalen?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Seien Sie nicht ironisch, Kapitän. Es ist nicht meine Schuld, dass wir immer in Schwierigkeiten geraten, Sie und ich. Aber bitte, machen Sie sich keine Sorgen, dieses Mal wird es wahrscheinlich keine Schießerei geben...";
			link.l1 = "Sie faszinieren mich, fahren Sie fort. Wie kann ich Ihnen behilflich sein?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Haben Sie jemals von Madame Botots feinem Etablissement gehört? Während der Belagerung wurde unser... Bordell bis auf die Grundmauern niedergebrannt. Eines Tages bot sich eine gewisse Dame an, es wieder aufzubauen.";
			link.l1 = "Ein Brand in einem Bordell und ohne mich? Übrigens wurde ich an diesem Tag auch von den Spaniern erschossen.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Verdammt nochmal, Charles, was ist heute mit dir los? Dein Witz ist unangebracht! Auch wenn es sich nicht um eine Staatsangelegenheit handelt, ist es dennoch eine wichtige Angelegenheit für mich persönlich! Ich brauche deine Hilfe! Um Gottes willen, reiß dich zusammen und hör mir zu!";
			link.l1 = "Verzeihen Sie mir, Eure Exzellenz. Ich verspüre eine große Erleichterung, das ist alles. Um ehrlich zu sein, ich bin all dieser ständigen Kämpfe und Kämpfe müde. Ich erwartete, dass Sie mich in einen weiteren Kreis der Gewalt hineinziehen würden. Bitte machen Sie weiter. Noch nie von dieser Madame Botot gehört.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Also, diese ehrenwerte Dame hat das Etablissement auf ein völlig neues Niveau gehoben. Es ist jetzt ein Ort der hohen und edlen Gesellschaft, nicht mehr ein Rattenloch, wie es früher war. Ein Ort der ausgezeichneten Laster, teuren Weins und unbeschränkten Glücksspiels. Sie werden alles selbst sehen!";
			link.l1 = "Eure Exzellenz, ich bin kein Prüde und Ihre Beschreibung war sehr farbenfroh, aber warum erzählen Sie mir das?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Weil Sie auf der Liste stehen, warum sonst?! Sehen Sie, ich fühle mich schuldig für die Marquise und versprach, Sie morgen auf einer ihrer Partys vorzustellen. Juliana macht das nicht oft, also seien Sie bitte so nett, uns beizutreten. Dieses Mal kein Kampf, Schießen und Verfolgen, ich verspreche es. Alles wird höflich und würdevoll sein: Wein, wunderschöne Frauen, Karten und andere noble Vergnügungen.";
			link.l1 = "Karten und Dirnen. Es ist eine Weile her, in einem anderen Leben. Ich folge Ihnen immer noch nicht. Warum ich?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Bist du taub? Juliana Botot, sie... sammelt leuchtende und berühmte Gesichter. Sie machen ihre Partys besonders und frisch. Du hast dir einen ziemlichen Namen gemacht, die Marquise hat lange darauf gewartet, dich als ihren Gast zu bekommen. Mein Fehltritt gab ihr die Möglichkeit und ich werde es nicht hinnehmen, wenn sie sich weigert, mich wieder zu empfangen. Das ist alles, was ich bekomme, wenn ich dich nicht zu ihr bringe!";
			link.l1 = "Ihre Exzellenz, Sie sind ein attraktiver Witwer und Gouverneur... Warum kümmern Sie sich überhaupt um die Meinung einer Kurtisane? Sie sind es, die Ihre Gunst suchen sollten, nicht umgekehrt.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Marquise Botot steht unter dem Schutz des Grafen Henry de Levi-Vantadur - der, durch die Gnade Seiner Majestät, das Oberhaupt der Staaten von Neu-Frankreich in Nordamerika ist. Glaube mir, Charles, niemand hier möchte ihm über den Weg laufen.";
			link.l1 = "Fast hätten Sie mich hier gehabt - ich dachte, es geht nur um Lust und Liebe. Jetzt sehe ich, dass es die ganze Zeit um Politik ging. Banal, aber erwartet. Sehr gut, ich werde Ihnen helfen. Es wird süß sein, für eine Nacht in die Tage meiner Jugend zurückzukehren.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Kapitän, Sie sind ohne Zweifel ein erfahrener Mann, versuchen Sie jedoch nicht, sich als Alter zu geben. Es geht nicht nur um Politik. Ich schätze Julianas Anwesenheit und bin dankbar für Ihre Hilfe. Es ist mir persönlich wichtig, wirklich. Kommen Sie morgen nach Einbruch der Dunkelheit zum Platz der Marquise Botot. Ich verspreche Ihnen, dass die Politik die Nacht nicht verderben wird.";
			link.l1 = "Wein, Karten, Frauen. Ganz wie in den guten alten Zeiten. Auf Wiedersehen, Eure Exzellenz!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, was ist passiert, du siehst aus wie die Hölle!";
			link.l1 = "Angerran, verdammt, Chievous, Exzellenz. Er hat meine Fregatte letzte Nacht gestohlen. Er hat meine Preisbesatzung getötet und segelte im Nebel davon.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "Es ist eine unangenehme Wendung der Ereignisse, ich verstehe, aber vertraue mir - ein solches Ergebnis ist durchaus zufriedenstellend. Sie benötigen keine dringenden Schiffe und Männer, während de Levi Vantadur eine erhebliche Summe zahlen wird, um die Wahrheit hinter einem bestimmten kürzlichen Duell zu verbergen. Oder er wird sich kostenlos an unsere Rolle bei der Vertuschung erinnern, was auch sehr viel wert ist. De Chievous hat zweimal unehrliche Dinge getan, aber er ist jetzt weit weg, während wir immer noch anständige Karten gegen ihn haben.";
			link.l1 = "Dreimal, Eure Exzellenz. Angerran gab zu, dass er während unseres Kartenspiels betrogen hat. Aber er wird mich nicht mit Geld abspeisen, wenn Sie das meinen. Er hat eine Grenze überschritten. Auf diesem Schiff heute Morgen war eine bestimmte Person... sie ist mir sehr lieb! Ich werde nicht zulassen, dass der Bastard ihr Schaden zufügt! Hörst du das, Jacques, ich werde es nicht zulassen!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Ich glaube, ich weiß, von wem du sprichst - ich erinnere mich daran, dich mit einem... Mädchen gesehen zu haben, gekleidet wie ein Mann und bewaffnet bis an die Zähne wie ein Pirat. Charles, sei kein Idiot! Du hattest Glück, du hast großen Ärger vermieden und was, du versuchst dich wieder in sie hineinzuziehen? Lass es sein. De Chievous ist auf der Flucht - Gott sei Dank! Und was deine 'Freundin in Waffen' angeht - nimm den Rat deines Freundes an - geh zu Julianna und vergiss all das.";
			link.l1 = "Ausgeschlossen, Eure Exzellenz. Einige Dinge liegen einfach jenseits Ihres Verständnisses, in Ordnung? Erzählen Sie mir jetzt alles, was Sie über den Bastard wissen. Wo könnte er von Saint Pierre aus hingehen? Und versuchen Sie nicht, mich wieder abzubringen - ich habe mich mit der niederländischen Handelsgesellschaft angelegt, mit Piratenbaronen, Generalgouverneuren, sogar mit der Heiligen Inquisition! Ich bin kein leicht zu verängstigender Mann. Ich werde sie zurückholen, koste es was es wolle!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, haben Sie jemals darüber nachgedacht, wer die Generalgouverneure ernennt? Das ist eine völlig andere Welt! Sie haben sie kaum berührt, sie ist jenseits Ihres Verständnisses, Sie sind wie ein Kind in einem Pulverlager. Und Sie bitten mich, Ihnen eine brennende Kerze zu reichen. Was die Generalgouverneure betrifft: de Poincy selbst überkreuzt den Grafen weder in Geld- noch in Politikfragen. Vizekönig, der Begriff, der bei den einfachen Leuten so beliebt ist, würde Henri de Levi Vantadur gut stehen.";
			link.l1 = "Und hier bin ich, beabsichtige, seinen einzigen männlichen Erben zu häuten, ich weiß, was ich hier riskiere. Nun, sag mir einfach: Gibt es irgendetwas Nützliches, das du weißt, das mir helfen könnte?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "In anderen Zeiten würde ich diese Bewegung zu deiner Pistole als ein Ende unserer Freundschaft ansehen, Charles. Aber ich verstehe deinen derzeitigen Geisteszustand. Deshalb bin ich bereit, dies zu vergessen. Ich weiß nichts Nützliches für dich, die Fregatte ging früh am Morgen nach Westen. Du solltest der Marquise einen Besuch abstatten... Warte, nicht so! Julianna weiß viel über deinen Feind und sie war persönlich... eine Zeit lang mit seinem Vater bekannt. Frag sie. Im Gegensatz zu mir wird sie dich nicht aufhalten.";
			link.l1 = "Das ist der Plan. Auf Wiedersehen, Exzellenz. Danke für Ihre Zeit.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Schmuggelware, sagen Sie? Hmm... höchst faszinierend. Bitte, erleuchten Sie mich mit den Einzelheiten Ihrer Entdeckung.";
			link.l1 = "Vor drei Tagen sollte ein mit Schmuggelware beladenes Schiff in der Le-Marin-Bucht vor Anker gehen. Das Schiff hat sein Rendezvous versäumt, aber ich habe triftige Gründe zu glauben, dass es bald noch in den Hafen einlaufen wird. Vielleicht könnten Ihre Männer diesen Briganten bei ihrer Ankunft einen gebührenden Empfang bereiten, Exzellenz.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;
		
		case "VPVL_Magor_2":
			dialog.text = "Ein namenloses Schiff mit unbenannter Ladung... Und Sie vermuten, dass ich die Streitkräfte Seiner Majestät aufgrund solch nebulöser Informationen entsenden sollte?";
			link.l1 = "Exzellenz, ich gestehe, dass die Einzelheiten spärlich sind. Aber ich bitte Sie, mir zu erlauben, zu erzählen, wie diese Informationen in meinen Besitz gelangten. (erzählt)";
			link.l1.go = "VPVL_Magor_3";
		break;
		
		case "VPVL_Magor_3":
			dialog.text = "Nun gut, wir werden Ihre Informationen auf die Probe stellen. Sollte tatsächlich ein Schiff mit Schmuggelware vor den Küsten von Le Marin ankern, werden Sie, Kapitän, für Ihren Dienst an der Krone großzügig belohnt. Kommen Sie in drei Tagen wieder zu mir. Bis dahin wird sich der Nebel der Ungewissheit gelichtet haben.";
			link.l1 = "Ausgezeichnet. Dann sehen wir uns in drei Tagen wieder.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;
		
		case "VPVL_Magor_4":
			dialog.text = "Ah, Kapitän! Es ist mir eine Freude, Sie wieder zu empfangen. Ihre Informationen haben sich als äußerst wertvoll erwiesen. Meine Männer haben das Schiff genau dort abgefangen, wo Sie es angegeben haben. Hier—einhundertfünfzig spanische Dublonen, frisch geprägt und schwer im Beutel. Nehmen Sie sie mit meinem Dank entgegen.";
			link.l1 = "Ich bin Ihnen für Ihre Erwägung sehr dankbar, Exzellenz. Es ist ein Glück, dass mein Bröckchen an Informationen den Interessen der Krone gedient hat. Sollte sich die Gelegenheit erneut bieten, so wisset, dass mein Schwertarm und mein scharfes Auge zu Eurer Verfügung stehen.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;
		
		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;
		
		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
