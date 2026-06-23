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
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Non, ce n'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... Et où est Molligan ? Ne voulait-il pas me voir lui-même ?";
				link.l1 = "Notre pauvre Paul a la fievre. Il n'est pas d'humeur a faire du commerce. Je suis ici a sa place.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Que voulez-vous, Monsieur ?";
				link.l1 = "Je suppose que vous attendez pour acheter du bois de fer ?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Qui vous a raconté ces balivernes, Monsieur ? Je n'attends ni personne ni quoi que ce soit. Mon navire patrouille dans la région par ordre du gouverneur de Willemstad. Alors, seriez-vous assez aimable de quitter mon navire, vous devez vous tromper.";
			link.l1 = "Hm... Je vois. Je suis désolé de vous importuner.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "N'avons-nous pas déjà eu cette conversation, monsieur ?";
			link.l1 = "Oui, oui. Je pars et j'embarque déjà sur mon navire.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "Et qui es-tu ?";
			link.l1 = "Ne te soucies-tu pas avec qui tu fais du commerce ? J'ai apporté du bois de fer à vendre. Combien ?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Selon l'accord - quarante doublons par pièce.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Mon pote, on avait un accord avec Molligan. C'est un bon prix, tu n'en trouveras pas de meilleur. Alors ne te comporte pas comme un paysan à la boutique. Combien de bois de fer as-tu ?";
			link.l1 = ""+FindRussianQtyString(int(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = int(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Splendide. C'est plus que ce à quoi je m'attendais. Tiens, prends l'or. Si tu obtiens plus de bois de fer, va à la taverne de Saint-Martin et parle à... tu sais qui. Il organisera une rencontre pour nous. Je vois que tu es un bien meilleur partenaire que cet imbécile de Molligan.";
				link.l1 = "Très bien. Marché conclu.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Bien. Tiens, prends l'or. Si tu obtiens plus de bois de fer, rends-toi à la taverne de Philipsburg et parle à... tu sais qui. Il prendra contact avec moi. Je vois que nous pouvons faire affaire avec toi aussi bien qu'avec cet imbécile de Molligan.";
				link.l1 = "D'accord. C'est un marché.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... Je m'attendais à plus. Soit. Tiens, prends l'or. Et dis à Molligan que la prochaine fois, il doit apporter un lot de pas moins de cent pièces.";
				link.l1 = "Très bien. Je vais lui dire.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Tu te moques de moi ? Nous avions un accord avec Molligan, le lot ne doit pas être inférieur à cinquante pièces ! Dégage et ne reviens pas tant que tu n'en as pas assez.";
			link.l1 = "D'accord, d'accord, calme-toi.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = int(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = int((iTemp*40-2000)/2);
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
			dialog.text = "Oh, mon vieil ami ! Tu as du bois de fer à vendre ?";
			link.l1 = "Exactement, Michel. Faisons du commerce.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Combien as-tu? J'ai besoin d'un lot pas plus petit que "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= int(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Je le sais. J'ai "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  de bois de fer que vous êtes si pressé d'obtenir.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hum. Malheureusement, je n'ai pas autant.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Merde, ne t'ont-ils pas prévenu ? Ou les rats ont-ils rongé le bois ? J'ai besoin "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value))+" et pas une pièce de moins. La prochaine fois, apportez-moi autant de bois que mon agent vous dit. J'espère que vous ne me décevrez pas à nouveau, sinon je devrai refuser vos services.";
				link.l1 = "D'accord, Monsieur, je serai plus attentif à l'avenir.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (int(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Tu me roules dans la farine pour la deuxième fois. Je n'aime pas ça. Sache que c'est le dernier avertissement, la prochaine fois je refuserai tes services.";
					link.l1 = "Les maudits rats ont abîmé mes marchandises ! Je te promets, Michael, que c'était la dernière fois.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "Et maintenant ma patience est à bout ! Je ne veux plus faire affaire avec toi. Fiche le camp et oublie-moi.";
					link.l1 = "Mais Monsieur...";
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
			else npchar.quest.bakaut_angry = int(npchar.quest.bakaut_angry)+1;
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
			if (iTemp > int(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Waouh ! Je suis désolé, ami, mais je ne peux acheter que "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value)+20)+", je n'ai pas d'argent pour tout votre chargement. J'attendais un lot de "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value))+" pièces pour quarante doublons chacune...";
				link.l1 = "Bien. Prends "+FindRussianQtyString(int(pchar.GenQuest.Bakaut.Value)+20)+" maintenant et je te vendrai le reste la prochaine fois.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = int(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Très bien. Le prix est le même que d'habitude, quarante doublons pour chaque pièce.";
				link.l1 = "Ça me va. Prends ton lot.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "C'est un plaisir de faire affaire avec vous. Revenez me voir si vous voulez vendre plus de bois de fer.";
			link.l1 = "Je vous reverrai, Monsieur. Notre collaboration est très profitable pour moi. Adieu!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = int(npchar.quest.bakaut);
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
