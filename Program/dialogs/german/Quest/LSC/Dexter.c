// старпом Акулы - Лейтон Декстер
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
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Was willst du, Junge? Sprich mit Shark, er ist hier der Boss.";
				link.l1 = "Kann ich dir wenigstens Hallo sagen oder ist das gegen die Regeln?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, Shark hat mir erzählt, dass du eine Karte der Insel hast. Verkaufst du sie?";
					link.l2.go = "map";
				}
				dialog.text = "A-ah, "+GetFullName(pchar)+"! Hast du Geschäfte mit mir oder willst du nur wieder reden? Wenn ja, bring nächstes Mal eine Flasche Rum mit, ha-ha!";
				link.l1 = "Nein, ich habe kein besonderes Geschäft für dich. Nächstes Mal bringe ich Rum, nur für dich.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! Du bist ein Spaßvogel, nicht wahr, Junge? Gut... Mein Name ist Layton Dexter, ich bin Sharks Stellvertreter und heutzutage bin ich sein Vertreter in dieser verdammten Stadt der verlassenen Schiffe. In der Zwischenzeit verkaufe ich Vorräte und versuche, Geld aus diesem Faulenzer Fazio zu bekommen.";
			link.l1 = "Und mein Name ist "+GetFullName(pchar)+". Freut mich, Sie kennenzulernen!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Ich nehme an, du hast schon gehört, dass Steven tot ist. Die Narwale haben es getan.";
			link.l1 = "Du hast recht, das weiß ich... Na und, du bist jetzt der Admiral?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Genau. Chad ist zu den Narwalen übergetreten, Steven ist tot und deshalb - da ich der Zweite im Kommando bin, bin ich jetzt natürlich der Admiral. Einwände?";
			link.l1 = "Nein. Keine Einwände.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Gut. Lass deine Fragen hören.";
			link.l1 = "Bist du dabei, Rache an den Narwalen für Stevens Tod zu nehmen?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "Du meinst, ob ich ihnen den Krieg erklären werde? Nein. Es gibt bessere Wege, um sie bezahlen zu lassen. Zuerst werde ich den Preis, den sie für Vorräte zahlen, verdreifachen\nWenn sie die 'San Augustine' angreifen, werden wir ihnen die Hölle heiß machen. Dann werde ich mit den Rivados verhandeln. Natürlich können wir diesen schmutzigen Niggern nicht trauen und sie hegen einen Groll gegen uns wegen des Todes ihres Zauberers, aber jedes Problem kann mit Rum und Essen geglättet werden.";
			link.l1 = "Ich verstehe. Gut, Layton, ich muss gehen...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Warte. Steven hat mir erzählt, dass du versuchst, die Stadt der verlassenen Schiffe irgendwie zu verlassen und hierher zurückzukehren auf einem Schiff?";
			link.l1 = "Das ist der Plan.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Nimm diese Segelanweisungen. Damit kannst du heil hierher zurückkehren. Das bedeutet: du wirst nicht auf den Riffen stranden, du wirst nicht von der Strömung fortgetragen und dein Schiff wird nicht auf die anderen Wracks am äußeren Rand geworfen.\nOhne sie wirst du entweder keinen Durchgang finden oder dein Schiff wird sich hier ihren Schwestern anschließen. Denke daran, dass du ein kleines Schiff mit geringem Tiefgang verwenden musst, um die Untiefen zu passieren. Logger, Schoner, Brigantine, Brig... nichts größer als eine vierte Klasse. Verstanden?";
			link.l1 = "Ja, das tue ich. Danke! Das ist genau das, was ich brauche.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Vergessen Sie nicht, Ihren Laderaum mit Vorräten zu füllen. Ich werde sie Ihnen zu einem guten Preis verkaufen. Zeigen Sie dieses Dokument niemandem, unsere Basis muss geheim bleiben. Ich gebe Ihnen dieses Dokument nur, weil Steven selbst es Ihnen geben wollte, und Sie sind ein Freund von Jan Svenson.";
			link.l1 = "Mach dir darüber keine Sorgen. Danke nochmals und bis bald!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "Haben Sie Fortschritte beim Entkommen aus der Stadt der verlassenen Schiffe gemacht, "+pchar.name+"?";
			link.l1 = "Noch keine Fortschritte, Layton. Ich arbeite daran.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Hier bist du, "+pchar.name+". Ich habe ein paar Dinge mit Ihnen zu besprechen.";
			link.l1 = "Soweit ich verstanden habe, haben Sie nach seinem Tod Stevens Position eingenommen. Sind Sie jetzt also der Admiral?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Genau. Als Zweiter im Befehl bin ich jetzt der Admiral. Einwände?";
			link.l1 = "Keine Einwände. Sie haben jedes Recht, diese Position zu behalten.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Ich bin froh, dass wir uns verstehen. Lass mich wissen, wenn du etwas brauchst.";
			link.l1 = "Wirst du Rache an den Narwalen für Stevens Tod nehmen?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Meinst du, ich werde ihnen den Krieg erklären? Nein. Es gibt bessere Wege, sie zahlen zu lassen. Ich werde den Preis, den sie für Vorräte bezahlen, verdreifachen\nWenn sie 'San Augustine' angreifen, werden wir ihnen die Hölle heiß machen. Außerdem haben wir jetzt gute Beziehungen zu den Rivados, also werden die Narwale nichts riskieren, um dumm zu handeln.";
			link.l1 = "Ich verstehe. Möchten Sie mir noch etwas sagen? Oder kann ich jetzt gehen?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Ich schon. Ich sehe nur einen Weg, wie wir die Narwale bekommen können. Es ist nicht perfekt, aber ich sehe keine Alternative. Wir werden sie von zwei Richtungen aus angreifen. Eine Gruppe von kühnen Halsabschneidern auf Langbooten wird die 'Ceres Schmiede' entern, während eine zweite Gruppe zusammen mit den Rivados die 'Esmeralda' stürmen wird. Dies wird sie entweder vollständig eliminieren, oder sie werden zur 'San Gabriel' fliehen. Das zweite Szenario ist das wahrscheinlichste, die San Gabriel ist eine stark befestigte Position und ihre Belagerung wird lange dauern. Aber so oder so, wir werden gewinnen.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "Wir warten auf die Ergebnisse Ihres Gesprächs mit Donald Greenspen. Es ist eine sehr wichtige Angelegenheit, also verschwenden Sie keine Zeit.";
			link.l1 = "Ich bin auf dem Weg!";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Ja, ich habe die Karte. Möchten Sie sie kaufen? Sie sind willkommen, wenn Sie möchten. Sie gehört Ihnen für nur zweihundert Dublonen.";
			link.l1 = "Wie wäre es mit Pesos?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "Nein. Ich will Gold. Kein Feilschen wird helfen.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 200)
			{
				link.l1 = "Gut. Nimm dein Gold, ich stimme zu.";
				link.l1.go = "map_2";
			}
			link.l2 = "Ich habe nicht so viel Gold. Vielleicht später...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveItems(pchar, "gold_dublon", 200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Schöner Handel, Junge! Nimm deine Karte. Sie ist den Preis wert - ich bin eine ganze Woche durch die Stadt gekrochen, um sie zu zeichnen, also habe ich sie dir eigentlich ziemlich billig verkauft.";
			link.l1 = "Günstig?! Sicher. Naja, danke trotzdem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Halt, Kumpel! Ja, Shark hatte recht, dieser Kerl ist verrückt geworden. So viele Männer sind wegen ihm gestorben... Fesselt ihn, Jungs, und werft ihn ins Verlies!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steven hat mich an seiner Stelle zum Admiral der Stadt gemacht - ich nehme an, dass du und er zusammen in die Karibik zurückkehren. Ich werde hier bleiben und das Geschäft weiterführen, Steven und ich sind nicht bereit, eine so großartige Basis zu verlieren. Und ich möchte dir sagen, dass du hier immer ein willkommener Gast sein wirst.";
			link.l1 = "Danke, Layton. Ich denke, ich werde oft auf deine Insel zurückkehren.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "Ach, mein alter Freund "+GetFullName(pchar)+"! Sie haben es geschafft, die Stadt der verlassenen Schiffe mit Stevens Segelanweisungen zu finden, nicht wahr? Ich bin sehr, sehr froh, Sie zu sehen. Sie sind hier immer ein willkommener Gast.";
			link.l1 = "Danke, Layton. Ich glaube, ich werde oft in deine Stadt zurückkehren.";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Sehr gut. Haben Sie Essen zum Verkauf? Ich bin bereit, es Ihnen für das Doppelte des üblichen Preises abzukaufen.";
			if (iTrade > 0)
			{
				link.l1 = "Ja, ich kann Ihnen einige Vorräte verkaufen.";
				link.l1.go = "trade";
			}
			link.l2 = "Leider habe ich im Moment nichts zu verkaufen.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Schade. Vergessen Sie nicht, es nächstes Mal mitzubringen - ich werde gut bezahlen.";
			link.l1 = "Gut. Ich werde versuchen, es nicht zu vergessen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Wie viel?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "Verdammt, du bist steinbesoffen, Kumpel! Ich bin beeindruckt! Geh schlafen, wir handeln später.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Ich werde meinen Arsch nicht mal für so einen lächerlichen Betrag vom Stuhl heben. Bring mir mehr!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "Und wie willst du segeln, ohne Vorräte auf deinem Schiff, Kumpel? Willst du, dass deine Jungs verhungern? Behalte wenigstens "+FindRussianQtyString(GetCrewQuantity(pchar))+" für dich selbst.";
				link.l1 = "Hm, du hast recht.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Wow, Kumpel, das ist zu viel für uns! Wir werden es nicht schaffen, es zu essen, bevor es verfault. Im Moment kann ich nicht mehr nehmen als "+iTemp+".";
			 link.l1 = "Was auch immer du sagst.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? Gut. Ich werde dich bezahlen "+FindRussianMoneyString(iMoney)+". Abgemacht?";
			link.l1 = "Sicher! Schön, Geschäfte mit dir zu machen!";
			link.l1.go = "trade_2";
			link.l2 = "Hm. Nein, ich habe meine Meinung geändert.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Abgemacht. Ich werde dich bezahlen "+FindRussianMoneyString(iMoney)+" für die Waren. Ist es genug?";
			link.l1 = "Sicher! Schöner Handel!";
			link.l1.go = "trade_4";
			link.l2 = "Hm. Nein, ich habe meine Meinung geändert.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Verdammt nochmal! Mein Lagerhaus ist voll! Ich muss für das nächste halbe Jahr keine Vorräte kaufen.";
				link.l1 = "Gut. Dann werde ich Ihnen in sechs Monaten die nächste Ladung Proviant bringen.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Großartig! Bring mir das nächste Mal mehr.";
				link.l1 = "Sicher!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Schön! Mein Lager ist jetzt voll. Ich muss die nächsten sechs Monate keine Lebensmittel kaufen.";
				link.l1 = "Gut. Dann bringe ich die nächste Ladung Vorräte in sechs Monaten zu dir.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Großartig! Bringen Sie mir nächstes Mal mehr.";
				link.l1 = "Sicher!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+"! Froh dich zu sehen! Was willst du?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Möchten Sie einige Vorräte von mir kaufen?";
				link.l1.go = "trade";
			}
			link.l2 = "Es ist nichts, wollte nur wissen, wie es dir geht.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
