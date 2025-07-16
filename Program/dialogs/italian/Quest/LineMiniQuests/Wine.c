void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Questo è un maledetto bug. Avverti gli sviluppatori, per mille balene.";
			link.l1 = "Sicuro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Hai portato la bottiglia?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Già, l’ho fatto. Ho sborsato 700 pesos per quella roba, dunque da te mi aspetto almeno 1000 pesos.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "No, ci sto ancora lavorando.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Sia lodato il Signore, stavo per morire di sete. Grazie di cuore, capitano! Tieni, prendi i tuoi mille e io mi tengo la bottiglia, ahah! Senti, già che facciamo affari così bene, avrei un’altra richiesta da farti.\nPotresti procurarci altro vino per me e i miei compari, per... usi futuri? Abbiamo appena spennato una banda di contrabbandieri, quindi monete ne abbiamo, eh eh...";
			link.l1 = "Scusa compare, non ho tempo per andare di nuovo a procacciarti del rum.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "I soldi fanno sempre comodo. Quante bottiglie ti servono?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Come desideri. Grazie comunque per l'aiuto! Alla salute e alla tua fortuna!";
			link.l1 = "Continua così, soldato!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "A mille pezzi da otto a bottiglia, possiamo permetterci di comprarne sessanta, ma non di più. Però non portarcene meno di dieci, eh – ci verrebbe solo più sete!";
			link.l1 = "Inteso, non più di 60 bottiglie e non meno di dieci. Ti porterò il tuo vino.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Benedetti siano quei piedi che portano novelle di buon bere! Conto su di voi, capitano. Ah, quasi mi scordavo! Dovrete far arrivare il rum qui in meno di una settimana, ché la mia compagnia di marinai salpa per la flotta tra sette giorni e spariremo in mare per un paio di mesi appena molleremo gli ormeggi.";
			link.l1 = "Capisco. Cercherò di sbrigarmi.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "Allora, capitano, hai portato il vino?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Sì, ce l'ho.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "No.    Ci sto ancora lavorando.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Santo Arnolfo, pregate per noi! Quello è un mare di vino! Splendido! Purtroppo, come dicevo, possiamo permetterci solo sessanta bottiglie, non abbiamo abbastanza dobloni per acquistarne di più. Prendi i tuoi pesos e io custodirò queste sessanta bottiglie. Tieni pure il resto.";
				link.l1 = "Grazie. Assicurati che tu e i tuoi compagni d'arme alziate un bicchiere alla mia salute!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Bentornato. Vediamo un po'... Hai portato "+sti(pchar.questTemp.Wine.Qty)+" bottiglie. Ottimo! Le prendo io. Ecco il pagamento: "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Grazie. Mi raccomando, tu e i tuoi compari d'arme alzate un boccale alla mia salute!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "Ci puoi scommettere, "+GetAddress_Form(NPChar)+"! Il tamburo suona la raccolta, devo andare ora. Addio!";
			link.l1 = "Venti propizi e mari favorevoli, compare!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
