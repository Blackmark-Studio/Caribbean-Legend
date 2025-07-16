// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"...","Über den ganzen Tag hinweg ist das das dritte Mal, dass du über irgendeine Frage sprichst...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Hmpf, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Man sagt, jemand hat Euch Euren kostbaren Gin gestohlen. Oder sind das nur Gerüchte?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Gute Nachrichten, "+npchar.name+"! Ich habe Euer Fass wiedergefunden"+GetSexPhrase("","e")+"!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Leider ist es wahr. Was habt Ihr sonst noch gehört? Wisst Ihr etwas? Ich flehe Euch an – sagt mir, dass Ihr wisst, wo es ist. Wenn ich es nicht finde... muss ich die Stadt verlassen. Entweder aus freien Stücken oder in einem Sarg.";
			link.l1 = "Hm... Sieht ganz so aus, als stünden die Dinge bei Euch schlecht, Freund. Nein, ich habe nur flüchtig von Eurem Unglück gehört"+GetSexPhrase("","e")+". Wie konntet Ihr etwas so Wertvolles aus den Augen verlieren?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "Ach... Was soll ich sagen... Es wurde mir direkt unter der Nase gestohlen! Am Morgen war das Fass definitiv noch da. Es kam vorgestern an, und ich nahm es über Nacht mit nach Hause, um ruhig schlafen zu können. Morgens brachte ich es zurück, stellte es unter den Tresen – und am Abend war es einfach verschwunden! Niemand hat etwas gesehen oder gehört.";
			link.l1 = "Das ist ja unglaublich...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "Hätte ich nur irgendeine Spur, ich wäre schon längst auf der Suche. Aber leider – nichts. Es ist, als ob das Fass zu gut für diese Welt war und die Götter es geholt hätten. Ich zahle hundertfünfzig Dublonen jedem, der es mir zurückbringt. Nein, ich werde sogar eine Plakette mit seinem Namen in der Taverne anbringen, damit jeder von seiner Heldentat erfährt!";
			link.l1 = "Ich werde sehen, was ich tun kann. Und über die Plakette reden wir später. Sagt mir lieber: Wer wusste von dem Fass? Und wer, außer Euch, hätte hinter dem Tresen stehen können?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Hundertfünfzig Dublonen für ein Fass? Interessant. Aber das ist nicht mein Problem. Kümmert Euch selbst darum.";
			link.l2.go = "OS_Tavern1_end";
		break;
		
		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;
		
		case "OS_Tavern1_4":
			dialog.text = "Eigentlich niemand! Außer vielleicht meiner Kellnerin, aber das kann ich ausschließen. An dem Tag war in der Taverne ein riesiger Rummel – die Crew vom 'Sea Beast' war von der Jagd zurück und hatte ordentlich Beute gemacht. Sie hatte keine Minute zum Verschnaufen, geschweige denn Zeit, sich hinter den Tresen zu schleichen.";
			link.l1 = "Seid Ihr Euch da sicher?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Ganz sicher! Der Dauerstress hat ihr gar nicht gefallen und gegen Abend war sie ziemlich gereizt. Einer der Matrosen fing an, sie anzumachen, und sie schrie so laut, dass es allen die Ohren klingelte. Ich musste sogar selbst hinter dem Tresen hervorkommen, um die Leute zu beruhigen. Normalerweise reagiert sie auf sowas viel gelassener.";
			link.l1 = "War das alles? Nichts Weiteres Bemerkenswertes an diesem Tag?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "Während ich mich noch mit dem ersten Aufruhr beschäftigte, brach eine Schlägerei aus – zwei Matrosen gerieten im hinteren Eck der Taverne aneinander. Die Prügelei dauerte aber nicht lange: sie schienen aus derselben Crew zu sein und wurden schnell auseinandergezogen. Danach war tatsächlich Ruhe, nichts weiter erwähnenswertes geschah.";
			link.l1 = "Na gut, ich bin bereit, mit der Suche zu beginnen. Wartet ab. Ich denke, das Fass wird bald wieder unter Eurer, äh... aufmerksamen Beobachtung stehen.";
			link.l1.go = "OS_Tavern1_7";
		break;
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Ihr habt es gefunden?! Ist das wahr? Kapitän, Ihr habt mir das Leben gerettet! Wer steckt dahinter? Ich muss den Namen dieses Halunken wissen!";
			link.l1 = "Es war ein sorgfältig geplanter Trick von einem gewissen Jack Veils, zusammen mit dem Kapitän des 'Sea Beast'. Sie haben ihre Matrosen mit ins Spiel gebracht und ein richtiges Schauspiel aufgeführt, um Euch abzulenken. Als Ihr den Tresen verlasst, blieb das Fass unbeaufsichtigt – und sie konnten es problemlos stehlen.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Unglaublich! Jack Veils! Also ist er wieder hier... Und offenbar hat er versucht, sich so die Taverne zurückzuholen. Dieser Fuchs gibt nie auf!";
			link.l1 = "Er war also früher einmal der Besitzer dieser Taverne? Ich kann Euch versichern – ein weiterer Trick wird ihm nicht gelingen. Ich habe ihn zu seinen Ahnen geschickt"+GetSexPhrase("","e")+".";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Kapitän! Das ist erstaunlich! Ihr... Ihr habt mich von der ständigen Angst um meine Zukunft befreit! Ich wusste immer, dass er eines Tages zurückkehren würde... Vor ein paar Jahren haben wir um den Besitz dieser Taverne konkurriert, und er hat gewonnen\nAber der Rausch seines Sieges wurde ihm zum Verhängnis – er hat so ausgelassen gefeiert, dass er gar nicht bemerkte, wie er sie mir beim Kartenspiel verlor. Am nächsten Morgen kam er angerannt, flehte mich an, sie zurückzugeben, versprach alles Mögliche\nAber ich bin ja kein kompletter Narr, um auf sowas einzugehen. Dann verschwand er... Ich wusste, er würde das nicht einfach auf sich sitzen lassen. Ich spürte, dass er eines Tages zurückkommt. Und siehe da – dieser Tag ist gekommen.";
			link.l1 = "Man muss es ihm lassen, er hat das wirklich clever eingefädelt.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Wartet mal! Woher wusste er überhaupt von dem Fass? Ich glaube... ich beginne zu verstehen! Die Kellnerin! Deswegen ist sie so plötzlich und ohne ein Wort verschwunden. Sie hat wohl erfahren, dass Ihr Jack beseitigt habt. Jetzt ergibt alles Sinn. Kapitän, ich stehe tief in Eurer Schuld, Ihr...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
