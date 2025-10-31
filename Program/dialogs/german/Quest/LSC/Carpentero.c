// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "Ich will nicht mit dir reden. Du greifst friedliche Leute ohne Grund an und provozierst sie zum Kampf. Verschwinde aus meiner Taverne!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! Ich bin so froh dich zu sehen! Ich wusste es, ich wusste, dass die Gerüchte eine Lüge waren! Verdammt, wir müssen jetzt unbedingt darauf trinken!";
				link.l1 = "Nun, lass uns trinken, Kumpel! Ich bin auch verdammt froh, dich zu sehen!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", es tut mir leid wegen deines Versagens. Nur wenige können den dicken Mann übertrinken. Wie geht es deinem Kopf?";
				link.l1 = "Ja, Kumpel, du hast da einen guten starken Rum. Ich schulde dir für die Drinks... wie viel?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Du hast Fazio besiegt, "+pchar.name+"! Ich bin überrascht, nur wenige konnten ihn unter den Tisch trinken. Hier, nimm deine zweihundert Dublonen.";
				link.l1 = "Danke für die freundlichen Worte, Kumpel!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? Sie sagen, dass du in einem Anzug, der von einem Narwal-Mechaniker gemacht wurde, auf den Grund getaucht bist. Ist das wahr oder nur Klatsch, wie üblich?";
				link.l1 = "Es ist wahr, Kumpel. Ich bin dort wirklich getaucht.";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Grüße an den neuen Mann in meiner Taverne! Willkommen! In meiner Taverne gibt es immer etwas zu trinken, meine Weinvorräte sind gefüllt, kann nicht dasselbe über Essen sagen, allerdings, ha-ha... Nur ein Scherz. Mein Name ist Sancho Carpentero und ich besitze diesen Ort.";
				link.l1 = TimeGreeting()+", Sancho. Mein Name ist "+GetFullName(pchar)+". Schön, dich zu treffen.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, mein Freund "+pchar.name+"! Froh, dich in meiner Taverne zu sehen! Möchtest du etwas trinken?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Hör zu, Sancho, weißt du, wo ich ein gutes Musketen bekommen kann? Nicht eine gewöhnliche Soldatenwaffe, sondern etwas Genaueres, vielleicht zum Jagen?";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Hör zu, Sancho, ich habe ein paar Fragen an dich. Ich suche einen Mann namens Adolf Barbier. Man sagt, dass er diesen Ort oft besucht...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Hör mal, Sancho, man sagt, dass Chad Kapper bei dir etwas Arsen gekauft hat...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, möchtest du, dass ich dir etwas Interessantes zeige? Ist das die Fledermausmaske, die du so sehr in die Hände bekommen wolltest?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, ich bin wegen meines Kürassiers hier. Hier ist das Geld.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, ich bin wegen meiner Rüstung hier. Hier ist das Geld.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Serviere mir etwas Rum, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Ich möchte übernachten.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Gelangweilt... Sancho, ich möchte hier mit einer Flasche Wein bis zum Abend verbringen...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Haben Sie etwas Interessantes zu erzählen?","Was ist kürzlich auf der Insel passiert?","Irgendwelche Klatschgeschichten?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Sancho, ich möchte dir Krabbenklauen verkaufen.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, ich möchte dich etwas über die Insel fragen.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Nein, Kumpel. Wollte nur mal sehen, wie es dir hier geht.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "So bin ich auch. Ich hoffe, ich werde Sie zumindest jeden zweiten Tag oder sogar jeden Abend sehen, ha-ha! Ich bin aufrichtig froh, jeden Besucher in meiner Taverne zu haben.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Serviere mir etwas Rum, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Ich möchte übernachten.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, ich möchte dich etwas über die Insel fragen.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Auf Wiedersehen, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Nein, Freund, ich kann dir nicht helfen. Weißt du, ich bin Spezialist für Biergläser und Weinflaschen - aber nicht für Musketen, ha-ha! Geh zum Laden, ich habe gehört, dass Axel manchmal interessante Waffen verkauft. Vielleicht findest du dort, was du brauchst.";
			link.l1 = "Danke für den Rat.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Ja, er besucht mich ab und zu, obwohl ich ihn in den letzten Tagen nicht gesehen habe. Er ist verschwunden, seitdem er mit diesem fetten Mann Giuseppe gesprochen hat.";
			link.l1 = "Giuseppe? Meinst du Giuseppe Fazio?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ha, Kumpel, es gibt nur einen Giuseppe auf der Insel - Giuseppe Fazio. Ja, das ist er. Sie saßen ein paar Stunden rum und tranken Rum, führten ein sehr lebhaftes Gespräch.";
			link.l1 = "Haben sie gestritten?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Nein. Es sah so aus, als wären sie alte Kumpel. Schau, besuche einfach Fazio bei der 'Caroline' und frage ihn nach Adolf.";
			link.l1 = "Gut, ich mache das.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Ist das alles? Du hast gesagt, du hättest ein paar Fragen...";
			link.l1 = "Ja. Sag mir, wer sind Rote Mary und Zyklop Marcello?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Red Mary ist eine der Narwale. Eine junge und schöne Frau, aber sie ist völlig wild, ja. Sie weiß, wie man ihr Schwert und eine Handfeuerwaffe genauso gut wie jeder Mann benutzt. Sie war die Freundin von Alan Milrow, einem ehemaligen Anführer des Narwal-Clans, bevor der Admiral ihn tötete\nAlans Tod hat sie hart getroffen, die meiste Zeit weint und verflucht sie Shark in ihrer Kabine auf der 'Ceres Smithy'... Aber sie wird darüber hinwegkommen, das Leben geht schließlich weiter\nÜber Marcello weiß ich nicht viel, habe ihn nur ein paar Mal gesehen. Verdächtiger Kerl. Man sagt, dass er ein königlicher Jäger war, verlor ein Auge im Kampf und ging als Enteroffizier segeln\nEr hasst Piraten, sieht so aus, als hätte er eine Abneigung gegen sie. Nicht überraschend, angesichts seines früheren Dienstes in Entertrupps von Handelsschiffen.";
			link.l1 = "Ich verstehe. Vielen Dank, Sancho, du hast sehr geholfen!";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Du bist willkommen, Kumpel, komm wieder vorbei, und wir werden zusammen ein Bier trinken...";
			link.l1 = "Sicher!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper? Nein. Er hat die Taverne in letzter Zeit nicht besucht. Marcello Zyklop hat vor gerade mal fünfzehn Minuten eine Flasche Arsen gekauft - er wird auch von Ratten geplagt. Ich verstehe ihn vollkommen... Verdammt noch mal, Ratten.";
			link.l1 = "Marcello Zyklop?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Nun, ja. Ist das seltsam?";
			link.l1 = "Nein, natürlich nicht! Ich suche ihn schon seit einigen Tagen und es stellt sich heraus, dass er kürzlich hier war. Könnten Sie mir sagen, wohin er gegangen ist?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Er war mit Adolf Barbier, der in der 'Santa Florentina' wohnt. Vielleicht gingen sie dorthin.";
			link.l1 = "Danke!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Wenn Sie etwas Arsen brauchen, dann kann ich Ihnen eine Flasche für zwanzig Dublonen verkaufen.";
			link.l1 = "Gut. Wir werden später darüber sprechen, Sancho. Bis später!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Komm schon, Kumpel! Du schuldest mir nichts. Du hast bereits hundert Dublonen verloren. Es war ein Fehler, mit Fazio Geschäfte zu machen...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Nein-nein, Sancho! Danke und bitte nimm diese fünfhundert Pesos. Das sollte die Kosten für die Getränke decken, soweit ich mich erinnere. Ich möchte nicht in deiner Schuld stehen.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh, danke, Sancho. Du hast recht.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... dann habe ich einen Vorschlag für dich. Hast du dort Riesenkrebse gesehen?";
			link.l1 = "Habe ich Krabben gesehen? Es gab Horden von ihnen! Und von welchem Vorschlag sprichst du?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Wenn du einige Krabben tötest, bring mir bitte die Scheren. Ich werde dich gut in Dublonen bezahlen - fünf Münzen für jede. Axel Yost zahlt nicht so viel, vertrau mir. Ich bitte nicht darum, dass du für diese Aufgabe Krabben jagst - aber wenn du auf einige stößt, denk bitte daran...";
			link.l1 = "Warum Scheren? Was ist mit den anderen Teilen eines Krebses? Was machst du damit?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Warum Scheren? Weil das meiste Fleisch daran ist. Krabben haben nicht viel Fleisch an ihren Beinen und die Körper sind von einer festen Schale bedeckt. Krabbenfleisch ist hier eine Delikatesse, es hat einen exquisiten Geschmack und ist sehr nahrhaft\nIch habe auch ein einzigartiges Rezept dafür, also zahle ich Ihnen fünf Dublonen für jede Zange.";
			link.l1 = "Gut. Ich werde es im Hinterkopf behalten.";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Prächtig! Wie viele hast du?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "Ich habe meine Meinung geändert.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Abgemacht. Hier, nimm deine Dublonen - "+FindRussianQtyString(iTotalTemp*5)+". Danke, Kumpel, wenn du mehr bekommst, bring sie zu mir.";
			link.l1 = "Sicher, Freund.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Was?! Zeig mir! Lass es mich sehen!";
			link.l1 = "Sicher.";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Das ist es... wirklich! Es ist genau das gleiche wie das auf dem Bild, das ein Seemann für mich gezeichnet hat! Freund, es muss einen Grund geben, warum du das zu mir gebracht hast, was willst du dafür? Wie viel?";
			link.l1 = "Natürlich habe ich es aus einem Grund zu dir gebracht. Aber was kannst du als Belohnung anbieten? Wenn ich mich recht erinnere, hast du mir eine königliche Belohnung für dieses Ding versprochen...";
			link.l1.go = "rat_2";
			link.l2 = "Entschuldigung, Kumpel, es steht nicht zum Verkauf. Ich brauche es für mich selbst. Wollte nur sicherstellen, dass dies das Amulett ist, von dem du gesprochen hast.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, was für eine Schande... Ja, Bursche, das ist genau dieser Talisman. Glücklicher Teufel! Jetzt werden die Ratten dir keine Probleme mehr bereiten. Und ich muss sie weiterhin mit Arsen ausrotten...";
			link.l1 = "Es tut mir leid, dass ich dich geärgert habe, Sancho. Ich habe es noch nie zuvor gesehen, also brauchte ich eine Beratung. Es tut mir leid.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Dafür,"+pchar.name+", ich biete Ihnen die Möglichkeit, den feinsten und wertvollsten Gegenstand zu erwerben, den ich besitze. Es wäre ein ausgezeichneter Tausch für diesen Charme, besonders für einen mutigen Krieger wie Sie. Lassen Sie mich es für Sie holen.\nSchauen Sie: hier ist ein einzigartiger, prächtiger Mailänder Kürass, akribisch gearbeitet! Er bietet außergewöhnlichen Schutz im Kampf, ermöglicht uneingeschränkte Bewegung und ist leicht und bequem. Rüstungen dieser Qualität sind sowohl in der Karibik als auch in Europa selten.\nIch stolperte vor einigen Jahren in der Kapitänskajüte eines spanischen Kriegsschiffs über diesen Kürass und behielt ihn genau für einen Anlass wie diesen. Ich bin bereit, ihn Ihnen für zweitausend Goldmünzen und den Rattengott zu verkaufen!";
			link.l1 = "Hmm... Das IST eine ausgezeichnete Panzerung! Ich glaube, dieser Austausch passt zu mir. Ich werde die Rattensituation in den Griff bekommen, aber eine weitere Panzerung wie diese zu finden, wäre fast unmöglich. Ich habe noch nie eine ganz wie diese gesehen. Wirklich, es ist ein einzigartiges Rüstungsteil.";
			link.l1.go = "rat_yes";
			link.l2 = "Wie viel? Sancho, haben deine Ratten dich heute Morgen schon ein paar Mal gebissen? Was meinst du mit zweitausend? Weißt du überhaupt, was es mich gekostet hat, dir dieses Idol zu besorgen? Senke den Preis sofort!";
			link.l2.go = "rat_torg";
			link.l3 = "Wie viel?! Du bist ein Hai, weißt du das, Sancho? 'Biete eine Kaufgelegenheit an!' Ha! Für diese Art von Geld könnte ich mir auf dem Festland eine Rüstung bestellen, die Kugeln abwehrt und mich obendrein heilt! Und wofür würdest du so viel Gold brauchen? Damit Jürgen deine eigene Statue für dich gießt und sie in voller Höhe auf 'San Agustin' ausstellt?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Ich bin froh, dass Sie an Bord sind, mein Freund. Danke, dass Sie mein Problem nicht vergessen haben! Also, ich werde meine Dublonen erwarten. Die Rüstung wird auf Sie warten.";
			link.l1 = "Ich bringe sie gleich rüber!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", unter anderen Umständen würde ich fünftausend verlangen. Der Admiral selbst hat Interesse gezeigt, und er ist nicht der Einzige, glaub mir. Nimm dir Zeit zum Überlegen. Die Rüstung wird so lange auf dich warten, wie du brauchst. Ich werde sie nur an dich verkaufen.";
				link.l1 = "Ich werde darüber nachdenken, Sancho. Ich werde lange und gründlich nachdenken.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", unter anderen Umständen würde ich fünftausend verlangen. Der Admiral selbst hat Interesse gezeigt, und er ist nicht allein, glauben Sie mir. Gut, ich werde fünfhundert abziehen, wenn Sie mich und mein Problem nicht vergessen haben. Es scheint, dass es unterwegs einige Abenteuer gab.";
				link.l1 = "Das ist besser. Aber ich verstehe immer noch nicht, warum ich in diesem Handel mit gleichermaßen einzigartigen Gegenständen extra zahlen sollte. Vielleicht solltest du derjenige sein, der mir bezahlt, hm Sancho?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "Nein, "+pchar.name+", wird nicht passieren. Ich kann Ratten mit Gift bekämpfen, aber diese Rüstung könnte eines Tages dein Leben retten. Und du wirst aussehen wie ein italienischer Herzog, der sie trägt. Eintausendfünfhundert, das ist mein letztes Angebot. Denk darüber nach und lass es mich wissen. Die Rüstung wird so lange auf dich warten, wie du brauchst, ich werde sie nur an dich verkaufen.";
				link.l1 = "Sancho, wenn du nicht der einzige Wirt in diesem traurigen Friedhof wärst... Ich werde über dein Angebot nachdenken.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "Für einen Militärkapitän und einen Piraten, können Sie sicher verhandeln! Erinnern Sie sich an Jost? Er hat es einmal geschafft, all mein Arsen mit einem Rabatt zu kaufen, während die Ratten mich schon gequält haben. Also gut, "+pchar.name+", du gewinnst. Ich ziehe weitere fünfhundert für dich ab! Aber das ist mein letztes Angebot!";
				link.l1 = "This still feels like a rip-off, but at least now I won't feel like a typical damsel in distress in the jungle. Wait for the money; I'll bring it soon.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Beruhige dich, "+pchar.name+". Von jemand anderem würde ich fünftausend verlangen! Der Admiral selbst hat Interesse gezeigt, und er ist nicht allein, glaub mir. Die Rüstung wird so lange auf dich warten, wie es nötig ist. Das ist auch im Preis des Idols inbegriffen.";
			link.l1 = "Welch eine Ehre! Mach weiter mit dem Polieren deiner Brille, und ich bin auf meinem Weg. Zwei tausend!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Fertig! Ich bin froh, dass du zugestimmt hast, Kumpel. Danke, dass du mein Problem nicht vergessen hast! Nimm die Kürass, möge sie dir im Kampf gut dienen.";
			link.l1 = "Hier, nimm auch dein Talisman - es sieht so aus, als kämen dunkle Tage auf die Ratten in deiner Taverne zu!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "Du erstaunst mich immer noch "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Erinnere mich nicht daran!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Ich höre zu.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Was ist das hier für ein Ort? Kannst du mir mehr darüber erzählen?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Wie kann ich die Insel verlassen?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Was sollte ich über die Insel wissen?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Und wie geht es Ihnen hier? Wie läuft Ihre Kneipe?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Ich habe keine Fragen, vergiss es...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Dieser Ort? Nun, sie nennen es die Insel der Gerechtigkeit, die Insel der verlassenen Schiffe oder Stadt der verlassenen Schiffe - aber wir nennen es einfach die Insel. Sie besteht aus Schiffswracks, die auf einem Riff unter den Riffen stecken geblieben sind. Der zentrale Teil der Insel ist ein Wohngebiet und der äußere Ring ist unbewohnt. Seit zehn Jahren besteht keine Verbindung zur Außenwelt.";
			link.l1 = "Habs verstanden...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Bau ein Langboot oder ein Floß. Aber es wird nicht gut für dich enden. Es gibt eine Anomalie-Sturmzone um die Insel, du wirst den äußeren Ring nicht passieren können, ohne dein Leben zu riskieren. Außerdem wird die Insel von einer starken Strömung umkreist\nDu brauchst ein Team, um auch nur eine schlanke Überlebenschance zu haben. Und sehr wenige Einheimische sind bereit, diesen Ort zu verlassen. Noch weniger sind bereit, Risiken einzugehen. Die Leute hier mögen ihre Lebensweise. Frag herum, wenn du mir nicht glaubst.";
			link.l1 = "Ich sehe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Zuerst sollten Sie sich daran erinnern, dass es auf der Insel mehrere eingeschränkte Bereiche gibt. Zwei Clans - Narwale und Rivados, sie leben schon seit langem hier, bekämpfen einander und schützen furchtlos die Gebiete, die sie für ihre eigenen halten. Versuchen Sie, sie ungebeten zu besuchen, und Sie sind ein toter Mann\nSie müssen das aktuelle Passwort kennen, wenn Sie ihr Territorium betreten wollen. Machen Sie sich keine Sorgen, dort zufällig hinzugelangen, die Wachen werden Ihnen mehrere Warnungen geben, bevor sie anfangen zu schießen.";
			link.l1 = "Ich werde das im Hinterkopf behalten...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I used to work with food and drinks: I worked as a cook a long time ago in Europe, as an intendant in a garrison, a tavern keeper, and a cook on a ship; so the first thing I did here was establishing a tavern\nI like my job and my life is oddly satisfying. Folks are friendly here, mostly. At least they don't kill each other frequently. Clans don't interfere with my activities. All in all, this the best place I've had my life. I'm free here and no one tells me what to do\nThe only thing driving me mad are rats. They torture me, eating my provisions and ruining my tableware. I have trouble getting rid of them.";
			link.l1 = "Ratten? Ja, sie sind das Problem aller...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Ach, ich bin hier der unglücklichste Mensch, wenn es um Ratten geht. Andere Schiffe werden nicht so von Ratten terrorisiert und Axel Yost hat es irgendwie geschafft, sie ein für alle Mal loszuwerden. Was mich betrifft, so kriechen hier Armeen von Ratten herum. Eh, mir wurde gesagt, dass es einen besonderen Amulett namens der Rattengott gibt.\nEs sieht aus wie eine Fledermausgesichtsmaske. Sie sagen, dass dieses Amulett Ratten zu Tode erschreckt. Ich vermute, jemand hat Axel dieses Amulett verkauft, er kauft und verkauft jeden Müll, den sie auf dem äußeren Ring finden\nIch wünschte, jemand würde mir das Amulett bringen, ich biete dieser Person eine königliche Belohnung an!";
			link.l1 = "Interessant...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", Ich denke, du solltest aufhören. Gott bewahre, dass du in Schwierigkeiten gerätst oder über Bord fällst, um Krabbenfutter zu werden... Es ist keine gute Idee, hier zu viel zu trinken, viele Leute sind deswegen gestorben.";
				link.l1 = "Hm... Ich vermute, du hast Recht, Sancho - Ich habe bereits genug. Danke für deine Besorgnis!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Sei willkommen, Kumpel. Nur fünfundzwanzig Pesos für den Liter meines besten Rums!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Nun, auf Ihre Gesundheit und auf den Wohlstand Ihrer Taverne, Kumpel!","Nun, zu denen, die auf See sind!","Nun, zu den Bewohnern Ihrer Insel!"),LinkRandPhrase("Nun, zur Insel, und möge sie für immer bestehen!","Nun, möge der Wind immer günstig in all unseren Taten sein!","Nun, auf Glück, Glückseligkeit und... Frauen!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Ich glaube nicht, dass es eine gute Idee für dich ist, jetzt zu trinken. Vertrau mir...";
				link.l1 = "Gut.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, du bist ein seltsamer Mann... Hast du niemanden, mit dem du hier auf der Insel die Zeit verbringen kannst? Kumpel, Mary wird mich umbringen, wenn ich dich hier alleine betrunken werden lasse. Komm am Abend her und amüsiere dich bis zum Morgengrauen, wenn du willst.";
				link.l1 = "Gut...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Kein Problem, Kumpel. Für nur dreihundert Pesos bekommst du eine feine Flasche von "+LinkRandPhrase("Spanisch","Italienisch","Französisch")+" Wein - und amüsiere dich so lange du willst.";
				link.l1 = "Danke!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Ich glaube nicht, dass du gerade jetzt schlafen solltest. Vertrau mir...";
				link.l1 = "Gut.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Ich habe noch nie einen so seltsamen Mann getroffen. Ein schönes Mädchen wartet auf ihn in der 'Ceres Schmiede' und er will die Nacht in der Taverne verbringen. Denk nicht einmal daran, dass ich dich hier schlafen lasse. Mary würde mich dafür umbringen.";
					link.l1 = "Gut...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Du kannst dich oben bis zum Abend ausruhen. Aber ich lasse dich hier nicht übernachten - Mary würde mich dafür umbringen. Es tut mir leid...";
					link.l1 = "Gut. Ich bleibe hier bis zum Abend...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Gut... Ich werde ohne Schlaf auskommen.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Sie können für nur zwanzig Pesos im Bett oben schlafen. Wann soll ich Sie wecken?";
			if(!isDay())
			{
				link.l1 = "Am Morgen.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Vor Einbruch der Nacht.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Nächster Morgen.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Ich habe meine Meinung geändert. Ich möchte nicht schlafen.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
