// Соломон Шнеур - старый еврей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "Was willst du von diesem alten Juden, junger Mann?";
					link.l1 = "Solomon, ich brauche, dass du hart nachdenkst und dich an die verlorene Insel erinnerst, auf der du Schiffbruch erlitten hast. Du hast dort einen Vorrat versteckt. Ich habe mit deiner Tochter gesprochen. Mein Chef Lucas Rodenburg hat mir Carte Blanche gegeben, um zum Wohl deiner Familie zu handeln. So wie ich das sehe, ist es für dich in diesem Moment das Wichtigste, das Kapital deiner Familie zurückzuholen, und ohne meine Hilfe bekommst du keinen Hauch von diesem Gold.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && int(Pchar.money) >= 200000)
				{
					dialog.text = "Oh, mein junger Mann, bist du es? Kannst du mir nichts Gutes erzählen? Seid ihr Christen hier, um diesen armen alten Juden wieder mit Fragen zu quälen?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "Ich habe die Insel gefunden, obwohl es ziemlich schwierig war. Ich habe auch deine Kiste mit dem Geld und diesen Schädel gefunden. Ich nehme an, das ist der Schädel deines Großvater-Patriarchen, von dem du gesprochen hast.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "Ich habe die Insel gefunden, obwohl es keine leichte Angelegenheit war. Ich habe auch deine Kiste mit dem Geld gefunden. Aber in dieser Kiste waren keine Schädel.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "Nein, ich habe momentan keine Fragen.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Oh, mein junger Mann, bist du das? Kannst du mir etwas Gutes erzählen? Oder wirst du diesen armen alten Juden wieder mit Fragen quälen?";
					link.l1 = "Ich habe die Insel gefunden, obwohl es ziemlich schwierig war. Ich habe auch deine Kiste mit dem Geld gefunden. Hier bist du.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Hallo, junger Mann. Was willst du von diesem armen alten Juden?";
				link.l1 = "Guten Nachmittag. Nein, nichts, ich bin nur gekommen, um Hallo zu sagen.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Guten Tag, junger Mann. Ich sehe, du bist mit einem Zweck gekommen... Was willst du? Bekomme ich etwas davon oder habe ich etwas übersehen?";
					link.l1 = "Guten Nachmittag, Solomon. Ich möchte mit Abigail sprechen.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Hallo, junger Mann. Was willst du von diesem armen alten Juden?";
				link.l1 = "Guten Nachmittag, Solomon. Nichts, ich bin nur gekommen, um Hallo zu sagen.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Guten Tag, junger Mann. Ich sehe, Sie sind mit einem Ziel hier... Was wollen Sie? Bekomme ich etwas davon oder habe ich etwas verpasst?";
					link.l1 = "Ich muss mit Abigail sprechen. Ich habe einen Brief für sie.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Hallo junger Mann. Was wollen Sie? Noch einen Brief für meine Tochter?";
					link.l1 = "Nein. Wo ist Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "He, ... Sprichst du über mein Geld, junger Mann?";
					link.l1 = "Ja, Mynheer. Über das Geld, das Sie auf einer Insel versteckt haben. Ist es wahr, dass Sie und Abigail sich nicht an den Ort erinnern können?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "In Ordnung. Ich erinnere mich an die Fluyt und ihren Kapitän. Ich habe ihn sogar einmal in Amsterdam gesehen. Der Name der Fluyt war 'Leiden' und der Name des Kapitäns war Toff Keller.";
					link.l1 = "Das ist ein Anfang! Ich habe jetzt eine Spur.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Ach du lieber Himmel, was willst du dieses Mal von diesem armen alten Juden?";
				link.l1 = "Guten Nachmittag. Nein, nichts, ich bin nur gekommen, um Hallo zu sagen.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ach du meine Güte, was willst du diesmal von diesem armen alten Juden?";
			link.l1 = "Guten Nachmittag. Nein, nichts, ich bin nur gekommen, um Hallo zu sagen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Und was willst du von mir? Sieh ich aus wie ein Mann, der etwas weiß? Wie könnte ich wissen, dass an solch einem gottverlassenen Tag genau dort ein Stück Land mit Waren und Gold zum Mitnehmen war? Stell dir vor, wie jeder der Heiden da draußen auf den Straßen versucht, einen Juden wie mich zu übertölpeln und mein Geld zu nehmen!\nEs gibt eine Insel. Kein einziger Mann dort, außer Abi und mir. Kein einziger. Niemanden. Dort war eine Grotte in der Mitte. Ich habe meine Truhe dort hingestellt, um sie vor diesem Piraten-Goy Amalek zu retten! Eine Truhe voller Gold, kein Tand darunter. Ich habe es den ganzen Weg aus der alten Heimat geschleppt! Alles, was ich durch den Schweiß meiner Stirn verdient habe, ist dort. Plus, der Schädel meines Großvaters... Vertrau mir, das Ding hat uns gerettet, ja-ja\nOh-ho-ho, es ist ein alter Talisman voller talmudischer Magie! Gott bewahre uns vor Amalek! Oy vey, es ist schwierig, in diesem Zeitalter der Heiden neu anzufangen! Ich wünschte, du wüsstest es, junger Mann! Oh, ich wünschte, du wüsstest es!";
			link.l1 = "Was um Himmels willen faselst du da, du Wahnsinniger? Wen interessiert's. Ich werde es alleine regeln. Tschüss!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Ach, es gibt einen Gott und du bist ein echter Mensch! Du hast nicht nur mein Gold zurückgebracht, sondern auch den Namen Shneur wiederhergestellt! Was für eine Schande hast du verhindert! Mynheer Rodenburg kann zu Recht stolz darauf sein, dass er Kapitäne wie dich unter seinem Kommando hat. Ich werde den Schädel Mynheer Rodenburg geben, er hat versprochen, eine erhebliche Summe dafür zu zahlen. Ich möchte dir persönlich danken, du bist ein feiner Shabbos-Goy - bitte, nimm diesen Amulett als kleines Dankeschön dieses Juden an.";
			link.l1 = "Äh, danke, denke ich.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Oy, es gibt einen Gott und du bist ein echter Mensch! Du hast nicht nur mein Gold zurückgebracht, sondern auch den Namen Shneur gerettet! Was für eine Schande hast du verhindert! Was den Schädel betrifft - na gut, egal, er war sowieso ein verrückter Trottel! Mynheer Rodenburg kann zu Recht stolz darauf sein, dass er Kapitäne wie dich unter seinem Kommando hat. Ich möchte dir persönlich danken, du bist ein feiner Shabbos Goy - bitte, nimm dieses Amulett als Andenken.";
			link.l1 = "Äh, danke, denke ich.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "Was? Was sagen Sie, junger Mann? Ist das wahr? Lass mich mal sehen... ";
			link.l1 = "Hier ist dein Geld. Es gehört dir und Abigail. Aber leider habe ich den Schädel deines Großvaters nicht gefunden.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Oh Geld, Geld, Geld, wunderbares Geld... Hmm, das sieht nicht aus wie mein Geld... Riecht nicht nach meinem schönen Geld. Aber dann wieder - Geld ist doch alles gleich, junger Mann, nicht wahr? Ich werde nicht darüber klagen. 'Schaue keinem geschenkten Goy ins Maul,' wie wir gerne sagen! Vielen Dank, dass Sie mir meine Ersparnisse zurückgegeben haben. Ich möchte Ihnen auch danken, bitte, nehmen Sie diesen Amulett. Jetzt gehen Sie und erzählen Sie Abi die gute Nachricht. Ich muss das zählen.";
			link.l1 = "Herzlichen Glückwunsch, Solomon.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Ach du meine Güte, pass auf dich auf! Mynheer Rodenburg ist nur einen Schritt davon entfernt, mein goy Schwiegersohn zu sein. Alle Soldaten aus der Garnison werden in einer Sekunde hier sein, sollte ich um Hilfe rufen!";
			link.l1 = "Wer zum Teufel bist du?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Hör mir zu, Kapitän. Ich bin ihr Vater Solomon. Tue das Richtige, bring mir meine verlorenen Münzen und den Jadetotenkopf ihres Urgroßvaters. Dieser alte Jude mag nicht so schlau sein wie du, aber selbst er weiß, dass du etwas von seiner Tochter willst\nVielleicht wurdest du von jemandem geschickt, von irgendeinem Kapitän, der mich kennt, ich werde Abi alles erzählen, mach dir keine Sorgen. Sie ist jetzt nicht zu Hause, sie betet für die Seelen heidnischer Sünder wie du.";
			link.l1 = "Das ergab kaum einen Sinn...Verdammt, du bist wirklich eine harte Nuss. Auf Wiedersehen, du alter Geizhals.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "Einen Brief? Du sagst es! Hör zu Junge, Mynheer Rodenburg ist einen Schritt davon entfernt, mein Schwiegersohn zu werden. Du kannst deinen Hintern hier rausholen, weil ich ihn mag!";
			link.l1 = "Hör zu, es ist mir scheißegal wer dein Schwiegersohn ist. Ich bin verpflichtet, diesen Brief an Abigail zu übergeben. Weißt du, wo ich sie finden kann? Und wer zum Teufel bist du?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Wer bin ich? Ich bin ihr Vater Solomon... Und ich mag dich nicht, Goy.";
			link.l1 = "Ich wäre mehr besorgt, wenn Sie sagten, Sie mögen mich. Werden Sie mich weiterhin bevormunden oder holen Sie Abigail? Ich sage es noch einmal, ich bin ein Bote! Ich habe einen Brief für Ihre Tochter!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Gib mir diesen Brief. Ich werde ihn meiner Tochter übergeben.";
			link.l1 = "Ich werde dir die Locken rasieren und dir die Nase zwicken, bevor ich dir diesen Brief übergebe. Ich habe den Befehl, diese Nachricht persönlich zu übergeben. Mir wurde kein Wort über ihren Vater gesagt und es könnte mir nicht egaler sein. Wo kann ich Abigail finden?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Sobald ich schreie, junger Goy, wird jeder Soldat in der Stadt sofort hier sein. Sei nicht so stur, du kannst sehen, dass ich alle Karten in der Hand halte.";
			link.l1 = "Jesus, Maria und Josef! Wirklich? Und dann was? Erwartest du, dass sie mich für die Zustellung eines Briefes in Ketten legen? Sei nicht lächerlich!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Bist du meshuggeneh? Mit deinem Brief hast du mein armes Mädchen fast zu Tode erschreckt... Sie hat beschlossen, diesem schmucklosen englischen Kapitän nachzujagen! Sie segelte auf dem ersten verfügbaren Schiff davon! Oy veyy, meine arme Tochter! Was soll dieser alte Jude jetzt tun? Mein Leben ist ruiniert! Es ist eine Schande! Lass mich in meinem Elend, oder bleib und freu dich, es ist mir egal! Ohhh meine arme Abigail! Du hast den grauen Kopf deines Vaters in Verzweiflung nach Sheol gebracht!";
			link.l1 = "Nun, wie wäre es damit! Scheint, sie konnte keinen Moment länger warten. Tschüss Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Wie sieht es aus? Es ist nur eine Insel mit niemandem außer mir und Abigail. Dort habe ich meine Truhe versteckt, um zu verhindern, dass dieser Piratengoy Amalek sie nimmt. Alles, was ich ehrlich durch den Schweiß meiner Stirn verdient habe, ist in dieser Truhe...";
			link.l1 = "Sag mir, Solomon, vielleicht könntest du dich an den Namen der Fluyt erinnern, von dem deine Tochter gesprochen hat? Und wie hieß ihr Kapitän?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Nun, ich weiß es nicht. Der Kopf dieses armen alten Juden ist durcheinander wie ein Topf voller Gefilte Fisch! Und warum fragen Sie, junger Mann?";
			link.l1 = "Ich möchte einfach nur Ihrer Tochter helfen, Solomon. Ich kann nichts versprechen, aber ich möchte es versuchen. Mein ehemaliger Chef hat sie schlecht behandelt und danach denke ich, bin ich verpflichtet, ihr irgendwie beim Einleben zu helfen.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Ach du lieber Himmel, wenn das der Fall ist...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Junger Mann! Warte!";
			link.l1 = "Ja?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Junger Mensch! Ich möchte dir danken für alles, was du für mich und meine Tochter getan hast. Du hast uns gerettet. Es tut mir leid, dass ich dir beim ersten Treffen einen harten Empfang bereitet habe und an deinem aufrichtigen Wunsch zu helfen gezweifelt habe. Bitte, vergib diesem alten Juden. Du bist wahrlich ein gesegneter Mann unter den Heiden. Nun sag mir, hast du in der Grotte etwas anderes gefunden als mein Geld?";
			link.l1 = "Nein, Solomon. Es gab nichts als Geld. Ich musste gegen van Bergs Schläger kämpfen - er war es, der vor Monaten dein Schiff versenkt hat. Es könnte sein, dass sie schon etwas gestohlen hatten... Was sollte sonst noch da sein?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Ach nichts Wichtiges... Ein alter Familienrelikt... Nun, egal! Vergiss es, er war sowieso ein Trottel! Und... Nur noch eine Sache, junger Mann... ";
			link.l1 = "Mach weiter.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Sie... nun, ich habe etwas über Sie herausgefunden. Unser Gouverneur hält sehr viel von Ihnen, und Sie sind ein bemerkenswerter Kapitän. Ich werde Ihnen ein Geheimnis verraten... meine Tochter mag Sie sehr. Sie hat es mir selbst gesagt. Vielleicht... denken Sie darüber nach? Abigail ist ein sehr gutes Mädchen, das versichere ich Ihnen, besser als alle Shiksa Dirnen, die Sie auf Ihren Reisen getroffen haben könnten.";
			link.l1 = "Ach du meine Güte... Es ist nicht so einfach, Solomon. Deine Tochter ist wirklich eine seltene Perle. Du passt gut auf sie auf.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Überlegen Sie es sich, junger Mann. Denken Sie noch einmal nach und kommen Sie zurück! Wir würden Sie gerne wiedersehen!";
			link.l1 = "Sicher...Tschüss, Solomon.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Manchmal ist es unmöglich, ein neues Leben zu beginnen, junger Mann. In Armut zu leben - was kann schlimmer sein für einen alten Tölpel wie mich?";
			link.l1 = "Es tut mir leid, Solomon. Bleib standhaft und suche Christus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist ein "+GetSexPhrase("Dieb, Herr! Wachen, nehmt ihn","Diebin, Mädchen! Wachen, nehmt sie fest")+"!!!","Schau dir das an! Kaum war ich in Gedanken verloren, hast du beschlossen, meine Truhe zu durchsuchen! Fangt den Dieb!!!","Wachen! Raub! Fangt den Dieb!!!");
			link.l1 = "Verdammt!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
