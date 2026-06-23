// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was willst du?","Was möchten Sie wissen?"),"Was brauchen Sie, "+GetAddress_Form(NPChar)+"?","Das ist das dritte Mal, dass du versuchst, mich zu fragen...","Ich habe genug von dir, verschwinde!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Entschuldigung, ich habe meine Meinung geändert.","Es ist nichts, Entschuldigungen."),"Ich habe vergessen, meine Entschuldigung...","Drittes Mal ist Glück, ey? Entschuldigen Sie mich...","Entschuldigung, Entschuldigung! Ich werde dann gehen...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Grüße. Der Inquisitor von Santiago, Dadre Vincento, hat Sie in seinem Brief erwähnt. Er sagte, Sie könnten mir vielleicht helfen.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Gibt es Neuigkeiten von Padre Vincento, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Ich muss Padre Vincento sehen. Ich habe die Gegenstände gefunden, an denen er interessiert ist.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Also, "+npchar.name+", was hat Padre Vincento dir erzählt?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Sicher, Senor. Sie müssen ein Mann von hohem Ansehen sein, wenn Padre Vincento selbst Geschäfte mit Ihnen macht.";
			link.l1 = "Hervorragend. Sie sind also unser Läufer. Jetzt hören Sie zu, dieser Mann ist von großem Interesse für Padre Vincento. Er liegt nun in Ihrer Verantwortung, Sie müssen ihn nach Santiago überführen oder jemanden finden, der das tut.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "Sie sind im Namen des Inquisitors für den Gefangenen verantwortlich. Ich würde Ihnen nicht raten, seine Fesseln zu entfernen, Gaius Marchais ist ein starker Mann. Geben Sie diesen Brief an Padre Vincento und sagen Sie ihm, dass ich in zwei Tagen eine Antwort von ihm erwarte. Das sollte hoffentlich ausreichen.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Verstanden, Senor. Ich werde mein Bestes geben. Es ist nicht das erste Mal, dass ich dem heiligen Vater helfe.";
			link.l1 = "Das ist nicht alles. Der Kapitän der Carraca, San Gregorio, Carlos Guevarra muss hier gewesen sein. Er hat Vanille für mich mitgebracht. Hat er dir meinen Brief gegeben?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ja, Ihre Ladung ist in Ordnung und wartet auf Sie, Senor.";
			link.l1 = "Gut, ich werde es dann auf mein Schiff schleppen. Ich werde hier zwei Tage auf Padre Vincentos Antwort warten. Das ist vorerst kein Abschied, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + int(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Ja, Senor. Hier ist ein Brief von Padre Vincento. Er ist sehr zufrieden mit Ihnen, den Rest erfahren Sie aus dem Brief.";
			link.l1 = "Prächtig. Bis dahin, "+npchar.name+". Und für jetzt - Lebewohl.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Sehr gut. Gib sie mir und ich werde sie dem heiligen Vater bringen.";
			link.l1 = "Keine Chance, Kumpel! Es war nicht einfach, die zu bekommen und ich werde sie nicht einfach so übergeben. Ich werde sie nur persönlich an Padre Vincento geben.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Aber Senor! Wie kann ich wissen, dass Sie mich nicht betrügen?";
			link.l1 = "Nehmen Sie einen Blick: das Räuchergefäß, der Kelch und das Kreuz mit dem Lapislazuli... "+npchar.name+", wen hältst du mich? Denkst du wirklich, ich bin dumm genug, ohne sie zur Inquisition zu gehen?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Verzeihen Sie mir, senor... Kommen Sie morgen und ich werde Padre Vincento von Ihrer Ankunft berichten.";
			link.l1 = "Gut. Bis morgen.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Seine Gnaden wird Sie empfangen, Senor. Zögern Sie nicht mit Ihrem Besuch. Hier ist das Dokument, zeigen Sie es den Wachen und sie werden Sie hereinlassen. Aber hissen Sie zuerst eine spanische Flagge, sonst werden die Soldaten Sie wahrscheinlich verhaften.";
			link.l1 = "Hab's verstanden. Dann also Spanisch. Danke, Kumpel! Ich bin auf dem Weg!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
