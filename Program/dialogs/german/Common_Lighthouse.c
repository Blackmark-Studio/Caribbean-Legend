#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Alarm wird in der Stadt ausgelöst. Anscheinend ist es an der Zeit, dass auch ich die Waffen ergreife...","Jagen die Stadtwachen zufällig hinter dir her?","Du findest hier keinen Schutz, aber vielleicht mehrere Zoll kalten Stahl unter deinem Rippen!"),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Schurke")+"?! Die Wachen sind dir auf der Spur, du wirst nicht weit kommen, "+GetSexPhrase("schmutziger Pirat","Stinker")+"!",""+GetSexPhrase("Dreckig","Schmutzig")+" Mörder! Wachen!!!","Ich fürchte dich nicht, "+GetSexPhrase("Schleicher","Stinker")+"! Bald wirst du in unserer Festung gehängt werden, du wirst nicht weit kommen..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Ich sehe, du bist es leid zu leben...","Es scheint also, es gibt keine friedlichen Leute in "+XI_ConvertString("Colony"+npchar.city+"Gen")+", jeder will ein Held sein!"),RandPhraseSimple("Geh zur Hölle!","Heh, das werden die letzten paar Sekunden deines Lebens sein..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Was führt dich diesmal zu mir?";
				link.l1 = "Ich glaube, Sie kennen einen Gentleman namens Gerard LeCroix? Er sollte eine Belohnung für mich hinterlassen haben...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Guten Tag, Matrose! Mein Name ist "+GetFullName(npchar)+", und ich bin der Wärter dieses Leuchtturms. Welcher Wind hat dich hierher gebracht?","Hallo! Es ist schon eine Weile her, seit ich das letzte Mal neue Gesichter an meinem Leuchtturm gesehen habe... Darf ich mich vorstellen - "+GetFullName(npchar)+", und dieser Leuchtturm ist mein Zuhause und meine Arbeit. Was kann ich für dich tun?");
				link.l1 = "Hallo dort, "+npchar.name+"! Mein Name ist "+GetFullName(pchar)+", ich bin ein Schiffskapitän. Ich machte einen Spaziergang um diese wunderbare Bucht und beschloss, vorbeizuschauen, um zu sehen, wer dort lebt.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, mein alter Freund, Kapitän "+GetFullName(pchar)+"! Komm rein, komm rein! Was hat dich dieses Mal hierher gebracht?";
				link.l1 = "Sei gegrüßt, alter Seebär! Jammerst du nicht in Einsamkeit hier an deinem Leuchtturm?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Nun, jetzt weißt du es. Ich war einmal ein Seemann, genau wie du, aber es ist lange her, seit ich das letzte Mal einen Schiffsboden betreten habe. Jetzt ist dieser Leuchtturm in meiner Obhut, und ich verkaufe auch ein paar Sachen...";
			link.l1 = "Und was genau verkaufen Sie?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " Was hat dich diesmal hierher gebracht?";
			link.l1 = RandPhraseSimple("Können Sie mir sagen, ob in Ihrer Kolonie kürzlich etwas Interessantes passiert ist?","Ich war schon eine Weile nicht mehr an Land... Was geht hier vor?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Lassen Sie uns sehen, was Sie zum Verkauf haben.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Also, "+npchar.name+", ist mein Amulett schon angekommen?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", Ich möchte bei dir ein Amulett bestellen.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Hör zu, "+npchar.name+", Ich weiß, dass Sie sich mit der Lieferung von Amuletten auf Bestellung beschäftigen. Also, Sie wissen sicherlich viel darüber. Schauen Sie bitte auf dieses kleine Ding - was können Sie mir darüber sagen?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Freund, ich bin wieder hier, um dich über diese seltsamen Amulette zu fragen";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Es gibt etwas, das ich dich fragen wollte...";
			link.l4.go = "quests";
			link.l9 = "Ich habe gerade mal reingeschaut...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Manchmal gehe ich an die Küste und sammle Muscheln, es gibt einen hübschen Ort nicht weit von hier, daher könnt ihr bei mir immer Perlen kaufen. Jeder Sturm bringt Bernstein, den verkaufe ich auch, obwohl er euch viel kosten wird.\nManchmal bringen die Wellen allerlei interessante Krimskrams von gesunkenen Schiffen und meine alten Kumpels bringen mir besondere Gegenstände. Ich bin an verzauberten Amuletten interessiert, weise Männer zahlen gutes Geld dafür.\nIch biete auch Waffen zu besonderen Anlässen an, fragt mich nicht, wo ich sie her bekomme. Ein Stadthändler kauft mir all den Mist ab, die guten Sachen verkaufe ich selbst, nachdem ich sie repariert und gereinigt habe.\nIch bin an Rum interessiert. Ich spreche nicht von dem Pisswasser, das sie in der örtlichen Taverne für zwei Pesos pro Krug servieren. Ich spreche von echtem jamaikanischem Rum in Flaschen. Er heilt und erweckt Menschen zum Leben. Für jede Flasche, die ihr bringt, zahle ich das Zehnfache. Denkt darüber nach.";
			link.l1 = "Hör zu, "+npchar.name+", Sie haben gesagt, dass Sie alte Seefahrerfreunde haben, die Ihnen verzauberte Amulette bringen. Ist es möglich, ein bestimmtes Amulett bei Ihnen zu bestellen? Ich werde dafür gut bezahlen.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Kapitän, eine Menge Waren ist kürzlich angespült worden - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". Einige Teile wurden durch salziges Wasser verdorben, aber "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" Ich habe es geschafft, in großartigem Zustand zu retten. Möchtest du etwas kaufen? Ich gebe sie billig weg, nur für "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" pro Einheit.";
				link.l1 = "Nein. Zeige mir deine neuesten Sammlungen.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... Ein ehrliches Angebot, ich stimme zu. Ich denke, ich könnte es mit etwas Gewinn weiterverkaufen. Lass uns sehen... Das würde sich auf "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Ist das korrekt?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Sie haben es richtig erkannt, Kapitän. Ein großartiges Geschäft! Wir haben beide einen anständigen Gewinn daraus gemacht...";
			link.l1 = "In Ordnung, dann. Ich werde die Matrosen losschicken, um die Ladung auf mein Schiff zu bringen. Zeig mir nun, was du zum Verkauf gesammelt hast.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Nun, nicht alle von ihnen, aber einige Krimskrams werden häufiger gebracht als andere, also denke ich, ich könnte Ihnen helfen. Aber ich warne Sie: alle auf diese Weise bestellten Amulette werden Sie 100 Dublonen kosten. Sie sollten verstehen...";
				link.l1 = "Preis ist kein Problem. Welche Amulette können Sie liefern?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! Man könnte ein Schiff mit so viel Geld kaufen. Es ist zu teuer. Ich denke, ich werde alleine zurechtkommen...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Nein, Kapitän. Solche Dinge können rein zufällig gefunden werden, daher ist es unmöglich, sie im Voraus zu bestellen. Und außerdem müssten Sie etwas weniger als für immer auf sie warten...";
				link.l1 = "Nun, wenn das der Fall ist, ist nichts zu tun.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Wie du wünschst. Komm und besuche mich, wenn du deine Meinung änderst.";
			else dialog.text = "Möchten Sie sehen, was ich heute zum Verkauf habe, Kapitän? Wenn Sie nichts Würdiges finden, kommen Sie bald wieder - ich könnte etwas anderes zum Verkauf haben.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "All dies, natürlich, ist gut, aber hier ist, was ich fragen wollte - Ich nehme an, du kennst einen Gentleman namens Gerard Lecroix? Er sollte eine Belohnung für mich hinterlassen haben...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Zeig mir deine Sachen.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Sag mir nur, was in letzter Zeit Interessantes in deiner Kolonie passiert ist?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Handel ist Handel, aber ich wollte etwas fragen.";
			link.l3.go = "quests";
			link.l4 = "Hab einen schönen Tag, "+npchar.name+"! Es war schön, dich zu treffen! Ich schaue ein anderes Mal vorbei...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Treffen Sie Ihre Wahl.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Leider interessiert mich bisher nichts von dieser Liste.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Eine Voodoo-Puppe? Du hast eine Vorliebe für Schusswaffen? Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Ein Schwarzpulvertester? Scharfschießen ist der Schlüssel zum Erfolg in jedem Scharmützel. Schön...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Ein Ritualmesser? Du magst es, deine Feinde mit kräftigen Schlägen eines schweren Breitschwerts zu zerfetzen? Dann ist das für dich. Gut... ";
			link.l1 = "Wann sollte ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Eine Hellebarde? Ein Schlag von oben mit einer riesigen Axt wird jeden Feind zermalmen! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Eine Tsantsa? Jetzt kann das Ding sogar den unerschrockensten Piraten erschrecken. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Ein Korallenkopf? Die Traubenschüsse deiner Kanonen werden direkt ins Ziel fliegen! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Buckelwal? Ausdauer ist der beste Freund eines Kriegers. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Lass den Rumpf des feindlichen Schiffes zu Staub zerfallen! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Setz Baldo ein - und alle Kanonenkugeln fliegen direkt ins Ziel! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Schlangengift ist das gefährlichste. Gut...";
			link.l1 = "Wann sollte ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Ngombo Maske? Leg die Wachsamkeit deiner Feinde ab, ha-ha! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Ngombo Schild? Wenn du es nicht geschafft hast, einer Kugel auszuweichen, kann dieses Amulett dein Leben retten. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? Ein gutes Gebet kann sogar eine Kugel ablenken. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Ein Kreuz? Dieses wird einem Christen im Nahkampf sehr helfen. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? Dieser wird eine tödliche Wunde nur zu einem Kratzer machen. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? Und lasst die Kanonen immer kampfbereit sein! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? Das Antlitz der allerheiligsten Jungfrau besitzt mächtige Heilkräfte. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Heiliges Wasser? Selbst ein Schwächling, der mit heiligem Wasser bespritzt wird, wird zum epischen Helden! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Ein Anker? Und möge dein Schiff auch unter einer Salve von Kanonenkugeln schwimmen bleiben, ha-ha! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? Eure Segel sollen keinen Wind fürchten, solange ihr diesen Amulett besitzt. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Wunderwirker? Möge der Herr über deine Mannschaft sowohl an Land als auch auf See wachen! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? Musketenkugeln sollen über deinen Kopf fliegen, ohne Schaden anzurichten! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Jeder Schiffsbauer träumt davon. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? Das wird etwas Zeit beim Flicken der Segel sparen. Gut...";
			link.l1 = "Wann sollte ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Ein Affe? Ich würde sagen, ein Packesel! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Zigeunerfan? Leg einem Patrouillen die Scheuklappen an! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Ein Jadepanzer? Das ist dein Trumpf im Spiel! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Ein Affenknoten? Wie man sagt - lass sie dich respektieren! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Ein Fischer? Das ist der Traum jedes Navigators. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Händlerperlen? Geld wird gerne gezählt, nicht wahr? Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Jeder alte Kahn mit niedriger Geschwindigkeit wird schneller fliegen als der Wind! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Seemannsohring? Gib den mal deinem Steuermann! Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Pilger? Gegenwind wird zu Rückenwind. Gut...";
			link.l1 = "Wann soll ich zurückkommen, um meine Bestellung abzuholen?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "In zwei Monaten, nicht früher. Ich denke, bis dahin werden sie es mir gebracht haben. Also warte ich in zwei Monaten mit dem Geld auf dich.";
			link.l1 = "Großartig! Ich werde da sein! Danke, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Ja, ich habe es. Hast du 100 Dublonen vorbereitet, Kapitän?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Sicher! Hier hast du, wie vereinbart.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Oh, ich habe das Geld auf dem Schiff vergessen! Ich bringe es bald.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Noch nicht. Komm später zu mir. Und mach dir keine Sorgen - dein Amulett wird sicher ankommen.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Alles scheint in Ordnung zu sein. Hier ist dein Amulett. Viel Glück damit!";
			link.l1 = "Danke, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Zeig mal, was du da hast.";
			link.l1 = "Hier, es sieht aus wie ein alter indisches Amulett. Aber ich habe keine Ahnung, wie man es benutzt oder seine verborgene Kraft.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Nun, nun. Du bist die dritte Person, die mir so etwas zeigt, Kumpel. Dieser Amulett wurde aus dem wilden Selva des südlichen Main hierher gebracht. Es gibt Indianer nicht weit von Panama, die solche Schmuckstücke wie dieses tragen. Die Rothäute sagen, dass dies ein Vermächtnis ihrer 'großen Vorfahren' ist.\nIch habe keine Ahnung, wer ihre Vorfahren waren oder welches Vermächtnis sie hinterlassen haben, aber ich kann dir einen Rat geben, wo du dich erkundigen kannst. Interessiert?";
				link.l1 = "Sicherlich!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one, I see for the first time in the Caribbean. Sorry, mate, I cannot help you; I don't know this kind of stuff. But it is not a simple thing; that's a fact. Ask somebody else. I know for sure that there are other lighthouse keepers like me who know about amulets not any less.";
				link.l1 = "Entschuldigung... Ich werde dann weiter fragen.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is a Carib village on Dominica, and the local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, a highly respected Indian. He's not one of the Caribs; he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. He really hates them. After all, they once enslaved him and took him away from his home...";
			link.l1 = "Ich nehme an, er ist auf diese Weise in die Karibik gekommen?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Ja. Das ist eine sehr interessante Geschichte. Das Schiff, welches indische Sklaven transportierte, wurde in der Nähe von Marie Galante von der Flaute gefangen und die Hälfte der Besatzung starb an einem plötzlichen Fieber. Doch kein einziger Inder erkrankte!\nDanach drehte der Kapitän durch und setzte sein Schiff in Brand. Daraufhin begannen die eingesperrten Inder einen Aufstand und schlachteten die Besatzung ab. Kannst du erraten, wer ihr Anführer war?";
			link.l1 = "Ich mache...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Das ist es. Ich wette, es war ein Schamanenzauber, der das Meer so ruhig wie einen Toten machte und die Mannschaft mit einer tödlichen Krankheit infizierte. Dieser Indianer ist sehr klug und sehr gefährlich. Wenn du zu ihm gehst - verhalte dich höflich und hüte deine Zunge - sonst gibt es viele Probleme für dich. Außerdem wird er nicht einmal mit dir reden, ohne ein Opfer für ihn.";
			link.l1 = "Und welche Art von Opfer könnte er verlangen?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Du wirst ihn nicht mit irgendeinem Müll bestechen. Soweit ich weiß, schickt er seine Karibischen Soldaten zu den Siedlungen der Weißen, um Feuerwaffen zu kaufen. Bring ihm ein Musket als Geschenk und dann, denke ich, wird er erfreut sein und dir etwas seiner Aufmerksamkeit schenken.";
			link.l1 = "Danke! Ich werde tun, was du sagst... Sag mal, Kumpel, wie weißt du das alles?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Mein Freund war ein Seemann auf dem unglückseligen Schiff. Glücklicherweise konnte er in dieser Hölle überleben... Ich sah an ihm einen solchen Amulett wie deinen, es scheint, als hätte der verstorbene Kapitän auch die Habseligkeiten des Indianers ergriffen. Ich bin sicher, dass dein Amulett aus seiner Sammlung stammt - als der Kapitän verrückt wurde und sein Schiff in Brand setzte, töteten seine Seeleute ihn und plünderten dann die Truhen in der Kabine.";
			link.l1 = "Verstanden. Dann muss ich nur mit einem Geschenk nach Dominica gehen. Danke für deine Hilfe und die interessante Geschichte!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Viel Glück, mein Freund, und sei vorsichtig mit diesem Rotfell-Teufel...";
			link.l1 = "..., Freund.";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Ja? Du hast mit Tuttuathapak gesprochen, nicht wahr?";
			link.l1 = "Genau. Und jetzt möchte ich zwei weitere Amulette finden. Du hast gesagt, ich sei der Dritte, der dir dieses Artefakt gezeigt hat. Und wer waren die anderen beiden?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Einer ist mein Freund, der Seemann von dem Schiff, das Tuttuathapak zu den Karibischen Inseln brachte. Seit diesem Vorfall hat er keinen Fuß mehr auf ein Schiffsdeck gesetzt. Ich habe ihn eine Weile nicht gesehen, aber ich weiß, wo er lebt. Sucht ihn in der West Main, in Belize - er ist jetzt Jäger und streift durch den Dschungel. Sein Name ist Fergus Hooper.";
			link.l1 = "Gut. Und der Zweite?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Ich weiß nur ein wenig über den Zweiten. Ob sein Name Jack oder Jackson ist, und ob er ein Freibeuter, Kleinunternehmer oder einfach nur ein Abenteurer ist. Er besitzt eine Xebec mit einem seltsamen Namen... hmm... ihr Name ist... Verdammt, ich habe es vergessen! Aber der Name ist irgendwie dämonisch. Ich fragte ihn, was es bedeutete, und er sagte, es sei eine Vogelfrau, geboren von Meeresgöttern. Pfah! Gottlos...";
			link.l1 = "Nerd... Erinnerst du dich also nicht an ihren Namen?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Nein, möge der Donner mich treffen, ich erinnere mich nicht. Oh, und als er sich vorstellte, erwähnte er, dass er aus Barbados stammt.";
			link.l1 = "Das ist doch was! Gut, ich werde versuchen, diesen Liebhaber von gefiederten Frauen zu finden, bevor ihn jemand anderes findet... Danke, Kumpel, du hast mir sehr geholfen!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Seid willkommen, Kapitän, kommt manchmal vorbei.";
			link.l1 = "Sicher!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Du bist "+GetSexPhrase(" ein Dieb, meine Liebe! Wachen, ergreift ihn"," Dieb! Wachen, ergreift sie")+"!!!","Wow! Ich habe nur kurz weggeschaut, und schon hast du den Kopf schon in der Truhe! Halt den Dieb!","Wachen! Raub! Stoppt den Dieb!");
			link.l1 = "Verdammt nochmal!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ach, also bist du dieser Kapitän! Ja, ich habe auf dich gewartet. Gerard hat auch gewartet, aber er musste dringend auf eine Expedition, also bat er mich, die Zahlung an dich zu überweisen. Er sagte, du musst kommen. Hier sind vierhundert Dublonen, wenn es dir recht ist.");
			link.l1 = "Danke! Es ist schön, mit ehrlichen Leuten zu verhandeln.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("You have received 400 doubloons");
			PlaySound("interface\important_item.wav");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
