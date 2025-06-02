#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Sehen Sie, Herr, möchten Sie nicht eine amüsante Kleinigkeit kaufen? Es ist günstig, nur ein paar tausend Pesos...";
				link.l1 = "Hmm. Wahrscheinlich hast du dieses 'kleine Ding' gestohlen, und jetzt versuchst du, es loszuwerden?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Hallo. Mein Name ist "+GetFullName(npchar)+". Ich vermute, du bist nicht froh mich zu treffen, aber vielleicht wirst du zumindest meinen Namen in Erinnerung behalten...","Grüße, "+GetAddress_Form(NPChar)+". Mein Name ist "+GetFullName(npchar)+".","Mein Name ist "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". Schön, dich zu treffen.");
				link.l1 = RandPhraseSimple("Grüße.","Hallo.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "He, hör zu, möchtest du ein paar tausend Pesos verdienen statt dieser erbärmlichen Almosen?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Dieser Anhänger mit der Kamee... Wo hast du ihn gefunden?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Schau, wie tief ich gefallen bin...","Von Almosen zu leben ist nicht einfach...","Ich würde alles geben, um aus dieser Armut herauszukommen!","Du schon wieder?..","Block",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Ich verstehe. Nun, kein großes Ding.","Natürlich. Nun, du weißt, der größte Mann in der Geschichte war der ärmste.","Dann solltest du anfangen, etwas zu tun, nicht den ganzen Tag hier sitzen.","Aha. Nerv ich dich schon?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Was brauchst du?","Was willst du?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "He, hör mal, möchtest du lieber ein paar tausend Pesos verdienen anstatt dieser erbärmlichen Almosen?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Dieser Anhänger mit der Kamee... Wo hast du ihn gefunden?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Können Sie mir etwas Interessantes erzählen?","Was gibt's Neues in der Stadt?","Oh, ich würde gerne die neuesten Klatsch und Tratsch hören...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Nein, warum, schon genervt? Ich bin nicht besonders beschäftigt, wie du sehen kannst...","Macht mich nur müde. Obwohl arm, bin ich immer noch ein Mann.");
			link.l1 = "Heh, ich sehe...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, "+GetAddress_Form(NPChar)+", Leute sagen viele hässliche Dinge über dich. Aber ich glaube immer an Menschen - sogar an solche wie dich. Bitte, gib mir Almosen für Brot und Wasser, hab Erbarmen mit mir.","Ich bitte dich, "+GetAddress_Form(NPChar)+"! Bitte, wende dich nicht ab von einem armen Mann, gib Almosen für eine Mahlzeit...");
				link.l1 = RandPhraseSimple("Ich gebe dir nichts.","Du wirst es ohne Geld schaffen.");
				link.l1.go = "exit";
				Link.l2 = "In Ordnung, und wie viel brauchst du genau?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("Von dir? Nichts.","Ich brauche nichts, "+GetAddress_Form(NPChar)+", danke.");
				link.l1 = RandPhraseSimple("Hmm, in Ordnung.","Anscheinend ist dein Leben gar nicht so schlecht, Kumpel.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Ich würde nicht einmal einen lumpigen Kupfer ablehnen, "+GetAddress_Form(NPChar)+". So viel wie Ihre Börse und Ihre Gnade geben können...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Die Schwachen und Müden zu verspotten ist eine Sünde...";
				link.l1 = "Ha-ha-ha! Du dachtest einen Moment, ich würde dir Geld geben, du verrückter Bettler?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Danke dir für "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+". Jetzt kann ich mit diesem Geld etwas Brot kaufen...";
				link.l1 = "Hier, Landstreicher - geh dich ein bisschen stärken.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Danke, "+GetAddress_Form(NPChar)+". Ich kann jetzt eine Woche mit diesem Geld leben!";
				link.l1 = "Es war mir ein Vergnügen zu helfen.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Danke, "+GetAddress_Form(NPChar)+". Ich werde allen von deiner Güte erzählen!";
				link.l1 = "Das ist wirklich nicht notwendig.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Danke, geehrter "+GetSexPhrase("Herr","Dame")+" "+GetAddress_Form(NPChar)+". Möge der Herr über dich wachen...";
				link.l1 = "Ja, Sein Schutz würde sicherlich nicht schaden!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Danke, "+GetSexPhrase("sehr geschätzter Herr","sehr verehrte Dame")+" "+GetAddress_Form(NPChar)+". Ich wünsche Ihnen alles Gute!";
				link.l1 = "Danke, Kumpel.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Hör zu, "+GetAddress_Form(NPChar)+", bist du verrückt oder was? Du gibst mir "+FindRussianMoneyString(iTemp)+"! Ich kann solches Geld nicht annehmen, sicherlich gibt es einen Haken... Lass mich in Ruhe!";
				link.l1 = "Nun, wie du wünschst...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Fünfundzwanzigtausend akzeptiert ... Dieses Geld wird für Lelya und mich für ein ganzes Jahr reichen!";
				link.l1 = "Lebe erst dieses Jahr...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Hör zu, "+GetAddress_Form(NPChar)+", bist du verrückt oder was? Du gibst mir "+FindRussianMoneyString(iTemp)+"! Ich kann solches Geld nicht annehmen, sicherlich muss es einen Haken geben... Lass mich in Ruhe!";
				link.l1 = "Nun, wie du willst...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Eine dumme Frage, Senor! Natürlich würde ich! Aber... was muss ich tun? Sicherlich geben Sie mir das Geld nicht nur für mein schönes Lächeln.";
			link.l1 = "Natürlich nicht. Hör jetzt zu. Ich handle im Auftrag des Gouverneurs selbst. Seine Gnaden vermuten, dass jemand auf der Werft absichtlich den Start von 'Alacantara', seiner Galeone, sabotiert. Und seine Verdächtigungen wurden nur stärker, nachdem kürzlich ein französischer Spion gefasst wurde...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Seine Gnaden hat bereits die Ausreden des Schiffsbauers gehört, aber er ist sich nicht sicher, ob er die Wahrheit sagt. Wir müssen herausfinden, wer die Arbeit sabotiert und warum. Geh zu den Docks, sieh dich um und frag die Arbeiter, warum zum Teufel die 'Alacantara' immer noch nicht segelfertig ist...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Niemand wird dich verdächtigen, du könntest sogar einen Haufen Tabak erbeuten. Was mich betrifft, wird mir niemand etwas erzählen. Jeder wird wissen, für wen ich arbeite. Wenn du es schaffst, etwas Würdiges zu erfahren, erhältst du dreitausend Pesos. Genug, um deinen 'Job' mindestens einen Monat lang aufzugeben.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Dreitausend Pesos? Aber, geschätzter Herr...";
			link.l1 = "Handelst du mit mir oder was? Oh, und wenn du herausfindest, wer hinter all diesen Verzögerungen steckt, bekommst du noch zweitausend dazu. Abgemacht?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "In Ordnung, señor. Sollte nicht zu schwierig sein - viele meiner alten Kumpels arbeiten heutzutage an den Docks. Hey, ich war auch mal lange Zeit Seemann. So, vor zehn Jahren...";
			link.l1 = "Du wirst mir später deine Lebensgeschichte erzählen können. Triff mich nach elf Uhr nachts am Pier. Jetzt geh.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 22.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1 = "Timer";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.hour  = 6.00;
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition = "Trial_ReturnPoormanNorm";
			//SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Guten Abend, Senor...";
			link.l1 = "Also? Hast du etwas herausgefunden?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "Ich habe, senor, ich habe. Nicht sicher, wie es sich mit dem vereinbart, was Sie mir erzählt haben... Haben Sie das Geld mitgebracht? Fünftausend Pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Mach dir keine Sorgen. Hier ist dein Geld. Jetzt spuck es aus.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Erst die Informationen, dann das Geld. Los, verschwende nicht meine Zeit!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Sie versuchen, mich zu betrügen, Senor! Wenn Sie nicht zahlen wollen - fragen Sie jemand anderen selbst. Und denken Sie nicht einmal daran, nach Ihrem Schwert zu greifen, oder ich rufe die Wachen!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Also so läuft das: 'Alcantara' ist schon lange segelbereit, wurde aber absichtlich und auf Anordnung des Gouverneurs selbst nicht beladen. So wurde es mir jedenfalls gesagt. Und die Zimmerleute erledigen jetzt alle möglichen kleinen Arbeiten, die die Abfahrt des Schiffes nicht beeinträchtigen.\nJeder wartet auf die Ankunft irgendeiner Bark aus Cartagena. Die Sache ist, dass 'Alcantara' nach Meinung ihres Kapitäns einen unzureichenden Vorrat an Schießpulver hat. Also bleibt das Schiff hier und wartet tagelang, bis 'Puebla' Schießpulver bringt.\nAber jeder denkt, dass all dieses Warten nur Zeitverschwendung ist, also wenn 'Puebla' nicht in drei Tagen ankommt, wird 'Alcantara' den Anker ohne das Schießpulver lichten...";
			link.l1 = "Ist das so? Und wer hat dir das gesagt? Name?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Einer der Matrosen von der 'Alacantara' - Felipe Dabinho... Aber das ist eigentlich gar kein Geheimnis, und Seine Gnaden der Gouverneur selbst hatte befohlen...";
			link.l1 = "Ich verstehe. Das habe ich erwartet. Französische Spione sind in der Stadt, aber diese Idioten plappern wie Handelsmädchen, unglaublich! Jeder Neuankömmling kann herausfinden, was er über die Pläne Seiner Gnaden wissen will. Oh, dieser Felipe Dabinho steckt jetzt in ernsten Schwierigkeiten! Und der Bootsmann der 'Alacantara' auch! Es ist seine Schuld, dass seine Mannschaft nichts über Disziplin weiß!";
			link.l1.go = "trial_10";
			QuestPointerToLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("shore47", "reload", "boat");
		break;
		
		case "trial_10":
			dialog.text = "Oh... Also, du wusstest es von Anfang an? Aber warum... Es ist nicht meine Schuld! Du hast mir gesagt, ich soll das tun!";
			link.l1 = "Es war nicht deine Schuld, du solltest dir keine Sorgen machen, niemand wird dich bestrafen. Jetzt wissen wir, dass die Mannschaft der 'Alacantara' jede Information an einen Feind ausplaudern kann - sogar das, was geheim gehalten werden soll. Gut, du kannst jetzt gehen. Danke für deine Hilfe. Geh und gib dein Geld aus.";
			link.l1.go = "trial_11";
			// belamour legendary edition -->
			link.l2 = "Auf Wiedersehen. (Töte ihn)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddMoneyToCharacter(npchar, 5000);
			npchar.SaveItemsForDead  = true; 
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой 
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Bomzh", 1.0); 
		break;
		
		case "trial_11":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			// <-- legendary edition
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Entschuldige mich, guter Herr... Ich habe es in einem Würfelspiel gegen einen Fremden gewonnen, ich dachte, es wäre ein verzauberter Heilamulett, aber ich lag falsch... Es heilt keine Krankheiten, und die Markthändler sind nicht daran interessiert. Und hier bist du - ein Seemann, Kapitän, ein gelehrter Mann. Schau es dir an, und du könntest es nützlich finden.\nFür dich ist dieses Paar Tausend ein kleiner Betrag, aber für mich ist es ein Stück Brot und ein Schluck Rum für einen Monat. Schau, Herr...";
			link.l1 = "Gut, zeige...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Hier...";
			link.l1 = "So lala... Interessante Sache, das stimme ich zu. Ich bin sicher, es wurde aus den indischen Siedlungen gestohlen. Gut, ich nehme es. Hier ist dein Geld.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Danke, Herr! Ich hoffe, dieses Ding bringt Ihnen Glück! Möge der Herr Sie schützen!";
			link.l1 = "Viel Glück, Kumpel. Gib nicht all das Geld auf einmal in der Taverne aus.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		/// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Ach, "+GetAddress_Form(NPChar)+", was geht Euch ein altes Schmuckstück an?";
			link.l1 = "Wenn ich dir gleich mit meinem Stiefel eine verpasse, wirst du sofort verstehen, warum mich das interessiert.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Dieser Anhänger gehörte Betsy Price. Also, wo hast du ihn gefunden?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "Er lag im Blumenbeet beim Haus mit der Laterne, "+GetAddress_Form(NPChar)+". In den Schlamm getreten von einem groben Männerstiefel. Aber in diesem Haus wohnt schon lange niemand mehr, also dachte ich, er sei herrenlos...";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "Er lag im Blumenbeet beim Haus mit der Laterne, "+GetAddress_Form(NPChar)+". In den Schlamm getreten von einem groben Männerstiefel. Aber in diesem Haus wohnt schon lange niemand mehr, also dachte ich, er sei herrenlos...";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
