// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Ich möchte nicht mit dir reden. Du greifst friedliche Zivilisten ohne Grund an und provozierst sie zum Kampf. Verzieh dich!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Kumpel, du kommst gerade rechtzeitig... Ich möchte mit dir reden... über ein Geschäft. Ein wichtiges.";
				link.l1 = "Wirklich? Es sieht so aus, als wärst du nicht betrunken. Ist etwas passiert? Es ist ungewöhnlich, dich nüchtern zu sehen.";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Hallo, Kumpel...";
				link.l1 = TimeGreeting()+". Sieht so aus, als hättest du schon genug gehabt, Kumpel.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! Hic! Was willst du?";
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Ist auf der Insel etwas Neues passiert?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Wollte nur wissen, wie es dir geht. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ja! Genug? N-ein! Ich bin ein verrückter Betrunkener, hi-hicks! Ja, Leonard Musket ist betrunken und das ist richtig so!";
			link.l1 = "Liebst du Getränke, huh? Ja, mein Name ist "+GetFullName(pchar)+". Schön, dich zu treffen.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Wenn du meinst. Wir alle hier... hic, treffen uns.";
			link.l1 = "Gut, es sieht so aus, als wärst du nicht in Stimmung zum Reden. Auf Wiedersehen!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Ich möchte Ihnen ein paar Fragen über die Insel stellen.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "Ja, Kumpel, ich bin fast nüchtern. Und das liegt daran, dass ich ein Geschäft für dich habe, ein wichtiges. Und es scheint, dass du das erledigen kannst...";
			link.l1 = "Was? Was hast du im Kopf? Sprich und verschwende meine Zeit nicht umsonst!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Kumpel, willst du etwas Geld verdienen? Silberpesos, goldene Dublonen? Ich werde dir sagen wie. Aber du wirst mit mir teilen müssen - wir werden zusammenarbeiten.";
			link.l1 = "Ich möchte immer. Aber alles hängt von deinem Vorschlag ab: Ich mache keine Arbeit, auch wenn sie sehr lukrativ ist.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "Das Geschäft ist nicht wirklich legal, sicher, aber es ist profitabel... und wir werden in der Lage sein, einen Mann zu bestrafen, der zu wählerisch geworden ist. Er wird nicht arm werden, er hat zu viel Geld. Jeder teilt mit ihm, also ist es jetzt an der Zeit, dass er dasselbe tut. Sag mal, kannst du mit Rum umgehen? Wie viel kannst du trinken, bevor du unter den Tisch gehst?";
			link.l1 = "Es kommt darauf an. Ich bin mir nicht sicher, ob ich eine Vorliebe für verrücktes Trinken habe... Wirst du mir endlich Details erzählen?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Ich komme schon zur Sache, du siehst es nur noch nicht. Gut. Ich werde spezifisch. Auf der Insel gibt es einen fetten hässlichen Bastard - Giuseppe Fazio. Ein seltener Abschaum. Er häutet lebendige Narwale, Rivados und die Einheimischen. Ich habe ihn eine Weile beobachtet und endlich habe ich etwas\nEs gibt zwei Truhen in seiner Kabine in Carolina: die erste enthält Papiere, die zweite enthält Gold und Silber. Beide sind mit verschiedenen Schlüsseln verschlossen. Der fette Mann hat die Schlüssel immer bei sich.";
			link.l1 = "Nun, es scheint, dass du Fazio ausrauben willst? Da mache ich nicht mit. Und du solltest froh sein, dass ich niemandem davon erzähle. Wenn du die Truhe des dicken Mannes untersuchen willst, dann solltest du dir einen anderen Partner suchen.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha! Interessant! Mach weiter...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Zu schade, wirklich schade... Es gibt viel Gold, genug für uns beide. Gut, wir sehen uns...";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Zwei Türen führen in seine Kabine. Eine von ihnen ist immer verschlossen. Aber der Schlüssel, der die Truhe mit Gold öffnet, öffnet auch die Tür. Ich weiß nicht, was der ganze Sinn dahinter ist, aber es ist eine Tatsache. Sie benötigen nur einen Schlüssel, um die Kabine zu öffnen und das Gold zu bekommen. Eine logische Frage kommt als nächstes - wie bekommt man den Schlüssel? Also, ich habe einen Plan\nEin hervorragender Plan, wenn es richtig geht, wird Fazio nie bemerken, was passiert ist und wer daran schuld ist. Sie werden denken, dass es der geheimnisvolle Dieb war. Das Problem ist, dass ich einen Partner mit einem Kopf aus Eisen brauche, um es zu erledigen. Verstehst du?";
			link.l1 = "Ich höre zu. Mach weiter.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio liebt es, bei Sancho zu sitzen und ein gutes Getränk zu haben, aber sein Körper ist zu schwer für den Rum, um seine Wirkung zu zeigen. Also hat er ein Trinkspiel erfunden - das Spiel, bei dem die Leute versuchen, ihn zu übertrinken. Wenn du ihn aufforderst, dieses Spiel zu spielen, wird er zweifellos zustimmen\nUnd dann kommt der lustige Teil. Du machst eine Wette mit ihm, gehst in die Taverne, nimmst Rum und trinkst, bis einer von euch den Tisch küsst. Wenn du aussteigst, dann ist der ganze Plan gescheitert, ich kann es nicht alleine schaffen\nDeshalb habe ich nach deinem Kopf gefragt. Wenn du Fazio quietschen und grunzen lässt wie ein Schwein, dann betrachte es als erledigt. Ich werde die ganze Zeit in der Nähe sein. Wenn er fertig ist, werde ich seine Schlüssel nehmen\nDann bringen wir den dicken Mann zu einem Bett nach oben und schleichen uns in seine Kabine, während er schläft. Ich werde den Schlüssel direkt nachdem wir seine Truhe geplündert haben, zurückgeben, er wird nicht einmal merken, dass er ausgeraubt wurde\nIch werde den Schlüssel besorgen und zurückgeben, deine Mission ist es, Fazio betrunken zu machen und in sein Eigentum einzudringen. Ich werde Wache halten, falls jemand auftaucht, so dass du genug Zeit hast, durch die Hintertür zu flüchten\nWir werden den Inhalt der Truhe halbieren, das wäre fair. Also, bist du dabei?";
			link.l1 = "Guter Plan! Sicher, lass es uns versuchen!";
			link.l1.go = "facio_6";
			link.l2 = "Nein, Kumpel. Ich passe. Ich fürchte, dass ich nicht so viel trinken kann, um auf den Beinen zu bleiben und Fazio zu übertrinken. Such dir einen anderen Partner, ein bisschen stärker als ich.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Ich bin froh, dass ich recht mit dir hatte. Geh nun zu Fazio und arrangiere ein Treffen in der Taverne am Abend nach neun Uhr. Ich hoffe, dass du dieses Schwein besäufst. Viel Glück und bis zum Abend!";
			link.l1 = "Ich werde es versuchen... Auf Wiedersehen!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Kumpel, ich zähle auf dich. Besäuf dich mit dem fetten Mann...";
			link.l1 = "Sicher...";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "Es ist erledigt, das fette Schwein schläft oben. Ich habe den Schlüssel. Du machst das gut, du scheinst nüchtern genug zu sein!";
			link.l1 = "Ist das so? Es ist eine lange Zeit her, seit ich so betrunken war. Fühle mich ein bisschen schwindlig... Lass uns gehen?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "Es ist erledigt, das fette Schwein schläft oben. Ich habe den Schlüssel. Du machst das gut, du hast es wirklich geschafft, dieses Schweinchen zu übertrinken...";
			link.l1 = "Ich habe, aber es ist eine lange Zeit her, seit ich so betrunken war. Mein Kopf ist in einem Wirbel... Sollen wir dann gehen?";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, Kumpel, du hast es nicht geschafft, den dicken Mann zu übertrinken... Schade. Nun, zumindest haben wir es versucht...";
			link.l1 = "V-verdammt, er ist wie ein... b-bodenloses Fass. Argh, ich muss mich a-ausruhen... Es ist vorbei, v-verschwinde! Hic!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Ja. Los geht's! Folge mir zur 'Carolina'! Und stromere nicht herum, wir haben nicht viel Zeit!";
			link.l1 = "Lass uns gehen!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Hier. Nimm den Schlüssel. Die Kiste, die du brauchst, ist links vom Eingang. Nimm so schnell wie möglich so viel du kannst. Vergiss nicht, sie wieder abzuschließen. Wenn ich etwas sehen werde, klopfe ich dreimal an die Tür. Lauf in diesem Fall durch die hintere Galerie weg.";
			link.l1 = "Gut. Sei auf der Hut!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable loot... And were we risking for it? Eh... Fine, let's share what we have got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there will be much more... Risk wasn't worth it. Eh... Fine, let's share what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought that we will get more. Fine, let's share it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We have done well, partner! This is a whole lot of coins! Let's share!";
						else
						{
							sTotalTemp = "Wow! I haven't ever thought that the fat man's stash is so huge. Well done, partner! Let's share!";
						}
					}
				}
			}
			dialog.text = "Endlich! Was hast du aus der Truhe dieses Schurken geschafft? Zeig mir, ich warte mit Ungeduld!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Es gab überhaupt nichts. Nur ein paar Fetzen, Amulette und solcher Kram.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "Ich habe aus der Truhe genommen "+sPeso+" und "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Unmöglich! Es scheint, dass alles umsonst war... Vielleicht hat dieser Bastard seine Beute in einer anderen Kiste versteckt. Eh! Gut, gib mir den Schlüssel und ich werde ihn seinem Besitzer zurückgeben, bevor er ihn vermisst. Leb wohl, Kumpel...";
			link.l1 = "..., Freund.";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Lass uns teilen...";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Gut, gib mir den Schlüssel und ich werde ihn seinem Besitzer zurückgeben, bis er ihn nicht vermisst. Lebewohl, Kumpel...";
			link.l1 = "Viel Glück, Kumpel...";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone has cleaned out his chest. It seems that the mysterious thief did that.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Have you heard? Fazio was robbed! He was robbed while being drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your own feet! That 's something...", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Wirklich?... Hic! Ich höre zu...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Wie bist du hier gelandet?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Trinkst du immer? Und wo findest du Münzen für Getränke?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Was können Sie mir über die Einheimischen erzählen?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Möchten Sie diesen Ort verlassen und zum Festland gehen?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Keine Fragen. Entschuldigung...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Jawohl! Ich schwöre, ich erinnere mich nicht. Ja, ja, ich tue es nicht! Es war vor langer Zeit. Irgendwie segelte ich irgendwohin und landete schließlich hier. Hicks!";
			link.l1 = "Hm... In Ordnung, in Ordnung.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ja, ich bin ein Säufer... Trinken, verdammt nochmal, weil ich nichts anderes zu tun habe... Siehst du, Kumpel, ich bin erledigt. Die Flasche Rum ist das Einzige, was ich will. Also werde ich weiter trinken. Und Geld... he-he, Rum kostet nicht viel. Wie auch immer, ich muss es nicht einmal kaufen\nEs gibt einen Ort, der voller Rum ist, aber du musst schwimmen, wenn du ihn holen willst, deshalb kaufe ich nur dann Rum, wenn ich zu betrunken zum Schwimmen bin... hicks! Jizjezezejizeze, nein, ich werde dir nicht sagen, wohin du schwimmen musst, he-he, frag nicht einmal...";
			link.l1 = "Wunderbar.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Was kann ich sagen, hic... über sie? Gute Leute zum Reden und zum Trinken. Giuseppe Fazio ist ein so wichtiger Mann, ein örtlicher Großkopf, seine Truhen sind voll mit Gold... und doch respektiert er den alten Leo, kauft ihm Getränke in der Taverne. Obwohl, manchmal verlangt er auch etwas im Gegenzug, aber das ist nichts, hic!\nHeh, weißt du nicht, wie viele Dublonen Fazio besitzt, aha-ha-ha! Genug, um den Rest deines Lebens im besten Haus der gesamten Karibik zu verbringen, nicht arbeitend und den besten Rum der Welt trinkend. Aber er bleibt hier, auf der Insel. Scheint immer noch nicht genug Geld für ihn zu sein...";
			link.l1 = "Habs verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Aufbrechen? Hic! Warum? Nein, ich will weder aufs Festland noch auf die arme Insel. Gibt es kostenlosen Rum? Nein! Es gibt keinen kostenlosen Rum, hic! Und das bedeutet, dass es dort nichts für mich zu tun gibt... Kumpel, mir geht's gut hier. Ich sage dir mehr - frag die Leute, ob sie diesen Ort verlassen wollen. Niemand will, außer zwei oder drei, hic!";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du beschlossen, meine Truhe zu überprüfen!","Du hast dich also entschieden, meine Truhen zu überprüfen? Damit kommst du nicht durch!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Truhen zu durchsuchen? Das wirst du nicht ungestraft tun!";
			link.l1 = "Dummes Mädchen!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Es macht mich nervös.","Weißt du, hier wird nicht toleriert, mit der Klinge herumzulaufen. Nimm sie weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","In Ordnung.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir laufen. Es ängstigt mich...");
				link.l1 = RandPhraseSimple("Habs verstanden.","Ich nehme es weg.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
