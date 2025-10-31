// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was willst du? Frag nur.","Ich höre zu, was ist die Frage?"),"Das ist das zweite Mal, dass Sie versuchen zu fragen...","Das ist das dritte Mal, dass Sie versuchen zu fragen...","Wann wird das endlich aufhören?! Ich bin ein beschäftigter Mann, der sich um Kolonieangelegenheiten kümmert und Sie stören mich immer noch!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert, Entschuldigung.","Nicht jetzt. Falscher Ort und Zeit."),"Wahrlich, ich habe jetzt nichts zu sagen, Entschuldigung.","Ich werde später fragen.","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Herr Gouverneur, ich habe schreckliche Neuigkeiten für Sie. Ich werde kurz sein: Ihre Frau will Sie berauben. Sie hat versucht, mich dazu zu überreden, eine Ihrer Schranktruhen aufzubrechen. Ich dachte, Sie sollten das wissen.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Monsieur. Ich bin hier, wie vom Gouverneur-General Chevalier de Poincy befohlen. Meine Aufgabe ist es, einen Baron namens Noel Forget nach Tortuga zu bringen, der aus der Mutterkolonie gekommen ist, um die Kolonien zu inspizieren. Sein Hauptziel ist die Gründung einer Französischen Westindischen Handelsgesellschaft. Darf ich ihn Ihnen vorstellen... Er wird Ihnen alle Einzelheiten selbst erklären.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "Wh-a-at? Wieder? Diese Schlampe! Sie wird es bereuen, oh, ich schwöre es! Kampacho wird sie schreien lassen. Warum bist du noch hier? Verschwinde endlich!";
			link.l1 = "Ich dachte...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Immer das Gleiche! Hier, nimm das! Es ist alles, was ich auf dem Tisch habe! Jetzt geh raus!";
			link.l1 = "Danke, Eure Exzellenz. Ich werde mich selbst hinaus begleiten.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Immer das Gleiche! Hier, nimm das! Es ist alles, was ich auf dem Tisch habe!.. Obwohl, gut, du siehst nicht aus wie der Rest der Idioten und Verlierer, mit denen meine Insel gefüllt ist. Nimm ein bisschen extra... Jetzt raus!";
			link.l1 = "Danke, Eure Exzellenz. Ich werde mich selbst hinaus begleiten.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "Gut, Kapitän Charles de Maure. Der Baron wird entsprechend behandelt und ich werde tun, was ich kann, um ihm bei seiner Aufgabe zu helfen.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
