// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... Und wo ist Molligan? Wollte er mich nicht selbst sehen?";
				link.l1 = "Unser armer Paul hat Fieber. Er ist nicht in der Stimmung zu handeln. Ich bin hier an seiner Stelle.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Was wollen Sie, Mister?";
				link.l1 = "Ich nehme an, dass Sie darauf warten, etwas Eisenholz zu kaufen?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Wer hat Ihnen diesen Unsinn erzählt, Mister? Ich warte auf niemanden und nichts. Mein Schiff patrouilliert auf Befehl des Gouverneurs von Willemstad in der näheren Umgebung. Also, würden Sie so freundlich sein, mein Schiff zu verlassen, Sie müssen sich irren.";
			link.l1 = "Hm... Ich verstehe. Es tut mir leid, dass ich Sie belästigt habe.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Haben wir dieses Gespräch nicht schon geführt, Mister?";
			link.l1 = "Ja, ja. Ich gehe schon und besteige mein Schiff.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "Und wer bist du?";
			link.l1 = "Dich interessiert es doch nicht, mit wem du handelst? Ich habe Eisenholz zum Verkauf gebracht. Wie viel?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Nach der Vereinbarung - vierzig Dublonen pro Stück.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Kumpel, wir hatten einen Deal mit Molligan. Das ist ein guter Preis, du wirst keinen besseren finden. Also verhalte dich nicht wie ein Bauer im Laden. Wie viel Eisenholz hast du?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Prächtig. Das ist mehr als ich erwartet habe. Hier, nimm das Gold. Wenn du mehr Eisenholz bekommst, geh zur Taverne in Saint Martin und rede mit... du weißt schon wer. Er wird ein Treffen für uns arrangieren. Ich sehe, dass du ein viel besserer Partner bist als dieser Idiot Molligan.";
				link.l1 = "Gut. Es ist ein Deal.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Gut. Hier, nimm das Gold. Wenn du mehr Eisenholz bekommst, geh zur Taverne in Philipsburg und sprich mit... du weißt schon wer. Er wird Kontakt mit mir aufnehmen. Ich sehe, dass wir mit dir nicht schlechter Geschäfte machen können als mit diesem Idioten Molligan.";
				link.l1 = "Gut. Es ist ein Deal.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... Ich habe mehr erwartet. Schön. Hier, nimm das Gold. Und sag Molligan, dass er das nächste Mal eine Partie nicht kleiner als hundert Stück bringen muss.";
				link.l1 = "Gut. Ich werde es ihm sagen.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Bist du verrückt? Wir hatten eine Abmachung mit Molligan, die Lieferung darf nicht kleiner als fünfzig Stück sein! Verschwinde und komm nicht zurück, bevor du genug hast.";
			link.l1 = "Gut, gut, beruhige dich.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get ironwood, I will be able to sell it to Michael Rosencraft by having a meeting arranged with his man at the tavern in Philipsburg.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "Oh, mein alter Freund! Hast du etwas Eisenholz zu verkaufen?";
			link.l1 = "Genau, Michael. Lass uns handeln.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Wie viel hast du? Ich brauche eine Partie nicht kleiner als "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Ich weiß das. Ich habe "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  Stück Eisenholz, das du so begierig zu bekommen scheinst.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Leider habe ich nicht so viel.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Verdammt, haben sie dich nicht gewarnt? Oder haben die Ratten das Holz gefressen? Ich brauche "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" und nicht ein Stück weniger. Beim nächsten Mal bring mir so viel Holz, wie mein Beauftragter dir sagt. Ich hoffe sehr, dass du mich nicht noch einmal enttäuschen wirst, oder ich werde gezwungen sein, deine Dienste abzulehnen.";
				link.l1 = "Gut, Mynheer, ich werde in Zukunft aufmerksamer sein.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Du nimmst mich zum zweiten Mal aus. Mir gefällt das nicht. Wisse, dass dies die letzte Warnung ist, das nächste Mal werde ich deine Dienste ablehnen.";
					link.l1 = "Verdammte Ratten haben meine Waren beschädigt! Ich verspreche dir, Michael, das war das letzte Mal.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "Und jetzt ist meine Geduld am Ende! Ich möchte keine Geschäfte mehr mit dir machen. Verschwinde und vergiss mich.";
					link.l1 = "Aber Mynheer...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Wahnsinn! Es tut mir leid, Freund, aber ich kann nur kaufen "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", Ich habe nicht genug Geld für all Ihre Ladung. Ich habe eine Lieferung erwartet von "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" Stücke für vierzig Dublonen jeder...";
				link.l1 = "Gut. Nimm "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" jetzt und ich werde dir das Restliche nächstes Mal verkaufen.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Sehr gut. Der Preis ist der übliche, vierzig Dublonen für jedes Stück.";
				link.l1 = "In Ordnung für mich. Nimm deine Partie.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Freut mich, Geschäfte mit Ihnen zu machen. Kommen Sie wieder, wenn Sie mehr Eisenholz verkaufen möchten.";
			link.l1 = "Auf Wiedersehen, Mister. Unsere Zusammenarbeit ist sehr profitabel für mich. Auf Wiedersehen!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
