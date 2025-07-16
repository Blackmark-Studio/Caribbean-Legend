// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"...","Das ist jetzt das dritte Mal, dass du mich belästigst...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Hmpf, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ich möchte etwas trinken. Schenken Sie mir den besten Rum ein, den Sie haben.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Hör zu, wo ist Callow Gaston?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Haben Sie zufällig irgendeine Art von Arbeit? Oder könnten Sie vielleicht etwas vorschlagen?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "Ich habe die Arbeit erledigt. Fernando Rodriguez ist tot.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Hör zu, war hier ein Alchemist in dieser Stadt angekommen, ein Arzt? Er ist Italiener, etwa dreißig Jahre alt, sein Name ist Gino Gvineili. Haben Sie davon gehört?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Hier ist dein Getränk. Der beste Rum für unseren neuen Gast! Ist dies ein besonderer Anlass oder bist du einfach vorbeigekommen, um deinen Schnabel zu benetzen";
			link.l1 = "Ja, man kann sagen, es ist ein besonderer Anlass. Ich bringe einige Schwarze nach Blueweld. Ich habe kürzlich den Laderaum meiner neuen Brigantine speziell für diesen Zweck modifiziert. Ich habe gerade eine Plantage besucht und mit dem Aufseher gesprochen, er hat eine schöne Ladung 'schwarzes Elfenbein' bei mir bestellt. Also wartet bald wieder in eurer Taverne auf mich. Ich liefere die Ware nach Blueweld und dann mache ich hier auf Barbados noch ein paar Geschäfte, yo ho!";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Wirklich? Nun, es gibt keine Schande darin, für ein gutes Geschäft zu trinken! Also, Sie sagen, Sie werden auf Barbados Geschäfte machen? Das ist großartig! Prost auf Sie, Kapitän!";
			link.l1 = "Vielen Dank Kumpel. Gut... Ich werde einen Platz suchen, wo ich mich hinsetzen kann.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston hat die Stadt zwei Tage nach deiner 'Händler'-Aktion verlassen. Du hast hier eine Show abgezogen, ha! Dein Betrug wurde schnell aufgedeckt, diese Stadt ist klein und Gerüchte verbreiten sich schnell. Das hat Gaston veranlasst, seine Sachen zu packen. Seitdem hat ihn hier niemand mehr gesehen. Er hat allerdings einen Brief für dich hinterlassen\nEr bat darum, ihn dir persönlich zu übergeben, falls du hier auftauchst, bevor er es tut. Tatsächlich bist du nicht der erste Mann, der nach Gaston sucht. Es gab da einen schmaläugigen großen Mann und einen alten, sah Spanisch oder Portugiesisch aus, ich kann es nicht genau sagen. Aber ich kann sein Gesicht nicht vergessen, etwas an ihm war sehr falsch...";
			link.l1 = "Gib mir diesen Brief... Danke!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Rogue)", "None");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Ich brauche die Dienste eines Schurken nicht. Ich habe keine Aufgabe, die ich Ihnen anbieten könnte.";
				link.l1 = "He, he. Ruhig mit der Sprache, Kumpel!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				notification("Skill Check Failed (35)", SKILL_F_LIGHT);
				notification("Skill Check Failed (35)", SKILL_FENCING);
				notification("Skill Check Failed (35)", SKILL_F_HEAVY);
				notification("Skill Check Failed (35)", SKILL_PISTOL);
				// <--
				dialog.text = "Kapitän, Sie sind zu weich. Ich brauche einen Kämpfer, der ein bisschen angesehener ist als Sie. Kommen Sie zurück, wenn Sie gelernt haben, mit dem Stahl umzugehen, der an Ihrem Gürtel baumelt. Und ein bisschen Treffsicherheit beim Schießen würde auch nicht schaden.";
				link.l1 = "Ich verstehe. Dann werde ich Sie später besuchen.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... Du bist tatsächlich pünktlich. Ich habe eine Aufgabe, die sofort erledigt werden muss. Wenn du dich gut zeigst, stelle ich dich einigen einflussreichen Leuten vor. Jetzt höre zu, das musst du tun.";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Ein Hidalgo ist kürzlich aus Sevilla gekommen, um einige unerwünschte Folgen eines Duells in Europa zu vermeiden. Aber Rache kennt keine Grenzen und eine spanische Adelsfamilie wünscht sich diesen Hidalgo tot. Erfülle ihren Wunsch mit allen notwendigen Mitteln\nBringe den Finger des Mannes mit seinem Ring darauf als Beweis. Außerdem, bringe alle anderen Gegenstände, die du auf seiner Leiche findest. Bist du bereit, den Auftrag anzunehmen?";
			link.l1 = "Wenn die Bezahlung gut ist, bin ich dabei.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Als Auftragsmörder arbeiten? Auf keinen Fall!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "Dann verpiss dich und vergiss, worüber wir gesprochen haben.";
			link.l1 = "Ich gehe.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Ihre Belohnung wird 30.000 Stücke von acht sein, gutes Geld. Dazu können Sie jede Münze nehmen, die Sie auf seinem Körper finden werden. Jetzt besprechen wir die Details. Der Name ist Don Fernando Rodriguez, 35 Jahre alt, groß, dunkelhäutig, gekleidet wie ein Militäroffizier. Er ist ein guter Seemann und erfahrener Fechter\nIch kann Ihnen nicht sagen, wo Sie ihn finden, alles was ich weiß ist, dass er irgendwo in der Karibik ist\nSuchen Sie jede spanische Stadt ab, bis Sie ihn haben. Sie haben zwei Monate Zeit. Noch eines: Mir ist bewusst, was er bei sich trägt, also denken Sie nicht einmal daran, Gegenstände vor mir zu verstecken. Fragen?";
			link.l1 = "Ich habe keine Fragen. Ich bin auf meinem Weg!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Haben Sie einen Finger mit dem Ring dabei? Lassen Sie mich ihn sehen.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Ja, natürlich. Hier ist es.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Nein. Fernando sank zusammen mit seinem Schiff ins Wasser und der Finger sank mit Fernando.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "Der Finger mit dem Ring war eine obligatorische Bedingung im Vertrag. Er sollte als Bestätigung des Todes des Kunden dienen. Wer weiß, ob Rodriquez von dem gesunkenen Schiff an Land geschwommen ist? Haben Sie überprüft? Nein. Sie haben im Grunde die Aufgabe nicht erfüllt, also ist unsere Vereinbarung vorbei. Alles Gute.";
			link.l1 = "Aber ich habe ihn aus dem Weg geräumt. Er ist weg! Oh, fick dich... Es gibt noch genug andere Dinge zu tun in der Karibik. Tschüss.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Wunderbar! Den Finger behalte ich selbst. Jetzt zu dem Inhalt seiner Taschen. Lass uns mal sehen, was du mitgebracht hast.";
			link.l1 = "Mach weiter, schau mal...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, das ist alles, was ich brauche. Gut gemacht! Du hast gute Arbeit geleistet. Ich bin sehr zufrieden mit dir.";
				link.l1 = "Danke! Es ist immer schön, für eine gut gemachte Arbeit gelobt zu werden.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... Ich habe dich gewarnt, ich weiß, auf was Rodriguez niemals verzichten würde. Und ich sehe nicht, was ich hier brauche. Hast du diese Dinge eingesteckt? Hast du sie verloren? Es spielt sowieso keine Rolle. Ich habe keine Lust mehr, mich mit dir zu beschäftigen. Verlass diesen Ort.";
				link.l1 = "Oh, fick dich...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Hier ist Ihre versprochene Belohnung, dreißigtausend. Und ich habe auch eine zusätzliche, hochverantwortliche, hochriskante Aufgabe, aber die Bezahlung wird entsprechend steigen, 40.000 Pesos.";
			link.l1 = "Ich bin ganz Ohr. Wer ist der nächste Kunde?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Diesmal gehst du nicht auf Menschenjagd, sondern auf Gegenstandsjagd. Du musst dich in Richard Fleetwoods Haus auf Antigua einschleichen und sein Logbuch stehlen. Er ist ein englischer Kapitän. Der Ort ist streng bewacht und Richard selbst besucht sein Haus selten\nDer Plan ist einfach. Der Gouverneur von St. Jones organisiert in zehn Tagen eine private Party, an der Fleetwood teilnehmen wird. Du musst nachts zwischen ein und drei Uhr in sein Haus gelangen. Drinnen wird nur ein Soldat sein\nSchalte ihn aus. Suche in Richards Wohnung nach einem Journal. Nimm diesen Schlüssel.";
			link.l1 = "Hm... Interessant. Ich habe verstanden, was ich tun muss. Ich bin bereit loszulegen!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Sei vorsichtig. Schleiche dich nicht vor dem von mir angegebenen Datum ins Haus. Im besten Fall werfen sie dich einfach raus oder im schlimmsten Fall landest du hinter Gittern. Wiederhole mir das Datum und die Uhrzeit.";
			link.l1 = "In genau zehn Tagen, zwischen ein und drei Uhr morgens.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Gut. Du kannst gehen. Viel Glück!";
			link.l1 = "Danke dir, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nein, haben wir nicht. Wir haben Kräuterkenner und Ärzte, aber keinen mit einem solchen Namen.","Das ist das erste Mal, dass ich so einen seltsamen Namen höre. Nein, der Mann, von dem du sprichst, hat uns nie besucht.","Wir haben überhaupt keine Alchemisten. Wir haben Ärzte, aber keinen mit so einem seltsamen Namen.");
			link.l1 = "Ich verstehe. Das ist zu schade. Ich werde weiter suchen!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
