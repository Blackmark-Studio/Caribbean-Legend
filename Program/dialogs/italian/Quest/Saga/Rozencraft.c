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
			dialog.text = "Desideri qualcosa?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hmm... E dov’è finito Molligan? Non voleva mica vedermi di persona?";
				link.l1 = "Il nostro povero Paul ha la febbre. Non ha testa per fare affari oggi. Sono io qui al suo posto.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Cosa desiderate, messere?";
				link.l1 = "Immagino che tu stia aspettando di acquistare un po’ di legno di ferro?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Chi ti ha raccontato queste fandonie, signore? Non sto aspettando né anima viva né cosa alcuna. La mia nave pattuglia queste acque per ordine del governatore di Willemstad. Dunque, saresti tanto gentile da lasciare il mio vascello? Devi aver sbagliato nave.";
			link.l1 = "Hm... Capisco. Mi rincresce d'avervi importunato.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Non abbiamo già avuto questa chiacchierata, signore?";
			link.l1 = "Sì, sì. Me ne vado e sto già salendo a bordo della mia nave.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "E tu chi saresti?";
			link.l1 = "Non t’importa con chi fai affari? Ho portato del legno di ferro da vendere. Quanto mi dai?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Secondo l’accordo – quaranta dobloni a cranio.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Compare, avevamo un patto con Molligan. Questo è un buon prezzo, non ne troverai uno migliore. Quindi non fare il contadino al mercato. Quanta legna di ferro hai con te?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Splendido. È più di quanto mi aspettassi. Prendi l’oro, dunque. Se metti le mani su altro legno di ferro, vai alla taverna di Saint Martin e parla con... sai tu chi. Lui organizzerà un incontro tra noi. Vedo che sei un socio ben migliore di quel babbeo di Molligan.";
				link.l1 = "D'accordo. Affare fatto.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Bene.   Ecco l’oro. Se trovi altro legno di ferro, vai alla taverna di Philipsburg e parla con... lo sai tu chi. Lui mi farà sapere. Mi pare che con te si possa far affari non peggio, che con quel babbeo di Molligan.";
				link.l1 = "D'accordo. Affare fatto.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... Mi aspettavo di meglio. Va bene. Prendi l’oro. E di’ a Molligan che la prossima volta deve portare non meno di cento pezzi.";
				link.l1 = "Va bene. Glielo dirò io.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Mi prendi in giro? Avevamo un patto con Molligan, la partita doveva essere di almeno cinquanta pezzi! Sparisci e non tornare finché non ne hai abbastanza.";
			link.l1 = "Va bene, va bene, calmati.";
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
			dialog.text = "Oh, vecchio mio! Hai del legno di ferro da smerciare?";
			link.l1 = "Esattamente, Michel. Facciamo uno scambio.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Quanto hai con te? Mi serve una partita non inferiore a "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Lo so. Ho già "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  di legno di ferro che tanto brami ottenere.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Ahimè, non ne ho così tanto.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Maledizione, non ti hanno avvertito? O sono stati i topi a rosicchiare il legno? Ho bisogno di "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" e non un pezzo di meno. La prossima volta portami tanto legname quanto ti dice il mio uomo. Spero proprio che non mi deluderai di nuovo, altrimenti sarò costretto a rinunciare ai tuoi servigi.";
				link.l1 = "D'accordo, signor mio, in futuro starò più attento.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Mi stai fregando per la seconda volta. Non mi va affatto. Sappi che questa è l’ultima ammonizione, la prossima volta rifiuterò i tuoi servigi.";
					link.l1 = "Maledetti topi hanno rovinato la mia merce! Te lo giuro, Michel, che questa è stata l'ultima volta.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "E adesso la mia pazienza è finita! Non voglio più averci a che fare con te. Sparisci e dimenticati di me.";
					link.l1 = "Ma signor mio...";
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
				dialog.text = "Perdinci! Mi dispiace, compare, ma posso acquistare solo "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+", Non ho denaro per tutta la tua merce. Mi aspettavo solo una partita di "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" pezzi a quaranta dobloni l’uno...";
				link.l1 = "Va bene. Prendi "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" ora e ti venderò il resto la prossima volta.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Benissimo. Il prezzo è quello di sempre, quaranta dobloni per ogni pezzo.";
				link.l1 = "Va bene per me. Prendi la tua parte.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "È stato un piacere fare affari con te. Torna pure da me se vuoi vendere altro legno di ferro.";
			link.l1 = "Ci rivedremo, signore. La nostra collaborazione mi riempie le tasche d’oro. Addio!";
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
