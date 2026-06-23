// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Mach weiter, was willst du?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage sprichst...","Hör zu, das ist ein Laden. Die Leute kaufen hier Sachen. Störe mich nicht!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Richtig, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Hm, ich werde nicht...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Hör zu, ein kleiner Vogel hat mir erzählt, dass die Preise für rotes Holz und Kakao in Belize bald in die Höhe schießen werden. Ich habe kürzlich einen guten Deal gemacht und meine Börse mit Dublonen gefüllt, he-he... Ich würde gerne einige dieser Waren erwerben. Kann ich mit einem Rabatt rechnen?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "Eine Galeone namens 'Admirable' ist kürzlich unter dem Kommando von Kapitän Gaius Marchais in Ihrer Kolonie eingelaufen. Sagen Sie mal, könnte er sich hier mit Munition oder Waren zum Wiederverkauf eingedeckt haben?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Nun, Herr, wenn die Partie wirklich groß ist, dann können wir natürlich einen angemessenen Rabatt besprechen.";
			link.l1 = "Wunderbar! Ich habe gehört, dass jeden Tag eine neue Fluyt im Schiffswerft zum Verkauf stehen sollte. Ich werde warten und dieses Schiff kaufen. Obwohl ich alle Kanonen von meiner Brigg gestrippt habe, gibt es immer noch nicht genug Platz in meinem Laderaum für all diese Waren! Ich komme später vorbei!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (int(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ha! Ich erinnere mich an diesen merkwürdigen Kerl! Er glaubte irgendeinem dummen Gerede, dass Guadeloupe verzweifelt Vanille brauchen würde, weil eine große Karawane europäischer Händler dort Halt machen würde, um so viele Gewürze zu kaufen, wie sie tragen können\nIch höre solchen Unsinn jeden Monat, aber Marchais nahm dies am ernstesten. Er verbrachte eine Woche hier, sagte mir, ich solle genug Vanille sammeln, um seine Frachträume zu füllen\nEs scheint, dass er jeden Groschen dafür ausgegeben hat. Ich fühle mich schlecht für diesen Mann, aber ich kann Männer nicht davon abhalten, verrückt zu werden, wenn sie es wollen.";
			link.l1 = "Also, könnte er jetzt gerade in Guadeloupe sein?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Höchstwahrscheinlich. Denn er wird weiterhin auf seine Fantasie-'Händler' warten bis zur zweiten Ankunft Christi und er wird nur Geld verlieren, wenn er Vanille verkauft. Wenn er klug ist, bleibt er in Basse-Terre, bis die Nachfrage nach Vanille in die Höhe schießt oder bis er sicher einen anderen Ort findet, wo sie mehr benötigt wird.";
			link.l1 = "Aye. Danke, du hast mir sehr geholfen!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
