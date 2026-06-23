// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was willst du?","Was möchten Sie wissen?"),"Was brauchen Sie, "+GetAddress_Form(NPChar)+"?","Das ist das dritte Mal, dass du versuchst, mich zu fragen...","Ich habe genug von dir, verschwinde!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Entschuldigung, ich habe meine Meinung geändert.","Es ist nichts, Entschuldigung."),"Ich habe vergessen, meine Entschuldigung...","Drittes Mal ist Glück, ey? Entschuldigen Sie mich...","Entschuldigung, Entschuldigung! Ich werde dann schon gehen...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Hör zu, eine Fregatte unter dem Kommando von Miguel Dichoso war im April 1654 hier in der Nähe, sie ist dann verschwunden. Können Sie mir mehr über sein Schiff erzählen? Vielleicht haben Sie gesehen, was damit passiert ist oder wohin es gegangen ist? Erinnern Sie sich an irgendetwas?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh-ho... Ja, Senor, das war ein Anblick zum Staunen! Man vergisst Dinge wie diese nicht, ha!";
			link.l1 = "Können Sie mir sagen, was passiert ist?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Das Kriegsschiff des Senior Dichoso hat im Hafen von San Jose vor Anker gelegt. Ich hatte einen guten Ausblick, um alles zu sehen, aye. Ich sage dir, es war ein ausgezeichnetes Kriegsschiff, ein Meisterwerk, ich schwöre auf mein blutendes Herz! Die Besatzung prahlte mit der Geschwindigkeit, es konnte bis zu sechzehn Knoten beschleunigen!\nSie verbrachten einen Tag hier, dann segelten sie direkt zur Insel Tobago. Dann, du würdest es nicht glauben, begannen merkwürdige Dinge mit dem Wetter zu passieren, sobald sie hinter dem Horizont verschwunden waren. Das Wetter war tagelang schön gewesen, keine einzige Wolke!\nUnd doch kam dieses schreckliche Unwetter aus dem Nichts. Es sah so aus, als hätte uns Neptun selbst einen Besuch abgestattet! Ich ging hinauf auf meinen Leuchtturm, um ihn anzuzünden, aber dann sah ich sie... Santa Quiteria! Sie raste auf riesigen Wellen begleitet von einem riesigen Tornado!\nDie Fregatte flog wie ein Funken an meinem Leuchtturm vorbei und wurde dann vom Sturm nach Nordwesten getrieben! Niemand hat seitdem die Santa Quiteria gesehen. Nur eine Stunde später waren der Wind und der Regen und die Wolken verschwunden und die Sonne schien, kein einziges Anzeichen des Sturms! So etwas habe ich noch nie gesehen! Obwohl ich an diesem Tag so viel Bernstein aus meiner Bucht gesammelt habe...";
			link.l1 = "So hat der Sturm die Fregatte zurück in die Karibik getrieben?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Es hat! Weit drüben nach Martinique. Ich bezweifle, dass Dichoso diesen Sturm überlebt hat, er hat jedoch sein Bestes gegeben! Die Fregatte sank nicht, aber Santa Quiteria muss jetzt unter den Korallen auf dem Meeresgrund liegen... Tatsächlich bist du nicht die erste Person, die mich nach Dichoso und seiner Fregatte gefragt hat.";
			link.l1 = "Wirklich? Wer sonst war an Miguel interessiert?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Etwas fabelhafter Kapitän der spanischen Flotte, nicht weniger! Er hat sich vorgestellt als...oh... Ich habe es vergessen... Ah! Senor Diego. Sein Name war Diego, aber sein Nachname... de Montagna oder de Montoya. So etwas. Er hörte mir zu, genau wie du, bedankte sich und ging weg. Seitdem habe ich ihn nicht mehr gesehen.";
			if (int(Pchar.money) >= 5000)
			{
				link.l1 = "Ich verstehe. Vielen Dank für Ihre Geschichte, Sie haben mir sehr geholfen. Nehmen Sie meine Dankbarkeit in Münzen. Auf Wiedersehen.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "Ich verstehe. Vielen Dank für Ihre Geschichte, Sie haben mir sehr geholfen. Lebewohl.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
