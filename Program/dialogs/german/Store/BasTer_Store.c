// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Mach schon, was willst du?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage redest...","Hör zu, das ist ein Laden. Die Leute kaufen hier Sachen. Stör mich nicht!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Stimmt, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Hm, ich werde nicht...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Danke, Kapitän, dass Sie meinen Wunsch erfüllt haben. Nun, wenn "+pchar.questTemp.Shadowtrader.Guardername+" ist hier, ich kann zumindest ein bisschen entspannter fühlen.";
					link.l1 = "Hmm... Ich möchte nicht aufdringlich erscheinen, aber es scheint mir, dass Sie Probleme haben. Können Sie mir sagen, was los ist - vielleicht könnte ich Ihnen helfen?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Also? Haben Sie meinen Brief übergeben?";
					link.l1 = "Ich habe. Der Kommandant antwortete mündlich, dass die Beweise in Ihrem Brief für die Stadtwache unzureichend sind, um Maßnahmen zu ergreifen."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "Ich habe schon von den Neuigkeiten gehört - heute Nacht haben die Wachen einen illegalen Handelsposten von Schmugglern entdeckt und alle verhaftet. Es stand unter dem Kommando eines seltenen Stückes Abschaum, es ist jetzt in Ordnung, er wird für eine Weile niemandem mehr Schaden zufügen können\nDer Kommandant hat mir von Ihrer Rolle in alldem erzählt, Sie haben meine Dankbarkeit! Sie haben Ihr Wort gehalten! Hier, nehmen Sie das Geld - 15 000 Pesos. Sie haben mich gerettet. Jetzt bedroht nichts mehr mein Geschäft!";
					link.l1 = "Bitte sehr. Es war einfach."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Also, irgendwelche guten Nachrichten, "+pchar.name+"?";
					link.l1 = "Ich habe Ihren Rivalen gefunden. Er wird Ihnen nicht wieder auf den Wecker gehen - ich habe es geschafft, ihn zu überzeugen... diese Insel zu verlassen. Sein 'Geschäft' war in einem Haus nahe dem Stadttor. Es liegt an Ihnen zu entscheiden, was mit der zurückgelassenen Ladung geschehen soll. Sie können sie den Behörden übergeben oder versuchen, sie selbst einzusammeln."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ich habe die Nachricht schon gehört - heute Nacht haben die Wachen einen Schmugglerausgang unter einem der Häuser entdeckt. Zwei Schurken wurden tot gefunden. Gute Arbeit, "+pchar.name+", Ich bewundere Sie! Hier, nehmen Sie die Belohnung - 15 000 Pesos. Sie haben mich gerade gerettet! Jetzt werde ich wirklich handeln!\nBefriedigen Sie meine Neugier - ihr Anführer... auch unter den zwei Toten?";
					link.l1 = "Nein. Aber er wird nie wieder sein Gesicht in deiner Stadt zeigen. Ich glaube, er sollte mehrere Dutzend Meilen von dieser Insel entfernt sein, während wir sprechen."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ich habe die Neuigkeiten bereits gehört - diese Nacht haben die Wachen einen geheimen Schmugglerladen in einem der Häuser lokalisiert. Drei Schurken wurden tot aufgefunden. Hervorragende Arbeit, "+pchar.name+", Ich bewundere dich! Hier, nimm die Belohnung - 15.000 Pesos. Du hast mich gerade gerettet! Jetzt werde ich erst richtig handeln! \nStill meine Neugier - ihr Anführer... auch unter den beiden Toten?";
					link.l1 = "Ja. Sie haben Ihren Rivalen für immer los. Er wird Sie nie wieder belästigen."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(int(npchar.nation), "man");
			dialog.text = "Könnten Sie bitte zur Taverne gehen, einen Mann namens "+pchar.questTemp.Shadowtrader.Guardername+" und sag ihm, er soll so schnell wie möglich hierher kommen? Ich kann den Laden nicht verlassen und dieser Dummkopf sitzt in der Taverne, lädt sich mit Rum voll und wird sicherlich nicht einmal daran denken, hierher zu kommen, obwohl er Dienst hat.";
			link.l1 = "Ich helfe immer gerne, Kumpel - umso mehr, weil ich sowieso die Taverne besuchen wollte.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Verspottest du mich? Sehe ich aus wie dein Laufbursche? Die Taverne ist nur ein paar Schritte von hier entfernt - du kannst selbst dorthin gehen.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Danke! Bitte sagen Sie ihm, er soll sofort hierher kommen. Ach du meine Güte, warum muss er nur solch eine Plage sein...";
			link.l1 = "Mach dir keine Sorgen. Ich werde ihn zu dir schicken.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = int(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, int(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Oh, Kapitän, ich könnte wirklich deine Hilfe gebrauchen. Könntest du bitte diesen Brief so schnell wie möglich zum Kommandanten bringen? Ich würde dir 300 Münzen für diese Kleinigkeit zahlen - wie ich schon sagte, ich kann meinen Laden nicht verlassen.";
			link.l1 = "Kein Problem. Gib mir diesen Brief.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Nein, mein guter Mann, ich habe keine Zeit mehr für diesen Unsinn.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Hier, bitte. Geben Sie es ihm noch heute und bringen Sie mir seine Antwort.";
			link.l1 = "Mach dir keine Sorgen, ich werde es tun.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Nun, anscheinend muss ich jemand anderen fragen. Entschuldigen Sie die Störung, Kapitän.";
			link.l1 = "Kein Problem. Auf Wiedersehen!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Das hat er gesagt? Welche Beweise braucht er von mir, dann?! Meine Leiche? Nun, bald wird es eine geben, wenn es so weitergeht!..";
			link.l1 = "He, he, "+npchar.name+", beruhige dich, sonst bekommst du noch einen Schlaganfall. Hier, trink etwas Wasser... Jetzt erzähl mir, was los ist - vielleicht kann ich dir helfen?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Oh, Kapitän! Bitte nehmen Sie Ihre 300 Pesos - ich hatte fast vergessen... Natürlich werde ich Ihnen erzählen, aber ich bin mir nicht sicher, wie Sie mir helfen könnten. Mein Geschäft ist fast ruiniert - alles wegen dieser verfluchten Schmuggler und diesem unbekannten Bastard, der sie anführt.";
			link.l1 = "Schmuggler?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "Das ist es! Diese Schurken haben offensichtlich beschlossen, mich aus der Stadt zu werfen! Bis dahin war alles wie gewöhnlich - sie verkauften verbotene Artikel weiter, und wenn Patrouillen sie erwischten, versteckten sie sich oder kauften sie aus. Aber neulich haben sie irgendwo in einer Seitenstraße einen Laden eröffnet und begannen, die beliebtesten Waren zu unglaublich niedrigen Preisen zu verkaufen!\nIch kann mir diesen Luxus nicht leisten - schließlich muss ich Steuern zahlen - ich verarmte allmählich und Seeleute wollen meine Waren fast nicht mehr - alle Waren kaufen sie von diesen Schurken.";
			link.l1 = "Aber Sie hätten sich an die Behörden wenden sollen! Schließlich ist es ihre Aufgabe - solche Gesetzlosigkeit zu stoppen.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Sie haben das letzte Berufungsergebnis selbst gesehen. Der Gouverneur ist zu beschäftigt und der Kommandant glaubte nicht, dass Schmuggler Hinterhofläden organisierten, oder tut so, als würde er nicht glauben - und, ich vermute, das ist der Fall\nNatürlich, warum sollten sie das tun? Und ich sage: Ich bin sicher, irgendein Schurke, der mich zerstören und aus der Stadt vertreiben will, hat das alles erfunden, und dann wird er mein Geschäft leise aufräumen, um ihre schmutzigen kleinen Hände zu reinigen.";
			link.l1 = "Hm... deine Meinung ist nicht unbegründet. Es liegt in der Natur der Händler - jemanden zum Katzenpfötchen zu machen... Oh, entschuldigung, ich meinte natürlich nicht dich. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Oh, nichts... Und neulich kam irgendein Taugenichts zu mir und sagte frech, wenn ich weiter Lärm mache, würden sie meinen Laden anzünden\nAlso habe ich einen Leibwächter eingestellt. "+pchar.questTemp.Shadowtrader.Guardername+" kommt nicht billig, aber er ist ein Profi und unter seinem Schutz kann ich mich ein wenig beruhigter fühlen.";
			link.l1 = "Ich sehe... Eine unangenehme Geschichte, in der Tat. Anscheinend hattest du recht - es gibt nichts, was ich für dich tun kann. Aber dennoch bin ich sicher, dass sich die Dinge von selbst regeln werden - solche zwielichtigen Etablissements halten normalerweise nicht lange. Nun, viel Glück!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Ich verstehe. Nun, vielleicht könnte ich Ihnen trotzdem helfen...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Du bietest mir trotzdem deine Hilfe an? Aber was wirst du tun?";
			link.l1 = "Ich werde versuchen, diesen 'Kollegen' von dir zu finden und... ihn zu überreden, dich in Ruhe zu lassen. Du weißt, ich habe gewisse Fähigkeiten, Menschen zu überreden.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Bist du ernst? Möge der Herr deine gerechte Sache segnen! Wenn du mich von diesem Dreck befreist, werde ich dir zu Dank verpflichtet sein.";
			link.l1 = "In Ordnung, betrachten wir es als abgemacht. Ich werde dann suchen.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Ist das wahr? Ich kann jetzt ohne jede Angst Geschäfte machen? Oh, vielen Dank! Hier ist Ihre Belohnung - 15000 Pesos. Was die Waren in ihrem Haus betrifft, denke ich, es ist am besten, sie dem Kommandanten zu übergeben. Nochmals vielen Dank!";
			link.l1 = "Gern geschehen. Es war nicht allzu schwer. Ich habe dir gesagt, dass ich gut im Überreden bin.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Kommen Sie wieder zu Besuch, Kapitän - Ich werde immer froh sein, Sie zu sehen.";
			link.l1 = "Natürlich! Und jetzt erlauben Sie mir, mich zu verabschieden - ich habe Dinge zu erledigen! Auf Wiedersehen und viel Glück in Ihrem Handel, "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
